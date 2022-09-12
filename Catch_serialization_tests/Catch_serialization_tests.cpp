#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"

struct c_struct {
	int32_t v1 = 5;
	double v2 = 0.0;
};

struct c_struct_b {
	float total = 0.0f;
};

#include "old_ser.hpp"
#include "new_ser.hpp"

uint64_t os::data_container::serialize_size(std::vector<float> const& obj) const {
	return sizeof(uint16_t) + sizeof(float) * obj.size();
}

void os::data_container::serialize(std::byte*& output_buffer, std::vector<float> const& obj) const {
	*reinterpret_cast<uint16_t*>(output_buffer) = uint16_t(obj.size());
	output_buffer += sizeof(uint16_t);
	std::memcpy(output_buffer, obj.data(), sizeof(float) * obj.size());
	output_buffer += sizeof(float) * obj.size();
}

void os::data_container::deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const {
	uint16_t sz = input_buffer + sizeof(uint16_t) <= end ?
		*reinterpret_cast<uint16_t const*>(input_buffer) : 0;
	obj.resize(sz);
	input_buffer += sizeof(uint16_t);
	std::memcpy(obj.data(), input_buffer, std::min(sizeof(float) * sz, size_t(end - input_buffer)));
	input_buffer += sizeof(float) * sz;
}

void ns::data_container::deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const {
	uint16_t sz = input_buffer + sizeof(uint16_t) <= end ?
		*reinterpret_cast<uint16_t const*>(input_buffer) : 0;
	obj.resize(sz);
	input_buffer += sizeof(uint16_t);
	std::memcpy(obj.data(), input_buffer, std::min(sizeof(float) * sz, size_t(end - input_buffer)));
	input_buffer += sizeof(float) * sz;
}

c_struct_b ns::data_container::convert_type(std::vector<float> const& source, c_struct_b*) const {
	c_struct_b result;
	for(int i = 0; i < source.size(); ++i) {
		result.total += source[i];
	}
	return result;
}

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
		ptr->thingy_pooled_v_add_unique(target, int16_t(-5));
		ptr->thingy_resize_big_array(2);
		ptr->thingy_resize_big_array_bf(4);

		ptr->thingy_set_big_array(target, 0, 1.5f);
		ptr->thingy_set_big_array(target, 1, 3.5f);
		ptr->thingy_set_big_array_bf(target, 3, true);
		target.get_i_value() = int16_t(35);
		target.get_f_value() = 7.5f;
		target.pooled_v_push_back(3);
		target.pooled_v_push_back(5);
		target.set_bf_value(true);
		target.get_custom_struct().v1 = 7;
		target.get_custom_struct().v2 = 9.0;

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

		REQUIRE(target.get_custom_struct().v1 == 5);
		REQUIRE(target.get_custom_struct().v2 == 0.0);
		REQUIRE(target.get_bf_value());
		REQUIRE(target.get_i_value() == 35);
		REQUIRE(target.get_f_value() == 7.5f);
		REQUIRE(target.get_pooled_v_size() == 0);
		REQUIRE(target.get_obj_value().size() == 0);
		REQUIRE(target.get_pooled_v_size() == 0);
		REQUIRE(target.get_big_array_size() == 0);
		REQUIRE(target.get_big_array_bf_size() == 0);


	}

	delete[] bptr;
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
		ptr->thingy_pooled_v_add_unique(target, int16_t(-5));
		ptr->thingy_resize_big_array(2);
		ptr->thingy_resize_big_array_bf(4);

		ptr->thingy_set_big_array(target, 0, 1.5f);
		ptr->thingy_set_big_array(target, 1, 3.5f);
		ptr->thingy_set_big_array_bf(target, 3, true);
		target.get_i_value() = int16_t(35);
		target.get_f_value() = 7.5f;
		target.pooled_v_push_back(3);
		target.pooled_v_push_back(5);
		target.set_bf_value(true);
		target.get_custom_struct().v1 = 7;
		target.get_custom_struct().v2 = 9.0;

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

		REQUIRE(target.get_custom_struct().v1 == 7);
		REQUIRE(target.get_custom_struct().v2 == 9.0);
		REQUIRE(target.get_big_array_size() == 2);
		REQUIRE(target.get_big_array_bf_size() == 4);
		REQUIRE(target.get_pooled_v_size() == 3);
		REQUIRE(target.get_pooled_v_at(1) == 3);
		REQUIRE(target.get_pooled_v_at(2) == 5);
		REQUIRE(ptr->thingy_get_obj_value(target).size() == 2);
		REQUIRE(ptr->thingy_get_obj_value(target)[1] == 4.0f);
		REQUIRE(ptr->thingy_pooled_v_contains(target, int16_t(-5)) == true);
		REQUIRE(ptr->thingy_get_big_array(target, 0) == 1.5f);
		REQUIRE(ptr->thingy_get_big_array(target, 1) == 3.5f);
		REQUIRE(ptr->thingy_get_big_array_bf(target, 3) == true);
	}

	delete[] bptr;
}

