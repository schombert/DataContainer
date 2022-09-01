#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\common_types.hpp"

TEST_CASE("operations on invalid", "[storage_tests]") {
	auto ptr = std::make_unique<dcon::stable_variable_vector_storage_mk_2<float, 8, 4000>>();

	dcon::stable_mk_2_tag inv_tag = std::numeric_limits<dcon::stable_mk_2_tag>::max();

	auto rng = dcon::get_range(*ptr, inv_tag);

	REQUIRE(rng.first == rng.second);
	REQUIRE(dcon::get_size(*ptr, inv_tag) == 0);
	REQUIRE(dcon::contains_item(*ptr, inv_tag, 17.5f) == false);
}

TEST_CASE("single item", "[storage_tests]") {
	auto ptr = std::make_unique<dcon::stable_variable_vector_storage_mk_2<float, 8, 4000>>();

	dcon::stable_mk_2_tag store = std::numeric_limits<dcon::stable_mk_2_tag>::max();

	dcon::push_back(*ptr, store, 3.5f);

	auto rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.first != rng.second);
	REQUIRE(*rng.first == 3.5f);
	REQUIRE(dcon::get_size(*ptr, store) == 1);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 3.5f) == true);
	REQUIRE(dcon::get(*ptr, store, 0) == 3.5f);
	REQUIRE(dcon::contains_item(*ptr, store, 3.5f) == true);


	dcon::pop_back(*ptr, store);

	rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.first == rng.second);
	REQUIRE(dcon::get_size(*ptr, store) == 0);
	REQUIRE(dcon::contains_item(*ptr, store, 3.5f) == false);
}

TEST_CASE("loaded_range", "[storage_tests]") {
	std::vector<float> fvec = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

	auto ptr = std::make_unique<dcon::stable_variable_vector_storage_mk_2<float, 8, 4000>>();

	dcon::stable_mk_2_tag store = std::numeric_limits<dcon::stable_mk_2_tag>::max();

	dcon::load_range(*ptr, store, fvec.data(), fvec.data() + 6);

	auto rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.second - rng.first == 6);
	REQUIRE(*rng.first == 1.0f);
	REQUIRE(dcon::get_size(*ptr, store) == 6);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 4.0f) == true);
	REQUIRE(dcon::get(*ptr, store, 2) == 3.0f);
	REQUIRE(dcon::contains_item(*ptr, store, 1.0f) == true);
	REQUIRE(dcon::contains_item(*ptr, store, 6.0f) == true);

	dcon::pop_back(*ptr, store);
	rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.second - rng.first == 5);
	REQUIRE(*rng.first == 1.0f);
	REQUIRE(dcon::get_size(*ptr, store) == 5);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 4.0f) == true);
	REQUIRE(dcon::get(*ptr, store, 2) == 3.0f);
	REQUIRE(dcon::contains_item(*ptr, store, 1.0f) == true);
	REQUIRE(dcon::contains_item(*ptr, store, 6.0f) == false);

	auto old_back = dcon::get(*ptr, store, 4);
	dcon::remove_at(*ptr, store, 2);

	REQUIRE(dcon::get_size(*ptr, store) == 4);
	REQUIRE(dcon::get(*ptr, store, 2) == old_back);

	dcon::resize(*ptr, store, 2);
	rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.second - rng.first == 2);
	REQUIRE(*rng.first == 1.0f);
	REQUIRE(dcon::get_size(*ptr, store) == 2);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 4.0f) == false);
	REQUIRE(dcon::get(*ptr, store, 1) == 2.0f);
	REQUIRE(dcon::contains_item(*ptr, store, 1.0f) == true);
	REQUIRE(dcon::contains_item(*ptr, store, 6.0f) == false);

	ptr->release(store);
	REQUIRE(store == std::numeric_limits<dcon::stable_mk_2_tag>::max());
	rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.first == rng.second);
	REQUIRE(dcon::get_size(*ptr, store) == 0);
	REQUIRE(dcon::contains_item(*ptr, store, 1.0f) == false);
}

TEST_CASE("growing storage", "[storage_tests]") {
	auto ptr = std::make_unique<dcon::stable_variable_vector_storage_mk_2<float, 8, 4000>>();
	dcon::stable_mk_2_tag store = std::numeric_limits<dcon::stable_mk_2_tag>::max();

	for(int i = 0; i < 300; ++i) {
		dcon::push_back(*ptr, store, float(i));
	}

	auto rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.second - rng.first == 300);
	REQUIRE(*rng.first == 0.0f);
	REQUIRE(dcon::get_size(*ptr, store) == 300);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 299.0f) == true);
	REQUIRE(dcon::get(*ptr, store, 134) == 134.0f);
	REQUIRE(dcon::contains_item(*ptr, store, 120.0f) == true);
	REQUIRE(dcon::contains_item(*ptr, store, 6.0f) == true);

	dcon::remove_unique_item(*ptr, store, 130.0f);
	REQUIRE(dcon::get_size(*ptr, store) == 299);
	REQUIRE(dcon::contains_item(*ptr, store, 130.0f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 140.0f) == true);

	dcon::replace_unique_item(*ptr, store, 120.0f, 2.5f);
	REQUIRE(dcon::get_size(*ptr, store) == 299);
	REQUIRE(dcon::contains_item(*ptr, store, 120.0f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 2.5f) == true);

	dcon::resize(*ptr, store, 2);
	rng = dcon::get_range(*ptr, store);
	REQUIRE(rng.second - rng.first == 2);
	REQUIRE(dcon::get_size(*ptr, store) == 2);
	REQUIRE(dcon::contains_item(*ptr, store, 17.5f) == false);
	REQUIRE(dcon::contains_item(*ptr, store, 4.0f) == false);
	REQUIRE(dcon::get(*ptr, store, 1) == 1.0f);
	REQUIRE(dcon::contains_item(*ptr, store, 0.0f) == true);
	REQUIRE(dcon::contains_item(*ptr, store, 6.0f) == false);
}

TEST_CASE("growing multiple", "[storage_tests]") {
	auto ptr = std::make_unique<dcon::stable_variable_vector_storage_mk_2<float, 8, 4000>>();
	dcon::stable_mk_2_tag storea = std::numeric_limits<dcon::stable_mk_2_tag>::max();
	dcon::stable_mk_2_tag storeb = std::numeric_limits<dcon::stable_mk_2_tag>::max();

	for(int i = 0; i < 300; ++i) {
		dcon::push_back(*ptr, storea, float(i));
		dcon::push_back(*ptr, storeb, float(i * 2));
	}

	REQUIRE(dcon::get_size(*ptr, storea) == 300);
	REQUIRE(dcon::get_size(*ptr, storeb) == 300);

	REQUIRE(dcon::contains_item(*ptr, storea, 400.0f) == false);
	REQUIRE(dcon::contains_item(*ptr, storeb, 400.0f) == true);
}

TEST_CASE("local vector", "[storage_tests]") {
	{
		dcon::local_vector<int> lv;

		for(int i = 0; i < 300; ++i) {
			lv.push_back(i);
		}

		REQUIRE(lv.end() - lv.begin() == 300);
		for(int i = 0; i < 300; ++i) {
			REQUIRE(*(lv.begin() + i) == i);
		}
	}
	{
		dcon::local_vector<int> lv;

		for(int i = 0; i < 55; ++i) {
			lv.push_back(i);
		}

		REQUIRE(lv.end() - lv.begin() == 55);
		for(int i = 0; i < 55; ++i) {
			REQUIRE(*(lv.begin() + i) == i);
		}
	}
}