#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"

float sum(float a, float b) {
	return a + b;
}

#include "query_objs.hpp"

TEST_CASE("simplest query", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	int32_t count = 0;
	int32_t saw_pa = 0;
	int32_t saw_pb = 0;
	int32_t saw_pc = 0;
	int32_t saw_none = 0;
	for(auto& q : ptr->query_q_all_owner_ages()) {
		++count;
		if(q.get_person_id() == pa)
			++saw_pa;
		if(q.get_person_id() == pb)
			++saw_pb;
		if(q.get_person_id() == pc)
			++saw_pc;
		if(!bool(q.get_person_id()))
			++saw_none;
		if(q.get_person_id() == pc)
			q.set_person_age(30);
	}

	REQUIRE(count == 4);
	REQUIRE(saw_pa == 1);
	REQUIRE(saw_pb == 2);
	REQUIRE(saw_pc == 1);
	REQUIRE(saw_none == 0);
	REQUIRE(ptr->person_get_age(pc) == 30);
	REQUIRE(ptr->person_get_age(pa) == 0);
	REQUIRE(ptr->person_get_age(pb) == 0);
}

TEST_CASE("simple reverse query", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	int32_t count = 0;
	int32_t saw_pa = 0;
	int32_t saw_pb = 0;
	int32_t saw_pc = 0;
	int32_t saw_pd = 0;
	int32_t saw_pe = 0;
	int32_t saw_none = 0;
	for(auto& q : ptr->query_rev_car_from_owner()) {
		++count;
		if(q.get_car_id() == cara)
			++saw_pa;
		if(q.get_car_id() == carb)
			++saw_pb;
		if(q.get_car_id() == carc)
			++saw_pc;
		if(q.get_car_id() == card)
			++saw_pd;
		if(q.get_car_id() == care)
			++saw_pe;
		if(!bool(q.get_car_id()))
			++saw_none;
		if(q.get_car_id() == card)
			q.set_rv(3.0f);
	}

	REQUIRE(count == 4);
	REQUIRE(saw_pa == 1);
	REQUIRE(saw_pb == 1);
	REQUIRE(saw_pc == 0);
	REQUIRE(saw_pd == 1);
	REQUIRE(saw_pe == 1);
	REQUIRE(saw_none == 0);
	REQUIRE(ptr->car_get_resale_value(cara) == 0.0f);
	REQUIRE(ptr->car_get_resale_value(card) == 3.0f);
}

TEST_CASE("lookup with parameter", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	int32_t count = 0;
	int32_t saw_pa = 0;
	int32_t saw_pb = 0;
	int32_t saw_pc = 0;
	int32_t saw_pd = 0;
	int32_t saw_pe = 0;
	int32_t saw_none = 0;
	for(auto& q : ptr->query_param_car_from_owner(pb)) {
		++count;
		if(q.get_car_id() == cara)
			++saw_pa;
		if(q.get_car_id() == carb)
			++saw_pb;
		if(q.get_car_id() == carc)
			++saw_pc;
		if(q.get_car_id() == card)
			++saw_pd;
		if(q.get_car_id() == care)
			++saw_pe;
		if(!bool(q.get_car_id()))
			++saw_none;
		if(q.get_car_id() == card)
			q.set_rv(3.0f);
	}

	REQUIRE(count == 2);
	REQUIRE(saw_pa == 1);
	REQUIRE(saw_pb == 0);
	REQUIRE(saw_pc == 0);
	REQUIRE(saw_pd == 1);
	REQUIRE(saw_pe == 0);
	REQUIRE(saw_none == 0);
	REQUIRE(ptr->car_get_resale_value(cara) == 0.0f);
	REQUIRE(ptr->car_get_resale_value(card) == 3.0f);
}