TEST_CASE("deserialize a related object", "[serialization_tests]") {
	auto ptr = std::make_unique< os::data_container >();

	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	auto j1 = ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	auto target = fatten(*ptr, ptr->create_thingy());
	ptr->create_thingy();
	ptr->create_thingy();


	target.get_i_value() = int16_t(35);
	target.get_f_value() = 7.5f;

	auto s1 = ptr->create_thingy2();
	auto s2 = ptr->create_thingy2();
	auto s3 = ptr->create_thingy2();
	auto s4 = ptr->create_thingy2();
	auto s5 = ptr->create_thingy2();
	auto s6 = ptr->create_thingy2();
	auto s7 = ptr->create_thingy2();

	ptr->thingy2_set_some_value(s1, 1);
	ptr->thingy2_set_some_value(s2, 2);
	ptr->thingy2_set_some_value(s3, 3);
	ptr->thingy2_set_some_value(s4, 4);
	ptr->thingy2_set_some_value(s5, 5);
	ptr->thingy2_set_some_value(s6, 6);
	ptr->thingy2_set_some_value(s7, 7);



	REQUIRE(bool(ptr->try_create_dummy_rel(target, s1)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s2)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s3)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s4)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s5)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s6)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s7)));

	REQUIRE(target.get_i_value() == 35);
	REQUIRE(target.get_f_value() == 7.5f);

	REQUIRE(target.has_right_from_dummy_rel(s1));
	REQUIRE(target.has_right_from_dummy_rel(s2));
	REQUIRE(target.has_right_from_dummy_rel(s5));
	REQUIRE(target.has_right_from_dummy_rel(s7));

	REQUIRE(!target.has_right_from_dummy_rel(s3));
	REQUIRE(!target.has_right_from_dummy_rel(s4));
	REQUIRE(!target.has_right_from_dummy_rel(s6));

	REQUIRE(ptr->thingy2_get_some_value(s1) == 1);
	REQUIRE(ptr->thingy2_get_some_value(s4) == 4);
	REQUIRE(ptr->thingy2_get_some_value(s7) == 7);

	REQUIRE(ptr->get_dummy_rel_by_joint(target, s5).value == 5);

	std::byte* bptr;
	size_t sz = 0;

	sz = ptr->serialize_size(ptr->make_serialize_record_store_right());
	bptr = new std::byte[sz];
	{
		auto iptr = bptr;
		ptr->serialize(iptr, ptr->make_serialize_record_store_right());
		REQUIRE(iptr == bptr + sz);
	}

	ptr->thingy2_resize(0);
	
	REQUIRE(target.get_i_value() == 35);
	REQUIRE(target.get_f_value() == 7.5f);

	REQUIRE(ptr->get_dummy_rel_by_joint(target, s5).value == 0);
	REQUIRE(!target.has_right_from_dummy_rel(s1));
	REQUIRE(!target.has_right_from_dummy_rel(s2));
	REQUIRE(!target.has_right_from_dummy_rel(s5));
	REQUIRE(!target.has_right_from_dummy_rel(s7));
	REQUIRE(!target.has_right_from_dummy_rel(s3));
	REQUIRE(!target.has_right_from_dummy_rel(s4));
	REQUIRE(!target.has_right_from_dummy_rel(s6));

	REQUIRE(ptr->thingy2_get_some_value(s1) == 0);
	REQUIRE(ptr->thingy2_get_some_value(s4) == 0);
	REQUIRE(ptr->thingy2_get_some_value(s7) == 0);


	{
		os::load_record record;
		std::byte const* iptr = bptr;
		ptr->deserialize(iptr, iptr + sz, record);

		REQUIRE(!record.thingy_i_value);
		REQUIRE(!record.thingy_f_value);
		REQUIRE(!record.thingy_bf_value);
		REQUIRE(!record.thingy_obj_value);
		REQUIRE(!record.thingy_pooled_v);
		REQUIRE(!record.thingy_big_array);
		REQUIRE(!record.thingy_big_array_bf);
		REQUIRE(record.thingy2);
		REQUIRE(record.thingy2_some_value);
		REQUIRE(record.dummy_rel);
	}


	REQUIRE(target.get_i_value() == 35);
	REQUIRE(target.get_f_value() == 7.5f);

	REQUIRE(target.has_right_from_dummy_rel(s1));
	REQUIRE(target.has_right_from_dummy_rel(s2));
	REQUIRE(target.has_right_from_dummy_rel(s5));
	REQUIRE(target.has_right_from_dummy_rel(s7));

	REQUIRE(!target.has_right_from_dummy_rel(s3));
	REQUIRE(!target.has_right_from_dummy_rel(s4));
	REQUIRE(!target.has_right_from_dummy_rel(s6));

	REQUIRE(ptr->thingy2_get_some_value(s1) == 1);
	REQUIRE(ptr->thingy2_get_some_value(s4) == 4);
	REQUIRE(ptr->thingy2_get_some_value(s7) == 7);

	REQUIRE(ptr->get_dummy_rel_by_joint(target, s5).value == 5);

	delete[] bptr;
}

