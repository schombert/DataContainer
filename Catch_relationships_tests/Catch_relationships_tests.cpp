#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
#include "relation.hpp"
#include <array>
TEST_CASE("double relation test", "[relationships_tests]") {
	static_assert(std::is_trivially_copyable_v<dcon::thingyA_id>);
	static_assert(std::is_trivially_copy_constructible_v<dcon::thingyA_id>);
	static_assert(std::is_trivially_move_constructible_v<dcon::thingyA_id>);
	static_assert(std::is_trivially_copy_assignable_v<dcon::thingyA_id>);
	static_assert(std::is_trivially_move_assignable_v<dcon::thingyA_id>);
	static_assert(std::is_trivially_destructible_v<dcon::thingyA_id>);
	static_assert(std::is_nothrow_default_constructible_v<dcon::thingyA_id>);

	REQUIRE(dcon::thingyA_id().index() == -1);

	auto ptr = std::make_unique< dcon::data_container >();
	auto o1 = fatten(*ptr, ptr->create_thingyA());
	auto o2 = fatten(*ptr, ptr->create_thingyA());

	auto r1 = fatten(*ptr, ptr->try_create_relate_same(o1, o2));

	REQUIRE(bool(r1));
	REQUIRE(ptr->relate_same_size() == 2);
	REQUIRE(r1.get_left() == o1);
	REQUIRE(r1.get_right() == o2);
}

