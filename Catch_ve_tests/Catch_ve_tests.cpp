#define CATCH_CONFIG_MAIN 
#pragma warning(disable : 4127)

#define DCON_TRAP_INVALID_STORE

#include "..\CommonIncludes\catch.hpp"
#include "..\CommonIncludes\ve.hpp"
#include "..\CommonIncludes\common_types.hpp"


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

template<>
struct ve::value_to_vector_type_s<dummy_id> {
	using type = tagged_vector<dummy_id>;
};

static_assert(sizeof(dummy_id) == 2);

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
#ifdef __AVX512BW__
		ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.f, 28.f, 30.f, 32.f, 34.f);
		ve::int_vector ivec(4, 5, 9, 10, 15, 11, 29, 1, 30, 33, 36, 39, 42, 45, 48, 51);
		ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(),
										dummy_id(27), dummy_id(21), dummy_id(22), dummy_id(23), dummy_id(24), dummy_id(25), dummy_id(26), dummy_id(20));
		ve::tagged_vector<int32_t> tivec(4, 5, 9, 10, 15, 11, 29, 1, 31, 30, 33, 32, 35, 34, 37, 36);
		ve::mask_vector mvec(true, true, false, true, false, true, false, false,
							false, true, false, false, false, true, true, false);
#else
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
		if(ve::vector_size > 8) {
			REQUIRE(vec[8] == 20.0f);
			REQUIRE(vec[9] == 22.0f);
			REQUIRE(vec[10] == 24.0f);
			REQUIRE(vec[11] == 26.0f);
			REQUIRE(vec[12] == 28.0f);
			REQUIRE(vec[13] == 30.0f);
			REQUIRE(vec[14] == 32.0f);
			REQUIRE(vec[15] == 34.0f);
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
		if(ve::vector_size > 8) {
			REQUIRE(ivec[8] == 30);
			REQUIRE(ivec[9] == 33);
			REQUIRE(ivec[10] == 36);
			REQUIRE(ivec[11] == 39);
			REQUIRE(ivec[12] == 42);
			REQUIRE(ivec[13] == 45);
			REQUIRE(ivec[14] == 48);
			REQUIRE(ivec[15] == 51);
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
		if(ve::vector_size > 8) {
			REQUIRE(tvec[8] == dummy_id(27));
			REQUIRE(tvec[9] == dummy_id(21));
			REQUIRE(tvec[10] == dummy_id(22));
			REQUIRE(tvec[11] == dummy_id(23));
			REQUIRE(tvec[12] == dummy_id(24));
			REQUIRE(tvec[13] == dummy_id(25));
			REQUIRE(tvec[14] == dummy_id(26));
			REQUIRE(tvec[15] == dummy_id(20));
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
		if(ve::vector_size > 8) {
			REQUIRE(tivec[8] == 31);
			REQUIRE(tivec[9] == 30);
			REQUIRE(tivec[10] == 33);
			REQUIRE(tivec[11] == 32);
			REQUIRE(tivec[12] == 35);
			REQUIRE(tivec[13] == 34);
			REQUIRE(tivec[14] == 37);
			REQUIRE(tivec[15] == 36);
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
		if(ve::vector_size > 8) {
			REQUIRE(!mvec[8]);
			REQUIRE(mvec[9]);
			REQUIRE(!mvec[10]);
			REQUIRE(!mvec[11]);
			REQUIRE(!mvec[12]);
			REQUIRE(mvec[13]);
			REQUIRE(mvec[14]);
			REQUIRE(!mvec[15]);
		}
	}
}

TEST_CASE("bitfield constructors", "[ve_tests]") {
#ifdef __AVX512BW__
	ve::mask_vector mvec(ve::vbitfield_type{ uint16_t(0x01 | 0x04 | 0x10 | 0x20 | 0x400 | 0x2000 | 0x100 | 0x8000 ) });
#else
#ifdef __AVX2__
	ve::mask_vector mvec(ve::vbitfield_type{ uint8_t(0x01 | 0x04 | 0x10 | 0x20) });
#else
#ifdef __AVX__
	ve::mask_vector mvec(ve::vbitfield_type{ uint8_t(0x01 | 0x04 | 0x10 | 0x20) });
#else // SSE
	ve::mask_vector mvec(ve::vbitfield_type{uint8_t(0x01 | 0x04)});
#endif
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
	if(ve::vector_size > 8) {
		REQUIRE(mvec[8]);
		REQUIRE(!mvec[9]);
		REQUIRE(mvec[10]);
		REQUIRE(!mvec[11]);
		REQUIRE(!mvec[12]);
		REQUIRE(mvec[13]);
		REQUIRE(!mvec[14]);
		REQUIRE(mvec[15]);
	}
	
}

TEST_CASE("tagged_vector int32_t specialization", "[ve_tests]") {
	ve::tagged_vector<int32_t> etvec;
	ve::tagged_vector<int32_t> utvec(7);

#ifdef __AVX512BW__
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3, 8, 2, 4, 5, -9, 10, -11, 12, -13, -14, -15, 16);
#else
#ifdef __AVX2__
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3, 8, 2, 4, 5);
#else
#ifdef __AVX__
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3, 8, 2, 4, 5);
#else // SSE
	ve::tagged_vector<int32_t> tvec(0, 5, -1, 3);
#endif
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
	if(ve::vector_size > 8) {
		REQUIRE(tvec[8] == -9);
		REQUIRE(tvec[9] == 10);
		REQUIRE(tvec[10] == -11);
		REQUIRE(tvec[11] == 12);
		REQUIRE(tvec[12] == -13);
		REQUIRE(tvec[13] == -14);
		REQUIRE(tvec[14] == -15);
		REQUIRE(tvec[15] == 16);
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
	if(ve::vector_size > 8) {
		REQUIRE(etvec[8] == -1);
		REQUIRE(etvec[9] == -1);
		REQUIRE(etvec[10] == -1);
		REQUIRE(etvec[11] == -1);
		REQUIRE(etvec[12] == -1);
		REQUIRE(etvec[13] == -1);
		REQUIRE(etvec[14] == -1);
		REQUIRE(etvec[15] == -1);
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
	if(ve::vector_size > 8) {
		REQUIRE(utvec[8] == 7);
		REQUIRE(utvec[9] == 7);
		REQUIRE(utvec[10] == 7);
		REQUIRE(utvec[11] == 7);
		REQUIRE(utvec[12] == 7);
		REQUIRE(utvec[13] == 7);
		REQUIRE(utvec[14] == 7);
		REQUIRE(utvec[15] == 7);
	}
}

TEST_CASE("tagged_vector loading from raw values", "[ve_tests]") {
#ifdef __AVX512BW__
	ve::tagged_vector<int32_t> tvec(_mm512_setr_epi32(0, 5, -1, 3, 8, 2, 4, 5, 7, 8, 9, 10, 4, 3, 1, 2));
	ve::tagged_vector<dummy_id> dtvec(_mm512_setr_epi32(1, 6, 0, 4, 9, 3, 5, 6, 8, 9, 10, 11, 5, 4, 2, 3));
#else
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

	if(ve::vector_size > 8) {
		REQUIRE(dtvec[8] == dummy_id(7));
		REQUIRE(dtvec[9] == dummy_id(8));
		REQUIRE(dtvec[10] == dummy_id(9));
		REQUIRE(dtvec[11] == dummy_id(10));
		REQUIRE(dtvec[12] == dummy_id(4));
		REQUIRE(dtvec[13] == dummy_id(3));
		REQUIRE(dtvec[14] == dummy_id(1));
		REQUIRE(dtvec[15] == dummy_id(2));
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

	if(ve::vector_size > 8) {
		REQUIRE(tvec[8] == 7);
		REQUIRE(tvec[9] == 8);
		REQUIRE(tvec[10] == 9);
		REQUIRE(tvec[11] == 10);
		REQUIRE(tvec[12] == 4);
		REQUIRE(tvec[13] == 3);
		REQUIRE(tvec[14] == 1);
		REQUIRE(tvec[15] == 2);
	}
}

TEST_CASE("fp_vector reduction test", "[ve_tests]") {
#ifdef __AVX512BW__
	ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 20.0f, 21.0f, 22.0f, 23.0f);
	ve::fp_vector vec2(1.0f, 7.0f, 0.0f, -2.0f, 1.5f, 3.0f, 9.0f, 2.0f, -1.0f, -2.0f, -3.0f, 7.0f, -4.0f, -5.0f, -6.0f, 7.0f);
#else
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
#endif

#ifdef __AVX512BW__
	REQUIRE(vec.reduce() == 1.0f + 3.0f + 4.0f + 7.0f + 10.0f + 14.5f + 16.0f + 18.0f + 19.0f + 20.0f + 21.0f + 22.0f + 20.0f + 21.0f + 22.0f + 23.0f);
	REQUIRE(vec2.reduce() == 1.0f + 7.0f + 0.0f + -2.0f + 1.5f + 3.0f + 9.0f + 2.0f + -1.0f + -2.0f + -3.0f + 7.0f + -4.0f + -5.0f + -6.0f + 7.0f);
#else
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
#endif
}

TEST_CASE("vectorizable buffer", "[ve_tests]") {
	ve::vectorizable_buffer<float, dummy_id> buf(31);

	REQUIRE((reinterpret_cast<size_t>(&(buf.get(dummy_id(0)))) & uint64_t(63)) == 0); // first address is aligned
	REQUIRE(&(buf.get(dummy_id(0))) - &(buf.get(dummy_id())) == 1); // invalid address is one prior

	REQUIRE(buf.get(dummy_id(0)) == 0.0f); // values are initially zero
	REQUIRE(buf.get(dummy_id(17)) == 0.0f);

	auto mask_result = buf.get(ve::contiguous_tags<dummy_id>(16)) == ve::fp_vector();
	REQUIRE(mask_result[0]);
	REQUIRE(mask_result[1]);
	REQUIRE(mask_result[2]);
	REQUIRE(mask_result[3]);
	if(ve::vector_size > 4) {
		REQUIRE(mask_result[4]);
		REQUIRE(mask_result[5]);
		REQUIRE(mask_result[6]);
		REQUIRE(mask_result[7]);
	}
	if(ve::vector_size > 8) {
		REQUIRE(mask_result[8]);
		REQUIRE(mask_result[9]);
		REQUIRE(mask_result[10]);
		REQUIRE(mask_result[11]);
		REQUIRE(mask_result[12]);
		REQUIRE(mask_result[13]);
		REQUIRE(mask_result[14]);
		REQUIRE(mask_result[15]);
	}

#ifdef __AVX512BW__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2),
									dummy_id(24), dummy_id(30), dummy_id(29), dummy_id(28), dummy_id(27), dummy_id(26), dummy_id(25), dummy_id(31));
	ve::fp_vector inc1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.5f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.5f, 15.0f, 16.0f);
	ve::fp_vector inc2(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.5f, 70.0f, 80.0f, 90.0f, 100.0f, 110.0f, 120.0f, 130.0f, 140.5f, 150.0f, 160.0f);
#else
#ifdef __AVX2__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2));
	ve::fp_vector inc1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector inc2(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.5f, 70.0f, 80.0f);
#else
#ifdef __AVX__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2));
	ve::fp_vector inc1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector inc2(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.5f, 70.0f, 80.0f);