TEST_CASE("simplest query plus", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	int32_t count = 0;
	int32_t saw_pa = 0;
	int32_t saw_pb = 0;
	int32_t saw_pc = 0;
	int32_t saw_none = 0;
	for(auto& q : ptr->query_q_all_owner_ages_plus()) {
		++count;
		if(q.get_person_id() == pa)
			++saw_pa;
		if(q.get_person_id() == pb)
			++saw_pb;
		if(q.get_person_id() == pc)
			++saw_pc;
		if(!bool(q.get_person_id()))
			++saw_none;
		if(q.get_person_id() == pc)
			q.set_person_age(30);
	}

	REQUIRE(count == 5);
	REQUIRE(saw_pa == 1);
	REQUIRE(saw_pb == 2);
	REQUIRE(saw_pc == 1);
	REQUIRE(saw_none == 1);
	REQUIRE(ptr->person_get_age(pc) == 30);
	REQUIRE(ptr->person_get_age(pa) == 0);
	REQUIRE(ptr->person_get_age(pb) == 0);
}

TEST_CASE("simple reverse query plus", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pd = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	int32_t count = 0;
	int32_t saw_pa = 0;
	int32_t saw_pb = 0;
	int32_t saw_pc = 0;
	int32_t saw_pd = 0;
	int32_t saw_pe = 0;
	int32_t saw_none = 0;
	for(auto& q : ptr->query_rev_car_from_owner_plus()) {
		++count;
		if(q.get_car_id() == cara)
			++saw_pa;
		if(q.get_car_id() == carb)
			++saw_pb;
		if(q.get_car_id() == carc)
			++saw_pc;
		if(q.get_car_id() == card)
			++saw_pd;
		if(q.get_car_id() == care)
			++saw_pe;
		if(!bool(q.get_car_id()))
			++saw_none;
		if(q.get_car_id() == card)
			q.set_rv(3.0f);
	}

	REQUIRE(count == 5);
	REQUIRE(saw_pa == 1);
	REQUIRE(saw_pb == 1);
	REQUIRE(saw_pc == 0);
	REQUIRE(saw_pd == 1);
	REQUIRE(saw_pe == 1);
	REQUIRE(saw_none == 1);
	REQUIRE(ptr->car_get_resale_value(cara) == 0.0f);
	REQUIRE(ptr->car_get_resale_value(card) == 3.0f);
}


TEST_CASE("empty queries", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	int32_t count = 0;
	for(auto& q : ptr->query_rev_car_from_owner_plus()) {
		++count;
	}
	REQUIRE(count == 0);

	for(auto& q: ptr->query_rev_car_from_owner()) {
		++count;
	}
	REQUIRE(count == 0);

	for(auto& q: ptr->query_q_all_owner_ages_plus()) {
		++count;
	}
	REQUIRE(count == 0);

	for(auto& q: ptr->query_q_all_owner_ages()) {
		++count;
	}
	REQUIRE(count == 0);

	for(auto& q: ptr->query_param_car_from_owner(dcon::person_id(1))) {
		++count;
	}
	REQUIRE(count == 0);
}

