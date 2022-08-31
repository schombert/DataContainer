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