#else // SSE
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(1));
	ve::fp_vector inc1(1.0f, 2.0f, 3.0f, 4.0f);
	ve::fp_vector inc1b(5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector inc2(10.0f, 20.0f, 30.0f, 40.0f);
	ve::fp_vector inc2b(50.0f, 60.5f, 70.0f, 80.0f);
#endif
#endif
#endif

	mask_result = buf.get(tvec) == ve::fp_vector();
	REQUIRE(mask_result[0]);
	REQUIRE(mask_result[1]);
	REQUIRE(mask_result[2]);
	REQUIRE(mask_result[3]);
	if(ve::vector_size > 4) {
		REQUIRE(mask_result[4]);
		REQUIRE(mask_result[5]);
		REQUIRE(mask_result[6]);
		REQUIRE(mask_result[7]);
	}
	if(ve::vector_size > 8) {
		REQUIRE(mask_result[8]);
		REQUIRE(mask_result[9]);
		REQUIRE(mask_result[10]);
		REQUIRE(mask_result[11]);
		REQUIRE(mask_result[12]);
		REQUIRE(mask_result[13]);
		REQUIRE(mask_result[14]);
		REQUIRE(mask_result[15]);
	}

	

#ifdef __AVX512BW__
	buf.set(ve::contiguous_tags<dummy_id>(0), inc1);
	buf.set(ve::contiguous_tags<dummy_id>(16), inc2);
#else
#ifdef __AVX2__
	buf.set(ve::contiguous_tags<dummy_id>(0), inc1);
	buf.set(ve::contiguous_tags<dummy_id>(8), inc2);
#else
#ifdef __AVX__
	buf.set(ve::contiguous_tags<dummy_id>(0), inc1);
	buf.set(ve::contiguous_tags<dummy_id>(8), inc2);
#else // SSE
	buf.set(ve::contiguous_tags<dummy_id>(0), inc1);
	buf.set(ve::contiguous_tags<dummy_id>(4), inc1b);
	buf.set(ve::contiguous_tags<dummy_id>(8), inc2);
	buf.set(ve::contiguous_tags<dummy_id>(12), inc2b);
#endif
#endif
#endif

#ifdef __AVX512BW__
	mask_result = buf.get(ve::contiguous_tags<dummy_id>(0)) == inc1;
#else
#ifdef __AVX2__
	mask_result = buf.get(ve::contiguous_tags<dummy_id>(0)) == inc1;
#else
#ifdef __AVX__
	mask_result = buf.get(ve::contiguous_tags<dummy_id>(0)) == inc1;
#else // SSE
	mask_result = buf.get(ve::contiguous_tags<dummy_id>(4)) == inc1b;
#endif
#endif
#endif
	
	REQUIRE(mask_result[0]);
	REQUIRE(mask_result[1]);
	REQUIRE(mask_result[2]);
	REQUIRE(mask_result[3]);
	if(ve::vector_size > 4) {
		REQUIRE(mask_result[4]);
		REQUIRE(mask_result[5]);
		REQUIRE(mask_result[6]);
		REQUIRE(mask_result[7]);
	}
	if(ve::vector_size > 8) {
		REQUIRE(mask_result[8]);
		REQUIRE(mask_result[9]);
		REQUIRE(mask_result[10]);
		REQUIRE(mask_result[11]);
		REQUIRE(mask_result[12]);
		REQUIRE(mask_result[13]);
		REQUIRE(mask_result[14]);
		REQUIRE(mask_result[15]);
	}

	
#ifdef __AVX512BW__
	mask_result = buf.get(tvec) == ve::fp_vector(9.0f, 1.0f, 6.5f, 2.0f, 11.0f, 12.0f, 40.0f, 3.0f, 90.0f, 150.0f, 140.5f, 130.0f, 120.0f, 110.0f, 100.0f, 160.0f);
#else
#ifdef __AVX2__
	mask_result = buf.get(tvec) == ve::fp_vector(10.0f, 1.0f, 6.5f, 2.0f, 30.0f, 40.0f, 0.0f, 3.0f);
#else
#ifdef __AVX__
	mask_result = buf.get(tvec) == ve::fp_vector(10.0f, 1.0f, 6.5f, 2.0f, 30.0f, 40.0f, 0.0f, 3.0f);
#else // SSE
	mask_result = buf.get(tvec) == ve::fp_vector(10.0f, 1.0f, 6.5f, 2.0f);
#endif
#endif
#endif

	REQUIRE(mask_result[0]);
	REQUIRE(mask_result[1]);
	REQUIRE(mask_result[2]);
	REQUIRE(mask_result[3]);
	if(ve::vector_size > 4) {
		REQUIRE(mask_result[4]);
		REQUIRE(mask_result[5]);
		REQUIRE(mask_result[6]);
		REQUIRE(mask_result[7]);
	}
	if(ve::vector_size > 8) {
		REQUIRE(mask_result[8]);
		REQUIRE(mask_result[9]);
		REQUIRE(mask_result[10]);
		REQUIRE(mask_result[11]);
		REQUIRE(mask_result[12]);
		REQUIRE(mask_result[13]);
		REQUIRE(mask_result[14]);
		REQUIRE(mask_result[15]);
	}

	REQUIRE(buf.get(dummy_id(5)) == 6.5f); 


#ifdef __AVX512BW__
	buf.set(tvec, inc1);
	mask_result = buf.get(tvec) == inc1;
#else
#ifdef __AVX2__
	buf.set(tvec, inc1);
	mask_result = buf.get(tvec) == inc1;
#else
#ifdef __AVX__
	buf.set(tvec, inc1);
	mask_result = buf.get(tvec) == inc1;
#else // SSE
	buf.set(tvec, inc1);
	mask_result = buf.get(tvec) == inc1;
#endif
#endif
#endif

	REQUIRE(mask_result[0]);
	REQUIRE(mask_result[1]);
	REQUIRE(mask_result[2]);
	REQUIRE(mask_result[3]);
	if(ve::vector_size > 4) {
		REQUIRE(mask_result[4]);
		REQUIRE(mask_result[5]);
		REQUIRE(mask_result[6]);
		REQUIRE(mask_result[7]);
	}
	if(ve::vector_size > 8) {
		REQUIRE(mask_result[8]);
		REQUIRE(mask_result[9]);
		REQUIRE(mask_result[10]);
		REQUIRE(mask_result[11]);
		REQUIRE(mask_result[12]);
		REQUIRE(mask_result[13]);
		REQUIRE(mask_result[14]);
		REQUIRE(mask_result[15]);
	}

	REQUIRE(buf.get(tvec[3]) == inc1[3]);
	REQUIRE(buf.get(dummy_id(5)) == 3.0f);
}

TEST_CASE("mathematical operations", "[ve_tests]") {

// TODO
#ifdef __AVX512BW__
	ve::tagged_vector<dummy_id> tveca(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(3), dummy_id(), dummy_id(11), dummy_id(9), dummy_id(2),
									dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(3), dummy_id(), dummy_id(11), dummy_id(9), dummy_id(2));
	ve::tagged_vector<dummy_id> tvecb(dummy_id(), dummy_id(0), dummy_id(7), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(4),
									dummy_id(), dummy_id(0), dummy_id(7), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(4));
	ve::fp_vector fveca(1.0f, 2.0f, 0.0f, 11.0f, 5.0f, 6.5f, 7.0f, 8.0f, 1.0f, 2.0f, 0.0f, 11.0f, 5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector fvecb(10.0f, 2.0f, 3.0f, 7.0f, 5.0f, 60.5f, 1.0f, 0.5f, 10.0f, 2.0f, 3.0f, 7.0f, 5.0f, 60.5f, 1.0f, 0.5f);
	ve::int_vector iveca(1, 2, 0, -5, 10, 4, 9, -2, 1, 2, 0, -5, 10, 4, 9, -2);
	ve::int_vector ivecb(6, 33, 6, -5, 1, 4, 2, 0, 6, 33, 6, -5, 1, 4, 2, 0);
	ve::mask_vector mveca(true, true, false, true, false, true, false, false, false, true, true, false, false, false, true, false);
	ve::mask_vector mvecb(true, false, false, true, false, true, true, false, true, true, false, true, false, false, true, true);
#else
#ifdef __AVX2__
	ve::tagged_vector<dummy_id> tveca(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(3), dummy_id(), dummy_id(11), dummy_id(9), dummy_id(2));
	ve::tagged_vector<dummy_id> tvecb(dummy_id(), dummy_id(0), dummy_id(7), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(4));
	ve::fp_vector fveca(1.0f, 2.0f, 0.0f, 11.0f, 5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector fvecb(10.0f, 2.0f, 3.0f, 7.0f, 5.0f, 60.5f, 1.0f, 0.5f);
	ve::int_vector iveca(1, 2, 0, -5, 10, 4, 9, -2);
	ve::int_vector ivecb(6, 33, 6, -5, 1, 4, 2, 0);
	ve::mask_vector mveca(true, true, false, true, false, true, false, false);
	ve::mask_vector mvecb(true, false, false, true, false, true, true, false);
#else
#ifdef __AVX__
	ve::tagged_vector<dummy_id> tveca(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(3), dummy_id(), dummy_id(11), dummy_id(9), dummy_id(2));
	ve::tagged_vector<dummy_id> tvecb(dummy_id(), dummy_id(0), dummy_id(7), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(4));
	ve::fp_vector fveca(1.0f, 2.0f, 0.0f, 11.0f, 5.0f, 6.5f, 7.0f, 8.0f);
	ve::fp_vector fvecb(10.0f, 2.0f, 3.0f, 7.0f, 5.0f, 60.5f, 1.0f, 0.5f);
	ve::int_vector iveca(1, 2, 0, -5, 10, 4, 9, -2);
	ve::int_vector ivecb(6, 33, 6, -5, 1, 4, 2, 0);
	ve::mask_vector mveca(true, true, false, true, false, true, false, false);
	ve::mask_vector mvecb(true, false, false, true, false, true, true, false);
#else // SSE
	ve::tagged_vector<dummy_id> tveca(dummy_id(8), dummy_id(0), dummy_id(5), dummy_id(3));
	ve::tagged_vector<dummy_id> tvecb(dummy_id(), dummy_id(0), dummy_id(7), dummy_id(1));
	ve::fp_vector fveca(1.0f, 2.0f, 0.0f, 11.0f);
	ve::fp_vector fvecb(10.0f, 2.0f, 3.0f, 7.0f);
	ve::int_vector iveca(1, 2, 0, -5);
	ve::int_vector ivecb(6, 33, 6, -5);
	ve::mask_vector mveca(true, true, false, true);
	ve::mask_vector mvecb(true, false, false, true);
#endif
#endif
#endif


	auto fres = fveca + fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(fveca[i] + fvecb[i]));
	}
	fres = 4.0f + fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(4.0f + fvecb[i]));
	}
	fres = fveca * fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(fveca[i] * fvecb[i]));
	}
	fres = 4.0f * fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(4.0f * fvecb[i]));
	}
	fres = fveca - fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(fveca[i] - fvecb[i]));
	}
	fres = fveca / fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(fveca[i] / fvecb[i]));
	}
	fres = -fveca;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == -(fveca[i]));
	}

	auto ires = iveca + ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == iveca[i] + ivecb[i]);
	}
	ires = 4 + ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == 4 + ivecb[i]);
	}
	ires = iveca * ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == iveca[i] * ivecb[i]);
	}
	ires = 4 * ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == 4 * ivecb[i]);
	}
	ires = iveca - ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == iveca[i] - ivecb[i]);
	}
	ires = -iveca;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == -(iveca[i]));
	}

	fres = ve::inverse(fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(1.0f / (fvecb[i])).margin(0.001));
	}
	fres = ve::sqrt(fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(std::sqrt( (fvecb[i]))));
	}
	fres = ve::inverse_sqrt(fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(1.0f / std::sqrt((fvecb[i]))).margin(0.001));
	}
	fres = ve::abs(fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::abs(fvecb[i]));
	}

	ires = ve::abs(ivecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == std::abs(ivecb[i]));
	}

	fres = ve::multiply_and_add(fveca, fveca + fvecb, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx( (fveca[i] * (fveca[i] + fvecb[i])) + fvecb[i] ));
	}
	fres = ve::multiply_and_subtract(fveca, fveca + fvecb, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx((fveca[i] * (fveca[i] + fvecb[i])) - fvecb[i]));
	}
	fres = ve::negate_multiply_and_add(fveca, fveca + fvecb, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(-(fveca[i] * (fveca[i] + fvecb[i])) + fvecb[i]));
	}
	fres = ve::negate_multiply_and_subtract(fveca, fveca + fvecb, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(-(fveca[i] * (fveca[i] + fvecb[i])) - fvecb[i]));
	}

	// conversion

	fres = ve::to_float(ivecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == Approx(float(ivecb[i])));
	}

	ires = ve::to_int(fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == int32_t(fvecb[i]));
	}

	fres = ve::floor(fveca);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::floor(fveca[i]));
	}
	fres = ve::ceil(fveca);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::ceil(fveca[i]));
	}

