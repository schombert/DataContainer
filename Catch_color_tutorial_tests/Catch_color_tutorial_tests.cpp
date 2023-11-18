#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
#include "color_container.hpp"
#include "color_tutorial.hpp"
#include "old_color_container.hpp"
#include "common_types.cpp"

TEST_CASE("test basic access", "[tutorial_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	ptr->create_colored_thing();
	ptr->create_colored_thing();
	auto h = fatten(*ptr, ptr->create_colored_thing());
	ptr->create_colored_thing();

	h.set_blue(5.0f);
	REQUIRE(h.get_blue() == 5.0f);
	REQUIRE(h.get_color().blue == 5.0f);
}

TEST_CASE("test deserialize", "[tutorial_tests]") {

	std::byte* bptr;
	size_t sz = 0;

	auto ptr = std::make_unique< old::data_container >();
	ptr->create_colored_thing();
	auto id = fatten(*ptr, ptr->create_colored_thing());
	id.set_blue(2.0f);
	id.set_green(3.0f);
	id.set_red(4.0f);

	sz = ptr->serialize_size(ptr->serialize_entire_container_record());
	bptr = new std::byte[sz];
	{
		auto iptr = bptr;
		ptr->serialize(iptr, ptr->serialize_entire_container_record());
		REQUIRE(iptr == bptr + sz);
	}


	auto ptrb = std::make_unique< dcon::data_container >();

	{
		dcon::load_record record;
		std::byte const* iptr = bptr;
		ptrb->deserialize(iptr, bptr + sz, record);
		ptrb->deserialize_rgb(bptr, bptr + sz, record);

		REQUIRE(record.colored_thing_color);

		REQUIRE(fatten(*ptrb, dcon::colored_thing_id(1)).get_blue() == 2.0f);
		REQUIRE(fatten(*ptrb, dcon::colored_thing_id(1)).get_green() == 3.0f);
		REQUIRE(fatten(*ptrb, dcon::colored_thing_id(1)).get_red() == 4.0f);
	}

	delete[] bptr;
}

TEST_CASE("test SIMD", "[tutorial_tests]") {
	{
		auto ptr = std::make_unique< dcon::data_container >();

		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(1.0f);
			h.set_green(3.0f);
		}
		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(7.0f);
			h.set_green(1.0f);
		}
		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(1.0f);
			h.set_green(2.0f);
		}

		ptr->create_colored_thing();

		ptr->execute_serial_over_colored_thing([p = ptr.get()](auto position){
			auto red_value = ve::apply(
				[p](dcon::colored_thing_id i) { return p->colored_thing_get_color(i).red; },
				position);
			auto green_value = ve::apply(
				[p](dcon::colored_thing_id i) { return p->colored_thing_get_color(i).green; },
				position);
			ve::apply(
				[p](dcon::colored_thing_id i, float v) { p->colored_thing_get_color(i).blue = v; },
				position, (red_value + green_value) / 2.0f);
		});

		REQUIRE(ptr->colored_thing_get_color(dcon::colored_thing_id(0)).blue == 2.0f);
		REQUIRE(ptr->colored_thing_get_color(dcon::colored_thing_id(1)).blue == 4.0f);
		REQUIRE(ptr->colored_thing_get_color(dcon::colored_thing_id(2)).blue == 1.5f);
	}
	{
		auto ptr = std::make_unique< old::data_container >();

		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(1.0f);
			h.set_green(3.0f);
		}
		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(7.0f);
			h.set_green(1.0f);
		}
		{
			auto h = fatten(*ptr, ptr->create_colored_thing());
			h.set_red(1.0f);
			h.set_green(2.0f);
		}

		ptr->create_colored_thing();

		ptr->execute_serial_over_colored_thing([p = ptr.get()](auto position){
			p->colored_thing_set_blue(position,
				(p->colored_thing_get_red(position) + p->colored_thing_get_green(position)) / 2.0f);
		});

		REQUIRE(ptr->colored_thing_get_blue(old::colored_thing_id(0)) == 2.0f);
		REQUIRE(ptr->colored_thing_get_blue(old::colored_thing_id(1)) == 4.0f);
		REQUIRE(ptr->colored_thing_get_blue(old::colored_thing_id(2)) == 1.5f);
	}
}