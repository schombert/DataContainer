#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "common_types.hpp"
#include "ecs.hpp"
#include "common_types.cpp"

void dcon::data_container::on_delete_entity(entity_id e) {
	if (auto c = entity_get_position_component(e); bool(c)) {
		delete_position(c);
	}
	if (auto c = entity_get_sprite_component(e); bool(c)) {
		delete_sprite(c);
	}
}

dcon::entity_id make_entity(dcon::data_container& dc) {
	return dc.try_create_entity(dcon::position_id(), dcon::sprite_id());
}


TEST_CASE("destructor test", "[ecs_tutorial_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto e1 = make_entity(*ptr);
	auto e2 = make_entity(*ptr);
	auto e3 = make_entity(*ptr);
	auto e4 = make_entity(*ptr);

	REQUIRE(bool(e1));
	REQUIRE(bool(e2));
	REQUIRE(bool(e3));
	REQUIRE(bool(e4));

	auto p1 = ptr->create_position();
	auto p2 = ptr->create_position();
	ptr->entity_set_position_component(e1, p1);
	ptr->entity_set_position_component(e3, p2);
	auto s1 = ptr->create_sprite();
	auto s2 = ptr->create_sprite();
	ptr->entity_set_sprite_component(e3, s1);
	ptr->entity_set_sprite_component(e4, s2);

	REQUIRE(ptr->position_is_valid(p1));
	REQUIRE(ptr->position_is_valid(p2));
	REQUIRE(ptr->sprite_is_valid(s1));
	REQUIRE(ptr->sprite_is_valid(s2));

	REQUIRE(ptr->position_size() == 2);
	REQUIRE(ptr->sprite_size() == 2);

	ptr->delete_entity(e1);

	REQUIRE(!ptr->position_is_valid(p1));
	REQUIRE(ptr->position_is_valid(p2));

	ptr->delete_entity(e3);

	REQUIRE(!ptr->position_is_valid(p1));
	REQUIRE(!ptr->position_is_valid(p2));
	REQUIRE(!ptr->sprite_is_valid(s1));
	REQUIRE(ptr->sprite_is_valid(s2));

	ptr->delete_entity(e4);

	REQUIRE(!ptr->sprite_is_valid(s1));
	REQUIRE(!ptr->sprite_is_valid(s2));

	REQUIRE(ptr->position_size() == 0);
	REQUIRE(ptr->sprite_size() == 0);

	ptr->delete_entity(e2);

	REQUIRE(ptr->entity_size() == 0);
}


TEST_CASE("iteration test", "[ecs_tutorial_tests]") {
	auto ptr = std::make_unique<dcon::data_container>();

	auto e1 = make_entity(*ptr);
	auto e2 = make_entity(*ptr);
	auto e3 = make_entity(*ptr);
	auto e4 = make_entity(*ptr);

	auto p1 = ptr->create_position();
	auto p2 = ptr->create_position();
	auto p3 = ptr->create_position();
	auto p4 = ptr->create_position();

	auto s1 = ptr->create_sprite();
	auto s2 = ptr->create_sprite();
	auto s4 = ptr->create_sprite();

	ptr->entity_set_position_component(e1, p1);
	ptr->entity_set_position_component(e2, p2);
	ptr->entity_set_position_component(e3, p3);
	ptr->entity_set_position_component(e4, p4);

	ptr->entity_set_sprite_component(e1, s1);
	ptr->entity_set_sprite_component(e2, s2);
	ptr->entity_set_sprite_component(e4, s4);

	ptr->position_set_x(p1, 1.0f);
	ptr->position_set_x(p2, 2.0f);
	ptr->position_set_x(p3, 3.0f);
	ptr->position_set_x(p4, 4.0f);

	ptr->sprite_set_sprite_id(s1, 1);
	ptr->sprite_set_sprite_id(s2, 2);
	ptr->sprite_set_sprite_id(s4, 1);

	int32_t count = 0;
	for (auto& q : ptr->query_sprites_with_position()) {
		++count;
		if (q.get_position().get_x() == 1.0f)
			REQUIRE(q.get_sprite().get_sprite_id() == uint16_t(1));
		if (q.get_position().get_x() == 2.0f)
			REQUIRE(q.get_sprite().get_sprite_id() == uint16_t(2));
		if (q.get_position().get_x() == 3.0f)
			REQUIRE(q.get_sprite().get_sprite_id() == uint16_t(4)); // impossible
		if (q.get_position().get_x() == 4.0f)
			REQUIRE(q.get_sprite().get_sprite_id() == uint16_t(1));
	}
	REQUIRE(count == 3);

}
