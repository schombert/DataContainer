#include "code_fragments.hpp"

basic_builder& make_load_record(basic_builder& o, file_def const & fd) {
	o + "struct load_record" + class_block{
		for(auto& ro : fd.relationship_objects) {
			o + substitute("object", ro.name);
			o + "bool @object@ = false;";
			for(auto& io : ro.indexed_objects) {
				o + substitute("prop_name", io.property_name);
				o + "bool @object@_@prop_name@ = false;";
			}
			for(auto& io : ro.properties) {
				o + substitute("prop_name", io.name);
				o + "bool @object@_@prop_name@ = false;";
			}
		}
	};
	return o;
}

basic_builder& make_id_definition(basic_builder& o, std::string const& type_name, std::string const& underlying_type) {
	o + substitute("name", type_name) + substitute("type", underlying_type);
	o + heading{"definition of strongly typed index for @name@"};
	o + "class @name@_id" + class_block{ o
		+ "public:"
		+ "using value_base_t = @type@;"
		+ "using zero_is_null_t = std::true_type;"
		+ line_break{}
		+"@type@ value;"
		+ line_break{}
		+"explicit constexpr @name@_id(@type@ v) noexcept : value(v + 1) {}"
		+ "constexpr @name@_id(@name@_id const& v) noexcept = default;"
		+ "constexpr @name@_id(@name@_id&& v) noexcept = default;"
		+ "constexpr @name@_id() noexcept : value(@type@(0)) {}"
		+ line_break{}
		+"@name@_id& operator=(@name@_id v) noexcept { value = v.value; return *this; }"
		+"constexpr bool operator==(@name@_id v) const noexcept { return value == v.value; }"
		+ "constexpr bool operator!=(@name@_id v) const noexcept { return value != v.value; }"
		+ "explicit constexpr operator bool() const noexcept { return value != @type@(0); }"
		+ "constexpr DCON_RELEASE_INLINE int32_t index() const noexcept" + block{
			o + "return int32_t(value) - 1;";
		};
	} + line_break{}
	+"class @name@_id_pair" + class_block{ o
		+ "@name@_id left;"
		+ "@name@_id right;";
	} + line_break{}
	+ "DCON_RELEASE_INLINE bool is_valid_index(@name@_id id) { return bool(id); }" + line_break{};

	return o;
}

basic_builder& make_value_to_vector_type(basic_builder& o, std::string const& qualified_name) {
	o + substitute("type", qualified_name)
		+ "template<>"
		+ "struct value_to_vector_type_s<@type@>" + class_block {
			o + "using type = tagged_vector<@type@>;";
		} + line_break{};
	return o;
}

basic_builder& make_member_container(basic_builder& o,
	std::string const& member_name, std::string const& type_name, std::string const& size,
	struct_padding pad, bool is_expandable, std::optional<std::string> const& special_fill) {

	o + substitute("type", type_name) + substitute("name", member_name) + substitute{"size", size}
	+ substitute{ "align", pad != struct_padding::none ? "alignas(64) " : "" }
	+ substitute{"fill", special_fill.has_value() ? *special_fill : std::string("")};

	o + heading{"storage space for @name@ of type @type@"};
	o + "struct @align@dtype_@name@" + block{
		if(is_expandable) {
			o + "std::vector<@type@> values;"
			+ "DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }"
			+ "DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }";
		} else {
			if(pad == struct_padding::fixed)
				o + "uint8_t padding[64];";
			else if(pad == struct_padding::calculated)
				o + "uint8_t padding[(sizeof(@type@) + 63ui32) & ~63ui32];";
			o + "@type@ values[@size@];"
			+ "DCON_RELEASE_INLINE auto vptr() const { return values; }"
			+ "DCON_RELEASE_INLINE auto vptr() { return values; }";
		}
		
		if(!special_fill.has_value()) {
			if(is_expandable)
				o + "dtype_@name@() { values.emplace_back(); }";
			else if(pad == struct_padding::none)
				o + "dtype_@name@() { std::uninitialized_value_construct_n(values, @size@); }";
			else
				o + "dtype_@name@() { std::uninitialized_value_construct_n(values - 1, 1 + @size@); }";
		} else {
			if(is_expandable)
				o + "dtype_@name@() { values.push_back( @fill@ ); }";
			else if(pad == struct_padding::none)
				o + "dtype_@name@() { std::uninitialized_fill_n(values, @size@, @fill@); }";
			else
				o + "dtype_@name@() { std::uninitialized_fill_n(values - 1, 1 + @size@, @fill@); }";
		}
	} +"m_@name@;" + line_break{};

	return o;
}

