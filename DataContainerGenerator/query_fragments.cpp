#include "code_fragments.hpp"

basic_builder& make_query_instance_types(basic_builder& o, prepared_query_definition const& pdef) {
	o + substitute{ "name", pdef.name };

	std::string param_list;
	std::string arg_list;
	int32_t i = 0;

	for(auto& param : pdef.parameters) {
		if(param_list.length() > 0) {
			param_list += ", ";
			arg_list += ", ";
		}
		param_list += param.type + " p" + std::to_string(i);
		arg_list += param.name + "(p" + std::to_string(i) + ")";
		++i;
	}

	o + substitute{ "cparams", param_list };
	o + substitute{ "cinit", arg_list };

	o + "class query_@name@_instance" + class_block{
		o + "public:";
		
		o + "data_container& container;";
		
		for(auto& param : pdef.parameters) {
			o + substitute{ "type", param.type };
			o + substitute{ "pname", param.name };

			o + "@type@ @pname@;";
		}

		o + "query_@name@_instance(data_container& c, @param_list@) : container(c), @arg_list@ {}";

		o + "query_@name@_iterator begin() const" + block{
			o + "return query_@name@_iterator(c, *this);";
		};
		o + "dcon::invalid_iterator_type end() const" + block{
			o + "return dcon::invalid_iterator_type{};";
		};
	};

	o + "class query_@name@_const_instance" + class_block{
		o + "public:";

		o + "data_container const& container;";

		for(auto& param : pdef.parameters) {
			o + substitute{ "type", param.type };
			o + substitute{ "pname", param.name };

			o + "@type@ @pname@;";
		}

		o + "query_@name@_const_instance(data_container const& c, @param_list@) : container(c), @arg_list@ {}";

		o + "query_@name@_iterator begin() const" + block{
			o + "return query_@name@_const_iterator(c, *this);";
		};
		o + "dcon::invalid_iterator_type end() const" + block{
			o + "return dcon::invalid_iterator_type{};";
		};
	};

	o + line_break{};
	return o;
}

