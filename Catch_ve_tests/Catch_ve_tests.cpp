#define CATCH_CONFIG_MAIN 

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\ve.hpp"


class dummy_id {
public:
	using value_base_t = uint16_t;
	using zero_is_null_t = std::true_type;


	//value member declaration
	uint16_t value;

	//constructors
	explicit constexpr dummy_id(int16_t v) noexcept : value(v + 1) {}
	constexpr dummy_id(const dummy_id& v) noexcept = default;
	constexpr dummy_id(dummy_id&& v) noexcept = default;
	constexpr dummy_id() noexcept : value(uint16_t(0)) {}

	//operators
	dummy_id& operator=(dummy_id&& v) noexcept = default;
	dummy_id& operator=(dummy_id const& v) noexcept = default;
	bool operator==(dummy_id v) const noexcept { return value == v.value; }
	bool operator!=(dummy_id v) const noexcept { return value != v.value; }
	bool operator<(dummy_id v) const noexcept { return value < v.value; }
	bool operator<=(dummy_id v) const noexcept { return value <= v.value; }
	explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }

	//index_function
	constexpr int32_t index() const noexcept {
		return int32_t(value) - 1;
	}
};

TEST_CASE("constructors", "[ve_tests]") {
	SECTION("default construction") {
		ve::fp_vector fvec;
		ve::int_vector ivec;
		ve::tagged_vector<dummy_id> tvec;
		ve::mask_vector mvec;

		REQUIRE(fvec[0] == 0.0f);
		REQUIRE(fvec[1] == 0.0f);
		REQUIRE(fvec[2] == 0.0f);
		REQUIRE(fvec[3] == 0.0f);

		if(ve::vector_size > 4) {
			REQUIRE(fvec[4] == 0.0f);
			REQUIRE(fvec[5] == 0.0f);
			REQUIRE(fvec[6] == 0.0f);
			REQUIRE(fvec[7] == 0.0f);
		}

		REQUIRE(ivec[0] == 0);
		REQUIRE(ivec[1] == 0);
		REQUIRE(ivec[2] == 0);
		REQUIRE(ivec[3] == 0);

		if(ve::vector_size > 4) {
			REQUIRE(ivec[4] == 0);
			REQUIRE(ivec[5] == 0);
			REQUIRE(ivec[6] == 0);
			REQUIRE(ivec[7] == 0);
		}

		REQUIRE(tvec[0] == dummy_id());
		REQUIRE(tvec[1] == dummy_id());
		REQUIRE(tvec[2] == dummy_id());
		REQUIRE(tvec[3] == dummy_id());

		if(ve::vector_size > 4) {
			REQUIRE(tvec[4] == dummy_id());
			REQUIRE(tvec[5] == dummy_id());
			REQUIRE(tvec[6] == dummy_id());
			REQUIRE(tvec[7] == dummy_id());
		}


		REQUIRE(!mvec[0]);
		REQUIRE(!mvec[1]);
		REQUIRE(!mvec[2]);
		REQUIRE(!mvec[3]);

		if(ve::vector_size > 4) {
			REQUIRE(!mvec[4]);
			REQUIRE(!mvec[5]);
			REQUIRE(!mvec[6]);
			REQUIRE(!mvec[7]);
		}
	}

	SECTION("single value construction") {
		ve::fp_vector fvec(2.5f);
		ve::int_vector ivec(7);
		ve::tagged_vector<dummy_id> tvec(dummy_id(8));
		ve::tagged_vector<int32_t> tivec(7);
		ve::mask_vector mvec(true);

		REQUIRE(fvec[0] == 2.5f);
		REQUIRE(fvec[1] == 2.5f);
		REQUIRE(fvec[2] == 2.5f);
		REQUIRE(fvec[3] == 2.5f);

		if(ve::vector_size > 4) {
			REQUIRE(fvec[4] == 2.5f);
			REQUIRE(fvec[5] == 2.5f);
			REQUIRE(fvec[6] == 2.5f);
			REQUIRE(fvec[7] == 2.5f);
		}

		REQUIRE(ivec[0] == 7);
		REQUIRE(ivec[1] == 7);
		REQUIRE(ivec[2] == 7);
		REQUIRE(ivec[3] == 7);

		if(ve::vector_size > 4) {
			REQUIRE(ivec[4] == 7);
			REQUIRE(ivec[5] == 7);
			REQUIRE(ivec[6] == 7);
			REQUIRE(ivec[7] == 7);
		}

		REQUIRE(tvec[0] == dummy_id(8));
		REQUIRE(tvec[1] == dummy_id(8));
		REQUIRE(tvec[2] == dummy_id(8));
		REQUIRE(tvec[3] == dummy_id(8));

		if(ve::vector_size > 4) {
			REQUIRE(tvec[4] == dummy_id(8));
			REQUIRE(tvec[5] == dummy_id(8));
			REQUIRE(tvec[6] == dummy_id(8));
			REQUIRE(tvec[7] == dummy_id(8));
		}

		REQUIRE(tivec[0] == 7);
		REQUIRE(tivec[1] == 7);
		REQUIRE(tivec[2] == 7);
		REQUIRE(tivec[3] == 7);

		if(ve::vector_size > 4) {
			REQUIRE(tivec[4] == 7);
			REQUIRE(tivec[5] == 7);
			REQUIRE(tivec[6] == 7);
			REQUIRE(tivec[7] == 7);
		}

		REQUIRE(mvec[0]);
		REQUIRE(mvec[1]);
		REQUIRE(mvec[2]);
		REQUIRE(mvec[3]);

		if(ve::vector_size > 4) {
			REQUIRE(mvec[4]);
			REQUIRE(mvec[5]);
			REQUIRE(mvec[6]);
			REQUIRE(mvec[7]);
		}
	}

	SECTION("construct with individual values") {
#ifdef __AVX2__
		ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f);
		ve::int_vector ivec(4, 5, 9, 10, 15, 11, 29, 1);
		ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id());
		ve::tagged_vector<int32_t> tivec(4, 5, 9, 10, 15, 11, 29, 1);
		ve::mask_vector mvec(true, true, false, true, false, true, false, false);
#else
#ifdef __AVX__
		ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f);
		ve::int_vector ivec(4, 5, 9, 10, 15, 11, 29, 1);
		ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id());
		ve::tagged_vector<int32_t> tivec(4, 5, 9, 10, 15, 11, 29, 1);
		ve::mask_vector mvec(true, true, false, true, false, true, false, false);
#else // SSE
		ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f);
		ve::int_vector ivec(4, 5, 9, 10);
		ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(), dummy_id(5), dummy_id(1));
		ve::tagged_vector<int32_t> tivec(4, 5, 9, 10);
		ve::mask_vector mvec(true, true, false, true);
#endif
#endif

		REQUIRE(vec[0] == 1.0f);
		REQUIRE(vec[1] == 3.0f);
		REQUIRE(vec[2] == 4.0f);
		REQUIRE(vec[3] == 7.0f);

		if(ve::vector_size > 4) {
			REQUIRE(vec[4] == 10.0f);
			REQUIRE(vec[5] == 14.5f);
			REQUIRE(vec[6] == 16.0f);
			REQUIRE(vec[7] == 18.0f);
		}

		REQUIRE(ivec[0] == 4);
		REQUIRE(ivec[1] == 5);
		REQUIRE(ivec[2] == 9);
		REQUIRE(ivec[3] == 10);

		if(ve::vector_size > 4) {
			REQUIRE(ivec[4] == 15);
			REQUIRE(ivec[5] == 11);
			REQUIRE(ivec[6] == 29);
			REQUIRE(ivec[7] == 1);
		}

		REQUIRE(tvec[0] == dummy_id(8));
		REQUIRE(tvec[1] == dummy_id());
		REQUIRE(tvec[2] == dummy_id(5));
		REQUIRE(tvec[3] == dummy_id(1));

		if(ve::vector_size > 4) {
			REQUIRE(tvec[4] == dummy_id(10));
			REQUIRE(tvec[5] == dummy_id(11));
			REQUIRE(tvec[6] == dummy_id(19));
			REQUIRE(tvec[7] == dummy_id());
		}

		REQUIRE(tivec[0] == 4);
		REQUIRE(tivec[1] == 5);
		REQUIRE(tivec[2] == 9);
		REQUIRE(tivec[3] == 10);

		if(ve::vector_size > 4) {
			REQUIRE(tivec[4] == 15);
			REQUIRE(tivec[5] == 11);
			REQUIRE(tivec[6] == 29);
			REQUIRE(tivec[7] == 1);
		}

		REQUIRE(mvec[0]);
		REQUIRE(mvec[1]);
		REQUIRE(!mvec[2]);
		REQUIRE(mvec[3]);

		if(ve::vector_size > 4) {
			REQUIRE(!mvec[4]);
			REQUIRE(mvec[5]);
			REQUIRE(!mvec[6]);
			REQUIRE(!mvec[7]);
		}
	}
}

TEST_CASE("bitfield constructors", "[ve_tests]") {
#ifdef __AVX2__
	ve::mask_vector mvec(ve::vbitfield_type{ uint8_t(0x01 | 0x04 | 0x10 | 0x20) });
#else
#ifdef __AVX__
	ve::mask_vector mvec(ve::vbitfield_type{ uint8_t(0x01 | 0x04 | 0x10 | 0x20) });
#else // SSE
	ve::mask_vector mvec(ve::vbitfield_type{uint8_t(0x01 | 0x04)});
#endif
#endif

	REQUIRE(mvec[0]);
	REQUIRE(!mvec[1]);
	REQUIRE(mvec[2]);
	REQUIRE(!mvec[3]);

	if(ve::vector_size > 4) {
		REQUIRE(mvec[4]);
		REQUIRE(mvec[5]);
		REQUIRE(!mvec[6]);
		REQUIRE(!mvec[7]);
	}
	
}

