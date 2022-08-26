#pragma once
#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include "ve.hpp"

#ifdef NDEBUG
#ifdef _MSC_VER
#define DCON_RELEASE_INLINE __forceinline
#else
#define DCON_RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define DCON_RELEASE_INLINE inline
#endif

namespace car_owner_basic {
	struct load_record{
		bool car = false;
		bool car_wheels = false;
		bool person = false;
		bool person_age = false;
		bool car_ownership = false;
		bool car_ownership_owner = false;
		bool car_ownership_owned_car = false;
		bool car_ownership_ownership_date = false;
	};

	class car_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;

		uint16_t value;

		explicit constexpr car_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr car_id(const car_id& v) noexcept = default;
		constexpr car_id(car_id&& v) noexcept = default;
		constexpr car_id() noexcept : value(uint16_t(0)) {}

		car_id& operator=(car_id&& v) noexcept = default;
		car_id& operator=(car_id const& v) noexcept = default;
		constexpr bool operator==(car_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(car_id v) const noexcept { return value != v.value; }
		constexpr bool operator<(car_id v) const noexcept { return value < v.value; }
		constexpr bool operator<=(car_id v) const noexcept { return value <= v.value; }
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

	constexpr DCON_RELEASE_INLINE bool is_valid_index(car_id id) { return bool(id); }

	class person_id {
		public:
		using value_base_t = uint8_t;
		using zero_is_null_t = std::true_type;

		uint8_t value;

		explicit constexpr person_id(uint8_t v) noexcept : value(v + 1) {}
		constexpr person_id(const person_id& v) noexcept = default;
		constexpr person_id(person_id&& v) noexcept = default;
		constexpr person_id() noexcept : value(uint8_t(0)) {}

		person_id& operator=(person_id&& v) noexcept = default;
		person_id& operator=(person_id const& v) noexcept = default;
		constexpr bool operator==(person_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(person_id v) const noexcept { return value != v.value; }
		constexpr bool operator<(person_id v) const noexcept { return value < v.value; }
		constexpr bool operator<=(person_id v) const noexcept { return value <= v.value; }
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

	constexpr DCON_RELEASE_INLINE bool is_valid_index(person_id id) { return bool(id); }

	using car_ownership_id = car_id;

}

namespace ve {
		template<>
		struct value_to_vector_type_s<car_owner_basic::car_id> {
			using type = tagged_vector<car_owner_basic::car_id>;
		};
		template<>
		struct value_to_vector_type_s<car_owner_basic::person_id> {
			using type = tagged_vector<car_owner_basic::person_id>;
		};
}

namespace car_owner_basic {
	class data_container;

	namespace internal {
		class alignas(64) car_class {
			private:
			uint32_t size_used = 0;
			struct alignas(64) dtype_wheels { 
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32]; 
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))]; 
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_wheels() { std::uninitialized_value_construct_n(values - 1, (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200)) + 1); }
			} m_wheels;

