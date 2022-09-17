#pragma once

//
// This file was automatically generated from: query_objs.txt
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

#ifdef NDEBUG
#ifdef _MSC_VER
#define DCON_RELEASE_INLINE __forceinline
#else
#define DCON_RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define DCON_RELEASE_INLINE inline
#endif
#pragma warning( push )
#pragma warning( disable : 4324 )

namespace dcon {
	struct load_record {
		bool car : 1;
		bool car_wheels : 1;
		bool car_resale_value : 1;
		bool person : 1;
		bool person_age : 1;
		bool person_wealth : 1;
		bool car_ownership : 1;
		bool car_ownership_owner : 1;
		bool car_ownership_owned_car : 1;
		bool car_ownership_ownership_date : 1;
		bool parentage : 1;
		bool parentage_child : 1;
		bool parentage_bio_parent : 1;
		load_record() {
			car = false;
			car_wheels = false;
			car_resale_value = false;
			person = false;
			person_age = false;
			person_wealth = false;
			car_ownership = false;
			car_ownership_owner = false;
			car_ownership_owned_car = false;
			car_ownership_ownership_date = false;
			parentage = false;
			parentage_child = false;
			parentage_bio_parent = false;
		}
	};
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
	
	//
	// definition of strongly typed index for parentage_id
	//
	class parentage_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;
		
		uint8_t value = 0;
		
		constexpr parentage_id() noexcept = default;
		explicit constexpr parentage_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr parentage_id(parentage_id const& v) noexcept = default;
		constexpr parentage_id(parentage_id&& v) noexcept = default;
		