std::string expand_size_to_fill_cacheline_calculation(std::string const& member_type, size_t base_size) {
	return std::string("(sizeof(") + member_type + ") <= 64 ? ("
		"uint32_t(" + std::to_string(base_size) + ") + (64ui32 / uint32_t(sizeof(" + member_type + "))) - 1ui32) "
		"& ~(64ui32 / uint32_t(sizeof(" + member_type + ")) - 1ui32) : uint32_t(" + std::to_string(base_size) + "))";
}

basic_builder& make_erasable_object_constructor(basic_builder& o, std::string const& name, size_t size) {
	o + substitute{ "name", name } +substitute{ "size", std::to_string(size) } +substitute{"u_type", size_to_tag_type(size) }
	+"@name@" + block{
		o + "for(int32_t i = @size@ - 1; i >= 0; --i)" + block{
			o + "m__index.vptr()[i] = first_free;";
			o + "first_free = @name@_id(@u_type@(i));";
		};
	};
	return o;
}

basic_builder& make_hooked_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& property_type, hook_type ht, bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name } +substitute{ "type", property_type } +
		substitute{ "vector_position", is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags" };

	o + heading{"getter hooks for @obj@: @prop@"};
	
	if(ht == hook_type::bitfield) {
		o + "bool @obj@_get_@prop@(@obj@_id id) const;";
		o + "ve::vbitfield_type @obj@_get_@prop@(@vector_position@<@obj@_id> id) const" + block{
			o + "ve::vbitfield_type r; r.v = 0;";
			o + "for(int32_t i = 0; i < ve::vector_size; ++i)" + block{
				o + "tr.v |= (@obj@_get_@prop@(@@obj_id(id.value + i))) << i;";
			};
			o + "return r;";
		};
		o + "ve::vbitfield_type @obj@_get_@prop@(ve::partial_contiguous_tags<@obj@_id> id) const" + block{
			o + "ve::vbitfield_type r; r.v = 0;";
			o + "for(int32_t i = 0; i < id.subcount; ++i)" + block{
				o + "tr.v |= (@obj@_get_@prop@(@@obj_id(id.value + i))) << i;";
			};
			o + "return r;";
		};
		o + "ve::vbitfield_type @obj@_get_@prop@(ve::tagged_vector<@obj@ _id> id) const" + block{
			o + "ve::vbitfield_type r; r.v = 0;";
			o + "for(int32_t i = 0; i < ve::vector_size; ++i)" + block{
				o + "tr.v |= (@obj@_get_@prop@(@@obj_id(id.value + i))) << i;";
			};
			o + "return r;";
		};
	} else if(ht == hook_type::vectorizable) {
		o + "@type@ @obj@_get_@prop@(@obj@_id id) const;";
		o + "ve::value_to_vector_type<@type@> @obj@_get_@prop@(@vector_position@<@obj@_id> id) const" + block{
			o + "return ve::apply(id, [t = this](@obj@_id i){ return t->@obj@_get_@prop@(i); });";
		};
		o + "ve::value_to_vector_type<@type@> @obj@_get_@prop@(ve::partial_contiguous_tags<@obj@_id> id) const" + block{
			o + "return ve::apply(id, [t = this](@obj@_id i){ return t->@obj@_get_@prop@(i); });";
		};
		o + "ve::value_to_vector_type<@type@> @obj@_get_@prop@(ve::tagged_vector<@obj@_id> id) const" + block{
			o + "return ve::apply(id, [t = this](@obj@_id i){ return t->@obj@_get_@prop@(i); });";
		};
	} else {
		o + "@type@ @obj@_get_@prop@(@obj@_id id) const;";
	}
	o + line_break{};
	return o;
}