#ifdef __AVX512BW__
	auto mvres = ve::compress_mask(mveca);
	REQUIRE(mvres.v == uint16_t(0x01 | 0x02 | 0x08 | 0x20 | 0x200 | 0x400 | 0x4000));
#else
#ifdef __AVX2__
	auto mvres = ve::compress_mask(mveca);
	REQUIRE(mvres.v == uint8_t(0x01 | 0x02 | 0x08 | 0x20));
#else
#ifdef __AVX__
	auto mvres = ve::compress_mask(mveca);
	REQUIRE(mvres.v == uint8_t(0x01 | 0x02 | 0x08 | 0x20));
#else // SSE
	auto mvres = ve::compress_mask(mveca);
	REQUIRE(mvres.v == uint8_t(0x01 | 0x02 | 0x08));
	
#endif
#endif
#endif

	for (int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ve::mask_vector(mvres)[i] == mveca[i]);
	}

	auto mres = mveca & mvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((mveca[i]) && (mvecb[i]) ));
	}

	mres = mveca | mvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ( (mveca[i]) || (mvecb[i]) ));
	}

	mres = mveca ^ mvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ( (mveca[i]) != (mvecb[i]) ));
	}

	mres = ~mveca;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ( !(mveca[i]) ));
	}

	mres = ve::and_not(mveca, mvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((mveca[i]) && !(mvecb[i])));
	}

	mres = fveca < fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ( (fveca[i]) < (fvecb[i]) ));
	}

	mres = fveca <= fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((fveca[i]) <= (fvecb[i])));
	}

	mres = fveca > fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((fveca[i]) > (fvecb[i])));
	}

	mres = fveca >= fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((fveca[i]) >= (fvecb[i])));
	}

	mres = fveca == fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((fveca[i]) == (fvecb[i])));
	}

	mres = fveca != fvecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((fveca[i]) != (fvecb[i])));
	}

	mres = iveca < ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) < (ivecb[i])));
	}

	mres = iveca <= ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) <= (ivecb[i])));
	}

	mres = iveca > ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) > (ivecb[i])));
	}

	mres = iveca >= ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) >= (ivecb[i])));
	}

	mres = iveca == ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) == (ivecb[i])));
	}

	mres = iveca != ivecb;
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((iveca[i]) != (ivecb[i])));
	}

	mres = (mveca != mvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((mveca[i]) != (mvecb[i])));
	}
	mres = (mveca == mvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((mveca[i]) == (mvecb[i])));
	}

	mres = (tveca == tvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((tveca[i]) == (tvecb[i])));
	}
	mres = (tveca != tvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(mres[i] == ((tveca[i]) != (tvecb[i])));
	}

	fres = ve::min(fveca, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::min(fveca[i], fvecb[i]));
	}
	fres = ve::max(fveca, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::max(fveca[i], fvecb[i]));
	}
	fres = ve::select(mveca, fveca, fvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == (mveca[i] ? fveca[i] : fvecb[i]));
	}
	ires = ve::select(mveca, iveca, ivecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(ires[i] == (mveca[i] ? iveca[i] : ivecb[i]));
	}
	auto tres = ve::select(mveca, tveca, tvecb);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(tres[i] == (mveca[i] ? tveca[i] : tvecb[i]));
	}
}