TEST_CASE("find gp", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto gp1 = ptr->create_person();
	auto gp2 = ptr->create_person();
	auto gp3 = ptr->create_person();
	auto gp4 = ptr->create_person();
	auto gp5 = ptr->create_person();
	auto gp6 = ptr->create_person();
	auto gp7 = ptr->create_person();
	auto gp8 = ptr->create_person();
	auto gp9 = ptr->create_person();
	auto gp10 = ptr->create_person();

	auto p1 = ptr->create_person();
	auto p2 = ptr->create_person();
	auto p3 = ptr->create_person();
	auto p4 = ptr->create_person();
	auto p5 = ptr->create_person();
	auto p6 = ptr->create_person();
	auto p7 = ptr->create_person();

	auto c1 = ptr->create_person();
	auto c2 = ptr->create_person();
	auto c3 = ptr->create_person();
	auto c4 = ptr->create_person();
	auto c5 = ptr->create_person();
	auto c6 = ptr->create_person();
	auto c7 = ptr->create_person();
	auto c8 = ptr->create_person();

	ptr->person_set_age(c1, 18);
	ptr->person_set_age(c2, 20);
	ptr->person_set_age(c3, 24);
	ptr->person_set_age(c4, 28);
	ptr->person_set_age(c5, 32);
	ptr->person_set_age(c6, 44);
	ptr->person_set_age(c7, 48);
	ptr->person_set_age(c8, 54);

	ptr->try_create_parentage(c1, p1, p2);
	ptr->try_create_parentage(c2, p1, p2);

	ptr->try_create_parentage(c3, p3, p4);
	ptr->try_create_parentage(c4, p3, p4);

	ptr->try_create_parentage(c5, p5, p4);

	ptr->try_create_parentage(c6, p6, p7);
	ptr->try_create_parentage(c7, p1, gp1);
	ptr->try_create_parentage(c8, p5, gp2);

	ptr->try_create_parentage(p1, gp1, gp2);
	ptr->try_create_parentage(p2, gp3, gp4);
	ptr->try_create_parentage(p3, gp5, gp6);
	ptr->try_create_parentage(p4, gp1, gp3);
	ptr->try_create_parentage(p5, gp7, gp8);
	ptr->try_create_parentage(p6, gp3, gp9);
	ptr->try_create_parentage(p7, gp10, gp5);

	{
		int32_t count = 0;
		bool tc1 = false;
		bool tc2 = false;
		bool tc3 = false;
		bool tc4 = false;
		for(auto& q : ptr->query_grandparents(c3)) {
			// parents p3, p4, gp gp5, gp6, gp1, gp3
			++count;
			if(q.get_parent() == p3 && q.get_grandparent() == gp5)
				tc1 = true;
			if(q.get_parent() == p3 && q.get_grandparent() == gp6)
				tc2 = true;
			if(q.get_parent() == p4 && q.get_grandparent() == gp1)
				tc3 = true;
			if(q.get_parent() == p4 && q.get_grandparent() == gp3)
				tc4 = true;
		}

		REQUIRE(count == 4);
		REQUIRE(tc1);
		REQUIRE(tc2);
		REQUIRE(tc3);
		REQUIRE(tc4);

	}
	{
		int32_t count = 0;
		bool tc1 = false;
		bool tc2 = false;
		for(auto& q : ptr->query_grandparents(c8)) {
			// parents p5, gp gp7, gp8
			++count;
			if(q.get_parent() == p5 && q.get_grandparent() == gp7)
				tc1 = true;
			if(q.get_parent() == p5 && q.get_grandparent() == gp8)
				tc2 = true;
		}

		REQUIRE(count == 2);
		REQUIRE(tc1);
		REQUIRE(tc2);
	}
	{
		{
			auto rng = ptr->person_range_of_parentage_as_bio_parent(p1);
			REQUIRE(rng.second - rng.first == 3);
		}
		{
			auto rng = ptr->person_range_of_parentage_as_bio_parent(gp2);
			REQUIRE(rng.second - rng.first == 2);
		}
		int32_t count = 0;
		bool tc1 = false;
		bool tc2 = false;
		bool tc3 = false;
		for(auto& q : ptr->query_grandchildren(gp2, 100)) {
			//p1, c8; c1 c2 c7
			++count;
			if(q.get_child() == p1 && q.get_grandchild() == c1)
				tc1 = true;
			if(q.get_child() == p1 && q.get_grandchild() == c2)
				tc2 = true;
			if(q.get_child() == p1 && q.get_grandchild() == c7)
				tc3 = true;
		}
		REQUIRE(count == 3);
		REQUIRE(tc1);
		REQUIRE(tc2);
		REQUIRE(tc3);
	}
	{
		int32_t count = 0;
		bool tc1 = false;
		bool tc2 = false;
		bool tc3 = false;
		for(auto& q : ptr->query_grandchildren(gp2, 30)) {
			//p1, c8; c1 c2 c7
			++count;
			if(q.get_child() == p1 && q.get_grandchild() == c1)
				tc1 = true;
			if(q.get_child() == p1 && q.get_grandchild() == c2)
				tc2 = true;
			if(q.get_child() == p1 && q.get_grandchild() == c7)
				tc3 = true;
		}
		REQUIRE(count == 2);
		REQUIRE(tc1);
		REQUIRE(tc2);
		REQUIRE(!tc3);
	}
}