basic_builder& make_hooked_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& property_type, hook_type ht, bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name } +substitute{ "type", property_type } +
		substitute{ "vector_position", is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags" };
	o + heading{ "setter hooks for @obj@: @prop@" };

	if(ht == hook_type::bitfield) {
		o + "void @obj@_set_@prop@(@obj@_id id, bool value);";
		o + "void @obj@_set_@prop@(@vector_position@<@obj@_id> id, ve::vbitfield_type value)" + block{
			o + "for(int32_t i = 0; i < ve::vector_size; ++i)" + block{
				o + "@obj@_set_@prop@(@obj@_id(id.value + i), (value.v & uint8_t(1 << i)) != 0);";
			};
		};
		o + "void @obj@_set_@prop@(partial_contiguous_tags<@obj@_id> id, ve::vbitfield_type value)" + block{
			o + "for(int32_t i = 0; i < id.subcount; ++i)" + block{
				o + "@obj@_set_@prop@(@obj@_id(id.value + i), (value.v & uint8_t(1 << i)) != 0);";
			};
		};
		o + "void @obj@_set_@prop@(ve::tagged_vector<<@obj@_id> id, ve::vbitfield_type value)" + block{
			o + "for(int32_t i = 0; i < ve::vector_size; ++i)" + block{
				o + "@obj@_set_@prop@(id[i], (value.v & uint8_t(1 << i)) != 0);";
			};
		};
	} else if(ht == hook_type::vectorizable) {
		o + "void @obj@_set_@prop@(@obj@_id id, @type@ value);";
		o + "void @obj@_set_@prop@(@vector_position@<@obj@_id> id, ve::value_to_vector_type<@type@> value)" + block{
			o + "ve::apply(id, value, [t = this](@obj@_id i, @type@ v){ t->@obj@_set_@prop@(i, v); });";
		};
		o + "void @obj@_set_@prop@(partial_contiguous_tags<@obj@_id> id, ve::value_to_vector_type<@type@> value)" + block{
			o + "ve::apply(id, value, [t = this](@obj@_id i, @type@ v){ t->@obj@_set_@prop@(i, v); });";
		};
		o + "void @obj@_set_@prop@(ve::tagged_vector<@obj@_id> id, ve::value_to_vector_type<@type@> value)" + block{
			o + "ve::apply(id, value, [t = this](@obj@_id i, @type@ v){ t->@obj@_set_@prop@(i, v); });";
		};
	} else {
		o + "void @obj@_set_@prop@(@obj@_id id, @type@ const& value);";
	}

	o + line_break{};
	return o;
}

basic_builder& make_vectorizable_getters(basic_builder& o, std::string const& type, bool is_expandable) {
	o + substitute{ "vector_position", is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags" }
		+ substitute{"type", type};
	o + "DCON_RELEASE_INLINE @type@ @obj@_get_@prop@(@vector_position@<@obj@_id> id) const noexcept" + block{
		o + "return ve::load(id, @obj@.m_@prop@.vptr());";
	};
	o + "DCON_RELEASE_INLINE @type@ @obj@_get_@prop@(ve::partial_contiguous_tags<@obj@_id> id) const noexcept" + block{
		o + "return ve::load(id, @obj@.m_@prop@.vptr());";
	};
	o + "DCON_RELEASE_INLINE @type@ @obj@_get_@prop@(ve::tagged_vector<@obj@_id> id) const noexcept" + block{
		o + "return ve::load(id, @obj@.m_@prop@.vptr());";
	};

	return o;
}

basic_builder& make_vectorizable_setters(basic_builder& o, std::string const& type, bool is_expandable) {
	o + substitute{ "vector_position", is_expandable ? "ve::unaligned_contiguous_tags" : "ve::contiguous_tags" }
	+substitute{ "type", type };

	o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(@vector_position@<@obj@_id> id, @type@ values) noexcept" + block{
		o + "ve::store(id, @obj@.m_@prop@.vptr(), values);";
	};
	o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(ve::partial_contiguous_tags<@obj@_id> id, @type@ values) noexcept" + block{
		o + "ve::store(id, @obj@.m_@prop@.vptr(), values);";
	};
	o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(ve::tagged_vector<@obj@_id> id, @type@ values) noexcept" + block{
		o + "ve::store(id, @obj@.m_@prop@.vptr(), values);";
	};

	return o;
}

basic_builder& make_single_getter(basic_builder& o, std::string const& type, bool return_reference) {
	o + substitute{ "type", type };
	if(!return_reference) {
		o + "DCON_RELEASE_INLINE @type@ @obj@_get_@prop@(@obj@_id id) const noexcept" + block{
			o + "return @obj@.m_@prop@.vptr()[id.index()];";
		};
	} else {
		o + "DCON_RELEASE_INLINE @type@ const& @obj@_get_@prop@(@obj@_id id) const noexcept" + block{
			o + "return @obj@.m_@prop@.vptr()[id.index()];";
		};
		o + "DCON_RELEASE_INLINE @type@& @obj@_get_@prop@(@obj@_id id) noexcept" + block{
			o + "return @obj@.m_@prop@.vptr()[id.index()];";
		};
	}
	return o;
}
basic_builder& make_single_setter(basic_builder& o, std::string const& type, bool by_reference) {
	o + substitute{ "type", type };
	if(by_reference) {
		o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(@obj@_id id, @type@ const& value) noexcept" + block{
			o + "@obj@.m_@prop@.vptr()[id.index()] = value;";
		};
	} else {
		o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(@obj@_id id, @type@ value) noexcept" + block{
			o + "@obj@.m_@prop@.vptr()[id.index()] = value;";
		};
	}
	return o;
}

