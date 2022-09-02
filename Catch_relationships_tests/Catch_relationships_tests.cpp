#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
#include "relation.hpp"

TEST_CASE("double relation test", "[relationships_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();
	auto o1 = fatten(*ptr, ptr->create_thingyA());
	auto o2 = fatten(*ptr, ptr->create_thingyA());

	auto r1 = fatten(*ptr, ptr->try_create_relate_same(o1, o2));

	REQUIRE(bool(r1));
	REQUIRE(ptr->relate_same_size() == 2);
	REQUIRE(r1.get_left() == o1);
	REQUIRE(r1.get_right() == o2);
}