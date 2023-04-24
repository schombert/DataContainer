#pragma once

//
// This file provided as part of the DataContainer project
//

#include <smmintrin.h>

namespace ve {
	constexpr int32_t vector_size = 4;

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

	struct alignas(__m128) mask_vector {
		using wrapped_value = bool;

		__m128 value;

		RELEASE_INLINE mask_vector() : value(_mm_setzero_ps()) {}
		RELEASE_INLINE mask_vector(bool b) : value(_mm_castsi128_ps(_mm_set1_epi32(-int32_t(b)))) {}
		RELEASE_INLINE mask_vector(bool a, bool b, bool c, bool d) :
			value(_mm_castsi128_ps(_mm_setr_epi32(-int32_t(a), -int32_t(b), -int32_t(c), -int32_t(d)))) {}
		RELEASE_INLINE mask_vector(vbitfield_type b) {
			const auto repeated_mask = _mm_set1_epi32(b.v);
			const auto mask_filter = _mm_setr_epi32(
				0x00000001, 0x00000002, 0x00000004, 0x00000008);
			//value = _mm_castsi128_ps(_mm_xor_si128(_mm_and_si128(repeated_mask, mask_filter), _mm_set1_epi32(-1)));
			value = _mm_castsi128_ps(_mm_cmpeq_epi32(mask_filter, _mm_and_si128(repeated_mask, mask_filter)));
		}
		RELEASE_INLINE constexpr mask_vector(__m128 v) : value(v) {}
		RELEASE_INLINE constexpr operator __m128() const {
			return value;
		}
		RELEASE_INLINE bool operator[](uint32_t i) const noexcept {
			switch(i) {
				case 0: return _mm_extract_epi32(_mm_castps_si128(value), 0) != 0;
				case 1: return _mm_extract_epi32(_mm_castps_si128(value), 1) != 0;
				case 2: return _mm_extract_epi32(_mm_castps_si128(value), 2) != 0;
				case 3: return _mm_extract_epi32(_mm_castps_si128(value), 3) != 0;
			}
			return false;
		}
		RELEASE_INLINE void set(uint32_t i, bool v) noexcept {
			auto tmp = _mm_castps_si128(value);
			switch(i) {
				case 0: value = _mm_castsi128_ps(_mm_insert_epi32(tmp, -int32_t(v), 0)); break;
				case 1: value = _mm_castsi128_ps(_mm_insert_epi32(tmp, -int32_t(v), 0)); break;
				case 2: value = _mm_castsi128_ps(_mm_insert_epi32(tmp, -int32_t(v), 0)); break;
				case 3: value = _mm_castsi128_ps(_mm_insert_epi32(tmp, -int32_t(v), 0)); break;
			}
			
		}
		RELEASE_INLINE operator vbitfield_type() const noexcept {
			vbitfield_type t;
			t.v = uint8_t(_mm_movemask_ps(value));
			return t;
		}
	};



	


	struct alignas(__m128) fp_vector {
		using wrapped_value = float;

		__m128 value;

		RELEASE_INLINE fp_vector() : value(_mm_setzero_ps()) {}
		RELEASE_INLINE constexpr fp_vector(__m128 v) : value(v) {}
		RELEASE_INLINE fp_vector(float v) : value(_mm_set1_ps(v)) {}
		RELEASE_INLINE fp_vector(float a, float b, float c, float d) : value(_mm_setr_ps(a, b, c, d)) {}
		RELEASE_INLINE constexpr operator __m128() const {
			return value;
		}
		RELEASE_INLINE float reduce() const {
			// source: Peter Cordes
			__m128 shuf = _mm_movehdup_ps(value); // broadcast elements 3,1 to 2,0
			__m128 sums = _mm_add_ps(value, shuf);
			shuf = _mm_movehl_ps(shuf, sums); // high half -> low half
			sums = _mm_add_ss(sums, shuf);
			return _mm_cvtss_f32(sums);
		}
		RELEASE_INLINE float operator[](uint32_t i) const noexcept {
#ifdef _MSC_VER 
#ifdef __clang__
			return value[i];
#else
			return value.m128_f32[i];
#endif
#else
			return value[i];
#endif
		}
		RELEASE_INLINE void set(uint32_t i, float v) noexcept {
#ifdef _MSC_VER 
#ifdef __clang__
			value[i] = v;
#else
			value.m128_f32[i] = v;
#endif
#else
			value[i] = v;
#endif
		}
	};

	struct alignas(__m128i) int_vector {
		using wrapped_value = int32_t;

		__m128i value;

		RELEASE_INLINE int_vector() : value(_mm_setzero_si128()) {}
		RELEASE_INLINE constexpr int_vector(__m128i v) : value(v) {}
		RELEASE_INLINE int_vector(int32_t v) : value(_mm_set1_epi32(v)) {}
		RELEASE_INLINE int_vector(uint32_t v) : value(_mm_set1_epi32(int32_t(v))) {}
		RELEASE_INLINE int_vector(int32_t a, int32_t b, int32_t c, int32_t d) :
			value(_mm_setr_epi32(a, b, c, d)) {}
		RELEASE_INLINE int_vector(uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
			value(_mm_setr_epi32(int32_t(a), int32_t(b), int32_t(c), int32_t(d))) {}
		
		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			switch(i) {
				case 0: return _mm_extract_epi32(value, 0);
				case 1: return _mm_extract_epi32(value, 1);
				case 2: return _mm_extract_epi32(value, 2);
				case 3: return _mm_extract_epi32(value, 3);
			}
			return 0;
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			switch(i) {
				case 0: value = _mm_insert_epi32(value, v, 0); break;
				case 1: value = _mm_insert_epi32(value, v, 1); break;
				case 2: value = _mm_insert_epi32(value, v, 2); break;
				case 3: value = _mm_insert_epi32(value, v, 3); break;
			}
		}
	};

	template<typename tag_type>
	struct alignas(__m128i) tagged_vector {
		using wrapped_value = tag_type;
		static_assert(sizeof(typename tag_type::value_base_t) <= 4);

		__m128i value;

		RELEASE_INLINE tagged_vector() : value(_mm_set1_epi32(-1)) {}
		RELEASE_INLINE constexpr tagged_vector(__m128i v) : value(tag_type::zero_is_null_t::value ? _mm_sub_epi32(v, _mm_set1_epi32(1)) : v) {}
		RELEASE_INLINE tagged_vector(tag_type v) : value(_mm_set1_epi32(v.index())) {}
		RELEASE_INLINE tagged_vector(tag_type a, tag_type b, tag_type c, tag_type d) :
			value(_mm_setr_epi32(a.index(), b.index(), c.index(), d.index()))
			{}
		RELEASE_INLINE constexpr tagged_vector(__m128i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m128i() const {
			return value;
		}
		RELEASE_INLINE __m128i to_original_values() const {
			return tag_type::zero_is_null_t::value ? _mm_add_epi32(value, _mm_set1_epi32(1)) : value;
		}

		RELEASE_INLINE tag_type operator[](uint32_t i) const noexcept {
			if constexpr(tag_type::zero_is_null_t::value) {
				tag_type r;
				switch(i) {
					case 0: r.value = typename tag_type::value_base_t(_mm_extract_epi32(value, 0) + 1); break;
					case 1: r.value = typename tag_type::value_base_t(_mm_extract_epi32(value, 1) + 1); break;
					case 2: r.value = typename tag_type::value_base_t(_mm_extract_epi32(value, 2) + 1); break;
					case 3: r.value = typename tag_type::value_base_t(_mm_extract_epi32(value, 3) + 1); break;
				}
				return r;
			} else {
				switch(i) {
					case 0: return tag_type(typename tag_type::value_base_t(_mm_extract_epi32(value, 0)));
					case 1: return tag_type(typename tag_type::value_base_t(_mm_extract_epi32(value, 1)));
					case 2: return tag_type(typename tag_type::value_base_t(_mm_extract_epi32(value, 2)));
					case 3: return tag_type(typename tag_type::value_base_t(_mm_extract_epi32(value, 3)));
				}
				return tag_type();
			}
		}
		RELEASE_INLINE void set(uint32_t i, tag_type v) noexcept {
			switch(i) {
				case 0: value = _mm_insert_epi32(value, v.index(), 0); break;
				case 1: value = _mm_insert_epi32(value, v.index(), 1); break;
				case 2: value = _mm_insert_epi32(value, v.index(), 2); break;
				case 3: value = _mm_insert_epi32(value, v.index(), 3); break;
			}
		}
	};

	template<>
	struct alignas(__m128i) tagged_vector<int32_t> {
		using wrapped_value = int32_t;

		__m128i value;

		RELEASE_INLINE tagged_vector() : value(_mm_set1_epi32(-1)) {}
		RELEASE_INLINE constexpr tagged_vector(__m128i v) : value(v) {}
		RELEASE_INLINE tagged_vector(int32_t v) : value(_mm_set1_epi32(v)) {}
		RELEASE_INLINE tagged_vector(int32_t a, int32_t b, int32_t c, int32_t d) : value(_mm_setr_epi32(a, b, c, d)) {}
		RELEASE_INLINE constexpr tagged_vector(__m128i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m128i() const {
			return value;
		}
		RELEASE_INLINE __m128i to_original_values() const {
			return value;
		}

		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			switch(i) {
				case 0: return _mm_extract_epi32(value, 0);
				case 1: return _mm_extract_epi32(value, 1);
				case 2: return _mm_extract_epi32(value, 2);
				case 3: return _mm_extract_epi32(value, 3);
			}
			return 0;
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			switch(i) {
				case 0: value = _mm_insert_epi32(value, v, 0); break;
				case 1: value = _mm_insert_epi32(value, v, 1); break;
				case 2: value = _mm_insert_epi32(value, v, 2); break;
				case 3: value = _mm_insert_epi32(value, v, 3); break;
			}
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

	template<>
	struct contiguous_tags_base<int32_t> {
		uint32_t value = 0;
		using tag_type = int32_t;
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
			return tag_type(value + i);
		}

		constexpr bool operator==(contiguous_tags_base<tag_type> o) const noexcept {
			return value == o.value;
		}
		constexpr bool operator!=(contiguous_tags_base<tag_type> o) const noexcept {
			return value != o.value;
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

			if constexpr(std::is_same_v<decltype(f(nth_item<uint32_t(0)>(params) ...)), void>) {
				switch(limit) {
					default:;
					case uint32_t(4): f(nth_item<uint32_t(3)>(params) ...);
					case uint32_t(3): f(nth_item<uint32_t(2)>(params) ...);
					case uint32_t(2): f(nth_item<uint32_t(1)>(params) ...);
					case uint32_t(1): f(nth_item<uint32_t(0)>(params) ...);
					case uint32_t(0):;
				}
			} else {
				value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))> temp;
				switch(limit) {
					default:;
					case uint32_t(4): temp.set(3, f(nth_item<uint32_t(3)>(params) ...));
					case uint32_t(3): temp.set(2, f(nth_item<uint32_t(2)>(params) ...));
					case uint32_t(2): temp.set(1, f(nth_item<uint32_t(1)>(params) ...));
					case uint32_t(1): temp.set(0, f(nth_item<uint32_t(0)>(params) ...));
					case uint32_t(0):;
				}
				return temp;
			}
		} else if constexpr(any_is_vector_type<PARAMS ...>::value) {
			if constexpr(std::is_same_v<decltype(f(nth_item<uint32_t(0)>(params) ...)), void>) {
				f(nth_item<uint32_t(0)>(params) ...);
				f(nth_item<uint32_t(1)>(params) ...);
				f(nth_item<uint32_t(2)>(params) ...);
				f(nth_item<uint32_t(3)>(params) ...);
			} else {
				return value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))>(
					f(nth_item<uint32_t(0)>(params) ...),
					f(nth_item<uint32_t(1)>(params) ...),
					f(nth_item<uint32_t(2)>(params) ...),
					f(nth_item<uint32_t(3)>(params) ...)
					);
			}
		} else {
			return f(params ...);
		}
	}

	template<typename FUNC, typename ... PARAMS>
	RELEASE_INLINE auto apply_with_indices(FUNC&& f, PARAMS ... params)
		->  value_to_vector_type<decltype(f(uint32_t(0), nth_item<uint32_t(0)>(params) ...))> {
		if constexpr(any_is_partial<PARAMS ...>) {
			const uint32_t limit = minimum_partial(params ...);

			if constexpr(std::is_same_v<decltype(f(uint32_t(0), nth_item<uint32_t(0)>(params) ...)), void>) {
				switch(limit) {
					default:;
					case uint32_t(4): f(uint32_t(3), nth_item<uint32_t(3)>(params) ...);
					case uint32_t(3): f(uint32_t(2), nth_item<uint32_t(2)>(params) ...);
					case uint32_t(2): f(uint32_t(1), nth_item<uint32_t(1)>(params) ...);
					case uint32_t(1): f(uint32_t(0), nth_item<uint32_t(0)>(params) ...);
					case uint32_t(0):;
				}
			} else {
				value_to_vector_type<decltype(f(uint32_t(0), nth_item<uint32_t(0)>(params) ...))> temp;
				switch(limit) {
					default:;
					case uint32_t(4): temp.set(3, f(uint32_t(3), nth_item<uint32_t(3)>(params) ...));
					case uint32_t(3): temp.set(2, f(uint32_t(2), nth_item<uint32_t(2)>(params) ...));
					case uint32_t(2): temp.set(1, f(uint32_t(1), nth_item<uint32_t(1)>(params) ...));
					case uint32_t(1): temp.set(0, f(uint32_t(0), nth_item<uint32_t(0)>(params) ...));
					case uint32_t(0):;
				}
				return temp;
			}
		} else if constexpr(std::is_same_v<decltype(f(uint32_t(0), nth_item<uint32_t(0)>(params) ...)), void>) {
			f(uint32_t(0), nth_item<uint32_t(0)>(params) ...);
			f(uint32_t(1), nth_item<uint32_t(1)>(params) ...);
			f(uint32_t(2), nth_item<uint32_t(2)>(params) ...);
			f(uint32_t(3), nth_item<uint32_t(3)>(params) ...);
		} else {
			return value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))>(
				f(uint32_t(0), nth_item<uint32_t(0)>(params) ...),
				f(uint32_t(1), nth_item<uint32_t(1)>(params) ...),
				f(uint32_t(2), nth_item<uint32_t(2)>(params) ...),
				f(uint32_t(3), nth_item<uint32_t(3)>(params) ...)
				);
		}
	}

	RELEASE_INLINE fp_vector to_float(int_vector v) {
		return _mm_cvtepi32_ps(v.value);
	}
	RELEASE_INLINE int_vector to_int(fp_vector v) {
		return _mm_cvtps_epi32(v);
	}

	RELEASE_INLINE fp_vector operator+(fp_vector a, fp_vector b) {
		return _mm_add_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a, fp_vector b) {
		return _mm_sub_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator*(fp_vector a, fp_vector b) {
		return _mm_mul_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator/(fp_vector a, fp_vector b) {
		return _mm_div_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a) {
		return fp_vector() - a;
	}

	RELEASE_INLINE int_vector operator+(int_vector a, int_vector b) {
		return _mm_add_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator-(int_vector a, int_vector b) {
		return _mm_sub_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator*(int_vector a, int_vector b) {
		return _mm_mullo_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator-(int_vector a) {
		return int_vector() - a;
	}

	RELEASE_INLINE int_vector operator|(int_vector a, int_vector b) {
		return _mm_or_si128(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator&(int_vector a, int_vector b) {
		return _mm_and_si128(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator^(int_vector a, int_vector b) {
		return _mm_xor_si128(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator~(int_vector a) {
		return int_vector() ^ a;
	}

	RELEASE_INLINE mask_vector operator&(mask_vector a, mask_vector b) {
		return _mm_and_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator|(mask_vector a, mask_vector b) {
		return _mm_or_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator^(mask_vector a, mask_vector b) {
		return _mm_xor_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator~(mask_vector a) {
		return _mm_xor_ps(a, mask_vector(true));
	}
	RELEASE_INLINE mask_vector operator!(mask_vector a) {
		return _mm_xor_ps(a, mask_vector(true));
	}
	RELEASE_INLINE mask_vector and_not(mask_vector a, mask_vector b) {
		return _mm_andnot_ps(b, a);
	}

	RELEASE_INLINE mask_vector operator&&(mask_vector a, mask_vector b) {
		return _mm_and_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator||(mask_vector a, mask_vector b) {
		return _mm_or_ps(a, b);
	}

	RELEASE_INLINE fp_vector inverse(fp_vector a) {
		return _mm_rcp_ps(a);
	}
	RELEASE_INLINE fp_vector sqrt(fp_vector a) {
		return _mm_sqrt_ps(a);
	}
	RELEASE_INLINE fp_vector inverse_sqrt(fp_vector a) {
		return _mm_rsqrt_ps(a);
	}

	RELEASE_INLINE int_vector abs(int_vector a) {
		return _mm_abs_epi32(a.value);
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
		return _mm_min_ps(a, b);
	}
	RELEASE_INLINE fp_vector max(fp_vector a, fp_vector b) {
		return _mm_max_ps(a, b);
	}
	RELEASE_INLINE fp_vector abs(fp_vector a) {
		return ve::max(a, -a);
	}
	RELEASE_INLINE fp_vector floor(fp_vector a) {
		return _mm_floor_ps(a);
	}
	RELEASE_INLINE fp_vector ceil(fp_vector a) {
		return _mm_ceil_ps(a);
	}

	RELEASE_INLINE mask_vector operator<(fp_vector a, fp_vector b) {
		return _mm_cmplt_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator>(fp_vector a, fp_vector b) {
		return _mm_cmpgt_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator<=(fp_vector a, fp_vector b) {
		return _mm_cmple_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator>=(fp_vector a, fp_vector b) {
		return _mm_cmpge_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator==(fp_vector a, fp_vector b) {
		return _mm_cmpeq_ps(a, b);
	}
	RELEASE_INLINE mask_vector operator!=(fp_vector a, fp_vector b) {
		return _mm_cmpneq_ps(a, b);
	}

	RELEASE_INLINE mask_vector operator<(int_vector a, int_vector b) {
		return _mm_castsi128_ps(_mm_cmpgt_epi32(b.value, a.value));
	}
	RELEASE_INLINE mask_vector operator>(int_vector a, int_vector b) {
		return _mm_castsi128_ps(_mm_cmpgt_epi32(a.value, b.value));
	}
	RELEASE_INLINE mask_vector operator==(int_vector a, int_vector b) {
		return _mm_castsi128_ps(_mm_cmpeq_epi32(a.value, b.value));
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
		return (a ^ b);
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
			tag_type(typename tag_type::value_base_t(a.value + 3))) == b;
	}
	template<typename tag_type>
	RELEASE_INLINE mask_vector operator!=(contiguous_tags_base<tag_type> a, tagged_vector<typename ve_identity<tag_type>::type> b) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3))) != b;
	}


	template<typename tag_type>
	RELEASE_INLINE mask_vector operator==(tagged_vector<typename ve_identity<tag_type>::type> b, contiguous_tags_base<tag_type> a) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3))) == b;
	}
	template<typename tag_type>
	RELEASE_INLINE mask_vector operator!=(tagged_vector<typename ve_identity<tag_type>::type> b, contiguous_tags_base<tag_type> a) {
		return tagged_vector<tag_type>(
			tag_type(typename tag_type::value_base_t(a.value)),
			tag_type(typename tag_type::value_base_t(a.value + 1)),
			tag_type(typename tag_type::value_base_t(a.value + 2)),
			tag_type(typename tag_type::value_base_t(a.value + 3))) != b;
	}

	RELEASE_INLINE fp_vector select(mask_vector mask, fp_vector a, fp_vector b) {
		return _mm_blendv_ps(b, a, mask);
	}

	RELEASE_INLINE int_vector select(mask_vector mask, int_vector a, int_vector b) {
		return _mm_blendv_epi8(b.value, a.value, _mm_castps_si128(mask));
	}

	template<typename T>
	RELEASE_INLINE tagged_vector<T> select(mask_vector mask, tagged_vector<T> a, tagged_vector<typename ve_identity<T>::type> b) {
		return tagged_vector<T>(_mm_blendv_epi8(b, a, _mm_castps_si128(mask)), std::true_type{});
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
		t.v  = uint8_t(_mm_movemask_ps(mask));
		return t;
	}


	constexpr uint32_t load_masks[16] = {
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0x00000000,
		0x00000000,
		0x00000000,
		0x00000000,
	};


	template<typename T>
	RELEASE_INLINE vbitfield_type load(contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(((source[e.value / uint32_t(8)].v) >> (e.value & 0x00000004)) & 0x0000000F) };
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(unaligned_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(0x0F & (
			((source[e.value / uint32_t(8)].v) >> (e.value & 0x07))
			| ((((e.value & 0x7) > 4) ? (source[1 + e.value / uint32_t(8)].v) : 0) << (8 - (e.value & 0x07))))
		) };
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(partial_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t((0x00FF >> (8 - e.subcount)) & (
			((source[e.value / uint32_t(8)].v) >> (e.value & 0x07))
			| ((((e.value & 0x7) > 4) ? (source[1 + e.value / uint32_t(8)].v) : 0) << (8 - (e.value & 0x07))))
		) };
	}
	template<typename T>
	RELEASE_INLINE fp_vector load(contiguous_tags<T> e, float const* source) {
		return _mm_load_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int32_t const* source) {
		return _mm_load_si128((__m128i const*)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint32_t const* source) {
		return _mm_load_si128((__m128i const*)(source + e.value));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		return _mm_load_si128((__m128i const*)(source + e.value));
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(unaligned_contiguous_tags<T> e, float const* source) {
		return _mm_loadu_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int32_t const* source) {
		return _mm_loadu_si128((__m128i const*)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint32_t const* source) {
		return _mm_loadu_si128((__m128i const*)(source + e.value));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		return _mm_loadu_si128((__m128i const*)(source + e.value));
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(partial_contiguous_tags<T> e, float const* source) {
		auto const mask = _mm_loadu_ps((float const*)(load_masks)+uint32_t(4) - e.subcount);
		auto const v = _mm_loadu_ps(source + e.value);
		return _mm_blendv_ps(_mm_setzero_ps(), v, mask);
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int32_t const* source) {
		auto const mask = _mm_loadu_si128((__m128i const*)(load_masks + uint32_t(4) - e.subcount));
		auto const v = _mm_loadu_si128((__m128i const*)(source + e.value));
		return _mm_blendv_epi8(_mm_setzero_si128(), v, mask);
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint32_t const* source) {
		auto const mask = _mm_loadu_si128((__m128i const*)(load_masks + uint32_t(4) - e.subcount));
		auto const v = _mm_loadu_si128((__m128i const*)(source + e.value));
		return _mm_blendv_epi8(_mm_setzero_si128(), v, mask);
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		auto const mask = _mm_loadu_si128((__m128i const*)(load_masks + uint32_t(4) - e.subcount));
		auto const v = _mm_loadu_si128((__m128i const*)(source + e.value));
		return _mm_blendv_epi8(_mm_setzero_si128(), v, mask);
	}

	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, float const* source) {
		return fp_vector(
			source[indices[0].index()],
			source[indices[1].index()],
			source[indices[2].index()],
			source[indices[3].index()]
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			int32_t(source[indices[0].index()]),
			int32_t(source[indices[1].index()]),
			int32_t(source[indices[2].index()]),
			int32_t(source[indices[3].index()])
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			source[indices[0].index()],
			source[indices[1].index()],
			source[indices[2].index()],
			source[indices[3].index()]
		);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t(dcon::bit_vector_test(source, indices[0].index())) << 0) |
			(int32_t(dcon::bit_vector_test(source, indices[1].index())) << 1) |
			(int32_t(dcon::bit_vector_test(source, indices[2].index())) << 2) |
			(int32_t(dcon::bit_vector_test(source, indices[3].index())) << 3)
		) };
	}

	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, mask_vector mask, float const* source) {
		return fp_vector(
			(mask[0]) ? source[indices[0].index()] : 0.0f,
			(mask[1]) ? source[indices[1].index()] : 0.0f,
			(mask[2]) ? source[indices[2].index()] : 0.0f,
			(mask[3]) ? source[indices[3].index()] : 0.0f
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, mask_vector mask, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			(mask[0]) ? int32_t(source[indices[0].index()]) : 0,
			(mask[1]) ? int32_t(source[indices[1].index()]) : 0,
			(mask[2]) ? int32_t(source[indices[2].index()]) : 0,
			(mask[3]) ? int32_t(source[indices[3].index()]) : 0
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, mask_vector mask, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			(mask[0]) ? source[indices[0].index()] : U(),
			(mask[1]) ? source[indices[1].index()] : U(),
			(mask[2]) ? source[indices[2].index()] : U(),
			(mask[3]) ? source[indices[3].index()] : U()
			);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t((mask[0]) ? dcon::bit_vector_test(source, indices[0].index()) : false) << 0) |
			(int32_t((mask[1]) ? dcon::bit_vector_test(source, indices[1].index()) : false) << 1) |
			(int32_t((mask[2]) ? dcon::bit_vector_test(source, indices[2].index()) : false) << 2) |
			(int32_t((mask[3]) ? dcon::bit_vector_test(source, indices[3].index()) : false) << 3)
		) };
	}

	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, vbitfield_type mask, float const* source) {
		return fp_vector(
			(mask.v & 0x01) != 0 ? source[indices[0].index()] : 0.0f,
			(mask.v & 0x02) != 0 ? source[indices[1].index()] : 0.0f,
			(mask.v & 0x04) != 0 ? source[indices[2].index()] : 0.0f,
			(mask.v & 0x08) != 0 ? source[indices[3].index()] : 0.0f
		);
	}
	template<typename U, typename I>
	RELEASE_INLINE auto load(tagged_vector<U> indices, vbitfield_type mask, I const* source) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, int_vector> {
		return int_vector(
			(mask.v & 0x01) != 0 ? int32_t(source[indices[0].index()]) : 0,
			(mask.v & 0x02) != 0 ? int32_t(source[indices[1].index()]) : 0,
			(mask.v & 0x04) != 0 ? int32_t(source[indices[2].index()]) : 0,
			(mask.v & 0x08) != 0 ? int32_t(source[indices[3].index()]) : 0
		);
	}
	template<typename U, typename T>
	RELEASE_INLINE auto load(tagged_vector<U> indices, vbitfield_type mask, T const* source) -> std::enable_if_t<!std::numeric_limits<T>::is_integer, tagged_vector<T>> {
		return tagged_vector<T>(
			(mask.v & 0x01) != 0 ? source[indices[0].index()] : U(),
			(mask.v & 0x02) != 0 ? source[indices[1].index()] : U(),
			(mask.v & 0x04) != 0 ? source[indices[2].index()] : U(),
			(mask.v & 0x08) != 0 ? source[indices[3].index()] : U()
			);
	}
	template<typename U>
	RELEASE_INLINE vbitfield_type load(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type const* source) {
		return vbitfield_type{ uint8_t(
			(int32_t((mask.v & 0x01) != 0 ? dcon::bit_vector_test(source, indices[0].index()) : false) << 0) |
			(int32_t((mask.v & 0x02) != 0 ? dcon::bit_vector_test(source, indices[1].index()) : false) << 1) |
			(int32_t((mask.v & 0x04) != 0 ? dcon::bit_vector_test(source, indices[2].index()) : false) << 2) |
			(int32_t((mask.v & 0x08) != 0 ? dcon::bit_vector_test(source, indices[3].index()) : false) << 3)
		) };
	}


	namespace detail {
		template<typename T>
		constexpr auto zero_is_null_wrapper(int) -> std::enable_if_t<T::zero_is_null_t, bool> { return true; }
		template<typename T>
		constexpr auto zero_is_null_wrapper(...) { return false; }
	}

	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		return _mm_cvtepi16_epi32(vl);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		return _mm_cvtepu16_epi32(vl);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			return _mm_cvtepi16_epi32(vl);
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			return _mm_cvtepu16_epi32(vl);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		return _mm_cvtepi16_epi32(vl);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		return _mm_cvtepu16_epi32(vl);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			return _mm_cvtepi16_epi32(vl);
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			return _mm_cvtepu16_epi32(vl);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const cl = _mm_cvtepi16_epi32(vl);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
		return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint16_t const* source) {
		auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
		auto const cl = _mm_cvtepu16_epi32(vl);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
		return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const cl = _mm_cvtepi16_epi32(vl);

			auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
			return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
		} else {
			auto const vl = _mm_loadl_epi64((const __m128i *)(source + e.value));
			auto const cl = _mm_cvtepu16_epi32(vl);

			auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
			return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		return _mm_cvtepi8_epi32(vl);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		return _mm_cvtepu8_epi32(vl);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			return _mm_cvtepi8_epi32(vl);
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			return _mm_cvtepu8_epi32(vl);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		return _mm_cvtepi8_epi32(vl);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		return _mm_cvtepu8_epi32(vl);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			return _mm_cvtepi8_epi32(vl);
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			return _mm_cvtepu8_epi32(vl);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const cl = _mm_cvtepi8_epi32(vl);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
		return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint8_t const* source) {
		auto const vl = _mm_loadu_si32(source + e.value);
		auto const cl = _mm_cvtepu8_epi32(vl);

		auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
		return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const cl = _mm_cvtepi8_epi32(vl);

			auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
			return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
		} else {
			auto const vl = _mm_loadu_si32(source + e.value);
			auto const cl = _mm_cvtepu8_epi32(vl);

			auto const mask_l = _mm_loadu_si128((const __m128i *)(load_masks + uint32_t(4) - e.subcount));
			return _mm_blendv_epi8(_mm_setzero_si128(), cl, mask_l);
		}
	}


	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, float* dest, fp_vector values) {
		_mm_store_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, int32_t* dest, int_vector values) {
		_mm_store_si128((__m128i*)(dest + e.value), values.value);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		_mm_store_si128((__m128i*)(dest + e.value), values.value);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		_mm_store_si128((__m128i*)(dest + e.value), values.to_original_values());
	}

	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, float* dest, fp_vector values) {
		_mm_storeu_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, int32_t* dest, int_vector values) {
		_mm_storeu_si128((__m128i*)(dest + e.value), values.value);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		_mm_storeu_si128((__m128i*)(dest + e.value), values.value);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(unaligned_contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		_mm_storeu_si128((__m128i*)(dest + e.value), values.to_original_values());
	}


	template<typename T>
	RELEASE_INLINE void store(contiguous_tags_base<T> e, int16_t* dest, int_vector values) {
		for(int i = 0 ; i < int(ve::vector_size); ++i)
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
	RELEASE_INLINE auto store(contiguous_tags_base<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) < 4, void> {
		for(int i = 0; i < int(ve::vector_size); ++i)
			dest[e.value + i] = values[i];
	}

	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, float* dest, fp_vector values) {
		switch(e.subcount) {
			default:
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
	template<typename T, typename U>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, U* dest, tagged_vector<U> values) {
		switch(e.subcount) {
			default:
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
		auto old_value = dest[e.value / uint32_t(8)].v;
		auto mask = 0x0F << (e.value & 0x04);
		auto adju_value = values.v << (e.value & 0x04);

		dest[e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | adju_value);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			auto old_value = dest[e.value / uint32_t(8)].v;
			auto mask = 0x0F << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			dest[e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | adju_value);
		}
		{
			if((e.value & 0x07) > 4) {
				auto old_value = dest[1 + e.value / uint32_t(8)].v;
				auto mask = 0x0F >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (8 - (e.value & 0x07));
				dest[1 + e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | (adju_value & mask));
			}
		}
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			auto old_value = dest[e.value / uint32_t(8)].v;
			auto mask = (0x0F >> e.subcount) << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			dest[e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | (adju_value & mask));
		}
		{
			if((e.value & 0x07) > 4) {
				auto old_value = dest[1 + e.value / uint32_t(8)].v;
				auto mask = (0x0F >> e.subcount) >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (8 - (e.value & 0x07));
				dest[1 + e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | (adju_value & mask));
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
		for (int32_t i = 0; i < vector_size; ++i) {
#ifdef DCON_TRAP_INVALID_STORE
			assert(indices[i].index() >= 0);
#endif
			dest[indices[i].index()] = values[i];
		}
		
	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for (int32_t i = 0; i < vector_size; ++i) {
#ifdef DCON_TRAP_INVALID_STORE
			assert(indices[i].index() >= 0);
#endif
			dest[indices[i].index()] = I(values[i]);
		}
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, T* dest, tagged_vector<T> values) {
		for (int32_t i = 0; i < vector_size; ++i) {
#ifdef DCON_TRAP_INVALID_STORE
			assert(indices[i].index() >= 0);
#endif
			dest[indices[i].index()] = values[i];
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, dcon::bitfield_type* dest, vbitfield_type values) {
		for (int32_t i = 0; i < vector_size; ++i) {
#ifdef DCON_TRAP_INVALID_STORE
			assert(indices[i].index() >= 0);
#endif
			dcon::bit_vector_set(dest, indices[i].index(), ((values.v >> i) & 1) != 0);
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, dcon::bitfield_type* dest, mask_vector values) {
		for (int32_t i = 0; i < vector_size; ++i) {
#ifdef DCON_TRAP_INVALID_STORE
			assert(indices[i].index() >= 0);
#endif
			dcon::bit_vector_set(dest, indices[i].index(), values[i]);
		}
	}

	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, float* dest, fp_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (((mask.v >> i) & 1) != 0) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = values[i];
			}
		}

	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, vbitfield_type mask, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (((mask.v >> i) & 1) != 0) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = I(values[i]);
			}
		}
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, T* dest, tagged_vector<T> values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (((mask.v >> i) & 1) != 0) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = values[i];
			}
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type* dest, vbitfield_type values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (((mask.v >> i) & 1) != 0) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dcon::bit_vector_set(dest, indices[i].index(), ((values.v >> i) & 1) != 0);
			}
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, vbitfield_type mask, dcon::bitfield_type* dest, mask_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (((mask.v >> i) & 1) != 0) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dcon::bit_vector_set(dest, indices[i].index(), values[i]);
			}
		}
	}

	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, float* dest, fp_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (mask[i]) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = values[i];
			}
		}

	}
	template<typename U, typename I>
	RELEASE_INLINE auto store(tagged_vector<U> indices, mask_vector mask, I* dest, int_vector values) -> std::enable_if_t<std::numeric_limits<I>::is_integer && sizeof(I) <= 4, void> {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (mask[i]) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = I(values[i]);
			}
		}
	}
	template<typename U, typename T>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, T* dest, tagged_vector<T> values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (mask[i]) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dest[indices[i].index()] = values[i];
			}
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type* dest, vbitfield_type values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (mask[i]) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dcon::bit_vector_set(dest, indices[i].index(), ((values.v >> i) & 1) != 0);
			}
		}
	}
	template<typename U>
	RELEASE_INLINE void store(tagged_vector<U> indices, mask_vector mask, dcon::bitfield_type* dest, mask_vector values) {
		for(int32_t i = 0; i < vector_size; ++i) {
			if (mask[i]) {
#ifdef DCON_TRAP_INVALID_STORE
				assert(indices[i].index() >= 0);
#endif
				dcon::bit_vector_set(dest, indices[i].index(), values[i]);
			}
		}
	}
}