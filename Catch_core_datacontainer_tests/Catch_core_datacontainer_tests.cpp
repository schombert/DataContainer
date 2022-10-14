#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\ve.hpp"
#include "..\CommonIncludes\common_types.hpp"
#include "car_owner_basic.hpp"
#include "car_owner_basic2.hpp"
#include "car_owner_basic3.hpp"
#include "expandable_test.hpp"


TEST_CASE("simple case", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();
	
	REQUIRE( (size_t(ptr.get()) & 63) == 0 );

	REQUIRE(ptr->car_size() == 0);

	auto new_car = ptr->create_car();

	REQUIRE(ptr->car_size() == 1);
	REQUIRE(new_car.index() == 0);
	REQUIRE(bool(new_car) == true);
	REQUIRE(ptr->car_is_valid(new_car) == true);

	REQUIRE(ptr->car_get_wheels(new_car) == 0);
	REQUIRE(ptr->car_get_resale_value(new_car) == 0.0f);

	REQUIRE(ptr->car_get_wheels(car_owner_basic::car_id()) == 0);
	REQUIRE(ptr->car_get_resale_value(car_owner_basic::car_id()) == 0.0f);

	ptr->car_get_wheels(new_car) = 4;
	ptr->car_set_resale_value(new_car, 100.5f);

	REQUIRE(ptr->car_get_wheels(new_car) == 4);
	REQUIRE(ptr->car_get_resale_value(new_car) == 100.5f);

	ptr->pop_back_car();
	REQUIRE(ptr->car_size() == 0);
	REQUIRE(ptr->car_get_wheels(new_car) == 0);
	REQUIRE(ptr->car_get_resale_value(new_car) == 0.0f);
	REQUIRE(ptr->car_is_valid(new_car) == false);


	auto new_person = ptr->create_person();

	REQUIRE(new_person == car_owner_basic::person_id(0));
	REQUIRE(ptr->person_get_age(new_person) == 0);

	ptr->person_set_age(new_person, 21);

	REQUIRE(ptr->person_get_age(new_person) == 21);

	auto car_a = ptr->create_car();
	auto car_b = ptr->create_car();

	REQUIRE(car_a != car_b);
	REQUIRE(ptr->car_ownership_is_valid(ptr->car_get_car_ownership_as_owned_car(car_a)) == false);
	REQUIRE(ptr->car_ownership_is_valid(ptr->car_get_car_ownership_as_owned_car(car_b)) == false);
}

TEST_CASE("simple case the good syntax", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();

	REQUIRE((size_t(ptr.get()) & 63) == 0);

	REQUIRE(ptr->car_size() == 0);

	auto new_car = car_owner_basic::fatten(*ptr, ptr->create_car());

	REQUIRE(ptr->car_size() == 1);
	REQUIRE(bool(new_car) == true);
	REQUIRE(new_car.is_valid() == true);

	REQUIRE(new_car.get_wheels() == 0);
	REQUIRE(new_car.get_resale_value() == 0.0f);


	new_car.get_wheels() = 4;
	new_car.set_resale_value(100.5f);

	REQUIRE(new_car.get_wheels() == 4);
	REQUIRE(new_car.get_resale_value() == 100.5f);

	ptr->pop_back_car();
	REQUIRE(new_car.is_valid() == false);


	auto new_person = car_owner_basic::fatten(*ptr, ptr->create_person());

	REQUIRE(new_person == car_owner_basic::person_id(0));
	REQUIRE(new_person.get_age() == 0);

	new_person.set_age(21);

	REQUIRE(new_person.get_age() == 21);

	auto car_a = car_owner_basic::fatten(*ptr, ptr->create_car());
	auto car_b = car_owner_basic::fatten(*ptr, ptr->create_car());

	REQUIRE(car_a != car_b);
	REQUIRE(car_a.get_car_ownership().is_valid() == false);
	REQUIRE(car_b.get_car_ownership().is_valid() == false);
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

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;
	ptr->person_for_each_car_ownership_as_owner(personb, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	count = 0;
	found_car = false;
	for(auto i : ptr->person_get_car_ownership(personb)) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	};

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	count = 0;
	found_car = false;
	for(auto i : ptr->in_car_ownership) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	}

	REQUIRE(count == 3);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;
	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;
	for(auto i : ptr->person_get_car_ownership_as_owner(persona)) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	}

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	auto r2 = ptr->try_create_car_ownership(personb, carb);
	REQUIRE(!ptr->car_ownership_is_valid(r2));

	auto r3 = ptr->try_create_car_ownership(persona, cara);

	count = 0;
	found_car = false;
	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;
	for(auto i : ptr->person_get_car_ownership_as_owner(persona)) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	}

	REQUIRE(count == 2);
	REQUIRE(found_car == true);


	ptr->car_ownership_set_owner(r1, car_owner_basic::person_id());

	count = 0;
	found_car = false;
	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == false);

	count = 0;
	found_car = false;
	for(auto i : ptr->person_get_car_ownership_as_owner(persona)) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	}

	REQUIRE(count == 1);
	REQUIRE(found_car == false);

	auto r4 = ptr->force_create_car_ownership(personb, cara);
	REQUIRE(ptr->car_ownership_is_valid(r4));

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	count = 0;
	found_car = false;
	for(auto i : ptr->person_get_car_ownership_as_owner(persona)) {
		++count;
		if(i.get_owned_car() == cara)
			found_car = true;
	}
	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(personb, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

}

