#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\DataContainerGenerator\parsing.hpp"
#include "..\DataContainerGenerator\parsing.cpp"

TEST_CASE("correctly fromatted cases", "[parsing_tests]") {
	{
		error_record err;
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
		error_record err;
		char text[] = "key_a{TEXT IN KEY}";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT IN KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err;
		char text[] = "key_a  {  TEXT IN KEY   }";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT IN KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err;
		char text[] = "key_a{TEXT {} IN{ adasdd } KEY}";
		auto result = extract_item(text, text + strlen(text), text, err);

		REQUIRE(result.values.size() == 1);
		REQUIRE(result.key.to_string() == std::string("key_a"));
		REQUIRE(result.values[0].to_string() == std::string("TEXT {} IN{ adasdd } KEY"));
		REQUIRE(err.accumulated.length() == 0);
	}

	{
		error_record err;
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
		error_record err;
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
		error_record err;
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
		error_record err;
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