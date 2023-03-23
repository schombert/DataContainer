#define CATCH_CONFIG_MAIN 
#define DCON_USE_EXCEPTIONS
#define DCON_TRAP_INVALID_STORE

#include "catch.hpp"
#include "common_types.hpp"

struct my_struct {
	float internal_val = 2.0f;
};

#include "objects_def.hpp"

void dcon::data_container::on_create_thingy(thingy_id) {
	++counter;
}
void dcon::data_container::on_delete_thingy(thingy_id) {
	++counter;
}
void dcon::data_container::on_move_thingy(thingy_id, thingy_id) {
	++counter;
}

int32_t dcon::data_container::thingy_get_d_value(thingy_id) const {
	return 6;
}

void dcon::data_container::thingy_set_dbf_value(thingy_id, bool) {
	++counter;
}

void dcon::oop_thingy_fat_id::reset_internal() {
	set_pstruct(my_struct{4.0f});
}
int dcon::oop_thingy_const_fat_id::get_a_value(float offset) {
	return int(get_pstruct().internal_val + get_pfloat() + offset);
}

TEST_CASE("oop case", "[objects_and_properties_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	auto fid = fatten(*ptr, ptr->create_oop_thingy());

	REQUIRE(fid.get_pstruct().internal_val == 2.0f);
	fid.reset_internal();
	REQUIRE(fid.get_pstruct().internal_val == 4.0f);

	REQUIRE(fid.get_a_value(6.0f) == 10);
}

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
	REQUIRE(ptr->thingy_get_pooled_v(target).size() == 0);
	REQUIRE(ptr->thingy_get_big_array_size() == 0);
	REQUIRE(ptr->thingy_get_big_array_bf_size() == 0);

	ptr->thingy_set_bf_value(target, true);
	ptr->thingy_get_obj_value(target).push_back(3.0f);
	ptr->thingy_get_obj_value(target).push_back(4.0f);
	ptr->thingy_get_pooled_v(target).add_unique(int16_t(-5));
	ptr->thingy_resize_big_array(2);
	ptr->thingy_resize_big_array_bf(4);

	target.set_some_value(35);
	REQUIRE(target.get_pooled_v().size() == 1);
	target.get_pooled_v().push_back(3);
	target.get_pooled_v().push_back(5);

	REQUIRE(ptr->thingy_get_big_array_size() == 2);
	REQUIRE(ptr->thingy_get_big_array_bf_size() == 4);

	REQUIRE(ptr->thingy_get_big_array(target, 0) == 0.0f);
	REQUIRE(ptr->thingy_get_big_array(target, 1) == 0.0f);

	REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == false);

	REQUIRE(target.get_some_value() == 35);
	REQUIRE(target.get_pooled_v().size() == 3);
	REQUIRE(target.get_pooled_v().at(1) == 3);
	REQUIRE(target.get_pooled_v().at(2) == 5);

	ptr->thingy_set_big_array(target, 0, 1.5f);
	ptr->thingy_set_big_array(target, 1, 3.5f);
	ptr->thingy_set_big_array_bf(target, 3, true);

	REQUIRE(ptr->thingy_get_bf_value(target) == true);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 2);
	REQUIRE(ptr->thingy_get_obj_value(target)[1] == 4.0f);
	REQUIRE(ptr->thingy_get_pooled_v(target).contains(int16_t(-5)) == true);
	REQUIRE(ptr->thingy_get_big_array(target, 0) == 1.5f);
	REQUIRE(ptr->thingy_get_big_array(target, 1) == 3.5f);
	REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == true);

	ptr->delete_thingy(target);

	REQUIRE(ptr->thingy_get_bf_value(target) == false);
	REQUIRE(ptr->thingy_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy_get_pooled_v(target).size() == 0);
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
	REQUIRE(ptr->thingy2_get_pooled_v(target).size() == 0);
	REQUIRE(ptr->thingy2_get_big_array_size() == 0);
	REQUIRE(ptr->thingy2_get_big_array_bf_size() == 0);

	ptr->thingy2_set_bf_value(target, true);
	ptr->thingy2_get_obj_value(target).push_back(3.0f);
	ptr->thingy2_get_obj_value(target).push_back(4.0f);
	ptr->thingy2_get_pooled_v(target).add_unique(int16_t(-5));
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
	REQUIRE(ptr->thingy2_get_pooled_v(target).contains(int16_t(-5)) == true);
	REQUIRE(ptr->thingy2_get_pooled_v(target).size() == 1);
	REQUIRE(ptr->thingy2_get_big_array(target, 0) == 1.5f);
	REQUIRE(ptr->thingy2_get_big_array(target, 1) == 3.5f);
	REQUIRE(ptr->thingy2_get_big_array_bf(target, 3) == true);

	ptr->delete_thingy2(target);

	REQUIRE(ptr->thingy2_get_bf_value(target) == false);
	REQUIRE(ptr->thingy2_get_obj_value(target).size() == 0);
	REQUIRE(ptr->thingy2_get_pooled_v(target).size() == 0);
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