TEST_CASE("tagged_vector int32_t specialization", "[ve_tests]") {
	ve::tagged_vector<int32_t> etvec;
	ve::tagged_vector<int32_t> utvec(7);

#ifdef __AVX2__
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3, 8, 2, 4, 5);
#else
#ifdef __AVX__
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3, 8, 2, 4, 5);
#else // SSE
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3);
#endif
#endif

	REQUIRE(tvec[0] == 0);
	REQUIRE(tvec[1] == 5);
	REQUIRE(tvec[2] == -1);
	REQUIRE(tvec[3] == 3);

	if(ve::vector_size > 4) {
		REQUIRE(tvec[4] == 8);
		REQUIRE(tvec[5] == 2);
		REQUIRE(tvec[6] == 4);
		REQUIRE(tvec[7] == 5);
	}

	REQUIRE(etvec[0] == -1);
	REQUIRE(etvec[1] == -1);
	REQUIRE(etvec[2] == -1);
	REQUIRE(etvec[3] == -1);

	if(ve::vector_size > 4) {
		REQUIRE(etvec[4] == -1);
		REQUIRE(etvec[5] == -1);
		REQUIRE(etvec[6] == -1);
		REQUIRE(etvec[7] == -1);
	}


	REQUIRE(utvec[0] == 7);
	REQUIRE(utvec[1] == 7);
	REQUIRE(utvec[2] == 7);
	REQUIRE(utvec[3] == 7);

	if(ve::vector_size > 4) {
		REQUIRE(utvec[4] == 7);
		REQUIRE(utvec[5] == 7);
		REQUIRE(utvec[6] == 7);
		REQUIRE(utvec[7] == 7);
	}
}

TEST_CASE("tagged_vector loading from raw values", "[ve_tests]") {
#ifdef __AVX2__
	ve::tagged_vector<int32_t> tvec(_mm256_setr_epi32(0, 5, -1, 3, 8, 2, 4, 5));
	ve::tagged_vector<dummy_id> dtvec(_mm256_setr_epi32(1, 6, 0, 4, 9, 3, 5, 6));
#else
#ifdef __AVX__
	ve::tagged_vector<int32_t> tvec(_mm256_setr_epi32(0, 5, -1, 3, 8, 2, 4, 5));
	ve::tagged_vector<dummy_id> dtvec(_mm256_setr_epi32(1, 6, 0, 4, 9, 3, 5, 6));
#else // SSE
	ve::tagged_vector<int32_t> tvec(_mm_setr_epi32(0, 5, -1, 3));
	ve::tagged_vector<dummy_id> dtvec(_mm_setr_epi32(1, 6, 0, 4));
#endif
#endif

	REQUIRE(dtvec[0] == dummy_id(0));
	REQUIRE(dtvec[1] == dummy_id(5));
	REQUIRE(dtvec[2] == dummy_id());
	REQUIRE(dtvec[3] == dummy_id(3));

	if(ve::vector_size > 4) {
		REQUIRE(dtvec[4] == dummy_id(8));
		REQUIRE(dtvec[5] == dummy_id(2));
		REQUIRE(dtvec[6] == dummy_id(4));
		REQUIRE(dtvec[7] == dummy_id(5));
	}

	REQUIRE(tvec[0] == 0);
	REQUIRE(tvec[1] == 5);
	REQUIRE(tvec[2] == -1);
	REQUIRE(tvec[3] == 3);

	if(ve::vector_size > 4) {
		REQUIRE(tvec[4] == 8);
		REQUIRE(tvec[5] == 2);
		REQUIRE(tvec[6] == 4);
		REQUIRE(tvec[7] == 5);
	}
}

TEST_CASE("fp_vector reduction test", "[ve_tests]") {
#ifdef __AVX2__
	ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f);
	ve::fp_vector vec2(1.0f, 7.0f, 0.0f, -2.0f, 1.5f, 3.0f, 9.0f, 2.0f);
#else
#ifdef __AVX__
	ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f);
	ve::fp_vector vec2(1.0f, 7.0f, 0.0f, -2.0f, 1.5f, 3.0f, 9.0f, 2.0f);
#else // SSE
	ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f);
	ve::fp_vector vec2(1.0f, 7.0f, 0.0f, -2.0f);
#endif
#endif

#ifdef __AVX2__
	REQUIRE(vec.reduce() == 1.0f + 3.0f + 4.0f + 7.0f + 10.0f + 14.5f + 16.0f + 18.0f);
	REQUIRE(vec2.reduce() == 1.0f + 7.0f + 0.0f + -2.0f + 1.5f + 3.0f + 9.0f + 2.0f);
#else
#ifdef __AVX__
	REQUIRE(vec.reduce() == 1.0f + 3.0f + 4.0f + 7.0f + 10.0f + 14.5f + 16.0f + 18.0f);
	REQUIRE(vec2.reduce() == 1.0f + 7.0f + 0.0f + -2.0f + 1.5f + 3.0f + 9.0f + 2.0f);
#else // SSE
	REQUIRE(vec.reduce() == 1.0f + 3.0f +  4.0f + 7.0f);
	REQUIRE(vec2.reduce() == 1.0f + 7.0f + 0.0f + -2.0f);
#endif
#endif
}