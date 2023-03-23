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

namespace cob3 {
	struct load_record {
		bool car : 1;
		bool car__index : 1;
		bool car_wheels : 1;
		bool car_resale_value : 1;
		bool person : 1;
		bool person__index : 1;
		bool person_age : 1;
		bool car_ownership : 1;
		bool car_ownership_owner : 1;
		bool car_ownership_owned_car : 1;
		bool car_ownership_ownership_date : 1;
		load_record() {
			car = false;
			car__index = false;
			car_wheels = false;
			car_resale_value = false;
			person = false;
			person__index = false;
			person_age = false;
			car_ownership = false;
			car_ownership_owner = false;
			car_ownership_owned_car = false;
			car_ownership_ownership_date = false;
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
namespace cob3 {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class const_object_iterator_car;
		class object_iterator_car;

		class alignas(64) car_class {
			friend const_object_iterator_car;
			friend object_iterator_car;
			private:
			//
			// storage space for _index of type car_id
			//
			struct dtype__index {
				car_id values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 1200); }
			}
			m__index;
			
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
			
			car_id first_free = car_id();
			uint32_t size_used = 0;


			public:
			car_class() {
				for(int32_t i = 1200 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = car_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_person;
		class object_iterator_person;

		class alignas(64) person_class {
			friend const_object_iterator_person;
			friend object_iterator_person;
			private:
			//
			// storage space for _index of type person_id
			//
			struct dtype__index {
				person_id values[100];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 100); }
			}
			m__index;
			
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
			
			person_id first_free = person_id();
			uint32_t size_used = 0;


			public:
			person_class() {
				for(int32_t i = 100 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = person_id(uint8_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_car_ownership;
		class object_iterator_car_ownership;
		class const_iterator_person_foreach_car_ownership_as_owner;
		class iterator_person_foreach_car_ownership_as_owner;
		struct const_iterator_person_foreach_car_ownership_as_owner_generator;
		struct iterator_person_foreach_car_ownership_as_owner_generator;

		class alignas(64) car_ownership_class {
			friend const_object_iterator_car_ownership;
			friend object_iterator_car_ownership;
			friend const_iterator_person_foreach_car_ownership_as_owner;
			friend iterator_person_foreach_car_ownership_as_owner;
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
			car_ownership_class() {
			}
			friend data_container;
		};

	}

	class car_const_fat_id;
	class car_fat_id;
	class person_const_fat_id;
	class person_fat_id;
	class car_ownership_const_fat_id;
	class car_ownership_fat_id;
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
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership_as_owner(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership_as_owner() const;
		DCON_RELEASE_INLINE void remove_all_car_ownership_as_owner() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator get_car_ownership_as_owner() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership() const;
		DCON_RELEASE_INLINE void remove_all_car_ownership() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator get_car_ownership() const;
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
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership_as_owner(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership_as_owner() const;
		DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator get_car_ownership_as_owner() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) const;
		DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> range_of_car_ownership() const;
		DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator get_car_ownership() const;
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
	
	namespace internal {
		class object_iterator_car {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_car(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_car& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_car& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_car const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_car const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_fat_id operator*() const noexcept {
				return car_fat_id(container, car_id(car_id::value_base_t(index)));
			}
		};
		class const_object_iterator_car {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_car(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_car& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_car& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_car const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_car const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_const_fat_id operator*() const noexcept {
				return car_const_fat_id(container, car_id(car_id::value_base_t(index)));
			}
		};
		
		class object_iterator_person {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_person(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_person& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_person& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_person const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_person const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE person_fat_id operator*() const noexcept {
				return person_fat_id(container, person_id(person_id::value_base_t(index)));
			}
		};
		class const_object_iterator_person {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_person(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_person& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_person& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_person const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_person const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE person_const_fat_id operator*() const noexcept {
				return person_const_fat_id(container, person_id(person_id::value_base_t(index)));
			}
		};
		
		class iterator_person_foreach_car_ownership_as_owner {
			private:
			data_container& container;
			car_ownership_id const* ptr = nullptr;
			public:
			iterator_person_foreach_car_ownership_as_owner(data_container& c, person_id fr) noexcept;
			iterator_person_foreach_car_ownership_as_owner(data_container& c, car_ownership_id const* r) noexcept : container(c), ptr(r) {}
			iterator_person_foreach_car_ownership_as_owner(data_container& c, person_id fr, int) noexcept;
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_ownership_fat_id operator*() const noexcept {
				return car_ownership_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner operator+(ptrdiff_t n) const noexcept {
				return iterator_person_foreach_car_ownership_as_owner(container, ptr + n);
			}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner operator-(ptrdiff_t n) const noexcept {
				return iterator_person_foreach_car_ownership_as_owner(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE car_ownership_fat_id operator[](ptrdiff_t n) const noexcept {
				return car_ownership_fat_id(container, *(ptr + n));
			}
		};
		class const_iterator_person_foreach_car_ownership_as_owner {
			private:
			data_container const& container;
			car_ownership_id const* ptr = nullptr;
			public:
			const_iterator_person_foreach_car_ownership_as_owner(data_container const& c, person_id fr) noexcept;
			const_iterator_person_foreach_car_ownership_as_owner(data_container const& c, car_ownership_id const* r) noexcept : container(c), ptr(r) {}
			const_iterator_person_foreach_car_ownership_as_owner(data_container const& c, person_id fr, int) noexcept;
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr == o.ptr;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_ownership_const_fat_id operator*() const noexcept {
				return car_ownership_const_fat_id(container, *ptr);
			}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& operator+=(ptrdiff_t n) noexcept {
				ptr += n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& operator-=(ptrdiff_t n) noexcept {
				ptr -= n;
				return *this;
			}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner operator+(ptrdiff_t n) const noexcept {
				return const_iterator_person_foreach_car_ownership_as_owner(container, ptr + n);
			}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner operator-(ptrdiff_t n) const noexcept {
				return const_iterator_person_foreach_car_ownership_as_owner(container, ptr - n);
			}
			DCON_RELEASE_INLINE ptrdiff_t operator-(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr - o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr > o.ptr;
			}
			DCON_RELEASE_INLINE bool operator>=(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr >= o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr < o.ptr;
			}
			DCON_RELEASE_INLINE bool operator<=(const_iterator_person_foreach_car_ownership_as_owner const& o) const noexcept {
				return ptr <= o.ptr;
			}
			DCON_RELEASE_INLINE car_ownership_const_fat_id operator[](ptrdiff_t n) const noexcept {
				return car_ownership_const_fat_id(container, *(ptr + n));
			}
		};
		
		struct iterator_person_foreach_car_ownership_as_owner_generator {
			data_container& container;
			person_id ob;
			iterator_person_foreach_car_ownership_as_owner_generator(data_container& c, person_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner begin() const noexcept {
				return iterator_person_foreach_car_ownership_as_owner(container, ob);
			}
			DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner end() const noexcept {
				return iterator_person_foreach_car_ownership_as_owner(container, ob, 0);
			}
		};
		struct const_iterator_person_foreach_car_ownership_as_owner_generator {
			data_container const& container;
			person_id ob;
			const_iterator_person_foreach_car_ownership_as_owner_generator(data_container const& c, person_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner begin() const noexcept {
				return const_iterator_person_foreach_car_ownership_as_owner(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner end() const noexcept {
				return const_iterator_person_foreach_car_ownership_as_owner(container, ob, 0);
			}
		};
		
		class object_iterator_car_ownership {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_car_ownership(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_car_ownership& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_car_ownership& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_car_ownership const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_car_ownership const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_ownership_fat_id operator*() const noexcept {
				return car_ownership_fat_id(container, car_ownership_id(car_ownership_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_car_ownership& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_car_ownership& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_car_ownership operator+(int32_t n) const noexcept {
				return object_iterator_car_ownership(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_car_ownership operator-(int32_t n) const noexcept {
				return object_iterator_car_ownership(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_car_ownership const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_car_ownership const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_car_ownership const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_car_ownership const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_car_ownership const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE car_ownership_fat_id operator[](int32_t n) const noexcept {
				return car_ownership_fat_id(container, car_ownership_id(car_ownership_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_car_ownership {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_car_ownership(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_car_ownership& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_car_ownership& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_car_ownership const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_car_ownership const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE car_ownership_const_fat_id operator*() const noexcept {
				return car_ownership_const_fat_id(container, car_ownership_id(car_ownership_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_car_ownership& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_car_ownership& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_car_ownership operator+(int32_t n) const noexcept {
				return const_object_iterator_car_ownership(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_car_ownership operator-(int32_t n) const noexcept {
				return const_object_iterator_car_ownership(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_car_ownership const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_car_ownership const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_car_ownership const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_car_ownership const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_car_ownership const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE car_ownership_const_fat_id operator[](int32_t n) const noexcept {
				return car_ownership_const_fat_id(container, car_ownership_id(car_ownership_id::value_base_t(int32_t(index) + n)));
			}
		};
		
	}

	class alignas(64) data_container {
		public:
		internal::car_class car;
		internal::person_class person;
		internal::car_ownership_class car_ownership;

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
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
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
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
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
			return bool(id) && uint32_t(id.index()) < car.size_used && car.m__index.vptr()[id.index()] == id;
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
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
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
		DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator person_get_car_ownership_as_owner(person_id id) const {
			return internal::const_iterator_person_foreach_car_ownership_as_owner_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator person_get_car_ownership_as_owner(person_id id) {
			return internal::iterator_person_foreach_car_ownership_as_owner_generator(*this, id);
		}
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
		DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator person_get_car_ownership(person_id id) const {
			return internal::const_iterator_person_foreach_car_ownership_as_owner_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator person_get_car_ownership(person_id id) {
			return internal::iterator_person_foreach_car_ownership_as_owner_generator(*this, id);
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
		DCON_RELEASE_INLINE bool person_is_valid(person_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < person.size_used && person.m__index.vptr()[id.index()] == id;
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
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
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
		// container delete for car
		//
		void delete_car(car_id id_removed) {
			if(!car_is_valid(id_removed)) return;
			car.m__index.vptr()[id_removed.index()] = car.first_free;
			car.first_free = id_removed;
			if(int32_t(car.size_used) - 1 == id_removed.index()) {
				for( ; car.size_used > 0 && car.m__index.vptr()[car.size_used - 1] != car_id(car_id::value_base_t(car.size_used - 1));  --car.size_used) ;
			}
			delete_car_ownership(car_ownership_id(car_ownership_id::value_base_t(id_removed.index())));
			car_ownership.size_used = car.size_used;
			car.m_wheels.vptr()[id_removed.index()] = int32_t{};
			car.m_resale_value.vptr()[id_removed.index()] = float{};
		}
		
		//
		// container create for car
		//
		car_id create_car() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(car.first_free)) std::abort();
			#else
			if(!bool(car.first_free)) throw dcon::out_of_space{};
			#endif
			car_id new_id = car.first_free;
			car.first_free = car.m__index.vptr()[car.first_free.index()];
			car.m__index.vptr()[new_id.index()] = new_id;
			car.size_used = std::max(car.size_used, uint32_t(new_id.index() + 1));
			car_ownership.size_used = car.size_used;
			return new_id;
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
				car.first_free = car_id();
				int32_t i = int32_t(1200 - 1);
				for(; i >= int32_t(new_size); --i) {
					car.m__index.vptr()[i] = car.first_free;
					car.first_free = car_id(car_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(car.m__index.vptr()[i] != car_id(car_id::value_base_t(i))) {
						car.m__index.vptr()[i] = car.first_free;
						car.first_free = car_id(car_id::value_base_t(i));
					}
				}
				std::fill_n(car.m_wheels.vptr() + new_size, old_size - new_size, int32_t{});
				std::fill_n(car.m_resale_value.vptr() + new_size, old_size - new_size, float{});
				car_ownership_resize(std::min(new_size, car_ownership.size_used));
			} else if(new_size > old_size) {
				car.first_free = car_id();
				int32_t i = int32_t(1200 - 1);
				for(; i >= int32_t(old_size); --i) {
					car.m__index.vptr()[i] = car.first_free;
					car.first_free = car_id(car_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(car.m__index.vptr()[i] != car_id(car_id::value_base_t(i))) {
						car.m__index.vptr()[i] = car.first_free;
						car.first_free = car_id(car_id::value_base_t(i));
					}
				}
			}
			car.size_used = new_size;
		}
		
		//
		// container delete for person
		//
		void delete_person(person_id id_removed) {
			if(!person_is_valid(id_removed)) return;
			person.m__index.vptr()[id_removed.index()] = person.first_free;
			person.first_free = id_removed;
			if(int32_t(person.size_used) - 1 == id_removed.index()) {
				for( ; person.size_used > 0 && person.m__index.vptr()[person.size_used - 1] != person_id(person_id::value_base_t(person.size_used - 1));  --person.size_used) ;
			}
			person_remove_all_car_ownership_as_owner(id_removed);
			person.m_age.vptr()[id_removed.index()] = int32_t{};
		}
		
		//
		// container create for person
		//
		person_id create_person() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(person.first_free)) std::abort();
			#else
			if(!bool(person.first_free)) throw dcon::out_of_space{};
			#endif
			person_id new_id = person.first_free;
			person.first_free = person.m__index.vptr()[person.first_free.index()];
			person.m__index.vptr()[new_id.index()] = new_id;
			person.size_used = std::max(person.size_used, uint32_t(new_id.index() + 1));
			return new_id;
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
				person.first_free = person_id();
				int32_t i = int32_t(100 - 1);
				for(; i >= int32_t(new_size); --i) {
					person.m__index.vptr()[i] = person.first_free;
					person.first_free = person_id(person_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(person.m__index.vptr()[i] != person_id(person_id::value_base_t(i))) {
						person.m__index.vptr()[i] = person.first_free;
						person.first_free = person_id(person_id::value_base_t(i));
					}
				}
				std::fill_n(person.m_age.vptr() + new_size, old_size - new_size, int32_t{});
				car_ownership_resize(0);
			} else if(new_size > old_size) {
				person.first_free = person_id();
				int32_t i = int32_t(100 - 1);
				for(; i >= int32_t(old_size); --i) {
					person.m__index.vptr()[i] = person.first_free;
					person.first_free = person_id(person_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(person.m__index.vptr()[i] != person_id(person_id::value_base_t(i))) {
						person.m__index.vptr()[i] = person.first_free;
						person.first_free = person_id(person_id::value_base_t(i));
					}
				}
			}
			person.size_used = new_size;
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
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id_removed.index() >= 0);
			#endif
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
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car(T&& func) {
			for(uint32_t i = 0; i < car.size_used; ++i) {
				car_id tmp = car_id(car_id::value_base_t(i));
				if(car.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_car;
		friend internal::object_iterator_car;
		struct {
			internal::object_iterator_car begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_car));
				return internal::object_iterator_car(*container, uint32_t(0));
			}
			internal::object_iterator_car end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_car));
				return internal::object_iterator_car(*container, container->car_size());
			}
			internal::const_object_iterator_car begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_car));
				return internal::const_object_iterator_car(*container, uint32_t(0));
			}
			internal::const_object_iterator_car end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_car));
				return internal::const_object_iterator_car(*container, container->car_size());
			}
		}  in_car ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_person(T&& func) {
			for(uint32_t i = 0; i < person.size_used; ++i) {
				person_id tmp = person_id(person_id::value_base_t(i));
				if(person.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_person;
		friend internal::object_iterator_person;
		struct {
			internal::object_iterator_person begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_person));
				return internal::object_iterator_person(*container, uint32_t(0));
			}
			internal::object_iterator_person end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_person));
				return internal::object_iterator_person(*container, container->person_size());
			}
			internal::const_object_iterator_person begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_person));
				return internal::const_object_iterator_person(*container, uint32_t(0));
			}
			internal::const_object_iterator_person end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_person));
				return internal::const_object_iterator_person(*container, container->person_size());
			}
		}  in_person ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) {
			for(uint32_t i = 0; i < car_ownership.size_used; ++i) {
				car_ownership_id tmp = car_ownership_id(car_ownership_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_car_ownership;
		friend internal::object_iterator_car_ownership;
		struct {
			internal::object_iterator_car_ownership begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_car_ownership));
				return internal::object_iterator_car_ownership(*container, uint32_t(0));
			}
			internal::object_iterator_car_ownership end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_car_ownership));
				return internal::object_iterator_car_ownership(*container, container->car_ownership_size());
			}
			internal::const_object_iterator_car_ownership begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_car_ownership));
				return internal::const_object_iterator_car_ownership(*container, uint32_t(0));
			}
			internal::const_object_iterator_car_ownership end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_car_ownership));
				return internal::const_object_iterator_car_ownership(*container, container->car_ownership_size());
			}
		}  in_car_ownership ;
		



		void reset() {
			car_ownership_resize(0);
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
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.car = true;
			result.car__index = true;
			result.car_wheels = true;
			result.car_resale_value = true;
			result.person = true;
			result.person__index = true;
			result.person_age = true;
			result.car_ownership = true;
			result.car_ownership_owner = true;
			result.car_ownership_owned_car = true;
			result.car_ownership_ownership_date = true;
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
			if(serialize_selection.car__index) {
				dcon::record_header iheader(0, "uint16_t", "car", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(car_id) * car.size_used;
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
			if(serialize_selection.person__index) {
				dcon::record_header iheader(0, "uint8_t", "person", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(person_id) * person.size_used;
			}
			if(serialize_selection.person_age) {
				dcon::record_header iheader(0, "int32_t", "person", "age");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * person.size_used;
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
			if(serialize_selection.car__index) {
				dcon::record_header header(sizeof(car_id) * car.size_used, "uint16_t", "car", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<car_id*>(output_buffer), car.m__index.vptr(), sizeof(car_id) * car.size_used);
				output_buffer += sizeof(car_id) * car.size_used;
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
			if(serialize_selection.person__index) {
				dcon::record_header header(sizeof(person_id) * person.size_used, "uint8_t", "person", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<person_id*>(output_buffer), person.m__index.vptr(), sizeof(person_id) * person.size_used);
				output_buffer += sizeof(person_id) * person.size_used;
			}
			if(serialize_selection.person_age) {
				dcon::record_header header(sizeof(int32_t) * person.size_used, "int32_t", "person", "age");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), person.m_age.vptr(), sizeof(int32_t) * person.size_used);
				output_buffer += sizeof(int32_t) * person.size_used;
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
		}
		
		//
		// deserialize the desired objects, relationships, and properties
		//
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
					do {
						if(header.is_object("car")) {
							if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
								car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
								serialize_selection.car = true;
							}
							else if(header.is_property("_index")) {
								if(header.is_type("uint16_t")) {
									std::memcpy(car.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(uint16_t), header.record_size));
									serialize_selection.car__index = true;
								}
								else if(header.is_type("uint8_t")) {
									for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
										car.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
									}
									serialize_selection.car__index = true;
								}
								else if(header.is_type("uint32_t")) {
									for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
										car.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
									}
									serialize_selection.car__index = true;
								}
								if(serialize_selection.car__index == true) {
									car.size_used = 0;
									car.first_free = car_id();
									for(int32_t j = 1200 - 1; j > 0; --j) {
										if(car.m__index.vptr()[j] != car_id(uint16_t(j))) {
											car.m__index.vptr()[j] = car.first_free;
											car.first_free = car_id(uint16_t(j));
										} else {
											car.size_used = std::max(car.size_used, uint32_t(j));
										}
									}
								}
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
							break;
						}
						if(header.is_object("person")) {
							if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
								person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
								serialize_selection.person = true;
							}
							else if(header.is_property("_index")) {
								if(header.is_type("uint8_t")) {
									std::memcpy(person.m__index.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(uint8_t), header.record_size));
									serialize_selection.person__index = true;
								}
								else if(header.is_type("uint16_t")) {
									for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
										person.m__index.vptr()[i].value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
									}
									serialize_selection.person__index = true;
								}
								else if(header.is_type("uint32_t")) {
									for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
										person.m__index.vptr()[i].value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
									}
									serialize_selection.person__index = true;
								}
								if(serialize_selection.person__index == true) {
									person.size_used = 0;
									person.first_free = person_id();
									for(int32_t j = 100 - 1; j > 0; --j) {
										if(person.m__index.vptr()[j] != person_id(uint8_t(j))) {
											person.m__index.vptr()[j] = person.first_free;
											person.first_free = person_id(uint8_t(j));
										} else {
											person.size_used = std::max(person.size_used, uint32_t(j));
										}
									}
								}
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
							break;
						}
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
							break;
						}
					} while(false);
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
					do {
						if(header.is_object("car") && mask.car) {
							if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
								car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
								serialize_selection.car = true;
							}
							else if(header.is_property("_index") && mask.car__index) {
								if(header.is_type("uint16_t")) {
									std::memcpy(car.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(uint16_t), header.record_size));
									serialize_selection.car__index = true;
								}
								else if(header.is_type("uint8_t")) {
									for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
										car.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
									}
									serialize_selection.car__index = true;
								}
								else if(header.is_type("uint32_t")) {
									for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
										car.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
									}
									serialize_selection.car__index = true;
								}
								if(serialize_selection.car__index == true) {
									car.size_used = 0;
									car.first_free = car_id();
									for(int32_t j = 1200 - 1; j > 0; --j) {
										if(car.m__index.vptr()[j] != car_id(uint16_t(j))) {
											car.m__index.vptr()[j] = car.first_free;
											car.first_free = car_id(uint16_t(j));
										} else {
											car.size_used = std::max(car.size_used, uint32_t(j));
										}
									}
								}
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
							break;
						}
						if(header.is_object("person") && mask.person) {
							if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
								person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
								serialize_selection.person = true;
							}
							else if(header.is_property("_index") && mask.person__index) {
								if(header.is_type("uint8_t")) {
									std::memcpy(person.m__index.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(uint8_t), header.record_size));
									serialize_selection.person__index = true;
								}
								else if(header.is_type("uint16_t")) {
									for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
										person.m__index.vptr()[i].value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
									}
									serialize_selection.person__index = true;
								}
								else if(header.is_type("uint32_t")) {
									for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
										person.m__index.vptr()[i].value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
									}
									serialize_selection.person__index = true;
								}
								if(serialize_selection.person__index == true) {
									person.size_used = 0;
									person.first_free = person_id();
									for(int32_t j = 100 - 1; j > 0; --j) {
										if(person.m__index.vptr()[j] != person_id(uint8_t(j))) {
											person.m__index.vptr()[j] = person.first_free;
											person.first_free = person_id(uint8_t(j));
										} else {
											person.size_used = std::max(person.size_used, uint32_t(j));
										}
									}
								}
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
							break;
						}
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
							break;
						}
					} while(false);
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
	DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator person_fat_id::get_car_ownership_as_owner() const {
		return internal::iterator_person_foreach_car_ownership_as_owner_generator(container, id);
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
	DCON_RELEASE_INLINE internal::iterator_person_foreach_car_ownership_as_owner_generator person_fat_id::get_car_ownership() const {
		return internal::iterator_person_foreach_car_ownership_as_owner_generator(container, id);
	}
	DCON_RELEASE_INLINE bool person_fat_id::is_valid() const noexcept {
		return container.person_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t person_const_fat_id::get_age() const noexcept {
		return container.person_get_age(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_car_ownership_as_owner(T&& func) const {
		container.person_for_each_car_ownership_as_owner(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_const_fat_id::range_of_car_ownership_as_owner() const {
		return container.person_range_of_car_ownership_as_owner(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator person_const_fat_id::get_car_ownership_as_owner() const {
		return internal::const_iterator_person_foreach_car_ownership_as_owner_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void person_const_fat_id::for_each_car_ownership(T&& func) const {
		container.person_for_each_car_ownership(id, [&, t = this](car_ownership_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<car_ownership_id const*, car_ownership_id const*> person_const_fat_id::range_of_car_ownership() const {
		return container.person_range_of_car_ownership(id);
	}
	DCON_RELEASE_INLINE internal::const_iterator_person_foreach_car_ownership_as_owner_generator person_const_fat_id::get_car_ownership() const {
		return internal::const_iterator_person_foreach_car_ownership_as_owner_generator(container, id);
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
	

	namespace internal {
		DCON_RELEASE_INLINE object_iterator_car::object_iterator_car(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_car::const_object_iterator_car(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_car& object_iterator_car::operator++() noexcept {
			++index;
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_car& const_object_iterator_car::operator++() noexcept {
			++index;
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_car& object_iterator_car::operator--() noexcept {
			--index;
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_car& const_object_iterator_car::operator--() noexcept {
			--index;
			while(container.car.m__index.vptr()[index] != car_id(car_id::value_base_t(index)) && index < container.car.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_person::object_iterator_person(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_person::const_object_iterator_person(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_person& object_iterator_person::operator++() noexcept {
			++index;
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_person& const_object_iterator_person::operator++() noexcept {
			++index;
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_person& object_iterator_person::operator--() noexcept {
			--index;
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_person& const_object_iterator_person::operator--() noexcept {
			--index;
			while(container.person.m__index.vptr()[index] != person_id(person_id::value_base_t(index)) && index < container.person.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner::iterator_person_foreach_car_ownership_as_owner(data_container& c,  person_id fr) noexcept : container(c) {
			ptr = container.car_ownership.m_array_owner.vptr()[fr.index()].data();
		}
		DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner::iterator_person_foreach_car_ownership_as_owner(data_container& c, person_id fr, int) noexcept : container(c) {
			auto& vref = container.car_ownership.m_array_owner.vptr()[fr.index()];
			ptr = vref.data() + vref.size();
		}
		DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& iterator_person_foreach_car_ownership_as_owner::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_person_foreach_car_ownership_as_owner& iterator_person_foreach_car_ownership_as_owner::operator--() noexcept {
			--ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner::const_iterator_person_foreach_car_ownership_as_owner(data_container const& c,  person_id fr) noexcept : container(c) {
			ptr = container.car_ownership.m_array_owner.vptr()[fr.index()].data();
		}
		DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner::const_iterator_person_foreach_car_ownership_as_owner(data_container const& c, person_id fr, int) noexcept : container(c) {
			auto& vref = container.car_ownership.m_array_owner.vptr()[fr.index()];
			ptr = vref.data() + vref.size();
		}
		DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& const_iterator_person_foreach_car_ownership_as_owner::operator++() noexcept {
			++ptr;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_person_foreach_car_ownership_as_owner& const_iterator_person_foreach_car_ownership_as_owner::operator--() noexcept {
			--ptr;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_car_ownership::object_iterator_car_ownership(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_car_ownership::const_object_iterator_car_ownership(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_car_ownership& object_iterator_car_ownership::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_car_ownership& const_object_iterator_car_ownership::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_car_ownership& object_iterator_car_ownership::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_car_ownership& const_object_iterator_car_ownership::operator--() noexcept {
			--index;
			return *this;
		}
		
	};


}

#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif

