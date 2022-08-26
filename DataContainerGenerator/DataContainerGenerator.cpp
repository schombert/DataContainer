//
// This file provided as part of the DataContainer project
//

#include <string>
#include <vector>
#include <fstream>
#include <filesystem> 
#include <iostream> 
#include <algorithm>

std::string extract_string(char const* & input, char const* end) {
	std::string result;

	while(input < end && (*input == ' ' || *input == ',' || *input == '\t' || *input == '\r' || *input == '\n'))
		++input;

	if(input >= end)
		return result;

	bool in_quote = false;
	int in_lt = 0;

	while(input < end && (in_quote || in_lt > 0 || (*input != ' ' && *input != '\t' && *input != '\r' && *input != '\n'))) {
		if(!in_quote && *input == '<')
			++in_lt;
		else if(!in_quote && *input == '>')
			--in_lt;
		else if(*input == '\"')
			in_quote = !in_quote;
		
		result += *input;
		++input;
	}

	return result;
}

enum class parsing_state { outer, in_object_relation, in_property, in_load_save };
enum class storage_type { contiguous, erasable, compactable};

struct property_def {
	std::string name;

	bool is_object = false;
	bool is_special_vector = false;
	bool is_derived = false;
	bool is_bitfield = false;

	int special_pool_size = 1000;
	std::string data_type;

	bool hook_get = false;
	bool hook_set = false;

	std::vector<std::string> property_tags;
};

enum class index_type { many, at_most_one, none };
enum class list_type { list, array, std_vector };

struct relationship_object_def;

struct related_object {
	std::string property_name;
	std::string type_name;
	index_type index;
	list_type ltype;
	relationship_object_def* related_to;
};

struct in_relation_information {
	std::string relation_name;
	std::string property_name;
	bool as_primary_key;
	index_type indexed_as;
	list_type listed_as;
	relationship_object_def* rel_ptr;
};

struct relationship_object_def {
	std::string name;
	bool is_relationship = false;
	std::vector<std::string> obj_tags;
	size_t size = 1000;
	bool is_expandable = false;
	storage_type store_type = storage_type::contiguous;

	bool hook_create = false;
	bool hook_delete = false;
	bool hook_move = false;

	std::vector<related_object> indexed_objects;
	std::vector<property_def> properties;
	std::vector<in_relation_information> relationships_involved_in;

	relationship_object_def* primary_key = nullptr;
};

struct load_save_def {
	std::string name;
	bool all_properties = true;
	bool all_objects = true;
	std::vector<std::string> pos_obj_tags;
	std::vector<std::string> pos_property_tags;
	std::vector<std::string> neg_obj_tags;
	std::vector<std::string> neg_property_tags;
};

struct conversion_def {
	std::string from;
	std::string to;
};

struct file_def {
	std::string namspace = "dcon";
	std::vector<std::string> includes;
	std::vector<std::string> globals;
	std::vector<std::string> legacy_types;

	std::vector<relationship_object_def> relationship_objects;
	std::vector<load_save_def> load_save_routines;
	std::vector<conversion_def> conversion_list;

	std::vector<std::string> object_types;
};

relationship_object_def* find_by_name(file_def& def, std::string const& name) {
	if(auto r = std::find_if(
		def.relationship_objects.begin(), def.relationship_objects.end(),
		[&name](relationship_object_def const& o) { return o.name == name; }); r != def.relationship_objects.end()) {
		return &(*r);
	}
	return nullptr;
}

std::string make_relationship_parameters(relationship_object_def const& o) {
	std::string result;
	for(auto& i : o.indexed_objects) {
		if(result.length() != 0) 
			result += ", ";
		result += i.type_name + "_id " + i.property_name + "_p";
	}
	return result;
}

void process_data_type(std::string &second_term, property_def * last_prop, const char * &str_ptr, const char *const &str_end) {
	if(second_term == "bitfield") {
		last_prop->is_bitfield = true;
	} else if(second_term == "derived") {
		last_prop->is_derived = true;
		last_prop->data_type = extract_string(str_ptr, str_end);

		while(str_ptr < str_end) {
			auto const extra_term = extract_string(str_ptr, str_end);
			if(extra_term.size() > 0) {
				last_prop->data_type += " ";
				last_prop->data_type += extra_term;
			}
		}
	} else if(second_term == "object") {
		last_prop->is_object = true;
		last_prop->data_type = extract_string(str_ptr, str_end);
	} else if(second_term == "vector_pool") {
		last_prop->is_special_vector = true;
		last_prop->special_pool_size = std::stoi(extract_string(str_ptr, str_end));
		last_prop->data_type = extract_string(str_ptr, str_end);

		while(str_ptr < str_end) {
			auto const extra_term = extract_string(str_ptr, str_end);
			if(extra_term.size() > 0) {
				last_prop->data_type += " ";
				last_prop->data_type += extra_term;
			}
		}
	} else {
		last_prop->data_type = second_term;

		while(str_ptr < str_end) {
			auto const extra_term = extract_string(str_ptr, str_end);
			if(extra_term.size() > 0) {
				last_prop->data_type += " ";
				last_prop->data_type += extra_term;
			}
		}
	}
}

bool is_vectorizable_type(file_def& def, std::string const& name) {
	return name == "char" || name == "int" || name == "short" || name == "unsigned short" || 
		name == "unsigned int" || name == "unsigned char" || name == "signed char" ||
		name == "float" || name == "int8_t" || name == "uint8_t" || 
		name == "int16_t" || name == "uint16_t" || name == "int32_t" || name == "uint32_t"
		|| [&](){
			return name.length() >= 4 && name[name.length() - 1] == 'd' && name[name.length() - 2] == 'i' &&
				name[name.length() - 3] == '_' && find_by_name(def, name.substr(0, name.length() - 3)) != nullptr;
		}();
}

std::vector<std::string> common_types{ std::string("int8_t"), std::string("uint8_t"), std::string("int16_t"), std::string("uint16_t")
	, std::string("int32_t"), std::string("uint32_t"), std::string("int64_t"), std::string("uint64_t"), std::string("float"), std::string("double") };

std::string normalize_type(std::string in) {
	if(in == "char" || in == "unsigned char")
		return "uint8_t";
	if(in == "signed char")
		return "int8_t";
	if(in == "short")
		return "int16_t";
	if(in == "unsigned short")
		return "uint16_t";
	if(in == "int" || in == "long")
		return "int32_t";
	if(in == "unsigned int" || in == "unsigned long")
		return "uint32_t";
	if(in == "size_t" || in == "unsigned long long")
		return "uint64_t";
	if(in == "long long")
		return "int64_t";
	else
		return in;
}

bool is_common_type(std::string in) {
	return std::find(common_types.begin(), common_types.end(), normalize_type(in)) != common_types.end();
}

