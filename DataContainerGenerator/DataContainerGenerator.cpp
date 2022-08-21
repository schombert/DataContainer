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

	while(input < end && (in_quote || in_lt > 0 || (*input != ' ' && *input != '\t' && *input != ',' && *input != '\r' && *input != '\n'))) {
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

	std::vector<relationship_object_def> relationship_objects;
	std::vector<load_save_def> load_save_routines;
	std::vector<conversion_def> conversion_list;
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
		if(i.index == index_type::at_most_one) {
			if(result.length() != 0) 
				result += ", ";
			result += i.type_name + "_id " + i.property_name + " _p";
		}
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

std::string size_to_tag_type(size_t sz) {
	if(sz <= 126) {
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
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		std::fstream input_file;
		input_file.open(argv[1], std::ios::in);
		
		const std::string output_file_name = [otemp = std::string(argv[1])]() mutable {
			if(otemp.length() >= 4 && otemp[otemp.length() - 4] == '.') {
				otemp[otemp.length() - 3] = 'c';
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
					error_to_file(output_file_name, std::string("All objects must be named (line: ") + std::to_string(line_count) + ")" );
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
										if(next_str == ">=0")
											i = index_type::many;
										else if(next_str == "<=1")
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
						link.related_to->relationships_involved_in.push_back(in_relation_information{r.name, link.property_name,
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

		for(auto& r : parsed_file.relationship_objects) {
			for(auto& p : r.properties) {
				if(p.is_object) {
					if(std::find(needs_serialize.begin(), needs_serialize.end(), p.data_type) == needs_serialize.end()) {
						needs_serialize.push_back(p.data_type);
					}
				}
			}
		}

		// compose contents of generated file
		std::string output;

		//includes
		output += "#pragma once\r\n";
		output += "#include <cstdint>\r\n";
		output += "#include <utility>\r\n";
		output += "#include <vector>\r\n";
		output += "#include <algorithem>\r\n";
		output += "#include \"ve.h\"\r\n";
		for(auto& i : parsed_file.includes) {
			output += "#include ";
			output += i;
			output += "\r\n";
		}

		//open new namespace
		output += "\r\n";

		output += "#ifdef NDEBUG\r\n";
		output += "#ifdef _MSC_VER\r\n";
		output += "#define DCON_RELEASE_INLINE __forceinline\r\n";
		output += "#else\r\n";
		output += "#define DCON_RELEASE_INLINE inline __attribute__((always_inline))\r\n";
		output += "#endif\r\n";
		output += "#else\r\n";
		output += "#define DCON_RELEASE_INLINE inline\r\n";
		output += "#endif\r\n";

		output += "\r\n";
		output += "namespace " + parsed_file.namspace + " {\r\n";

		{
			//id types definitions
			for(auto& o : parsed_file.relationship_objects) {
				if( !o.primary_key) {
					const auto underlying_type = o.is_expandable ?  std::string("uint32_t") : size_to_tag_type(o.size);
					//id class begin
					output += std::string("\tclass ") + o.name + "_id {\r\n";

					output += "\t\tpublic:\r\n";
					output += "\t\tusing value_base_t = " + underlying_type + ";\r\n";
					output += "\t\tusing zero_is_null_t = std::true_type;\r\n";
					output += "\r\n";

					//value member declaration
					output += std::string("\t\t") + underlying_type + " value;\r\n\r\n";

					//constructors
					output += std::string("\t\texplicit constexpr ") + o.name + "_id(" + underlying_type + " v) noexcept : value(v + 1);\r\n";
					output += std::string("\t\tconstexpr ") + o.name +  "_id(const " + o.name + "_id& v) noexcept = default\r\n";
					output += std::string("\t\tconstexpr ") + o.name + "_id(" + o.name + "_id&& v) noexcept = default\r\n";
					output += std::string("\t\tconstexpr ") + o.name + "_id() noexcept : value(" + underlying_type + "(0));\r\n\r\n";

					//operators
					output += "\t\t" + o.name + "_id& operator=(" + o.name + "_id&& v) noexcept = default;\r\n";
					output += "\t\t" + o.name + "_id& operator=(" + o.name + "_id const& v) noexcept = default;\r\n";
					output += "\t\tconstexpr bool operator==(" + o.name + "_id v) const noexcept { return value == v.value; }\r\n";
					output += "\t\tconstexpr bool operator!=(" + o.name + "_id v) const noexcept { return value != v.value; }\r\n";
					output += "\t\tconstexpr bool operator<(" + o.name + "_id v) const noexcept { return value < v.value; }\r\n";
					output += "\t\tconstexpr bool operator<=(" + o.name + "_id v) const noexcept { return value <= v.value; }\r\n";
					output += "\t\texplicit constexpr operator bool() const noexcept { return value != " + underlying_type + "(0); }\r\n\r\n";

					//index_function
					output += "\t\tconstexpr DCON_RELEASE_INLINE int32_t index() const noexcept {\r\n";
					output += "\t\t\treturn int32_t(value) - 1;\r\n";
					output += "\t\t}\r\n";

					//id class end
					output += "\t};\r\n\r\n";

					output += std::string("\tclass ") + o.name + "_id_pair {\r\n";
					output += "\t\tpublic:\r\n";
					output += "\t\t" + o.name + "_id left;\r\n";
					output += "\t\t" + o.name + "_id right;\r\n";
					output += "\t};\r\n\r\n";
				} else {
					output += "using " + o.name + "_id = " + o.primary_key->name + "_id;\r\n\r\n";
				}
				output += "constexpr DCON_RELEASE_INLINE bool is_valid_index(" + o.name + "_id id) { return bool(id); }\r\n\r\n";
			}

			// close namespace briefly
			output += "}\r\n\r\n";

			//mark each id as going into a tagged vector
			output += "namespace ve {\r\n";
			for(auto& o : parsed_file.relationship_objects) {
				if(!o.primary_key) {
					output += "\t\ttemplate<>\r\n";
					output += "\t\tstruct value_to_vector_type_s<" + o.name + "_id> {\r\n";
					output += "\t\t\tusing type = tagged_vector<" + o.name + "_id>;\r\n";
					output += "\t\t};\r\n";
				}
			}
			output += "}\r\n\r\n";


			//reopen namespace
			output += "namespace " + parsed_file.namspace + " {\r\n";

			//predeclare data_container
			output += "\tclass data_container;\r\n\r\n";

			//write internal classes

			//open internal namespace
			output += "\tnamespace internal {\r\n";

			for(auto& o : parsed_file.relationship_objects) {
				//object class begin
				output += "\t\tclass alignas(64) " + o.name + "_class {\r\n";

				//begin members declaration
				output += "\t\t\tprivate:\r\n";
				output += "\t\t\tuint32_t size_used = 0;\r\n";
				if(o.store_type == storage_type::erasable) {
					if(!o.is_expandable) {
						output += "\t\t\t" + o.name + "_id first_free;\r\n";
						output += "\t\t\tstruct alignas(64) dtype__index { \r\n"
							"\t\t\t\t" + o.name + "_id values[" + std::to_string(o.size) + "]; \r\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
							"\t\t\t\tdtype__index() { std::uninitialized_value_construct_n(values, " + std::to_string(o.size) + "); } "
							"\t\t\t} m__index;\r\n";
					} else {
						output += "\t\t\t" + o.name + "_id first_free;\r\n";
						output += "\t\t\tstruct dtype__index { \r\n"
							"\t\t\t\tstd::vector<" + o.name + "_id> values; \r\n"
							"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
							"\t\t\t\tdtype__index() { values.emplace_back(); }"
							"\t\t\t} m__index;\r\n";
					}
				}

				for(auto& p : o.properties) {
					if(p.is_derived) {
						// no data for a derived property
					} else if(p.is_bitfield) {
						if(!o.is_expandable) {
							std::string bytes_size = std::string("((uint32_t(") + std::to_string(o.size) + " + 7)) / 8ui32 + 63ui32) & ~63ui32";
							output += "\t\t\tstruct alignas(64) dtype_" + p.name + " { \r\n"
								"\t\t\t\tdcon::bitfield_type padding[64]; \r\n"
								"\t\t\t\tdcon::bitfield_type values[" + bytes_size + "]; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
								"\t\t\t\tdtype_" + p.name + "() { std::fill_n(values - 1, 1 + " + bytes_size + ", dcon::bitfield_type{ 0ui8 }); }\r\n"
								"\t\t\t} m_" + p.name + ";\r\n";
						} else {
							output += "\t\t\tstruct dtype_" + p.name + " { \r\n"
								"\t\t\t\tstd::vector<dcon::bitfield_type> values; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
								"\t\t\t\tdtype_" + p.name + "() { values.push_back(dcon::bitfield_type{ 0ui8 }); }\r\n"
								"\t\t\t} m_" + p.name + ";\r\n";
						}
					} else if(p.is_object) {
						if(!o.is_expandable) {
							output += "\t\t struct dtype_" + p.name + " { \r\n"
								"\t\t\t " + p.data_type + " values[" + std::to_string(o.size) + "]; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
								"\t\t\t dtype_" + p.name + "() {}\r\n"
								"\t\t } m_" + p.name + ";\r\n";
						} else {
							output += "\t\t struct dtype_" + p.name + " { \r\n"
								"\t\t\tstd::vector<" + p.data_type + "> values; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
								"\t\t\t dtype_" + p.name + "() { values.emplace_back(); }\r\n"
								"\t\t } m_" + p.name + ";\r\n";
						}
					} else if(p.is_special_vector) {
						//fill in with special vector type and pool object
						if(!o.is_expandable) {
							output += "\t\t struct dtype_" + p.name + " { \r\n"
								"\t\t\tstable_mk_2_tag values[" + std::to_string(o.size) + "]; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
								"\t\t\tdtype_" + p.name + "() { std::uninitialized_fill_n(values, " + std::to_string(o.size) +
								", std::numeric_limits<dcon::stable_mk_2_tag>::max()); }\r\n"
								"\t\t } m_" + p.name + ";\r\n";
							output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + p.data_type + ", 16, " + std::to_string(p.special_pool_size) + " > " + p.name + "_storage;\r\n";
						} else {
							output += "\t\t struct dtype_" + p.name + " { \r\n"
								"\t\t\tstd::vector<stable_mk_2_tag> values; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
								"\t\t\tdtype_" + p.name + "() { values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max())); }\r\n"
								"\t\t } m_" + p.name + ";\r\n";
							output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + p.data_type + ", 16, " + std::to_string(p.special_pool_size) + " > " + p.name + "_storage;\r\n";
						}
					} else {
						if(!o.is_expandable) {
							std::string member_count = std::string("(sizeof(") + p.data_type + ") <= 64 ? ("
								"uint32_t(" + std::to_string(o.size) + ") + (64ui32 / uint32_t(sizeof(" + p.data_type + "))) - 1ui32) "
								"& ~(64ui32 / uint32_t(sizeof(" + p.data_type + ")) - 1ui32) : uint32_t(" + std::to_string(o.size) + "))";
							output += "\t\t\tstruct alignas(64) dtype_" + p.name + " { \r\n"
								"\t\t\t\tuint8_t padding[(sizeof(" + p.data_type + ") + 63ui32) & ~63ui32]; \r\n"
								"\t\t\t\t" + p.data_type + " values[" + member_count + "]; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
								"\t\t\t\tdtype_" + p.name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\r\n"
								"\t\t\t} m_" + p.name + ";\r\n";
						} else {
							output += "\t\t\tstruct dtype_" + p.name + " { \r\n"
								"\t\t\t\tstd::vector<" + p.data_type + "> values; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
								"\t\t\t\tdtype_" + p.name + "() { values.emplace_back(); }\r\n"
								"\t\t\t} m_" + p.name + ";\r\n";
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
							output += "\t\t\tstruct alignas(64) dtype_" + i.property_name + " { \r\n"
								"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \r\n"
								"\t\t\t\t" + i.type_name + "_id values[" + member_count + "]; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
								"\t\t\t\tdtype_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\r\n"
								"\t\t\t} m_" + i.property_name + ";\r\n";
						} else {
							output += "\t\t\tstruct dtype_" + i.property_name + " { \r\n"
								"\t\t\t\tstd::vector<" + i.type_name + "_id> values; \r\n"
								"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
								"\t\t\t\tdtype_" + i.property_name + "() { values.emplace_back(); }\r\n"
								"\t\t\t} m_" + i.property_name + ";\r\n";
						}
					}

					if(i.index == index_type::many) {
						if(i.ltype == list_type::list) {
							if(!o.is_expandable) {
								// list intrusive links
								output += "\t\t struct dtype_link_" + i.property_name + " { \r\n"
									"\t\t\t " + i.type_name + "_id_pair values[" + std::to_string(o.size) + "]; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
									"\t\t\t dtype_link_" + i.property_name + "() { std::uninitialized_value_construct_n(values, " + std::to_string(o.size) + "); }\r\n"
									"\t\t } m_link_" + i.property_name + ";\r\n";
							} else {
								// list intrusive links
								output += "\t\t struct dtype_link_" + i.property_name + " { \r\n"
									"\t\t\tstd::vector<" + i.type_name + "_id_pair> values; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
									"\t\t\t dtype_link_" + i.property_name + "() { values.emplace_back(); }\r\n"
									"\t\t } m_link_" + i.property_name + ";\r\n";
							}

							if(!i.related_to->is_expandable) {
								// reference back to head list entry from object
								std::string member_count = std::string("(sizeof(") + o.name + "_id) <= 64 ? ("
									"uint32_t(" + std::to_string(i.related_to->size) + ") + (64ui32 / uint32_t(sizeof(" + o.name + "_id))) - 1ui32) "
									"& ~(64ui32 / uint32_t(sizeof(" + i.type_name + "_id)) - 1ui32) : uint32_t(" + std::to_string(i.related_to->size) + "))";
								output += "\t\t\tstruct alignas(64) dtype_head_back_" + i.property_name + " { \r\n"
									"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \r\n"
									"\t\t\t\t" + o.name + "_id values[" + member_count + "]; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
									"\t\t\t\tdtype_head_back_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\r\n"
									"\t\t\t} m_head_back_" + i.property_name + ";\r\n";
							} else {
								// reference back to head list entry from object
								output += "\t\t\tstruct dtype_head_back_" + i.property_name + " { \r\n"
									"\t\t\t\tstd::vector<" + o.name + "_id> values; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
									"\t\t\t\tdtype_head_back_" + i.property_name + "() { values.emplace_back(); }\r\n"
									"\t\t\t} m_head_back_" + i.property_name + ";\r\n";
							}
						} else if(i.ltype == list_type::std_vector) {
							//array of relation ids in object
							if(!i.related_to->is_expandable) {
								output += "\t\t struct dtype_array_" + i.property_name + " { \r\n"
									"\t\t\tstd::vector<" + o.name + "_id> values[" + std::to_string(i.related_to->size) + "]; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
									"\t\t\t dtype_array_" + i.property_name + "() {  }\r\n"
									"\t\t } m_array_" + i.property_name + ";\r\n";
							} else {
								output += "\t\t struct dtype_array_" + i.property_name + " { \r\n"
									"\t\t\tstd::vector<std::vector<" + o.name + "_id>> values; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
									"\t\t\t dtype_array_" + i.property_name + "() { values.emplace_back(); }\r\n"
									"\t\t } m_array_" + i.property_name + ";\r\n";
							}
						} else if(i.ltype == list_type::array) {
							//array of relation ids in object
							if(!i.related_to->is_expandable) {
								output += "\t\t struct alignas(64) dtype_array_" + i.property_name + " { \r\n"
									"\t\t\tstable_mk_2_tag values[" + std::to_string(i.related_to->size) + "]; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
									"\t\t\tdtype_array_" + i.property_name + "() { std::uninitialized_fill_n(values, " + std::to_string(i.related_to->size) +
									", std::numeric_limits<dcon::stable_mk_2_tag>::max()); }\r\n"
									"\t\t } m_array_" + i.property_name + ";\r\n";
								output += "\t\tdcon::stable_variable_vector_storage_mk_2<" + i.type_name + "_id, 16, " + std::to_string(o.size * 2) + " > "
									+ i.property_name + "_storage;\r\n";
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
								output += "\t\t\tstruct alignas(64) dtype_link_back_" + i.property_name + " { \r\n"
									"\t\t\t\tuint8_t padding[(sizeof(" + i.type_name + "_id) + 63ui32) & ~63ui32]; \r\n"
									"\t\t\t\t" + o.name + "_id values[" + member_count + "]; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values; }\r\n"
									"\t\t\t\tdtype_link_back_" + i.property_name + "() { std::uninitialized_value_construct_n(values - 1, " + member_count + " + 1); }\r\n"
									"\t\t\t} m_link_back_" + i.property_name + ";\r\n";
							} else {
								output += "\t\t\tstruct dtype_link_back_" + i.property_name + " { \r\n"
									"\t\t\t\tstd::vector<" + o.name + "_id> values; \r\n"
									"\t\t\t\tDCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }\r\n"
									"\t\t\t\tdtype_link_back_" + i.property_name + "() { values.emplace_back(); }\r\n"
									"\t\t\t} m_link_back_" + i.property_name + ";\r\n";
							}
						}
					}
				}


				
				output += "\r\n";
				output += "\t\t\tpublic:\r\n";

				// constructor
				if(o.store_type == storage_type::erasable) {
					output += "\t\t\t" + o.name + "() {\r\n";
					output += "\t\t\t\tfor(int32_t i = " + std::to_string(o.size) + " - 1; i >= 0; --i) {\r\n";
					output += "\t\t\t\t\tm_index.vptr()[i] = first_free;\r\n";
					output += "\t\t\t\t\tfirst_free = " + o.name + "_id(" + size_to_tag_type(o.size) + "(i));\r\n";
					output += "\t\t\t\t}\r\n";
					output += "\t\t\t}\r\n\r\n";
				}

				//object class end
				output += "\t\t\tfriend class data_container;\r\n";
				output += "\t\t};\r\n\r\n";
			}

			//close internal namespace
			output += "\t}\r\n\r\n";

			//class data_container begin
			output += "\tclass data_container {\r\n";
			output += "\t\tpublic:\r\n";
			for(auto& o : parsed_file.relationship_objects) {
				output += "\t\t" + o.name + "_class " + o.name + ";\r\n";
			}
			output += "\r\n";

			for(auto& o : parsed_file.relationship_objects) {
				const std::string id_name = (o.primary_key ? o.primary_key->name : o.name) + "_id";
				const std::string con_tags_type = o.is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

				//getters and setters
				for(auto& p : o.properties) {

					if(p.hook_get) {
						if(p.is_bitfield) {
							output += "\t\tbool get_ " + o.name + "_" + p.name + "(" + id_name + " id) const;\r\n";

							output += "\t\tve::vbitfield_type get_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::vbitfield_type r; r.v = 0;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tr.v |= (get_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i))) << i;\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";

							output += "\t\tve::vbitfield_type get_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::vbitfield_type r; r.v = 0;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\r\n";
							output += "\t\t\t\tr.v |= (get_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i))) << i;\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";

							output += "\t\tve::vbitfield_type get_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::vbitfield_type r; r.v = 0;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tr.v |= (get_" + o.name + "_" + p.name + "(id[i])) << i;\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";
						} else if(is_vectorizable_type(parsed_file, p.data_type)) {
							output += "\t\t" + p.data_type + " get_ " + o.name + " _" + p.name + "(" + id_name + " id) const;\r\n";
							
							output += "\t\tve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tr.set(i, get_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i)));\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";

							output += "\t\tve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\r\n";
							output += "\t\t\t\tr.set(i, get_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i)));\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";

							output += "\t\tve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const {\r\n";
							output += "\t\t\tve::value_to_vector_type<" + p.data_type + "> r;\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tr.set(i, get_" + o.name + "_" + p.name + "(id[i]));\r\n";
							output += "\t\t\treturn r;\r\n";
							output += "\t\t}\r\n";
						} else {
							output += "\t\t" + p.data_type + " get_ " + o.name + " _" + p.name + "(" + id_name + " id) const;\r\n";
						}
					}
					if(p.hook_set) {
						if(p.is_bitfield) {
							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(" + id_name + " id, bool value);\r\n";

							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
								"ve::vbitfield_type value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i), (value.v & uint8_t(1 << i)) != 0);\r\n";
							output += "\t\t}\r\n";

							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
								"ve::vbitfield_type value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i), (value.v & uint8_t(1 << i)) != 0);\r\n";
							output += "\t\t}\r\n";

							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
								"ve::vbitfield_type value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(id[i], (value.v & uint8_t(1 << i)) != 0);\r\n";
							output += "\t\t}\r\n";

						} else if(is_vectorizable_type(parsed_file, p.data_type)) {
							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(" + id_name + " id, " + p.data_type + " value);\r\n";

							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i), value[i]);\r\n";
							output += "\t\t}\r\n";


							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < id.subcount; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(" + id_name + "(id.value + i), value[i]);\r\n";
							output += "\t\t}\r\n";

							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> value) {\r\n";
							output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
							output += "\t\t\t\tset_" + o.name + "_" + p.name + "(id[i], value[i]);\r\n";
							output += "\t\t}\r\n";

						} else {
							output += "\t\t" "void set_ " + o.name + "_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value);\r\n";
						}
					}

					if(p.is_derived) {

					} else if(p.is_bitfield) {
						if(!p.hook_get) {
							output += "\t\t" "DCON_RELEASE_INLINE bool get_ " + o.name + "_" + p.name + "(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn dcon::bit_vector_test(" + o.name + ".m_" + p.name + ".vptr()[id.index()]);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type get_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(" + con_tags_type + "<int32_t>(id.value), " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type get_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::vbitfield_type get_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(id.value, " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";
						}
						if(!p.hook_set) {
							output += "\t\t" "DCON_RELEASE_INLINE void set_ " + o.name + "_" + p.name + "(" + id_name + " id, bool value) {\r\n";
							output += "\t\t\tdcon::bit_vector_set(" + o.name + ".m_" + p.name + ".vptr(), id.index(), value);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
								"ve::vbitfield_type values) noexcept (\r\n";
							output += "\t\t\tve::store(" + con_tags_type + "<int32_t>(id.value), " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
								"ve::vbitfield_type values) noexcept (\r\n";
							output += "\t\t\tve::store(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
								"ve::vbitfield_type values) noexcept (\r\n";
							output += "\t\t\tve::store(id.value, " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";
						}
					} else if(p.is_object) {
						if(!p.hook_get) {
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "const& get_ " + o.name + "_" + p.name + "(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& get_ " + o.name + "_" + p.name + "(" + id_name + " id) noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";
						}
						if(!p.hook_set) {
							output += "\t\tDCON_RELEASE_INLINE void set_ " + o.name + "_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value) noexcept {\r\n";
							output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\r\n";
							output += "\t\t)\r\n";
						}
					} else if(p.is_special_vector) {

						if(!p.hook_get) {
							output += "\t\tstd::pair<" + p.data_type + "*, " + p.data_type + "*> get_" + o.name + "_" + p.name + "_range(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn dcon::get_range(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\r\n";
							output += "\t\t}\r\n";

							output += "\t\t" + p.data_type + "& get_" + o.name + "_" + p.name + "_at(" + id_name + " id, uint32_t inner_index) const noexcept {\r\n";
							output += "\t\t\treturn dcon::get(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], inner_index);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tuint32_t get_" + o.name + "_" + p.name + "_capacity(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn dcon::get_capacity(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tuint32_t get_" + o.name + "_" + p.name + "_size(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn dcon::get_size(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tbool " + o.name + "_" + p.name + "_contains(" + id_name + " id, " + p.data_type + " obj) const noexcept {\r\n";
							output += "\t\t\treturn dcon::contains_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\r\n";
							output += "\t\t}\r\n";
						}
						if(!p.hook_set) {
							output += "\t\tvoid " + o.name + "_" + p.name + "_push_back(" + id_name + " id, " + p.data_type + " obj) noexcept {\r\n";
							output += "\t\t\treturn dcon::push_back(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tvoid " + o.name + "_" + p.name + "_pop_back(" + id_name + " id) noexcept {\r\n";
							output += "\t\t\treturn dcon::pop_back(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()]);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tvoid " + o.name + "_" + p.name + "_add_unique(" + id_name + " id, " + p.data_type + " obj) noexcept {\r\n";
							output += "\t\t\treturn dcon::add_unique_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\r\n";
							output += "\t\t}\r\n";

							output += "\t\tvoid " + o.name + "_" + p.name + "_remove_unique(" + id_name + " id, " + p.data_type + " obj) noexcept {\r\n";
							output += "\t\t\treturn dcon::remove_unique_item(" + o.name + "." + p.name + "_storage, " + o.name + ".m_" + p.name + ".vptr()[id.index()], obj);\r\n";
							output += "\t\t}\r\n";
						}
					} else if(is_vectorizable_type(parsed_file, p.data_type)) {
						if(!p.hook_get) {
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "const& get_ " + o.name + "_" + p.name + "(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& get_ " + o.name + "_" + p.name + "(" + id_name + " id) noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(" + con_tags_type + "<int32_t>(id.value), " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE ve::value_to_vector_type<" + p.data_type + "> get_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id) const noexcept (\r\n";
							output += "\t\t\treturn ve::load(id.value, " + o.name + ".m_" + p.name + ".vptr());\r\n";
							output += "\t\t)\r\n";
						}
						if(!p.hook_set) {
							output += "\t\tDCON_RELEASE_INLINE void set_ " + o.name + "_" + p.name + "(" + id_name + " id, " + p.data_type + " value) noexcept {\r\n";
							output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(" + con_tags_type + "<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> values) noexcept (\r\n";
							output += "\t\t\tve::store(" + con_tags_type + "<int32_t>(id.value), " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> values) noexcept (\r\n";
							output += "\t\t\tve::store(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";

							output += "\t\tDCON_RELEASE_INLINE " "void set_ " + o.name + "_" + p.name + "(ve::tagged_vector<" + id_name + "> id, "
								"ve::value_to_vector_type<" + p.data_type + "> values) noexcept (\r\n";
							output += "\t\t\tve::store(id.value, " + o.name + ".m_" + p.name + ".vptr(), values);\r\n";
							output += "\t\t)\r\n";
						}
					} else { // nonvectorizable data type w/o special handling
						if(!p.hook_get) {
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "const& get_ " + o.name + "_" + p.name + "(" + id_name + " id) const noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";
							output += "\t\tDCON_RELEASE_INLINE " + p.data_type + "& get_ " + o.name + "_" + p.name + "(" + id_name + " id) noexcept {\r\n";
							output += "\t\t\treturn " + o.name + ".m_" + p.name + ".vptr()[id.index()];\r\n";
							output += "\t\t)\r\n";
						}
						if(!p.hook_set) {
							output += "\t\tDCON_RELEASE_INLINE void set_ " + o.name + "_" + p.name + "(" + id_name + " id, " + p.data_type + " const& value) noexcept {\r\n";
							output += "\t\t\t" + o.name + ".m_" + p.name + ".vptr()[id.index()] = value;\r\n";
							output += "\t\t)\r\n";
						}
					}
				} // end loop over each property

				output += "\r\n";

				// creation / deletion / move hook routines
				if(o.hook_create) {
					output += "\t\tvoid on_create_" + o.name + "(" + id_name + " id);\r\n";
				}
				if(o.hook_delete) {
					output += "\t\tvoid on_delete_" + o.name + "(" + id_name + " id);\r\n";
				}
				if(o.hook_move) {
					output += "\t\tvoid on_move_" + o.name + "(" + id_name + " new_id," + id_name + " old_id);\r\n";
				}

				output += "\t\tuint32_t " + o.name + "_size() const noexcept { return " + o.name + ".size_used; }\r\n";

				// creation / deletion stubs
				
				if(!o.is_relationship) {
					if(o.store_type == storage_type::contiguous) {
						output += "\t\tvoid " + o.name + "_pop_back();\r\n";
						output += "\t\tvoid " + o.name + "_resize(uint32_t new_size);\r\n";
						output += "\t\t" + id_name + " create_" + o.name + "();\r\n";
						output += "\t\tbool is_valid_" + o.name + "(" + id_name + " id) const;\r\n";
					} else if(o.store_type == storage_type::erasable) {
						output += "\t\tvoid delete_" + o.name + "(" + id_name + " id);\r\n";
						output += "\t\t" + id_name + " create_" + o.name + "();\r\n";
						output += "\t\tvoid " + o.name + "_resize(uint32_t new_size);\r\n";
						output += "\t\tbool is_valid_" + o.name + "(" + id_name + " id) const;\r\n";
					} else if(o.store_type == storage_type::compactable) {
						output += "\t\tvoid delete_" + o.name + "(" + id_name + " id);\r\n";
						output += "\t\t" + id_name + " create_" + o.name + "();\r\n";
						output += "\t\tvoid " + o.name + "_resize(uint32_t new_size);\r\n";
						output += "\t\tbool is_valid_" + o.name + "(" + id_name + " id) const;\r\n";
					}
				} else {
					output += "\t\tvoid " + o.name + "_resize(uint32_t sz);\r\n";
					output += "\t\tvoid delete_" + o.name + "(" + id_name + " id);\r\n";
					output += "\t\tbool is_valid_" + o.name + "(" + id_name + " id) const;\r\n";
					output += "\t\tvoid internal_move_relationship_" + o.name + "(" + id_name + " old_id, " + id_name + " new_id);\r\n";
					output += "\t\t" + id_name + " try_create_" + o.name + "(" + make_relationship_parameters(o) + ");\r\n";
					output += "\t\t" + id_name + " force_create_" + o.name + "(" + make_relationship_parameters(o) + ");\r\n";
				}
				
				output += "\r\n";

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

						output += "\t\tDCON_RELEASE_INLINE " + id_name + " get_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn id;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\r\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
						output += "\t\t\t\tresult.set(uint32_t(i), id[i]);\r\n";
						output += "\t\t\treturn result;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\r\n";
						output += "\t\t\tfor(uint32_t i = 0; i < id.subcount; ++i)\r\n";
						output += "\t\t\t\tresult.set(i, id[i]);\r\n";
						output += "\t\t\treturn result;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn id;\r\n";
						output += "\t\t)\r\n";

						// setter in relationship

						output += "\t\tvoid set_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\r\n";
						output += "\t\t\tif(value) {\r\n";
						output += "\t\t\tdelete_" + r.name + "(value);\r\n";
						output += "\t\t\tinternal_move_relationship" + r.name + "(id, value);\r\n";
						output += "\t\t\t} else {\r\n";
						output += "\t\t\tdelete_" + r.name + "(id);\r\n";
						output += "\t\t\t}\r\n";
						output += "\t\t)\r\n";

						// getter in related object

						output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(" + id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn id;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(" + con_tags_type + "<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\r\n";
						output += "\t\t\tfor(int32_t i = 0; i < ve::vector_size; ++i)\r\n";
						output += "\t\t\t\tresult.set(uint32_t(i), id[i]);\r\n";
						output += "\t\t\treturn result;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\tve::tagged_vector<" + relation_id_name + "> result;\r\n";
						output += "\t\t\tfor(uint32_t i = 0; i < id.subcount; ++i)\r\n";
						output += "\t\t\t\tresult.set(i, id[i]);\r\n";
						output += "\t\t\treturn result;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(ve::tagged_vector<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn id;\r\n";
						output += "\t\t)\r\n";

						// setter in related object

						output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\r\n";
						output += "\t\t\tif(auto id = " + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]; bool(id))\r\n";
						output += "\t\t\t\tdelete_" + r.name + "(id);\r\n";
						output += "\t\t)\r\n";
					} else if(i.index == index_type::at_most_one) {
						// first: getter in the relationship itself

						const std::string id_name = i.type_name + "_id";
						const std::string con_tags_type = i.related_to->is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

						output += "\t\tDCON_RELEASE_INLINE " + id_name + " get_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(" + relation_con_tags_type + "<int32_t>(id.value), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(id.value, " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						// second: setter in the relationship itself

						output += "\t\tvoid set_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\r\n";
						output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value))\r\n";
						output += "\t\t\t\t" + r.name + ".m_link_back_" + i.property_name + ".vptr()[old_value].index()] = " + relation_id_name + "();\r\n";
						output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\r\n";
						output += "\t\t\tif(value) {\r\n";
						output += "\t\t\t\tif(" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()])\r\n";
						output += "\t\t\t\t\tdelete_" + r.name + "(" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]);\r\n";
						output += "\t\t\t\t" + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()] = id;\r\n";
						output += "\t\t\t}\r\n";
						output += "\t\t)\r\n";

						// third: getter in the object related to

						output += "\t\tDCON_RELEASE_INLINE " + relation_id_name + " get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(" + id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn " + r.name + ".m_link_back_" + i.property_name + ".vptr()[id.index()];\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(" + con_tags_type + "<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(" + con_tags_type + "<int32_t>(id.value), " + r.name + ".m_link_back_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(ve::partial_contiguous_tags<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + r.name + ".m_link_back_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + relation_id_name + "> get_ " + i.type_name + "_" + r.name + "_as_" + i.property_name +
							"(ve::tagged_vector<" + id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(id.value, " + r.name + ".m_link_back_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						// fourth: setter in the object related to

						output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_remove_" +  r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\r\n";
						output += "\t\t\tif(auto id = " + r.name + ".m_link_back_" + i.property_name + ".vptr()[value.index()]; bool(id))\r\n";
						output += "\t\t\t\tdelete_" + r.name + "(id);\r\n";
						output += "\t\t)\r\n";

					} else if(i.index == index_type::many) {
						// first: getter in the relationship itself

						const std::string id_name = i.type_name + "_id";
						const std::string con_tags_type = i.related_to->is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags";

						output += "\t\tDCON_RELEASE_INLINE " + id_name + " get_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(" + relation_con_tags_type + "<int32_t>(id.value), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(id.value, " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						// second: setter in the relationship itself

						output += "\t\tvoid set_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\r\n";
						
						if(i.ltype == list_type::list) {
							output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\r\n";
							output += "\t\t\t\tif(auto old_left = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left; bool(old_left)) {\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[old_left.index()].right = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right;\r\n";
							output += "\t\t\t\t} else {\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_head_back_" + i.property_name + ".vptr()[old_value.index()] = m_link_" + i.property_name + ".vptr()[id.index()].right;\r\n";
							output += "\t\t\t\t}\r\n";
							output += "\t\t\t\tif(auto old_right = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right; bool(old_right))\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[old_right.index()].left = " + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left;\r\n";
							output += "\t\t\t\t}\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t\tif(value) {\r\n";
							output += "\t\t\t\tif(auto existing_list = " + r.name + ".m_head_back_" + i.property_name + ".vptr()[value.index()]]; bool(existing_list)) {\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = existing_list;\r\n";
							output += "\t\t\t\t\tif(auto r = " + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right; bool(r)) {\r\n";
							output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = r;\r\n";
							output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[r.index()].left = id;\r\n";
							output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right = id;\r\n";
							output += "\t\t\t\t\t} else {\r\n";
							output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name +"();\r\n";
							output += "\t\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[existing_list.index()].right = id;\r\n";
							output += "\t\t\t\t\t}\r\n";
							output += "\t\t\t\t} else {\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_head_back_" + i.property_name + ".vptr()[value.index()]] = id;\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name +"();\r\n";
							output += "\t\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = " + relation_id_name +"();\r\n";
							output += "\t\t\t\t}\r\n";
							output += "\t\t\t} else {\r\n";
							output += "\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].right = " + relation_id_name +"();\r\n";
							output += "\t\t\t\t" + r.name + ".m_link_" + i.property_name + ".vptr()[id.index()].left = " + relation_id_name +"();\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\r\n";
						} else if(i.ltype == list_type::array) {
							output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\r\n";
							output += "\t\t\t\tauto vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[old_value.index()];\r\n";
							output += "\t\t\t\tdcon::remove_unique_item(" + r.name + "." + i.property_name + "_storage, vref, id)\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t\tif(value)\r\n";
							output += "\t\t\t\tdcon::push_back(" + r.name + "." + i.property_name + "_storage, " + r.name + ".m_array_" + i.property_name + ".vptr()[value.index()], id);\r\n";
							output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\r\n";
						} else if(i.ltype == list_type::std_vector) {
							output += "\t\t\tif(auto old_value = " + r.name + ".m_" + i.property_name + ".vptr()[id.index()]; bool(old_value)) {\r\n";
							output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[old_value.index()];\r\n";
							output += "\t\t\t\tif(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {\r\n";
							output += "\t\t\t\t\t*it = vref.back();\r\n";
							output += "\t\t\t\t\tvref.pop_back();\r\n";
							output += "\t\t\t\t}\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t\tif(value)\r\n";
							output += "\t\t\t\t" + r.name + ".m_array_" + i.property_name + ".vptr()[value.index()].push_back(id);\r\n";
							output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\r\n";
						}
						
						output += "\t\t)\r\n";

						// third: getter in the object related to

						output += "\t\ttemplate<typename T>\r\n";
						output += "\t\tDCON_RELEASE_INLINE void " + i.type_name + "_for_each_"  + r.name + "_as_" + i.property_name + "("
							+ id_name + " id, T func) const {\r\n";

						if(i.ltype == list_type::list) {
							output += "\t\t\tif(bool(id)) {\r\n";
							output += "\t\t\t\tfor(auto list_pos = " + r.name + ".m_head_back_" + i.property_name + ".vptr()[id.index()]; "
								+ "bool(list_pos); list_pos = " + r.name + ".m_link_" + i.property_name + ".vptr()[list_pos.index()].right) {\r\n";
							output += "\t\t\t\t\tfunc(list_pos);";
							output += "\t\t\t\t}\r\n";
							output += "\t\t\t}\r\n";

						} else if(i.ltype == list_type::array) {
							output += "\t\t\tif(bool(id)) {\r\n";
							output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
								+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\r\n";
							output += "\t\t\t\tstd::for_each(vrange.first, vrange.second, func);\r\n";
							output += "\t\t\t}\r\n";
						} else if(i.ltype == list_type::std_vector) {
							output += "\t\t\tif(bool(id)) {\r\n";
							output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\r\n";
							output += "\t\t\t\tstd::for_each(vref.begin(), vref.end(), func);\r\n";
							output += "\t\t\t}\r\n";
						}
						output += "\t\t}\r\n";


						if(i.ltype == list_type::array) {
							output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
								+ i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) const {\r\n";
							output += "\t\t\tif(bool(id)) {\r\n";
							output += "\t\t\t\tauto vrange = dcon::get_range(" + r.name + "." + i.property_name + "_storage, "
								+ r.name + ".m_array_" + i.property_name + ".vptr()[id.index()]);\r\n";
							output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(vrange.first, vrange.second);\r\n";
							output += "\t\t\t} else {\r\n";
							output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t}\r\n";
						} else if(i.ltype == list_type::std_vector) {
							output += "\t\tDCON_RELEASE_INLINE std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*> "
								+ i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) const {\r\n";
							output += "\t\t\tif(bool(id)) {\r\n";
							output += "\t\t\t\tauto& vref = " + r.name + ".m_array_" + i.property_name + ".vptr()[id.index()];\r\n";
							output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name 
								+ " const*>(&(*vrange.begin()), &(*vrange.end()));\r\n";
							output += "\t\t\t} else {\r\n";
							output += "\t\t\t\treturn std::pair<" + relation_id_name + " const*, " + relation_id_name + " const*>(nullptr, nullptr);\r\n";
							output += "\t\t\t}\r\n";
							output += "\t\t}\r\n";
						}

						// fourth: setter in the object related to

						output += "\t\tvoid " + i.type_name + "_remove_all_" + r.name + "_as_" + i.property_name + "(" + id_name + " id) noexcept {\r\n";
						if(i.ltype == list_type::array || i.ltype == list_type::std_vector) {
							output += "\t\t\tauto rng = " + i.type_name + "_range_of_" + r.name + "_as_" + i.property_name + "(id);\r\n";
							output += "\t\t\tstd::vector<" + relation_id_name + "> temp(rng.first, rng.second);\r\n";
							output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\r\n";
						} else {
							output += "\t\t\tstd::vector<" + relation_id_name + "> temp;\r\n";
							output += "\t\t\t" + i.type_name + "_for_each_" + r.name + "_as_" + i.property_name + 
								"(id, [&](" + relation_id_name + " j) { temp.push_back(j); });\r\n";
							output += "\t\t\tstd::for_each(temp.begin(), temp.end(), [t = this](" + relation_id_name + " i) { t->delete_" + r.name + "(i); });\r\n";
						}
						output += "\t\t)\r\n";

					} else if(i.index == index_type::none) {
						// first: getter in the relationship itself

						const std::string id_name = i.type_name + "_id";

						output += "\t\tDCON_RELEASE_INLINE " + id_name + " get_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id) const noexcept {\r\n";
						output += "\t\t\treturn " + r.name + ".m_" + i.property_name + ".vptr()[id.index()];\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(" + relation_con_tags_type + "<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(" + relation_con_tags_type + "<int32_t>(id.value), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::partial_contiguous_tags<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE ve::tagged_vector<" + id_name + "> get_ " + r.name + "_" + i.property_name + "(ve::tagged_vector<" + relation_id_name + "> id) const noexcept (\r\n";
						output += "\t\t\treturn ve::load(id.value, " + r.name + ".m_" + i.property_name + ".vptr());\r\n";
						output += "\t\t)\r\n";

						// second: setter in the relationship itself

						output += "\t\tDCON_RELEASE_INLINE void set_ " + r.name + "_" + i.property_name + "(" + relation_id_name + " id, " + id_name + " value) noexcept {\r\n";
						output += "\t\t\t" + r.name + ".m_" + i.property_name + ".vptr()[id.index()] = value;\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE " "void set_ " + r.name + "_" + i.property_name + "(" + relation_con_tags_type + "<" + id_name + "> id, "
							"ve::tagged_vector<" + id_name + "> values) noexcept (\r\n";
						output += "\t\t\tve::store(" + relation_con_tags_type + "<int32_t>(id.value), " + r.name + ".m_" + i.property_name + ".vptr(), values);\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE " "void set_ " + r.name + "_" + i.property_name + "(ve::partial_contiguous_tags<" + id_name + "> id, "
							"ve::tagged_vector<" + id_name + "> values) noexcept (\r\n";
						output += "\t\t\tve::store(ve::partial_contiguous_tags<int32_t>(id.value, id.subcount), " + r.name + ".m_" + i.property_name + ".vptr(), values);\r\n";
						output += "\t\t)\r\n";

						output += "\t\tDCON_RELEASE_INLINE " "void set_ " + r.name + "_" + i.property_name + "(ve::tagged_vector<" + id_name + "> id, "
							"ve::tagged_vector<" + id_name + "> values) noexcept (\r\n";
						output += "\t\t\tve::store(id.value, " + r.name + ".m_" + i.property_name + ".vptr(), values);\r\n";
						output += "\t\t)\r\n";
					}// end -- creation of property references getters / setters

				} //end of loop creating individual property getters / setters
			} // end creating relationship getters / setters

			output += "\r\n";

			// creation / deletion reoutines
			for(auto& co : parsed_file.relationship_objects) {
				const std::string id_name = co.name + "_id";

				if(!co.is_relationship) {
					if(co.store_type == storage_type::contiguous || co.store_type == storage_type::compactable) {
						// pop_back
						output += "\t\tvoid " + co.name + "_pop_back() {\r\n";
						output += "\t\t\tif(" + co.name + ".size_used > 0) {\r\n";

						output += "\t\t\t\t" + id_name + " id_removed(" + co.name + ".size_used - 1);\r\n";
						if(co.hook_delete)
							output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\r\n";

						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\r\n";
								output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used - 1;\r\n";
								if(co.is_expandable) {
									for(auto& rp : cr.rel_ptr->properties) {
										if(rp.is_special_vector) {
											output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\r\n";
										} else if(rp.is_bitfield) {
											output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." +  "vptr()" + ", id_removed.index(), false);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\r\n";
										}
										if(!rp.is_bitfield && !rp.is_derived) {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\r\n";
										}
									}
									for(auto& ri : cr.rel_ptr->indexed_objects) {
										if(ri.related_to == cr.rel_ptr->primary_key) {
										} else {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.pop_back();\r\n";
										}
										if(ri.ltype == list_type::list && ri.index == index_type::many) {
											output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.pop_back();\r\n";
										}
									}
								} else {
									for(auto& rp : cr.rel_ptr->properties) {
										if(rp.is_derived) {
										} else if(rp.is_special_vector) {
											output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\r\n";
										} else if(rp.is_bitfield) {
											output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + ".vptr(), id_removed.index(), false);\r\n";
										} else {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + rp.data_type + "{};\r\n";
										}
									}
								}
							} else if(cr.indexed_as == index_type::at_most_one) {
								output += "\t\t\t\t" + co.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\r\n";
								if(co.is_expandable) {
									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.pop_back();\r\n";
								}
							} else if(cr.indexed_as == index_type::many) {
								output += "\t\t\t\t" + co.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\r\n";
								if(co.is_expandable) {
									if(cr.listed_as == list_type::list) {
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.pop_back();\r\n";
									} else if(cr.listed_as == list_type::array) {
										output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\r\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\r\n";
									} else if(cr.listed_as == list_type::std_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\r\n";
									}
								}
							}
						}
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\r\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), false);\r\n";
								if(co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\r\n";
							} else {
								if(!co.is_expandable)
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\r\n";
							}

							if(co.is_expandable && !cp.is_bitfield && !cp.is_derived) {
								output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\r\n";
							}
						}
						output += "\t\t\t\t--" + co.name + ".size_used;\r\n";
						output += "\t\t\t}\r\n";
						output += "\t\t}\r\n";

						//resize
						output += "\t\tvoid " + co.name + "_resize(uint32_t new_size) {\r\n";
						output += "\t\t\tconst uint32_t old_size = " + co.name + ".size_used;\r\n";
						output += "\t\t\tif(" + co.name + ".size_used < ) {\r\n"; // contracting

						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {

							} else if(cr.indexed_as == index_type::at_most_one) {
								if(!co.is_expandable)
									output += "\t\t\t\tstd::fill_n(" + cr.relation_name + ".m_link_back_" + cr.property_name
										+ ".vptr() + new_size, old_size - new_size, " + cr.relation_name + "_id());\r\n";
							} else if(cr.indexed_as == index_type::many) {
								if(cr.listed_as == list_type::list) {
									if(!co.is_expandable)
										output += "\t\t\t\tstd::fill_n(" + cr.relation_name + ".m_head_back_" + cr.property_name
										+ ".vptr() + new_size, old_size - new_size, " + cr.relation_name + "_id());\r\n";
								} else if(cr.listed_as == list_type::array) {
									output += "\t\t\t\tstd::for_each(" + cr.relation_name + ".m_" + cr.property_name + ".vptr() + new_size, "
										+ cr.relation_name + ".m_" + cr.property_name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->"
										+ cr.relation_name + "." + cr.property_name + "_storage.release(i); });\r\n";
								} else if(cr.listed_as == list_type::std_vector) {
									if(!co.is_expandable)
										output += "\t\t\t\tstd::fill_n(" + cr.relation_name + ".m_" + cr.property_name + ".vptr() + new_size, old_size - new_size, std::vector<" + cr.relation_name + " _id>());\r\n";
								}

							}
						}
						for(auto& cp : co.properties) {
							if(cp.is_derived) {
							} else if(cp.is_special_vector) {
								output += "\t\t\t\tstd::for_each(" + co.name + ".m_" + cp.name + ".vptr() + new_size, "
									+ co.name + ".m_" + cp.name + ".vptr() + old_size, [t = this](dcon::stable_mk_2_tag& i){ t->" + co.name + "."
									+ cp.name + "_storage.release(i); });\r\n";
								
								output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\r\n";
							} else if(cp.is_bitfield) {
								output += "\t\t\t\tfor(uint32_t i = new_size; i < 8*(((new_size + 7)/8)); ++i)\r\n";
								output += "\t\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), i, false);\r\n";
								if(!co.is_expandable)
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + (new_size + 7) / 8, (old_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});\r\n";
							} else {
								if(!co.is_expandable)
									output += "\t\t\t\tstd::fill_n(" + co.name + ".m_" + cp.name + ".vptr() + new_size, old_size - new_size, " + cp.data_type + "{});\r\n";
							}
						}

						output += "\t\t\t} else {\r\n"; //expanding
						output += "\t\t\t}\r\n";

						//both
						if(co.is_expandable) {
							for(auto& cr : co.relationships_involved_in) {
								if(cr.as_primary_key) {
									output += "\t\t\t\t" + cr.relation_name + ".resize(new_size);\r\n";
								} else if(cr.indexed_as == index_type::at_most_one) {
									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.resize(1 + new_size);\r\n";
								} else if(cr.indexed_as == index_type::many) {
									if(cr.listed_as == list_type::list) {
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.resize(1 + new_size);\r\n";
									} else if(cr.listed_as == list_type::array) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\r\n";
									} else if(cr.listed_as == list_type::std_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.resize(1 + new_size);\r\n";
									}
									
								}
							}
							for(auto& cp : co.properties) {
								if(cp.is_derived) {
								} else if(cp.is_special_vector) {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());\r\n";
								} else if(cp.is_bitfield) {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (new_size + 7) / 8);\r\n";
								} else {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + new_size);\r\n";
								}
							}
						} else {
							for(auto& cr : co.relationships_involved_in) {
								if(cr.as_primary_key) {
									output += "\t\t\t\t" + cr.relation_name + ".resize(new_size);\r\n";
								}
							}
						}
						output += "\t\t\t" + co.name + ".size_used = new_size; {\r\n";
						output += "\t\t}\r\n";

						if(co.store_type == storage_type::compactable) {
							//delete
							output += "\t\tvoid delete_" + co.name + "(" + id_name + " id) {\r\n";
							output += "\t\t\t\t" + id_name + " id_removed = id;\r\n";
							output += "\t\t\t\t" + id_name + " last_id(" + co.name + ".size_used - 1);\r\n";

							if(co.hook_delete)
								output += "\t\t\t\ton_delete_" + co.name + "(id_removed);\r\n";

							for(auto& cr : co.relationships_involved_in) {
								if(cr.as_primary_key) {
									output += "\t\t\t\tdelete_" + cr.relation_name + "(id_removed);\r\n";
									output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used - 1;\r\n";
									
									for(auto& rp : cr.rel_ptr->properties) {
										if(rp.is_derived) {
										} else if(rp.is_special_vector) {
											output += "\t\t\t\t" + cr.relation_name + "." + rp.name + "_storage.release(" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()]);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()];\r\n";
											if(co.is_expandable)
												output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\r\n";
											else
												output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();\r\n";
										} else if(rp.is_bitfield) {
											output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", id_removed.index(), "
												+ "dcon::bit_vector_get(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", last_id.index()));\r\n";
											output += "\t\t\t\tdcon::bit_vector_set(" + cr.relation_name + ".m_" + rp.name + "." + "vptr()" + ", last_id.index(), false);\r\n";
											if(co.is_expandable)
												output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\r\n";
										} else {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[id_removed.index()] = std::move(" 
												+ cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()]);\r\n";
											if(co.is_expandable)
												output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.pop_back();\r\n";
											else
												output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".vptr()[last_id.index()] = " + rp.data_type + "{};\r\n";
										}
									}
									for(auto& ri : cr.rel_ptr->indexed_objects) {
										if(ri.related_to == cr.rel_ptr->primary_key) {
										} else {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_" + ri.property_name + ".vptr()[last_id.index()];\r\n";
											if(co.is_expandable)
												output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.pop_back();\r\n";
											else
												output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".vptr()[last_id.index()] = " + ri.property_name + "_id();\r\n";
										}
										if(ri.ltype == list_type::list && ri.index == index_type::many) {
											output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[id_removed.index()] = " + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[last_id.index()];\r\n";
											if(co.is_expandable)
												output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.pop_back();\r\n";
											else
												output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".vptr()[last_id.index()] = " + ri.property_name + "_id_pair();\r\n";
										}
									}
								} else if(cr.indexed_as == index_type::at_most_one) {
									output += "\t\t\t\t" + co.name + "_remove_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed));\r\n";

									// TODO renumber last_item id

									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
										+ cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[last_id.index()];\r\n";
									if(co.is_expandable) {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.pop_back();\r\n";
									} else {
										output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".vptr()[last_id.index()] = " + cr.relation_name + "_id();\r\n";
									}
								} else if(cr.indexed_as == index_type::many) {
									output += "\t\t\t\t" + co.name + "_remove_all_" + cr.relation_name + "_as_" + cr.property_name + "(id_removed);\r\n";

									// TODO renumber last_item id

									if(co.is_expandable) {
										if(cr.listed_as == list_type::list) {
											output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
												+ cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()];\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.pop_back();\r\n";
										} else if(cr.listed_as == list_type::array) {
											output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = "
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()];\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\r\n";
										} else if(cr.listed_as == list_type::std_vector) {
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = std::move("
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()]);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.pop_back();\r\n";
										}
									} else {
										if(cr.listed_as == list_type::list) {
											output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[id_removed.index()] = "
												+ cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()];\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".vptr()[last_id.index()] = " 
												+ cr.relation_name +"_id_pair();\r\n";
										} else if(cr.listed_as == list_type::array) {
											output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = "
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()];\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();\r\n";
										} else if(cr.listed_as == list_type::std_vector) {
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()] = std::move("
												+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()]);\r\n";
											output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[last_id.index()].empty();\r\n";
										}
									}
								}
							}
							for(auto& cp : co.properties) {
								if(cp.is_derived) {
								} else if(cp.is_special_vector) {
									output += "\t\t\t\t" + co.name + "." + cp.name + "_storage.release(" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()]);\r\n";
									output += "\t\t\t\t"+ co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " 
										+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()];\r\n";
									if(co.is_expandable)
										output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\r\n";
									else
										output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = "
											+ "std::numeric_limits<dcon::stable_mk_2_tag>::max();\r\n";
								} else if(cp.is_bitfield) {
									output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), id_removed.index(), "
										+ "dcon::bit_vector_get(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index()));\r\n";
									output += "\t\t\t\tdcon::bit_vector_set(" + co.name + ".m_" + cp.name + ".vptr(), last_id.index(), false);\r\n";
									if(co.is_expandable)
										output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 6) / 8);\r\n";
										
								} else {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = std::move("
										+ co.name + ".m_" + cp.name + ".vptr()[last_id.index()]);\r\n";
									if(co.is_expandable)
										output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.pop_back();\r\n";
									else
										output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".vptr()[id_removed.index()] = " + cp.data_type + "{};\r\n";
								}
							}
							output += "\t\t\t\t--" + co.name + ".size_used;\r\n";
							output += "\t\t\t}\r\n";

							output += "\t\t}\r\n";
						}

						//create
						output += "\t\t" + id_name + " create_" + co.name + "() {\r\n";
						output += "\t\t\t" + id_name + " new_id(" + co.name + ".size_used);\r\n";

						
						for(auto& cr : co.relationships_involved_in) {
							if(cr.as_primary_key) {
								output += "\t\t\t\t" + cr.relation_name + ".size_used = " + co.name + ".size_used + 1;\r\n";
								if(co.is_expandable) {
									for(auto& rp : cr.rel_ptr->properties) {
										if(rp.is_bitfield) {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.resize(1 + (" + co.name + ".size_used + 8) / 8);\r\n";
										}
										if(!rp.is_bitfield && !rp.is_derived) {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + rp.name + ".values.emplace_back();\r\n";
										}
									}
									for(auto& ri : cr.rel_ptr->indexed_objects) {
										if(ri.related_to == cr.rel_ptr->primary_key) {
										} else {
											output += "\t\t\t\t" + cr.relation_name + ".m_" + ri.property_name + ".values.emplace_back();\r\n";
										}
										if(ri.ltype == list_type::list && ri.index == index_type::many) {
											output += "\t\t\t\t" + cr.relation_name + ".m_link_" + ri.property_name + ".values.emplace_back();\r\n";
										}
									}
								}
							} else if(cr.indexed_as == index_type::at_most_one) {
								if(co.is_expandable) {
									output += "\t\t\t\t" + cr.relation_name + ".m_link_back_" + cr.property_name + ".values.emplace_back();\r\n";
								}
							} else if(cr.indexed_as == index_type::many) {
								if(co.is_expandable) {
									if(cr.listed_as == list_type::list) {
										output += "\t\t\t\t" + cr.relation_name + ".m_head_back_" + cr.property_name + ".values.emplace_back();\r\n";
									} else if(cr.listed_as == list_type::array) {
										output += "\t\t\t\t" + cr.relation_name + "." + cr.property_name + "_storage.release("
											+ cr.relation_name + ".m_array_" + cr.property_name + ".vptr()[id_removed.index()]);\r\n";
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.emplace_back();\r\n";
									} else if(cr.listed_as == list_type::std_vector) {
										output += "\t\t\t\t" + cr.relation_name + ".m_array_" + cr.property_name + ".values.emplace_back();\r\n";
									}
								}
							}
						}
						if(co.is_expandable) {
							for(auto& cp : co.properties) {
								if(cp.is_bitfield) {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.resize(1 + (" + co.name + ".size_used + 8) / 8);\r\n";
								} else if(!cp.is_derived) {
									output += "\t\t\t\t" + co.name + ".m_" + cp.name + ".values.emplace_back();\r\n";
								}
							}
						}

						output += "\t\t\t++" + co.name + ".size_used;\r\n";
						if(co.hook_create)
							output += "\t\t\t\ton_create_" + co.name + "(id_removed);\r\n";
						output += "\t\t\treturn new_id;\r\n";
						output += "\t\t}\r\n";

						output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const {\r\n";
						output += "\t\t\treturn bool(id) && uint32_t(i.value) <= " + co.name + ".size_used;\r\n";
						output += "\t\t}\r\n";
					} else if(co.store_type == storage_type::erasable) {
						output += "\t\tvoid delete_" + co.name + "(" + id_name + " id);\r\n";
						output += "\t\t" + id_name + " create_" + co.name + "();\r\n";
						output += "\t\tvoid " + co.name + "_resize(uint32_t new_size);\r\n";
						output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const;\r\n";
					}
				} else {
					output += "\t\tvoid " + co.name + "_resize(uint32_t sz);\r\n";
					output += "\t\tvoid delete_" + co.name + "(" + id_name + " id);\r\n";
					output += "\t\tbool is_valid_" + co.name + "(" + id_name + " id) const;\r\n";
					output += "\t\tvoid internal_move_relationship_" + co.name + "(" + id_name + " old_id, " + id_name + " new_id);\r\n";
					output += "\t\t" + id_name + " try_create_" + co.name + "(" + make_relationship_parameters(co) + ");\r\n";
					output += "\t\t" + id_name + " force_create_" + co.name + "(" + make_relationship_parameters(co) + ");\r\n";
				}
			} // end creation / deletion reoutines creation loop

			//class data_container end
			output += "\t};\r\n\r\n";
		}

		//close new namespace
		output += "}\r\n";

		output += "\r\n";


		output += "#undef DCON_RELEASE_INLINE\r\n";

		//newline at end of file
		output += "\r\n";
	}
}
