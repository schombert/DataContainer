//
// This file provided as part of the DataContainer project
//

#include <string>
#include <vector>
#include <fstream>
#include <filesystem> 
#include <iostream> 
#include <algorithm>

#include "parsing.hpp"
#include "code_fragments.hpp"



[[noreturn]] void error_to_file(std::string const& file_name, std::string const& message) {
	std::fstream fileout;
	fileout.open(file_name, std::ios::out);
	if(fileout.is_open()) {
		fileout << message;
		fileout.close();
	}
	std::abort();
}

relationship_object_def* better_primary_key(relationship_object_def* oldr, relationship_object_def* newr) {
	if(oldr == nullptr) {
		return newr;
	}

	if(oldr->is_expandable && !newr->is_expandable)
		return newr;

	switch(oldr->store_type) {
		case storage_type::contiguous:
		{
			switch(newr->store_type) {
				case storage_type::contiguous:
					return oldr->size <= newr->size ? oldr : newr;
				case storage_type::compactable:
				case storage_type::erasable:
					return oldr;
			}
			break;
		}
		case storage_type::erasable:
		{
			switch(newr->store_type) {
				case storage_type::contiguous:
					return newr;
				case storage_type::erasable:
					return oldr->size <= newr->size ? oldr : newr;
				case storage_type::compactable:
					return oldr;
			}
			break;
		}
		case storage_type::compactable:
		{
			switch(newr->store_type) {
				case storage_type::contiguous:
				case storage_type::erasable:
					return newr;
				case storage_type::compactable:
					return oldr->size <= newr->size ? oldr : newr;
			}
			break;
		}
	}

	return oldr;
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		std::fstream input_file;
		input_file.open(argv[1], std::ios::in);

		const std::string output_file_name = [otemp = std::string(argv[1])]() mutable {
			if(otemp.length() >= 4 && otemp[otemp.length() - 4] == '.') {
				otemp[otemp.length() - 3] = 'h';
				otemp[otemp.length() - 2] = 'p';
				otemp[otemp.length() - 1] = 'p';
				return otemp;
			}
			return otemp + ".cpp";
		}();


		if(!input_file.is_open()) {
			error_to_file(output_file_name, std::string("Could not open input file: ") + argv[1]);
		}

		
		error_record err;
		
		std::string file_contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
		
		file_def parsed_file = parse_file(file_contents.c_str(), file_contents.c_str() + file_contents.length(), err);

		if(err.accumulated.length() > 0)
			error_to_file(output_file_name, err.accumulated);

		input_file.close();

		// patchup relationship pointers & other information

		for(auto& r : parsed_file.relationship_objects) {
			if(r.is_relationship) {
				for(auto& l : r.indexed_objects) {
					if(auto linked_object = find_by_name(parsed_file, l.type_name); linked_object) {
						l.related_to = linked_object;
					} else {
						error_to_file(output_file_name, std::string("Could not find object named: ") + l.type_name + " in relationship: " + r.name);
					}
					if(l.index == index_type::at_most_one) {
						r.primary_key.points_to = better_primary_key(r.primary_key.points_to, l.related_to);
						r.primary_key.property_name = l.property_name;
					}
				}

				

				if(r.indexed_objects.size() <= 1) {
					error_to_file(output_file_name, std::string("Relationship: ") + r.name + " is between too few objects");
				}

				
				if(r.force_pk.length() > 0) {
					bool pk_forced = false;
					for(auto& link : r.indexed_objects) {
						if(link.property_name == r.force_pk && link.index == index_type::at_most_one) {
							r.primary_key.points_to = link.related_to;
							r.primary_key.property_name = link.property_name;
							pk_forced = true;
						}
					}
					if(!pk_forced) {
						error_to_file(output_file_name, std::string("Was unable to use ") + r.force_pk + std::string(" as a primary key for relationship: ") + r.name);
					}
				}

				for(auto& link : r.indexed_objects) {
					if(link.index != index_type::none)
						link.related_to->relationships_involved_in.push_back(in_relation_information{ r.name, link.property_name,
							r.primary_key.points_to == link.related_to, link.index, link.ltype, &r });
				}

				if(r.primary_key.points_to) {
					r.size = r.primary_key.points_to->size;
					r.store_type = storage_type::contiguous;
					r.is_expandable = r.primary_key.points_to->is_expandable;
				}

			} // end if is a relationship
		} // patchup relationship pointers loop

		// compile list of objects that need serailization stubs
		std::vector<std::string> needs_serialize;
		std::vector<std::string> needs_load_only;

		for(auto& r : parsed_file.relationship_objects) {
			for(auto& p : r.properties) {
				if(p.type == property_type::object) {
					if(std::find(needs_serialize.begin(), needs_serialize.end(), p.data_type) == needs_serialize.end()) {
						needs_serialize.push_back(p.data_type);
						parsed_file.object_types.push_back(p.data_type);
					}
				}
			}
		}
		for(auto &lt : parsed_file.legacy_types) {
			if(std::find(needs_serialize.begin(), needs_serialize.end(), lt) == needs_serialize.end()
				&& std::find(needs_load_only.begin(), needs_load_only.end(), lt) == needs_load_only.end()) {
				needs_load_only.push_back(lt);
				parsed_file.object_types.push_back(lt);
			}
		}

		// identify vectorizable types
		for(auto& ob : parsed_file.relationship_objects) {
			for(auto& prop : ob.properties) {
				if(prop.type == property_type::other && is_vectorizable_type(parsed_file, prop.data_type))
					prop.type = property_type::vectorizable;
			}
		}

		// compose contents of generated file
		std::string output;

		basic_builder o;
		//includes
		output += "#pragma once\n";
		output += "#include <cstdint>\n";
		output += "#include <cstddef>\n";
		output += "#include <utility>\n";
		output += "#include <vector>\n";
		output += "#include <algorithm>\n";
		output += "#include <cassert>\n";
		output += "#ifndef DCON_NO_VE\n";
		output += "#include \"ve.hpp\"\n";
		output += "#endif\n";
		for(auto& i : parsed_file.includes) {
			output += "#include ";
			output += i;
			output += "\n";
		}

		//open new namespace
		output += "\n";

		output += "#ifdef NDEBUG\n";
		output += "#ifdef _MSC_VER\n";
		output += "#define DCON_RELEASE_INLINE __forceinline\n";
		output += "#else\n";
		output += "#define DCON_RELEASE_INLINE inline __attribute__((always_inline))\n";
		output += "#endif\n";
		output += "#else\n";
		output += "#define DCON_RELEASE_INLINE inline\n";
		output += "#endif\n";

		output += "\n";
		output += "namespace " + parsed_file.namspace + " {\n";

		//load record type
		output += make_load_record(o, parsed_file).to_string(1);
		

		//id types definitions
		for(auto& ob : parsed_file.relationship_objects) {
			if(ob.primary_key.points_to == nullptr) {
				const auto underlying_type = ob.is_expandable ? std::string("uint32_t") : size_to_tag_type(ob.size);
				//id class begin
				output += make_id_definition(o, ob.name, underlying_type).to_string(1);
			} else {
				output += "\tusing " + ob.name + "_id = " + ob.primary_key.points_to->name + "_id;\n\n";
			}
		}

		// close namespace briefly
		output += "}\n\n";

		//mark each id as going into a tagged vector
		output += "namespace ve {\n";
		for(auto& ob : parsed_file.relationship_objects) {
			if(ob.primary_key.points_to == nullptr) {
				output += make_value_to_vector_type(o, parsed_file.namspace + "::" + ob.name + "_id").to_string(1);
			}
		}
		output += "}\n\n";


		//reopen namespace
		output += "namespace " + parsed_file.namspace + " {\n";

		//predeclare data_container
		output += "\tclass data_container;\n\n";

		//write internal classes

		//open internal namespace
		output += "\tnamespace internal {\n";

		for(auto& ob : parsed_file.relationship_objects) {
			//object class begin
			output += "\t\tclass alignas(64) " + ob.name + "_class {\n";

			//begin members declaration

			output += "\t\t\tprivate:\n";
			output += "\t\t\tuint32_t size_used = 0;\n";
			if(ob.store_type == storage_type::erasable) {
				output += make_member_container(o, "_index", ob.name + "_id",
					std::to_string(ob.size), struct_padding::none, ob.is_expandable).to_string(3);
			}

			for(auto& p : ob.properties) {
				if(p.is_derived) {
					// no data for a derived property
				} else if(p.type == property_type::bitfield) {
					output += make_member_container(o, p.name, "dcon::bitfield_type",
						std::string("((uint32_t(") + std::to_string(ob.size) + " + 7)) / 8ui32 + 63ui32) & ~63ui32",
						struct_padding::fixed, ob.is_expandable).to_string(3);
				} else if(p.type == property_type::object) {
					output += make_member_container(o, p.name, p.data_type,
						std::to_string(ob.size),
						struct_padding::none, ob.is_expandable).to_string(3);
				} else if(p.type == property_type::special_vector) {
					//fill in with special vector type and pool object
					output += make_member_container(o, p.name, "dcon::stable_mk_2_tag",
						std::to_string(ob.size),
						struct_padding::none, ob.is_expandable, "std::numeric_limits<dcon::stable_mk_2_tag>::max()").to_string(3);
					
					output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + p.data_type + ", 16, " + std::to_string(p.special_pool_size) + " > " + p.name + "_storage;\n";
				} else {
					output += make_member_container(o, p.name, p.data_type,
						expand_size_to_fill_cacheline_calculation(p.data_type, ob.size),
						struct_padding::calculated, ob.is_expandable).to_string(3);
				}
			} //end non relationship members

			// begin relationship members
			for(auto& i : ob.indexed_objects) {
				if(ob.primary_key == i) {
					//skip recording index value
				} else {
					output += make_member_container(o, i.property_name, i.type_name + "_id",
						expand_size_to_fill_cacheline_calculation(i.type_name + "_id", ob.size),
						struct_padding::calculated, ob.is_expandable).to_string(3);
				}

				if(i.index == index_type::many) {
					if(i.ltype == list_type::list) {
						// list intrusive links
						output += make_member_container(o, std::string("link_") + i.property_name, i.type_name + "_id",
							std::to_string(ob.size),
							struct_padding::none, ob.is_expandable).to_string(3);

						output += make_member_container(o, std::string("head_back_") + i.property_name, ob.name + "_id",
							expand_size_to_fill_cacheline_calculation(ob.name + "_id", i.related_to->size),
							struct_padding::calculated, i.related_to->is_expandable).to_string(3);

					} else if(i.ltype == list_type::std_vector) {
						//array of relation ids in object
						output += make_member_container(o, std::string("array_") + i.property_name,
							std::string("std::vector<") + ob.name + "_id>",
							std::to_string(i.related_to->size),
							struct_padding::none, i.related_to->is_expandable).to_string(3);
					} else if(i.ltype == list_type::array) {
						//array of relation ids in object
						if(!i.related_to->is_expandable) {
							output += make_member_container(o, std::string("array_") + i.property_name,
								"dcon::stable_mk_2_tag values",
								std::to_string(i.related_to->size),
								struct_padding::none, i.related_to->is_expandable,
								"std::numeric_limits<dcon::stable_mk_2_tag>::max()").to_string(3);

							output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + i.type_name + "_id, 16, " + std::to_string(ob.size * 2) + " > "
								+ i.property_name + "_storage;\n";
						} else {
							error_to_file(output_file_name, std::string("Unable to estimate an upper bound on storage space for ") +
								ob.name + " " + i.property_name + " arrays because the target is expandable");
						}

					}
				} else if(i.index == index_type::at_most_one) {
					if(ob.primary_key == i) {
						// no link back for primary key
					} else {
						output += make_member_container(o, std::string("link_back_") + i.property_name, ob.name + "_id",
							expand_size_to_fill_cacheline_calculation(ob.name + "_id", i.related_to->size),
							struct_padding::calculated, i.related_to->is_expandable).to_string(3);
					}
				}
			} // end relationship members



			output += "\n";
			output += "\t\t\tpublic:\n";

			// constructor
			if(ob.store_type == storage_type::erasable && !ob.is_expandable) {
				output += make_erasable_object_constructor(o, ob.name, ob.size).to_string(3);
			}

			//object class end
			output += "\t\t\tfriend class data_container;\n";
			output += "\t\t};\n\n";
		}

		//close internal namespace
		output += "\t}\n\n";

		//class data_container begin
		output += "\tclass alignas(64) data_container {\n";
		output += "\t\tpublic:\n";
		for(auto& ob : parsed_file.relationship_objects) {
			output += "\t\tinternal::" + ob.name + "_class " + ob.name + ";\n";
		}
		output += "\n";

		for(auto& ob : parsed_file.relationship_objects) {
			const std::string id_name = (ob.primary_key.points_to ? ob.primary_key.points_to->name : ob.name) + "_id";

			//getters and setters
			for(auto& p : ob.properties) {
				// hook stubs
				if(p.hook_get) {
					output += make_hooked_getters(o, ob.name, p.name, p.data_type,
						p.type == property_type::bitfield ? hook_type::bitfield :
						(p.type == property_type::vectorizable ? hook_type::vectorizable : hook_type::other),
						ob.is_expandable).to_string(2);
				}
				if(p.hook_set) {
					output += make_hooked_setters(o, ob.name, p.name, p.data_type,
						p.type == property_type::bitfield ? hook_type::bitfield :
						(p.type == property_type::vectorizable ? hook_type::vectorizable : hook_type::other),
						ob.is_expandable).to_string(2);
				}

				if(p.is_derived) {
					
				} else if(p.type == property_type::bitfield) {
					if(!p.hook_get)
						output += make_bitfield_getters(o, ob.name, p.name, ob.is_expandable).to_string(2);
					if(!p.hook_set) 
						output += make_bitfield_setters(o, ob.name, p.name, ob.is_expandable).to_string(2);
				} else if(p.type == property_type::object) {
					if(!p.hook_get)
						output += make_object_getters(o, ob.name, p.name, p.data_type).to_string(2);
					if(!p.hook_set)
						output += make_object_setters(o, ob.name, p.name, p.data_type).to_string(2);
				} else if(p.type == property_type::special_vector) {
					if(!p.hook_get)
						output += make_special_array_getters(o, ob.name, p.name, p.data_type).to_string(2);
					if(!p.hook_set) 
						output += make_special_array_setters(o, ob.name, p.name, p.data_type).to_string(2);
				} else if(p.type == property_type::vectorizable) {
					if(!p.hook_get)
						output += make_vectorizable_type_getters(o, ob.name, p.name, p.data_type, ob.is_expandable).to_string(2);
					if(!p.hook_set)
						output += make_vectorizable_type_setters(o, ob.name, p.name, p.data_type, ob.is_expandable).to_string(2);
				} else { // nonvectorizable data type w/o special handling
					if(!p.hook_get)
						output += make_object_getters(o, ob.name, p.name, p.data_type).to_string(2);
					if(!p.hook_set)
						output += make_object_setters(o, ob.name, p.name, p.data_type).to_string(2);
				}
			} // end loop over each property

			// creation / deletion / move hook routines
			if(ob.hook_create) {
				output += "\t\tvoid on_create_" + ob.name + "(" + id_name + " id);\n";
			}
			if(ob.hook_delete) {
				output += "\t\tvoid on_delete_" + ob.name + "(" + id_name + " id);\n";
			}
			if(ob.hook_move) {
				output += "\t\tvoid on_move_" + ob.name + "(" + id_name + " new_id," + id_name + " old_id);\n";
			}

			output += "\t\tuint32_t " + ob.name + "_size() const noexcept { return " + ob.name + ".size_used; }\n\n";
		} // end getters / setters creation loop over relationships / objects



		/*
			relationship design:

			each relationship entry contains one id for each related object not the primary key = m_ property_name

			if the object(s) related to are of the many type, then either: each relationship entry contains an intrusive linked list = m_link_ property_name
				(and related object contains a reference back to the head relationship entry = m_head_back_ property_name)
			or if it is of the array type the object related to gets an array with the indexes of all the relationship ids of this type it appears in
				= m_array_ property_name and possibly property_name _storage

			if the object(s) are of single type and not the primary key,
				it has an entry referencing the relationship entry = m_link_back_ property_name,
				if any (the primary key object, can find its relationship by its own key -- check wether the relationship exists by seeing whether
				the other references in the relationship are set)

			provided functions :
				object related by many -> for each over relationships where it is in a particular position
					-> also expose range if it is array type

				object related by one (and indexed) / the relationship itself by name : get / set for any properties (and get other by one related values)

				find relationship: fill in all related objects -> returns existing relationship if it exists (uses index if possible)

				try_create relationship : /create if the relationship is new -- if there is an index/, and if no other relationships have to be destroyed
				force_create relationship : /do nothing if it already exists -- by index/, break any other conflicting relations
				delete relationship
			*/

		for(auto& r : parsed_file.relationship_objects) {

			for(auto& i : r.indexed_objects) {
				if(i.index == index_type::at_most_one && r.primary_key == i) {
					output += make_relation_pk_getters_setters(o, r.name, i.property_name, r.is_expandable).to_string(2);
					output += make_relation_pk_reverse_getters_setters(o, r.name, i.property_name, i.type_name,
						i.related_to->is_expandable, false).to_string(2);

					bool is_only_of_type = true;
					for(auto ir : r.indexed_objects) {
						if(ir.type_name == i.type_name && ir.property_name != i.property_name)
							is_only_of_type = false;
					}
					if(is_only_of_type) {
						output += make_relation_pk_reverse_getters_setters(o, r.name, i.property_name, i.type_name,
							i.related_to->is_expandable, true).to_string(2);
					}
				} else if(i.index == index_type::at_most_one) {
					output += make_relation_unique_non_pk_getters_setters(o, r.name,
						i.property_name, i.type_name, r.is_expandable).to_string(2);
					output += make_relation_unique_non_pk_reverse_getters_setters(o, r.name,
						i.property_name, i.type_name, i.related_to->is_expandable, false).to_string(2);
					
					bool is_only_of_type = true;
					for(auto ir : r.indexed_objects) {
						if(ir.type_name == i.type_name && ir.property_name != i.property_name)
							is_only_of_type = false;
					}

					if(is_only_of_type) { //make shortcut function names
						output += make_relation_unique_non_pk_reverse_getters_setters(o, r.name,
							i.property_name, i.type_name, i.related_to->is_expandable, true).to_string(2);
					}
				} else if(i.index == index_type::many) {
					output += make_relation_many_getters_setters(o, r.name, i.ltype,
						i.property_name, i.type_name, r.is_expandable).to_string(2);
					output += make_relation_many_reverse_getters_setters(o, r.name, i.ltype,
						i.property_name, i.type_name, i.related_to->is_expandable, false).to_string(2);

					bool is_only_of_type = true;
					for(auto ir : r.indexed_objects) {
						if(ir.type_name == i.type_name && ir.property_name != i.property_name)
							is_only_of_type = false;
					}
					if(is_only_of_type) { // shortcut functions
						output += make_relation_many_reverse_getters_setters(o, r.name, i.ltype,
							i.property_name, i.type_name, i.related_to->is_expandable, true).to_string(2);
					} //end shortcut functions in relationship
				} else if(i.index == index_type::none) {
					output += make_vectorizable_type_getters(o, r.name, i.property_name,
						i.type_name + "_id", r.is_expandable).to_string(2);
					output += make_vectorizable_type_setters(o, r.name, i.property_name,
						i.type_name + "_id", r.is_expandable).to_string(2);
				}// end -- creation of property references getters / setters
			} //end of loop creating individual property getters / setters
		} // end creating relationship getters / setters

		output += "\n";

		for(auto cob : parsed_file.relationship_objects) {
			if(cob.is_relationship) {
				output += make_join_getters_setters(o, cob).to_string(2);
			}
		}

		// creation / deletion routines
		for(auto& cob : parsed_file.relationship_objects) {
			const std::string id_name = cob.name + "_id";

			if(!cob.is_relationship) {
				if(cob.store_type == storage_type::contiguous || cob.store_type == storage_type::compactable) {
					output += make_pop_back(o, cob).to_string(2);
					output += make_object_resize(o, cob).to_string(2);
					output += make_non_erasable_create(o, cob).to_string(2);

					if(cob.store_type == storage_type::compactable) {
						output += make_compactable_delete(o, cob).to_string(2);
					}

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(cob.store_type == storage_type::erasable) {
					output += make_erasable_delete(o, cob).to_string(2);
					output += make_erasable_create(o, cob).to_string(2);
					output += make_object_resize(o, cob).to_string(2);

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && "
						+ cob.name + ".m__index.vptr()[id.index()] == id;\n";
					output += "\t\t}\n";
				}
			} else if(cob.primary_key.points_to) { // primary key relationship
				output += make_object_resize(o, cob).to_string(2);
				output += make_clearing_delete(o, cob).to_string(2);
				
				output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
				output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && " + 
					"is_valid_" + cob.primary_key.points_to->name + "(id) && (";
				for(auto& iob : cob.indexed_objects) {
					if(cob.primary_key != iob) {
						output += "bool(" + cob.name + ".m_" + iob.property_name + ".vptr()[id.index()]) || ";
					}
				}
				output += "false);\n";
				output += "\t\t}\n"; // end is_valid

				output += "\t\tprivate:\n";
				output += make_internal_move_relationship(o, cob).to_string(2);
				output += "\t\tpublic:\n";

				output += make_relation_try_create(o, cob).to_string(2);
				output += make_relation_force_create(o, cob).to_string(2);

			} else { // non pk relationship
				if(cob.store_type == storage_type::contiguous || cob.store_type == storage_type::compactable) {
					output += make_pop_back(o, cob).to_string(2);
					output += make_object_resize(o, cob).to_string(2);
					if(cob.store_type == storage_type::compactable) {
						output += make_compactable_delete(o, cob).to_string(2);
					}

					output += make_relation_try_create(o, cob).to_string(2);
					output += make_relation_force_create(o, cob).to_string(2);

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(cob.store_type == storage_type::erasable) {
					output += make_erasable_delete(o, cob).to_string(2);
					output += make_object_resize(o, cob).to_string(2);

					output += make_relation_try_create(o, cob).to_string(2);
					output += make_relation_force_create(o, cob).to_string(2);

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && "
						+ cob.name + ".m__index.vptr()[id.index()] == id;\n";
					output += "\t\t}\n";
				}
			} // end case relationship no primary key
		} // end creation / deletion reoutines creation loop

		//iterate over all routines
		for(auto& cob : parsed_file.relationship_objects) {
			output += make_iterate_over_objects(o, cob).to_string(2);
		}

		//write save and load object stubs
		output += "\n";
		for(auto& ostr : needs_serialize) {
			output += "\t\tuint64_t serialize_size(" + ostr + " const& obj) const;\n";
			output += "\t\tvoid serialize(std::byte*& output_buffer, " + ostr + " const& obj) const;\n";
			output += "\t\tvoid deserialize(std::byte const*& input_buffer, " + ostr + " & obj, std::byte const* end) const;\n";
		}
		for(auto& ostr : needs_load_only) {
			output += "\t\tvoid deserialize(std::byte const*& input_buffer, " + ostr + "& obj, std::byte const* end) const;\n";
		}

		// type conversion stubs
		for(auto& con : parsed_file.conversion_list) {
			if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.to) != parsed_file.object_types.end() ||
				std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
				output += "\t\t" + con.to + " convert_type(" + con.from + " const* source, " + con.to + "* overload_selector) const;\n";
			}
		}

		output += "\n";
		//reset function
		output += "\t\tvoid reset() {\n";
		for(auto& cob : parsed_file.relationship_objects) {
			if(cob.is_relationship)
				output += "\t\t\t" + cob.name + "_resize(0);\n";
		}
		for(auto& cob : parsed_file.relationship_objects) {
			if(!cob.is_relationship)
				output += "\t\t\t" + cob.name + "_resize(0);\n";
		}
		output += "\t\t}\n";

		output += "\n";
		//make ve interface
		output += "\t\t#ifndef DCON_NO_VE\n";
		for(auto& ob : parsed_file.relationship_objects) {
			output += "\t\tve::vectorizable_buffer<float, " + ob.name + "_id> " + ob.name + "_make_vectorizable_float_buffer() const noexcept {\n";
			output += "\t\t\treturn ve::vectorizable_buffer<float, " + ob.name + "_id>(" + ob.name + ".size_used);\n";
			output += "\t\t}\n";
			output += "\t\tve::vectorizable_buffer<int32_t, " + ob.name + "_id> " + ob.name + "_make_vectorizable_int_buffer() const noexcept {\n";
			output += "\t\t\treturn ve::vectorizable_buffer<int32_t, " + ob.name + "_id>(" + ob.name + ".size_used);\n";
			output += "\t\t}\n";
			if(!ob.is_expandable) {
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_serial_over_" + ob.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_serial(" + ob.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#ifndef VE_NO_TBB\n";
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_parallel_over_" + ob.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_parallel_exact(" + ob.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#endif\n";
			} else {
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_serial_over_" + ob.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_serial_unaligned(" + ob.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#ifndef VE_NO_TBB\n";
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_parallel_over_" + ob.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_parallel_unaligned(" + ob.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#endif\n";
			}
		}
		output += "\t\t#endif\n";

		

		output += "\n";
		
		for(auto& rt : parsed_file.load_save_routines) {
			output += make_serialize_plan_generator(o, parsed_file, rt).to_string(2);
		}
		output += make_serialize_all_generator(o, parsed_file).to_string(2);

		output += make_serialize_size(o, parsed_file).to_string(2);
		output += make_serialize(o, parsed_file).to_string(2);
		output += make_deserialize(o, parsed_file, false).to_string(2);
		output += make_deserialize(o, parsed_file, true).to_string(2);

		//write globals
		output += "\n";
		for(auto& gstr : parsed_file.globals) {
			output += "\t\t" + gstr + "\n";
		}

		//class data_container end
		output += "\t};\n\n";

		//close new namespace
		output += "}\n";

		output += "\n";


		output += "#undef DCON_RELEASE_INLINE\n";

		//newline at end of file
		output += "\n";

		std::fstream fileout;
		fileout.open(output_file_name, std::ios::out);
		if(fileout.is_open()) {
			fileout << output;
			fileout.close();
		} else {
			std::abort();
		}
	}
}
