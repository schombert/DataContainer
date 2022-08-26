#pragma once

//
// This file provided as part of the DataContainer project
//

#include <intrin.h>
#include <cstdlib>

namespace ve {
	constexpr int32_t vector_size = 8;

	struct int_vector;

	template<typename tag_type>
	struct tagged_vector;

	struct fp_vector;

	struct mask_vector;

	template<typename T>
	struct ve_identity {
		using type = T;

	};
	struct vbitfield_type {
		using storage = uint8_t;

		uint8_t v;
	};

	RELEASE_INLINE vbitfield_type operator&(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(a.v & b.v) };
	}
	RELEASE_INLINE vbitfield_type operator|(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(a.v | b.v) };
	}
	RELEASE_INLINE vbitfield_type operator^(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(a.v ^ b.v) };
	}
	RELEASE_INLINE vbitfield_type operator~(vbitfield_type a) {
		return vbitfield_type{ uint8_t(~a.v) };
	}
	RELEASE_INLINE vbitfield_type operator!(vbitfield_type a) {
		return vbitfield_type{ uint8_t(~a.v) };
	}
	RELEASE_INLINE vbitfield_type and_not(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(a.v & (~b.v)) };
	}
	RELEASE_INLINE vbitfield_type operator!=(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(a.v ^ b.v) };
	}
	RELEASE_INLINE vbitfield_type operator==(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint8_t(~(a.v ^ b.v)) };
	}

	struct alignas(__m256) mask_vector {
		using wrapped_value = bool;

		__m256 value;

		RELEASE_INLINE mask_vector() : value(_mm256_setzero_ps()) {}
		RELEASE_INLINE mask_vector(bool b) : value(_mm256_castsi256_ps(_mm256_set1_epi32(-int32_t(b)))) {}
		RELEASE_INLINE mask_vector(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h) :
			value(_mm256_castsi256_ps(_mm256_setr_epi32(-int32_t(a), -int32_t(b), -int32_t(c), -int32_t(d), -int32_t(e), -int32_t(f), -int32_t(g), -int32_t(h)))) {}
		RELEASE_INLINE mask_vector(vbitfield_type b) {
			const auto repeated_mask = _mm256_set1_epi32(b.v);
			const auto mask_filter = _mm256_setr_epi32(
				0x00000001, 0x00000002, 0x00000004, 0x00000008,
				0x00000010, 0x00000020, 0x00000040, 0x00000080);
			//value = _mm256_castsi256_ps(_mm256_xor_si256(_mm256_and_si256(repeated_mask, mask_filter), _mm256_set1_epi32(-1)));
			value = _mm256_cmp_ps(_mm256_setzero_ps(), _mm256_castsi256_ps(_mm256_and_si256(repeated_mask, mask_filter)), _CMP_NEQ_UQ);
		}
		RELEASE_INLINE constexpr mask_vector(__m256 v) : value(v) {}
		RELEASE_INLINE constexpr operator __m256() const {
			return value;
		}
		RELEASE_INLINE bool operator[](uint32_t i) const noexcept {
			return _mm256_castps_si256(value).m256i_i32[i] != 0;
		}
		RELEASE_INLINE void set(uint32_t i, bool v) noexcept {
			auto tmp = _mm256_castps_si256(value);
			tmp.m256i_i32[i] = -(int32_t(v));
			value = _mm256_castsi256_ps(tmp);
		}
	};

	struct alignas(__m256) fp_vector {
		using wrapped_value = float;

		__m256 value;

		RELEASE_INLINE fp_vector() : value(_mm256_setzero_ps()) {}
		RELEASE_INLINE constexpr fp_vector(__m256 v) : value(v) {}
		RELEASE_INLINE fp_vector(float v) : value(_mm256_set1_ps(v)) {}
		RELEASE_INLINE fp_vector(float a, float b, float c, float d, float e, float f, float g, float h) : value(_mm256_setr_ps(a, b, c, d, e, f, g, h)) {}
		RELEASE_INLINE constexpr operator __m256() const {
			return value;
		}
		RELEASE_INLINE float reduce() const {
			// source: Peter Cordes
			const __m128 vlow = _mm256_castps256_ps128(value);
			const __m128 vhigh = _mm256_extractf128_ps(value, 1); // high 128
			const __m128 v = _mm_add_ps(vlow, vhigh);  // add the low 128

			__m128 shuf = _mm_movehdup_ps(v); // broadcast elements 3,1 to 2,0
			__m128 sums = _mm_add_ps(v, shuf);
			shuf = _mm_movehl_ps(shuf, sums); // high half -> low half
			sums = _mm_add_ss(sums, shuf);
			return _mm_cvtss_f32(sums);
		}
		RELEASE_INLINE float operator[](uint32_t i) const noexcept {
			return value.m256_f32[i];
		}
		RELEASE_INLINE void set(uint32_t i, float v) noexcept {
			value.m256_f32[i] = v;
		}
	};

	struct alignas(__m128i) int_vector {
		using wrapped_value = int32_t;

		__m128i value_low;
		__m128i value_high;

		RELEASE_INLINE int_vector() : value_low(_mm_setzero_si128()), value_high(_mm_setzero_si128()) {}
		RELEASE_INLINE constexpr int_vector(__m128i l, __m128i h) : value_low(l), value_high(h) {}
		RELEASE_INLINE int_vector(__m256i v) : value_low(_mm256_extractf128_si256(v, 0)), value_high(_mm256_extractf128_si256(v, 1)) {}
		RELEASE_INLINE int_vector(int32_t v) : value_low(_mm_set1_epi32(v)), value_high(_mm_set1_epi32(v)) {}
		RELEASE_INLINE int_vector(uint32_t v) : value_low(_mm_set1_epi32(int32_t(v))), value_high(_mm_set1_epi32(int32_t(v))) {}
		RELEASE_INLINE int_vector(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h) : 
			value_low(_mm_setr_epi32(a, b, c, d)), value_high(_mm_setr_epi32(e, f, g, h)) {}
		RELEASE_INLINE int_vector(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h) :
			value_low(_mm_setr_epi32(int32_t(a), int32_t(b), int32_t(c), int32_t(d))),
			value_high(_mm_setr_epi32(int32_t(e), int32_t(f), int32_t(g), int32_t(h))) {}
		
		RELEASE_INLINE __m256i to_256_packed_int() const noexcept {
			return _mm256_setr_m128i(value_low, value_high);
		}

		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			if(i < 4)
				return value_low.m128i_i32[i];
			else
				return value_high.m128i_i32[i - 4];
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			if(i < 4)
				value_low.m128i_i32[i] = v;
			else
				value_high.m128i_i32[i - 4] = v;
		}
	};

	template<typename tag_type>
	struct alignas(__m256i) tagged_vector {
		using wrapped_value = tag_type;
		static_assert(sizeof(tag_type::value_base_t) <= 4);

		__m256i value;

		RELEASE_INLINE tagged_vector() : value(_mm256_set_m128i(_mm_set1_epi32(-1), _mm_set1_epi32(-1))) {}
		RELEASE_INLINE tagged_vector(__m256i v) {
			if constexpr(tag_type::zero_is_null_t::value) {
				value = _mm256_set_m128i(_mm_sub_epi32(_mm256_extractf128_si256(v, 1), _mm_set1_epi32(int32_t(1))), _mm_sub_epi32(_mm256_extractf128_si256(v, 0), _mm_set1_epi32(int32_t(1))));
			} else {
				value = v;
			}
		}
		RELEASE_INLINE tagged_vector(tag_type v) : value(_mm256_set_m128i(_mm_set1_epi32(v.index()), _mm_set1_epi32(v.index()))) {}
		RELEASE_INLINE tagged_vector(tag_type a, tag_type b, tag_type c, tag_type d, tag_type e, tag_type f, tag_type g, tag_type h) :
			value(_mm256_setr_epi32(a.index(), b.index(), c.index(), d.index(), e.index(), f.index(), g.index(), h.index())) 
		{}
		RELEASE_INLINE constexpr tagged_vector(__m256i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m256i() const {
			return value;
		}

		RELEASE_INLINE tag_type operator[](uint32_t i) const noexcept {
			if constexpr(tag_type::zero_is_null_t::value) {
				tag_type r;
				r.value = typename tag_type::value_base_t(value.m256i_i32[i] + 1);
				return r;
			} else
				return tag_type(typename tag_type::value_base_t(value.m256i_i32[i]));
		}
		RELEASE_INLINE void set(uint32_t i, tag_type v) noexcept {
			value.m256i_i32[i] = v.index();
		}
	};

	template<>
	struct alignas(__m256i) tagged_vector<int32_t> {
		using wrapped_value = int32_t;

		__m256i value;

		RELEASE_INLINE tagged_vector() : value(_mm256_set1_epi32(-1)) {}
		RELEASE_INLINE constexpr tagged_vector(__m256i v) : value(v) {}
		RELEASE_INLINE tagged_vector(int32_t v) : value(_mm256_set1_epi32(v)) {}
		RELEASE_INLINE tagged_vector(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h) : value(_mm256_setr_epi32(a, b, c, d, e, f, g, h))
			{}
		RELEASE_INLINE constexpr tagged_vector(__m256i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m256i() const {
			return value;
		}

		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			return value.m256i_i32[i];
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			value.m256i_i32[i] = v;
		}
	};


	template<typename tag_type>
	struct contiguous_tags_base {
		uint32_t value = 0;
		using wrapped_value = tag_type;

		constexpr contiguous_tags_base() : value(0) {}
		constexpr explicit contiguous_tags_base(uint32_t v) : value(v) {}
		constexpr contiguous_tags_base(const contiguous_tags_base& v) noexcept = default;
		constexpr contiguous_tags_base(contiguous_tags_base&& v) noexcept = default;

		template<typename T, typename = std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>> >
		constexpr contiguous_tags_base(contiguous_tags_base<T> v) : value(v.value) {}

		contiguous_tags_base& operator=(contiguous_tags_base&& v) noexcept = default;
		contiguous_tags_base& operator=(contiguous_tags_base const& v) noexcept = default;

		template<typename T>
		std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>, contiguous_tags_base&> operator=(contiguous_tags_base<T> v) noexcept {
			value = v.value;
			return *this;
		}

		RELEASE_INLINE tag_type operator[](uint32_t i) const noexcept {
			return tag_type(typename tag_type::value_base_t(value + i));
		}

		constexpr bool operator==(contiguous_tags_base<tag_type> o) const noexcept {
			return value == o.value;
		}
		constexpr bool operator!=(contiguous_tags_base<tag_type> o) const noexcept {
			return value != o.value;
		}
	};

	template<typename tag_type>
	struct contiguous_tags : public contiguous_tags_base<tag_type> {

		constexpr contiguous_tags() : contiguous_tags_base<tag_type>(0) {}
		constexpr explicit contiguous_tags(uint32_t v) : contiguous_tags_base<tag_type>(v) {}
		constexpr contiguous_tags(const contiguous_tags& v) noexcept = default;
		constexpr contiguous_tags(contiguous_tags&& v) noexcept = default;

		template<typename T, typename = std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>> >
		constexpr contiguous_tags(contiguous_tags<T> v) : contiguous_tags_base<tag_type>(v.value) {}

		contiguous_tags& operator=(contiguous_tags&& v) noexcept = default;
		contiguous_tags& operator=(contiguous_tags const& v) noexcept = default;

		template<typename T>
		std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>, contiguous_tags&> operator=(contiguous_tags<T> v) noexcept {
			contiguous_tags_base<tag_type>::value = v.value;
			return *this;
		}
	};

	template<typename tag_type>
	struct unaligned_contiguous_tags : public contiguous_tags_base<tag_type> {

		constexpr unaligned_contiguous_tags() : contiguous_tags_base<tag_type>(0) {}
		constexpr explicit unaligned_contiguous_tags(uint32_t v) : contiguous_tags_base<tag_type>(v) {}
		constexpr unaligned_contiguous_tags(const unaligned_contiguous_tags& v) noexcept = default;
		constexpr unaligned_contiguous_tags(unaligned_contiguous_tags&& v) noexcept = default;

		template<typename T, typename = std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>> >
		constexpr unaligned_contiguous_tags(unaligned_contiguous_tags<T> v) : contiguous_tags_base<tag_type>(v.value) {}

		unaligned_contiguous_tags& operator=(unaligned_contiguous_tags&& v) noexcept = default;
		unaligned_contiguous_tags& operator=(unaligned_contiguous_tags const& v) noexcept = default;

		template<typename T>
		std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>, unaligned_contiguous_tags&> operator=(unaligned_contiguous_tags<T> v) noexcept {
			contiguous_tags_base<tag_type>::value = v.value;
			return *this;
		}
	};

	template<typename tag_type>
	struct partial_contiguous_tags {
		using wrapped_value = tag_type;

		uint32_t value = 0;
		uint32_t subcount = vector_size;

		constexpr partial_contiguous_tags() : value(0), subcount(vector_size) {}
		constexpr explicit partial_contiguous_tags(uint32_t v, uint32_t s) : value(v), subcount(s) {}
		constexpr partial_contiguous_tags(const partial_contiguous_tags& v) noexcept = default;
		constexpr partial_contiguous_tags(partial_contiguous_tags&& v) noexcept = default;

		template<typename T, typename = std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>> >
		constexpr partial_contiguous_tags(partial_contiguous_tags<T> v) : value(v.value), subcount(v.subcount) {}

		partial_contiguous_tags& operator=(partial_contiguous_tags&& v) noexcept = default;
		partial_contiguous_tags& operator=(partial_contiguous_tags const& v) noexcept = default;

		template<typename T>
		std::enable_if_t<std::is_constructible_v<tag_type, T> && !std::is_same_v<tag_type, T>, partial_contiguous_tags&> operator=(partial_contiguous_tags<T> v) noexcept {
			value = v.value;
			subcount = v.subcount;
			return *this;
		}

		RELEASE_INLINE tag_type operator[](uint32_t i) const noexcept {
			return tag_type(typename tag_type::value_base_t(value + i));
		}
	};

	template<typename T>
	struct value_to_vector_type_s;

	template<>
	struct value_to_vector_type_s<int32_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<int16_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<uint16_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<int8_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<uint8_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<void> {
		using type = void;
	};
	template<>
	struct value_to_vector_type_s<uint32_t> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<float> {
		using type = fp_vector;
	};
	template<>
	struct value_to_vector_type_s<bool> {
		using type = mask_vector;
	};

	template<>
	struct value_to_vector_type_s<int_vector> {
		using type = int_vector;
	};
	template<>
	struct value_to_vector_type_s<fp_vector> {
		using type = fp_vector;
	};
	template<>
	struct value_to_vector_type_s<mask_vector> {
		using type = mask_vector;
	};
	template<typename T>
	struct value_to_vector_type_s<tagged_vector<T>> {
		using type = tagged_vector<T>;
	};
	template<typename T>
	struct value_to_vector_type_s<contiguous_tags<T>> {
		using type = contiguous_tags<T>;
	};
	template<typename T>
	struct value_to_vector_type_s<unaligned_contiguous_tags<T>> {
		using type = unaligned_contiguous_tags<T>;
	};
	template<typename T>
	struct value_to_vector_type_s<partial_contiguous_tags<T>> {
		using type = partial_contiguous_tags<T>;
	};

	template<typename T>
	using value_to_vector_type = typename value_to_vector_type_s<T>::type;

	template<typename T>
	struct is_vector_type_s {
		constexpr static bool value = false;
	};
	template<>
	struct is_vector_type_s<int_vector> {
		constexpr static bool value = true;
	};
	template<>
	struct is_vector_type_s<fp_vector> {
		constexpr static bool value = true;
	};
	template<>
	struct is_vector_type_s<mask_vector> {
		constexpr static bool value = true;
	};
	template<typename T>
	struct is_vector_type_s<tagged_vector<T>> {
		constexpr static bool value = true;
	};
	template<typename T>
	struct is_vector_type_s<contiguous_tags<T>> {
		constexpr static bool value = true;
	};
	template<typename T>
	struct is_vector_type_s<unaligned_contiguous_tags<T>> {
		constexpr static bool value = true;
	};
	template<typename T>
	struct is_vector_type_s<partial_contiguous_tags<T>> {
		constexpr static bool value = true;
	};

	template<typename T>
	constexpr bool is_vector_type = is_vector_type_s<T>::value;

	template<typename ... T>
	struct any_is_vector_type;

	template<>
	struct any_is_vector_type<> { constexpr static bool value = false; };

	template<typename F, typename ... R>
	struct any_is_vector_type<F, R...> { constexpr static bool value = is_vector_type<F> || any_is_vector_type<R...>::value; };

	template<typename TO, typename FROM>
	RELEASE_INLINE auto widen_to(FROM v) -> std::conditional_t<is_vector_type<TO>, value_to_vector_type<std::remove_cv_t<FROM>>, FROM> { return v; }

	template<typename TO, typename ... REST, typename FROM>
	RELEASE_INLINE auto widen_to(FROM v) -> std::conditional_t<is_vector_type<TO>, value_to_vector_type<std::remove_cv_t<FROM>>, decltype(widen_to<REST ...>(v))> { return v; }

	template<uint32_t i, typename T>
	RELEASE_INLINE std::enable_if_t<is_vector_type<T>, typename T::wrapped_value> nth_item(T v) {
		return v[i];
	}
	template<uint32_t i, typename T>
	RELEASE_INLINE std::enable_if_t<!is_vector_type<T>, T> nth_item(T v) {
		return v;
	}

	template<typename ... T>
	struct any_is_partial_s;

	template<>
	struct any_is_partial_s<> {
		constexpr static bool value = false;
	};

	template<typename ttype, typename ... T>
	struct any_is_partial_s<partial_contiguous_tags<ttype>, T...> {
		constexpr static bool value = true;
	};

	template<typename first, typename ... T>
	struct any_is_partial_s<first, T...> {
		constexpr static bool value = any_is_partial_s<T...>::value;
	};

	template<typename ... T>
	constexpr bool any_is_partial = any_is_partial_s<T...>::value;

	RELEASE_INLINE constexpr uint32_t minimum_partial() {
		return uint32_t(vector_size);
	}

	template<typename ttype, typename ... T>
	RELEASE_INLINE uint32_t minimum_partial(partial_contiguous_tags<ttype> p, T... args) {
		return std::min(p.subcount, minimum_partial(args ...));
	}

	template<typename first, typename ... T>
	RELEASE_INLINE uint32_t minimum_partial(first, T... args) {
		return minimum_partial(args ...);
	}

	template<typename FUNC, typename ... PARAMS>
	RELEASE_INLINE auto apply(FUNC&& f, PARAMS ... params) {
		if constexpr(any_is_partial<PARAMS ...>) {
			const uint32_t limit = minimum_partial(params ...);

			if constexpr(std::is_same_v<decltype(f(nth_item<0ui32>(params) ...)), void>) {
				if(limit > 0ui32) f(nth_item<0ui32>(params) ...);
				if(limit > 1ui32) f(nth_item<1ui32>(params) ...);
				if(limit > 2ui32) f(nth_item<2ui32>(params) ...);
				if(limit > 3ui32) f(nth_item<3ui32>(params) ...);
				if(limit > 4ui32) f(nth_item<4ui32>(params) ...);
				if(limit > 5ui32) f(nth_item<5ui32>(params) ...);
				if(limit > 6ui32) f(nth_item<6ui32>(params) ...);
				if(limit > 7ui32) f(nth_item<7ui32>(params) ...);
			} else {
				return value_to_vector_type<decltype(f(nth_item<0ui32>(params) ...))>(
					(limit > 0ui32) ? f(nth_item<0ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 1ui32) ? f(nth_item<1ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 2ui32) ? f(nth_item<2ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 3ui32) ? f(nth_item<3ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 4ui32) ? f(nth_item<4ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 5ui32) ? f(nth_item<5ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 6ui32) ? f(nth_item<6ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))(),
					(limit > 7ui32) ? f(nth_item<7ui32>(params) ...) : decltype(f(nth_item<0ui32>(params) ...))()
					);
			}
		} else if constexpr(any_is_vector_type<PARAMS ...>::value) {
			if constexpr(std::is_same_v<decltype(f(nth_item<0ui32>(params) ...)), void>) {
				f(nth_item<0ui32>(params) ...);
				f(nth_item<1ui32>(params) ...);
				f(nth_item<2ui32>(params) ...);
				f(nth_item<3ui32>(params) ...);
				f(nth_item<4ui32>(params) ...);
				f(nth_item<5ui32>(params) ...);
				f(nth_item<6ui32>(params) ...);
				f(nth_item<7ui32>(params) ...);
			} else {
				return value_to_vector_type<decltype(f(nth_item<0ui32>(params) ...))>(
					f(nth_item<0ui32>(params) ...),
					f(nth_item<1ui32>(params) ...),
					f(nth_item<2ui32>(params) ...),
					f(nth_item<3ui32>(params) ...),
					f(nth_item<4ui32>(params) ...),
					f(nth_item<5ui32>(params) ...),
					f(nth_item<6ui32>(params) ...),
					f(nth_item<7ui32>(params) ...)
					);
			}
		} else {
			return f(params ...);
		}
	}

	template<typename FUNC, typename ... PARAMS>
	RELEASE_INLINE auto apply_with_indices(FUNC&& f, PARAMS ... params)
		->  value_to_vector_type<decltype(f(0ui32, nth_item<0ui32>(params) ...))> {
		if constexpr(any_is_partial<PARAMS ...>) {
			const uint32_t limit = minimum_partial(params ...);

			if constexpr(std::is_same_v<decltype(f(0ui32, nth_item<0ui32>(params) ...)), void>) {
				if(limit > 0ui32) f(0ui32, nth_item<0ui32>(params) ...);
				if(limit > 1ui32) f(1ui32, nth_item<1ui32>(params) ...);
				if(limit > 2ui32) f(2ui32, nth_item<2ui32>(params) ...);
				if(limit > 3ui32) f(3ui32, nth_item<3ui32>(params) ...);
				if(limit > 4ui32) f(4ui32, nth_item<4ui32>(params) ...);
				if(limit > 5ui32) f(5ui32, nth_item<5ui32>(params) ...);
				if(limit > 6ui32) f(6ui32, nth_item<6ui32>(params) ...);
				if(limit > 7ui32) f(7ui32, nth_item<7ui32>(params) ...);
			} else {
				return value_to_vector_type<decltype(f(nth_item<0ui32>(params) ...))>(
					(limit > 0ui32) ? f(0ui32, nth_item<0ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 1ui32) ? f(1ui32, nth_item<1ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 2ui32) ? f(2ui32, nth_item<2ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 3ui32) ? f(3ui32, nth_item<3ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 4ui32) ? f(4ui32, nth_item<4ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 5ui32) ? f(5ui32, nth_item<5ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 6ui32) ? f(6ui32, nth_item<6ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))(),
					(limit > 7ui32) ? f(7ui32, nth_item<7ui32>(params) ...) : decltype(f(0ui32, nth_item<0ui32>(params) ...))()
					);
			}
		} else if constexpr(std::is_same_v<decltype(f(0ui32, nth_item<0ui32>(params) ...)), void>) {
			f(0ui32, nth_item<0ui32>(params) ...);
			f(1ui32, nth_item<1ui32>(params) ...);
			f(2ui32, nth_item<2ui32>(params) ...);
			f(3ui32, nth_item<3ui32>(params) ...);
			f(4ui32, nth_item<4ui32>(params) ...);
			f(5ui32, nth_item<5ui32>(params) ...);
			f(6ui32, nth_item<6ui32>(params) ...);
			f(7ui32, nth_item<7ui32>(params) ...);
		} else {
			return value_to_vector_type<decltype(f(nth_item<0ui32>(params) ...))>(
				f(0ui32, nth_item<0ui32>(params) ...),
				f(1ui32, nth_item<1ui32>(params) ...),
				f(2ui32, nth_item<2ui32>(params) ...),
				f(3ui32, nth_item<3ui32>(params) ...),
				f(4ui32, nth_item<4ui32>(params) ...),
				f(5ui32, nth_item<5ui32>(params) ...),
				f(6ui32, nth_item<6ui32>(params) ...),
				f(7ui32, nth_item<7ui32>(params) ...)
				);
		}
	}

	RELEASE_INLINE fp_vector to_float(int_vector v) {
		return _mm256_cvtepi32_ps(_mm256_setr_m128i(v.value_low, v.value_high));
	}
	RELEASE_INLINE int_vector to_int(fp_vector v) {
		return _mm256_cvtps_epi32(v);
	}

	RELEASE_INLINE fp_vector operator+(fp_vector a, fp_vector b) {
		return _mm256_add_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a, fp_vector b) {
		return _mm256_sub_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator*(fp_vector a, fp_vector b) {
		return _mm256_mul_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator/(fp_vector a, fp_vector b) {
		return _mm256_div_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a) {
		return fp_vector() - a;
	}


	RELEASE_INLINE int_vector operator+(int_vector a, int_vector b) {
		return int_vector(_mm_add_epi32(a.value_low, b.value_low), _mm_add_epi32(a.value_high, b.value_high));
	}
	RELEASE_INLINE int_vector operator-(int_vector a, int_vector b) {
		return int_vector(_mm_sub_epi32(a.value_low, b.value_low), _mm_sub_epi32(a.value_high, b.value_high));
	}
	RELEASE_INLINE int_vector operator*(int_vector a, int_vector b) {
		return int_vector(_mm_mullo_epi32(a.value_low, b.value_low), _mm_mullo_epi32(a.value_high, b.value_high));
	}
	RELEASE_INLINE int_vector operator-(int_vector a) {
		return int_vector() - a;
	}

	RELEASE_INLINE mask_vector operator&(mask_vector a, mask_vector b) {
		return _mm256_and_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator|(mask_vector a, mask_vector b) {
		return _mm256_or_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator^(mask_vector a, mask_vector b) {
		return _mm256_xor_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator~(mask_vector a) {
		return _mm256_xor_ps(a, mask_vector(true));
	}
	RELEASE_INLINE mask_vector operator!(mask_vector a) {
		return _mm256_xor_ps(a, mask_vector(true));
	}
	RELEASE_INLINE mask_vector and_not(mask_vector a, mask_vector b) {
		return _mm256_andnot_ps(b, a);
	}

	RELEASE_INLINE fp_vector inverse(fp_vector a) {
		return _mm256_rcp_ps(a);
	}
	RELEASE_INLINE fp_vector sqrt(fp_vector a) {
		return _mm256_sqrt_ps(a);
	}
	RELEASE_INLINE fp_vector inverse_sqrt(fp_vector a) {
		return _mm256_rsqrt_ps(a);
	}

	RELEASE_INLINE int_vector abs(int_vector a) {
		return int_vector(std::abs(a[0]), std::abs(a[1]), std::abs(a[2]), std::abs(a[3]),
			std::abs(a[4]), std::abs(a[5]), std::abs(a[6]), std::abs(a[7]));
	}
	
	RELEASE_INLINE fp_vector multiply_and_add(fp_vector a, fp_vector b, fp_vector c) {
		return (a * b) + c;
	}
	RELEASE_INLINE fp_vector multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c) {
		return (a * b) - c;
	}
	RELEASE_INLINE fp_vector negate_multiply_and_add(fp_vector a, fp_vector b, fp_vector c) {
		return c - (a * b);
	}
	RELEASE_INLINE fp_vector negate_multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c) {
		return (0.0f - c) - (a * b);
	}

	RELEASE_INLINE fp_vector min(fp_vector a, fp_vector b) {
		return _mm256_min_ps(a, b);
	}
	RELEASE_INLINE fp_vector max(fp_vector a, fp_vector b) {
		return _mm256_max_ps(a, b);
	}
	RELEASE_INLINE fp_vector abs(fp_vector a) {
		return max(a, -a);
	}
	RELEASE_INLINE fp_vector floor(fp_vector a) {
		return _mm256_floor_ps(a);
	}
	RELEASE_INLINE fp_vector ceil(fp_vector a) {
		return _mm256_ceil_ps(a);
	}

	RELEASE_INLINE mask_vector operator<(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_LT_OQ);
	}
	RELEASE_INLINE mask_vector operator>(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_GT_OQ);
	}
	RELEASE_INLINE mask_vector operator<=(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_LE_OQ);
	}
	RELEASE_INLINE mask_vector operator>=(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_GE_OQ);
	}
	RELEASE_INLINE mask_vector operator==(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_EQ_OQ);
	}
	RELEASE_INLINE mask_vector operator!=(fp_vector a, fp_vector b) {
		return _mm256_cmp_ps(a, b, _CMP_NEQ_OQ);
	}

	RELEASE_INLINE mask_vector operator<(int_vector a, int_vector b) {
		auto const lo = _mm_cmpgt_epi32(b.value_low, a.value_low);
		auto const hi = _mm_cmpgt_epi32(b.value_high, a.value_high);
		return _mm256_castsi256_ps(_mm256_setr_m128i(lo, hi));
	}
	RELEASE_INLINE mask_vector operator>(int_vector a, int_vector b) {
		auto const lo = _mm_cmpgt_epi32(a.value_low, b.value_low);
		auto const hi = _mm_cmpgt_epi32(a.value_high, b.value_high);
		return _mm256_castsi256_ps(_mm256_setr_m128i(lo, hi));
	}
	RELEASE_INLINE mask_vector operator==(int_vector a, int_vector b) {
		auto const lo = _mm_cmpeq_epi32(a.value_low, b.value_low);
		auto const hi = _mm_cmpeq_epi32(a.value_high, b.value_high);
		return _mm256_castsi256_ps(_mm256_setr_m128i(lo, hi));
	}
	RELEASE_INLINE mask_vector operator!=(int_vector a, int_vector b) {
		return (a > b) | (b > a);
	}
	RELEASE_INLINE mask_vector operator<=(int_vector a, int_vector b) {
		return (a < b) | (a == b);
	}
	RELEASE_INLINE mask_vector operator>=(int_vector a, int_vector b) {
		return (a > b) | (a == b);
	}
	RELEASE_INLINE mask_vector operator==(mask_vector a, mask_vector b) {
		return !(a ^ b);
	}
	RELEASE_INLINE mask_vector operator!=(mask_vector a, mask_vector b) {
		return a ^ b;
	}

	template<typename T>
	RELEASE_INLINE mask_vector operator==(tagged_vector<T> a, tagged_vector<T> b) {
		return int_vector(a.value) == int_vector(b.value);
	}
	template<typename T>
	RELEASE_INLINE mask_vector operator!=(tagged_vector<T> a, tagged_vector<T> b) {
		return int_vector(a.value) != int_vector(b.value);
	}

	template<typename T>
	RELEASE_INLINE mask_vector operator==(tagged_vector<T> a, typename ve_identity<T>::type b) {
		return a == tagged_vector<T>(b);
	}
	template<typename T>
	RELEASE_INLINE mask_vector operator!=(tagged_vector<T> a, typename ve_identity<T>::type b) {
		return a != tagged_vector<T>(b);
	}

	template<typename T>
	RELEASE_INLINE mask_vector operator==(typename ve_identity<T>::type a, tagged_vector<T> b) {
		return b == tagged_vector<T>(a);
	}
	template<typename T>
	RELEASE_INLINE mask_vector operator!=(typename ve_identity<T>::type a, tagged_vector<T> b) {
		return b != tagged_vector<T>(a);
	}

	template<typename tag_type>
	RELEASE_INLINE mask_vector operator==(contiguous_tags_base<tag_type> a, tagged_vector<typename ve_identity<tag_type>::type> b) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3)),
			tag_type(typename tag_type::value_base_t(a.value + 4)),
			tag_type(typename tag_type::value_base_t(a.value + 5)),
			tag_type(typename tag_type::value_base_t(a.value + 6)),
			tag_type(typename tag_type::value_base_t(a.value + 7))) == b;
	}
	template<typename tag_type>
	RELEASE_INLINE mask_vector operator!=(contiguous_tags_base<tag_type> a, tagged_vector<typename ve_identity<tag_type>::type> b) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3)),
			tag_type(typename tag_type::value_base_t(a.value + 4)),
			tag_type(typename tag_type::value_base_t(a.value + 5)),
			tag_type(typename tag_type::value_base_t(a.value + 6)),
			tag_type(typename tag_type::value_base_t(a.value + 7))) != b;
	}


	template<typename tag_type>
	RELEASE_INLINE mask_vector operator==(tagged_vector<typename ve_identity<tag_type>::type> b, contiguous_tags_base<tag_type> a) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3)),
			tag_type(typename tag_type::value_base_t(a.value + 4)),
			tag_type(typename tag_type::value_base_t(a.value + 5)),
			tag_type(typename tag_type::value_base_t(a.value + 6)),
			tag_type(typename tag_type::value_base_t(a.value + 7))) == b;
	}
	template<typename tag_type>
	RELEASE_INLINE mask_vector operator!=(tagged_vector<typename ve_identity<tag_type>::type> b, contiguous_tags_base<tag_type> a) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3)),
			tag_type(typename tag_type::value_base_t(a.value + 4)),
			tag_type(typename tag_type::value_base_t(a.value + 5)),
			tag_type(typename tag_type::value_base_t(a.value + 6)),
			tag_type(typename tag_type::value_base_t(a.value + 7))) != b;
	}


	RELEASE_INLINE fp_vector select(mask_vector mask, fp_vector a, fp_vector b) {
		return _mm256_blendv_ps(b, a, mask);
	}

	RELEASE_INLINE int_vector select(mask_vector mask, int_vector a, int_vector b) {
		auto const mask_as_int = int_vector(_mm256_castps_si256(mask));
		return int_vector(
			_mm_blendv_epi8(b.value_low, a.value_low, mask_as_int.value_low), 
			_mm_blendv_epi8(b.value_high, a.value_high, mask_as_int.value_high));
	}

	template<typename T>
	RELEASE_INLINE tagged_vector<T> select(mask_vector mask, tagged_vector<T> a, tagged_vector<typename ve_identity<T>::type> b) {
		return tagged_vector<T>(_mm256_castps_si256(_mm256_blendv_ps(_mm256_castsi256_ps(b.value), _mm256_castsi256_ps(a.value), mask)), std::true_type{});
	}

	RELEASE_INLINE mask_vector is_non_zero(int_vector i) {
		return i != int_vector();
	}
	RELEASE_INLINE mask_vector is_zero(int_vector i) {
		return i == int_vector();
	}

	template<typename T>
	RELEASE_INLINE mask_vector is_valid_index(tagged_vector<T> i) {
		return i != tagged_vector<T>();
	}
	template<typename T>
	RELEASE_INLINE mask_vector is_invalid(tagged_vector<T> i) {
		return i == tagged_vector<T>();
	}

	RELEASE_INLINE vbitfield_type compress_mask(mask_vector mask) {
		vbitfield_type t;
		t.v =  uint8_t(_mm256_movemask_ps(mask));
		return t;
	}


	inline constexpr uint32_t load_masks[16] = {
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000
	};


	template<typename T>
	RELEASE_INLINE vbitfield_type load(contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ source[e.value / 8ui32].v };
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(unaligned_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(0x0FF & (
			((source[e.value / 8ui32].v) >> (e.value & 0x07))
			| (((e.value & 0x7) != 0 ? (source[1 + e.value / 8ui32].v) : 0) << (8 - (e.value & 0x07))))
		) };
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(partial_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t((0x00FF >> (8 - e.subcount)) & (
			((source[e.value / 8ui32].v) >> (e.value & 0x07))
			| (((e.value & 0x7) != 0 ? (source[1 + e.value / 8ui32].v) : 0) << (8 - (e.value & 0x07))))
		) };
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(contiguous_tags<T> e, float const* source) {
		assert((intptr_t(source + e.value) & 31) == 0);
		return _mm256_load_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int32_t const* source) {
		assert((intptr_t(source + e.value) & 31) == 0);
		return _mm256_load_si256((const __m256i *)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint32_t const* source) {
		assert((intptr_t(source + e.value) & 31) == 0);
		return _mm256_load_si256((const __m256i *)(source + e.value));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		assert((intptr_t(source + e.value) & 31) == 0);
		return _mm256_load_si256((const __m256i *)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE fp_vector load(unaligned_contiguous_tags<T> e, float const* source) {
		return _mm256_loadu_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int32_t const* source) {
		return _mm256_loadu_si256((const __m256i *)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint32_t const* source) {
		return _mm256_loadu_si256((const __m256i *)(source + e.value));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		return _mm256_loadu_si256((const __m256i *)(source + e.value));
	}

	namespace detail {
		template<typename T>
		constexpr auto zero_is_null_wrapper(int) -> std::enable_if_t<T::zero_is_null_t, bool> { return true; }
		template<typename T>
		constexpr auto zero_is_null_wrapper(...) { return false; }
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(partial_contiguous_tags<T> e, float const* source) {
		auto mask = _mm256_loadu_ps((float const*)(load_masks)+8ui32 - e.subcount);
		auto const v = _mm256_loadu_ps(source + e.value);
		return _mm256_blendv_ps(_mm256_setzero_ps(), v, mask);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int32_t const* source) {
		auto mask = _mm256_loadu_ps((float const*)(load_masks)+8ui32 - e.subcount);
		auto const v = _mm256_loadu_ps((float const*)(source)+e.value);
		return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), v, mask));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint32_t const* source) {
		auto mask = _mm256_loadu_ps((float const*)(load_masks)+8ui32 - e.subcount);
		auto const v = _mm256_loadu_ps((float const*)(source)+e.value);
		return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), v, mask));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		auto mask = _mm256_loadu_ps((float const*)(load_masks)+8ui32 - e.subcount);
		auto const v = _mm256_loadu_ps((float const*)(source)+e.value);
		return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), v, mask));
	}
	

