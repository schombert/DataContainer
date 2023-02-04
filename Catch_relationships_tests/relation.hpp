#pragma once

//
// This file was automatically generated from: relation.txt
// EDIT AT YOUR OWN RISK; all changes will be lost upon regeneration
// NOT SUITABLE FOR USE IN CRITICAL SOFTWARE WHERE LIVES OR LIVELIHOODS DEPEND ON THE CORRECT OPERATION
//

#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>
#include <memory>
#include <assert.h>
#include <cstring>
#include "common_types.hpp"
#ifndef DCON_NO_VE
#include "ve.hpp"
#endif
#include "unordered_dense.h"

#ifdef NDEBUG
#ifdef _MSC_VER
#define DCON_RELEASE_INLINE __forceinline
#else
#define DCON_RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define DCON_RELEASE_INLINE inline
#endif
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4324 )
#endif

namespace dcon {
	struct load_record {
		bool thingyA : 1;
		bool thingyA_some_value : 1;
		bool thingyB : 1;
		bool thingyB__index : 1;
		bool thingyB_some_value : 1;
		bool relate_same : 1;
		bool relate_same_left : 1;
		bool relate_same_right : 1;
		bool relate_in_array : 1;
		bool relate_in_array_left : 1;
		bool relate_in_array_right : 1;
		bool relate_in_list : 1;
		bool relate_in_list_left : 1;
		bool relate_in_list_right : 1;
		bool many_many : 1;
		bool many_many__index : 1;
		bool many_many_A : 1;
		bool many_many_B : 1;
		bool many_many_C : 1;
		bool many_many_D : 1;
		bool many_many_E : 1;
		bool many_many_F : 1;
		bool many_many_ignore : 1;
		bool relate_as_optional : 1;
		bool relate_as_optional__index : 1;
		bool relate_as_optional_left : 1;
		bool relate_as_optional_right : 1;
		bool relate_as_non_optional : 1;
		bool relate_as_non_optional__index : 1;
		bool relate_as_non_optional_left : 1;
		bool relate_as_non_optional_right : 1;
		bool relate_as_multipleA : 1;
		bool relate_as_multipleA__index : 1;
		bool relate_as_multipleA_left : 1;
		bool relate_as_multipleB : 1;
		bool relate_as_multipleB__index : 1;
		bool relate_as_multipleB_left : 1;
		bool relate_as_multipleC : 1;
		bool relate_as_multipleC__index : 1;
		bool relate_as_multipleC_left : 1;
		bool relate_as_multipleD : 1;
		bool relate_as_multipleD__index : 1;
		bool relate_as_multipleD_left : 1;
		load_record() {
			thingyA = false;
			thingyA_some_value = false;
			thingyB = false;
			thingyB__index = false;
			thingyB_some_value = false;
			relate_same = false;
			relate_same_left = false;
			relate_same_right = false;
			relate_in_array = false;
			relate_in_array_left = false;
			relate_in_array_right = false;
			relate_in_list = false;
			relate_in_list_left = false;
			relate_in_list_right = false;
			many_many = false;
			many_many__index = false;
			many_many_A = false;
			many_many_B = false;
			many_many_C = false;
			many_many_D = false;
			many_many_E = false;
			many_many_F = false;
			many_many_ignore = false;
			relate_as_optional = false;
			relate_as_optional__index = false;
			relate_as_optional_left = false;
			relate_as_optional_right = false;
			relate_as_non_optional = false;
			relate_as_non_optional__index = false;
			relate_as_non_optional_left = false;
			relate_as_non_optional_right = false;
			relate_as_multipleA = false;
			relate_as_multipleA__index = false;
			relate_as_multipleA_left = false;
			relate_as_multipleB = false;
			relate_as_multipleB__index = false;
			relate_as_multipleB_left = false;
			relate_as_multipleC = false;
			relate_as_multipleC__index = false;
			relate_as_multipleC_left = false;
			relate_as_multipleD = false;
			relate_as_multipleD__index = false;
			relate_as_multipleD_left = false;
		}
	};
	//
	// definition of strongly typed index for thingyA_id
	//
	class thingyA_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr thingyA_id() noexcept = default;
		explicit constexpr thingyA_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr thingyA_id(thingyA_id const& v) noexcept = default;
		constexpr thingyA_id(thingyA_id&& v) noexcept = default;
		