TEST_CASE("remove in the other direction", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_remove_car_ownership_as_owned_car(
		carb);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == car_owner_basic::person_id());
	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	r1 = ptr->try_create_car_ownership(persona, carb);
	ptr->try_create_car_ownership(persona, carc);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	count = 0;
	found_car = false;


	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, carb) == true);
	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, cara) == false);

	ptr->person_for_each_owned_car_from_car_ownership(persona, [&](car_owner_basic::car_id) { ++count; });

	REQUIRE(count == 2);

	ptr->person_remove_all_car_ownership_as_owner(persona);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == car_owner_basic::person_id());
	REQUIRE(ptr->car_get_owner_from_car_ownership(carc) == car_owner_basic::person_id());

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](car_owner_basic::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);
}
TEST_CASE("for compatactable basic relationship functions", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< cob2::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;
	ptr->person_for_each_car_ownership_as_owner(personb, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	auto r2 = ptr->try_create_car_ownership(personb, carb);
	REQUIRE(!ptr->car_ownership_is_valid(r2));

	auto r3 = ptr->try_create_car_ownership(persona, cara);

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_ownership_set_owner(r1, cob2::person_id());

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == false);

	auto r4 = ptr->force_create_car_ownership(personb, cara);
	REQUIRE(ptr->car_ownership_is_valid(r4));

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(personb, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

}

TEST_CASE("for compatactable remove in the other direction", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< cob2::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_remove_car_ownership_as_owned_car(carb);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == cob2::person_id());
	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	r1 = ptr->try_create_car_ownership(persona, carb);
	ptr->try_create_car_ownership(persona, carc);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	count = 0;
	found_car = false;


	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, carb) == true);
	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, cara) == false);

	ptr->person_for_each_owned_car_from_car_ownership(persona, [&](cob2::car_id) { ++count; });

	REQUIRE(count == 2);

	ptr->person_remove_all_car_ownership_as_owner(persona);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == cob2::person_id());
	REQUIRE(ptr->car_get_owner_from_car_ownership(carc) == cob2::person_id());

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob2::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);
}


