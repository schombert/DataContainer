#pragma once

#include <string>
#include <vector>
#include <algorithm>

inline std::string extract_string(char const* & input, char const* end) {
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
enum class storage_type { contiguous, erasable, compactable };

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

inline relationship_object_def* find_by_name(file_def& def, std::string const& name) {
	if(auto r = std::find_if(
		def.relationship_objects.begin(), def.relationship_objects.end(),
		[&name](relationship_object_def const& o) { return o.name == name; }); r != def.relationship_objects.end()) {
		return &(*r);
	}
	return nullptr;
}

inline std::string make_relationship_parameters(relationship_object_def const& o) {
	std::string result;
	for(auto& i : o.indexed_objects) {
		if(result.length() != 0)
			result += ", ";
		result += i.type_name + "_id " + i.property_name + "_p";
	}
	return result;
}

inline void process_data_type(std::string &second_term, property_def * last_prop, const char * &str_ptr, const char *const &str_end) {
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

inline bool is_vectorizable_type(file_def& def, std::string const& name) {
	return name == "char" || name == "int" || name == "short" || name == "unsigned short" ||
		name == "unsigned int" || name == "unsigned char" || name == "signed char" ||
		name == "float" || name == "int8_t" || name == "uint8_t" ||
		name == "int16_t" || name == "uint16_t" || name == "int32_t" || name == "uint32_t"
		|| [&]() {
		return name.length() >= 4 && name[name.length() - 1] == 'd' && name[name.length() - 2] == 'i' &&
			name[name.length() - 3] == '_' && find_by_name(def, name.substr(0, name.length() - 3)) != nullptr;
	}();
}

inline std::vector<std::string> common_types{ std::string("int8_t"), std::string("uint8_t"), std::string("int16_t"), std::string("uint16_t")
	, std::string("int32_t"), std::string("uint32_t"), std::string("int64_t"), std::string("uint64_t"), std::string("float"), std::string("double") };

inline std::string normalize_type(std::string in) {
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

inline bool is_common_type(std::string in) {
	return std::find(common_types.begin(), common_types.end(), normalize_type(in)) != common_types.end();
}

inline std::string size_to_tag_type(size_t sz) {
	if(sz == 0) {
		return "uint32_t";
	} else if(sz <= 126) {
		return "uint8_t";
	} else if(sz <= std::numeric_limits<int16_t>::max() - 1) {
		return "uint16_t";
	}
	return "uint32_t";
}
