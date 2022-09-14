#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
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