TEST_CASE("loads and stores", "[ve_tests]") {
	int32_t reference_int_data[] = { 1, 23, 5, 1, -3, 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 486, 586,
		100, 101, 102, 104, 102, 104, 5034, 1234, 88, 77, 66};
	int32_t* int_data = dcon::cache_aligned_allocator<int32_t>().allocate(32);
	memcpy(int_data, reference_int_data, sizeof(int32_t) * 32);

	uint32_t reference_uint_data[] = { 1, 23, 5, 1, 3, 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 486, 586,
		100, 101, 102, 104, 102, 104, 5034, 1234, 88, 77, 66 };
	uint32_t* uint_data = dcon::cache_aligned_allocator<uint32_t>().allocate(32);
	memcpy(uint_data, reference_uint_data, sizeof(uint32_t) * 32);

	float reference_float_data[] = { 1.0f, 2.0f, 0.5f, 1.4f, 1.2f, 3.3f, 4.4f, 55.0f, 66.0f, 1.0f, 0.0f, -1.0f, -2.0f,
		11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 17.0f, 77.7f, 9.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 2.6f, 2.8f, 3.9f, 
		40.0f, 42.0f, 43.0f};
	float* float_data = dcon::cache_aligned_allocator<float>().allocate(32);
	memcpy(float_data, reference_float_data, sizeof(float) * 32);

	int16_t reference_int16_data[] = { 1, 23, 5, 1, -3, 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 486, 586,
		100, 101, 102, 104, 102, 104, 5034, 1234, 88, 77, 66 };
	int16_t* int16_data = dcon::cache_aligned_allocator<int16_t>().allocate(32);
	memcpy(int16_data, reference_int16_data, sizeof(int16_t) * 32);

	uint16_t reference_uint16_data[] = { 1, 23, 5, 1, uint16_t(-3), 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 486, 586,
		100, 101, 102, 104, 102, 104, 5034, 1234, 88, 77, 66 };
	uint16_t* uint16_data = dcon::cache_aligned_allocator<uint16_t>().allocate(32);
	memcpy(uint16_data, reference_uint16_data, sizeof(uint16_t) * 32);

	int8_t reference_int8_data[] = { 1, 23, 5, 1, -3, 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 186, 86,
		100, 101, 102, 104, 102, 104, 34, 234, 88, 77, 66 };
	int8_t* int8_data = dcon::cache_aligned_allocator<int8_t>().allocate(32);
	memcpy(int8_data, reference_int8_data, sizeof(int8_t) * 32);

	uint8_t reference_uint8_data[] = { 1, 23, 5, 1, 3, 5, 0, 1, 5, 23, 5, 2, 6, 235, 23, 35, 235, 253, 36, 186, 86,
		100, 101, 102, 104, 102, 104, 34, 234, 88, 77, 66 };
	uint8_t* uint8_data = dcon::cache_aligned_allocator<uint8_t>().allocate(32);
	memcpy(uint8_data, reference_uint8_data, sizeof(uint8_t) * 32);

	dummy_id reference_t_data[] = { dummy_id(1), dummy_id(23), dummy_id(5), dummy_id(1), dummy_id(3),
		dummy_id(5), dummy_id(0), dummy_id(1), dummy_id(5), dummy_id(23), dummy_id(5), dummy_id(),
		dummy_id(6), dummy_id(235), dummy_id(23), dummy_id(35), dummy_id(235), dummy_id(253), dummy_id(36), dummy_id(186),
		dummy_id(86), dummy_id(100), dummy_id(101), dummy_id(102), dummy_id(104), dummy_id(102), dummy_id(104), dummy_id(),
		dummy_id(234), dummy_id(88), dummy_id(77), dummy_id(66) };
	dummy_id* t_data = dcon::cache_aligned_allocator<dummy_id>().allocate(32);
	memcpy(t_data, reference_t_data, sizeof(dummy_id) * 32);

	dcon::bitfield_type reference_b_data[] = { dcon::bitfield_type{ 0x8B}, dcon::bitfield_type{ 0xA1},
		dcon::bitfield_type{ 0x04}, dcon::bitfield_type{ 0xCD} };
	dcon::bitfield_type* b_data = dcon::cache_aligned_allocator<dcon::bitfield_type>().allocate(4);
	memcpy(b_data, reference_b_data, sizeof(dcon::bitfield_type) * 4);

	SECTION("basic loads") {
		//int32_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), int_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int_data[i + 8]);
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), int_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int_data[i + 5]);
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), int_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int_data[i + 1]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//uint32_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), uint_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint_data[i + 8]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), uint_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint_data[i + 5]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), uint_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int32_t(uint_data[i + 1]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//int16_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), int16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(int16_data[i + 8]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), int16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(int16_data[i + 5]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), int16_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int32_t(int16_data[i + 1]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//uint16_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), uint16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint16_data[i + 8]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), uint16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint16_data[i + 5]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), uint16_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int32_t(uint16_data[i + 1]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//uint8_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), uint8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint8_data[i + 8]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), uint8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(uint8_data[i + 5]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), uint8_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int32_t(uint8_data[i + 1]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//int8_t
		{
			ve::int_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), int8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(int8_data[i + 8]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), int8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == int32_t(int8_data[i + 5]));
			}
		}
		{
			ve::int_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), int8_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == int32_t(int8_data[i + 1]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0);
			}
		}
		//float
		{
			ve::fp_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), float_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == float_data[i + 8]);
			}
		}
		{
			ve::fp_vector ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), float_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == float_data[i + 5]);
			}
		}
		{
			ve::fp_vector ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), float_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == float_data[i + 1]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == 0.0f);
			}
		}

		//tags
		{
			ve::tagged_vector<dummy_id> ires = ve::load(ve::contiguous_tags<int32_t>(8), t_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == t_data[i + 8]);
			}
		}
		{
			ve::tagged_vector<dummy_id> ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(5), t_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == t_data[i + 5]);
			}
		}
		{
			ve::tagged_vector<dummy_id> ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), t_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == t_data[i + 1]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == dummy_id());
			}
		}

		//bitfield
		{
			ve::vbitfield_type ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 8 + i));
			}
		}
		{
			ve::vbitfield_type ires = ve::load(ve::unaligned_contiguous_tags<int32_t>(1), b_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 1 + i));
			}
		}
		{
			ve::vbitfield_type ires = ve::load(ve::partial_contiguous_tags<int32_t>(1, 3), b_data);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 1 + i));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == false);
			}
		}
	}
	
	SECTION("basic stores, aligned") {
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int_data);
			ve::store(ve::contiguous_tags<int32_t>(0), int_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int_data[i + 0]);
			}
		}
		{
			ve::fp_vector res = ve::load(ve::contiguous_tags<int32_t>(16), float_data);
			ve::store(ve::contiguous_tags<int32_t>(0), float_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == float_data[i + 0]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint_data);
			ve::store(ve::contiguous_tags<int32_t>(0), uint_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int32_t(uint_data[i + 0]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int16_data);
			ve::store(ve::contiguous_tags<int32_t>(0), int16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int16_data[i + 0]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint16_data);
			ve::store(ve::contiguous_tags<int32_t>(0), uint16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == uint16_data[i + 0]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int8_data);
			ve::store(ve::contiguous_tags<int32_t>(0), int8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int8_data[i + 0]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint8_data);
			ve::store(ve::contiguous_tags<int32_t>(0), uint8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == uint8_data[i + 0]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(ve::contiguous_tags<int32_t>(16), t_data);
			ve::store(ve::contiguous_tags<int32_t>(0), t_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == t_data[i + 0]);
			}
		}
		{
			ve::vbitfield_type ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			ve::store(ve::contiguous_tags<int32_t>(0), b_data, ires);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 0 + i));
			}
		}
	}

	SECTION("basic stores, unaligned") {
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), int_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int_data[i + 3]);
			}
		}
		{
			ve::fp_vector res = ve::load(ve::contiguous_tags<int32_t>(16), float_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), float_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == float_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), uint_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int32_t(uint_data[i + 3]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int16_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), int16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int16_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint16_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), uint16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == uint16_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int8_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), int8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == int8_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint8_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), uint8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == uint8_data[i + 3]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(ve::contiguous_tags<int32_t>(16), t_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), t_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(res[i] == t_data[i + 3]);
			}
		}
		{
			ve::vbitfield_type ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), b_data, ires);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 3 + i));
			}
		}
	}

	SECTION("basic stores, partial") {
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), int_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == int_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(int_data[i + 3] == reference_int_data[i + 3]);
			}
		}
		{
			ve::fp_vector res = ve::load(ve::contiguous_tags<int32_t>(16), float_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), float_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == float_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(float_data[i + 3] == reference_float_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), uint_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == int32_t(uint_data[i + 3]));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(uint_data[i + 3] == reference_uint_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int16_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), int16_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == int16_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(int16_data[i + 3] == reference_int16_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint16_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), uint16_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == uint16_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(uint16_data[i + 3] == reference_uint16_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int8_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), int8_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == int8_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(int8_data[i + 3] == reference_int8_data[i + 3]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint8_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), uint8_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == uint8_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(uint8_data[i + 3] == reference_uint8_data[i + 3]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(ve::contiguous_tags<int32_t>(16), t_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), t_data, res);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(res[i] == t_data[i + 3]);
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(t_data[i + 3] == reference_t_data[i + 3]);
			}
		}
		{
			ve::vbitfield_type ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), b_data, ires);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE((((ires.v >> i) & 0x01) != 0) == dcon::bit_vector_test(b_data, 3 + i));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(dcon::bit_vector_test(reference_b_data, 3 + i) == dcon::bit_vector_test(b_data, 3 + i));
			}
		}
	}
	SECTION("misc mask vector stores A") {
		{
			ve::mask_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			ve::store(ve::partial_contiguous_tags<int32_t>(3, 3), b_data, ires);
			for(int32_t i = 0; i < 3; ++i) {
				REQUIRE(ires[i] == dcon::bit_vector_test(b_data, 3 + i));
			}
			for(int32_t i = 3; i < ve::vector_size; ++i) {
				REQUIRE(dcon::bit_vector_test(reference_b_data, 3 + i) == dcon::bit_vector_test(b_data, 3 + i));
			}
		}
	}
	SECTION("misc mask vector stores B") {
		{
			ve::mask_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
			ve::store(ve::unaligned_contiguous_tags<int32_t>(3), b_data, ires);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(ires[i] == dcon::bit_vector_test(b_data, 3 + i));
			}
		}
	}
	SECTION("misc mask vector stores C") {
		ve::mask_vector ires = ve::load(ve::contiguous_tags<int32_t>(8), b_data);
		ve::store(ve::contiguous_tags<int32_t>(0), b_data, ires);
		for(int32_t i = 0; i < ve::vector_size; ++i) {
			REQUIRE(ires[i] == dcon::bit_vector_test(b_data, 0 + i));
		}
	}


