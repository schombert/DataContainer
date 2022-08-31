#pragma once
#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
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

namespace cob2 {
	struct load_record {
		bool car : 1;
		bool car_wheels : 1;
		bool car_resale_value : 1;
		bool person : 1;
		bool person_age : 1;
		bool car_ownership : 1;
		bool car_ownership_owner : 1;
		bool car_ownership_owned_car : 1;
		bool car_ownership_ownership_date : 1;
		load_record() {
			car = false;
			car_wheels = false;
			car_resale_value = false;
			person = false;
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
	
		uint16_t value;
	
		explicit constexpr car_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr car_id(car_id const& v) noexcept = default;
		constexpr car_id(car_id&& v) noexcept = default;
		constexpr car_id() noexcept : value(uint16_t(0)) {}
	
		car_id& operator=(car_id v) noexcept { value = v.value; return *this; }
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
	
		uint8_t value;
	
		explicit constexpr person_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr person_id(person_id const& v) noexcept = default;
		constexpr person_id(person_id&& v) noexcept = default;
		constexpr person_id() noexcept : value(uint8_t(0)) {}
	
		person_id& operator=(person_id v) noexcept { value = v.value; return *this; }
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
	
	using car_ownership_id = car_id;

}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<cob2::car_id> {
		using type = tagged_vector<cob2::car_id>;
	};
	
	template<>
	struct value_to_vector_type_s<cob2::person_id> {
		using type = tagged_vector<cob2::person_id>;
	};
	
}

#endif
namespace cob2 {
	class data_container;