basic_builder& make_bitfield_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "getters for @obj@: @prop@" };

	o + "DCON_RELEASE_INLINE bool @obj@_get_@prop@(@obj@_id id) const noexcept" + block{
		o + "return dcon::bit_vector_test(@obj@.m_@prop@.vptr()[id.index()]);";
	};
	make_vectorizable_getters(o, "ve::vbitfield_type", is_expandable);
	o + line_break{};
	return o;
}

basic_builder& make_bitfield_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "setters for @obj@: @prop@" };

	o + "DCON_RELEASE_INLINE void @obj@_set_@prop@(@obj@_id id, bool value) noexcept" + block{
		o + "dcon::bit_vector_set(@obj@.m_@prop@.vptr(), id.index(), value);";
	};

	make_vectorizable_setters(o, "ve::vbitfield_type", is_expandable);
	o + line_break{};
	return o;
}

basic_builder& make_object_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "getters for @obj@: @prop@" };

	make_single_getter(o, type, true);
	o + line_break{};
	return o;
}

basic_builder& make_object_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "setters for @obj@: @prop@" };

	make_single_setter(o, type, true);
	o + line_break{};
	return o;
}

basic_builder& make_vectorizable_type_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type, bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "getters for @obj@: @prop@" };

	make_single_getter(o, type, true);
	make_vectorizable_getters(o, std::string("ve::value_to_vector_type<") + type + ">", is_expandable);
	o + line_break{};
	return o;
}

basic_builder& make_vectorizable_type_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type, bool is_expandable) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name };
	o + heading{ "setters for @obj@: @prop@" };

	make_single_setter(o, type, false);
	make_vectorizable_setters(o, std::string("ve::value_to_vector_type<") + type + ">", is_expandable);
	o + line_break{};
	return o;
}

basic_builder& make_special_array_getters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type) {

	o + substitute{ "obj", object_name } +substitute{ "prop", property_name }+substitute{ "type", type };;
	o + heading{ "getters for @obj@: @prop@ (special array)" };

	o + "std::pair<@type@*, @type@*> @obj@_get_@prop@_range(@obj@_id id) const noexcept" + block{
		o + "return dcon::get_range(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()]);";
	};

	o + "@type@& @obj@_get_@prop@_at(@obj@_id id, uint32_t inner_index) const noexcept" + block{
		o + "return dcon::get(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()], inner_index);";
	};

	o + "uint32_t @obj@_get_@prop@_capacity(@obj@_id id) const noexcept" + block{
		o + "return dcon::get_capacity(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()]);";
	};

	o + "uint32_t @obj@_get_@prop@_size(@obj@_id id) const noexcept" + block{
		o + "return dcon::get_size(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()]);";
	};

	o + "bool @obj@_@prop@_contains(@obj@_id id, @type@ obj) const noexcept" + block{
		o + "return dcon::contains_item(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()], obj);";
	};
	o + line_break{};
	return o;

}
basic_builder& make_special_array_setters(basic_builder& o, std::string const& object_name, std::string const& property_name,
	std::string const& type) {
	o + substitute{ "obj", object_name } +substitute{ "prop", property_name }+substitute{ "type", type };;
	o + heading{ "setters for @obj@: @prop@ (special array)" };

	o + "void @obj@_@prop@_push_back(@obj@_id id, @type@ obj) noexcept" + block{
		o + "return dcon::push_back(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()], obj);";
	};

	o + "void @obj@_@prop@_pop_back(@obj@_id id) noexcept" + block{
		o + "return dcon::pop_back(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()]);";
	};

	o + "void @obj@_@prop@_add_unique(@obj@_id id, @prop@ obj) noexcept" + block{
		o + "return dcon::add_unique_item(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()], obj);";
	};

	o + "void @obj@_@prop@_remove_unique(@obj@_id id, @prop@ obj) noexcept" + block{
		o + "return dcon::remove_unique_item(@obj@.@prop@_storage, @obj@.m_@prop@.vptr()[id.index()], obj);";
	};
	o + line_break{};
	return o;
}