		parentage_id& operator=(parentage_id const& v) noexcept = default;
		parentage_id& operator=(parentage_id&& v) noexcept = default;
		constexpr bool operator==(parentage_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(parentage_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint8_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class parentage_id_pair {
		public:
		parentage_id left;
		parentage_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(parentage_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::car_id> {
		using type = tagged_vector<dcon::car_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::person_id> {
		using type = tagged_vector<dcon::person_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::car_ownership_id> {
		using type = tagged_vector<dcon::car_ownership_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::parentage_id> {
		using type = tagged_vector<dcon::parentage_id>;
	};
	
}

#endif
namespace dcon {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class query_q_all_owner_ages_iterator;
		class query_q_all_owner_ages_const_iterator;
		class query_q_all_owner_ages_instance {
			public:
			data_container& container;
			query_q_all_owner_ages_instance(data_container& c ) : container(c)  {}
			query_q_all_owner_ages_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_q_all_owner_ages_const_instance {
			public:
			data_container const& container;
			query_q_all_owner_ages_const_instance(data_container const& c ) : container(c)  {}
			query_q_all_owner_ages_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_rev_car_from_owner_iterator;
		class query_rev_car_from_owner_const_iterator;
		class query_rev_car_from_owner_instance {
			public:
			data_container& container;
			query_rev_car_from_owner_instance(data_container& c ) : container(c)  {}
			query_rev_car_from_owner_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_rev_car_from_owner_const_instance {
			public:
			data_container const& container;
			query_rev_car_from_owner_const_instance(data_container const& c ) : container(c)  {}
			query_rev_car_from_owner_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_param_car_from_owner_iterator;
		class query_param_car_from_owner_const_iterator;
		class query_param_car_from_owner_instance {
			public:
			data_container& container;
			person_id from_person;
			query_param_car_from_owner_instance(data_container& c , person_id p0) : container(c) , from_person(p0) {}
			query_param_car_from_owner_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_param_car_from_owner_const_instance {
			public:
			data_container const& container;
			person_id from_person;
			query_param_car_from_owner_const_instance(data_container const& c , person_id p0) : container(c) , from_person(p0) {}
			query_param_car_from_owner_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_q_all_owner_ages_plus_iterator;
		class query_q_all_owner_ages_plus_const_iterator;
		class query_q_all_owner_ages_plus_instance {
			public:
			data_container& container;
			query_q_all_owner_ages_plus_instance(data_container& c ) : container(c)  {}
			query_q_all_owner_ages_plus_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_q_all_owner_ages_plus_const_instance {
			public:
			data_container const& container;
			query_q_all_owner_ages_plus_const_instance(data_container const& c ) : container(c)  {}
			query_q_all_owner_ages_plus_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_rev_car_from_owner_plus_iterator;
		class query_rev_car_from_owner_plus_const_iterator;
		class query_rev_car_from_owner_plus_instance {
			public:
			data_container& container;
			query_rev_car_from_owner_plus_instance(data_container& c ) : container(c)  {}
			query_rev_car_from_owner_plus_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_rev_car_from_owner_plus_const_instance {
			public:
			data_container const& container;
			query_rev_car_from_owner_plus_const_instance(data_container const& c ) : container(c)  {}
			query_rev_car_from_owner_plus_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_grandparents_iterator;
		class query_grandparents_const_iterator;
		class query_grandparents_instance {
			public:
			data_container& container;
			person_id from_person;
			query_grandparents_instance(data_container& c , person_id p0) : container(c) , from_person(p0) {}
			query_grandparents_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_grandparents_const_instance {
			public:
			data_container const& container;
			person_id from_person;
			query_grandparents_const_instance(data_container const& c , person_id p0) : container(c) , from_person(p0) {}
			query_grandparents_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_grandchildren_iterator;
		class query_grandchildren_const_iterator;
		class query_grandchildren_instance {
			public:
			data_container& container;
			person_id from_person;
			int32_t age_filter;
			query_grandchildren_instance(data_container& c , person_id p0, int32_t p1) : container(c) , from_person(p0), age_filter(p1) {}
			query_grandchildren_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_grandchildren_const_instance {
			public:
			data_container const& container;
			person_id from_person;
			int32_t age_filter;
			query_grandchildren_const_instance(data_container const& c , person_id p0, int32_t p1) : container(c) , from_person(p0), age_filter(p1) {}
			query_grandchildren_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_group_grandchildren_iterator;
		class query_group_grandchildren_const_iterator;
		class query_group_grandchildren_instance {
			public:
			data_container& container;
			int32_t age_filter;
			query_group_grandchildren_instance(data_container& c , int32_t p0) : container(c) , age_filter(p0) {}
			query_group_grandchildren_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_group_grandchildren_const_instance {
			public:
			data_container const& container;
			int32_t age_filter;
			query_group_grandchildren_const_instance(data_container const& c , int32_t p0) : container(c) , age_filter(p0) {}
			query_group_grandchildren_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_sum_car_value_iterator;
		class query_sum_car_value_const_iterator;
		class query_sum_car_value_instance {
			public:
			data_container& container;
			person_id from_person;
			query_sum_car_value_instance(data_container& c , person_id p0) : container(c) , from_person(p0) {}
			query_sum_car_value_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_sum_car_value_const_instance {
			public:
			data_container const& container;
			person_id from_person;
			query_sum_car_value_const_instance(data_container const& c , person_id p0) : container(c) , from_person(p0) {}
			query_sum_car_value_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_pairs_of_cars_iterator;
		class query_pairs_of_cars_const_iterator;
		class query_pairs_of_cars_instance {
			public:
			data_container& container;
			query_pairs_of_cars_instance(data_container& c ) : container(c)  {}
			query_pairs_of_cars_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_pairs_of_cars_const_instance {
			public:
			data_container const& container;
			query_pairs_of_cars_const_instance(data_container const& c ) : container(c)  {}
			query_pairs_of_cars_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class query_siblings_iterator;
		class query_siblings_const_iterator;
		class query_siblings_instance {
			public:
			data_container& container;
			person_id person_param;
			query_siblings_instance(data_container& c , person_id p0) : container(c) , person_param(p0) {}
			query_siblings_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_siblings_const_instance {
			public:
			data_container const& container;
			person_id person_param;
			query_siblings_const_instance(data_container const& c , person_id p0) : container(c) , person_param(p0) {}
			query_siblings_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class alignas(64) car_class {
			private:
			//
			// storage space for wheels of type int32_t
			//
			struct alignas(64) dtype_wheels {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_wheels() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_wheels;
			
			//
			// storage space for resale_value of type float
			//
			struct alignas(64) dtype_resale_value {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_resale_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_resale_value;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class alignas(64) person_class {
			private:
			//
			// storage space for age of type int32_t
			//
			struct alignas(64) dtype_age {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(100) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(100))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_age() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(100) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(100))); }
			}
			m_age;
			
			//
			// storage space for wealth of type float
			//
			struct alignas(64) dtype_wealth {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(100) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(100))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_wealth() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(100) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(100))); }
			}
			m_wealth;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class alignas(64) car_ownership_class {
			private:
			//
			// storage space for ownership_date of type int32_t
			//
			struct alignas(64) dtype_ownership_date {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_ownership_date() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_ownership_date;
			
			//
			// storage space for owner of type person_id
			//
			struct alignas(64) dtype_owner {
				uint8_t padding[(63 + sizeof(person_id)) & ~uint64_t(63)];
				person_id values[(sizeof(person_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(person_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(person_id)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_owner() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(person_id) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(person_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(person_id)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_owner;
			
			//
			// storage space for array_owner of type std::vector<car_ownership_id>
			//
			struct dtype_array_owner {
				std::vector<car_ownership_id> values[100];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_owner() { std::uninitialized_value_construct_n(values, 100); }
			}
			m_array_owner;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class alignas(64) parentage_class {
			private:
			//
			// storage space for bio_parent of type person_id
			//
			struct dtype_bio_parent {
				std::array<person_id, 2> values[100];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_bio_parent() { std::uninitialized_value_construct_n(values, 100); }
			}
			m_bio_parent;
			
			//
			// storage space for array_bio_parent of type dcon::stable_mk_2_tag
			//
			struct dtype_array_bio_parent {
				dcon::stable_mk_2_tag values[100];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_bio_parent() { std::uninitialized_fill_n(values, 100, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_array_bio_parent;
			
			dcon::stable_variable_vector_storage_mk_2<parentage_id, 8, 200 > bio_parent_storage;
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

	}

	class car_const_fat_id;
	class car_fat_id;
	class person_const_fat_id;
	class person_fat_id;
	class car_ownership_const_fat_id;
	class car_ownership_fat_id;
	class parentage_const_fat_id;
	class parentage_fat_id;
	class car_fat_id {
		friend data_container;
		public:
		data_container& container;
		car_id id;
		car_fat_id(data_container& c, car_id i) noexcept : container(c), id(i) {}
		car_fat_id(car_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator car_id() const noexcept { return id; }
		DCON_RELEASE_INLINE car_fat_id& operator=(car_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_fat_id& operator=(car_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(car_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(car_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_wheels() const noexcept;
		DCON_RELEASE_INLINE void set_wheels(int32_t v) const noexcept;
		DCON_RELEASE_INLINE float& get_resale_value() const noexcept;
		DCON_RELEASE_INLINE void set_resale_value(float v) const noexcept;
		DCON_RELEASE_INLINE car_ownership_fat_id get_car_ownership_as_owned_car() const noexcept;
		DCON_RELEASE_INLINE void remove_car_ownership_as_owned_car() const noexcept;
		DCON_RELEASE_INLINE car_ownership_fat_id get_car_ownership() const noexcept;
		DCON_RELEASE_INLINE void remove_car_ownership() const noexcept;
		DCON_RELEASE_INLINE person_fat_id get_owner_from_car_ownership() const noexcept;
		DCON_RELEASE_INLINE void set_owner_from_car_ownership(person_id v) const noexcept;
		DCON_RELEASE_INLINE void set_ownership_date_from_car_ownership(int32_t v) const noexcept;
		DCON_RELEASE_INLINE int32_t get_ownership_date_from_car_ownership() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE car_fat_id fatten(data_container& c, car_id id) noexcept {
		return car_fat_id(c, id);
	}
	
	class car_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		car_id id;
		car_const_fat_id(data_container const& c, car_id i) noexcept : container(c), id(i) {}
		car_const_fat_id(car_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		car_const_fat_id(car_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator car_id() const noexcept { return id; }
		DCON_RELEASE_INLINE car_const_fat_id& operator=(car_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_const_fat_id& operator=(car_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_const_fat_id& operator=(car_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(car_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(car_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_wheels() const noexcept;
		DCON_RELEASE_INLINE float get_resale_value() const noexcept;
		DCON_RELEASE_INLINE car_ownership_const_fat_id get_car_ownership_as_owned_car() const noexcept;
		DCON_RELEASE_INLINE car_ownership_const_fat_id get_car_ownership() const noexcept;
		DCON_RELEASE_INLINE person_const_fat_id get_owner_from_car_ownership() const noexcept;
		DCON_RELEASE_INLINE int32_t get_ownership_date_from_car_ownership() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(car_fat_id const& l, car_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(car_fat_id const& l, car_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE car_const_fat_id fatten(data_container const& c, car_id id) noexcept {
		return car_const_fat_id(c, id);
	}
	
	class person_fat_id {
		friend data_container;
		public:
		data_container& container;
		person_id id;
		person_fat_id(data_container& c, person_id i) noexcept : container(c), id(i) {}
		person_fat_id(person_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator person_id() const noexcept { return id; }
		DCON_RELEASE_INLINE person_fat_id& operator=(person_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE person_fat_id& operator=(person_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(person_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(person_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(person_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(person_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_age() const noexcept;
		DCON_RELEASE_INLINE void set_age(int32_t v) const noexcept;
		DCON_RELEASE_INLINE float& get_wealth() const noexcept;
		DCON_RELEASE_INLINE void set_wealth(float v) const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership_as_owner(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership_as_owner() const;
		DCON_RELEASE_INLINE void remove_all_car_ownership_as_owner() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership() const;
		DCON_RELEASE_INLINE void remove_all_car_ownership() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_owned_car_from_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE bool has_owned_car_from_car_ownership(car_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_ownership_date_from_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE bool has_ownership_date_from_car_ownership(int32_t target) const;
		DCON_RELEASE_INLINE parentage_fat_id get_parentage_as_child() const noexcept;
		DCON_RELEASE_INLINE void remove_parentage_as_child() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_parentage_as_bio_parent(T&& func) const;
		DCON_RELEASE_INLINE std::pair<parentage_id const*, parentage_id const*> range_of_parentage_as_bio_parent() const;
		DCON_RELEASE_INLINE void remove_all_parentage_as_bio_parent() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE person_fat_id fatten(data_container& c, person_id id) noexcept {
		return person_fat_id(c, id);
	}
	
	class person_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		person_id id;
		person_const_fat_id(data_container const& c, person_id i) noexcept : container(c), id(i) {}
		person_const_fat_id(person_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		person_const_fat_id(person_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator person_id() const noexcept { return id; }
		DCON_RELEASE_INLINE person_const_fat_id& operator=(person_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE person_const_fat_id& operator=(person_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE person_const_fat_id& operator=(person_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(person_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(person_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(person_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(person_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(person_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(person_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_age() const noexcept;
		DCON_RELEASE_INLINE float get_wealth() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership_as_owner(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership_as_owner() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_owned_car_from_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE bool has_owned_car_from_car_ownership(car_id target) const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_ownership_date_from_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE bool has_ownership_date_from_car_ownership(int32_t target) const;
		DCON_RELEASE_INLINE parentage_const_fat_id get_parentage_as_child() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_parentage_as_bio_parent(T&& func) const;
		DCON_RELEASE_INLINE std::pair<parentage_id const*, parentage_id const*> range_of_parentage_as_bio_parent() const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(person_fat_id const& l, person_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(person_fat_id const& l, person_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE person_const_fat_id fatten(data_container const& c, person_id id) noexcept {
		return person_const_fat_id(c, id);
	}
	
	class car_ownership_fat_id {
		friend data_container;
		public:
		data_container& container;
		car_ownership_id id;
		car_ownership_fat_id(data_container& c, car_ownership_id i) noexcept : container(c), id(i) {}
		car_ownership_fat_id(car_ownership_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator car_ownership_id() const noexcept { return id; }
		DCON_RELEASE_INLINE car_ownership_fat_id& operator=(car_ownership_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_ownership_fat_id& operator=(car_ownership_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(car_ownership_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_ownership_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(car_ownership_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_ownership_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_ownership_date() const noexcept;
		DCON_RELEASE_INLINE void set_ownership_date(int32_t v) const noexcept;
		DCON_RELEASE_INLINE person_fat_id get_owner() const noexcept;
		DCON_RELEASE_INLINE void set_owner(person_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_owner(person_id val) const noexcept;
		DCON_RELEASE_INLINE car_fat_id get_owned_car() const noexcept;
		DCON_RELEASE_INLINE void set_owned_car(car_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_owned_car(car_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE car_ownership_fat_id fatten(data_container& c, car_ownership_id id) noexcept {
		return car_ownership_fat_id(c, id);
	}
	
	class car_ownership_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		car_ownership_id id;
		car_ownership_const_fat_id(data_container const& c, car_ownership_id i) noexcept : container(c), id(i) {}
		car_ownership_const_fat_id(car_ownership_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		car_ownership_const_fat_id(car_ownership_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator car_ownership_id() const noexcept { return id; }
		DCON_RELEASE_INLINE car_ownership_const_fat_id& operator=(car_ownership_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_ownership_const_fat_id& operator=(car_ownership_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE car_ownership_const_fat_id& operator=(car_ownership_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(car_ownership_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_ownership_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(car_ownership_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(car_ownership_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_ownership_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(car_ownership_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_ownership_date() const noexcept;
		DCON_RELEASE_INLINE person_const_fat_id get_owner() const noexcept;
		DCON_RELEASE_INLINE car_const_fat_id get_owned_car() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(car_ownership_fat_id const& l, car_ownership_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(car_ownership_fat_id const& l, car_ownership_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE car_ownership_const_fat_id fatten(data_container const& c, car_ownership_id id) noexcept {
		return car_ownership_const_fat_id(c, id);
	}
	
	class parentage_fat_id {
		friend data_container;
		public:
		data_container& container;
		parentage_id id;
		parentage_fat_id(data_container& c, parentage_id i) noexcept : container(c), id(i) {}
		parentage_fat_id(parentage_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator parentage_id() const noexcept { return id; }
		DCON_RELEASE_INLINE parentage_fat_id& operator=(parentage_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE parentage_fat_id& operator=(parentage_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(parentage_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(parentage_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(parentage_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(parentage_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE person_fat_id get_child() const noexcept;
		DCON_RELEASE_INLINE void set_child(person_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_child(person_id val) const noexcept;
		DCON_RELEASE_INLINE person_fat_id get_bio_parent(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_bio_parent(person_id val) const noexcept;
		DCON_RELEASE_INLINE void set_bio_parent(int32_t i, person_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_bio_parent(int32_t i, person_id val) const noexcept;
		DCON_RELEASE_INLINE void replace_bio_parent(person_id newval, person_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool try_replace_bio_parent(person_id newval, person_id oldval) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE parentage_fat_id fatten(data_container& c, parentage_id id) noexcept {
		return parentage_fat_id(c, id);
	}
	
	class parentage_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		parentage_id id;
		parentage_const_fat_id(data_container const& c, parentage_id i) noexcept : container(c), id(i) {}
		parentage_const_fat_id(parentage_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		parentage_const_fat_id(parentage_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator parentage_id() const noexcept { return id; }
		DCON_RELEASE_INLINE parentage_const_fat_id& operator=(parentage_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE parentage_const_fat_id& operator=(parentage_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE parentage_const_fat_id& operator=(parentage_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(parentage_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(parentage_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(parentage_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(parentage_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(parentage_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(parentage_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE person_const_fat_id get_child() const noexcept;
		DCON_RELEASE_INLINE person_const_fat_id get_bio_parent(int32_t i) const noexcept;
		DCON_RELEASE_INLINE bool has_bio_parent(person_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(parentage_fat_id const& l, parentage_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(parentage_fat_id const& l, parentage_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE parentage_const_fat_id fatten(data_container const& c, parentage_id id) noexcept {
		return parentage_const_fat_id(c, id);
	}
	
	class alignas(64) data_container {
		public:
		internal::car_class car;
		internal::person_class person;
		internal::car_ownership_class car_ownership;
		internal::parentage_class parentage;

		//
		// Functions for car:
		//
		//
		// accessors for car: wheels
		//
		DCON_RELEASE_INLINE int32_t const& car_get_wheels(car_id id) const noexcept {
			return car.m_wheels.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& car_get_wheels(car_id id) noexcept {
			return car.m_wheels.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::tagged_vector<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void car_set_wheels(car_id id, int32_t value) noexcept {
			car.m_wheels.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void car_set_wheels(ve::contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_wheels(ve::partial_contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_wheels(ve::tagged_vector<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}
		#endif
		//
		// accessors for car: resale_value
		//
		DCON_RELEASE_INLINE float const& car_get_resale_value(car_id id) const noexcept {
			return car.m_resale_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& car_get_resale_value(car_id id) noexcept {
			return car.m_resale_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> car_get_resale_value(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_resale_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> car_get_resale_value(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_resale_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> car_get_resale_value(ve::tagged_vector<car_id> id) const noexcept {
			return ve::load(id, car.m_resale_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void car_set_resale_value(car_id id, float value) noexcept {
			car.m_resale_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void car_set_resale_value(ve::contiguous_tags<car_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, car.m_resale_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_resale_value(ve::partial_contiguous_tags<car_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, car.m_resale_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_resale_value(ve::tagged_vector<car_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, car.m_resale_value.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE car_ownership_id car_get_car_ownership_as_owned_car(car_id id) const noexcept {
			return (id.value <= car_ownership.size_used) ? car_ownership_id(car_ownership_id::value_base_t(id.index())) : car_ownership_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<car_ownership_id> car_get_car_ownership_as_owned_car(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::contiguous_tags<car_ownership_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<car_ownership_id> car_get_car_ownership_as_owned_car(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::partial_contiguous_tags<car_ownership_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership_as_owned_car(ve::tagged_vector<car_id> id) const noexcept {
			return ve::tagged_vector<car_ownership_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void car_remove_car_ownership_as_owned_car(car_id id) noexcept {
			if(car_ownership_is_valid(car_ownership_id(car_ownership_id::value_base_t(id.index())))) {
				car_ownership_set_owned_car(car_ownership_id(car_ownership_id::value_base_t(id.index())), car_id());
			}
		}
		DCON_RELEASE_INLINE car_ownership_id car_get_car_ownership(car_id id) const noexcept {
			return (id.value <= car_ownership.size_used) ? car_ownership_id(car_ownership_id::value_base_t(id.index())) : car_ownership_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<car_ownership_id> car_get_car_ownership(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::contiguous_tags<car_ownership_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<car_ownership_id> car_get_car_ownership(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::partial_contiguous_tags<car_ownership_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership(ve::tagged_vector<car_id> id) const noexcept {
			return ve::tagged_vector<car_ownership_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void car_remove_car_ownership(car_id id) noexcept {
			if(car_ownership_is_valid(car_ownership_id(car_ownership_id::value_base_t(id.index())))) {
				car_ownership_set_owned_car(car_ownership_id(car_ownership_id::value_base_t(id.index())), car_id());
			}
		}
		DCON_RELEASE_INLINE person_id car_get_owner_from_car_ownership(car_id ref_id) const {
			return car_ownership_get_owner(car_ownership_id(car_ownership_id::value_base_t(ref_id.index())));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_owner(ve::contiguous_tags<car_ownership_id>(ref_id.value));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::partial_contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_owner(ve::partial_contiguous_tags<car_ownership_id>(ref_id.value, ref_id.subcount));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::tagged_vector<car_id> ref_id) const {
			return car_ownership_get_owner(ve::tagged_vector<car_ownership_id>(ref_id, std::true_type{}));
		}
		#endif
		void car_set_owner_from_car_ownership(car_id ref_id, person_id val) {
			car_ownership_set_owner(car_ownership_id(car_ownership_id::value_base_t(ref_id.index())), val);
		}
		void car_set_ownership_date_from_car_ownership(car_id ref_id, int32_t val) {
			car_ownership_set_ownership_date(car_ownership_id(car_ownership_id::value_base_t(ref_id.index())), val);
		}
		int32_t car_get_ownership_date_from_car_ownership(car_id ref_id) const {
			return car_ownership_get_ownership_date(car_ownership_id(car_ownership_id::value_base_t(ref_id.index())));
		}
		#ifndef DCON_NO_VE
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ve::contiguous_tags<car_ownership_id>(ref_id.value));
		}
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::partial_contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ve::partial_contiguous_tags<car_ownership_id>(ref_id.value, ref_id.subcount));
		}
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::tagged_vector<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ve::tagged_vector<car_ownership_id>(ref_id, std::true_type{}));
		}
		#endif
		DCON_RELEASE_INLINE bool car_is_valid(car_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < car.size_used;
		}
		
		uint32_t car_size() const noexcept { return car.size_used; }

		//
		// Functions for person:
		//
		//
		// accessors for person: age
		//
		DCON_RELEASE_INLINE int32_t const& person_get_age(person_id id) const noexcept {
			return person.m_age.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& person_get_age(person_id id) noexcept {
			return person.m_age.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::partial_contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::tagged_vector<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void person_set_age(person_id id, int32_t value) noexcept {
			person.m_age.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void person_set_age(ve::contiguous_tags<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_age(ve::partial_contiguous_tags<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_age(ve::tagged_vector<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}
		#endif
		//
		// accessors for person: wealth
		//
		DCON_RELEASE_INLINE float const& person_get_wealth(person_id id) const noexcept {
			return person.m_wealth.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& person_get_wealth(person_id id) noexcept {
			return person.m_wealth.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> person_get_wealth(ve::contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_wealth.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> person_get_wealth(ve::partial_contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_wealth.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> person_get_wealth(ve::tagged_vector<person_id> id) const noexcept {
			return ve::load(id, person.m_wealth.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void person_set_wealth(person_id id, float value) noexcept {
			person.m_wealth.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void person_set_wealth(ve::contiguous_tags<person_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, person.m_wealth.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_wealth(ve::partial_contiguous_tags<person_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, person.m_wealth.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_wealth(ve::tagged_vector<person_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, person.m_wealth.vptr(), values);
		}
		#endif
		template<typename T>
		DCON_RELEASE_INLINE void person_for_each_car_ownership_as_owner(person_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_range_of_car_ownership_as_owner(person_id id) const {
			if(bool(id)) {
				auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
				return std::pair<car_ownership_id const*, car_ownership_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<car_ownership_id const*, car_ownership_id const*>(nullptr, nullptr);
			}
		}
		void person_remove_all_car_ownership_as_owner(person_id id) noexcept {
			auto rng = person_range_of_car_ownership_as_owner(id);
			dcon::local_vector<car_ownership_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](car_ownership_id i) { t->car_ownership_set_owner(i, person_id()); });
		}
		template<typename T>
		DCON_RELEASE_INLINE void person_for_each_car_ownership(person_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_range_of_car_ownership(person_id id) const {
			if(bool(id)) {
				auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
				return std::pair<car_ownership_id const*, car_ownership_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<car_ownership_id const*, car_ownership_id const*>(nullptr, nullptr);
			}
		}
		void person_remove_all_car_ownership(person_id id) noexcept {
			auto rng = person_range_of_car_ownership_as_owner(id);
			dcon::local_vector<car_ownership_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](car_ownership_id i) { t->car_ownership_set_owner(i, person_id()); });
		}
		template<typename T>
		void person_for_each_owned_car_from_car_ownership(person_id id, T&& func) const {
			person_for_each_car_ownership_as_owner(id, [&](car_ownership_id i) {
				func(car_ownership_get_owned_car(i));
			} );
		}
		bool person_has_owned_car_from_car_ownership(person_id id, car_id target) const {
			auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(pos->index() == target.index()) return true;
			}
			return false;
		}
		template<typename T>
		void person_for_each_ownership_date_from_car_ownership(person_id id, T&& func) const {
			person_for_each_car_ownership_as_owner(id, [&](car_ownership_id i) {
				func(car_ownership_get_ownership_date(i));
			} );
		}
		bool person_has_ownership_date_from_car_ownership(person_id id, int32_t target) const {
			auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(car_ownership.m_ownership_date.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE parentage_id person_get_parentage_as_child(person_id id) const noexcept {
			return (id.value <= parentage.size_used) ? parentage_id(parentage_id::value_base_t(id.index())) : parentage_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<parentage_id> person_get_parentage_as_child(ve::contiguous_tags<person_id> id) const noexcept {
			return ve::contiguous_tags<parentage_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<parentage_id> person_get_parentage_as_child(ve::partial_contiguous_tags<person_id> id) const noexcept {
			return ve::partial_contiguous_tags<parentage_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<parentage_id> person_get_parentage_as_child(ve::tagged_vector<person_id> id) const noexcept {
			return ve::tagged_vector<parentage_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void person_remove_parentage_as_child(person_id id) noexcept {
			if(parentage_is_valid(parentage_id(parentage_id::value_base_t(id.index())))) {
				parentage_set_child(parentage_id(parentage_id::value_base_t(id.index())), person_id());
			}
		}
		template<typename T>
		DCON_RELEASE_INLINE void person_for_each_parentage_as_bio_parent(person_id id, T&& func) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(parentage.bio_parent_storage, parentage.m_array_bio_parent.vptr()[id.index()]);
				std::for_each(vrange.first, vrange.second, func);
			}
		}
		DCON_RELEASE_INLINE std::pair<parentage_id const*, parentage_id const*> person_range_of_parentage_as_bio_parent(person_id id) const {
			if(bool(id)) {
				auto vrange = dcon::get_range(parentage.bio_parent_storage, parentage.m_array_bio_parent.vptr()[id.index()]);
				return std::pair<parentage_id const*, parentage_id const*>(vrange.first, vrange.second);
			} else {
				return std::pair<parentage_id const*, parentage_id const*>(nullptr, nullptr);
			}
		}
		void person_remove_all_parentage_as_bio_parent(person_id id) noexcept {
			auto rng = person_range_of_parentage_as_bio_parent(id);
			dcon::local_vector<parentage_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this, id](parentage_id i) { t->parentage_replace_bio_parent(i, person_id(), id); });
		}
		DCON_RELEASE_INLINE bool person_is_valid(person_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < person.size_used;
		}
		
		uint32_t person_size() const noexcept { return person.size_used; }

		//
		// Functions for car_ownership:
		//
		//
		// accessors for car_ownership: ownership_date
		//
		DCON_RELEASE_INLINE int32_t const& car_ownership_get_ownership_date(car_ownership_id id) const noexcept {
			return car_ownership.m_ownership_date.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& car_ownership_get_ownership_date(car_ownership_id id) noexcept {
			return car_ownership.m_ownership_date.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(car_ownership_id id, int32_t value) noexcept {
			car_ownership.m_ownership_date.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::contiguous_tags<car_ownership_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::partial_contiguous_tags<car_ownership_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::tagged_vector<car_ownership_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE person_id car_ownership_get_owner(car_ownership_id id) const noexcept {
			return car_ownership.m_owner.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_ownership_get_owner(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_ownership_get_owner(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<person_id> car_ownership_get_owner(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		#endif
		private:
		void internal_car_ownership_set_owner(car_ownership_id id, person_id value) noexcept {
			if(auto old_value = car_ownership.m_owner.vptr()[id.index()]; bool(old_value)) {
				auto& vref = car_ownership.m_array_owner.vptr()[old_value.index()];
				if(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {
					*it = vref.back();
					vref.pop_back();
				}
			}
			if(bool(value)) {
				car_ownership.m_array_owner.vptr()[value.index()].push_back(id);
			}
			car_ownership.m_owner.vptr()[id.index()] = value;
		}
		public:
		void car_ownership_set_owner(car_ownership_id id, person_id value) noexcept {
			if(!bool(value)) {
				delete_car_ownership(id);
				return;
			}
			internal_car_ownership_set_owner(id, value);
		}
		bool car_ownership_try_set_owner(car_ownership_id id, person_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_car_ownership_set_owner(id, value);
			return true;
		}
		DCON_RELEASE_INLINE car_id car_ownership_get_owned_car(car_ownership_id id) const noexcept {
			return car_id(car_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<car_id> car_ownership_get_owned_car(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::contiguous_tags<car_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<car_id> car_ownership_get_owned_car(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::partial_contiguous_tags<car_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_id> car_ownership_get_owned_car(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return ve::tagged_vector<car_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_car_ownership_set_owned_car(car_ownership_id id, car_id value) noexcept {
			if(bool(value)) {
				delete_car_ownership( car_ownership_id(car_ownership_id::value_base_t(value.index())) );
				internal_move_relationship_car_ownership(id, car_ownership_id(car_ownership_id::value_base_t(value.index())) );
			}
		}
		public:
		void car_ownership_set_owned_car(car_ownership_id id, car_id value) noexcept {
			if(bool(value)) {
				delete_car_ownership( car_ownership_id(car_ownership_id::value_base_t(value.index())) );
				internal_move_relationship_car_ownership(id, car_ownership_id(car_ownership_id::value_base_t(value.index())) );
			} else {
				delete_car_ownership(id);
			}
		}
		bool car_ownership_try_set_owned_car(car_ownership_id id, car_id value) noexcept {
			if(bool(value)) {
				if(car_ownership_is_valid( car_ownership_id(car_ownership_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_car_ownership(id, car_ownership_id(car_ownership_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE bool car_ownership_is_valid(car_ownership_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < car_ownership.size_used && car_is_valid(car_id(car_id::value_base_t(id.index()))) && (bool(car_ownership.m_owner.vptr()[id.index()]) || false);
		}
		
		uint32_t car_ownership_size() const noexcept { return car_ownership.size_used; }

		//
		// Functions for parentage:
		//
		DCON_RELEASE_INLINE person_id parentage_get_child(parentage_id id) const noexcept {
			return person_id(person_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<person_id> parentage_get_child(ve::contiguous_tags<parentage_id> id) const noexcept {
			return ve::contiguous_tags<person_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<person_id> parentage_get_child(ve::partial_contiguous_tags<parentage_id> id) const noexcept {
			return ve::partial_contiguous_tags<person_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<person_id> parentage_get_child(ve::tagged_vector<parentage_id> id) const noexcept {
			return ve::tagged_vector<person_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_parentage_set_child(parentage_id id, person_id value) noexcept {
			if(bool(value)) {
				delete_parentage( parentage_id(parentage_id::value_base_t(value.index())) );
				internal_move_relationship_parentage(id, parentage_id(parentage_id::value_base_t(value.index())) );
			}
		}
		public:
		void parentage_set_child(parentage_id id, person_id value) noexcept {
			if(bool(value)) {
				delete_parentage( parentage_id(parentage_id::value_base_t(value.index())) );
				internal_move_relationship_parentage(id, parentage_id(parentage_id::value_base_t(value.index())) );
			} else {
				delete_parentage(id);
			}
		}
		bool parentage_try_set_child(parentage_id id, person_id value) noexcept {
			if(bool(value)) {
				if(parentage_is_valid( parentage_id(parentage_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_parentage(id, parentage_id(parentage_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE person_id parentage_get_bio_parent(parentage_id id, int32_t i) const noexcept {
			return parentage.m_bio_parent.vptr()[id.index()][i];
		}
		DCON_RELEASE_INLINE bool parentage_has_bio_parent(parentage_id id, person_id v) const noexcept {
			if(parentage.m_bio_parent.vptr()[id.index()][0] == v) return true;
			if(parentage.m_bio_parent.vptr()[id.index()][1] == v) return true;
			return false;
		}
		private:
		void internal_parentage_set_bio_parent(parentage_id id, int32_t i, person_id value) noexcept {
			if(auto old_value = parentage.m_bio_parent.vptr()[id.index()][i]; bool(old_value)) {
				auto& vref = parentage.m_array_bio_parent.vptr()[old_value.index()];
				dcon::remove_unique_item(parentage.bio_parent_storage, vref, id);
			}
			if(bool(value)) {
				dcon::push_back(parentage.bio_parent_storage, parentage.m_array_bio_parent.vptr()[value.index()], id);
			}
			parentage.m_bio_parent.vptr()[id.index()][i] = value;
		}
		public:
		void parentage_set_bio_parent(parentage_id id, int32_t i, person_id value) noexcept {
			if(parentage_has_bio_parent(id, value)) value = person_id();
			if(!bool(value)) {
				delete_parentage(id);
				return;
			}
			internal_parentage_set_bio_parent(id, i, value);
		}
		bool parentage_try_set_bio_parent(parentage_id id, int32_t i, person_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			if(parentage_has_bio_parent(id, value)) return false;
			internal_parentage_set_bio_parent(id, i, value);
			return true;
		}
		void parentage_replace_bio_parent(parentage_id id, person_id newvalue, person_id oldvalue) noexcept {
			if(parentage.m_bio_parent.vptr()[id.index()][0] == oldvalue) {
				parentage_set_bio_parent(id, 0, newvalue);
				return;
			}
			if(parentage.m_bio_parent.vptr()[id.index()][1] == oldvalue) {
				parentage_set_bio_parent(id, 1, newvalue);
				return;
			}
		}
		bool parentage_try_replace_bio_parent(parentage_id id, person_id newvalue, person_id oldvalue) noexcept {
			if(parentage.m_bio_parent.vptr()[id.index()][0] == oldvalue) {
				return parentage_try_set_bio_parent(id, 0, newvalue);
			}
			if(parentage.m_bio_parent.vptr()[id.index()][1] == oldvalue) {
				return parentage_try_set_bio_parent(id, 1, newvalue);
			}
			return false;
		}
		DCON_RELEASE_INLINE bool parentage_is_valid(parentage_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < parentage.size_used && person_is_valid(person_id(person_id::value_base_t(id.index()))) && (bool(parentage.m_bio_parent.vptr()[id.index()][1]) || bool(parentage.m_bio_parent.vptr()[id.index()][1]) || false);
		}
		
		uint32_t parentage_size() const noexcept { return parentage.size_used; }


		//
		// container pop_back for car
		//
		void pop_back_car() {
			if(car.size_used == 0) return;
			car_id id_removed(car_id::value_base_t(car.size_used - 1));
			delete_car_ownership(car_ownership_id(car_ownership_id::value_base_t(id_removed.index())));
			car_ownership.size_used = car.size_used - 1;
			car.m_wheels.vptr()[id_removed.index()] = int32_t{};
			car.m_resale_value.vptr()[id_removed.index()] = float{};
			--car.size_used;
		}
		
		//
		// container resize for car
		//
		void car_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = car.size_used;
			if(new_size < old_size) {
				std::fill_n(car.m_wheels.vptr() + new_size, old_size - new_size, int32_t{});
				std::fill_n(car.m_resale_value.vptr() + new_size, old_size - new_size, float{});
				car_ownership_resize(std::min(new_size, car_ownership.size_used));
			} else if(new_size > old_size) {
			}
			car.size_used = new_size;
		}
		
		//
		// container create for car
		//
		car_id create_car() {
			car_id new_id(car_id::value_base_t(car.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(car.size_used >= 1200) std::abort();
			#else
			if(car.size_used >= 1200) throw dcon::out_of_space{};
			#endif
			car_ownership.size_used = car.size_used + 1;
			++car.size_used;
			return new_id;
		}
		
		//
		// container pop_back for person
		//
		void pop_back_person() {
			if(person.size_used == 0) return;
			person_id id_removed(person_id::value_base_t(person.size_used - 1));
			person_remove_all_car_ownership_as_owner(id_removed);
			delete_parentage(parentage_id(parentage_id::value_base_t(id_removed.index())));
			parentage.size_used = person.size_used - 1;
			person_remove_all_parentage_as_bio_parent(id_removed);
			person.m_age.vptr()[id_removed.index()] = int32_t{};
			person.m_wealth.vptr()[id_removed.index()] = float{};
			--person.size_used;
		}
		
		//
		// container resize for person
		//
		void person_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 100) std::abort();
			#else
			if(new_size > 100) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = person.size_used;
			if(new_size < old_size) {
				std::fill_n(person.m_age.vptr() + new_size, old_size - new_size, int32_t{});
				std::fill_n(person.m_wealth.vptr() + new_size, old_size - new_size, float{});
				car_ownership_resize(0);
				parentage_resize(std::min(new_size, parentage.size_used));
				parentage_resize(0);
			} else if(new_size > old_size) {
			}
			person.size_used = new_size;
		}
		
		//
		// container create for person
		//
		person_id create_person() {
			person_id new_id(person_id::value_base_t(person.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(person.size_used >= 100) std::abort();
			#else
			if(person.size_used >= 100) throw dcon::out_of_space{};
			#endif
			parentage.size_used = person.size_used + 1;
			++person.size_used;
			return new_id;
		}
		
		//
		// container resize for car_ownership
		//
		void car_ownership_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = car_ownership.size_used;
			if(new_size < old_size) {
				std::fill_n(car_ownership.m_owner.vptr() + 0, old_size, person_id{});
				std::fill_n(car_ownership.m_array_owner.vptr() + 0, person.size_used, std::vector<car_ownership_id>{});
				std::fill_n(car_ownership.m_ownership_date.vptr() + new_size, old_size - new_size, int32_t{});
			} else if(new_size > old_size) {
			}
			car_ownership.size_used = new_size;
		}
		
		//
		// container delete for car_ownership
		//
		void delete_car_ownership(car_ownership_id id_removed) {
			internal_car_ownership_set_owner(id_removed, person_id());
			car_ownership.m_ownership_date.vptr()[id_removed.index()] = int32_t{};
		}
		
		//
		// container pop_back for car_ownership
		//
		void pop_back_car_ownership() {
			if(car_ownership.size_used == 0) return;
			car_ownership_id id_removed(car_ownership_id::value_base_t(car_ownership.size_used - 1));
			internal_car_ownership_set_owner(id_removed, person_id());
			car_ownership.m_ownership_date.vptr()[id_removed.index()] = int32_t{};
			--car_ownership.size_used;
		}
		
		private:
		//
		// container move relationship for car_ownership
		//
		void internal_move_relationship_car_ownership(car_ownership_id last_id, car_ownership_id id_removed) {
			internal_car_ownership_set_owner(id_removed, person_id());
			if(auto tmp = car_ownership.m_owner.vptr()[last_id.index()]; bool(tmp)) {
				auto& vref = car_ownership.m_array_owner.vptr()[tmp.index()];
				if(auto pos = std::find(vref.begin(), vref.end(), last_id); pos != vref.end()) {
					*pos = id_removed;
				}
			}
			car_ownership.m_owner.vptr()[id_removed.index()] = std::move(car_ownership.m_owner.vptr()[last_id.index()]);
			car_ownership.m_owner.vptr()[last_id.index()] = person_id();
			car_ownership.m_ownership_date.vptr()[id_removed.index()] = std::move(car_ownership.m_ownership_date.vptr()[last_id.index()]);
			car_ownership.m_ownership_date.vptr()[last_id.index()] = int32_t{};
		}
		
		public:
		//
		// container try create relationship for car_ownership
		//
		car_ownership_id try_create_car_ownership(person_id owner_p, car_id owned_car_p) {
			if(!bool(owner_p)) return car_ownership_id();
			if(!bool(owned_car_p)) return car_ownership_id();
			if(car_ownership_is_valid(car_ownership_id(car_ownership_id::value_base_t(owned_car_p.index())))) return car_ownership_id();
			car_ownership_id new_id(car_ownership_id::value_base_t(owned_car_p.index()));
			if(car_ownership.size_used < uint32_t(owned_car_p.value)) car_ownership_resize(uint32_t(owned_car_p.value));
			internal_car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}
		
		//
		// container force create relationship for car_ownership
		//
		car_ownership_id force_create_car_ownership(person_id owner_p, car_id owned_car_p) {
			car_ownership_id new_id(car_ownership_id::value_base_t(owned_car_p.index()));
			if(car_ownership.size_used < uint32_t(owned_car_p.value)) car_ownership_resize(uint32_t(owned_car_p.value));
			internal_car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}
		
		//
		// container resize for parentage
		//
		void parentage_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 100) std::abort();
			#else
			if(new_size > 100) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = parentage.size_used;
			if(new_size < old_size) {
				std::destroy_n(parentage.m_bio_parent.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(parentage.m_bio_parent.vptr() + 0, old_size);
				std::for_each(parentage.m_array_bio_parent.vptr() + 0, parentage.m_array_bio_parent.vptr() + 0 + person.size_used, [t = this](dcon::stable_mk_2_tag& i){ t->parentage.bio_parent_storage.release(i); });
			} else if(new_size > old_size) {
			}
			parentage.size_used = new_size;
		}
		
		//
		// container delete for parentage
		//
		void delete_parentage(parentage_id id_removed) {
			internal_parentage_set_bio_parent(id_removed, 0, person_id());
			internal_parentage_set_bio_parent(id_removed, 1, person_id());
		}
		
		//
		// container pop_back for parentage
		//
		void pop_back_parentage() {
			if(parentage.size_used == 0) return;
			parentage_id id_removed(parentage_id::value_base_t(parentage.size_used - 1));
			internal_parentage_set_bio_parent(id_removed, 0, person_id());
			internal_parentage_set_bio_parent(id_removed, 1, person_id());
			--parentage.size_used;
		}
		
		private:
		//
		// container move relationship for parentage
		//
		void internal_move_relationship_parentage(parentage_id last_id, parentage_id id_removed) {
			internal_parentage_set_bio_parent(id_removed, 0, person_id());
			internal_parentage_set_bio_parent(id_removed, 1, person_id());
			if(auto tmp = parentage.m_bio_parent.vptr()[last_id.index()][0]; bool(tmp)) {
				dcon::replace_unique_item(parentage.bio_parent_storage, parentage.m_array_bio_parent.vptr()[tmp.index()], last_id, id_removed);
			}
			if(auto tmp = parentage.m_bio_parent.vptr()[last_id.index()][1]; bool(tmp)) {
				dcon::replace_unique_item(parentage.bio_parent_storage, parentage.m_array_bio_parent.vptr()[tmp.index()], last_id, id_removed);
			}
			parentage.m_bio_parent.vptr()[id_removed.index()][0] = parentage.m_bio_parent.vptr()[last_id.index()][0];
			parentage.m_bio_parent.vptr()[last_id.index()][0] = person_id();
			parentage.m_bio_parent.vptr()[id_removed.index()][1] = parentage.m_bio_parent.vptr()[last_id.index()][1];
			parentage.m_bio_parent.vptr()[last_id.index()][1] = person_id();
		}
		
		public:
		//
		// container try create relationship for parentage
		//
		parentage_id try_create_parentage(person_id child_p, person_id bio_parent_p0, person_id bio_parent_p1) {
			if(!bool(child_p)) return parentage_id();
			if(parentage_is_valid(parentage_id(parentage_id::value_base_t(child_p.index())))) return parentage_id();
			if(!bool(bio_parent_p0)) return parentage_id();
			if(bool(bio_parent_p0) && bio_parent_p0 == bio_parent_p1) return parentage_id();
			if(!bool(bio_parent_p1)) return parentage_id();
			parentage_id new_id(parentage_id::value_base_t(child_p.index()));
			if(parentage.size_used < uint32_t(child_p.value)) parentage_resize(uint32_t(child_p.value));
			internal_parentage_set_bio_parent(new_id, 0, bio_parent_p0);
			internal_parentage_set_bio_parent(new_id, 1, bio_parent_p1);
			return new_id;
		}
		
		//
		// container force create relationship for parentage
		//
		parentage_id force_create_parentage(person_id child_p, person_id bio_parent_p0, person_id bio_parent_p1) {
			parentage_id new_id(parentage_id::value_base_t(child_p.index()));
			if(parentage.size_used < uint32_t(child_p.value)) parentage_resize(uint32_t(child_p.value));
			internal_parentage_set_bio_parent(new_id, 0, bio_parent_p0);
			internal_parentage_set_bio_parent(new_id, 1, bio_parent_p1);
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car(T&& func) {
			for(uint32_t i = 0; i < car.size_used; ++i) {
				car_id tmp = car_id(car_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_person(T&& func) {
			for(uint32_t i = 0; i < person.size_used; ++i) {
				person_id tmp = person_id(person_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) {
			for(uint32_t i = 0; i < car_ownership.size_used; ++i) {
				car_ownership_id tmp = car_ownership_id(car_ownership_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_parentage(T&& func) {
			for(uint32_t i = 0; i < parentage.size_used; ++i) {
				parentage_id tmp = parentage_id(parentage_id::value_base_t(i));
				func(tmp);
			}
		}
		

		friend internal::query_q_all_owner_ages_const_iterator;
		friend internal::query_q_all_owner_ages_iterator;
		internal::query_q_all_owner_ages_instance query_q_all_owner_ages() { return internal::query_q_all_owner_ages_instance(*this); }
		internal::query_q_all_owner_ages_const_instance query_q_all_owner_ages() const { return internal::query_q_all_owner_ages_const_instance(*this); }
		friend internal::query_rev_car_from_owner_const_iterator;
		friend internal::query_rev_car_from_owner_iterator;
		internal::query_rev_car_from_owner_instance query_rev_car_from_owner() { return internal::query_rev_car_from_owner_instance(*this); }
		internal::query_rev_car_from_owner_const_instance query_rev_car_from_owner() const { return internal::query_rev_car_from_owner_const_instance(*this); }
		friend internal::query_param_car_from_owner_const_iterator;
		friend internal::query_param_car_from_owner_iterator;
		internal::query_param_car_from_owner_instance query_param_car_from_owner(person_id from_person) { return internal::query_param_car_from_owner_instance(*this, from_person); }
		internal::query_param_car_from_owner_const_instance query_param_car_from_owner(person_id from_person) const { return internal::query_param_car_from_owner_const_instance(*this, from_person); }
		friend internal::query_q_all_owner_ages_plus_const_iterator;
		friend internal::query_q_all_owner_ages_plus_iterator;
		internal::query_q_all_owner_ages_plus_instance query_q_all_owner_ages_plus() { return internal::query_q_all_owner_ages_plus_instance(*this); }
		internal::query_q_all_owner_ages_plus_const_instance query_q_all_owner_ages_plus() const { return internal::query_q_all_owner_ages_plus_const_instance(*this); }
		friend internal::query_rev_car_from_owner_plus_const_iterator;
		friend internal::query_rev_car_from_owner_plus_iterator;
		internal::query_rev_car_from_owner_plus_instance query_rev_car_from_owner_plus() { return internal::query_rev_car_from_owner_plus_instance(*this); }
		internal::query_rev_car_from_owner_plus_const_instance query_rev_car_from_owner_plus() const { return internal::query_rev_car_from_owner_plus_const_instance(*this); }
		friend internal::query_grandparents_const_iterator;
		friend internal::query_grandparents_iterator;
		internal::query_grandparents_instance query_grandparents(person_id from_person) { return internal::query_grandparents_instance(*this, from_person); }
		internal::query_grandparents_const_instance query_grandparents(person_id from_person) const { return internal::query_grandparents_const_instance(*this, from_person); }
		friend internal::query_grandchildren_const_iterator;
		friend internal::query_grandchildren_iterator;
		internal::query_grandchildren_instance query_grandchildren(person_id from_person, int32_t age_filter) { return internal::query_grandchildren_instance(*this, from_person, age_filter); }
		internal::query_grandchildren_const_instance query_grandchildren(person_id from_person, int32_t age_filter) const { return internal::query_grandchildren_const_instance(*this, from_person, age_filter); }
		friend internal::query_group_grandchildren_const_iterator;
		friend internal::query_group_grandchildren_iterator;
		internal::query_group_grandchildren_instance query_group_grandchildren(int32_t age_filter) { return internal::query_group_grandchildren_instance(*this, age_filter); }
		internal::query_group_grandchildren_const_instance query_group_grandchildren(int32_t age_filter) const { return internal::query_group_grandchildren_const_instance(*this, age_filter); }
		friend internal::query_sum_car_value_const_iterator;
		friend internal::query_sum_car_value_iterator;
		internal::query_sum_car_value_instance query_sum_car_value(person_id from_person) { return internal::query_sum_car_value_instance(*this, from_person); }
		internal::query_sum_car_value_const_instance query_sum_car_value(person_id from_person) const { return internal::query_sum_car_value_const_instance(*this, from_person); }
		friend internal::query_pairs_of_cars_const_iterator;
		friend internal::query_pairs_of_cars_iterator;
		internal::query_pairs_of_cars_instance query_pairs_of_cars() { return internal::query_pairs_of_cars_instance(*this); }
		internal::query_pairs_of_cars_const_instance query_pairs_of_cars() const { return internal::query_pairs_of_cars_const_instance(*this); }
		friend internal::query_siblings_const_iterator;
		friend internal::query_siblings_iterator;
		internal::query_siblings_instance query_siblings(person_id person_param) { return internal::query_siblings_instance(*this, person_param); }
		internal::query_siblings_const_instance query_siblings(person_id person_param) const { return internal::query_siblings_const_instance(*this, person_param); }


		void reset() {
			car_ownership_resize(0);
			parentage_resize(0);
			car_resize(0);
			person_resize(0);
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, car_id> car_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, car_id>(car.size_used);
		}
		ve::vectorizable_buffer<int32_t, car_id> car_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, car_id>(car.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_car(F&& functor) {
			ve::execute_serial<car_id>(car.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_car(F&& functor) {
			ve::execute_parallel_exact<car_id>(car.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, person_id> person_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, person_id>(person.size_used);
		}
		ve::vectorizable_buffer<int32_t, person_id> person_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, person_id>(person.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_person(F&& functor) {
			ve::execute_serial<person_id>(person.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_person(F&& functor) {
			ve::execute_parallel_exact<person_id>(person.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, car_ownership_id> car_ownership_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, car_ownership_id>(car_ownership.size_used);
		}
		ve::vectorizable_buffer<int32_t, car_ownership_id> car_ownership_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, car_ownership_id>(car_ownership.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_car_ownership(F&& functor) {
			ve::execute_serial<car_ownership_id>(car_ownership.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_car_ownership(F&& functor) {
			ve::execute_parallel_exact<car_ownership_id>(car_ownership.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, parentage_id> parentage_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, parentage_id>(parentage.size_used);
		}
		ve::vectorizable_buffer<int32_t, parentage_id> parentage_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, parentage_id>(parentage.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_parentage(F&& functor) {
			ve::execute_serial<parentage_id>(parentage.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_parentage(F&& functor) {
			ve::execute_parallel_exact<parentage_id>(parentage.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.car = true;
			result.car_wheels = true;
			result.car_resale_value = true;
			result.person = true;
			result.person_age = true;
			result.person_wealth = true;
			result.car_ownership = true;
			result.car_ownership_owner = true;
			result.car_ownership_owned_car = true;
			result.car_ownership_ownership_date = true;
			result.parentage = true;
			result.parentage_child = true;
			result.parentage_bio_parent = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.car) {
				dcon::record_header header(0, "uint32_t", "car", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.car_wheels) {
				dcon::record_header iheader(0, "int32_t", "car", "wheels");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * car.size_used;
			}
			if(serialize_selection.car_resale_value) {
				dcon::record_header iheader(0, "float", "car", "resale_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * car.size_used;
			}
			if(serialize_selection.person) {
				dcon::record_header header(0, "uint32_t", "person", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.person_age) {
				dcon::record_header iheader(0, "int32_t", "person", "age");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * person.size_used;
			}
			if(serialize_selection.person_wealth) {
				dcon::record_header iheader(0, "float", "person", "wealth");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * person.size_used;
			}
			if(serialize_selection.car_ownership) {
				dcon::record_header header(0, "uint32_t", "car_ownership", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.car_ownership_owner) {
					dcon::record_header iheader(0, "uint8_t", "car_ownership", "owner");
					total_size += iheader.serialize_size();
					total_size += sizeof(person_id) * car_ownership.size_used;
				}
				dcon::record_header headerb(0, "$", "car_ownership", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header iheader(0, "int32_t", "car_ownership", "ownership_date");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * car_ownership.size_used;
			}
			if(serialize_selection.parentage) {
				dcon::record_header header(0, "uint32_t", "parentage", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.parentage_bio_parent) {
					dcon::record_header iheader(0, "std::array<uint8_t,2>", "parentage", "bio_parent");
					total_size += iheader.serialize_size();
					total_size += sizeof(std::array<person_id, 2>) * parentage.size_used;
				}
				dcon::record_header headerb(0, "$", "parentage", "$index_end");
				total_size += headerb.serialize_size();
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.car) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = car.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.car_wheels) {
				dcon::record_header header(sizeof(int32_t) * car.size_used, "int32_t", "car", "wheels");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), car.m_wheels.vptr(), sizeof(int32_t) * car.size_used);
				output_buffer += sizeof(int32_t) * car.size_used;
			}
			if(serialize_selection.car_resale_value) {
				dcon::record_header header(sizeof(float) * car.size_used, "float", "car", "resale_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), car.m_resale_value.vptr(), sizeof(float) * car.size_used);
				output_buffer += sizeof(float) * car.size_used;
			}
			if(serialize_selection.person) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "person", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = person.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.person_age) {
				dcon::record_header header(sizeof(int32_t) * person.size_used, "int32_t", "person", "age");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), person.m_age.vptr(), sizeof(int32_t) * person.size_used);
				output_buffer += sizeof(int32_t) * person.size_used;
			}
			if(serialize_selection.person_wealth) {
				dcon::record_header header(sizeof(float) * person.size_used, "float", "person", "wealth");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), person.m_wealth.vptr(), sizeof(float) * person.size_used);
				output_buffer += sizeof(float) * person.size_used;
			}
			if(serialize_selection.car_ownership) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car_ownership", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = car_ownership.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(person_id) * car_ownership.size_used, "uint8_t", "car_ownership", "owner");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<person_id*>(output_buffer), car_ownership.m_owner.vptr(), sizeof(person_id) * car_ownership.size_used);
					output_buffer += sizeof(person_id) *  car_ownership.size_used;
				}
				dcon::record_header headerb(0, "$", "car_ownership", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header header(sizeof(int32_t) * car_ownership.size_used, "int32_t", "car_ownership", "ownership_date");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), car_ownership.m_ownership_date.vptr(), sizeof(int32_t) * car_ownership.size_used);
				output_buffer += sizeof(int32_t) * car_ownership.size_used;
			}
			if(serialize_selection.parentage) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "parentage", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = parentage.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(std::array<person_id, 2>) * parentage.size_used, "std::array<uint8_t,2>", "parentage", "bio_parent");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<std::array<person_id, 2>*>(output_buffer), parentage.m_bio_parent.vptr(), sizeof(std::array<person_id, 2>) * parentage.size_used);
					output_buffer += sizeof(std::array<person_id, 2>) *  parentage.size_used;
				}
				dcon::record_header headerb(0, "$", "parentage", "$index_end");
				headerb.serialize(output_buffer);
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
					if(header.is_object("car")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.car = true;
						}
						else if(header.is_property("wheels")) {
							if(header.is_type("int32_t")) {
								std::memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
						}
						else if(header.is_property("resale_value")) {
							if(header.is_type("float")) {
								std::memcpy(car.m_resale_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(float), header.record_size));
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
						}
					} else
					if(header.is_object("person")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.person = true;
						}
						else if(header.is_property("age")) {
							if(header.is_type("int32_t")) {
								std::memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
						}
						else if(header.is_property("wealth")) {
							if(header.is_type("float")) {
								std::memcpy(person.m_wealth.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(float), header.record_size));
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
						}
					} else
					if(header.is_object("car_ownership")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= car_ownership.size_used) {
								car_ownership_resize(0);
							}
							car_ownership_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.car_ownership = true;
						}
						else if(header.is_property("owner")) {
							if(header.is_type("uint8_t")) {
								std::memcpy(car_ownership.m_owner.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(uint8_t), header.record_size));
								serialize_selection.car_ownership_owner = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car_ownership.m_owner.vptr()[i].value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_owner = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car_ownership.m_owner.vptr()[i].value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_owner = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.car_ownership_owner == true) {
								for(uint32_t i = 0; i < car_ownership.size_used; ++i) {
									auto tmp = car_ownership.m_owner.vptr()[i];
									car_ownership.m_owner.vptr()[i] = person_id();
									internal_car_ownership_set_owner(car_ownership_id(car_ownership_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("ownership_date")) {
							if(header.is_type("int32_t")) {
								std::memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
						}
					} else
					if(header.is_object("parentage")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= parentage.size_used) {
								parentage_resize(0);
							}
							parentage_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.parentage = true;
						}
						else if(header.is_property("bio_parent")) {
							if(header.is_type("std::array<uint8_t,2>")) {
								std::memcpy(parentage.m_bio_parent.vptr(), reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer), std::min(size_t(parentage.size_used) * sizeof(std::array<uint8_t, 2>), header.record_size));
								serialize_selection.parentage_bio_parent = true;
							}
							else if(header.is_type("std::array<uint16_t,2>")) {
								for(uint32_t i = 0; i < std::min(parentage.size_used, uint32_t(header.record_size / sizeof(std::array<uint16_t,2>))); ++i) {
									parentage.m_bio_parent.vptr()[i][0].value = uint8_t((*(reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer) + i))[0]);
									parentage.m_bio_parent.vptr()[i][1].value = uint8_t((*(reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.parentage_bio_parent = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(parentage.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									parentage.m_bio_parent.vptr()[i][0].value = uint8_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									parentage.m_bio_parent.vptr()[i][1].value = uint8_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.parentage_bio_parent = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.parentage_bio_parent == true) {
								for(uint32_t i = 0; i < parentage.size_used; ++i) {
									 {
										auto tmp = parentage.m_bio_parent.vptr()[i][0];
										parentage.m_bio_parent.vptr()[i][0] = person_id();
										internal_parentage_set_bio_parent(parentage_id(parentage_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = parentage.m_bio_parent.vptr()[i][1];
										parentage.m_bio_parent.vptr()[i][1] = person_id();
										internal_parentage_set_bio_parent(parentage_id(parentage_id::value_base_t(i)), 1, tmp);
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
					if(header.is_object("car") && mask.car) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.car = true;
						}
						else if(header.is_property("wheels") && mask.car_wheels) {
							if(header.is_type("int32_t")) {
								std::memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_wheels = true;
							}
						}
						else if(header.is_property("resale_value") && mask.car_resale_value) {
							if(header.is_type("float")) {
								std::memcpy(car.m_resale_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(float), header.record_size));
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car.m_resale_value.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_resale_value = true;
							}
						}
					} else
					if(header.is_object("person") && mask.person) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.person = true;
						}
						else if(header.is_property("age") && mask.person_age) {
							if(header.is_type("int32_t")) {
								std::memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.person_age = true;
							}
						}
						else if(header.is_property("wealth") && mask.person_wealth) {
							if(header.is_type("float")) {
								std::memcpy(person.m_wealth.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(float), header.record_size));
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									person.m_wealth.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.person_wealth = true;
							}
						}
					} else
					if(header.is_object("car_ownership") && mask.car_ownership) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= car_ownership.size_used) {
								car_ownership_resize(0);
							}
							car_ownership_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.car_ownership = true;
						}
						else if(header.is_property("owner") && mask.car_ownership_owner) {
							if(header.is_type("uint8_t")) {
								std::memcpy(car_ownership.m_owner.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(uint8_t), header.record_size));
								serialize_selection.car_ownership_owner = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car_ownership.m_owner.vptr()[i].value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_owner = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car_ownership.m_owner.vptr()[i].value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_owner = true;
							}
						}
						else if(header.is_property("$index_end") && mask.car_ownership) {
							if(serialize_selection.car_ownership_owner == true) {
								for(uint32_t i = 0; i < car_ownership.size_used; ++i) {
									auto tmp = car_ownership.m_owner.vptr()[i];
									car_ownership.m_owner.vptr()[i] = person_id();
									internal_car_ownership_set_owner(car_ownership_id(car_ownership_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("ownership_date") && mask.car_ownership_ownership_date) {
							if(header.is_type("int32_t")) {
								std::memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.car_ownership_ownership_date = true;
							}
						}
					} else
					if(header.is_object("parentage") && mask.parentage) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= parentage.size_used) {
								parentage_resize(0);
							}
							parentage_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.parentage = true;
						}
						else if(header.is_property("bio_parent") && mask.parentage_bio_parent) {
							if(header.is_type("std::array<uint8_t,2>")) {
								std::memcpy(parentage.m_bio_parent.vptr(), reinterpret_cast<std::array<uint8_t,2> const*>(input_buffer), std::min(size_t(parentage.size_used) * sizeof(std::array<uint8_t, 2>), header.record_size));
								serialize_selection.parentage_bio_parent = true;
							}
							else if(header.is_type("std::array<uint16_t,2>")) {
								for(uint32_t i = 0; i < std::min(parentage.size_used, uint32_t(header.record_size / sizeof(std::array<uint16_t,2>))); ++i) {
									parentage.m_bio_parent.vptr()[i][0].value = uint8_t((*(reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer) + i))[0]);
									parentage.m_bio_parent.vptr()[i][1].value = uint8_t((*(reinterpret_cast<std::array<uint16_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.parentage_bio_parent = true;
							}
							else if(header.is_type("std::array<uint32_t,2>")) {
								for(uint32_t i = 0; i < std::min(parentage.size_used, uint32_t(header.record_size / sizeof(std::array<uint32_t,2>))); ++i) {
									parentage.m_bio_parent.vptr()[i][0].value = uint8_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[0]);
									parentage.m_bio_parent.vptr()[i][1].value = uint8_t((*(reinterpret_cast<std::array<uint32_t,2> const*>(input_buffer) + i))[1]);
								}
								serialize_selection.parentage_bio_parent = true;
							}
						}
						else if(header.is_property("$index_end") && mask.parentage) {
							if(serialize_selection.parentage_bio_parent == true) {
								for(uint32_t i = 0; i < parentage.size_used; ++i) {
									 {
										auto tmp = parentage.m_bio_parent.vptr()[i][0];
										parentage.m_bio_parent.vptr()[i][0] = person_id();
										internal_parentage_set_bio_parent(parentage_id(parentage_id::value_base_t(i)), 0, tmp);
									}
									 {
										auto tmp = parentage.m_bio_parent.vptr()[i][1];
										parentage.m_bio_parent.vptr()[i][1] = person_id();
										internal_parentage_set_bio_parent(parentage_id(parentage_id::value_base_t(i)), 1, tmp);
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

	DCON_RELEASE_INLINE int32_t& car_fat_id::get_wheels() const noexcept {
		return container.car_get_wheels(id);
	}
	DCON_RELEASE_INLINE void car_fat_id::set_wheels(int32_t v) const noexcept {
		container.car_set_wheels(id, v);
	}
	DCON_RELEASE_INLINE float& car_fat_id::get_resale_value() const noexcept {
		return container.car_get_resale_value(id);
	}
	DCON_RELEASE_INLINE void car_fat_id::set_resale_value(float v) const noexcept {
		container.car_set_resale_value(id, v);
	}
	DCON_RELEASE_INLINE car_ownership_fat_id car_fat_id::get_car_ownership_as_owned_car() const noexcept {
		return car_ownership_fat_id(container, container.car_get_car_ownership_as_owned_car(id));
	}
	DCON_RELEASE_INLINE void car_fat_id::remove_car_ownership_as_owned_car() const noexcept {
		container.car_remove_car_ownership_as_owned_car(id);
	}
	DCON_RELEASE_INLINE car_ownership_fat_id car_fat_id::get_car_ownership() const noexcept {
		return car_ownership_fat_id(container, container.car_get_car_ownership(id));
	}
	DCON_RELEASE_INLINE void car_fat_id::remove_car_ownership() const noexcept {
		container.car_remove_car_ownership(id);
	}
	DCON_RELEASE_INLINE person_fat_id car_fat_id::get_owner_from_car_ownership() const noexcept {
		return person_fat_id(container, container.car_get_owner_from_car_ownership(id));
	}
	DCON_RELEASE_INLINE void car_fat_id::set_owner_from_car_ownership(person_id v) const noexcept {
		container.car_set_owner_from_car_ownership(id, v);
	}
	DCON_RELEASE_INLINE void car_fat_id::set_ownership_date_from_car_ownership(int32_t v) const noexcept {
		container.car_set_ownership_date_from_car_ownership(id, v);
	}
	DCON_RELEASE_INLINE int32_t car_fat_id::get_ownership_date_from_car_ownership() const noexcept {
		return container.car_get_ownership_date_from_car_ownership(id);
	}
	DCON_RELEASE_INLINE bool car_fat_id::is_valid() const noexcept {
		return container.car_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t car_const_fat_id::get_wheels() const noexcept {
		return container.car_get_wheels(id);
	}
	DCON_RELEASE_INLINE float car_const_fat_id::get_resale_value() const noexcept {
		return container.car_get_resale_value(id);
	}
	DCON_RELEASE_INLINE car_ownership_const_fat_id car_const_fat_id::get_car_ownership_as_owned_car() const noexcept {
		return car_ownership_const_fat_id(container, container.car_get_car_ownership_as_owned_car(id));
	}
	DCON_RELEASE_INLINE car_ownership_const_fat_id car_const_fat_id::get_car_ownership() const noexcept {
		return car_ownership_const_fat_id(container, container.car_get_car_ownership(id));
	}
	DCON_RELEASE_INLINE person_const_fat_id car_const_fat_id::get_owner_from_car_ownership() const noexcept {
		return person_const_fat_id(container, container.car_get_owner_from_car_ownership(id));
	}
	DCON_RELEASE_INLINE int32_t car_const_fat_id::get_ownership_date_from_car_ownership() const noexcept {
		return container.car_get_ownership_date_from_car_ownership(id);
	}
	DCON_RELEASE_INLINE bool car_const_fat_id::is_valid() const noexcept {
		return container.car_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t& person_fat_id::get_age() const noexcept {
		return container.person_get_age(id);
	}
	DCON_RELEASE_INLINE void person_fat_id::set_age(int32_t v) const noexcept {
		container.person_set_age(id, v);
	}
	DCON_RELEASE_INLINE float& person_fat_id::get_wealth() const noexcept {
		return container.person_get_wealth(id);
	}
	DCON_RELEASE_INLINE void person_fat_id::set_wealth(float v) const noexcept {
		container.person_set_wealth(id, v);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_fat_id::for_each_car_ownership_as_owner(T&& func) const {
		container.person_for_each_car_ownership_as_owner(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_fat_id::range_of_car_ownership_as_owner() const {
		return container.person_range_of_car_ownership_as_owner(id);
	}
	DCON_RELEASE_INLINE void person_fat_id::remove_all_car_ownership_as_owner() const noexcept {
		container.person_remove_all_car_ownership_as_owner(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_fat_id::for_each_car_ownership(T&& func) const {
		container.person_for_each_car_ownership(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_fat_id::range_of_car_ownership() const {
		return container.person_range_of_car_ownership(id);
	}
	DCON_RELEASE_INLINE void person_fat_id::remove_all_car_ownership() const noexcept {
		container.person_remove_all_car_ownership(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_fat_id::for_each_owned_car_from_car_ownership(T&& func) const {
		container.person_for_each_owned_car_from_car_ownership(id, [&, t = this](car_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool person_fat_id::has_owned_car_from_car_ownership(car_id target) const {
		return container.person_has_owned_car_from_car_ownership(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_fat_id::for_each_ownership_date_from_car_ownership(T&& func) const {
		container.person_for_each_ownership_date_from_car_ownership(id, func);
	}
	DCON_RELEASE_INLINE bool person_fat_id::has_ownership_date_from_car_ownership(int32_t target) const {
		return container.person_has_ownership_date_from_car_ownership(id, target);
	}
	DCON_RELEASE_INLINE parentage_fat_id person_fat_id::get_parentage_as_child() const noexcept {
		return parentage_fat_id(container, container.person_get_parentage_as_child(id));
	}
	DCON_RELEASE_INLINE void person_fat_id::remove_parentage_as_child() const noexcept {
		container.person_remove_parentage_as_child(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_fat_id::for_each_parentage_as_bio_parent(T&& func) const {
		container.person_for_each_parentage_as_bio_parent(id, [&, t = this](parentage_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<parentage_id const*, parentage_id const*> person_fat_id::range_of_parentage_as_bio_parent() const {
		return container.person_range_of_parentage_as_bio_parent(id);
	}
	DCON_RELEASE_INLINE void person_fat_id::remove_all_parentage_as_bio_parent() const noexcept {
		container.person_remove_all_parentage_as_bio_parent(id);
	}
	DCON_RELEASE_INLINE bool person_fat_id::is_valid() const noexcept {
		return container.person_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t person_const_fat_id::get_age() const noexcept {
		return container.person_get_age(id);
	}
	DCON_RELEASE_INLINE float person_const_fat_id::get_wealth() const noexcept {
		return container.person_get_wealth(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_car_ownership_as_owner(T&& func) const {
		container.person_for_each_car_ownership_as_owner(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_const_fat_id::range_of_car_ownership_as_owner() const {
		return container.person_range_of_car_ownership_as_owner(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_car_ownership(T&& func) const {
		container.person_for_each_car_ownership(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_const_fat_id::range_of_car_ownership() const {
		return container.person_range_of_car_ownership(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_owned_car_from_car_ownership(T&& func) const {
		container.person_for_each_owned_car_from_car_ownership(id, [&, t = this](car_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool person_const_fat_id::has_owned_car_from_car_ownership(car_id target) const {
		return container.person_has_owned_car_from_car_ownership(id, target);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_ownership_date_from_car_ownership(T&& func) const {
		container.person_for_each_ownership_date_from_car_ownership(id, func);
	}
	DCON_RELEASE_INLINE bool person_const_fat_id::has_ownership_date_from_car_ownership(int32_t target) const {
		return container.person_has_ownership_date_from_car_ownership(id, target);
	}
	DCON_RELEASE_INLINE parentage_const_fat_id person_const_fat_id::get_parentage_as_child() const noexcept {
		return parentage_const_fat_id(container, container.person_get_parentage_as_child(id));
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_parentage_as_bio_parent(T&& func) const {
		container.person_for_each_parentage_as_bio_parent(id, [&, t = this](parentage_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<parentage_id const*, parentage_id const*> person_const_fat_id::range_of_parentage_as_bio_parent() const {
		return container.person_range_of_parentage_as_bio_parent(id);
	}
	DCON_RELEASE_INLINE bool person_const_fat_id::is_valid() const noexcept {
		return container.person_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t& car_ownership_fat_id::get_ownership_date() const noexcept {
		return container.car_ownership_get_ownership_date(id);
	}
	DCON_RELEASE_INLINE void car_ownership_fat_id::set_ownership_date(int32_t v) const noexcept {
		container.car_ownership_set_ownership_date(id, v);
	}
	DCON_RELEASE_INLINE person_fat_id car_ownership_fat_id::get_owner() const noexcept {
		return person_fat_id(container, container.car_ownership_get_owner(id));
	}
	DCON_RELEASE_INLINE void car_ownership_fat_id::set_owner(person_id val) const noexcept {
		container.car_ownership_set_owner(id, val);
	}
	DCON_RELEASE_INLINE bool car_ownership_fat_id::try_set_owner(person_id val) const noexcept {
		return container.car_ownership_try_set_owner(id, val);
	}
	DCON_RELEASE_INLINE car_fat_id car_ownership_fat_id::get_owned_car() const noexcept {
		return car_fat_id(container, container.car_ownership_get_owned_car(id));
	}
	DCON_RELEASE_INLINE void car_ownership_fat_id::set_owned_car(car_id val) const noexcept {
		container.car_ownership_set_owned_car(id, val);
	}
	DCON_RELEASE_INLINE bool car_ownership_fat_id::try_set_owned_car(car_id val) const noexcept {
		return container.car_ownership_try_set_owned_car(id, val);
	}
	DCON_RELEASE_INLINE bool car_ownership_fat_id::is_valid() const noexcept {
		return container.car_ownership_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t car_ownership_const_fat_id::get_ownership_date() const noexcept {
		return container.car_ownership_get_ownership_date(id);
	}
	DCON_RELEASE_INLINE person_const_fat_id car_ownership_const_fat_id::get_owner() const noexcept {
		return person_const_fat_id(container, container.car_ownership_get_owner(id));
	}
	DCON_RELEASE_INLINE car_const_fat_id car_ownership_const_fat_id::get_owned_car() const noexcept {
		return car_const_fat_id(container, container.car_ownership_get_owned_car(id));
	}
	DCON_RELEASE_INLINE bool car_ownership_const_fat_id::is_valid() const noexcept {
		return container.car_ownership_is_valid(id);
	}
	
	DCON_RELEASE_INLINE person_fat_id parentage_fat_id::get_child() const noexcept {
		return person_fat_id(container, container.parentage_get_child(id));
	}
	DCON_RELEASE_INLINE void parentage_fat_id::set_child(person_id val) const noexcept {
		container.parentage_set_child(id, val);
	}
	DCON_RELEASE_INLINE bool parentage_fat_id::try_set_child(person_id val) const noexcept {
		return container.parentage_try_set_child(id, val);
	}
	DCON_RELEASE_INLINE person_fat_id parentage_fat_id::get_bio_parent(int32_t i) const noexcept {
		return person_fat_id(container, container.parentage_get_bio_parent(id, i));
	}
	DCON_RELEASE_INLINE bool parentage_fat_id::has_bio_parent(person_id val) const noexcept {
		return container.parentage_has_bio_parent(id, val);
	}
	DCON_RELEASE_INLINE void parentage_fat_id::set_bio_parent(int32_t i, person_id val) const noexcept {
		container.parentage_set_bio_parent(id, i, val);
	}
	DCON_RELEASE_INLINE bool parentage_fat_id::try_set_bio_parent(int32_t i, person_id val) const noexcept {
		return container.parentage_try_set_bio_parent(id, i, val);
	}
	DCON_RELEASE_INLINE void parentage_fat_id::replace_bio_parent(person_id newval, person_id oldval) const noexcept {
		container.parentage_replace_bio_parent(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool parentage_fat_id::try_replace_bio_parent(person_id newval, person_id oldval) const noexcept {
		return container.parentage_try_replace_bio_parent(id, newval, oldval);
	}
	DCON_RELEASE_INLINE bool parentage_fat_id::is_valid() const noexcept {
		return container.parentage_is_valid(id);
	}
	
	DCON_RELEASE_INLINE person_const_fat_id parentage_const_fat_id::get_child() const noexcept {
		return person_const_fat_id(container, container.parentage_get_child(id));
	}
	DCON_RELEASE_INLINE person_const_fat_id parentage_const_fat_id::get_bio_parent(int32_t i) const noexcept {
		return person_const_fat_id(container, container.parentage_get_bio_parent(id, i));
	}
	DCON_RELEASE_INLINE bool parentage_const_fat_id::has_bio_parent(person_id val) const noexcept {
		return container.parentage_has_bio_parent(id, val);
	}
	DCON_RELEASE_INLINE bool parentage_const_fat_id::is_valid() const noexcept {
		return container.parentage_is_valid(id);
	}
	

	namespace internal {
		class query_q_all_owner_ages_instance;
		class query_q_all_owner_ages_const_instance;
		class query_q_all_owner_ages_iterator {
			private:
			data_container& m_container;
			query_q_all_owner_ages_instance& m_parameters;
			car_id m_tableindex0;
			car_ownership_id m_tableindex1;
			person_id m_tableindex2;
			public:
			query_q_all_owner_ages_iterator(data_container& c, query_q_all_owner_ages_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.car_size() > 0) {
					internal_init(car_id(car_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_q_all_owner_ages_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_q_all_owner_ages_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(car_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(car_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_person_age() const -> decltype(m_container.person_get_age(person_id()));
			void set_person_age(int32_t v) const;
			person_fat_id get_person_id() const noexcept;
			bool has_car() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_person() const noexcept;
			
		};
		class query_q_all_owner_ages_const_iterator {
			private:
			data_container const& m_container;
			query_q_all_owner_ages_const_instance& m_parameters;
			car_id m_tableindex0;
			car_ownership_id m_tableindex1;
			person_id m_tableindex2;
			public:
			query_q_all_owner_ages_const_iterator(data_container const& c, query_q_all_owner_ages_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.car_size() > 0) {
					internal_init(car_id(car_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_q_all_owner_ages_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_q_all_owner_ages_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(car_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(car_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_person_age() const -> decltype(m_container.person_get_age(person_id()));
			person_const_fat_id get_person_id() const noexcept;
			bool has_car() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_person() const noexcept;
			
		};
		
		query_q_all_owner_ages_iterator query_q_all_owner_ages_instance::begin() {
			return query_q_all_owner_ages_iterator(container, *this);
		}
		query_q_all_owner_ages_const_iterator query_q_all_owner_ages_const_instance::begin() {
			return query_q_all_owner_ages_const_iterator(container, *this);
		}
		class query_rev_car_from_owner_instance;
		class query_rev_car_from_owner_const_instance;
		class query_rev_car_from_owner_iterator {
			private:
			data_container& m_container;
			query_rev_car_from_owner_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_rev_car_from_owner_iterator(data_container& c, query_rev_car_from_owner_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_rev_car_from_owner_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_rev_car_from_owner_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			void set_rv(float v) const;
			car_fat_id get_car_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		class query_rev_car_from_owner_const_iterator {
			private:
			data_container const& m_container;
			query_rev_car_from_owner_const_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_rev_car_from_owner_const_iterator(data_container const& c, query_rev_car_from_owner_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_rev_car_from_owner_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_rev_car_from_owner_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			car_const_fat_id get_car_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		
		query_rev_car_from_owner_iterator query_rev_car_from_owner_instance::begin() {
			return query_rev_car_from_owner_iterator(container, *this);
		}
		query_rev_car_from_owner_const_iterator query_rev_car_from_owner_const_instance::begin() {
			return query_rev_car_from_owner_const_iterator(container, *this);
		}
		class query_param_car_from_owner_instance;
		class query_param_car_from_owner_const_instance;
		class query_param_car_from_owner_iterator {
			private:
			data_container& m_container;
			query_param_car_from_owner_instance& m_parameters;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_param_car_from_owner_iterator(data_container& c, query_param_car_from_owner_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_param_car_from_owner_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_param_car_from_owner_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			void set_rv(float v) const;
			car_fat_id get_car_id() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		class query_param_car_from_owner_const_iterator {
			private:
			data_container const& m_container;
			query_param_car_from_owner_const_instance& m_parameters;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_param_car_from_owner_const_iterator(data_container const& c, query_param_car_from_owner_const_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_param_car_from_owner_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_param_car_from_owner_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			car_const_fat_id get_car_id() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		
		query_param_car_from_owner_iterator query_param_car_from_owner_instance::begin() {
			return query_param_car_from_owner_iterator(container, *this);
		}
		query_param_car_from_owner_const_iterator query_param_car_from_owner_const_instance::begin() {
			return query_param_car_from_owner_const_iterator(container, *this);
		}
		class query_q_all_owner_ages_plus_instance;
		class query_q_all_owner_ages_plus_const_instance;
		class query_q_all_owner_ages_plus_iterator {
			private:
			data_container& m_container;
			query_q_all_owner_ages_plus_instance& m_parameters;
			car_id m_tableindex0;
			car_ownership_id m_tableindex1;
			person_id m_tableindex2;
			public:
			query_q_all_owner_ages_plus_iterator(data_container& c, query_q_all_owner_ages_plus_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.car_size() > 0) {
					internal_init(car_id(car_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_q_all_owner_ages_plus_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_q_all_owner_ages_plus_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(car_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(car_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_person_age() const -> decltype(m_container.person_get_age(person_id()));
			void set_person_age(int32_t v) const;
			person_fat_id get_person_id() const noexcept;
			bool has_car() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_person() const noexcept;
			
		};
		class query_q_all_owner_ages_plus_const_iterator {
			private:
			data_container const& m_container;
			query_q_all_owner_ages_plus_const_instance& m_parameters;
			car_id m_tableindex0;
			car_ownership_id m_tableindex1;
			person_id m_tableindex2;
			public:
			query_q_all_owner_ages_plus_const_iterator(data_container const& c, query_q_all_owner_ages_plus_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.car_size() > 0) {
					internal_init(car_id(car_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_q_all_owner_ages_plus_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_q_all_owner_ages_plus_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(car_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(car_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_person_age() const -> decltype(m_container.person_get_age(person_id()));
			person_const_fat_id get_person_id() const noexcept;
			bool has_car() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_person() const noexcept;
			
		};
		
		query_q_all_owner_ages_plus_iterator query_q_all_owner_ages_plus_instance::begin() {
			return query_q_all_owner_ages_plus_iterator(container, *this);
		}
		query_q_all_owner_ages_plus_const_iterator query_q_all_owner_ages_plus_const_instance::begin() {
			return query_q_all_owner_ages_plus_const_iterator(container, *this);
		}
		class query_rev_car_from_owner_plus_instance;
		class query_rev_car_from_owner_plus_const_instance;
		class query_rev_car_from_owner_plus_iterator {
			private:
			data_container& m_container;
			query_rev_car_from_owner_plus_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_rev_car_from_owner_plus_iterator(data_container& c, query_rev_car_from_owner_plus_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_rev_car_from_owner_plus_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_rev_car_from_owner_plus_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			void set_rv(float v) const;
			car_fat_id get_car_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		class query_rev_car_from_owner_plus_const_iterator {
			private:
			data_container const& m_container;
			query_rev_car_from_owner_plus_const_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_rev_car_from_owner_plus_const_iterator(data_container const& c, query_rev_car_from_owner_plus_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_rev_car_from_owner_plus_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_rev_car_from_owner_plus_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			auto get_rv() const -> decltype(m_container.car_get_resale_value(car_id()));
			car_const_fat_id get_car_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		
		query_rev_car_from_owner_plus_iterator query_rev_car_from_owner_plus_instance::begin() {
			return query_rev_car_from_owner_plus_iterator(container, *this);
		}
		query_rev_car_from_owner_plus_const_iterator query_rev_car_from_owner_plus_const_instance::begin() {
			return query_rev_car_from_owner_plus_const_iterator(container, *this);
		}
		class query_grandparents_instance;
		class query_grandparents_const_instance;
		class query_grandparents_iterator {
			private:
			data_container& m_container;
			query_grandparents_instance& m_parameters;
			parentage_id m_tableindex1;
			person_id m_tableindex2;
			int32_t m_index_into_m_tableindex2 = 0;
			parentage_id m_tableindex3;
			person_id m_tableindex4;
			int32_t m_index_into_m_tableindex4 = 0;
			public:
			query_grandparents_iterator(data_container& c, query_grandparents_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_grandparents_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_grandparents_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_fat_id get_grandparent() const noexcept;
			person_fat_id get_parent() const noexcept;
			bool has_parentage() const noexcept;
			bool has_par() const noexcept;
			bool has_gp() const noexcept;
			
		};
		class query_grandparents_const_iterator {
			private:
			data_container const& m_container;
			query_grandparents_const_instance& m_parameters;
			parentage_id m_tableindex1;
			person_id m_tableindex2;
			int32_t m_index_into_m_tableindex2 = 0;
			parentage_id m_tableindex3;
			person_id m_tableindex4;
			int32_t m_index_into_m_tableindex4 = 0;
			public:
			query_grandparents_const_iterator(data_container const& c, query_grandparents_const_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_grandparents_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_grandparents_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_const_fat_id get_grandparent() const noexcept;
			person_const_fat_id get_parent() const noexcept;
			bool has_parentage() const noexcept;
			bool has_par() const noexcept;
			bool has_gp() const noexcept;
			
		};
		
		query_grandparents_iterator query_grandparents_instance::begin() {
			return query_grandparents_iterator(container, *this);
		}
		query_grandparents_const_iterator query_grandparents_const_instance::begin() {
			return query_grandparents_const_iterator(container, *this);
		}
		class query_grandchildren_instance;
		class query_grandchildren_const_instance;
		class query_grandchildren_iterator {
			private:
			data_container& m_container;
			query_grandchildren_instance& m_parameters;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_grandchildren_iterator(data_container& c, query_grandchildren_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_grandchildren_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_grandchildren_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_fat_id get_grandchild() const noexcept;
			person_fat_id get_child() const noexcept;
			bool has_parentage() const noexcept;
			bool has_ch() const noexcept;
			bool has_gch() const noexcept;
			
		};
		class query_grandchildren_const_iterator {
			private:
			data_container const& m_container;
			query_grandchildren_const_instance& m_parameters;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_grandchildren_const_iterator(data_container const& c, query_grandchildren_const_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_grandchildren_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_grandchildren_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_const_fat_id get_grandchild() const noexcept;
			person_const_fat_id get_child() const noexcept;
			bool has_parentage() const noexcept;
			bool has_ch() const noexcept;
			bool has_gch() const noexcept;
			
		};
		
		query_grandchildren_iterator query_grandchildren_instance::begin() {
			return query_grandchildren_iterator(container, *this);
		}
		query_grandchildren_const_iterator query_grandchildren_const_instance::begin() {
			return query_grandchildren_const_iterator(container, *this);
		}
		class query_group_grandchildren_instance;
		class query_group_grandchildren_const_instance;
		class query_group_grandchildren_iterator {
			private:
			data_container& m_container;
			query_group_grandchildren_instance& m_parameters;
			int32_t m_count_gc;
			int32_t m_max_age;
			person_id m_gch_wealth;
			person_id m_tableindex0;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_group_grandchildren_iterator(data_container& c, query_group_grandchildren_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_group_grandchildren_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_group_grandchildren_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool as_first);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool force, bool& hit_group);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_fat_id get_grandparent() const noexcept;
			auto get_gch_wealth() const -> decltype(m_container.person_get_wealth(person_id()));
			void set_gch_wealth(float v) const;
			int32_t get_count_gc() const noexcept;
			int32_t get_max_age() const noexcept;
			bool has_base() const noexcept;
			bool has_parentage() const noexcept;
			bool has_ch() const noexcept;
			bool has_gch() const noexcept;
			
		};
		class query_group_grandchildren_const_iterator {
			private:
			data_container const& m_container;
			query_group_grandchildren_const_instance& m_parameters;
			int32_t m_count_gc;
			int32_t m_max_age;
			person_id m_gch_wealth;
			person_id m_tableindex0;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_group_grandchildren_const_iterator(data_container const& c, query_group_grandchildren_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_group_grandchildren_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_group_grandchildren_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool as_first);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool force, bool& hit_group);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_const_fat_id get_grandparent() const noexcept;
			auto get_gch_wealth() const -> decltype(m_container.person_get_wealth(person_id()));
			int32_t get_count_gc() const noexcept;
			int32_t get_max_age() const noexcept;
			bool has_base() const noexcept;
			bool has_parentage() const noexcept;
			bool has_ch() const noexcept;
			bool has_gch() const noexcept;
			
		};
		
		query_group_grandchildren_iterator query_group_grandchildren_instance::begin() {
			return query_group_grandchildren_iterator(container, *this);
		}
		query_group_grandchildren_const_iterator query_group_grandchildren_const_instance::begin() {
			return query_group_grandchildren_const_iterator(container, *this);
		}
		class query_sum_car_value_instance;
		class query_sum_car_value_const_instance;
		class query_sum_car_value_iterator {
			private:
			data_container& m_container;
			query_sum_car_value_instance& m_parameters;
			float m_rv_sum;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_sum_car_value_iterator(data_container& c, query_sum_car_value_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_sum_car_value_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_sum_car_value_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool as_first);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool force, bool& hit_group);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			float get_rv_sum() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		class query_sum_car_value_const_iterator {
			private:
			data_container const& m_container;
			query_sum_car_value_const_instance& m_parameters;
			float m_rv_sum;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			public:
			query_sum_car_value_const_iterator(data_container const& c, query_sum_car_value_const_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.from_person);
			}
			auto operator++() -> query_sum_car_value_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_sum_car_value_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool as_first);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool force, bool& hit_group);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			float get_rv_sum() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car() const noexcept;
			
		};
		
		query_sum_car_value_iterator query_sum_car_value_instance::begin() {
			return query_sum_car_value_iterator(container, *this);
		}
		query_sum_car_value_const_iterator query_sum_car_value_const_instance::begin() {
			return query_sum_car_value_const_iterator(container, *this);
		}
		class query_pairs_of_cars_instance;
		class query_pairs_of_cars_const_instance;
		class query_pairs_of_cars_iterator {
			private:
			data_container& m_container;
			query_pairs_of_cars_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			car_ownership_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			car_id m_tableindex4;
			public:
			query_pairs_of_cars_iterator(data_container& c, query_pairs_of_cars_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_pairs_of_cars_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_pairs_of_cars_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(car_ownership_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(car_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_fat_id get_person_id() const noexcept;
			car_fat_id get_car_a_id() const noexcept;
			car_fat_id get_car_b_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car_a() const noexcept;
			bool has_car_b() const noexcept;
			
		};
		class query_pairs_of_cars_const_iterator {
			private:
			data_container const& m_container;
			query_pairs_of_cars_const_instance& m_parameters;
			person_id m_tableindex0;
			car_ownership_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			car_id m_tableindex2;
			car_ownership_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			car_id m_tableindex4;
			public:
			query_pairs_of_cars_const_iterator(data_container const& c, query_pairs_of_cars_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.person_size() > 0) {
					internal_init(person_id(person_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_pairs_of_cars_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_pairs_of_cars_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(car_ownership_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(car_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(car_ownership_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(car_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_const_fat_id get_person_id() const noexcept;
			car_const_fat_id get_car_a_id() const noexcept;
			car_const_fat_id get_car_b_id() const noexcept;
			bool has_person() const noexcept;
			bool has_car_ownership() const noexcept;
			bool has_car_a() const noexcept;
			bool has_car_b() const noexcept;
			
		};
		
		query_pairs_of_cars_iterator query_pairs_of_cars_instance::begin() {
			return query_pairs_of_cars_iterator(container, *this);
		}
		query_pairs_of_cars_const_iterator query_pairs_of_cars_const_instance::begin() {
			return query_pairs_of_cars_const_iterator(container, *this);
		}
		class query_siblings_instance;
		class query_siblings_const_instance;
		class query_siblings_iterator {
			private:
			data_container& m_container;
			query_siblings_instance& m_parameters;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_siblings_iterator(data_container& c, query_siblings_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.person_param);
			}
			auto operator++() -> query_siblings_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_siblings_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_fat_id get_base_id() const noexcept;
			person_fat_id get_sibling_a_id() const noexcept;
			person_fat_id get_sibling_b_id() const noexcept;
			bool has_parentage() const noexcept;
			bool has_sibling_a() const noexcept;
			bool has_sibling_b() const noexcept;
			
		};
		class query_siblings_const_iterator {
			private:
			data_container const& m_container;
			query_siblings_const_instance& m_parameters;
			parentage_id m_tableindex1;
			int32_t m_index_into_m_tableindex1 = 0;
			int32_t m_size_of_m_tableindex1 = 0;
			person_id m_tableindex2;
			parentage_id m_tableindex3;
			int32_t m_index_into_m_tableindex3 = 0;
			int32_t m_size_of_m_tableindex3 = 0;
			person_id m_tableindex4;
			public:
			query_siblings_const_iterator(data_container const& c, query_siblings_const_instance& p) : m_container(c), m_parameters(p) {
				internal_init(m_parameters.person_param);
			}
			auto operator++() -> query_siblings_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_siblings_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(person_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(person_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(parentage_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(person_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			void internal_reset_v3();
			bool internal_set_v3(parentage_id v);
			bool internal_increment_v3(bool force, bool& hit_group);
			void internal_reset_v4();
			bool internal_set_v4(person_id v);
			bool internal_increment_v4(bool force, bool& hit_group);
			public:
			person_const_fat_id get_base_id() const noexcept;
			person_const_fat_id get_sibling_a_id() const noexcept;
			person_const_fat_id get_sibling_b_id() const noexcept;
			bool has_parentage() const noexcept;
			bool has_sibling_a() const noexcept;
			bool has_sibling_b() const noexcept;
			
		};
		
		query_siblings_iterator query_siblings_instance::begin() {
			return query_siblings_iterator(container, *this);
		}
		query_siblings_const_iterator query_siblings_const_instance::begin() {
			return query_siblings_const_iterator(container, *this);
		}
	};


	auto internal::query_q_all_owner_ages_const_iterator::operator++() -> query_q_all_owner_ages_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_q_all_owner_ages_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_q_all_owner_ages_const_iterator::operator*() -> query_q_all_owner_ages_const_iterator const& {
		return *this;
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_set_aggregates() {
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_update_aggregates() {
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_init(car_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_reset_v0() {
		m_tableindex0 = car_id();
		internal_reset_v1();
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_set_v0(car_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.car_get_car_ownership_as_owned_car(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.car_size(); ++i) {
			if(internal_set_v0( car_id(car_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = car_id( );
		return false;
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_reset_v1() {
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owner(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_q_all_owner_ages_const_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_q_all_owner_ages_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_q_all_owner_ages_const_iterator::get_person_age() const -> decltype(m_container.person_get_age(person_id())) {
		return m_container.person_get_age( m_tableindex2 );
	}
	person_const_fat_id internal::query_q_all_owner_ages_const_iterator::get_person_id() const noexcept {
		return person_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_q_all_owner_ages_const_iterator::has_car() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_q_all_owner_ages_const_iterator::has_person() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_q_all_owner_ages_iterator::operator++() -> query_q_all_owner_ages_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_q_all_owner_ages_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_q_all_owner_ages_iterator::operator*() -> query_q_all_owner_ages_iterator const& {
		return *this;
	}
	void internal::query_q_all_owner_ages_iterator::internal_reset_aggregates() {
	}
	void internal::query_q_all_owner_ages_iterator::internal_set_aggregates() {
	}
	void internal::query_q_all_owner_ages_iterator::internal_update_aggregates() {
	}
	void internal::query_q_all_owner_ages_iterator::internal_init(car_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_q_all_owner_ages_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_q_all_owner_ages_iterator::internal_reset_v0() {
		m_tableindex0 = car_id();
		internal_reset_v1();
	}
	bool internal::query_q_all_owner_ages_iterator::internal_set_v0(car_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.car_get_car_ownership_as_owned_car(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.car_size(); ++i) {
			if(internal_set_v0( car_id(car_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = car_id( );
		return false;
	}
	void internal::query_q_all_owner_ages_iterator::internal_reset_v1() {
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_q_all_owner_ages_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owner(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_q_all_owner_ages_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_q_all_owner_ages_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_q_all_owner_ages_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_q_all_owner_ages_iterator::get_person_age() const -> decltype(m_container.person_get_age(person_id())) {
		return m_container.person_get_age( m_tableindex2 );
	}
	void internal::query_q_all_owner_ages_iterator::set_person_age(int32_t v) const {
		m_container.person_set_age( m_tableindex2, v );
	}
	person_fat_id internal::query_q_all_owner_ages_iterator::get_person_id() const noexcept {
		return person_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_q_all_owner_ages_iterator::has_car() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_q_all_owner_ages_iterator::has_person() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_rev_car_from_owner_const_iterator::operator++() -> query_rev_car_from_owner_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_rev_car_from_owner_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_rev_car_from_owner_const_iterator::operator*() -> query_rev_car_from_owner_const_iterator const& {
		return *this;
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_set_aggregates() {
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_update_aggregates() {
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_rev_car_from_owner_const_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_rev_car_from_owner_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_rev_car_from_owner_const_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	car_const_fat_id internal::query_rev_car_from_owner_const_iterator::get_car_id() const noexcept {
		return car_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_rev_car_from_owner_const_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_rev_car_from_owner_const_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_rev_car_from_owner_iterator::operator++() -> query_rev_car_from_owner_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_rev_car_from_owner_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_rev_car_from_owner_iterator::operator*() -> query_rev_car_from_owner_iterator const& {
		return *this;
	}
	void internal::query_rev_car_from_owner_iterator::internal_reset_aggregates() {
	}
	void internal::query_rev_car_from_owner_iterator::internal_set_aggregates() {
	}
	void internal::query_rev_car_from_owner_iterator::internal_update_aggregates() {
	}
	void internal::query_rev_car_from_owner_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_rev_car_from_owner_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_rev_car_from_owner_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_rev_car_from_owner_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_rev_car_from_owner_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_rev_car_from_owner_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_rev_car_from_owner_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_rev_car_from_owner_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_rev_car_from_owner_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_rev_car_from_owner_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	void internal::query_rev_car_from_owner_iterator::set_rv(float v) const {
		m_container.car_set_resale_value( m_tableindex2, v );
	}
	car_fat_id internal::query_rev_car_from_owner_iterator::get_car_id() const noexcept {
		return car_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_rev_car_from_owner_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_rev_car_from_owner_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_param_car_from_owner_const_iterator::operator++() -> query_param_car_from_owner_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_param_car_from_owner_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_param_car_from_owner_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_param_car_from_owner_const_iterator::operator*() -> query_param_car_from_owner_const_iterator const& {
		return *this;
	}
	void internal::query_param_car_from_owner_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_param_car_from_owner_const_iterator::internal_set_aggregates() {
	}
	void internal::query_param_car_from_owner_const_iterator::internal_update_aggregates() {
	}
	void internal::query_param_car_from_owner_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_param_car_from_owner_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_param_car_from_owner_const_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_param_car_from_owner_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_param_car_from_owner_const_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_param_car_from_owner_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_param_car_from_owner_const_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	car_const_fat_id internal::query_param_car_from_owner_const_iterator::get_car_id() const noexcept {
		return car_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_param_car_from_owner_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_param_car_from_owner_const_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_param_car_from_owner_iterator::operator++() -> query_param_car_from_owner_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_param_car_from_owner_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_param_car_from_owner_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_param_car_from_owner_iterator::operator*() -> query_param_car_from_owner_iterator const& {
		return *this;
	}
	void internal::query_param_car_from_owner_iterator::internal_reset_aggregates() {
	}
	void internal::query_param_car_from_owner_iterator::internal_set_aggregates() {
	}
	void internal::query_param_car_from_owner_iterator::internal_update_aggregates() {
	}
	void internal::query_param_car_from_owner_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_param_car_from_owner_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_param_car_from_owner_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_param_car_from_owner_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_param_car_from_owner_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_param_car_from_owner_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_param_car_from_owner_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_param_car_from_owner_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_param_car_from_owner_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_param_car_from_owner_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_param_car_from_owner_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_param_car_from_owner_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	void internal::query_param_car_from_owner_iterator::set_rv(float v) const {
		m_container.car_set_resale_value( m_tableindex2, v );
	}
	car_fat_id internal::query_param_car_from_owner_iterator::get_car_id() const noexcept {
		return car_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_param_car_from_owner_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_param_car_from_owner_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_q_all_owner_ages_plus_const_iterator::operator++() -> query_q_all_owner_ages_plus_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_q_all_owner_ages_plus_const_iterator::operator*() -> query_q_all_owner_ages_plus_const_iterator const& {
		return *this;
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_set_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_update_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_init(car_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_reset_v0() {
		m_tableindex0 = car_id();
		internal_reset_v1();
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_set_v0(car_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.car_get_car_ownership_as_owned_car(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.car_size(); ++i) {
			if(internal_set_v0( car_id(car_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = car_id( );
		return false;
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_reset_v1() {
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			internal_reset_v1();
			return true;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owner(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_q_all_owner_ages_plus_const_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			internal_reset_v2();
			return true;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_q_all_owner_ages_plus_const_iterator::get_person_age() const -> decltype(m_container.person_get_age(person_id())) {
		return m_container.person_get_age( m_tableindex2 );
	}
	person_const_fat_id internal::query_q_all_owner_ages_plus_const_iterator::get_person_id() const noexcept {
		return person_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::has_car() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_q_all_owner_ages_plus_const_iterator::has_person() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_q_all_owner_ages_plus_iterator::operator++() -> query_q_all_owner_ages_plus_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_q_all_owner_ages_plus_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_plus_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_q_all_owner_ages_plus_iterator::operator*() -> query_q_all_owner_ages_plus_iterator const& {
		return *this;
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_reset_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_set_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_update_aggregates() {
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_init(car_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_reset_v0() {
		m_tableindex0 = car_id();
		internal_reset_v1();
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_set_v0(car_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.car_get_car_ownership_as_owned_car(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.car_size(); ++i) {
			if(internal_set_v0( car_id(car_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = car_id( );
		return false;
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_reset_v1() {
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			internal_reset_v1();
			return true;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owner(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_q_all_owner_ages_plus_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			internal_reset_v2();
			return true;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_q_all_owner_ages_plus_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_q_all_owner_ages_plus_iterator::get_person_age() const -> decltype(m_container.person_get_age(person_id())) {
		return m_container.person_get_age( m_tableindex2 );
	}
	void internal::query_q_all_owner_ages_plus_iterator::set_person_age(int32_t v) const {
		m_container.person_set_age( m_tableindex2, v );
	}
	person_fat_id internal::query_q_all_owner_ages_plus_iterator::get_person_id() const noexcept {
		return person_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_q_all_owner_ages_plus_iterator::has_car() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_q_all_owner_ages_plus_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_q_all_owner_ages_plus_iterator::has_person() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_rev_car_from_owner_plus_const_iterator::operator++() -> query_rev_car_from_owner_plus_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_rev_car_from_owner_plus_const_iterator::operator*() -> query_rev_car_from_owner_plus_const_iterator const& {
		return *this;
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_set_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_update_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			internal_reset_v1();
			return true;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_rev_car_from_owner_plus_const_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_rev_car_from_owner_plus_const_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	car_const_fat_id internal::query_rev_car_from_owner_plus_const_iterator::get_car_id() const noexcept {
		return car_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_rev_car_from_owner_plus_const_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_rev_car_from_owner_plus_iterator::operator++() -> query_rev_car_from_owner_plus_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_rev_car_from_owner_plus_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_plus_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_rev_car_from_owner_plus_iterator::operator*() -> query_rev_car_from_owner_plus_iterator const& {
		return *this;
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_reset_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_set_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_update_aggregates() {
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			internal_reset_v1();
			return true;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_rev_car_from_owner_plus_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_rev_car_from_owner_plus_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	auto internal::query_rev_car_from_owner_plus_iterator::get_rv() const -> decltype(m_container.car_get_resale_value(car_id())) {
		return m_container.car_get_resale_value( m_tableindex2 );
	}
	void internal::query_rev_car_from_owner_plus_iterator::set_rv(float v) const {
		m_container.car_set_resale_value( m_tableindex2, v );
	}
	car_fat_id internal::query_rev_car_from_owner_plus_iterator::get_car_id() const noexcept {
		return car_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_rev_car_from_owner_plus_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_rev_car_from_owner_plus_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_rev_car_from_owner_plus_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_grandparents_const_iterator::operator++() -> query_grandparents_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_grandparents_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_grandparents_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_grandparents_const_iterator::operator*() -> query_grandparents_const_iterator const& {
		return *this;
	}
	void internal::query_grandparents_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_grandparents_const_iterator::internal_set_aggregates() {
	}
	void internal::query_grandparents_const_iterator::internal_update_aggregates() {
	}
	void internal::query_grandparents_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_grandparents_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v4(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_grandparents_const_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_grandparents_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		return internal_set_v1(m_container.person_get_parentage_as_child(m_parameters.from_person));
		}() && 
		true;
	}
	bool internal::query_grandparents_const_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_grandparents_const_iterator::internal_reset_v1() {
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_grandparents_const_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		m_index_into_m_tableindex2 = 0;
		for( ; m_index_into_m_tableindex2 < 2; ++m_index_into_m_tableindex2) {
			if(internal_set_v2( m_container.parentage_get_bio_parent(m_tableindex1, m_index_into_m_tableindex2) ) ) {
				return true;
			}
		}
		return false;
		}() && 
		true;
	}
	bool internal::query_grandparents_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_grandparents_const_iterator::internal_reset_v2() {
		m_index_into_m_tableindex2 = 0;
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_grandparents_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		return internal_set_v3(m_container.person_get_parentage_as_child(m_tableindex2));
		}() && 
		true;
	}
	bool internal::query_grandparents_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		if(m_index_into_m_tableindex2 + 1 < 2) {
			++m_index_into_m_tableindex2;
			return internal_set_v2( m_container.parentage_get_bio_parent(m_tableindex1, m_index_into_m_tableindex2) );
		} else {
			m_tableindex2 = person_id();
			return internal_increment_v1(force, hit_group);
		}
	}
	void internal::query_grandparents_const_iterator::internal_reset_v3() {
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_grandparents_const_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		m_index_into_m_tableindex4 = 0;
		for( ; m_index_into_m_tableindex4 < 2; ++m_index_into_m_tableindex4) {
			if(internal_set_v4( m_container.parentage_get_bio_parent(m_tableindex3, m_index_into_m_tableindex4) ) ) {
				return true;
			}
		}
		return false;
		}() && 
		true;
	}
	bool internal::query_grandparents_const_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		return internal_increment_v2(force, hit_group);
	}
	void internal::query_grandparents_const_iterator::internal_reset_v4() {
		m_index_into_m_tableindex4 = 0;
		m_tableindex4 = person_id();
	}
	bool internal::query_grandparents_const_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_grandparents_const_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		if(m_index_into_m_tableindex4 + 1 < 2) {
			++m_index_into_m_tableindex4;
			return internal_set_v4( m_container.parentage_get_bio_parent(m_tableindex3, m_index_into_m_tableindex4) );
		} else {
			m_tableindex4 = person_id();
			return internal_increment_v3(force, hit_group);
		}
	}
	person_const_fat_id internal::query_grandparents_const_iterator::get_grandparent() const noexcept {
		return person_const_fat_id(m_container, m_tableindex4 );
	}
	person_const_fat_id internal::query_grandparents_const_iterator::get_parent() const noexcept {
		return person_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_grandparents_const_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_grandparents_const_iterator::has_par() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_grandparents_const_iterator::has_gp() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_grandparents_iterator::operator++() -> query_grandparents_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_grandparents_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_grandparents_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_grandparents_iterator::operator*() -> query_grandparents_iterator const& {
		return *this;
	}
	void internal::query_grandparents_iterator::internal_reset_aggregates() {
	}
	void internal::query_grandparents_iterator::internal_set_aggregates() {
	}
	void internal::query_grandparents_iterator::internal_update_aggregates() {
	}
	void internal::query_grandparents_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_grandparents_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v4(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_grandparents_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_grandparents_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		return internal_set_v1(m_container.person_get_parentage_as_child(m_parameters.from_person));
		}() && 
		true;
	}
	bool internal::query_grandparents_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_grandparents_iterator::internal_reset_v1() {
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_grandparents_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		m_index_into_m_tableindex2 = 0;
		for( ; m_index_into_m_tableindex2 < 2; ++m_index_into_m_tableindex2) {
			if(internal_set_v2( m_container.parentage_get_bio_parent(m_tableindex1, m_index_into_m_tableindex2) ) ) {
				return true;
			}
		}
		return false;
		}() && 
		true;
	}
	bool internal::query_grandparents_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_grandparents_iterator::internal_reset_v2() {
		m_index_into_m_tableindex2 = 0;
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_grandparents_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		return internal_set_v3(m_container.person_get_parentage_as_child(m_tableindex2));
		}() && 
		true;
	}
	bool internal::query_grandparents_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		if(m_index_into_m_tableindex2 + 1 < 2) {
			++m_index_into_m_tableindex2;
			return internal_set_v2( m_container.parentage_get_bio_parent(m_tableindex1, m_index_into_m_tableindex2) );
		} else {
			m_tableindex2 = person_id();
			return internal_increment_v1(force, hit_group);
		}
	}
	void internal::query_grandparents_iterator::internal_reset_v3() {
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_grandparents_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		m_index_into_m_tableindex4 = 0;
		for( ; m_index_into_m_tableindex4 < 2; ++m_index_into_m_tableindex4) {
			if(internal_set_v4( m_container.parentage_get_bio_parent(m_tableindex3, m_index_into_m_tableindex4) ) ) {
				return true;
			}
		}
		return false;
		}() && 
		true;
	}
	bool internal::query_grandparents_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		return internal_increment_v2(force, hit_group);
	}
	void internal::query_grandparents_iterator::internal_reset_v4() {
		m_index_into_m_tableindex4 = 0;
		m_tableindex4 = person_id();
	}
	bool internal::query_grandparents_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_grandparents_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		if(m_index_into_m_tableindex4 + 1 < 2) {
			++m_index_into_m_tableindex4;
			return internal_set_v4( m_container.parentage_get_bio_parent(m_tableindex3, m_index_into_m_tableindex4) );
		} else {
			m_tableindex4 = person_id();
			return internal_increment_v3(force, hit_group);
		}
	}
	person_fat_id internal::query_grandparents_iterator::get_grandparent() const noexcept {
		return person_fat_id(m_container, m_tableindex4 );
	}
	person_fat_id internal::query_grandparents_iterator::get_parent() const noexcept {
		return person_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_grandparents_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_grandparents_iterator::has_par() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_grandparents_iterator::has_gp() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_grandchildren_const_iterator::operator++() -> query_grandchildren_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_grandchildren_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_grandchildren_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_grandchildren_const_iterator::operator*() -> query_grandchildren_const_iterator const& {
		return *this;
	}
	void internal::query_grandchildren_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_grandchildren_const_iterator::internal_set_aggregates() {
	}
	void internal::query_grandchildren_const_iterator::internal_update_aggregates() {
	}
	void internal::query_grandchildren_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_grandchildren_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v4(false, hit_group)) {
			}
			if(bool(m_parameters.from_person)) {
				if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
					return;
				}
			}
		}
	}
	void internal::query_grandchildren_const_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_grandchildren_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_grandchildren_const_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_grandchildren_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_grandchildren_const_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_grandchildren_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_grandchildren_const_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_grandchildren_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_grandchildren_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_grandchildren_const_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_grandchildren_const_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_grandchildren_const_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_grandchildren_const_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_grandchildren_const_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_grandchildren_const_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_const_fat_id internal::query_grandchildren_const_iterator::get_grandchild() const noexcept {
		return person_const_fat_id(m_container, m_tableindex4 );
	}
	person_const_fat_id internal::query_grandchildren_const_iterator::get_child() const noexcept {
		return person_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_grandchildren_const_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_grandchildren_const_iterator::has_ch() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_grandchildren_const_iterator::has_gch() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_grandchildren_iterator::operator++() -> query_grandchildren_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_grandchildren_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_grandchildren_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_grandchildren_iterator::operator*() -> query_grandchildren_iterator const& {
		return *this;
	}
	void internal::query_grandchildren_iterator::internal_reset_aggregates() {
	}
	void internal::query_grandchildren_iterator::internal_set_aggregates() {
	}
	void internal::query_grandchildren_iterator::internal_update_aggregates() {
	}
	void internal::query_grandchildren_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_grandchildren_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.from_person)) {
			while(bool(m_parameters.from_person) && !internal_increment_v4(false, hit_group)) {
			}
			if(bool(m_parameters.from_person)) {
				if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
					return;
				}
			}
		}
	}
	void internal::query_grandchildren_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_grandchildren_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_grandchildren_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_grandchildren_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_grandchildren_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_grandchildren_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_grandchildren_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_grandchildren_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_grandchildren_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_grandchildren_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_grandchildren_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_grandchildren_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_grandchildren_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_grandchildren_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_grandchildren_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_fat_id internal::query_grandchildren_iterator::get_grandchild() const noexcept {
		return person_fat_id(m_container, m_tableindex4 );
	}
	person_fat_id internal::query_grandchildren_iterator::get_child() const noexcept {
		return person_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_grandchildren_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_grandchildren_iterator::has_ch() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_grandchildren_iterator::has_gch() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_group_grandchildren_const_iterator::operator++() -> query_group_grandchildren_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_group_grandchildren_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_group_grandchildren_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_group_grandchildren_const_iterator::operator*() -> query_group_grandchildren_const_iterator const& {
		return *this;
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_aggregates() {
		m_count_gc = int32_t{};
		m_max_age = int32_t{};
		m_gch_wealth = person_id{};
	}
	void internal::query_group_grandchildren_const_iterator::internal_set_aggregates() {
		m_count_gc = 1;
		m_max_age = m_container.person_get_age(m_tableindex4);
		m_gch_wealth = m_tableindex4;
	}
	void internal::query_group_grandchildren_const_iterator::internal_update_aggregates() {
		++m_count_gc;
		if(bool(m_tableindex4) && m_max_age < m_container.person_get_age(m_tableindex4) ) {
			m_gch_wealth = m_tableindex4;
			m_max_age = m_container.person_get_age(m_tableindex4);
		}
	}
	void internal::query_group_grandchildren_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
				internal_set_aggregates();
				internal_increment_to_result(false);
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_group_grandchildren_const_iterator::internal_increment_to_result(bool as_first) {
		if(as_first) internal_reset_aggregates();
		bool first_time = as_first;
		while(bool(m_tableindex0)) {
			bool hit_group = false;
			while(bool(m_tableindex0) && !internal_increment_v4(first_time, hit_group)) {
			}
			if(!hit_group) {
				if(bool(m_tableindex0)) {
					if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
						if(first_time) {
							first_time = false;
							internal_set_aggregates();
						} else {
							internal_update_aggregates();
						}
					}
				}
			} else {
				return;
			}
		}
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_group_grandchildren_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_const_iterator::internal_increment_v0(bool force, bool& hit_group) {
		if(!force) {
			hit_group = true;
			return true;
		}
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_group_grandchildren_const_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_group_grandchildren_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_group_grandchildren_const_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_const_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_group_grandchildren_const_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_group_grandchildren_const_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_group_grandchildren_const_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_const_fat_id internal::query_group_grandchildren_const_iterator::get_grandparent() const noexcept {
		return person_const_fat_id(m_container, m_tableindex0 );
	}
	auto internal::query_group_grandchildren_const_iterator::get_gch_wealth() const -> decltype(m_container.person_get_wealth(person_id())) {
		return m_container.person_get_wealth( m_gch_wealth );
	}
	int32_t internal::query_group_grandchildren_const_iterator::get_count_gc() const noexcept {
		return m_count_gc;
	}
	int32_t internal::query_group_grandchildren_const_iterator::get_max_age() const noexcept {
		return m_max_age;
	}
	bool internal::query_group_grandchildren_const_iterator::has_base() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_group_grandchildren_const_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_group_grandchildren_const_iterator::has_ch() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_group_grandchildren_const_iterator::has_gch() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_group_grandchildren_iterator::operator++() -> query_group_grandchildren_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_group_grandchildren_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_group_grandchildren_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_group_grandchildren_iterator::operator*() -> query_group_grandchildren_iterator const& {
		return *this;
	}
	void internal::query_group_grandchildren_iterator::internal_reset_aggregates() {
		m_count_gc = int32_t{};
		m_max_age = int32_t{};
		m_gch_wealth = person_id{};
	}
	void internal::query_group_grandchildren_iterator::internal_set_aggregates() {
		m_count_gc = 1;
		m_max_age = m_container.person_get_age(m_tableindex4);
		m_gch_wealth = m_tableindex4;
	}
	void internal::query_group_grandchildren_iterator::internal_update_aggregates() {
		++m_count_gc;
		if(bool(m_tableindex4) && m_max_age < m_container.person_get_age(m_tableindex4) ) {
			m_gch_wealth = m_tableindex4;
			m_max_age = m_container.person_get_age(m_tableindex4);
		}
	}
	void internal::query_group_grandchildren_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
				internal_set_aggregates();
				internal_increment_to_result(false);
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_group_grandchildren_iterator::internal_increment_to_result(bool as_first) {
		if(as_first) internal_reset_aggregates();
		bool first_time = as_first;
		while(bool(m_tableindex0)) {
			bool hit_group = false;
			while(bool(m_tableindex0) && !internal_increment_v4(first_time, hit_group)) {
			}
			if(!hit_group) {
				if(bool(m_tableindex0)) {
					if(m_container.person_get_age(m_tableindex4) < m_parameters.age_filter) {
						if(first_time) {
							first_time = false;
							internal_set_aggregates();
						} else {
							internal_update_aggregates();
						}
					}
				}
			} else {
				return;
			}
		}
	}
	void internal::query_group_grandchildren_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
	}
	bool internal::query_group_grandchildren_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_iterator::internal_increment_v0(bool force, bool& hit_group) {
		if(!force) {
			hit_group = true;
			return true;
		}
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_group_grandchildren_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_group_grandchildren_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_group_grandchildren_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
		internal_reset_v3();
	}
	bool internal::query_group_grandchildren_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_group_grandchildren_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_group_grandchildren_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_group_grandchildren_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_tableindex2);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_group_grandchildren_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_group_grandchildren_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_group_grandchildren_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_fat_id internal::query_group_grandchildren_iterator::get_grandparent() const noexcept {
		return person_fat_id(m_container, m_tableindex0 );
	}
	auto internal::query_group_grandchildren_iterator::get_gch_wealth() const -> decltype(m_container.person_get_wealth(person_id())) {
		return m_container.person_get_wealth( m_gch_wealth );
	}
	void internal::query_group_grandchildren_iterator::set_gch_wealth(float v) const {
		m_container.person_set_wealth( m_gch_wealth, v );
	}
	int32_t internal::query_group_grandchildren_iterator::get_count_gc() const noexcept {
		return m_count_gc;
	}
	int32_t internal::query_group_grandchildren_iterator::get_max_age() const noexcept {
		return m_max_age;
	}
	bool internal::query_group_grandchildren_iterator::has_base() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_group_grandchildren_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_group_grandchildren_iterator::has_ch() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_group_grandchildren_iterator::has_gch() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_sum_car_value_const_iterator::operator++() -> query_sum_car_value_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_sum_car_value_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_sum_car_value_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_sum_car_value_const_iterator::operator*() -> query_sum_car_value_const_iterator const& {
		return *this;
	}
	void internal::query_sum_car_value_const_iterator::internal_reset_aggregates() {
		m_rv_sum = float{};
	}
	void internal::query_sum_car_value_const_iterator::internal_set_aggregates() {
		m_rv_sum = m_container.car_get_resale_value(m_tableindex2);
	}
	void internal::query_sum_car_value_const_iterator::internal_update_aggregates() {
		m_rv_sum = sum(m_rv_sum, m_container.car_get_resale_value(m_tableindex2));
	}
	void internal::query_sum_car_value_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			internal_set_aggregates();
			internal_increment_to_result(false);
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_sum_car_value_const_iterator::internal_increment_to_result(bool as_first) {
		if(as_first) internal_reset_aggregates();
		bool first_time = as_first;
		while(bool(m_parameters.from_person)) {
			bool hit_group = false;
			while(bool(m_parameters.from_person) && !internal_increment_v2(first_time, hit_group)) {
			}
			if(!hit_group) {
				if(first_time) {
					first_time = false;
					internal_set_aggregates();
				} else {
					internal_update_aggregates();
				}
			} else {
				return;
			}
		}
	}
	void internal::query_sum_car_value_const_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_sum_car_value_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_sum_car_value_const_iterator::internal_increment_v0(bool force, bool& hit_group) {
		if(!force) {
			hit_group = true;
			return true;
		}
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_sum_car_value_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_sum_car_value_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_sum_car_value_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_sum_car_value_const_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_sum_car_value_const_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_sum_car_value_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	float internal::query_sum_car_value_const_iterator::get_rv_sum() const noexcept {
		return m_rv_sum;
	}
	bool internal::query_sum_car_value_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_sum_car_value_const_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_sum_car_value_iterator::operator++() -> query_sum_car_value_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_sum_car_value_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.from_person);
	}
	bool internal::query_sum_car_value_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.from_person);
	}
	auto internal::query_sum_car_value_iterator::operator*() -> query_sum_car_value_iterator const& {
		return *this;
	}
	void internal::query_sum_car_value_iterator::internal_reset_aggregates() {
		m_rv_sum = float{};
	}
	void internal::query_sum_car_value_iterator::internal_set_aggregates() {
		m_rv_sum = m_container.car_get_resale_value(m_tableindex2);
	}
	void internal::query_sum_car_value_iterator::internal_update_aggregates() {
		m_rv_sum = sum(m_rv_sum, m_container.car_get_resale_value(m_tableindex2));
	}
	void internal::query_sum_car_value_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			internal_set_aggregates();
			internal_increment_to_result(false);
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_sum_car_value_iterator::internal_increment_to_result(bool as_first) {
		if(as_first) internal_reset_aggregates();
		bool first_time = as_first;
		while(bool(m_parameters.from_person)) {
			bool hit_group = false;
			while(bool(m_parameters.from_person) && !internal_increment_v2(first_time, hit_group)) {
			}
			if(!hit_group) {
				if(first_time) {
					first_time = false;
					internal_set_aggregates();
				} else {
					internal_update_aggregates();
				}
			} else {
				return;
			}
		}
	}
	void internal::query_sum_car_value_iterator::internal_reset_v0() {
		internal_reset_v1();
	}
	bool internal::query_sum_car_value_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_sum_car_value_iterator::internal_increment_v0(bool force, bool& hit_group) {
		if(!force) {
			hit_group = true;
			return true;
		}
		m_parameters.from_person = person_id();
		return false;
	}
	void internal::query_sum_car_value_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_sum_car_value_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_sum_car_value_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_parameters.from_person);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_sum_car_value_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_sum_car_value_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_sum_car_value_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	float internal::query_sum_car_value_iterator::get_rv_sum() const noexcept {
		return m_rv_sum;
	}
	bool internal::query_sum_car_value_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_sum_car_value_iterator::has_car() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_pairs_of_cars_const_iterator::operator++() -> query_pairs_of_cars_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_pairs_of_cars_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_pairs_of_cars_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_pairs_of_cars_const_iterator::operator*() -> query_pairs_of_cars_const_iterator const& {
		return *this;
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_pairs_of_cars_const_iterator::internal_set_aggregates() {
	}
	void internal::query_pairs_of_cars_const_iterator::internal_update_aggregates() {
	}
	void internal::query_pairs_of_cars_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_pairs_of_cars_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v4(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
		internal_reset_v3();
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = car_ownership_id();
		internal_reset_v4();
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_set_v3(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.car_ownership_get_owned_car(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = car_ownership_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_pairs_of_cars_const_iterator::internal_reset_v4() {
		m_tableindex4 = car_id();
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_set_v4(car_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_pairs_of_cars_const_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_const_fat_id internal::query_pairs_of_cars_const_iterator::get_person_id() const noexcept {
		return person_const_fat_id(m_container, m_tableindex0 );
	}
	car_const_fat_id internal::query_pairs_of_cars_const_iterator::get_car_a_id() const noexcept {
		return car_const_fat_id(m_container, m_tableindex2 );
	}
	car_const_fat_id internal::query_pairs_of_cars_const_iterator::get_car_b_id() const noexcept {
		return car_const_fat_id(m_container, m_tableindex4 );
	}
	bool internal::query_pairs_of_cars_const_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_pairs_of_cars_const_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_pairs_of_cars_const_iterator::has_car_a() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_pairs_of_cars_const_iterator::has_car_b() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_pairs_of_cars_iterator::operator++() -> query_pairs_of_cars_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_pairs_of_cars_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_pairs_of_cars_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_pairs_of_cars_iterator::operator*() -> query_pairs_of_cars_iterator const& {
		return *this;
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_aggregates() {
	}
	void internal::query_pairs_of_cars_iterator::internal_set_aggregates() {
	}
	void internal::query_pairs_of_cars_iterator::internal_update_aggregates() {
	}
	void internal::query_pairs_of_cars_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_pairs_of_cars_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v4(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_v0() {
		m_tableindex0 = person_id();
		internal_reset_v1();
		internal_reset_v3();
	}
	bool internal::query_pairs_of_cars_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.person_size(); ++i) {
			if(internal_set_v0( person_id(person_id::value_base_t(i)) )) return true;
		}
		m_tableindex0 = person_id( );
		return false;
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = car_ownership_id();
		internal_reset_v2();
	}
	bool internal::query_pairs_of_cars_iterator::internal_set_v1(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.car_ownership_get_owned_car(m_tableindex1) );
		}() && 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = car_ownership_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_v2() {
		m_tableindex2 = car_id();
	}
	bool internal::query_pairs_of_cars_iterator::internal_set_v2(car_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( car_ownership_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = car_ownership_id();
		internal_reset_v4();
	}
	bool internal::query_pairs_of_cars_iterator::internal_set_v3(car_ownership_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.car_ownership_get_owned_car(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_pairs_of_cars_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_car_ownership_as_owner(m_tableindex0);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = car_ownership_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_pairs_of_cars_iterator::internal_reset_v4() {
		m_tableindex4 = car_id();
	}
	bool internal::query_pairs_of_cars_iterator::internal_set_v4(car_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_pairs_of_cars_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_fat_id internal::query_pairs_of_cars_iterator::get_person_id() const noexcept {
		return person_fat_id(m_container, m_tableindex0 );
	}
	car_fat_id internal::query_pairs_of_cars_iterator::get_car_a_id() const noexcept {
		return car_fat_id(m_container, m_tableindex2 );
	}
	car_fat_id internal::query_pairs_of_cars_iterator::get_car_b_id() const noexcept {
		return car_fat_id(m_container, m_tableindex4 );
	}
	bool internal::query_pairs_of_cars_iterator::has_person() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_pairs_of_cars_iterator::has_car_ownership() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_pairs_of_cars_iterator::has_car_a() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_pairs_of_cars_iterator::has_car_b() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_siblings_const_iterator::operator++() -> query_siblings_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_siblings_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.person_param);
	}
	bool internal::query_siblings_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.person_param);
	}
	auto internal::query_siblings_const_iterator::operator*() -> query_siblings_const_iterator const& {
		return *this;
	}
	void internal::query_siblings_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_siblings_const_iterator::internal_set_aggregates() {
	}
	void internal::query_siblings_const_iterator::internal_update_aggregates() {
	}
	void internal::query_siblings_const_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_tableindex2 .index() < m_tableindex4 .index()) {
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_siblings_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.person_param)) {
			while(bool(m_parameters.person_param) && !internal_increment_v4(false, hit_group)) {
			}
			if(bool(m_parameters.person_param)) {
				if(m_tableindex2 .index() < m_tableindex4 .index()) {
					return;
				}
			}
		}
	}
	void internal::query_siblings_const_iterator::internal_reset_v0() {
		internal_reset_v1();
		internal_reset_v3();
	}
	bool internal::query_siblings_const_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_const_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.person_param = person_id();
		return false;
	}
	void internal::query_siblings_const_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_siblings_const_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_siblings_const_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_siblings_const_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_siblings_const_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_siblings_const_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_siblings_const_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_siblings_const_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_siblings_const_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_siblings_const_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_const_fat_id internal::query_siblings_const_iterator::get_base_id() const noexcept {
		return person_const_fat_id(m_container, m_parameters.person_param );
	}
	person_const_fat_id internal::query_siblings_const_iterator::get_sibling_a_id() const noexcept {
		return person_const_fat_id(m_container, m_tableindex2 );
	}
	person_const_fat_id internal::query_siblings_const_iterator::get_sibling_b_id() const noexcept {
		return person_const_fat_id(m_container, m_tableindex4 );
	}
	bool internal::query_siblings_const_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_siblings_const_iterator::has_sibling_a() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_siblings_const_iterator::has_sibling_b() const noexcept {
		return bool(m_tableindex4);
	}
	
	auto internal::query_siblings_iterator::operator++() -> query_siblings_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_siblings_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_parameters.person_param);
	}
	bool internal::query_siblings_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_parameters.person_param);
	}
	auto internal::query_siblings_iterator::operator*() -> query_siblings_iterator const& {
		return *this;
	}
	void internal::query_siblings_iterator::internal_reset_aggregates() {
	}
	void internal::query_siblings_iterator::internal_set_aggregates() {
	}
	void internal::query_siblings_iterator::internal_update_aggregates() {
	}
	void internal::query_siblings_iterator::internal_init(person_id first_value) {
		if(internal_set_v0(first_value)) {
			if(m_tableindex2 .index() < m_tableindex4 .index()) {
				return;
			}
		}
		internal_increment_to_result(true);
	}
	void internal::query_siblings_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_parameters.person_param)) {
			while(bool(m_parameters.person_param) && !internal_increment_v4(false, hit_group)) {
			}
			if(bool(m_parameters.person_param)) {
				if(m_tableindex2 .index() < m_tableindex4 .index()) {
					return;
				}
			}
		}
	}
	void internal::query_siblings_iterator::internal_reset_v0() {
		internal_reset_v1();
		internal_reset_v3();
	}
	bool internal::query_siblings_iterator::internal_set_v0(person_id v) {
		if(!bool(v)) {
			return false;
		}
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex1 == 0) {
			return internal_set_v1( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex1 < m_size_of_m_tableindex1 ; ++ m_index_into_m_tableindex1) {
				if(internal_set_v1( *(range.first + m_index_into_m_tableindex1) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_iterator::internal_increment_v0(bool, bool&) {
		m_parameters.person_param = person_id();
		return false;
	}
	void internal::query_siblings_iterator::internal_reset_v1() {
		m_index_into_m_tableindex1 = 0;
		m_size_of_m_tableindex1 = 0;
		m_tableindex1 = parentage_id();
		internal_reset_v2();
	}
	bool internal::query_siblings_iterator::internal_set_v1(parentage_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.parentage_get_child(m_tableindex1) );
		}() && 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		if(m_index_into_m_tableindex1 + 1 < m_size_of_m_tableindex1) {
			++m_index_into_m_tableindex1;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
			return internal_set_v1( *(range.first + m_index_into_m_tableindex1) );
		} else {
			m_tableindex1 = parentage_id();
			return internal_increment_v0(force, hit_group);
		}
	}
	void internal::query_siblings_iterator::internal_reset_v2() {
		m_tableindex2 = person_id();
	}
	bool internal::query_siblings_iterator::internal_set_v2(person_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		[&](){
		auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = int32_t(range.second - range.first);
		if(m_size_of_m_tableindex3 == 0) {
			return internal_set_v3( parentage_id() );
		} else {
			for( ; m_index_into_m_tableindex3 < m_size_of_m_tableindex3 ; ++ m_index_into_m_tableindex3) {
				if(internal_set_v3( *(range.first + m_index_into_m_tableindex3) )) {
					return true;
				}
			}
			return false;
		}
		}() && 
		true;
	}
	bool internal::query_siblings_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	void internal::query_siblings_iterator::internal_reset_v3() {
		m_index_into_m_tableindex3 = 0;
		m_size_of_m_tableindex3 = 0;
		m_tableindex3 = parentage_id();
		internal_reset_v4();
	}
	bool internal::query_siblings_iterator::internal_set_v3(parentage_id v) {
		if(!bool(v)) {
			m_tableindex3 = v;
			return false;
		}
		m_tableindex3 = v;
		return 
		[&](){
		return internal_set_v4( m_container.parentage_get_child(m_tableindex3) );
		}() && 
		true;
	}
	bool internal::query_siblings_iterator::internal_increment_v3(bool force, bool& hit_group) {
		if(!bool(m_tableindex3)) {
			return internal_increment_v2(force, hit_group);
		}
		if(m_index_into_m_tableindex3 + 1 < m_size_of_m_tableindex3) {
			++m_index_into_m_tableindex3;
			auto range = m_container.person_range_of_parentage_as_bio_parent(m_parameters.person_param);
			return internal_set_v3( *(range.first + m_index_into_m_tableindex3) );
		} else {
			m_tableindex3 = parentage_id();
			return internal_increment_v2(force, hit_group);
		}
	}
	void internal::query_siblings_iterator::internal_reset_v4() {
		m_tableindex4 = person_id();
	}
	bool internal::query_siblings_iterator::internal_set_v4(person_id v) {
		if(!bool(v)) {
			m_tableindex4 = v;
			return false;
		}
		m_tableindex4 = v;
		return 
		true;
	}
	bool internal::query_siblings_iterator::internal_increment_v4(bool force, bool& hit_group) {
		if(!bool(m_tableindex4)) {
			return internal_increment_v3(force, hit_group);
		}
		return internal_increment_v3(force, hit_group);
	}
	person_fat_id internal::query_siblings_iterator::get_base_id() const noexcept {
		return person_fat_id(m_container, m_parameters.person_param );
	}
	person_fat_id internal::query_siblings_iterator::get_sibling_a_id() const noexcept {
		return person_fat_id(m_container, m_tableindex2 );
	}
	person_fat_id internal::query_siblings_iterator::get_sibling_b_id() const noexcept {
		return person_fat_id(m_container, m_tableindex4 );
	}
	bool internal::query_siblings_iterator::has_parentage() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_siblings_iterator::has_sibling_a() const noexcept {
		return bool(m_tableindex2);
	}
	bool internal::query_siblings_iterator::has_sibling_b() const noexcept {
		return bool(m_tableindex4);
	}
	
}

#undef DCON_RELEASE_INLINE
#pragma warning( pop )