basic_builder& make_query_iterator_declarations(basic_builder& o, prepared_query_definition const& pdef) {
	o + substitute{ "name", pdef.name };

	o + "class query_@name@_instance;";
	o + "class query_@name@_const_instance;";

	o + "class query_@name@_iterator" + class_block{
		o + "private:";
		o + "data_container& container;";
		o + "query_@name@_instance const& m_parameters;";

		for(auto& agg : pdef.exposed_aggregates) {
			if(agg.from_link)
				o + substitute{ "type", agg.from_link->type_name + "_id" };
			else if(agg.from_property)
				o + substitute{ "type", agg.from_property->data_type };
			o + substitute{ "pname", agg.aggregate_name };

			o + "@type@ @pname@;";
		}
		for(auto& mm : pdef.exposed_min_max_terms) {
			o + substitute{ "type", mm.derived_from_slot->actual_table->name + "_id" };
			o + substitute{ "pname", mm.exposed_name };

			o + "@type@ @pname@;";
		}
		for(auto& ts : pdef.table_slots) {
			if(!ts.is_parameter_type) {
				o + substitute{ "type", ts.actual_table->name + "_id" };
				o + substitute{ "pname", ts.internally_named_as };
			}
			o + "@type@ @pname@;";
		}

		o + "public:";

		o + "query_@name@_iterator(data_container& c, query_@name@_instance const& p) : container(c), m_parameters(p) {}";

		o + "query_@name@_iterator& operator++();";
		o + "bool operator==(dcon::invalid_iterator_type);";
		o + "query_@name@_iterator const& operator*() { return *this; }";

		/* getters and setters */

		for(auto& prop : pdef.exposed_values) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + substitute{ "ptype", prop.from_link->type_name + "_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
				o + "void set_@exname@(@ptype@) const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };
				o + substitute{ "ptype", prop.from_property->data_type };
				
				switch(prop.from_property->type) {
					case property_type::array_bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(bool, int32_t) const;";
						break;
					case property_type::array_other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(@ptype@ const&, int32_t) const;";
						break;
					case property_type::array_vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(@ptype@, int32_t) const;";
						break;
					case property_type::bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(bool) const;";
						break;
					case property_type::object:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@) const;";
						break;
					case property_type::special_vector:
						break;
				}
			}
		}
		for(auto& prop : pdef.exposed_min_max_terms) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + substitute{ "ptype", prop.from_link->type_name + "_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
				o + "void set_@exname@(@ptype@) const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };
				o + substitute{ "ptype", prop.from_property->data_type };

				switch(prop.from_property->type) {
					case property_type::array_bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(bool, int32_t) const;";
						break;
					case property_type::array_other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(@ptype@ const&, int32_t) const;";
						break;
					case property_type::array_vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						o + "void set_@exname@(@ptype@, int32_t) const;";
						break;
					case property_type::bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(bool) const;";
						break;
					case property_type::object:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						o + "void set_@exname@(@ptype@) const;";
						break;
					case property_type::special_vector:
						break;
				}
			}
		}
		for(auto& prop : pdef.exposed_aggregates) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };
				o + substitute{ "ptype", prop.from_property->data_type };

				switch(prop.from_property->type) {
					case property_type::bitfield:
						o + "bool get_@exname@() const;";
						break;
					case property_type::object:
						o + "@ptype@ const& get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::other:
						o + "@ptype@ const& get_@exname@() const;";
						break;
					case property_type::vectorizable:
						o + "@ptype@ get_@exname@() const;";
						break;
					default:
						break;
				}
			}
		}
		for(auto& table : pdef.table_slots) {
			if(table.expose_has_name) {
				o + substitute{ "tnaame", table.reference_name };
				o + "bool has_@tname@() const noexcept;";
			}
		}

	};

	o + "class query_@name@_cosnt_iterator" + class_block{
		o + "private:";
		o + "data_container const& container;";
		o + "query_@name@_instance const& m_parameters;";

		for(auto& agg : pdef.exposed_aggregates) {
			if(agg.from_link)
				o + substitute{ "type", agg.from_link->type_name + "_id" };
			else if(agg.from_property)
				o + substitute{ "type", agg.from_property->data_type };
			o + substitute{ "pname", agg.aggregate_name };

			o + "@type@ @pname@;";
		}
		for(auto& mm : pdef.exposed_min_max_terms) {
			o + substitute{ "type", mm.derived_from_slot->actual_table->name + "_id" };
			o + substitute{ "pname", mm.exposed_name };

			o + "@type@ @pname@;";
		}
		for(auto& ts : pdef.table_slots) {
			if(!ts.is_parameter_type) {
				o + substitute{ "type", ts.actual_table->name + "_id" };
				o + substitute{ "pname", ts.internally_named_as };
			}
			o + "@type@ @pname@;";
		}

		o + "public:";

		o + "query_@name@_const_iterator(data_container const& c, query_@name@_instance const& p) : container(c), m_parameters(p) {}";

		o + "query_@name@_const_iterator& operator++();";
		o + "bool operator==(dcon::invalid_iterator_type);";
		o + "query_@name@_const_iterator const& operator*() { return *this; }";

		/* getters and setters */

		for(auto& prop : pdef.exposed_values) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };

				switch(prop.from_property->type) {
					case property_type::array_bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::array_other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::array_vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::object:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::special_vector:
						break;
				}
			}
		}
		for(auto& prop : pdef.exposed_min_max_terms) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };

				switch(prop.from_property->type) {
					case property_type::array_bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::array_other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::array_vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id(), 0)) get_@exname@(int32_t i) const;";
						break;
					case property_type::bitfield:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::object:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::other:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::vectorizable:
						o + "decltype(container.@obj@_get_@propname@(@obj@_id())) get_@exname@() const;";
						break;
					case property_type::special_vector:
						break;
				}
			}
		}
		for(auto& prop : pdef.exposed_aggregates) {
			o + substitute{ "exname", prop.exposed_name };
			if(prop.from_link) {
				o + substitute{ "rtype", prop.from_link->type_name + "_fat_id" };
				o + "@rtype@ get_@exname@() const noexcept;";
			} else if(prop.from_property) {
				o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
				o + substitute{ "propname", prop.from_property->name };
				o + substitute{ "ptype", prop.from_property->data_type };

				switch(prop.from_property->type) {
					case property_type::bitfield:
						o + "bool get_@exname@() const;";
						break;
					case property_type::object:
						o + "@ptype@ const& get_@exname@() const;";
						o + "void set_@exname@(@ptype@ const&) const;";
						break;
					case property_type::other:
						o + "@ptype@ const& get_@exname@() const;";
						break;
					case property_type::vectorizable:
						o + "@ptype@ get_@exname@() const;";
						break;
					default:
						break;
				}
			}
		}
		for(auto& table : pdef.table_slots) {
			if(table.expose_has_name) {
				o + substitute{ "tnaame", table.reference_name };
				o + "bool has_@tname@() const noexcept;";
			}
		}

	};

	o + line_break{};
	return o;
}