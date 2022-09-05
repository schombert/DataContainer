#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
#include "old_ser.hpp"

TEST_CASE("header record tests", "[serialization_tests]") {
	dcon::record_header tr(17, "test_type", "test_obj", "test_property");

	REQUIRE(tr.serialize_size() == sizeof(uint64_t) + 9 + 8 + 13 + 3);

	std::byte output_array[sizeof(uint64_t) + 9 + 8 + 13 + 3 + 1];
	output_array[sizeof(uint64_t) + 9 + 8 + 13 + 3] = std::byte(0xFC);

	std::byte* outptr = output_array;

	REQUIRE(tr.serialize_size() == sizeof(uint64_t) + 9 + 8 + 13 + 3);
	tr.serialize(outptr);

	REQUIRE(outptr == output_array + sizeof(uint64_t) + 9 + 8 + 13 + 3);
	REQUIRE(output_array[sizeof(uint64_t) + 9 + 8 + 13 + 3] == std::byte(0xFC));

	dcon::record_header loading;

	std::byte const* inptr = output_array;
	loading.deserialize(inptr, outptr);

	REQUIRE(inptr == outptr);
	REQUIRE(loading.is_type("test_type"));
	REQUIRE(!loading.is_type("test"));
	REQUIRE(!loading.is_type("test_type_extra"));
	REQUIRE(loading.is_object("test_obj"));
	REQUIRE(loading.is_property("test_property"));
}

TEST_CASE("simple serialzie", "[serialization_tests]") {
	std::byte* bptr;
	size_t sz = 0;
	{
		auto ptr = std::make_unique< os::data_container >();

		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		auto target = fatten(*ptr, ptr->create_thingy());
		ptr->create_thingy();
		ptr->create_thingy();


		ptr->thingy_get_obj_value(target).push_back(3.0f);
		ptr->thingy_get_obj_value(target).push_back(4.0f);
		ptr->thingy_pooled_v_add_unique(target, -5i16);
		ptr->thingy_resize_big_array(2);
		ptr->thingy_resize_big_array_bf(4);

		ptr->thingy_set_big_array(target, 0, 1.5f);
		ptr->thingy_set_big_array(target, 1, 3.5f);
		ptr->thingy_set_big_array_bf(target, 3, true);
		target.get_i_value() = 35i16;
		target.get_f_value() = 7.5f;
		target.pooled_v_push_back(3);
		target.pooled_v_push_back(5);
		target.set_bf_value(true);

		sz = ptr->serialize_size(ptr->make_serialize_record_store_simple());
		bptr = new std::byte[sz];
		auto iptr = bptr;
		ptr->serialize(iptr, ptr->make_serialize_record_store_simple());

		REQUIRE(iptr == bptr + sz);
	}


	{
		auto ptr = std::make_unique< os::data_container >();
		os::load_record record;
		std::byte const* iptr = bptr;
		ptr->deserialize(iptr, iptr + sz, record);

		REQUIRE(iptr == bptr + sz);

		REQUIRE(record.thingy);
		REQUIRE(record.thingy_i_value);
		REQUIRE(record.thingy_f_value);
		REQUIRE(record.thingy_bf_value);
		REQUIRE(!record.thingy_obj_value);
		REQUIRE(!record.thingy_pooled_v);
		REQUIRE(!record.thingy_big_array);
		REQUIRE(!record.thingy_big_array_bf);
		REQUIRE(!record.thingy2);
		REQUIRE(!record.dummy_rel);

		REQUIRE(ptr->thingy_size() == 9);
		auto target = fatten(*ptr, os::thingy_id(6));

		REQUIRE(target.get_bf_value());
		REQUIRE(target.get_i_value() == 35);
		REQUIRE(target.get_f_value() == 7.5f);
		REQUIRE(target.get_pooled_v_size() == 0);
		REQUIRE(target.get_obj_value().size() == 0);
		REQUIRE(target.get_pooled_v_size() == 0);
		REQUIRE(target.get_big_array_size() == 0);
		REQUIRE(target.get_big_array_bf_size() == 0);


	}
}

TEST_CASE("serialzie complex props", "[serialization_tests]") {
	std::byte* bptr;
	size_t sz = 0;
	{
		auto ptr = std::make_unique< os::data_container >();

		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		ptr->create_thingy();
		auto target = fatten(*ptr, ptr->create_thingy());
		ptr->create_thingy();
		ptr->create_thingy();


		ptr->thingy_get_obj_value(target).push_back(3.0f);
		ptr->thingy_get_obj_value(target).push_back(4.0f);
		ptr->thingy_pooled_v_add_unique(target, -5i16);
		ptr->thingy_resize_big_array(2);
		ptr->thingy_resize_big_array_bf(4);

		ptr->thingy_set_big_array(target, 0, 1.5f);
		ptr->thingy_set_big_array(target, 1, 3.5f);
		ptr->thingy_set_big_array_bf(target, 3, true);
		target.get_i_value() = 35i16;
		target.get_f_value() = 7.5f;
		target.pooled_v_push_back(3);
		target.pooled_v_push_back(5);
		target.set_bf_value(true);

		sz = ptr->serialize_size(ptr->make_serialize_record_store_left());
		bptr = new std::byte[sz];
		auto iptr = bptr;
		ptr->serialize(iptr, ptr->make_serialize_record_store_left());

		REQUIRE(iptr == bptr + sz);
	}


	{
		auto ptr = std::make_unique< os::data_container >();
		os::load_record record;
		std::byte const* iptr = bptr;
		ptr->deserialize(iptr, iptr + sz, record);

		REQUIRE(record.thingy);
		REQUIRE(record.thingy_i_value);
		REQUIRE(record.thingy_f_value);
		REQUIRE(record.thingy_bf_value);
		REQUIRE(record.thingy_obj_value);
		REQUIRE(record.thingy_pooled_v);
		REQUIRE(record.thingy_big_array);
		REQUIRE(record.thingy_big_array_bf);
		REQUIRE(!record.thingy2);
		REQUIRE(!record.dummy_rel);

		REQUIRE(iptr == bptr + sz);

		REQUIRE(ptr->thingy_size() == 9);
		auto target = fatten(*ptr, os::thingy_id(6));

		REQUIRE(target.get_bf_value());
		REQUIRE(target.get_i_value() == 35);
		REQUIRE(target.get_f_value() == 7.5f);

		REQUIRE(target.get_big_array_size() == 2);
		REQUIRE(target.get_big_array_bf_size() == 4);
		REQUIRE(target.get_pooled_v_size() == 3);
		REQUIRE(target.get_pooled_v_at(1) == 3);
		REQUIRE(target.get_pooled_v_at(2) == 5);
		REQUIRE(ptr->thingy_get_obj_value(target).size() == 2);
		REQUIRE(ptr->thingy_get_obj_value(target)[1] == 4.0f);
		REQUIRE(ptr->thingy_pooled_v_contains(target, -5i16) == true);
		REQUIRE(ptr->thingy_get_big_array(target, 0) == 1.5f);
		REQUIRE(ptr->thingy_get_big_array(target, 1) == 3.5f);
		REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == true);
	}
}