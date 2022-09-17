#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\DataContainerGenerator\parsing.hpp"
#include "..\DataContainerGenerator\parsing.cpp"

TEST_CASE("correctly fromatted cases", "[parsing_tests]") {
	{
		error_record err("dummy_file");
		char text[] = "key_a key_b";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 0);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(err.accumulated.length() == 0);

		auto resultb = extract_item(result.terminal, text + strlen(text), text, err);

		REQUIRE(resultb.values.size() == 0);
		REQUIRE(resultb.key.to_string() == std::string("key_b"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a{TEXT IN KEY}";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT IN KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a  {  TEXT IN KEY   }";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT IN KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a{TEXT {} IN{ adasdd } KEY}";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT {} IN{ adasdd } KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a{}\t{param {\n} 2}{...}  key_b";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 3);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string(""));
		REQUIRE(result.values[1].to_string() == std::string("param {\n} 2"));
		REQUIRE(result.values[2].to_string() == std::string("..."));
		REQUIRE(err.accumulated.length() == 0);
	}
}

TEST_CASE("incorrectly fromatted cases", "[parsing_tests]") {
	{
		error_record err("dummy_file");
		char text[] = "key_a{TEXT IN KEY";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT IN KEY"));
		REQUIRE(*result.values[0].end == 0);
		REQUIRE(uint64_t(result.terminal) == uint64_t(result.values[0].end));
		REQUIRE(err.accumulated.length() > 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a{TEXT { } IN KEY";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT { } IN KEY"));
		REQUIRE(*result.values[0].end == 0);
		REQUIRE(uint64_t(result.terminal) == uint64_t(result.values[0].end));
		REQUIRE(err.accumulated.length() > 0);
	}

	{
		error_record err("dummy_file");
		char text[] = "key_a{fine}{TEXT { } IN KEY";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 2);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[1].to_string() == std::string("TEXT { } IN KEY"));
		REQUIRE(*result.values[1].end == 0);
		REQUIRE(uint64_t(result.terminal) == uint64_t(result.values[1].end));
		REQUIRE(err.accumulated.length() > 0);
	}
}

TEST_CASE("query parsing", "[parsing_tests]") {
	{
		error_record err("dummy_file");
		char text[] = "A, B, C from T";
		const char* tp = text;
		auto s1 = parse_select_statement(tp, text + strlen(text), text, err);
		
		REQUIRE(s1.returned_values.size() == 3);
		REQUIRE(s1.returned_values[0].is_aggregate == false);
		REQUIRE(s1.returned_values[0].property.as_name == "A");
		REQUIRE(s1.returned_values[0].property.member_name == "A");

		REQUIRE(s1.returned_values[1].is_aggregate == false);
		REQUIRE(s1.returned_values[1].property.as_name == "B");
		REQUIRE(s1.returned_values[1].property.member_name == "B");

		REQUIRE(s1.returned_values[2].is_aggregate == false);
		REQUIRE(s1.returned_values[2].property.as_name == "C");
		REQUIRE(s1.returned_values[2].property.member_name == "C");

		REQUIRE(s1.from.size() == 1);

		REQUIRE(s1.from[0].type == from_type::none);
		REQUIRE(s1.from[0].table_identifier.as_name == "T");

		REQUIRE(s1.where_clause == "");
		REQUIRE(s1.group_by == "");
	}

	{
		error_record err("dummy_file");
		char text[] = "T.A, add(B as C), sum(T.C as xyz) from @param join+ S as table, T.join on www Y";
		const char* tp = text;
		auto s1 = parse_select_statement(tp, text + strlen(text), text, err);

		REQUIRE(s1.returned_values.size() == 3);
		REQUIRE(s1.returned_values[0].is_aggregate == false);
		REQUIRE(s1.returned_values[0].property.as_name == "T_A");
		REQUIRE(s1.returned_values[0].property.member_name == "A");
		REQUIRE(s1.returned_values[0].property.type_name == "T");

		REQUIRE(s1.returned_values[1].is_aggregate == true);
		REQUIRE(s1.returned_values[1].aggregate_name == "add");
		REQUIRE(s1.returned_values[1].property.as_name == "C");
		REQUIRE(s1.returned_values[1].property.member_name == "B");

		REQUIRE(s1.returned_values[2].is_aggregate == true);
		REQUIRE(s1.returned_values[2].aggregate_name == "sum");
		REQUIRE(s1.returned_values[2].property.type_name == "T");
		REQUIRE(s1.returned_values[2].property.member_name == "C");
		REQUIRE(s1.returned_values[2].property.as_name == "xyz");

		REQUIRE(s1.from.size() == 3);

		REQUIRE(s1.from[0].type == from_type::parameter);
		REQUIRE(s1.from[0].table_identifier.member_name == "param");

		REQUIRE(s1.from[1].type == from_type::join_plus);
		REQUIRE(s1.from[1].left_of_join == "");
		REQUIRE(s1.from[1].table_identifier.as_name == "table");
		REQUIRE(s1.from[1].table_identifier.member_name == "S");

		REQUIRE(s1.from[2].type == from_type::join);
		REQUIRE(s1.from[2].left_of_join == "T");
		REQUIRE(s1.from[2].join_on == "www");
		REQUIRE(s1.from[2].table_identifier.as_name == "Y");
		REQUIRE(s1.from[2].table_identifier.member_name == "Y");

		REQUIRE(s1.where_clause == "");
		REQUIRE(s1.group_by == "");
	}

	{
		error_record err("dummy_file");
		char text[] = "min(X) from Y, R group Y";
		const char* tp = text;
		auto s1 = parse_select_statement(tp, text + strlen(text), text, err);

		REQUIRE(s1.returned_values.size() == 1);
		REQUIRE(s1.returned_values[0].is_aggregate == true);
		REQUIRE(s1.returned_values[0].property.as_name == "X");
		REQUIRE(s1.returned_values[0].aggregate_name == "min");
		REQUIRE(s1.returned_values[0].property.member_name == "X");
		REQUIRE(s1.returned_values[0].property.type_name == "");


		REQUIRE(s1.from.size() == 2);

		REQUIRE(s1.from[0].type == from_type::none);
		REQUIRE(s1.from[0].left_of_join == "");
		REQUIRE(s1.from[0].table_identifier.as_name == "Y");
		REQUIRE(s1.from[0].table_identifier.member_name == "Y");

		REQUIRE(s1.from[1].type == from_type::none);
		REQUIRE(s1.from[1].left_of_join == "");
		REQUIRE(s1.from[1].table_identifier.as_name == "R");
		REQUIRE(s1.from[1].table_identifier.member_name == "R");

		REQUIRE(s1.where_clause == "");
		REQUIRE(s1.group_by == "Y");
	}

	{
		error_record err("dummy_file");
		char text[] = "min(X) from Y, R where (@a group @bb) rem group Y";
		const char* tp = text;
		auto s1 = parse_select_statement(tp, text + strlen(text), text, err);

		REQUIRE(s1.returned_values.size() == 1);
		REQUIRE(s1.returned_values[0].is_aggregate == true);
		REQUIRE(s1.returned_values[0].property.as_name == "X");
		REQUIRE(s1.returned_values[0].aggregate_name == "min");
		REQUIRE(s1.returned_values[0].property.member_name == "X");
		REQUIRE(s1.returned_values[0].property.type_name == "");


		REQUIRE(s1.from.size() == 2);

		REQUIRE(s1.from[0].type == from_type::none);
		REQUIRE(s1.from[0].left_of_join == "");
		REQUIRE(s1.from[0].table_identifier.as_name == "Y");
		REQUIRE(s1.from[0].table_identifier.member_name == "Y");

		REQUIRE(s1.from[1].type == from_type::none);
		REQUIRE(s1.from[1].left_of_join == "");
		REQUIRE(s1.from[1].table_identifier.as_name == "R");
		REQUIRE(s1.from[1].table_identifier.member_name == "R");

		REQUIRE(s1.where_clause == "(@a group @bb) rem");
		REQUIRE(s1.group_by == "Y");
	}
}
