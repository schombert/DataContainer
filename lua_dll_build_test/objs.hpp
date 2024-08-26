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
		bool thingy_obj_value : 1;
		bool thingy_pooled_v : 1;
		bool thingy_big_array : 1;
		bool thingy_big_array_bf : 1;
		load_record() {
			thingy = false;
			thingy_some_value = false;
			thingy_bf_value = false;
			thingy_lua_value = false;
			thingy_obj_value = false;
			thingy_pooled_v = false;
			thingy_big_array = false;
			thingy_big_array_bf = false;
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
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::thingy_id> {
		using type = ::ve::tagged_vector<dcon::thingy_id>;
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
			// storage space for obj_value of type std::vector<float>
			//
			struct dtype_obj_value {
				std::vector<std::vector<float>> values;
				DCON_RELEASE_INLINE auto vptr() const { return values.data() + 1; }
				DCON_RELEASE_INLINE auto vptr() { return values.data() + 1; }
				dtype_obj_value() { values.emplace_back(); }
			}
			m_obj_value;
			
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

	}

	class thingy_const_fat_id;
	class thingy_fat_id;
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
		DCON_RELEASE_INLINE std::vector<float>& get_obj_value() const noexcept;
		DCON_RELEASE_INLINE void set_obj_value(std::vector<float> const& v) const noexcept;
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
		DCON_RELEASE_INLINE std::vector<float> const& get_obj_value() const noexcept;
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
		
	}

	class alignas(64) data_container {
		public:
		internal::thingy_class thingy;

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
		// accessors for thingy: obj_value
		//
		DCON_RELEASE_INLINE std::vector<float> const& thingy_get_obj_value(thingy_id id) const noexcept {
			return thingy.m_obj_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE std::vector<float>& thingy_get_obj_value(thingy_id id) noexcept {
			return thingy.m_obj_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE void thingy_set_obj_value(thingy_id id, std::vector<float> const& value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			thingy.m_obj_value.vptr()[id.index()] = value;
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
		// container pop_back for thingy
		//
		void pop_back_thingy() {
			if(thingy.size_used == 0) return;
			thingy_id id_removed(thingy_id::value_base_t(thingy.size_used - 1));
			thingy.m_some_value.values.pop_back();
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), false);
			thingy.m_bf_value.values.resize(1 + (thingy.size_used + 6) / 8);
			thingy.m_lua_value.values.pop_back();
			thingy.m_obj_value.values.pop_back();
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
				thingy.m_obj_value.values.resize(1 + new_size);
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
				thingy.m_obj_value.values.resize(1 + new_size);
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
			thingy.m_obj_value.values.emplace_back();
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
			thingy.m_obj_value.vptr()[id_removed.index()] = std::move(thingy.m_obj_value.vptr()[last_id.index()]);
			thingy.m_obj_value.values.pop_back();
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_pooled_v.vptr()[id_removed.index()] = std::move(thingy.m_pooled_v.vptr()[last_id.index()]);
			thingy.m_pooled_v.values.pop_back();
			thingy.m_big_array.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array.pop_back_all(thingy.size_used);
			thingy.m_big_array_bf.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array_bf.pop_back_all(thingy.size_used);
			--thingy.size_used;
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
		


		uint64_t serialize_size(std::vector<float> const& obj) const;
		void serialize(std::byte*& output_buffer, std::vector<float> const& obj) const;
		void deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const;

		void reset() {
			thingy_resize(0);
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
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_some_value = true;
			result.thingy_bf_value = true;
			result.thingy_lua_value = true;
			result.thingy_obj_value = true;
			result.thingy_pooled_v = true;
			result.thingy_big_array = true;
			result.thingy_big_array_bf = true;
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
			if(serialize_selection.thingy_obj_value) {
				std::for_each(thingy.m_obj_value.vptr(), thingy.m_obj_value.vptr() + thingy.size_used, [t = this, &total_size](std::vector<float> const& obj){ total_size += t->serialize_size(obj); });
				dcon::record_header iheader(0, "std::vector<float>", "thingy", "obj_value");
				total_size += iheader.serialize_size();
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
			if(serialize_selection.thingy_obj_value) {
				size_t total_size = 0;
				std::for_each(thingy.m_obj_value.vptr(), thingy.m_obj_value.vptr() + thingy.size_used, [t = this, &total_size](std::vector<float> const& obj) {
					total_size += t->serialize_size(obj);
				} );
				dcon::record_header header(total_size, "std::vector<float>", "thingy", "obj_value");
				header.serialize(output_buffer);
				std::for_each(thingy.m_obj_value.vptr(), thingy.m_obj_value.vptr() + thingy.size_used, [t = this, &output_buffer](std::vector<float> const& obj){ t->serialize(output_buffer, obj); });
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
								if(header.is_property("obj_value")) {
									if(header.is_type("std::vector<float>")) {
										std::byte const* icpy = input_buffer;
										for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy.size_used; ++i) {
											deserialize(icpy, thingy.m_obj_value.vptr()[i], input_buffer + header.record_size);
										}
										serialize_selection.thingy_obj_value = true;
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
								if(header.is_property("obj_value") && mask.thingy_obj_value) {
									if(header.is_type("std::vector<float>")) {
										std::byte const* icpy = input_buffer;
										for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy.size_used; ++i) {
											deserialize(icpy, thingy.m_obj_value.vptr()[i], input_buffer + header.record_size);
										}
										serialize_selection.thingy_obj_value = true;
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
	DCON_RELEASE_INLINE std::vector<float>& thingy_fat_id::get_obj_value() const noexcept {
		return container.thingy_get_obj_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_obj_value(std::vector<float> const& v) const noexcept {
		container.thingy_set_obj_value(id, v);
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
	DCON_RELEASE_INLINE std::vector<float> const& thingy_const_fat_id::get_obj_value() const noexcept {
		return container.thingy_get_obj_value(id);
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
		
	};


}

#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif

