#include "code_fragments.hpp"

basic_builder make_load_record(file_def const & fd) {
	basic_builder o;
	o + "struct load_record" + class_block(
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
	);
	return o;
}