TEST_CASE("summarize gc", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto gp1 = ptr->create_person();
	auto gp2 = ptr->create_person();
	auto gp3 = ptr->create_person();
	auto gp4 = ptr->create_person();
	auto gp5 = ptr->create_person();
	auto gp6 = ptr->create_person();
	auto gp7 = ptr->create_person();
	auto gp8 = ptr->create_person();
	auto gp9 = ptr->create_person();
	auto gp10 = ptr->create_person();

	auto p1 = ptr->create_person();
	auto p2 = ptr->create_person();
	auto p3 = ptr->create_person();
	auto p4 = ptr->create_person();
	auto p5 = ptr->create_person();
	auto p6 = ptr->create_person();
	auto p7 = ptr->create_person();

	auto c1 = ptr->create_person();
	auto c2 = ptr->create_person();
	auto c3 = ptr->create_person();
	auto c4 = ptr->create_person();
	auto c5 = ptr->create_person();
	auto c6 = ptr->create_person();
	auto c7 = ptr->create_person();
	auto c8 = ptr->create_person();

	ptr->person_set_age(c1, 18);
	ptr->person_set_age(c2, 20);
	ptr->person_set_age(c3, 24);
	ptr->person_set_age(c4, 28);
	ptr->person_set_age(c5, 32);
	ptr->person_set_age(c6, 44);
	ptr->person_set_age(c7, 48);
	ptr->person_set_age(c8, 54);

	ptr->person_set_wealth(c1, 1.8f);
	ptr->person_set_wealth(c2, 20.0f);
	ptr->person_set_wealth(c3, 24.0f);
	ptr->person_set_wealth(c4, 2.8f);
	ptr->person_set_wealth(c5, 0.32f);
	ptr->person_set_wealth(c6, 4.4f);
	ptr->person_set_wealth(c7, 48.0f);
	ptr->person_set_wealth(c8, 5.4f);


	ptr->try_create_parentage(c1, p1, p2);
	ptr->try_create_parentage(c2, p1, p2);

	ptr->try_create_parentage(c3, p3, p4);
	ptr->try_create_parentage(c4, p3, p4);

	ptr->try_create_parentage(c5, p5, p4);

	ptr->try_create_parentage(c6, p6, p7);
	ptr->try_create_parentage(c7, p1, gp1);
	ptr->try_create_parentage(c8, p5, gp2);

	ptr->try_create_parentage(p1, gp1, gp2);
	ptr->try_create_parentage(p2, gp3, gp4);
	ptr->try_create_parentage(p3, gp5, gp6);
	ptr->try_create_parentage(p4, gp1, gp3);
	ptr->try_create_parentage(p5, gp7, gp8);
	ptr->try_create_parentage(p6, gp3, gp9);
	ptr->try_create_parentage(p7, gp10, gp5);

	int32_t count = 0;
	for(auto& q : ptr->query_group_grandchildren(100)) {
		REQUIRE(q.get_grandparent().id.index() == count);
		switch(count) {
			case 0:
				REQUIRE(q.get_count_gc() == 6);
				REQUIRE(q.get_max_age() == 48);
				REQUIRE(q.get_gch_wealth() == 48.0f);
				break;
			case 1:
				REQUIRE(q.get_count_gc() == 3);
				REQUIRE(q.get_max_age() == 48);
				REQUIRE(q.get_gch_wealth() == 48.0f);
				break;
			case 2:
				REQUIRE(q.get_count_gc() == 6);
				REQUIRE(q.get_max_age() == 44);
				REQUIRE(q.get_gch_wealth() == 4.4f);
				break;
			case 3:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 20);
				REQUIRE(q.get_gch_wealth() == 20.0f);
				break;
			case 4:
				REQUIRE(q.get_count_gc() == 3);
				REQUIRE(q.get_max_age() == 44);
				REQUIRE(q.get_gch_wealth() == 4.4f);
				break;
			case 5:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 28);
				REQUIRE(q.get_gch_wealth() == 2.8f);
				break;
			case 6:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 54);
				REQUIRE(q.get_gch_wealth() == 5.4f);
				break;
			case 7:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 54);
				REQUIRE(q.get_gch_wealth() == 5.4f);
				break;
			case 8:
				REQUIRE(q.get_count_gc() == 1);
				REQUIRE(q.get_max_age() == 44);
				REQUIRE(q.get_gch_wealth() == 4.4f);
				break;
			case 9:break;
				REQUIRE(q.get_count_gc() == 1);
				REQUIRE(q.get_max_age() == 44);
				REQUIRE(q.get_gch_wealth() == 4.4f);
				break;
		}
		count++;
	}

	REQUIRE(count == 10);

	count = 0;
	for(auto& q : ptr->query_group_grandchildren(40)) {
		REQUIRE(q.get_grandparent().id.index() == count);
		switch(count) {
			case 0:
				REQUIRE(q.get_count_gc() == 5);
				REQUIRE(q.get_max_age() == 32);
				REQUIRE(q.get_gch_wealth() == 0.32f);
				break;
			case 1:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 20);
				REQUIRE(q.get_gch_wealth() == 20.0f);
				break;
			case 2:
				REQUIRE(q.get_count_gc() == 5);
				REQUIRE(q.get_max_age() == 32);
				REQUIRE(q.get_gch_wealth() == 0.32f);
				break;
			case 3:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 20);
				REQUIRE(q.get_gch_wealth() == 20.0f);
				break;
			case 4:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 28);
				REQUIRE(q.get_gch_wealth() == 2.8f);
				break;
			case 5:
				REQUIRE(q.get_count_gc() == 2);
				REQUIRE(q.get_max_age() == 28);
				REQUIRE(q.get_gch_wealth() == 2.8f);
				break;
			case 6:
				REQUIRE(q.get_count_gc() == 1);
				REQUIRE(q.get_max_age() == 32);
				REQUIRE(q.get_gch_wealth() == 0.32f);
				break;
			case 7:
				REQUIRE(q.get_count_gc() == 1);
				REQUIRE(q.get_max_age() == 32);
				REQUIRE(q.get_gch_wealth() == 0.32f);
				break;
		}
		count++;
	}

	REQUIRE(count == 8);
}

