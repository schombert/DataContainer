#define CATCH_CONFIG_MAIN 
#define DCON_NO_VE
#define DCON_USE_EXCEPTIONS

#include "catch.hpp"
#include "common_types.hpp"
#include "objects_def.hpp"

TEST_CASE("hooked_functions", "[objects_and_properties_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	ptr->thingy_set_some_value(ptr->create_thingy(), 1);
	ptr->thingy_set_some_value(ptr->create_thingy(), 2);
	ptr->thingy_set_some_value(ptr->create_thingy(), 3);
	ptr->thingy_set_some_value(ptr->create_thingy(), 4);

	REQUIRE(ptr->counter == 4);
	ptr->counter = 0;
	
	REQUIRE(ptr->thingy_get_some_value(dcon::thingy_id(2)) == 3);

	ptr->delete_thingy(dcon::thingy_id(2));

	REQUIRE(ptr->counter == 2);
	ptr->counter = 0;

	REQUIRE(ptr->thingy_get_some_value(dcon::thingy_id(2)) == 4);

	ptr->delete_thingy(dcon::thingy_id(2));
	REQUIRE(ptr->counter == 1);
}

TEST_CASE("property_types", "[objects_and_properties_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	auto target = ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();

	REQUIRE(ptr->thingy_get_bf_value(target) == false);
	REQUIRE(ptr->thingy_get_bool_value(target) == false);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy_get_pooled_v_size(target) == 0);

	ptr->thingy_set_bf_value(target, true);
	ptr->thingy_set_bool_value(target, true);
	ptr->thingy_get_obj_value(target).push_back(3.0f);
	ptr->thingy_get_obj_value(target).push_back(4.0f);
	ptr->thingy_pooled_v_add_unique(target, -5i16);

	REQUIRE(ptr->thingy_get_bf_value(target) == true);
	REQUIRE(ptr->thingy_get_bool_value(target) == true);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 2);
	REQUIRE(ptr->thingy_get_obj_value(target)[1] == 4.0f);
	REQUIRE(ptr->thingy_pooled_v_contains(target, -5i16) == true);
	REQUIRE(ptr->thingy_get_pooled_v_size(target) == 1);

	ptr->delete_thingy(target);

	REQUIRE(ptr->thingy_get_bf_value(target) == false);
	REQUIRE(ptr->thingy_get_bool_value(target) == false);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy_get_pooled_v_size(target) == 0);
}