#ifdef __AVX512BW__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(7), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2),
									dummy_id(24), dummy_id(30), dummy_id(29), dummy_id(28), dummy_id(27), dummy_id(26), dummy_id(25), dummy_id(31));
	ve::mask_vector mvec(true, true, false, true, false, true, false, false, false, true, false, false, true, true, true, false);
#else
#ifdef __AVX2__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(7), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2));
	ve::mask_vector mvec(true, true, false, true, false, true, false, false);
#else
#ifdef __AVX__
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(7), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(2));
	ve::mask_vector mvec(true, true, false, true, false, true, false, false);
#else // SSE
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(7), dummy_id(5), dummy_id(1));
	ve::mask_vector mvec(true, true, false, true);
#endif
#endif
#endif

	SECTION("scatter stores") {
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int_data);
			ve::store(tvec, int_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::fp_vector res = ve::load(ve::contiguous_tags<int32_t>(16), float_data);
			ve::store(tvec, float_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(float_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint_data);
			ve::store(tvec, uint_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int32_t(uint_data[tvec[i].index()]) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int16_data);
			ve::store(tvec, int16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int16_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint16_data);
			ve::store(tvec, uint16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint16_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int8_data);
			ve::store(tvec, int8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int8_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint8_data);
			ve::store(tvec, uint8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint8_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(ve::contiguous_tags<int32_t>(16), t_data);
			ve::store(tvec, t_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(t_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::mask_vector res = ve::load(ve::contiguous_tags<int32_t>(16), b_data);
			ve::store(tvec, b_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(dcon::bit_vector_test(b_data, tvec[i].index()) == res[i]);
			}
		}
	}
	SECTION("masked scatter stores") {
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int_data);
			ve::store(tvec, mvec, int_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_int_data[tvec[i].index()]) );
			}
		}
		{
			ve::fp_vector res = ve::load(ve::contiguous_tags<int32_t>(16), float_data);
			ve::store(tvec, mvec, float_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(float_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_float_data[tvec[i].index()]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint_data);
			ve::store(tvec, mvec, uint_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_uint_data[tvec[i].index()]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int16_data);
			ve::store(tvec, mvec, int16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int16_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_int16_data[tvec[i].index()]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint16_data);
			ve::store(tvec, mvec, uint16_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint16_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_uint16_data[tvec[i].index()]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), int8_data);
			ve::store(tvec, mvec, int8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int8_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_int8_data[tvec[i].index()]));
			}
		}
		{
			ve::int_vector res = ve::load(ve::contiguous_tags<int32_t>(16), uint8_data);
			ve::store(tvec, mvec, uint8_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint8_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_uint8_data[tvec[i].index()]));
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(ve::contiguous_tags<int32_t>(16), t_data);
			ve::store(tvec, mvec, t_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(t_data[tvec[i].index()] == (mvec[i] ? res[i] : reference_t_data[tvec[i].index()]));
			}
		}
		{
			ve::mask_vector res = ve::load(ve::contiguous_tags<int32_t>(16), b_data);
			ve::store(tvec, mvec, b_data, res);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(dcon::bit_vector_test(b_data, tvec[i].index()) ==
					(mvec[i] ? res[i] : dcon::bit_vector_test(reference_b_data, tvec[i].index())));
			}
		}
	}

	SECTION("gather loads") {
		{
			ve::fp_vector res = ve::load(tvec, float_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(float_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, int_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, uint_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int32_t(uint_data[tvec[i].index()]) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, int16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int16_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, uint16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint16_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, int8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(int8_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, uint8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(uint8_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(tvec, t_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(t_data[tvec[i].index()] == res[i]);
			}
		}
		{
			ve::mask_vector res = ve::load(tvec, b_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE(dcon::bit_vector_test(b_data, tvec[i].index()) == res[i]);
			}
		}
	}

	SECTION("masked gather loads") {
		{
			ve::fp_vector res = ve::load(tvec, mvec, float_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? float_data[tvec[i].index()] : 0.0f) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, int_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? int_data[tvec[i].index()] : 0) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, uint_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? int32_t(uint_data[tvec[i].index()]) : 0) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, int16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? int16_data[tvec[i].index()] : 0) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, uint16_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? uint16_data[tvec[i].index()] : 0 ) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, int8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? int8_data[tvec[i].index()] : 0 ) == res[i]);
			}
		}
		{
			ve::int_vector res = ve::load(tvec, mvec, uint8_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? uint8_data[tvec[i].index()] : 0) == res[i]);
			}
		}
		{
			ve::tagged_vector<dummy_id> res = ve::load(tvec, mvec, t_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? t_data[tvec[i].index()] : dummy_id()) == res[i]);
			}
		}
		{
			ve::mask_vector res = ve::load(tvec, mvec, b_data);
			for(int32_t i = 0; i < ve::vector_size; ++i) {
				REQUIRE((mvec[i] ? dcon::bit_vector_test(b_data, tvec[i].index()) : false) == res[i]);
			}
		}
	}


	dcon::cache_aligned_allocator<int32_t>().deallocate(int_data, 32);
	dcon::cache_aligned_allocator<uint32_t>().deallocate(uint_data, 32);
	dcon::cache_aligned_allocator<float>().deallocate(float_data, 32);
	dcon::cache_aligned_allocator<int16_t>().deallocate(int16_data, 32);
	dcon::cache_aligned_allocator<uint16_t>().deallocate(uint16_data, 32);
	dcon::cache_aligned_allocator<int8_t>().deallocate(int8_data, 32);
	dcon::cache_aligned_allocator<uint8_t>().deallocate(uint8_data, 32);
	dcon::cache_aligned_allocator<dummy_id>().deallocate(t_data, 32);
	dcon::cache_aligned_allocator<dcon::bitfield_type>().deallocate(b_data, 4);

}

TEST_CASE("utility", "[ve_tests]") {
	REQUIRE(ve::vector_size * 2 == ve::to_vector_size(ve::vector_size + 1));
	REQUIRE(ve::vector_size * 2 == ve::to_vector_size(ve::vector_size * 2));
	REQUIRE(ve::vector_size * 2 == ve::to_vector_size(ve::vector_size * 2 - 1));

#ifdef __AVX512BW__
	ve::fp_vector vec(1.0f, 3.0f, 4.0f, 7.0f, 10.0f, 14.5f, 16.0f, 18.0f, 4.0f, 6.0f, 8.0f, 9.0f, -2.0f, 3.5f, -4.0f, 5.0f);
	ve::int_vector ivec(4, 5, 9, 10, 15, 11, 29, 1, 8, 9, 10, 10, 3, 4, 5, 5);
	ve::tagged_vector<dummy_id> tvec(dummy_id(8), dummy_id(), dummy_id(5), dummy_id(1), dummy_id(10), dummy_id(11), dummy_id(19), dummy_id(),
									dummy_id(24), dummy_id(30), dummy_id(29), dummy_id(28), dummy_id(27), dummy_id(26), dummy_id(25), dummy_id(31));
	ve::tagged_vector<int32_t> tivec(4, 5, 9, 10, 15, 11, 29, 1, 8, 9, 10, 10, 3, 4, 5, 5);
	ve::mask_vector mvec(true, true, false, true, false, true, false, false, true, false, true, true, true, false, false, true);
#else
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
#endif

	auto fres = ve::apply([](float v) { return std::sin(v); }, vec);
	for(int32_t i = 0; i < ve::vector_size; ++i) {
		REQUIRE(fres[i] == std::sin(vec[i]));
	}
	int32_t count = 0;
	ve::apply_with_indices([&count](uint32_t slot, dummy_id) { count += slot; }, ve::contiguous_tags<dummy_id>(0));
	REQUIRE(count == (ve::vector_size / 2) * (ve::vector_size - 1));

	count = 0;
	ve::apply_with_indices([&count](uint32_t slot, dummy_id) { count += slot; }, ve::partial_contiguous_tags<dummy_id>(0, 3));
	REQUIRE(count == 3);
}

#ifdef NDEBUG 
#ifdef _MSC_VER 
#define RELEASE_INLINE __forceinline
#else
#define RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define RELEASE_INLINE inline
#endif

struct accumulate_product_operator {
	float* const dest;
	float const* const a;
	float const* const b;

	accumulate_product_operator(float* d, float const* va, float const* vb) : dest(d), a(va), b(vb) {};

	template<typename T>
	RELEASE_INLINE void operator()(T position) {
		ve::store(position, dest,
			ve::multiply_and_add(
				ve::load(position, a),
				ve::load(position, b),
				ve::load(position, dest))
		);
	}
};

void accumulate_product(uint32_t size, float* destination, float const* a, float const* b) {
	ve::serial_unaligned::template execute<int32_t>(
		size, accumulate_product_operator(destination, a, b));
}

struct sum_all_operator {
	float const* const a;
	ve::fp_vector accumulators[4];

	sum_all_operator(float const* va) : a(va) {};

	template<typename T>
	RELEASE_INLINE void operator()(T position) {
		auto i = 0x03 & (position.value >> dcon::ct_log2(ve::vector_size));
		accumulators[i] = accumulators[i] + ve::load(position, a);
	}
};

float sum_vall_values(uint32_t size, float const* a) {
	sum_all_operator op(a);
	ve::serial_unaligned::template execute<int32_t>(size, op);
	auto intermediate_result = (op.accumulators[0] + op.accumulators[1])
		+ (op.accumulators[2] + op.accumulators[3]);
	return intermediate_result.reduce();
}

TEST_CASE("examples", "[ve_tests]") {
	float arraya[17] = { 4.0f, 1.0f, 3.0f, 5.0f, 8.0f, 2.0f, 6.0f, 14.0f, 11.0f, 13.0f, 15.0f, 18.0f, 12.0f, 16.0f, 24.0f, 21.0f, 23.0f };
	float arrayb[17] = { 7.0f, 4.0f, 24.0f, 5.0f, 3.0f, 1.0f, -2.0f, 4.0f, 1.0f, 0.0f, 5.0f, 182.0f, 2.0f, 2.0f, 4.0f, 1.0f, 3.0f };
	float dest[17] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f };
	float dest_orig[17] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f };

	accumulate_product(17, dest, arraya, arrayb);

	for(int32_t i = 0; i < 17; ++i)
		REQUIRE(dest[i] == (arraya[i] * arrayb[i] + dest_orig[i]));

	float sum = 0.0f;
	for(int32_t i = 0; i < 17; ++i)
		sum += dest[i];

	REQUIRE(sum == sum_vall_values(17, dest));
}

class dummy_signed_id {
public:
	using value_base_t = int16_t;
	using zero_is_null_t = std::false_type;

	//value member declaration
	int16_t value;

	//constructors
	explicit constexpr dummy_signed_id(int16_t v) noexcept : value(v) {}
	constexpr dummy_signed_id(const dummy_signed_id& v) noexcept = default;
	constexpr dummy_signed_id(dummy_signed_id&& v) noexcept = default;
	constexpr dummy_signed_id() noexcept : value(int16_t(-1)) {}

	//operators
	dummy_signed_id& operator=(dummy_signed_id&& v) noexcept = default;
	dummy_signed_id& operator=(dummy_signed_id const& v) noexcept = default;
	bool operator==(dummy_signed_id v) const noexcept { return value == v.value; }
	bool operator!=(dummy_signed_id v) const noexcept { return value != v.value; }
	explicit constexpr operator bool() const noexcept { return value != -1; }

	//index_function
	constexpr int32_t index() const noexcept {
		return int32_t(value);
	}
};

template<>
struct ve::value_to_vector_type_s<dummy_signed_id> {
	using type = tagged_vector<dummy_signed_id>;
};

class dummy_signed_id_s {
public:
	using value_base_t = int8_t;
	using zero_is_null_t = std::false_type;

	//value member declaration
	int8_t value;

	//constructors
	explicit constexpr dummy_signed_id_s(int8_t v) noexcept : value(v) {}
	constexpr dummy_signed_id_s(const dummy_signed_id_s& v) noexcept = default;
	constexpr dummy_signed_id_s(dummy_signed_id_s&& v) noexcept = default;
	constexpr dummy_signed_id_s() noexcept : value(int8_t(-1)) {}

	//operators
	dummy_signed_id_s& operator=(dummy_signed_id_s&& v) noexcept = default;
	dummy_signed_id_s& operator=(dummy_signed_id_s const& v) noexcept = default;
	bool operator==(dummy_signed_id_s v) const noexcept { return value == v.value; }
	bool operator!=(dummy_signed_id_s v) const noexcept { return value != v.value; }
	explicit constexpr operator bool() const noexcept { return value != -1i8; }

	//index_function
	constexpr int32_t index() const noexcept {
		return int32_t(value);
	}
};

template<>
struct ve::value_to_vector_type_s<dummy_signed_id_s> {
	using type = tagged_vector<dummy_signed_id_s>;
};

class dummy_id_s {
public:
	using value_base_t = uint8_t;
	using zero_is_null_t = std::true_type;


	//value member declaration
	uint16_t value;

	//constructors
	explicit constexpr dummy_id_s(uint8_t v) noexcept : value(v + 1) {}
	constexpr dummy_id_s(const dummy_id_s& v) noexcept = default;
	constexpr dummy_id_s(dummy_id_s&& v) noexcept = default;
	constexpr dummy_id_s() noexcept : value(uint16_t(0)) {}

	//operators
	dummy_id_s& operator=(dummy_id_s&& v) noexcept = default;
	dummy_id_s& operator=(dummy_id_s const& v) noexcept = default;
	bool operator==(dummy_id_s v) const noexcept { return value == v.value; }
	bool operator!=(dummy_id_s v) const noexcept { return value != v.value; }
	explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }

	//index_function
	constexpr int32_t index() const noexcept {
		return int32_t(value) - 1;
	}
};

template<>
struct ve::value_to_vector_type_s<dummy_id_s> {
	using type = tagged_vector<dummy_id_s>;
};

TEST_CASE("id variations", "[ve_tests]") {
	dummy_signed_id sgnd[] = { dummy_signed_id(0), dummy_signed_id(), dummy_signed_id(1), dummy_signed_id(2), dummy_signed_id(3),
		dummy_signed_id(), dummy_signed_id(), dummy_signed_id(1), dummy_signed_id(2), dummy_signed_id(3), dummy_signed_id(19),
		dummy_signed_id(9), dummy_signed_id(7), dummy_signed_id(1), dummy_signed_id(20), dummy_signed_id(30) };
	dummy_signed_id_s sgnd_small[] = { dummy_signed_id_s(0), dummy_signed_id_s(), dummy_signed_id_s(1), dummy_signed_id_s(2), dummy_signed_id_s(3),
		dummy_signed_id_s(), dummy_signed_id_s(), dummy_signed_id_s(1), dummy_signed_id_s(2), dummy_signed_id_s(3), dummy_signed_id_s(19),
		dummy_signed_id_s(9), dummy_signed_id_s(7), dummy_signed_id_s(1), dummy_signed_id_s(20), dummy_signed_id_s(30) };
	dummy_id_s usgnd_small[] = { dummy_id_s(0), dummy_id_s(), dummy_id_s(1), dummy_id_s(2), dummy_id_s(3),
		dummy_id_s(), dummy_id_s(), dummy_id_s(1), dummy_id_s(2), dummy_id_s(3), dummy_id_s(19),
		dummy_id_s(9), dummy_id_s(7), dummy_id_s(1), dummy_id_s(20), dummy_id_s(30) };


#ifdef __AVX512BW__
	auto sres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd);
	REQUIRE(sres[0].index() == 0);
	REQUIRE(sres[1].index() == -1);
	REQUIRE(sres[2].index() == 1);
	REQUIRE(sres[3].index() == 2);

	auto ssres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd_small);
	REQUIRE(ssres[0].index() == 0);
	REQUIRE(ssres[1].index() == -1);
	REQUIRE(ssres[2].index() == 1);
	REQUIRE(ssres[3].index() == 2);

	auto ussres = ve::load(ve::contiguous_tags<int32_t>(0), usgnd_small);
	REQUIRE(ussres[0].index() == 0);
	REQUIRE(ussres[1].index() == -1);
	REQUIRE(ussres[2].index() == 1);
	REQUIRE(ussres[3].index() == 2);
#else
#ifdef __AVX2__
	auto sres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd);
	REQUIRE(sres[0].index() == 0);
	REQUIRE(sres[1].index() == -1);
	REQUIRE(sres[2].index() == 1);
	REQUIRE(sres[3].index() == 2);

	auto ssres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd_small);
	REQUIRE(ssres[0].index() == 0);
	REQUIRE(ssres[1].index() == -1);
	REQUIRE(ssres[2].index() == 1);
	REQUIRE(ssres[3].index() == 2);

	auto ussres = ve::load(ve::contiguous_tags<int32_t>(0), usgnd_small);
	REQUIRE(ussres[0].index() == 0);
	REQUIRE(ussres[1].index() == -1);
	REQUIRE(ussres[2].index() == 1);
	REQUIRE(ussres[3].index() == 2);
#else
#ifdef __AVX__
	auto sres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd);
	REQUIRE(sres[0].index() == 0);
	REQUIRE(sres[1].index() == -1);
	REQUIRE(sres[2].index() == 1);
	REQUIRE(sres[3].index() == 2);

	auto ssres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd_small);
	REQUIRE(ssres[0].index() == 0);
	REQUIRE(ssres[1].index() == -1);
	REQUIRE(ssres[2].index() == 1);
	REQUIRE(ssres[3].index() == 2);

	auto ussres = ve::load(ve::contiguous_tags<int32_t>(0), usgnd_small);
	REQUIRE(ussres[0].index() == 0);
	REQUIRE(ussres[1].index() == -1);
	REQUIRE(ussres[2].index() == 1);
	REQUIRE(ussres[3].index() == 2);
#else // SSE
	auto sres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd);
	REQUIRE(sres[0].index() == 0);
	REQUIRE(sres[1].index() == -1);
	REQUIRE(sres[2].index() == 1);
	REQUIRE(sres[3].index() == 2);

	auto ssres = ve::load(ve::contiguous_tags<int32_t>(0), sgnd_small);
	REQUIRE(ssres[0].index() == 0);
	REQUIRE(ssres[1].index() == -1);
	REQUIRE(ssres[2].index() == 1);
	REQUIRE(ssres[3].index() == 2);

	auto ussres = ve::load(ve::contiguous_tags<int32_t>(0), usgnd_small);
	REQUIRE(ussres[0].index() == 0);
	REQUIRE(ussres[1].index() == -1);
	REQUIRE(ussres[2].index() == 1);
	REQUIRE(ussres[3].index() == 2);
#endif
#endif
#endif

// Inspired by this amazing blog post:
// https://randomascii.wordpress.com/2014/01/27/theres-only-four-billion-floatsso-test-them-all/
TEST_CASE("ceil_and_floor", "[ve_tests]") {
	for(uint32_t i = 1; i != 0; ++i) {
		auto const f = *reinterpret_cast<float const*>(&i);
		ve::fp_vector vp(f);
		REQUIRE(ve::ceil(vp)[0] == std::ceil(f));
		REQUIRE(ve::floor(vp)[0] == std::floor(f));
	}
}

}

#undef RELEASE_INLINE
