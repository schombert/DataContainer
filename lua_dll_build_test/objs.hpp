#pragma once

//
// This file was automatically generated from: C:\VSProjects\DataContainer\lua_dll_build_test\objs.txt
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

namespace fif { std::string container_interface(); }

namespace dcon {
	struct load_record {
		bool thingy : 1;
		bool thingy_some_value : 1;
		bool thingy_bf_value : 1;
		bool thingy_lua_value : 1;
		bool thingy_pooled_v : 1;
		bool thingy_big_array : 1;
		bool thingy_big_array_bf : 1;
		bool pop : 1;
		bool pop__index : 1;
		bool negotiation : 1;
		bool negotiation__index : 1;
		bool negotiation_initiator : 1;
		bool negotiation_target : 1;
		load_record() {
			thingy = false;
			thingy_some_value = false;
			thingy_bf_value = false;
			thingy_lua_value = false;
			thingy_pooled_v = false;
			thingy_big_array = false;
			thingy_big_array_bf = false;
			pop = false;
			pop__index = false;
			negotiation = false;
			negotiation__index = false;
			negotiation_initiator = false;
			negotiation_target = false;
		}
	};
	//
	// definition of strongly typed index for thingy_id
	//
	class thingy_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
		
		uint32_t value = 0;
		
		constexpr thingy_id() noexcept = default;
		explicit constexpr thingy_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr thingy_id(thingy_id const& v) noexcept = default;
		constexpr thingy_id(thingy_id&& v) noexcept = default;
		
