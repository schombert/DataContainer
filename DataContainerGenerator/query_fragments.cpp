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

	o + "class query_@name@_iterator;";
	o + "class query_@name@_const_iterator;";

	o + "class query_@name@_instance" + class_block{
		o + "public:";
		
		o + "data_container& container;";
		
		for(auto& param : pdef.parameters) {
			o + substitute{ "type", param.type };
			o + substitute{ "pname", param.name };

			o + "@type@ @pname@;";
		}

		o + "query_@name@_instance(data_container& c, @param_list@) : container(c), @arg_list@ {}";

		o + "query_@name@_iterator begin() const;";

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

		o + "query_@name@_const_iterator begin() const;";

		o + "dcon::invalid_iterator_type end() const" + block{
			o + "return dcon::invalid_iterator_type{};";
		};
	};

	o + line_break{};
	return o;
}

basic_builder& make_query_instance_definitions(basic_builder& o, prepared_query_definition const& pdef) {
	o + substitute{ "name", pdef.name };

	o + "query_@name@_iterator query_@name@_instance::begin() const" + block{
			o + "return query_@name@_iterator(c, *this);";
	};
	o + "query_@name@_const_iterator query_@name@_const_instance::begin() const" + block{
			o + "return query_@name@_const_iterator(c, *this);";
	};
}

basic_builder& make_query_iterator_declarations(basic_builder& o, prepared_query_definition const& pdef) {
	o + substitute{ "name", pdef.name };

	o + "class query_@name@_instance;";
	o + "class query_@name@_const_instance;";

	o + "class query_@name@_iterator" + class_block{
		o + "private:";
		o + "data_container& m_container;";
		o + "query_@name@_instance const& m_parameters;";

		for(auto& agg : pdef.exposed_aggregates) {
			if(agg.aggregate_name == "count")
				o + substitute{ "type", "int32_t" };
			else if(agg.from_link)
				o + substitute{ "type", agg.from_link->type_name + "_id" };
			else if(agg.from_property)
				o + substitute{ "type", agg.from_property->data_type };
			o + substitute{ "pname", agg.aggregate_name };

			o + "@type@ m_@pname@;";
		}
		for(auto& mm : pdef.exposed_min_max_terms) {
			o + substitute{ "type", mm.derived_from_slot->actual_table->name + "_id" };
			o + substitute{ "pname", mm.exposed_name };

			o + "@type@ m_@pname@;";
		}
		for(auto& ts : pdef.table_slots) {
			if(!ts.is_parameter_type) {
				o + substitute{ "type", ts.actual_table->name + "_id" };
				o + substitute{ "pname", ts.internally_named_as };

				o + "@type@ m_@pname@;";
				if(ts.joind_by_link->multiplicity > 1 && !ts.actual_table->is_relationship) {
					o + "in32_t m_index_into_@pname@ = 0;";
				} else if(ts.joind_by_link->index == index_type::many && ts.joind_by_link->ltype != list_type::list
					&& ts.actual_table->is_relationship) {
					o + "in32_t m_index_into_@pname@ = 0;";
					o + "in32_t m_size_of_@pname@ = 0;";
				}
			}
		}

		o + "public:";

		o + "query_@name@_iterator(data_container& c, query_@name@_instance const& p) : m_container(c), m_parameters(p)" + block{
			for(auto& ts : pdef.table_slots) {
				o + substitute{"id_name", ts.internally_named_as};
				o + substitute{ "obj", ts.actual_table->name };
				if(ts.is_parameter_type) {
					
				} else if(ts.joined_to) {
					o + substitute{ "parent", ts.joined_to->internally_named_as };
					o + substitute{ "pobj", ts.joined_to->actual_table->name };
					o + substitute{ "lname", ts.joind_by_link->property_name };
					if(ts.actual_table->is_relationship) {
						if(ts.joind_by_link->index == index_type::at_most_one) {
							o + "@id_name@ = bool(@parent@) ? m_container.@pobj@_get_@obj@_as_@lname@(@parent@) : @obj@_id();";
						} else if(ts.joind_by_link->index == index_type::many) {

						} else { // type none

						}
					} else {
						if(ts.joind_by_link->multiplicity == 1)
							o + "@id_name@ = bool(@parent@) ? m_container.@pobj@_get_@lname@(@parent@) : @obj@_id();";
						else
							o + "@id_name@ = bool(@parent@) ? m_container.@pobj@_get_@lname@(@parent@, 0) : @obj@_id();";
					}
				} else { // first
					o + "@id_name@ = m_container.@obj@_size() > 0 ? @obj@_id(@obj@_id::value_base_t(0)) : @obj@_id();";
				}
			}
		};

		make_query_iterator_body(o, pdef, "", false);

	};

	o + "class query_@name@_const_iterator" + class_block{
		o + "private:";
		o + "data_container const& m_container;";
		o + "query_@name@_instance const& m_parameters;";

		for(auto& agg : pdef.exposed_aggregates) {
			if(agg.aggregate_name == "count")
				o + substitute{ "type", "int32_t" };
			else if(agg.from_link)
				o + substitute{ "type", agg.from_link->type_name + "_id" };
			else if(agg.from_property)
				o + substitute{ "type", agg.from_property->data_type };
			o + substitute{ "pname", agg.aggregate_name };

			o + "@type@ m_@pname@;";
		}
		for(auto& mm : pdef.exposed_min_max_terms) {
			o + substitute{ "type", mm.derived_from_slot->actual_table->name + "_id" };
			o + substitute{ "pname", mm.exposed_name };

			o + "@type@ m_@pname@;";
		}
		for(auto& ts : pdef.table_slots) {
			if(!ts.is_parameter_type) {
				o + substitute{ "type", ts.actual_table->name + "_id" };
				o + substitute{ "pname", ts.internally_named_as };

				o + "@type@ m_@pname@;";
				if(ts.joind_by_link->multiplicity > 1 && !ts.actual_table->is_relationship) {
					o + "in32_t m_index_into_@pname@ = 0;";
				} else if(ts.joind_by_link->index == index_type::many && ts.joind_by_link->ltype != list_type::list
					&& ts.actual_table->is_relationship) {
					o + "in32_t m_index_into_@pname@ = 0;";
					o + "in32_t m_size_of_@pname@ = 0;";
				}
			}
		}

		o + "public:";

		o + "query_@name@_const_iterator(data_container const& c, query_@name@_instance const& p) : m_container(c), m_parameters(p) {}";
		
		make_query_iterator_body(o, pdef, "", true);

	};

	o + line_break{};
	return o;
}

