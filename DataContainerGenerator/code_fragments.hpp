#pragma once

#include <optional>
#include "source_builder.hpp"
#include "parsing.hpp"

basic_builder& make_load_record(basic_builder& o, file_def const & fd);
basic_builder& make_id_definition(basic_builder& o, std::string const& type_name, std::string const& underlying_type);
basic_builder& make_value_to_vector_type(basic_builder& o, std::string const& qualified_name);

enum class struct_padding { none, fixed };

basic_builder& make_member_container(basic_builder& o,
	std::string const& member_name, std::string const& type_name, std::string const& size, struct_padding pad, bool is_expandable,
	std::optional<std::string> const& special_fill = std::optional<std::string>());
basic_builder& make_array_member_container(basic_builder& o,
	std::string const& member_name, std::string const& type_name, size_t raw_size,
	bool is_expandable, bool is_bitfield);

std::string expand_size_to_fill_cacheline_calculation(std::string const& member_type, size_t base_size);

basic_builder& make_erasable_object_constructor(basic_builder& o, std::string const& name, size_t size);

enum class hook_type { bitfield, vectorizable, other };

basic_builder& make_hooked_getters(basic_builder& o, std::string const& object_name, std::string const& property_name, 
	std::string const& property_type, hook_type ht, bool is_expandable);
basic_builder& make_hooked_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& property_type, hook_type ht, bool is_expandable);
basic_builder& make_array_hooked_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& property_type, std::string const& index_type, hook_type ht, bool is_expandable);
basic_builder& make_array_hooked_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& property_type, std::string const& index_type, hook_type ht, bool is_expandable);

basic_builder& make_bitfield_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	bool is_expandable);
basic_builder& make_bitfield_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	bool is_expandable);
basic_builder& make_object_getters(basic_builder& o, std::string const& object_name,  std::string const& property_name,
	std::string const& type);
basic_builder& make_object_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type);
basic_builder& make_vectorizable_type_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type, bool is_expandable);
basic_builder& make_vectorizable_type_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type, bool is_expandable);
basic_builder& make_special_array_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type);
basic_builder& make_special_array_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type);


basic_builder& make_relation_pk_getters_setters(basic_builder& o, std::string const& relation_name, std::string const& property_name,
	bool is_expandable);
basic_builder& make_relation_pk_reverse_getters_setters(basic_builder& o, std::string const& relation_name,
	std::string const& property_name, std::string const& property_type, bool is_expandable, bool skip_as);
basic_builder& make_relation_unique_non_pk_getters_setters(basic_builder& o, std::string const& relation_name,
	std::string const& property_name, std::string const& property_type, bool is_expandable);
basic_builder& make_relation_unique_non_pk_reverse_getters_setters(basic_builder& o, std::string const& relation_name,
	std::string const& property_name, std::string const& property_type, bool is_expandable, bool skip_as);
basic_builder& make_relation_many_getters_setters(basic_builder& o, std::string const& relation_name, list_type ltype,
	std::string const& property_name, std::string const& property_type, bool is_expandable);
basic_builder& make_relation_many_reverse_getters_setters(basic_builder& o, std::string const& relation_name, list_type ltype,
	std::string const& property_name, std::string const& property_type, bool is_expandable, bool skip_as);
basic_builder& make_pop_back(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_object_resize(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_compactable_delete(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_non_erasable_create(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_erasable_delete(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_clearing_delete(basic_builder& o, relationship_object_def const& cob);
basic_builder& make_erasable_create(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_internal_move_relationship(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_relation_try_create(basic_builder& o, relationship_object_def const& cob);
basic_builder& make_relation_force_create(basic_builder& o, relationship_object_def const& cob);
basic_builder& make_serialize_plan_generator(basic_builder& o, file_def const& parsed_file, load_save_def const& rt);
basic_builder& make_serialize_size(basic_builder& o, file_def const& parsed_file);
basic_builder& make_serialize(basic_builder& o, file_def const& parsed_file);
basic_builder& make_deserialize(basic_builder& o, file_def const& parsed_file, bool with_mask);
basic_builder& make_serialize_all_generator(basic_builder& o, file_def const& parsed_file);
basic_builder& make_join_getters_setters(basic_builder& o, relationship_object_def const& obj);
basic_builder& make_iterate_over_objects(basic_builder& o, relationship_object_def const& obj);
