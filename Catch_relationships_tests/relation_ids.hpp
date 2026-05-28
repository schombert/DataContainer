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

#ifdef DCON_RELEASE_INLINE
#define DCON_RELEASE_INLINE_DEFINED
#endif
#ifndef DCON_RELEASE_INLINE_DEFINED
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
#endif
namespace dcon {
	//
	// definition of strongly typed index for pop_id
	//
	class pop_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;
		
		uint8_t value = 0;
		
		constexpr pop_id() noexcept = default;
		explicit constexpr pop_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr pop_id(pop_id const& v) noexcept = default;
		constexpr pop_id(pop_id&& v) noexcept = default;
		
		pop_id& operator=(pop_id const& v) noexcept = default;
		pop_id& operator=(pop_id&& v) noexcept = default;
		constexpr bool operator==(pop_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(pop_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class pop_id_pair {
		public:
		pop_id left;
		pop_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(pop_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for employment_id
	//
	class employment_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;
		
		uint8_t value = 0;
		
		constexpr employment_id() noexcept = default;
		explicit constexpr employment_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr employment_id(employment_id const& v) noexcept = default;
		constexpr employment_id(employment_id&& v) noexcept = default;
		
		employment_id& operator=(employment_id const& v) noexcept = default;
		employment_id& operator=(employment_id&& v) noexcept = default;
		constexpr bool operator==(employment_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(employment_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class employment_id_pair {
		public:
		employment_id left;
		employment_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(employment_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for job_id
	//
	class job_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;
		
		uint8_t value = 0;
		
		constexpr job_id() noexcept = default;
		explicit constexpr job_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr job_id(job_id const& v) noexcept = default;
		constexpr job_id(job_id&& v) noexcept = default;
		
		job_id& operator=(job_id const& v) noexcept = default;
		job_id& operator=(job_id&& v) noexcept = default;
		constexpr bool operator==(job_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(job_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class job_id_pair {
		public:
		job_id left;
		job_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(job_id id) { return bool(id); }
	
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
	struct value_to_vector_type_s<dcon::pop_id> {
		using type = ::ve::tagged_vector<dcon::pop_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::employment_id> {
		using type = ::ve::tagged_vector<dcon::employment_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::job_id> {
		using type = ::ve::tagged_vector<dcon::job_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::thingyA_id> {
		using type = ::ve::tagged_vector<dcon::thingyA_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::thingyB_id> {
		using type = ::ve::tagged_vector<dcon::thingyB_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_same_id> {
		using type = ::ve::tagged_vector<dcon::relate_same_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_in_array_id> {
		using type = ::ve::tagged_vector<dcon::relate_in_array_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_in_list_id> {
		using type = ::ve::tagged_vector<dcon::relate_in_list_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::many_many_id> {
		using type = ::ve::tagged_vector<dcon::many_many_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_optional_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_optional_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_non_optional_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_non_optional_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleA_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_multipleA_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleB_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_multipleB_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleC_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_multipleC_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::relate_as_multipleD_id> {
		using type = ::ve::tagged_vector<dcon::relate_as_multipleD_id>;
	};
	
}

#endif
#ifndef DCON_RELEASE_INLINE_DEFINED
#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif
#else
#undef DCON_RELEASE_INLINE_DEFINED
#endif