TEST_CASE("upgrading", "[serialization_tests]") {
	auto ptr = std::make_unique< os::data_container >();

	ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	auto j1 = ptr->create_thingy();
	ptr->create_thingy();
	ptr->create_thingy();
	auto target = fatten(*ptr, ptr->create_thingy());
	ptr->create_thingy();
	ptr->create_thingy();

	target.get_i_value() = int16_t(35);
	target.get_f_value() = 7.5f;

	auto s1 = ptr->create_thingy2();
	auto s2 = ptr->create_thingy2();
	auto s3 = ptr->create_thingy2();
	auto s4 = ptr->create_thingy2();
	auto s5 = ptr->create_thingy2();
	auto s6 = ptr->create_thingy2();
	auto s7 = ptr->create_thingy2();

	ptr->thingy2_set_some_value(s1, 1);
	ptr->thingy2_set_some_value(s2, 2);
	ptr->thingy2_set_some_value(s3, 3);
	ptr->thingy2_set_some_value(s4, 4);
	ptr->thingy2_set_some_value(s5, 5);
	ptr->thingy2_set_some_value(s6, 6);
	ptr->thingy2_set_some_value(s7, 7);

	target.get_obj_value().push_back(3.0f);
	target.get_obj_value().push_back(4.0f);

	REQUIRE(bool(ptr->try_create_dummy_rel(target, s1)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s2)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s3)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s4)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s5)));
	REQUIRE(bool(ptr->try_create_dummy_rel(j1, s6)));
	REQUIRE(bool(ptr->try_create_dummy_rel(target, s7)));

	REQUIRE(target.get_i_value() == 35);
	REQUIRE(target.get_f_value() == 7.5f);

	REQUIRE(target.has_right_from_dummy_rel(s1));
	REQUIRE(target.has_right_from_dummy_rel(s2));
	REQUIRE(target.has_right_from_dummy_rel(s5));
	REQUIRE(target.has_right_from_dummy_rel(s7));

	REQUIRE(!target.has_right_from_dummy_rel(s3));
	REQUIRE(!target.has_right_from_dummy_rel(s4));
	REQUIRE(!target.has_right_from_dummy_rel(s6));

	REQUIRE(ptr->thingy2_get_some_value(s1) == 1);
	REQUIRE(ptr->thingy2_get_some_value(s4) == 4);
	REQUIRE(ptr->thingy2_get_some_value(s7) == 7);

	REQUIRE(ptr->get_dummy_rel_by_joint(target, s5).value == 5);

	std::byte* bptr;
	size_t sz = 0;

	sz = ptr->serialize_size(ptr->serialize_entire_container_record());
	bptr = new std::byte[sz];
	{
		auto iptr = bptr;
		ptr->serialize(iptr, ptr->serialize_entire_container_record());
		REQUIRE(iptr == bptr + sz);
	}

	
	auto ptrb = std::make_unique< ns::data_container >();

	{
		ns::load_record record;
		std::byte const* iptr = bptr;
		ptrb->deserialize(iptr, iptr + sz, record);

		REQUIRE(record.thingy_i_value);
		REQUIRE(record.thingy_f_value);
		REQUIRE(record.thingy_obj_value);
		REQUIRE(record.thingy_custom_struct);
		REQUIRE(record.thingy_obj_value);
		REQUIRE(record.thingy2);
		REQUIRE(record.thingy2_some_value);
		REQUIRE(record.dummy_rel);
	}

	auto targetb = fatten(*ptrb, ns::thingy_id(ns::thingy_id::value_base_t(target.id.index())));

	auto s1b = ns::thingy2_id(ns::thingy2_id::value_base_t(s1.index()));
	auto s2b = ns::thingy2_id(ns::thingy2_id::value_base_t(s2.index()));
	auto s3b = ns::thingy2_id(ns::thingy2_id::value_base_t(s3.index()));
	auto s4b = ns::thingy2_id(ns::thingy2_id::value_base_t(s4.index()));
	auto s5b = ns::thingy2_id(ns::thingy2_id::value_base_t(s5.index()));
	auto s6b = ns::thingy2_id(ns::thingy2_id::value_base_t(s6.index()));
	auto s7b = ns::thingy2_id(ns::thingy2_id::value_base_t(s7.index()));

	REQUIRE(targetb.get_obj_value().total == 7.0f);

	REQUIRE(targetb.get_i_value() == 35);
	REQUIRE(targetb.get_f_value() == 7.5f);

	REQUIRE(targetb.has_right_from_dummy_rel(s1b));
	REQUIRE(targetb.has_right_from_dummy_rel(s2b));
	REQUIRE(targetb.has_right_from_dummy_rel(s5b));
	REQUIRE(targetb.has_right_from_dummy_rel(s7b));

	REQUIRE(!targetb.has_right_from_dummy_rel(s3b));
	REQUIRE(!targetb.has_right_from_dummy_rel(s4b));
	REQUIRE(!targetb.has_right_from_dummy_rel(s6b));

	REQUIRE(ptrb->thingy2_get_some_value(s1b) == 1);
	REQUIRE(ptrb->thingy2_get_some_value(s4b) == 4);
	REQUIRE(ptrb->thingy2_get_some_value(s7b) == 7);

	REQUIRE(ptrb->get_dummy_rel_by_joint(targetb, s5b).value == 5);

	delete[] bptr;
}