TEST_CASE("for erasable basic relationship functions", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< cob3::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;
	ptr->person_for_each_car_ownership_as_owner(personb, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	count = 0;
	found_car = false;
	for(auto i : ptr->in_car_ownership) {
		++count;
		if(i.get_owned_car() == carb)
			found_car = true;
	}

	REQUIRE(count == 3);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;
	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	auto r2 = ptr->try_create_car_ownership(personb, carb);
	REQUIRE(!ptr->car_ownership_is_valid(r2));

	auto r3 = ptr->try_create_car_ownership(persona, cara);

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_ownership_set_owner(r1, cob3::person_id());

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == false);

	auto r4 = ptr->force_create_car_ownership(personb, cara);
	REQUIRE(ptr->car_ownership_is_valid(r4));

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	ptr->person_for_each_car_ownership_as_owner(personb, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == cara.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

}

TEST_CASE("for erasable remove in the other direction", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< cob3::data_container >();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();

	auto persona = ptr->create_person();
	auto personb = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(persona, carb);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	int32_t count = 0;
	bool found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 1);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	ptr->car_remove_car_ownership_as_owned_car(carb);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == cob3::person_id());
	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);

	r1 = ptr->try_create_car_ownership(persona, carb);
	ptr->try_create_car_ownership(persona, carc);

	REQUIRE(bool(r1) == true);
	ptr->car_ownership_set_ownership_date(r1, 7);

	REQUIRE(ptr->car_ownership_is_valid(r1));
	REQUIRE(ptr->car_ownership_get_owner(r1) == persona);
	REQUIRE(ptr->car_ownership_get_owned_car(r1) == carb);
	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == persona);
	REQUIRE(ptr->car_get_ownership_date_from_car_ownership(carb) == 7);
	REQUIRE(ptr->car_get_car_ownership(carb) == r1);
	REQUIRE(ptr->car_get_car_ownership_as_owned_car(carb) == r1);

	count = 0;
	found_car = false;


	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 2);
	REQUIRE(found_car == true);

	count = 0;
	found_car = false;

	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, carb) == true);
	REQUIRE(ptr->person_has_owned_car_from_car_ownership(persona, cara) == false);

	ptr->person_for_each_owned_car_from_car_ownership(persona, [&](cob3::car_id) { ++count; });

	REQUIRE(count == 2);

	ptr->person_remove_all_car_ownership_as_owner(persona);

	REQUIRE(ptr->car_get_owner_from_car_ownership(carb) == cob3::person_id());
	REQUIRE(ptr->car_get_owner_from_car_ownership(carc) == cob3::person_id());

	count = 0;
	found_car = false;

	ptr->person_for_each_car_ownership_as_owner(persona, [&](cob3::car_ownership_id i) {
		++count;
		if(i.index() == carb.index())
			found_car = true;
	});

	REQUIRE(count == 0);
	REQUIRE(found_car == false);
}

TEST_CASE("objects and relationships with expandable storage", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< ex1::data_container >();

	auto ta = ptr->create_top();
	auto tb = ptr->create_top();
	auto tc = ptr->create_top();
	auto td = ptr->create_top();
	auto te = ptr->create_top();
	auto tf = ptr->create_top();

	auto ba = ptr->create_bottom();
	auto bb = ptr->create_bottom();
	auto bc = ptr->create_bottom();
	auto bd = ptr->create_bottom();
	auto be = ptr->create_bottom();
	auto bf = ptr->create_bottom();
	auto bg = ptr->create_bottom();

	REQUIRE(bool(ptr->try_create_lr_relation(ta, bc)));
	REQUIRE(bool(ptr->try_create_lr_relation(ta, bd)));
	REQUIRE(bool(ptr->try_create_lr_relation(ta, be)));
	REQUIRE(bool(ptr->try_create_lr_relation(tb, ba)));
	REQUIRE(bool(ptr->try_create_lr_relation(tb, bc)));
	REQUIRE(bool(ptr->try_create_lr_relation(tc, bf)));
	REQUIRE(bool(ptr->try_create_lr_relation(td, bc)));
	REQUIRE(bool(ptr->try_create_lr_relation(td, bd)));
	REQUIRE(bool(ptr->try_create_lr_relation(te, bf)));
	REQUIRE(bool(ptr->try_create_lr_relation(tf, bc)));

	{
		auto rng = ptr->bottom_range_of_lr_relation(bc);
		REQUIRE(rng.second - rng.first == 4);
		REQUIRE(ptr->bottom_has_left_from_lr_relation(bc, tb));
	}

	{
		auto rng = ptr->bottom_range_of_lr_relation(bd);
		REQUIRE(rng.second - rng.first == 2);
		REQUIRE(ptr->bottom_has_left_from_lr_relation(bc, ta));
		REQUIRE(!ptr->bottom_has_left_from_lr_relation(bc, te));
	}

	{
		auto rng = ptr->top_range_of_lr_relation(tc);
		REQUIRE(rng.second - rng.first == 1);
		REQUIRE(ptr->top_has_right_from_lr_relation(tc, bf));
	}

	{
		auto rng = ptr->top_range_of_lr_relation(ta);
		REQUIRE(rng.second - rng.first == 3);
		REQUIRE(ptr->top_has_right_from_lr_relation(ta, bd));
	}

	ptr->top_remove_all_lr_relation(tb);

	{
		auto rng = ptr->bottom_range_of_lr_relation(bc);
		REQUIRE(rng.second - rng.first == 3);
		REQUIRE(!ptr->bottom_has_left_from_lr_relation(bc, tb));
	}

	{
		auto rng = ptr->top_range_of_lr_relation(tb);
		REQUIRE(rng.second - rng.first == 0);
		REQUIRE(!ptr->top_has_right_from_lr_relation(ta, ba));
	}
}