			public:
			friend class data_container;
		};

		class alignas(64) person_class {
			private:
			uint32_t size_used = 0;
			struct alignas(64) dtype_age { 
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32]; 
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(100) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(100))]; 
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_age() { std::uninitialized_value_construct_n(values - 1, (sizeof(int32_t) <= 64 ? (uint32_t(100) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(100)) + 1); }
			} m_age;

			public:
			friend class data_container;
		};

		class alignas(64) car_ownership_class {
			private:
			uint32_t size_used = 0;
			struct alignas(64) dtype_ownership_date { 
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32]; 
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))]; 
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_ownership_date() { std::uninitialized_value_construct_n(values - 1, (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200)) + 1); }
			} m_ownership_date;
			struct alignas(64) dtype_owner { 
				uint8_t padding[(sizeof(person_id) + 63ui32) & ~63ui32]; 
				person_id values[(sizeof(person_id) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(person_id))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(person_id)) - 1ui32) : uint32_t(1200))]; 
				DCON_RELEASE_INLINE auto vptr() { return values; }
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				dtype_owner() { std::uninitialized_value_construct_n(values - 1, (sizeof(person_id) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(person_id))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(person_id)) - 1ui32) : uint32_t(1200)) + 1); }
			} m_owner;
			struct dtype_array_owner { 
				std::vector<car_ownership_id> values[100]; 
				DCON_RELEASE_INLINE auto vptr() { return values; }
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				dtype_array_owner() {  }
			} m_array_owner;

			public:
			friend class data_container;
		};

	}

	class alignas(64) data_container {
		public:
		internal::car_class car;
		internal::person_class person;
		internal::car_ownership_class car_ownership;

		DCON_RELEASE_INLINE int32_t const& car_get_wheels(car_id id) const noexcept {
			return car.m_wheels.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& car_get_wheels(car_id id) noexcept {
			return car.m_wheels.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_get_wheels(ve::tagged_vector<car_id> id) const noexcept {
			return ve::load(id, car.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE void car_set_wheels(car_id id, int32_t value) noexcept {
			car.m_wheels.vptr()[id.index()] = value;
		}
		DCON_RELEASE_INLINE void car_set_wheels(ve::contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_wheels(ve::partial_contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_set_wheels(ve::tagged_vector<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car.m_wheels.vptr(), values);
		}

		uint32_t car_size() const noexcept { return car.size_used; }

		DCON_RELEASE_INLINE int32_t const& person_get_age(person_id id) const noexcept {
			return person.m_age.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& person_get_age(person_id id) noexcept {
			return person.m_age.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::partial_contiguous_tags<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> person_get_age(ve::tagged_vector<person_id> id) const noexcept {
			return ve::load(id, person.m_age.vptr());
		}
		DCON_RELEASE_INLINE void person_set_age(person_id id, int32_t value) noexcept {
			person.m_age.vptr()[id.index()] = value;
		}
		DCON_RELEASE_INLINE void person_set_age(ve::contiguous_tags<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_age(ve::partial_contiguous_tags<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}
		DCON_RELEASE_INLINE void person_set_age(ve::tagged_vector<person_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, person.m_age.vptr(), values);
		}

		uint32_t person_size() const noexcept { return person.size_used; }

		DCON_RELEASE_INLINE int32_t const& car_ownership_get_ownership_date(car_id id) const noexcept {
			return car_ownership.m_ownership_date.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& car_ownership_get_ownership_date(car_id id) noexcept {
			return car_ownership.m_ownership_date.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::partial_contiguous_tags<car_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> car_ownership_get_ownership_date(ve::tagged_vector<car_id> id) const noexcept {
			return ve::load(id, car_ownership.m_ownership_date.vptr());
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(car_id id, int32_t value) noexcept {
			car_ownership.m_ownership_date.vptr()[id.index()] = value;
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::partial_contiguous_tags<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}
		DCON_RELEASE_INLINE void car_ownership_set_ownership_date(ve::tagged_vector<car_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, car_ownership.m_ownership_date.vptr(), values);
		}

		uint32_t car_ownership_size() const noexcept { return car_ownership.size_used; }

		DCON_RELEASE_INLINE person_id car_ownership_get_owner(car_ownership_id id) const noexcept {
			return car_ownership.m_owner.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE ve::tagged_vector<person_id> car_ownership_get_owner(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<person_id> car_ownership_get_owner(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<person_id> car_ownership_get_owner(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return ve::load(id, car_ownership.m_owner.vptr());
		}
		void car_ownership_set_owner(car_ownership_id id, person_id value) noexcept {
			if(auto old_value = car_ownership.m_owner.vptr()[id.index()]; bool(old_value)) {
				auto& vref = car_ownership.m_array_owner.vptr()[old_value.index()];
				if(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {
					*it = vref.back();
					vref.pop_back();
				}
			}
			if(value)
				car_ownership.m_array_owner.vptr()[value.index()].push_back(id);
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
				return std::pair<car_ownership_id const*, car_ownership_id const*>(&(*vref.begin()), &(*vref.end()));
			} else {
				return std::pair<car_ownership_id const*, car_ownership_id const*>(nullptr, nullptr);
			}
		}
		void person_remove_all_car_ownership_as_owner(person_id id) noexcept {
			auto rng = person_range_of_car_ownership_as_owner(id);
			std::vector<car_ownership_id> temp(rng.first, rng.second);
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
				return std::pair<car_ownership_id const*, car_ownership_id const*>(&(*vref.begin()), &(*vref.end()));
			} else {
				return std::pair<car_ownership_id const*, car_ownership_id const*>(nullptr, nullptr);
			}
		}
		void person_remove_all_car_ownership(person_id id) noexcept {
			auto rng = person_range_of_car_ownership(id);
			std::vector<car_ownership_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](car_ownership_id i) { t->delete_car_ownership(i); });
		}
		DCON_RELEASE_INLINE car_id car_ownership_get_owned_car(car_ownership_id id) const noexcept {
			return id;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_id> car_ownership_get_owned_car(ve::contiguous_tags<car_ownership_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(int32_t i = 0; i < ve::vector_size; ++i)
				result.set(uint32_t(i), id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_id> car_ownership_get_owned_car(ve::partial_contiguous_tags<car_ownership_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(uint32_t i = 0; i < id.subcount; ++i)
				result.set(i, id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_id> car_ownership_get_owned_car(ve::tagged_vector<car_ownership_id> id) const noexcept {
			return id;
		}
		void car_ownership_set_owned_car(car_ownership_id id, car_id value) noexcept {
			if(value) {
				delete_car_ownership(value);
				internal_move_relationship_car_ownership(id, value);
			} else {
				delete_car_ownership(id);
			}
		}
		DCON_RELEASE_INLINE car_ownership_id get_car_ownership_from_car_as_owned_car(car_id id) const noexcept {
			return id;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car_as_owned_car(ve::contiguous_tags<car_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(int32_t i = 0; i < ve::vector_size; ++i)
				result.set(uint32_t(i), id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car_as_owned_car(ve::partial_contiguous_tags<car_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(uint32_t i = 0; i < id.subcount; ++i)
				result.set(i, id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car_as_owned_car(ve::tagged_vector<car_id> id) const noexcept {
			return id;
		}
		DCON_RELEASE_INLINE void car_remove_car_ownership_as_owned_car(car_id id) noexcept {
			if(bool(id))
				delete_car_ownership(id);
		}
		DCON_RELEASE_INLINE car_ownership_id get_car_ownership_from_car(car_id id) const noexcept {
			return id;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car(ve::contiguous_tags<car_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(int32_t i = 0; i < ve::vector_size; ++i)
				result.set(uint32_t(i), id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car(ve::partial_contiguous_tags<car_id> id) const noexcept {
			ve::tagged_vector<car_ownership_id> result;
			for(uint32_t i = 0; i < id.subcount; ++i)
				result.set(i, id[i]);
			return result;
		}
		DCON_RELEASE_INLINE ve::tagged_vector<car_ownership_id> get_car_ownership_from_car(ve::tagged_vector<car_id> id) const noexcept {
			return id;
		}
		DCON_RELEASE_INLINE void car_remove_car_ownership(car_id id) noexcept {
			if(bool(id))
				delete_car_ownership(id);
		}

		void car_pop_back() {
			if(car.size_used > 0) {
				car_id id_removed(car.size_used - 1);
				delete_car_ownership(id_removed);
				car_ownership.size_used = car.size_used - 1;
				car_ownership.m_ownership_date.vptr()[id_removed.index()] = int32_t{};
				car.m_wheels.vptr()[id_removed.index()] = int32_t{};
				--car.size_used;
			}
		}
		void car_resize(uint32_t new_size) {
			if(new_size > 1200) std::abort();
			const uint32_t old_size = car.size_used;
			if(new_size < old_size) {
				std::fill_n(car.m_wheels.vptr() + new_size, old_size - new_size, int32_t{});
			} else {
			}
			car_ownership_resize(new_size);
			car.size_used = new_size;
		}
		car_id create_car() {
			if(car.size_used >= 1200) std::abort();
			car_id new_id(car.size_used);
				car_ownership.size_used = car.size_used + 1;
			++car.size_used;
			return new_id;
		}
		bool is_valid_car(car_id id) const {
			return bool(id) && uint32_t(id.index()) < car.size_used;
		}
		void person_pop_back() {
			if(person.size_used > 0) {
				person_id id_removed(person.size_used - 1);
				person_remove_all_car_ownership_as_owner(id_removed);
				person.m_age.vptr()[id_removed.index()] = int32_t{};
				--person.size_used;
			}
		}
		void person_resize(uint32_t new_size) {
			if(new_size > 100) std::abort();
			const uint32_t old_size = person.size_used;
			if(new_size < old_size) {
				std::fill_n(person.m_age.vptr() + new_size, old_size - new_size, int32_t{});
			} else {
			}
			std::destroy_n(car_ownership.m_array_owner.vptr(), old_size);
			std::uninitialized_default_construct_n(car_ownership.m_array_owner.vptr(), old_size);
			person.size_used = new_size;
		}
		person_id create_person() {
			if(person.size_used >= 100) std::abort();
			person_id new_id(person.size_used);
			++person.size_used;
			return new_id;
		}
		bool is_valid_person(person_id id) const {
			return bool(id) && uint32_t(id.index()) < person.size_used;
		}
		void car_ownership_resize(uint32_t new_size) {
			if(new_size > 1200) std::abort();
			const uint32_t old_size = car_ownership.size_used;
			if(new_size < old_size) {
				std::fill_n(car_ownership.m_ownership_date.vptr() + new_size, old_size - new_size, int32_t{});
			} else {
			}
			std::fill_n(car_ownership.m_owner.vptr(), old_size, person_id());
			car_ownership.size_used = new_size;
		}
		void delete_car_ownership(car_ownership_id id_removed) {
				car_ownership_set_owner(id_removed, person_id());
		}
		bool is_valid_car_ownership(car_ownership_id id) const {
			return bool(id) && uint32_t(id.index()) < car_ownership.size_used && is_valid_car(id) && (bool(car_ownership.m_owner.vptr()[id.index()]) || false);
		}
		private:
		void internal_move_relationship_car_ownership(car_ownership_id old_id, car_ownership_id new_id) {
				car_ownership.m_owner.vptr()[new_id.index()] = car_ownership.m_owner.vptr()[old_id.index()];
				car_ownership.m_owner.vptr()[old_id.index()] = person_id();
				car_ownership.m_ownership_date.vptr()[new_id.index()] = std::move(car_ownership.m_ownership_date.vptr()[old_id.index()]);
				car_ownership.m_ownership_date.vptr()[old_id.index()] = int32_t{};
		}
		public:
		car_ownership_id try_create_car_ownership(person_id owner_p, car_id owned_car_p) {
			if(is_valid_car_ownership(owned_car_p)) return car_ownership_id();
			car_ownership_id new_id = owned_car_p;
				car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}
		car_ownership_id force_create_car_ownership(person_id owner_p, car_id owned_car_p) {
			car_ownership_id new_id = owned_car_p;
				car_ownership_set_owner(new_id, owner_p);
			return new_id;
		}


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


		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.car) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car", "@size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.car_wheels) {
				dcon::record_header header(sizeof(int32_t) * car.size_used, "int32_t", "car", "wheels");
				total_size += header.serialize_size();
				total_size += sizeof(int32_t) * car.size_used;
			}
			if(serialize_selection.person) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "person", "@size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.person_age) {
				dcon::record_header header(sizeof(int32_t) * person.size_used, "int32_t", "person", "age");
				total_size += header.serialize_size();
				total_size += sizeof(int32_t) * person.size_used;
			}
			if(serialize_selection.car_ownership) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car_ownership", "@size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.car_ownership_owner) {
				dcon::record_header header(sizeof(person_id) * car_ownership.size_used, "uint8_t", "car_ownership", "owner");
				total_size += header.serialize_size();
				total_size += sizeof(person_id) * car_ownership.size_used;
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header header(sizeof(int32_t) * car_ownership.size_used, "int32_t", "car_ownership", "ownership_date");
				total_size += header.serialize_size();
				total_size += sizeof(int32_t) * car_ownership.size_used;
			}
			return total_size;
		}
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.car) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car", "@size");
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
			if(serialize_selection.person) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "person", "@size");
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
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "car_ownership", "@size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = car_ownership.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.car_ownership_owner) {
				dcon::record_header header(sizeof(person_id) * car_ownership.size_used, "uint8_t", "car_ownership", "owner");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<person_id*>(output_buffer), car_ownership.m_owner.vptr(), sizeof(person_id) * car_ownership.size_used);
				output_buffer += sizeof(person_id) * car_ownership.size_used;
			}
			if(serialize_selection.car_ownership_ownership_date) {
				dcon::record_header header(sizeof(int32_t) * car_ownership.size_used, "int32_t", "car_ownership", "ownership_date");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), car_ownership.m_ownership_date.vptr(), sizeof(int32_t) * car_ownership.size_used);
				output_buffer += sizeof(int32_t) * car_ownership.size_used;
			}
		}
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
				if(header.is_object("car")) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.car = true;
					}
					else if(header.is_property("wheels")) {
					if(header.is_type("int32_t")) {
						memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					}
				}
				else if(header.is_object("person")) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.person = true;
					}
					else if(header.is_property("age")) {
					if(header.is_type("int32_t")) {
						memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					}
				}
				else if(header.is_object("car_ownership")) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						car_ownership_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.car_ownership = true;
					}
					else if(header.is_property("owner")) {
					if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					}
					else if(header.is_property("owned_car")) {
					if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					}
					else if(header.is_property("ownership_date")) {
					if(header.is_type("int32_t")) {
						memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					}
				}
				}
				input_buffer += header.record_size;
			}
		}
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection, load_record const& mask) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
				if(header.is_object("car") && mask.car) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						car_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.car = true;
					}
					else if(header.is_property("wheels") && mask.car_wheels) {
					if(header.is_type("int32_t")) {
						memcpy(car.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(car.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							car.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
						serialize_selection.car_wheels = true;
					}
					}
				}
				else if(header.is_object("person")) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						person_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.person = true;
					}
					else if(header.is_property("age") && mask.person_age) {
					if(header.is_type("int32_t")) {
						memcpy(person.m_age.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(person.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(person.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							person.m_age.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
						serialize_selection.person_age = true;
					}
					}
				}
				else if(header.is_object("car_ownership")) {
					if(header.is_property("@size") && header.record_size == sizeof(uint32_t)) {
						car_ownership_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
						serialize_selection.car_ownership = true;
					}
					else if(header.is_property("owner") && mask.car_ownership_owner) {
					if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
							person_id temp;
							temp.value = uint8_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
							car_ownership_set_owner(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owner = true;
					}
					}
					else if(header.is_property("owned_car") && mask.car_ownership_owned_car) {
					if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
							car_id temp;
							temp.value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
							car_ownership_set_owned_car(car_ownership_id(uint16_t(i)), temp);
						}
						serialize_selection.car_ownership_owned_car = true;
					}
					}
					else if(header.is_property("ownership_date") && mask.car_ownership_ownership_date) {
					if(header.is_type("int32_t")) {
						memcpy(car_ownership.m_ownership_date.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(car_ownership.size_used) * sizeof(int32_t), header.record_size));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint8_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint16_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint32_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("int64_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("uint64_t")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("float")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(float))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
						serialize_selection.car_ownership_ownership_date = true;
					}
					else if(header.is_type("double")) {
						for(uint32_t i = 0; i < std::min(car_ownership.size_used, uint32_t(header.record_size / sizeof(double))); ++i)
							car_ownership.m_ownership_date.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
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

