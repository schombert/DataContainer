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

		parsing_state pstate = parsing_state::outer;

		file_def parsed_file;
		property_def* last_prop = nullptr;
		relationship_object_def* last_obj = nullptr;
		load_save_def* last_load_save = nullptr;
		int line_count = 0;

		for(std::string line; std::getline(input_file, line, '\n'); ) {
			char const* str_ptr = line.data();
			char const* const str_end = str_ptr + line.size();
			++line_count;

			auto const first_term = extract_string(str_ptr, str_end);
			auto second_term = extract_string(str_ptr, str_end);

			if(first_term == "namespace:") {
				pstate = parsing_state::outer;
				if(second_term.size() > 0)
					parsed_file.namspace = second_term;
			} else if(first_term == "include:") {
				pstate = parsing_state::outer;
				if(second_term.size() > 0)
					parsed_file.includes.emplace_back(second_term);

				while(str_ptr < str_end) {
					auto const extra_term = extract_string(str_ptr, str_end);
					if(extra_term.size() > 0)
						parsed_file.includes.emplace_back(extra_term);
				}
			} else if(first_term == "object:") {
				pstate = parsing_state::in_object_relation;
				if(second_term.size() == 0) {
					error_to_file(output_file_name, std::string("All objects must be named (line: ") + std::to_string(line_count) + ")");
				}
				parsed_file.relationship_objects.emplace_back();
				last_obj = &(parsed_file.relationship_objects.back());
				last_obj->name = second_term;
				last_obj->is_relationship = false;
				last_prop = nullptr;

			} else if(first_term == "relationship:") {
				pstate = parsing_state::in_object_relation;
				if(second_term.size() == 0) {
					error_to_file(output_file_name, std::string("All relationships must be named (line: ") + std::to_string(line_count) + ")");
				}
				parsed_file.relationship_objects.emplace_back();
				last_obj = &(parsed_file.relationship_objects.back());
				last_obj->name = second_term;
				last_obj->is_relationship = true;
				last_prop = nullptr;

			} else if(first_term == "load_save:") {
				pstate = parsing_state::in_load_save;
				if(second_term.size() == 0) {
					error_to_file(output_file_name, std::string("All load/save routines must be named (line: ") + std::to_string(line_count) + ")");
				}
				parsed_file.load_save_routines.emplace_back();
				last_load_save = &(parsed_file.load_save_routines.back());
				last_load_save->name = second_term;
				last_prop = nullptr;

			} else if(first_term == "convert:") {
				pstate = parsing_state::outer;
				parsed_file.conversion_list.push_back(conversion_def{ second_term , extract_string(str_ptr, str_end) });

			} else if(first_term == "global:") {
				pstate = parsing_state::outer;

				std::string gstr;
				if(second_term.size() > 0)
					gstr += second_term;

				while(str_ptr < str_end) {
					auto const extra_term = extract_string(str_ptr, str_end);
					if(extra_term.size() > 0) {
						if(gstr.length() > 0) gstr += " ";
						gstr += extra_term;
					}
				}

				parsed_file.globals.push_back(gstr);

			} else if(first_term == "legacy_type:") {
				pstate = parsing_state::outer;

				if(second_term.size() > 0)
					parsed_file.legacy_types.push_back(second_term);

				while(str_ptr < str_end) {
					auto const extra_term = extract_string(str_ptr, str_end);
					if(extra_term.size() > 0) {
						parsed_file.legacy_types.push_back(extra_term);
					}
				}



			} else if(first_term.size() > 0) {
				switch(pstate) {
					case parsing_state::outer:
					{
						error_to_file(output_file_name, std::string("Unexpected token: ") + first_term + " (line: " + std::to_string(line_count) + ")");
						break;
					}
					case parsing_state::in_object_relation:
					{
						if(first_term == "type:") {
							if(second_term == "contiguous") {
								last_obj->store_type = storage_type::contiguous;
							} else if(second_term == "erasable") {
								last_obj->store_type = storage_type::erasable;
							} else if(second_term == "compactable") {
								last_obj->store_type = storage_type::compactable;
							} else {
								error_to_file(output_file_name, std::string("Unexpected token: ") + second_term + " (line: " + std::to_string(line_count) + ")");
							}
						} else if(first_term == "size:") {
							if(second_term == "expandable") {
								last_obj->is_expandable = true;
								last_obj->size = 0;
							} else {
								last_obj->is_expandable = false;
								last_obj->size = std::stoi(second_term);
							}
						} else if(first_term == "tags:") {
							if(second_term.size() > 0)
								last_obj->obj_tags.emplace_back(second_term);

							while(str_ptr < str_end) {
								auto const extra_term = extract_string(str_ptr, str_end);
								if(extra_term.size() > 0)
									last_obj->obj_tags.emplace_back(extra_term);
							}
						} else if(first_term == "hook:") {
							do {
								if(second_term.size() == 0) {
								} else if(second_term == "create") {
									last_obj->hook_create = true;
								} else if(second_term == "delete") {
									last_obj->hook_delete = true;
								} else if(second_term == "move") {
									last_obj->hook_move = true;
								} else {
									error_to_file(output_file_name, std::string("Unexpected token: ") + second_term + " (line: " + std::to_string(line_count) + ")");
								}
								second_term = extract_string(str_ptr, str_end);
							} while(second_term.size() > 0 && str_ptr < str_end);
						} else if(first_term == "properties:") {
							// just ignore a line starting with "properties:"
						} else if(first_term[first_term.size() - 1] == ':') {
							const auto stripped = first_term.substr(0, first_term.size() - 1);

							if(find_by_name(parsed_file, stripped)) { // is an object name: thus must be a relationship def
								if(last_obj->is_relationship == false) {
									error_to_file(output_file_name, std::string("Cannot add a property with the name of exising object: ") + stripped +
										" (line: " + std::to_string(line_count) + ")");
								}
								if(second_term.size() > 0) {
									auto next_str = extract_string(str_ptr, str_end);
									index_type i = index_type::none;
									list_type l = list_type::list;

									while(next_str.length() > 0) {
										if(next_str == "many")
											i = index_type::many;
										else if(next_str == "unique")
											i = index_type::at_most_one;
										else if(next_str == "list")
											l = list_type::list;
										else if(next_str == "array")
											l = list_type::array;
										else if(next_str == "std_vector")
											l = list_type::std_vector;
										else
											error_to_file(output_file_name, std::string("Unexpected token: ") + next_str + " (line: " + std::to_string(line_count) + ")");

										next_str = extract_string(str_ptr, str_end);
									}

									last_obj->indexed_objects.push_back(related_object{ second_term, stripped, i, l, nullptr });

								} else {
									error_to_file(output_file_name, std::string("Unexpected end of line (line: ") + std::to_string(line_count) + ")");
								}
							} else { // is not an object, thus is a new property
								last_obj->properties.emplace_back();
								last_prop = &(last_obj->properties.back());
								last_prop->name = stripped;

								process_data_type(second_term, last_prop, str_ptr, str_end);

								pstate = parsing_state::in_property;
							}
						} else {
							error_to_file(output_file_name, std::string("Unexpected token: ") + first_term + " (line: " + std::to_string(line_count) + ")");
						}
						break;
					}
					case parsing_state::in_property:
					{
						if(first_term == "tags:") {
							if(second_term.size() > 0)
								last_prop->property_tags.emplace_back(second_term);

							while(str_ptr < str_end) {
								auto const extra_term = extract_string(str_ptr, str_end);
								if(extra_term.size() > 0)
									last_prop->property_tags.emplace_back(extra_term);
							}
						} else if(first_term == "hook:") {
							do {
								if(second_term.size() == 0) {
								} else if(second_term == "get") {
									last_prop->hook_get = true;
								} else if(second_term == "set") {
									last_prop->hook_set = true;
								} else {
									error_to_file(output_file_name, std::string("Unexpected token: ") + second_term + " (line: " + std::to_string(line_count) + ")");
								}
								second_term = extract_string(str_ptr, str_end);
							} while(second_term.size() > 0 && str_ptr < str_end);
						} else if(first_term[first_term.size() - 1] == ':') {
							last_obj->properties.emplace_back();
							last_prop = &(last_obj->properties.back());
							last_prop->name = first_term.substr(0, first_term.size() - 1);

							process_data_type(second_term, last_prop, str_ptr, str_end);
						} else {
							error_to_file(output_file_name, std::string("Unexpected token: ") + first_term + " (line: " + std::to_string(line_count) + ")");
						}
						break;
					}
					case parsing_state::in_load_save:
					{
						if(first_term == "object_tags:") {
							if(second_term.size() > 0) {
								if(second_term[0] == '!')
									last_load_save->neg_obj_tags.emplace_back(second_term.substr(1));
								else
									last_load_save->pos_obj_tags.emplace_back(second_term);
							}

							while(str_ptr < str_end) {
								auto const extra_term = extract_string(str_ptr, str_end);
								if(extra_term[0] == '!')
									last_load_save->neg_obj_tags.emplace_back(extra_term.substr(1));
								else
									last_load_save->pos_obj_tags.emplace_back(extra_term);
							}
						} else if(first_term == "property_tags:") {
							if(second_term.size() > 0) {
								if(second_term[0] == '!')
									last_load_save->neg_property_tags.emplace_back(second_term.substr(1));
								else
									last_load_save->pos_property_tags.emplace_back(second_term);
							}

							while(str_ptr < str_end) {
								auto const extra_term = extract_string(str_ptr, str_end);
								if(extra_term[0] == '!')
									last_load_save->neg_property_tags.emplace_back(extra_term.substr(1));
								else
									last_load_save->pos_property_tags.emplace_back(extra_term);
							}
						} else {
							error_to_file(output_file_name, std::string("Unexpected token: ") + first_term + " (line: " + std::to_string(line_count) + ")");
						}
						break;
					}
				} // end of parsing state switch
			} // end of ifs testing for condition to switch between top level parsing state
		} // end of line-reading loop, and end of file parsing

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
					if(l.index == index_type::at_most_one)
						r.primary_key = better_primary_key(r.primary_key, l.related_to);
				}

				for(auto& link : r.indexed_objects) {
					if(link.index != index_type::none)
						link.related_to->relationships_involved_in.push_back(in_relation_information{ r.name, link.property_name,
							r.primary_key == link.related_to, link.index, link.ltype, &r });
				}

				if(r.indexed_objects.size() <= 1) {
					error_to_file(output_file_name, std::string("Relationship: ") + r.name + " is between too few objects");
				}

				if(r.primary_key) {
					r.size = r.primary_key->size;
					r.store_type = storage_type::contiguous;
					r.is_expandable = r.primary_key->is_expandable;
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
		output += "#include \"ve.hpp\"\n";
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
			if(!ob.primary_key) {
				const auto underlying_type = ob.is_expandable ? std::string("uint32_t") : size_to_tag_type(ob.size);
				//id class begin
				output += make_id_definition(o, ob.name, underlying_type).to_string(1);
			} else {
				output += "\tusing " + ob.name + "_id = " + ob.primary_key->name + "_id;\n\n";
			}
		}

		// close namespace briefly
		output += "}\n\n";

		//mark each id as going into a tagged vector
		output += "namespace ve {\n";
		for(auto& ob : parsed_file.relationship_objects) {
			if(!ob.primary_key) {
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
				if(i.related_to == ob.primary_key) {
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
					if(i.related_to == ob.primary_key) {
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
			const std::string id_name = (ob.primary_key ? ob.primary_key->name : ob.name) + "_id";
			const std::string con_tags_type = ob.is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

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
			const std::string relation_id_name = r.name + "_id";
			const std::string relation_con_tags_type = r.is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

			for(auto& i : r.indexed_objects) {
				if(i.index == index_type::at_most_one && i.related_to == r.primary_key) {
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

		// creation / deletion reoutines
		for(auto& cob : parsed_file.relationship_objects) {
			const std::string id_name = cob.name + "_id";

			if(!cob.is_relationship) {
				if(cob.store_type == storage_type::contiguous || cob.store_type == storage_type::compactable) {
					output += make_pop_back(o, cob).to_string(2);
					output += make_object_resize(o, cob).to_string(2);

					if(cob.store_type == storage_type::compactable) {
						output += make_compactable_delete(o, cob).to_string(2);
					}

					//create
					output += "\t\t" + id_name + " create_" + cob.name + "() {\n";

					if(!cob.is_expandable)
						output += "\t\t\tif(" + cob.name + ".size_used >= " + std::to_string(cob.size) + ") std::abort();\n";

					output += "\t\t\t" + id_name + " new_id(" + cob.name + ".size_used);\n";

					for(auto& cr : cob.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t\t" + cr.relation_name + ".size_used = " + cob.name + ".size_used + 1;\n";
							if(cob.is_expandable) {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} if(rp.type == property_type::bitfield) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + cob.name + ".size_used + 8) / 8);\n";
									} else if(rp.type == property_type::special_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.emplace_back();\n";
									}
								}
								for(auto& ri : cr.rel_ptr->indexed_objects) {
									if(ri.related_to == cr.rel_ptr->primary_key) {
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.emplace_back();\n";
									}
									if(ri.ltype == list_type::list && ri.index == index_type::many) {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.emplace_back();\n";
									}
								}
							}
						} else if(cr.indexed_as == index_type::at_most_one) {
							if(cob.is_expandable) {
								output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.emplace_back();\n";
							}
						} else if(cr.indexed_as == index_type::many) {
							if(cob.is_expandable) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.emplace_back();\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.emplace_back();\n";
								}
							}
						}
					}
					if(cob.is_expandable) {
						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 8) / 8);\n";
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
					}

					output += "\t\t\t++" + cob.name + ".size_used;\n";
					if(cob.hook_create)
						output += "\t\t\t\ton_create_" + cob.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(cob.store_type == storage_type::erasable) {

					// delete
					output += "\t\tvoid delete_" + cob.name + "(" + id_name + " id_removed) {\n";

					output += "\t\t\tif(is_valid_" + cob.name + "(id_removed)) {\n";
					if(cob.hook_delete)
						output += "\t\t\t\ton_delete_" + cob.name + "(id_removed);\n";

					output += "\t\t\t\t" + cob.name + ".m__index.vptr()[id_removed.index()] = " + cob.name + ".first_free;\n"; // FN
					output += "\t\t\t\t" + cob.name + ".first_free = id_removed;\n";
					output += "\t\t\t\tif(" + cob.name + ".size_used - 1 == id_removed.index()) {\n"; // OIF
					output += "\t\t\t\t\tfor( ; " + cob.name + ".size_used > 0 && "
						+ cob.name + ".m__index.vptr()[" + cob.name + ".size_used - 1] != "
						+ cob.name + "_id(" + cob.name + "_id::value_base_t(" + cob.name + ".size_used - 1)) ;"
						+ " --" + cob.name + ".size_used) ; \\ intentionally empty loop\n";
					output += "\t\t\t\t}\n"; // OIF

					for(auto& cr : cob.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\n";
							output += "\t\t\t\t" + cr.relation_name + ".size_used = " + cob.name + ".size_used;\n";

							for(auto& rp : cr.rel_ptr->properties) {
								if(rp.is_derived) {
								} else if(rp.type == property_type::special_vector) {
									output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\n";
								} else if(rp.type == property_type::bitfield) {
									output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + ".vptr(), id_removed.index(), false);\n";
								} else {
									output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + rp.data_type + "{};\n";
								}
							}

						} else if(cr.indexed_as == index_type::at_most_one) {
							output += "\t\t\t\t" + cob.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\n";

						} else if(cr.indexed_as == index_type::many) {
							output += "\t\t\t\t" + cob.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\n";
						}
					}
					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
						} else {
							output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}
					}
					output += "\t\t\t}\n";
					output += "\t\t}\n"; // end delete

					//create
					output += "\t\t" + id_name + " create_" + cob.name + "() {\n";
					if(!cob.is_expandable) {
						output += "\t\t\tif(!bool(" + cob.name + ".first_free )) std::abort();\n";
						output += "\t\t\t" + id_name + " new_id =" + cob.name + ".first_free;\n";
						output += "\t\t\tfirst_free = " + cob.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t" + cob.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
					} else {
						output += "\t\t\t" + id_name + " new_id;\n";
						output += "\t\t\tconst bool expanded = !bool(" + cob.name + ".first_free );\n";
						output += "\t\t\tif(expanded) {\n";
						output += "\t\t\t\tnew_id = " + id_name + "(" + id_name + "::value_base_t(" + cob.name + ".size_used));\n";
						output += "\t\t\t\t" + cob.name + ".m__index.values.push_back(new_id);\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\tnew_id = " + cob.name + ".first_free;\n";
						output += "\t\t\t\tfirst_free = " + cob.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t\t" + cob.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
						output += "\t\t\t}\n";

					}
					output += "\t\t\t" + cob.name + ".size_used = std::max(" + cob.name + ".size_used, uint32_t(new_id.index() + 1));\n";

					for(auto& cr : cob.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t" + cr.relation_name + ".size_used = " + cob.name + ".size_used;\n";
						}
					}

					if(cob.is_expandable) {
						output += "\t\t\tif(expanded) {\n;";
						for(auto& cr : cob.relationships_involved_in) {
							if(cr.as_primary_key) {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} if(rp.type == property_type::bitfield) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + cob.name + ".size_used + 7) / 8);\n";
									} else if(rp.type == property_type::special_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.emplace_back();\n";
									}
								}
								for(auto& ri : cr.rel_ptr->indexed_objects) {
									if(ri.related_to == cr.rel_ptr->primary_key) {
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.emplace_back();\n";
									}
									if(ri.ltype == list_type::list && ri.index == index_type::many) {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.emplace_back();\n";
									}
								}
							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.emplace_back();\n";
							} else if(cr.indexed_as == index_type::many) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.emplace_back();\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.emplace_back();\n";
								}
							}
						}

						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 7) / 8);\n";
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
						output += "\t\t\t}\n;"; // end expanded if
					}

					if(cob.hook_create)
						output += "\t\t\ton_create_" + cob.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					//resize
					output += "\t\tvoid " + cob.name + "_resize(uint32_t new_size) {\n";

					if(!cob.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(cob.size) + ") std::abort();\n";

					output += "\t\t\tconst uint32_t old_size = " + cob.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting


					output += "\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id();\n";
					if(cob.is_expandable) {
						output += "\t\t\t\t" + cob.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(cob.size) + ");\n";
						output += "\t\t\t\tfor(; i >= new_size; --i) {\n";
						output += "\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
						output += "\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
						output += "\t\t\t\t}\n\n";
					}

					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + cob.name + ".m__index.vptr()[i] != " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";


					
					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\tstd::for_each(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ cob.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + cob.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!cob.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!cob.is_expandable) {
								if(cp.type == property_type::object) {
									output += "\t\t\t\tstd::std::destroy_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding

					output += "\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id();\n";
					if(cob.is_expandable) {
						output += "\t\t\t\t" + cob.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(cob.size) + ");\n";
					}

					output += "\t\t\t\tfor(; i >= old_size; --i) {\n";
					output += "\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t}\n\n";


					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + cob.name + ".m__index.vptr()[i] != " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					output += "\t\t\t}\n";

					//both
					if(cob.is_expandable) {
						for(auto& cr : cob.relationships_involved_in) {
							if(cr.as_primary_key) {

							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\tstd::fill_n(" + cr.relation_name + ".m_link_back_" + cr.property_name
									+ ".vptr(), new_size, " + cr.relation_name + "_id());\n";
							} else if(cr.indexed_as == index_type::many) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\tstd::fill_n(" + cr.relation_name + ".m_head_back_" + cr.property_name
										+ ".vptr(), new_size, " + cr.relation_name + "_id());\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\tstd::for_each(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), "
										+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->"
										+ cr.relation_name + "." + cr.property_name + "_storage.release(i); });\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\tstd::destroy_n(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), new_size);\n";
									output += "\t\t\tstd::uninitialized_default_construct_n(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), new_size);\n";
								}

							}
						}

						for(auto& cr : cob.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t" + cr.relation_name + "_resize(new_size);\n";
							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.resize(1 + new_size);\n";
							} else if(cr.indexed_as == index_type::many) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.resize(1 + new_size);\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.resize(1 + new_size);\n";
								}

							}
						}
						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					} else {
						for(auto& cr : cob.relationships_involved_in) {
							if(cr.as_primary_key) {

							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\tstd::fill_n(" + cr.relation_name + ".m_link_back_" + cr.property_name
									+ ".vptr(), old_size, " + cr.relation_name + "_id());\n";
							} else if(cr.indexed_as == index_type::many) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\tstd::fill_n(" + cr.relation_name + ".m_head_back_" + cr.property_name
										+ ".vptr(), old_size, " + cr.relation_name + "_id());\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\tstd::for_each(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), "
										+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->"
										+ cr.relation_name + "." + cr.property_name + "_storage.release(i); });\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\tstd::destroy_n(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), old_size);\n";
									output += "\t\t\tstd::uninitialized_default_construct_n(" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr(), old_size);\n";
								}

							}
						}

						for(auto& cr : cob.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t" + cr.relation_name + "_resize(new_size);\n";
							}
						}
					}
					output += "\t\t\t" + cob.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && "
						+ cob.name + ".m__index.vptr()[id.index()] == id;\n";
					output += "\t\t}\n";
				}
			} else if(cob.primary_key) { // primary key relationship
				//resize
				output += "\t\tvoid " + cob.name + "_resize(uint32_t new_size) {\n";
				if(!cob.is_expandable)
					output += "\t\t\tif(new_size > " + std::to_string(cob.size) + ") std::abort();\n";
				output += "\t\t\tconst uint32_t old_size = " + cob.name + ".size_used;\n";
				output += "\t\t\tif(new_size < old_size) {\n"; // contracting

				

				for(auto& cp : cob.properties) {
					if(cp.is_derived) {
					} else if(cp.type == property_type::special_vector) {
						output += "\t\t\t\tstd::for_each(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, "
							+ cob.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + cob.name + "."
							+ cp.name + "_storage.release(i); });\n";

						output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
					} else if(cp.type == property_type::bitfield) {
						output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
						output += "\t\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), i, false);\n";
						if(!cob.is_expandable)
							output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
					} else {
						if(!cob.is_expandable) {
							if(cp.type == property_type::object) {
								output += "\t\t\t\tstd::std::destroy_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								output += "\t\t\t\tstd::uninitialized_default_construct_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
							} else {
								output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
							}
						}
					}
				}

				output += "\t\t\t} else {\n"; //expanding
				output += "\t\t\t}\n";

				//both
				if(cob.is_expandable) {
					for(auto& iob : cob.indexed_objects) {
						output += "\t\t\tstd::fill_n(" + cob.name + ".m_" + iob.property_name + ".vptr(), new_size, " + iob.type_name + "_id());\n";
						if(iob.ltype == list_type::list)
							output += "\t\t\tstd::fill_n(" + cob.name + ".m_link_" + iob.property_name + ".vptr(), new_size, " + iob.type_name + "_id_pair());\n";

					}

					for(auto& iob : cob.indexed_objects) {
						output += "\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.resize(1 + new_size);\n";
						if(iob.ltype == list_type::list)
							output += "\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.resize(1 + new_size);\n";
					}

					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
						} else {
							output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
						}
					}
				} else {
					for(auto& iob : cob.indexed_objects) {
						if(iob.related_to != cob.primary_key) {
							output += "\t\t\tstd::fill_n(" + cob.name + ".m_" + iob.property_name + ".vptr(), old_size, " + iob.type_name + "_id());\n";
							if(iob.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + cob.name + ".m_link_" + iob.property_name + ".vptr(), old_size, " + iob.type_name + "_id_pair());\n";
						}

					}
				}
				output += "\t\t\t" + cob.name + ".size_used = new_size;\n";
				output += "\t\t}\n"; // end resize

				output += "\t\tvoid delete_" + cob.name + "(" + id_name + " id_removed) {\n";
				if(cob.hook_delete)
					output += "\t\t\t\ton_delete_" + cob.name + "(id_removed);\n";

				for(auto& iob : cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(id_removed, " + iob.type_name + "_id());\n";
					}
				}
				output += "\t\t}\n"; // end delete

				output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
				output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && " + 
					"is_valid_" + cob.primary_key->name + "(id) && (";
				for(auto& iob : cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						output += "bool(" + cob.name + ".m_" + iob.property_name + ".vptr()[id.index()]) || ";
					}
				}
				output += "false);\n";
				output += "\t\t}\n"; // end is_valid

				output += "\t\tprivate:\n";
				output += "\t\tvoid internal_move_relationship_" + cob.name + "(" + id_name + " old_id, " + id_name + " new_id) {\n";

				for(auto& iob : cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".vptr()[new_id.index()] = "
							+ cob.name + ".m_" + iob.property_name + ".vptr()[old_id.index()];\n";
						output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".vptr()[old_id.index()] = " + iob.type_name + "_id();\n";
						
						if(iob.index == index_type::at_most_one) {
							output += "\t\t\t\tif(auto tmp = " + cob.name + ".m_" + iob.property_name + ".vptr()[new_id.index()]; bool(tmp))\n";
							output += "\t\t\t\t\t" + cob.name + ".m_link_back_" + iob.property_name + ".vptr()[tmp.index()] = new_id;\n";
						} else if(iob.index == index_type::many && iob.ltype == list_type::list) {
							output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[new_id.index()] = "
								+ cob.name + ".m_link_" + iob.property_name + ".vptr()[old_id.index()];\n";
							output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[old_id.index()] = " + iob.type_name + "_id_pair();\n";

							output += "\t\t\t\t{auto tmp = " + cob.name + ".m_link_" + iob.property_name + ".vptr()[new_id.index()];\n";
							output += "\t\t\t\t\tif(bool(tmp.left)) {\n";
							output += "\t\t\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[tmp.left.index()].right = new_id;\n";
							output += "\t\t\t\t\t} else {\n";
							output += "\t\t\t\t\t\rfor(auto lpos = tmp; bool(lpos); lpos = " + cob.name + ".m_link_" + iob.property_name + ".vptr()[lpos.index()].right)\n";
							output += "\t\t\t\t\t\t" + cob.name + ".m_head_back_" + iob.property_name + ".vptr()["
								+ cob.name + ".m_" + iob.property_name + ".vptr()[lpos.index()].index()] = new_id;\n";
							output += "\t\t\t\t\t}\n";
							output += "\t\t\t\t\tif(bool(tmp.right)) " + cob.name + ".m_link_" + iob.property_name + ".vptr()[tmp.right.index()].left = new_id;\n";
							output += "\t\t\t\t}\n";

							if(cob.is_expandable)
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.pop_back();\n";
							else
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[last_id.index()] = " + iob.type_name + "_id_pair();\n";
						}
					}
				}

				for(auto& cp : cob.properties) {
					if(cp.is_derived) {
					} else if(cp.type == property_type::special_vector) {
						output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[new_id.index()] = "
							+ cob.name + ".m_" + cp.name + ".vptr()[old_id.index()];\n";
						output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[old_id.index()] = "
							+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
					} else if(cp.type == property_type::bitfield) {
						output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), new_id.index(), "
							+ "dcon::bit_vector_get(" + cob.name + ".m_" + cp.name + ".vptr(), old_id.index()));\n";
						output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), old_id.index(), false);\n";
					} else {
						output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[new_id.index()] = std::move("
							+ cob.name + ".m_" + cp.name + ".vptr()[old_id.index()]);\n";
						output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[old_id.index()] = " + cp.data_type + "{};\n";
					}
				}
				if(cob.hook_move)
					output += "\t\t\t\ton_move_" + cob.name + "(new_id, old_id);\n";

				output += "\t\t}\n"; // end internal_move_relationship

				output += "\t\tpublic:\n";
				output += "\t\t" + id_name + " try_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";

				for(auto& iob : cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						if(iob.index == index_type::at_most_one) {
							output += "\t\t\tif(bool(" + iob.property_name + "_p) && bool("
								+ cob.name + ".m_link_" + iob.property_name + ".vptr()[" + iob.property_name + "_p.index()])) return " + id_name + "();\n";
						}
					} else {
						output += "\t\t\tif(is_valid_" + cob.name + "(" + iob.property_name + "_p)) return " + id_name + "();\n";
					}
				}

				output += "\t\t\t" + id_name + " new_id = ";
				for(auto& iob: cob.indexed_objects) {
					if(iob.related_to == cob.primary_key) {
						output += iob.property_name;
					}
				}
				output += "_p;\n";

				for(auto& iob : cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(new_id, " + iob.property_name + "_p);\n";
					}
				}

				if(cob.hook_create)
					output += "\t\t\t\ton_create_" + cob.name + "(new_id);\n";
				output += "\t\t\treturn new_id;\n";
				output += "\t\t}\n"; // end try_create

				output += "\t\t" + id_name + " force_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";
				output += "\t\t\t" + id_name + " new_id = ";
				for(auto& iob: cob.indexed_objects) {
					if(iob.related_to == cob.primary_key) {
						output += iob.property_name;
					}
				}
				output += "_p;\n";

				for(auto& iob: cob.indexed_objects) {
					if(iob.related_to != cob.primary_key) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(new_id, " + iob.property_name + "_p);\n";
					}
				}

				if(cob.hook_create)
					output += "\t\t\t\ton_create_" + cob.name + "(new_id);\n";
				output += "\t\t\treturn new_id;\n";
				output += "\t\t}\n"; // end force_create
			} else { // non pk relationship
				if(cob.store_type == storage_type::contiguous || cob.store_type == storage_type::compactable) {

					// pop_back
					output += "\t\tvoid " + cob.name + "_pop_back() {\n";
					output += "\t\t\tif(" + cob.name + ".size_used > 0) {\n";

					output += "\t\t\t\t" + id_name + " id_removed(" + cob.name + ".size_used - 1);\n";
					if(cob.hook_delete)
						output += "\t\t\t\ton_delete_" + cob.name + "(id_removed);\n";

					for(auto& iob: cob.indexed_objects) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(id_removed, " + iob.type_name + "_id());\n";
						if(cob.is_expandable) {
							output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.pop_back();\n";
							if(iob.ltype == list_type::list)
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.pop_back();\n";
						}
					}

					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
							if(cob.is_expandable)
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 6) / 8);\n";
						} else {
							if(!cob.is_expandable)
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}

						if(cob.is_expandable && cp.type != property_type::bitfield && !cp.is_derived) {
							output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.pop_back();\n";
						}
					}

					output += "\t\t\t\t--" + cob.name + ".size_used;\n";
					output += "\t\t\t}\n";
					output += "\t\t}\n";


					//resize
					output += "\t\tvoid " + cob.name + "_resize(uint32_t new_size) {\n";
					if(!cob.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(cob.size) + ") std::abort();\n";
					output += "\t\t\tconst uint32_t old_size = " + cob.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting

					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\tstd::for_each(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ cob.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + cob.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!cob.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!cob.is_expandable) {
								if(cp.type == property_type::object) {
									output += "\t\t\t\tstd::std::destroy_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding
					output += "\t\t\t}\n";

					//both
					if(cob.is_expandable) {
						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\tstd::fill_n(" + cob.name + ".m_" + iob.property_name + ".vptr(), new_size, " + iob.type_name + "_id());\n";
							if(iob.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + cob.name + ".m_link_" + iob.property_name + ".vptr(), new_size, " + iob.type_name + "_id_pair());\n";

						}

						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.resize(1 + new_size);\n";
							if(iob.ltype == list_type::list)
								output += "\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.resize(1 + new_size);\n";
						}

						
						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					} else {
						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\tstd::fill_n(" + cob.name + ".m_" + iob.property_name + ".vptr(), old_size, " + iob.type_name + "_id());\n";
							if(iob.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + cob.name + ".m_link_" + iob.property_name + ".vptr(), old_size, " + iob.type_name + "_id_pair());\n";

						}
					}
					output += "\t\t\t" + cob.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					if(cob.store_type == storage_type::compactable) {
						//delete
						output += "\t\tvoid delete_" + cob.name + "(" + id_name + " id) {\n";
						output += "\t\t\t\t" + id_name + " id_removed = id;\n";
						output += "\t\t\t\t" + id_name + " last_id(" + cob.name + ".size_used - 1);\n";

						output += "\t\t\t\tif(id_removed == last_id) { " + cob.name + ".pop_back(); return; }\n";

						if(cob.hook_delete)
							output += "\t\t\t\ton_delete_" + cob.name + "(id_removed);\n";

						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(id_removed, " + iob.type_name + "_id());\n";

							output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".vptr()[id_removed.index()] = "
								+ cob.name + ".m_" + iob.property_name + ".vptr()[last_id.index()];\n";
							if(cob.is_expandable)
								output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.pop_back();\n";
							else
								output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".vptr()[last_id.index()] = " + iob.type_name + "_id();\n";

							if(iob.ltype == list_type::list) {
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[id_removed.index()] = "
									+ cob.name + ".m_link_" + iob.property_name + ".vptr()[last_id.index()];\n";
								output += "\t\t\t\t{ auto tmp = " + cob.name + ".m_link_" + iob.property_name + ".vptr()[id_removed.index()];\n";
								output += "\t\t\t\t\tif(bool(tmp.left)) {\n";
								output += "\t\t\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[tmp.left.index()].right = id_removed;\n";
								output += "\t\t\t\t\t} else {\n";
								output += "\t\t\t\t\t\rfor(auto lpos = tmp; bool(lpos); lpos = " + cob.name + ".m_link_" + iob.property_name + ".vptr()[lpos.index()].right)\n";
								output += "\t\t\t\t\t\t" + cob.name + ".m_head_back_" + iob.property_name + ".vptr()["
									+ cob.name + ".m_" + iob.property_name + ".vptr()[lpos.index()].index()] = id_removed;\n";
								output += "\t\t\t\t\t}\n";
								output += "\t\t\t\t\tif(bool(tmp.right)) " + cob.name + ".m_link_" + iob.property_name + ".vptr()[tmp.right.index()].left = id_removed;\n";
								output += "\t\t\t\t}\n";

								if(cob.is_expandable)
									output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".vptr()[last_id.index()] = " + iob.type_name + "_id_pair();\n";
							}
						}


						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = "
									+ cob.name + ".m_" + cp.name + ".vptr()[last_id.index()];\n";
								if(cob.is_expandable)
									output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[last_id.index()] = "
									+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), id_removed.index(), "
									+ "dcon::bit_vector_get(" + cob.name + ".m_" + cp.name + ".vptr(), last_id.index()));\n";
								output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), last_id.index(), false);\n";
								if(cob.is_expandable)
									output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 6) / 8);\n";

							} else {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = std::move("
									+ cob.name + ".m_" + cp.name + ".vptr()[last_id.index()]);\n";
								if(cob.is_expandable)
									output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[last_id.index()] = " + cp.data_type + "{};\n";
							}
						}
						output += "\t\t\t\t--" + cob.name + ".size_used;\n";
						if(cob.hook_move)
							output += "\t\t\t\ton_move_" + cob.name + "(id_removed, last_id);\n";

						output += "\t\t\t}\n";

						output += "\t\t}\n";
					} // end compactible delete


					//try create
					output += "\t\t" + id_name + " try_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";
					// we can skip trying because this is not a relationship with a primary key: thus all are >= type
					output += "\t\t\treturn " + id_name + " force_create_" + cob.name + "(" +
						([&]() {
						std::string result;
						for(auto& i : cob.indexed_objects) {
							if(result.length() != 0)
								result += ", ";
							result += i.property_name + "_p";
						}
						return result;
					}())
						+ ");\n";
					output += "\t\t}\n";

					//force create
					output += "\t\t" + id_name + " force_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";
					if(!cob.is_expandable)
						output += "\t\t\tif(" + cob.name + ".size_used >= " + std::to_string(cob.size) + ") std::abort();\n";

					output += "\t\t\t" + id_name + " new_id(" + cob.name + ".size_used);\n";

					if(cob.is_expandable) {
						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.emplace_back();\n";
							if(iob.ltype == list_type::list) {
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.emplace_back();\n";
							}
						}
						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 8) / 8);\n";
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
					}

					for(auto& iob: cob.indexed_objects) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(new_id, " + iob.property_name + "_p);\n";
					}

					output += "\t\t\t++" + cob.name + ".size_used;\n";
					if(cob.hook_create)
						output += "\t\t\t\ton_create_" + cob.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(cob.store_type == storage_type::erasable) {
					// delete
					output += "\t\tvoid delete_" + cob.name + "(" + id_name + " id_removed) {\n";

					output += "\t\t\tif(is_valid_" + cob.name + "(id_removed)) {\n";
					if(cob.hook_delete)
						output += "\t\t\t\ton_delete_" + cob.name + "(id_removed);\n";

					output += "\t\t\t\t" + cob.name + ".m__index.vptr()[id_removed.index()] = " + cob.name + ".first_free;\n"; // FN
					output += "\t\t\t\t" + cob.name + ".first_free = id_removed;\n";
					output += "\t\t\t\tif(" + cob.name + ".size_used - 1 == id_removed.index()) {\n"; // OIF
					output += "\t\t\t\t\tfor( ; " + cob.name + ".size_used > 0 && "
						+ cob.name + ".m__index.vptr()[" + cob.name + ".size_used - 1] != "
						+ cob.name + "_id(" + cob.name + "_id::value_base_t(" + cob.name + ".size_used - 1)) ;"
						+ " --" + cob.name + ".size_used) ; \\ intentionally empty loop\n";
					output += "\t\t\t\t}\n"; // OIF

					for(auto& iob: cob.indexed_objects) {
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name + "(id_removed, " + iob.type_name + "_id());\n";
					}

					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
						} else {
							output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}
					}
					output += "\t\t\t}\n";
					output += "\t\t}\n"; // end delete

					//try create
					output += "\t\t" + id_name + " try_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";
					// we can skip trying because this is not a relationship with a primary key: thus all are >= type
					output += "\t\t\treturn " + id_name + " force_create_" + cob.name + "(" +
						([&]() {
						std::string result;
						for(auto& i : cob.indexed_objects) {
							if(result.length() != 0)
								result += ", ";
							result += i.property_name + "_p";
						}
						return result;
					}()) + ");\n";
					output += "\t\t}\n";

					//force create
					output += "\t\t" + id_name + " force_create_" + cob.name + "(" + make_relationship_parameters(cob) + ") {\n";

					if(!cob.is_expandable) {
						output += "\t\t\tif(!bool(" + cob.name + ".first_free )) std::abort();\n";
						output += "\t\t\t" + id_name + " new_id =" + cob.name + ".first_free;\n";
						output += "\t\t\tfirst_free = " + cob.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t" + cob.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
					} else {
						output += "\t\t\t" + id_name + " new_id;\n";
						output += "\t\t\tconst bool expanded = !bool(" + cob.name + ".first_free );\n";
						output += "\t\t\tif(expanded) {\n";
						output += "\t\t\t\tnew_id = " + id_name + "(" + id_name + "::value_base_t(" + cob.name + ".size_used));\n";
						output += "\t\t\t\t" + cob.name + ".m__index.values.push_back(new_id);\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\tnew_id = " + cob.name + ".first_free;\n";
						output += "\t\t\t\tfirst_free = " + cob.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t\t" + cob.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
						output += "\t\t\t}\n";

					}
					output += "\t\t\t" + cob.name + ".size_used = std::max(" + cob.name + ".size_used, uint32_t(new_id.index() + 1));\n";


					if(cob.is_expandable) {
						output += "\t\t\tif(expanded) {\n;";

						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.emplace_back();\n";
							if(iob.ltype == list_type::list) {
								output += "\t\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.emplace_back();\n";
							}
						}

						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (" + cob.name + ".size_used + 7) / 8);\n";
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + cob.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
						output += "\t\t\t}\n;";
					}

					if(cob.hook_create)
						output += "\t\t\ton_create_" + cob.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					// resize
					output += "\t\tvoid " + cob.name + "_resize(uint32_t new_size) {\n";

					if(!cob.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(cob.size) + ") std::abort();\n";

					output += "\t\t\tconst uint32_t old_size = " + cob.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting


					output += "\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id();\n";
					if(cob.is_expandable) {
						output += "\t\t\t\t" + cob.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(cob.size) + ");\n";
						output += "\t\t\t\tfor(; i >= new_size; --i) {\n";
						output += "\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
						output += "\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
						output += "\t\t\t\t}\n\n";
					}

					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + cob.name + ".m__index.vptr()[i] != " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					for(auto& iob: cob.indexed_objects) {
						output += "\t\t\t\tfor(int32_t j = int32_t(old_size); j >= new_size; --j) {\n";
						output += "\t\t\t\t" + cob.name + "_set_" + iob.property_name
							+ "(" + cob.name + "_id(" + cob.name + "::value_base_t(j)), " + iob.type_name + "_id());\n";
					}


					for(auto& cp : cob.properties) {
						if(cp.is_derived) {
						} else if(cp.type == property_type::special_vector) {
							output += "\t\t\t\tstd::for_each(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ cob.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + cob.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + cob.name + "." + cp.name + "_storage.release(" + cob.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.type == property_type::bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + cob.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!cob.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!cob.is_expandable) {
								if(cp.type == property_type::object) {
									output += "\t\t\t\tstd::std::destroy_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + cob.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding

					output += "\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id();\n";
					if(cob.is_expandable) {
						output += "\t\t\t\t" + cob.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(cob.size) + ");\n";
					}

					output += "\t\t\t\tfor(; i >= old_size; --i) {\n";
					output += "\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t}\n\n";


					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + cob.name + ".m__index.vptr()[i] != " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + cob.name + ".m__index.vptr()[i] = " + cob.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + cob.name + ".first_free = " + cob.name + "_id(" + size_to_tag_type(cob.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					output += "\t\t\t}\n";

					//both
					if(cob.is_expandable) {
						for(auto& iob: cob.indexed_objects) {
							output += "\t\t\t" + cob.name + ".m_" + iob.property_name + ".values.resize(1 + new_size);\n";
							if(iob.ltype == list_type::list) {
								output += "\t\t\t" + cob.name + ".m_link_" + iob.property_name + ".values.resize(1 + new_size);\n";
							}
						}

						for(auto& cp : cob.properties) {
							if(cp.is_derived) {
							} else if(cp.type == property_type::special_vector) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.type == property_type::bitfield) {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + cob.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					}
					output += "\t\t\t" + cob.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					output += "\t\tbool is_valid_" + cob.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + cob.name + ".size_used && "
						+ cob.name + ".m__index.vptr()[id.index()] == id;\n";
					output += "\t\t}\n";
				}
			} // end case relationship no primary key
		} // end creation / deletion reoutines creation loop

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

		//make ve interface

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

		

		output += "\n";
		
		//make serialize records
		for(auto& rt : parsed_file.load_save_routines) {
			output += "\t\tload_record make_serialize_record_" + rt.name + "() const noexcept {\n";
			output += "\t\t\tload_record result;\n";

			for(auto& ob : parsed_file.relationship_objects) {
				bool passed_filter = false;
				if(rt.pos_obj_tags.size() == 0) {
					passed_filter = true;
				} else {
					for(auto& tg : rt.pos_obj_tags) {
						if(std::find(ob.obj_tags.begin(), ob.obj_tags.end(), tg) != ob.obj_tags.end())
							passed_filter = true;
					}
				}
				for(auto& tg : rt.neg_obj_tags) {
					if(std::find(ob.obj_tags.begin(), ob.obj_tags.end(), tg) != ob.obj_tags.end())
						passed_filter = false;
				}
				if(passed_filter) {
					output += "\t\t\tresult." + ob.name + " = true;\n";
					for(auto& iob: ob.indexed_objects) {
						output += "\t\t\tresult." + ob.name + "_" + iob.property_name + " = true;\n";

					}
					if(ob.store_type == storage_type::erasable) {
						output += "\t\t\tresult." + ob.name + "__index = true;\n";
					}
					for(auto& prop : ob.properties) {
						bool passed_sub_filter = false;
						if(rt.pos_property_tags.size() == 0) {
							passed_sub_filter = true;
						} else {
							for(auto& tg : rt.pos_property_tags) {
								if(std::find(prop.property_tags.begin(), prop.property_tags.end(), tg) != prop.property_tags.end())
									passed_sub_filter = true;
							}
						}
						for(auto& tg : rt.neg_property_tags) {
							if(std::find(prop.property_tags.begin(), prop.property_tags.end(), tg) != prop.property_tags.end())
								passed_sub_filter = false;
						}

						if(passed_sub_filter) {
							output += "\t\t\tresult." + ob.name + "_" + prop.name + " = true;\n";
						}
					}
				}
			}
			output += "\t\t\treturn result;\n";
			output += "\t\t}\n";
		}
		// make serialize records

		output += "\n";

		//serialize_size
		output += "\t\tuint64_t serialize_size(load_record const& serialize_selection) const {\n";
		output += "\t\t\tuint64_t total_size = 0;\n";
		for(auto& ob : parsed_file.relationship_objects) {
			output += "\t\t\tif(serialize_selection." + ob.name + ") {\n";
			output += "\t\t\t\tdcon::record_header header(sizeof(uint32_t), \"uint32_t\", \"" + ob.name + "\", \"@size\");\n";
			output += "\t\t\t\ttotal_size += header.serialize_size();\n";
			output += "\t\t\t\ttotal_size += sizeof(uint32_t);\n";
			output += "\t\t\t}\n";

			if(ob.store_type == storage_type::erasable) {
				output += "\t\t\tif(serialize_selection." + ob.name + "__index) {\n";
				output += "\t\t\t\tdcon::record_header header(sizeof(" + ob.name + "_id) * " + ob.name + ".size_used, \"" + size_to_tag_type(ob.size) + "\", \"" + ob.name + "\", \"_index\");\n";
				output += "\t\t\t\ttotal_size += header.serialize_size();\n";
				output += "\t\t\t\ttotal_size += sizeof(" + ob.name + "_id) * " + ob.name + ".size_used;\n";
				output += "\t\t\t}\n";
			}

			for(auto& iob: ob.indexed_objects) {
				if(iob.related_to != ob.primary_key) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + iob.property_name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + iob.type_name + "_id) * " + ob.name + ".size_used, \""
						+ size_to_tag_type(iob.related_to->size) + "\", \"" + ob.name + "\", \"" + iob.property_name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += sizeof(" + iob.type_name + "_id) * " + ob.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}

			for(auto& prop : ob.properties) {
				if(prop.is_derived) {

				} else if(prop.type == property_type::bitfield) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header((" + ob.name + ".size_used + 7) / 8, \""
						+ "bitfield" + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += (" + ob.name + ".size_used + 7) / 8;\n";
					output += "\t\t\t}\n";
				} else if(prop.type == property_type::special_vector) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, &total_size](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + ob.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\ttotal_size += sizeof(uint16_t); total_size += sizeof(" + prop.data_type + ") * (rng.second - rng.first); });\n";
					output += "\t\t\t\ttotal_size += " + std::to_string(prop.data_type.length() + 1) + ";\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \"stable_mk_2_tag\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";

					output += "\t\t\t}\n";
				} else if(prop.type == property_type::object) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, &total_size]("
						+ prop.data_type + " const& obj){ total_size += t->serialize_size(obj); });\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \""
						+ prop.data_type + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t}\n";
				} else {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + prop.data_type + ") * " + ob.name + ".size_used, \""
						+ prop.data_type + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += sizeof(" + prop.data_type + ") * " + ob.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}
		}
		output += "\t\t\treturn total_size;\n";
		output += "\t\t}\n";

		//serialize
		output += "\t\tvoid serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {\n";

		for(auto& ob : parsed_file.relationship_objects) {
			output += "\t\t\tif(serialize_selection." + ob.name + ") {\n";
			output += "\t\t\t\tdcon::record_header header(sizeof(uint32_t), \"uint32_t\", \"" + ob.name + "\", \"@size\");\n";
			output += "\t\t\t\theader.serialize(output_buffer);\n";
			output += "\t\t\t\t*(reinterpret_cast<uint32_t*>(output_buffer)) = " + ob.name + ".size_used;\n";
			output += "\t\t\t\toutput_buffer += sizeof(uint32_t);\n";
			output += "\t\t\t}\n";

			if(ob.store_type == storage_type::erasable) {
				output += "\t\t\tif(serialize_selection." + ob.name + "__index) {\n";
				output += "\t\t\t\tdcon::record_header header(sizeof(" + ob.name + "_id) * " + ob.name + ".size_used, \"" + size_to_tag_type(ob.size) + "\", \"" + ob.name + "\", \"_index\");\n";
				output += "\t\t\t\theader.serialize(output_buffer);\n";
				output += "\t\t\t\tmemcpy(reinterpret_cast<" + ob.name + "_id*>(output_buffer), "
					+ ob.name + ".m__index.vptr(), sizeof(" + ob.name + "_id) * " + ob.name + ".size_used);\n";
				output += "\t\t\t\toutput_buffer += sizeof(" + ob.name + "_id) * " + ob.name + ".size_used;\n";
				output += "\t\t\t}\n";
			}

			for(auto& iob: ob.indexed_objects) {
				if(iob.related_to != ob.primary_key) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + iob.property_name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + iob.type_name + "_id) * " + ob.name + ".size_used, \""
						+ size_to_tag_type(iob.related_to->size) + "\", \"" + ob.name + "\", \"" + iob.property_name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<" + iob.type_name + "_id*>(output_buffer), "
						+ ob.name + ".m_" + iob.property_name + ".vptr(), sizeof(" + iob.type_name + "_id) * " + ob.name + ".size_used);\n";
					output += "\t\t\t\toutput_buffer += sizeof(" + iob.type_name + "_id) * " + ob.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}

			for(auto& prop : ob.properties) {
				if(prop.is_derived) {

				} else if(prop.type == property_type::bitfield) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header((" + ob.name + ".size_used + 7) / 8, \""
						+ "bitfield" + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<bitfield_type*>(output_buffer), "
						+ ob.name + ".m_" + prop.name  + ".vptr(), (" + ob.name + ".size_used + 7) / 8);\n";
					output += "\t\t\t\toutput_buffer += (" + ob.name + ".size_used + 7) / 8;\n";
					output += "\t\t\t}\n";
				} else if(prop.type == property_type::special_vector) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";

					output += "\t\t\t\tsize_t total_size = 0;\n";
					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, &total_size](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + ob.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\ttotal_size += sizeof(uint16_t); total_size += sizeof(" + prop.data_type + ") * (rng.second - rng.first); });\n";
					output += "\t\t\t\ttotal_size += " + std::to_string(prop.data_type.length() + 1) + ";\n";

					output += "\t\t\t\tdcon::record_header header(total_size, \"stable_mk_2_tag\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";

					output += "\t\t\t\tmemcpy(reinterpret_cast<char*>(output_buffer), \"" + prop.data_type + "\", " + std::to_string(prop.data_type.length() + 1) + ");\n";
					output += "\t\t\t\toutput_buffer += " + std::to_string(prop.data_type.length() + 1) + ";\n";

					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, output_buffer](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + ob.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\t*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(rng.second - rng.first);\n";
					output += "\t\t\t\t\toutput_buffer += sizeof(uint16_t);\n";
					output += "\t\t\t\t\tmemcpy(reinterpret_cast<" + prop.data_type + "*>(output_buffer), rng.first, sizeof(" + prop.data_type + ") * (rng.second - rng.first));\n"
						+ ob.name + ".m_" + prop.name + ".vptr(), sizeof(" + prop.data_type + ") * " + ob.name + ".size_used);\n";
					output += "\t\t\t\t\toutput_buffer += sizeof(" + prop.data_type + ") * (rng.second - rng.first);\n";
					output += "\t\t\t\t\t});\n";

					output += "\t\t\t}\n";
				} else if(prop.type == property_type::object) {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tsize_t total_size = 0;\n";
					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, &total_size](" 
						+ prop.data_type + " const& obj){ total_size += t->serialize_size(obj); });\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \""
						+ prop.data_type + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tstd::for_each(" + ob.name + ".m_" + prop.name + ".vptr(), "
						+ ob.name + ".m_" + prop.name + ".vptr() " + ob.name + ".size_used, [t = this, &output_buffer]("
						+ prop.data_type + " const& obj){ t->serialize(output_buffer, obj); });\n";
					output += "\t\t\t}\n";
				} else {
					output += "\t\t\tif(serialize_selection." + ob.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + prop.data_type + ") * " + ob.name + ".size_used, \""
						+ prop.data_type + "\", \"" + ob.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<" + prop.data_type + "*>(output_buffer), "
						+ ob.name + ".m_" + prop.name + ".vptr(), sizeof(" + prop.data_type + ") * " + ob.name + ".size_used);\n";
					output += "\t\t\t\toutput_buffer += sizeof(" + prop.data_type + ") * " + ob.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}
		}
		output += "\t\t}\n";

		//deserialize (no mask)
		output += "\t\tvoid deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection) {\n";
		output += "\t\t\twhile(input_buffer < end) {\n"; // loop over input buffer
		output += "\t\t\t\tdcon::record_header header;\n";
		output += "\t\t\t\theader.deserialize(input_buffer, end);\n";

		output += "\t\t\t\tif(input_buffer + header.record_size <= end) {\n"; // wrap: gaurantee enough space to read entire buffer

		bool first = true;
		for(auto& ob : parsed_file.relationship_objects) {
			if(first) {
				output += "\t\t\t\tif(header.is_object(\"" + ob.name + "\")) {\n"; //has matched object
				first = false;
			} else {
				output += "\t\t\t\telse if(header.is_object(\"" + ob.name + "\")) {\n"; //has matched object
			}
			output += "\t\t\t\t\tif(header.is_property(\"@size\") && header.record_size == sizeof(uint32_t)) {\n"; // is size
			output += "\t\t\t\t\t\t" + ob.name + "_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));\n";
			output += "\t\t\t\t\t\tserialize_selection." + ob.name + " = true;\n";
			output += "\t\t\t\t\t}\n"; // end is size

			if(ob.store_type == storage_type::erasable) {
				output += "\t\t\t\t\telse if(header.is_property(\"__index\")) {\n"; // matches
				output += "\t\t\t\t\tif(header.is_type(\"" + size_to_tag_type(ob.size)  + "\")) {\n"; //correct type
				output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m__index.vptr(), reinterpret_cast<" + size_to_tag_type(ob.size) + " const*>(input_buffer)"
					", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + size_to_tag_type(ob.size) + "), "
					"header.record_size));\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
				output += "\t\t\t\t\t}\n";// end correct type
				if(size_to_tag_type(ob.size) != "uint8_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint8_t\")) {\n"; //wrong type uint8_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint8_t
				}
				if(size_to_tag_type(ob.size) != "uint16_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //wrong type uint16_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint16_t
				}
				if(size_to_tag_type(ob.size) != "uint32_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //wrong type uint32_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint32_t
				}

				//redo free list
				output += "\t\t\t\t\t\tif(serialize_selection." + ob.name + "__index == true){\n";
				output += "\t\t\t\t\t" + ob.name + ".first_free = " + ob.name + "_id();\n";
				output += "\t\t\t\t\tfor(int32_t j = int32_t(" + std::to_string(ob.size) + "); j >= 0; --j) {\n";
				output += "\t\t\t\t\t\tif(" + ob.name + ".m__index.vptr()[j] != " + ob.name + "_id(" + size_to_tag_type(ob.size) + "(j))) {\n";
				output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[j] = " + ob.name + ".first_free;\n";
				output += "\t\t\t\t\t\t\t" + ob.name + ".first_free = " + ob.name + "_id(" + size_to_tag_type(ob.size) + "(j));\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t}\n\n";
				output += "\t\t\t\t\t}\n\n";

				output += "\t\t\t\t\t}\n"; //end index match
			} // end: load index handling for erasable

			for(auto& iob: ob.indexed_objects) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + iob.property_name + "\")) {\n"; // matches
				
				output += "\t\t\t\t\tif(header.is_type(\"uint8_t\")) {\n"; //type uint8_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint8_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size)  + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint16_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint32_t

				output += "\t\t\t\t\t}\n"; //end property match
			} // end index properties

			for(auto& prop : ob.properties) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + prop.name + "\")) {\n"; // matches
				if(prop.is_derived) {

				} else if(prop.type == property_type::bitfield) {
					output += "\t\t\t\t\tif(header.is_type(\"bitfield\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<bitfield_type const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used + 7) / 8, header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == "bool") {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + ob.name + ".m_" + prop.name + ".vptr(), i, convert_type(&temp, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + ob.name + ".m_" + prop.name + ".vptr(), i, "
									"convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				} else if(prop.type == property_type::special_vector) {
					output += "\t\t\t\t\tif(header.is_type(\"stable_mk_2_tag\")) {\n"; //correct type
					output += "\t\t\t\t\t\t\tuint32_t ix = 0;\n";

					//read internal data type
					output += "\t\t\t\tstd::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, 0);\n";
					
					output += "\t\t\t\t\tif(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
						"reinterpret_cast<char const*>(zero_pos), \"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ){\n";
					output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n";
					
					output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n";
					output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
						"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + prop.data_type + ") ));\n";
					output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
					output += "\t\t\t\t\t\t\t}\n"; // endif

					output += "\t\t\t\t\t\t\tdcon::load_range(" + ob.name + "." + prop.name + "_storage, " 
						+ ob.name + ".m_" + prop.name + ".vptr()[ix], reinterpret_cast<" + prop.data_type + " const*>(icpy), "
						"reinterpret_cast<" + prop.data_type + " const*>(icpy) + sz)\n";
					output += "\t\t\t\t\t\t\ticpy += sz * sizeof(" + prop.data_type + ");\n";
					output += "\t\t\t\t\t\t\t++ix;\n";
					output += "\t\t\t\t\t\t}\n"; //end for

					output += "\t\t\t\t\t}\n"; // end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from
								
								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";
								
								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(reinterpret_cast<" + con.from + " const*>(icpy), (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + con.from + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from

							}
						}
					} // end for each in conversion list
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + basic_type + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + basic_type + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(icpy) + i));\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + basic_type + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							}
						}
					}
					// end if prop is special array
				} else if(prop.type == property_type::object) {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + prop.data_type + "))); ++i) {\n";
					output += "\t\t\t\t\t\t\tdeserialize(icpy, " + ob.name + ".m_" + prop.name + ".vptr()[i], input_buffer + header.record_size);\n";
					output += "\t\t\t\t\t\t}\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";

					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer, (" + con.to + "*)nullptr) + i);\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
				} else {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(header.is_type(\"" + basic_type + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + basic_type + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(input_buffer) + i));\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				}
				output += "\t\t\t\t\t}\n"; //end property match
			} // end properties

			output += "\t\t\t\t}\n"; // end has matched object
		}
		output += "\t\t\t\t}\n"; // end wrap: gaurantee enough space to read entire buffer
		output += "\t\t\t\tinput_buffer += header.record_size;\n";

		output += "\t\t\t}\n"; // end loop -- input buffer exhausted
		output += "\t\t}\n"; // end deserialize (no mask)


		//deserialize (with mask)
		output += "\t\tvoid deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection, load_record const& mask) {\n";
		output += "\t\t\twhile(input_buffer < end) {\n"; // loop over input buffer
		output += "\t\t\t\tdcon::record_header header;\n";
		output += "\t\t\t\theader.deserialize(input_buffer, end);\n";

		output += "\t\t\t\tif(input_buffer + header.record_size <= end) {\n"; // wrap: gaurantee enough space to read entire buffer

		bool first_header_if = true;
		for(auto& ob : parsed_file.relationship_objects) {
			if(first_header_if) {
				output += "\t\t\t\tif(header.is_object(\"" + ob.name + "\") && mask." + ob.name + ") {\n"; //has matched object
				first_header_if = false;
			} else {
				output += "\t\t\t\telse if(header.is_object(\"" + ob.name + "\")) {\n"; //has matched object
			}
			output += "\t\t\t\t\tif(header.is_property(\"@size\") && header.record_size == sizeof(uint32_t)) {\n"; // is size
			output += "\t\t\t\t\t\t" + ob.name + "_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));\n";
			output += "\t\t\t\t\t\tserialize_selection." + ob.name + " = true;\n";
			output += "\t\t\t\t\t}\n"; // end is size

			if(ob.store_type == storage_type::erasable) {
				output += "\t\t\t\t\telse if(header.is_property(\"__index\") && mask." + ob.name + "__index) {\n"; // matches
				output += "\t\t\t\t\tif(header.is_type(\"" + size_to_tag_type(ob.size) + "\")) {\n"; //correct type
				output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m__index.vptr(), reinterpret_cast<" + size_to_tag_type(ob.size) + " const*>(input_buffer)"
					", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + size_to_tag_type(ob.size) + "), "
					"header.record_size));\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
				output += "\t\t\t\t\t}\n";// end correct type
				if(size_to_tag_type(ob.size) != "uint8_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint8_t\")) {\n"; //wrong type uint8_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint8_t
				}
				if(size_to_tag_type(ob.size) != "uint16_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //wrong type uint16_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint16_t
				}
				if(size_to_tag_type(ob.size) != "uint32_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //wrong type uint32_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(ob.size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint32_t
				}

				//redo free list
				output += "\t\t\t\t\t\tif(serialize_selection." + ob.name + "__index == true){\n";
				output += "\t\t\t\t\t" + ob.name + ".first_free = " + ob.name + "_id();\n";
				output += "\t\t\t\t\tfor(int32_t j = int32_t(" + std::to_string(ob.size) + "); j >= 0; --j) {\n";
				output += "\t\t\t\t\t\tif(" + ob.name + ".m__index.vptr()[j] != " + ob.name + "_id(" + size_to_tag_type(ob.size) + "(j))) {\n";
				output += "\t\t\t\t\t\t\t" + ob.name + ".m__index.vptr()[j] = " + ob.name + ".first_free;\n";
				output += "\t\t\t\t\t\t\t" + ob.name + ".first_free = " + ob.name + "_id(" + size_to_tag_type(ob.size) + "(j));\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t}\n\n";
				output += "\t\t\t\t\t}\n\n";

				output += "\t\t\t\t\t}\n"; //end index match
			} // end: load index handling for erasable

			for(auto& iob: ob.indexed_objects) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + iob.property_name + "\") && mask." + ob.name + "_" + iob.property_name + ") {\n"; // matches

				output += "\t\t\t\t\tif(header.is_type(\"uint8_t\")) {\n"; //type uint8_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint8_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint16_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + iob.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(iob.related_to->size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + ob.name + "_set_" + iob.property_name + "(" + ob.name + "_id(" + size_to_tag_type(ob.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + iob.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint32_t

				output += "\t\t\t\t\t}\n"; //end property match
			} // end index properties

			for(auto& prop : ob.properties) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + prop.name + "\") && mask." + ob.name + "_" + prop.name + ") {\n"; // matches
				if(prop.is_derived) {

				} else if(prop.type == property_type::bitfield) {
					output += "\t\t\t\t\tif(header.is_type(\"bitfield\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<bitfield_type const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used + 7) / 8, header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == "bool") {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + ob.name + ".m_" + prop.name + ".vptr(), i, convert_type(&temp, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + ob.name + ".m_" + prop.name + ".vptr(), i, "
									"convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				} else if(prop.type == property_type::special_vector) {
					output += "\t\t\t\t\tif(header.is_type(\"stable_mk_2_tag\")) {\n"; //correct type
					output += "\t\t\t\t\t\t\tuint32_t ix = 0;\n";

					//read internal data type
					output += "\t\t\t\tstd::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, 0);\n";

					output += "\t\t\t\t\tif(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
						"reinterpret_cast<char const*>(zero_pos), \"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ){\n";
					output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n";

					output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n";
					output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
						"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + prop.data_type + ") ));\n";
					output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
					output += "\t\t\t\t\t\t\t}\n"; // endif

					output += "\t\t\t\t\t\t\tdcon::load_range(" + ob.name + "." + prop.name + "_storage, "
						+ ob.name + ".m_" + prop.name + ".vptr()[ix], reinterpret_cast<" + prop.data_type + " const*>(icpy), "
						"reinterpret_cast<" + prop.data_type + " const*>(icpy) + sz)\n";
					output += "\t\t\t\t\t\t\ticpy += sz * sizeof(" + prop.data_type + ");\n";
					output += "\t\t\t\t\t\t\t++ix;\n";
					output += "\t\t\t\t\t\t}\n"; //end for

					output += "\t\t\t\t\t}\n"; // end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(reinterpret_cast<" + con.from + " const*>(icpy), (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + con.from + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from

							}
						}
					} // end for each in conversion list
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + basic_type + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + ob.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + basic_type + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + ob.name + "." + prop.name + "_storage, " + ob.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(icpy) + i));\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + basic_type + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							}
						}
					}
					// end if prop is special array
				} else if(prop.type == property_type::object) {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + prop.data_type + "))); ++i) {\n";
					output += "\t\t\t\t\t\t\tdeserialize(icpy, " + ob.name + ".m_" + prop.name + ".vptr()[i], input_buffer + header.record_size);\n";
					output += "\t\t\t\t\t\t}\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";

					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer, (" + con.to + "*)nullptr) + i);\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
				} else {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + ob.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + ob.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(header.is_type(\"" + basic_type + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + ob.name + ".size_used, uint32_t(header.record_size / sizeof(" + basic_type + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + ob.name + ".m_" + prop.name + ".vptr()[i] = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(input_buffer) + i));\n";
								output += "\t\t\t\t\t\tserialize_selection." + ob.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				}
				output += "\t\t\t\t\t}\n"; //end property match
			} // end properties

			output += "\t\t\t\t}\n"; // end has matched object
		}
		output += "\t\t\t\t}\n"; // end wrap: gaurantee enough space to read entire buffer
		output += "\t\t\t\tinput_buffer += header.record_size;\n";

		output += "\t\t\t}\n"; // end loop -- input buffer exhausted
		output += "\t\t}\n"; // end deserialize (with mask)

		output += "\n";
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
