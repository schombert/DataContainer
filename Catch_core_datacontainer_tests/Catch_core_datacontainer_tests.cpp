#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\ve.hpp"
#include "..\CommonIncludes\common_types.hpp"
#include "car_owner_basic.hpp"

TEST_CASE("simple case", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();
	
	REQUIRE( (size_t(ptr.get()) & 63) == 0 );

	REQUIRE(ptr->car_size() == 0);

	auto new_car = ptr->create_car();

	REQUIRE(ptr->car_size() == 1);
	REQUIRE(new_car.index() == 0);
	REQUIRE(bool(new_car) == true);
	REQUIRE(ptr->is_valid_car(new_car) == true);

	REQUIRE(ptr->car_get_wheels(new_car) == 0);
	REQUIRE(ptr->car_get_resale_value(new_car) == 0.0f);

	REQUIRE(ptr->car_get_wheels(car_owner_basic::car_id()) == 0);
	REQUIRE(ptr->car_get_resale_value(car_owner_basic::car_id()) == 0.0f);

	ptr->car_get_wheels(new_car) = 4;
	ptr->car_set_resale_value(new_car, 100.5f);

	REQUIRE(ptr->car_get_wheels(new_car) == 4);
	REQUIRE(ptr->car_get_resale_value(new_car) == 100.5f);

	ptr->car_pop_back();
	REQUIRE(ptr->car_size() == 0);
	REQUIRE(ptr->car_get_wheels(new_car) == 0);
	REQUIRE(ptr->car_get_resale_value(new_car) == 0.0f);
	REQUIRE(ptr->is_valid_car(new_car) == false);


	auto new_person = ptr->create_person();

	REQUIRE(new_person == car_owner_basic::person_id(0));
	REQUIRE(ptr->person_get_age(new_person) == 0);

	ptr->person_set_age(new_person, 21);

	REQUIRE(ptr->person_get_age(new_person) == 21);

	auto car_a = ptr->create_car();
	auto car_b = ptr->create_car();

	REQUIRE(car_a != car_b);
	REQUIRE(ptr->is_valid_car_ownership(ptr->get_car_ownership_from_car_as_owned_car(car_a)) == false);
	REQUIRE(ptr->is_valid_car_ownership(ptr->get_car_ownership_from_car_as_owned_car(car_b)) == false);
}

TEST_CASE("basic relationship functions", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);
	
	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->is_valid_car_ownership(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);

	int32_t count = 0;
	bool found_car = false;
	ptr->person_for_each_car_ownership_as_owner(personb, [&](car_owner_basic::car_id i) {
		++count;
		if(i == carb)
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_id i) {
		++count;
		if(i == carb)
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	auto r2 = ptr->try_create_car_ownership(personb, carb);
	REQUIRE(!ptr->is_valid_car_ownership(r2));

	auto r3 = ptr->try_create_car_ownership(persona, cara);

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_id i) {
		++count;
		if(i == carb)
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_ownership_set_owner(r1, car_owner_basic::person_id());

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_id i) {
		++count;
		if(i == carb)
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == false);

	auto r4 = ptr->force_create_car_ownership(personb, cara);
	REQUIRE(ptr->is_valid_car_ownership(r4));

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_id i) {
		++count;
		if(i == cara)
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(personb, [&](car_owner_basic::car_id i) {
		++count;
		if(i == cara)
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

}