basic_builder& make_query_iterator_body(basic_builder& o, prepared_query_definition const& pdef, std::string const& ns, bool is_const) {
	o + substitute{ "name", pdef.name };
	o + substitute{ "namesp", pdef.name };
	o + substitute{ "id_type", is_const ? "const_fat_id" : "fat_id" };
	
	
	o + "query_@name@_iterator& @namesp@operator++();";
	o + "bool @namesp@operator==(dcon::invalid_iterator_type)" + block{
		if(pdef.table_slots.size() > 0) {
			o + substitute{"first_id", pdef.table_slots[0].internally_named_as};
			o + "return !bool(@first_id@);";
		} else {
			o + "return true;";
		}
	};
	o + "bool @namesp@operator!=(dcon::invalid_iterator_type)" + block{
		if(pdef.table_slots.size() > 0) {
			o + substitute{"first_id", pdef.table_slots[0].internally_named_as};
			o + "return bool(@first_id@);";
		} else {
			o + "return false;";
		}
	};
	if(is_const) {
		o + "query_@name@_iterator const& @namesp@operator*()" + block{
			o + "return *this;";
		};
	} else {
		o + "query_@name@_const_iterator const& @namesp@operator*()" + block{
			o + "return *this;";
		};
	}

	/* getters and setters */

	for(auto& prop : pdef.exposed_values) {
		o + substitute{ "exname", prop.exposed_name };
		o + substitute{ "internal_tag", prop.derived_from_slot->internally_named_as };
		o + substitute{ "obj", prop.derived_from_slot->actual_table->name };

		if(prop.from_link) {
			o + substitute{ "rtype", prop.from_link->type_name };
			o + substitute{ "ptype", prop.from_link->type_name + "_id" };
			o + substitute{ "propname", prop.from_link->property_name };

			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return @rtype@_@id_type@(m_container, m_container.@obj@_get_@propname@( @internal_tag@ ))";
			};
			if(!is_const) {
				o + "void @namesp@set_@exname@(@ptype@ v) const noexcept" + block{
					o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
				};
			}
		} else if(prop.from_property) {
			o + substitute{ "propname", prop.from_property->name };
			o + substitute{ "ptype", prop.from_property->data_type };
			o + substitute{ "index_type", prop.from_property->array_index_type };
			
			switch(prop.from_property->type) {
				case property_type::array_bitfield:
					o + "bool @namesp@get_@exname@(@index_type@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@index_type@ i, bool v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::array_other:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id(), @index_type@())) @namesp@get_@exname@(@internal_tag@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@internal_tag@ i, @ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::array_vectorizable:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id(), @index_type@())) @namesp@get_@exname@(@internal_tag@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@internal_tag@ i, @ptype@ v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::bitfield:
					o + "bool @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(bool v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::object:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::other:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::vectorizable:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::special_vector:
					break;
			}
		} else {
			o + substitute{ "rtype", prop.derived_from_slot->actual_table->name };
			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return @rtype@_@id_type@(m_container, @internal_tag@ )";
			};
		}
	}
	for(auto& prop : pdef.exposed_min_max_terms) {
		o + substitute{ "exname", prop.exposed_name };
		o + substitute{ "internal_tag", "m_" + prop.exposed_name };
		o + substitute{ "obj", prop.derived_from_slot->actual_table->name };

		if(prop.from_link) {
			o + substitute{ "rtype", prop.from_link->type_name };
			o + substitute{ "ptype", prop.from_link->type_name + "_id" };
			o + substitute{ "propname", prop.from_link->property_name };

			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return @rtype@_@id_type@(m_container, m_container.@obj@_get_@propname@( @internal_tag@ ))";
			};
			if(!is_const) {
				o + "void @namesp@set_@exname@(@ptype@ v) const noexcept" + block{
					o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
				};
			}
		} else if(prop.from_property) {
			o + substitute{ "propname", prop.from_property->name };
			o + substitute{ "ptype", prop.from_property->data_type };
			o + substitute{ "index_type", prop.from_property->array_index_type };

			switch(prop.from_property->type) {
				case property_type::array_bitfield:
					o + "bool @namesp@get_@exname@(@index_type@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@index_type@ i, bool v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::array_other:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id(), @index_type@())) @namesp@get_@exname@(@internal_tag@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@internal_tag@ i, @ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::array_vectorizable:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id(), @index_type@())) @namesp@get_@exname@(@internal_tag@ i) const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@, i );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@internal_tag@ i, @ptype@ v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, i, v )";
						};
					}
					break;
				case property_type::bitfield:
					o + "bool @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(bool v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::object:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::other:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ const& v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::vectorizable:
					o + "decltype(m_container.@obj@_get_@propname@(@obj@_id())) @namesp@get_@exname@() const" + block{
						o + "return m_container.@obj@_get_@propname@( @internal_tag@ );";
					};
					if(!is_const) {
						o + "void @namesp@set_@exname@(@ptype@ v) const" + block{
							o + "m_container.@obj@_set_@propname@( @internal_tag@, v )";
						};
					}
					break;
				case property_type::special_vector:
					break;
			}
		} else {
			o + substitute{ "rtype", prop.derived_from_slot->actual_table->name };
			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return @rtype@_@id_type@(m_container, @internal_tag@ )";
			};
		}
	}
	for(auto& prop : pdef.exposed_aggregates) {
		o + substitute{ "exname", prop.exposed_name };
		if(prop.aggregate_name == "count") {
			o + "int32_t @namesp@get_@exname@() const noexcept" + block{
				o + "return m_@exname@;";
			};
		} else if(prop.from_link) {
			o + substitute{ "rtype", prop.from_link->type_name};
			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return m_@exname@;";
			};
		} else if(prop.from_property) {
			o + substitute{ "obj", prop.derived_from_slot->actual_table->name };
			o + substitute{ "propname", prop.from_property->name };
			o + substitute{ "ptype", prop.from_property->data_type };

			switch(prop.from_property->type) {
				case property_type::bitfield:
					o + "bool @namesp@get_@exname@() const noexcept" + block{
						o + "return m_@exname@;";
					};
					break;
				case property_type::object:
					o + "@ptype@ const& @namesp@get_@exname@() const noexcept" + block{
						o + "return m_@exname@;";
					};
					break;
				case property_type::other:
					o + "@ptype@ const& @namesp@get_@exname@() const noexcept" + block{
						o + "return m_@exname@;";
					};
					break;
				case property_type::vectorizable:
					o + "@ptype@ @namesp@get_@exname@() const noexcept" + block{
						o + "return m_@exname@;";
					};
					break;
				default:
					break;
			}
		} else {
			o + substitute{ "rtype", prop.derived_from_slot->actual_table->name };
			o + "@rtype@_@id_type@ @namesp@get_@exname@() const noexcept" + block{
				o + "return m_@exname@;";
			};
		}
	}
	for(auto& table : pdef.table_slots) {
		if(table.expose_has_name) {
			o + substitute{ "tnaame", table.reference_name };
			o + substitute{ "int", table.internally_named_as };
			o + "bool @namesp@has_@tname@() const noexcept" + block{
				o + "return bool(@int@)";
			};
		}
	}

	o + line_break{};
	return o;
}