TEST_CASE("sum of car_values", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	ptr->car_set_resale_value(cara, 2.0f);
	ptr->car_set_resale_value(card, 3.0f);

	int32_t count = 0;
	for(auto& q : ptr->query_sum_car_value(pb)) {
		++count;
		REQUIRE(q.get_rv_sum() == 5.0f);
	}
	REQUIRE(count == 1);

	count = 0;
	for(auto& q : ptr->query_sum_car_value(pa)) {
		++count;
		REQUIRE(q.get_rv_sum() == 0.0f);
	}
	REQUIRE(count == 1);
}

TEST_CASE("pairs of cars", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto cara = ptr->create_car();
	auto carb = ptr->create_car();
	auto carc = ptr->create_car();
	auto card = ptr->create_car();
	auto care = ptr->create_car();

	auto pa = ptr->create_person();
	auto pb = ptr->create_person();
	auto pc = ptr->create_person();

	auto r1 = ptr->try_create_car_ownership(pa, carb);
	auto r2 = ptr->try_create_car_ownership(pb, cara);
	auto r3 = ptr->try_create_car_ownership(pb, card);
	auto r4 = ptr->try_create_car_ownership(pc, care);

	ptr->car_set_resale_value(cara, 2.0f);
	ptr->car_set_resale_value(card, 3.0f);

	int32_t count = 0;
	bool ca = false;
	bool cb = false;
	bool cc = false;
	bool cd = false;
	for(auto& q : ptr->query_pairs_of_cars()) {
		++count;
		if(q.get_person_id() == pa) {
			REQUIRE(q.get_car_a_id() == carb);
			REQUIRE(q.get_car_b_id() == carb);
		} else if(q.get_person_id() == pc) {
			REQUIRE(q.get_car_a_id() == care);
			REQUIRE(q.get_car_b_id() == care);
		} else if(q.get_person_id() == pb) {
			if(q.get_car_a_id() == cara && q.get_car_b_id() == card)
				ca = true;
			if(q.get_car_a_id() == cara && q.get_car_b_id() == cara)
				cb = true;
			if(q.get_car_a_id() == card && q.get_car_b_id() == card)
				cc = true;
			if(q.get_car_a_id() == card && q.get_car_b_id() == cara)
				cd = true;
		}
	}
	REQUIRE(ca);
	REQUIRE(cb);
	REQUIRE(cc);
	REQUIRE(cd);
	REQUIRE(count == 6);
}

