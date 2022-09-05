#define CATCH_CONFIG_MAIN 
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
	auto target = fatten(*ptr, ptr->create_thingy());
	ptr->create_thingy();
	ptr->create_thingy();

	REQUIRE(ptr->thingy_get_bf_value(target) == false);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy_get_pooled_v_size(target) == 0);
	REQUIRE(ptr->thingy_get_big_array_size() == 0);
	REQUIRE(ptr->thingy_get_big_array_bf_size() == 0);

	ptr->thingy_set_bf_value(target, true);
	ptr->thingy_get_obj_value(target).push_back(3.0f);
	ptr->thingy_get_obj_value(target).push_back(4.0f);
	ptr->thingy_pooled_v_add_unique(target, -5i16);
	ptr->thingy_resize_big_array(2);
	ptr->thingy_resize_big_array_bf(4);

	target.set_some_value(35);
	REQUIRE(target.get_pooled_v_size() == 1);
	target.pooled_v_push_back(3);
	target.pooled_v_push_back(5);

	REQUIRE(ptr->thingy_get_big_array_size() == 2);
	REQUIRE(ptr->thingy_get_big_array_bf_size() == 4);

	REQUIRE(ptr->thingy_get_big_array(target, 0) == 0.0f);
	REQUIRE(ptr->thingy_get_big_array(target, 1) == 0.0f);

	REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == false);

	REQUIRE(target.get_some_value() == 35);
	REQUIRE(target.get_pooled_v_size() == 3);
	REQUIRE(target.get_pooled_v_at(1) == 3);
	REQUIRE(target.get_pooled_v_at(2) == 5);

	ptr->thingy_set_big_array(target, 0, 1.5f);
	ptr->thingy_set_big_array(target, 1, 3.5f);
	ptr->thingy_set_big_array_bf(target, 3, true);

	REQUIRE(ptr->thingy_get_bf_value(target) == true);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 2);
	REQUIRE(ptr->thingy_get_obj_value(target)[1] == 4.0f);
	REQUIRE(ptr->thingy_pooled_v_contains(target, -5i16) == true);
	REQUIRE(ptr->thingy_get_big_array(target, 0) == 1.5f);
	REQUIRE(ptr->thingy_get_big_array(target, 1) == 3.5f);
	REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == true);

	ptr->delete_thingy(target);

	REQUIRE(ptr->thingy_get_bf_value(target) == false);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy_get_pooled_v_size(target) == 0);
	REQUIRE(ptr->thingy_get_big_array(target, 0) == 0.0f);
	REQUIRE(ptr->thingy_get_big_array(target, 1) == 0.0f);
	REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == false);
}

TEST_CASE("expandable_property_types", "[objects_and_properties_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	ptr->create_thingy2();
	ptr->create_thingy2();
	ptr->create_thingy2();
	ptr->create_thingy2();
	ptr->create_thingy2();
	ptr->create_thingy2();
	auto target = ptr->create_thingy2();
	ptr->create_thingy2();
	ptr->create_thingy2();

	REQUIRE(ptr->thingy2_get_bf_value(target) == false);
	REQUIRE(ptr->thingy2_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy2_get_pooled_v_size(target) == 0);
	REQUIRE(ptr->thingy2_get_big_array_size() == 0);
	REQUIRE(ptr->thingy2_get_big_array_bf_size() == 0);

	ptr->thingy2_set_bf_value(target, true);
	ptr->thingy2_get_obj_value(target).push_back(3.0f);
	ptr->thingy2_get_obj_value(target).push_back(4.0f);
	ptr->thingy2_pooled_v_add_unique(target, -5i16);
	ptr->thingy2_resize_big_array(2);
	ptr->thingy2_resize_big_array_bf(4);

	REQUIRE(ptr->thingy2_get_big_array_size() == 2);
	REQUIRE(ptr->thingy2_get_big_array_bf_size() == 4);

	REQUIRE(ptr->thingy2_get_big_array(target, 0) == 0.0f);
	REQUIRE(ptr->thingy2_get_big_array(target, 1) == 0.0f);

	REQUIRE(ptr->thingy2_get_big_array_bf(target, 3) == false);

	ptr->thingy2_set_big_array(target, 0, 1.5f);
	ptr->thingy2_set_big_array(target, 1, 3.5f);
	ptr->thingy2_set_big_array_bf(target, 3, true);

	REQUIRE(ptr->thingy2_get_bf_value(target) == true);
	REQUIRE(ptr->thingy2_get_obj_value(target).size() == 2);
	REQUIRE(ptr->thingy2_get_obj_value(target)[1] == 4.0f);
	REQUIRE(ptr->thingy2_pooled_v_contains(target, -5i16) == true);
	REQUIRE(ptr->thingy2_get_pooled_v_size(target) == 1);
	REQUIRE(ptr->thingy2_get_big_array(target, 0) == 1.5f);
	REQUIRE(ptr->thingy2_get_big_array(target, 1) == 3.5f);
	REQUIRE(ptr->thingy2_get_big_array_bf(target, 3) == true);

	ptr->delete_thingy2(target);

	REQUIRE(ptr->thingy2_get_bf_value(target) == false);
	REQUIRE(ptr->thingy2_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy2_get_pooled_v_size(target) == 0);
	REQUIRE(ptr->thingy2_get_big_array(target, 0) == 0.0f);
	REQUIRE(ptr->thingy2_get_big_array(target, 1) == 0.0f);
	REQUIRE(ptr->thingy2_get_big_array_bf(target, 3) == false);
}

TEST_CASE("hooked property getter, setter", "[objects_and_properties_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();
	auto thng = dcon::fatten(*ptr, ptr->create_thingy());

	REQUIRE(thng.get_d_value() == 6);
	REQUIRE(ptr->counter == 1);

	thng.set_dbf_value(false);

	REQUIRE(ptr->counter == 2);
}