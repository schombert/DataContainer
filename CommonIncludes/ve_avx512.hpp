#pragma once

//
// This file provided as part of the DataContainer project
//

#include <cstdlib>

namespace ve {
	constexpr int32_t vector_size = 16;

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
		using storage = uint16_t;

		uint16_t v;
	};

	RELEASE_INLINE __m512i _mm512_insert_epi32(__m512i target, const int32_t x, const uint32_t index)
	{
		return _mm512_mask_set1_epi32(target, 1UL << index, x);
	}

	template <int index>
	RELEASE_INLINE int32_t _mm512_extract_epi32(__m512i target)
	{
		return _mm512_cvtsi512_si32(_mm512_alignr_epi32(target, target, index));
	}

	RELEASE_INLINE vbitfield_type operator&(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(a.v & b.v) };
	}
	RELEASE_INLINE vbitfield_type operator|(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(a.v | b.v) };
	}
	RELEASE_INLINE vbitfield_type operator^(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(a.v ^ b.v) };
	}
	RELEASE_INLINE vbitfield_type operator~(vbitfield_type a) {
		return vbitfield_type{ uint16_t(~a.v) };
	}
	RELEASE_INLINE vbitfield_type operator!(vbitfield_type a) {
		return vbitfield_type{ uint16_t(~a.v) };
	}
	RELEASE_INLINE vbitfield_type and_not(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(a.v & (~b.v)) };
	}
	RELEASE_INLINE vbitfield_type operator!=(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(a.v ^ b.v) };
	}
	RELEASE_INLINE vbitfield_type operator==(vbitfield_type a, vbitfield_type b) {
		return vbitfield_type{ uint16_t(~(a.v ^ b.v)) };
	}


	struct alignas(__mmask16) mask_vector {
		using wrapped_value = bool;

		__mmask16 value;

		RELEASE_INLINE mask_vector() : value(__mmask16(0)) {}
		RELEASE_INLINE mask_vector(bool b) : value(__mmask16(-int32_t(b))) {}
		RELEASE_INLINE mask_vector(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h, bool i, bool j, bool k, bool l, bool m, bool n, bool o, bool p) {
			value = 0;
			value |= a << 0;
			value |= b << 1;
			value |= c << 2;
			value |= d << 3;
			value |= e << 4;
			value |= f << 5;
			value |= g << 6;
			value |= h << 7;
			value |= i << 8;
			value |= j << 9;
			value |= k << 10;
			value |= l << 11;
			value |= m << 12;
			value |= n << 13;
			value |= o << 14;
			value |= p << 15;
		}
		RELEASE_INLINE mask_vector(vbitfield_type b) {
			value = (__mmask16)b.v;
		}

		RELEASE_INLINE constexpr mask_vector(__mmask16 v) : value(v) {}
		RELEASE_INLINE constexpr operator __mmask16() const
		{
			return value;
		}
		RELEASE_INLINE bool operator[](uint32_t i) const noexcept {
			return value & (1 << i);
		}
		RELEASE_INLINE void set(uint32_t i, bool v) noexcept {
			value = v ? value | (1 << i) : value & ~(1 << i);
		}
		RELEASE_INLINE operator vbitfield_type() const noexcept {
			vbitfield_type t;
			t.v = uint16_t(value);
			return t;
		}
	};


	RELEASE_INLINE vbitfield_type compress_mask(mask_vector mask) {
		vbitfield_type t;
		t.v = uint16_t(mask.value);
		return t;
	}

	struct alignas(__m512) fp_vector {
		using wrapped_value = float;

		__m512 value;

		RELEASE_INLINE fp_vector() : value(_mm512_setzero_ps()) {}
		RELEASE_INLINE constexpr fp_vector(__m512 v) : value(v) {}
		RELEASE_INLINE fp_vector(float v) : value(_mm512_set1_ps(v)) {}
		RELEASE_INLINE fp_vector(float a, float b, float c, float d, float e, float f, float g, float h, 
			float i, float j, float k, float l, float m, float n, float o, float p) : value(_mm512_setr_ps(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)) {}
		RELEASE_INLINE constexpr operator __m512() const {
			return value;
		}
		RELEASE_INLINE float reduce() const
		{
			return _mm512_reduce_add_ps(value);
		}
		RELEASE_INLINE float operator[](uint32_t i) const noexcept {
#ifdef _MSC_VER
#ifdef __clang__
			return value[i];
#else
			return value.m512_f32[i];
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
			value.m512_f32[i] = v;
#endif
#else
			value[i] = v;
#endif
		}
	};

	struct alignas(__m512i) int_vector {
		using wrapped_value = int32_t;

		__m512i value;

		RELEASE_INLINE int_vector() : value(_mm512_setzero_si512()) {}
		RELEASE_INLINE constexpr int_vector(__m512i v) : value(v) {}
		RELEASE_INLINE int_vector(int32_t v) : value(_mm512_set1_epi32(v)) {}
		RELEASE_INLINE int_vector(uint32_t v) : value(_mm512_set1_epi32(int32_t(v))) {}
		RELEASE_INLINE int_vector(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h,
			int32_t i, int32_t j, int32_t k, int32_t l, int32_t m, int32_t n, int32_t o, int32_t p) : value(_mm512_setr_epi32(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)) {}
		RELEASE_INLINE int_vector(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h,
			uint32_t i, uint32_t j, uint32_t k, uint32_t l, uint32_t m, uint32_t n, uint32_t o, uint32_t p) :
			value(_mm512_setr_epi32(int32_t(a), int32_t(b), int32_t(c), int32_t(d), int32_t(e), int32_t(f), int32_t(g), int32_t(h),
				int32_t(i), int32_t(j), int32_t(k), int32_t(l), int32_t(m), int32_t(n), int32_t(o), int32_t(p))) {}

		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			switch(i) {
				case 0: return _mm512_extract_epi32<0>(value);
				case 1: return _mm512_extract_epi32<1>(value);
				case 2: return _mm512_extract_epi32<2>(value);
				case 3: return _mm512_extract_epi32<3>(value);
				case 4: return _mm512_extract_epi32<4>(value);
				case 5: return _mm512_extract_epi32<5>(value);
				case 6: return _mm512_extract_epi32<6>(value);
				case 7: return _mm512_extract_epi32<7>(value);
				case 8: return _mm512_extract_epi32<8>(value);
				case 9: return _mm512_extract_epi32<9>(value);
				case 10: return _mm512_extract_epi32<10>(value);
				case 11: return _mm512_extract_epi32<11>(value);
				case 12: return _mm512_extract_epi32<12>(value);
				case 13: return _mm512_extract_epi32<13>(value);
				case 14: return _mm512_extract_epi32<14>(value);
				case 15: return _mm512_extract_epi32<15>(value);
			}
			return 0;
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			switch(i) {
				case 0: value = _mm512_insert_epi32(value, v, 0); break;
				case 1: value = _mm512_insert_epi32(value, v, 1); break;
				case 2: value = _mm512_insert_epi32(value, v, 2); break;
				case 3: value = _mm512_insert_epi32(value, v, 3); break;
				case 4: value = _mm512_insert_epi32(value, v, 4); break;
				case 5: value = _mm512_insert_epi32(value, v, 5); break;
				case 6: value = _mm512_insert_epi32(value, v, 6); break;
				case 7: value = _mm512_insert_epi32(value, v, 7); break;
				case 8: value = _mm512_insert_epi32(value, v, 8); break;
				case 9: value = _mm512_insert_epi32(value, v, 9); break;
				case 10: value = _mm512_insert_epi32(value, v, 10); break;
				case 11: value = _mm512_insert_epi32(value, v, 11); break;
				case 12: value = _mm512_insert_epi32(value, v, 12); break;
				case 13: value = _mm512_insert_epi32(value, v, 13); break;
				case 14: value = _mm512_insert_epi32(value, v, 14); break;
				case 15: value = _mm512_insert_epi32(value, v, 15); break;
			}
		}
	};

	template<typename tag_type>
	struct alignas(__m512i) tagged_vector {
		using wrapped_value = tag_type;
		static_assert(sizeof(typename tag_type::value_base_t) <= 4);

		__m512i value;

		RELEASE_INLINE tagged_vector() : value(_mm512_set1_epi32(-1)) {}
		RELEASE_INLINE constexpr tagged_vector(__m512i v) : value(tag_type::zero_is_null_t::value ? _mm512_sub_epi32(v, _mm512_set1_epi32(1)) : v) {}
		RELEASE_INLINE tagged_vector(tag_type v) : value(_mm512_set1_epi32(v.index())) {}
		RELEASE_INLINE tagged_vector(tag_type a, tag_type b, tag_type c, tag_type d, tag_type e, tag_type f, tag_type g, tag_type h,
			tag_type i, tag_type j, tag_type k, tag_type l, tag_type m, tag_type n, tag_type o, tag_type p) :
			value(_mm512_setr_epi32(a.index(), b.index(), c.index(), d.index(), e.index(), f.index(), g.index(), h.index(),
				i.index(), j.index(), k.index(), l.index(), m.index(), n.index(), o.index(), p.index()))
		{}
		RELEASE_INLINE constexpr tagged_vector(__m512i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m512i() const {
			return value;
		}
		RELEASE_INLINE __m512i to_original_values() const {
			if constexpr (tag_type::zero_is_null_t::value) {
				return _mm512_add_epi32(value, _mm512_set1_epi32(1));
			} else {
				return value;
			}
		}

		RELEASE_INLINE tag_type operator[](uint32_t i) const noexcept {
			if constexpr(tag_type::zero_is_null_t::value) {
				tag_type r;
				switch(i) {
					case 0: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<0>(value) + 1); break;
					case 1: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<1>(value) + 1); break;
					case 2: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<2>(value) + 1); break;
					case 3: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<3>(value) + 1); break;
					case 4: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<4>(value) + 1); break;
					case 5: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<5>(value) + 1); break;
					case 6: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<6>(value) + 1); break;
					case 7: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<7>(value) + 1); break;
					case 8: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<8>(value) + 1); break;
					case 9: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<9>(value) + 1); break;
					case 10: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<10>(value) + 1); break;
					case 11: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<11>(value) + 1); break;
					case 12: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<12>(value) + 1); break;
					case 13: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<13>(value) + 1); break;
					case 14: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<14>(value) + 1); break;
					case 15: r.value = typename tag_type::value_base_t(_mm512_extract_epi32<15>(value) + 1); break;
				}

				return r;
			} else {
				switch(i) {
					case 0: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<0>(value)));
					case 1: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<1>(value)));
					case 2: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<2>(value)));
					case 3: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<3>(value)));
					case 4: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<4>(value)));
					case 5: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<5>(value)));
					case 6: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<6>(value)));
					case 7: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<7>(value)));
					case 8: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<8>(value)));
					case 9: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<9>(value)));
					case 10: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<10>(value)));
					case 11: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<11>(value)));
					case 12: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<12>(value)));
					case 13: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<13>(value)));
					case 14: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<14>(value)));
					case 15: return tag_type(typename tag_type::value_base_t(_mm512_extract_epi32<15>(value)));
				}
				return tag_type();
			}
		}
		RELEASE_INLINE void set(uint32_t i, tag_type v) noexcept {
			switch(i) {
				case 0: value = _mm512_insert_epi32(value, v.index(), 0); break;
				case 1: value = _mm512_insert_epi32(value, v.index(), 1); break;
				case 2: value = _mm512_insert_epi32(value, v.index(), 2); break;
				case 3: value = _mm512_insert_epi32(value, v.index(), 3); break;
				case 4: value = _mm512_insert_epi32(value, v.index(), 4); break;
				case 5: value = _mm512_insert_epi32(value, v.index(), 5); break;
				case 6: value = _mm512_insert_epi32(value, v.index(), 6); break;
				case 7: value = _mm512_insert_epi32(value, v.index(), 7); break;
				case 8: value = _mm512_insert_epi32(value, v.index(), 0); break;
				case 9: value = _mm512_insert_epi32(value, v.index(), 9); break;
				case 10: value = _mm512_insert_epi32(value, v.index(), 10); break;
				case 11: value = _mm512_insert_epi32(value, v.index(), 11); break;
				case 12: value = _mm512_insert_epi32(value, v.index(), 12); break;
				case 13: value = _mm512_insert_epi32(value, v.index(), 13); break;
				case 14: value = _mm512_insert_epi32(value, v.index(), 14); break;
				case 15: value = _mm512_insert_epi32(value, v.index(), 15); break;
			}
		}
	};

	template<>
	struct alignas(__m512i) tagged_vector<int32_t> {
		using wrapped_value = int32_t;

		__m512i value;

		RELEASE_INLINE tagged_vector() : value(_mm512_set1_epi32(-1)) {}
		RELEASE_INLINE constexpr tagged_vector(__m512i v) : value(v) {}
		RELEASE_INLINE tagged_vector(int32_t v) : value(_mm512_set1_epi32(v)) {}
		RELEASE_INLINE tagged_vector(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h,
			int32_t i, int32_t j, int32_t k, int32_t l, int32_t m, int32_t n, int32_t o, int32_t p) : value(_mm512_setr_epi32(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)) {}
		RELEASE_INLINE constexpr tagged_vector(__m512i v, std::true_type) : value(v) {}

		RELEASE_INLINE constexpr operator __m512i() const {
			return value;
		}

		RELEASE_INLINE int32_t operator[](uint32_t i) const noexcept {
			switch(i) {
				case 0: return _mm512_extract_epi32<0>(value);
				case 1: return _mm512_extract_epi32<1>(value);
				case 2: return _mm512_extract_epi32<2>(value);
				case 3: return _mm512_extract_epi32<3>(value);
				case 4: return _mm512_extract_epi32<4>(value);
				case 5: return _mm512_extract_epi32<5>(value);
				case 6: return _mm512_extract_epi32<6>(value);
				case 7: return _mm512_extract_epi32<7>(value);
				case 8: return _mm512_extract_epi32<8>(value);
				case 9: return _mm512_extract_epi32<9>(value);
				case 10: return _mm512_extract_epi32<10>(value);
				case 11: return _mm512_extract_epi32<11>(value);
				case 12: return _mm512_extract_epi32<12>(value);
				case 13: return _mm512_extract_epi32<13>(value);
				case 14: return _mm512_extract_epi32<14>(value);
				case 15: return _mm512_extract_epi32<15>(value);
			}
			return 0;
		}
		RELEASE_INLINE void set(uint32_t i, int32_t v) noexcept {
			switch(i) {
				case 0: value = _mm512_insert_epi32(value, v, 0); break;
				case 1: value = _mm512_insert_epi32(value, v, 1); break;
				case 2: value = _mm512_insert_epi32(value, v, 2); break;
				case 3: value = _mm512_insert_epi32(value, v, 3); break;
				case 4: value = _mm512_insert_epi32(value, v, 4); break;
				case 5: value = _mm512_insert_epi32(value, v, 5); break;
				case 6: value = _mm512_insert_epi32(value, v, 6); break;
				case 7: value = _mm512_insert_epi32(value, v, 7); break;
				case 8: value = _mm512_insert_epi32(value, v, 8); break;
				case 9: value = _mm512_insert_epi32(value, v, 9); break;
				case 10: value = _mm512_insert_epi32(value, v, 10); break;
				case 11: value = _mm512_insert_epi32(value, v, 11); break;
				case 12: value = _mm512_insert_epi32(value, v, 12); break;
				case 13: value = _mm512_insert_epi32(value, v, 13); break;
				case 14: value = _mm512_insert_epi32(value, v, 14); break;
				case 15: value = _mm512_insert_epi32(value, v, 15); break;
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

			if constexpr(std::is_same_v<decltype(f(nth_item<uint32_t(0)>(params) ...)), void>) {
				switch(limit) {
					default: ;
					case uint32_t(16): f(nth_item<uint32_t(15)>(params) ...);
					case uint32_t(15): f(nth_item<uint32_t(14)>(params) ...);
					case uint32_t(14): f(nth_item<uint32_t(13)>(params) ...);
					case uint32_t(13): f(nth_item<uint32_t(12)>(params) ...);
					case uint32_t(12): f(nth_item<uint32_t(11)>(params) ...);
					case uint32_t(11): f(nth_item<uint32_t(10)>(params) ...);
					case uint32_t(10): f(nth_item<uint32_t(9)>(params) ...);
					case uint32_t(9): f(nth_item<uint32_t(8)>(params) ...);
					case uint32_t(8): f(nth_item<uint32_t(7)>(params) ...);
					case uint32_t(7): f(nth_item<uint32_t(6)>(params) ...);
					case uint32_t(6): f(nth_item<uint32_t(5)>(params) ...);
					case uint32_t(5): f(nth_item<uint32_t(4)>(params) ...);
					case uint32_t(4): f(nth_item<uint32_t(3)>(params) ...);
					case uint32_t(3): f(nth_item<uint32_t(2)>(params) ...);
					case uint32_t(2): f(nth_item<uint32_t(1)>(params) ...);
					case uint32_t(1): f(nth_item<uint32_t(0)>(params) ...);
					case uint32_t(0): ;
				}
			} else {
				value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))> temp;
				switch(limit) {
					default: ;
					case uint32_t(16): temp.set(15, f(nth_item<uint32_t(15)>(params) ...));
					case uint32_t(15): temp.set(14, f(nth_item<uint32_t(14)>(params) ...));
					case uint32_t(14): temp.set(13, f(nth_item<uint32_t(13)>(params) ...));
					case uint32_t(13): temp.set(12, f(nth_item<uint32_t(12)>(params) ...));
					case uint32_t(12): temp.set(11, f(nth_item<uint32_t(11)>(params) ...));
					case uint32_t(11): temp.set(10, f(nth_item<uint32_t(10)>(params) ...));
					case uint32_t(10): temp.set(9, f(nth_item<uint32_t(9)>(params) ...));
					case uint32_t(9): temp.set(8, f(nth_item<uint32_t(8)>(params) ...));
					case uint32_t(8): temp.set(7, f(nth_item<uint32_t(7)>(params) ...));
					case uint32_t(7): temp.set(6, f(nth_item<uint32_t(6)>(params) ...));
					case uint32_t(6): temp.set(5, f(nth_item<uint32_t(5)>(params) ...));
					case uint32_t(5): temp.set(4, f(nth_item<uint32_t(4)>(params) ...));
					case uint32_t(4): temp.set(3, f(nth_item<uint32_t(3)>(params) ...));
					case uint32_t(3): temp.set(2, f(nth_item<uint32_t(2)>(params) ...));
					case uint32_t(2): temp.set(1, f(nth_item<uint32_t(1)>(params) ...));
					case uint32_t(1): temp.set(0, f(nth_item<uint32_t(0)>(params) ...));
					case uint32_t(0): ;
				}
				return temp;
			}
		} else if constexpr(any_is_vector_type<PARAMS ...>::value) {
			if constexpr(std::is_same_v<decltype(f(nth_item<uint32_t(0)>(params) ...)), void>) {
				f(nth_item<uint32_t(0)>(params) ...);
				f(nth_item<uint32_t(1)>(params) ...);
				f(nth_item<uint32_t(2)>(params) ...);
				f(nth_item<uint32_t(3)>(params) ...);
				f(nth_item<uint32_t(4)>(params) ...);
				f(nth_item<uint32_t(5)>(params) ...);
				f(nth_item<uint32_t(6)>(params) ...);
				f(nth_item<uint32_t(7)>(params) ...);
				f(nth_item<uint32_t(8)>(params) ...);
				f(nth_item<uint32_t(9)>(params) ...);
				f(nth_item<uint32_t(10)>(params) ...);
				f(nth_item<uint32_t(11)>(params) ...);
				f(nth_item<uint32_t(12)>(params) ...);
				f(nth_item<uint32_t(13)>(params) ...);
				f(nth_item<uint32_t(14)>(params) ...);
				f(nth_item<uint32_t(15)>(params) ...);
			} else {
				return value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))>(
					f(nth_item<uint32_t(0)>(params) ...),
					f(nth_item<uint32_t(1)>(params) ...),
					f(nth_item<uint32_t(2)>(params) ...),
					f(nth_item<uint32_t(3)>(params) ...),
					f(nth_item<uint32_t(4)>(params) ...),
					f(nth_item<uint32_t(5)>(params) ...),
					f(nth_item<uint32_t(6)>(params) ...),
					f(nth_item<uint32_t(7)>(params) ...),
					f(nth_item<uint32_t(8)>(params) ...),
					f(nth_item<uint32_t(9)>(params) ...),
					f(nth_item<uint32_t(10)>(params) ...),
					f(nth_item<uint32_t(11)>(params) ...),
					f(nth_item<uint32_t(12)>(params) ...),
					f(nth_item<uint32_t(13)>(params) ...),
					f(nth_item<uint32_t(14)>(params) ...),
					f(nth_item<uint32_t(15)>(params) ...)
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
					case uint32_t(16): f(uint32_t(15), nth_item<uint32_t(15)>(params) ...);
					case uint32_t(15): f(uint32_t(14), nth_item<uint32_t(14)>(params) ...);
					case uint32_t(14): f(uint32_t(13), nth_item<uint32_t(13)>(params) ...);
					case uint32_t(13): f(uint32_t(12), nth_item<uint32_t(12)>(params) ...);
					case uint32_t(12): f(uint32_t(11), nth_item<uint32_t(11)>(params) ...);
					case uint32_t(11): f(uint32_t(10), nth_item<uint32_t(10)>(params) ...);
					case uint32_t(10): f(uint32_t(9), nth_item<uint32_t(9)>(params) ...);
					case uint32_t(9): f(uint32_t(8), nth_item<uint32_t(8)>(params) ...);
					case uint32_t(8): f(uint32_t(7), nth_item<uint32_t(7)>(params) ...);
					case uint32_t(7): f(uint32_t(6), nth_item<uint32_t(6)>(params) ...);
					case uint32_t(6): f(uint32_t(5), nth_item<uint32_t(5)>(params) ...);
					case uint32_t(5): f(uint32_t(4), nth_item<uint32_t(4)>(params) ...);
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
					case uint32_t(16): temp.set(15, f(uint32_t(15), nth_item<uint32_t(15)>(params) ...));
					case uint32_t(15): temp.set(14, f(uint32_t(14), nth_item<uint32_t(14)>(params) ...));
					case uint32_t(14): temp.set(13, f(uint32_t(13), nth_item<uint32_t(13)>(params) ...));
					case uint32_t(13): temp.set(12, f(uint32_t(12), nth_item<uint32_t(12)>(params) ...));
					case uint32_t(12): temp.set(11, f(uint32_t(11), nth_item<uint32_t(11)>(params) ...));
					case uint32_t(11): temp.set(10, f(uint32_t(10), nth_item<uint32_t(10)>(params) ...));
					case uint32_t(10): temp.set(9, f(uint32_t(9), nth_item<uint32_t(9)>(params) ...));
					case uint32_t(9): temp.set(8, f(uint32_t(8), nth_item<uint32_t(8)>(params) ...));
					case uint32_t(8): temp.set(7, f(uint32_t(7), nth_item<uint32_t(7)>(params) ...));
					case uint32_t(7): temp.set(6, f(uint32_t(6), nth_item<uint32_t(6)>(params) ...));
					case uint32_t(6): temp.set(5, f(uint32_t(5), nth_item<uint32_t(5)>(params) ...));
					case uint32_t(5): temp.set(4, f(uint32_t(4), nth_item<uint32_t(4)>(params) ...));
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
			f(uint32_t(4), nth_item<uint32_t(4)>(params) ...);
			f(uint32_t(5), nth_item<uint32_t(5)>(params) ...);
			f(uint32_t(6), nth_item<uint32_t(6)>(params) ...);
			f(uint32_t(7), nth_item<uint32_t(7)>(params) ...);
			f(uint32_t(8), nth_item<uint32_t(8)>(params) ...);
			f(uint32_t(9), nth_item<uint32_t(9)>(params) ...);
			f(uint32_t(10), nth_item<uint32_t(10)>(params) ...);
			f(uint32_t(11), nth_item<uint32_t(11)>(params) ...);
			f(uint32_t(12), nth_item<uint32_t(12)>(params) ...);
			f(uint32_t(13), nth_item<uint32_t(13)>(params) ...);
			f(uint32_t(14), nth_item<uint32_t(14)>(params) ...);
			f(uint32_t(15), nth_item<uint32_t(15)>(params) ...);
		} else {
			return value_to_vector_type<decltype(f(nth_item<uint32_t(0)>(params) ...))>(
				f(uint32_t(0), nth_item<uint32_t(0)>(params) ...),
				f(uint32_t(1), nth_item<uint32_t(1)>(params) ...),
				f(uint32_t(2), nth_item<uint32_t(2)>(params) ...),
				f(uint32_t(3), nth_item<uint32_t(3)>(params) ...),
				f(uint32_t(4), nth_item<uint32_t(4)>(params) ...),
				f(uint32_t(5), nth_item<uint32_t(5)>(params) ...),
				f(uint32_t(6), nth_item<uint32_t(6)>(params) ...),
				f(uint32_t(7), nth_item<uint32_t(7)>(params) ...),
				f(uint32_t(8), nth_item<uint32_t(8)>(params) ...),
				f(uint32_t(9), nth_item<uint32_t(9)>(params) ...),
				f(uint32_t(10), nth_item<uint32_t(10)>(params) ...),
				f(uint32_t(11), nth_item<uint32_t(11)>(params) ...),
				f(uint32_t(12), nth_item<uint32_t(12)>(params) ...),
				f(uint32_t(13), nth_item<uint32_t(13)>(params) ...),
				f(uint32_t(14), nth_item<uint32_t(14)>(params) ...),
				f(uint32_t(15), nth_item<uint32_t(15)>(params) ...)
				);
		}
	}

	RELEASE_INLINE fp_vector to_float(int_vector v) {
		return _mm512_cvtepi32_ps(v.value);
	}
	RELEASE_INLINE int_vector to_int(fp_vector v) {
		return _mm512_cvtps_epi32(v);
	}

	RELEASE_INLINE fp_vector operator+(fp_vector a, fp_vector b) {
		return _mm512_add_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a, fp_vector b) {
		return _mm512_sub_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator*(fp_vector a, fp_vector b) {
		return _mm512_mul_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator/(fp_vector a, fp_vector b) {
		return _mm512_div_ps(a, b);
	}
	RELEASE_INLINE fp_vector operator-(fp_vector a) {
		return fp_vector() - a;
	}

	RELEASE_INLINE int_vector operator+(int_vector a, int_vector b) {
		return _mm512_add_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator-(int_vector a, int_vector b) {
		return _mm512_sub_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator*(int_vector a, int_vector b) {
		return _mm512_mullo_epi32(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator-(int_vector a) {
		return int_vector() - a;
	}

	RELEASE_INLINE int_vector operator|(int_vector a, int_vector b) {
		return _mm512_or_si512(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator&(int_vector a, int_vector b) {
		return _mm512_and_si512(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator^(int_vector a, int_vector b) {
		return _mm512_xor_si512(a.value, b.value);
	}
	RELEASE_INLINE int_vector operator~(int_vector a) {
		return int_vector() ^ a;
	}

	RELEASE_INLINE mask_vector operator&(mask_vector a, mask_vector b) {
		return __mmask16(a.value & b.value);
	}
	RELEASE_INLINE mask_vector operator|(mask_vector a, mask_vector b) {
		return __mmask16(a.value | b.value);
	}
	RELEASE_INLINE mask_vector operator^(mask_vector a, mask_vector b) {
		return __mmask16(a.value ^ b.value);
	}
	RELEASE_INLINE mask_vector operator~(mask_vector a) {
		return __mmask16(~a.value);
	}
	RELEASE_INLINE mask_vector operator!(mask_vector a) {
		return __mmask16(~a.value);
	}
	RELEASE_INLINE mask_vector and_not(mask_vector a, mask_vector b) {
		return __mmask16(a.value & (~b.value));
	}
	RELEASE_INLINE mask_vector operator&&(mask_vector a, mask_vector b) {
		return __mmask16(a.value & b.value);
	}
	RELEASE_INLINE mask_vector operator||(mask_vector a, mask_vector b) {
		return __mmask16(a.value | b.value);
	}

	RELEASE_INLINE fp_vector inverse(fp_vector a) {
		return _mm512_rcp14_ps(a);
	}
	RELEASE_INLINE fp_vector sqrt(fp_vector a) {
		return _mm512_sqrt_ps(a);
	}
	RELEASE_INLINE fp_vector inverse_sqrt(fp_vector a) {
		return _mm512_rsqrt14_ps(a);
	}
	RELEASE_INLINE int_vector abs(int_vector a) {
		return _mm512_abs_epi32(a.value);
	}

	RELEASE_INLINE fp_vector multiply_and_add(fp_vector a, fp_vector b, fp_vector c) {
		return _mm512_fmadd_ps(a, b, c);
	}
	RELEASE_INLINE fp_vector multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c) {
		return _mm512_fmsub_ps(a, b, c);
	}
	RELEASE_INLINE fp_vector negate_multiply_and_add(fp_vector a, fp_vector b, fp_vector c) {
		return _mm512_fnmadd_ps(a, b, c);
	}
	RELEASE_INLINE fp_vector negate_multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c) {
		return _mm512_fnmsub_ps(a, b, c);
	}

	RELEASE_INLINE fp_vector min(fp_vector a, fp_vector b) {
		return _mm512_min_ps(a, b);
	}
	RELEASE_INLINE fp_vector max(fp_vector a, fp_vector b) {
		return _mm512_max_ps(a, b);
	}
	RELEASE_INLINE fp_vector abs(fp_vector a) {
		return max(a, -a);
	}
	RELEASE_INLINE fp_vector floor(fp_vector a) {
		return _mm512_floor_ps(a);
	}
	RELEASE_INLINE fp_vector ceil(fp_vector a) {
		return _mm512_ceil_ps(a);
	}

	RELEASE_INLINE mask_vector operator<(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_LT_OQ);
	}
	RELEASE_INLINE mask_vector operator>(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_GT_OQ);
	}
	RELEASE_INLINE mask_vector operator<=(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_LE_OQ);
	}
	RELEASE_INLINE mask_vector operator>=(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_GE_OQ);
	}
	RELEASE_INLINE mask_vector operator==(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_EQ_OQ);
	}
	RELEASE_INLINE mask_vector operator!=(fp_vector a, fp_vector b) {
		return _mm512_cmp_ps_mask(a, b, _CMP_NEQ_OQ);
	}

	RELEASE_INLINE mask_vector operator<(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_LT);
	}
	RELEASE_INLINE mask_vector operator>(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_NLE);
	}
	RELEASE_INLINE mask_vector operator<=(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_LE);
	}
	RELEASE_INLINE mask_vector operator>=(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_NLT);
	}
	RELEASE_INLINE mask_vector operator==(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_EQ);
	}
	RELEASE_INLINE mask_vector operator!=(int_vector a, int_vector b) {
		return _mm512_cmp_epi32_mask(a.value, b.value, _MM_CMPINT_NE);
	}
	RELEASE_INLINE mask_vector operator==(mask_vector a, mask_vector b) {
		return !(a ^ b);
	}
	RELEASE_INLINE mask_vector operator!=(mask_vector a, mask_vector b) {
		return a ^ b;
	}

	template<typename T>
	RELEASE_INLINE mask_vector operator==(tagged_vector<T> a, tagged_vector<T> b) {
		return _mm512_cmp_epi32_mask(a, b, _MM_CMPINT_EQ);
	}
	template<typename T>
	RELEASE_INLINE mask_vector operator!=(tagged_vector<T> a, tagged_vector<T> b) {
		return _mm512_cmp_epi32_mask(a, b, _MM_CMPINT_NE);
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
			tag_type(typename tag_type::value_base_t(a.value + 7)),
			tag_type(typename tag_type::value_base_t(a.value + 8)),
			tag_type(typename tag_type::value_base_t(a.value + 9)),
			tag_type(typename tag_type::value_base_t(a.value + 10)),
			tag_type(typename tag_type::value_base_t(a.value + 11)),
			tag_type(typename tag_type::value_base_t(a.value + 12)),
			tag_type(typename tag_type::value_base_t(a.value + 13)),
			tag_type(typename tag_type::value_base_t(a.value + 14)),
			tag_type(typename tag_type::value_base_t(a.value + 15))) == b;
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
			tag_type(typename tag_type::value_base_t(a.value + 7)),
			tag_type(typename tag_type::value_base_t(a.value + 8)),
			tag_type(typename tag_type::value_base_t(a.value + 9)),
			tag_type(typename tag_type::value_base_t(a.value + 10)),
			tag_type(typename tag_type::value_base_t(a.value + 11)),
			tag_type(typename tag_type::value_base_t(a.value + 12)),
			tag_type(typename tag_type::value_base_t(a.value + 13)),
			tag_type(typename tag_type::value_base_t(a.value + 14)),
			tag_type(typename tag_type::value_base_t(a.value + 15))) != b;
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
			tag_type(typename tag_type::value_base_t(a.value + 7)),
			tag_type(typename tag_type::value_base_t(a.value + 8)),
			tag_type(typename tag_type::value_base_t(a.value + 9)),
			tag_type(typename tag_type::value_base_t(a.value + 10)),
			tag_type(typename tag_type::value_base_t(a.value + 11)),
			tag_type(typename tag_type::value_base_t(a.value + 12)),
			tag_type(typename tag_type::value_base_t(a.value + 13)),
			tag_type(typename tag_type::value_base_t(a.value + 14)),
			tag_type(typename tag_type::value_base_t(a.value + 15))) == b;
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
			tag_type(typename tag_type::value_base_t(a.value + 7)),
			tag_type(typename tag_type::value_base_t(a.value + 8)),
			tag_type(typename tag_type::value_base_t(a.value + 9)),
			tag_type(typename tag_type::value_base_t(a.value + 10)),
			tag_type(typename tag_type::value_base_t(a.value + 11)),
			tag_type(typename tag_type::value_base_t(a.value + 12)),
			tag_type(typename tag_type::value_base_t(a.value + 13)),
			tag_type(typename tag_type::value_base_t(a.value + 14)),
			tag_type(typename tag_type::value_base_t(a.value + 15))) != b;
	}


	RELEASE_INLINE fp_vector select(mask_vector mask, fp_vector a, fp_vector b) {
		return _mm512_mask_blend_ps(mask, b, a);
	}

	RELEASE_INLINE int_vector select(mask_vector mask, int_vector a, int_vector b) {
		return _mm512_mask_blend_epi32(mask, b.value, a.value);
	}

	template<typename T>
	RELEASE_INLINE tagged_vector<T> select(mask_vector mask, tagged_vector<T> a, tagged_vector<typename ve_identity<T>::type> b) {
		return tagged_vector<T>(_mm512_mask_blend_epi32(mask, b, a), std::true_type{});
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


	template<typename T>
	RELEASE_INLINE vbitfield_type load(contiguous_tags<T> e, dcon::bitfield_type const* source) {
		vbitfield_type output;
		memcpy(&output.v, source + (e.value / uint32_t(8)), sizeof(uint16_t));
		return output;
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(unaligned_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		auto overflow = (e.value & 0x7) != 0 ? (source[2 + e.value / uint32_t(8)].v) : 0;
		vbitfield_type output;
		memcpy(&output.v, source + (e.value / uint32_t(8)), sizeof(uint16_t));
		output.v = output.v >> (e.value & 0x07);
		output.v = output.v | uint16_t(overflow << (16 - (e.value & 0x07)));
		return output;
	}
	template<typename T>
	RELEASE_INLINE vbitfield_type load(partial_contiguous_tags<T> e, dcon::bitfield_type const* source) {
		auto overflow = (e.value & 0x7) != 0 ? (source[2 + e.value / uint32_t(8)].v) : 0;
		vbitfield_type output;
		memcpy(&output.v, source + (e.value / uint32_t(8)), sizeof(uint16_t));
		output.v = output.v >> (e.value & 0x07);
		output.v = output.v | uint16_t(overflow << (16 - (e.value & 0x07)));
		output.v = output.v & (0xFFFF >> (16 - e.subcount));
		return output;
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(contiguous_tags<T> e, float const* source) {
		return _mm512_load_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int32_t const* source) {
		return _mm512_load_si512((const __m512i *)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint32_t const* source) {
		return _mm512_load_si512((const __m512i *)(source + e.value));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		return _mm512_load_si512((const __m512i *)(source + e.value));
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(unaligned_contiguous_tags<T> e, float const* source) {
		return _mm512_loadu_ps(source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int32_t const* source) {
		return _mm512_loadu_si512((const __m512i *)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint32_t const* source) {
		return _mm512_loadu_si512((const __m512i *)(source + e.value));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		return _mm512_loadu_si512((const __m512i *)(source + e.value));
	}

	template<typename T>
	RELEASE_INLINE fp_vector load(partial_contiguous_tags<T> e, float const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		return _mm512_mask_load_ps(_mm512_setzero_ps(), mask, source + e.value);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int32_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		return _mm512_mask_load_epi32(_mm512_setzero_si512(), mask, (int32_t const*)(source + e.value));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint32_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		return _mm512_mask_load_epi32(_mm512_setzero_si512(), mask, (int32_t const*)(source + e.value));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 4, tagged_vector<U>> {
		auto mask = __mmask16((1 << e.subcount) - 1);
		return _mm512_mask_load_epi32(_mm512_setzero_si512(), mask, (int32_t const*)(source + e.value));
	}


	// CONTINUE
	namespace detail {
		template<typename T>
		constexpr auto zero_is_null_wrapper(int) -> std::enable_if_t<T::zero_is_null_t, bool> { return true; }
		template<typename T>
		constexpr auto zero_is_null_wrapper(...) { return false; }
	}

	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int16_t const* source) {
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_cvtepi16_epi32(v);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint16_t const* source) {
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_cvtepu16_epi32(v);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_cvtepi16_epi32(v);
		} else {
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_cvtepu16_epi32(v);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int16_t const* source) {
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_cvtepi16_epi32(v);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint16_t const* source) {
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_cvtepu16_epi32(v);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_cvtepi16_epi32(v);
		} else {
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_cvtepu16_epi32(v);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int16_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_mask_blend_epi32(mask, _mm512_setzero_si512(), _mm512_cvtepi16_epi32(v));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint16_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
		return _mm512_mask_blend_epi32(mask, _mm512_setzero_si512(), _mm512_cvtepu16_epi32(v));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto mask = __mmask16((1 << e.subcount) - 1);
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_mask_blend_epi32(mask, _mm512_setzero_si512(), _mm512_cvtepi16_epi32(v));
		} else {
			auto mask = __mmask16((1 << e.subcount) - 1);
			auto v = _mm256_loadu_si256((const __m256i *)(source + e.value));
			return _mm512_mask_blend_epi32(mask, _mm512_setzero_si512(), _mm512_cvtepu16_epi32(v));
		}
	}

	


	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, int8_t const* source) {
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_cvtepi8_epi32(v);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(contiguous_tags<T> e, uint8_t const* source) {
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_cvtepu8_epi32(v);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_cvtepi8_epi32(v);
		} else {
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_cvtepu8_epi32(v);
		}
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, int8_t const* source) {
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_cvtepi8_epi32(v);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(unaligned_contiguous_tags<T> e, uint8_t const* source) {
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_cvtepu8_epi32(v);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(unaligned_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_cvtepi8_epi32(v);
		} else {
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_cvtepu8_epi32(v);
		}
	}

	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, int8_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_mask_mov_epi32(_mm512_setzero_si512(), mask, _mm512_cvtepi8_epi32(v));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(partial_contiguous_tags<T> e, uint8_t const* source) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
		return _mm512_mask_mov_epi32(_mm512_setzero_si512(), mask, _mm512_cvtepu8_epi32(v));
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(partial_contiguous_tags<T> e, U const* source) -> std::enable_if_t<sizeof(U) == 1 && !std::is_same_v<U, dcon::bitfield_type>, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto mask = __mmask16((1 << e.subcount) - 1);
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_mask_mov_epi32(_mm512_setzero_si512(), mask, _mm512_cvtepi8_epi32(v));
		} else {
			auto mask = __mmask16((1 << e.subcount) - 1);
			auto v = _mm_loadu_si128((const __m128i *)(source + e.value));
			return _mm512_mask_mov_epi32(_mm512_setzero_si512(), mask, _mm512_cvtepu8_epi32(v));
		}
	}

	// gather unmasked
	template<typename T>
	RELEASE_INLINE mask_vector load(tagged_vector<T> indices, dcon::bitfield_type const* source) {
		const auto byte_indices = _mm512_srai_epi32(indices.value, 3);
		const auto bit_indices = _mm512_and_si512(indices.value, _mm512_set1_epi32(0x00000007));
		auto const gathered = _mm512_i32gather_epi32(byte_indices, (int32_t const*)(source), 1);
		auto const shifted = _mm512_srlv_epi32(gathered, bit_indices);
		return _mm512_test_epi32_mask(shifted, _mm512_set1_epi32(0x00000001));
	}
	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, float const* source) {
		return _mm512_i32gather_ps(indices.value, source, 4);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, U const* source) -> std::enable_if_t<std::numeric_limits<U>::is_integer && sizeof(U) == 4, value_to_vector_type<U>> {
		return _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 4);
	}

	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, int16_t const* source) {
		auto v = _mm512_i32gather_epi32(_mm512_sub_epi32(indices.value, _mm512_set1_epi32(1)), (int32_t const*)source, 2);
		return _mm512_srai_epi32(v, 16);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, uint16_t const* source) {
		auto v = _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 2);
		return _mm512_and_si512(v, _mm512_set1_epi32(0xFFFF));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, int8_t const* source) {
		auto v = _mm512_i32gather_epi32(_mm512_sub_epi32(indices.value, _mm512_set1_epi32(3)), (int32_t const*)source, 1);
		return _mm512_srai_epi32(v, 24);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, uint8_t const* source) {
		auto v = _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 1);
		return _mm512_and_si512(v, _mm512_set1_epi32(0xFF));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, U const* source) -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 4, tagged_vector<U>> {
		return _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 4);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, U const* source)  -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm512_i32gather_epi32(_mm512_sub_epi32(indices.value, _mm512_set1_epi32(1)), (int32_t const*)source, 2);
			return _mm512_srai_epi32(v, 16);
		} else {
			auto v = _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 2);
			return _mm512_and_si512(v, _mm512_set1_epi32(0xFFFF));
		}
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, U const* source) -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 1, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm512_i32gather_epi32(_mm512_sub_epi32(indices.value, _mm512_set1_epi32(3)), (int32_t const*)source, 1);
			return _mm512_srai_epi32(v, 24);
		} else {
			auto v = _mm512_i32gather_epi32(indices.value, (int32_t const*)source, 1);
			return _mm512_and_si512(v, _mm512_set1_epi32(0xFF));
		}
	}

	// gather masked
	template<typename T>
	RELEASE_INLINE mask_vector load(tagged_vector<T> indices, mask_vector mask, dcon::bitfield_type const* source) {
		const auto byte_indices = _mm512_srai_epi32(indices.value, 3);
		const auto bit_indices = _mm512_and_si512(indices.value, _mm512_set1_epi32(0x00000007));
		auto const gathered = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, byte_indices, (int32_t const*)(source), 1);
		auto const shifted = _mm512_srlv_epi32(gathered, bit_indices);
		return _mm512_test_epi32_mask(shifted, _mm512_set1_epi32(0x00000001));
	}
	template<typename U>
	RELEASE_INLINE fp_vector load(tagged_vector<U> indices, mask_vector mask, float const* source) {
		return _mm512_mask_i32gather_ps(_mm512_setzero_ps(), mask, indices.value, source, 4);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, mask_vector mask, U const* source) -> std::enable_if_t<std::numeric_limits<U>::is_integer && sizeof(U) == 4, value_to_vector_type<U>> {
		return _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 4);
	}

	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, mask_vector mask, int16_t const* source) {
		auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, _mm512_sub_epi32(indices.value, _mm512_set1_epi32(1)), (int32_t const*)source, 2);
		return _mm512_srai_epi32(v, 16);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, mask_vector mask, uint16_t const* source) {
		auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 2);
		return _mm512_and_si512(v, _mm512_set1_epi32(0xFFFF));
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, mask_vector mask, int8_t const* source) {
		auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, _mm512_sub_epi32(indices.value, _mm512_set1_epi32(3)), (int32_t const*)source, 1);
		return _mm512_srai_epi32(v, 24);
	}
	template<typename T>
	RELEASE_INLINE int_vector load(tagged_vector<T> indices, mask_vector mask, uint8_t const* source) {
		auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 1);
		return _mm512_and_si512(v, _mm512_set1_epi32(0xFF));
	}

	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, mask_vector mask, U const* source)  -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 4, tagged_vector<U>> {
		return _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 4);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, mask_vector mask, U const* source)  -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 2, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, _mm512_sub_epi32(indices.value, _mm512_set1_epi32(1)), (int32_t const*)source, 2);
			return _mm512_srai_epi32(v, 16);
		} else {
			auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 2);
			return _mm512_and_si512(v, _mm512_set1_epi32(0xFFFF));
		}
	}
	template<typename T, typename U>
	RELEASE_INLINE auto load(tagged_vector<T> indices, mask_vector mask, U const* source)  -> std::enable_if_t<!std::numeric_limits<U>::is_integer && sizeof(U) == 1, tagged_vector<U>> {
		if constexpr(!detail::zero_is_null_wrapper<U>(0)) {
			auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, _mm512_sub_epi32(indices.value, _mm512_set1_epi32(3)), (int32_t const*)source, 1);
			return _mm512_srai_epi32(v, 24);
		} else {
			auto v = _mm512_mask_i32gather_epi32(_mm512_setzero_si512(), mask, indices.value, (int32_t const*)source, 1);
			return _mm512_and_si512(v, _mm512_set1_epi32(0xFF));
		}
	}


	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, float* dest, fp_vector values) {
		_mm512_store_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, int32_t* dest, int_vector values) {
		_mm512_store_si512((__m512i *)(dest + e.value), values.value);
	}
	template<typename T>
	RELEASE_INLINE void store(contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		_mm512_store_si512((__m512i*)(dest + e.value), values.value);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		_mm512_store_si512((__m512i*)(dest + e.value), values.to_original_values());
	}

	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, float* dest, fp_vector values) {
		_mm512_storeu_ps(dest + e.value, values);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, int32_t* dest, int_vector values) {
		_mm512_storeu_si512((__m512i *)(dest + e.value), values.value);
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		_mm512_storeu_si512((__m512i*)(dest + e.value), values.value);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(unaligned_contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		_mm512_store_si512((__m512i*)(dest + e.value), values.to_original_values());
	}

	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, float* dest, fp_vector values) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		_mm512_mask_store_ps(dest + e.value, mask, values);
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, int32_t* dest, int_vector values) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		_mm512_mask_store_epi32(dest + e.value, mask, values.value);
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, uint32_t* dest, int_vector values) {
		auto mask = __mmask16((1 << e.subcount) - 1);
		_mm512_mask_store_epi32((int32_t*)(dest + e.value), mask, values.value);
	}
	template<typename T, typename U>
	RELEASE_INLINE auto store(partial_contiguous_tags<T> e, U* dest, tagged_vector<U> values) -> std::enable_if_t<sizeof(U) == 4, void> {
		auto mask = __mmask16((1 << e.subcount) - 1);
		_mm512_mask_store_epi32((int32_t*)(dest + e.value), mask, values.to_original_values());
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
	template<typename T, typename I>
	RELEASE_INLINE auto store(partial_contiguous_tags<T> e, I* dest, int_vector values) -> std::enable_if_t<sizeof(I) < 4, void> {
		switch(e.subcount) {
			default:
				// fallthrough
			case 16:
				dest[e.value + 15] = I(values[15]);
				// fallthrough
			case 15:
				dest[e.value + 14] = I(values[14]);
				// fallthrough
			case 14:
				dest[e.value + 13] = I(values[13]);
				// fallthrough
			case 13:
				dest[e.value + 12] = I(values[12]);
				// fallthrough
			case 12:
				dest[e.value + 11] = I(values[11]);
				// fallthrough
			case 11:
				dest[e.value + 10] = I(values[10]);
				// fallthrough
			case 10:
				dest[e.value + 9] = I(values[9]);
				// fallthrough
			case 9:
				dest[e.value + 8] = I(values[8]);
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
	RELEASE_INLINE auto store(partial_contiguous_tags<T> e, I* dest, tagged_vector<I> values)->std::enable_if_t < sizeof(I) < 4, void > {
		switch(e.subcount) {
			default:
				// fallthrough
			case 16:
				dest[e.value + 15] = values[15];
				// fallthrough
			case 15:
				dest[e.value + 14] = values[14];
				// fallthrough
			case 14:
				dest[e.value + 13] = values[13];
				// fallthrough
			case 13:
				dest[e.value + 12] = values[12];
				// fallthrough
			case 12:
				dest[e.value + 11] = values[11];
				// fallthrough
			case 11:
				dest[e.value + 10] = values[10];
				// fallthrough
			case 10:
				dest[e.value + 9] = values[9];
				// fallthrough
			case 9:
				dest[e.value + 8] = values[8];
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
		memcpy(dest + e.value / uint32_t(8), &values.v , sizeof(uint16_t));
	}
	template<typename T>
	RELEASE_INLINE void store(unaligned_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			uint16_t old_value;
			std::memcpy(&old_value, dest + e.value / uint32_t(8), sizeof(uint16_t));
			auto mask = 0x0FFFF << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			auto old_masked_out = (old_value & ~mask);
			auto combined = uint16_t(old_masked_out | adju_value);
			memcpy(dest + e.value / uint32_t(8), &combined, sizeof(uint16_t));
		}
		{
			if((e.value & 0x07) != 0) {
				auto old_value = dest[2 + (e.value / uint32_t(8))].v;
				auto mask = 0x0FF >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (16 - (e.value & 0x07));
				dest[2 + e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | (adju_value & mask));
			}
		}
	}
	template<typename T>
	RELEASE_INLINE void store(partial_contiguous_tags<T> e, dcon::bitfield_type* dest, vbitfield_type values) {
		{
			uint16_t old_value;
			memcpy(&old_value, dest + e.value / uint32_t(8), sizeof(uint16_t));
			auto mask = (0x0FFFF >> (16 - e.subcount)) << (e.value & 0x07);
			auto adju_value = values.v << (e.value & 0x07);
			auto combined = uint16_t((old_value & ~mask) | (adju_value & mask));
			memcpy(dest + e.value / uint32_t(8), &combined, sizeof(uint16_t));
		}
		{
			if((e.value & 0x07) != 0) {
				auto old_value = dest[2 + e.value / uint32_t(8)].v;
				auto mask = (0x0FF >> (16 - e.subcount)) >> (8 - (e.value & 0x07));
				auto adju_value = values.v >> (16 - (e.value & 0x07));
				dest[2 + e.value / uint32_t(8)].v = uint8_t((old_value & ~mask) | (adju_value & mask));
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