TEST_CASE("siblings test", "[query_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto gp1 = ptr->create_person();
	auto gp2 = ptr->create_person();
	auto gp3 = ptr->create_person();
	auto gp4 = ptr->create_person();
	auto gp5 = ptr->create_person();
	auto gp6 = ptr->create_person();
	auto gp7 = ptr->create_person();
	auto gp8 = ptr->create_person();
	auto gp9 = ptr->create_person();
	auto gp10 = ptr->create_person();

	auto p1 = ptr->create_person();
	auto p2 = ptr->create_person();
	auto p3 = ptr->create_person();
	auto p4 = ptr->create_person();
	auto p5 = ptr->create_person();
	auto p6 = ptr->create_person();
	auto p7 = ptr->create_person();

	auto c1 = ptr->create_person();
	auto c2 = ptr->create_person();
	auto c3 = ptr->create_person();
	auto c4 = ptr->create_person();
	auto c5 = ptr->create_person();
	auto c6 = ptr->create_person();
	auto c7 = ptr->create_person();
	auto c8 = ptr->create_person();

	ptr->person_set_age(c1, 18);
	ptr->person_set_age(c2, 20);
	ptr->person_set_age(c3, 24);
	ptr->person_set_age(c4, 28);
	ptr->person_set_age(c5, 32);
	ptr->person_set_age(c6, 44);
	ptr->person_set_age(c7, 48);
	ptr->person_set_age(c8, 54);

	ptr->person_set_wealth(c1, 1.8f);
	ptr->person_set_wealth(c2, 20.0f);
	ptr->person_set_wealth(c3, 24.0f);
	ptr->person_set_wealth(c4, 2.8f);
	ptr->person_set_wealth(c5, 0.32f);
	ptr->person_set_wealth(c6, 4.4f);
	ptr->person_set_wealth(c7, 48.0f);
	ptr->person_set_wealth(c8, 5.4f);


	ptr->try_create_parentage(c1, p1, p2);
	ptr->try_create_parentage(c2, p1, p2);

	ptr->try_create_parentage(c3, p3, p4);
	ptr->try_create_parentage(c4, p3, p4);

	ptr->try_create_parentage(c5, p5, p4);

	ptr->try_create_parentage(c6, p6, p7);
	ptr->try_create_parentage(c7, p1, gp1);
	ptr->try_create_parentage(c8, p5, gp2);

	ptr->try_create_parentage(p1, gp1, gp2);
	ptr->try_create_parentage(p2, gp3, gp4);
	ptr->try_create_parentage(p3, gp5, gp6);
	ptr->try_create_parentage(p4, gp1, gp3);
	ptr->try_create_parentage(p5, gp7, gp8);
	ptr->try_create_parentage(p6, gp3, gp9);
	ptr->try_create_parentage(p7, gp10, gp5);

	bool cb1 = false;
	bool cb2 = false;
	bool cb3 = false;
	int32_t count = 0;
	for(auto& q : ptr->query_siblings(p1)) {
		++count;
		if(q.get_sibling_a_id() == c1 && q.get_sibling_b_id() == c2)
			cb1 = true;
		if(q.get_sibling_a_id() == c1 && q.get_sibling_b_id() == c7)
			cb2 = true;
		if(q.get_sibling_a_id() == c2 && q.get_sibling_b_id() == c7)
			cb3 = true;
	}
	REQUIRE(count == 3);
	REQUIRE(cb1);
	REQUIRE(cb2);
	REQUIRE(cb3);
}