		thingy_id& operator=(thingy_id const& v) noexcept = default;
		thingy_id& operator=(thingy_id&& v) noexcept = default;
		constexpr bool operator==(thingy_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingy_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class thingy_id_pair {
		public:
		thingy_id left;
		thingy_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(thingy_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for pop_id
	//
	class pop_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
		
		uint32_t value = 0;
		
		constexpr pop_id() noexcept = default;
		explicit constexpr pop_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr pop_id(pop_id const& v) noexcept = default;
		constexpr pop_id(pop_id&& v) noexcept = default;
		
		pop_id& operator=(pop_id const& v) noexcept = default;
		pop_id& operator=(pop_id&& v) noexcept = default;
		constexpr bool operator==(pop_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(pop_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
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
	// definition of strongly typed index for negotiation_id
	//
	class negotiation_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr negotiation_id() noexcept = default;
		explicit constexpr negotiation_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr negotiation_id(negotiation_id const& v) noexcept = default;
		constexpr negotiation_id(negotiation_id&& v) noexcept = default;
		
		negotiation_id& operator=(negotiation_id const& v) noexcept = default;
		negotiation_id& operator=(negotiation_id&& v) noexcept = default;
		constexpr bool operator==(negotiation_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(negotiation_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class negotiation_id_pair {
		public:
		negotiation_id left;
		negotiation_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(negotiation_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::thingy_id> {
		using type = ::ve::tagged_vector<dcon::thingy_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::pop_id> {
		using type = ::ve::tagged_vector<dcon::pop_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::negotiation_id> {
		using type = ::ve::tagged_vector<dcon::negotiation_id>;
	};
	
}

#endif
namespace dcon {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class const_object_iterator_thingy;
		class object_iterator_thingy;

		class alignas(64) thingy_class {
			friend const_object_iterator_thingy;
			friend object_iterator_thingy;
			friend std::string fif::container_interface();
			private:
			//
			// storage space for some_value of type int32_t
			//
			struct alignas(64) dtype_some_value {
				std::vector<int32_t> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_some_value() { values.emplace_back(); }
			}
			m_some_value;
			
			//
			// storage space for bf_value of type dcon::bitfield_type
			//
			struct alignas(64) dtype_bf_value {
				std::vector<dcon::bitfield_type> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_bf_value() { values.emplace_back(); }
			}
			m_bf_value;
			
			//
			// storage space for lua_value of type lua_reference_type
			//
			struct alignas(64) dtype_lua_value {
				std::vector<lua_reference_type> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_lua_value() { values.emplace_back(); }
			}
			m_lua_value;
			
			//
			// storage space for pooled_v of type dcon::stable_mk_2_tag
			//
			struct alignas(64) dtype_pooled_v {
				std::vector<dcon::stable_mk_2_tag> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_pooled_v() { values.push_back( std::numeric_limits<dcon::stable_mk_2_tag>::max() ); }
			}
			m_pooled_v;
			
			dcon::stable_variable_vector_storage_mk_2<int16_t, 16, 1000 > pooled_v_storage;
			//
			// storage space for big_array of type array of float
			//
			struct dtype_big_array {
				std::vector<std::vector<float>> values;
				uint32_t size = 0;
				DCON_RELEASE_INLINE auto vptr(int32_t i) const { return values[i].data() + 1; }
				DCON_RELEASE_INLINE auto vptr(int32_t i) { return values[i].data() + 1; }
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t container_size) {
					values.resize(sz + 1);
					for(uint32_t i = size; i < sz + 1; ++i) values[i].resize(container_size + 1);
					size = sz;
				}
				DCON_RELEASE_INLINE void emplace_back_all(uint32_t) {
					for(auto& v : values) v.emplace_back();
				}
				DCON_RELEASE_INLINE void copy_value(int32_t dest, int32_t source) {
					for(auto& v : values) {
						v[1 + dest] = v[1 + source];
					}
				}
				DCON_RELEASE_INLINE void pop_back_all(uint32_t) {
					for(auto& v : values) {
						v.pop_back();
					}
				}
				DCON_RELEASE_INLINE void zero_at(int32_t dest) {
					for(auto& v : values) {
						v[1 + dest] = float{};
					}
				}
			}
			m_big_array;
			
			//
			// storage space for big_array_bf of type array of dcon::bitfield_type
			//
			struct dtype_big_array_bf {
				std::vector<std::vector<dcon::bitfield_type>> values;
				uint32_t size = 0;
				DCON_RELEASE_INLINE auto vptr(int32_t i) const { return values[i].data() + 1; }
				DCON_RELEASE_INLINE auto vptr(int32_t i) { return values[i].data() + 1; }
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t container_size) {
					values.resize(sz + 1);
					for(uint32_t i = size; i < sz + 1; ++i) values[i].resize((container_size + 7) / 8 + 1);
					size = sz;
				}
				DCON_RELEASE_INLINE void emplace_back_all(uint32_t newsz) {
					for(auto& v : values) {
						v.resize(1 + (newsz + 7) / 8);
					}
				}
				DCON_RELEASE_INLINE void copy_value(int32_t dest, int32_t source) {
					for(int32_t i = 1; i < int32_t(size + 1); ++i) {
						dcon::bit_vector_set(vptr(i), dest, dcon::bit_vector_test(vptr(i), source));
					}
				}
				DCON_RELEASE_INLINE void pop_back_all(uint32_t vsize) {
					for(auto& v : values) {
						v.resize(1 + (vsize + 6) / 8);
					}
				}
				DCON_RELEASE_INLINE void zero_at(int32_t dest) {
					for(int32_t i = 0; i < int32_t(size + 1); ++i) {
						dcon::bit_vector_set(vptr(i), dest, false);
					}
				}
			}
			m_big_array_bf;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class const_object_iterator_pop;
		class object_iterator_pop;

		class alignas(64) pop_class {
			friend const_object_iterator_pop;
			friend object_iterator_pop;
			friend std::string fif::container_interface();
			private:
			//
			// storage space for _index of type pop_id
			//
			struct dtype__index {
				pop_id values[300000];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 300000); }
			}
			m__index;
			
			pop_id first_free = pop_id();
			uint32_t size_used = 0;


			public:
			pop_class() {
				for(int32_t i = 300000 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = pop_id(uint32_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_negotiation;
		class object_iterator_negotiation;
		class const_iterator_pop_foreach_negotiation_as_initiator;
		class iterator_pop_foreach_negotiation_as_initiator;
		struct const_iterator_pop_foreach_negotiation_as_initiator_generator;
		struct iterator_pop_foreach_negotiation_as_initiator_generator;
		class const_iterator_pop_foreach_negotiation_as_target;
		class iterator_pop_foreach_negotiation_as_target;
		struct const_iterator_pop_foreach_negotiation_as_target_generator;
		struct iterator_pop_foreach_negotiation_as_target_generator;

		class alignas(64) negotiation_class {
			friend const_object_iterator_negotiation;
			friend object_iterator_negotiation;
			friend std::string fif::container_interface();
			friend const_iterator_pop_foreach_negotiation_as_initiator;
			friend iterator_pop_foreach_negotiation_as_initiator;
			friend const_iterator_pop_foreach_negotiation_as_target;
			friend iterator_pop_foreach_negotiation_as_target;
			private:
			//
			// storage space for _index of type negotiation_id
			//
			struct dtype__index {
				negotiation_id values[2500];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 2500); }
			}
			m__index;
			
			//
			// storage space for initiator of type pop_id
			//
			struct alignas(64) dtype_initiator {
				uint8_t padding[(63 + sizeof(pop_id)) & ~uint64_t(63)];
				pop_id values[(sizeof(pop_id) <= 64 ? (uint32_t(2500) + (uint32_t(64) / uint32_t(sizeof(pop_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(pop_id)) - uint32_t(1)) : uint32_t(2500))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_initiator() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(pop_id) <= 64 ? (uint32_t(2500) + (uint32_t(64) / uint32_t(sizeof(pop_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(pop_id)) - uint32_t(1)) : uint32_t(2500))); }
			}
			m_initiator;
			
			//
			// storage space for link_initiator of type negotiation_id_pair
			//
			struct dtype_link_initiator {
				negotiation_id_pair values[2500];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_initiator() { std::uninitialized_value_construct_n(values, 2500); }
			}
			m_link_initiator;
			
			//
			// storage space for head_back_initiator of type negotiation_id
			//
			struct alignas(64) dtype_head_back_initiator {
				uint8_t padding[(63 + sizeof(negotiation_id)) & ~uint64_t(63)];
				negotiation_id values[(sizeof(negotiation_id) <= 64 ? (uint32_t(300000) + (uint32_t(64) / uint32_t(sizeof(negotiation_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(negotiation_id)) - uint32_t(1)) : uint32_t(300000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_head_back_initiator() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(negotiation_id) <= 64 ? (uint32_t(300000) + (uint32_t(64) / uint32_t(sizeof(negotiation_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(negotiation_id)) - uint32_t(1)) : uint32_t(300000))); }
			}
			m_head_back_initiator;
			
			//
			// storage space for target of type pop_id
			//
			struct alignas(64) dtype_target {
				uint8_t padding[(63 + sizeof(pop_id)) & ~uint64_t(63)];
				pop_id values[(sizeof(pop_id) <= 64 ? (uint32_t(2500) + (uint32_t(64) / uint32_t(sizeof(pop_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(pop_id)) - uint32_t(1)) : uint32_t(2500))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_target() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(pop_id) <= 64 ? (uint32_t(2500) + (uint32_t(64) / uint32_t(sizeof(pop_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(pop_id)) - uint32_t(1)) : uint32_t(2500))); }
			}
			m_target;
			
			//
			// storage space for link_target of type negotiation_id_pair
			//
			struct dtype_link_target {
				negotiation_id_pair values[2500];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_target() { std::uninitialized_value_construct_n(values, 2500); }
			}
			m_link_target;
			
			//
			// storage space for head_back_target of type negotiation_id
			//
			struct alignas(64) dtype_head_back_target {
				uint8_t padding[(63 + sizeof(negotiation_id)) & ~uint64_t(63)];
				negotiation_id values[(sizeof(negotiation_id) <= 64 ? (uint32_t(300000) + (uint32_t(64) / uint32_t(sizeof(negotiation_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(negotiation_id)) - uint32_t(1)) : uint32_t(300000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_head_back_target() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(negotiation_id) <= 64 ? (uint32_t(300000) + (uint32_t(64) / uint32_t(sizeof(negotiation_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(negotiation_id)) - uint32_t(1)) : uint32_t(300000))); }
			}
			m_head_back_target;
			
			negotiation_id first_free = negotiation_id();
			uint32_t size_used = 0;


			public:
			negotiation_class() {
				for(int32_t i = 2500 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = negotiation_id(uint16_t(i));
				}
			}
			friend data_container;
		};

	}

	class thingy_const_fat_id;
	class thingy_fat_id;
	class pop_const_fat_id;
	class pop_fat_id;
	class negotiation_const_fat_id;
	class negotiation_fat_id;
	class thingy_fat_id {
		friend data_container;
		public:
		data_container& container;
		thingy_id id;
		thingy_fat_id(data_container& c, thingy_id i) noexcept : container(c), id(i) {}
		thingy_fat_id(thingy_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingy_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingy_fat_id& operator=(thingy_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy_fat_id& operator=(thingy_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingy_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_some_value() const noexcept;
		DCON_RELEASE_INLINE void set_some_value(int32_t v) const noexcept;
		DCON_RELEASE_INLINE bool get_bf_value() const noexcept;
		DCON_RELEASE_INLINE void set_bf_value(bool v) const noexcept;
		DCON_RELEASE_INLINE lua_reference_type& get_lua_value() const noexcept;
		DCON_RELEASE_INLINE void set_lua_value(lua_reference_type const& v) const noexcept;
		DCON_RELEASE_INLINE dcon::dcon_vv_fat_id<int16_t> get_pooled_v() const noexcept;
		DCON_RELEASE_INLINE float& get_big_array(thingy_id i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_size() const noexcept;
		DCON_RELEASE_INLINE void set_big_array(thingy_id i, float v) const noexcept;
		DCON_RELEASE_INLINE void resize_big_array(uint32_t sz) const noexcept;
		DCON_RELEASE_INLINE bool get_big_array_bf(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_bf_size() const noexcept;
		DCON_RELEASE_INLINE void set_big_array_bf(int32_t i, bool v) const noexcept;
		DCON_RELEASE_INLINE void resize_big_array_bf(uint32_t sz) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE thingy_fat_id fatten(data_container& c, thingy_id id) noexcept {
		return thingy_fat_id(c, id);
	}
	
	class thingy_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		thingy_id id;
		thingy_const_fat_id(data_container const& c, thingy_id i) noexcept : container(c), id(i) {}
		thingy_const_fat_id(thingy_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		thingy_const_fat_id(thingy_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingy_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingy_const_fat_id& operator=(thingy_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy_const_fat_id& operator=(thingy_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy_const_fat_id& operator=(thingy_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingy_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_some_value() const noexcept;
		DCON_RELEASE_INLINE bool get_bf_value() const noexcept;
		DCON_RELEASE_INLINE lua_reference_type const& get_lua_value() const noexcept;
		DCON_RELEASE_INLINE dcon::dcon_vv_const_fat_id<int16_t> get_pooled_v() const noexcept;
		DCON_RELEASE_INLINE float get_big_array(thingy_id i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_size() const noexcept;
		DCON_RELEASE_INLINE bool get_big_array_bf(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_bf_size() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(thingy_fat_id const& l, thingy_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(thingy_fat_id const& l, thingy_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE thingy_const_fat_id fatten(data_container const& c, thingy_id id) noexcept {
		return thingy_const_fat_id(c, id);
	}
	
	class pop_fat_id {
		friend data_container;
		public:
		data_container& container;
		pop_id id;
		pop_fat_id(data_container& c, pop_id i) noexcept : container(c), id(i) {}
		pop_fat_id(pop_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator pop_id() const noexcept { return id; }
		DCON_RELEASE_INLINE pop_fat_id& operator=(pop_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE pop_fat_id& operator=(pop_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(pop_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(pop_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(pop_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(pop_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		template<typename T>
		DCON_RELEASE_INLINE void for_each_negotiation_as_initiator(T&& func) const;
		DCON_RELEASE_INLINE void remove_all_negotiation_as_initiator() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_initiator_generator get_negotiation_as_initiator() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_negotiation_as_target(T&& func) const;
		DCON_RELEASE_INLINE void remove_all_negotiation_as_target() const noexcept;
		DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_target_generator get_negotiation_as_target() const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE pop_fat_id fatten(data_container& c, pop_id id) noexcept {
		return pop_fat_id(c, id);
	}
	
	class pop_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		pop_id id;
		pop_const_fat_id(data_container const& c, pop_id i) noexcept : container(c), id(i) {}
		pop_const_fat_id(pop_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		pop_const_fat_id(pop_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator pop_id() const noexcept { return id; }
		DCON_RELEASE_INLINE pop_const_fat_id& operator=(pop_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE pop_const_fat_id& operator=(pop_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE pop_const_fat_id& operator=(pop_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(pop_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(pop_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(pop_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(pop_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(pop_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(pop_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		template<typename T>
		DCON_RELEASE_INLINE void for_each_negotiation_as_initiator(T&& func) const;
		DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_initiator_generator get_negotiation_as_initiator() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_negotiation_as_target(T&& func) const;
		DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_target_generator get_negotiation_as_target() const;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(pop_fat_id const& l, pop_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(pop_fat_id const& l, pop_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE pop_const_fat_id fatten(data_container const& c, pop_id id) noexcept {
		return pop_const_fat_id(c, id);
	}
	
	class negotiation_fat_id {
		friend data_container;
		public:
		data_container& container;
		negotiation_id id;
		negotiation_fat_id(data_container& c, negotiation_id i) noexcept : container(c), id(i) {}
		negotiation_fat_id(negotiation_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator negotiation_id() const noexcept { return id; }
		DCON_RELEASE_INLINE negotiation_fat_id& operator=(negotiation_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE negotiation_fat_id& operator=(negotiation_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(negotiation_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(negotiation_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(negotiation_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(negotiation_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE pop_fat_id get_initiator() const noexcept;
		DCON_RELEASE_INLINE void set_initiator(pop_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_initiator(pop_id val) const noexcept;
		DCON_RELEASE_INLINE pop_fat_id get_target() const noexcept;
		DCON_RELEASE_INLINE void set_target(pop_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_target(pop_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE negotiation_fat_id fatten(data_container& c, negotiation_id id) noexcept {
		return negotiation_fat_id(c, id);
	}
	
	class negotiation_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		negotiation_id id;
		negotiation_const_fat_id(data_container const& c, negotiation_id i) noexcept : container(c), id(i) {}
		negotiation_const_fat_id(negotiation_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		negotiation_const_fat_id(negotiation_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator negotiation_id() const noexcept { return id; }
		DCON_RELEASE_INLINE negotiation_const_fat_id& operator=(negotiation_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE negotiation_const_fat_id& operator=(negotiation_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE negotiation_const_fat_id& operator=(negotiation_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(negotiation_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(negotiation_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(negotiation_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(negotiation_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(negotiation_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(negotiation_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE pop_const_fat_id get_initiator() const noexcept;
		DCON_RELEASE_INLINE pop_const_fat_id get_target() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(negotiation_fat_id const& l, negotiation_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(negotiation_fat_id const& l, negotiation_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE negotiation_const_fat_id fatten(data_container const& c, negotiation_id id) noexcept {
		return negotiation_const_fat_id(c, id);
	}
	
	namespace internal {
		class object_iterator_thingy {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_thingy(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_thingy& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_thingy& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_thingy const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_thingy const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingy_fat_id operator*() const noexcept {
				return thingy_fat_id(container, thingy_id(thingy_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_thingy& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_thingy& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_thingy operator+(int32_t n) const noexcept {
				return object_iterator_thingy(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_thingy operator-(int32_t n) const noexcept {
				return object_iterator_thingy(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_thingy const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_thingy const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_thingy const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_thingy const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_thingy const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE thingy_fat_id operator[](int32_t n) const noexcept {
				return thingy_fat_id(container, thingy_id(thingy_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_thingy {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_thingy(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingy& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_thingy& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_thingy const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_thingy const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE thingy_const_fat_id operator*() const noexcept {
				return thingy_const_fat_id(container, thingy_id(thingy_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_thingy& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_thingy& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_thingy operator+(int32_t n) const noexcept {
				return const_object_iterator_thingy(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_thingy operator-(int32_t n) const noexcept {
				return const_object_iterator_thingy(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_thingy const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_thingy const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_thingy const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_thingy const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_thingy const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE thingy_const_fat_id operator[](int32_t n) const noexcept {
				return thingy_const_fat_id(container, thingy_id(thingy_id::value_base_t(int32_t(index) + n)));
			}
		};
		
		class object_iterator_pop {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_pop(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_pop& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_pop& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_pop const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_pop const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE pop_fat_id operator*() const noexcept {
				return pop_fat_id(container, pop_id(pop_id::value_base_t(index)));
			}
		};
		class const_object_iterator_pop {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_pop(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_pop& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_pop& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_pop const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_pop const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE pop_const_fat_id operator*() const noexcept {
				return pop_const_fat_id(container, pop_id(pop_id::value_base_t(index)));
			}
		};
		
		class iterator_pop_foreach_negotiation_as_initiator {
			private:
			data_container& container;
			negotiation_id list_pos;
			public:
			iterator_pop_foreach_negotiation_as_initiator(data_container& c, pop_id fr) noexcept;
			iterator_pop_foreach_negotiation_as_initiator(data_container& c, negotiation_id r) noexcept : container(c), list_pos(r) {}
			iterator_pop_foreach_negotiation_as_initiator(data_container& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_pop_foreach_negotiation_as_initiator const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_pop_foreach_negotiation_as_initiator const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_fat_id operator*() const noexcept {
				return negotiation_fat_id(container, list_pos);
			}
		};
		class const_iterator_pop_foreach_negotiation_as_initiator {
			private:
			data_container const& container;
			negotiation_id list_pos;
			public:
			const_iterator_pop_foreach_negotiation_as_initiator(data_container const& c, pop_id fr) noexcept;
			const_iterator_pop_foreach_negotiation_as_initiator(data_container const& c, negotiation_id r) noexcept : container(c), list_pos(r) {}
			const_iterator_pop_foreach_negotiation_as_initiator(data_container const& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_pop_foreach_negotiation_as_initiator const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_pop_foreach_negotiation_as_initiator const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_const_fat_id operator*() const noexcept {
				return negotiation_const_fat_id(container, list_pos);
			}
		};
		
		struct iterator_pop_foreach_negotiation_as_initiator_generator {
			data_container& container;
			pop_id ob;
			iterator_pop_foreach_negotiation_as_initiator_generator(data_container& c, pop_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator begin() const noexcept {
				return iterator_pop_foreach_negotiation_as_initiator(container, ob);
			}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator end() const noexcept {
				return iterator_pop_foreach_negotiation_as_initiator(container);
			}
		};
		struct const_iterator_pop_foreach_negotiation_as_initiator_generator {
			data_container const& container;
			pop_id ob;
			const_iterator_pop_foreach_negotiation_as_initiator_generator(data_container const& c, pop_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator begin() const noexcept {
				return const_iterator_pop_foreach_negotiation_as_initiator(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator end() const noexcept {
				return const_iterator_pop_foreach_negotiation_as_initiator(container);
			}
		};
		
		class iterator_pop_foreach_negotiation_as_target {
			private:
			data_container& container;
			negotiation_id list_pos;
			public:
			iterator_pop_foreach_negotiation_as_target(data_container& c, pop_id fr) noexcept;
			iterator_pop_foreach_negotiation_as_target(data_container& c, negotiation_id r) noexcept : container(c), list_pos(r) {}
			iterator_pop_foreach_negotiation_as_target(data_container& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target& operator++() noexcept;
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(iterator_pop_foreach_negotiation_as_target const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(iterator_pop_foreach_negotiation_as_target const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_fat_id operator*() const noexcept {
				return negotiation_fat_id(container, list_pos);
			}
		};
		class const_iterator_pop_foreach_negotiation_as_target {
			private:
			data_container const& container;
			negotiation_id list_pos;
			public:
			const_iterator_pop_foreach_negotiation_as_target(data_container const& c, pop_id fr) noexcept;
			const_iterator_pop_foreach_negotiation_as_target(data_container const& c, negotiation_id r) noexcept : container(c), list_pos(r) {}
			const_iterator_pop_foreach_negotiation_as_target(data_container const& c) noexcept : container(c) {}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target& operator++() noexcept;
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_iterator_pop_foreach_negotiation_as_target const& o) const noexcept {
				return list_pos == o.list_pos;
			}
			DCON_RELEASE_INLINE bool operator!=(const_iterator_pop_foreach_negotiation_as_target const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_const_fat_id operator*() const noexcept {
				return negotiation_const_fat_id(container, list_pos);
			}
		};
		
		struct iterator_pop_foreach_negotiation_as_target_generator {
			data_container& container;
			pop_id ob;
			iterator_pop_foreach_negotiation_as_target_generator(data_container& c, pop_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target begin() const noexcept {
				return iterator_pop_foreach_negotiation_as_target(container, ob);
			}
			DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target end() const noexcept {
				return iterator_pop_foreach_negotiation_as_target(container);
			}
		};
		struct const_iterator_pop_foreach_negotiation_as_target_generator {
			data_container const& container;
			pop_id ob;
			const_iterator_pop_foreach_negotiation_as_target_generator(data_container const& c, pop_id o) : container(c), ob(o) {}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target begin() const noexcept {
				return const_iterator_pop_foreach_negotiation_as_target(container, ob);
			}
			DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target end() const noexcept {
				return const_iterator_pop_foreach_negotiation_as_target(container);
			}
		};
		
		class object_iterator_negotiation {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_negotiation(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_negotiation& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_negotiation& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_negotiation const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_negotiation const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_fat_id operator*() const noexcept {
				return negotiation_fat_id(container, negotiation_id(negotiation_id::value_base_t(index)));
			}
		};
		class const_object_iterator_negotiation {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_negotiation(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_negotiation& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_negotiation& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_negotiation const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_negotiation const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE negotiation_const_fat_id operator*() const noexcept {
				return negotiation_const_fat_id(container, negotiation_id(negotiation_id::value_base_t(index)));
			}
		};
		
	}

	class alignas(64) data_container {
		public:
		internal::thingy_class thingy;
		internal::pop_class pop;
		internal::negotiation_class negotiation;

		//
		// Functions for thingy:
		//
		//
		// accessors for thingy: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingy_get_some_value(thingy_id id) const noexcept {
			return thingy.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingy_get_some_value(thingy_id id) noexcept {
			return thingy.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::unaligned_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_some_value(thingy_id id, int32_t value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			thingy.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_some_value(ve::unaligned_contiguous_tags<thingy_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_some_value(ve::partial_contiguous_tags<thingy_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_some_value(ve::tagged_vector<thingy_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy.m_some_value.vptr(), values);
		}
		#endif
		//
		// accessors for thingy: bf_value
		//
		DCON_RELEASE_INLINE bool thingy_get_bf_value(thingy_id id) const noexcept {
			return dcon::bit_vector_test(thingy.m_bf_value.vptr(), id.index());
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::unaligned_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_bf_value(thingy_id id, bool value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id.index(), value);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_bf_value(ve::unaligned_contiguous_tags<thingy_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_bf_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_bf_value(ve::partial_contiguous_tags<thingy_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_bf_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_bf_value(ve::tagged_vector<thingy_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_bf_value.vptr(), values);
		}
		#endif
		//
		// accessors for thingy: lua_value
		//
		DCON_RELEASE_INLINE lua_reference_type const& thingy_get_lua_value(thingy_id id) const noexcept {
			return thingy.m_lua_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE lua_reference_type& thingy_get_lua_value(thingy_id id) noexcept {
			return thingy.m_lua_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE void thingy_set_lua_value(thingy_id id, lua_reference_type const& value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			thingy.m_lua_value.vptr()[id.index()] = value;
		}
		//
		// accessors for thingy: pooled_v
		//
		DCON_RELEASE_INLINE dcon::dcon_vv_const_fat_id<int16_t> thingy_get_pooled_v(thingy_id id) const noexcept {
			return dcon::dcon_vv_const_fat_id<int16_t>(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		DCON_RELEASE_INLINE dcon::dcon_vv_fat_id<int16_t> thingy_get_pooled_v(thingy_id id) noexcept {
			return dcon::dcon_vv_fat_id<int16_t>(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		//
		// accessors for thingy: big_array
		//
		DCON_RELEASE_INLINE float const& thingy_get_big_array(thingy_id id, thingy_id n) const noexcept {
			return thingy.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE float& thingy_get_big_array(thingy_id id, thingy_id n) noexcept {
			return thingy.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE uint32_t thingy_get_big_array_size() const noexcept {
			return thingy.m_big_array.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::unaligned_contiguous_tags<thingy_id> id, thingy_id n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::partial_contiguous_tags<thingy_id> id, thingy_id n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::tagged_vector<thingy_id> id, thingy_id n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_big_array(thingy_id id, thingy_id n, float value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			assert(dcon::get_index(n) >= 0);
			#endif
			thingy.m_big_array.vptr(dcon::get_index(n))[id.index()] = value;
		}
		DCON_RELEASE_INLINE void thingy_resize_big_array(uint32_t size) noexcept {
			return thingy.m_big_array.resize(size, thingy.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::unaligned_contiguous_tags<thingy_id> id, thingy_id n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::partial_contiguous_tags<thingy_id> id, thingy_id n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::tagged_vector<thingy_id> id, thingy_id n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		#endif
		//
		// accessors for thingy: big_array_bf
		//
		DCON_RELEASE_INLINE bool thingy_get_big_array_bf(thingy_id id, int32_t n) const noexcept {
			return dcon::bit_vector_test(thingy.m_big_array_bf.vptr(dcon::get_index(n)), id.index());
		}
		DCON_RELEASE_INLINE uint32_t thingy_get_big_array_bf_size() const noexcept {
			return thingy.m_big_array_bf.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::unaligned_contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::partial_contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::tagged_vector<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(thingy_id id, int32_t n, bool value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			assert(dcon::get_index(n) >= 0);
			#endif
			dcon::bit_vector_set(thingy.m_big_array_bf.vptr(dcon::get_index(n)), id.index(), value);
		}
		DCON_RELEASE_INLINE void thingy_resize_big_array_bf(uint32_t size) noexcept {
			thingy.m_big_array_bf.resize(size, thingy.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::unaligned_contiguous_tags<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::partial_contiguous_tags<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::tagged_vector<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		#endif
		DCON_RELEASE_INLINE bool thingy_is_valid(thingy_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < thingy.size_used;
		}
		
		uint32_t thingy_size() const noexcept { return thingy.size_used; }

		//
		// Functions for pop:
		//
		DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_initiator_generator pop_get_negotiation_as_initiator(pop_id id) const {
			return internal::const_iterator_pop_foreach_negotiation_as_initiator_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_initiator_generator pop_get_negotiation_as_initiator(pop_id id) {
			return internal::iterator_pop_foreach_negotiation_as_initiator_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void pop_for_each_negotiation_as_initiator(pop_id id, T&& func) const {
			if(bool(id)) {
				for(auto list_pos = negotiation.m_head_back_initiator.vptr()[id.index()]; bool(list_pos); list_pos = negotiation.m_link_initiator.vptr()[list_pos.index()].right) {
					func(list_pos);
				}
			}
		}
		void pop_remove_all_negotiation_as_initiator(pop_id id) noexcept {
			dcon::local_vector<negotiation_id> temp;
			pop_for_each_negotiation_as_initiator(id, [&](negotiation_id j) { temp.push_back(j); });
			std::for_each(temp.begin(), temp.end(), [t = this](negotiation_id i) { t->negotiation_set_initiator(i, pop_id()); });
		}
		DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_target_generator pop_get_negotiation_as_target(pop_id id) const {
			return internal::const_iterator_pop_foreach_negotiation_as_target_generator(*this, id);
		}
		DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_target_generator pop_get_negotiation_as_target(pop_id id) {
			return internal::iterator_pop_foreach_negotiation_as_target_generator(*this, id);
		}
		template<typename T>
		DCON_RELEASE_INLINE void pop_for_each_negotiation_as_target(pop_id id, T&& func) const {
			if(bool(id)) {
				for(auto list_pos = negotiation.m_head_back_target.vptr()[id.index()]; bool(list_pos); list_pos = negotiation.m_link_target.vptr()[list_pos.index()].right) {
					func(list_pos);
				}
			}
		}
		void pop_remove_all_negotiation_as_target(pop_id id) noexcept {
			dcon::local_vector<negotiation_id> temp;
			pop_for_each_negotiation_as_target(id, [&](negotiation_id j) { temp.push_back(j); });
			std::for_each(temp.begin(), temp.end(), [t = this](negotiation_id i) { t->negotiation_set_target(i, pop_id()); });
		}
		DCON_RELEASE_INLINE bool pop_is_valid(pop_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < pop.size_used && pop.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t pop_size() const noexcept { return pop.size_used; }

		//
		// Functions for negotiation:
		//
		DCON_RELEASE_INLINE pop_id negotiation_get_initiator(negotiation_id id) const noexcept {
			return negotiation.m_initiator.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_initiator(ve::contiguous_tags<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_initiator.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_initiator(ve::partial_contiguous_tags<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_initiator.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_initiator(ve::tagged_vector<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_initiator.vptr());
		}
		#endif
		private:
		void internal_negotiation_set_initiator(negotiation_id id, pop_id value) noexcept {
			if(auto old_value = negotiation.m_initiator.vptr()[id.index()]; bool(old_value)) {
				if(auto old_left = negotiation.m_link_initiator.vptr()[id.index()].left; bool(old_left)) {
					negotiation.m_link_initiator.vptr()[old_left.index()].right = negotiation.m_link_initiator.vptr()[id.index()].right;
				} else {
					negotiation.m_head_back_initiator.vptr()[old_value.index()] = negotiation.m_link_initiator.vptr()[id.index()].right;
				}
				if(auto old_right = negotiation.m_link_initiator.vptr()[id.index()].right; bool(old_right)) {
					negotiation.m_link_initiator.vptr()[old_right.index()].left = negotiation.m_link_initiator.vptr()[id.index()].left;
				}
			}
			if(bool(value)) {
				if(auto existing_list = negotiation.m_head_back_initiator.vptr()[value.index()]; bool(existing_list)) {
					negotiation.m_link_initiator.vptr()[id.index()].left = existing_list;
					if(auto r = negotiation.m_link_initiator.vptr()[existing_list.index()].right; bool(r)) {
						negotiation.m_link_initiator.vptr()[id.index()].right = r;
						negotiation.m_link_initiator.vptr()[r.index()].left = id;
					} else {
						negotiation.m_link_initiator.vptr()[id.index()].right = negotiation_id();
					}
					negotiation.m_link_initiator.vptr()[existing_list.index()].right = id;
					negotiation.m_head_back_initiator.vptr()[value.index()] = existing_list;
				} else {
					negotiation.m_head_back_initiator.vptr()[value.index()] = id;
					negotiation.m_link_initiator.vptr()[id.index()].right = negotiation_id();
					negotiation.m_link_initiator.vptr()[id.index()].left = negotiation_id();
				}
			} else {
				negotiation.m_link_initiator.vptr()[id.index()].right = negotiation_id();
				negotiation.m_link_initiator.vptr()[id.index()].left = negotiation_id();
			}
			negotiation.m_initiator.vptr()[id.index()] = value;
		}
		public:
		void negotiation_set_initiator(negotiation_id id, pop_id value) noexcept {
			if(!bool(value)) {
				delete_negotiation(id);
				return;
			}
			internal_negotiation_set_initiator(id, value);
		}
		bool negotiation_try_set_initiator(negotiation_id id, pop_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_negotiation_set_initiator(id, value);
			return true;
		}
		DCON_RELEASE_INLINE pop_id negotiation_get_target(negotiation_id id) const noexcept {
			return negotiation.m_target.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_target(ve::contiguous_tags<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_target.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_target(ve::partial_contiguous_tags<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_target.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<pop_id> negotiation_get_target(ve::tagged_vector<negotiation_id> id) const noexcept {
			return ve::load(id, negotiation.m_target.vptr());
		}
		#endif
		private:
		void internal_negotiation_set_target(negotiation_id id, pop_id value) noexcept {
			if(auto old_value = negotiation.m_target.vptr()[id.index()]; bool(old_value)) {
				if(auto old_left = negotiation.m_link_target.vptr()[id.index()].left; bool(old_left)) {
					negotiation.m_link_target.vptr()[old_left.index()].right = negotiation.m_link_target.vptr()[id.index()].right;
				} else {
					negotiation.m_head_back_target.vptr()[old_value.index()] = negotiation.m_link_target.vptr()[id.index()].right;
				}
				if(auto old_right = negotiation.m_link_target.vptr()[id.index()].right; bool(old_right)) {
					negotiation.m_link_target.vptr()[old_right.index()].left = negotiation.m_link_target.vptr()[id.index()].left;
				}
			}
			if(bool(value)) {
				if(auto existing_list = negotiation.m_head_back_target.vptr()[value.index()]; bool(existing_list)) {
					negotiation.m_link_target.vptr()[id.index()].left = existing_list;
					if(auto r = negotiation.m_link_target.vptr()[existing_list.index()].right; bool(r)) {
						negotiation.m_link_target.vptr()[id.index()].right = r;
						negotiation.m_link_target.vptr()[r.index()].left = id;
					} else {
						negotiation.m_link_target.vptr()[id.index()].right = negotiation_id();
					}
					negotiation.m_link_target.vptr()[existing_list.index()].right = id;
					negotiation.m_head_back_target.vptr()[value.index()] = existing_list;
				} else {
					negotiation.m_head_back_target.vptr()[value.index()] = id;
					negotiation.m_link_target.vptr()[id.index()].right = negotiation_id();
					negotiation.m_link_target.vptr()[id.index()].left = negotiation_id();
				}
			} else {
				negotiation.m_link_target.vptr()[id.index()].right = negotiation_id();
				negotiation.m_link_target.vptr()[id.index()].left = negotiation_id();
			}
			negotiation.m_target.vptr()[id.index()] = value;
		}
		public:
		void negotiation_set_target(negotiation_id id, pop_id value) noexcept {
			if(!bool(value)) {
				delete_negotiation(id);
				return;
			}
			internal_negotiation_set_target(id, value);
		}
		bool negotiation_try_set_target(negotiation_id id, pop_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			internal_negotiation_set_target(id, value);
			return true;
		}
		DCON_RELEASE_INLINE bool negotiation_is_valid(negotiation_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < negotiation.size_used && negotiation.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t negotiation_size() const noexcept { return negotiation.size_used; }


		//
		// container pop_back for thingy
		//
		void pop_back_thingy() {
			if(thingy.size_used == 0) return;
			thingy_id id_removed(thingy_id::value_base_t(thingy.size_used - 1));
			thingy.m_some_value.values.pop_back();
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), false);
			thingy.m_bf_value.values.resize(1 + (thingy.size_used + 6) / 8);
			thingy.m_lua_value.values.pop_back();
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_pooled_v.values.pop_back();
			thingy.m_big_array.pop_back_all(thingy.size_used);
			thingy.m_big_array_bf.pop_back_all(thingy.size_used);
			--thingy.size_used;
		}
		
		//
		// container resize for thingy
		//
		void thingy_resize(uint32_t new_size) {
			const uint32_t old_size = thingy.size_used;
			if(new_size < old_size) {
				thingy.m_some_value.values.resize(1 + new_size);
				for(uint32_t s = new_size; s < 8 * (((new_size + 7) / 8)); ++s) {
					dcon::bit_vector_set(thingy.m_bf_value.vptr(), s, false);
				}
				thingy.m_bf_value.values.resize(1 + (new_size + 7) / 8);
				thingy.m_lua_value.values.resize(1 + new_size);
				std::for_each(thingy.m_pooled_v.vptr() + new_size, thingy.m_pooled_v.vptr() + new_size + old_size - new_size, [t = this](dcon::stable_mk_2_tag& i){ t->thingy.pooled_v_storage.release(i); });
				thingy.m_pooled_v.values.resize(1 + new_size);
				for(int32_t s = 0; s < int32_t(thingy.m_big_array.size); ++s) {
					thingy.m_big_array.values[s].resize(1 + new_size);
				}
				for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size); ++s) {
					for(uint32_t t = new_size; t < 8 * (((new_size + 7) / 8)); ++t) {
						dcon::bit_vector_set(thingy.m_big_array_bf.vptr(s), t, false);
					}
					thingy.m_big_array_bf.values[s].resize(1 + (new_size + 7) / 8);
				}
			} else if(new_size > old_size) {
				thingy.m_some_value.values.resize(1 + new_size);
				thingy.m_bf_value.values.resize(1 + (new_size + 7) / 8);
				thingy.m_lua_value.values.resize(1 + new_size);
				thingy.m_pooled_v.values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());
				for(int32_t s = 0; s < int32_t(thingy.m_big_array.size); ++s) {
					thingy.m_big_array.values[s].resize(1 + new_size);
				}
				for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size); ++s) {
					thingy.m_big_array_bf.values[s].resize(1 + (new_size + 7) / 8);
				}
			}
			thingy.size_used = new_size;
		}
		
		//
		// container create for thingy
		//
		thingy_id create_thingy() {
			thingy_id new_id(thingy_id::value_base_t(thingy.size_used));
			thingy.m_some_value.values.emplace_back();
			thingy.m_bf_value.values.resize(1 + (thingy.size_used + 8) / 8);
			thingy.m_lua_value.values.emplace_back();
			thingy.m_pooled_v.values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());
			thingy.m_big_array.emplace_back_all(thingy.size_used + 1);
			thingy.m_big_array_bf.emplace_back_all(thingy.size_used + 1);
			++thingy.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for thingy
		//
		void delete_thingy(thingy_id id) {
			thingy_id id_removed = id;
			#ifndef NDEBUG
			assert(id.index() >= 0);
			assert(uint32_t(id.index()) < thingy.size_used );
			assert(thingy.size_used != 0);
			#endif
			thingy_id last_id(thingy_id::value_base_t(thingy.size_used - 1));
			if(id_removed == last_id) { pop_back_thingy(); return; }
			thingy.m_some_value.vptr()[id_removed.index()] = std::move(thingy.m_some_value.vptr()[last_id.index()]);
			thingy.m_some_value.values.pop_back();
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), dcon::bit_vector_test(thingy.m_bf_value.vptr(), last_id.index()));
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), last_id.index(), false);
			thingy.m_bf_value.values.resize(1 + (thingy.size_used + 6) / 8);
			thingy.m_lua_value.vptr()[id_removed.index()] = std::move(thingy.m_lua_value.vptr()[last_id.index()]);
			thingy.m_lua_value.values.pop_back();
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_pooled_v.vptr()[id_removed.index()] = std::move(thingy.m_pooled_v.vptr()[last_id.index()]);
			thingy.m_pooled_v.values.pop_back();
			thingy.m_big_array.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array.pop_back_all(thingy.size_used);
			thingy.m_big_array_bf.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array_bf.pop_back_all(thingy.size_used);
			--thingy.size_used;
		}
		
		//
		// container delete for pop
		//
		void delete_pop(pop_id id_removed) {
			#ifndef NDEBUG
			assert(id_removed.index() >= 0);
			assert(pop.m__index.vptr()[id_removed.index()] == id_removed);
			#endif
			pop.m__index.vptr()[id_removed.index()] = pop.first_free;
			pop.first_free = id_removed;
			if(int32_t(pop.size_used) - 1 == id_removed.index()) {
				for( ; pop.size_used > 0 && pop.m__index.vptr()[pop.size_used - 1] != pop_id(pop_id::value_base_t(pop.size_used - 1));  --pop.size_used) ;
			}
			pop_remove_all_negotiation_as_initiator(id_removed);
			pop_remove_all_negotiation_as_target(id_removed);
		}
		
		//
		// container create for pop
		//
		pop_id create_pop() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(pop.first_free)) std::abort();
			#else
			if(!bool(pop.first_free)) throw dcon::out_of_space{};
			#endif
			pop_id new_id = pop.first_free;
			pop.first_free = pop.m__index.vptr()[pop.first_free.index()];
			pop.m__index.vptr()[new_id.index()] = new_id;
			pop.size_used = std::max(pop.size_used, uint32_t(new_id.index() + 1));
			return new_id;
		}
		
		//
		// container resize for pop
		//
		void pop_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 300000) std::abort();
			#else
			if(new_size > 300000) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = pop.size_used;
			if(new_size < old_size) {
				pop.first_free = pop_id();
				int32_t i = int32_t(300000 - 1);
				for(; i >= int32_t(new_size); --i) {
					pop.m__index.vptr()[i] = pop.first_free;
					pop.first_free = pop_id(pop_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(pop.m__index.vptr()[i] != pop_id(pop_id::value_base_t(i))) {
						pop.m__index.vptr()[i] = pop.first_free;
						pop.first_free = pop_id(pop_id::value_base_t(i));
					}
				}
				negotiation_resize(0);
				negotiation_resize(0);
			} else if(new_size > old_size) {
				pop.first_free = pop_id();
				int32_t i = int32_t(300000 - 1);
				for(; i >= int32_t(old_size); --i) {
					pop.m__index.vptr()[i] = pop.first_free;
					pop.first_free = pop_id(pop_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(pop.m__index.vptr()[i] != pop_id(pop_id::value_base_t(i))) {
						pop.m__index.vptr()[i] = pop.first_free;
						pop.first_free = pop_id(pop_id::value_base_t(i));
					}
				}
			}
			pop.size_used = new_size;
		}
		
		//
		// container delete for negotiation
		//
		void delete_negotiation(negotiation_id id_removed) {
			#ifndef NDEBUG
			assert(id_removed.index() >= 0);
			assert(negotiation.m__index.vptr()[id_removed.index()] == id_removed);
			#endif
			negotiation.m__index.vptr()[id_removed.index()] = negotiation.first_free;
			negotiation.first_free = id_removed;
			if(int32_t(negotiation.size_used) - 1 == id_removed.index()) {
				for( ; negotiation.size_used > 0 && negotiation.m__index.vptr()[negotiation.size_used - 1] != negotiation_id(negotiation_id::value_base_t(negotiation.size_used - 1));  --negotiation.size_used) ;
			}
			internal_negotiation_set_initiator(id_removed, pop_id());
			internal_negotiation_set_target(id_removed, pop_id());
		}
		
		//
		// container resize for negotiation
		//
		void negotiation_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 2500) std::abort();
			#else
			if(new_size > 2500) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = negotiation.size_used;
			if(new_size < old_size) {
				negotiation.first_free = negotiation_id();
				int32_t i = int32_t(2500 - 1);
				for(; i >= int32_t(new_size); --i) {
					negotiation.m__index.vptr()[i] = negotiation.first_free;
					negotiation.first_free = negotiation_id(negotiation_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(negotiation.m__index.vptr()[i] != negotiation_id(negotiation_id::value_base_t(i))) {
						negotiation.m__index.vptr()[i] = negotiation.first_free;
						negotiation.first_free = negotiation_id(negotiation_id::value_base_t(i));
					}
				}
				std::fill_n(negotiation.m_initiator.vptr() + 0, old_size, pop_id{});
				std::fill_n(negotiation.m_link_initiator.vptr() + 0, old_size, negotiation_id_pair{});
				std::fill_n(negotiation.m_head_back_initiator.vptr() + 0, pop.size_used, negotiation_id{});
				std::fill_n(negotiation.m_target.vptr() + 0, old_size, pop_id{});
				std::fill_n(negotiation.m_link_target.vptr() + 0, old_size, negotiation_id_pair{});
				std::fill_n(negotiation.m_head_back_target.vptr() + 0, pop.size_used, negotiation_id{});
			} else if(new_size > old_size) {
				negotiation.first_free = negotiation_id();
				int32_t i = int32_t(2500 - 1);
				for(; i >= int32_t(old_size); --i) {
					negotiation.m__index.vptr()[i] = negotiation.first_free;
					negotiation.first_free = negotiation_id(negotiation_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(negotiation.m__index.vptr()[i] != negotiation_id(negotiation_id::value_base_t(i))) {
						negotiation.m__index.vptr()[i] = negotiation.first_free;
						negotiation.first_free = negotiation_id(negotiation_id::value_base_t(i));
					}
				}
			}
			negotiation.size_used = new_size;
		}
		
		//
		// container try create relationship for negotiation
		//
		negotiation_id try_create_negotiation(pop_id initiator_p, pop_id target_p) {
			if(!bool(initiator_p)) return negotiation_id();
			if(!bool(target_p)) return negotiation_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(negotiation.first_free)) std::abort();
			#else
			if(!bool(negotiation.first_free)) throw dcon::out_of_space{};
			#endif
			negotiation_id new_id = negotiation.first_free;
			negotiation.first_free = negotiation.m__index.vptr()[negotiation.first_free.index()];
			negotiation.m__index.vptr()[new_id.index()] = new_id;
			negotiation.size_used = std::max(negotiation.size_used, uint32_t(new_id.index() + 1));
			internal_negotiation_set_initiator(new_id, initiator_p);
			internal_negotiation_set_target(new_id, target_p);
			return new_id;
		}
		
		//
		// container force create relationship for negotiation
		//
		negotiation_id force_create_negotiation(pop_id initiator_p, pop_id target_p) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(negotiation.first_free)) std::abort();
			#else
			if(!bool(negotiation.first_free)) throw dcon::out_of_space{};
			#endif
			negotiation_id new_id = negotiation.first_free;
			negotiation.first_free = negotiation.m__index.vptr()[negotiation.first_free.index()];
			negotiation.m__index.vptr()[new_id.index()] = new_id;
			negotiation.size_used = std::max(negotiation.size_used, uint32_t(new_id.index() + 1));
			internal_negotiation_set_initiator(new_id, initiator_p);
			internal_negotiation_set_target(new_id, target_p);
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy(T&& func) {
			for(uint32_t i = 0; i < thingy.size_used; ++i) {
				thingy_id tmp = thingy_id(thingy_id::value_base_t(i));
				func(tmp);
			}
		}
		friend internal::const_object_iterator_thingy;
		friend internal::object_iterator_thingy;
		struct {
			internal::object_iterator_thingy begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingy));
				return internal::object_iterator_thingy(*container, uint32_t(0));
			}
			internal::object_iterator_thingy end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_thingy));
				return internal::object_iterator_thingy(*container, container->thingy_size());
			}
			internal::const_object_iterator_thingy begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingy));
				return internal::const_object_iterator_thingy(*container, uint32_t(0));
			}
			internal::const_object_iterator_thingy end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_thingy));
				return internal::const_object_iterator_thingy(*container, container->thingy_size());
			}
		}  in_thingy ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_pop(T&& func) {
			for(uint32_t i = 0; i < pop.size_used; ++i) {
				pop_id tmp = pop_id(pop_id::value_base_t(i));
				if(pop.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_pop;
		friend internal::object_iterator_pop;
		struct {
			internal::object_iterator_pop begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_pop));
				return internal::object_iterator_pop(*container, uint32_t(0));
			}
			internal::object_iterator_pop end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_pop));
				return internal::object_iterator_pop(*container, container->pop_size());
			}
			internal::const_object_iterator_pop begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_pop));
				return internal::const_object_iterator_pop(*container, uint32_t(0));
			}
			internal::const_object_iterator_pop end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_pop));
				return internal::const_object_iterator_pop(*container, container->pop_size());
			}
		}  in_pop ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_negotiation(T&& func) {
			for(uint32_t i = 0; i < negotiation.size_used; ++i) {
				negotiation_id tmp = negotiation_id(negotiation_id::value_base_t(i));
				if(negotiation.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_negotiation;
		friend internal::object_iterator_negotiation;
		struct {
			internal::object_iterator_negotiation begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_negotiation));
				return internal::object_iterator_negotiation(*container, uint32_t(0));
			}
			internal::object_iterator_negotiation end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_negotiation));
				return internal::object_iterator_negotiation(*container, container->negotiation_size());
			}
			internal::const_object_iterator_negotiation begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_negotiation));
				return internal::const_object_iterator_negotiation(*container, uint32_t(0));
			}
			internal::const_object_iterator_negotiation end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_negotiation));
				return internal::const_object_iterator_negotiation(*container, container->negotiation_size());
			}
		}  in_negotiation ;
		



		void reset() {
			negotiation_resize(0);
			thingy_resize(0);
			pop_resize(0);
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, thingy_id> thingy_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, thingy_id>(thingy.size_used);
		}
		ve::vectorizable_buffer<int32_t, thingy_id> thingy_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, thingy_id>(thingy.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_thingy(F&& functor) {
			ve::execute_serial_unaligned<thingy_id>(thingy.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy(F&& functor) {
			ve::execute_parallel_unaligned<thingy_id>(thingy.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, pop_id> pop_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, pop_id>(pop.size_used);
		}
		ve::vectorizable_buffer<int32_t, pop_id> pop_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, pop_id>(pop.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_pop(F&& functor) {
			ve::execute_serial<pop_id>(pop.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_pop(F&& functor) {
			ve::execute_parallel_exact<pop_id>(pop.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, negotiation_id> negotiation_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, negotiation_id>(negotiation.size_used);
		}
		ve::vectorizable_buffer<int32_t, negotiation_id> negotiation_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, negotiation_id>(negotiation.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_negotiation(F&& functor) {
			ve::execute_serial<negotiation_id>(negotiation.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_negotiation(F&& functor) {
			ve::execute_parallel_exact<negotiation_id>(negotiation.size_used, functor);
		}
#endif
		#endif

		load_record make_serialize_record_store_simple() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_some_value = true;
			result.thingy_bf_value = true;
			return result;
		}
		
		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_some_value = true;
			result.thingy_bf_value = true;
			result.thingy_lua_value = true;
			result.thingy_pooled_v = true;
			result.thingy_big_array = true;
			result.thingy_big_array_bf = true;
			result.pop = true;
			result.pop__index = true;
			result.negotiation = true;
			result.negotiation_initiator = true;
			result.negotiation_target = true;
			result.negotiation__index = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.thingy) {
				dcon::record_header header(0, "uint32_t", "thingy", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.thingy_some_value) {
				dcon::record_header iheader(0, "int32_t", "thingy", "some_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * thingy.size_used;
			}
			if(serialize_selection.thingy_bf_value) {
				dcon::record_header iheader(0, "bitfield", "thingy", "bf_value");
				total_size += iheader.serialize_size();
				total_size += (thingy.size_used + 7) / 8;
			}
			if(serialize_selection.thingy_lua_value) {
				dcon::record_header iheader(0, "lua_reference_type", "thingy", "lua_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(lua_reference_type) * thingy.size_used;
			}
			if(serialize_selection.thingy_pooled_v) {
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &total_size](dcon::stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy.pooled_v_storage, obj);
					total_size += sizeof(uint16_t);
					total_size += sizeof(int16_t) * (rng.second - rng.first);
				} );
				 {
					total_size += 8;
					dcon::record_header iheader(0, "stable_mk_2_tag", "thingy", "pooled_v");
					total_size += iheader.serialize_size();
				}
			}
			if(serialize_selection.thingy_big_array) {
				total_size += 6;
				total_size += sizeof(uint16_t);
				total_size += thingy.m_big_array.size * sizeof(float) * thingy.size_used;
				dcon::record_header iheader(0, "$array", "thingy", "big_array");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy_big_array_bf) {
				total_size += 9;
				total_size += sizeof(uint16_t);
				total_size += thingy.m_big_array_bf.size * ((thingy.size_used + 7) / 8);
				dcon::record_header iheader(0, "$array", "thingy", "big_array_bf");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.pop) {
				dcon::record_header header(0, "uint32_t", "pop", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.pop__index) {
				dcon::record_header iheader(0, "uint32_t", "pop", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(pop_id) * pop.size_used;
			}
			if(serialize_selection.negotiation) {
				dcon::record_header header(0, "uint32_t", "negotiation", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.negotiation_initiator) {
					dcon::record_header iheader(0, "uint32_t", "negotiation", "initiator");
					total_size += iheader.serialize_size();
					total_size += sizeof(pop_id) * negotiation.size_used;
				}
				if(serialize_selection.negotiation_target) {
					dcon::record_header iheader(0, "uint32_t", "negotiation", "target");
					total_size += iheader.serialize_size();
					total_size += sizeof(pop_id) * negotiation.size_used;
				}
				dcon::record_header headerb(0, "$", "negotiation", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.negotiation__index) {
				dcon::record_header iheader(0, "uint16_t", "negotiation", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(negotiation_id) * negotiation.size_used;
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.thingy) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "thingy", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = thingy.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.thingy_some_value) {
				dcon::record_header header(sizeof(int32_t) * thingy.size_used, "int32_t", "thingy", "some_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), thingy.m_some_value.vptr(), sizeof(int32_t) * thingy.size_used);
				output_buffer += sizeof(int32_t) * thingy.size_used;
			}
			if(serialize_selection.thingy_bf_value) {
				dcon::record_header header((thingy.size_used + 7) / 8, "bitfield", "thingy", "bf_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<dcon::bitfield_type*>(output_buffer), thingy.m_bf_value.vptr(), (thingy.size_used + 7) / 8);
				output_buffer += (thingy.size_used + 7) / 8;
			}
			if(serialize_selection.thingy_lua_value) {
				dcon::record_header header(sizeof(lua_reference_type) * thingy.size_used, "lua_reference_type", "thingy", "lua_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<lua_reference_type*>(output_buffer), thingy.m_lua_value.vptr(), sizeof(lua_reference_type) * thingy.size_used);
				output_buffer += sizeof(lua_reference_type) * thingy.size_used;
			}
			if(serialize_selection.thingy_pooled_v) {
				size_t total_size = 0;
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &total_size](dcon::stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy.pooled_v_storage, obj);
					total_size += sizeof(uint16_t) + sizeof(int16_t) * (rng.second - rng.first);
				} );
				total_size += 8;
				dcon::record_header header(total_size, "stable_mk_2_tag", "thingy", "pooled_v");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "int16_t", 8);
				output_buffer += 8;
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &output_buffer](dcon::stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy.pooled_v_storage, obj);
					*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(rng.second - rng.first);
					output_buffer += sizeof(uint16_t);
					std::memcpy(reinterpret_cast<int16_t*>(output_buffer), rng.first, sizeof(int16_t) * (rng.second - rng.first));
					output_buffer += sizeof(int16_t) * (rng.second - rng.first);
				} );
			}
			if(serialize_selection.thingy_big_array) {
				dcon::record_header header(6 + sizeof(uint16_t) + sizeof(float) * thingy.m_big_array.size * thingy.size_used, "$array", "thingy", "big_array");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "float", 6);
				output_buffer += 6;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy.m_big_array.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy.m_big_array.size); ++s) {
					std::memcpy(reinterpret_cast<float*>(output_buffer), thingy.m_big_array.vptr(s), sizeof(float) * thingy.size_used);
					output_buffer +=  sizeof(float) * thingy.size_used;
				}
			}
			if(serialize_selection.thingy_big_array_bf) {
				dcon::record_header header(9 + sizeof(uint16_t) + thingy.m_big_array_bf.size * ((thingy.size_used + 7) / 8), "$array", "thingy", "big_array_bf");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "bitfield", 9);
				output_buffer += 9;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy.m_big_array_bf.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size); ++s) {
					std::memcpy(reinterpret_cast<dcon::bitfield_type*>(output_buffer), thingy.m_big_array_bf.vptr(s), (thingy.size_used + 7) / 8);
					output_buffer += (thingy.size_used + 7) / 8;
				}
			}
			if(serialize_selection.pop) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "pop", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = pop.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.pop__index) {
				dcon::record_header header(sizeof(pop_id) * pop.size_used, "uint32_t", "pop", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<pop_id*>(output_buffer), pop.m__index.vptr(), sizeof(pop_id) * pop.size_used);
				output_buffer += sizeof(pop_id) * pop.size_used;
			}
			if(serialize_selection.negotiation) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "negotiation", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = negotiation.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(pop_id) * negotiation.size_used, "uint32_t", "negotiation", "initiator");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<pop_id*>(output_buffer), negotiation.m_initiator.vptr(), sizeof(pop_id) * negotiation.size_used);
					output_buffer += sizeof(pop_id) *  negotiation.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(pop_id) * negotiation.size_used, "uint32_t", "negotiation", "target");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<pop_id*>(output_buffer), negotiation.m_target.vptr(), sizeof(pop_id) * negotiation.size_used);
					output_buffer += sizeof(pop_id) *  negotiation.size_used;
				}
				dcon::record_header headerb(0, "$", "negotiation", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.negotiation__index) {
				dcon::record_header header(sizeof(negotiation_id) * negotiation.size_used, "uint16_t", "negotiation", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<negotiation_id*>(output_buffer), negotiation.m__index.vptr(), sizeof(negotiation_id) * negotiation.size_used);
				output_buffer += sizeof(negotiation_id) * negotiation.size_used;
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
						if(header.is_object("thingy")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									thingy_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.thingy = true;
									break;
								}
								if(header.is_property("some_value")) {
									if(header.is_type("int32_t")) {
										std::memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), size_t(header.record_size)));
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("float")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									break;
								}
								if(header.is_property("bf_value")) {
									if(header.is_type("bitfield")) {
										std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<dcon::bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, size_t(header.record_size)));
										serialize_selection.thingy_bf_value = true;
									}
									break;
								}
								if(header.is_property("lua_value")) {
									if(header.is_type("lua_reference_type")) {
										std::memcpy(thingy.m_lua_value.vptr(), reinterpret_cast<lua_reference_type const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(lua_reference_type), size_t(header.record_size)));
										serialize_selection.thingy_lua_value = true;
									}
									break;
								}
								if(header.is_property("pooled_v")) {
									if(header.is_type("stable_mk_2_tag")) {
										uint32_t ix = 0;
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int16_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::load_range(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], reinterpret_cast<int16_t const*>(icpy), reinterpret_cast<int16_t const*>(icpy) + sz);
												icpy += sz * sizeof(int16_t);
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int8_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy)));
													icpy += sizeof(int8_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint8_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy)));
													icpy += sizeof(uint8_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint16_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy)));
													icpy += sizeof(uint16_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int32_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy)));
													icpy += sizeof(int32_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint32_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy)));
													icpy += sizeof(uint32_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int64_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy)));
													icpy += sizeof(int64_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint64_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy)));
													icpy += sizeof(uint64_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(float) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy)));
													icpy += sizeof(float);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(double) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy)));
													icpy += sizeof(double);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
									}
									break;
								}
								if(header.is_property("big_array")) {
									if(header.is_type("$array")) {
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										std::byte const* icpy = zero_pos + 1;
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												std::memcpy(thingy.m_big_array.vptr(s), reinterpret_cast<float const*>(icpy), std::min(sizeof(float) * thingy.size_used, size_t(input_buffer + header.record_size - icpy)));
												icpy += sizeof(float) * thingy.size_used;
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int8_t const*>(icpy)));
													icpy += sizeof(int8_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint8_t const*>(icpy)));
													icpy += sizeof(uint8_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int16_t const*>(icpy)));
													icpy += sizeof(int16_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint16_t const*>(icpy)));
													icpy += sizeof(uint16_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int32_t const*>(icpy)));
													icpy += sizeof(int32_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint32_t const*>(icpy)));
													icpy += sizeof(uint32_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int64_t const*>(icpy)));
													icpy += sizeof(int64_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint64_t const*>(icpy)));
													icpy += sizeof(uint64_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<double const*>(icpy)));
													icpy += sizeof(double);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
									}
									break;
								}
								if(header.is_property("big_array_bf")) {
									if(header.is_type("$array")) {
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										std::byte const* icpy = zero_pos + 1;
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "bitfield")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array_bf.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array_bf.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size) && icpy < input_buffer + header.record_size; ++s) {
												std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<dcon::bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
												icpy += (thingy.size_used + 7) / 8;
											}
											serialize_selection.thingy_big_array_bf = true;
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("pop")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									pop_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.pop = true;
									break;
								}
								if(header.is_property("_index")) {
									if(header.is_type("uint32_t")) {
										std::memcpy(pop.m__index.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(pop.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.pop__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(pop.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											pop.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.pop__index = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(pop.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											pop.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.pop__index = true;
									}
									if(serialize_selection.pop__index == true) {
										pop.first_free = pop_id();
										for(int32_t j = 300000 - 1; j >= 0; --j) {
											if(pop.m__index.vptr()[j] != pop_id(uint32_t(j))) {
												pop.m__index.vptr()[j] = pop.first_free;
												pop.first_free = pop_id(uint32_t(j));
											} else {
											}
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("negotiation")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= negotiation.size_used) {
										negotiation_resize(0);
									}
									negotiation_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.negotiation = true;
									break;
								}
								if(header.is_property("_index")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(negotiation.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint16_t), size_t(header.record_size)));
										serialize_selection.negotiation__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											negotiation.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation__index = true;
									}
									if(serialize_selection.negotiation__index == true) {
										negotiation.first_free = negotiation_id();
										for(int32_t j = 2500 - 1; j >= 0; --j) {
											if(negotiation.m__index.vptr()[j] != negotiation_id(uint16_t(j))) {
												negotiation.m__index.vptr()[j] = negotiation.first_free;
												negotiation.first_free = negotiation_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("initiator")) {
									if(header.is_type("uint32_t")) {
										std::memcpy(negotiation.m_initiator.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.negotiation_initiator = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m_initiator.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_initiator = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											negotiation.m_initiator.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_initiator = true;
									}
									break;
								}
								if(header.is_property("target")) {
									if(header.is_type("uint32_t")) {
										std::memcpy(negotiation.m_target.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.negotiation_target = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m_target.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_target = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											negotiation.m_target.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_target = true;
									}
									break;
								}
								if(header.is_property("$index_end")) {
									if(serialize_selection.negotiation_initiator == true) {
										for(uint32_t i = 0; i < negotiation.size_used; ++i) {
											auto tmp = negotiation.m_initiator.vptr()[i];
											negotiation.m_initiator.vptr()[i] = pop_id();
											internal_negotiation_set_initiator(negotiation_id(negotiation_id::value_base_t(i)), tmp);
										}
									}
									if(serialize_selection.negotiation_target == true) {
										for(uint32_t i = 0; i < negotiation.size_used; ++i) {
											auto tmp = negotiation.m_target.vptr()[i];
											negotiation.m_target.vptr()[i] = pop_id();
											internal_negotiation_set_target(negotiation_id(negotiation_id::value_base_t(i)), tmp);
										}
									}
									break;
								}
							} while(false);
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
						if(header.is_object("thingy") && mask.thingy) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									thingy_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.thingy = true;
									break;
								}
								if(header.is_property("some_value") && mask.thingy_some_value) {
									if(header.is_type("int32_t")) {
										std::memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), size_t(header.record_size)));
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("float")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											thingy.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.thingy_some_value = true;
									}
									break;
								}
								if(header.is_property("bf_value") && mask.thingy_bf_value) {
									if(header.is_type("bitfield")) {
										std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<dcon::bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, size_t(header.record_size)));
										serialize_selection.thingy_bf_value = true;
									}
									break;
								}
								if(header.is_property("lua_value") && mask.thingy_lua_value) {
									if(header.is_type("lua_reference_type")) {
										std::memcpy(thingy.m_lua_value.vptr(), reinterpret_cast<lua_reference_type const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(lua_reference_type), size_t(header.record_size)));
										serialize_selection.thingy_lua_value = true;
									}
									break;
								}
								if(header.is_property("pooled_v") && mask.thingy_pooled_v) {
									if(header.is_type("stable_mk_2_tag")) {
										uint32_t ix = 0;
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int16_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::load_range(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], reinterpret_cast<int16_t const*>(icpy), reinterpret_cast<int16_t const*>(icpy) + sz);
												icpy += sz * sizeof(int16_t);
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int8_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy)));
													icpy += sizeof(int8_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint8_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy)));
													icpy += sizeof(uint8_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint16_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy)));
													icpy += sizeof(uint16_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int32_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy)));
													icpy += sizeof(int32_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint32_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy)));
													icpy += sizeof(uint32_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int64_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy)));
													icpy += sizeof(int64_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint64_t) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy)));
													icpy += sizeof(uint64_t);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(float) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy)));
													icpy += sizeof(float);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
											for(std::byte const* icpy = zero_pos + 1; ix < thingy.size_used && icpy < input_buffer + header.record_size; ) {
												uint16_t sz = 0;
												if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
													sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(double) ));
													icpy += sizeof(uint16_t);
												}
												dcon::resize(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], sz);
												for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
													dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy)));
													icpy += sizeof(double);
												}
												++ix;
											}
											serialize_selection.thingy_pooled_v = true;
										}
									}
									break;
								}
								if(header.is_property("big_array") && mask.thingy_big_array) {
									if(header.is_type("$array")) {
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										std::byte const* icpy = zero_pos + 1;
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												std::memcpy(thingy.m_big_array.vptr(s), reinterpret_cast<float const*>(icpy), std::min(sizeof(float) * thingy.size_used, size_t(input_buffer + header.record_size - icpy)));
												icpy += sizeof(float) * thingy.size_used;
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int8_t const*>(icpy)));
													icpy += sizeof(int8_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint8_t const*>(icpy)));
													icpy += sizeof(uint8_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int16_t const*>(icpy)));
													icpy += sizeof(int16_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint16_t const*>(icpy)));
													icpy += sizeof(uint16_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int32_t const*>(icpy)));
													icpy += sizeof(int32_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint32_t const*>(icpy)));
													icpy += sizeof(uint32_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<int64_t const*>(icpy)));
													icpy += sizeof(int64_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<uint64_t const*>(icpy)));
													icpy += sizeof(uint64_t);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
										else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
												for(uint32_t j = 0; j < thingy.size_used && icpy < input_buffer + header.record_size; ++j) {
													thingy.m_big_array.vptr(s)[j] = float(*(reinterpret_cast<double const*>(icpy)));
													icpy += sizeof(double);
												}
											}
											serialize_selection.thingy_big_array = true;
										}
									}
									break;
								}
								if(header.is_property("big_array_bf") && mask.thingy_big_array_bf) {
									if(header.is_type("$array")) {
										std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
										std::byte const* icpy = zero_pos + 1;
										if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "bitfield")) {
											if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
												thingy.m_big_array_bf.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy.size_used);
												icpy += sizeof(uint16_t);
											} else {
												thingy.m_big_array_bf.resize(0, thingy.size_used);
											}
											for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size) && icpy < input_buffer + header.record_size; ++s) {
												std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<dcon::bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
												icpy += (thingy.size_used + 7) / 8;
											}
											serialize_selection.thingy_big_array_bf = true;
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("pop") && mask.pop) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									pop_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.pop = true;
									break;
								}
								if(header.is_property("_index") && mask.pop__index) {
									if(header.is_type("uint32_t")) {
										std::memcpy(pop.m__index.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(pop.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.pop__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(pop.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											pop.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.pop__index = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(pop.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											pop.m__index.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.pop__index = true;
									}
									if(serialize_selection.pop__index == true) {
										pop.first_free = pop_id();
										for(int32_t j = 300000 - 1; j >= 0; --j) {
											if(pop.m__index.vptr()[j] != pop_id(uint32_t(j))) {
												pop.m__index.vptr()[j] = pop.first_free;
												pop.first_free = pop_id(uint32_t(j));
											} else {
											}
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("negotiation") && mask.negotiation) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= negotiation.size_used) {
										negotiation_resize(0);
									}
									negotiation_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.negotiation = true;
									break;
								}
								if(header.is_property("_index") && mask.negotiation__index) {
									if(header.is_type("uint16_t")) {
										std::memcpy(negotiation.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint16_t), size_t(header.record_size)));
										serialize_selection.negotiation__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											negotiation.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation__index = true;
									}
									if(serialize_selection.negotiation__index == true) {
										negotiation.first_free = negotiation_id();
										for(int32_t j = 2500 - 1; j >= 0; --j) {
											if(negotiation.m__index.vptr()[j] != negotiation_id(uint16_t(j))) {
												negotiation.m__index.vptr()[j] = negotiation.first_free;
												negotiation.first_free = negotiation_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("initiator") && mask.negotiation_initiator) {
									if(header.is_type("uint32_t")) {
										std::memcpy(negotiation.m_initiator.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.negotiation_initiator = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m_initiator.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_initiator = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											negotiation.m_initiator.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_initiator = true;
									}
									break;
								}
								if(header.is_property("target") && mask.negotiation_target) {
									if(header.is_type("uint32_t")) {
										std::memcpy(negotiation.m_target.vptr(), reinterpret_cast<uint32_t const*>(input_buffer), std::min(size_t(negotiation.size_used) * sizeof(uint32_t), size_t(header.record_size)));
										serialize_selection.negotiation_target = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											negotiation.m_target.vptr()[i].value = uint32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_target = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(negotiation.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											negotiation.m_target.vptr()[i].value = uint32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.negotiation_target = true;
									}
									break;
								}
								if(header.is_property("$index_end") && mask.negotiation) {
									if(serialize_selection.negotiation_initiator == true) {
										for(uint32_t i = 0; i < negotiation.size_used; ++i) {
											auto tmp = negotiation.m_initiator.vptr()[i];
											negotiation.m_initiator.vptr()[i] = pop_id();
											internal_negotiation_set_initiator(negotiation_id(negotiation_id::value_base_t(i)), tmp);
										}
									}
									if(serialize_selection.negotiation_target == true) {
										for(uint32_t i = 0; i < negotiation.size_used; ++i) {
											auto tmp = negotiation.m_target.vptr()[i];
											negotiation.m_target.vptr()[i] = pop_id();
											internal_negotiation_set_target(negotiation_id(negotiation_id::value_base_t(i)), tmp);
										}
									}
									break;
								}
							} while(false);
							break;
						}
					} while(false);
				}
				input_buffer += header.record_size;
			}
		}
		

	};

	DCON_RELEASE_INLINE int32_t& thingy_fat_id::get_some_value() const noexcept {
		return container.thingy_get_some_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_some_value(int32_t v) const noexcept {
		container.thingy_set_some_value(id, v);
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::get_bf_value() const noexcept {
		return container.thingy_get_bf_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_bf_value(bool v) const noexcept {
		container.thingy_set_bf_value(id, v);
	}
	DCON_RELEASE_INLINE lua_reference_type& thingy_fat_id::get_lua_value() const noexcept {
		return container.thingy_get_lua_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_lua_value(lua_reference_type const& v) const noexcept {
		container.thingy_set_lua_value(id, v);
	}
	DCON_RELEASE_INLINE dcon::dcon_vv_fat_id<int16_t> thingy_fat_id::get_pooled_v() const noexcept {
		return container.thingy_get_pooled_v(id);
	}
	DCON_RELEASE_INLINE float& thingy_fat_id::get_big_array(thingy_id i) const noexcept {
		return container.thingy_get_big_array(id, i);
	}
	DCON_RELEASE_INLINE uint32_t thingy_fat_id::get_big_array_size() const noexcept {
		return container.thingy_get_big_array_size();
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_big_array(thingy_id i, float v) const noexcept {
		container.thingy_set_big_array(id, i, v);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::resize_big_array(uint32_t sz) const noexcept {
		container.thingy_resize_big_array(sz);
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::get_big_array_bf(int32_t i) const noexcept {
		return container.thingy_get_big_array_bf(id, i);
	}
	DCON_RELEASE_INLINE uint32_t thingy_fat_id::get_big_array_bf_size() const noexcept {
		return container.thingy_get_big_array_bf_size();
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_big_array_bf(int32_t i, bool v) const noexcept {
		container.thingy_set_big_array_bf(id, i, v);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::resize_big_array_bf(uint32_t sz) const noexcept {
		container.thingy_resize_big_array_bf(sz);
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::is_valid() const noexcept {
		return container.thingy_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t thingy_const_fat_id::get_some_value() const noexcept {
		return container.thingy_get_some_value(id);
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::get_bf_value() const noexcept {
		return container.thingy_get_bf_value(id);
	}
	DCON_RELEASE_INLINE lua_reference_type const& thingy_const_fat_id::get_lua_value() const noexcept {
		return container.thingy_get_lua_value(id);
	}
	DCON_RELEASE_INLINE dcon::dcon_vv_const_fat_id<int16_t> thingy_const_fat_id::get_pooled_v() const noexcept {
		return container.thingy_get_pooled_v(id);
	}
	DCON_RELEASE_INLINE float thingy_const_fat_id::get_big_array(thingy_id i) const noexcept {
		return container.thingy_get_big_array(id, i);
	}
	DCON_RELEASE_INLINE uint32_t thingy_const_fat_id::get_big_array_size() const noexcept {
		return container.thingy_get_big_array_size();
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::get_big_array_bf(int32_t i) const noexcept {
		return container.thingy_get_big_array_bf(id, i);
	}
	DCON_RELEASE_INLINE uint32_t thingy_const_fat_id::get_big_array_bf_size() const noexcept {
		return container.thingy_get_big_array_bf_size();
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::is_valid() const noexcept {
		return container.thingy_is_valid(id);
	}
	
	template<typename T>
	DCON_RELEASE_INLINE void pop_fat_id::for_each_negotiation_as_initiator(T&& func) const {
		container.pop_for_each_negotiation_as_initiator(id, [&, t = this](negotiation_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE void pop_fat_id::remove_all_negotiation_as_initiator() const noexcept {
		container.pop_remove_all_negotiation_as_initiator(id);
	}
	DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_initiator_generator pop_fat_id::get_negotiation_as_initiator() const {
		return internal::iterator_pop_foreach_negotiation_as_initiator_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void pop_fat_id::for_each_negotiation_as_target(T&& func) const {
		container.pop_for_each_negotiation_as_target(id, [&, t = this](negotiation_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE void pop_fat_id::remove_all_negotiation_as_target() const noexcept {
		container.pop_remove_all_negotiation_as_target(id);
	}
	DCON_RELEASE_INLINE internal::iterator_pop_foreach_negotiation_as_target_generator pop_fat_id::get_negotiation_as_target() const {
		return internal::iterator_pop_foreach_negotiation_as_target_generator(container, id);
	}
	DCON_RELEASE_INLINE bool pop_fat_id::is_valid() const noexcept {
		return container.pop_is_valid(id);
	}
	
	template<typename T>
	DCON_RELEASE_INLINE void pop_const_fat_id::for_each_negotiation_as_initiator(T&& func) const {
		container.pop_for_each_negotiation_as_initiator(id, [&, t = this](negotiation_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_initiator_generator pop_const_fat_id::get_negotiation_as_initiator() const {
		return internal::const_iterator_pop_foreach_negotiation_as_initiator_generator(container, id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void pop_const_fat_id::for_each_negotiation_as_target(T&& func) const {
		container.pop_for_each_negotiation_as_target(id, [&, t = this](negotiation_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE internal::const_iterator_pop_foreach_negotiation_as_target_generator pop_const_fat_id::get_negotiation_as_target() const {
		return internal::const_iterator_pop_foreach_negotiation_as_target_generator(container, id);
	}
	DCON_RELEASE_INLINE bool pop_const_fat_id::is_valid() const noexcept {
		return container.pop_is_valid(id);
	}
	
	DCON_RELEASE_INLINE pop_fat_id negotiation_fat_id::get_initiator() const noexcept {
		return pop_fat_id(container, container.negotiation_get_initiator(id));
	}
	DCON_RELEASE_INLINE void negotiation_fat_id::set_initiator(pop_id val) const noexcept {
		container.negotiation_set_initiator(id, val);
	}
	DCON_RELEASE_INLINE bool negotiation_fat_id::try_set_initiator(pop_id val) const noexcept {
		return container.negotiation_try_set_initiator(id, val);
	}
	DCON_RELEASE_INLINE pop_fat_id negotiation_fat_id::get_target() const noexcept {
		return pop_fat_id(container, container.negotiation_get_target(id));
	}
	DCON_RELEASE_INLINE void negotiation_fat_id::set_target(pop_id val) const noexcept {
		container.negotiation_set_target(id, val);
	}
	DCON_RELEASE_INLINE bool negotiation_fat_id::try_set_target(pop_id val) const noexcept {
		return container.negotiation_try_set_target(id, val);
	}
	DCON_RELEASE_INLINE bool negotiation_fat_id::is_valid() const noexcept {
		return container.negotiation_is_valid(id);
	}
	
	DCON_RELEASE_INLINE pop_const_fat_id negotiation_const_fat_id::get_initiator() const noexcept {
		return pop_const_fat_id(container, container.negotiation_get_initiator(id));
	}
	DCON_RELEASE_INLINE pop_const_fat_id negotiation_const_fat_id::get_target() const noexcept {
		return pop_const_fat_id(container, container.negotiation_get_target(id));
	}
	DCON_RELEASE_INLINE bool negotiation_const_fat_id::is_valid() const noexcept {
		return container.negotiation_is_valid(id);
	}
	

	namespace internal {
		DCON_RELEASE_INLINE object_iterator_thingy::object_iterator_thingy(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_thingy::const_object_iterator_thingy(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_thingy& object_iterator_thingy::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingy& const_object_iterator_thingy::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_thingy& object_iterator_thingy::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_thingy& const_object_iterator_thingy::operator--() noexcept {
			--index;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_pop::object_iterator_pop(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_pop::const_object_iterator_pop(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_pop& object_iterator_pop::operator++() noexcept {
			++index;
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_pop& const_object_iterator_pop::operator++() noexcept {
			++index;
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_pop& object_iterator_pop::operator--() noexcept {
			--index;
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_pop& const_object_iterator_pop::operator--() noexcept {
			--index;
			while(container.pop.m__index.vptr()[index] != pop_id(pop_id::value_base_t(index)) && index < container.pop.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator::iterator_pop_foreach_negotiation_as_initiator(data_container& c,  pop_id fr) noexcept : container(c) {
			list_pos = container.negotiation.m_head_back_initiator.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator& iterator_pop_foreach_negotiation_as_initiator::operator++() noexcept {
			list_pos = container.negotiation.m_link_initiator.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_initiator& iterator_pop_foreach_negotiation_as_initiator::operator--() noexcept {
			list_pos = container.negotiation.m_link_initiator.vptr()[list_pos.index()].left;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator::const_iterator_pop_foreach_negotiation_as_initiator(data_container const& c,  pop_id fr) noexcept : container(c) {
			list_pos = container.negotiation.m_head_back_initiator.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator& const_iterator_pop_foreach_negotiation_as_initiator::operator++() noexcept {
			list_pos = container.negotiation.m_link_initiator.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_initiator& const_iterator_pop_foreach_negotiation_as_initiator::operator--() noexcept {
			list_pos = container.negotiation.m_link_initiator.vptr()[list_pos.index()].left;
			return *this;
		}
		
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target::iterator_pop_foreach_negotiation_as_target(data_container& c,  pop_id fr) noexcept : container(c) {
			list_pos = container.negotiation.m_head_back_target.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target& iterator_pop_foreach_negotiation_as_target::operator++() noexcept {
			list_pos = container.negotiation.m_link_target.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE iterator_pop_foreach_negotiation_as_target& iterator_pop_foreach_negotiation_as_target::operator--() noexcept {
			list_pos = container.negotiation.m_link_target.vptr()[list_pos.index()].left;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target::const_iterator_pop_foreach_negotiation_as_target(data_container const& c,  pop_id fr) noexcept : container(c) {
			list_pos = container.negotiation.m_head_back_target.vptr()[fr.index()];
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target& const_iterator_pop_foreach_negotiation_as_target::operator++() noexcept {
			list_pos = container.negotiation.m_link_target.vptr()[list_pos.index()].right;
			return *this;
		}
		DCON_RELEASE_INLINE const_iterator_pop_foreach_negotiation_as_target& const_iterator_pop_foreach_negotiation_as_target::operator--() noexcept {
			list_pos = container.negotiation.m_link_target.vptr()[list_pos.index()].left;
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_negotiation::object_iterator_negotiation(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_negotiation::const_object_iterator_negotiation(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_negotiation& object_iterator_negotiation::operator++() noexcept {
			++index;
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_negotiation& const_object_iterator_negotiation::operator++() noexcept {
			++index;
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_negotiation& object_iterator_negotiation::operator--() noexcept {
			--index;
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_negotiation& const_object_iterator_negotiation::operator--() noexcept {
			--index;
			while(container.negotiation.m__index.vptr()[index] != negotiation_id(negotiation_id::value_base_t(index)) && index < container.negotiation.size_used) {
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