	namespace internal {
		class alignas(64) car_class {
			private:
			//
			// storage space for wheels of type int32_t
			//
			struct alignas(64) dtype_wheels {
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_wheels() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))); }
			}
			m_wheels;
			
			//
			// storage space for resale_value of type float
			//
			struct alignas(64) dtype_resale_value {
				uint8_t padding[(sizeof(float) + 63ui32) & ~63ui32];
				float values[(sizeof(float) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(float))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(float)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_resale_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(float))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(float)) - 1ui32) : uint32_t(1200))); }
			}
			m_resale_value;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

		class alignas(64) person_class {
			private:
			//
			// storage space for age of type int32_t
			//
			struct alignas(64) dtype_age {
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(100) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(100))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_age() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(100) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(100))); }
			}
			m_age;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

		class alignas(64) car_ownership_class {
			private:
			//
			// storage space for ownership_date of type int32_t
			//
			struct alignas(64) dtype_ownership_date {
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_ownership_date() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))); }
			}
			m_ownership_date;
			
			//
			// storage space for owner of type person_id
			//
			struct alignas(64) dtype_owner {
				uint8_t padding[(sizeof(person_id) + 63ui32) & ~63ui32];
				person_id values[(sizeof(person_id) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(person_id))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(person_id)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_owner() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(person_id) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(person_id))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(person_id)) - 1ui32) : uint32_t(1200))); }
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
			friend class data_container;
		};

	}

	class alignas(64) data_container {
		public:
		internal::car_class car;
		internal::person_class person;
		internal::car_ownership_class car_ownership;

		//
		// getters for car: wheels
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
		
		//
		// setters for car: wheels
		//
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
		// getters for car: resale_value
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
		
		//
		// setters for car: resale_value
		//
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
		
		uint32_t car_size() const noexcept { return car.size_used; }

		//
		// getters for person: age
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
		
		//
		// setters for person: age
		//
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
		
		uint32_t person_size() const noexcept { return person.size_used; }

		//
		// getters for car_ownership: ownership_date
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
		
		//
		// setters for car_ownership: ownership_date
		//
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
		
		uint32_t car_ownership_size() const noexcept { return car_ownership.size_used; }

		//
		// many key getters and setters for car_ownership: owner
		//
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
		void car_ownership_set_owner(car_ownership_id id, person_id value) noexcept {
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
			std::for_each(temp.begin(), temp.end(), [t = this](car_ownership_id i) { t->delete_car_ownership(i); });
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
			std::for_each(temp.begin(), temp.end(), [t = this](car_ownership_id i) { t->delete_car_ownership(i); });
		}
		
		//
		// primary key getters and setters for car_ownership: owned_car
		//
		DCON_RELEASE_INLINE car_ownership_id car_ownership_get_owned_car(car_ownership_id id) const noexcept {
			return id;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_ownership_get_owned_car(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_ownership_get_owned_car(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_ownership_get_owned_car(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return id;
		}
		#endif
		void car_ownership_set_owned_car(car_ownership_id id, car_ownership_id value) noexcept {
			if(bool(value)) {
				delete_car_ownership(value);
				internal_move_relationship_car_ownership(id, value);
			} else {
				delete_car_ownership(id);
			}
		}
		bool car_ownership_try_set_owned_car(car_ownership_id id, car_ownership_id value) noexcept {
			if(bool(value)) {
				if(is_valid_car_ownership(value)) return false;
				internal_move_relationship_car_ownership(id, value);
			} else {
				delete_car_ownership(id);
			}
			return true;
		}
		
		DCON_RELEASE_INLINE car_ownership_id car_get_car_ownership_as_owned_car(car_id id) const noexcept {
			return id;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership_as_owned_car(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership_as_owned_car(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership_as_owned_car(ve::tagged_vector<car_id> id) const noexcept {
			return id;
		}
		#endif
		DCON_RELEASE_INLINE void car_remove_car_ownership_as_owned_car(car_id id) noexcept {
			if(is_valid_car_ownership(id)) {
				delete_car_ownership(id);
			}
		}
		
		DCON_RELEASE_INLINE car_ownership_id car_get_car_ownership(car_id id) const noexcept {
			return id;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::apply([](car_ownership_id i){ return i; }, id);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> car_get_car_ownership(ve::tagged_vector<car_id> id) const noexcept {
			return id;
		}
		#endif
		DCON_RELEASE_INLINE void car_remove_car_ownership(car_id id) noexcept {
			if(is_valid_car_ownership(id)) {
				delete_car_ownership(id);
			}
		}
		

		//
		// convenience getters and setters that operate via an implcit join
		//
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
		int32_t car_get_ownership_date_from_car_ownership(car_id ref_id) const {
			return car_ownership_get_ownership_date(ref_id);
		}
		#ifndef DCON_NO_VE
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ref_id);
		}
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::partial_contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ref_id);
		}
		ve::value_to_vector_type<int32_t> car_get_ownership_date_from_car_ownership(ve::tagged_vector<car_id> ref_id) const {
			return car_ownership_get_ownership_date(ref_id);
		}
		#endif
		void car_set_ownership_date_from_car_ownership(car_id ref_id, int32_t val) {
			car_ownership_set_ownership_date(ref_id, val);
		}
		person_id car_get_owner_from_car_ownership(car_id ref_id) const {
			return car_ownership_get_owner(ref_id);
		}
		#ifndef DCON_NO_VE
		ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_owner(ref_id);
		}
		ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::partial_contiguous_tags<car_id> ref_id) const {
			return car_ownership_get_owner(ref_id);
		}
		ve::value_to_vector_type<person_id> car_get_owner_from_car_ownership(ve::tagged_vector<car_id> ref_id) const {
			return car_ownership_get_owner(ref_id);
		}
		#endif
		void car_set_owner_from_car_ownership(car_id ref_id, person_id val) {
			car_ownership_set_owner(ref_id, val);
		}
		template<typename T>
		void person_for_each_owned_car_from_car_ownership(person_id id, T&& func) const {
			person_for_each_car_ownership_as_owner(id, [&](car_ownership_id i) {
				func(car_ownership_get_owned_car(i));
			} );
		}
		bool person_has_owned_car_from_car_ownership(person_id id, car_id const& target) const {
			auto& vref = car_ownership.m_array_owner.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(*pos == target) return true;
			}
			return false;
		}
		
		//
		// container pop_back for car
		//
		void car_pop_back() {
			if(car.size_used == 0) return;
			car_id id_removed(car_id::value_base_t(car.size_used - 1));
			delete_car_ownership(id_removed);
			car_ownership.size_used = car.size_used - 1;
			car_ownership.m_ownership_date.vptr()[id_removed.index()] = int32_t{};
			car.m_wheels.vptr()[id_removed.index()] = int32_t{};
			car.m_resale_value.vptr()[id_removed.index()] = float{};
			--car.size_used;
		}
		
		//
		// container resize for car
		//
		void car_resize(uint32_t new_size) {
			if(new_size > 1200) std::abort();
			const uint32_t old_size = car.size_used;
			if(new_size < old_size) {
				std::fill_n(car.m_wheels.vptr() + new_size, old_size - new_size, int32_t{});
				std::fill_n(car.m_resale_value.vptr() + new_size, old_size - new_size, float{});
				car_ownership_resize(new_size);
			} else if(new_size > old_size) {
				car_ownership_resize(new_size);
			}
			car.size_used = new_size;
		}
		
		//
		// container create for car
		//
		car_id create_car() {
			car_id new_id(car_id::value_base_t(car.size_used));
			if(car.size_used >= 1200) std::abort();
			car_ownership.size_used = car.size_used + 1;
			++car.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for car
		//
		void delete_car(car_id id) {
			car_id id_removed = id;
			car_id last_id(car_id::value_base_t(car.size_used - 1));
			if(id_removed == last_id) { car_pop_back(); return; }
			delete_car_ownership(id_removed);
			internal_move_relationship_car_ownership(last_id, id_removed);
			car_ownership.size_used = car.size_used - 1;
			car.m_wheels.vptr()[id_removed.index()] = std::move(car.m_wheels.vptr()[last_id.index()]);
			car.m_wheels.vptr()[last_id.index()] = int32_t{};
			car.m_resale_value.vptr()[id_removed.index()] = std::move(car.m_resale_value.vptr()[last_id.index()]);
			car.m_resale_value.vptr()[last_id.index()] = float{};
			--car.size_used;
		}
		
		bool is_valid_car(car_id id) const {
			return bool(id) && uint32_t(id.index()) < car.size_used;
		}
		//
		// container pop_back for person
		//
		void person_pop_back() {
			if(person.size_used == 0) return;
			person_id id_removed(person_id::value_base_t(person.size_used - 1));
			person_remove_all_car_ownership_as_owner(id_removed);
			person.m_age.vptr()[id_removed.index()] = int32_t{};
			--person.size_used;
		}
		
		//
		// container resize for person
		//
		void person_resize(uint32_t new_size) {
			if(new_size > 100) std::abort();
			const uint32_t old_size = person.size_used;
			if(new_size < old_size) {
				std::fill_n(person.m_age.vptr() + new_size, old_size - new_size, int32_t{});
				std::destroy_n(car_ownership.m_array_owner.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(car_ownership.m_array_owner.vptr() + 0, old_size);
				std::fill_n(car_ownership.m_owner.vptr() + 0, car_ownership.size_used, person_id{});
			} else if(new_size > old_size) {
				std::destroy_n(car_ownership.m_array_owner.vptr() + 0, new_size);
				std::uninitialized_default_construct_n(car_ownership.m_array_owner.vptr() + 0, new_size);
				std::fill_n(car_ownership.m_owner.vptr() + 0, car_ownership.size_used, person_id{});
			}
			person.size_used = new_size;
		}
		
		//
		// container create for person
		//
		person_id create_person() {
			person_id new_id(person_id::value_base_t(person.size_used));
			if(person.size_used >= 100) std::abort();
			++person.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for person
		//
		void delete_person(person_id id) {
			person_id id_removed = id;
			person_id last_id(person_id::value_base_t(person.size_used - 1));
			if(id_removed == last_id) { person_pop_back(); return; }
			person_remove_all_car_ownership_as_owner(id_removed);
			person_for_each_car_ownership_as_owner(last_id, [t = this, id_removed](car_ownership_id i){ t->car_ownership.m_owner.vptr()[i.index()] = id_removed; });
			car_ownership.m_array_owner.vptr()[id_removed.index()] = std::move(car_ownership.m_array_owner.vptr()[last_id.index()]);
			car_ownership.m_array_owner.vptr()[last_id.index()] = std::vector<car_ownership_id>{};
			person.m_age.vptr()[id_removed.index()] = std::move(person.m_age.vptr()[last_id.index()]);
			person.m_age.vptr()[last_id.index()] = int32_t{};
			--person.size_used;
		}
		
		bool is_valid_person(person_id id) const {
			return bool(id) && uint32_t(id.index()) < person.size_used;
		}
		//
		// container resize for car_ownership
		//
		void car_ownership_resize(uint32_t new_size) {
			if(new_size > 1200) std::abort();
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
			car_ownership_set_owner(id_removed, person_id());
			car_ownership.m_ownership_date.vptr()[id_removed.index()] = int32_t{};
		}
		
		bool is_valid_car_ownership(car_ownership_id id) const {
			return bool(id) && uint32_t(id.index()) < car_ownership.size_used && is_valid_car(id) && (bool(car_ownership.m_owner.vptr()[id.index()]) || false);
		}
		private:
		//
		// container move relationship for car_ownership
		//
		void internal_move_relationship_car_ownership(car_ownership_id last_id, car_ownership_id id_removed) {
			car_ownership_set_owner(id_removed, person_id());
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
			if(is_valid_car_ownership(owned_car_p)) return car_ownership_id();
			car_ownership_id new_id = owned_car_p;
			car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}
		
		//
		// container force create relationship for car_ownership
		//
		car_ownership_id force_create_car_ownership(person_id owner_p, car_id owned_car_p) {
			car_ownership_id new_id = owned_car_p;
			car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car(T&& func) {
			for(uint32_t i = 0; i < car.size_used; ++i) {
				car_id tmp(car_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_person(T&& func) {
			for(uint32_t i = 0; i < person.size_used; ++i) {
				person_id tmp(person_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_car_ownership(T&& func) {
			for(uint32_t i = 0; i < car_ownership.size_used; ++i) {
				car_ownership_id tmp(car_ownership_id::value_base_t(i));
				func(tmp);
			}
		}
		


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
			ve::execute_serial(car.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_car(F&& functor) {
			ve::execute_parallel_exact(car.size_used, functor);
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
			ve::execute_serial(person.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_person(F&& functor) {
			ve::execute_parallel_exact(person.size_used, functor);
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
			ve::execute_serial(car_ownership.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_car_ownership(F&& functor) {
			ve::execute_parallel_exact(car_ownership.size_used, functor);
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
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.car_wheels) {
				dcon::record_header iheader(sizeof(int32_t) * car.size_used, "int32_t", "car", "wheels");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * car.size_used;
			}
			if(serialize_selection.car_resale_value) {
				dcon::record_header iheader(sizeof(float) * car.size_used, "float", "car", "resale_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * car.size_used;
			}
			if(serialize_selection.person) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "person", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.person_age) {
				dcon::record_header iheader(sizeof(int32_t) * person.size_used, "int32_t", "person", "age");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * person.size_used;
			}
			if(serialize_selection.car_ownership) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car_ownership", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.car_ownership_owner) {
					dcon::record_header iheader(sizeof(person_id) * car_ownership.size_used, "uint8_t", "car_ownership", "owner");
					total_size += iheader.serialize_size();
					total_size += sizeof(person_id) * car_ownership.size_used;
				}
				dcon::record_header headerb(0, "$", "car_ownership", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header iheader(sizeof(int32_t) * car_ownership.size_used, "int32_t", "car_ownership", "ownership_date");
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
			if(serialize_selection.car_wheels) {
				dcon::record_header header(sizeof(int32_t) * car.size_used, "int32_t", "car", "wheels");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), car.m_wheels.vptr(), sizeof(int32_t) * car.size_used);
				output_buffer += sizeof(int32_t) * car.size_used;
			}
			if(serialize_selection.car_resale_value) {
				dcon::record_header header(sizeof(float) * car.size_used, "float", "car", "resale_value");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<float*>(output_buffer), car.m_resale_value.vptr(), sizeof(float) * car.size_used);
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
				memcpy(reinterpret_cast<int32_t*>(output_buffer), person.m_age.vptr(), sizeof(int32_t) * person.size_used);
				output_buffer += sizeof(int32_t) * person.size_used;
			}
			if(serialize_selection.car_ownership) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car_ownership", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = car_ownership.size_used;
				output_buffer += sizeof(uint32_t);
				dcon::record_header iheader(sizeof(person_id) * car_ownership.size_used, "uint8_t", "car_ownership", "owner");
				iheader.serialize(output_buffer);
				memcpy(reinterpret_cast<person_id*>(output_buffer), car_ownership.m_owner.vptr(), sizeof(person_id) * car_ownership.size_used);
				output_buffer += sizeof(person_id) * car_ownership.size_used;
				dcon::record_header headerb(0, "$", "car_ownership", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header header(sizeof(int32_t) * car_ownership.size_used, "int32_t", "car_ownership", "ownership_date");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), car_ownership.m_ownership_date.vptr(), sizeof(int32_t) * car_ownership.size_used);
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
					if(header.is_object("car")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.car = true;
						}
						else if(header.is_property("wheels")) {
							if(header.is_type("int32_t")) {
								memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(car.m_resale_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(float), header.record_size));
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
								memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(car_ownership.m_owner.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(uint8_t), header.record_size));
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
									car_ownership_set_owner(car_ownership_id(car_ownership_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("ownership_date")) {
							if(header.is_type("int32_t")) {
								memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(car.m_resale_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(float), header.record_size));
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
								memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(car_ownership.m_owner.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(uint8_t), header.record_size));
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
									car_ownership_set_owner(car_ownership_id(car_ownership_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("ownership_date") && mask.car_ownership_ownership_date) {
							if(header.is_type("int32_t")) {
								memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
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
					}
				}
				input_buffer += header.record_size;
			}
		}
		

	};

}

#undef DCON_RELEASE_INLINE
#pragma warning( pop )