		thingyA_id& operator=(thingyA_id const& v) noexcept = default;
		thingyA_id& operator=(thingyA_id&& v) noexcept = default;
		constexpr bool operator==(thingyA_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingyA_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class thingyA_id_pair {
		public:
		thingyA_id left;
		thingyA_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(thingyA_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for thingyB_id
	//
	class thingyB_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr thingyB_id() noexcept = default;
		explicit constexpr thingyB_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr thingyB_id(thingyB_id const& v) noexcept = default;
		constexpr thingyB_id(thingyB_id&& v) noexcept = default;
		
		thingyB_id& operator=(thingyB_id const& v) noexcept = default;
		thingyB_id& operator=(thingyB_id&& v) noexcept = default;
		constexpr bool operator==(thingyB_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingyB_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class thingyB_id_pair {
		public:
		thingyB_id left;
		thingyB_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(thingyB_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_same_id
	//
	class relate_same_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_same_id() noexcept = default;
		explicit constexpr relate_same_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_same_id(relate_same_id const& v) noexcept = default;
		constexpr relate_same_id(relate_same_id&& v) noexcept = default;
		
		relate_same_id& operator=(relate_same_id const& v) noexcept = default;
		relate_same_id& operator=(relate_same_id&& v) noexcept = default;
		constexpr bool operator==(relate_same_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_same_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_same_id_pair {
		public:
		relate_same_id left;
		relate_same_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_same_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_in_array_id
	//
	class relate_in_array_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_in_array_id() noexcept = default;
		explicit constexpr relate_in_array_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_in_array_id(relate_in_array_id const& v) noexcept = default;
		constexpr relate_in_array_id(relate_in_array_id&& v) noexcept = default;
		
		relate_in_array_id& operator=(relate_in_array_id const& v) noexcept = default;
		relate_in_array_id& operator=(relate_in_array_id&& v) noexcept = default;
		constexpr bool operator==(relate_in_array_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_in_array_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_in_array_id_pair {
		public:
		relate_in_array_id left;
		relate_in_array_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_in_array_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_in_list_id
	//
	class relate_in_list_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_in_list_id() noexcept = default;
		explicit constexpr relate_in_list_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_in_list_id(relate_in_list_id const& v) noexcept = default;
		constexpr relate_in_list_id(relate_in_list_id&& v) noexcept = default;
		
		relate_in_list_id& operator=(relate_in_list_id const& v) noexcept = default;
		relate_in_list_id& operator=(relate_in_list_id&& v) noexcept = default;
		constexpr bool operator==(relate_in_list_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_in_list_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_in_list_id_pair {
		public:
		relate_in_list_id left;
		relate_in_list_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_in_list_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for many_many_id
	//
	class many_many_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr many_many_id() noexcept = default;
		explicit constexpr many_many_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr many_many_id(many_many_id const& v) noexcept = default;
		constexpr many_many_id(many_many_id&& v) noexcept = default;
		
		many_many_id& operator=(many_many_id const& v) noexcept = default;
		many_many_id& operator=(many_many_id&& v) noexcept = default;
		constexpr bool operator==(many_many_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(many_many_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class many_many_id_pair {
		public:
		many_many_id left;
		many_many_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(many_many_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_optional_id
	//
	class relate_as_optional_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_optional_id() noexcept = default;
		explicit constexpr relate_as_optional_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_optional_id(relate_as_optional_id const& v) noexcept = default;
		constexpr relate_as_optional_id(relate_as_optional_id&& v) noexcept = default;
		
		relate_as_optional_id& operator=(relate_as_optional_id const& v) noexcept = default;
		relate_as_optional_id& operator=(relate_as_optional_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_optional_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_optional_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_optional_id_pair {
		public:
		relate_as_optional_id left;
		relate_as_optional_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_optional_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_non_optional_id
	//
	class relate_as_non_optional_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_non_optional_id() noexcept = default;
		explicit constexpr relate_as_non_optional_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_non_optional_id(relate_as_non_optional_id const& v) noexcept = default;
		constexpr relate_as_non_optional_id(relate_as_non_optional_id&& v) noexcept = default;
		
		relate_as_non_optional_id& operator=(relate_as_non_optional_id const& v) noexcept = default;
		relate_as_non_optional_id& operator=(relate_as_non_optional_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_non_optional_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_non_optional_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_non_optional_id_pair {
		public:
		relate_as_non_optional_id left;
		relate_as_non_optional_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_non_optional_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_multipleA_id
	//
	class relate_as_multipleA_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_multipleA_id() noexcept = default;
		explicit constexpr relate_as_multipleA_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_multipleA_id(relate_as_multipleA_id const& v) noexcept = default;
		constexpr relate_as_multipleA_id(relate_as_multipleA_id&& v) noexcept = default;
		
		relate_as_multipleA_id& operator=(relate_as_multipleA_id const& v) noexcept = default;
		relate_as_multipleA_id& operator=(relate_as_multipleA_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_multipleA_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_multipleA_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_multipleA_id_pair {
		public:
		relate_as_multipleA_id left;
		relate_as_multipleA_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_multipleA_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_multipleB_id
	//
	class relate_as_multipleB_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_multipleB_id() noexcept = default;
		explicit constexpr relate_as_multipleB_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_multipleB_id(relate_as_multipleB_id const& v) noexcept = default;
		constexpr relate_as_multipleB_id(relate_as_multipleB_id&& v) noexcept = default;
		
		relate_as_multipleB_id& operator=(relate_as_multipleB_id const& v) noexcept = default;
		relate_as_multipleB_id& operator=(relate_as_multipleB_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_multipleB_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_multipleB_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_multipleB_id_pair {
		public:
		relate_as_multipleB_id left;
		relate_as_multipleB_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_multipleB_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_multipleC_id
	//
	class relate_as_multipleC_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_multipleC_id() noexcept = default;
		explicit constexpr relate_as_multipleC_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_multipleC_id(relate_as_multipleC_id const& v) noexcept = default;
		constexpr relate_as_multipleC_id(relate_as_multipleC_id&& v) noexcept = default;
		
		relate_as_multipleC_id& operator=(relate_as_multipleC_id const& v) noexcept = default;
		relate_as_multipleC_id& operator=(relate_as_multipleC_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_multipleC_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_multipleC_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_multipleC_id_pair {
		public:
		relate_as_multipleC_id left;
		relate_as_multipleC_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_multipleC_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for relate_as_multipleD_id
	//
	class relate_as_multipleD_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr relate_as_multipleD_id() noexcept = default;
		explicit constexpr relate_as_multipleD_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr relate_as_multipleD_id(relate_as_multipleD_id const& v) noexcept = default;
		constexpr relate_as_multipleD_id(relate_as_multipleD_id&& v) noexcept = default;
		
		relate_as_multipleD_id& operator=(relate_as_multipleD_id const& v) noexcept = default;
		relate_as_multipleD_id& operator=(relate_as_multipleD_id&& v) noexcept = default;
		constexpr bool operator==(relate_as_multipleD_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(relate_as_multipleD_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class relate_as_multipleD_id_pair {
		public:
		relate_as_multipleD_id left;
		relate_as_multipleD_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(relate_as_multipleD_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::thingyA_id> {
		using type = tagged_vector<dcon::thingyA_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::thingyB_id> {
		using type = tagged_vector<dcon::thingyB_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_same_id> {
		using type = tagged_vector<dcon::relate_same_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_in_array_id> {
		using type = tagged_vector<dcon::relate_in_array_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_in_list_id> {
		using type = tagged_vector<dcon::relate_in_list_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::many_many_id> {
		using type = tagged_vector<dcon::many_many_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_optional_id> {
		using type = tagged_vector<dcon::relate_as_optional_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_non_optional_id> {
		using type = tagged_vector<dcon::relate_as_non_optional_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleA_id> {
		using type = tagged_vector<dcon::relate_as_multipleA_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleB_id> {
		using type = tagged_vector<dcon::relate_as_multipleB_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleC_id> {
		using type = tagged_vector<dcon::relate_as_multipleC_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleD_id> {
		using type = tagged_vector<dcon::relate_as_multipleD_id>;
	};
	
}

#endif
namespace dcon {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class const_object_iterator_thingyA;
		class object_iterator_thingyA;

		class alignas(64) thingyA_class {
			friend const_object_iterator_thingyA;
			friend object_iterator_thingyA;
			private:
			//
			// storage space for some_value of type int32_t
			//
			struct alignas(64) dtype_some_value {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_some_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_some_value;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class const_object_iterator_thingyB;
		class object_iterator_thingyB;

		class alignas(64) thingyB_class {
			friend const_object_iterator_thingyB;
			friend object_iterator_thingyB;
			private:
			//
			// storage space for _index of type thingyB_id
			//
			struct dtype__index {
				thingyB_id values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 1200); }
			}
			m__index;
			
			//
			// storage space for some_value of type int32_t
			//
			struct alignas(64) dtype_some_value {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_some_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_some_value;
			
			thingyB_id first_free = thingyB_id();
			uint32_t size_used = 0;


			public:
			thingyB_class() {
				for(int32_t i = 1200 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = thingyB_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_same;
		class object_iterator_relate_same;

		class alignas(64) relate_same_class {
			friend const_object_iterator_relate_same;
			friend object_iterator_relate_same;
			private:
			//
			// storage space for right of type thingyA_id
			//
			struct alignas(64) dtype_right {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_right;
			
			uint32_t size_used = 0;

			ankerl::unordered_dense::map<uint32_t, relate_same_id, ankerl::unordered_dense::hash<uint32_t>> hashm_joint;
			uint32_t to_joint_keydata(thingyA_id left_p, thingyA_id right_p) {
				uint32_t result = 0;
				result |= (uint32_t(left_p.value) << 0);
				result |= (uint32_t(right_p.value) << 11);
				return result;
			}
			

			public:
			friend data_container;
		};

		class const_object_iterator_relate_in_array;
		class object_iterator_relate_in_array;
		class const_iterator_thingyB_foreach_relate_in_array_as_right;
		class iterator_thingyB_foreach_relate_in_array_as_right;
		struct const_iterator_thingyB_foreach_relate_in_array_as_right_generator;
		struct iterator_thingyB_foreach_relate_in_array_as_right_generator;

		class alignas(64) relate_in_array_class {
			friend const_object_iterator_relate_in_array;
			friend object_iterator_relate_in_array;
			friend const_iterator_thingyB_foreach_relate_in_array_as_right;
			friend iterator_thingyB_foreach_relate_in_array_as_right;
			private:
			//
			// storage space for right of type thingyB_id
			//
			struct alignas(64) dtype_right {
				uint8_t padding[(63 + sizeof(thingyB_id)) & ~uint64_t(63)];
				thingyB_id values[(sizeof(thingyB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_right;
			
			//
			// storage space for array_right of type dcon::stable_mk_2_tag
			//
			struct dtype_array_right {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_right() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_right;
			
			dcon::stable_variable_vector_storage_mk_2<relate_in_array_id, 8, 2400 > right_storage;
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class const_object_iterator_relate_in_list;
		class object_iterator_relate_in_list;
		class const_iterator_thingyB_foreach_relate_in_list_as_right;
		class iterator_thingyB_foreach_relate_in_list_as_right;
		struct const_iterator_thingyB_foreach_relate_in_list_as_right_generator;
		struct iterator_thingyB_foreach_relate_in_list_as_right_generator;

		class alignas(64) relate_in_list_class {
			friend const_object_iterator_relate_in_list;
			friend object_iterator_relate_in_list;
			friend const_iterator_thingyB_foreach_relate_in_list_as_right;
			friend iterator_thingyB_foreach_relate_in_list_as_right;
			private:
			//
			// storage space for right of type thingyB_id
			//
			struct alignas(64) dtype_right {
				uint8_t padding[(63 + sizeof(thingyB_id)) & ~uint64_t(63)];
				thingyB_id values[(sizeof(thingyB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_right;
			
			//
			// storage space for link_right of type relate_in_list_id_pair
			//
			struct dtype_link_right {
				relate_in_list_id_pair values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_right() { std::uninitialized_value_construct_n(values, 1200); }
			}
			m_link_right;
			
			//
			// storage space for head_back_right of type relate_in_list_id
			//
			struct alignas(64) dtype_head_back_right {
				uint8_t padding[(63 + sizeof(relate_in_list_id)) & ~uint64_t(63)];
				relate_in_list_id values[(sizeof(relate_in_list_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(relate_in_list_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(relate_in_list_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_head_back_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(relate_in_list_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(relate_in_list_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(relate_in_list_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_head_back_right;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class const_object_iterator_many_many;
		class object_iterator_many_many;

		class alignas(64) many_many_class {
			friend const_object_iterator_many_many;
			friend object_iterator_many_many;
			private:
			//
			// storage space for _index of type many_many_id
			//
			struct dtype__index {
				many_many_id values[200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 200); }
			}
			m__index;
			
			//
			// storage space for A of type thingyA_id
			//
			struct alignas(64) dtype_A {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_A() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_A;
			
			//
			// storage space for B of type thingyA_id
			//
			struct alignas(64) dtype_B {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_B() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_B;
			
			//
			// storage space for C of type thingyA_id
			//
			struct alignas(64) dtype_C {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_C() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_C;
			
			//
			// storage space for D of type thingyA_id
			//
			struct alignas(64) dtype_D {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_D() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_D;
			
			//
			// storage space for E of type thingyA_id
			//
			struct alignas(64) dtype_E {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_E() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_E;
			
			//
			// storage space for F of type thingyA_id
			//
			struct alignas(64) dtype_F {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_F() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_F;
			
			//
			// storage space for ignore of type thingyA_id
			//
			struct alignas(64) dtype_ignore {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_ignore() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(200) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(200))); }
			}
			m_ignore;
			
			many_many_id first_free = many_many_id();
			uint32_t size_used = 0;

			ankerl::unordered_dense::map<uint64_t, many_many_id, ankerl::unordered_dense::hash<uint64_t>> hashm_joint;
			uint64_t to_joint_keydata(thingyA_id A_p, thingyA_id B_p, thingyA_id C_p, thingyA_id D_p, thingyA_id E_p, thingyA_id F_p) {
				uint64_t result = 0;
				result |= (uint64_t(A_p.value) << 0);
				result |= (uint64_t(B_p.value) << 8);
				result |= (uint64_t(C_p.value) << 16);
				result |= (uint64_t(D_p.value) << 24);
				result |= (uint64_t(E_p.value) << 32);
				result |= (uint64_t(F_p.value) << 40);
				return result;
			}
			

			public:
			many_many_class() {
				for(int32_t i = 200 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = many_many_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_optional;
		class object_iterator_relate_as_optional;
		class const_iterator_thingyA_foreach_relate_as_optional_as_left;
		class iterator_thingyA_foreach_relate_as_optional_as_left;
		struct const_iterator_thingyA_foreach_relate_as_optional_as_left_generator;
		struct iterator_thingyA_foreach_relate_as_optional_as_left_generator;
		class const_iterator_thingyB_foreach_relate_as_optional_as_right;
		class iterator_thingyB_foreach_relate_as_optional_as_right;
		struct const_iterator_thingyB_foreach_relate_as_optional_as_right_generator;
		struct iterator_thingyB_foreach_relate_as_optional_as_right_generator;

		class alignas(64) relate_as_optional_class {
			friend const_object_iterator_relate_as_optional;
			friend object_iterator_relate_as_optional;
			friend const_iterator_thingyA_foreach_relate_as_optional_as_left;
			friend iterator_thingyA_foreach_relate_as_optional_as_left;
			friend const_iterator_thingyB_foreach_relate_as_optional_as_right;
			friend iterator_thingyB_foreach_relate_as_optional_as_right;
			private:
			//
			// storage space for _index of type relate_as_optional_id
			//
			struct dtype__index {
				relate_as_optional_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct alignas(64) dtype_left {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(400))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(400))); }
			}
			m_left;
			
			//
			// storage space for array_left of type dcon::stable_mk_2_tag
			//
			struct dtype_array_left {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_left() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_left;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_optional_id, 8, 800 > left_storage;
			//
			// storage space for right of type thingyB_id
			//
			struct alignas(64) dtype_right {
				uint8_t padding[(63 + sizeof(thingyB_id)) & ~uint64_t(63)];
				thingyB_id values[(sizeof(thingyB_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(400))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyB_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(400))); }
			}
			m_right;
			
			//
			// storage space for array_right of type dcon::stable_mk_2_tag
			//
			struct dtype_array_right {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_right() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_right;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_optional_id, 8, 800 > right_storage;
			relate_as_optional_id first_free = relate_as_optional_id();
			uint32_t size_used = 0;


			public:
			relate_as_optional_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_optional_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_non_optional;
		class object_iterator_relate_as_non_optional;
		class const_iterator_thingyA_foreach_relate_as_non_optional_as_left;
		class iterator_thingyA_foreach_relate_as_non_optional_as_left;
		struct const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator;
		struct iterator_thingyA_foreach_relate_as_non_optional_as_left_generator;
		class const_iterator_thingyB_foreach_relate_as_non_optional_as_right;
		class iterator_thingyB_foreach_relate_as_non_optional_as_right;
		struct const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator;
		struct iterator_thingyB_foreach_relate_as_non_optional_as_right_generator;

		class alignas(64) relate_as_non_optional_class {
			friend const_object_iterator_relate_as_non_optional;
			friend object_iterator_relate_as_non_optional;
			friend const_iterator_thingyA_foreach_relate_as_non_optional_as_left;
			friend iterator_thingyA_foreach_relate_as_non_optional_as_left;
			friend const_iterator_thingyB_foreach_relate_as_non_optional_as_right;
			friend iterator_thingyB_foreach_relate_as_non_optional_as_right;
			private:
			//
			// storage space for _index of type relate_as_non_optional_id
			//
			struct dtype__index {
				relate_as_non_optional_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct alignas(64) dtype_left {
				uint8_t padding[(63 + sizeof(thingyA_id)) & ~uint64_t(63)];
				thingyA_id values[(sizeof(thingyA_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(400))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyA_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyA_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyA_id)) - uint32_t(1)) : uint32_t(400))); }
			}
			m_left;
			
			//
			// storage space for array_left of type dcon::stable_mk_2_tag
			//
			struct dtype_array_left {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_left() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_left;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_non_optional_id, 8, 800 > left_storage;
			//
			// storage space for right of type thingyB_id
			//
			struct alignas(64) dtype_right {
				uint8_t padding[(63 + sizeof(thingyB_id)) & ~uint64_t(63)];
				thingyB_id values[(sizeof(thingyB_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(400))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_right() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingyB_id) <= 64 ? (uint32_t(400) + (uint32_t(64) / uint32_t(sizeof(thingyB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingyB_id)) - uint32_t(1)) : uint32_t(400))); }
			}
			m_right;
			
			//
			// storage space for array_right of type dcon::stable_mk_2_tag
			//
			struct dtype_array_right {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_right() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_right;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_non_optional_id, 8, 800 > right_storage;
			relate_as_non_optional_id first_free = relate_as_non_optional_id();
			uint32_t size_used = 0;


			public:
			relate_as_non_optional_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_non_optional_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_multipleA;
		class object_iterator_relate_as_multipleA;
		class const_iterator_thingyA_foreach_relate_as_multipleA_as_left;
		class iterator_thingyA_foreach_relate_as_multipleA_as_left;
		struct const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator;
		struct iterator_thingyA_foreach_relate_as_multipleA_as_left_generator;

		class alignas(64) relate_as_multipleA_class {
			friend const_object_iterator_relate_as_multipleA;
			friend object_iterator_relate_as_multipleA;
			friend const_iterator_thingyA_foreach_relate_as_multipleA_as_left;
			friend iterator_thingyA_foreach_relate_as_multipleA_as_left;
			private:
			//
			// storage space for _index of type relate_as_multipleA_id
			//
			struct dtype__index {
				relate_as_multipleA_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct dtype_left {
				std::array<thingyA_id, 2> values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values, 400); }
			}
			m_left;
			
			//
			// storage space for array_left of type dcon::stable_mk_2_tag
			//
			struct dtype_array_left {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_left() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_left;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_multipleA_id, 8, 800 > left_storage;
			relate_as_multipleA_id first_free = relate_as_multipleA_id();
			uint32_t size_used = 0;

			ankerl::unordered_dense::map<uint32_t, relate_as_multipleA_id, ankerl::unordered_dense::hash<uint32_t>> hashm_joint;
			uint32_t to_joint_keydata(std::array<thingyA_id, 2> const& left_p) {
				uint32_t result = 0;
				result |= (uint32_t(left_p[0].value) << 0);
				result |= (uint32_t(left_p[1].value) << 9);
				return result;
			}
			

			public:
			relate_as_multipleA_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_multipleA_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_multipleB;
		class object_iterator_relate_as_multipleB;

		class alignas(64) relate_as_multipleB_class {
			friend const_object_iterator_relate_as_multipleB;
			friend object_iterator_relate_as_multipleB;
			private:
			//
			// storage space for _index of type relate_as_multipleB_id
			//
			struct dtype__index {
				relate_as_multipleB_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct dtype_left {
				std::array<thingyA_id, 2> values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values, 400); }
			}
			m_left;
			
			//
			// storage space for link_back_left of type relate_as_multipleB_id
			//
			struct alignas(64) dtype_link_back_left {
				uint8_t padding[(63 + sizeof(relate_as_multipleB_id)) & ~uint64_t(63)];
				relate_as_multipleB_id values[(sizeof(relate_as_multipleB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(relate_as_multipleB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(relate_as_multipleB_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_back_left() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(relate_as_multipleB_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(relate_as_multipleB_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(relate_as_multipleB_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_link_back_left;
			
			relate_as_multipleB_id first_free = relate_as_multipleB_id();
			uint32_t size_used = 0;


			public:
			relate_as_multipleB_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_multipleB_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_multipleC;
		class object_iterator_relate_as_multipleC;
		class const_iterator_thingyA_foreach_relate_as_multipleC_as_left;
		class iterator_thingyA_foreach_relate_as_multipleC_as_left;
		struct const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator;
		struct iterator_thingyA_foreach_relate_as_multipleC_as_left_generator;

		class alignas(64) relate_as_multipleC_class {
			friend const_object_iterator_relate_as_multipleC;
			friend object_iterator_relate_as_multipleC;
			friend const_iterator_thingyA_foreach_relate_as_multipleC_as_left;
			friend iterator_thingyA_foreach_relate_as_multipleC_as_left;
			private:
			//
			// storage space for _index of type relate_as_multipleC_id
			//
			struct dtype__index {
				relate_as_multipleC_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct dtype_left {
				std::array<thingyA_id, 2> values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values, 400); }
			}
			m_left;
			
			//
			// storage space for array_left of type dcon::stable_mk_2_tag
			//
			struct dtype_array_left {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_left() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_left;
			
			dcon::stable_variable_vector_storage_mk_2<relate_as_multipleC_id, 8, 800 > left_storage;
			relate_as_multipleC_id first_free = relate_as_multipleC_id();
			uint32_t size_used = 0;


			public:
			relate_as_multipleC_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_multipleC_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_relate_as_multipleD;
		class object_iterator_relate_as_multipleD;

		class alignas(64) relate_as_multipleD_class {
			friend const_object_iterator_relate_as_multipleD;
			friend object_iterator_relate_as_multipleD;
			private:
			//
			// storage space for _index of type relate_as_multipleD_id
			//
			struct dtype__index {
				relate_as_multipleD_id values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 400); }
			}
			m__index;
			
			//
			// storage space for left of type thingyA_id
			//
			struct dtype_left {
				std::array<thingyA_id, 2> values[400];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values, 400); }
			}
			m_left;
			
			relate_as_multipleD_id first_free = relate_as_multipleD_id();
			uint32_t size_used = 0;


			public:
			relate_as_multipleD_class() {
				for(int32_t i = 400 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = relate_as_multipleD_id(uint16_t(i));
				}
			}
			friend data_container;
		};

	}

	class thingyA_const_fat_id;
	class thingyA_fat_id;
	class thingyB_const_fat_id;
	class thingyB_fat_id;
	class relate_same_const_fat_id;
	class relate_same_fat_id;
	class relate_in_array_const_fat_id;
	class relate_in_array_fat_id;
	class relate_in_list_const_fat_id;
	class relate_in_list_fat_id;
	class many_many_const_fat_id;
	class many_many_fat_id;
	class relate_as_optional_const_fat_id;
	class relate_as_optional_fat_id;
	class relate_as_non_optional_const_fat_id;
	class relate_as_non_optional_fat_id;
	class relate_as_multipleA_const_fat_id;
	class relate_as_multipleA_fat_id;
	class relate_as_multipleB_const_fat_id;
	class relate_as_multipleB_fat_id;
	class relate_as_multipleC_const_fat_id;
	class relate_as_multipleC_fat_id;
	class relate_as_multipleD_const_fat_id;
	class relate_as_multipleD_fat_id;
	class thingyA_fat_id {
		friend data_container;
		public:
		data_container& container;
		thingyA_id id;
		thingyA_fat_id(data_container& c, thingyA_id i) noexcept : container(c), id(i) {}
		thingyA_fat_id(thingyA_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingyA_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingyA_fat_id& operator=(thingyA_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyA_fat_id& operator=(thingyA_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingyA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyA_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyA_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_some_value() const noexcept;
		DCON_RELEASE_INLINE void set_some_value(int32_t v) const noexcept;
		DCON_RELEASE_INLINE relate_same_fat_id get_relate_same_as_left() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_same_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_array_fat_id get_relate_in_array_as_left() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_in_array_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_array_fat_id get_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right_from_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE void set_right_from_relate_in_array(thingyB_id v) const noexcept;
		DCON_RELEASE_INLINE relate_in_list_fat_id get_relate_in_list_as_left() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_in_list_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_list_fat_id get_relate_in_list() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_in_list() const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right_from_relate_in_list() const noexcept;
		DCON_RELEASE_INLINE void set_right_from_relate_in_list(thingyB_id v) const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional_as_left() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_optional_as_left() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator get_relate_as_optional_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_optional() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator get_relate_as_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_relate_as_optional(thingyB_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional_as_left() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_non_optional_as_left() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator get_relate_as_non_optional_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_non_optional() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator get_relate_as_non_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_relate_as_non_optional(thingyB_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleA_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> range_of_relate_as_multipleA_as_left() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_multipleA_as_left() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator get_relate_as_multipleA_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleA(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> range_of_relate_as_multipleA() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_multipleA() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator get_relate_as_multipleA() const;
		DCON_RELEASE_INLINE relate_as_multipleB_fat_id get_relate_as_multipleB_as_left() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_as_multipleB_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_as_multipleB_fat_id get_relate_as_multipleB() const noexcept;
		DCON_RELEASE_INLINE void remove_relate_as_multipleB() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleC_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> range_of_relate_as_multipleC_as_left() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_multipleC_as_left() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator get_relate_as_multipleC_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleC(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> range_of_relate_as_multipleC() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_multipleC() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator get_relate_as_multipleC() const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE thingyA_fat_id fatten(data_container& c, thingyA_id id) noexcept {
		return thingyA_fat_id(c, id);
	}
	
	class thingyA_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		thingyA_id id;
		thingyA_const_fat_id(data_container const& c, thingyA_id i) noexcept : container(c), id(i) {}
		thingyA_const_fat_id(thingyA_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		thingyA_const_fat_id(thingyA_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingyA_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingyA_const_fat_id& operator=(thingyA_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyA_const_fat_id& operator=(thingyA_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyA_const_fat_id& operator=(thingyA_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingyA_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyA_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyA_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyA_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_some_value() const noexcept;
		DCON_RELEASE_INLINE relate_same_const_fat_id get_relate_same_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_array_const_fat_id get_relate_in_array_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_array_const_fat_id get_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right_from_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE relate_in_list_const_fat_id get_relate_in_list_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_in_list_const_fat_id get_relate_in_list() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right_from_relate_in_list() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional_as_left() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator get_relate_as_optional_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator get_relate_as_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_relate_as_optional(thingyB_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional_as_left() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator get_relate_as_non_optional_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator get_relate_as_non_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_relate_as_non_optional(thingyB_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleA_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> range_of_relate_as_multipleA_as_left() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator get_relate_as_multipleA_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleA(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> range_of_relate_as_multipleA() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator get_relate_as_multipleA() const;
		DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id get_relate_as_multipleB_as_left() const noexcept;
		DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id get_relate_as_multipleB() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleC_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> range_of_relate_as_multipleC_as_left() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator get_relate_as_multipleC_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleC(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> range_of_relate_as_multipleC() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator get_relate_as_multipleC() const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(thingyA_fat_id const& l, thingyA_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(thingyA_fat_id const& l, thingyA_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id fatten(data_container const& c, thingyA_id id) noexcept {
		return thingyA_const_fat_id(c, id);
	}
	
	class thingyB_fat_id {
		friend data_container;
		public:
		data_container& container;
		thingyB_id id;
		thingyB_fat_id(data_container& c, thingyB_id i) noexcept : container(c), id(i) {}
		thingyB_fat_id(thingyB_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingyB_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingyB_fat_id& operator=(thingyB_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyB_fat_id& operator=(thingyB_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingyB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyB_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyB_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_some_value() const noexcept;
		DCON_RELEASE_INLINE void set_some_value(int32_t v) const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_array_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> range_of_relate_in_array_as_right() const;
		DCON_RELEASE_INLINE void remove_all_relate_in_array_as_right() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator get_relate_in_array_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_array(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> range_of_relate_in_array() const;
		DCON_RELEASE_INLINE void remove_all_relate_in_array() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator get_relate_in_array() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_in_array(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_in_array(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_list_as_right(T&& func) const;
		DCON_RELEASE_INLINE void remove_all_relate_in_list_as_right() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator get_relate_in_list_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_list(T&& func) const;
		DCON_RELEASE_INLINE void remove_all_relate_in_list() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator get_relate_in_list() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_in_list(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_in_list(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional_as_right() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_optional_as_right() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator get_relate_as_optional_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_optional() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator get_relate_as_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_as_optional(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional_as_right() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_non_optional_as_right() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator get_relate_as_non_optional_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional() const;
		DCON_RELEASE_INLINE void remove_all_relate_as_non_optional() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator get_relate_as_non_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_as_non_optional(thingyA_id target) const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE thingyB_fat_id fatten(data_container& c, thingyB_id id) noexcept {
		return thingyB_fat_id(c, id);
	}
	
	class thingyB_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		thingyB_id id;
		thingyB_const_fat_id(data_container const& c, thingyB_id i) noexcept : container(c), id(i) {}
		thingyB_const_fat_id(thingyB_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		thingyB_const_fat_id(thingyB_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingyB_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingyB_const_fat_id& operator=(thingyB_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyB_const_fat_id& operator=(thingyB_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingyB_const_fat_id& operator=(thingyB_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingyB_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingyB_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyB_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingyB_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_some_value() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_array_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> range_of_relate_in_array_as_right() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator get_relate_in_array_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_array(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> range_of_relate_in_array() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator get_relate_in_array() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_in_array(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_in_array(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_list_as_right(T&& func) const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator get_relate_in_list_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_list(T&& func) const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator get_relate_in_list() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_in_list(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_in_list(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional_as_right() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator get_relate_as_optional_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> range_of_relate_as_optional() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator get_relate_as_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_as_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_as_optional(thingyA_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional_as_right(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional_as_right() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator get_relate_as_non_optional_as_right() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> range_of_relate_as_non_optional() const;
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator get_relate_as_non_optional() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_left_from_relate_as_non_optional(T&& func) const;
		DCON_RELEASE_INLINE bool has_left_from_relate_as_non_optional(thingyA_id target) const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(thingyB_fat_id const& l, thingyB_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(thingyB_fat_id const& l, thingyB_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id fatten(data_container const& c, thingyB_id id) noexcept {
		return thingyB_const_fat_id(c, id);
	}
	
	class relate_same_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_same_id id;
		relate_same_fat_id(data_container& c, relate_same_id i) noexcept : container(c), id(i) {}
		relate_same_fat_id(relate_same_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_same_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_same_fat_id& operator=(relate_same_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_same_fat_id& operator=(relate_same_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_same_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_same_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_same_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_same_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_same_fat_id fatten(data_container& c, relate_same_id id) noexcept {
		return relate_same_fat_id(c, id);
	}
	
	class relate_same_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_same_id id;
		relate_same_const_fat_id(data_container const& c, relate_same_id i) noexcept : container(c), id(i) {}
		relate_same_const_fat_id(relate_same_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_same_const_fat_id(relate_same_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_same_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_same_const_fat_id& operator=(relate_same_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_same_const_fat_id& operator=(relate_same_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_same_const_fat_id& operator=(relate_same_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_same_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_same_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_same_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_same_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_same_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_same_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_same_fat_id const& l, relate_same_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_same_fat_id const& l, relate_same_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_same_const_fat_id fatten(data_container const& c, relate_same_id id) noexcept {
		return relate_same_const_fat_id(c, id);
	}
	
	class relate_in_array_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_in_array_id id;
		relate_in_array_fat_id(data_container& c, relate_in_array_id i) noexcept : container(c), id(i) {}
		relate_in_array_fat_id(relate_in_array_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_in_array_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_in_array_fat_id& operator=(relate_in_array_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_array_fat_id& operator=(relate_in_array_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_array_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_array_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_array_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_array_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_in_array_fat_id fatten(data_container& c, relate_in_array_id id) noexcept {
		return relate_in_array_fat_id(c, id);
	}
	
	class relate_in_array_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_in_array_id id;
		relate_in_array_const_fat_id(data_container const& c, relate_in_array_id i) noexcept : container(c), id(i) {}
		relate_in_array_const_fat_id(relate_in_array_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_in_array_const_fat_id(relate_in_array_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_in_array_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_in_array_const_fat_id& operator=(relate_in_array_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_array_const_fat_id& operator=(relate_in_array_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_array_const_fat_id& operator=(relate_in_array_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_array_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_array_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_array_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_array_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_array_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_array_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_in_array_fat_id const& l, relate_in_array_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_in_array_fat_id const& l, relate_in_array_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_in_array_const_fat_id fatten(data_container const& c, relate_in_array_id id) noexcept {
		return relate_in_array_const_fat_id(c, id);
	}
	
	class relate_in_list_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_in_list_id id;
		relate_in_list_fat_id(data_container& c, relate_in_list_id i) noexcept : container(c), id(i) {}
		relate_in_list_fat_id(relate_in_list_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_in_list_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_in_list_fat_id& operator=(relate_in_list_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_list_fat_id& operator=(relate_in_list_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_list_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_list_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_list_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_list_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_in_list_fat_id fatten(data_container& c, relate_in_list_id id) noexcept {
		return relate_in_list_fat_id(c, id);
	}
	
	class relate_in_list_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_in_list_id id;
		relate_in_list_const_fat_id(data_container const& c, relate_in_list_id i) noexcept : container(c), id(i) {}
		relate_in_list_const_fat_id(relate_in_list_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_in_list_const_fat_id(relate_in_list_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_in_list_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_in_list_const_fat_id& operator=(relate_in_list_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_list_const_fat_id& operator=(relate_in_list_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_in_list_const_fat_id& operator=(relate_in_list_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_list_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_list_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_in_list_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_list_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_list_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_in_list_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_in_list_fat_id const& l, relate_in_list_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_in_list_fat_id const& l, relate_in_list_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_in_list_const_fat_id fatten(data_container const& c, relate_in_list_id id) noexcept {
		return relate_in_list_const_fat_id(c, id);
	}
	
	class many_many_fat_id {
		friend data_container;
		public:
		data_container& container;
		many_many_id id;
		many_many_fat_id(data_container& c, many_many_id i) noexcept : container(c), id(i) {}
		many_many_fat_id(many_many_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator many_many_id() const noexcept { return id; }
		DCON_RELEASE_INLINE many_many_fat_id& operator=(many_many_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE many_many_fat_id& operator=(many_many_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(many_many_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(many_many_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(many_many_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(many_many_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_A() const noexcept;
		DCON_RELEASE_INLINE void set_A(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_A(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_B() const noexcept;
		DCON_RELEASE_INLINE void set_B(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_B(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_C() const noexcept;
		DCON_RELEASE_INLINE void set_C(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_C(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_D() const noexcept;
		DCON_RELEASE_INLINE void set_D(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_D(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_E() const noexcept;
		DCON_RELEASE_INLINE void set_E(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_E(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_F() const noexcept;
		DCON_RELEASE_INLINE void set_F(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_F(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyA_fat_id get_ignore() const noexcept;
		DCON_RELEASE_INLINE void set_ignore(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_ignore(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE many_many_fat_id fatten(data_container& c, many_many_id id) noexcept {
		return many_many_fat_id(c, id);
	}
	
	class many_many_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		many_many_id id;
		many_many_const_fat_id(data_container const& c, many_many_id i) noexcept : container(c), id(i) {}
		many_many_const_fat_id(many_many_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		many_many_const_fat_id(many_many_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator many_many_id() const noexcept { return id; }
		DCON_RELEASE_INLINE many_many_const_fat_id& operator=(many_many_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE many_many_const_fat_id& operator=(many_many_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE many_many_const_fat_id& operator=(many_many_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(many_many_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(many_many_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(many_many_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(many_many_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(many_many_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(many_many_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_A() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_B() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_C() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_D() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_E() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_F() const noexcept;
		DCON_RELEASE_INLINE thingyA_const_fat_id get_ignore() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(many_many_fat_id const& l, many_many_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(many_many_fat_id const& l, many_many_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE many_many_const_fat_id fatten(data_container const& c, many_many_id id) noexcept {
		return many_many_const_fat_id(c, id);
	}
	
	class relate_as_optional_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_optional_id id;
		relate_as_optional_fat_id(data_container& c, relate_as_optional_id i) noexcept : container(c), id(i) {}
		relate_as_optional_fat_id(relate_as_optional_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_optional_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_optional_fat_id& operator=(relate_as_optional_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_optional_fat_id& operator=(relate_as_optional_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_optional_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_optional_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_optional_fat_id fatten(data_container& c, relate_as_optional_id id) noexcept {
		return relate_as_optional_fat_id(c, id);
	}
	
	class relate_as_optional_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_optional_id id;
		relate_as_optional_const_fat_id(data_container const& c, relate_as_optional_id i) noexcept : container(c), id(i) {}
		relate_as_optional_const_fat_id(relate_as_optional_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_optional_const_fat_id(relate_as_optional_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_optional_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_optional_const_fat_id& operator=(relate_as_optional_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_optional_const_fat_id& operator=(relate_as_optional_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_optional_const_fat_id& operator=(relate_as_optional_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_optional_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_optional_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_optional_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_optional_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_optional_fat_id const& l, relate_as_optional_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_optional_fat_id const& l, relate_as_optional_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_optional_const_fat_id fatten(data_container const& c, relate_as_optional_id id) noexcept {
		return relate_as_optional_const_fat_id(c, id);
	}
	
	class relate_as_non_optional_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_non_optional_id id;
		relate_as_non_optional_fat_id(data_container& c, relate_as_non_optional_id i) noexcept : container(c), id(i) {}
		relate_as_non_optional_fat_id(relate_as_non_optional_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_non_optional_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_non_optional_fat_id& operator=(relate_as_non_optional_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_non_optional_fat_id& operator=(relate_as_non_optional_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE thingyB_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingyB_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_non_optional_fat_id fatten(data_container& c, relate_as_non_optional_id id) noexcept {
		return relate_as_non_optional_fat_id(c, id);
	}
	
	class relate_as_non_optional_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_non_optional_id id;
		relate_as_non_optional_const_fat_id(data_container const& c, relate_as_non_optional_id i) noexcept : container(c), id(i) {}
		relate_as_non_optional_const_fat_id(relate_as_non_optional_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_non_optional_const_fat_id(relate_as_non_optional_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_non_optional_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id& operator=(relate_as_non_optional_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id& operator=(relate_as_non_optional_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id& operator=(relate_as_non_optional_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingyB_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_non_optional_fat_id const& l, relate_as_non_optional_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_non_optional_fat_id const& l, relate_as_non_optional_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id fatten(data_container const& c, relate_as_non_optional_id id) noexcept {
		return relate_as_non_optional_const_fat_id(c, id);
	}
	
	class relate_as_multipleA_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_multipleA_id id;
		relate_as_multipleA_fat_id(data_container& c, relate_as_multipleA_id i) noexcept : container(c), id(i) {}
		relate_as_multipleA_fat_id(relate_as_multipleA_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleA_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleA_fat_id& operator=(relate_as_multipleA_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleA_fat_id& operator=(relate_as_multipleA_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_multipleA_fat_id fatten(data_container& c, relate_as_multipleA_id id) noexcept {
		return relate_as_multipleA_fat_id(c, id);
	}
	
	class relate_as_multipleA_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_multipleA_id id;
		relate_as_multipleA_const_fat_id(data_container const& c, relate_as_multipleA_id i) noexcept : container(c), id(i) {}
		relate_as_multipleA_const_fat_id(relate_as_multipleA_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_multipleA_const_fat_id(relate_as_multipleA_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleA_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id& operator=(relate_as_multipleA_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id& operator=(relate_as_multipleA_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id& operator=(relate_as_multipleA_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_multipleA_fat_id const& l, relate_as_multipleA_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_multipleA_fat_id const& l, relate_as_multipleA_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id fatten(data_container const& c, relate_as_multipleA_id id) noexcept {
		return relate_as_multipleA_const_fat_id(c, id);
	}
	
	class relate_as_multipleB_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_multipleB_id id;
		relate_as_multipleB_fat_id(data_container& c, relate_as_multipleB_id i) noexcept : container(c), id(i) {}
		relate_as_multipleB_fat_id(relate_as_multipleB_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleB_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleB_fat_id& operator=(relate_as_multipleB_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleB_fat_id& operator=(relate_as_multipleB_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_multipleB_fat_id fatten(data_container& c, relate_as_multipleB_id id) noexcept {
		return relate_as_multipleB_fat_id(c, id);
	}
	
	class relate_as_multipleB_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_multipleB_id id;
		relate_as_multipleB_const_fat_id(data_container const& c, relate_as_multipleB_id i) noexcept : container(c), id(i) {}
		relate_as_multipleB_const_fat_id(relate_as_multipleB_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_multipleB_const_fat_id(relate_as_multipleB_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleB_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id& operator=(relate_as_multipleB_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id& operator=(relate_as_multipleB_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id& operator=(relate_as_multipleB_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_multipleB_fat_id const& l, relate_as_multipleB_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_multipleB_fat_id const& l, relate_as_multipleB_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id fatten(data_container const& c, relate_as_multipleB_id id) noexcept {
		return relate_as_multipleB_const_fat_id(c, id);
	}
	
	class relate_as_multipleC_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_multipleC_id id;
		relate_as_multipleC_fat_id(data_container& c, relate_as_multipleC_id i) noexcept : container(c), id(i) {}
		relate_as_multipleC_fat_id(relate_as_multipleC_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleC_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleC_fat_id& operator=(relate_as_multipleC_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleC_fat_id& operator=(relate_as_multipleC_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_multipleC_fat_id fatten(data_container& c, relate_as_multipleC_id id) noexcept {
		return relate_as_multipleC_fat_id(c, id);
	}
	
	class relate_as_multipleC_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_multipleC_id id;
		relate_as_multipleC_const_fat_id(data_container const& c, relate_as_multipleC_id i) noexcept : container(c), id(i) {}
		relate_as_multipleC_const_fat_id(relate_as_multipleC_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_multipleC_const_fat_id(relate_as_multipleC_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleC_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id& operator=(relate_as_multipleC_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id& operator=(relate_as_multipleC_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id& operator=(relate_as_multipleC_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_multipleC_fat_id const& l, relate_as_multipleC_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_multipleC_fat_id const& l, relate_as_multipleC_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id fatten(data_container const& c, relate_as_multipleC_id id) noexcept {
		return relate_as_multipleC_const_fat_id(c, id);
	}
	
	class relate_as_multipleD_fat_id {
		friend data_container;
		public:
		data_container& container;
		relate_as_multipleD_id id;
		relate_as_multipleD_fat_id(data_container& c, relate_as_multipleD_id i) noexcept : container(c), id(i) {}
		relate_as_multipleD_fat_id(relate_as_multipleD_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleD_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleD_fat_id& operator=(relate_as_multipleD_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleD_fat_id& operator=(relate_as_multipleD_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(int32_t i, thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE void replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE relate_as_multipleD_fat_id fatten(data_container& c, relate_as_multipleD_id id) noexcept {
		return relate_as_multipleD_fat_id(c, id);
	}
	
	class relate_as_multipleD_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		relate_as_multipleD_id id;
		relate_as_multipleD_const_fat_id(data_container const& c, relate_as_multipleD_id i) noexcept : container(c), id(i) {}
		relate_as_multipleD_const_fat_id(relate_as_multipleD_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		relate_as_multipleD_const_fat_id(relate_as_multipleD_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator relate_as_multipleD_id() const noexcept { return id; }
		DCON_RELEASE_INLINE relate_as_multipleD_const_fat_id& operator=(relate_as_multipleD_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleD_const_fat_id& operator=(relate_as_multipleD_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE relate_as_multipleD_const_fat_id& operator=(relate_as_multipleD_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingyA_const_fat_id get_left(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_left(thingyA_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(relate_as_multipleD_fat_id const& l, relate_as_multipleD_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(relate_as_multipleD_fat_id const& l, relate_as_multipleD_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE relate_as_multipleD_const_fat_id fatten(data_container const& c, relate_as_multipleD_id id) noexcept {
		return relate_as_multipleD_const_fat_id(c, id);
	}
	
	namespace internal {
		class object_iterator_thingyA {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_thingyA(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_thingyA& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_thingyA& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_thingyA const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_thingyA const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingyA_fat_id operator*() const noexcept {
				return thingyA_fat_id(container, thingyA_id(thingyA_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_thingyA& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_thingyA& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_thingyA operator+(int32_t n) const noexcept {
				return object_iterator_thingyA(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_thingyA operator-(int32_t n) const noexcept {
				return object_iterator_thingyA(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_thingyA const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_thingyA const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_thingyA const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_thingyA const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_thingyA const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE thingyA_fat_id operator[](int32_t n) const noexcept {
				return thingyA_fat_id(container, thingyA_id(thingyA_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_thingyA {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_thingyA(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingyA& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingyA& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_thingyA const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_thingyA const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingyA_const_fat_id operator*() const noexcept {
				return thingyA_const_fat_id(container, thingyA_id(thingyA_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_thingyA& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_thingyA& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_thingyA operator+(int32_t n) const noexcept {
				return const_object_iterator_thingyA(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_thingyA operator-(int32_t n) const noexcept {
				return const_object_iterator_thingyA(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_thingyA const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_thingyA const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_thingyA const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_thingyA const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_thingyA const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE thingyA_const_fat_id operator[](int32_t n) const noexcept {
				return thingyA_const_fat_id(container, thingyA_id(thingyA_id::value_base_t(int32_t(index) + n)));
			}
		};
		
		class iterator_thingyA_foreach_relate_as_optional_as_left {
			private:
			data_container& container;
			relate_as_optional_id const* ptr = nullptr;
			public:
			iterator_thingyA_foreach_relate_as_optional_as_left(data_container& c, thingyA_id fr) noexcept;
			iterator_thingyA_foreach_relate_as_optional_as_left(data_container& c, relate_as_optional_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyA_foreach_relate_as_optional_as_left(data_container& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_fat_id operator*() const noexcept {
				return relate_as_optional_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_optional_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_optional_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_optional_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_optional_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyA_foreach_relate_as_optional_as_left {
			private:
			data_container const& container;
			relate_as_optional_id const* ptr = nullptr;
			public:
			const_iterator_thingyA_foreach_relate_as_optional_as_left(data_container const& c, thingyA_id fr) noexcept;
			const_iterator_thingyA_foreach_relate_as_optional_as_left(data_container const& c, relate_as_optional_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyA_foreach_relate_as_optional_as_left(data_container const& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_const_fat_id operator*() const noexcept {
				return relate_as_optional_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_optional_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_optional_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyA_foreach_relate_as_optional_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_optional_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_optional_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyA_foreach_relate_as_optional_as_left_generator {
			data_container& container;
			thingyA_id ob;
			iterator_thingyA_foreach_relate_as_optional_as_left_generator(data_container& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left begin() const noexcept {
				return iterator_thingyA_foreach_relate_as_optional_as_left(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left end() const noexcept {
				return iterator_thingyA_foreach_relate_as_optional_as_left(container, ob, 0);
			}
		};
		struct const_iterator_thingyA_foreach_relate_as_optional_as_left_generator {
			data_container const& container;
			thingyA_id ob;
			const_iterator_thingyA_foreach_relate_as_optional_as_left_generator(data_container const& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left begin() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_optional_as_left(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left end() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_optional_as_left(container, ob, 0);
			}
		};
		
		class iterator_thingyA_foreach_relate_as_non_optional_as_left {
			private:
			data_container& container;
			relate_as_non_optional_id const* ptr = nullptr;
			public:
			iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container& c, thingyA_id fr) noexcept;
			iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container& c, relate_as_non_optional_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_fat_id operator*() const noexcept {
				return relate_as_non_optional_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_non_optional_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_non_optional_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyA_foreach_relate_as_non_optional_as_left {
			private:
			data_container const& container;
			relate_as_non_optional_id const* ptr = nullptr;
			public:
			const_iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container const& c, thingyA_id fr) noexcept;
			const_iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container const& c, relate_as_non_optional_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container const& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id operator*() const noexcept {
				return relate_as_non_optional_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyA_foreach_relate_as_non_optional_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_non_optional_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyA_foreach_relate_as_non_optional_as_left_generator {
			data_container& container;
			thingyA_id ob;
			iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(data_container& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left begin() const noexcept {
				return iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left end() const noexcept {
				return iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ob, 0);
			}
		};
		struct const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator {
			data_container const& container;
			thingyA_id ob;
			const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(data_container const& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left begin() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left end() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_non_optional_as_left(container, ob, 0);
			}
		};
		
		class iterator_thingyA_foreach_relate_as_multipleA_as_left {
			private:
			data_container& container;
			relate_as_multipleA_id const* ptr = nullptr;
			public:
			iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container& c, thingyA_id fr) noexcept;
			iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container& c, relate_as_multipleA_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleA_fat_id operator*() const noexcept {
				return relate_as_multipleA_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_multipleA_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_multipleA_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyA_foreach_relate_as_multipleA_as_left {
			private:
			data_container const& container;
			relate_as_multipleA_id const* ptr = nullptr;
			public:
			const_iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container const& c, thingyA_id fr) noexcept;
			const_iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container const& c, relate_as_multipleA_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container const& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id operator*() const noexcept {
				return relate_as_multipleA_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyA_foreach_relate_as_multipleA_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_multipleA_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyA_foreach_relate_as_multipleA_as_left_generator {
			data_container& container;
			thingyA_id ob;
			iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(data_container& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left begin() const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left end() const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ob, 0);
			}
		};
		struct const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator {
			data_container const& container;
			thingyA_id ob;
			const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(data_container const& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left begin() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left end() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleA_as_left(container, ob, 0);
			}
		};
		
		class iterator_thingyA_foreach_relate_as_multipleC_as_left {
			private:
			data_container& container;
			relate_as_multipleC_id const* ptr = nullptr;
			public:
			iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container& c, thingyA_id fr) noexcept;
			iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container& c, relate_as_multipleC_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleC_fat_id operator*() const noexcept {
				return relate_as_multipleC_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_multipleC_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_multipleC_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyA_foreach_relate_as_multipleC_as_left {
			private:
			data_container const& container;
			relate_as_multipleC_id const* ptr = nullptr;
			public:
			const_iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container const& c, thingyA_id fr) noexcept;
			const_iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container const& c, relate_as_multipleC_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container const& c, thingyA_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id operator*() const noexcept {
				return relate_as_multipleC_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyA_foreach_relate_as_multipleC_as_left const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_multipleC_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyA_foreach_relate_as_multipleC_as_left_generator {
			data_container& container;
			thingyA_id ob;
			iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(data_container& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left begin() const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left end() const noexcept {
				return iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ob, 0);
			}
		};
		struct const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator {
			data_container const& container;
			thingyA_id ob;
			const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(data_container const& c, thingyA_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left begin() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left end() const noexcept {
				return const_iterator_thingyA_foreach_relate_as_multipleC_as_left(container, ob, 0);
			}
		};
		
		class object_iterator_thingyB {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_thingyB(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_thingyB& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_thingyB& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_thingyB const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_thingyB const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingyB_fat_id operator*() const noexcept {
				return thingyB_fat_id(container, thingyB_id(thingyB_id::value_base_t(index)));
			}
		};
		class const_object_iterator_thingyB {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_thingyB(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingyB& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingyB& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_thingyB const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_thingyB const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingyB_const_fat_id operator*() const noexcept {
				return thingyB_const_fat_id(container, thingyB_id(thingyB_id::value_base_t(index)));
			}
		};
		
		class iterator_thingyB_foreach_relate_in_array_as_right {
			private:
			data_container& container;
			relate_in_array_id const* ptr = nullptr;
			public:
			iterator_thingyB_foreach_relate_in_array_as_right(data_container& c, thingyB_id fr) noexcept;
			iterator_thingyB_foreach_relate_in_array_as_right(data_container& c, relate_in_array_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyB_foreach_relate_in_array_as_right(data_container& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_array_fat_id operator*() const noexcept {
				return relate_in_array_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_in_array_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_in_array_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_in_array_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_in_array_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyB_foreach_relate_in_array_as_right {
			private:
			data_container const& container;
			relate_in_array_id const* ptr = nullptr;
			public:
			const_iterator_thingyB_foreach_relate_in_array_as_right(data_container const& c, thingyB_id fr) noexcept;
			const_iterator_thingyB_foreach_relate_in_array_as_right(data_container const& c, relate_in_array_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyB_foreach_relate_in_array_as_right(data_container const& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_array_const_fat_id operator*() const noexcept {
				return relate_in_array_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_in_array_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_in_array_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyB_foreach_relate_in_array_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_in_array_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_in_array_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyB_foreach_relate_in_array_as_right_generator {
			data_container& container;
			thingyB_id ob;
			iterator_thingyB_foreach_relate_in_array_as_right_generator(data_container& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right begin() const noexcept {
				return iterator_thingyB_foreach_relate_in_array_as_right(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right end() const noexcept {
				return iterator_thingyB_foreach_relate_in_array_as_right(container, ob, 0);
			}
		};
		struct const_iterator_thingyB_foreach_relate_in_array_as_right_generator {
			data_container const& container;
			thingyB_id ob;
			const_iterator_thingyB_foreach_relate_in_array_as_right_generator(data_container const& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right begin() const noexcept {
				return const_iterator_thingyB_foreach_relate_in_array_as_right(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right end() const noexcept {
				return const_iterator_thingyB_foreach_relate_in_array_as_right(container, ob, 0);
			}
		};
		
		class iterator_thingyB_foreach_relate_in_list_as_right {
			private:
			data_container& container;
			relate_in_list_id list_pos;
			public:
			iterator_thingyB_foreach_relate_in_list_as_right(data_container& c, thingyB_id fr) noexcept;
			iterator_thingyB_foreach_relate_in_list_as_right(data_container& c, relate_in_list_id r) noexcept : container(c), list_pos(r) {}
			iterator_thingyB_foreach_relate_in_list_as_right(data_container& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyB_foreach_relate_in_list_as_right const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyB_foreach_relate_in_list_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_list_fat_id operator*() const noexcept {
				return relate_in_list_fat_id(container, list_pos);
			}
		};
		class const_iterator_thingyB_foreach_relate_in_list_as_right {
			private:
			data_container const& container;
			relate_in_list_id list_pos;
			public:
			const_iterator_thingyB_foreach_relate_in_list_as_right(data_container const& c, thingyB_id fr) noexcept;
			const_iterator_thingyB_foreach_relate_in_list_as_right(data_container const& c, relate_in_list_id r) noexcept : container(c), list_pos(r) {}
			const_iterator_thingyB_foreach_relate_in_list_as_right(data_container const& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyB_foreach_relate_in_list_as_right const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyB_foreach_relate_in_list_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_list_const_fat_id operator*() const noexcept {
				return relate_in_list_const_fat_id(container, list_pos);
			}
		};
		
		struct iterator_thingyB_foreach_relate_in_list_as_right_generator {
			data_container& container;
			thingyB_id ob;
			iterator_thingyB_foreach_relate_in_list_as_right_generator(data_container& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right begin() const noexcept {
				return iterator_thingyB_foreach_relate_in_list_as_right(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right end() const noexcept {
				return iterator_thingyB_foreach_relate_in_list_as_right(container);
			}
		};
		struct const_iterator_thingyB_foreach_relate_in_list_as_right_generator {
			data_container const& container;
			thingyB_id ob;
			const_iterator_thingyB_foreach_relate_in_list_as_right_generator(data_container const& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right begin() const noexcept {
				return const_iterator_thingyB_foreach_relate_in_list_as_right(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right end() const noexcept {
				return const_iterator_thingyB_foreach_relate_in_list_as_right(container);
			}
		};
		
		class iterator_thingyB_foreach_relate_as_optional_as_right {
			private:
			data_container& container;
			relate_as_optional_id const* ptr = nullptr;
			public:
			iterator_thingyB_foreach_relate_as_optional_as_right(data_container& c, thingyB_id fr) noexcept;
			iterator_thingyB_foreach_relate_as_optional_as_right(data_container& c, relate_as_optional_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyB_foreach_relate_as_optional_as_right(data_container& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_fat_id operator*() const noexcept {
				return relate_as_optional_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_as_optional_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_as_optional_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_optional_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_optional_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyB_foreach_relate_as_optional_as_right {
			private:
			data_container const& container;
			relate_as_optional_id const* ptr = nullptr;
			public:
			const_iterator_thingyB_foreach_relate_as_optional_as_right(data_container const& c, thingyB_id fr) noexcept;
			const_iterator_thingyB_foreach_relate_as_optional_as_right(data_container const& c, relate_as_optional_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyB_foreach_relate_as_optional_as_right(data_container const& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_const_fat_id operator*() const noexcept {
				return relate_as_optional_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_as_optional_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_as_optional_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyB_foreach_relate_as_optional_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_optional_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_optional_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyB_foreach_relate_as_optional_as_right_generator {
			data_container& container;
			thingyB_id ob;
			iterator_thingyB_foreach_relate_as_optional_as_right_generator(data_container& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right begin() const noexcept {
				return iterator_thingyB_foreach_relate_as_optional_as_right(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right end() const noexcept {
				return iterator_thingyB_foreach_relate_as_optional_as_right(container, ob, 0);
			}
		};
		struct const_iterator_thingyB_foreach_relate_as_optional_as_right_generator {
			data_container const& container;
			thingyB_id ob;
			const_iterator_thingyB_foreach_relate_as_optional_as_right_generator(data_container const& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right begin() const noexcept {
				return const_iterator_thingyB_foreach_relate_as_optional_as_right(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right end() const noexcept {
				return const_iterator_thingyB_foreach_relate_as_optional_as_right(container, ob, 0);
			}
		};
		
		class iterator_thingyB_foreach_relate_as_non_optional_as_right {
			private:
			data_container& container;
			relate_as_non_optional_id const* ptr = nullptr;
			public:
			iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container& c, thingyB_id fr) noexcept;
			iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container& c, relate_as_non_optional_id const* r) noexcept : container(c), ptr(r) {}
			iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_fat_id operator*() const noexcept {
				return relate_as_non_optional_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right operator+(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right operator-(ptrdiff_t n) const noexcept {
				return iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_non_optional_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_non_optional_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_thingyB_foreach_relate_as_non_optional_as_right {
			private:
			data_container const& container;
			relate_as_non_optional_id const* ptr = nullptr;
			public:
			const_iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container const& c, thingyB_id fr) noexcept;
			const_iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container const& c, relate_as_non_optional_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container const& c, thingyB_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id operator*() const noexcept {
				return relate_as_non_optional_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right operator+(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right operator-(ptrdiff_t n) const noexcept {
				return const_iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_thingyB_foreach_relate_as_non_optional_as_right const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return relate_as_non_optional_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_thingyB_foreach_relate_as_non_optional_as_right_generator {
			data_container& container;
			thingyB_id ob;
			iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(data_container& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right begin() const noexcept {
				return iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ob);
			}
			DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right end() const noexcept {
				return iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ob, 0);
			}
		};
		struct const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator {
			data_container const& container;
			thingyB_id ob;
			const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(data_container const& c, thingyB_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right begin() const noexcept {
				return const_iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right end() const noexcept {
				return const_iterator_thingyB_foreach_relate_as_non_optional_as_right(container, ob, 0);
			}
		};
		
		class object_iterator_relate_same {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_same(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_same& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_same& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_same const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_same const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_same_fat_id operator*() const noexcept {
				return relate_same_fat_id(container, relate_same_id(relate_same_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_relate_same& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_same& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_same operator+(int32_t n) const noexcept {
				return object_iterator_relate_same(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_relate_same operator-(int32_t n) const noexcept {
				return object_iterator_relate_same(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_relate_same const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_relate_same const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_relate_same const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_relate_same const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_relate_same const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_same_fat_id operator[](int32_t n) const noexcept {
				return relate_same_fat_id(container, relate_same_id(relate_same_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_relate_same {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_same(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_same& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_same& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_same const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_same const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_same_const_fat_id operator*() const noexcept {
				return relate_same_const_fat_id(container, relate_same_id(relate_same_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_same& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_same& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_same operator+(int32_t n) const noexcept {
				return const_object_iterator_relate_same(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_same operator-(int32_t n) const noexcept {
				return const_object_iterator_relate_same(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_relate_same const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_relate_same const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_relate_same const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_relate_same const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_relate_same const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_same_const_fat_id operator[](int32_t n) const noexcept {
				return relate_same_const_fat_id(container, relate_same_id(relate_same_id::value_base_t(int32_t(index) + n)));
			}
		};
		
		class object_iterator_relate_in_array {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_in_array(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_in_array& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_in_array& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_in_array const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_in_array const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_array_fat_id operator*() const noexcept {
				return relate_in_array_fat_id(container, relate_in_array_id(relate_in_array_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_array& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_array& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_array operator+(int32_t n) const noexcept {
				return object_iterator_relate_in_array(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_array operator-(int32_t n) const noexcept {
				return object_iterator_relate_in_array(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_relate_in_array const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_relate_in_array const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_relate_in_array const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_relate_in_array const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_relate_in_array const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_in_array_fat_id operator[](int32_t n) const noexcept {
				return relate_in_array_fat_id(container, relate_in_array_id(relate_in_array_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_relate_in_array {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_in_array(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_in_array const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_in_array const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_array_const_fat_id operator*() const noexcept {
				return relate_in_array_const_fat_id(container, relate_in_array_id(relate_in_array_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array operator+(int32_t n) const noexcept {
				return const_object_iterator_relate_in_array(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_array operator-(int32_t n) const noexcept {
				return const_object_iterator_relate_in_array(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_relate_in_array const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_relate_in_array const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_relate_in_array const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_relate_in_array const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_relate_in_array const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_in_array_const_fat_id operator[](int32_t n) const noexcept {
				return relate_in_array_const_fat_id(container, relate_in_array_id(relate_in_array_id::value_base_t(int32_t(index) + n)));
			}
		};
		
		class object_iterator_relate_in_list {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_in_list(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_in_list& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_in_list& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_in_list const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_in_list const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_list_fat_id operator*() const noexcept {
				return relate_in_list_fat_id(container, relate_in_list_id(relate_in_list_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_list& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_list& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_list operator+(int32_t n) const noexcept {
				return object_iterator_relate_in_list(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_relate_in_list operator-(int32_t n) const noexcept {
				return object_iterator_relate_in_list(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_relate_in_list const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_relate_in_list const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_relate_in_list const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_relate_in_list const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_relate_in_list const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_in_list_fat_id operator[](int32_t n) const noexcept {
				return relate_in_list_fat_id(container, relate_in_list_id(relate_in_list_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_relate_in_list {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_in_list(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_in_list const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_in_list const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_in_list_const_fat_id operator*() const noexcept {
				return relate_in_list_const_fat_id(container, relate_in_list_id(relate_in_list_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list operator+(int32_t n) const noexcept {
				return const_object_iterator_relate_in_list(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_relate_in_list operator-(int32_t n) const noexcept {
				return const_object_iterator_relate_in_list(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_relate_in_list const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_relate_in_list const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_relate_in_list const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_relate_in_list const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_relate_in_list const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE relate_in_list_const_fat_id operator[](int32_t n) const noexcept {
				return relate_in_list_const_fat_id(container, relate_in_list_id(relate_in_list_id::value_base_t(int32_t(index) + n)));
			}
		};
		
		class object_iterator_many_many {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_many_many(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_many_many& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_many_many& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_many_many const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_many_many const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE many_many_fat_id operator*() const noexcept {
				return many_many_fat_id(container, many_many_id(many_many_id::value_base_t(index)));
			}
		};
		class const_object_iterator_many_many {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_many_many(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_many_many& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_many_many& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_many_many const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_many_many const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE many_many_const_fat_id operator*() const noexcept {
				return many_many_const_fat_id(container, many_many_id(many_many_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_optional {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_optional(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_optional& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_optional& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_optional const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_optional const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_fat_id operator*() const noexcept {
				return relate_as_optional_fat_id(container, relate_as_optional_id(relate_as_optional_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_optional {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_optional(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_optional& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_optional& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_optional const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_optional const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_optional_const_fat_id operator*() const noexcept {
				return relate_as_optional_const_fat_id(container, relate_as_optional_id(relate_as_optional_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_non_optional {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_non_optional(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_non_optional& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_non_optional& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_non_optional const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_non_optional const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_fat_id operator*() const noexcept {
				return relate_as_non_optional_fat_id(container, relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_non_optional {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_non_optional(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_non_optional& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_non_optional& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_non_optional const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_non_optional const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_non_optional_const_fat_id operator*() const noexcept {
				return relate_as_non_optional_const_fat_id(container, relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_multipleA {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_multipleA(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleA& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleA& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_multipleA const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_multipleA const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleA_fat_id operator*() const noexcept {
				return relate_as_multipleA_fat_id(container, relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_multipleA {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_multipleA(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleA& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleA& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_multipleA const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_multipleA const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleA_const_fat_id operator*() const noexcept {
				return relate_as_multipleA_const_fat_id(container, relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_multipleB {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_multipleB(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleB& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleB& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_multipleB const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_multipleB const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleB_fat_id operator*() const noexcept {
				return relate_as_multipleB_fat_id(container, relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_multipleB {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_multipleB(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleB& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleB& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_multipleB const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_multipleB const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id operator*() const noexcept {
				return relate_as_multipleB_const_fat_id(container, relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_multipleC {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_multipleC(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleC& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleC& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_multipleC const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_multipleC const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleC_fat_id operator*() const noexcept {
				return relate_as_multipleC_fat_id(container, relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_multipleC {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_multipleC(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleC& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleC& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_multipleC const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_multipleC const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleC_const_fat_id operator*() const noexcept {
				return relate_as_multipleC_const_fat_id(container, relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)));
			}
		};
		
		class object_iterator_relate_as_multipleD {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_relate_as_multipleD(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleD& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_relate_as_multipleD& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_relate_as_multipleD const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_relate_as_multipleD const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleD_fat_id operator*() const noexcept {
				return relate_as_multipleD_fat_id(container, relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)));
			}
		};
		class const_object_iterator_relate_as_multipleD {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_relate_as_multipleD(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleD& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleD& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_relate_as_multipleD const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_relate_as_multipleD const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE relate_as_multipleD_const_fat_id operator*() const noexcept {
				return relate_as_multipleD_const_fat_id(container, relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)));
			}
		};
		
	}

	class alignas(64) data_container {
		public:
		internal::thingyA_class thingyA;
		internal::thingyB_class thingyB;
		internal::relate_same_class relate_same;
		internal::relate_in_array_class relate_in_array;
		internal::relate_in_list_class relate_in_list;
		internal::many_many_class many_many;
		internal::relate_as_optional_class relate_as_optional;
		internal::relate_as_non_optional_class relate_as_non_optional;
		internal::relate_as_multipleA_class relate_as_multipleA;
		internal::relate_as_multipleB_class relate_as_multipleB;
		internal::relate_as_multipleC_class relate_as_multipleC;
		internal::relate_as_multipleD_class relate_as_multipleD;

		//
		// Functions for thingyA:
		//
		//
		// accessors for thingyA: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingyA_get_some_value(thingyA_id id) const noexcept {
			return thingyA.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingyA_get_some_value(thingyA_id id) noexcept {
			return thingyA.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyA_get_some_value(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, thingyA.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyA_get_some_value(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, thingyA.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyA_get_some_value(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::load(id, thingyA.m_some_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_set_some_value(thingyA_id id, int32_t value) noexcept {
			thingyA.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingyA_set_some_value(ve::contiguous_tags<thingyA_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyA.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingyA_set_some_value(ve::partial_contiguous_tags<thingyA_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyA.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingyA_set_some_value(ve::tagged_vector<thingyA_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyA.m_some_value.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE relate_same_id thingyA_get_relate_same_as_left(thingyA_id id) const noexcept {
			return (id.value <= relate_same.size_used) ? relate_same_id(relate_same_id::value_base_t(id.index())) : relate_same_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<relate_same_id> thingyA_get_relate_same_as_left(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::contiguous_tags<relate_same_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<relate_same_id> thingyA_get_relate_same_as_left(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::partial_contiguous_tags<relate_same_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_same_id> thingyA_get_relate_same_as_left(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::tagged_vector<relate_same_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_same_as_left(thingyA_id id) noexcept {
			if(relate_same_is_valid(relate_same_id(relate_same_id::value_base_t(id.index())))) {
				relate_same_set_left(relate_same_id(relate_same_id::value_base_t(id.index())), thingyA_id());
			}
		}
		DCON_RELEASE_INLINE relate_in_array_id thingyA_get_relate_in_array_as_left(thingyA_id id) const noexcept {
			return (id.value <= relate_in_array.size_used) ? relate_in_array_id(relate_in_array_id::value_base_t(id.index())) : relate_in_array_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<relate_in_array_id> thingyA_get_relate_in_array_as_left(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::contiguous_tags<relate_in_array_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<relate_in_array_id> thingyA_get_relate_in_array_as_left(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::partial_contiguous_tags<relate_in_array_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_in_array_id> thingyA_get_relate_in_array_as_left(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::tagged_vector<relate_in_array_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_in_array_as_left(thingyA_id id) noexcept {
			if(relate_in_array_is_valid(relate_in_array_id(relate_in_array_id::value_base_t(id.index())))) {
				relate_in_array_set_left(relate_in_array_id(relate_in_array_id::value_base_t(id.index())), thingyA_id());
			}
		}
		DCON_RELEASE_INLINE relate_in_array_id thingyA_get_relate_in_array(thingyA_id id) const noexcept {
			return (id.value <= relate_in_array.size_used) ? relate_in_array_id(relate_in_array_id::value_base_t(id.index())) : relate_in_array_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<relate_in_array_id> thingyA_get_relate_in_array(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::contiguous_tags<relate_in_array_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<relate_in_array_id> thingyA_get_relate_in_array(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::partial_contiguous_tags<relate_in_array_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_in_array_id> thingyA_get_relate_in_array(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::tagged_vector<relate_in_array_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_in_array(thingyA_id id) noexcept {
			if(relate_in_array_is_valid(relate_in_array_id(relate_in_array_id::value_base_t(id.index())))) {
				relate_in_array_set_left(relate_in_array_id(relate_in_array_id::value_base_t(id.index())), thingyA_id());
			}
		}
		DCON_RELEASE_INLINE thingyB_id thingyA_get_right_from_relate_in_array(thingyA_id ref_id) const {
			return relate_in_array_get_right(relate_in_array_id(relate_in_array_id::value_base_t(ref_id.index())));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_array(ve::contiguous_tags<thingyA_id> ref_id) const {
			return relate_in_array_get_right(ve::contiguous_tags<relate_in_array_id>(ref_id.value));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_array(ve::partial_contiguous_tags<thingyA_id> ref_id) const {
			return relate_in_array_get_right(ve::partial_contiguous_tags<relate_in_array_id>(ref_id.value, ref_id.subcount));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_array(ve::tagged_vector<thingyA_id> ref_id) const {
			return relate_in_array_get_right(ve::tagged_vector<relate_in_array_id>(ref_id, std::true_type{}));
		}
		#endif
		void thingyA_set_right_from_relate_in_array(thingyA_id ref_id, thingyB_id val) {
			relate_in_array_set_right(relate_in_array_id(relate_in_array_id::value_base_t(ref_id.index())), val);
		}
		DCON_RELEASE_INLINE relate_in_list_id thingyA_get_relate_in_list_as_left(thingyA_id id) const noexcept {
			return (id.value <= relate_in_list.size_used) ? relate_in_list_id(relate_in_list_id::value_base_t(id.index())) : relate_in_list_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<relate_in_list_id> thingyA_get_relate_in_list_as_left(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::contiguous_tags<relate_in_list_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<relate_in_list_id> thingyA_get_relate_in_list_as_left(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::partial_contiguous_tags<relate_in_list_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_in_list_id> thingyA_get_relate_in_list_as_left(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::tagged_vector<relate_in_list_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_in_list_as_left(thingyA_id id) noexcept {
			if(relate_in_list_is_valid(relate_in_list_id(relate_in_list_id::value_base_t(id.index())))) {
				relate_in_list_set_left(relate_in_list_id(relate_in_list_id::value_base_t(id.index())), thingyA_id());
			}
		}
		DCON_RELEASE_INLINE relate_in_list_id thingyA_get_relate_in_list(thingyA_id id) const noexcept {
			return (id.value <= relate_in_list.size_used) ? relate_in_list_id(relate_in_list_id::value_base_t(id.index())) : relate_in_list_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<relate_in_list_id> thingyA_get_relate_in_list(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::contiguous_tags<relate_in_list_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<relate_in_list_id> thingyA_get_relate_in_list(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::partial_contiguous_tags<relate_in_list_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_in_list_id> thingyA_get_relate_in_list(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::tagged_vector<relate_in_list_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_in_list(thingyA_id id) noexcept {
			if(relate_in_list_is_valid(relate_in_list_id(relate_in_list_id::value_base_t(id.index())))) {
				relate_in_list_set_left(relate_in_list_id(relate_in_list_id::value_base_t(id.index())), thingyA_id());
			}
		}
		DCON_RELEASE_INLINE thingyB_id thingyA_get_right_from_relate_in_list(thingyA_id ref_id) const {
			return relate_in_list_get_right(relate_in_list_id(relate_in_list_id::value_base_t(ref_id.index())));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_list(ve::contiguous_tags<thingyA_id> ref_id) const {
			return relate_in_list_get_right(ve::contiguous_tags<relate_in_list_id>(ref_id.value));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_list(ve::partial_contiguous_tags<thingyA_id> ref_id) const {
			return relate_in_list_get_right(ve::partial_contiguous_tags<relate_in_list_id>(ref_id.value, ref_id.subcount));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> thingyA_get_right_from_relate_in_list(ve::tagged_vector<thingyA_id> ref_id) const {
			return relate_in_list_get_right(ve::tagged_vector<relate_in_list_id>(ref_id, std::true_type{}));
		}
		#endif
		void thingyA_set_right_from_relate_in_list(thingyA_id ref_id, thingyB_id val) {
			relate_in_list_set_right(relate_in_list_id(relate_in_list_id::value_base_t(ref_id.index())), val);
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_get_relate_as_optional_as_left(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_get_relate_as_optional_as_left(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_optional_as_left(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_range_of_relate_as_optional_as_left(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_optional_as_left(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_optional_as_left(id);
			dcon::local_vector<relate_as_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_optional_id i) { t->relate_as_optional_set_left(i, thingyA_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_get_relate_as_optional(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_get_relate_as_optional(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_optional(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_range_of_relate_as_optional(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_optional(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_optional_as_left(id);
			dcon::local_vector<relate_as_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_optional_id i) { t->relate_as_optional_set_left(i, thingyA_id()); });
		}
		template<typename T>
		void thingyA_for_each_right_from_relate_as_optional(thingyA_id id, T&& func) const {
			thingyA_for_each_relate_as_optional_as_left(id, [&](relate_as_optional_id i) {
				func(relate_as_optional_get_right(i));
			} );
		}
		bool thingyA_has_right_from_relate_as_optional(thingyA_id id, thingyB_id target) const {
			auto vrange = dcon::get_range(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[id.index()]);
			for(auto pos = vrange.first; pos != vrange.second; ++pos) {
				if(relate_as_optional.m_right.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_get_relate_as_non_optional_as_left(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_get_relate_as_non_optional_as_left(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_non_optional_as_left(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_range_of_relate_as_non_optional_as_left(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_non_optional_as_left(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_non_optional_as_left(id);
			dcon::local_vector<relate_as_non_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_non_optional_id i) { t->relate_as_non_optional_set_left(i, thingyA_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_get_relate_as_non_optional(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_get_relate_as_non_optional(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_non_optional(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_range_of_relate_as_non_optional(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_non_optional(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_non_optional_as_left(id);
			dcon::local_vector<relate_as_non_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_non_optional_id i) { t->relate_as_non_optional_set_left(i, thingyA_id()); });
		}
		template<typename T>
		void thingyA_for_each_right_from_relate_as_non_optional(thingyA_id id, T&& func) const {
			thingyA_for_each_relate_as_non_optional_as_left(id, [&](relate_as_non_optional_id i) {
				func(relate_as_non_optional_get_right(i));
			} );
		}
		bool thingyA_has_right_from_relate_as_non_optional(thingyA_id id, thingyB_id target) const {
			auto vrange = dcon::get_range(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[id.index()]);
			for(auto pos = vrange.first; pos != vrange.second; ++pos) {
				if(relate_as_non_optional.m_right.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_get_relate_as_multipleA_as_left(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_get_relate_as_multipleA_as_left(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_multipleA_as_left(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleA.left_storage, relate_as_multipleA.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_range_of_relate_as_multipleA_as_left(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleA.left_storage, relate_as_multipleA.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_multipleA_as_left(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_multipleA_as_left(id);
			dcon::local_vector<relate_as_multipleA_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this, id](relate_as_multipleA_id i) { t->relate_as_multipleA_replace_left(i, thingyA_id(), id); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_get_relate_as_multipleA(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_get_relate_as_multipleA(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_multipleA(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleA.left_storage, relate_as_multipleA.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_range_of_relate_as_multipleA(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleA.left_storage, relate_as_multipleA.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_multipleA(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_multipleA_as_left(id);
			dcon::local_vector<relate_as_multipleA_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this, id](relate_as_multipleA_id i) { t->relate_as_multipleA_replace_left(i, thingyA_id(), id); });
		}
		DCON_RELEASE_INLINE relate_as_multipleB_id thingyA_get_relate_as_multipleB_as_left(thingyA_id id) const noexcept {
			return relate_as_multipleB.m_link_back_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB_as_left(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB_as_left(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB_as_left(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_as_multipleB_as_left(thingyA_id id) noexcept {
			if(auto backid = relate_as_multipleB.m_link_back_left.vptr()[id.index()]; bool(backid)) {
				relate_as_multipleB_replace_left(backid, thingyA_id(), id);
			}
		}
		DCON_RELEASE_INLINE relate_as_multipleB_id thingyA_get_relate_as_multipleB(thingyA_id id) const noexcept {
			return relate_as_multipleB.m_link_back_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB(ve::contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB(ve::partial_contiguous_tags<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<relate_as_multipleB_id> thingyA_get_relate_as_multipleB(ve::tagged_vector<thingyA_id> id) const noexcept {
			return ve::load(id, relate_as_multipleB.m_link_back_left.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingyA_remove_relate_as_multipleB(thingyA_id id) noexcept {
			if(auto backid = relate_as_multipleB.m_link_back_left.vptr()[id.index()]; bool(backid)) {
				relate_as_multipleB_replace_left(backid, thingyA_id(), id);
			}
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_get_relate_as_multipleC_as_left(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_get_relate_as_multipleC_as_left(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_multipleC_as_left(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleC.left_storage, relate_as_multipleC.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_range_of_relate_as_multipleC_as_left(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleC.left_storage, relate_as_multipleC.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_multipleC_as_left(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_multipleC_as_left(id);
			dcon::local_vector<relate_as_multipleC_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this, id](relate_as_multipleC_id i) { t->relate_as_multipleC_replace_left(i, thingyA_id(), id); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_get_relate_as_multipleC(thingyA_id id) const {
			return internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_get_relate_as_multipleC(thingyA_id id) {
			return internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyA_for_each_relate_as_multipleC(thingyA_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleC.left_storage, relate_as_multipleC.m_array_left.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_range_of_relate_as_multipleC(thingyA_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_multipleC.left_storage, relate_as_multipleC.m_array_left.vptr()[id.index()]);
				return std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*>(nullptr, nullptr);
			}
		}
		void thingyA_remove_all_relate_as_multipleC(thingyA_id id) noexcept {
			auto rng = thingyA_range_of_relate_as_multipleC_as_left(id);
			dcon::local_vector<relate_as_multipleC_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this, id](relate_as_multipleC_id i) { t->relate_as_multipleC_replace_left(i, thingyA_id(), id); });
		}
		DCON_RELEASE_INLINE bool thingyA_is_valid(thingyA_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < thingyA.size_used;
		}
		
		uint32_t thingyA_size() const noexcept { return thingyA.size_used; }

		//
		// Functions for thingyB:
		//
		//
		// accessors for thingyB: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingyB_get_some_value(thingyB_id id) const noexcept {
			return thingyB.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingyB_get_some_value(thingyB_id id) noexcept {
			return thingyB.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyB_get_some_value(ve::contiguous_tags<thingyB_id> id) const noexcept {
			return ve::load(id, thingyB.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyB_get_some_value(ve::partial_contiguous_tags<thingyB_id> id) const noexcept {
			return ve::load(id, thingyB.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingyB_get_some_value(ve::tagged_vector<thingyB_id> id) const noexcept {
			return ve::load(id, thingyB.m_some_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingyB_set_some_value(thingyB_id id, int32_t value) noexcept {
			thingyB.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingyB_set_some_value(ve::contiguous_tags<thingyB_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyB.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingyB_set_some_value(ve::partial_contiguous_tags<thingyB_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyB.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingyB_set_some_value(ve::tagged_vector<thingyB_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingyB.m_some_value.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_get_relate_in_array_as_right(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_get_relate_in_array_as_right(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_in_array_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_in_array_as_right(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_range_of_relate_in_array_as_right(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[id.index()]);
				return std::pair<relate_in_array_id const*, relate_in_array_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_in_array_id const*, relate_in_array_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_in_array_as_right(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_in_array_as_right(id);
			dcon::local_vector<relate_in_array_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_in_array_id i) { t->relate_in_array_set_right(i, thingyB_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_get_relate_in_array(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_get_relate_in_array(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_in_array_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_in_array(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_range_of_relate_in_array(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[id.index()]);
				return std::pair<relate_in_array_id const*, relate_in_array_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_in_array_id const*, relate_in_array_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_in_array(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_in_array_as_right(id);
			dcon::local_vector<relate_in_array_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_in_array_id i) { t->relate_in_array_set_right(i, thingyB_id()); });
		}
		template<typename T>
		void thingyB_for_each_left_from_relate_in_array(thingyB_id id, T&& func) const {
			thingyB_for_each_relate_in_array_as_right(id, [&](relate_in_array_id i) {
				func(relate_in_array_get_left(i));
			} );
		}
		bool thingyB_has_left_from_relate_in_array(thingyB_id id, thingyA_id target) const {
			auto vrange = dcon::get_range(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[id.index()]);
			for(auto pos = vrange.first; pos != vrange.second; ++pos) {
				if(pos->index() == target.index()) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_get_relate_in_list_as_right(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_get_relate_in_list_as_right(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_in_list_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_in_list_as_right(thingyB_id id, T&& func) const {
			if(bool(id)) {
				for(auto list_pos = relate_in_list.m_head_back_right.vptr()[id.index()]; bool(list_pos); list_pos = relate_in_list.m_link_right.vptr()[list_pos.index()].right) {
					func(list_pos);
				}
			}
		}
		void thingyB_remove_all_relate_in_list_as_right(thingyB_id id) noexcept {
			dcon::local_vector<relate_in_list_id> temp;
			thingyB_for_each_relate_in_list_as_right(id, [&](relate_in_list_id j) { temp.push_back(j); });
			std::for_each(temp.begin(), temp.end(), [t = this](relate_in_list_id i) { t->relate_in_list_set_right(i, thingyB_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_get_relate_in_list(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_get_relate_in_list(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_in_list_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_in_list(thingyB_id id, T&& func) const {
			if(bool(id)) {
				for(auto list_pos = relate_in_list.m_head_back_right.vptr()[id.index()]; bool(list_pos); list_pos = relate_in_list.m_link_right.vptr()[list_pos.index()].right) {
					func(list_pos);
				}
			}
		}
		void thingyB_remove_all_relate_in_list(thingyB_id id) noexcept {
			dcon::local_vector<relate_in_list_id> temp;
			thingyB_for_each_relate_in_list_as_right(id, [&](relate_in_list_id j) { temp.push_back(j); });
			std::for_each(temp.begin(), temp.end(), [t = this](relate_in_list_id i) { t->relate_in_list_set_right(i, thingyB_id()); });
		}
		template<typename T>
		void thingyB_for_each_left_from_relate_in_list(thingyB_id id, T&& func) const {
			thingyB_for_each_relate_in_list_as_right(id, [&](relate_in_list_id i) {
				func(relate_in_list_get_left(i));
			} );
		}
		bool thingyB_has_left_from_relate_in_list(thingyB_id id, thingyA_id target) const {
			for(auto list_pos = relate_in_list.m_head_back_right.vptr()[id.index()]; bool(list_pos); list_pos = relate_in_list.m_link_right.vptr()[list_pos.index()].right) {
				if(list_pos.index() == target.index()) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_get_relate_as_optional_as_right(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_get_relate_as_optional_as_right(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_as_optional_as_right(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_range_of_relate_as_optional_as_right(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[id.index()]);
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_as_optional_as_right(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_as_optional_as_right(id);
			dcon::local_vector<relate_as_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_optional_id i) { t->relate_as_optional_set_right(i, thingyB_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_get_relate_as_optional(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_get_relate_as_optional(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_as_optional(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_range_of_relate_as_optional(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[id.index()]);
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_optional_id const*, relate_as_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_as_optional(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_as_optional_as_right(id);
			dcon::local_vector<relate_as_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_optional_id i) { t->relate_as_optional_set_right(i, thingyB_id()); });
		}
		template<typename T>
		void thingyB_for_each_left_from_relate_as_optional(thingyB_id id, T&& func) const {
			thingyB_for_each_relate_as_optional_as_right(id, [&](relate_as_optional_id i) {
				func(relate_as_optional_get_left(i));
			} );
		}
		bool thingyB_has_left_from_relate_as_optional(thingyB_id id, thingyA_id target) const {
			auto vrange = dcon::get_range(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[id.index()]);
			for(auto pos = vrange.first; pos != vrange.second; ++pos) {
				if(relate_as_optional.m_left.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_get_relate_as_non_optional_as_right(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_get_relate_as_non_optional_as_right(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_as_non_optional_as_right(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_range_of_relate_as_non_optional_as_right(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[id.index()]);
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_as_non_optional_as_right(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_as_non_optional_as_right(id);
			dcon::local_vector<relate_as_non_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_non_optional_id i) { t->relate_as_non_optional_set_right(i, thingyB_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_get_relate_as_non_optional(thingyB_id id) const {
			return internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_get_relate_as_non_optional(thingyB_id id) {
			return internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingyB_for_each_relate_as_non_optional(thingyB_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_range_of_relate_as_non_optional(thingyB_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[id.index()]);
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*>(nullptr, nullptr);
			}
		}
		void thingyB_remove_all_relate_as_non_optional(thingyB_id id) noexcept {
			auto rng = thingyB_range_of_relate_as_non_optional_as_right(id);
			dcon::local_vector<relate_as_non_optional_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](relate_as_non_optional_id i) { t->relate_as_non_optional_set_right(i, thingyB_id()); });
		}
		template<typename T>
		void thingyB_for_each_left_from_relate_as_non_optional(thingyB_id id, T&& func) const {
			thingyB_for_each_relate_as_non_optional_as_right(id, [&](relate_as_non_optional_id i) {
				func(relate_as_non_optional_get_left(i));
			} );
		}
		bool thingyB_has_left_from_relate_as_non_optional(thingyB_id id, thingyA_id target) const {
			auto vrange = dcon::get_range(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[id.index()]);
			for(auto pos = vrange.first; pos != vrange.second; ++pos) {
				if(relate_as_non_optional.m_left.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE bool thingyB_is_valid(thingyB_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < thingyB.size_used && thingyB.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t thingyB_size() const noexcept { return thingyB.size_used; }

		//
		// Functions for relate_same:
		//
		DCON_RELEASE_INLINE thingyA_id relate_same_get_left(relate_same_id id) const noexcept {
			return thingyA_id(thingyA_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<thingyA_id> relate_same_get_left(ve::contiguous_tags<relate_same_id> id) const noexcept {
			return ve::contiguous_tags<thingyA_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<thingyA_id> relate_same_get_left(ve::partial_contiguous_tags<relate_same_id> id) const noexcept {
			return ve::partial_contiguous_tags<thingyA_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<thingyA_id> relate_same_get_left(ve::tagged_vector<relate_same_id> id) const noexcept {
			return ve::tagged_vector<thingyA_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_relate_same_set_left(relate_same_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_same( relate_same_id(relate_same_id::value_base_t(value.index())) );
				internal_move_relationship_relate_same(id, relate_same_id(relate_same_id::value_base_t(value.index())) );
			}
		}
		public:
		void relate_same_set_left(relate_same_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_same( relate_same_id(relate_same_id::value_base_t(value.index())) );
				internal_move_relationship_relate_same(id, relate_same_id(relate_same_id::value_base_t(value.index())) );
			} else {
				delete_relate_same(id);
			}
		}
		bool relate_same_try_set_left(relate_same_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				if(relate_same_is_valid( relate_same_id(relate_same_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_relate_same(id, relate_same_id(relate_same_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE thingyA_id relate_same_get_right(relate_same_id id) const noexcept {
			return relate_same.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_same_get_right(ve::contiguous_tags<relate_same_id> id) const noexcept {
			return ve::load(id, relate_same.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_same_get_right(ve::partial_contiguous_tags<relate_same_id> id) const noexcept {
			return ve::load(id, relate_same.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_same_get_right(ve::tagged_vector<relate_same_id> id) const noexcept {
			return ve::load(id, relate_same.m_right.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_relate_same_set_right(relate_same_id id, thingyA_id value) noexcept {
			relate_same.m_right.vptr()[id.index()] = value;
		}
		public:
		void relate_same_set_right(relate_same_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_relate_same(id);
				return;
			}
			relate_same.hashm_joint.erase( relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id.index())), relate_same.m_right.vptr()[id.index()]) );
			relate_same.m_right.vptr()[id.index()] = value;
			if(auto it = relate_same.hashm_joint.find( relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id.index())), relate_same.m_right.vptr()[id.index()]) ); it != relate_same.hashm_joint.end()) {
				delete_relate_same(it->second);
			}
			relate_same.hashm_joint.insert_or_assign(relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id.index())), relate_same.m_right.vptr()[id.index()]), id);
		}
		bool relate_same_try_set_right(relate_same_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(relate_same.hashm_joint.find( relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id.index())), value) ) != relate_same.hashm_joint.end()) return false;
			relate_same.m_right.vptr()[id.index()] = value;
			relate_same.hashm_joint.insert_or_assign(relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id.index())), relate_same.m_right.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE bool relate_same_is_valid(relate_same_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_same.size_used && thingyA_is_valid(thingyA_id(thingyA_id::value_base_t(id.index()))) && (bool(relate_same.m_right.vptr()[id.index()]) || false);
		}
		
		uint32_t relate_same_size() const noexcept { return relate_same.size_used; }

		//
		// Functions for relate_in_array:
		//
		DCON_RELEASE_INLINE thingyA_id relate_in_array_get_left(relate_in_array_id id) const noexcept {
			return thingyA_id(thingyA_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<thingyA_id> relate_in_array_get_left(ve::contiguous_tags<relate_in_array_id> id) const noexcept {
			return ve::contiguous_tags<thingyA_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<thingyA_id> relate_in_array_get_left(ve::partial_contiguous_tags<relate_in_array_id> id) const noexcept {
			return ve::partial_contiguous_tags<thingyA_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<thingyA_id> relate_in_array_get_left(ve::tagged_vector<relate_in_array_id> id) const noexcept {
			return ve::tagged_vector<thingyA_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_relate_in_array_set_left(relate_in_array_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_in_array( relate_in_array_id(relate_in_array_id::value_base_t(value.index())) );
				internal_move_relationship_relate_in_array(id, relate_in_array_id(relate_in_array_id::value_base_t(value.index())) );
			}
		}
		public:
		void relate_in_array_set_left(relate_in_array_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_in_array( relate_in_array_id(relate_in_array_id::value_base_t(value.index())) );
				internal_move_relationship_relate_in_array(id, relate_in_array_id(relate_in_array_id::value_base_t(value.index())) );
			} else {
				delete_relate_in_array(id);
			}
		}
		bool relate_in_array_try_set_left(relate_in_array_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				if(relate_in_array_is_valid( relate_in_array_id(relate_in_array_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_relate_in_array(id, relate_in_array_id(relate_in_array_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE thingyB_id relate_in_array_get_right(relate_in_array_id id) const noexcept {
			return relate_in_array.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_array_get_right(ve::contiguous_tags<relate_in_array_id> id) const noexcept {
			return ve::load(id, relate_in_array.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_array_get_right(ve::partial_contiguous_tags<relate_in_array_id> id) const noexcept {
			return ve::load(id, relate_in_array.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_array_get_right(ve::tagged_vector<relate_in_array_id> id) const noexcept {
			return ve::load(id, relate_in_array.m_right.vptr());
		}
		#endif
		private:
		void internal_relate_in_array_set_right(relate_in_array_id id, thingyB_id value) noexcept {
			if(auto old_value = relate_in_array.m_right.vptr()[id.index()]; bool(old_value)) {
				auto& vref = relate_in_array.m_array_right.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_in_array.right_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[value.index()], id);
			}
			relate_in_array.m_right.vptr()[id.index()] = value;
		}
		public:
		void relate_in_array_set_right(relate_in_array_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				delete_relate_in_array(id);
				return;
			}
			internal_relate_in_array_set_right(id, value);
		}
		bool relate_in_array_try_set_right(relate_in_array_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_in_array_set_right(id, value);
			return true;
		}
		DCON_RELEASE_INLINE bool relate_in_array_is_valid(relate_in_array_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_in_array.size_used && thingyA_is_valid(thingyA_id(thingyA_id::value_base_t(id.index()))) && (bool(relate_in_array.m_right.vptr()[id.index()]) || false);
		}
		
		uint32_t relate_in_array_size() const noexcept { return relate_in_array.size_used; }

		//
		// Functions for relate_in_list:
		//
		DCON_RELEASE_INLINE thingyA_id relate_in_list_get_left(relate_in_list_id id) const noexcept {
			return thingyA_id(thingyA_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<thingyA_id> relate_in_list_get_left(ve::contiguous_tags<relate_in_list_id> id) const noexcept {
			return ve::contiguous_tags<thingyA_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<thingyA_id> relate_in_list_get_left(ve::partial_contiguous_tags<relate_in_list_id> id) const noexcept {
			return ve::partial_contiguous_tags<thingyA_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<thingyA_id> relate_in_list_get_left(ve::tagged_vector<relate_in_list_id> id) const noexcept {
			return ve::tagged_vector<thingyA_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_relate_in_list_set_left(relate_in_list_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_in_list( relate_in_list_id(relate_in_list_id::value_base_t(value.index())) );
				internal_move_relationship_relate_in_list(id, relate_in_list_id(relate_in_list_id::value_base_t(value.index())) );
			}
		}
		public:
		void relate_in_list_set_left(relate_in_list_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				delete_relate_in_list( relate_in_list_id(relate_in_list_id::value_base_t(value.index())) );
				internal_move_relationship_relate_in_list(id, relate_in_list_id(relate_in_list_id::value_base_t(value.index())) );
			} else {
				delete_relate_in_list(id);
			}
		}
		bool relate_in_list_try_set_left(relate_in_list_id id, thingyA_id value) noexcept {
			if(bool(value)) {
				if(relate_in_list_is_valid( relate_in_list_id(relate_in_list_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_relate_in_list(id, relate_in_list_id(relate_in_list_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE thingyB_id relate_in_list_get_right(relate_in_list_id id) const noexcept {
			return relate_in_list.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_list_get_right(ve::contiguous_tags<relate_in_list_id> id) const noexcept {
			return ve::load(id, relate_in_list.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_list_get_right(ve::partial_contiguous_tags<relate_in_list_id> id) const noexcept {
			return ve::load(id, relate_in_list.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_in_list_get_right(ve::tagged_vector<relate_in_list_id> id) const noexcept {
			return ve::load(id, relate_in_list.m_right.vptr());
		}
		#endif
		private:
		void internal_relate_in_list_set_right(relate_in_list_id id, thingyB_id value) noexcept {
			if(auto old_value = relate_in_list.m_right.vptr()[id.index()]; bool(old_value)) {
				if(auto old_left = relate_in_list.m_link_right.vptr()[id.index()].left; bool(old_left)) {
					relate_in_list.m_link_right.vptr()[old_left.index()].right = relate_in_list.m_link_right.vptr()[id.index()].right;
				} else {
					relate_in_list.m_head_back_right.vptr()[old_value.index()] = relate_in_list.m_link_right.vptr()[id.index()].right;
				}
				if(auto old_right = relate_in_list.m_link_right.vptr()[id.index()].right; bool(old_right)) {
					relate_in_list.m_link_right.vptr()[old_right.index()].left = relate_in_list.m_link_right.vptr()[id.index()].left;
				}
			}
			if(bool(value)) {
				if(auto existing_list = relate_in_list.m_head_back_right.vptr()[value.index()]; bool(existing_list)) {
					relate_in_list.m_link_right.vptr()[id.index()].left = existing_list;
					if(auto r = relate_in_list.m_link_right.vptr()[existing_list.index()].right; bool(r)) {
						relate_in_list.m_link_right.vptr()[id.index()].right = r;
						relate_in_list.m_link_right.vptr()[r.index()].left = id;
					} else {
						relate_in_list.m_link_right.vptr()[id.index()].right = relate_in_list_id();
					}
					relate_in_list.m_link_right.vptr()[existing_list.index()].right = id;
					relate_in_list.m_head_back_right.vptr()[value.index()] = existing_list;
				} else {
					relate_in_list.m_head_back_right.vptr()[value.index()] = id;
					relate_in_list.m_link_right.vptr()[id.index()].right = relate_in_list_id();
					relate_in_list.m_link_right.vptr()[id.index()].left = relate_in_list_id();
				}
			} else {
				relate_in_list.m_link_right.vptr()[id.index()].right = relate_in_list_id();
				relate_in_list.m_link_right.vptr()[id.index()].left = relate_in_list_id();
			}
			relate_in_list.m_right.vptr()[id.index()] = value;
		}
		public:
		void relate_in_list_set_right(relate_in_list_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				delete_relate_in_list(id);
				return;
			}
			internal_relate_in_list_set_right(id, value);
		}
		bool relate_in_list_try_set_right(relate_in_list_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_in_list_set_right(id, value);
			return true;
		}
		DCON_RELEASE_INLINE bool relate_in_list_is_valid(relate_in_list_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_in_list.size_used && thingyA_is_valid(thingyA_id(thingyA_id::value_base_t(id.index()))) && (bool(relate_in_list.m_right.vptr()[id.index()]) || false);
		}
		
		uint32_t relate_in_list_size() const noexcept { return relate_in_list.size_used; }

		//
		// Functions for many_many:
		//
		DCON_RELEASE_INLINE thingyA_id many_many_get_A(many_many_id id) const noexcept {
			return many_many.m_A.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_A(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_A.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_A(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_A.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_A(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_A.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_A(many_many_id id, thingyA_id value) noexcept {
			many_many.m_A.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_A(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_A.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_A(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(value, many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ) != many_many.hashm_joint.end()) return false;
			many_many.m_A.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_B(many_many_id id) const noexcept {
			return many_many.m_B.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_B(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_B.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_B(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_B.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_B(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_B.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_B(many_many_id id, thingyA_id value) noexcept {
			many_many.m_B.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_B(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_B.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_B(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], value, many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ) != many_many.hashm_joint.end()) return false;
			many_many.m_B.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_C(many_many_id id) const noexcept {
			return many_many.m_C.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_C(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_C.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_C(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_C.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_C(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_C.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_C(many_many_id id, thingyA_id value) noexcept {
			many_many.m_C.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_C(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_C.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_C(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], value, many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ) != many_many.hashm_joint.end()) return false;
			many_many.m_C.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_D(many_many_id id) const noexcept {
			return many_many.m_D.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_D(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_D.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_D(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_D.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_D(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_D.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_D(many_many_id id, thingyA_id value) noexcept {
			many_many.m_D.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_D(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_D.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_D(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], value, many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ) != many_many.hashm_joint.end()) return false;
			many_many.m_D.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_E(many_many_id id) const noexcept {
			return many_many.m_E.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_E(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_E.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_E(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_E.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_E(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_E.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_E(many_many_id id, thingyA_id value) noexcept {
			many_many.m_E.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_E(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_E.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_E(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], value, many_many.m_F.vptr()[id.index()]) ) != many_many.hashm_joint.end()) return false;
			many_many.m_E.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_F(many_many_id id) const noexcept {
			return many_many.m_F.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_F(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_F.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_F(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_F.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_F(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_F.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_F(many_many_id id, thingyA_id value) noexcept {
			many_many.m_F.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_F(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) );
			many_many.m_F.vptr()[id.index()] = value;
			if(auto it = many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]) ); it != many_many.hashm_joint.end()) {
				delete_many_many(it->second);
			}
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
		}
		bool many_many_try_set_F(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(many_many.hashm_joint.find( many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], value) ) != many_many.hashm_joint.end()) return false;
			many_many.m_F.vptr()[id.index()] = value;
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(many_many.m_A.vptr()[id.index()], many_many.m_B.vptr()[id.index()], many_many.m_C.vptr()[id.index()], many_many.m_D.vptr()[id.index()], many_many.m_E.vptr()[id.index()], many_many.m_F.vptr()[id.index()]), id);
			return true;
		}
		DCON_RELEASE_INLINE thingyA_id many_many_get_ignore(many_many_id id) const noexcept {
			return many_many.m_ignore.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_ignore(ve::contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_ignore.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_ignore(ve::partial_contiguous_tags<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_ignore.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> many_many_get_ignore(ve::tagged_vector<many_many_id> id) const noexcept {
			return ve::load(id, many_many.m_ignore.vptr());
		}
		#endif
		private:
		DCON_RELEASE_INLINE void internal_many_many_set_ignore(many_many_id id, thingyA_id value) noexcept {
			many_many.m_ignore.vptr()[id.index()] = value;
		}
		public:
		void many_many_set_ignore(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_many_many(id);
				return;
			}
			many_many.m_ignore.vptr()[id.index()] = value;
		}
		bool many_many_try_set_ignore(many_many_id id, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			many_many.m_ignore.vptr()[id.index()] = value;
			return true;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void many_many_set_ignore(ve::contiguous_tags<many_many_id> id, ve::value_to_vector_type<thingyA_id> values) noexcept {
			ve::store(id, many_many.m_ignore.vptr(), values);
		}
		DCON_RELEASE_INLINE void many_many_set_ignore(ve::partial_contiguous_tags<many_many_id> id, ve::value_to_vector_type<thingyA_id> values) noexcept {
			ve::store(id, many_many.m_ignore.vptr(), values);
		}
		DCON_RELEASE_INLINE void many_many_set_ignore(ve::tagged_vector<many_many_id> id, ve::value_to_vector_type<thingyA_id> values) noexcept {
			ve::store(id, many_many.m_ignore.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE bool many_many_is_valid(many_many_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < many_many.size_used && many_many.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t many_many_size() const noexcept { return many_many.size_used; }

		//
		// Functions for relate_as_optional:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_optional_get_left(relate_as_optional_id id) const noexcept {
			return relate_as_optional.m_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_optional_get_left(ve::contiguous_tags<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_optional_get_left(ve::partial_contiguous_tags<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_optional_get_left(ve::tagged_vector<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_left.vptr());
		}
		#endif
		private:
		void internal_relate_as_optional_set_left(relate_as_optional_id id, thingyA_id value) noexcept {
			if(auto old_value = relate_as_optional.m_left.vptr()[id.index()]; bool(old_value)) {
				auto& vref = relate_as_optional.m_array_left.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_as_optional.left_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_optional.left_storage, relate_as_optional.m_array_left.vptr()[value.index()], id);
			}
			relate_as_optional.m_left.vptr()[id.index()] = value;
		}
		public:
		void relate_as_optional_set_left(relate_as_optional_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_relate_as_optional(id);
				return;
			}
			internal_relate_as_optional_set_left(id, value);
		}
		bool relate_as_optional_try_set_left(relate_as_optional_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_as_optional_set_left(id, value);
			return true;
		}
		DCON_RELEASE_INLINE thingyB_id relate_as_optional_get_right(relate_as_optional_id id) const noexcept {
			return relate_as_optional.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_optional_get_right(ve::contiguous_tags<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_optional_get_right(ve::partial_contiguous_tags<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_optional_get_right(ve::tagged_vector<relate_as_optional_id> id) const noexcept {
			return ve::load(id, relate_as_optional.m_right.vptr());
		}
		#endif
		private:
		void internal_relate_as_optional_set_right(relate_as_optional_id id, thingyB_id value) noexcept {
			if(auto old_value = relate_as_optional.m_right.vptr()[id.index()]; bool(old_value)) {
				auto& vref = relate_as_optional.m_array_right.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_as_optional.right_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_optional.right_storage, relate_as_optional.m_array_right.vptr()[value.index()], id);
			}
			relate_as_optional.m_right.vptr()[id.index()] = value;
		}
		public:
		void relate_as_optional_set_right(relate_as_optional_id id, thingyB_id value) noexcept {
			internal_relate_as_optional_set_right(id, value);
		}
		bool relate_as_optional_try_set_right(relate_as_optional_id id, thingyB_id value) noexcept {
			internal_relate_as_optional_set_right(id, value);
			return true;
		}
		DCON_RELEASE_INLINE bool relate_as_optional_is_valid(relate_as_optional_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_optional.size_used && relate_as_optional.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_optional_size() const noexcept { return relate_as_optional.size_used; }

		//
		// Functions for relate_as_non_optional:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_non_optional_get_left(relate_as_non_optional_id id) const noexcept {
			return relate_as_non_optional.m_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_non_optional_get_left(ve::contiguous_tags<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_non_optional_get_left(ve::partial_contiguous_tags<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyA_id> relate_as_non_optional_get_left(ve::tagged_vector<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_left.vptr());
		}
		#endif
		private:
		void internal_relate_as_non_optional_set_left(relate_as_non_optional_id id, thingyA_id value) noexcept {
			if(auto old_value = relate_as_non_optional.m_left.vptr()[id.index()]; bool(old_value)) {
				auto& vref = relate_as_non_optional.m_array_left.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_as_non_optional.left_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_non_optional.left_storage, relate_as_non_optional.m_array_left.vptr()[value.index()], id);
			}
			relate_as_non_optional.m_left.vptr()[id.index()] = value;
		}
		public:
		void relate_as_non_optional_set_left(relate_as_non_optional_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_relate_as_non_optional(id);
				return;
			}
			internal_relate_as_non_optional_set_left(id, value);
		}
		bool relate_as_non_optional_try_set_left(relate_as_non_optional_id id, thingyA_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_as_non_optional_set_left(id, value);
			return true;
		}
		DCON_RELEASE_INLINE thingyB_id relate_as_non_optional_get_right(relate_as_non_optional_id id) const noexcept {
			return relate_as_non_optional.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_non_optional_get_right(ve::contiguous_tags<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_non_optional_get_right(ve::partial_contiguous_tags<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingyB_id> relate_as_non_optional_get_right(ve::tagged_vector<relate_as_non_optional_id> id) const noexcept {
			return ve::load(id, relate_as_non_optional.m_right.vptr());
		}
		#endif
		private:
		void internal_relate_as_non_optional_set_right(relate_as_non_optional_id id, thingyB_id value) noexcept {
			if(auto old_value = relate_as_non_optional.m_right.vptr()[id.index()]; bool(old_value)) {
				auto& vref = relate_as_non_optional.m_array_right.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_as_non_optional.right_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_non_optional.right_storage, relate_as_non_optional.m_array_right.vptr()[value.index()], id);
			}
			relate_as_non_optional.m_right.vptr()[id.index()] = value;
		}
		public:
		void relate_as_non_optional_set_right(relate_as_non_optional_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				delete_relate_as_non_optional(id);
				return;
			}
			internal_relate_as_non_optional_set_right(id, value);
		}
		bool relate_as_non_optional_try_set_right(relate_as_non_optional_id id, thingyB_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_as_non_optional_set_right(id, value);
			return true;
		}
		DCON_RELEASE_INLINE bool relate_as_non_optional_is_valid(relate_as_non_optional_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_non_optional.size_used && relate_as_non_optional.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_non_optional_size() const noexcept { return relate_as_non_optional.size_used; }

		//
		// Functions for relate_as_multipleA:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_multipleA_get_left(relate_as_multipleA_id id, int32_t i) const noexcept {
			return relate_as_multipleA.m_left.vptr()[id.index()][i];
		}
		DCON_RELEASE_INLINE bool relate_as_multipleA_has_left(relate_as_multipleA_id id, thingyA_id v) const noexcept {
			if(relate_as_multipleA.m_left.vptr()[id.index()][0] == v) return true;
			if(relate_as_multipleA.m_left.vptr()[id.index()][1] == v) return true;
			return false;
		}
		private:
		void internal_relate_as_multipleA_set_left(relate_as_multipleA_id id, int32_t i, thingyA_id value) noexcept {
			if(auto old_value = relate_as_multipleA.m_left.vptr()[id.index()][i]; bool(old_value)) {
				auto& vref = relate_as_multipleA.m_array_left.vptr()[old_value.index()];
				dcon::remove_all_items(relate_as_multipleA.left_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_multipleA.left_storage, relate_as_multipleA.m_array_left.vptr()[value.index()], id);
			}
			relate_as_multipleA.m_left.vptr()[id.index()][i] = value;
		}
		public:
		void relate_as_multipleA_set_left(relate_as_multipleA_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_relate_as_multipleA(id);
				return;
			}
			relate_as_multipleA.hashm_joint.erase( relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[id.index()]) );
			internal_relate_as_multipleA_set_left(id, i, value);
			std::sort(relate_as_multipleA.m_left.vptr()[id.index()].begin(), relate_as_multipleA.m_left.vptr()[id.index()].end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			if(auto it = relate_as_multipleA.hashm_joint.find( relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[id.index()]) ); it != relate_as_multipleA.hashm_joint.end()) {
				delete_relate_as_multipleA(it->second);
			}
			relate_as_multipleA.hashm_joint.insert_or_assign(relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[id.index()]), id);
		}
		bool relate_as_multipleA_try_set_left(relate_as_multipleA_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			auto temp = relate_as_multipleA.m_left.vptr()[id.index()];
			temp[i] = value;
			std::sort(temp.begin(), temp.end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			if(relate_as_multipleA.hashm_joint.find( relate_as_multipleA.to_joint_keydata(temp) ) != relate_as_multipleA.hashm_joint.end()) {
				return false;
			}
			internal_relate_as_multipleA_set_left(id, i, value);
			std::sort(relate_as_multipleA.m_left.vptr()[id.index()].begin(), relate_as_multipleA.m_left.vptr()[id.index()].end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			relate_as_multipleA.hashm_joint.insert_or_assign(relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[id.index()]), id);
			return true;
		}
		void relate_as_multipleA_replace_left(relate_as_multipleA_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleA.m_left.vptr()[id.index()][0] == oldvalue) {
				relate_as_multipleA_set_left(id, 0, newvalue);
				return;
			}
			if(relate_as_multipleA.m_left.vptr()[id.index()][1] == oldvalue) {
				relate_as_multipleA_set_left(id, 1, newvalue);
				return;
			}
		}
		bool relate_as_multipleA_try_replace_left(relate_as_multipleA_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleA.m_left.vptr()[id.index()][0] == oldvalue) {
				return relate_as_multipleA_try_set_left(id, 0, newvalue);
			}
			if(relate_as_multipleA.m_left.vptr()[id.index()][1] == oldvalue) {
				return relate_as_multipleA_try_set_left(id, 1, newvalue);
			}
			return false;
		}
		DCON_RELEASE_INLINE bool relate_as_multipleA_is_valid(relate_as_multipleA_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_multipleA.size_used && relate_as_multipleA.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_multipleA_size() const noexcept { return relate_as_multipleA.size_used; }

		//
		// Functions for relate_as_multipleB:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_multipleB_get_left(relate_as_multipleB_id id, int32_t i) const noexcept {
			return relate_as_multipleB.m_left.vptr()[id.index()][i];
		}
		DCON_RELEASE_INLINE bool relate_as_multipleB_has_left(relate_as_multipleB_id id, thingyA_id v) const noexcept {
			if(relate_as_multipleB.m_left.vptr()[id.index()][0] == v) return true;
			if(relate_as_multipleB.m_left.vptr()[id.index()][1] == v) return true;
			return false;
		}
		private:
		void internal_relate_as_multipleB_set_left(relate_as_multipleB_id id, int32_t i, thingyA_id value) noexcept {
			if(auto old_value = relate_as_multipleB.m_left.vptr()[id.index()][i]; bool(old_value)) {
				relate_as_multipleB.m_link_back_left.vptr()[old_value.index()] = relate_as_multipleB_id();
			}
			if(bool(value)) {
				if(auto old_rel = relate_as_multipleB.m_link_back_left.vptr()[value.index()]; bool(old_rel)) {
					delete_relate_as_multipleB(old_rel);
				}
				relate_as_multipleB.m_link_back_left.vptr()[value.index()] = id;
			}
			relate_as_multipleB.m_left.vptr()[id.index()][i] = value;
		}
		public:
		void relate_as_multipleB_set_left(relate_as_multipleB_id id, int32_t i, thingyA_id value) noexcept {
			if(auto old_value = relate_as_multipleB.m_left.vptr()[id.index()][i]; bool(old_value)) {
				relate_as_multipleB.m_link_back_left.vptr()[old_value.index()] = relate_as_multipleB_id();
			}
			if(relate_as_multipleB_has_left(id, value)) value = thingyA_id();
			if(bool(value)) {
				if(auto old_rel = relate_as_multipleB.m_link_back_left.vptr()[value.index()]; bool(old_rel)) {
					delete_relate_as_multipleB(old_rel);
				}
				relate_as_multipleB.m_link_back_left.vptr()[value.index()] = id;
				relate_as_multipleB.m_left.vptr()[id.index()][i] = value;
			} else {
				delete_relate_as_multipleB(id);
			}
		}
		void relate_as_multipleB_replace_left(relate_as_multipleB_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleB.m_left.vptr()[id.index()][0] == oldvalue) {
				relate_as_multipleB_set_left(id, 0, newvalue);
				return;
			}
			if(relate_as_multipleB.m_left.vptr()[id.index()][1] == oldvalue) {
				relate_as_multipleB_set_left(id, 1, newvalue);
				return;
			}
		}
		bool relate_as_multipleB_try_set_left(relate_as_multipleB_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) return false;
			if(relate_as_multipleB_has_left(id, value)) return false;
			if(bool(value)) {
				if(auto old_rel = relate_as_multipleB.m_link_back_left.vptr()[value.index()]; bool(old_rel)) {
					return false;
				}
				relate_as_multipleB.m_link_back_left.vptr()[value.index()] = id;
			}
			if(auto old_value = relate_as_multipleB.m_left.vptr()[id.index()][i]; bool(old_value)) {
				relate_as_multipleB.m_link_back_left.vptr()[old_value.index()] = relate_as_multipleB_id();
			}
			relate_as_multipleB.m_left.vptr()[id.index()][i] = value;
			return true;
		}
		bool relate_as_multipleB_try_replace_left(relate_as_multipleB_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleB.m_left.vptr()[id.index()][0] == oldvalue) {
				return relate_as_multipleB_try_set_left(id, 0, newvalue);
			}
			if(relate_as_multipleB.m_left.vptr()[id.index()][1] == oldvalue) {
				return relate_as_multipleB_try_set_left(id, 1, newvalue);
			}
			return false;
		}
		DCON_RELEASE_INLINE bool relate_as_multipleB_is_valid(relate_as_multipleB_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_multipleB.size_used && relate_as_multipleB.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_multipleB_size() const noexcept { return relate_as_multipleB.size_used; }

		//
		// Functions for relate_as_multipleC:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_multipleC_get_left(relate_as_multipleC_id id, int32_t i) const noexcept {
			return relate_as_multipleC.m_left.vptr()[id.index()][i];
		}
		DCON_RELEASE_INLINE bool relate_as_multipleC_has_left(relate_as_multipleC_id id, thingyA_id v) const noexcept {
			if(relate_as_multipleC.m_left.vptr()[id.index()][0] == v) return true;
			if(relate_as_multipleC.m_left.vptr()[id.index()][1] == v) return true;
			return false;
		}
		private:
		void internal_relate_as_multipleC_set_left(relate_as_multipleC_id id, int32_t i, thingyA_id value) noexcept {
			if(auto old_value = relate_as_multipleC.m_left.vptr()[id.index()][i]; bool(old_value)) {
				auto& vref = relate_as_multipleC.m_array_left.vptr()[old_value.index()];
				dcon::remove_unique_item(relate_as_multipleC.left_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(relate_as_multipleC.left_storage, relate_as_multipleC.m_array_left.vptr()[value.index()], id);
			}
			relate_as_multipleC.m_left.vptr()[id.index()][i] = value;
		}
		public:
		void relate_as_multipleC_set_left(relate_as_multipleC_id id, int32_t i, thingyA_id value) noexcept {
			if(relate_as_multipleC_has_left(id, value)) value = thingyA_id();
			if(!bool(value)) {
				delete_relate_as_multipleC(id);
				return;
			}
			internal_relate_as_multipleC_set_left(id, i, value);
		}
		bool relate_as_multipleC_try_set_left(relate_as_multipleC_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			if(relate_as_multipleC_has_left(id, value)) return false;
			internal_relate_as_multipleC_set_left(id, i, value);
			return true;
		}
		void relate_as_multipleC_replace_left(relate_as_multipleC_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleC.m_left.vptr()[id.index()][0] == oldvalue) {
				relate_as_multipleC_set_left(id, 0, newvalue);
				return;
			}
			if(relate_as_multipleC.m_left.vptr()[id.index()][1] == oldvalue) {
				relate_as_multipleC_set_left(id, 1, newvalue);
				return;
			}
		}
		bool relate_as_multipleC_try_replace_left(relate_as_multipleC_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleC.m_left.vptr()[id.index()][0] == oldvalue) {
				return relate_as_multipleC_try_set_left(id, 0, newvalue);
			}
			if(relate_as_multipleC.m_left.vptr()[id.index()][1] == oldvalue) {
				return relate_as_multipleC_try_set_left(id, 1, newvalue);
			}
			return false;
		}
		DCON_RELEASE_INLINE bool relate_as_multipleC_is_valid(relate_as_multipleC_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_multipleC.size_used && relate_as_multipleC.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_multipleC_size() const noexcept { return relate_as_multipleC.size_used; }

		//
		// Functions for relate_as_multipleD:
		//
		DCON_RELEASE_INLINE thingyA_id relate_as_multipleD_get_left(relate_as_multipleD_id id, int32_t i) const noexcept {
			return relate_as_multipleD.m_left.vptr()[id.index()][i];
		}
		DCON_RELEASE_INLINE bool relate_as_multipleD_has_left(relate_as_multipleD_id id, thingyA_id v) const noexcept {
			if(relate_as_multipleD.m_left.vptr()[id.index()][0] == v) return true;
			if(relate_as_multipleD.m_left.vptr()[id.index()][1] == v) return true;
			return false;
		}
		private:
		DCON_RELEASE_INLINE void internal_relate_as_multipleD_set_left(relate_as_multipleD_id id, int32_t i, thingyA_id value) noexcept {
			relate_as_multipleD.m_left.vptr()[id.index()][i] = value;
		}
		public:
		void relate_as_multipleD_set_left(relate_as_multipleD_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) {
				delete_relate_as_multipleD(id);
				return;
			}
			internal_relate_as_multipleD_set_left(id, i, value);
		}
		bool relate_as_multipleD_try_set_left(relate_as_multipleD_id id, int32_t i, thingyA_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_relate_as_multipleD_set_left(id, i, value);
			return true;
		}
		void relate_as_multipleD_replace_left(relate_as_multipleD_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleD.m_left.vptr()[id.index()][0] == oldvalue) {
				relate_as_multipleD_set_left(id, 0, newvalue);
				return;
			}
			if(relate_as_multipleD.m_left.vptr()[id.index()][1] == oldvalue) {
				relate_as_multipleD_set_left(id, 1, newvalue);
				return;
			}
		}
		bool relate_as_multipleD_try_replace_left(relate_as_multipleD_id id, thingyA_id newvalue, thingyA_id oldvalue) noexcept {
			if(relate_as_multipleD.m_left.vptr()[id.index()][0] == oldvalue) {
				return relate_as_multipleD_try_set_left(id, 0, newvalue);
			}
			if(relate_as_multipleD.m_left.vptr()[id.index()][1] == oldvalue) {
				return relate_as_multipleD_try_set_left(id, 1, newvalue);
			}
			return false;
		}
		DCON_RELEASE_INLINE bool relate_as_multipleD_is_valid(relate_as_multipleD_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < relate_as_multipleD.size_used && relate_as_multipleD.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t relate_as_multipleD_size() const noexcept { return relate_as_multipleD.size_used; }


		//
		// container pop_back for thingyA
		//
		void pop_back_thingyA() {
			if(thingyA.size_used == 0) return;
			thingyA_id id_removed(thingyA_id::value_base_t(thingyA.size_used - 1));
			delete_relate_same(relate_same_id(relate_same_id::value_base_t(id_removed.index())));
			relate_same.size_used = thingyA.size_used - 1;
			delete_relate_in_array(relate_in_array_id(relate_in_array_id::value_base_t(id_removed.index())));
			relate_in_array.size_used = thingyA.size_used - 1;
			delete_relate_in_list(relate_in_list_id(relate_in_list_id::value_base_t(id_removed.index())));
			relate_in_list.size_used = thingyA.size_used - 1;
			thingyA_remove_all_relate_as_optional_as_left(id_removed);
			thingyA_remove_all_relate_as_non_optional_as_left(id_removed);
			thingyA_remove_all_relate_as_multipleA_as_left(id_removed);
			thingyA_remove_relate_as_multipleB_as_left(id_removed);
			thingyA_remove_all_relate_as_multipleC_as_left(id_removed);
			thingyA.m_some_value.vptr()[id_removed.index()] = int32_t{};
			--thingyA.size_used;
		}
		
		//
		// container resize for thingyA
		//
		void thingyA_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = thingyA.size_used;
			if(new_size < old_size) {
				std::fill_n(thingyA.m_some_value.vptr() + new_size, old_size - new_size, int32_t{});
				relate_same_resize(std::min(new_size, relate_same.size_used));
				relate_in_array_resize(std::min(new_size, relate_in_array.size_used));
				relate_in_list_resize(std::min(new_size, relate_in_list.size_used));
				relate_as_optional_resize(0);
				relate_as_non_optional_resize(0);
				relate_as_multipleA_resize(0);
				relate_as_multipleB_resize(0);
				relate_as_multipleC_resize(0);
			} else if(new_size > old_size) {
			}
			thingyA.size_used = new_size;
		}
		
		//
		// container create for thingyA
		//
		thingyA_id create_thingyA() {
			thingyA_id new_id(thingyA_id::value_base_t(thingyA.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(thingyA.size_used >= 1200) std::abort();
			#else
			if(thingyA.size_used >= 1200) throw dcon::out_of_space{};
			#endif
			relate_same.size_used = thingyA.size_used + 1;
			relate_in_array.size_used = thingyA.size_used + 1;
			relate_in_list.size_used = thingyA.size_used + 1;
			++thingyA.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for thingyA
		//
		void delete_thingyA(thingyA_id id) {
			thingyA_id id_removed = id;
			thingyA_id last_id(thingyA_id::value_base_t(thingyA.size_used - 1));
			if(id_removed == last_id) { pop_back_thingyA(); return; }
			delete_relate_same(relate_same_id(relate_same_id::value_base_t(id_removed.index())));
			internal_move_relationship_relate_same(relate_same_id(relate_same_id::value_base_t(last_id.index())), relate_same_id(relate_same_id::value_base_t(id_removed.index())));
			relate_same.size_used = thingyA.size_used - 1;
			delete_relate_in_array(relate_in_array_id(relate_in_array_id::value_base_t(id_removed.index())));
			internal_move_relationship_relate_in_array(relate_in_array_id(relate_in_array_id::value_base_t(last_id.index())), relate_in_array_id(relate_in_array_id::value_base_t(id_removed.index())));
			relate_in_array.size_used = thingyA.size_used - 1;
			delete_relate_in_list(relate_in_list_id(relate_in_list_id::value_base_t(id_removed.index())));
			internal_move_relationship_relate_in_list(relate_in_list_id(relate_in_list_id::value_base_t(last_id.index())), relate_in_list_id(relate_in_list_id::value_base_t(id_removed.index())));
			relate_in_list.size_used = thingyA.size_used - 1;
			thingyA_remove_all_relate_as_optional_as_left(id_removed);
			thingyA_for_each_relate_as_optional_as_left(last_id, [this, id_removed, last_id](relate_as_optional_id i) {
				relate_as_optional.m_left.vptr()[i.index()] = id_removed;
			} );
			relate_as_optional.left_storage.release(relate_as_optional.m_array_left.vptr()[id_removed.index()]);
			relate_as_optional.m_array_left.vptr()[id_removed.index()] = std::move(relate_as_optional.m_array_left.vptr()[last_id.index()]);
			relate_as_optional.m_array_left.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingyA_remove_all_relate_as_non_optional_as_left(id_removed);
			thingyA_for_each_relate_as_non_optional_as_left(last_id, [this, id_removed, last_id](relate_as_non_optional_id i) {
				relate_as_non_optional.m_left.vptr()[i.index()] = id_removed;
			} );
			relate_as_non_optional.left_storage.release(relate_as_non_optional.m_array_left.vptr()[id_removed.index()]);
			relate_as_non_optional.m_array_left.vptr()[id_removed.index()] = std::move(relate_as_non_optional.m_array_left.vptr()[last_id.index()]);
			relate_as_non_optional.m_array_left.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingyA_remove_all_relate_as_multipleA_as_left(id_removed);
			thingyA_for_each_relate_as_multipleA_as_left(last_id, [this, id_removed, last_id](relate_as_multipleA_id i) {
				relate_as_multipleA.hashm_joint.erase(relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[i.index()]));
				if(relate_as_multipleA.m_left.vptr()[i.index()][0] == last_id) relate_as_multipleA.m_left.vptr()[i.index()][0] = id_removed;
				if(relate_as_multipleA.m_left.vptr()[i.index()][1] == last_id) relate_as_multipleA.m_left.vptr()[i.index()][1] = id_removed;
				std::sort(relate_as_multipleA.m_left.vptr()[i.index()].begin(), relate_as_multipleA.m_left.vptr()[i.index()].end(), [](thingyA_id l, thingyA_id r){ return l.value < r.value; });
				relate_as_multipleA.hashm_joint.insert_or_assign(relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[i.index()]), i);
			} );
			relate_as_multipleA.left_storage.release(relate_as_multipleA.m_array_left.vptr()[id_removed.index()]);
			relate_as_multipleA.m_array_left.vptr()[id_removed.index()] = std::move(relate_as_multipleA.m_array_left.vptr()[last_id.index()]);
			relate_as_multipleA.m_array_left.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingyA_remove_relate_as_multipleB_as_left(id_removed);
			if(auto bk = relate_as_multipleB.m_link_back_left.vptr()[last_id.index()]; bool(bk)) {
				if(relate_as_multipleB.m_left.vptr()[bk.index()][0] == last_id) relate_as_multipleB.m_left.vptr()[bk.index()][0] = id_removed;
				if(relate_as_multipleB.m_left.vptr()[bk.index()][1] == last_id) relate_as_multipleB.m_left.vptr()[bk.index()][1] = id_removed;
			}
			relate_as_multipleB.m_link_back_left.vptr()[id_removed.index()] = std::move(relate_as_multipleB.m_link_back_left.vptr()[last_id.index()]);
			relate_as_multipleB.m_link_back_left.vptr()[last_id.index()] = relate_as_multipleB_id();
			thingyA_remove_all_relate_as_multipleC_as_left(id_removed);
			thingyA_for_each_relate_as_multipleC_as_left(last_id, [this, id_removed, last_id](relate_as_multipleC_id i) {
				if(relate_as_multipleC.m_left.vptr()[i.index()][0] == last_id) relate_as_multipleC.m_left.vptr()[i.index()][0] = id_removed;
				if(relate_as_multipleC.m_left.vptr()[i.index()][1] == last_id) relate_as_multipleC.m_left.vptr()[i.index()][1] = id_removed;
			} );
			relate_as_multipleC.left_storage.release(relate_as_multipleC.m_array_left.vptr()[id_removed.index()]);
			relate_as_multipleC.m_array_left.vptr()[id_removed.index()] = std::move(relate_as_multipleC.m_array_left.vptr()[last_id.index()]);
			relate_as_multipleC.m_array_left.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingyA.m_some_value.vptr()[id_removed.index()] = std::move(thingyA.m_some_value.vptr()[last_id.index()]);
			thingyA.m_some_value.vptr()[last_id.index()] = int32_t{};
			--thingyA.size_used;
		}
		
		//
		// container delete for thingyB
		//
		void delete_thingyB(thingyB_id id_removed) {
			if(!thingyB_is_valid(id_removed)) return;
			thingyB.m__index.vptr()[id_removed.index()] = thingyB.first_free;
			thingyB.first_free = id_removed;
			if(int32_t(thingyB.size_used) - 1 == id_removed.index()) {
				for( ; thingyB.size_used > 0 && thingyB.m__index.vptr()[thingyB.size_used - 1] != thingyB_id(thingyB_id::value_base_t(thingyB.size_used - 1));  --thingyB.size_used) ;
			}
			thingyB_remove_all_relate_in_array_as_right(id_removed);
			thingyB_remove_all_relate_in_list_as_right(id_removed);
			thingyB_remove_all_relate_as_optional_as_right(id_removed);
			thingyB_remove_all_relate_as_non_optional_as_right(id_removed);
			thingyB.m_some_value.vptr()[id_removed.index()] = int32_t{};
		}
		
		//
		// container create for thingyB
		//
		thingyB_id create_thingyB() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(thingyB.first_free)) std::abort();
			#else
			if(!bool(thingyB.first_free)) throw dcon::out_of_space{};
			#endif
			thingyB_id new_id = thingyB.first_free;
			thingyB.first_free = thingyB.m__index.vptr()[thingyB.first_free.index()];
			thingyB.m__index.vptr()[new_id.index()] = new_id;
			thingyB.size_used = std::max(thingyB.size_used, uint32_t(new_id.index() + 1));
			return new_id;
		}
		
		//
		// container resize for thingyB
		//
		void thingyB_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = thingyB.size_used;
			if(new_size < old_size) {
				thingyB.first_free = thingyB_id();
				int32_t i = int32_t(1200 - 1);
				for(; i >= int32_t(new_size); --i) {
					thingyB.m__index.vptr()[i] = thingyB.first_free;
					thingyB.first_free = thingyB_id(thingyB_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(thingyB.m__index.vptr()[i] != thingyB_id(thingyB_id::value_base_t(i))) {
						thingyB.m__index.vptr()[i] = thingyB.first_free;
						thingyB.first_free = thingyB_id(thingyB_id::value_base_t(i));
					}
				}
				std::fill_n(thingyB.m_some_value.vptr() + new_size, old_size - new_size, int32_t{});
				relate_in_array_resize(0);
				relate_in_list_resize(0);
				relate_as_optional_resize(0);
				relate_as_non_optional_resize(0);
			} else if(new_size > old_size) {
				thingyB.first_free = thingyB_id();
				int32_t i = int32_t(1200 - 1);
				for(; i >= int32_t(old_size); --i) {
					thingyB.m__index.vptr()[i] = thingyB.first_free;
					thingyB.first_free = thingyB_id(thingyB_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(thingyB.m__index.vptr()[i] != thingyB_id(thingyB_id::value_base_t(i))) {
						thingyB.m__index.vptr()[i] = thingyB.first_free;
						thingyB.first_free = thingyB_id(thingyB_id::value_base_t(i));
					}
				}
			}
			thingyB.size_used = new_size;
		}
		
		//
		// container resize for relate_same
		//
		void relate_same_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_same.size_used;
			if(new_size < old_size) {
				relate_same.hashm_joint.clear();
				std::fill_n(relate_same.m_right.vptr() + 0, old_size, thingyA_id{});
			} else if(new_size > old_size) {
			}
			relate_same.size_used = new_size;
		}
		
		//
		// container delete for relate_same
		//
		void delete_relate_same(relate_same_id id_removed) {
			relate_same.hashm_joint.erase( relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id_removed.index())), relate_same.m_right.vptr()[id_removed.index()]) );
			internal_relate_same_set_right(id_removed, thingyA_id());
		}
		
		//
		// container pop_back for relate_same
		//
		void pop_back_relate_same() {
			if(relate_same.size_used == 0) return;
			relate_same_id id_removed(relate_same_id::value_base_t(relate_same.size_used - 1));
			relate_same.hashm_joint.erase( relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id_removed.index())), relate_same.m_right.vptr()[id_removed.index()]) );
			internal_relate_same_set_right(id_removed, thingyA_id());
			--relate_same.size_used;
		}
		
		private:
		//
		// container move relationship for relate_same
		//
		void internal_move_relationship_relate_same(relate_same_id last_id, relate_same_id id_removed) {
			relate_same.hashm_joint.erase(relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(last_id.index())), relate_same.m_right.vptr()[last_id.index()]));
			internal_relate_same_set_right(id_removed, thingyA_id());
			relate_same.m_right.vptr()[id_removed.index()] = std::move(relate_same.m_right.vptr()[last_id.index()]);
			relate_same.m_right.vptr()[last_id.index()] = thingyA_id();
			relate_same.hashm_joint.erase(relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(last_id.index())), relate_same.m_right.vptr()[id_removed.index()]));
			relate_same.hashm_joint.insert_or_assign(relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(id_removed.index())), relate_same.m_right.vptr()[id_removed.index()]), id_removed);
		}
		
		public:
		//
		// container try create relationship for relate_same
		//
		relate_same_id try_create_relate_same(thingyA_id left_p, thingyA_id right_p) {
			if(!bool(left_p)) return relate_same_id();
			if(relate_same_is_valid(relate_same_id(relate_same_id::value_base_t(left_p.index())))) return relate_same_id();
			if(!bool(right_p)) return relate_same_id();
			relate_same_id new_id(relate_same_id::value_base_t(left_p.index()));
			if(relate_same.size_used < uint32_t(left_p.value)) relate_same_resize(uint32_t(left_p.value));
			internal_relate_same_set_right(new_id, right_p);
			relate_same.hashm_joint.insert_or_assign(relate_same.to_joint_keydata(left_p, right_p), new_id);
			return new_id;
		}
		
		//
		// container force create relationship for relate_same
		//
		relate_same_id force_create_relate_same(thingyA_id left_p, thingyA_id right_p) {
			relate_same_id new_id(relate_same_id::value_base_t(left_p.index()));
			if(relate_same.size_used < uint32_t(left_p.value)) relate_same_resize(uint32_t(left_p.value));
			 {
				auto key_dat = relate_same.to_joint_keydata(left_p, right_p);
				if(auto it = relate_same.hashm_joint.find(key_dat); it !=  relate_same.hashm_joint.end()) {
					delete_relate_same(it->second);
				}
				relate_same.hashm_joint.insert_or_assign(key_dat, new_id);
			}
			internal_relate_same_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container resize for relate_in_array
		//
		void relate_in_array_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_in_array.size_used;
			if(new_size < old_size) {
				std::fill_n(relate_in_array.m_right.vptr() + 0, old_size, thingyB_id{});
				std::for_each(relate_in_array.m_array_right.vptr() + 0, relate_in_array.m_array_right.vptr() + 0 + thingyB.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_in_array.right_storage.release(i); });
			} else if(new_size > old_size) {
			}
			relate_in_array.size_used = new_size;
		}
		
		//
		// container delete for relate_in_array
		//
		void delete_relate_in_array(relate_in_array_id id_removed) {
			internal_relate_in_array_set_right(id_removed, thingyB_id());
		}
		
		//
		// container pop_back for relate_in_array
		//
		void pop_back_relate_in_array() {
			if(relate_in_array.size_used == 0) return;
			relate_in_array_id id_removed(relate_in_array_id::value_base_t(relate_in_array.size_used - 1));
			internal_relate_in_array_set_right(id_removed, thingyB_id());
			--relate_in_array.size_used;
		}
		
		private:
		//
		// container move relationship for relate_in_array
		//
		void internal_move_relationship_relate_in_array(relate_in_array_id last_id, relate_in_array_id id_removed) {
			internal_relate_in_array_set_right(id_removed, thingyB_id());
			if(auto tmp = relate_in_array.m_right.vptr()[last_id.index()]; bool(tmp)) {
				dcon::replace_unique_item(relate_in_array.right_storage, relate_in_array.m_array_right.vptr()[tmp.index()], last_id, id_removed);
			}
			relate_in_array.m_right.vptr()[id_removed.index()] = std::move(relate_in_array.m_right.vptr()[last_id.index()]);
			relate_in_array.m_right.vptr()[last_id.index()] = thingyB_id();
		}
		
		public:
		//
		// container try create relationship for relate_in_array
		//
		relate_in_array_id try_create_relate_in_array(thingyA_id left_p, thingyB_id right_p) {
			if(!bool(left_p)) return relate_in_array_id();
			if(relate_in_array_is_valid(relate_in_array_id(relate_in_array_id::value_base_t(left_p.index())))) return relate_in_array_id();
			if(!bool(right_p)) return relate_in_array_id();
			relate_in_array_id new_id(relate_in_array_id::value_base_t(left_p.index()));
			if(relate_in_array.size_used < uint32_t(left_p.value)) relate_in_array_resize(uint32_t(left_p.value));
			internal_relate_in_array_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container force create relationship for relate_in_array
		//
		relate_in_array_id force_create_relate_in_array(thingyA_id left_p, thingyB_id right_p) {
			relate_in_array_id new_id(relate_in_array_id::value_base_t(left_p.index()));
			if(relate_in_array.size_used < uint32_t(left_p.value)) relate_in_array_resize(uint32_t(left_p.value));
			internal_relate_in_array_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container resize for relate_in_list
		//
		void relate_in_list_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_in_list.size_used;
			if(new_size < old_size) {
				std::fill_n(relate_in_list.m_right.vptr() + 0, old_size, thingyB_id{});
				std::fill_n(relate_in_list.m_link_right.vptr() + 0, old_size, relate_in_list_id_pair{});
				std::fill_n(relate_in_list.m_head_back_right.vptr() + 0, thingyB.size_used, relate_in_list_id{});
			} else if(new_size > old_size) {
			}
			relate_in_list.size_used = new_size;
		}
		
		//
		// container delete for relate_in_list
		//
		void delete_relate_in_list(relate_in_list_id id_removed) {
			internal_relate_in_list_set_right(id_removed, thingyB_id());
		}
		
		//
		// container pop_back for relate_in_list
		//
		void pop_back_relate_in_list() {
			if(relate_in_list.size_used == 0) return;
			relate_in_list_id id_removed(relate_in_list_id::value_base_t(relate_in_list.size_used - 1));
			internal_relate_in_list_set_right(id_removed, thingyB_id());
			--relate_in_list.size_used;
		}
		
		private:
		//
		// container move relationship for relate_in_list
		//
		void internal_move_relationship_relate_in_list(relate_in_list_id last_id, relate_in_list_id id_removed) {
			internal_relate_in_list_set_right(id_removed, thingyB_id());
			if(bool(relate_in_list.m_right.vptr()[last_id.index()])) {
				auto tmp = relate_in_list.m_link_right.vptr()[last_id.index()];
				if(bool(tmp.left)) {
					relate_in_list.m_link_right.vptr()[tmp.left.index()].right = id_removed;
				} else {
					for(auto lpos = last_id; bool(lpos); lpos = relate_in_list.m_link_right.vptr()[lpos.index()].right) {
						relate_in_list.m_head_back_right.vptr()[relate_in_list.m_right.vptr()[lpos.index()].index()] = id_removed;
					}
				}
				if(bool(tmp.right)) {
					relate_in_list.m_link_right.vptr()[tmp.right.index()].left = id_removed;
				}
			}
			relate_in_list.m_link_right.vptr()[id_removed.index()] = std::move(relate_in_list.m_link_right.vptr()[last_id.index()]);
			relate_in_list.m_link_right.vptr()[last_id.index()] = relate_in_list_id_pair();
			relate_in_list.m_right.vptr()[id_removed.index()] = std::move(relate_in_list.m_right.vptr()[last_id.index()]);
			relate_in_list.m_right.vptr()[last_id.index()] = thingyB_id();
		}
		
		public:
		//
		// container try create relationship for relate_in_list
		//
		relate_in_list_id try_create_relate_in_list(thingyA_id left_p, thingyB_id right_p) {
			if(!bool(left_p)) return relate_in_list_id();
			if(relate_in_list_is_valid(relate_in_list_id(relate_in_list_id::value_base_t(left_p.index())))) return relate_in_list_id();
			if(!bool(right_p)) return relate_in_list_id();
			relate_in_list_id new_id(relate_in_list_id::value_base_t(left_p.index()));
			if(relate_in_list.size_used < uint32_t(left_p.value)) relate_in_list_resize(uint32_t(left_p.value));
			internal_relate_in_list_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container force create relationship for relate_in_list
		//
		relate_in_list_id force_create_relate_in_list(thingyA_id left_p, thingyB_id right_p) {
			relate_in_list_id new_id(relate_in_list_id::value_base_t(left_p.index()));
			if(relate_in_list.size_used < uint32_t(left_p.value)) relate_in_list_resize(uint32_t(left_p.value));
			internal_relate_in_list_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container delete for many_many
		//
		void delete_many_many(many_many_id id_removed) {
			if(!many_many_is_valid(id_removed)) return;
			many_many.m__index.vptr()[id_removed.index()] = many_many.first_free;
			many_many.first_free = id_removed;
			if(int32_t(many_many.size_used) - 1 == id_removed.index()) {
				for( ; many_many.size_used > 0 && many_many.m__index.vptr()[many_many.size_used - 1] != many_many_id(many_many_id::value_base_t(many_many.size_used - 1));  --many_many.size_used) ;
			}
			many_many.hashm_joint.erase( many_many.to_joint_keydata(many_many.m_A.vptr()[id_removed.index()], many_many.m_B.vptr()[id_removed.index()], many_many.m_C.vptr()[id_removed.index()], many_many.m_D.vptr()[id_removed.index()], many_many.m_E.vptr()[id_removed.index()], many_many.m_F.vptr()[id_removed.index()]) );
			internal_many_many_set_A(id_removed, thingyA_id());
			internal_many_many_set_B(id_removed, thingyA_id());
			internal_many_many_set_C(id_removed, thingyA_id());
			internal_many_many_set_D(id_removed, thingyA_id());
			internal_many_many_set_E(id_removed, thingyA_id());
			internal_many_many_set_F(id_removed, thingyA_id());
			internal_many_many_set_ignore(id_removed, thingyA_id());
		}
		
		//
		// container resize for many_many
		//
		void many_many_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 200) std::abort();
			#else
			if(new_size > 200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = many_many.size_used;
			if(new_size < old_size) {
				many_many.first_free = many_many_id();
				int32_t i = int32_t(200 - 1);
				for(; i >= int32_t(new_size); --i) {
					many_many.m__index.vptr()[i] = many_many.first_free;
					many_many.first_free = many_many_id(many_many_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(many_many.m__index.vptr()[i] != many_many_id(many_many_id::value_base_t(i))) {
						many_many.m__index.vptr()[i] = many_many.first_free;
						many_many.first_free = many_many_id(many_many_id::value_base_t(i));
					}
				}
				many_many.hashm_joint.clear();
				std::fill_n(many_many.m_A.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_B.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_C.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_D.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_E.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_F.vptr() + 0, old_size, thingyA_id{});
				std::fill_n(many_many.m_ignore.vptr() + 0, old_size, thingyA_id{});
			} else if(new_size > old_size) {
				many_many.first_free = many_many_id();
				int32_t i = int32_t(200 - 1);
				for(; i >= int32_t(old_size); --i) {
					many_many.m__index.vptr()[i] = many_many.first_free;
					many_many.first_free = many_many_id(many_many_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(many_many.m__index.vptr()[i] != many_many_id(many_many_id::value_base_t(i))) {
						many_many.m__index.vptr()[i] = many_many.first_free;
						many_many.first_free = many_many_id(many_many_id::value_base_t(i));
					}
				}
			}
			many_many.size_used = new_size;
		}
		
		//
		// container try create relationship for many_many
		//
		many_many_id try_create_many_many(thingyA_id A_p, thingyA_id B_p, thingyA_id C_p, thingyA_id D_p, thingyA_id E_p, thingyA_id F_p, thingyA_id ignore_p) {
			if(!bool(A_p)) return many_many_id();
			if(!bool(B_p)) return many_many_id();
			if(!bool(C_p)) return many_many_id();
			if(!bool(D_p)) return many_many_id();
			if(!bool(E_p)) return many_many_id();
			if(!bool(F_p)) return many_many_id();
			if(!bool(ignore_p)) return many_many_id();
			if(many_many.hashm_joint.contains(many_many.to_joint_keydata(A_p, B_p, C_p, D_p, E_p, F_p))) return many_many_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(many_many.first_free)) std::abort();
			#else
			if(!bool(many_many.first_free)) throw dcon::out_of_space{};
			#endif
			many_many_id new_id = many_many.first_free;
			many_many.first_free = many_many.m__index.vptr()[many_many.first_free.index()];
			many_many.m__index.vptr()[new_id.index()] = new_id;
			many_many.size_used = std::max(many_many.size_used, uint32_t(new_id.index() + 1));
			internal_many_many_set_A(new_id, A_p);
			internal_many_many_set_B(new_id, B_p);
			internal_many_many_set_C(new_id, C_p);
			internal_many_many_set_D(new_id, D_p);
			internal_many_many_set_E(new_id, E_p);
			internal_many_many_set_F(new_id, F_p);
			internal_many_many_set_ignore(new_id, ignore_p);
			many_many.hashm_joint.insert_or_assign(many_many.to_joint_keydata(A_p, B_p, C_p, D_p, E_p, F_p), new_id);
			return new_id;
		}
		
		//
		// container force create relationship for many_many
		//
		many_many_id force_create_many_many(thingyA_id A_p, thingyA_id B_p, thingyA_id C_p, thingyA_id D_p, thingyA_id E_p, thingyA_id F_p, thingyA_id ignore_p) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(many_many.first_free)) std::abort();
			#else
			if(!bool(many_many.first_free)) throw dcon::out_of_space{};
			#endif
			many_many_id new_id = many_many.first_free;
			many_many.first_free = many_many.m__index.vptr()[many_many.first_free.index()];
			many_many.m__index.vptr()[new_id.index()] = new_id;
			many_many.size_used = std::max(many_many.size_used, uint32_t(new_id.index() + 1));
			 {
				auto key_dat = many_many.to_joint_keydata(A_p, B_p, C_p, D_p, E_p, F_p);
				if(auto it = many_many.hashm_joint.find(key_dat); it !=  many_many.hashm_joint.end()) {
					delete_many_many(it->second);
				}
				many_many.hashm_joint.insert_or_assign(key_dat, new_id);
			}
			internal_many_many_set_A(new_id, A_p);
			internal_many_many_set_B(new_id, B_p);
			internal_many_many_set_C(new_id, C_p);
			internal_many_many_set_D(new_id, D_p);
			internal_many_many_set_E(new_id, E_p);
			internal_many_many_set_F(new_id, F_p);
			internal_many_many_set_ignore(new_id, ignore_p);
			return new_id;
		}
		
		//
		// container delete for relate_as_optional
		//
		void delete_relate_as_optional(relate_as_optional_id id_removed) {
			if(!relate_as_optional_is_valid(id_removed)) return;
			relate_as_optional.m__index.vptr()[id_removed.index()] = relate_as_optional.first_free;
			relate_as_optional.first_free = id_removed;
			if(int32_t(relate_as_optional.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_optional.size_used > 0 && relate_as_optional.m__index.vptr()[relate_as_optional.size_used - 1] != relate_as_optional_id(relate_as_optional_id::value_base_t(relate_as_optional.size_used - 1));  --relate_as_optional.size_used) ;
			}
			internal_relate_as_optional_set_left(id_removed, thingyA_id());
			internal_relate_as_optional_set_right(id_removed, thingyB_id());
		}
		
		//
		// container resize for relate_as_optional
		//
		void relate_as_optional_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_optional.size_used;
			if(new_size < old_size) {
				relate_as_optional.first_free = relate_as_optional_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_optional.m__index.vptr()[i] = relate_as_optional.first_free;
					relate_as_optional.first_free = relate_as_optional_id(relate_as_optional_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_optional.m__index.vptr()[i] != relate_as_optional_id(relate_as_optional_id::value_base_t(i))) {
						relate_as_optional.m__index.vptr()[i] = relate_as_optional.first_free;
						relate_as_optional.first_free = relate_as_optional_id(relate_as_optional_id::value_base_t(i));
					}
				}
				std::fill_n(relate_as_optional.m_left.vptr() + 0, old_size, thingyA_id{});
				std::for_each(relate_as_optional.m_array_left.vptr() + 0, relate_as_optional.m_array_left.vptr() + 0 + thingyA.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_optional.left_storage.release(i); });
				std::fill_n(relate_as_optional.m_right.vptr() + 0, old_size, thingyB_id{});
				std::for_each(relate_as_optional.m_array_right.vptr() + 0, relate_as_optional.m_array_right.vptr() + 0 + thingyB.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_optional.right_storage.release(i); });
			} else if(new_size > old_size) {
				relate_as_optional.first_free = relate_as_optional_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_optional.m__index.vptr()[i] = relate_as_optional.first_free;
					relate_as_optional.first_free = relate_as_optional_id(relate_as_optional_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_optional.m__index.vptr()[i] != relate_as_optional_id(relate_as_optional_id::value_base_t(i))) {
						relate_as_optional.m__index.vptr()[i] = relate_as_optional.first_free;
						relate_as_optional.first_free = relate_as_optional_id(relate_as_optional_id::value_base_t(i));
					}
				}
			}
			relate_as_optional.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_optional
		//
		relate_as_optional_id try_create_relate_as_optional(thingyA_id left_p, thingyB_id right_p) {
			if(!bool(left_p)) return relate_as_optional_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_optional.first_free)) std::abort();
			#else
			if(!bool(relate_as_optional.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_optional_id new_id = relate_as_optional.first_free;
			relate_as_optional.first_free = relate_as_optional.m__index.vptr()[relate_as_optional.first_free.index()];
			relate_as_optional.m__index.vptr()[new_id.index()] = new_id;
			relate_as_optional.size_used = std::max(relate_as_optional.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_optional_set_left(new_id, left_p);
			internal_relate_as_optional_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_optional
		//
		relate_as_optional_id force_create_relate_as_optional(thingyA_id left_p, thingyB_id right_p) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_optional.first_free)) std::abort();
			#else
			if(!bool(relate_as_optional.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_optional_id new_id = relate_as_optional.first_free;
			relate_as_optional.first_free = relate_as_optional.m__index.vptr()[relate_as_optional.first_free.index()];
			relate_as_optional.m__index.vptr()[new_id.index()] = new_id;
			relate_as_optional.size_used = std::max(relate_as_optional.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_optional_set_left(new_id, left_p);
			internal_relate_as_optional_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container delete for relate_as_non_optional
		//
		void delete_relate_as_non_optional(relate_as_non_optional_id id_removed) {
			if(!relate_as_non_optional_is_valid(id_removed)) return;
			relate_as_non_optional.m__index.vptr()[id_removed.index()] = relate_as_non_optional.first_free;
			relate_as_non_optional.first_free = id_removed;
			if(int32_t(relate_as_non_optional.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_non_optional.size_used > 0 && relate_as_non_optional.m__index.vptr()[relate_as_non_optional.size_used - 1] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(relate_as_non_optional.size_used - 1));  --relate_as_non_optional.size_used) ;
			}
			internal_relate_as_non_optional_set_left(id_removed, thingyA_id());
			internal_relate_as_non_optional_set_right(id_removed, thingyB_id());
		}
		
		//
		// container resize for relate_as_non_optional
		//
		void relate_as_non_optional_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_non_optional.size_used;
			if(new_size < old_size) {
				relate_as_non_optional.first_free = relate_as_non_optional_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_non_optional.m__index.vptr()[i] = relate_as_non_optional.first_free;
					relate_as_non_optional.first_free = relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_non_optional.m__index.vptr()[i] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i))) {
						relate_as_non_optional.m__index.vptr()[i] = relate_as_non_optional.first_free;
						relate_as_non_optional.first_free = relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i));
					}
				}
				std::fill_n(relate_as_non_optional.m_left.vptr() + 0, old_size, thingyA_id{});
				std::for_each(relate_as_non_optional.m_array_left.vptr() + 0, relate_as_non_optional.m_array_left.vptr() + 0 + thingyA.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_non_optional.left_storage.release(i); });
				std::fill_n(relate_as_non_optional.m_right.vptr() + 0, old_size, thingyB_id{});
				std::for_each(relate_as_non_optional.m_array_right.vptr() + 0, relate_as_non_optional.m_array_right.vptr() + 0 + thingyB.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_non_optional.right_storage.release(i); });
			} else if(new_size > old_size) {
				relate_as_non_optional.first_free = relate_as_non_optional_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_non_optional.m__index.vptr()[i] = relate_as_non_optional.first_free;
					relate_as_non_optional.first_free = relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_non_optional.m__index.vptr()[i] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i))) {
						relate_as_non_optional.m__index.vptr()[i] = relate_as_non_optional.first_free;
						relate_as_non_optional.first_free = relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i));
					}
				}
			}
			relate_as_non_optional.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_non_optional
		//
		relate_as_non_optional_id try_create_relate_as_non_optional(thingyA_id left_p, thingyB_id right_p) {
			if(!bool(left_p)) return relate_as_non_optional_id();
			if(!bool(right_p)) return relate_as_non_optional_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_non_optional.first_free)) std::abort();
			#else
			if(!bool(relate_as_non_optional.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_non_optional_id new_id = relate_as_non_optional.first_free;
			relate_as_non_optional.first_free = relate_as_non_optional.m__index.vptr()[relate_as_non_optional.first_free.index()];
			relate_as_non_optional.m__index.vptr()[new_id.index()] = new_id;
			relate_as_non_optional.size_used = std::max(relate_as_non_optional.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_non_optional_set_left(new_id, left_p);
			internal_relate_as_non_optional_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_non_optional
		//
		relate_as_non_optional_id force_create_relate_as_non_optional(thingyA_id left_p, thingyB_id right_p) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_non_optional.first_free)) std::abort();
			#else
			if(!bool(relate_as_non_optional.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_non_optional_id new_id = relate_as_non_optional.first_free;
			relate_as_non_optional.first_free = relate_as_non_optional.m__index.vptr()[relate_as_non_optional.first_free.index()];
			relate_as_non_optional.m__index.vptr()[new_id.index()] = new_id;
			relate_as_non_optional.size_used = std::max(relate_as_non_optional.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_non_optional_set_left(new_id, left_p);
			internal_relate_as_non_optional_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container delete for relate_as_multipleA
		//
		void delete_relate_as_multipleA(relate_as_multipleA_id id_removed) {
			if(!relate_as_multipleA_is_valid(id_removed)) return;
			relate_as_multipleA.m__index.vptr()[id_removed.index()] = relate_as_multipleA.first_free;
			relate_as_multipleA.first_free = id_removed;
			if(int32_t(relate_as_multipleA.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_multipleA.size_used > 0 && relate_as_multipleA.m__index.vptr()[relate_as_multipleA.size_used - 1] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(relate_as_multipleA.size_used - 1));  --relate_as_multipleA.size_used) ;
			}
			relate_as_multipleA.hashm_joint.erase( relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[id_removed.index()]) );
			internal_relate_as_multipleA_set_left(id_removed, 0, thingyA_id());
			internal_relate_as_multipleA_set_left(id_removed, 1, thingyA_id());
		}
		
		//
		// container resize for relate_as_multipleA
		//
		void relate_as_multipleA_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_multipleA.size_used;
			if(new_size < old_size) {
				relate_as_multipleA.first_free = relate_as_multipleA_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_multipleA.m__index.vptr()[i] = relate_as_multipleA.first_free;
					relate_as_multipleA.first_free = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleA.m__index.vptr()[i] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i))) {
						relate_as_multipleA.m__index.vptr()[i] = relate_as_multipleA.first_free;
						relate_as_multipleA.first_free = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i));
					}
				}
				relate_as_multipleA.hashm_joint.clear();
				std::destroy_n(relate_as_multipleA.m_left.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(relate_as_multipleA.m_left.vptr() + 0, old_size);
				std::for_each(relate_as_multipleA.m_array_left.vptr() + 0, relate_as_multipleA.m_array_left.vptr() + 0 + thingyA.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_multipleA.left_storage.release(i); });
			} else if(new_size > old_size) {
				relate_as_multipleA.first_free = relate_as_multipleA_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_multipleA.m__index.vptr()[i] = relate_as_multipleA.first_free;
					relate_as_multipleA.first_free = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleA.m__index.vptr()[i] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i))) {
						relate_as_multipleA.m__index.vptr()[i] = relate_as_multipleA.first_free;
						relate_as_multipleA.first_free = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i));
					}
				}
			}
			relate_as_multipleA.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_multipleA
		//
		relate_as_multipleA_id try_create_relate_as_multipleA(thingyA_id left_p0, thingyA_id left_p1) {
			if(!bool(left_p0)) return relate_as_multipleA_id();
			if(!bool(left_p1)) return relate_as_multipleA_id();
			std::array<thingyA_id, 2> left_p = {
				left_p0,
				left_p1,
			};
			std::sort(left_p.begin(), left_p.end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			if(relate_as_multipleA.hashm_joint.contains(relate_as_multipleA.to_joint_keydata(left_p))) return relate_as_multipleA_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleA.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleA.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleA_id new_id = relate_as_multipleA.first_free;
			relate_as_multipleA.first_free = relate_as_multipleA.m__index.vptr()[relate_as_multipleA.first_free.index()];
			relate_as_multipleA.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleA.size_used = std::max(relate_as_multipleA.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleA_set_left(new_id, 0, left_p[0]);
			internal_relate_as_multipleA_set_left(new_id, 1, left_p[1]);
			relate_as_multipleA.hashm_joint.insert_or_assign(relate_as_multipleA.to_joint_keydata(left_p), new_id);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_multipleA
		//
		relate_as_multipleA_id force_create_relate_as_multipleA(thingyA_id left_p0, thingyA_id left_p1) {
			std::array<thingyA_id, 2> left_p = {
				left_p0,
				left_p1,
			};
			std::sort(left_p.begin(), left_p.end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleA.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleA.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleA_id new_id = relate_as_multipleA.first_free;
			relate_as_multipleA.first_free = relate_as_multipleA.m__index.vptr()[relate_as_multipleA.first_free.index()];
			relate_as_multipleA.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleA.size_used = std::max(relate_as_multipleA.size_used, uint32_t(new_id.index() + 1));
			 {
				auto key_dat = relate_as_multipleA.to_joint_keydata(left_p);
				if(auto it = relate_as_multipleA.hashm_joint.find(key_dat); it !=  relate_as_multipleA.hashm_joint.end()) {
					delete_relate_as_multipleA(it->second);
				}
				relate_as_multipleA.hashm_joint.insert_or_assign(key_dat, new_id);
			}
			internal_relate_as_multipleA_set_left(new_id, 0, left_p[0]);
			internal_relate_as_multipleA_set_left(new_id, 1, left_p[1]);
			return new_id;
		}
		
		//
		// container delete for relate_as_multipleB
		//
		void delete_relate_as_multipleB(relate_as_multipleB_id id_removed) {
			if(!relate_as_multipleB_is_valid(id_removed)) return;
			relate_as_multipleB.m__index.vptr()[id_removed.index()] = relate_as_multipleB.first_free;
			relate_as_multipleB.first_free = id_removed;
			if(int32_t(relate_as_multipleB.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_multipleB.size_used > 0 && relate_as_multipleB.m__index.vptr()[relate_as_multipleB.size_used - 1] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(relate_as_multipleB.size_used - 1));  --relate_as_multipleB.size_used) ;
			}
			internal_relate_as_multipleB_set_left(id_removed, 0, thingyA_id());
			internal_relate_as_multipleB_set_left(id_removed, 1, thingyA_id());
		}
		
		//
		// container resize for relate_as_multipleB
		//
		void relate_as_multipleB_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_multipleB.size_used;
			if(new_size < old_size) {
				relate_as_multipleB.first_free = relate_as_multipleB_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_multipleB.m__index.vptr()[i] = relate_as_multipleB.first_free;
					relate_as_multipleB.first_free = relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleB.m__index.vptr()[i] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i))) {
						relate_as_multipleB.m__index.vptr()[i] = relate_as_multipleB.first_free;
						relate_as_multipleB.first_free = relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i));
					}
				}
				std::destroy_n(relate_as_multipleB.m_left.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(relate_as_multipleB.m_left.vptr() + 0, old_size);
				std::fill_n(relate_as_multipleB.m_link_back_left.vptr() + 0, thingyA.size_used, relate_as_multipleB_id{});
			} else if(new_size > old_size) {
				relate_as_multipleB.first_free = relate_as_multipleB_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_multipleB.m__index.vptr()[i] = relate_as_multipleB.first_free;
					relate_as_multipleB.first_free = relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleB.m__index.vptr()[i] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i))) {
						relate_as_multipleB.m__index.vptr()[i] = relate_as_multipleB.first_free;
						relate_as_multipleB.first_free = relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i));
					}
				}
			}
			relate_as_multipleB.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_multipleB
		//
		relate_as_multipleB_id try_create_relate_as_multipleB(thingyA_id left_p0, thingyA_id left_p1) {
			if(!bool(left_p0)) return relate_as_multipleB_id();
			if(bool(left_p0) && bool(relate_as_multipleB.m_link_back_left.vptr()[left_p0.index()])) return relate_as_multipleB_id();
			if(bool(left_p0) && left_p0 == left_p1) return relate_as_multipleB_id();
			if(!bool(left_p1)) return relate_as_multipleB_id();
			if(bool(left_p1) && bool(relate_as_multipleB.m_link_back_left.vptr()[left_p1.index()])) return relate_as_multipleB_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleB.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleB.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleB_id new_id = relate_as_multipleB.first_free;
			relate_as_multipleB.first_free = relate_as_multipleB.m__index.vptr()[relate_as_multipleB.first_free.index()];
			relate_as_multipleB.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleB.size_used = std::max(relate_as_multipleB.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleB_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleB_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_multipleB
		//
		relate_as_multipleB_id force_create_relate_as_multipleB(thingyA_id left_p0, thingyA_id left_p1) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleB.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleB.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleB_id new_id = relate_as_multipleB.first_free;
			relate_as_multipleB.first_free = relate_as_multipleB.m__index.vptr()[relate_as_multipleB.first_free.index()];
			relate_as_multipleB.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleB.size_used = std::max(relate_as_multipleB.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleB_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleB_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		//
		// container delete for relate_as_multipleC
		//
		void delete_relate_as_multipleC(relate_as_multipleC_id id_removed) {
			if(!relate_as_multipleC_is_valid(id_removed)) return;
			relate_as_multipleC.m__index.vptr()[id_removed.index()] = relate_as_multipleC.first_free;
			relate_as_multipleC.first_free = id_removed;
			if(int32_t(relate_as_multipleC.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_multipleC.size_used > 0 && relate_as_multipleC.m__index.vptr()[relate_as_multipleC.size_used - 1] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(relate_as_multipleC.size_used - 1));  --relate_as_multipleC.size_used) ;
			}
			internal_relate_as_multipleC_set_left(id_removed, 0, thingyA_id());
			internal_relate_as_multipleC_set_left(id_removed, 1, thingyA_id());
		}
		
		//
		// container resize for relate_as_multipleC
		//
		void relate_as_multipleC_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_multipleC.size_used;
			if(new_size < old_size) {
				relate_as_multipleC.first_free = relate_as_multipleC_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_multipleC.m__index.vptr()[i] = relate_as_multipleC.first_free;
					relate_as_multipleC.first_free = relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleC.m__index.vptr()[i] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i))) {
						relate_as_multipleC.m__index.vptr()[i] = relate_as_multipleC.first_free;
						relate_as_multipleC.first_free = relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i));
					}
				}
				std::destroy_n(relate_as_multipleC.m_left.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(relate_as_multipleC.m_left.vptr() + 0, old_size);
				std::for_each(relate_as_multipleC.m_array_left.vptr() + 0, relate_as_multipleC.m_array_left.vptr() + 0 + thingyA.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->relate_as_multipleC.left_storage.release(i); });
			} else if(new_size > old_size) {
				relate_as_multipleC.first_free = relate_as_multipleC_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_multipleC.m__index.vptr()[i] = relate_as_multipleC.first_free;
					relate_as_multipleC.first_free = relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleC.m__index.vptr()[i] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i))) {
						relate_as_multipleC.m__index.vptr()[i] = relate_as_multipleC.first_free;
						relate_as_multipleC.first_free = relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i));
					}
				}
			}
			relate_as_multipleC.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_multipleC
		//
		relate_as_multipleC_id try_create_relate_as_multipleC(thingyA_id left_p0, thingyA_id left_p1) {
			if(!bool(left_p0)) return relate_as_multipleC_id();
			if(bool(left_p0) && left_p0 == left_p1) return relate_as_multipleC_id();
			if(!bool(left_p1)) return relate_as_multipleC_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleC.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleC.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleC_id new_id = relate_as_multipleC.first_free;
			relate_as_multipleC.first_free = relate_as_multipleC.m__index.vptr()[relate_as_multipleC.first_free.index()];
			relate_as_multipleC.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleC.size_used = std::max(relate_as_multipleC.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleC_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleC_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_multipleC
		//
		relate_as_multipleC_id force_create_relate_as_multipleC(thingyA_id left_p0, thingyA_id left_p1) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleC.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleC.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleC_id new_id = relate_as_multipleC.first_free;
			relate_as_multipleC.first_free = relate_as_multipleC.m__index.vptr()[relate_as_multipleC.first_free.index()];
			relate_as_multipleC.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleC.size_used = std::max(relate_as_multipleC.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleC_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleC_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		//
		// container delete for relate_as_multipleD
		//
		void delete_relate_as_multipleD(relate_as_multipleD_id id_removed) {
			if(!relate_as_multipleD_is_valid(id_removed)) return;
			relate_as_multipleD.m__index.vptr()[id_removed.index()] = relate_as_multipleD.first_free;
			relate_as_multipleD.first_free = id_removed;
			if(int32_t(relate_as_multipleD.size_used) - 1 == id_removed.index()) {
				for( ; relate_as_multipleD.size_used > 0 && relate_as_multipleD.m__index.vptr()[relate_as_multipleD.size_used - 1] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(relate_as_multipleD.size_used - 1));  --relate_as_multipleD.size_used) ;
			}
			internal_relate_as_multipleD_set_left(id_removed, 0, thingyA_id());
			internal_relate_as_multipleD_set_left(id_removed, 1, thingyA_id());
		}
		
		//
		// container resize for relate_as_multipleD
		//
		void relate_as_multipleD_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 400) std::abort();
			#else
			if(new_size > 400) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = relate_as_multipleD.size_used;
			if(new_size < old_size) {
				relate_as_multipleD.first_free = relate_as_multipleD_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(new_size); --i) {
					relate_as_multipleD.m__index.vptr()[i] = relate_as_multipleD.first_free;
					relate_as_multipleD.first_free = relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleD.m__index.vptr()[i] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i))) {
						relate_as_multipleD.m__index.vptr()[i] = relate_as_multipleD.first_free;
						relate_as_multipleD.first_free = relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i));
					}
				}
				std::destroy_n(relate_as_multipleD.m_left.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(relate_as_multipleD.m_left.vptr() + 0, old_size);
			} else if(new_size > old_size) {
				relate_as_multipleD.first_free = relate_as_multipleD_id();
				int32_t i = int32_t(400 - 1);
				for(; i >= int32_t(old_size); --i) {
					relate_as_multipleD.m__index.vptr()[i] = relate_as_multipleD.first_free;
					relate_as_multipleD.first_free = relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(relate_as_multipleD.m__index.vptr()[i] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i))) {
						relate_as_multipleD.m__index.vptr()[i] = relate_as_multipleD.first_free;
						relate_as_multipleD.first_free = relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i));
					}
				}
			}
			relate_as_multipleD.size_used = new_size;
		}
		
		//
		// container try create relationship for relate_as_multipleD
		//
		relate_as_multipleD_id try_create_relate_as_multipleD(thingyA_id left_p0, thingyA_id left_p1) {
			if(!bool(left_p0)) return relate_as_multipleD_id();
			if(!bool(left_p1)) return relate_as_multipleD_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleD.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleD.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleD_id new_id = relate_as_multipleD.first_free;
			relate_as_multipleD.first_free = relate_as_multipleD.m__index.vptr()[relate_as_multipleD.first_free.index()];
			relate_as_multipleD.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleD.size_used = std::max(relate_as_multipleD.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleD_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleD_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		//
		// container force create relationship for relate_as_multipleD
		//
		relate_as_multipleD_id force_create_relate_as_multipleD(thingyA_id left_p0, thingyA_id left_p1) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(relate_as_multipleD.first_free)) std::abort();
			#else
			if(!bool(relate_as_multipleD.first_free)) throw dcon::out_of_space{};
			#endif
			relate_as_multipleD_id new_id = relate_as_multipleD.first_free;
			relate_as_multipleD.first_free = relate_as_multipleD.m__index.vptr()[relate_as_multipleD.first_free.index()];
			relate_as_multipleD.m__index.vptr()[new_id.index()] = new_id;
			relate_as_multipleD.size_used = std::max(relate_as_multipleD.size_used, uint32_t(new_id.index() + 1));
			internal_relate_as_multipleD_set_left(new_id, 0, left_p0);
			internal_relate_as_multipleD_set_left(new_id, 1, left_p1);
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingyA(T&& func) {
			for(uint32_t i = 0; i < thingyA.size_used; ++i) {
				thingyA_id tmp = thingyA_id(thingyA_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_thingyA;
		friend internal::object_iterator_thingyA;
		struct {
			internal::object_iterator_thingyA begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingyA));
				return internal::object_iterator_thingyA(*container, uint32_t(0));
			}
			internal::object_iterator_thingyA end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingyA));
				return internal::object_iterator_thingyA(*container, container->thingyA_size());
			}
			internal::const_object_iterator_thingyA begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingyA));
				return internal::const_object_iterator_thingyA(*container, uint32_t(0));
			}
			internal::const_object_iterator_thingyA end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingyA));
				return internal::const_object_iterator_thingyA(*container, container->thingyA_size());
			}
		}  in_thingyA ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingyB(T&& func) {
			for(uint32_t i = 0; i < thingyB.size_used; ++i) {
				thingyB_id tmp = thingyB_id(thingyB_id::value_base_t(i));
				if(thingyB.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_thingyB;
		friend internal::object_iterator_thingyB;
		struct {
			internal::object_iterator_thingyB begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingyB));
				return internal::object_iterator_thingyB(*container, uint32_t(0));
			}
			internal::object_iterator_thingyB end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingyB));
				return internal::object_iterator_thingyB(*container, container->thingyB_size());
			}
			internal::const_object_iterator_thingyB begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingyB));
				return internal::const_object_iterator_thingyB(*container, uint32_t(0));
			}
			internal::const_object_iterator_thingyB end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingyB));
				return internal::const_object_iterator_thingyB(*container, container->thingyB_size());
			}
		}  in_thingyB ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_same(T&& func) {
			for(uint32_t i = 0; i < relate_same.size_used; ++i) {
				relate_same_id tmp = relate_same_id(relate_same_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_same;
		friend internal::object_iterator_relate_same;
		struct {
			internal::object_iterator_relate_same begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_same));
				return internal::object_iterator_relate_same(*container, uint32_t(0));
			}
			internal::object_iterator_relate_same end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_same));
				return internal::object_iterator_relate_same(*container, container->relate_same_size());
			}
			internal::const_object_iterator_relate_same begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_same));
				return internal::const_object_iterator_relate_same(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_same end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_same));
				return internal::const_object_iterator_relate_same(*container, container->relate_same_size());
			}
		}  in_relate_same ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_array(T&& func) {
			for(uint32_t i = 0; i < relate_in_array.size_used; ++i) {
				relate_in_array_id tmp = relate_in_array_id(relate_in_array_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_in_array;
		friend internal::object_iterator_relate_in_array;
		struct {
			internal::object_iterator_relate_in_array begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_in_array));
				return internal::object_iterator_relate_in_array(*container, uint32_t(0));
			}
			internal::object_iterator_relate_in_array end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_in_array));
				return internal::object_iterator_relate_in_array(*container, container->relate_in_array_size());
			}
			internal::const_object_iterator_relate_in_array begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_in_array));
				return internal::const_object_iterator_relate_in_array(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_in_array end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_in_array));
				return internal::const_object_iterator_relate_in_array(*container, container->relate_in_array_size());
			}
		}  in_relate_in_array ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_in_list(T&& func) {
			for(uint32_t i = 0; i < relate_in_list.size_used; ++i) {
				relate_in_list_id tmp = relate_in_list_id(relate_in_list_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_in_list;
		friend internal::object_iterator_relate_in_list;
		struct {
			internal::object_iterator_relate_in_list begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_in_list));
				return internal::object_iterator_relate_in_list(*container, uint32_t(0));
			}
			internal::object_iterator_relate_in_list end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_in_list));
				return internal::object_iterator_relate_in_list(*container, container->relate_in_list_size());
			}
			internal::const_object_iterator_relate_in_list begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_in_list));
				return internal::const_object_iterator_relate_in_list(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_in_list end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_in_list));
				return internal::const_object_iterator_relate_in_list(*container, container->relate_in_list_size());
			}
		}  in_relate_in_list ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_many_many(T&& func) {
			for(uint32_t i = 0; i < many_many.size_used; ++i) {
				many_many_id tmp = many_many_id(many_many_id::value_base_t(i));
				if(many_many.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_many_many;
		friend internal::object_iterator_many_many;
		struct {
			internal::object_iterator_many_many begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_many_many));
				return internal::object_iterator_many_many(*container, uint32_t(0));
			}
			internal::object_iterator_many_many end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_many_many));
				return internal::object_iterator_many_many(*container, container->many_many_size());
			}
			internal::const_object_iterator_many_many begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_many_many));
				return internal::const_object_iterator_many_many(*container, uint32_t(0));
			}
			internal::const_object_iterator_many_many end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_many_many));
				return internal::const_object_iterator_many_many(*container, container->many_many_size());
			}
		}  in_many_many ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_optional(T&& func) {
			for(uint32_t i = 0; i < relate_as_optional.size_used; ++i) {
				relate_as_optional_id tmp = relate_as_optional_id(relate_as_optional_id::value_base_t(i));
				if(relate_as_optional.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_optional;
		friend internal::object_iterator_relate_as_optional;
		struct {
			internal::object_iterator_relate_as_optional begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_optional));
				return internal::object_iterator_relate_as_optional(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_optional end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_optional));
				return internal::object_iterator_relate_as_optional(*container, container->relate_as_optional_size());
			}
			internal::const_object_iterator_relate_as_optional begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_optional));
				return internal::const_object_iterator_relate_as_optional(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_optional end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_optional));
				return internal::const_object_iterator_relate_as_optional(*container, container->relate_as_optional_size());
			}
		}  in_relate_as_optional ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_non_optional(T&& func) {
			for(uint32_t i = 0; i < relate_as_non_optional.size_used; ++i) {
				relate_as_non_optional_id tmp = relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i));
				if(relate_as_non_optional.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_non_optional;
		friend internal::object_iterator_relate_as_non_optional;
		struct {
			internal::object_iterator_relate_as_non_optional begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_non_optional));
				return internal::object_iterator_relate_as_non_optional(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_non_optional end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_non_optional));
				return internal::object_iterator_relate_as_non_optional(*container, container->relate_as_non_optional_size());
			}
			internal::const_object_iterator_relate_as_non_optional begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_non_optional));
				return internal::const_object_iterator_relate_as_non_optional(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_non_optional end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_non_optional));
				return internal::const_object_iterator_relate_as_non_optional(*container, container->relate_as_non_optional_size());
			}
		}  in_relate_as_non_optional ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleA(T&& func) {
			for(uint32_t i = 0; i < relate_as_multipleA.size_used; ++i) {
				relate_as_multipleA_id tmp = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i));
				if(relate_as_multipleA.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_multipleA;
		friend internal::object_iterator_relate_as_multipleA;
		struct {
			internal::object_iterator_relate_as_multipleA begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleA));
				return internal::object_iterator_relate_as_multipleA(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_multipleA end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleA));
				return internal::object_iterator_relate_as_multipleA(*container, container->relate_as_multipleA_size());
			}
			internal::const_object_iterator_relate_as_multipleA begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleA));
				return internal::const_object_iterator_relate_as_multipleA(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_multipleA end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleA));
				return internal::const_object_iterator_relate_as_multipleA(*container, container->relate_as_multipleA_size());
			}
		}  in_relate_as_multipleA ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleB(T&& func) {
			for(uint32_t i = 0; i < relate_as_multipleB.size_used; ++i) {
				relate_as_multipleB_id tmp = relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i));
				if(relate_as_multipleB.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_multipleB;
		friend internal::object_iterator_relate_as_multipleB;
		struct {
			internal::object_iterator_relate_as_multipleB begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleB));
				return internal::object_iterator_relate_as_multipleB(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_multipleB end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleB));
				return internal::object_iterator_relate_as_multipleB(*container, container->relate_as_multipleB_size());
			}
			internal::const_object_iterator_relate_as_multipleB begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleB));
				return internal::const_object_iterator_relate_as_multipleB(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_multipleB end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleB));
				return internal::const_object_iterator_relate_as_multipleB(*container, container->relate_as_multipleB_size());
			}
		}  in_relate_as_multipleB ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleC(T&& func) {
			for(uint32_t i = 0; i < relate_as_multipleC.size_used; ++i) {
				relate_as_multipleC_id tmp = relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i));
				if(relate_as_multipleC.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_multipleC;
		friend internal::object_iterator_relate_as_multipleC;
		struct {
			internal::object_iterator_relate_as_multipleC begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleC));
				return internal::object_iterator_relate_as_multipleC(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_multipleC end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleC));
				return internal::object_iterator_relate_as_multipleC(*container, container->relate_as_multipleC_size());
			}
			internal::const_object_iterator_relate_as_multipleC begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleC));
				return internal::const_object_iterator_relate_as_multipleC(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_multipleC end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleC));
				return internal::const_object_iterator_relate_as_multipleC(*container, container->relate_as_multipleC_size());
			}
		}  in_relate_as_multipleC ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_relate_as_multipleD(T&& func) {
			for(uint32_t i = 0; i < relate_as_multipleD.size_used; ++i) {
				relate_as_multipleD_id tmp = relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i));
				if(relate_as_multipleD.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_relate_as_multipleD;
		friend internal::object_iterator_relate_as_multipleD;
		struct {
			internal::object_iterator_relate_as_multipleD begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleD));
				return internal::object_iterator_relate_as_multipleD(*container, uint32_t(0));
			}
			internal::object_iterator_relate_as_multipleD end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_relate_as_multipleD));
				return internal::object_iterator_relate_as_multipleD(*container, container->relate_as_multipleD_size());
			}
			internal::const_object_iterator_relate_as_multipleD begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleD));
				return internal::const_object_iterator_relate_as_multipleD(*container, uint32_t(0));
			}
			internal::const_object_iterator_relate_as_multipleD end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_relate_as_multipleD));
				return internal::const_object_iterator_relate_as_multipleD(*container, container->relate_as_multipleD_size());
			}
		}  in_relate_as_multipleD ;
		



		void reset() {
			relate_same_resize(0);
			relate_in_array_resize(0);
			relate_in_list_resize(0);
			many_many_resize(0);
			relate_as_optional_resize(0);
			relate_as_non_optional_resize(0);
			relate_as_multipleA_resize(0);
			relate_as_multipleB_resize(0);
			relate_as_multipleC_resize(0);
			relate_as_multipleD_resize(0);
			thingyA_resize(0);
			thingyB_resize(0);
		}
		relate_same_id get_relate_same_by_joint(thingyA_id left_p, thingyA_id right_p) {
			if(auto it = relate_same.hashm_joint.find(relate_same.to_joint_keydata(left_p, right_p)); it != relate_same.hashm_joint.end()) {
				return it->second;
			}
			return relate_same_id();
		}
		many_many_id get_many_many_by_joint(thingyA_id A_p, thingyA_id B_p, thingyA_id C_p, thingyA_id D_p, thingyA_id E_p, thingyA_id F_p) {
			if(auto it = many_many.hashm_joint.find(many_many.to_joint_keydata(A_p, B_p, C_p, D_p, E_p, F_p)); it != many_many.hashm_joint.end()) {
				return it->second;
			}
			return many_many_id();
		}
		relate_as_multipleA_id get_relate_as_multipleA_by_joint(thingyA_id left_p0, thingyA_id left_p1) {
			std::array<thingyA_id, 2> left_p = {
				left_p0,
				left_p1,
			};
			std::sort(left_p.begin(), left_p.end(), [](thingyA_id a, thingyA_id b){ return a.value < b.value; });
			if(auto it = relate_as_multipleA.hashm_joint.find(relate_as_multipleA.to_joint_keydata({left_p0, left_p1})); it != relate_as_multipleA.hashm_joint.end()) {
				return it->second;
			}
			return relate_as_multipleA_id();
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, thingyA_id> thingyA_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, thingyA_id>(thingyA.size_used);
		}
		ve::vectorizable_buffer<int32_t, thingyA_id> thingyA_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, thingyA_id>(thingyA.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_thingyA(F&& functor) {
			ve::execute_serial<thingyA_id>(thingyA.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingyA(F&& functor) {
			ve::execute_parallel_exact<thingyA_id>(thingyA.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, thingyB_id> thingyB_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, thingyB_id>(thingyB.size_used);
		}
		ve::vectorizable_buffer<int32_t, thingyB_id> thingyB_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, thingyB_id>(thingyB.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_thingyB(F&& functor) {
			ve::execute_serial<thingyB_id>(thingyB.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingyB(F&& functor) {
			ve::execute_parallel_exact<thingyB_id>(thingyB.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_same_id> relate_same_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_same_id>(relate_same.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_same_id> relate_same_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_same_id>(relate_same.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_same(F&& functor) {
			ve::execute_serial<relate_same_id>(relate_same.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_same(F&& functor) {
			ve::execute_parallel_exact<relate_same_id>(relate_same.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_in_array_id> relate_in_array_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_in_array_id>(relate_in_array.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_in_array_id> relate_in_array_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_in_array_id>(relate_in_array.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_in_array(F&& functor) {
			ve::execute_serial<relate_in_array_id>(relate_in_array.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_in_array(F&& functor) {
			ve::execute_parallel_exact<relate_in_array_id>(relate_in_array.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_in_list_id> relate_in_list_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_in_list_id>(relate_in_list.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_in_list_id> relate_in_list_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_in_list_id>(relate_in_list.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_in_list(F&& functor) {
			ve::execute_serial<relate_in_list_id>(relate_in_list.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_in_list(F&& functor) {
			ve::execute_parallel_exact<relate_in_list_id>(relate_in_list.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, many_many_id> many_many_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, many_many_id>(many_many.size_used);
		}
		ve::vectorizable_buffer<int32_t, many_many_id> many_many_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, many_many_id>(many_many.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_many_many(F&& functor) {
			ve::execute_serial<many_many_id>(many_many.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_many_many(F&& functor) {
			ve::execute_parallel_exact<many_many_id>(many_many.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_optional_id> relate_as_optional_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_optional_id>(relate_as_optional.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_optional_id> relate_as_optional_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_optional_id>(relate_as_optional.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_optional(F&& functor) {
			ve::execute_serial<relate_as_optional_id>(relate_as_optional.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_optional(F&& functor) {
			ve::execute_parallel_exact<relate_as_optional_id>(relate_as_optional.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_non_optional_id> relate_as_non_optional_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_non_optional_id>(relate_as_non_optional.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_non_optional_id> relate_as_non_optional_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_non_optional_id>(relate_as_non_optional.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_non_optional(F&& functor) {
			ve::execute_serial<relate_as_non_optional_id>(relate_as_non_optional.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_non_optional(F&& functor) {
			ve::execute_parallel_exact<relate_as_non_optional_id>(relate_as_non_optional.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_multipleA_id> relate_as_multipleA_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_multipleA_id>(relate_as_multipleA.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_multipleA_id> relate_as_multipleA_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_multipleA_id>(relate_as_multipleA.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_multipleA(F&& functor) {
			ve::execute_serial<relate_as_multipleA_id>(relate_as_multipleA.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_multipleA(F&& functor) {
			ve::execute_parallel_exact<relate_as_multipleA_id>(relate_as_multipleA.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_multipleB_id> relate_as_multipleB_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_multipleB_id>(relate_as_multipleB.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_multipleB_id> relate_as_multipleB_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_multipleB_id>(relate_as_multipleB.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_multipleB(F&& functor) {
			ve::execute_serial<relate_as_multipleB_id>(relate_as_multipleB.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_multipleB(F&& functor) {
			ve::execute_parallel_exact<relate_as_multipleB_id>(relate_as_multipleB.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_multipleC_id> relate_as_multipleC_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_multipleC_id>(relate_as_multipleC.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_multipleC_id> relate_as_multipleC_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_multipleC_id>(relate_as_multipleC.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_multipleC(F&& functor) {
			ve::execute_serial<relate_as_multipleC_id>(relate_as_multipleC.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_multipleC(F&& functor) {
			ve::execute_parallel_exact<relate_as_multipleC_id>(relate_as_multipleC.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, relate_as_multipleD_id> relate_as_multipleD_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, relate_as_multipleD_id>(relate_as_multipleD.size_used);
		}
		ve::vectorizable_buffer<int32_t, relate_as_multipleD_id> relate_as_multipleD_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, relate_as_multipleD_id>(relate_as_multipleD.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_relate_as_multipleD(F&& functor) {
			ve::execute_serial<relate_as_multipleD_id>(relate_as_multipleD.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_relate_as_multipleD(F&& functor) {
			ve::execute_parallel_exact<relate_as_multipleD_id>(relate_as_multipleD.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingyA = true;
			result.thingyA_some_value = true;
			result.thingyB = true;
			result.thingyB__index = true;
			result.thingyB_some_value = true;
			result.relate_same = true;
			result.relate_same_left = true;
			result.relate_same_right = true;
			result.relate_in_array = true;
			result.relate_in_array_left = true;
			result.relate_in_array_right = true;
			result.relate_in_list = true;
			result.relate_in_list_left = true;
			result.relate_in_list_right = true;
			result.many_many = true;
			result.many_many_A = true;
			result.many_many_B = true;
			result.many_many_C = true;
			result.many_many_D = true;
			result.many_many_E = true;
			result.many_many_F = true;
			result.many_many_ignore = true;
			result.many_many__index = true;
			result.relate_as_optional = true;
			result.relate_as_optional_left = true;
			result.relate_as_optional_right = true;
			result.relate_as_optional__index = true;
			result.relate_as_non_optional = true;
			result.relate_as_non_optional_left = true;
			result.relate_as_non_optional_right = true;
			result.relate_as_non_optional__index = true;
			result.relate_as_multipleA = true;
			result.relate_as_multipleA_left = true;
			result.relate_as_multipleA__index = true;
			result.relate_as_multipleB = true;
			result.relate_as_multipleB_left = true;
			result.relate_as_multipleB__index = true;
			result.relate_as_multipleC = true;
			result.relate_as_multipleC_left = true;
			result.relate_as_multipleC__index = true;
			result.relate_as_multipleD = true;
			result.relate_as_multipleD_left = true;
			result.relate_as_multipleD__index = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.thingyA) {
				dcon::record_header header(0, "uint32_t", "thingyA", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.thingyA_some_value) {
				dcon::record_header iheader(0, "int32_t", "thingyA", "some_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * thingyA.size_used;
			}
			if(serialize_selection.thingyB) {
				dcon::record_header header(0, "uint32_t", "thingyB", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.thingyB__index) {
				dcon::record_header iheader(0, "uint16_t", "thingyB", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(thingyB_id) * thingyB.size_used;
			}
			if(serialize_selection.thingyB_some_value) {
				dcon::record_header iheader(0, "int32_t", "thingyB", "some_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * thingyB.size_used;
			}
			if(serialize_selection.relate_same) {
				dcon::record_header header(0, "uint32_t", "relate_same", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_same_right) {
					dcon::record_header iheader(0, "uint16_t", "relate_same", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * relate_same.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_same", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_in_array) {
				dcon::record_header header(0, "uint32_t", "relate_in_array", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_in_array_right) {
					dcon::record_header iheader(0, "uint16_t", "relate_in_array", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyB_id) * relate_in_array.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_in_array", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_in_list) {
				dcon::record_header header(0, "uint32_t", "relate_in_list", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_in_list_right) {
					dcon::record_header iheader(0, "uint16_t", "relate_in_list", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyB_id) * relate_in_list.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_in_list", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.many_many) {
				dcon::record_header header(0, "uint32_t", "many_many", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.many_many_A) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "A");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_B) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "B");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_C) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "C");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_D) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "D");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_E) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "E");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_F) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "F");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				if(serialize_selection.many_many_ignore) {
					dcon::record_header iheader(0, "uint16_t", "many_many", "ignore");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * many_many.size_used;
				}
				dcon::record_header headerb(0, "$", "many_many", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.many_many__index) {
				dcon::record_header iheader(0, "uint16_t", "many_many", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(many_many_id) * many_many.size_used;
			}
			if(serialize_selection.relate_as_optional) {
				dcon::record_header header(0, "uint32_t", "relate_as_optional", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_optional_left) {
					dcon::record_header iheader(0, "uint16_t", "relate_as_optional", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * relate_as_optional.size_used;
				}
				if(serialize_selection.relate_as_optional_right) {
					dcon::record_header iheader(0, "uint16_t", "relate_as_optional", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyB_id) * relate_as_optional.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_optional", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_optional__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_optional", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_optional_id) * relate_as_optional.size_used;
			}
			if(serialize_selection.relate_as_non_optional) {
				dcon::record_header header(0, "uint32_t", "relate_as_non_optional", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_non_optional_left) {
					dcon::record_header iheader(0, "uint16_t", "relate_as_non_optional", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyA_id) * relate_as_non_optional.size_used;
				}
				if(serialize_selection.relate_as_non_optional_right) {
					dcon::record_header iheader(0, "uint16_t", "relate_as_non_optional", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingyB_id) * relate_as_non_optional.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_non_optional", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_non_optional__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_non_optional", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_non_optional_id) * relate_as_non_optional.size_used;
			}
			if(serialize_selection.relate_as_multipleA) {
				dcon::record_header header(0, "uint32_t", "relate_as_multipleA", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_multipleA_left) {
					dcon::record_header iheader(0, "std::array<uint16_t,2>", "relate_as_multipleA", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(std::array<thingyA_id, 2>) * relate_as_multipleA.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleA", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_multipleA__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_multipleA", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_multipleA_id) * relate_as_multipleA.size_used;
			}
			if(serialize_selection.relate_as_multipleB) {
				dcon::record_header header(0, "uint32_t", "relate_as_multipleB", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_multipleB_left) {
					dcon::record_header iheader(0, "std::array<uint16_t,2>", "relate_as_multipleB", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(std::array<thingyA_id, 2>) * relate_as_multipleB.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleB", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_multipleB__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_multipleB", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_multipleB_id) * relate_as_multipleB.size_used;
			}
			if(serialize_selection.relate_as_multipleC) {
				dcon::record_header header(0, "uint32_t", "relate_as_multipleC", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_multipleC_left) {
					dcon::record_header iheader(0, "std::array<uint16_t,2>", "relate_as_multipleC", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(std::array<thingyA_id, 2>) * relate_as_multipleC.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleC", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_multipleC__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_multipleC", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_multipleC_id) * relate_as_multipleC.size_used;
			}
			if(serialize_selection.relate_as_multipleD) {
				dcon::record_header header(0, "uint32_t", "relate_as_multipleD", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.relate_as_multipleD_left) {
					dcon::record_header iheader(0, "std::array<uint16_t,2>", "relate_as_multipleD", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(std::array<thingyA_id, 2>) * relate_as_multipleD.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleD", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.relate_as_multipleD__index) {
				dcon::record_header iheader(0, "uint16_t", "relate_as_multipleD", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(relate_as_multipleD_id) * relate_as_multipleD.size_used;
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.thingyA) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "thingyA", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = thingyA.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.thingyA_some_value) {
				dcon::record_header header(sizeof(int32_t) * thingyA.size_used, "int32_t", "thingyA", "some_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), thingyA.m_some_value.vptr(), sizeof(int32_t) * thingyA.size_used);
				output_buffer += sizeof(int32_t) * thingyA.size_used;
			}
			if(serialize_selection.thingyB) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "thingyB", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = thingyB.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.thingyB__index) {
				dcon::record_header header(sizeof(thingyB_id) * thingyB.size_used, "uint16_t", "thingyB", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<thingyB_id*>(output_buffer), thingyB.m__index.vptr(), sizeof(thingyB_id) * thingyB.size_used);
				output_buffer += sizeof(thingyB_id) * thingyB.size_used;
			}
			if(serialize_selection.thingyB_some_value) {
				dcon::record_header header(sizeof(int32_t) * thingyB.size_used, "int32_t", "thingyB", "some_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), thingyB.m_some_value.vptr(), sizeof(int32_t) * thingyB.size_used);
				output_buffer += sizeof(int32_t) * thingyB.size_used;
			}
			if(serialize_selection.relate_same) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_same", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_same.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * relate_same.size_used, "uint16_t", "relate_same", "right");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), relate_same.m_right.vptr(), sizeof(thingyA_id) * relate_same.size_used);
					output_buffer += sizeof(thingyA_id) *  relate_same.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_same", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_in_array) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_in_array", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_in_array.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyB_id) * relate_in_array.size_used, "uint16_t", "relate_in_array", "right");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyB_id*>(output_buffer), relate_in_array.m_right.vptr(), sizeof(thingyB_id) * relate_in_array.size_used);
					output_buffer += sizeof(thingyB_id) *  relate_in_array.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_in_array", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_in_list) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_in_list", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_in_list.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyB_id) * relate_in_list.size_used, "uint16_t", "relate_in_list", "right");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyB_id*>(output_buffer), relate_in_list.m_right.vptr(), sizeof(thingyB_id) * relate_in_list.size_used);
					output_buffer += sizeof(thingyB_id) *  relate_in_list.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_in_list", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.many_many) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "many_many", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = many_many.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "A");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_A.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "B");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_B.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "C");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_C.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "D");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_D.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "E");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_E.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "F");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_F.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * many_many.size_used, "uint16_t", "many_many", "ignore");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), many_many.m_ignore.vptr(), sizeof(thingyA_id) * many_many.size_used);
					output_buffer += sizeof(thingyA_id) *  many_many.size_used;
				}
				dcon::record_header headerb(0, "$", "many_many", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.many_many__index) {
				dcon::record_header header(sizeof(many_many_id) * many_many.size_used, "uint16_t", "many_many", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<many_many_id*>(output_buffer), many_many.m__index.vptr(), sizeof(many_many_id) * many_many.size_used);
				output_buffer += sizeof(many_many_id) * many_many.size_used;
			}
			if(serialize_selection.relate_as_optional) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_optional", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_optional.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * relate_as_optional.size_used, "uint16_t", "relate_as_optional", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), relate_as_optional.m_left.vptr(), sizeof(thingyA_id) * relate_as_optional.size_used);
					output_buffer += sizeof(thingyA_id) *  relate_as_optional.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyB_id) * relate_as_optional.size_used, "uint16_t", "relate_as_optional", "right");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyB_id*>(output_buffer), relate_as_optional.m_right.vptr(), sizeof(thingyB_id) * relate_as_optional.size_used);
					output_buffer += sizeof(thingyB_id) *  relate_as_optional.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_optional", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_optional__index) {
				dcon::record_header header(sizeof(relate_as_optional_id) * relate_as_optional.size_used, "uint16_t", "relate_as_optional", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_optional_id*>(output_buffer), relate_as_optional.m__index.vptr(), sizeof(relate_as_optional_id) * relate_as_optional.size_used);
				output_buffer += sizeof(relate_as_optional_id) * relate_as_optional.size_used;
			}
			if(serialize_selection.relate_as_non_optional) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_non_optional", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_non_optional.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingyA_id) * relate_as_non_optional.size_used, "uint16_t", "relate_as_non_optional", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyA_id*>(output_buffer), relate_as_non_optional.m_left.vptr(), sizeof(thingyA_id) * relate_as_non_optional.size_used);
					output_buffer += sizeof(thingyA_id) *  relate_as_non_optional.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(thingyB_id) * relate_as_non_optional.size_used, "uint16_t", "relate_as_non_optional", "right");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingyB_id*>(output_buffer), relate_as_non_optional.m_right.vptr(), sizeof(thingyB_id) * relate_as_non_optional.size_used);
					output_buffer += sizeof(thingyB_id) *  relate_as_non_optional.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_non_optional", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_non_optional__index) {
				dcon::record_header header(sizeof(relate_as_non_optional_id) * relate_as_non_optional.size_used, "uint16_t", "relate_as_non_optional", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_non_optional_id*>(output_buffer), relate_as_non_optional.m__index.vptr(), sizeof(relate_as_non_optional_id) * relate_as_non_optional.size_used);
				output_buffer += sizeof(relate_as_non_optional_id) * relate_as_non_optional.size_used;
			}
			if(serialize_selection.relate_as_multipleA) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_multipleA", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_multipleA.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(std::array<thingyA_id, 2>) * relate_as_multipleA.size_used, "std::array<uint16_t,2>", "relate_as_multipleA", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<std::array<thingyA_id, 2>*>(output_buffer), relate_as_multipleA.m_left.vptr(), sizeof(std::array<thingyA_id, 2>) * relate_as_multipleA.size_used);
					output_buffer += sizeof(std::array<thingyA_id, 2>) *  relate_as_multipleA.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleA", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_multipleA__index) {
				dcon::record_header header(sizeof(relate_as_multipleA_id) * relate_as_multipleA.size_used, "uint16_t", "relate_as_multipleA", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_multipleA_id*>(output_buffer), relate_as_multipleA.m__index.vptr(), sizeof(relate_as_multipleA_id) * relate_as_multipleA.size_used);
				output_buffer += sizeof(relate_as_multipleA_id) * relate_as_multipleA.size_used;
			}
			if(serialize_selection.relate_as_multipleB) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_multipleB", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_multipleB.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(std::array<thingyA_id, 2>) * relate_as_multipleB.size_used, "std::array<uint16_t,2>", "relate_as_multipleB", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<std::array<thingyA_id, 2>*>(output_buffer), relate_as_multipleB.m_left.vptr(), sizeof(std::array<thingyA_id, 2>) * relate_as_multipleB.size_used);
					output_buffer += sizeof(std::array<thingyA_id, 2>) *  relate_as_multipleB.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleB", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_multipleB__index) {
				dcon::record_header header(sizeof(relate_as_multipleB_id) * relate_as_multipleB.size_used, "uint16_t", "relate_as_multipleB", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_multipleB_id*>(output_buffer), relate_as_multipleB.m__index.vptr(), sizeof(relate_as_multipleB_id) * relate_as_multipleB.size_used);
				output_buffer += sizeof(relate_as_multipleB_id) * relate_as_multipleB.size_used;
			}
			if(serialize_selection.relate_as_multipleC) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_multipleC", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_multipleC.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(std::array<thingyA_id, 2>) * relate_as_multipleC.size_used, "std::array<uint16_t,2>", "relate_as_multipleC", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<std::array<thingyA_id, 2>*>(output_buffer), relate_as_multipleC.m_left.vptr(), sizeof(std::array<thingyA_id, 2>) * relate_as_multipleC.size_used);
					output_buffer += sizeof(std::array<thingyA_id, 2>) *  relate_as_multipleC.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleC", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_multipleC__index) {
				dcon::record_header header(sizeof(relate_as_multipleC_id) * relate_as_multipleC.size_used, "uint16_t", "relate_as_multipleC", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_multipleC_id*>(output_buffer), relate_as_multipleC.m__index.vptr(), sizeof(relate_as_multipleC_id) * relate_as_multipleC.size_used);
				output_buffer += sizeof(relate_as_multipleC_id) * relate_as_multipleC.size_used;
			}
			if(serialize_selection.relate_as_multipleD) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "relate_as_multipleD", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = relate_as_multipleD.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(std::array<thingyA_id, 2>) * relate_as_multipleD.size_used, "std::array<uint16_t,2>", "relate_as_multipleD", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<std::array<thingyA_id, 2>*>(output_buffer), relate_as_multipleD.m_left.vptr(), sizeof(std::array<thingyA_id, 2>) * relate_as_multipleD.size_used);
					output_buffer += sizeof(std::array<thingyA_id, 2>) *  relate_as_multipleD.size_used;
				}
				dcon::record_header headerb(0, "$", "relate_as_multipleD", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.relate_as_multipleD__index) {
				dcon::record_header header(sizeof(relate_as_multipleD_id) * relate_as_multipleD.size_used, "uint16_t", "relate_as_multipleD", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<relate_as_multipleD_id*>(output_buffer), relate_as_multipleD.m__index.vptr(), sizeof(relate_as_multipleD_id) * relate_as_multipleD.size_used);
				output_buffer += sizeof(relate_as_multipleD_id) * relate_as_multipleD.size_used;
			}
		}
		
		//
		// deserialize the desired objects, relationships, and properties
		//
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
					if(header.is_object("thingyA")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingyA_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingyA = true;
						}
						else if(header.is_property("some_value")) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingyA.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingyA.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
						}
					} else
					if(header.is_object("thingyB")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingyB_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingyB = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(thingyB.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(thingyB.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.thingyB__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB__index = true;
							}
							if(serialize_selection.thingyB__index == true) {
								thingyB.size_used = 0;
								thingyB.first_free = thingyB_id();
								for(int32_t j = 1200 - 1; j > 0; --j) {
									if(thingyB.m__index.vptr()[j] != thingyB_id(uint16_t(j))) {
										thingyB.m__index.vptr()[j] = thingyB.first_free;
										thingyB.first_free = thingyB_id(uint16_t(j));
									} else {
										thingyB.size_used = std::max(thingyB.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("some_value")) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingyB.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingyB.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
						}
					} else
					if(header.is_object("relate_same")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_same.size_used) {
								relate_same_resize(0);
							}
							relate_same_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_same = true;
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_same.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_same.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_same_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_same.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_same.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_same_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_same.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_same.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_same_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_same_right == true) {
								for(uint32_t i = 0; i < relate_same.size_used; ++i) {
									auto tmp = relate_same.m_right.vptr()[i];
									relate_same.m_right.vptr()[i] = thingyA_id();
									internal_relate_same_set_right(relate_same_id(relate_same_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < relate_same.size_used; ++idx) {
								auto this_key = relate_same_id(relate_same_id::value_base_t(idx));
								if(relate_same_is_valid(relate_same_id(relate_same_id::value_base_t(idx)))) {
									auto key_dat = relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(idx)), relate_same.m_right.vptr()[idx]);
									if(auto it = relate_same.hashm_joint.find(key_dat); it !=  relate_same.hashm_joint.end()) {
										delete_relate_same(it->second);
									}
									relate_same.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_in_array")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_in_array.size_used) {
								relate_in_array_resize(0);
							}
							relate_in_array_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_in_array = true;
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_in_array.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_in_array.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_in_array_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_array.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_in_array.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_array_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_array.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_in_array.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_array_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_in_array_right == true) {
								for(uint32_t i = 0; i < relate_in_array.size_used; ++i) {
									auto tmp = relate_in_array.m_right.vptr()[i];
									relate_in_array.m_right.vptr()[i] = thingyB_id();
									internal_relate_in_array_set_right(relate_in_array_id(relate_in_array_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_in_list")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_in_list.size_used) {
								relate_in_list_resize(0);
							}
							relate_in_list_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_in_list = true;
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_in_list.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_in_list.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_in_list_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_list.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_in_list.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_list_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_list.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_in_list.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_list_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_in_list_right == true) {
								for(uint32_t i = 0; i < relate_in_list.size_used; ++i) {
									auto tmp = relate_in_list.m_right.vptr()[i];
									relate_in_list.m_right.vptr()[i] = thingyB_id();
									internal_relate_in_list_set_right(relate_in_list_id(relate_in_list_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("many_many")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= many_many.size_used) {
								many_many_resize(0);
							}
							many_many_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.many_many = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many__index = true;
							}
							if(serialize_selection.many_many__index == true) {
								many_many.size_used = 0;
								many_many.first_free = many_many_id();
								for(int32_t j = 200 - 1; j > 0; --j) {
									if(many_many.m__index.vptr()[j] != many_many_id(uint16_t(j))) {
										many_many.m__index.vptr()[j] = many_many.first_free;
										many_many.first_free = many_many_id(uint16_t(j));
									} else {
										many_many.size_used = std::max(many_many.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("A")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_A.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_A = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_A.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_A = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_A.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_A = true;
							}
						}
						else if(header.is_property("B")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_B.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_B = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_B.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_B = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_B.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_B = true;
							}
						}
						else if(header.is_property("C")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_C.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_C = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_C.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_C = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_C.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_C = true;
							}
						}
						else if(header.is_property("D")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_D.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_D = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_D.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_D = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_D.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_D = true;
							}
						}
						else if(header.is_property("E")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_E.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_E = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_E.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_E = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_E.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_E = true;
							}
						}
						else if(header.is_property("F")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_F.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_F = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_F.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_F = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_F.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_F = true;
							}
						}
						else if(header.is_property("ignore")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_ignore.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_ignore = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_ignore.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_ignore = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_ignore.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_ignore = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.many_many_A == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_A.vptr()[i];
									many_many.m_A.vptr()[i] = thingyA_id();
									internal_many_many_set_A(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_B == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_B.vptr()[i];
									many_many.m_B.vptr()[i] = thingyA_id();
									internal_many_many_set_B(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_C == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_C.vptr()[i];
									many_many.m_C.vptr()[i] = thingyA_id();
									internal_many_many_set_C(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_D == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_D.vptr()[i];
									many_many.m_D.vptr()[i] = thingyA_id();
									internal_many_many_set_D(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_E == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_E.vptr()[i];
									many_many.m_E.vptr()[i] = thingyA_id();
									internal_many_many_set_E(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_F == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_F.vptr()[i];
									many_many.m_F.vptr()[i] = thingyA_id();
									internal_many_many_set_F(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_ignore == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_ignore.vptr()[i];
									many_many.m_ignore.vptr()[i] = thingyA_id();
									internal_many_many_set_ignore(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < many_many.size_used; ++idx) {
								auto this_key = many_many_id(many_many_id::value_base_t(idx));
								if(many_many_is_valid(many_many_id(many_many_id::value_base_t(idx)))) {
									auto key_dat = many_many.to_joint_keydata(many_many.m_A.vptr()[idx], many_many.m_B.vptr()[idx], many_many.m_C.vptr()[idx], many_many.m_D.vptr()[idx], many_many.m_E.vptr()[idx], many_many.m_F.vptr()[idx]);
									if(auto it = many_many.hashm_joint.find(key_dat); it !=  many_many.hashm_joint.end()) {
										delete_many_many(it->second);
									}
									many_many.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_as_optional")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_optional.size_used) {
								relate_as_optional_resize(0);
							}
							relate_as_optional_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_optional = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional__index = true;
							}
							if(serialize_selection.relate_as_optional__index == true) {
								relate_as_optional.size_used = 0;
								relate_as_optional.first_free = relate_as_optional_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_optional.m__index.vptr()[j] != relate_as_optional_id(uint16_t(j))) {
										relate_as_optional.m__index.vptr()[j] = relate_as_optional.first_free;
										relate_as_optional.first_free = relate_as_optional_id(uint16_t(j));
									} else {
										relate_as_optional.size_used = std::max(relate_as_optional.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_left = true;
							}
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_optional_left == true) {
								for(uint32_t i = 0; i < relate_as_optional.size_used; ++i) {
									auto tmp = relate_as_optional.m_left.vptr()[i];
									relate_as_optional.m_left.vptr()[i] = thingyA_id();
									internal_relate_as_optional_set_left(relate_as_optional_id(relate_as_optional_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.relate_as_optional_right == true) {
								for(uint32_t i = 0; i < relate_as_optional.size_used; ++i) {
									auto tmp = relate_as_optional.m_right.vptr()[i];
									relate_as_optional.m_right.vptr()[i] = thingyB_id();
									internal_relate_as_optional_set_right(relate_as_optional_id(relate_as_optional_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_as_non_optional")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_non_optional.size_used) {
								relate_as_non_optional_resize(0);
							}
							relate_as_non_optional_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_non_optional = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional__index = true;
							}
							if(serialize_selection.relate_as_non_optional__index == true) {
								relate_as_non_optional.size_used = 0;
								relate_as_non_optional.first_free = relate_as_non_optional_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_non_optional.m__index.vptr()[j] != relate_as_non_optional_id(uint16_t(j))) {
										relate_as_non_optional.m__index.vptr()[j] = relate_as_non_optional.first_free;
										relate_as_non_optional.first_free = relate_as_non_optional_id(uint16_t(j));
									} else {
										relate_as_non_optional.size_used = std::max(relate_as_non_optional.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_left = true;
							}
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_non_optional_left == true) {
								for(uint32_t i = 0; i < relate_as_non_optional.size_used; ++i) {
									auto tmp = relate_as_non_optional.m_left.vptr()[i];
									relate_as_non_optional.m_left.vptr()[i] = thingyA_id();
									internal_relate_as_non_optional_set_left(relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.relate_as_non_optional_right == true) {
								for(uint32_t i = 0; i < relate_as_non_optional.size_used; ++i) {
									auto tmp = relate_as_non_optional.m_right.vptr()[i];
									relate_as_non_optional.m_right.vptr()[i] = thingyB_id();
									internal_relate_as_non_optional_set_right(relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleA")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleA.size_used) {
								relate_as_multipleA_resize(0);
							}
							relate_as_multipleA_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleA = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleA.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleA.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleA__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleA.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleA__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleA.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleA__index = true;
							}
							if(serialize_selection.relate_as_multipleA__index == true) {
								relate_as_multipleA.size_used = 0;
								relate_as_multipleA.first_free = relate_as_multipleA_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleA.m__index.vptr()[j] != relate_as_multipleA_id(uint16_t(j))) {
										relate_as_multipleA.m__index.vptr()[j] = relate_as_multipleA.first_free;
										relate_as_multipleA.first_free = relate_as_multipleA_id(uint16_t(j));
									} else {
										relate_as_multipleA.size_used = std::max(relate_as_multipleA.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleA.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleA.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleA_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleA.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleA.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleA_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleA.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleA.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleA_left = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_multipleA_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleA.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleA.m_left.vptr()[i][0];
										relate_as_multipleA.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleA_set_left(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleA.m_left.vptr()[i][1];
										relate_as_multipleA.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleA_set_left(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i)), 1, tmp);
									}
								}
							}
							for(uint32_t idx = 0; idx < relate_as_multipleA.size_used; ++idx) {
								auto this_key = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(idx));
								if(relate_as_multipleA_is_valid(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(idx)))) {
									auto key_dat = relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[idx]);
									if(auto it = relate_as_multipleA.hashm_joint.find(key_dat); it !=  relate_as_multipleA.hashm_joint.end()) {
										delete_relate_as_multipleA(it->second);
									}
									relate_as_multipleA.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleB")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleB.size_used) {
								relate_as_multipleB_resize(0);
							}
							relate_as_multipleB_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleB = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleB.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleB.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleB__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleB__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleB__index = true;
							}
							if(serialize_selection.relate_as_multipleB__index == true) {
								relate_as_multipleB.size_used = 0;
								relate_as_multipleB.first_free = relate_as_multipleB_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleB.m__index.vptr()[j] != relate_as_multipleB_id(uint16_t(j))) {
										relate_as_multipleB.m__index.vptr()[j] = relate_as_multipleB.first_free;
										relate_as_multipleB.first_free = relate_as_multipleB_id(uint16_t(j));
									} else {
										relate_as_multipleB.size_used = std::max(relate_as_multipleB.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleB.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleB.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleB_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleB.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleB.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleB_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleB.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleB.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleB_left = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_multipleB_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleB.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleB.m_left.vptr()[i][0];
										relate_as_multipleB.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleB_set_left(relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleB.m_left.vptr()[i][1];
										relate_as_multipleB.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleB_set_left(relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleC")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleC.size_used) {
								relate_as_multipleC_resize(0);
							}
							relate_as_multipleC_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleC = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleC.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleC.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleC__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleC.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleC__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleC.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleC__index = true;
							}
							if(serialize_selection.relate_as_multipleC__index == true) {
								relate_as_multipleC.size_used = 0;
								relate_as_multipleC.first_free = relate_as_multipleC_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleC.m__index.vptr()[j] != relate_as_multipleC_id(uint16_t(j))) {
										relate_as_multipleC.m__index.vptr()[j] = relate_as_multipleC.first_free;
										relate_as_multipleC.first_free = relate_as_multipleC_id(uint16_t(j));
									} else {
										relate_as_multipleC.size_used = std::max(relate_as_multipleC.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleC.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleC.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleC_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleC.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleC.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleC_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleC.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleC.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleC_left = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_multipleC_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleC.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleC.m_left.vptr()[i][0];
										relate_as_multipleC.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleC_set_left(relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleC.m_left.vptr()[i][1];
										relate_as_multipleC.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleC_set_left(relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleD")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleD.size_used) {
								relate_as_multipleD_resize(0);
							}
							relate_as_multipleD_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleD = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleD.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleD.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleD__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleD.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleD__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleD.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleD__index = true;
							}
							if(serialize_selection.relate_as_multipleD__index == true) {
								relate_as_multipleD.size_used = 0;
								relate_as_multipleD.first_free = relate_as_multipleD_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleD.m__index.vptr()[j] != relate_as_multipleD_id(uint16_t(j))) {
										relate_as_multipleD.m__index.vptr()[j] = relate_as_multipleD.first_free;
										relate_as_multipleD.first_free = relate_as_multipleD_id(uint16_t(j));
									} else {
										relate_as_multipleD.size_used = std::max(relate_as_multipleD.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleD.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleD.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleD_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleD.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleD.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleD_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleD.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleD.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleD_left = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.relate_as_multipleD_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleD.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleD.m_left.vptr()[i][0];
										relate_as_multipleD.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleD_set_left(relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleD.m_left.vptr()[i][1];
										relate_as_multipleD.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleD_set_left(relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					}
				}
				input_buffer += header.record_size;
			}
		}
		
		//
		// deserialize the desired objects, relationships, and properties where the mask is set
		//
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection, load_record const& mask) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
					if(header.is_object("thingyA") && mask.thingyA) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingyA_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingyA = true;
						}
						else if(header.is_property("some_value") && mask.thingyA_some_value) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingyA.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingyA.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingyA.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingyA.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingyA_some_value = true;
							}
						}
					} else
					if(header.is_object("thingyB") && mask.thingyB) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingyB_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingyB = true;
						}
						else if(header.is_property("__index") && mask.thingyB__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(thingyB.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(thingyB.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.thingyB__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB__index = true;
							}
							if(serialize_selection.thingyB__index == true) {
								thingyB.size_used = 0;
								thingyB.first_free = thingyB_id();
								for(int32_t j = 1200 - 1; j > 0; --j) {
									if(thingyB.m__index.vptr()[j] != thingyB_id(uint16_t(j))) {
										thingyB.m__index.vptr()[j] = thingyB.first_free;
										thingyB.first_free = thingyB_id(uint16_t(j));
									} else {
										thingyB.size_used = std::max(thingyB.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("some_value") && mask.thingyB_some_value) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingyB.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingyB.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingyB.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingyB.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingyB_some_value = true;
							}
						}
					} else
					if(header.is_object("relate_same") && mask.relate_same) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_same.size_used) {
								relate_same_resize(0);
							}
							relate_same_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_same = true;
						}
						else if(header.is_property("right") && mask.relate_same_right) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_same.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_same.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_same_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_same.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_same.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_same_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_same.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_same.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_same_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_same) {
							if(serialize_selection.relate_same_right == true) {
								for(uint32_t i = 0; i < relate_same.size_used; ++i) {
									auto tmp = relate_same.m_right.vptr()[i];
									relate_same.m_right.vptr()[i] = thingyA_id();
									internal_relate_same_set_right(relate_same_id(relate_same_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < relate_same.size_used; ++idx) {
								auto this_key = relate_same_id(relate_same_id::value_base_t(idx));
								if(relate_same_is_valid(relate_same_id(relate_same_id::value_base_t(idx)))) {
									auto key_dat = relate_same.to_joint_keydata(thingyA_id(thingyA_id::value_base_t(idx)), relate_same.m_right.vptr()[idx]);
									if(auto it = relate_same.hashm_joint.find(key_dat); it !=  relate_same.hashm_joint.end()) {
										delete_relate_same(it->second);
									}
									relate_same.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_in_array") && mask.relate_in_array) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_in_array.size_used) {
								relate_in_array_resize(0);
							}
							relate_in_array_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_in_array = true;
						}
						else if(header.is_property("right") && mask.relate_in_array_right) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_in_array.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_in_array.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_in_array_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_array.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_in_array.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_array_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_array.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_in_array.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_array_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_in_array) {
							if(serialize_selection.relate_in_array_right == true) {
								for(uint32_t i = 0; i < relate_in_array.size_used; ++i) {
									auto tmp = relate_in_array.m_right.vptr()[i];
									relate_in_array.m_right.vptr()[i] = thingyB_id();
									internal_relate_in_array_set_right(relate_in_array_id(relate_in_array_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_in_list") && mask.relate_in_list) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_in_list.size_used) {
								relate_in_list_resize(0);
							}
							relate_in_list_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_in_list = true;
						}
						else if(header.is_property("right") && mask.relate_in_list_right) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_in_list.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_in_list.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_in_list_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_list.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_in_list.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_list_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_in_list.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_in_list.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_in_list_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_in_list) {
							if(serialize_selection.relate_in_list_right == true) {
								for(uint32_t i = 0; i < relate_in_list.size_used; ++i) {
									auto tmp = relate_in_list.m_right.vptr()[i];
									relate_in_list.m_right.vptr()[i] = thingyB_id();
									internal_relate_in_list_set_right(relate_in_list_id(relate_in_list_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("many_many") && mask.many_many) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= many_many.size_used) {
								many_many_resize(0);
							}
							many_many_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.many_many = true;
						}
						else if(header.is_property("__index") && mask.many_many__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many__index = true;
							}
							if(serialize_selection.many_many__index == true) {
								many_many.size_used = 0;
								many_many.first_free = many_many_id();
								for(int32_t j = 200 - 1; j > 0; --j) {
									if(many_many.m__index.vptr()[j] != many_many_id(uint16_t(j))) {
										many_many.m__index.vptr()[j] = many_many.first_free;
										many_many.first_free = many_many_id(uint16_t(j));
									} else {
										many_many.size_used = std::max(many_many.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("A") && mask.many_many_A) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_A.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_A = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_A.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_A = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_A.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_A = true;
							}
						}
						else if(header.is_property("B") && mask.many_many_B) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_B.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_B = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_B.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_B = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_B.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_B = true;
							}
						}
						else if(header.is_property("C") && mask.many_many_C) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_C.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_C = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_C.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_C = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_C.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_C = true;
							}
						}
						else if(header.is_property("D") && mask.many_many_D) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_D.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_D = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_D.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_D = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_D.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_D = true;
							}
						}
						else if(header.is_property("E") && mask.many_many_E) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_E.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_E = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_E.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_E = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_E.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_E = true;
							}
						}
						else if(header.is_property("F") && mask.many_many_F) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_F.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_F = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_F.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_F = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_F.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_F = true;
							}
						}
						else if(header.is_property("ignore") && mask.many_many_ignore) {
							if(header.is_type("uint16_t")) {
								std::memcpy(many_many.m_ignore.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(many_many.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.many_many_ignore = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									many_many.m_ignore.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_ignore = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(many_many.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									many_many.m_ignore.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.many_many_ignore = true;
							}
						}
						else if(header.is_property("$index_end") && mask.many_many) {
							if(serialize_selection.many_many_A == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_A.vptr()[i];
									many_many.m_A.vptr()[i] = thingyA_id();
									internal_many_many_set_A(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_B == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_B.vptr()[i];
									many_many.m_B.vptr()[i] = thingyA_id();
									internal_many_many_set_B(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_C == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_C.vptr()[i];
									many_many.m_C.vptr()[i] = thingyA_id();
									internal_many_many_set_C(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_D == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_D.vptr()[i];
									many_many.m_D.vptr()[i] = thingyA_id();
									internal_many_many_set_D(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_E == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_E.vptr()[i];
									many_many.m_E.vptr()[i] = thingyA_id();
									internal_many_many_set_E(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_F == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_F.vptr()[i];
									many_many.m_F.vptr()[i] = thingyA_id();
									internal_many_many_set_F(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.many_many_ignore == true) {
								for(uint32_t i = 0; i < many_many.size_used; ++i) {
									auto tmp = many_many.m_ignore.vptr()[i];
									many_many.m_ignore.vptr()[i] = thingyA_id();
									internal_many_many_set_ignore(many_many_id(many_many_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < many_many.size_used; ++idx) {
								auto this_key = many_many_id(many_many_id::value_base_t(idx));
								if(many_many_is_valid(many_many_id(many_many_id::value_base_t(idx)))) {
									auto key_dat = many_many.to_joint_keydata(many_many.m_A.vptr()[idx], many_many.m_B.vptr()[idx], many_many.m_C.vptr()[idx], many_many.m_D.vptr()[idx], many_many.m_E.vptr()[idx], many_many.m_F.vptr()[idx]);
									if(auto it = many_many.hashm_joint.find(key_dat); it !=  many_many.hashm_joint.end()) {
										delete_many_many(it->second);
									}
									many_many.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_as_optional") && mask.relate_as_optional) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_optional.size_used) {
								relate_as_optional_resize(0);
							}
							relate_as_optional_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_optional = true;
						}
						else if(header.is_property("__index") && mask.relate_as_optional__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional__index = true;
							}
							if(serialize_selection.relate_as_optional__index == true) {
								relate_as_optional.size_used = 0;
								relate_as_optional.first_free = relate_as_optional_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_optional.m__index.vptr()[j] != relate_as_optional_id(uint16_t(j))) {
										relate_as_optional.m__index.vptr()[j] = relate_as_optional.first_free;
										relate_as_optional.first_free = relate_as_optional_id(uint16_t(j));
									} else {
										relate_as_optional.size_used = std::max(relate_as_optional.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_optional_left) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_left = true;
							}
						}
						else if(header.is_property("right") && mask.relate_as_optional_right) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_optional.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_optional_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_optional_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_optional) {
							if(serialize_selection.relate_as_optional_left == true) {
								for(uint32_t i = 0; i < relate_as_optional.size_used; ++i) {
									auto tmp = relate_as_optional.m_left.vptr()[i];
									relate_as_optional.m_left.vptr()[i] = thingyA_id();
									internal_relate_as_optional_set_left(relate_as_optional_id(relate_as_optional_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.relate_as_optional_right == true) {
								for(uint32_t i = 0; i < relate_as_optional.size_used; ++i) {
									auto tmp = relate_as_optional.m_right.vptr()[i];
									relate_as_optional.m_right.vptr()[i] = thingyB_id();
									internal_relate_as_optional_set_right(relate_as_optional_id(relate_as_optional_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_as_non_optional") && mask.relate_as_non_optional) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_non_optional.size_used) {
								relate_as_non_optional_resize(0);
							}
							relate_as_non_optional_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_non_optional = true;
						}
						else if(header.is_property("__index") && mask.relate_as_non_optional__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional__index = true;
							}
							if(serialize_selection.relate_as_non_optional__index == true) {
								relate_as_non_optional.size_used = 0;
								relate_as_non_optional.first_free = relate_as_non_optional_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_non_optional.m__index.vptr()[j] != relate_as_non_optional_id(uint16_t(j))) {
										relate_as_non_optional.m__index.vptr()[j] = relate_as_non_optional.first_free;
										relate_as_non_optional.first_free = relate_as_non_optional_id(uint16_t(j));
									} else {
										relate_as_non_optional.size_used = std::max(relate_as_non_optional.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_non_optional_left) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_left = true;
							}
						}
						else if(header.is_property("right") && mask.relate_as_non_optional_right) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_non_optional.m_right.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_non_optional.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_non_optional_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_non_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_right = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_non_optional.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_non_optional.m_right.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_non_optional_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_non_optional) {
							if(serialize_selection.relate_as_non_optional_left == true) {
								for(uint32_t i = 0; i < relate_as_non_optional.size_used; ++i) {
									auto tmp = relate_as_non_optional.m_left.vptr()[i];
									relate_as_non_optional.m_left.vptr()[i] = thingyA_id();
									internal_relate_as_non_optional_set_left(relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.relate_as_non_optional_right == true) {
								for(uint32_t i = 0; i < relate_as_non_optional.size_used; ++i) {
									auto tmp = relate_as_non_optional.m_right.vptr()[i];
									relate_as_non_optional.m_right.vptr()[i] = thingyB_id();
									internal_relate_as_non_optional_set_right(relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(i)), tmp);
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleA") && mask.relate_as_multipleA) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleA.size_used) {
								relate_as_multipleA_resize(0);
							}
							relate_as_multipleA_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleA = true;
						}
						else if(header.is_property("__index") && mask.relate_as_multipleA__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleA.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleA.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleA__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleA.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleA__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleA.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleA__index = true;
							}
							if(serialize_selection.relate_as_multipleA__index == true) {
								relate_as_multipleA.size_used = 0;
								relate_as_multipleA.first_free = relate_as_multipleA_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleA.m__index.vptr()[j] != relate_as_multipleA_id(uint16_t(j))) {
										relate_as_multipleA.m__index.vptr()[j] = relate_as_multipleA.first_free;
										relate_as_multipleA.first_free = relate_as_multipleA_id(uint16_t(j));
									} else {
										relate_as_multipleA.size_used = std::max(relate_as_multipleA.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_multipleA_left) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleA.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleA.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleA_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleA.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleA.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleA_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleA.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleA.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleA.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleA_left = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_multipleA) {
							if(serialize_selection.relate_as_multipleA_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleA.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleA.m_left.vptr()[i][0];
										relate_as_multipleA.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleA_set_left(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleA.m_left.vptr()[i][1];
										relate_as_multipleA.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleA_set_left(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(i)), 1, tmp);
									}
								}
							}
							for(uint32_t idx = 0; idx < relate_as_multipleA.size_used; ++idx) {
								auto this_key = relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(idx));
								if(relate_as_multipleA_is_valid(relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(idx)))) {
									auto key_dat = relate_as_multipleA.to_joint_keydata(relate_as_multipleA.m_left.vptr()[idx]);
									if(auto it = relate_as_multipleA.hashm_joint.find(key_dat); it !=  relate_as_multipleA.hashm_joint.end()) {
										delete_relate_as_multipleA(it->second);
									}
									relate_as_multipleA.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleB") && mask.relate_as_multipleB) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleB.size_used) {
								relate_as_multipleB_resize(0);
							}
							relate_as_multipleB_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleB = true;
						}
						else if(header.is_property("__index") && mask.relate_as_multipleB__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleB.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleB.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleB__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleB__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleB.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleB__index = true;
							}
							if(serialize_selection.relate_as_multipleB__index == true) {
								relate_as_multipleB.size_used = 0;
								relate_as_multipleB.first_free = relate_as_multipleB_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleB.m__index.vptr()[j] != relate_as_multipleB_id(uint16_t(j))) {
										relate_as_multipleB.m__index.vptr()[j] = relate_as_multipleB.first_free;
										relate_as_multipleB.first_free = relate_as_multipleB_id(uint16_t(j));
									} else {
										relate_as_multipleB.size_used = std::max(relate_as_multipleB.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_multipleB_left) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleB.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleB.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleB_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleB.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleB.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleB_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleB.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleB.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleB.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleB_left = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_multipleB) {
							if(serialize_selection.relate_as_multipleB_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleB.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleB.m_left.vptr()[i][0];
										relate_as_multipleB.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleB_set_left(relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleB.m_left.vptr()[i][1];
										relate_as_multipleB.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleB_set_left(relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleC") && mask.relate_as_multipleC) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleC.size_used) {
								relate_as_multipleC_resize(0);
							}
							relate_as_multipleC_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleC = true;
						}
						else if(header.is_property("__index") && mask.relate_as_multipleC__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleC.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleC.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleC__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleC.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleC__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleC.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleC__index = true;
							}
							if(serialize_selection.relate_as_multipleC__index == true) {
								relate_as_multipleC.size_used = 0;
								relate_as_multipleC.first_free = relate_as_multipleC_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleC.m__index.vptr()[j] != relate_as_multipleC_id(uint16_t(j))) {
										relate_as_multipleC.m__index.vptr()[j] = relate_as_multipleC.first_free;
										relate_as_multipleC.first_free = relate_as_multipleC_id(uint16_t(j));
									} else {
										relate_as_multipleC.size_used = std::max(relate_as_multipleC.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_multipleC_left) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleC.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleC.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleC_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleC.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleC.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleC_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleC.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleC.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleC.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleC_left = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_multipleC) {
							if(serialize_selection.relate_as_multipleC_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleC.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleC.m_left.vptr()[i][0];
										relate_as_multipleC.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleC_set_left(relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleC.m_left.vptr()[i][1];
										relate_as_multipleC.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleC_set_left(relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					} else
					if(header.is_object("relate_as_multipleD") && mask.relate_as_multipleD) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= relate_as_multipleD.size_used) {
								relate_as_multipleD_resize(0);
							}
							relate_as_multipleD_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.relate_as_multipleD = true;
						}
						else if(header.is_property("__index") && mask.relate_as_multipleD__index) {
							if(header.is_type("uint16_t")) {
								std::memcpy(relate_as_multipleD.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(relate_as_multipleD.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.relate_as_multipleD__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									relate_as_multipleD.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleD__index = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									relate_as_multipleD.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.relate_as_multipleD__index = true;
							}
							if(serialize_selection.relate_as_multipleD__index == true) {
								relate_as_multipleD.size_used = 0;
								relate_as_multipleD.first_free = relate_as_multipleD_id();
								for(int32_t j = 400 - 1; j > 0; --j) {
									if(relate_as_multipleD.m__index.vptr()[j] != relate_as_multipleD_id(uint16_t(j))) {
										relate_as_multipleD.m__index.vptr()[j] = relate_as_multipleD.first_free;
										relate_as_multipleD.first_free = relate_as_multipleD_id(uint16_t(j));
									} else {
										relate_as_multipleD.size_used = std::max(relate_as_multipleD.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.relate_as_multipleD_left) {
							if(header.is_type("std::array<uint16_t,2>")) {
								std::memcpy(relate_as_multipleD.m_left.vptr(), reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer), std::min(size_t(relate_as_multipleD.size_used) * sizeof(std::array<uint16_t, 2>), header.record_size));
								serialize_selection.relate_as_multipleD_left = true;
							}
							else if(header.is_type("std::array<uint8_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(std::array<uint8_t,2>))); ++i) {
									relate_as_multipleD.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleD.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleD_left = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(relate_as_multipleD.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									relate_as_multipleD.m_left.vptr()[i][0].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									relate_as_multipleD.m_left.vptr()[i][1].value = uint16_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.relate_as_multipleD_left = true;
							}
						}
						else if(header.is_property("$index_end") && mask.relate_as_multipleD) {
							if(serialize_selection.relate_as_multipleD_left == true) {
								for(uint32_t i = 0; i < relate_as_multipleD.size_used; ++i) {
									 {
										auto tmp = relate_as_multipleD.m_left.vptr()[i][0];
										relate_as_multipleD.m_left.vptr()[i][0] = thingyA_id();
										internal_relate_as_multipleD_set_left(relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = relate_as_multipleD.m_left.vptr()[i][1];
										relate_as_multipleD.m_left.vptr()[i][1] = thingyA_id();
										internal_relate_as_multipleD_set_left(relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(i)), 1, tmp);
									}
								}
							}
						}
					}
				}
				input_buffer += header.record_size;
			}
		}
		

	};

	DCON_RELEASE_INLINE int32_t& thingyA_fat_id::get_some_value() const noexcept {
		return container.thingyA_get_some_value(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::set_some_value(int32_t v) const noexcept {
		container.thingyA_set_some_value(id, v);
	}
	DCON_RELEASE_INLINE relate_same_fat_id thingyA_fat_id::get_relate_same_as_left() const noexcept {
		return relate_same_fat_id(container, container.thingyA_get_relate_same_as_left(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_same_as_left() const noexcept {
		container.thingyA_remove_relate_same_as_left(id);
	}
	DCON_RELEASE_INLINE relate_in_array_fat_id thingyA_fat_id::get_relate_in_array_as_left() const noexcept {
		return relate_in_array_fat_id(container, container.thingyA_get_relate_in_array_as_left(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_in_array_as_left() const noexcept {
		container.thingyA_remove_relate_in_array_as_left(id);
	}
	DCON_RELEASE_INLINE relate_in_array_fat_id thingyA_fat_id::get_relate_in_array() const noexcept {
		return relate_in_array_fat_id(container, container.thingyA_get_relate_in_array(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_in_array() const noexcept {
		container.thingyA_remove_relate_in_array(id);
	}
	DCON_RELEASE_INLINE thingyB_fat_id thingyA_fat_id::get_right_from_relate_in_array() const noexcept {
		return thingyB_fat_id(container, container.thingyA_get_right_from_relate_in_array(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::set_right_from_relate_in_array(thingyB_id v) const noexcept {
		container.thingyA_set_right_from_relate_in_array(id, v);
	}
	DCON_RELEASE_INLINE relate_in_list_fat_id thingyA_fat_id::get_relate_in_list_as_left() const noexcept {
		return relate_in_list_fat_id(container, container.thingyA_get_relate_in_list_as_left(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_in_list_as_left() const noexcept {
		container.thingyA_remove_relate_in_list_as_left(id);
	}
	DCON_RELEASE_INLINE relate_in_list_fat_id thingyA_fat_id::get_relate_in_list() const noexcept {
		return relate_in_list_fat_id(container, container.thingyA_get_relate_in_list(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_in_list() const noexcept {
		container.thingyA_remove_relate_in_list(id);
	}
	DCON_RELEASE_INLINE thingyB_fat_id thingyA_fat_id::get_right_from_relate_in_list() const noexcept {
		return thingyB_fat_id(container, container.thingyA_get_right_from_relate_in_list(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::set_right_from_relate_in_list(thingyB_id v) const noexcept {
		container.thingyA_set_right_from_relate_in_list(id, v);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_optional_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_optional_as_left(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_fat_id::range_of_relate_as_optional_as_left() const {
		return container.thingyA_range_of_relate_as_optional_as_left(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_optional_as_left() const noexcept {
		container.thingyA_remove_all_relate_as_optional_as_left(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_fat_id::get_relate_as_optional_as_left() const {
		return internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_optional(T&& func) const {
		container.thingyA_for_each_relate_as_optional(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_fat_id::range_of_relate_as_optional() const {
		return container.thingyA_range_of_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_optional() const noexcept {
		container.thingyA_remove_all_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_fat_id::get_relate_as_optional() const {
		return internal::iterator_thingyA_foreach_relate_as_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_right_from_relate_as_optional(T&& func) const {
		container.thingyA_for_each_right_from_relate_as_optional(id, [&, t = this](thingyB_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyA_fat_id::has_right_from_relate_as_optional(thingyB_id target) const {
		return container.thingyA_has_right_from_relate_as_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_non_optional_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_non_optional_as_left(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_fat_id::range_of_relate_as_non_optional_as_left() const {
		return container.thingyA_range_of_relate_as_non_optional_as_left(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_non_optional_as_left() const noexcept {
		container.thingyA_remove_all_relate_as_non_optional_as_left(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_fat_id::get_relate_as_non_optional_as_left() const {
		return internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_non_optional(T&& func) const {
		container.thingyA_for_each_relate_as_non_optional(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_fat_id::range_of_relate_as_non_optional() const {
		return container.thingyA_range_of_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_non_optional() const noexcept {
		container.thingyA_remove_all_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_fat_id::get_relate_as_non_optional() const {
		return internal::iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_right_from_relate_as_non_optional(T&& func) const {
		container.thingyA_for_each_right_from_relate_as_non_optional(id, [&, t = this](thingyB_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyA_fat_id::has_right_from_relate_as_non_optional(thingyB_id target) const {
		return container.thingyA_has_right_from_relate_as_non_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_multipleA_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_multipleA_as_left(id, [&, t = this](relate_as_multipleA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_fat_id::range_of_relate_as_multipleA_as_left() const {
		return container.thingyA_range_of_relate_as_multipleA_as_left(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_multipleA_as_left() const noexcept {
		container.thingyA_remove_all_relate_as_multipleA_as_left(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_fat_id::get_relate_as_multipleA_as_left() const {
		return internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_multipleA(T&& func) const {
		container.thingyA_for_each_relate_as_multipleA(id, [&, t = this](relate_as_multipleA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_fat_id::range_of_relate_as_multipleA() const {
		return container.thingyA_range_of_relate_as_multipleA(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_multipleA() const noexcept {
		container.thingyA_remove_all_relate_as_multipleA(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_fat_id::get_relate_as_multipleA() const {
		return internal::iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(container, id);
	}
	DCON_RELEASE_INLINE relate_as_multipleB_fat_id thingyA_fat_id::get_relate_as_multipleB_as_left() const noexcept {
		return relate_as_multipleB_fat_id(container, container.thingyA_get_relate_as_multipleB_as_left(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_as_multipleB_as_left() const noexcept {
		container.thingyA_remove_relate_as_multipleB_as_left(id);
	}
	DCON_RELEASE_INLINE relate_as_multipleB_fat_id thingyA_fat_id::get_relate_as_multipleB() const noexcept {
		return relate_as_multipleB_fat_id(container, container.thingyA_get_relate_as_multipleB(id));
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_relate_as_multipleB() const noexcept {
		container.thingyA_remove_relate_as_multipleB(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_multipleC_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_multipleC_as_left(id, [&, t = this](relate_as_multipleC_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_fat_id::range_of_relate_as_multipleC_as_left() const {
		return container.thingyA_range_of_relate_as_multipleC_as_left(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_multipleC_as_left() const noexcept {
		container.thingyA_remove_all_relate_as_multipleC_as_left(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_fat_id::get_relate_as_multipleC_as_left() const {
		return internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_fat_id::for_each_relate_as_multipleC(T&& func) const {
		container.thingyA_for_each_relate_as_multipleC(id, [&, t = this](relate_as_multipleC_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_fat_id::range_of_relate_as_multipleC() const {
		return container.thingyA_range_of_relate_as_multipleC(id);
	}
	DCON_RELEASE_INLINE void thingyA_fat_id::remove_all_relate_as_multipleC() const noexcept {
		container.thingyA_remove_all_relate_as_multipleC(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_fat_id::get_relate_as_multipleC() const {
		return internal::iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(container, id);
	}
	DCON_RELEASE_INLINE bool thingyA_fat_id::is_valid() const noexcept {
		return container.thingyA_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t thingyA_const_fat_id::get_some_value() const noexcept {
		return container.thingyA_get_some_value(id);
	}
	DCON_RELEASE_INLINE relate_same_const_fat_id thingyA_const_fat_id::get_relate_same_as_left() const noexcept {
		return relate_same_const_fat_id(container, container.thingyA_get_relate_same_as_left(id));
	}
	DCON_RELEASE_INLINE relate_in_array_const_fat_id thingyA_const_fat_id::get_relate_in_array_as_left() const noexcept {
		return relate_in_array_const_fat_id(container, container.thingyA_get_relate_in_array_as_left(id));
	}
	DCON_RELEASE_INLINE relate_in_array_const_fat_id thingyA_const_fat_id::get_relate_in_array() const noexcept {
		return relate_in_array_const_fat_id(container, container.thingyA_get_relate_in_array(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id thingyA_const_fat_id::get_right_from_relate_in_array() const noexcept {
		return thingyB_const_fat_id(container, container.thingyA_get_right_from_relate_in_array(id));
	}
	DCON_RELEASE_INLINE relate_in_list_const_fat_id thingyA_const_fat_id::get_relate_in_list_as_left() const noexcept {
		return relate_in_list_const_fat_id(container, container.thingyA_get_relate_in_list_as_left(id));
	}
	DCON_RELEASE_INLINE relate_in_list_const_fat_id thingyA_const_fat_id::get_relate_in_list() const noexcept {
		return relate_in_list_const_fat_id(container, container.thingyA_get_relate_in_list(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id thingyA_const_fat_id::get_right_from_relate_in_list() const noexcept {
		return thingyB_const_fat_id(container, container.thingyA_get_right_from_relate_in_list(id));
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_optional_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_optional_as_left(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_const_fat_id::range_of_relate_as_optional_as_left() const {
		return container.thingyA_range_of_relate_as_optional_as_left(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_const_fat_id::get_relate_as_optional_as_left() const {
		return internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_optional(T&& func) const {
		container.thingyA_for_each_relate_as_optional(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyA_const_fat_id::range_of_relate_as_optional() const {
		return container.thingyA_range_of_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator thingyA_const_fat_id::get_relate_as_optional() const {
		return internal::const_iterator_thingyA_foreach_relate_as_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_right_from_relate_as_optional(T&& func) const {
		container.thingyA_for_each_right_from_relate_as_optional(id, [&, t = this](thingyB_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyA_const_fat_id::has_right_from_relate_as_optional(thingyB_id target) const {
		return container.thingyA_has_right_from_relate_as_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_non_optional_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_non_optional_as_left(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_const_fat_id::range_of_relate_as_non_optional_as_left() const {
		return container.thingyA_range_of_relate_as_non_optional_as_left(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_const_fat_id::get_relate_as_non_optional_as_left() const {
		return internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_non_optional(T&& func) const {
		container.thingyA_for_each_relate_as_non_optional(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyA_const_fat_id::range_of_relate_as_non_optional() const {
		return container.thingyA_range_of_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator thingyA_const_fat_id::get_relate_as_non_optional() const {
		return internal::const_iterator_thingyA_foreach_relate_as_non_optional_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_right_from_relate_as_non_optional(T&& func) const {
		container.thingyA_for_each_right_from_relate_as_non_optional(id, [&, t = this](thingyB_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyA_const_fat_id::has_right_from_relate_as_non_optional(thingyB_id target) const {
		return container.thingyA_has_right_from_relate_as_non_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_multipleA_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_multipleA_as_left(id, [&, t = this](relate_as_multipleA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_const_fat_id::range_of_relate_as_multipleA_as_left() const {
		return container.thingyA_range_of_relate_as_multipleA_as_left(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_const_fat_id::get_relate_as_multipleA_as_left() const {
		return internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_multipleA(T&& func) const {
		container.thingyA_for_each_relate_as_multipleA(id, [&, t = this](relate_as_multipleA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleA_id const*, relate_as_multipleA_id const*> thingyA_const_fat_id::range_of_relate_as_multipleA() const {
		return container.thingyA_range_of_relate_as_multipleA(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator thingyA_const_fat_id::get_relate_as_multipleA() const {
		return internal::const_iterator_thingyA_foreach_relate_as_multipleA_as_left_generator(container, id);
	}
	DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id thingyA_const_fat_id::get_relate_as_multipleB_as_left() const noexcept {
		return relate_as_multipleB_const_fat_id(container, container.thingyA_get_relate_as_multipleB_as_left(id));
	}
	DCON_RELEASE_INLINE relate_as_multipleB_const_fat_id thingyA_const_fat_id::get_relate_as_multipleB() const noexcept {
		return relate_as_multipleB_const_fat_id(container, container.thingyA_get_relate_as_multipleB(id));
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_multipleC_as_left(T&& func) const {
		container.thingyA_for_each_relate_as_multipleC_as_left(id, [&, t = this](relate_as_multipleC_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_const_fat_id::range_of_relate_as_multipleC_as_left() const {
		return container.thingyA_range_of_relate_as_multipleC_as_left(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_const_fat_id::get_relate_as_multipleC_as_left() const {
		return internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyA_const_fat_id::for_each_relate_as_multipleC(T&& func) const {
		container.thingyA_for_each_relate_as_multipleC(id, [&, t = this](relate_as_multipleC_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_multipleC_id const*, relate_as_multipleC_id const*> thingyA_const_fat_id::range_of_relate_as_multipleC() const {
		return container.thingyA_range_of_relate_as_multipleC(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator thingyA_const_fat_id::get_relate_as_multipleC() const {
		return internal::const_iterator_thingyA_foreach_relate_as_multipleC_as_left_generator(container, id);
	}
	DCON_RELEASE_INLINE bool thingyA_const_fat_id::is_valid() const noexcept {
		return container.thingyA_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t& thingyB_fat_id::get_some_value() const noexcept {
		return container.thingyB_get_some_value(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::set_some_value(int32_t v) const noexcept {
		container.thingyB_set_some_value(id, v);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_in_array_as_right(T&& func) const {
		container.thingyB_for_each_relate_in_array_as_right(id, [&, t = this](relate_in_array_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_fat_id::range_of_relate_in_array_as_right() const {
		return container.thingyB_range_of_relate_in_array_as_right(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_in_array_as_right() const noexcept {
		container.thingyB_remove_all_relate_in_array_as_right(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_fat_id::get_relate_in_array_as_right() const {
		return internal::iterator_thingyB_foreach_relate_in_array_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_in_array(T&& func) const {
		container.thingyB_for_each_relate_in_array(id, [&, t = this](relate_in_array_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_fat_id::range_of_relate_in_array() const {
		return container.thingyB_range_of_relate_in_array(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_in_array() const noexcept {
		container.thingyB_remove_all_relate_in_array(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_fat_id::get_relate_in_array() const {
		return internal::iterator_thingyB_foreach_relate_in_array_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_left_from_relate_in_array(T&& func) const {
		container.thingyB_for_each_left_from_relate_in_array(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_fat_id::has_left_from_relate_in_array(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_in_array(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_in_list_as_right(T&& func) const {
		container.thingyB_for_each_relate_in_list_as_right(id, [&, t = this](relate_in_list_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_in_list_as_right() const noexcept {
		container.thingyB_remove_all_relate_in_list_as_right(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_fat_id::get_relate_in_list_as_right() const {
		return internal::iterator_thingyB_foreach_relate_in_list_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_in_list(T&& func) const {
		container.thingyB_for_each_relate_in_list(id, [&, t = this](relate_in_list_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_in_list() const noexcept {
		container.thingyB_remove_all_relate_in_list(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_fat_id::get_relate_in_list() const {
		return internal::iterator_thingyB_foreach_relate_in_list_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_left_from_relate_in_list(T&& func) const {
		container.thingyB_for_each_left_from_relate_in_list(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_fat_id::has_left_from_relate_in_list(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_in_list(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_as_optional_as_right(T&& func) const {
		container.thingyB_for_each_relate_as_optional_as_right(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_fat_id::range_of_relate_as_optional_as_right() const {
		return container.thingyB_range_of_relate_as_optional_as_right(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_as_optional_as_right() const noexcept {
		container.thingyB_remove_all_relate_as_optional_as_right(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_fat_id::get_relate_as_optional_as_right() const {
		return internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_as_optional(T&& func) const {
		container.thingyB_for_each_relate_as_optional(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_fat_id::range_of_relate_as_optional() const {
		return container.thingyB_range_of_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_as_optional() const noexcept {
		container.thingyB_remove_all_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_fat_id::get_relate_as_optional() const {
		return internal::iterator_thingyB_foreach_relate_as_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_left_from_relate_as_optional(T&& func) const {
		container.thingyB_for_each_left_from_relate_as_optional(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_fat_id::has_left_from_relate_as_optional(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_as_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_as_non_optional_as_right(T&& func) const {
		container.thingyB_for_each_relate_as_non_optional_as_right(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_fat_id::range_of_relate_as_non_optional_as_right() const {
		return container.thingyB_range_of_relate_as_non_optional_as_right(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_as_non_optional_as_right() const noexcept {
		container.thingyB_remove_all_relate_as_non_optional_as_right(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_fat_id::get_relate_as_non_optional_as_right() const {
		return internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_relate_as_non_optional(T&& func) const {
		container.thingyB_for_each_relate_as_non_optional(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_fat_id::range_of_relate_as_non_optional() const {
		return container.thingyB_range_of_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE void thingyB_fat_id::remove_all_relate_as_non_optional() const noexcept {
		container.thingyB_remove_all_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_fat_id::get_relate_as_non_optional() const {
		return internal::iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_fat_id::for_each_left_from_relate_as_non_optional(T&& func) const {
		container.thingyB_for_each_left_from_relate_as_non_optional(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_fat_id::has_left_from_relate_as_non_optional(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_as_non_optional(id, target);
	}
	DCON_RELEASE_INLINE bool thingyB_fat_id::is_valid() const noexcept {
		return container.thingyB_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t thingyB_const_fat_id::get_some_value() const noexcept {
		return container.thingyB_get_some_value(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_in_array_as_right(T&& func) const {
		container.thingyB_for_each_relate_in_array_as_right(id, [&, t = this](relate_in_array_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_const_fat_id::range_of_relate_in_array_as_right() const {
		return container.thingyB_range_of_relate_in_array_as_right(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_const_fat_id::get_relate_in_array_as_right() const {
		return internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_in_array(T&& func) const {
		container.thingyB_for_each_relate_in_array(id, [&, t = this](relate_in_array_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_in_array_id const*, relate_in_array_id const*> thingyB_const_fat_id::range_of_relate_in_array() const {
		return container.thingyB_range_of_relate_in_array(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator thingyB_const_fat_id::get_relate_in_array() const {
		return internal::const_iterator_thingyB_foreach_relate_in_array_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_left_from_relate_in_array(T&& func) const {
		container.thingyB_for_each_left_from_relate_in_array(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_const_fat_id::has_left_from_relate_in_array(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_in_array(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_in_list_as_right(T&& func) const {
		container.thingyB_for_each_relate_in_list_as_right(id, [&, t = this](relate_in_list_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_const_fat_id::get_relate_in_list_as_right() const {
		return internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_in_list(T&& func) const {
		container.thingyB_for_each_relate_in_list(id, [&, t = this](relate_in_list_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator thingyB_const_fat_id::get_relate_in_list() const {
		return internal::const_iterator_thingyB_foreach_relate_in_list_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_left_from_relate_in_list(T&& func) const {
		container.thingyB_for_each_left_from_relate_in_list(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_const_fat_id::has_left_from_relate_in_list(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_in_list(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_as_optional_as_right(T&& func) const {
		container.thingyB_for_each_relate_as_optional_as_right(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_const_fat_id::range_of_relate_as_optional_as_right() const {
		return container.thingyB_range_of_relate_as_optional_as_right(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_const_fat_id::get_relate_as_optional_as_right() const {
		return internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_as_optional(T&& func) const {
		container.thingyB_for_each_relate_as_optional(id, [&, t = this](relate_as_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_optional_id const*, relate_as_optional_id const*> thingyB_const_fat_id::range_of_relate_as_optional() const {
		return container.thingyB_range_of_relate_as_optional(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator thingyB_const_fat_id::get_relate_as_optional() const {
		return internal::const_iterator_thingyB_foreach_relate_as_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_left_from_relate_as_optional(T&& func) const {
		container.thingyB_for_each_left_from_relate_as_optional(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_const_fat_id::has_left_from_relate_as_optional(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_as_optional(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_as_non_optional_as_right(T&& func) const {
		container.thingyB_for_each_relate_as_non_optional_as_right(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_const_fat_id::range_of_relate_as_non_optional_as_right() const {
		return container.thingyB_range_of_relate_as_non_optional_as_right(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_const_fat_id::get_relate_as_non_optional_as_right() const {
		return internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_relate_as_non_optional(T&& func) const {
		container.thingyB_for_each_relate_as_non_optional(id, [&, t = this](relate_as_non_optional_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<relate_as_non_optional_id const*, relate_as_non_optional_id const*> thingyB_const_fat_id::range_of_relate_as_non_optional() const {
		return container.thingyB_range_of_relate_as_non_optional(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator thingyB_const_fat_id::get_relate_as_non_optional() const {
		return internal::const_iterator_thingyB_foreach_relate_as_non_optional_as_right_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingyB_const_fat_id::for_each_left_from_relate_as_non_optional(T&& func) const {
		container.thingyB_for_each_left_from_relate_as_non_optional(id, [&, t = this](thingyA_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingyB_const_fat_id::has_left_from_relate_as_non_optional(thingyA_id target) const {
		return container.thingyB_has_left_from_relate_as_non_optional(id, target);
	}
	DCON_RELEASE_INLINE bool thingyB_const_fat_id::is_valid() const noexcept {
		return container.thingyB_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_same_fat_id::get_left() const noexcept {
		return thingyA_fat_id(container, container.relate_same_get_left(id));
	}
	DCON_RELEASE_INLINE void relate_same_fat_id::set_left(thingyA_id val) const noexcept {
		container.relate_same_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_same_fat_id::try_set_left(thingyA_id val) const noexcept {
		return container.relate_same_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id relate_same_fat_id::get_right() const noexcept {
		return thingyA_fat_id(container, container.relate_same_get_right(id));
	}
	DCON_RELEASE_INLINE void relate_same_fat_id::set_right(thingyA_id val) const noexcept {
		container.relate_same_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_same_fat_id::try_set_right(thingyA_id val) const noexcept {
		return container.relate_same_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_same_fat_id::is_valid() const noexcept {
		return container.relate_same_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_same_const_fat_id::get_left() const noexcept {
		return thingyA_const_fat_id(container, container.relate_same_get_left(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_same_const_fat_id::get_right() const noexcept {
		return thingyA_const_fat_id(container, container.relate_same_get_right(id));
	}
	DCON_RELEASE_INLINE bool relate_same_const_fat_id::is_valid() const noexcept {
		return container.relate_same_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_in_array_fat_id::get_left() const noexcept {
		return thingyA_fat_id(container, container.relate_in_array_get_left(id));
	}
	DCON_RELEASE_INLINE void relate_in_array_fat_id::set_left(thingyA_id val) const noexcept {
		container.relate_in_array_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_array_fat_id::try_set_left(thingyA_id val) const noexcept {
		return container.relate_in_array_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingyB_fat_id relate_in_array_fat_id::get_right() const noexcept {
		return thingyB_fat_id(container, container.relate_in_array_get_right(id));
	}
	DCON_RELEASE_INLINE void relate_in_array_fat_id::set_right(thingyB_id val) const noexcept {
		container.relate_in_array_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_array_fat_id::try_set_right(thingyB_id val) const noexcept {
		return container.relate_in_array_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_array_fat_id::is_valid() const noexcept {
		return container.relate_in_array_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_in_array_const_fat_id::get_left() const noexcept {
		return thingyA_const_fat_id(container, container.relate_in_array_get_left(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id relate_in_array_const_fat_id::get_right() const noexcept {
		return thingyB_const_fat_id(container, container.relate_in_array_get_right(id));
	}
	DCON_RELEASE_INLINE bool relate_in_array_const_fat_id::is_valid() const noexcept {
		return container.relate_in_array_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_in_list_fat_id::get_left() const noexcept {
		return thingyA_fat_id(container, container.relate_in_list_get_left(id));
	}
	DCON_RELEASE_INLINE void relate_in_list_fat_id::set_left(thingyA_id val) const noexcept {
		container.relate_in_list_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_list_fat_id::try_set_left(thingyA_id val) const noexcept {
		return container.relate_in_list_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingyB_fat_id relate_in_list_fat_id::get_right() const noexcept {
		return thingyB_fat_id(container, container.relate_in_list_get_right(id));
	}
	DCON_RELEASE_INLINE void relate_in_list_fat_id::set_right(thingyB_id val) const noexcept {
		container.relate_in_list_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_list_fat_id::try_set_right(thingyB_id val) const noexcept {
		return container.relate_in_list_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_in_list_fat_id::is_valid() const noexcept {
		return container.relate_in_list_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_in_list_const_fat_id::get_left() const noexcept {
		return thingyA_const_fat_id(container, container.relate_in_list_get_left(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id relate_in_list_const_fat_id::get_right() const noexcept {
		return thingyB_const_fat_id(container, container.relate_in_list_get_right(id));
	}
	DCON_RELEASE_INLINE bool relate_in_list_const_fat_id::is_valid() const noexcept {
		return container.relate_in_list_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_A() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_A(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_A(thingyA_id val) const noexcept {
		container.many_many_set_A(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_A(thingyA_id val) const noexcept {
		return container.many_many_try_set_A(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_B() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_B(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_B(thingyA_id val) const noexcept {
		container.many_many_set_B(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_B(thingyA_id val) const noexcept {
		return container.many_many_try_set_B(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_C() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_C(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_C(thingyA_id val) const noexcept {
		container.many_many_set_C(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_C(thingyA_id val) const noexcept {
		return container.many_many_try_set_C(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_D() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_D(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_D(thingyA_id val) const noexcept {
		container.many_many_set_D(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_D(thingyA_id val) const noexcept {
		return container.many_many_try_set_D(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_E() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_E(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_E(thingyA_id val) const noexcept {
		container.many_many_set_E(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_E(thingyA_id val) const noexcept {
		return container.many_many_try_set_E(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_F() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_F(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_F(thingyA_id val) const noexcept {
		container.many_many_set_F(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_F(thingyA_id val) const noexcept {
		return container.many_many_try_set_F(id, val);
	}
	DCON_RELEASE_INLINE thingyA_fat_id many_many_fat_id::get_ignore() const noexcept {
		return thingyA_fat_id(container, container.many_many_get_ignore(id));
	}
	DCON_RELEASE_INLINE void many_many_fat_id::set_ignore(thingyA_id val) const noexcept {
		container.many_many_set_ignore(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::try_set_ignore(thingyA_id val) const noexcept {
		return container.many_many_try_set_ignore(id, val);
	}
	DCON_RELEASE_INLINE bool many_many_fat_id::is_valid() const noexcept {
		return container.many_many_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_A() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_A(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_B() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_B(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_C() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_C(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_D() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_D(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_E() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_E(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_F() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_F(id));
	}
	DCON_RELEASE_INLINE thingyA_const_fat_id many_many_const_fat_id::get_ignore() const noexcept {
		return thingyA_const_fat_id(container, container.many_many_get_ignore(id));
	}
	DCON_RELEASE_INLINE bool many_many_const_fat_id::is_valid() const noexcept {
		return container.many_many_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_optional_fat_id::get_left() const noexcept {
		return thingyA_fat_id(container, container.relate_as_optional_get_left(id));
	}
	DCON_RELEASE_INLINE void relate_as_optional_fat_id::set_left(thingyA_id val) const noexcept {
		container.relate_as_optional_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_optional_fat_id::try_set_left(thingyA_id val) const noexcept {
		return container.relate_as_optional_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingyB_fat_id relate_as_optional_fat_id::get_right() const noexcept {
		return thingyB_fat_id(container, container.relate_as_optional_get_right(id));
	}
	DCON_RELEASE_INLINE void relate_as_optional_fat_id::set_right(thingyB_id val) const noexcept {
		container.relate_as_optional_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_optional_fat_id::try_set_right(thingyB_id val) const noexcept {
		return container.relate_as_optional_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_optional_fat_id::is_valid() const noexcept {
		return container.relate_as_optional_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_optional_const_fat_id::get_left() const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_optional_get_left(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id relate_as_optional_const_fat_id::get_right() const noexcept {
		return thingyB_const_fat_id(container, container.relate_as_optional_get_right(id));
	}
	DCON_RELEASE_INLINE bool relate_as_optional_const_fat_id::is_valid() const noexcept {
		return container.relate_as_optional_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_non_optional_fat_id::get_left() const noexcept {
		return thingyA_fat_id(container, container.relate_as_non_optional_get_left(id));
	}
	DCON_RELEASE_INLINE void relate_as_non_optional_fat_id::set_left(thingyA_id val) const noexcept {
		container.relate_as_non_optional_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_non_optional_fat_id::try_set_left(thingyA_id val) const noexcept {
		return container.relate_as_non_optional_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingyB_fat_id relate_as_non_optional_fat_id::get_right() const noexcept {
		return thingyB_fat_id(container, container.relate_as_non_optional_get_right(id));
	}
	DCON_RELEASE_INLINE void relate_as_non_optional_fat_id::set_right(thingyB_id val) const noexcept {
		container.relate_as_non_optional_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_non_optional_fat_id::try_set_right(thingyB_id val) const noexcept {
		return container.relate_as_non_optional_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_non_optional_fat_id::is_valid() const noexcept {
		return container.relate_as_non_optional_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_non_optional_const_fat_id::get_left() const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_non_optional_get_left(id));
	}
	DCON_RELEASE_INLINE thingyB_const_fat_id relate_as_non_optional_const_fat_id::get_right() const noexcept {
		return thingyB_const_fat_id(container, container.relate_as_non_optional_get_right(id));
	}
	DCON_RELEASE_INLINE bool relate_as_non_optional_const_fat_id::is_valid() const noexcept {
		return container.relate_as_non_optional_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_multipleA_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_fat_id(container, container.relate_as_multipleA_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleA_has_left(id, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleA_fat_id::set_left(int32_t i, thingyA_id val) const noexcept {
		container.relate_as_multipleA_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_fat_id::try_set_left(int32_t i, thingyA_id val) const noexcept {
		return container.relate_as_multipleA_try_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleA_fat_id::replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		container.relate_as_multipleA_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_fat_id::try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		return container.relate_as_multipleA_try_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleA_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_multipleA_const_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_multipleA_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_const_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleA_has_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleA_const_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleA_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_multipleB_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_fat_id(container, container.relate_as_multipleB_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleB_has_left(id, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleB_fat_id::set_left(int32_t i, thingyA_id val) const noexcept {
		container.relate_as_multipleB_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_fat_id::try_set_left(int32_t i, thingyA_id val) const noexcept {
		return container.relate_as_multipleB_try_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleB_fat_id::replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		container.relate_as_multipleB_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_fat_id::try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		return container.relate_as_multipleB_try_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleB_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_multipleB_const_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_multipleB_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_const_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleB_has_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleB_const_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleB_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_multipleC_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_fat_id(container, container.relate_as_multipleC_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleC_has_left(id, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleC_fat_id::set_left(int32_t i, thingyA_id val) const noexcept {
		container.relate_as_multipleC_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_fat_id::try_set_left(int32_t i, thingyA_id val) const noexcept {
		return container.relate_as_multipleC_try_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleC_fat_id::replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		container.relate_as_multipleC_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_fat_id::try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		return container.relate_as_multipleC_try_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleC_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_multipleC_const_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_multipleC_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_const_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleC_has_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleC_const_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleC_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_fat_id relate_as_multipleD_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_fat_id(container, container.relate_as_multipleD_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleD_has_left(id, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleD_fat_id::set_left(int32_t i, thingyA_id val) const noexcept {
		container.relate_as_multipleD_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_fat_id::try_set_left(int32_t i, thingyA_id val) const noexcept {
		return container.relate_as_multipleD_try_set_left(id, i, val);
	}
	DCON_RELEASE_INLINE void relate_as_multipleD_fat_id::replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		container.relate_as_multipleD_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_fat_id::try_replace_left(thingyA_id newval, thingyA_id oldval) const noexcept {
		return container.relate_as_multipleD_try_replace_left(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleD_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingyA_const_fat_id relate_as_multipleD_const_fat_id::get_left(int32_t i) const noexcept {
		return thingyA_const_fat_id(container, container.relate_as_multipleD_get_left(id, i));
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_const_fat_id::has_left(thingyA_id val) const noexcept {
		return container.relate_as_multipleD_has_left(id, val);
	}
	DCON_RELEASE_INLINE bool relate_as_multipleD_const_fat_id::is_valid() const noexcept {
		return container.relate_as_multipleD_is_valid(id);
	}
	

	namespace internal {
		DCON_RELEASE_INLINE object_iterator_thingyA::object_iterator_thingyA(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyA::const_object_iterator_thingyA(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_thingyA& object_iterator_thingyA::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyA& const_object_iterator_thingyA::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_thingyA& object_iterator_thingyA::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyA& const_object_iterator_thingyA::operator--() noexcept {
			--index;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left::iterator_thingyA_foreach_relate_as_optional_as_left(data_container& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.left_storage, container.relate_as_optional.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left::iterator_thingyA_foreach_relate_as_optional_as_left(data_container& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.left_storage, container.relate_as_optional.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& iterator_thingyA_foreach_relate_as_optional_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_optional_as_left& iterator_thingyA_foreach_relate_as_optional_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left::const_iterator_thingyA_foreach_relate_as_optional_as_left(data_container const& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.left_storage, container.relate_as_optional.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left::const_iterator_thingyA_foreach_relate_as_optional_as_left(data_container const& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.left_storage, container.relate_as_optional.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& const_iterator_thingyA_foreach_relate_as_optional_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_optional_as_left& const_iterator_thingyA_foreach_relate_as_optional_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left::iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.left_storage, container.relate_as_non_optional.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left::iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.left_storage, container.relate_as_non_optional.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& iterator_thingyA_foreach_relate_as_non_optional_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_non_optional_as_left& iterator_thingyA_foreach_relate_as_non_optional_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left::const_iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container const& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.left_storage, container.relate_as_non_optional.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left::const_iterator_thingyA_foreach_relate_as_non_optional_as_left(data_container const& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.left_storage, container.relate_as_non_optional.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& const_iterator_thingyA_foreach_relate_as_non_optional_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_non_optional_as_left& const_iterator_thingyA_foreach_relate_as_non_optional_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left::iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleA.left_storage, container.relate_as_multipleA.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left::iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleA.left_storage, container.relate_as_multipleA.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& iterator_thingyA_foreach_relate_as_multipleA_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleA_as_left& iterator_thingyA_foreach_relate_as_multipleA_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left::const_iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container const& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleA.left_storage, container.relate_as_multipleA.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left::const_iterator_thingyA_foreach_relate_as_multipleA_as_left(data_container const& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleA.left_storage, container.relate_as_multipleA.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& const_iterator_thingyA_foreach_relate_as_multipleA_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleA_as_left& const_iterator_thingyA_foreach_relate_as_multipleA_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left::iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleC.left_storage, container.relate_as_multipleC.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left::iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleC.left_storage, container.relate_as_multipleC.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& iterator_thingyA_foreach_relate_as_multipleC_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyA_foreach_relate_as_multipleC_as_left& iterator_thingyA_foreach_relate_as_multipleC_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left::const_iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container const& c,  thingyA_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleC.left_storage, container.relate_as_multipleC.m_array_left.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left::const_iterator_thingyA_foreach_relate_as_multipleC_as_left(data_container const& c, thingyA_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_multipleC.left_storage, container.relate_as_multipleC.m_array_left.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& const_iterator_thingyA_foreach_relate_as_multipleC_as_left::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyA_foreach_relate_as_multipleC_as_left& const_iterator_thingyA_foreach_relate_as_multipleC_as_left::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_thingyB::object_iterator_thingyB(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyB::const_object_iterator_thingyB(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_thingyB& object_iterator_thingyB::operator++() noexcept {
			++index;
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyB& const_object_iterator_thingyB::operator++() noexcept {
			++index;
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_thingyB& object_iterator_thingyB::operator--() noexcept {
			--index;
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingyB& const_object_iterator_thingyB::operator--() noexcept {
			--index;
			while(container.thingyB.m__index.vptr()[index] != thingyB_id(thingyB_id::value_base_t(index)) && index < container.thingyB.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right::iterator_thingyB_foreach_relate_in_array_as_right(data_container& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_in_array.right_storage, container.relate_in_array.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right::iterator_thingyB_foreach_relate_in_array_as_right(data_container& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_in_array.right_storage, container.relate_in_array.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& iterator_thingyB_foreach_relate_in_array_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_array_as_right& iterator_thingyB_foreach_relate_in_array_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right::const_iterator_thingyB_foreach_relate_in_array_as_right(data_container const& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_in_array.right_storage, container.relate_in_array.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right::const_iterator_thingyB_foreach_relate_in_array_as_right(data_container const& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_in_array.right_storage, container.relate_in_array.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& const_iterator_thingyB_foreach_relate_in_array_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_array_as_right& const_iterator_thingyB_foreach_relate_in_array_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right::iterator_thingyB_foreach_relate_in_list_as_right(data_container& c,  thingyB_id fr) noexcept : container(c) {
			list_pos = container.relate_in_list.m_head_back_right.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right& iterator_thingyB_foreach_relate_in_list_as_right::operator++() noexcept {
			list_pos = container.relate_in_list.m_link_right.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_in_list_as_right& iterator_thingyB_foreach_relate_in_list_as_right::operator--() noexcept {
			list_pos = container.relate_in_list.m_link_right.vptr()[list_pos.index()].left;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right::const_iterator_thingyB_foreach_relate_in_list_as_right(data_container const& c,  thingyB_id fr) noexcept : container(c) {
			list_pos = container.relate_in_list.m_head_back_right.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right& const_iterator_thingyB_foreach_relate_in_list_as_right::operator++() noexcept {
			list_pos = container.relate_in_list.m_link_right.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_in_list_as_right& const_iterator_thingyB_foreach_relate_in_list_as_right::operator--() noexcept {
			list_pos = container.relate_in_list.m_link_right.vptr()[list_pos.index()].left;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right::iterator_thingyB_foreach_relate_as_optional_as_right(data_container& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.right_storage, container.relate_as_optional.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right::iterator_thingyB_foreach_relate_as_optional_as_right(data_container& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.right_storage, container.relate_as_optional.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& iterator_thingyB_foreach_relate_as_optional_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_optional_as_right& iterator_thingyB_foreach_relate_as_optional_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right::const_iterator_thingyB_foreach_relate_as_optional_as_right(data_container const& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.right_storage, container.relate_as_optional.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right::const_iterator_thingyB_foreach_relate_as_optional_as_right(data_container const& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_optional.right_storage, container.relate_as_optional.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& const_iterator_thingyB_foreach_relate_as_optional_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_optional_as_right& const_iterator_thingyB_foreach_relate_as_optional_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right::iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.right_storage, container.relate_as_non_optional.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right::iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.right_storage, container.relate_as_non_optional.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& iterator_thingyB_foreach_relate_as_non_optional_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_thingyB_foreach_relate_as_non_optional_as_right& iterator_thingyB_foreach_relate_as_non_optional_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right::const_iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container const& c,  thingyB_id fr) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.right_storage, container.relate_as_non_optional.m_array_right.vptr()[fr.index()]).first;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right::const_iterator_thingyB_foreach_relate_as_non_optional_as_right(data_container const& c, thingyB_id fr, int) noexcept : container(c) {
			ptr = dcon::get_range(container.relate_as_non_optional.right_storage, container.relate_as_non_optional.m_array_right.vptr()[fr.index()]).second;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& const_iterator_thingyB_foreach_relate_as_non_optional_as_right::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_thingyB_foreach_relate_as_non_optional_as_right& const_iterator_thingyB_foreach_relate_as_non_optional_as_right::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_same::object_iterator_relate_same(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_same::const_object_iterator_relate_same(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_relate_same& object_iterator_relate_same::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_same& const_object_iterator_relate_same::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_same& object_iterator_relate_same::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_same& const_object_iterator_relate_same::operator--() noexcept {
			--index;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_in_array::object_iterator_relate_in_array(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_array::const_object_iterator_relate_in_array(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_relate_in_array& object_iterator_relate_in_array::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_array& const_object_iterator_relate_in_array::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_in_array& object_iterator_relate_in_array::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_array& const_object_iterator_relate_in_array::operator--() noexcept {
			--index;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_in_list::object_iterator_relate_in_list(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_list::const_object_iterator_relate_in_list(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_relate_in_list& object_iterator_relate_in_list::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_list& const_object_iterator_relate_in_list::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_in_list& object_iterator_relate_in_list::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_in_list& const_object_iterator_relate_in_list::operator--() noexcept {
			--index;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_many_many::object_iterator_many_many(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_many_many::const_object_iterator_many_many(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_many_many& object_iterator_many_many::operator++() noexcept {
			++index;
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_many_many& const_object_iterator_many_many::operator++() noexcept {
			++index;
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_many_many& object_iterator_many_many::operator--() noexcept {
			--index;
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_many_many& const_object_iterator_many_many::operator--() noexcept {
			--index;
			while(container.many_many.m__index.vptr()[index] != many_many_id(many_many_id::value_base_t(index)) && index < container.many_many.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_optional::object_iterator_relate_as_optional(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_optional::const_object_iterator_relate_as_optional(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_optional& object_iterator_relate_as_optional::operator++() noexcept {
			++index;
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_optional& const_object_iterator_relate_as_optional::operator++() noexcept {
			++index;
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_optional& object_iterator_relate_as_optional::operator--() noexcept {
			--index;
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_optional& const_object_iterator_relate_as_optional::operator--() noexcept {
			--index;
			while(container.relate_as_optional.m__index.vptr()[index] != relate_as_optional_id(relate_as_optional_id::value_base_t(index)) && index < container.relate_as_optional.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_non_optional::object_iterator_relate_as_non_optional(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_non_optional::const_object_iterator_relate_as_non_optional(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_non_optional& object_iterator_relate_as_non_optional::operator++() noexcept {
			++index;
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_non_optional& const_object_iterator_relate_as_non_optional::operator++() noexcept {
			++index;
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_non_optional& object_iterator_relate_as_non_optional::operator--() noexcept {
			--index;
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_non_optional& const_object_iterator_relate_as_non_optional::operator--() noexcept {
			--index;
			while(container.relate_as_non_optional.m__index.vptr()[index] != relate_as_non_optional_id(relate_as_non_optional_id::value_base_t(index)) && index < container.relate_as_non_optional.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleA::object_iterator_relate_as_multipleA(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleA::const_object_iterator_relate_as_multipleA(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleA& object_iterator_relate_as_multipleA::operator++() noexcept {
			++index;
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleA& const_object_iterator_relate_as_multipleA::operator++() noexcept {
			++index;
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleA& object_iterator_relate_as_multipleA::operator--() noexcept {
			--index;
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleA& const_object_iterator_relate_as_multipleA::operator--() noexcept {
			--index;
			while(container.relate_as_multipleA.m__index.vptr()[index] != relate_as_multipleA_id(relate_as_multipleA_id::value_base_t(index)) && index < container.relate_as_multipleA.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleB::object_iterator_relate_as_multipleB(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleB::const_object_iterator_relate_as_multipleB(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleB& object_iterator_relate_as_multipleB::operator++() noexcept {
			++index;
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleB& const_object_iterator_relate_as_multipleB::operator++() noexcept {
			++index;
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleB& object_iterator_relate_as_multipleB::operator--() noexcept {
			--index;
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleB& const_object_iterator_relate_as_multipleB::operator--() noexcept {
			--index;
			while(container.relate_as_multipleB.m__index.vptr()[index] != relate_as_multipleB_id(relate_as_multipleB_id::value_base_t(index)) && index < container.relate_as_multipleB.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleC::object_iterator_relate_as_multipleC(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleC::const_object_iterator_relate_as_multipleC(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleC& object_iterator_relate_as_multipleC::operator++() noexcept {
			++index;
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleC& const_object_iterator_relate_as_multipleC::operator++() noexcept {
			++index;
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleC& object_iterator_relate_as_multipleC::operator--() noexcept {
			--index;
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleC& const_object_iterator_relate_as_multipleC::operator--() noexcept {
			--index;
			while(container.relate_as_multipleC.m__index.vptr()[index] != relate_as_multipleC_id(relate_as_multipleC_id::value_base_t(index)) && index < container.relate_as_multipleC.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleD::object_iterator_relate_as_multipleD(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleD::const_object_iterator_relate_as_multipleD(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleD& object_iterator_relate_as_multipleD::operator++() noexcept {
			++index;
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleD& const_object_iterator_relate_as_multipleD::operator++() noexcept {
			++index;
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_relate_as_multipleD& object_iterator_relate_as_multipleD::operator--() noexcept {
			--index;
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_relate_as_multipleD& const_object_iterator_relate_as_multipleD::operator--() noexcept {
			--index;
			while(container.relate_as_multipleD.m__index.vptr()[index] != relate_as_multipleD_id(relate_as_multipleD_id::value_base_t(index)) && index < container.relate_as_multipleD.size_used) {
				--index;
			}
			return *this;
		}
		
	};


}

#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif

