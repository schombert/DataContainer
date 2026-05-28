#pragma once

//
// This file was automatically generated from: car_owner_basic3.txt
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
namespace cob3 {
	//
	// definition of strongly typed index for car_id
	//
	class car_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr car_id() noexcept = default;
		explicit constexpr car_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr car_id(car_id const& v) noexcept = default;
		constexpr car_id(car_id&& v) noexcept = default;
		
		car_id& operator=(car_id const& v) noexcept = default;
		car_id& operator=(car_id&& v) noexcept = default;
		constexpr bool operator==(car_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(car_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class car_id_pair {
		public:
		car_id left;
		car_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(car_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for person_id
	//
	class person_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;
		
		uint8_t value = 0;
		
		constexpr person_id() noexcept = default;
		explicit constexpr person_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr person_id(person_id const& v) noexcept = default;
		constexpr person_id(person_id&& v) noexcept = default;
		
		person_id& operator=(person_id const& v) noexcept = default;
		person_id& operator=(person_id&& v) noexcept = default;
		constexpr bool operator==(person_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(person_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class person_id_pair {
		public:
		person_id left;
		person_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(person_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for car_ownership_id
	//
	class car_ownership_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr car_ownership_id() noexcept = default;
		explicit constexpr car_ownership_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr car_ownership_id(car_ownership_id const& v) noexcept = default;
		constexpr car_ownership_id(car_ownership_id&& v) noexcept = default;
		
		car_ownership_id& operator=(car_ownership_id const& v) noexcept = default;
		car_ownership_id& operator=(car_ownership_id&& v) noexcept = default;
		constexpr bool operator==(car_ownership_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(car_ownership_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class car_ownership_id_pair {
		public:
		car_ownership_id left;
		car_ownership_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(car_ownership_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<cob3::car_id> {
		using type = ::ve::tagged_vector<cob3::car_id>;
	};
	
	template<>
	struct value_to_vector_type_s<cob3::person_id> {
		using type = ::ve::tagged_vector<cob3::person_id>;
	};
	
	template<>
	struct value_to_vector_type_s<cob3::car_ownership_id> {
		using type = ::ve::tagged_vector<cob3::car_ownership_id>;
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