#pragma warning( push )
#pragma warning( disable : 4245)

	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepi16_epi32(vl);
		auto const ch = _mm_cvtepi16_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepu16_epi32(vl);
		auto const ch = _mm_cvtepu16_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepi16_epi32(vl);
			auto const ch = _mm_cvtepi16_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepu16_epi32(vl);
			auto const ch = _mm_cvtepu16_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		}
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepi16_epi32(vl);
		auto const ch = _mm_cvtepi16_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepu16_epi32(vl);
		auto const ch = _mm_cvtepu16_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepi16_epi32(vl);
			auto const ch = _mm_cvtepi16_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepu16_epi32(vl);
			auto const ch = _mm_cvtepu16_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepi16_epi32(vl);
		auto const ch = _mm_cvtepi16_epi32(vh);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 - e.subcount));
		auto const mask_h = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 + 4ui32 - e.subcount));

		return int_vector(_mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l), _mm_blendv_epi8(_mm_setzero_si128(), ch, mask_h));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

		auto const cl = _mm_cvtepu16_epi32(vl);
		auto const ch = _mm_cvtepu16_epi32(vh);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 - e.subcount));
		auto const mask_h = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 + 4ui32 - e.subcount));

		return int_vector(_mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l), _mm_blendv_epi8(_mm_setzero_si128(), ch, mask_h));
	}
	
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepi16_epi32(vl);
			auto const ch = _mm_cvtepi16_epi32(vh);
			
			auto mask = _mm256_loadu_ps((float const*)load_masks + 8ui32 - e.subcount);
			return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), _mm256_castsi256_ps(_mm256_setr_m128i(cl, ch)), mask));
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const vh = _mm_loadl_epi64((const __m128i *)(source + e.value + 4));

			auto const cl = _mm_cvtepu16_epi32(vl);
			auto const ch = _mm_cvtepu16_epi32(vh);

			
			auto mask = _mm256_loadu_ps((float const*)load_masks + 8ui32 - e.subcount);
			return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), _mm256_castsi256_ps(_mm256_setr_m128i(cl, ch)), mask));
		}
	}
	
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepi8_epi32(vl);
		auto const ch = _mm_cvtepi8_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepu8_epi32(vl);
		auto const ch = _mm_cvtepu8_epi32(vh);
			
		return int_vector(cl, ch);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepi8_epi32(vl);
			auto const ch = _mm_cvtepi8_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepu8_epi32(vl);
			auto const ch = _mm_cvtepu8_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		}
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepi8_epi32(vl);
		auto const ch = _mm_cvtepi8_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepu8_epi32(vl);
		auto const ch = _mm_cvtepu8_epi32(vh);

		return int_vector(cl, ch);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepi8_epi32(vl);
			auto const ch = _mm_cvtepi8_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepu8_epi32(vl);
			auto const ch = _mm_cvtepu8_epi32(vh);

			return _mm256_setr_m128i(cl, ch);
		}
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepi8_epi32(vl);
		auto const ch = _mm_cvtepi8_epi32(vh);

			
		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 - e.subcount));
		auto const mask_h = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 + 4ui32 - e.subcount));

		return int_vector(_mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l), _mm_blendv_epi8(_mm_setzero_si128(), ch, mask_h));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const vh = _mm_loadu_si32(source + e.value + 4);

		auto const cl = _mm_cvtepu8_epi32(vl);
		auto const ch = _mm_cvtepu8_epi32(vh);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 - e.subcount));
		auto const mask_h = _mm_loadu_si128((const __m128i *)(load_masks + 8ui32 + 4ui32 - e.subcount));

		return int_vector(_mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l), _mm_blendv_epi8(_mm_setzero_si128(), ch, mask_h));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepi8_epi32(vl);
			auto const ch = _mm_cvtepi8_epi32(vh);

			
			auto mask = _mm256_loadu_ps((float const*)load_masks + 8ui32 - e.subcount);
			return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), _mm256_castsi256_ps(_mm256_setr_m128i(cl, ch)), mask));
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const vh = _mm_loadu_si32(source + e.value + 4);

			auto const cl = _mm_cvtepu8_epi32(vl);
			auto const ch = _mm_cvtepu8_epi32(vh);

			
			auto mask = _mm256_loadu_ps((float const*)load_masks + 8ui32 - e.subcount);
			return _mm256_castps_si256(_mm256_blendv_ps(_mm256_setzero_ps(), _mm256_castsi256_ps(_mm256_setr_m128i(cl, ch)), mask));
		}
	}
	
	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, float const* source) {
		return fp_vector(
			source[indices.value.m256i_i32[0]],
			source[indices.value.m256i_i32[1]],
			source[indices.value.m256i_i32[2]],
			source[indices.value.m256i_i32[3]],
			source[indices.value.m256i_i32[4]],
			source[indices.value.m256i_i32[5]],
			source[indices.value.m256i_i32[6]],
			source[indices.value.m256i_i32[7]]
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			int32_t(source[indices.value.m256i_i32[0]]),
			int32_t(source[indices.value.m256i_i32[1]]),
			int32_t(source[indices.value.m256i_i32[2]]),
			int32_t(source[indices.value.m256i_i32[3]]),
			int32_t(source[indices.value.m256i_i32[4]]),
			int32_t(source[indices.value.m256i_i32[5]]),
			int32_t(source[indices.value.m256i_i32[6]]),
			int32_t(source[indices.value.m256i_i32[7]])
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			source[indices.value.m256i_i32[0]],
			source[indices.value.m256i_i32[1]],
			source[indices.value.m256i_i32[2]],
			source[indices.value.m256i_i32[3]],
			source[indices.value.m256i_i32[4]],
			source[indices.value.m256i_i32[5]],
			source[indices.value.m256i_i32[6]],
			source[indices.value.m256i_i32[7]]
			);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[0])) << 0) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[1])) << 1) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[2])) << 2) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[3])) << 3) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[4])) << 4) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[5])) << 5) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[6])) << 6) |
			(int32_t(dcon::bit_vector_test(source, indices.value.m256i_i32[7])) << 7)
		) };
	}

	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, mask_vector mask, float const* source) {
		return fp_vector(
			(mask[0]) ? source[indices.value.m256i_i32[0]] : 0.0f,
			(mask[1]) ? source[indices.value.m256i_i32[1]] : 0.0f,
			(mask[2]) ? source[indices.value.m256i_i32[2]] : 0.0f,
			(mask[3]) ? source[indices.value.m256i_i32[3]] : 0.0f,
			(mask[4]) ? source[indices.value.m256i_i32[4]] : 0.0f,
			(mask[5]) ? source[indices.value.m256i_i32[5]] : 0.0f,
			(mask[6]) ? source[indices.value.m256i_i32[6]] : 0.0f,
			(mask[7]) ? source[indices.value.m256i_i32[7]] : 0.0f
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, mask_vector mask, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			(mask[0]) ? int32_t(source[indices.value.m256i_i32[0]]) : 0,
			(mask[1]) ? int32_t(source[indices.value.m256i_i32[1]]) : 0,
			(mask[2]) ? int32_t(source[indices.value.m256i_i32[2]]) : 0,
			(mask[3]) ? int32_t(source[indices.value.m256i_i32[3]]) : 0,
			(mask[4]) ? int32_t(source[indices.value.m256i_i32[4]]) : 0,
			(mask[5]) ? int32_t(source[indices.value.m256i_i32[5]]) : 0,
			(mask[6]) ? int32_t(source[indices.value.m256i_i32[6]]) : 0,
			(mask[7]) ? int32_t(source[indices.value.m256i_i32[7]]) : 0
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, mask_vector mask, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			(mask[0]) ? source[indices.value.m256i_i32[0]] : U(),
			(mask[1]) ? source[indices.value.m256i_i32[1]] : U(),
			(mask[2]) ? source[indices.value.m256i_i32[2]] : U(),
			(mask[3]) ? source[indices.value.m256i_i32[3]] : U(),
			(mask[4]) ? source[indices.value.m256i_i32[4]] : U(),
			(mask[5]) ? source[indices.value.m256i_i32[5]] : U(),
			(mask[6]) ? source[indices.value.m256i_i32[6]] : U(),
			(mask[7]) ? source[indices.value.m256i_i32[7]] : U()
			);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t((mask[0]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[0]) : false) << 0) |
			(int32_t((mask[1]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[1]) : false) << 1) |
			(int32_t((mask[2]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[2]) : false) << 2) |
			(int32_t((mask[3]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[3]) : false) << 3) |
			(int32_t((mask[4]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[4]) : false) << 4) |
			(int32_t((mask[5]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[5]) : false) << 5) |
			(int32_t((mask[6]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[6]) : false) << 6) |
			(int32_t((mask[7]) ? dcon::bit_vector_test(source, indices.value.m256i_i32[7]) : false) << 7)
		) };
	}

	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, vbitfield_type mask, float const* source) {
		return fp_vector(
			(mask.v & 0x001) != 0 ? source[indices.value.m256i_i32[0]] : 0.0f,
			(mask.v & 0x002) != 0 ? source[indices.value.m256i_i32[1]] : 0.0f,
			(mask.v & 0x004) != 0 ? source[indices.value.m256i_i32[2]] : 0.0f,
			(mask.v & 0x008) != 0 ? source[indices.value.m256i_i32[3]] : 0.0f,
			(mask.v & 0x010) != 0 ? source[indices.value.m256i_i32[4]] : 0.0f,
			(mask.v & 0x020) != 0 ? source[indices.value.m256i_i32[5]] : 0.0f,
			(mask.v & 0x040) != 0 ? source[indices.value.m256i_i32[6]] : 0.0f,
			(mask.v & 0x080) != 0 ? source[indices.value.m256i_i32[7]] : 0.0f
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, vbitfield_type mask, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			(mask.v & 0x001) != 0 ? int32_t(source[indices.value.m256i_i32[0]]) : 0,
			(mask.v & 0x002) != 0 ? int32_t(source[indices.value.m256i_i32[1]]) : 0,
			(mask.v & 0x004) != 0 ? int32_t(source[indices.value.m256i_i32[2]]) : 0,
			(mask.v & 0x008) != 0 ? int32_t(source[indices.value.m256i_i32[3]]) : 0,
			(mask.v & 0x010) != 0 ? int32_t(source[indices.value.m256i_i32[4]]) : 0,
			(mask.v & 0x020) != 0 ? int32_t(source[indices.value.m256i_i32[5]]) : 0,
			(mask.v & 0x040) != 0 ? int32_t(source[indices.value.m256i_i32[6]]) : 0,
			(mask.v & 0x080) != 0 ? int32_t(source[indices.value.m256i_i32[7]]) : 0
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, vbitfield_type mask, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			(mask.v & 0x001) != 0 ? source[indices.value.m256i_i32[0]] : U(),
			(mask.v & 0x002) != 0 ? source[indices.value.m256i_i32[1]] : U(),
			(mask.v & 0x004) != 0 ? source[indices.value.m256i_i32[2]] : U(),
			(mask.v & 0x008) != 0 ? source[indices.value.m256i_i32[3]] : U(),
			(mask.v & 0x010) != 0 ? source[indices.value.m256i_i32[4]] : U(),
			(mask.v & 0x020) != 0 ? source[indices.value.m256i_i32[5]] : U(),
			(mask.v & 0x040) != 0 ? source[indices.value.m256i_i32[6]] : U(),
			(mask.v & 0x080) != 0 ? source[indices.value.m256i_i32[7]] : U()
			);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t((mask.v & 0x001) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[0]) : false) << 0) |
			(int32_t((mask.v & 0x002) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[1]) : false) << 1) |
			(int32_t((mask.v & 0x004) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[2]) : false) << 2) |
			(int32_t((mask.v & 0x008) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[3]) : false) << 3) |
			(int32_t((mask.v & 0x010) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[4]) : false) << 4) |
			(int32_t((mask.v & 0x020) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[5]) : false) << 5) |
			(int32_t((mask.v & 0x040) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[6]) : false) << 6) |
			(int32_t((mask.v & 0x080) != 0 ? dcon::bit_vector_test(source, indices.value.m256i_i32[7]) : false) << 7)
		) };
	}
