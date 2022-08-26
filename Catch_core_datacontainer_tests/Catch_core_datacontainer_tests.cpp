#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\ve.hpp"
#include "..\CommonIncludes\common_types.hpp"
#include "car_owner_basic.hpp"

TEST_CASE("simple case", "[core_datacontainer_tests]") {
	auto ptr = std::make_unique< car_owner_basic::data_container >();
	
	REQUIRE( (size_t(ptr.get()) & 63) == 0 );

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
