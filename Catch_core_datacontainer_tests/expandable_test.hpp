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

namespace ex1 {
	struct load_record {
		bool top : 1;
		bool top_wheels : 1;
		bool bottom : 1;
		bool bottom_legs : 1;
		bool lr_relation : 1;
		bool lr_relation__index : 1;
		bool lr_relation_left : 1;
		bool lr_relation_right : 1;
		bool lr_relation_thingies : 1;
		load_record() {
			top = false;
			top_wheels = false;
			bottom = false;
			bottom_legs = false;
			lr_relation = false;
			lr_relation__index = false;
			lr_relation_left = false;
			lr_relation_right = false;
			lr_relation_thingies = false;
		}
	};
	//
	// definition of strongly typed index for top_id
	//
	class top_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
	
		uint32_t value;
	
		explicit constexpr top_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr top_id(top_id const& v) noexcept = default;
		constexpr top_id(top_id&& v) noexcept = default;
		constexpr top_id() noexcept : value(uint32_t(0)) {}
	
		top_id& operator=(top_id v) noexcept { value = v.value; return *this; }
		constexpr bool operator==(top_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(top_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class top_id_pair {
		public:
		top_id left;
		top_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(top_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for bottom_id
	//
	class bottom_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
	
		uint32_t value;
	
		explicit constexpr bottom_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr bottom_id(bottom_id const& v) noexcept = default;
		constexpr bottom_id(bottom_id&& v) noexcept = default;
		constexpr bottom_id() noexcept : value(uint32_t(0)) {}
	
		bottom_id& operator=(bottom_id v) noexcept { value = v.value; return *this; }
		constexpr bool operator==(bottom_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(bottom_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class bottom_id_pair {
		public:
		bottom_id left;
		bottom_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(bottom_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for lr_relation_id
	//
	class lr_relation_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
	
		uint32_t value;
	
		explicit constexpr lr_relation_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr lr_relation_id(lr_relation_id const& v) noexcept = default;
		constexpr lr_relation_id(lr_relation_id&& v) noexcept = default;
		constexpr lr_relation_id() noexcept : value(uint32_t(0)) {}
	
		lr_relation_id& operator=(lr_relation_id v) noexcept { value = v.value; return *this; }
		constexpr bool operator==(lr_relation_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(lr_relation_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class lr_relation_id_pair {
		public:
		lr_relation_id left;
		lr_relation_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(lr_relation_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<ex1::top_id> {
		using type = tagged_vector<ex1::top_id>;
	};
	
	template<>
	struct value_to_vector_type_s<ex1::bottom_id> {
		using type = tagged_vector<ex1::bottom_id>;
	};
	
	template<>
	struct value_to_vector_type_s<ex1::lr_relation_id> {
		using type = tagged_vector<ex1::lr_relation_id>;
	};
	
}

#endif
namespace ex1 {
	class data_container;

	namespace internal {
		class alignas(64) top_class {
			private:
			//
			// storage space for wheels of type int32_t
			//
			struct alignas(64) dtype_wheels {
				std::vector<int32_t> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_wheels() { values.emplace_back(); }
			}
			m_wheels;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

		class alignas(64) bottom_class {
			private:
			//
			// storage space for legs of type int32_t
			//
			struct alignas(64) dtype_legs {
				std::vector<int32_t> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_legs() { values.emplace_back(); }
			}
			m_legs;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

		class alignas(64) lr_relation_class {
			private:
			//
			// storage space for _index of type lr_relation_id
			//
			struct dtype__index {
				std::vector<lr_relation_id> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype__index() { values.emplace_back(); }
			}
			m__index;
			
			//
			// storage space for thingies of type int32_t
			//
			struct alignas(64) dtype_thingies {
				std::vector<int32_t> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_thingies() { values.emplace_back(); }
			}
			m_thingies;
			
			//
			// storage space for left of type top_id
			//
			struct alignas(64) dtype_left {
				std::vector<top_id> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_left() { values.emplace_back(); }
			}
			m_left;
			
			//
			// storage space for array_left of type std::vector<lr_relation_id>
			//
			struct dtype_array_left {
				std::vector<std::vector<lr_relation_id>> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_array_left() { values.emplace_back(); }
			}
			m_array_left;
			
			//
			// storage space for right of type bottom_id
			//
			struct alignas(64) dtype_right {
				std::vector<bottom_id> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_right() { values.emplace_back(); }
			}
			m_right;
			
			//
			// storage space for array_right of type std::vector<lr_relation_id>
			//
			struct dtype_array_right {
				std::vector<std::vector<lr_relation_id>> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_array_right() { values.emplace_back(); }
			}
			m_array_right;
			
			lr_relation_id first_free = lr_relation_id();
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

	}

	class alignas(64) data_container {
		public:
		internal::top_class top;
		internal::bottom_class bottom;
		internal::lr_relation_class lr_relation;

		//
		// getters for top: wheels
		//
		DCON_RELEASE_INLINE int32_t const& top_get_wheels(top_id id) const noexcept {
			return top.m_wheels.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& top_get_wheels(top_id id) noexcept {
			return top.m_wheels.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> top_get_wheels(ve::unaligned_contiguous_tags<top_id> id) const noexcept {
			return ve::load(id, top.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> top_get_wheels(ve::partial_contiguous_tags<top_id> id) const noexcept {
			return ve::load(id, top.m_wheels.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> top_get_wheels(ve::tagged_vector<top_id> id) const noexcept {
			return ve::load(id, top.m_wheels.vptr());
		}
		#endif
		
		//
		// setters for top: wheels
		//
		DCON_RELEASE_INLINE void top_set_wheels(top_id id, int32_t value) noexcept {
			top.m_wheels.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void top_set_wheels(ve::unaligned_contiguous_tags<top_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, top.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void top_set_wheels(ve::partial_contiguous_tags<top_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, top.m_wheels.vptr(), values);
		}
		DCON_RELEASE_INLINE void top_set_wheels(ve::tagged_vector<top_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, top.m_wheels.vptr(), values);
		}
		#endif
		
		uint32_t top_size() const noexcept { return top.size_used; }

		//
		// getters for bottom: legs
		//
		DCON_RELEASE_INLINE int32_t const& bottom_get_legs(bottom_id id) const noexcept {
			return bottom.m_legs.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& bottom_get_legs(bottom_id id) noexcept {
			return bottom.m_legs.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> bottom_get_legs(ve::unaligned_contiguous_tags<bottom_id> id) const noexcept {
			return ve::load(id, bottom.m_legs.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> bottom_get_legs(ve::partial_contiguous_tags<bottom_id> id) const noexcept {
			return ve::load(id, bottom.m_legs.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> bottom_get_legs(ve::tagged_vector<bottom_id> id) const noexcept {
			return ve::load(id, bottom.m_legs.vptr());
		}
		#endif
		
		//
		// setters for bottom: legs
		//
		DCON_RELEASE_INLINE void bottom_set_legs(bottom_id id, int32_t value) noexcept {
			bottom.m_legs.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void bottom_set_legs(ve::unaligned_contiguous_tags<bottom_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, bottom.m_legs.vptr(), values);
		}
		DCON_RELEASE_INLINE void bottom_set_legs(ve::partial_contiguous_tags<bottom_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, bottom.m_legs.vptr(), values);
		}
		DCON_RELEASE_INLINE void bottom_set_legs(ve::tagged_vector<bottom_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, bottom.m_legs.vptr(), values);
		}
		#endif
		
		uint32_t bottom_size() const noexcept { return bottom.size_used; }

		//
		// getters for lr_relation: thingies
		//
		DCON_RELEASE_INLINE int32_t const& lr_relation_get_thingies(lr_relation_id id) const noexcept {
			return lr_relation.m_thingies.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& lr_relation_get_thingies(lr_relation_id id) noexcept {
			return lr_relation.m_thingies.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> lr_relation_get_thingies(ve::unaligned_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_thingies.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> lr_relation_get_thingies(ve::partial_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_thingies.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> lr_relation_get_thingies(ve::tagged_vector<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_thingies.vptr());
		}
		#endif
		
		//
		// setters for lr_relation: thingies
		//
		DCON_RELEASE_INLINE void lr_relation_set_thingies(lr_relation_id id, int32_t value) noexcept {
			lr_relation.m_thingies.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void lr_relation_set_thingies(ve::unaligned_contiguous_tags<lr_relation_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, lr_relation.m_thingies.vptr(), values);
		}
		DCON_RELEASE_INLINE void lr_relation_set_thingies(ve::partial_contiguous_tags<lr_relation_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, lr_relation.m_thingies.vptr(), values);
		}
		DCON_RELEASE_INLINE void lr_relation_set_thingies(ve::tagged_vector<lr_relation_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, lr_relation.m_thingies.vptr(), values);
		}
		#endif
		
		uint32_t lr_relation_size() const noexcept { return lr_relation.size_used; }

		//
		// many key getters and setters for lr_relation: left
		//
		DCON_RELEASE_INLINE top_id lr_relation_get_left(lr_relation_id id) const noexcept {
			return lr_relation.m_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<top_id> lr_relation_get_left(ve::unaligned_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<top_id> lr_relation_get_left(ve::partial_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<top_id> lr_relation_get_left(ve::tagged_vector<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_left.vptr());
		}
		#endif
		void lr_relation_set_left(lr_relation_id id, top_id value) noexcept {
			if(auto old_value = lr_relation.m_left.vptr()[id.index()]; bool(old_value)) {
				auto& vref = lr_relation.m_array_left.vptr()[old_value.index()];
				if(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {
					*it = vref.back();
					vref.pop_back();
				}
			}
			if(bool(value)) {
				lr_relation.m_array_left.vptr()[value.index()].push_back(id);
			}
			lr_relation.m_left.vptr()[id.index()] = value;
		}
		
		template<typename T>
		DCON_RELEASE_INLINE void top_for_each_lr_relation_as_left(top_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_left.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<lr_relation_id const*, lr_relation_id const*> top_range_of_lr_relation_as_left(top_id id) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_left.vptr()[id.index()];
				return std::pair<lr_relation_id const*, lr_relation_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<lr_relation_id const*, lr_relation_id const*>(nullptr, nullptr);
			}
		}
		void top_remove_all_lr_relation_as_left(top_id id) noexcept {
			auto rng = top_range_of_lr_relation_as_left(id);
			dcon::local_vector<lr_relation_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](lr_relation_id i) { t->delete_lr_relation(i); });
		}
		
		template<typename T>
		DCON_RELEASE_INLINE void top_for_each_lr_relation(top_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_left.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<lr_relation_id const*, lr_relation_id const*> top_range_of_lr_relation(top_id id) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_left.vptr()[id.index()];
				return std::pair<lr_relation_id const*, lr_relation_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<lr_relation_id const*, lr_relation_id const*>(nullptr, nullptr);
			}
		}
		void top_remove_all_lr_relation(top_id id) noexcept {
			auto rng = top_range_of_lr_relation_as_left(id);
			dcon::local_vector<lr_relation_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](lr_relation_id i) { t->delete_lr_relation(i); });
		}
		
		//
		// many key getters and setters for lr_relation: right
		//
		DCON_RELEASE_INLINE bottom_id lr_relation_get_right(lr_relation_id id) const noexcept {
			return lr_relation.m_right.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<bottom_id> lr_relation_get_right(ve::unaligned_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<bottom_id> lr_relation_get_right(ve::partial_contiguous_tags<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_right.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<bottom_id> lr_relation_get_right(ve::tagged_vector<lr_relation_id> id) const noexcept {
			return ve::load(id, lr_relation.m_right.vptr());
		}
		#endif
		void lr_relation_set_right(lr_relation_id id, bottom_id value) noexcept {
			if(auto old_value = lr_relation.m_right.vptr()[id.index()]; bool(old_value)) {
				auto& vref = lr_relation.m_array_right.vptr()[old_value.index()];
				if(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {
					*it = vref.back();
					vref.pop_back();
				}
			}
			if(bool(value)) {
				lr_relation.m_array_right.vptr()[value.index()].push_back(id);
			}
			lr_relation.m_right.vptr()[id.index()] = value;
		}
		
		template<typename T>
		DCON_RELEASE_INLINE void bottom_for_each_lr_relation_as_right(bottom_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_right.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<lr_relation_id const*, lr_relation_id const*> bottom_range_of_lr_relation_as_right(bottom_id id) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_right.vptr()[id.index()];
				return std::pair<lr_relation_id const*, lr_relation_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<lr_relation_id const*, lr_relation_id const*>(nullptr, nullptr);
			}
		}
		void bottom_remove_all_lr_relation_as_right(bottom_id id) noexcept {
			auto rng = bottom_range_of_lr_relation_as_right(id);
			dcon::local_vector<lr_relation_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](lr_relation_id i) { t->delete_lr_relation(i); });
		}
		
		template<typename T>
		DCON_RELEASE_INLINE void bottom_for_each_lr_relation(bottom_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_right.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<lr_relation_id const*, lr_relation_id const*> bottom_range_of_lr_relation(bottom_id id) const {
			if(bool(id)) {
				auto& vref = lr_relation.m_array_right.vptr()[id.index()];
				return std::pair<lr_relation_id const*, lr_relation_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<lr_relation_id const*, lr_relation_id const*>(nullptr, nullptr);
			}
		}
		void bottom_remove_all_lr_relation(bottom_id id) noexcept {
			auto rng = bottom_range_of_lr_relation_as_right(id);
			dcon::local_vector<lr_relation_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](lr_relation_id i) { t->delete_lr_relation(i); });
		}
		

		//
		// convenience getters and setters that operate via an implcit join
		//
		template<typename T>
		void top_for_each_thingies_from_lr_relation(top_id id, T&& func) const {
			top_for_each_lr_relation_as_left(id, [&](lr_relation_id i) {
				func(lr_relation_get_thingies(i));
			} );
		}
		bool top_has_thingies_from_lr_relation(top_id id, int32_t target) const {
			auto& vref = lr_relation.m_array_left.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(lr_relation.m_thingies.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		template<typename T>
		void bottom_for_each_thingies_from_lr_relation(bottom_id id, T&& func) const {
			bottom_for_each_lr_relation_as_right(id, [&](lr_relation_id i) {
				func(lr_relation_get_thingies(i));
			} );
		}
		bool bottom_has_thingies_from_lr_relation(bottom_id id, int32_t target) const {
			auto& vref = lr_relation.m_array_right.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(lr_relation.m_thingies.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		template<typename T>
		void bottom_for_each_left_from_lr_relation(bottom_id id, T&& func) const {
			bottom_for_each_lr_relation_as_right(id, [&](lr_relation_id i) {
				func(lr_relation_get_left(i));
			} );
		}
		bool bottom_has_left_from_lr_relation(bottom_id id, top_id const& target) const {
			auto& vref = lr_relation.m_array_right.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(lr_relation.m_left.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		template<typename T>
		void top_for_each_right_from_lr_relation(top_id id, T&& func) const {
			top_for_each_lr_relation_as_left(id, [&](lr_relation_id i) {
				func(lr_relation_get_right(i));
			} );
		}
		bool top_has_right_from_lr_relation(top_id id, bottom_id const& target) const {
			auto& vref = lr_relation.m_array_left.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(lr_relation.m_right.vptr()[pos->index()] == target) return true;
			}
			return false;
		}
		
		//
		// container pop_back for top
		//
		void top_pop_back() {
			if(top.size_used == 0) return;
			top_id id_removed(top_id::value_base_t(top.size_used - 1));
			top_remove_all_lr_relation_as_left(id_removed);
			lr_relation.m_array_left.values.pop_back();
			top.m_wheels.values.pop_back();
			--top.size_used;
		}
		
		//
		// container resize for top
		//
		void top_resize(uint32_t new_size) {
			const uint32_t old_size = top.size_used;
			if(new_size < old_size) {
				top.m_wheels.values.resize(1 + new_size);
				lr_relation.m_array_left.values.resize(1 + new_size);
				std::destroy_n(lr_relation.m_array_left.vptr() + 0, new_size);
				std::uninitialized_default_construct_n(lr_relation.m_array_left.vptr() + 0, new_size);
				std::fill_n(lr_relation.m_left.vptr() + 0, lr_relation.size_used, top_id{});
			} else if(new_size > old_size) {
				top.m_wheels.values.resize(1 + new_size);
				std::destroy_n(lr_relation.m_array_left.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(lr_relation.m_array_left.vptr() + 0, old_size);
				std::fill_n(lr_relation.m_left.vptr() + 0, lr_relation.size_used, top_id{});
				lr_relation.m_array_left.values.resize(1 + new_size);
			}
			top.size_used = new_size;
		}
		
		//
		// container create for top
		//
		top_id create_top() {
			top_id new_id(top_id::value_base_t(top.size_used));
			lr_relation.m_array_left.values.emplace_back();
			top.m_wheels.values.emplace_back();
			++top.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for top
		//
		void delete_top(top_id id) {
			top_id id_removed = id;
			top_id last_id(top_id::value_base_t(top.size_used - 1));
			if(id_removed == last_id) { top_pop_back(); return; }
			top_remove_all_lr_relation_as_left(id_removed);
			top_for_each_lr_relation_as_left(last_id, [t = this, id_removed](lr_relation_id i){ t->lr_relation.m_left.vptr()[i.index()] = id_removed; });
			lr_relation.m_array_left.vptr()[id_removed.index()] = std::move(lr_relation.m_array_left.vptr()[last_id.index()]);
			lr_relation.m_array_left.values.pop_back();
			top.m_wheels.vptr()[id_removed.index()] = std::move(top.m_wheels.vptr()[last_id.index()]);
			top.m_wheels.values.pop_back();
			--top.size_used;
		}
		
		bool is_valid_top(top_id id) const {
			return bool(id) && uint32_t(id.index()) < top.size_used;
		}
		//
		// container pop_back for bottom
		//
		void bottom_pop_back() {
			if(bottom.size_used == 0) return;
			bottom_id id_removed(bottom_id::value_base_t(bottom.size_used - 1));
			bottom_remove_all_lr_relation_as_right(id_removed);
			lr_relation.m_array_right.values.pop_back();
			bottom.m_legs.values.pop_back();
			--bottom.size_used;
		}
		
		//
		// container resize for bottom
		//
		void bottom_resize(uint32_t new_size) {
			const uint32_t old_size = bottom.size_used;
			if(new_size < old_size) {
				bottom.m_legs.values.resize(1 + new_size);
				lr_relation.m_array_right.values.resize(1 + new_size);
				std::destroy_n(lr_relation.m_array_right.vptr() + 0, new_size);
				std::uninitialized_default_construct_n(lr_relation.m_array_right.vptr() + 0, new_size);
				std::fill_n(lr_relation.m_right.vptr() + 0, lr_relation.size_used, bottom_id{});
			} else if(new_size > old_size) {
				bottom.m_legs.values.resize(1 + new_size);
				std::destroy_n(lr_relation.m_array_right.vptr() + 0, old_size);
				std::uninitialized_default_construct_n(lr_relation.m_array_right.vptr() + 0, old_size);
				std::fill_n(lr_relation.m_right.vptr() + 0, lr_relation.size_used, bottom_id{});
				lr_relation.m_array_right.values.resize(1 + new_size);
			}
			bottom.size_used = new_size;
		}
		
		//
		// container create for bottom
		//
		bottom_id create_bottom() {
			bottom_id new_id(bottom_id::value_base_t(bottom.size_used));
			lr_relation.m_array_right.values.emplace_back();
			bottom.m_legs.values.emplace_back();
			++bottom.size_used;
			return new_id;
		}
		
		bool is_valid_bottom(bottom_id id) const {
			return bool(id) && uint32_t(id.index()) < bottom.size_used;
		}
		//
		// container delete for lr_relation
		//
		void delete_lr_relation(lr_relation_id id_removed) {
			if(!is_valid_lr_relation(id_removed)) return;
			lr_relation.m__index.vptr()[id_removed.index()] = lr_relation.first_free;
			lr_relation.first_free = id_removed;
			if(int32_t(lr_relation.size_used) - 1 == id_removed.index()) {
				for( ; lr_relation.size_used > 0 && lr_relation.m__index.vptr()[lr_relation.size_used - 1] != lr_relation_id(lr_relation_id::value_base_t(lr_relation.size_used - 1));  --lr_relation.size_used) ;
			}
			lr_relation_set_left(id_removed, top_id());
			lr_relation_set_right(id_removed, bottom_id());
			lr_relation.m_thingies.vptr()[id_removed.index()] = int32_t{};
		}
		
		//
		// container resize for lr_relation
		//
		void lr_relation_resize(uint32_t new_size) {
			const uint32_t old_size = lr_relation.size_used;
			if(new_size < old_size) {
				lr_relation.first_free = lr_relation_id();
				lr_relation.m__index.values.resize(new_size + 1);
				int32_t i = int32_t(new_size - 1);
				for(; i >= 0; --i) {
					if(lr_relation.m__index.vptr()[i] != lr_relation_id(lr_relation_id::value_base_t(i))) {
						lr_relation.m__index.vptr()[i] = lr_relation.first_free;
						lr_relation.first_free = lr_relation_id(lr_relation_id::value_base_t(i));
					}
				}
				lr_relation.m_left.values.resize(1 + new_size);
				std::fill_n(lr_relation.m_left.vptr() + 0, new_size, top_id{});
				std::fill_n(lr_relation.m_array_left.vptr() + 0, top.size_used, std::vector<lr_relation_id>{});
				lr_relation.m_right.values.resize(1 + new_size);
				std::fill_n(lr_relation.m_right.vptr() + 0, new_size, bottom_id{});
				std::fill_n(lr_relation.m_array_right.vptr() + 0, bottom.size_used, std::vector<lr_relation_id>{});
				lr_relation.m_thingies.values.resize(1 + new_size);
			} else if(new_size > old_size) {
				lr_relation.first_free = lr_relation_id();
				lr_relation.m__index.values.resize(new_size + 1);
				int32_t i = int32_t(new_size - 1);
				for(; i >= 0; --i) {
					if(lr_relation.m__index.vptr()[i] != lr_relation_id(lr_relation_id::value_base_t(i))) {
						lr_relation.m__index.vptr()[i] = lr_relation.first_free;
						lr_relation.first_free = lr_relation_id(lr_relation_id::value_base_t(i));
					}
				}
				lr_relation.m_thingies.values.resize(1 + new_size);
				lr_relation.m_left.values.resize(1 + new_size);
				lr_relation.m_right.values.resize(1 + new_size);
			}
			lr_relation.size_used = new_size;
		}
		
		//
		// container try create relationship for lr_relation
		//
		lr_relation_id try_create_lr_relation(top_id left_p, bottom_id right_p) {
			lr_relation_id new_id = lr_relation.first_free;
			bool expanded = !bool(lr_relation.first_free );
			if(expanded) {
				new_id = lr_relation_id(lr_relation_id::value_base_t(lr_relation.size_used));
				lr_relation.m__index.values.push_back(new_id);
				lr_relation.m_left.values.emplace_back();
				lr_relation.m_right.values.emplace_back();
				lr_relation.m_thingies.values.emplace_back();
				++lr_relation.size_used;
			} else {
				lr_relation.first_free = lr_relation.m__index.vptr()[lr_relation.first_free.index()];
				lr_relation.m__index.vptr()[new_id.index()] = new_id;
				lr_relation.size_used = std::max(lr_relation.size_used, uint32_t(new_id.index() + 1));
			}
			lr_relation_set_left(new_id, left_p);
			lr_relation_set_right(new_id, right_p);
			return new_id;
		}
		
		//
		// container force create relationship for lr_relation
		//
		lr_relation_id force_create_lr_relation(top_id left_p, bottom_id right_p) {
			lr_relation_id new_id = lr_relation.first_free;
			bool expanded = !bool(lr_relation.first_free );
			if(expanded) {
				new_id = lr_relation_id(lr_relation_id::value_base_t(lr_relation.size_used));
				lr_relation.m__index.values.push_back(new_id);
				lr_relation.m_left.values.emplace_back();
				lr_relation.m_right.values.emplace_back();
				lr_relation.m_thingies.values.emplace_back();
				++lr_relation.size_used;
			} else {
				lr_relation.first_free = lr_relation.m__index.vptr()[lr_relation.first_free.index()];
				lr_relation.m__index.vptr()[new_id.index()] = new_id;
				lr_relation.size_used = std::max(lr_relation.size_used, uint32_t(new_id.index() + 1));
			}
			lr_relation_set_left(new_id, left_p);
			lr_relation_set_right(new_id, right_p);
			return new_id;
		}
		
		bool is_valid_lr_relation(lr_relation_id id) const {
			return bool(id) && uint32_t(id.index()) < lr_relation.size_used && lr_relation.m__index.vptr()[id.index()] == id;
		}
		template <typename T>
		DCON_RELEASE_INLINE void for_each_top(T&& func) {
			for(uint32_t i = 0; i < top.size_used; ++i) {
				top_id tmp(top_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_bottom(T&& func) {
			for(uint32_t i = 0; i < bottom.size_used; ++i) {
				bottom_id tmp(bottom_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_lr_relation(T&& func) {
			for(uint32_t i = 0; i < lr_relation.size_used; ++i) {
				lr_relation_id tmp(lr_relation_id::value_base_t(i));
				if(lr_relation.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		


		void reset() {
			lr_relation_resize(0);
			top_resize(0);
			bottom_resize(0);
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, top_id> top_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, top_id>(top.size_used);
		}
		ve::vectorizable_buffer<int32_t, top_id> top_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, top_id>(top.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_top(F&& functor) {
			ve::execute_serial_unaligned(top.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_top(F&& functor) {
			ve::execute_parallel_unaligned(top.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, bottom_id> bottom_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, bottom_id>(bottom.size_used);
		}
		ve::vectorizable_buffer<int32_t, bottom_id> bottom_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, bottom_id>(bottom.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_bottom(F&& functor) {
			ve::execute_serial_unaligned(bottom.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_bottom(F&& functor) {
			ve::execute_parallel_unaligned(bottom.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, lr_relation_id> lr_relation_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, lr_relation_id>(lr_relation.size_used);
		}
		ve::vectorizable_buffer<int32_t, lr_relation_id> lr_relation_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, lr_relation_id>(lr_relation.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_lr_relation(F&& functor) {
			ve::execute_serial_unaligned(lr_relation.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_lr_relation(F&& functor) {
			ve::execute_parallel_unaligned(lr_relation.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.top = true;
			result.top_wheels = true;
			result.bottom = true;
			result.bottom_legs = true;
			result.lr_relation = true;
			result.lr_relation_left = true;
			result.lr_relation_right = true;
			result.lr_relation__index = true;
			result.lr_relation_thingies = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.top) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "top", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.top_wheels) {
				dcon::record_header iheader(sizeof(int32_t) * top.size_used, "int32_t", "top", "wheels");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * top.size_used;
			}
			if(serialize_selection.bottom) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "bottom", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.bottom_legs) {
				dcon::record_header iheader(sizeof(int32_t) * bottom.size_used, "int32_t", "bottom", "legs");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * bottom.size_used;
			}
			if(serialize_selection.lr_relation) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "lr_relation", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.lr_relation_left) {
					dcon::record_header iheader(sizeof(top_id) * lr_relation.size_used, "uint32_t", "lr_relation", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(top_id) * lr_relation.size_used;
				}
				if(serialize_selection.lr_relation_right) {
					dcon::record_header iheader(sizeof(bottom_id) * lr_relation.size_used, "uint32_t", "lr_relation", "right");
					total_size += iheader.serialize_size();
					total_size += sizeof(bottom_id) * lr_relation.size_used;
				}
				dcon::record_header headerb(0, "$", "lr_relation", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.lr_relation__index) {
				dcon::record_header iheader(sizeof(lr_relation_id) * lr_relation.size_used, "uint32_t", "lr_relation", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(lr_relation_id) * lr_relation.size_used;
			}
			if(serialize_selection.lr_relation_thingies) {
				dcon::record_header iheader(sizeof(int32_t) * lr_relation.size_used, "int32_t", "lr_relation", "thingies");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * lr_relation.size_used;
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.top) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "top", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = top.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.top_wheels) {
				dcon::record_header header(sizeof(int32_t) * top.size_used, "int32_t", "top", "wheels");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), top.m_wheels.vptr(), sizeof(int32_t) * top.size_used);
				output_buffer += sizeof(int32_t) * top.size_used;
			}
			if(serialize_selection.bottom) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "bottom", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = bottom.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.bottom_legs) {
				dcon::record_header header(sizeof(int32_t) * bottom.size_used, "int32_t", "bottom", "legs");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), bottom.m_legs.vptr(), sizeof(int32_t) * bottom.size_used);
				output_buffer += sizeof(int32_t) * bottom.size_used;
			}
			if(serialize_selection.lr_relation) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "lr_relation", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = lr_relation.size_used;
				output_buffer += sizeof(uint32_t);
				{
					dcon::record_header iheader(sizeof(top_id) * lr_relation.size_used, "uint32_t", "lr_relation", "left");
					iheader.serialize(output_buffer);
					memcpy(reinterpret_cast<top_id*>(output_buffer), lr_relation.m_left.vptr(), sizeof(top_id) * lr_relation.size_used);
					output_buffer += sizeof(top_id) * lr_relation.size_used;
				}
				{
					dcon::record_header iheader(sizeof(bottom_id) * lr_relation.size_used, "uint32_t", "lr_relation", "right");
					iheader.serialize(output_buffer);
					memcpy(reinterpret_cast<bottom_id*>(output_buffer), lr_relation.m_right.vptr(), sizeof(bottom_id) * lr_relation.size_used);
					output_buffer += sizeof(bottom_id) * lr_relation.size_used;
				}
				dcon::record_header headerb(0, "$", "lr_relation", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.lr_relation__index) {
				dcon::record_header header(sizeof(lr_relation_id) * lr_relation.size_used, "uint32_t", "lr_relation", "_index");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<lr_relation_id*>(output_buffer), lr_relation.m__index.vptr(), sizeof(lr_relation_id) * lr_relation.size_used);
				output_buffer += sizeof(lr_relation_id) * lr_relation.size_used;
			}
			if(serialize_selection.lr_relation_thingies) {
				dcon::record_header header(sizeof(int32_t) * lr_relation.size_used, "int32_t", "lr_relation", "thingies");
				header.serialize(output_buffer);
				memcpy(reinterpret_cast<int32_t*>(output_buffer), lr_relation.m_thingies.vptr(), sizeof(int32_t) * lr_relation.size_used);
				output_buffer += sizeof(int32_t) * lr_relation.size_used;
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
					if(header.is_object("top")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							top_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.top = true;
						}
						else if(header.is_property("wheels")) {
							if(header.is_type("int32_t")) {
								memcpy(top.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(top.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
						}
					} else
					if(header.is_object("bottom")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							bottom_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.bottom = true;
						}
						else if(header.is_property("legs")) {
							if(header.is_type("int32_t")) {
								memcpy(bottom.m_legs.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(bottom.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
						}
					} else
					if(header.is_object("lr_relation")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= lr_relation.size_used) {
								lr_relation_resize(0);
							}
							lr_relation_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.lr_relation = true;
						}
						else if(header.is_property("__index")) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m__index.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation__index = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation__index = true;
							}
							if(serialize_selection.lr_relation__index == true) {
								lr_relation.size_used = 0;
								lr_relation.first_free = lr_relation_id();
								for(int32_t j = 0 - 1; j > 0; --j) {
									if(lr_relation.m__index.vptr()[j] != lr_relation_id(uint32_t(j))) {
										lr_relation.m__index.vptr()[j] = lr_relation.first_free;
										lr_relation.first_free = lr_relation_id(uint32_t(j));
									} else {
										lr_relation.size_used = std::max(lr_relation.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left")) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m_left.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_left.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_left = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_left.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_left = true;
							}
						}
						else if(header.is_property("right")) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m_right.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_right.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_right = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_right.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_right = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.lr_relation_left == true) {
								for(uint32_t i = 0; i < lr_relation.size_used; ++i) {
									auto tmp = lr_relation.m_left.vptr()[i];
									lr_relation.m_left.vptr()[i] = top_id();
									lr_relation_set_left(lr_relation_id(lr_relation_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.lr_relation_right == true) {
								for(uint32_t i = 0; i < lr_relation.size_used; ++i) {
									auto tmp = lr_relation.m_right.vptr()[i];
									lr_relation.m_right.vptr()[i] = bottom_id();
									lr_relation_set_right(lr_relation_id(lr_relation_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("thingies")) {
							if(header.is_type("int32_t")) {
								memcpy(lr_relation.m_thingies.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
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
					if(header.is_object("top") && mask.top) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							top_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.top = true;
						}
						else if(header.is_property("wheels") && mask.top_wheels) {
							if(header.is_type("int32_t")) {
								memcpy(top.m_wheels.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(top.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(top.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									top.m_wheels.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.top_wheels = true;
							}
						}
					} else
					if(header.is_object("bottom") && mask.bottom) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							bottom_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.bottom = true;
						}
						else if(header.is_property("legs") && mask.bottom_legs) {
							if(header.is_type("int32_t")) {
								memcpy(bottom.m_legs.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(bottom.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(bottom.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									bottom.m_legs.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.bottom_legs = true;
							}
						}
					} else
					if(header.is_object("lr_relation") && mask.lr_relation) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= lr_relation.size_used) {
								lr_relation_resize(0);
							}
							lr_relation_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.lr_relation = true;
						}
						else if(header.is_property("__index") && mask.lr_relation__index) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m__index.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation__index = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation__index = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation__index = true;
							}
							if(serialize_selection.lr_relation__index == true) {
								lr_relation.size_used = 0;
								lr_relation.first_free = lr_relation_id();
								for(int32_t j = 0 - 1; j > 0; --j) {
									if(lr_relation.m__index.vptr()[j] != lr_relation_id(uint32_t(j))) {
										lr_relation.m__index.vptr()[j] = lr_relation.first_free;
										lr_relation.first_free = lr_relation_id(uint32_t(j));
									} else {
										lr_relation.size_used = std::max(lr_relation.size_used, uint32_t(j));
									}
								}
							}
						}
						else if(header.is_property("left") && mask.lr_relation_left) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m_left.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_left.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_left = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_left.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_left = true;
							}
						}
						else if(header.is_property("right") && mask.lr_relation_right) {
							if(header.is_type("uint32_t")) {
								memcpy(lr_relation.m_right.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(uint32_t), header.record_size));
								serialize_selection.lr_relation_right = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_right.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_right = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_right.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_right = true;
							}
						}
						else if(header.is_property("$index_end") && mask.lr_relation) {
							if(serialize_selection.lr_relation_left == true) {
								for(uint32_t i = 0; i < lr_relation.size_used; ++i) {
									auto tmp = lr_relation.m_left.vptr()[i];
									lr_relation.m_left.vptr()[i] = top_id();
									lr_relation_set_left(lr_relation_id(lr_relation_id::value_base_t(i)), tmp);
								}
							}
							if(serialize_selection.lr_relation_right == true) {
								for(uint32_t i = 0; i < lr_relation.size_used; ++i) {
									auto tmp = lr_relation.m_right.vptr()[i];
									lr_relation.m_right.vptr()[i] = bottom_id();
									lr_relation_set_right(lr_relation_id(lr_relation_id::value_base_t(i)), tmp);
								}
							}
						}
						else if(header.is_property("thingies") && mask.lr_relation_thingies) {
							if(header.is_type("int32_t")) {
								memcpy(lr_relation.m_thingies.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(lr_relation.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(lr_relation.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									lr_relation.m_thingies.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.lr_relation_thingies = true;
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