#pragma warning( pop ) 

	//-----

	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, float* dest, fp_vector values) {
		assert((intptr_t(dest + e.value) & 31) == 0);
		return _mm256_store_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, int32_t* dest, int_vector values) {
		assert((intptr_t(dest + e.value) & 31) == 0);
		_mm256_store_si256((__m256i *)(dest + e.value), values.to_256_packed_int());
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		assert((intptr_t(dest + e.value) & 31) == 0);
		_mm256_store_si256((__m256i*)(dest + e.value), values.to_256_packed_int());
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		assert((intptr_t(dest + e.value) & 31) == 0);
		_mm256_store_si256((__m128i*)(dest + e.value), values.to_original_values());
	}

	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, float* dest, fp_vector values) {
		return _mm256_storeu_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, int32_t* dest, int_vector values) {
		_mm256_storeu_si256((__m256i *)(dest + e.value), values.to_256_packed_int());
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		_mm256_storeu_si256((__m256i*)(dest + e.value), values.to_256_packed_int());
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(unaligned_contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		assert((intptr_t(dest + e.value) & 31) == 0);
		_mm256_store_si256((__m128i*)(dest + e.value), values.to_original_values());
	}

	template<typename T>
	RELEASE_INLINE void store(contiguous_tags_base<T> e, int16_t* dest, int_vector values) {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = int16_t(values[i]);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags_base<T> e, uint16_t* dest, int_vector values) {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = uint16_t(values[i]);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags_base<T> e, int8_t* dest, int_vector values) {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = int8_t(values[i]);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags_base<T> e, uint8_t* dest, int_vector values) {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = uint8_t(values[i]);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(contiguous_tags_base<T> e, U* dest, tagged_vector<U> values)->std::enable_if_t < sizeof(U) < 4, void > {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = values[i];
	}

	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, float* dest, fp_vector values) {
		switch(e.subcount) {
			default:
				// fallthrough
			case 8:
				dest[e.value + 7] = values[7];
				// fallthrough
			case 7:
				dest[e.value + 6] = values[6];
				// fallthrough
			case 6:
				dest[e.value + 5] = values[5];
				// fallthrough
			case 5:
				dest[e.value + 4] = values[4];
				// fallthrough
			case 4:
				dest[e.value + 3] = values[3];
				// fallthrough
			case 3:
				dest[e.value + 2] = values[2];
				// fallthrough
			case 2:
				dest[e.value + 1] = values[1];
				// fallthrough
			case 1:
				dest[e.value + 0] = values[0];
				// fallthrough
			case 0:
				break;
		}
	}
	template<typename T, typename I>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, I* dest, int_vector values) {
		switch(e.subcount) {
			default:
				// fallthrough
			case 8:
				dest[e.value + 7] = I(values[7]);
				// fallthrough
			case 7:
				dest[e.value + 6] = I(values[6]);
				// fallthrough
			case 6:
				dest[e.value + 5] = I(values[5]);
				// fallthrough
			case 5:
				dest[e.value + 4] = I(values[4]);
				// fallthrough
			case 4:
				dest[e.value + 3] = I(values[3]);
				// fallthrough
			case 3:
				dest[e.value + 2] = I(values[2]);
				// fallthrough
			case 2:
				dest[e.value + 1] = I(values[1]);
				// fallthrough
			case 1:
				dest[e.value + 0] = I(values[0]);
				// fallthrough
			case 0:
				break;
		}
	}
	template<typename T, typename I>
	RELEASE_INLINE auto store(partial_contiguous_tags<T> e, I* dest, tagged_vector<I> values) {
		switch(e.subcount) {
			default:
				// fallthrough
			case 8:
				dest[e.value + 7] = values[7];
				// fallthrough
			case 7:
				dest[e.value + 6] = values[6];
				// fallthrough
			case 6:
				dest[e.value + 5] = values[5];
				// fallthrough
			case 5:
				dest[e.value + 4] = values[4];
				// fallthrough
			case 4:
				dest[e.value + 3] = values[3];
				// fallthrough
			case 3:
				dest[e.value + 2] = values[2];
				// fallthrough
			case 2:
				dest[e.value + 1] = values[1];
				// fallthrough
			case 1:
				dest[e.value + 0] = values[0];
				// fallthrough
			case 0:
				break;
		}
	}

	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		dest[e.value / 8ui32].v = values.v;
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			auto old_value = dest[e.value / 8ui32].v;
			auto mask = 0x0FF << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			auto old_masked_out = (old_value & ~mask);
			auto combined = uint8_t(old_masked_out | adju_value);
			dest[e.value / 8ui32].v = uint8_t(combined);
		}
		{
			if((e.value & 0x07) != 0) {
				auto old_value = dest[1 + (e.value / 8ui32)].v;
				auto mask = 0x0FF >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (8 - (e.value & 0x07));
				dest[1 + e.value / 8ui32].v = uint8_t((old_value & ~mask) | (adju_value & mask));
			}
		}
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			auto old_value = dest[e.value / 8ui32].v;
			auto mask = (0x0FF >> (8 - e.subcount)) << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			dest[e.value / 8ui32].v = uint8_t((old_value & ~mask) | (adju_value & mask));
		}
		{
			if((e.value & 0x07) != 0) {
				auto old_value = dest[1 + e.value / 8ui32].v;
				auto mask = (0x0FF >> (8 - e.subcount)) >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (8 - (e.value & 0x07));
				dest[1 + e.value / 8ui32].v = uint8_t((old_value & ~mask) | (adju_value & mask));
			}
		}
	}

	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, dcon::bitfield_type* dest, mask_vector values) {
		store(e, dest, compress_mask(values));
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, dcon::bitfield_type* dest, mask_vector values) {
		store(e, dest, compress_mask(values));
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, dcon::bitfield_type* dest, mask_vector values) {
		store(e, dest, compress_mask(values));
	}

	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, float* dest, fp_vector values) {
		for(int32_t i = 0; i < vector_size; ++i)
			dest[indices.value.m256i_i32[i]] = values[i];

	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for(int32_t i = 0; i < vector_size; ++i)
			dest[indices.value.m256i_i32[i]] = I(values[i]);
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, T* dest, tagged_vector<T> values) {
		for(int32_t i = 0; i < vector_size; ++i)
			dest[indices.value.m256i_i32[i]] = values[i];
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, dcon::bitfield_type* dest, vbitfield_type values) {
		for(int32_t i = 0; i < vector_size; ++i)
			dcon::bit_vector_set(dest, indices.value.m256i_i32[i], (values.v >> i) != 0);
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, dcon::bitfield_type* dest, mask_vector values) {
		for(int32_t i = 0; i < vector_size; ++i)
			dcon::bit_vector_set(dest, indices.value.m256i_i32[i], values[i]);
	}

	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, float* dest, fp_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if((mask.v >> i) != 0)
				dest[indices.value.m256i_i32[i]] = values[i];
		}

	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, vbitfield_type mask, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for(int32_t i = 0; i < vector_size; ++i) {
			if((mask.v >> i) != 0)
				dest[indices.value.m256i_i32[i]] = I(values[i]);
		}
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, T* dest, tagged_vector<T> values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if((mask.v >> i) != 0)
				dest[indices.value.m256i_i32[i]] = values[i];
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type* dest, vbitfield_type values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if((mask.v >> i) != 0)
				dcon::bit_vector_set(dest, indices.value.m256i_i32[i], (values.v >> i) != 0);
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type* dest, mask_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if((mask.v >> i) != 0)
				dcon::bit_vector_set(dest, indices.value.m256i_i32[i], values[i]);
		}
	}

	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, float* dest, fp_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if(mask[i])
				dest[indices.value.m256i_i32[i]] = values[i];
		}

	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, mask_vector mask, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for(int32_t i = 0; i < vector_size; ++i) {
			if(mask[i])
				dest[indices.value.m256i_i32[i]] = I(values[i]);
		}
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, T* dest, tagged_vector<T> values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if(mask[i])
				dest[indices.value.m256i_i32[i]] = values[i];
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type* dest, vbitfield_type values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if(mask[i])
				dcon::bit_vector_set(dest, indices.value.m256i_i32[i], (values.v >> i) != 0);
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type* dest, mask_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if(mask[i])
				dcon::bit_vector_set(dest, indices.value.m256i_i32[i], values[i]);
		}
	}
	
}