TEST_CASE("array pool index storage", "[relationships_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	auto a1 = fatten(*ptr, ptr->create_thingyA());
	auto a2 = fatten(*ptr, ptr->create_thingyA());
	auto a3 = fatten(*ptr, ptr->create_thingyA());
	auto a4 = fatten(*ptr, ptr->create_thingyA());
	auto a5 = fatten(*ptr, ptr->create_thingyA());
	auto a6 = fatten(*ptr, ptr->create_thingyA());
	auto a7 = fatten(*ptr, ptr->create_thingyA());

	auto b1 = fatten(*ptr, ptr->create_thingyB());
	auto b2 = fatten(*ptr, ptr->create_thingyB());
	auto b3 = fatten(*ptr, ptr->create_thingyB());
	auto b4 = fatten(*ptr, ptr->create_thingyB());

	REQUIRE(bool(ptr->try_create_relate_in_array(a7, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_array(a3, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_array(a2, b2)));
	REQUIRE(bool(ptr->try_create_relate_in_array(a5, b2)));
	REQUIRE(bool(ptr->try_create_relate_in_array(a4, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_array(a1, b1)));

	REQUIRE(!a6.get_relate_in_array().is_valid());

	REQUIRE(a1.get_right_from_relate_in_array() == b1);
	REQUIRE(a2.get_right_from_relate_in_array() == b2);
	REQUIRE(a3.get_right_from_relate_in_array() == b3);
	REQUIRE(a4.get_right_from_relate_in_array() == b3);
	REQUIRE(a5.get_right_from_relate_in_array() == b2);
	REQUIRE(a6.get_right_from_relate_in_array() == dcon::thingyB_id());
	REQUIRE(a7.get_right_from_relate_in_array() == b3);

	{
		std::array<bool, 7> foundvals{false, false, false, false, false, false, false};
		int32_t found_count = 0;

		b3.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b3.has_left_from_relate_in_array(a7));

		REQUIRE(foundvals[6]);
		REQUIRE(foundvals[2]);
		REQUIRE(foundvals[3]);
		REQUIRE(found_count == 3);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_array(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(foundvals[1]);
		REQUIRE(found_count == 2);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_array(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}

	ptr->delete_thingyA(a2);

	// NOTE ALL IDS HAVE CHANGED AS FOLLOWS:
	// a2 = what was previously a7

	REQUIRE(a1.get_right_from_relate_in_array() == b1);
	REQUIRE(a2.get_right_from_relate_in_array() == b3);
	REQUIRE(a3.get_right_from_relate_in_array() == b3);
	REQUIRE(a4.get_right_from_relate_in_array() == b3);
	REQUIRE(a5.get_right_from_relate_in_array() == b2);
	REQUIRE(a6.get_right_from_relate_in_array() == dcon::thingyB_id());

	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b3.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b3.has_left_from_relate_in_array(a2));

		REQUIRE(foundvals[1]);
		REQUIRE(foundvals[2]);
		REQUIRE(foundvals[3]);
		REQUIRE(found_count == 3);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_array(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(found_count == 1);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_array(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}

	ptr->delete_thingyB(b3);

	REQUIRE(a1.get_right_from_relate_in_array() == b1);
	REQUIRE(a2.get_right_from_relate_in_array() == dcon::thingyB_id());
	REQUIRE(a3.get_right_from_relate_in_array() == dcon::thingyB_id());
	REQUIRE(a4.get_right_from_relate_in_array() == dcon::thingyB_id());
	REQUIRE(a5.get_right_from_relate_in_array() == b2);
	REQUIRE(a6.get_right_from_relate_in_array() == dcon::thingyB_id());

	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_array(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(found_count == 1);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_array([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_array(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}
}


TEST_CASE("list index storage", "[relationships_tests]") {
	auto ptr = std::make_unique< dcon::data_container >();

	auto a1 = fatten(*ptr, ptr->create_thingyA());
	auto a2 = fatten(*ptr, ptr->create_thingyA());
	auto a3 = fatten(*ptr, ptr->create_thingyA());
	auto a4 = fatten(*ptr, ptr->create_thingyA());
	auto a5 = fatten(*ptr, ptr->create_thingyA());
	auto a6 = fatten(*ptr, ptr->create_thingyA());
	auto a7 = fatten(*ptr, ptr->create_thingyA());

	auto b1 = fatten(*ptr, ptr->create_thingyB());
	auto b2 = fatten(*ptr, ptr->create_thingyB());
	auto b3 = fatten(*ptr, ptr->create_thingyB());
	auto b4 = fatten(*ptr, ptr->create_thingyB());

	REQUIRE(bool(ptr->try_create_relate_in_list(a7, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_list(a3, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_list(a2, b2)));
	REQUIRE(bool(ptr->try_create_relate_in_list(a5, b2)));
	REQUIRE(bool(ptr->try_create_relate_in_list(a4, b3)));
	REQUIRE(bool(ptr->try_create_relate_in_list(a1, b1)));

	REQUIRE(!a6.get_relate_in_list().is_valid());

	REQUIRE(a1.get_right_from_relate_in_list() == b1);
	REQUIRE(a2.get_right_from_relate_in_list() == b2);
	REQUIRE(a3.get_right_from_relate_in_list() == b3);
	REQUIRE(a4.get_right_from_relate_in_list() == b3);
	REQUIRE(a5.get_right_from_relate_in_list() == b2);
	REQUIRE(a6.get_right_from_relate_in_list() == dcon::thingyB_id());
	REQUIRE(a7.get_right_from_relate_in_list() == b3);

	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b3.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b3.has_left_from_relate_in_list(a7));

		REQUIRE(foundvals[6]);
		REQUIRE(foundvals[2]);
		REQUIRE(foundvals[3]);
		REQUIRE(found_count == 3);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_list(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(foundvals[1]);
		REQUIRE(found_count == 2);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_list(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}

	ptr->delete_thingyA(a2);

	// NOTE ALL IDS HAVE CHANGED AS FOLLOWS:
	// a2 = what was previously a7

	REQUIRE(a1.get_right_from_relate_in_list() == b1);
	REQUIRE(a2.get_right_from_relate_in_list () == b3);
	REQUIRE(a3.get_right_from_relate_in_list() == b3);
	REQUIRE(a4.get_right_from_relate_in_list() == b3);
	REQUIRE(a5.get_right_from_relate_in_list() == b2);
	REQUIRE(a6.get_right_from_relate_in_list() == dcon::thingyB_id());

	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b3.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b3.has_left_from_relate_in_list(a2));

		REQUIRE(foundvals[1]);
		REQUIRE(foundvals[2]);
		REQUIRE(foundvals[3]);
		REQUIRE(found_count == 3);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_list(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(found_count == 1);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_list(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}

	ptr->delete_thingyB(b3);

	REQUIRE(a1.get_right_from_relate_in_list() == b1);
	REQUIRE(a2.get_right_from_relate_in_list() == dcon::thingyB_id());
	REQUIRE(a3.get_right_from_relate_in_list() == dcon::thingyB_id());
	REQUIRE(a4.get_right_from_relate_in_list() == dcon::thingyB_id());
	REQUIRE(a5.get_right_from_relate_in_list() == b2);
	REQUIRE(a6.get_right_from_relate_in_list() == dcon::thingyB_id());

	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b2.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b2.has_left_from_relate_in_list(a5));

		REQUIRE(foundvals[4]);
		REQUIRE(found_count == 1);
	}
	{
		std::array<bool, 7> foundvals{ false, false, false, false, false, false, false };
		int32_t found_count = 0;

		b1.for_each_left_from_relate_in_list([&](auto fi) {
			foundvals[fi.id.index()] = true;
			found_count++;
		});

		REQUIRE(b1.has_left_from_relate_in_list(a1));

		REQUIRE(foundvals[0]);
		REQUIRE(found_count == 1);
	}
}