std::string size_to_tag_type(size_t sz) {
	if(sz == 0) {
		return "uint32_t";
	} else if(sz <= 126) {
		return "uint8_t";
	} else if(sz <= std::numeric_limits<int16_t>::max() - 1) {
		return "uint16_t";
	}
	return "uint32_t";
}

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
				if(p.is_object) {
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

		// compose contents of generated file
		std::string output;

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
		output += "\tstruct load_record{\n";
		for(auto& o : parsed_file.relationship_objects) {
			output += "\t\tbool " + o.name + " = false;\n";
			if(o.store_type == storage_type::erasable) {
				output += "\t\t\tbool " + o.name + "__index = false;\n";
			}
			for(auto& io : o.indexed_objects) {
				output += "\t\tbool " + o.name + "_" + io.property_name + " = false;\n";
			}
			for(auto& prop : o.properties) {
				output += "\t\tbool " + o.name + "_" + prop.name + " = false;\n";
			}
		}
		output += "\t};\n\n";

		

		//id types definitions
		for(auto& o : parsed_file.relationship_objects) {
			if(!o.primary_key) {
				const auto underlying_type = o.is_expandable ? std::string("uint32_t") : size_to_tag_type(o.size);
				//id class begin
				output += std::string("\tclass ") + o.name + "_id {\n";

				output += "\t\tpublic:\n";
				output += "\t\tusing value_base_t = " + underlying_type + ";\n";
				output += "\t\tusing zero_is_null_t = std::true_type;\n";
				output += "\n";

				//value member declaration
				output += std::string("\t\t") + underlying_type + " value;\n\n";

				//constructors
				output += std::string("\t\texplicit constexpr ") + o.name + "_id(" + underlying_type + " v) noexcept : value(v + 1) {}\n";
				output += std::string("\t\tconstexpr ") + o.name + "_id(const " + o.name + "_id& v) noexcept = default;\n";
				output += std::string("\t\tconstexpr ") + o.name + "_id(" + o.name + "_id&& v) noexcept = default;\n";
				output += std::string("\t\tconstexpr ") + o.name + "_id() noexcept : value(" + underlying_type + "(0)) {}\n\n";

				//operators
				output += "\t\t" + o.name + "_id& operator=(" + o.name + "_id&& v) noexcept = default;\n";
				output += "\t\t" + o.name + "_id& operator=(" + o.name + "_id const& v) noexcept = default;\n";
				output += "\t\tconstexpr bool operator==(" + o.name + "_id v) const noexcept { return value == v.value; }\n";
				output += "\t\tconstexpr bool operator!=(" + o.name + "_id v) const noexcept { return value != v.value; }\n";
				output += "\t\tconstexpr bool operator<(" + o.name + "_id v) const noexcept { return value < v.value; }\n";
				output += "\t\tconstexpr bool operator<=(" + o.name + "_id v) const noexcept { return value <= v.value; }\n";
				output += "\t\texplicit constexpr operator bool() const noexcept { return value != " + underlying_type + "(0); }\n\n";

				//index_function
				output += "\t\tconstexpr DCON_RELEASE_INLINE int32_t index() const noexcept {\n";
				output += "\t\t\treturn int32_t(value) - 1;\n";
				output += "\t\t}\n";

				//id class end
				output += "\t};\n\n";

				output += std::string("\tclass ") + o.name + "_id_pair {\n";
				output += "\t\tpublic:\n";
				output += "\t\t" + o.name + "_id left;\n";
				output += "\t\t" + o.name + "_id right;\n";
				output += "\t};\n\n";

				output += "\tconstexpr DCON_RELEASE_INLINE bool is_valid_index(" + o.name + "_id id) { return bool(id); }\n\n";
			} else {
				output += "\tusing " + o.name + "_id = " + o.primary_key->name + "_id;\n\n";
			}
		}

		// close namespace briefly
		output += "}\n\n";

		//mark each id as going into a tagged vector
		output += "namespace ve {\n";
		for(auto& o : parsed_file.relationship_objects) {
			if(!o.primary_key) {
				output += "\t\ttemplate<>\n";
				output += "\t\tstruct value_to_vector_type_s<" + parsed_file.namspace + "::" + o.name + "_id> {\n";
				output += "\t\t\tusing type = tagged_vector<" + parsed_file.namspace + "::" + o.name + "_id>;\n";
				output += "\t\t};\n";
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

		for(auto& o : parsed_file.relationship_objects) {
			//object class begin
			output += "\t\tclass alignas(64) " + o.name + "_class {\n";

			//begin members declaration
			output += "\t\t\tprivate:\n";
			output += "\t\t\tuint32_t size_used = 0;\n";
			if(o.store_type == storage_type::erasable) {
				if(!o.is_expandable) {
					output += "\t\t\t" + o.name + "_id first_free;\n";
					output += "\t\t\tstruct alignas(64) dtype__index { \n"
						"\t\t\t\t" + o.name + "_id values[" + std::to_string(o.size) + "]; \n"
						"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
						"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
						"\t\t\t\tdtype__index() { std::uninitialized_value_construct_n(values, " + std::to_string(o.size) + "); } "
						"\t\t\t} m__index;\n";
				} else {
					output += "\t\t\t" + o.name + "_id first_free;\n";
					output += "\t\t\tstruct dtype__index { \n"
						"\t\t\t\tstd::vector<" + o.name + "_id> values; \n"
						"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
						"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
						"\t\t\t\tdtype__index() { values.emplace_back(); }"
						"\t\t\t} m__index;\n";
				}
			}

			for(auto& p : o.properties) {
				if(p.is_derived) {
					// no data for a derived property
				} else if(p.is_bitfield) {
					if(!o.is_expandable) {
						std::string bytes_size = std::string("((uint32_t(") + std::to_string(o.size) + " + 7)) / 8ui32 + 63ui32) & ~63ui32";
						output += "\t\t\tstruct alignas(64) dtype_" + p.name + " { \n"
							"\t\t\t\tdcon::bitfield_type padding[64]; \n"
							"\t\t\t\tdcon::bitfield_type values[" + bytes_size + "]; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr()  const{ return values; }\n"
							"\t\t\t\tdtype_" + p.name + "() { std::fill_n(values - 1, 1 + " + bytes_size + ", dcon::bitfield_type{ 0ui8 }); }\n"
							"\t\t\t} m_" + p.name + ";\n";
					} else {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\t\tstd::vector<dcon::bitfield_type> values; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
							"\t\t\t\tdtype_" + p.name + "() { values.push_back(dcon::bitfield_type{ 0ui8 }); }\n"
							"\t\t\t} m_" + p.name + ";\n";
					}
				} else if(p.is_object) {
					if(!o.is_expandable) {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\t\t" + p.data_type + " values[" + std::to_string(o.size) + "]; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
							"\t\t\t\tdtype_" + p.name + "() {}\n"
							"\t\t\t} m_" + p.name + ";\n";
					} else {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\tstd::vector<" + p.data_type + "> values; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
							"\t\t\t\tdtype_" + p.name + "() { values.emplace_back(); }\n"
							"\t\t\t} m_" + p.name + ";\n";
					}
				} else if(p.is_special_vector) {
					//fill in with special vector type and pool object
					if(!o.is_expandable) {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\tstable_mk_2_tag values[" + std::to_string(o.size) + "]; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
							"\t\t\tdtype_" + p.name + "() { std::uninitialized_fill_n(values, " + std::to_string(o.size) +
							", std::numeric_limits<dcon::stable_mk_2_tag>::max()); }\n"
							"\t\t\t} m_" + p.name + ";\n";
						output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + p.data_type + ", 16, " + std::to_string(p.special_pool_size) + " > " + p.name + "_storage;\n";
					} else {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\tstd::vector<stable_mk_2_tag> values; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
							"\t\t\tdtype_" + p.name + "() { values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max())); }\n"
							"\t\t\t} m_" + p.name + ";\n";
						output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + p.data_type + ", 16, " + std::to_string(p.special_pool_size) + " > " + p.name + "_storage;\n";
					}
				} else {
					if(!o.is_expandable) {
						std::string member_count = std::string("(sizeof(") + p.data_type + ") <= 64 ? ("
							"uint32_t(" + std::to_string(o.size) + ") + (64ui32 / uint32_t(sizeof(" + p.data_type + "))) - 1ui32) "
							"& ~(64ui32 / uint32_t(sizeof(" + p.data_type + ")) - 1ui32) : uint32_t(" + std::to_string(o.size) + "))";
						output += "\t\t\tstruct alignas(64) dtype_" + p.name + " { \n"
							"\t\t\t\tuint8_t padding[(sizeof(" + p.data_type + ") + 63ui32) & ~63ui32]; \n"
							"\t\t\t\t" + p.data_type + " values[" + member_count + "]; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
							"\t\t\t\tdtype_" + p.name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\n"
							"\t\t\t} m_" + p.name + ";\n";
					} else {
						output += "\t\t\tstruct dtype_" + p.name + " { \n"
							"\t\t\t\tstd::vector<" + p.data_type + "> values; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
							"\t\t\t\tdtype_" + p.name + "() { values.emplace_back(); }\n"
							"\t\t\t} m_" + p.name + ";\n";
					}
				}
			}

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
			*/

			for(auto& i : o.indexed_objects) {
				if(i.related_to == o.primary_key) {
					//skip recording index value
				} else {
					if(!o.is_expandable) {
						std::string member_count = std::string("(sizeof(") + i.type_name + "_id) <= 64 ? ("
							"uint32_t(" + std::to_string(o.size) + ") + (64ui32 / uint32_t(sizeof(" + i.type_name + "_id))) - 1ui32) "
							"& ~(64ui32 / uint32_t(sizeof(" + i.type_name + "_id)) - 1ui32) : uint32_t(" + std::to_string(o.size) + "))";
						output += "\t\t\tstruct alignas(64) dtype_" + i.property_name + " { \n"
							"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \n"
							"\t\t\t\t" + i.type_name + "_id values[" + member_count + "]; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
							"\t\t\t\tdtype_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\n"
							"\t\t\t} m_" + i.property_name + ";\n";
					} else {
						output += "\t\t\tstruct dtype_" + i.property_name + " { \n"
							"\t\t\t\tstd::vector<" + i.type_name + "_id> values; \n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
							"\t\t\t\tdtype_" + i.property_name + "() { values.emplace_back(); }\n"
							"\t\t\t} m_" + i.property_name + ";\n";
					}
				}

				if(i.index == index_type::many) {
					if(i.ltype == list_type::list) {
						if(!o.is_expandable) {
							// list intrusive links
							output += "\t\t\tstruct dtype_link_" + i.property_name + " { \n"
								"\t\t\t\t" + i.type_name + "_id_pair values[" + std::to_string(o.size) + "]; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
								"\t\t\t\tdtype_link_" + i.property_name + "() { std::uninitialized_value_construct_n(values, " + std::to_string(o.size) + "); }\n"
								"\t\t\t} m_link_" + i.property_name + ";\n";
						} else {
							// list intrusive links
							output += "\t\t\tstruct dtype_link_" + i.property_name + " { \n"
								"\t\t\tstd::vector<" + i.type_name + "_id_pair> values; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
								"\t\t\t\tdtype_link_" + i.property_name + "() { values.emplace_back(); }\n"
								"\t\t\t} m_link_" + i.property_name + ";\n";
						}

						if(!i.related_to->is_expandable) {
							// reference back to head list entry from object
							std::string member_count = std::string("(sizeof(") + o.name + "_id) <= 64 ? ("
								"uint32_t(" + std::to_string(i.related_to->size) + ") + (64ui32 / uint32_t(sizeof(" + o.name + "_id))) - 1ui32) "
								"& ~(64ui32 / uint32_t(sizeof(" + i.type_name + "_id)) - 1ui32) : uint32_t(" + std::to_string(i.related_to->size) + "))";
							output += "\t\t\tstruct alignas(64) dtype_head_back_" + i.property_name + " { \n"
								"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \n"
								"\t\t\t\t" + o.name + "_id values[" + member_count + "]; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
								"\t\t\t\tdtype_head_back_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\n"
								"\t\t\t} m_head_back_" + i.property_name + ";\n";
						} else {
							// reference back to head list entry from object
							output += "\t\t\tstruct dtype_head_back_" + i.property_name + " { \n"
								"\t\t\t\tstd::vector<" + o.name + "_id> values; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
								"\t\t\t\tdtype_head_back_" + i.property_name + "() { values.emplace_back(); }\n"
								"\t\t\t} m_head_back_" + i.property_name + ";\n";
						}
					} else if(i.ltype == list_type::std_vector) {
						//array of relation ids in object
						if(!i.related_to->is_expandable) {
							output += "\t\t\tstruct dtype_array_" + i.property_name + " { \n"
								"\t\t\t\tstd::vector<" + o.name + "_id> values[" + std::to_string(i.related_to->size) + "]; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
								"\t\t\t\tdtype_array_" + i.property_name + "() {  }\n"
								"\t\t\t} m_array_" + i.property_name + ";\n";
						} else {
							output += "\t\t\tstruct dtype_array_" + i.property_name + " { \n"
								"\t\t\t\tstd::vector<std::vector<" + o.name + "_id>> values; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
								"\t\t\t\tdtype_array_" + i.property_name + "() { values.emplace_back(); }\n"
								"\t\t\t} m_array_" + i.property_name + ";\n";
						}
					} else if(i.ltype == list_type::array) {
						//array of relation ids in object
						if(!i.related_to->is_expandable) {
							output += "\t\t\tstruct alignas(64) dtype_array_" + i.property_name + " { \n"
								"\t\t\t\tstable_mk_2_tag values[" + std::to_string(i.related_to->size) + "]; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
								"\t\t\t\tdtype_array_" + i.property_name + "() { std::uninitialized_fill_n(values, " + std::to_string(i.related_to->size) +
								", std::numeric_limits<dcon::stable_mk_2_tag>::max()); }\n"
								"\t\t\t} m_array_" + i.property_name + ";\n";
							output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + i.type_name + "_id, 16, " + std::to_string(o.size * 2) + " > "
								+ i.property_name + "_storage;\n";
						} else {
							error_to_file(output_file_name, std::string("Unable to estimate an upper bound on storage space for ") +
								o.name + " " + i.property_name + " arrays because the target is expandable");
						}


					}
				} else if(i.index == index_type::at_most_one) {
					if(i.related_to == o.primary_key) {
						// no link back for primary key
					} else {
						if(!i.related_to->is_expandable) {
							std::string member_count = std::string("(sizeof(") + o.name + "_id) <= 64 ? ("
								"uint32_t(" + std::to_string(i.related_to->size) + ") + (64ui32 / uint32_t(sizeof(" + o.name + "_id))) - 1ui32) "
								"& ~(64ui32 / uint32_t(sizeof(" + i.type_name + "_id)) - 1ui32) : uint32_t(" + std::to_string(i.related_to->size) + "))";
							output += "\t\t\tstruct alignas(64) dtype_link_back_" + i.property_name + " { \n"
								"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \n"
								"\t\t\t\t" + o.name + "_id values[" + member_count + "]; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values; }\n"
								"\t\t\t\tdtype_link_back_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\n"
								"\t\t\t} m_link_back_" + i.property_name + ";\n";
						} else {
							output += "\t\t\tstruct dtype_link_back_" + i.property_name + " { \n"
								"\t\t\t\tstd::vector<" + o.name + "_id> values; \n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }\n"
								"\t\t\t\tdtype_link_back_" + i.property_name + "() { values.emplace_back(); }\n"
								"\t\t\t} m_link_back_" + i.property_name + ";\n";
						}
					}
				}
			}



			output += "\n";
			output += "\t\t\tpublic:\n";

			// constructor
			if(o.store_type == storage_type::erasable && !o.is_expandable) {
				output += "\t\t\t" + o.name + "() {\n";
				output += "\t\t\t\tfor(int32_t i = " + std::to_string(o.size) + " - 1; i >= 0; --i) {\n";
				output += "\t\t\t\t\tm_index.vptr()[i] = first_free;\n";
				output += "\t\t\t\t\tfirst_free = " + o.name + "_id(" + size_to_tag_type(o.size) + "(i));\n";
				output += "\t\t\t\t}\n";
				output += "\t\t\t}\n\n";
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
		for(auto& o : parsed_file.relationship_objects) {
			output += "\t\tinternal::" + o.name + "_class " + o.name + ";\n";
		}
		output += "\n";

		for(auto& o : parsed_file.relationship_objects) {
			const std::string id_name = (o.primary_key ? o.primary_key->name : o.name) + "_id";
			const std::string con_tags_type = o.is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

			//getters and setters
			for(auto& p : o.properties) {

				if(p.hook_get) {
					if(p.is_bitfield) {
						output += "\t\tbool " + o.name + "_get_" + p.name + "(" + id_name + " id) const;\n";

						output += "\t\tve::vbitfield_type " + o.name + "_get_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const {\n";
						output += "\t\t\tve::vbitfield_type r; r.v = 0;\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\tr.v |= (" + o.name + "_get_" + p.name + "(" + id_name + "(id.value + i))) << i;\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";

						output += "\t\tve::vbitfield_type " + o.name + "_get_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const {\n";
						output += "\t\t\tve::vbitfield_type r; r.v = 0;\n";
						output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\n";
						output += "\t\t\t\tr.v |= (" + o.name + "_get_" + p.name + "(" + id_name + "(id.value + i))) << i;\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";

						output += "\t\tve::vbitfield_type " + o.name + "_get_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const {\n";
						output += "\t\t\tve::vbitfield_type r; r.v = 0;\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\tr.v |= (" + o.name + "_get_" + p.name + "(id[i])) << i;\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";
					} else if(is_vectorizable_type(parsed_file, p.data_type)) {
						output += "\t\t" + p.data_type + " " + o.name + "_get_" + p.name + "(" + id_name + " id) const;\n";

						output += "\t\tve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const {\n";
						output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\tr.set(i, " + o.name + "_get_" + p.name + "(" + id_name + "(id.value + i)));\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";

						output += "\t\tve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const {\n";
						output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\n";
						output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\n";
						output += "\t\t\t\tr.set(i, " + o.name + "_get_" + p.name + "(" + id_name + "(id.value + i)));\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";

						output += "\t\tve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const {\n";
						output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\tr.set(i, " + o.name + "_get_" + p.name + "(id[i]));\n";
						output += "\t\t\treturn r;\n";
						output += "\t\t}\n";
					} else {
						output += "\t\t" + p.data_type + " " + o.name + "_get_" + p.name + "(" + id_name + " id) const;\n";
					}
				}
				if(p.hook_set) {
					if(p.is_bitfield) {
						output += "\t\t" "void " + o.name + "_set_" + p.name + "(" + id_name + " id, bool value);\n";

						output += "\t\t" "void " + o.name + "_set_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
							"ve::vbitfield_type value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(" + id_name + "(id.value + i), (value.v & uint8_t(1 << i)) != 0);\n";
						output += "\t\t}\n";

						output += "\t\t" "void " + o.name + "_set_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
							"ve::vbitfield_type value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(" + id_name + "(id.value + i), (value.v & uint8_t(1 << i)) != 0);\n";
						output += "\t\t}\n";

						output += "\t\t" "void " + o.name + "_set_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
							"ve::vbitfield_type value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(id[i], (value.v & uint8_t(1 << i)) != 0);\n";
						output += "\t\t}\n";

					} else if(is_vectorizable_type(parsed_file, p.data_type)) {
						output += "\t\t" "void " + o.name + "_set_" + p.name + "(" + id_name + " id, " + p.data_type + " value);\n";

						output += "\t\t" "void " + o.name + "_set_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(" + id_name + "(id.value + i), value[i]);\n";
						output += "\t\t}\n";


						output += "\t\t" "void " + o.name + "_set_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(" + id_name + "(id.value + i), value[i]);\n";
						output += "\t\t}\n";

						output += "\t\t" "void " + o.name + "_set_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> value) {\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
						output += "\t\t\t\t" + o.name + "_set_" + p.name + "(id[i], value[i]);\n";
						output += "\t\t}\n";

					} else {
						output += "\t\t" "void " + o.name + "_set_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value);\n";
					}
				}

				if(p.is_derived) {

				} else if(p.is_bitfield) {
					if(!p.hook_get) {
						output += "\t\t" "DCON_RELEASE_INLINE bool " + o.name + "_get_" + p.name + "(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn dcon::bit_vector_test(" + o.name + ".m_" + p.name + ".vptr()[id.index()]);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type " + o.name + "_get_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type " + o.name + "_get_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type " + o.name + "_get_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";
					}
					if(!p.hook_set) {
						output += "\t\t" "DCON_RELEASE_INLINE void " + o.name + "_set_" + p.name + "(" + id_name + " id, bool value) {\n";
						output += "\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + p.name + ".vptr(), id.index(), value);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
							"ve::vbitfield_type values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
							"ve::vbitfield_type values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
							"ve::vbitfield_type values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";
					}
				} else if(p.is_object) {
					if(!p.hook_get) {
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + " const& " + o.name + "_get_" + p.name + "(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& " + o.name + "_get_" + p.name + "(" + id_name + " id) noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";
					}
					if(!p.hook_set) {
						output += "\t\tDCON_RELEASE_INLINE void " + o.name + "_set_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value) noexcept {\n";
						output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\n";
						output += "\t\t}\n";
					}
				} else if(p.is_special_vector) {

					if(!p.hook_get) {
						output += "\t\tstd::pair<" + p.data_type + "*, " + p.data_type + "*> " + o.name + "_get_" + p.name + "_range(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn dcon::get_range(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\n";
						output += "\t\t}\n";

						output += "\t\t" + p.data_type + "& " + o.name + "_get_" + p.name + "_at(" + id_name + " id, uint32_t inner_index) const noexcept {\n";
						output += "\t\t\treturn dcon::get(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], inner_index);\n";
						output += "\t\t}\n";

						output += "\t\tuint32_t " + o.name + "_get_" + p.name + "_capacity(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn dcon::get_capacity(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\n";
						output += "\t\t}\n";

						output += "\t\tuint32_t " + o.name + "_get_" + p.name + "_size(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn dcon::get_size(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\n";
						output += "\t\t}\n";

						output += "\t\tbool " + o.name + "_" + p.name + "_contains(" + id_name + " id, " + p.data_type + " obj) const noexcept {\n";
						output += "\t\t\treturn dcon::contains_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\n";
						output += "\t\t}\n";
					}
					if(!p.hook_set) {
						output += "\t\tvoid " + o.name + "_" + p.name + "_push_back(" + id_name + " id, " + p.data_type + " obj) noexcept {\n";
						output += "\t\t\treturn dcon::push_back(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\n";
						output += "\t\t}\n";

						output += "\t\tvoid " + o.name + "_" + p.name + "_pop_back(" + id_name + " id) noexcept {\n";
						output += "\t\t\treturn dcon::pop_back(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\n";
						output += "\t\t}\n";

						output += "\t\tvoid " + o.name + "_" + p.name + "_add_unique(" + id_name + " id, " + p.data_type + " obj) noexcept {\n";
						output += "\t\t\treturn dcon::add_unique_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\n";
						output += "\t\t}\n";

						output += "\t\tvoid " + o.name + "_" + p.name + "_remove_unique(" + id_name + " id, " + p.data_type + " obj) noexcept {\n";
						output += "\t\t\treturn dcon::remove_unique_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\n";
						output += "\t\t}\n";
					}
				} else if(is_vectorizable_type(parsed_file, p.data_type)) {
					if(!p.hook_get) {
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + " const& " + o.name + "_get_" + p.name + "(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& " + o.name + "_get_" + p.name + "(" + id_name + " id) noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> " + o.name + "_get_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
						output += "\t\t\treturn ve::load(id, " + o.name + ".m_" + p.name + ".vptr());\n";
						output += "\t\t}\n";
					}
					if(!p.hook_set) {
						output += "\t\tDCON_RELEASE_INLINE void " + o.name + "_set_" + p.name + "(" + id_name + " id, " + p.data_type + " value) noexcept {\n";
						output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";

						output += "\t\tDCON_RELEASE_INLINE " "void " + o.name + "_set_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
							"ve::value_to_vector_type<" + p.data_type + "> values) noexcept {\n";
						output += "\t\t\tve::store(id, " + o.name + ".m_" + p.name + ".vptr(), values);\n";
						output += "\t\t}\n";
					}
				} else { // nonvectorizable data type w/o special handling
					if(!p.hook_get) {
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + " const& " + o.name + "_get_" + p.name + "(" + id_name + " id) const noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";
						output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& " + o.name + "_get_" + p.name + "(" + id_name + " id) noexcept {\n";
						output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\n";
						output += "\t\t}\n";
					}
					if(!p.hook_set) {
						output += "\t\tDCON_RELEASE_INLINE void " + o.name + "_set_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value) noexcept {\n";
						output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\n";
						output += "\t\t}\n";
					}
				}
			} // end loop over each property

			output += "\n";

			// creation / deletion / move hook routines
			if(o.hook_create) {
				output += "\t\tvoid on_create_" + o.name + "(" + id_name + " id);\n";
			}
			if(o.hook_delete) {
				output += "\t\tvoid on_delete_" + o.name + "(" + id_name + " id);\n";
			}
			if(o.hook_move) {
				output += "\t\tvoid on_move_" + o.name + "(" + id_name + " new_id," + id_name + " old_id);\n";
			}

			output += "\t\tuint32_t " + o.name + "_size() const noexcept { return " + o.name + ".size_used; }\n\n";
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
					const std::string id_name = i.type_name + "_id";
					const std::string con_tags_type = i.related_to->is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

					// getter in relationship

					output += "\t\tDCON_RELEASE_INLINE " + id_name + " " + r.name + "_get_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\n";
					output += "\t\t\treturn id;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
					output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
					output += "\t\t\t\tresult.set(uint32_t(i), id[i]);\n";
					output += "\t\t\treturn result;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
					output += "\t\t\tfor(uint32_t i = 0; i < id.subcount; ++i)\n";
					output += "\t\t\t\tresult.set(i, id[i]);\n";
					output += "\t\t\treturn result;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn id;\n";
					output += "\t\t}\n";

					// setter in relationship

					output += "\t\tvoid " + r.name + "_set_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\n";
					output += "\t\t\tif(value) {\n";
					output += "\t\t\t\tdelete_" + r.name + "(value);\n";
					output += "\t\t\t\tinternal_move_relationship_" + r.name + "(id, value);\n";
					output += "\t\t\t} else {\n";
					output += "\t\t\t\tdelete_" + r.name + "(id);\n";
					output += "\t\t\t}\n";
					output += "\t\t}\n";

					// getter in related object

					output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(" + id_name + " id) const noexcept {\n";
					output += "\t\t\treturn id;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
					output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
					output += "\t\t\t\tresult.set(uint32_t(i), id[i]);\n";
					output += "\t\t\treturn result;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
					output += "\t\t\tfor(uint32_t i = 0; i < id.subcount; ++i)\n";
					output += "\t\t\t\tresult.set(i, id[i]);\n";
					output += "\t\t\treturn result;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn id;\n";
					output += "\t\t}\n";

					// setter in related object

					output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\n";
					output += "\t\t\tif(bool(id))\n";
					output += "\t\t\t\tdelete_" + r.name + "(id);\n";
					output += "\t\t}\n";

					{
						bool is_only_of_type = true;
						for(auto ir : r.indexed_objects) {
							if(ir.type_name == i.type_name && ir.property_name != i.property_name)
								is_only_of_type = false;
						}

						if(is_only_of_type) { //make shortcut function names
							// getter in related object

							output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_" + r.name + "_from_" + i.type_name +
								"(" + id_name + " id) const noexcept {\n";
							output += "\t\t\treturn id;\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name +
								"(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\n";
							output += "\t\t\t\tresult.set(uint32_t(i), id[i]);\n";
							output += "\t\t\treturn result;\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name +
								"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\n";
							output += "\t\t\tfor(uint32_t i = 0; i < id.subcount; ++i)\n";
							output += "\t\t\t\tresult.set(i, id[i]);\n";
							output += "\t\t\treturn result;\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + 
								"(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\treturn id;\n";
							output += "\t\t}\n";

							// setter in related object

							output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" + r.name + "(" + id_name + " id) noexcept {\n";
							output += "\t\t\tif(bool(id))\n";
							output += "\t\t\t\tdelete_" + r.name + "(id);\n";
							output += "\t\t}\n";
						}
					}

				} else if(i.index == index_type::at_most_one) {
					// first: getter in the relationship itself

					const std::string id_name = i.type_name + "_id";
					const std::string con_tags_type = i.related_to->is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

					output += "\t\tDCON_RELEASE_INLINE " + id_name + " " + r.name + "_get_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\n";
					output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					// second: setter in the relationship itself

					output += "\t\tvoid " + r.name + "_set_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\n";
					output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value))\n";
					output += "\t\t\t\t" + r.name + ".m_link_back_" + i.property_name + ".vptr()[old_value].index()] = " + relation_id_name + "();\n";
					output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\n";
					output += "\t\t\tif(value) {\n";
					output += "\t\t\t\tif(" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()])\n";
					output += "\t\t\t\t\tdelete_" + r.name + "(" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]);\n";
					output += "\t\t\t\t" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()] = id;\n";
					output += "\t\t\t}\n";
					output += "\t\t}\n";

					// third: getter in the object related to

					output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(" + id_name + " id) const noexcept {\n";
					output += "\t\t\treturn " + r.name + ".m_link_back_" + i.property_name + ".vptr()[id.index()];\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + "_as_" + i.property_name +
						"(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					// fourth: setter in the object related to

					output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\n";
					output += "\t\t\tif(auto id = " + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]; bool(id))\n";
					output += "\t\t\t\tdelete_" + r.name + "(id);\n";
					output += "\t\t}\n";

					{
						bool is_only_of_type = true;
						for(auto ir : r.indexed_objects) {
							if(ir.type_name == i.type_name && ir.property_name != i.property_name)
								is_only_of_type = false;
						}

						if(is_only_of_type) { //make shortcut function names
							output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_" + r.name + "_from_" + i.type_name +
								"(" + id_name + " id) const noexcept {\n";
							output += "\t\t\treturn " + r.name + ".m_link_back_" + i.property_name + ".vptr()[id.index()];\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + 
								"(" + con_tags_type + "<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name + 
								"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
							output += "\t\t}\n";

							output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_" + r.name + "_from_" + i.type_name +
								"(ve::tagged_vector<" + id_name + "> id) const noexcept {\n";
							output += "\t\t\treturn ve::load(id, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\n";
							output += "\t\t}\n";

							// fourth: setter in the object related to

							output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" + r.name + "(" + id_name + " id) noexcept {\n";
							output += "\t\t\tif(auto id = " + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]; bool(id))\n";
							output += "\t\t\t\tdelete_" + r.name + "(id);\n";
							output += "\t\t}\n";
						}
					}

				} else if(i.index == index_type::many) {
					// first: getter in the relationship itself

					const std::string id_name = i.type_name + "_id";
					const std::string con_tags_type = i.related_to->is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

					output += "\t\tDCON_RELEASE_INLINE " + id_name + " " + r.name + "_get_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\n";
					output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					// second: setter in the relationship itself

					output += "\t\tvoid " + r.name + "_set_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\n";

					if(i.ltype == list_type::list) {
						output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\n";
						output += "\t\t\t\tif(auto old_left = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left; bool(old_left)) {\n";
						output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[old_left.index()].right = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right;\n";
						output += "\t\t\t\t} else {\n";
						output += "\t\t\t\t\t" + r.name + ".m_head_back_" + i.property_name + ".vptr()[old_value.index()] = m_link_" + i.property_name + ".vptr()[id.index()].right;\n";
						output += "\t\t\t\t}\n";
						output += "\t\t\t\tif(auto old_right = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right; bool(old_right))\n";
						output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[old_right.index()].left = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left;\n";
						output += "\t\t\t\t}\n";
						output += "\t\t\t}\n";
						output += "\t\t\tif(value) {\n";
						output += "\t\t\t\tif(auto existing_list = " + r.name + ".m_head_back_" + i.property_name + ".vptr()[value.index()]]; bool(existing_list)) {\n";
						output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = existing_list;\n";
						output += "\t\t\t\t\tif(auto r = " + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right; bool(r)) {\n";
						output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = r;\n";
						output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[r.index()].left = id;\n";
						output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right = id;\n";
						output += "\t\t\t\t\t} else {\n";
						output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name + "();\n";
						output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right = id;\n";
						output += "\t\t\t\t\t}\n";
						output += "\t\t\t\t} else {\n";
						output += "\t\t\t\t\t" + r.name + ".m_head_back_" + i.property_name + ".vptr()[value.index()]] = id;\n";
						output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name + "();\n";
						output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = " + relation_id_name + "();\n";
						output += "\t\t\t\t}\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name + "();\n";
						output += "\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = " + relation_id_name + "();\n";
						output += "\t\t\t}\n";
						output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\n";
					} else if(i.ltype == list_type::array) {
						output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\n";
						output += "\t\t\t\tauto vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[old_value.index()];\n";
						output += "\t\t\t\tdcon::remove_unique_item(" + r.name + "." + i.property_name + "_storage, vref, id)\n";
						output += "\t\t\t}\n";
						output += "\t\t\tif(value)\n";
						output += "\t\t\t\tdcon::push_back(" + r.name + "." + i.property_name + "_storage, " + r.name + ".m_array_" + i.property_name + ".vptr()[value.index()], id);\n";
						output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\n";
					} else if(i.ltype == list_type::std_vector) {
						output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\n";
						output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[old_value.index()];\n";
						output += "\t\t\t\tif(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {\n";
						output += "\t\t\t\t\t*it = vref.back();\n";
						output += "\t\t\t\t\tvref.pop_back();\n";
						output += "\t\t\t\t}\n";
						output += "\t\t\t}\n";
						output += "\t\t\tif(value)\n";
						output += "\t\t\t\t" + r.name + ".m_array_" + i.property_name + ".vptr()[value.index()].push_back(id);\n";
						output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\n";
					}

					output += "\t\t}\n";

					// third: getter in the object related to

					output += "\t\ttemplate<typename T>\n";
					output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_for_each_" + r.name + "_as_" + i.property_name + "("
						+ id_name + " id, T&& func) const {\n";

					if(i.ltype == list_type::list) {
						output += "\t\t\tif(bool(id)) {\n";
						output += "\t\t\t\tfor(auto list_pos = " + r.name + ".m_head_back_" + i.property_name + ".vptr()[id.index()]; "
							+ "bool(list_pos); list_pos = " + r.name + ".m_link_" + i.property_name + ".vptr()[list_pos.index()].right) {\n";
						output += "\t\t\t\t\tfunc(list_pos);";
						output += "\t\t\t\t}\n";
						output += "\t\t\t}\n";

					} else if(i.ltype == list_type::array) {
						output += "\t\t\tif(bool(id)) {\n";
						output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
							+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\n";
						output += "\t\t\t\tstd::for_each(vrange.first, vrange.second, func);\n";
						output += "\t\t\t}\n";
					} else if(i.ltype == list_type::std_vector) {
						output += "\t\t\tif(bool(id)) {\n";
						output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\n";
						output += "\t\t\t\tstd::for_each(vref.begin(), vref.end(), func);\n";
						output += "\t\t\t}\n";
					}
					output += "\t\t}\n";


					if(i.ltype == list_type::array) {
						output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
							+ i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) const {\n";
						output += "\t\t\tif(bool(id)) {\n";
						output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
							+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\n";
						output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(vrange.first, vrange.second);\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\n";
						output += "\t\t\t}\n";
						output += "\t\t}\n";
					} else if(i.ltype == list_type::std_vector) {
						output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
							+ i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) const {\n";
						output += "\t\t\tif(bool(id)) {\n";
						output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\n";
						output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name
							+ " const*>(&(*vref.begin()), &(*vref.end()));\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\n";
						output += "\t\t\t}\n";
						output += "\t\t}\n";
					}

					// fourth: setter in the object related to

					output += "\t\tvoid " + i.type_name + "_remove_all_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\n";
					if(i.ltype == list_type::array || i.ltype == list_type::std_vector) {
						output += "\t\t\tauto rng = " + i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(id);\n";
						output += "\t\t\tstd::vector<" + relation_id_name + "> temp(rng.first, rng.second);\n";
						output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\n";
					} else {
						output += "\t\t\tstd::vector<" + relation_id_name + "> temp;\n";
						output += "\t\t\t" + i.type_name + "_for_each_" + r.name + "_as_" + i.property_name +
							"(id, [&](" + relation_id_name + " j) { temp.push_back(j); });\n";
						output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\n";
					}
					output += "\t\t}\n";

					{
						bool is_only_of_type = true;
						for(auto ir : r.indexed_objects) {
							if(ir.type_name == i.type_name && ir.property_name != i.property_name)
								is_only_of_type = false;
						}
						if(is_only_of_type) { // shortcut functions
							// third: getter in the object related to

							output += "\t\ttemplate<typename T>\n";
							output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_for_each_" + r.name + "("
								+ id_name + " id, T&& func) const {\n";

							if(i.ltype == list_type::list) {
								output += "\t\t\tif(bool(id)) {\n";
								output += "\t\t\t\tfor(auto list_pos = " + r.name + ".m_head_back_" + i.property_name + ".vptr()[id.index()]; "
									+ "bool(list_pos); list_pos = " + r.name + ".m_link_" + i.property_name + ".vptr()[list_pos.index()].right) {\n";
								output += "\t\t\t\t\tfunc(list_pos);";
								output += "\t\t\t\t}\n";
								output += "\t\t\t}\n";

							} else if(i.ltype == list_type::array) {
								output += "\t\t\tif(bool(id)) {\n";
								output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
									+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\n";
								output += "\t\t\t\tstd::for_each(vrange.first, vrange.second, func);\n";
								output += "\t\t\t}\n";
							} else if(i.ltype == list_type::std_vector) {
								output += "\t\t\tif(bool(id)) {\n";
								output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\n";
								output += "\t\t\t\tstd::for_each(vref.begin(), vref.end(), func);\n";
								output += "\t\t\t}\n";
							}
							output += "\t\t}\n";


							if(i.ltype == list_type::array) {
								output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
									+ i.type_name + "_range_of_" + r.name + "(" + id_name + " id) const {\n";
								output += "\t\t\tif(bool(id)) {\n";
								output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
									+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\n";
								output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(vrange.first, vrange.second);\n";
								output += "\t\t\t} else {\n";
								output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\n";
								output += "\t\t\t}\n";
								output += "\t\t}\n";
							} else if(i.ltype == list_type::std_vector) {
								output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
									+ i.type_name + "_range_of_" + r.name + "(" + id_name + " id) const {\n";
								output += "\t\t\tif(bool(id)) {\n";
								output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\n";
								output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name
									+ " const*>(&(*vref.begin()), &(*vref.end()));\n";
								output += "\t\t\t} else {\n";
								output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\n";
								output += "\t\t\t}\n";
								output += "\t\t}\n";
							}

							// fourth: setter in the object related to

							output += "\t\tvoid " + i.type_name + "_remove_all_" + r.name + "(" + id_name + " id) noexcept {\n";
							if(i.ltype == list_type::array || i.ltype == list_type::std_vector) {
								output += "\t\t\tauto rng = " + i.type_name + "_range_of_" + r.name + "(id);\n";
								output += "\t\t\tstd::vector<" + relation_id_name + "> temp(rng.first, rng.second);\n";
								output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\n";
							} else {
								output += "\t\t\tstd::vector<" + relation_id_name + "> temp;\n";
								output += "\t\t\t" + i.type_name + "_for_each_" + r.name +
									"(id, [&](" + relation_id_name + " j) { temp.push_back(j); });\n";
								output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\n";
							}
							output += "\t\t}\n";
						} //end shortcut functions in relationship
					}

				} else if(i.index == index_type::none) {
					// first: getter in the relationship itself

					const std::string id_name = i.type_name + "_id";

					output += "\t\tDCON_RELEASE_INLINE " + id_name + " " + r.name + "_get_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\n";
					output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> " + r.name + "_get_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept {\n";
					output += "\t\t\treturn ve::load(id, " + r.name + ".m_" + i.property_name + ".vptr());\n";
					output += "\t\t}\n";

					// second: setter in the relationship itself

					output += "\t\tDCON_RELEASE_INLINE void " + r.name + "_set_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\n";
					output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE " "void " + r.name + "_set_" + i.property_name + "(" + relation_con_tags_type + "<" + id_name + "> id, "
						"ve::tagged_vector<" + id_name + "> values) noexcept {\n";
					output += "\t\t\tve::store(id, " + r.name + ".m_" + i.property_name + ".vptr(), values);\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE " "void " + r.name + "_set_" + i.property_name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
						"ve::tagged_vector<" + id_name + "> values) noexcept {\n";
					output += "\t\t\tve::store(id, " + r.name + ".m_" + i.property_name + ".vptr(), values);\n";
					output += "\t\t}\n";

					output += "\t\tDCON_RELEASE_INLINE " "void " + r.name + "_set_" + i.property_name + "(ve::tagged_vector<" + id_name + "> id, "
						"ve::tagged_vector<" + id_name + "> values) noexcept {\n";
					output += "\t\t\tve::store(id, " + r.name + ".m_" + i.property_name + ".vptr(), values);\n";
					output += "\t\t}\n";
				}// end -- creation of property references getters / setters

			} //end of loop creating individual property getters / setters
		} // end creating relationship getters / setters

		output += "\n";

		// creation / deletion reoutines
		for(auto& co : parsed_file.relationship_objects) {
			const std::string id_name = co.name + "_id";

			if(!co.is_relationship) {
				if(co.store_type == storage_type::contiguous || co.store_type == storage_type::compactable) {

					// pop_back
					output += "\t\tvoid " + co.name + "_pop_back() {\n";
					output += "\t\t\tif(" + co.name + ".size_used > 0) {\n";

					output += "\t\t\t\t" + id_name + " id_removed(" + co.name + ".size_used - 1);\n";
					if(co.hook_delete)
						output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

					for(auto& cr : co.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\n";
							output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used - 1;\n";
							if(co.is_expandable) {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_special_vector) {
										output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\n";
									} else if(rp.is_bitfield) {
										output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", id_removed.index(), false);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";
									}
									if(!rp.is_bitfield && !rp.is_derived) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\n";
									}
								}
								for(auto& ri : cr.rel_ptr->indexed_objects) {
									if(ri.related_to == cr.rel_ptr->primary_key) {
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.pop_back();\n";
									}
									if(ri.ltype == list_type::list && ri.index == index_type::many) {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.pop_back();\n";
									}
								}
							} else {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} else if(rp.is_special_vector) {
										output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\n";
									} else if(rp.is_bitfield) {
										output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + ".vptr(), id_removed.index(), false);\n";
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + rp.data_type + "{};\n";
									}
								}
							}
						} else if(cr.indexed_as == index_type::at_most_one) {
							output += "\t\t\t\t" + co.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\n";
							if(co.is_expandable) {
								output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.pop_back();\n";
							}
						} else if(cr.indexed_as == index_type::many) {
							output += "\t\t\t\t" + co.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\n";
							if(co.is_expandable) {
								if(cr.listed_as == list_type::list) {
									output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.pop_back();\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
										+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\n";
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\n";
								} else if(cr.listed_as == list_type::std_vector) {
									output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\n";
								}
							}
						}
					}
					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
							if(co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";
						} else {
							if(!co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}

						if(co.is_expandable && !cp.is_bitfield && !cp.is_derived) {
							output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
						}
					}
					output += "\t\t\t\t--" + co.name + ".size_used;\n";
					output += "\t\t\t}\n";
					output += "\t\t}\n";


					//resize
					output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\n";
					if(!co.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(co.size) + ") std::abort();\n";
					output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting

					
					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ co.name + ".m" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!co.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!co.is_expandable) {
								if(cp.is_object) {
									output += "\t\t\t\tstd::std::destroy_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding
					output += "\t\t\t}\n";

					//both
					if(co.is_expandable) {
						for(auto& cr : co.relationships_involved_in) {
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

						for(auto& cr : co.relationships_involved_in) {
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
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					} else {
						for(auto& cr : co.relationships_involved_in) {
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

						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t" + cr.relation_name + "_resize(new_size);\n";
							}
						}
					}
					output += "\t\t\t" + co.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					if(co.store_type == storage_type::compactable) {
						//delete
						output += "\t\tvoid delete_" + co.name + "(" + id_name + " id) {\n";
						output += "\t\t\t\t" + id_name + " id_removed = id;\n";
						output += "\t\t\t\t" + id_name + " last_id(" + co.name + ".size_used - 1);\n";

						output += "\t\t\t\tif(id_removed == last_id) { " + co.name + ".pop_back(); return; }\n";

						if(co.hook_delete)
							output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\n";
								output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used - 1;\n";

								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} else if(rp.is_special_vector) {
										output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()];\n";
										if(co.is_expandable)
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\n";
										else
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
									} else if(rp.is_bitfield) {
										output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", id_removed.index(), "
											+ "dcon::bit_vector_get(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", last_id.index()));\n";
										output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", last_id.index(), false);\n";
										if(co.is_expandable)
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = std::move("
											+ cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()]);\n";
										if(co.is_expandable)
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\n";
										else
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()] = " + rp.data_type + "{};\n";
									}
								}
								for(auto& ri : cr.rel_ptr->indexed_objects) {
									if(ri.related_to == cr.rel_ptr->primary_key) {
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_" + ri.property_name + ".vptr()[last_id.index()];\n";
										if(co.is_expandable)
											output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.pop_back();\n";
										else
											output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".vptr()[last_id.index()] = " + ri.property_name + "_id();\n";
									}
									if(ri.ltype == list_type::list && ri.index == index_type::many) {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[last_id.index()];\n";
										if(co.is_expandable)
											output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.pop_back();\n";
										else
											output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[last_id.index()] = " + ri.property_name + "_id_pair();\n";
									}
								}
							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\t\t" + co.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\n";

								// renumber last_item id
								output += "\t\t\t\tif(auto bk = " + cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[last_id.index()]; bool(bk)) {\n";
								output += "\t\t\t\t\t" + cr.relation_name + ".m_" + cr.property_name + ".vptr()[bk.index()] = id_removed;\n";
								output += "\t\t\t\t}\n";

								output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
									+ cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[last_id.index()];\n";
								if(co.is_expandable) {
									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.pop_back();\n";
								} else {
									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[last_id.index()] = " + cr.relation_name + "_id();\n";
								}
							} else if(cr.indexed_as == index_type::many) {
								output += "\t\t\t\t" + co.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\n";

								// renumber last_item id
								output += "\t\t\t\t" + co.name + "_for_each_" + cr.relation_name + "_as_" + cr.property_name
									+ "(last_id, [t = this](" + cr.relation_name + "_id i){ t->"
									+ cr.relation_name + "." + cr.property_name + ".vptr()[i.index()] = id_removed; });\n";

								if(co.is_expandable) {
									if(cr.listed_as == list_type::list) {
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
											+ cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()];\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.pop_back();\n";
									} else if(cr.listed_as == list_type::array) {
										output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = "
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()];\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\n";
									} else if(cr.listed_as == list_type::std_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = std::move("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()]);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\n";
									}
								} else {
									if(cr.listed_as == list_type::list) {
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
											+ cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()];\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()] = "
											+ cr.relation_name + "_id_pair();\n";
									} else if(cr.listed_as == list_type::array) {
										output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = "
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()];\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
									} else if(cr.listed_as == list_type::std_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = std::move("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()]);\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()].empty();\n";
									}
								}
							}
						}
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = "
									+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()];\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[last_id.index()] = "
									+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), "
									+ "dcon::bit_vector_get(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index()));\n";
								output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index(), false);\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";

							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = std::move("
									+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()]);\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[last_id.index()] = " + cp.data_type + "{};\n";
							}
						}
						output += "\t\t\t\t--" + co.name + ".size_used;\n";
						if(co.hook_move)
							output += "\t\t\t\ton_move_" + co.name + "(id_removed, last_id);\n";

						output += "\t\t\t}\n";

						output += "\t\t}\n";
					} // end compactible delete

					//create
					output += "\t\t" + id_name + " create_" + co.name + "() {\n";

					if(!co.is_expandable)
						output += "\t\t\tif(" + co.name + ".size_used >= " + std::to_string(co.size) + ") std::abort();\n";

					output += "\t\t\t" + id_name + " new_id(" + co.name + ".size_used);\n";

					for(auto& cr : co.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used + 1;\n";
							if(co.is_expandable) {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} if(rp.is_bitfield) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 8) / 8);\n";
									} else if(rp.is_special_vector) {
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
							if(co.is_expandable) {
								output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.emplace_back();\n";
							}
						} else if(cr.indexed_as == index_type::many) {
							if(co.is_expandable) {
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
					if(co.is_expandable) {
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_bitfield) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 8) / 8);\n";
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
					}

					output += "\t\t\t++" + co.name + ".size_used;\n";
					if(co.hook_create)
						output += "\t\t\t\ton_create_" + co.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + co.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(co.store_type == storage_type::erasable) {

					// delete
					output += "\t\tvoid delete_" + co.name + "(" + id_name + " id_removed) {\n";

					output += "\t\t\tif(is_valid_" + co.name + "(id_removed)) {\n";
					if(co.hook_delete)
						output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

					output += "\t\t\t\t" + co.name + ".m__index.vptr()[id_removed.index()] = " + co.name + ".first_free;\n"; // FN
					output += "\t\t\t\t" + co.name + ".first_free = id_removed;\n";
					output += "\t\t\t\tif(" + co.name + ".size_used - 1 == id_removed.index()) {\n"; // OIF
					output += "\t\t\t\t\tfor( ; " + co.name + ".size_used > 0 && "
						+ co.name + ".m__index.vptr()[" + co.name + ".size_used - 1] != "
						+ co.name + "_id(" + co.name + "_id::value_base_t(" + co.name + ".size_used - 1)) ;"
						+ " --" + co.name + ".size_used) ; \\ intentionally empty loop\n";
					output += "\t\t\t\t}\n"; // OIF

					for(auto& cr : co.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\n";
							output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used;\n";

							for(auto& rp : cr.rel_ptr->properties) {
								if(rp.is_derived) {
								} else if(rp.is_special_vector) {
									output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\n";
								} else if(rp.is_bitfield) {
									output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + ".vptr(), id_removed.index(), false);\n";
								} else {
									output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + rp.data_type + "{};\n";
								}
							}

						} else if(cr.indexed_as == index_type::at_most_one) {
							output += "\t\t\t\t" + co.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\n";

						} else if(cr.indexed_as == index_type::many) {
							output += "\t\t\t\t" + co.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\n";
						}
					}
					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
						} else {
							output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}
					}
					output += "\t\t\t}\n";
					output += "\t\t}\n"; // end delete

					//create
					output += "\t\t" + id_name + " create_" + co.name + "() {\n";
					if(!co.is_expandable) {
						output += "\t\t\tif(!bool(" + co.name + ".first_free )) std::abort();\n";
						output += "\t\t\t" + id_name + " new_id =" + co.name + ".first_free;\n";
						output += "\t\t\tfirst_free = " + co.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t" + co.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
					} else {
						output += "\t\t\t" + id_name + " new_id;\n";
						output += "\t\t\tconst bool expanded = !bool(" + co.name + ".first_free );\n";
						output += "\t\t\tif(expanded) {\n";
						output += "\t\t\t\tnew_id = " + id_name + "(" + id_name + "::value_base_t(" + co.name + ".size_used));\n";
						output += "\t\t\t\t" + co.name + ".m__index.values.push_back(new_id);\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\tnew_id = " + co.name + ".first_free;\n";
						output += "\t\t\t\tfirst_free = " + co.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t\t" + co.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
						output += "\t\t\t}\n";

					}
					output += "\t\t\t" + co.name + ".size_used = std::max(" + co.name + ".size_used, uint32_t(new_id.index() + 1));\n";

					for(auto& cr : co.relationships_involved_in) {
						if(cr.as_primary_key) {
							output += "\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used;\n";
						}
					}

					if(co.is_expandable) {
						output += "\t\t\tif(expanded) {\n;";
						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								for(auto& rp : cr.rel_ptr->properties) {
									if(rp.is_derived) {
									} if(rp.is_bitfield) {
										output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 7) / 8);\n";
									} else if(rp.is_special_vector) {
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

						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_bitfield) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 7) / 8);\n";
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
						output += "\t\t\t}\n;"; // end expanded if
					}

					if(co.hook_create)
						output += "\t\t\ton_create_" + co.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					//resize
					output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\n";

					if(!co.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(co.size) + ") std::abort();\n";

					output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting


					output += "\t\t\t\t" + co.name + ".first_free = " + co.name + "_id();\n";
					if(co.is_expandable) {
						output += "\t\t\t\t" + co.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(co.size) + ");\n";
						output += "\t\t\t\tfor(; i >= new_size; --i) {\n";
						output += "\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
						output += "\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
						output += "\t\t\t\t}\n\n";
					}

					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + co.name + ".m__index.vptr()[i] != " + co.name + "_id(" + size_to_tag_type(co.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";


					
					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ co.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!co.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!co.is_expandable) {
								if(cp.is_object) {
									output += "\t\t\t\tstd::std::destroy_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding

					output += "\t\t\t\t" + co.name + ".first_free = " + co.name + "_id();\n";
					if(co.is_expandable) {
						output += "\t\t\t\t" + co.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(co.size) + ");\n";
					}

					output += "\t\t\t\tfor(; i >= old_size; --i) {\n";
					output += "\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t}\n\n";


					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + co.name + ".m__index.vptr()[i] != " + co.name + "_id(" + size_to_tag_type(co.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					output += "\t\t\t}\n";

					//both
					if(co.is_expandable) {
						for(auto& cr : co.relationships_involved_in) {
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

						for(auto& cr : co.relationships_involved_in) {
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
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					} else {
						for(auto& cr : co.relationships_involved_in) {
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

						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t" + cr.relation_name + "_resize(new_size);\n";
							}
						}
					}
					output += "\t\t\t" + co.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + co.name + ".size_used && "
						+ co.name + ".m__index.vptr()[id.index()] == id;\n";
					output += "\t\t}\n";
				}
			} else if(co.primary_key) { // primary key relationship
				//resize
				output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\n";
				if(!co.is_expandable)
					output += "\t\t\tif(new_size > " + std::to_string(co.size) + ") std::abort();\n";
				output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\n";
				output += "\t\t\tif(new_size < old_size) {\n"; // contracting

				

				for(auto& cp : co.properties) {
					if(cp.is_derived) {
					} else if(cp.is_special_vector) {
						output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
							+ co.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
							+ cp.name + "_storage.release(i); });\n";

						output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
					} else if(cp.is_bitfield) {
						output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
						output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\n";
						if(!co.is_expandable)
							output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
					} else {
						if(!co.is_expandable) {
							if(cp.is_object) {
								output += "\t\t\t\tstd::std::destroy_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								output += "\t\t\t\tstd::uninitialized_default_construct_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
							} else {
								output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
							}
						}
					}
				}

				output += "\t\t\t} else {\n"; //expanding
				output += "\t\t\t}\n";

				//both
				if(co.is_expandable) {
					for(auto& io : co.indexed_objects) {
						output += "\t\t\tstd::fill_n(" + co.name + ".m_" + io.property_name + ".vptr(), new_size, " + io.type_name + "_id());\n";
						if(io.ltype == list_type::list)
							output += "\t\t\tstd::fill_n(" + co.name + ".m_link_" + io.property_name + ".vptr(), new_size, " + io.type_name + "_id_pair());\n";

					}

					for(auto& io : co.indexed_objects) {
						output += "\t\t\t" + co.name + ".m_" + io.property_name + ".values.resize(1 + new_size);\n";
						if(io.ltype == list_type::list)
							output += "\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.resize(1 + new_size);\n";
					}

					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
						} else {
							output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
						}
					}
				} else {
					for(auto& io : co.indexed_objects) {
						if(io.related_to != co.primary_key) {
							output += "\t\t\tstd::fill_n(" + co.name + ".m_" + io.property_name + ".vptr(), old_size, " + io.type_name + "_id());\n";
							if(io.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + co.name + ".m_link_" + io.property_name + ".vptr(), old_size, " + io.type_name + "_id_pair());\n";
						}

					}
				}
				output += "\t\t\t" + co.name + ".size_used = new_size;\n";
				output += "\t\t}\n"; // end resize

				output += "\t\tvoid delete_" + co.name + "(" + id_name + " id_removed) {\n";
				if(co.hook_delete)
					output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(id_removed, " + io.type_name + "_id());\n";
					}
				}
				output += "\t\t}\n"; // end delete

				output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\n";
				output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + co.name + ".size_used && " + 
					"is_valid_" + co.primary_key->name + "(id) && (";
				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						output += "bool(" + co.name + ".m_" + io.property_name + ".vptr()[id.index()]) || ";
					}
				}
				output += "false);\n";
				output += "\t\t}\n"; // end is_valid

				output += "\t\tprivate:\n";
				output += "\t\tvoid internal_move_relationship_" + co.name + "(" + id_name + " old_id, " + id_name + " new_id) {\n";

				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".vptr()[new_id.index()] = "
							+ co.name + ".m_" + io.property_name + ".vptr()[old_id.index()];\n";
						output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".vptr()[old_id.index()] = " + io.type_name + "_id();\n";
						
						if(io.index == index_type::at_most_one) {
							output += "\t\t\t\tif(auto tmp = " + co.name + ".m_" + io.property_name + ".vptr()[new_id.index()]; bool(tmp))\n";
							output += "\t\t\t\t\t" + co.name + ".m_link_back_" + io.property_name + ".vptr()[tmp.index()] = new_id;\n";
						} else if(io.index == index_type::many && io.ltype == list_type::list) {
							output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[new_id.index()] = "
								+ co.name + ".m_link_" + io.property_name + ".vptr()[old_id.index()];\n";
							output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[old_id.index()] = " + io.type_name + "_id_pair();\n";

							output += "\t\t\t\t{auto tmp = " + co.name + ".m_link_" + io.property_name + ".vptr()[new_id.index()];\n";
							output += "\t\t\t\t\tif(bool(tmp.left)) {\n";
							output += "\t\t\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[tmp.left.index()].right = new_id;\n";
							output += "\t\t\t\t\t} else {\n";
							output += "\t\t\t\t\t\rfor(auto lpos = tmp; bool(lpos); lpos = " + co.name + ".m_link_" + io.property_name + ".vptr()[lpos.index()].right)\n";
							output += "\t\t\t\t\t\t" + co.name + ".m_head_back_" + io.property_name + ".vptr()["
								+ co.name + ".m_" + io.property_name + ".vptr()[lpos.index()].index()] = new_id;\n";
							output += "\t\t\t\t\t}\n";
							output += "\t\t\t\t\tif(bool(tmp.right)) " + co.name + ".m_link_" + io.property_name + ".vptr()[tmp.right.index()].left = new_id;\n";
							output += "\t\t\t\t}\n";

							if(co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.pop_back();\n";
							else
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[last_id.index()] = " + io.type_name + "_id_pair();\n";
						}
					}
				}

				for(auto& cp : co.properties) {
					if(cp.is_derived) {
					} else if(cp.is_special_vector) {
						output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[new_id.index()] = "
							+ co.name + ".m_" + cp.name + ".vptr()[old_id.index()];\n";
						output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[old_id.index()] = "
							+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
					} else if(cp.is_bitfield) {
						output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), new_id.index(), "
							+ "dcon::bit_vector_get(" + co.name + ".m_" + cp.name + ".vptr(), old_id.index()));\n";
						output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), old_id.index(), false);\n";
					} else {
						output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[new_id.index()] = std::move("
							+ co.name + ".m_" + cp.name + ".vptr()[old_id.index()]);\n";
						output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[old_id.index()] = " + cp.data_type + "{};\n";
					}
				}
				if(co.hook_move)
					output += "\t\t\t\ton_move_" + co.name + "(new_id, old_id);\n";

				output += "\t\t}\n"; // end internal_move_relationship

				output += "\t\tpublic:\n";
				output += "\t\t" + id_name + " try_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";

				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						if(io.index == index_type::at_most_one) {
							output += "\t\t\tif(bool(" + io.property_name + "_p) && bool("
								+ co.name + ".m_link_" + io.property_name + ".vptr()[" + io.property_name + "_p.index()])) return " + id_name + "();\n";
						}
					} else {
						output += "\t\t\tif(is_valid_" + co.name + "(" + io.property_name + "_p)) return " + id_name + "();\n";
					}
				}

				output += "\t\t\t" + id_name + " new_id = ";
				for(auto& io : co.indexed_objects) {
					if(io.related_to == co.primary_key) {
						output += io.property_name;
					}
				}
				output += "_p;\n";

				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(new_id, " + io.property_name + "_p);\n";
					}
				}

				if(co.hook_create)
					output += "\t\t\t\ton_create_" + co.name + "(new_id);\n";
				output += "\t\t\treturn new_id;\n";
				output += "\t\t}\n"; // end try_create

				output += "\t\t" + id_name + " force_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";
				output += "\t\t\t" + id_name + " new_id = ";
				for(auto& io : co.indexed_objects) {
					if(io.related_to == co.primary_key) {
						output += io.property_name;
					}
				}
				output += "_p;\n";

				for(auto& io : co.indexed_objects) {
					if(io.related_to != co.primary_key) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(new_id, " + io.property_name + "_p);\n";
					}
				}

				if(co.hook_create)
					output += "\t\t\t\ton_create_" + co.name + "(new_id);\n";
				output += "\t\t\treturn new_id;\n";
				output += "\t\t}\n"; // end force_create
			} else { // non pk relationship
				if(co.store_type == storage_type::contiguous || co.store_type == storage_type::compactable) {

					// pop_back
					output += "\t\tvoid " + co.name + "_pop_back() {\n";
					output += "\t\t\tif(" + co.name + ".size_used > 0) {\n";

					output += "\t\t\t\t" + id_name + " id_removed(" + co.name + ".size_used - 1);\n";
					if(co.hook_delete)
						output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

					for(auto& io : co.indexed_objects) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(id_removed, " + io.type_name + "_id());\n";
						if(co.is_expandable) {
							output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".values.pop_back();\n";
							if(io.ltype == list_type::list)
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.pop_back();\n";
						}
					}

					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
							if(co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";
						} else {
							if(!co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}

						if(co.is_expandable && !cp.is_bitfield && !cp.is_derived) {
							output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
						}
					}

					output += "\t\t\t\t--" + co.name + ".size_used;\n";
					output += "\t\t\t}\n";
					output += "\t\t}\n";


					//resize
					output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\n";
					if(!co.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(co.size) + ") std::abort();\n";
					output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting

					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ co.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!co.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!co.is_expandable) {
								if(cp.is_object) {
									output += "\t\t\t\tstd::std::destroy_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding
					output += "\t\t\t}\n";

					//both
					if(co.is_expandable) {
						for(auto& io : co.indexed_objects) {
							output += "\t\t\tstd::fill_n(" + co.name + ".m_" + io.property_name + ".vptr(), new_size, " + io.type_name + "_id());\n";
							if(io.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + co.name + ".m_link_" + io.property_name + ".vptr(), new_size, " + io.type_name + "_id_pair());\n";

						}

						for(auto& io : co.indexed_objects) {
							output += "\t\t\t" + co.name + ".m_" + io.property_name + ".values.resize(1 + new_size);\n";
							if(io.ltype == list_type::list)
								output += "\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.resize(1 + new_size);\n";
						}

						
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					} else {
						for(auto& io : co.indexed_objects) {
							output += "\t\t\tstd::fill_n(" + co.name + ".m_" + io.property_name + ".vptr(), old_size, " + io.type_name + "_id());\n";
							if(io.ltype == list_type::list)
								output += "\t\t\tstd::fill_n(" + co.name + ".m_link_" + io.property_name + ".vptr(), old_size, " + io.type_name + "_id_pair());\n";

						}
					}
					output += "\t\t\t" + co.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					if(co.store_type == storage_type::compactable) {
						//delete
						output += "\t\tvoid delete_" + co.name + "(" + id_name + " id) {\n";
						output += "\t\t\t\t" + id_name + " id_removed = id;\n";
						output += "\t\t\t\t" + id_name + " last_id(" + co.name + ".size_used - 1);\n";

						output += "\t\t\t\tif(id_removed == last_id) { " + co.name + ".pop_back(); return; }\n";

						if(co.hook_delete)
							output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

						for(auto& io : co.indexed_objects) {
							output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(id_removed, " + io.type_name + "_id());\n";

							output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".vptr()[id_removed.index()] = "
								+ co.name + ".m_" + io.property_name + ".vptr()[last_id.index()];\n";
							if(co.is_expandable)
								output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".values.pop_back();\n";
							else
								output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".vptr()[last_id.index()] = " + io.type_name + "_id();\n";

							if(io.ltype == list_type::list) {
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[id_removed.index()] = "
									+ co.name + ".m_link_" + io.property_name + ".vptr()[last_id.index()];\n";
								output += "\t\t\t\t{ auto tmp = " + co.name + ".m_link_" + io.property_name + ".vptr()[id_removed.index()];\n";
								output += "\t\t\t\t\tif(bool(tmp.left)) {\n";
								output += "\t\t\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[tmp.left.index()].right = id_removed;\n";
								output += "\t\t\t\t\t} else {\n";
								output += "\t\t\t\t\t\rfor(auto lpos = tmp; bool(lpos); lpos = " + co.name + ".m_link_" + io.property_name + ".vptr()[lpos.index()].right)\n";
								output += "\t\t\t\t\t\t" + co.name + ".m_head_back_" + io.property_name + ".vptr()["
									+ co.name + ".m_" + io.property_name + ".vptr()[lpos.index()].index()] = id_removed;\n";
								output += "\t\t\t\t\t}\n";
								output += "\t\t\t\t\tif(bool(tmp.right)) " + co.name + ".m_link_" + io.property_name + ".vptr()[tmp.right.index()].left = id_removed;\n";
								output += "\t\t\t\t}\n";

								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".vptr()[last_id.index()] = " + io.type_name + "_id_pair();\n";
							}
						}


						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = "
									+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()];\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[last_id.index()] = "
									+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), "
									+ "dcon::bit_vector_get(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index()));\n";
								output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index(), false);\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\n";

							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = std::move("
									+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()]);\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\n";
								else
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[last_id.index()] = " + cp.data_type + "{};\n";
							}
						}
						output += "\t\t\t\t--" + co.name + ".size_used;\n";
						if(co.hook_move)
							output += "\t\t\t\ton_move_" + co.name + "(id_removed, last_id);\n";

						output += "\t\t\t}\n";

						output += "\t\t}\n";
					} // end compactible delete


					//try create
					output += "\t\t" + id_name + " try_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";
					// we can skip trying because this is not a relationship with a primary key: thus all are >= type
					output += "\t\t\treturn " + id_name + " force_create_" + co.name + "(" +
						([&]() {
						std::string result;
						for(auto& i : co.indexed_objects) {
							if(result.length() != 0)
								result += ", ";
							result += i.property_name + "_p";
						}
						return result;
					}())
						+ ");\n";
					output += "\t\t}\n";

					//force create
					output += "\t\t" + id_name + " force_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";
					if(!co.is_expandable)
						output += "\t\t\tif(" + co.name + ".size_used >= " + std::to_string(co.size) + ") std::abort();\n";

					output += "\t\t\t" + id_name + " new_id(" + co.name + ".size_used);\n";

					if(co.is_expandable) {
						for(auto& io : co.indexed_objects) {
							output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".values.emplace_back();\n";
							if(io.ltype == list_type::list) {
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.emplace_back();\n";
							}
						}
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_bitfield) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 8) / 8);\n";
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
					}

					for(auto& io : co.indexed_objects) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(new_id, " + io.property_name + "_p);\n";
					}

					output += "\t\t\t++" + co.name + ".size_used;\n";
					if(co.hook_create)
						output += "\t\t\t\ton_create_" + co.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + co.name + ".size_used;\n";
					output += "\t\t}\n";
				} else if(co.store_type == storage_type::erasable) {
					// delete
					output += "\t\tvoid delete_" + co.name + "(" + id_name + " id_removed) {\n";

					output += "\t\t\tif(is_valid_" + co.name + "(id_removed)) {\n";
					if(co.hook_delete)
						output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\n";

					output += "\t\t\t\t" + co.name + ".m__index.vptr()[id_removed.index()] = " + co.name + ".first_free;\n"; // FN
					output += "\t\t\t\t" + co.name + ".first_free = id_removed;\n";
					output += "\t\t\t\tif(" + co.name + ".size_used - 1 == id_removed.index()) {\n"; // OIF
					output += "\t\t\t\t\tfor( ; " + co.name + ".size_used > 0 && "
						+ co.name + ".m__index.vptr()[" + co.name + ".size_used - 1] != "
						+ co.name + "_id(" + co.name + "_id::value_base_t(" + co.name + ".size_used - 1)) ;"
						+ " --" + co.name + ".size_used) ; \\ intentionally empty loop\n";
					output += "\t\t\t\t}\n"; // OIF

					for(auto& io : co.indexed_objects) {
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name + "(id_removed, " + io.type_name + "_id());\n";
					}

					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\n";
						} else {
							output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\n";
						}
					}
					output += "\t\t\t}\n";
					output += "\t\t}\n"; // end delete

					//try create
					output += "\t\t" + id_name + " try_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";
					// we can skip trying because this is not a relationship with a primary key: thus all are >= type
					output += "\t\t\treturn " + id_name + " force_create_" + co.name + "(" +
						([&]() {
						std::string result;
						for(auto& i : co.indexed_objects) {
							if(result.length() != 0)
								result += ", ";
							result += i.property_name + "_p";
						}
						return result;
					}()) + ");\n";
					output += "\t\t}\n";

					//force create
					output += "\t\t" + id_name + " force_create_" + co.name + "(" + make_relationship_parameters(co) + ") {\n";

					if(!co.is_expandable) {
						output += "\t\t\tif(!bool(" + co.name + ".first_free )) std::abort();\n";
						output += "\t\t\t" + id_name + " new_id =" + co.name + ".first_free;\n";
						output += "\t\t\tfirst_free = " + co.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t" + co.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
					} else {
						output += "\t\t\t" + id_name + " new_id;\n";
						output += "\t\t\tconst bool expanded = !bool(" + co.name + ".first_free );\n";
						output += "\t\t\tif(expanded) {\n";
						output += "\t\t\t\tnew_id = " + id_name + "(" + id_name + "::value_base_t(" + co.name + ".size_used));\n";
						output += "\t\t\t\t" + co.name + ".m__index.values.push_back(new_id);\n";
						output += "\t\t\t} else {\n";
						output += "\t\t\t\tnew_id = " + co.name + ".first_free;\n";
						output += "\t\t\t\tfirst_free = " + co.name + ".m__index.vptr()[first_free.index()];\n";
						output += "\t\t\t\t" + co.name + ".m__index.vptr()[new_id.index()] = new_id;\n";
						output += "\t\t\t}\n";

					}
					output += "\t\t\t" + co.name + ".size_used = std::max(" + co.name + ".size_used, uint32_t(new_id.index() + 1));\n";


					if(co.is_expandable) {
						output += "\t\t\tif(expanded) {\n;";

						for(auto& io : co.indexed_objects) {
							output += "\t\t\t\t" + co.name + ".m_" + io.property_name + ".values.emplace_back();\n";
							if(io.ltype == list_type::list) {
								output += "\t\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.emplace_back();\n";
							}
						}

						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_bitfield) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 7) / 8);\n";
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.emplace_back();\n";
							}
						}
						output += "\t\t\t}\n;";
					}

					if(co.hook_create)
						output += "\t\t\ton_create_" + co.name + "(new_id);\n";
					output += "\t\t\treturn new_id;\n";
					output += "\t\t}\n"; // end create

					// resize
					output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\n";

					if(!co.is_expandable)
						output += "\t\t\tif(new_size > " + std::to_string(co.size) + ") std::abort();\n";

					output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\n";
					output += "\t\t\tif(new_size < old_size) {\n"; // contracting


					output += "\t\t\t\t" + co.name + ".first_free = " + co.name + "_id();\n";
					if(co.is_expandable) {
						output += "\t\t\t\t" + co.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(co.size) + ");\n";
						output += "\t\t\t\tfor(; i >= new_size; --i) {\n";
						output += "\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
						output += "\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
						output += "\t\t\t\t}\n\n";
					}

					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + co.name + ".m__index.vptr()[i] != " + co.name + "_id(" + size_to_tag_type(co.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					for(auto& io : co.indexed_objects) {
						output += "\t\t\t\tfor(int32_t j = int32_t(old_size); j >= new_size; --j) {\n";
						output += "\t\t\t\t" + co.name + "_set_" + io.property_name
							+ "(" + co.name + "_id(" + co.name + "::value_base_t(j)), " + io.type_name + "_id());\n";
					}


					for(auto& cp : co.properties) {
						if(cp.is_derived) {
						} else if(cp.is_special_vector) {
							output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
								+ co.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
								+ cp.name + "_storage.release(i); });\n";

							output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\n";
						} else if(cp.is_bitfield) {
							output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\n";
							output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\n";
							if(!co.is_expandable)
								output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\n";
						} else {
							if(!co.is_expandable) {
								if(cp.is_object) {
									output += "\t\t\t\tstd::std::destroy_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
									output += "\t\t\t\tstd::uninitialized_default_construct_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size);\n";
								} else {
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\n";
								}
							}
						}
					}

					output += "\t\t\t} else {\n"; //expanding

					output += "\t\t\t\t" + co.name + ".first_free = " + co.name + "_id();\n";
					if(co.is_expandable) {
						output += "\t\t\t\t" + co.name + ".m__index.values.resize(new_size + 1);\n";
						output += "\t\t\t\tint32_t i = int32_t(new_size);\n";
					} else {
						output += "\t\t\t\tint32_t i = int32_t(" + std::to_string(co.size) + ");\n";
					}

					output += "\t\t\t\tfor(; i >= old_size; --i) {\n";
					output += "\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t}\n\n";


					output += "\t\t\t\tfor(; i >= 0; --i) {\n";
					output += "\t\t\t\t\tif(" + co.name + ".m__index.vptr()[i] != " + co.name + "_id(" + size_to_tag_type(co.size) + "(i))) {\n";
					output += "\t\t\t\t\t\t" + co.name + ".m__index.vptr()[i] = " + co.name + ".first_free;\n";
					output += "\t\t\t\t\t\t" + co.name + ".first_free = " + co.name + "_id(" + size_to_tag_type(co.size) + "(i));\n";
					output += "\t\t\t\t\t}\n";
					output += "\t\t\t\t}\n\n";

					output += "\t\t\t}\n";

					//both
					if(co.is_expandable) {
						for(auto& io : co.indexed_objects) {
							output += "\t\t\t" + co.name + ".m_" + io.property_name + ".values.resize(1 + new_size);\n";
							if(io.ltype == list_type::list) {
								output += "\t\t\t" + co.name + ".m_link_" + io.property_name + ".values.resize(1 + new_size);\n";
							}
						}

						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\n";
							} else {
								output += "\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\n";
							}
						}
					}
					output += "\t\t\t" + co.name + ".size_used = new_size;\n";
					output += "\t\t}\n"; // end resize

					output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\n";
					output += "\t\t\treturn bool(id) && uint32_t(id.index()) < " + co.name + ".size_used && "
						+ co.name + ".m__index.vptr()[id.index()] == id;\n";
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

		for(auto& o : parsed_file.relationship_objects) {
			output += "\t\tve::vectorizable_buffer<float, " + o.name + "_id> " + o.name + "_make_vectorizable_float_buffer() const noexcept {\n";
			output += "\t\t\treturn ve::vectorizable_buffer<float, " + o.name + "_id>(" + o.name + ".size_used);\n";
			output += "\t\t}\n";
			output += "\t\tve::vectorizable_buffer<int32_t, " + o.name + "_id> " + o.name + "_make_vectorizable_int_buffer() const noexcept {\n";
			output += "\t\t\treturn ve::vectorizable_buffer<int32_t, " + o.name + "_id>(" + o.name + ".size_used);\n";
			output += "\t\t}\n";
			if(!o.is_expandable) {
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_serial_over_" + o.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_serial(" + o.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#ifndef VE_NO_TBB\n";
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_parallel_over_" + o.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_parallel_exact(" + o.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#endif\n";
			} else {
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_serial_over_" + o.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_serial_unaligned(" + o.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#ifndef VE_NO_TBB\n";
				output += "\t\ttemplate<typename F>\n";
				output += "\t\tDCON_RELEASE_INLINE void execute_parallel_over_" + o.name + "(F&& functor) {\n";
				output += "\t\t\tve::execute_parallel_unaligned(" + o.name + ".size_used, functor);\n";
				output += "\t\t}\n";
				output += "#endif\n";
			}
		}

		

		output += "\n";
		
		//make serialize records
		for(auto& rt : parsed_file.load_save_routines) {
			output += "\t\tload_record make_serialize_record_" + rt.name + "() const noexcept {\n";
			output += "\t\t\tload_record result;\n";

			for(auto& o : parsed_file.relationship_objects) {
				bool passed_filter = false;
				if(rt.pos_obj_tags.size() == 0) {
					passed_filter = true;
				} else {
					for(auto& tg : rt.pos_obj_tags) {
						if(std::find(o.obj_tags.begin(), o.obj_tags.end(), tg) != o.obj_tags.end())
							passed_filter = true;
					}
				}
				for(auto& tg : rt.neg_obj_tags) {
					if(std::find(o.obj_tags.begin(), o.obj_tags.end(), tg) != o.obj_tags.end())
						passed_filter = false;
				}
				if(passed_filter) {
					output += "\t\t\tresult." + o.name + " = true;\n";
					for(auto& io : o.indexed_objects) {
						output += "\t\t\tresult." + o.name + "_" + io.property_name + " = true;\n";

					}
					if(o.store_type == storage_type::erasable) {
						output += "\t\t\tresult." + o.name + "__index = true;\n";
					}
					for(auto& prop : o.properties) {
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
							output += "\t\t\tresult." + o.name + "_" + prop.name + " = true;\n";
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
		for(auto& o : parsed_file.relationship_objects) {
			output += "\t\t\tif(serialize_selection." + o.name + ") {\n";
			output += "\t\t\t\tdcon::record_header header(sizeof(uint32_t), \"uint32_t\", \"" + o.name + "\", \"@size\");\n";
			output += "\t\t\t\ttotal_size += header.serialize_size();\n";
			output += "\t\t\t\ttotal_size += sizeof(uint32_t);\n";
			output += "\t\t\t}\n";

			if(o.store_type == storage_type::erasable) {
				output += "\t\t\tif(serialize_selection." + o.name + "__index) {\n";
				output += "\t\t\t\tdcon::record_header header(sizeof(" + o.name + "_id) * " + o.name + ".size_used, \"" + size_to_tag_type(o.size) + "\", \"" + o.name + "\", \"_index\");\n";
				output += "\t\t\t\ttotal_size += header.serialize_size();\n";
				output += "\t\t\t\ttotal_size += sizeof(" + o.name + "_id) * " + o.name + ".size_used;\n";
				output += "\t\t\t}\n";
			}

			for(auto& io : o.indexed_objects) {
				if(io.related_to != o.primary_key) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + io.property_name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + io.type_name + "_id) * " + o.name + ".size_used, \""
						+ size_to_tag_type(io.related_to->size) + "\", \"" + o.name + "\", \"" + io.property_name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += sizeof(" + io.type_name + "_id) * " + o.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}

			for(auto& prop : o.properties) {
				if(prop.is_derived) {

				} else if(prop.is_bitfield) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header((" + o.name + ".size_used + 7) / 8, \""
						+ "bitfield" + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += (" + o.name + ".size_used + 7) / 8;\n";
					output += "\t\t\t}\n";
				} else if(prop.is_special_vector) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, &total_size](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + o.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\ttotal_size += sizeof(uint16_t); total_size += sizeof(" + prop.data_type + ") * (rng.second - rng.first); });\n";
					output += "\t\t\t\ttotal_size += " + std::to_string(prop.data_type.length() + 1) + ";\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \"stable_mk_2_tag\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";

					output += "\t\t\t}\n";
				} else if(prop.is_object) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, &total_size]("
						+ prop.data_type + " const& obj){ total_size += t->serialize_size(obj); });\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \""
						+ prop.data_type + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t}\n";
				} else {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + prop.data_type + ") * " + o.name + ".size_used, \""
						+ prop.data_type + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\ttotal_size += header.serialize_size();\n";
					output += "\t\t\t\ttotal_size += sizeof(" + prop.data_type + ") * " + o.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}
		}
		output += "\t\t\treturn total_size;\n";
		output += "\t\t}\n";

		//serialize
		output += "\t\tvoid serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {\n";

		for(auto& o : parsed_file.relationship_objects) {
			output += "\t\t\tif(serialize_selection." + o.name + ") {\n";
			output += "\t\t\t\tdcon::record_header header(sizeof(uint32_t), \"uint32_t\", \"" + o.name + "\", \"@size\");\n";
			output += "\t\t\t\theader.serialize(output_buffer);\n";
			output += "\t\t\t\t*(reinterpret_cast<uint32_t*>(output_buffer)) = " + o.name + ".size_used;\n";
			output += "\t\t\t\toutput_buffer += sizeof(uint32_t);\n";
			output += "\t\t\t}\n";

			if(o.store_type == storage_type::erasable) {
				output += "\t\t\tif(serialize_selection." + o.name + "__index) {\n";
				output += "\t\t\t\tdcon::record_header header(sizeof(" + o.name + "_id) * " + o.name + ".size_used, \"" + size_to_tag_type(o.size) + "\", \"" + o.name + "\", \"_index\");\n";
				output += "\t\t\t\theader.serialize(output_buffer);\n";
				output += "\t\t\t\tmemcpy(reinterpret_cast<" + o.name + "_id*>(output_buffer), "
					+ o.name + ".m__index.vptr(), sizeof(" + o.name + "_id) * " + o.name + ".size_used);\n";
				output += "\t\t\t\toutput_buffer += sizeof(" + o.name + "_id) * " + o.name + ".size_used;\n";
				output += "\t\t\t}\n";
			}

			for(auto& io : o.indexed_objects) {
				if(io.related_to != o.primary_key) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + io.property_name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + io.type_name + "_id) * " + o.name + ".size_used, \""
						+ size_to_tag_type(io.related_to->size) + "\", \"" + o.name + "\", \"" + io.property_name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<" + io.type_name + "_id*>(output_buffer), "
						+ o.name + ".m_" + io.property_name + ".vptr(), sizeof(" + io.type_name + "_id) * " + o.name + ".size_used);\n";
					output += "\t\t\t\toutput_buffer += sizeof(" + io.type_name + "_id) * " + o.name + ".size_used;\n";
					output += "\t\t\t}\n";
				}
			}

			for(auto& prop : o.properties) {
				if(prop.is_derived) {

				} else if(prop.is_bitfield) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header((" + o.name + ".size_used + 7) / 8, \""
						+ "bitfield" + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<bitfield_type*>(output_buffer), "
						+ o.name + ".m_" + prop.name  + ".vptr(), (" + o.name + ".size_used + 7) / 8);\n";
					output += "\t\t\t\toutput_buffer += (" + o.name + ".size_used + 7) / 8;\n";
					output += "\t\t\t}\n";
				} else if(prop.is_special_vector) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";

					output += "\t\t\t\tsize_t total_size = 0;\n";
					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, &total_size](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + o.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\ttotal_size += sizeof(uint16_t); total_size += sizeof(" + prop.data_type + ") * (rng.second - rng.first); });\n";
					output += "\t\t\t\ttotal_size += " + std::to_string(prop.data_type.length() + 1) + ";\n";

					output += "\t\t\t\tdcon::record_header header(total_size, \"stable_mk_2_tag\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";

					output += "\t\t\t\tmemcpy(reinterpret_cast<char*>(output_buffer), \"" + prop.data_type + "\", " + std::to_string(prop.data_type.length() + 1) + ");\n";
					output += "\t\t\t\toutput_buffer += " + std::to_string(prop.data_type.length() + 1) + ";\n";

					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, output_buffer](stable_mk_2_tag obj){\n";
					output += "\t\t\t\t\tauto rng = dcon::get_range(t->" + o.name + "." + prop.name + "_storage, obj);\n";
					output += "\t\t\t\t\t*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(rng.second - rng.first);\n";
					output += "\t\t\t\t\toutput_buffer += sizeof(uint16_t);\n";
					output += "\t\t\t\t\tmemcpy(reinterpret_cast<" + prop.data_type + "*>(output_buffer), rng.first, sizeof(" + prop.data_type + ") * (rng.second - rng.first));\n"
						+ o.name + ".m_" + prop.name + ".vptr(), sizeof(" + prop.data_type + ") * " + o.name + ".size_used);\n";
					output += "\t\t\t\t\toutput_buffer += sizeof(" + prop.data_type + ") * (rng.second - rng.first);\n";
					output += "\t\t\t\t\t});\n";

					output += "\t\t\t}\n";
				} else if(prop.is_object) {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tsize_t total_size = 0;\n";
					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, &total_size](" 
						+ prop.data_type + " const& obj){ total_size += t->serialize_size(obj); });\n";
					output += "\t\t\t\tdcon::record_header header(total_size, \""
						+ prop.data_type + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tstd::for_each(" + o.name + ".m_" + prop.name + ".vptr(), "
						+ o.name + ".m_" + prop.name + ".vptr() " + o.name + ".size_used, [t = this, &output_buffer]("
						+ prop.data_type + " const& obj){ t->serialize(output_buffer, obj); });\n";
					output += "\t\t\t}\n";
				} else {
					output += "\t\t\tif(serialize_selection." + o.name + "_" + prop.name + ") {\n";
					output += "\t\t\t\tdcon::record_header header(sizeof(" + prop.data_type + ") * " + o.name + ".size_used, \""
						+ prop.data_type + "\", \"" + o.name + "\", \"" + prop.name + "\");\n";
					output += "\t\t\t\theader.serialize(output_buffer);\n";
					output += "\t\t\t\tmemcpy(reinterpret_cast<" + prop.data_type + "*>(output_buffer), "
						+ o.name + ".m_" + prop.name + ".vptr(), sizeof(" + prop.data_type + ") * " + o.name + ".size_used);\n";
					output += "\t\t\t\toutput_buffer += sizeof(" + prop.data_type + ") * " + o.name + ".size_used;\n";
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
		for(auto& o : parsed_file.relationship_objects) {
			if(first) {
				output += "\t\t\t\tif(header.is_object(\"" + o.name + "\")) {\n"; //has matched object
				first = false;
			} else {
				output += "\t\t\t\telse if(header.is_object(\"" + o.name + "\")) {\n"; //has matched object
			}
			output += "\t\t\t\t\tif(header.is_property(\"@size\") && header.record_size == sizeof(uint32_t)) {\n"; // is size
			output += "\t\t\t\t\t\t" + o.name + "_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));\n";
			output += "\t\t\t\t\t\tserialize_selection." + o.name + " = true;\n";
			output += "\t\t\t\t\t}\n"; // end is size

			if(o.store_type == storage_type::erasable) {
				output += "\t\t\t\t\telse if(header.is_property(\"__index\")) {\n"; // matches
				output += "\t\t\t\t\tif(header.is_type(\"" + size_to_tag_type(o.size)  + "\")) {\n"; //correct type
				output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m__index.vptr(), reinterpret_cast<" + size_to_tag_type(o.size) + " const*>(input_buffer)"
					", std::min(size_t(" + o.name + ".size_used) * sizeof(" + size_to_tag_type(o.size) + "), "
					"header.record_size));\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
				output += "\t\t\t\t\t}\n";// end correct type
				if(size_to_tag_type(o.size) != "uint8_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint8_t\")) {\n"; //wrong type uint8_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint8_t
				}
				if(size_to_tag_type(o.size) != "uint16_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //wrong type uint16_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint16_t
				}
				if(size_to_tag_type(o.size) != "uint32_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //wrong type uint32_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint32_t
				}

				//redo free list
				output += "\t\t\t\t\t\tif(serialize_selection." + o.name + "__index == true){\n";
				output += "\t\t\t\t\t" + o.name + ".first_free = " + o.name + "_id();\n";
				output += "\t\t\t\t\tfor(int32_t j = int32_t(" + std::to_string(o.size) + "); j >= 0; --j) {\n";
				output += "\t\t\t\t\t\tif(" + o.name + ".m__index.vptr()[j] != " + o.name + "_id(" + size_to_tag_type(o.size) + "(j))) {\n";
				output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[j] = " + o.name + ".first_free;\n";
				output += "\t\t\t\t\t\t\t" + o.name + ".first_free = " + o.name + "_id(" + size_to_tag_type(o.size) + "(j));\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t}\n\n";
				output += "\t\t\t\t\t}\n\n";

				output += "\t\t\t\t\t}\n"; //end index match
			} // end: load index handling for erasable

			for(auto& io : o.indexed_objects) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + io.property_name + "\")) {\n"; // matches
				
				output += "\t\t\t\t\tif(header.is_type(\"uint8_t\")) {\n"; //type uint8_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint8_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size)  + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint16_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint32_t

				output += "\t\t\t\t\t}\n"; //end property match
			} // end index properties

			for(auto& prop : o.properties) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + prop.name + "\")) {\n"; // matches
				if(prop.is_derived) {

				} else if(prop.is_bitfield) {
					output += "\t\t\t\t\tif(header.is_type(\"bitfield\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<bitfield_type const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used + 7) / 8, header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == "bool") {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + prop.name + ".vptr(), i, convert_type(&temp, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + prop.name + ".vptr(), i, "
									"convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				} else if(prop.is_special_vector) {
					output += "\t\t\t\t\tif(header.is_type(\"stable_mk_2_tag\")) {\n"; //correct type
					output += "\t\t\t\t\t\t\tuint32_t ix = 0;\n";

					//read internal data type
					output += "\t\t\t\tstd::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, 0);\n";
					
					output += "\t\t\t\t\tif(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
						"reinterpret_cast<char const*>(zero_pos), \"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ){\n";
					output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n";
					
					output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n";
					output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
						"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + prop.data_type + ") ));\n";
					output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
					output += "\t\t\t\t\t\t\t}\n"; // endif

					output += "\t\t\t\t\t\t\tdcon::load_range(" + o.name + "." + prop.name + "_storage, " 
						+ o.name + ".m_" + prop.name + ".vptr()[ix], reinterpret_cast<" + prop.data_type + " const*>(icpy), "
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
								
								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";
								
								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(reinterpret_cast<" + con.from + " const*>(icpy), (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + con.from + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
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

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + basic_type + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(icpy) + i));\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + basic_type + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							}
						}
					}
					// end if prop is special array
				} else if(prop.is_object) {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + prop.data_type + "))); ++i) {\n";
					output += "\t\t\t\t\t\t\tdeserialize(icpy, " + o.name + ".m_" + prop.name + ".vptr()[i], input_buffer + header.record_size);\n";
					output += "\t\t\t\t\t\t}\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";

					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer, (" + con.to + "*)nullptr) + i);\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
				} else {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(header.is_type(\"" + basic_type + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + basic_type + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(input_buffer) + i));\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
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
		for(auto& o : parsed_file.relationship_objects) {
			if(first_header_if) {
				output += "\t\t\t\tif(header.is_object(\"" + o.name + "\") && mask." + o.name + ") {\n"; //has matched object
				first_header_if = false;
			} else {
				output += "\t\t\t\telse if(header.is_object(\"" + o.name + "\")) {\n"; //has matched object
			}
			output += "\t\t\t\t\tif(header.is_property(\"@size\") && header.record_size == sizeof(uint32_t)) {\n"; // is size
			output += "\t\t\t\t\t\t" + o.name + "_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));\n";
			output += "\t\t\t\t\t\tserialize_selection." + o.name + " = true;\n";
			output += "\t\t\t\t\t}\n"; // end is size

			if(o.store_type == storage_type::erasable) {
				output += "\t\t\t\t\telse if(header.is_property(\"__index\") && mask." + o.name + "__index) {\n"; // matches
				output += "\t\t\t\t\tif(header.is_type(\"" + size_to_tag_type(o.size) + "\")) {\n"; //correct type
				output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m__index.vptr(), reinterpret_cast<" + size_to_tag_type(o.size) + " const*>(input_buffer)"
					", std::min(size_t(" + o.name + ".size_used) * sizeof(" + size_to_tag_type(o.size) + "), "
					"header.record_size));\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
				output += "\t\t\t\t\t}\n";// end correct type
				if(size_to_tag_type(o.size) != "uint8_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint8_t\")) {\n"; //wrong type uint8_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint8_t
				}
				if(size_to_tag_type(o.size) != "uint16_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //wrong type uint16_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint16_t
				}
				if(size_to_tag_type(o.size) != "uint32_t") {
					output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //wrong type uint32_t
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)\n";
					output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[i].value = "
						+ size_to_tag_type(o.size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "__index = true;\n";
					output += "\t\t\t\t\t}\n";// end wrong type uint32_t
				}

				//redo free list
				output += "\t\t\t\t\t\tif(serialize_selection." + o.name + "__index == true){\n";
				output += "\t\t\t\t\t" + o.name + ".first_free = " + o.name + "_id();\n";
				output += "\t\t\t\t\tfor(int32_t j = int32_t(" + std::to_string(o.size) + "); j >= 0; --j) {\n";
				output += "\t\t\t\t\t\tif(" + o.name + ".m__index.vptr()[j] != " + o.name + "_id(" + size_to_tag_type(o.size) + "(j))) {\n";
				output += "\t\t\t\t\t\t\t" + o.name + ".m__index.vptr()[j] = " + o.name + ".first_free;\n";
				output += "\t\t\t\t\t\t\t" + o.name + ".first_free = " + o.name + "_id(" + size_to_tag_type(o.size) + "(j));\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t}\n\n";
				output += "\t\t\t\t\t}\n\n";

				output += "\t\t\t\t\t}\n"; //end index match
			} // end: load index handling for erasable

			for(auto& io : o.indexed_objects) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + io.property_name + "\") && mask." + o.name + "_" + io.property_name + ") {\n"; // matches

				output += "\t\t\t\t\tif(header.is_type(\"uint8_t\")) {\n"; //type uint8_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint8_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint16_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint16_t
				output += "\t\t\t\t\telse if(header.is_type(\"uint32_t\")) {\n"; //type uint16_t
				output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {\n";
				output += "\t\t\t\t\t\t\t" + io.type_name + "_id temp;\n";
				output += "\t\t\t\t\t\t\ttemp.value = " + size_to_tag_type(io.related_to->size) + "(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));\n";
				output += "\t\t\t\t\t\t\t" + o.name + "_set_" + io.property_name + "(" + o.name + "_id(" + size_to_tag_type(o.size) + "(i)), temp);\n";
				output += "\t\t\t\t\t\t}\n";
				output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + io.property_name + " = true;\n";
				output += "\t\t\t\t\t}\n";// end type uint32_t

				output += "\t\t\t\t\t}\n"; //end property match
			} // end index properties

			for(auto& prop : o.properties) {
				output += "\t\t\t\t\telse if(header.is_property(\"" + prop.name + "\") && mask." + o.name + "_" + prop.name + ") {\n"; // matches
				if(prop.is_derived) {

				} else if(prop.is_bitfield) {
					output += "\t\t\t\t\tif(header.is_type(\"bitfield\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<bitfield_type const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used + 7) / 8, header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type

					for(auto& con : parsed_file.conversion_list) {
						if(con.to == "bool") {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + prop.name + ".vptr(), i, convert_type(&temp, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + prop.name + ".vptr(), i, "
									"convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr));\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							}
						}
					}
				} else if(prop.is_special_vector) {
					output += "\t\t\t\t\tif(header.is_type(\"stable_mk_2_tag\")) {\n"; //correct type
					output += "\t\t\t\t\t\t\tuint32_t ix = 0;\n";

					//read internal data type
					output += "\t\t\t\tstd::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, 0);\n";

					output += "\t\t\t\t\tif(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
						"reinterpret_cast<char const*>(zero_pos), \"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ){\n";
					output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n";

					output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n";
					output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
						"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + prop.data_type + ") ));\n";
					output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
					output += "\t\t\t\t\t\t\t}\n"; // endif

					output += "\t\t\t\t\t\t\tdcon::load_range(" + o.name + "." + prop.name + "_storage, "
						+ o.name + ".m_" + prop.name + ".vptr()[ix], reinterpret_cast<" + prop.data_type + " const*>(icpy), "
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

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), "
									"reinterpret_cast<char const*>(zero_pos), \"" + con.from + "\")) {\n"; // if = from

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + con.from + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									"convert_type(reinterpret_cast<" + con.from + " const*>(icpy), (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + con.from + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
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

								output += "\t\t\t\t\t\tfor(std::byte const* icpy = zero_pos + 1; ix < " + o.name + ".size_used && icpy < input_buffer + header.record_size; ) {\n";
								output += "\t\t\t\t\t\t\tuint16_t sz = 0;\n"; // 2

								output += "\t\t\t\t\t\t\tif(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {\n"; // if read sz
								output += "\t\t\t\t\t\t\t\tsz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), "
									"(input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(" + basic_type + ") ));\n";
								output += "\t\t\t\t\t\t\t\ticpy += sizeof(uint16_t);\n";
								output += "\t\t\t\t\t\t\t}\n"; // endif read sz

								output += "\t\t\t\t\t\t\tdcon::resize(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], sz);\n";

								output += "\t\t\t\t\t\t\tfor(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {\n"; // ii for
								output += "\t\t\t\t\t\t\tdcon::get(" + o.name + "." + prop.name + "_storage, " + o.name + ".m_" + prop.name + ".vptr()[ix], ii) = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(icpy) + i));\n";
								output += "\t\t\t\t\t\t\ticpy += sizeof(" + basic_type + ");\n";
								output += "\t\t\t\t\t\t\t}\n"; //end ii for

								output += "\t\t\t\t\t\t\t++ix;\n";
								output += "\t\t\t\t\t\t}\n"; //end for

								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n"; // end if = from
							}
						}
					}
					// end if prop is special array
				} else if(prop.is_object) {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type

					output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
					output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + prop.data_type + "))); ++i) {\n";
					output += "\t\t\t\t\t\t\tdeserialize(icpy, " + o.name + ".m_" + prop.name + ".vptr()[i], input_buffer + header.record_size);\n";
					output += "\t\t\t\t\t\t}\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";

					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer, (" + con.to + "*)nullptr) + i);\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
				} else {
					output += "\t\t\t\t\tif(header.is_type(\"" + prop.data_type + "\")) {\n"; //correct type
					output += "\t\t\t\t\t\tmemcpy(" + o.name + ".m_" + prop.name + ".vptr(), reinterpret_cast<" + prop.data_type + " const*>(input_buffer)"
						", std::min(size_t(" + o.name + ".size_used) * sizeof(" + prop.data_type + "), header.record_size));\n";
					output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
					output += "\t\t\t\t\t}\n";// end correct type
					for(auto& con : parsed_file.conversion_list) {
						if(con.to == prop.data_type) {
							if(std::find(parsed_file.object_types.begin(), parsed_file.object_types.end(), con.from) != parsed_file.object_types.end()) {
								// from is an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\t\tstd::byte const* icpy = input_buffer;\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i) {\n";
								output += "\t\t\t\t\t\t\t" + con.from + " temp;\n";
								output += "\t\t\t\t\t\t\tdeserialize(icpy, temp, input_buffer + header.record_size);\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = convert_type(&temp, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\t}\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";
							} else {
								// from not an object
								output += "\t\t\t\t\telse if(header.is_type(\"" + con.from + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + con.from + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ "convert_type(reinterpret_cast<" + con.from + " const*>(input_buffer) + i, (" + con.to + "*)nullptr);\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
								output += "\t\t\t\t\t}\n";

							}
						}
					}
					if(is_common_type(prop.data_type)) {
						const auto normed_type = normalize_type(prop.data_type);
						for(auto& basic_type : common_types) {
							if(basic_type != normed_type) {
								output += "\t\t\t\t\telse if(header.is_type(\"" + basic_type + "\")) {\n";
								output += "\t\t\t\t\t\tfor(uint32_t i = 0; i < std::min(" + o.name + ".size_used, uint32_t(header.record_size / sizeof(" + basic_type + "))); ++i)\n";
								output += "\t\t\t\t\t\t\t" + o.name + ".m_" + prop.name + ".vptr()[i] = "
									+ prop.data_type + "(*(reinterpret_cast<" + basic_type + " const*>(input_buffer) + i));\n";
								output += "\t\t\t\t\t\tserialize_selection." + o.name + "_" + prop.name + " = true;\n";
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
