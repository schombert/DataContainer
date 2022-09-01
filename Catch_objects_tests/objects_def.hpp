#pragma once
#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
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
		bool thingy : 1;
		bool thingy_some_value : 1;
		bool thingy_bf_value : 1;
		bool thingy_bool_value : 1;
		bool thingy_d_value : 1;
		bool thingy_dbf_value : 1;
		bool thingy_obj_value : 1;
		bool thingy_pooled_v : 1;
		bool thingy_big_array : 1;
		bool thingy_big_array_bf : 1;
		bool thingy2 : 1;
		bool thingy2_some_value : 1;
		bool thingy2_bf_value : 1;
		bool thingy2_d_value : 1;
		bool thingy2_dbf_value : 1;
		bool thingy2_obj_value : 1;
		bool thingy2_pooled_v : 1;
		bool thingy2_big_array : 1;
		bool thingy2_big_array_bf : 1;
		load_record() {
			thingy = false;
			thingy_some_value = false;
			thingy_bf_value = false;
			thingy_bool_value = false;
			thingy_d_value = false;
			thingy_dbf_value = false;
			thingy_obj_value = false;
			thingy_pooled_v = false;
			thingy_big_array = false;
			thingy_big_array_bf = false;
			thingy2 = false;
			thingy2_some_value = false;
			thingy2_bf_value = false;
			thingy2_d_value = false;
			thingy2_dbf_value = false;
			thingy2_obj_value = false;
			thingy2_pooled_v = false;
			thingy2_big_array = false;
			thingy2_big_array_bf = false;
		}
	};
	//
	// definition of strongly typed index for thingy_id
	//
	class thingy_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
	
		uint16_t value;
	
		explicit constexpr thingy_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr thingy_id(thingy_id const& v) noexcept = default;
		constexpr thingy_id(thingy_id&& v) noexcept = default;
		constexpr thingy_id() noexcept : value(uint16_t(0)) {}
	
		thingy_id& operator=(thingy_id v) noexcept { value = v.value; return *this; }
		constexpr bool operator==(thingy_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingy_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
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
	// definition of strongly typed index for thingy2_id
	//
	class thingy2_id {
		public:
		using value_base_t = uint32_t;
		using zero_is_null_t = std::true_type;
	
		uint32_t value;
	
		explicit constexpr thingy2_id(uint32_t v) noexcept : value(v + 1) {}
		constexpr thingy2_id(thingy2_id const& v) noexcept = default;
		constexpr thingy2_id(thingy2_id&& v) noexcept = default;
		constexpr thingy2_id() noexcept : value(uint32_t(0)) {}
	
		thingy2_id& operator=(thingy2_id v) noexcept { value = v.value; return *this; }
		constexpr bool operator==(thingy2_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingy2_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint32_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class thingy2_id_pair {
		public:
		thingy2_id left;
		thingy2_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(thingy2_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::thingy_id> {
		using type = tagged_vector<dcon::thingy_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::thingy2_id> {
		using type = tagged_vector<dcon::thingy2_id>;
	};
	
}

#endif
namespace dcon {
	class data_container;

	namespace internal {
		class alignas(64) thingy_class {
			private:
			//
			// storage space for some_value of type int32_t
			//
			struct alignas(64) dtype_some_value {
				uint8_t padding[(63 + sizeof(int32_t)) & ~63ui64];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_some_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))); }
			}
			m_some_value;
			
			//
			// storage space for bf_value of type dcon::bitfield_type
			//
			struct alignas(64) dtype_bf_value {
				uint8_t padding[(63 + sizeof(dcon::bitfield_type)) & ~63ui64];
				dcon::bitfield_type values[((uint32_t(1200 + 7)) / 8ui32 + 63ui32) & ~63ui32];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_bf_value() { std::uninitialized_value_construct_n(values - 1, 1 + ((uint32_t(1200 + 7)) / 8ui32 + 63ui32) & ~63ui32); }
			}
			m_bf_value;
			
			//
			// storage space for bool_value of type bool
			//
			struct alignas(64) dtype_bool_value {
				uint8_t padding[(63 + sizeof(bool)) & ~63ui64];
				bool values[(sizeof(bool) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(bool))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(bool)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_bool_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(bool) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(bool))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(bool)) - 1ui32) : uint32_t(1200))); }
			}
			m_bool_value;
			
			//
			// storage space for obj_value of type std::vector<float>
			//
			struct dtype_obj_value {
				std::vector<float> values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_obj_value() { std::uninitialized_value_construct_n(values, 1200); }
			}
			m_obj_value;
			
			//
			// storage space for pooled_v of type dcon::stable_mk_2_tag
			//
			struct dtype_pooled_v {
				dcon::stable_mk_2_tag values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_pooled_v() { std::uninitialized_fill_n(values, 1200, std::numeric_limits<dcon::stable_mk_2_tag>::max()); }
			}
			m_pooled_v;
			
			dcon::stable_variable_vector_storage_mk_2<int16_t, 16, 1000 > pooled_v_storage;
			//
			// storage space for big_array of type array of float
			//
			struct dtype_big_array {
				std::byte* values = nullptr;
				uint32_t size = 0;
				DCON_RELEASE_INLINE auto vptr(int32_t i) const {
					return reinterpret_cast<float const*>(values + ((63ui64 + sizeof(float)) & ~63ui64) + i * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
				}
				DCON_RELEASE_INLINE auto vptr(int32_t i) {
					return reinterpret_cast<float*>(values + ((63ui64 + sizeof(float)) & ~63ui64) + i * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
				}
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t) {
					std::byte* temp = (std::byte*)(::operator new(((63ui64 + sizeof(float)) & ~63ui64) + sz * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)), std::align_val_t{ 64 }));
					if(sz > size) {
						if(values) {
							std::memcpy(temp, values, ((63ui64 + sizeof(float)) & ~63ui64) + size * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
							std::memset(temp + ((63ui64 + sizeof(float)) & ~63ui64) + size * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)), 0, (sz - size) * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
						} else {
							std::memset(temp, 0, ((63ui64 + sizeof(float)) & ~63ui64) + sz * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
						}
					} else {
						std::memcpy(temp, values, ((63ui64 + sizeof(float)) & ~63ui64) + sz * (sizeof(float) * 1200 + 64ui64 - ((sizeof(float) * 1200) & 63ui64) + ((sizeof(float) + 63ui64) & ~63ui64)));
					}
					::operator delete(values, std::align_val_t{ 64 });
					values = temp;
					size = sz;
				}
				~dtype_big_array() { ::operator delete(values, std::align_val_t{ 64 }); }
				DCON_RELEASE_INLINE void copy_value(int32_t dest, int32_t source) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						vptr(i)[dest] = vptr(i)[source];
					}
				}
				DCON_RELEASE_INLINE void zero_at(int32_t dest) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						vptr(i)[dest] = float{};
					}
				}
			}
			m_big_array;
			
			//
			// storage space for big_array_bf of type array of dcon::bitfield_type
			//
			struct dtype_big_array_bf {
				std::byte* values = nullptr;
				uint32_t size = 0;
				DCON_RELEASE_INLINE auto vptr(int32_t i) const {
					return reinterpret_cast<dcon::bitfield_type const*>(values + ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + i * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
				}
				DCON_RELEASE_INLINE auto vptr(int32_t i) {
					return reinterpret_cast<dcon::bitfield_type*>(values + ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + i * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
				}
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t) {
					std::byte* temp = (std::byte*)(::operator new(((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + sz * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ), std::align_val_t{ 64 }));
					if(sz > size) {
						if(values) {
							std::memcpy(temp, values, ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + size * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
							std::memset(temp + ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + size * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ), 0, (sz - size) * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
						} else {
							std::memset(temp, 0, ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + sz * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
						}
					} else {
						std::memcpy(temp, values, ((63ui64 + sizeof(dcon::bitfield_type)) & ~63ui64) + sz * ( (1200 + 7) / 8 + 64ui64 - (( (1200 + 7) / 8) & 63ui64) ));
					}
					::operator delete(values, std::align_val_t{ 64 });
					values = temp;
					size = sz;
				}
				~dtype_big_array_bf() { ::operator delete(values, std::align_val_t{ 64 }); }
				DCON_RELEASE_INLINE void copy_value(int32_t dest, int32_t source) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						dcon::bit_vector_set(vptr(i), dest, dcon::bit_vector_test(vptr(i), source));
					}
				}
				DCON_RELEASE_INLINE void zero_at(int32_t dest) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						dcon::bit_vector_set(vptr(i), dest, false);
					}
				}
			}
			m_big_array_bf;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

		class alignas(64) thingy2_class {
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
			struct dtype_pooled_v {
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
					values.resize(sz);
					for(uint32_t i = size; i < sz; ++i) values[i].resize(container_size + 1);
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
					values.resize(sz);
					for(uint32_t i = size; i < sz; ++i) values[i].resize((container_size + 7) / 8 + 1);
					size = sz;
				}
				DCON_RELEASE_INLINE void emplace_back_all(uint32_t newsz) {
					for(auto& v : values) {
						v.resize(1 + (newsz + 7) / 8);
					}
				}
				DCON_RELEASE_INLINE void copy_value(int32_t dest, int32_t source) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						dcon::bit_vector_set(vptr(i), dest, dcon::bit_vector_test(vptr(i), source));
					}
				}
				DCON_RELEASE_INLINE void pop_back_all(uint32_t vsize) {
					for(auto& v : values) {
						v.resize(1 + (vsize + 6) / 8);
					}
				}
				DCON_RELEASE_INLINE void zero_at(int32_t dest) {
					for(int32_t i = 0; i < int32_t(size); ++i) {
						dcon::bit_vector_set(vptr(i), dest, false);
					}
				}
			}
			m_big_array_bf;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

	}

	class alignas(64) data_container {
		public:
		internal::thingy_class thingy;
		internal::thingy2_class thingy2;

		//
		// getters for thingy: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingy_get_some_value(thingy_id id) const noexcept {
			return thingy.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingy_get_some_value(thingy_id id) noexcept {
			return thingy.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy_get_some_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_some_value.vptr());
		}
		#endif
		
		//
		// setters for thingy: some_value
		//
		DCON_RELEASE_INLINE void thingy_set_some_value(thingy_id id, int32_t value) noexcept {
			thingy.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_some_value(ve::contiguous_tags<thingy_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
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
		// getters for thingy: bf_value
		//
		DCON_RELEASE_INLINE bool thingy_get_bf_value(thingy_id id) const noexcept {
			return dcon::bit_vector_test(thingy.m_bf_value.vptr(), id.index());
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_bf_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bf_value.vptr());
		}
		#endif
		
		//
		// setters for thingy: bf_value
		//
		DCON_RELEASE_INLINE void thingy_set_bf_value(thingy_id id, bool value) noexcept {
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id.index(), value);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_bf_value(ve::contiguous_tags<thingy_id> id, ve::vbitfield_type values) noexcept {
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
		// getters for thingy: bool_value
		//
		DCON_RELEASE_INLINE bool const& thingy_get_bool_value(thingy_id id) const noexcept {
			return thingy.m_bool_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE bool& thingy_get_bool_value(thingy_id id) noexcept {
			return thingy.m_bool_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<bool> thingy_get_bool_value(ve::contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bool_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<bool> thingy_get_bool_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bool_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<bool> thingy_get_bool_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_bool_value.vptr());
		}
		#endif
		
		//
		// setters for thingy: bool_value
		//
		DCON_RELEASE_INLINE void thingy_set_bool_value(thingy_id id, bool value) noexcept {
			thingy.m_bool_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_bool_value(ve::contiguous_tags<thingy_id> id, ve::value_to_vector_type<bool> values) noexcept {
			ve::store(id, thingy.m_bool_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_bool_value(ve::partial_contiguous_tags<thingy_id> id, ve::value_to_vector_type<bool> values) noexcept {
			ve::store(id, thingy.m_bool_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_bool_value(ve::tagged_vector<thingy_id> id, ve::value_to_vector_type<bool> values) noexcept {
			ve::store(id, thingy.m_bool_value.vptr(), values);
		}
		#endif
		
		//
		// getters for thingy: obj_value
		//
		DCON_RELEASE_INLINE std::vector<float> const& thingy_get_obj_value(thingy_id id) const noexcept {
			return thingy.m_obj_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE std::vector<float>& thingy_get_obj_value(thingy_id id) noexcept {
			return thingy.m_obj_value.vptr()[id.index()];
		}
		
		//
		// setters for thingy: obj_value
		//
		DCON_RELEASE_INLINE void thingy_set_obj_value(thingy_id id, std::vector<float> const& value) noexcept {
			thingy.m_obj_value.vptr()[id.index()] = value;
		}
		
		//
		// getters for thingy: pooled_v (special array)
		//
		std::pair<int16_t*, int16_t*> thingy_get_pooled_v_range(thingy_id id) const noexcept {
			return dcon::get_range(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		int16_t& thingy_get_pooled_v_at(thingy_id id, uint32_t inner_index) const noexcept {
			return dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], inner_index);
		}
		uint32_t thingy_get_pooled_v_capacity(thingy_id id) const noexcept {
			return dcon::get_capacity(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		uint32_t thingy_get_pooled_v_size(thingy_id id) const noexcept {
			return dcon::get_size(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		bool thingy_pooled_v_contains(thingy_id id, int16_t obj) const noexcept {
			return dcon::contains_item(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], obj);
		}
		
		//
		// setters for thingy: pooled_v (special array)
		//
		void thingy_pooled_v_push_back(thingy_id id, int16_t obj) noexcept {
			dcon::push_back(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy_pooled_v_pop_back(thingy_id id) noexcept {
			dcon::pop_back(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()]);
		}
		void thingy_pooled_v_add_unique(thingy_id id, int16_t obj) noexcept {
			dcon::add_unique_item(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy_pooled_v_remove_unique(thingy_id id, int16_t obj) noexcept {
			dcon::remove_unique_item(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy_pooled_v_clear(thingy_id id) noexcept {
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id.index()]);
		}
		void thingy_pooled_v_remove_at(thingy_id id, uint32_t inner_index) noexcept {
			dcon::remove_at(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[id.index()], inner_index);
		}
		
		//
		// getters for thingy: big_array
		//
		DCON_RELEASE_INLINE float const& thingy_get_big_array(thingy_id id, int32_t n) const noexcept {
			return thingy.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE float& thingy_get_big_array(thingy_id id, int32_t n) noexcept {
			return thingy.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE uint32_t thingy_get_big_array_size() const noexcept {
			return thingy.m_big_array.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::partial_contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_big_array(ve::tagged_vector<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array.vptr(dcon::get_index(n)));
		}
		#endif
		
		//
		// setters for thingy: big_array
		//
		DCON_RELEASE_INLINE void thingy_set_big_array(thingy_id id, int32_t n, float value) noexcept {
			thingy.m_big_array.vptr(dcon::get_index(n))[id.index()] = value;
		}
		DCON_RELEASE_INLINE void thingy_resize_big_array(uint32_t size) noexcept {
			return thingy.m_big_array.resize(size, thingy.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::contiguous_tags<thingy_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::partial_contiguous_tags<thingy_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array(ve::tagged_vector<thingy_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_big_array.vptr(dcon::get_index(n)), values);
		}
		#endif
		
		//
		// getters for thingy: big_array_bf
		//
		DCON_RELEASE_INLINE bool thingy_get_big_array_bf(thingy_id id, int32_t n) const noexcept {
			return dcon::bit_vector_test(thingy.m_big_array_bf.vptr(dcon::get_index(n)), id.index());
		}
		DCON_RELEASE_INLINE uint32_t thingy_get_big_array_bf_size() const noexcept {
			return thingy.m_big_array_bf.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::partial_contiguous_tags<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy_get_big_array_bf(ve::tagged_vector<thingy_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		#endif
		
		//
		// setters for thingy: big_array_bf
		//
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(thingy_id id, int32_t n, bool value) noexcept {
			dcon::bit_vector_set(thingy.m_big_array_bf.vptr(dcon::get_index(n)), id.index(), value);
		}
		DCON_RELEASE_INLINE void thingy_resize_big_array_bf(uint32_t size) noexcept {
			return thingy.m_big_array_bf.resize(size, thingy.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::contiguous_tags<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::partial_contiguous_tags<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(ve::tagged_vector<thingy_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		#endif
		
		void on_create_thingy(thingy_id id);
		void on_delete_thingy(thingy_id id);
		void on_move_thingy(thingy_id new_id,thingy_id old_id);
		uint32_t thingy_size() const noexcept { return thingy.size_used; }

		//
		// getters for thingy2: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingy2_get_some_value(thingy2_id id) const noexcept {
			return thingy2.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingy2_get_some_value(thingy2_id id) noexcept {
			return thingy2.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::unaligned_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::partial_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::tagged_vector<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		#endif
		
		//
		// setters for thingy2: some_value
		//
		DCON_RELEASE_INLINE void thingy2_set_some_value(thingy2_id id, int32_t value) noexcept {
			thingy2.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::unaligned_contiguous_tags<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::partial_contiguous_tags<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::tagged_vector<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		#endif
		
		//
		// getters for thingy2: bf_value
		//
		DCON_RELEASE_INLINE bool thingy2_get_bf_value(thingy2_id id) const noexcept {
			return dcon::bit_vector_test(thingy2.m_bf_value.vptr(), id.index());
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_bf_value(ve::unaligned_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_bf_value(ve::partial_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_bf_value.vptr());
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_bf_value(ve::tagged_vector<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_bf_value.vptr());
		}
		#endif
		
		//
		// setters for thingy2: bf_value
		//
		DCON_RELEASE_INLINE void thingy2_set_bf_value(thingy2_id id, bool value) noexcept {
			dcon::bit_vector_set(thingy2.m_bf_value.vptr(), id.index(), value);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy2_set_bf_value(ve::unaligned_contiguous_tags<thingy2_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_bf_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_bf_value(ve::partial_contiguous_tags<thingy2_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_bf_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_bf_value(ve::tagged_vector<thingy2_id> id, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_bf_value.vptr(), values);
		}
		#endif
		
		//
		// getters for thingy2: obj_value
		//
		DCON_RELEASE_INLINE std::vector<float> const& thingy2_get_obj_value(thingy2_id id) const noexcept {
			return thingy2.m_obj_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE std::vector<float>& thingy2_get_obj_value(thingy2_id id) noexcept {
			return thingy2.m_obj_value.vptr()[id.index()];
		}
		
		//
		// setters for thingy2: obj_value
		//
		DCON_RELEASE_INLINE void thingy2_set_obj_value(thingy2_id id, std::vector<float> const& value) noexcept {
			thingy2.m_obj_value.vptr()[id.index()] = value;
		}
		
		//
		// getters for thingy2: pooled_v (special array)
		//
		std::pair<int16_t*, int16_t*> thingy2_get_pooled_v_range(thingy2_id id) const noexcept {
			return dcon::get_range(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()]);
		}
		int16_t& thingy2_get_pooled_v_at(thingy2_id id, uint32_t inner_index) const noexcept {
			return dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], inner_index);
		}
		uint32_t thingy2_get_pooled_v_capacity(thingy2_id id) const noexcept {
			return dcon::get_capacity(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()]);
		}
		uint32_t thingy2_get_pooled_v_size(thingy2_id id) const noexcept {
			return dcon::get_size(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()]);
		}
		bool thingy2_pooled_v_contains(thingy2_id id, int16_t obj) const noexcept {
			return dcon::contains_item(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], obj);
		}
		
		//
		// setters for thingy2: pooled_v (special array)
		//
		void thingy2_pooled_v_push_back(thingy2_id id, int16_t obj) noexcept {
			dcon::push_back(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy2_pooled_v_pop_back(thingy2_id id) noexcept {
			dcon::pop_back(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()]);
		}
		void thingy2_pooled_v_add_unique(thingy2_id id, int16_t obj) noexcept {
			dcon::add_unique_item(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy2_pooled_v_remove_unique(thingy2_id id, int16_t obj) noexcept {
			dcon::remove_unique_item(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], obj);
		}
		void thingy2_pooled_v_clear(thingy2_id id) noexcept {
			thingy2.pooled_v_storage.release(thingy2.m_pooled_v.vptr()[id.index()]);
		}
		void thingy2_pooled_v_remove_at(thingy2_id id, uint32_t inner_index) noexcept {
			dcon::remove_at(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[id.index()], inner_index);
		}
		
		//
		// getters for thingy2: big_array
		//
		DCON_RELEASE_INLINE float const& thingy2_get_big_array(thingy2_id id, int32_t n) const noexcept {
			return thingy2.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE float& thingy2_get_big_array(thingy2_id id, int32_t n) noexcept {
			return thingy2.m_big_array.vptr(dcon::get_index(n))[id.index()];
		}
		DCON_RELEASE_INLINE uint32_t thingy2_get_big_array_size() const noexcept {
			return thingy2.m_big_array.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy2_get_big_array(ve::unaligned_contiguous_tags<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy2_get_big_array(ve::partial_contiguous_tags<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy2_get_big_array(ve::tagged_vector<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array.vptr(dcon::get_index(n)));
		}
		#endif
		
		//
		// setters for thingy2: big_array
		//
		DCON_RELEASE_INLINE void thingy2_set_big_array(thingy2_id id, int32_t n, float value) noexcept {
			thingy2.m_big_array.vptr(dcon::get_index(n))[id.index()] = value;
		}
		DCON_RELEASE_INLINE void thingy2_resize_big_array(uint32_t size) noexcept {
			return thingy2.m_big_array.resize(size, thingy2.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy2_set_big_array(ve::unaligned_contiguous_tags<thingy2_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy2.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_big_array(ve::partial_contiguous_tags<thingy2_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy2.m_big_array.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_big_array(ve::tagged_vector<thingy2_id> id, int32_t n, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy2.m_big_array.vptr(dcon::get_index(n)), values);
		}
		#endif
		
		//
		// getters for thingy2: big_array_bf
		//
		DCON_RELEASE_INLINE bool thingy2_get_big_array_bf(thingy2_id id, int32_t n) const noexcept {
			return dcon::bit_vector_test(thingy2.m_big_array_bf.vptr(dcon::get_index(n)), id.index());
		}
		DCON_RELEASE_INLINE uint32_t thingy2_get_big_array_bf_size() const noexcept {
			return thingy2.m_big_array_bf.size;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_big_array_bf(ve::unaligned_contiguous_tags<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_big_array_bf(ve::partial_contiguous_tags<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		DCON_RELEASE_INLINE ve::vbitfield_type thingy2_get_big_array_bf(ve::tagged_vector<thingy2_id> id, int32_t n) const noexcept {
			return ve::load(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)));
		}
		#endif
		
		//
		// setters for thingy2: big_array_bf
		//
		DCON_RELEASE_INLINE void thingy2_set_big_array_bf(thingy2_id id, int32_t n, bool value) noexcept {
			dcon::bit_vector_set(thingy2.m_big_array_bf.vptr(dcon::get_index(n)), id.index(), value);
		}
		DCON_RELEASE_INLINE void thingy2_resize_big_array_bf(uint32_t size) noexcept {
			return thingy2.m_big_array_bf.resize(size, thingy2.size_used);
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy2_set_big_array_bf(ve::unaligned_contiguous_tags<thingy2_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_big_array_bf(ve::partial_contiguous_tags<thingy2_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_big_array_bf(ve::tagged_vector<thingy2_id> id, int32_t n, ve::vbitfield_type values) noexcept {
			ve::store(id, thingy2.m_big_array_bf.vptr(dcon::get_index(n)), values);
		}
		#endif
		
		uint32_t thingy2_size() const noexcept { return thingy2.size_used; }


		//
		// container pop_back for thingy
		//
		void pop_back_thingy() {
			if(thingy.size_used == 0) return;
			thingy_id id_removed(thingy_id::value_base_t(thingy.size_used - 1));
			on_delete_thingy(id_removed);
			thingy.m_some_value.vptr()[id_removed.index()] = int32_t{};
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), false);
			thingy.m_bool_value.vptr()[id_removed.index()] = bool{};
			thingy.m_obj_value.vptr()[id_removed.index()] = std::vector<float>{};
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_big_array.zero_at(id_removed.index());
			thingy.m_big_array_bf.zero_at(id_removed.index());
			--thingy.size_used;
		}
		
		//
		// container resize for thingy
		//
		void thingy_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 1200) std::abort();
			#else
			if(new_size > 1200) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = thingy.size_used;
			if(new_size < old_size) {
				std::fill_n(thingy.m_some_value.vptr() + new_size, old_size - new_size, int32_t{});
				for(uint32_t i = new_size; i < 8 * (((new_size + 7) / 8)); ++i) {
					dcon::bit_vector_set(thingy.m_bf_value.vptr(), i, false);
				}
				std::fill_n(thingy.m_bf_value.vptr() + (new_size + 7) / 8, (new_size + old_size - new_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});
				std::fill_n(thingy.m_bool_value.vptr() + new_size, old_size - new_size, bool{});
				std::destroy_n(thingy.m_obj_value.vptr() + new_size, old_size - new_size);
				std::uninitialized_default_construct_n(thingy.m_obj_value.vptr() + new_size, old_size - new_size);
				std::for_each(thingy.m_pooled_v.vptr() + new_size, thingy.m_pooled_v.vptr() + new_size + old_size - new_size, [t = this](dcon::stable_mk_2_tag& i){ t->thingy.pooled_v_storage.release(i); });
				for(int32_t s = 0; s < int32_t(thingy.m_big_array.size); ++s) {
					std::fill_n(thingy.m_big_array.vptr(s) + new_size, old_size - new_size, float{});
				}
				for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size); ++s) {
					for(uint32_t i = new_size; i < 8 * (((new_size + 7) / 8)); ++i) {
						dcon::bit_vector_set(thingy.m_big_array_bf.vptr(s), i, false);
					}
					std::fill_n(thingy.m_big_array_bf.vptr(s) + (new_size + 7) / 8, (new_size + old_size - new_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});
				}
			} else if(new_size > old_size) {
			}
			thingy.size_used = new_size;
		}
		
		//
		// container create for thingy
		//
		thingy_id create_thingy() {
			thingy_id new_id(thingy_id::value_base_t(thingy.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(thingy.size_used >= 1200) std::abort();
			#else
			if(thingy.size_used >= 1200) throw dcon::out_of_space{};
			#endif
			++thingy.size_used;
			on_create_thingy(new_id);
			return new_id;
		}
		
		//
		// container compactable delete for thingy
		//
		void delete_thingy(thingy_id id) {
			thingy_id id_removed = id;
			thingy_id last_id(thingy_id::value_base_t(thingy.size_used - 1));
			if(id_removed == last_id) { pop_back_thingy(); return; }
			on_delete_thingy(id_removed);
			thingy.m_some_value.vptr()[id_removed.index()] = std::move(thingy.m_some_value.vptr()[last_id.index()]);
			thingy.m_some_value.vptr()[last_id.index()] = int32_t{};
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), dcon::bit_vector_test(thingy.m_bf_value.vptr(), last_id.index()));
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), last_id.index(), false);
			thingy.m_bool_value.vptr()[id_removed.index()] = std::move(thingy.m_bool_value.vptr()[last_id.index()]);
			thingy.m_bool_value.vptr()[last_id.index()] = bool{};
			thingy.m_obj_value.vptr()[id_removed.index()] = std::move(thingy.m_obj_value.vptr()[last_id.index()]);
			thingy.m_obj_value.vptr()[last_id.index()] = std::vector<float>{};
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_pooled_v.vptr()[id_removed.index()] = std::move(thingy.m_pooled_v.vptr()[last_id.index()]);
			thingy.m_pooled_v.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingy.m_big_array.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array.zero_at(last_id.index());
			thingy.m_big_array_bf.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array_bf.zero_at(last_id.index());
			--thingy.size_used;
			on_move_thingy(id_removed, last_id);
		}
		
		bool is_valid_thingy(thingy_id id) const {
			return bool(id) && uint32_t(id.index()) < thingy.size_used;
		}
		//
		// container pop_back for thingy2
		//
		void pop_back_thingy2() {
			if(thingy2.size_used == 0) return;
			thingy2_id id_removed(thingy2_id::value_base_t(thingy2.size_used - 1));
			thingy2.m_some_value.values.pop_back();
			dcon::bit_vector_set(thingy2.m_bf_value.vptr(), id_removed.index(), false);
			thingy2.m_bf_value.values.resize(1 + (thingy2.size_used + 6) / 8);
			thingy2.m_obj_value.values.pop_back();
			thingy2.pooled_v_storage.release(thingy2.m_pooled_v.vptr()[id_removed.index()]);
			thingy2.m_pooled_v.values.pop_back();
			thingy2.m_big_array.pop_back_all(thingy2.size_used);
			thingy2.m_big_array_bf.pop_back_all(thingy2.size_used);
			--thingy2.size_used;
		}
		
		//
		// container resize for thingy2
		//
		void thingy2_resize(uint32_t new_size) {
			const uint32_t old_size = thingy2.size_used;
			if(new_size < old_size) {
				thingy2.m_some_value.values.resize(1 + new_size);
				for(uint32_t i = new_size; i < 8 * (((new_size + 7) / 8)); ++i) {
					dcon::bit_vector_set(thingy2.m_bf_value.vptr(), i, false);
				}
				thingy2.m_bf_value.values.resize(1 + (new_size + 7) / 8);
				thingy2.m_obj_value.values.resize(1 + new_size);
				std::for_each(thingy2.m_pooled_v.vptr() + new_size, thingy2.m_pooled_v.vptr() + new_size + old_size - new_size, [t = this](dcon::stable_mk_2_tag& i){ t->thingy2.pooled_v_storage.release(i); });
				thingy2.m_pooled_v.values.resize(1 + new_size);
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array.size); ++s) {
					thingy2.m_big_array.values[s].resize(1 + new_size);
				}
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array_bf.size); ++s) {
					for(uint32_t i = new_size; i < 8 * (((new_size + 7) / 8)); ++i) {
						dcon::bit_vector_set(thingy2.m_big_array_bf.vptr(s), i, false);
					}
					thingy2.m_big_array_bf.values[s].resize(1 + (new_size + 7) / 8);
				}
			} else if(new_size > old_size) {
				thingy2.m_some_value.values.resize(1 + new_size);
				thingy2.m_bf_value.values.resize(1 + (new_size + 7) / 8);
				thingy2.m_obj_value.values.resize(1 + new_size);
				thingy2.m_pooled_v.values.resize(1 + new_size, std::numeric_limits<dcon::stable_mk_2_tag>::max());
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array.size); ++s) {
					thingy2.m_big_array.values[s].resize(1 + new_size);
				}
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array_bf.size); ++s) {
					thingy2.m_big_array_bf.values[s].resize(1 + (new_size + 7) / 8);
				}
			}
			thingy2.size_used = new_size;
		}
		
		//
		// container create for thingy2
		//
		thingy2_id create_thingy2() {
			thingy2_id new_id(thingy2_id::value_base_t(thingy2.size_used));
			thingy2.m_some_value.values.emplace_back();
			thingy2.m_bf_value.values.resize(1 + (thingy2.size_used + 8) / 8);
			thingy2.m_obj_value.values.emplace_back();
			thingy2.m_pooled_v.values.push_back(std::numeric_limits<dcon::stable_mk_2_tag>::max());
			thingy2.m_big_array.emplace_back_all(thingy2.size_used + 1);
			thingy2.m_big_array_bf.emplace_back_all(thingy2.size_used + 1);
			++thingy2.size_used;
			return new_id;
		}
		
		//
		// container compactable delete for thingy2
		//
		void delete_thingy2(thingy2_id id) {
			thingy2_id id_removed = id;
			thingy2_id last_id(thingy2_id::value_base_t(thingy2.size_used - 1));
			if(id_removed == last_id) { pop_back_thingy2(); return; }
			thingy2.m_some_value.vptr()[id_removed.index()] = std::move(thingy2.m_some_value.vptr()[last_id.index()]);
			thingy2.m_some_value.values.pop_back();
			dcon::bit_vector_set(thingy2.m_bf_value.vptr(), id_removed.index(), dcon::bit_vector_test(thingy2.m_bf_value.vptr(), last_id.index()));
			dcon::bit_vector_set(thingy2.m_bf_value.vptr(), last_id.index(), false);
			thingy2.m_bf_value.values.resize(1 + (thingy2.size_used + 6) / 8);
			thingy2.m_obj_value.vptr()[id_removed.index()] = std::move(thingy2.m_obj_value.vptr()[last_id.index()]);
			thingy2.m_obj_value.values.pop_back();
			thingy2.pooled_v_storage.release(thingy2.m_pooled_v.vptr()[id_removed.index()]);
			thingy2.m_pooled_v.vptr()[id_removed.index()] = std::move(thingy2.m_pooled_v.vptr()[last_id.index()]);
			thingy2.m_pooled_v.values.pop_back();
			thingy2.m_big_array.copy_value(id_removed.index(), last_id.index());
			thingy2.m_big_array.pop_back_all(thingy2.size_used);
			thingy2.m_big_array_bf.copy_value(id_removed.index(), last_id.index());
			thingy2.m_big_array_bf.pop_back_all(thingy2.size_used);
			--thingy2.size_used;
		}
		
		bool is_valid_thingy2(thingy2_id id) const {
			return bool(id) && uint32_t(id.index()) < thingy2.size_used;
		}
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy(T&& func) {
			for(uint32_t i = 0; i < thingy.size_used; ++i) {
				thingy_id tmp(thingy_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy2(T&& func) {
			for(uint32_t i = 0; i < thingy2.size_used; ++i) {
				thingy2_id tmp(thingy2_id::value_base_t(i));
				func(tmp);
			}
		}
		

		uint64_t serialize_size(std::vector<float> const& obj) const;
		void serialize(std::byte*& output_buffer, std::vector<float> const& obj) const;
		void deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const;

		void reset() {
			thingy_resize(0);
			thingy2_resize(0);
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
			ve::execute_serial(thingy.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy(F&& functor) {
			ve::execute_parallel_exact(thingy.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, thingy2_id> thingy2_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, thingy2_id>(thingy2.size_used);
		}
		ve::vectorizable_buffer<int32_t, thingy2_id> thingy2_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, thingy2_id>(thingy2.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_thingy2(F&& functor) {
			ve::execute_serial_unaligned(thingy2.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy2(F&& functor) {
			ve::execute_parallel_unaligned(thingy2.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_some_value = true;
			result.thingy_bf_value = true;
			result.thingy_bool_value = true;
			result.thingy_d_value = true;
			result.thingy_dbf_value = true;
			result.thingy_obj_value = true;
			result.thingy_pooled_v = true;
			result.thingy_big_array = true;
			result.thingy_big_array_bf = true;
			result.thingy2 = true;
			result.thingy2_some_value = true;
			result.thingy2_bf_value = true;
			result.thingy2_d_value = true;
			result.thingy2_dbf_value = true;
			result.thingy2_obj_value = true;
			result.thingy2_pooled_v = true;
			result.thingy2_big_array = true;
			result.thingy2_big_array_bf = true;
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
			if(serialize_selection.thingy_bool_value) {
				dcon::record_header iheader(0, "uint8_t", "thingy", "bool_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(uint8_t) * thingy.size_used;
			}
			if(serialize_selection.thingy_obj_value) {
				std::for_each(thingy.m_obj_value.vptr(), thingy.m_obj_value.vptr() + thingy.size_used, [t = this, &total_size](std::vector<float> const& obj){ total_size += t->serialize_size(obj); });
				dcon::record_header iheader(0, "std::vector<float>", "thingy", "obj_value");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy_pooled_v) {
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &total_size](stable_mk_2_tag obj) {
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
				total_size += thingy.m_big_array_bf.size * (thingy.size_used + 7) / 8;
				dcon::record_header iheader(0, "$array", "thingy", "big_array_bf");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy2) {
				dcon::record_header header(0, "uint32_t", "thingy2", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.thingy2_some_value) {
				dcon::record_header iheader(0, "int32_t", "thingy2", "some_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * thingy2.size_used;
			}
			if(serialize_selection.thingy2_bf_value) {
				dcon::record_header iheader(0, "bitfield", "thingy2", "bf_value");
				total_size += iheader.serialize_size();
				total_size += (thingy2.size_used + 7) / 8;
			}
			if(serialize_selection.thingy2_obj_value) {
				std::for_each(thingy2.m_obj_value.vptr(), thingy2.m_obj_value.vptr() + thingy2.size_used, [t = this, &total_size](std::vector<float> const& obj){ total_size += t->serialize_size(obj); });
				dcon::record_header iheader(0, "std::vector<float>", "thingy2", "obj_value");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy2_pooled_v) {
				std::for_each(thingy2.m_pooled_v.vptr(), thingy2.m_pooled_v.vptr() + thingy2.size_used, [t = this, &total_size](stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy2.pooled_v_storage, obj);
					total_size += sizeof(uint16_t);
					total_size += sizeof(int16_t) * (rng.second - rng.first);
				} );
				{
					total_size += 8;
					dcon::record_header iheader(0, "stable_mk_2_tag", "thingy2", "pooled_v");
					total_size += iheader.serialize_size();
				}
			}
			if(serialize_selection.thingy2_big_array) {
				total_size += 6;
				total_size += sizeof(uint16_t);
				total_size += thingy2.m_big_array.size * sizeof(float) * thingy2.size_used;
				dcon::record_header iheader(0, "$array", "thingy2", "big_array");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy2_big_array_bf) {
				total_size += 9;
				total_size += sizeof(uint16_t);
				total_size += thingy2.m_big_array_bf.size * (thingy2.size_used + 7) / 8;
				dcon::record_header iheader(0, "$array", "thingy2", "big_array_bf");
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
				std::memcpy(reinterpret_cast<bitfield_type*>(output_buffer), thingy.m_bf_value.vptr(), (thingy.size_used + 7) / 8);
				output_buffer += (thingy.size_used + 7) / 8;
			}
			if(serialize_selection.thingy_bool_value) {
				dcon::record_header header(sizeof(uint8_t) * thingy.size_used, "uint8_t", "thingy", "bool_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<uint8_t*>(output_buffer), thingy.m_bool_value.vptr(), sizeof(uint8_t) * thingy.size_used);
				output_buffer += sizeof(uint8_t) * thingy.size_used;
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
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &total_size](stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy.pooled_v_storage, obj);
					total_size += sizeof(uint16_t) + sizeof(int16_t) * (rng.second - rng.first);
				} );
				total_size += 8;
				dcon::record_header header(total_size, "stable_mk_2_tag", "thingy", "pooled_v");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "int16_t", 8);
				output_buffer += 8;
				std::for_each(thingy.m_pooled_v.vptr(), thingy.m_pooled_v.vptr() + thingy.size_used, [t = this, &output_buffer](stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy.pooled_v_storage, obj);
					*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(rng.second - rng.first);
					output_buffer += sizeof(uint16_t);
					std::memcpy(reinterpret_cast<int16_t*>(output_buffer), rng.first, sizeof(int16_t) * (rng.second - rng.first));
					output_buffer += sizeof(int16_t) * (rng.second - rng.first);
				} );
			}
			if(serialize_selection.thingy_big_array) {
				dcon::record_header header(6 + sizeof(uint16_t) + sizeof(float) * thingy.size_used, "$array", "thingy", "big_array");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "float", 8);
				output_buffer += 8;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy.m_big_array.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy.m_big_array.size); ++s) {
					std::memcpy(reinterpret_cast<float*>(output_buffer), thingy.m_big_array.vptr(s), sizeof(float) * thingy.size_used);
					output_buffer +=  sizeof(float) * thingy.size_used;
				}
			}
			if(serialize_selection.thingy_big_array_bf) {
				dcon::record_header header(9 + sizeof(uint16_t) + thingy.m_big_array_bf.size * (thingy.size_used + 7) / 8, "$array", "thingy", "big_array_bf");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "bitfield", 8);
				output_buffer += 8;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy.m_big_array_bf.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy.m_big_array_bf.size); ++s) {
					std::memcpy(reinterpret_cast<bitfield_type*>(output_buffer), thingy.m_big_array_bf.vptr(s), (thingy.size_used + 7) / 8);
					output_buffer += (thingy.size_used + 7) / 8;
				}
			}
			if(serialize_selection.thingy2) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "thingy2", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = thingy2.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.thingy2_some_value) {
				dcon::record_header header(sizeof(int32_t) * thingy2.size_used, "int32_t", "thingy2", "some_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int32_t*>(output_buffer), thingy2.m_some_value.vptr(), sizeof(int32_t) * thingy2.size_used);
				output_buffer += sizeof(int32_t) * thingy2.size_used;
			}
			if(serialize_selection.thingy2_bf_value) {
				dcon::record_header header((thingy2.size_used + 7) / 8, "bitfield", "thingy2", "bf_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<bitfield_type*>(output_buffer), thingy2.m_bf_value.vptr(), (thingy2.size_used + 7) / 8);
				output_buffer += (thingy2.size_used + 7) / 8;
			}
			if(serialize_selection.thingy2_obj_value) {
				size_t total_size = 0;
				std::for_each(thingy2.m_obj_value.vptr(), thingy2.m_obj_value.vptr() + thingy2.size_used, [t = this, &total_size](std::vector<float> const& obj) {
					total_size += t->serialize_size(obj);
				} );
				dcon::record_header header(total_size, "std::vector<float>", "thingy2", "obj_value");
				header.serialize(output_buffer);
				std::for_each(thingy2.m_obj_value.vptr(), thingy2.m_obj_value.vptr() + thingy2.size_used, [t = this, &output_buffer](std::vector<float> const& obj){ t->serialize(output_buffer, obj); });
			}
			if(serialize_selection.thingy2_pooled_v) {
				size_t total_size = 0;
				std::for_each(thingy2.m_pooled_v.vptr(), thingy2.m_pooled_v.vptr() + thingy2.size_used, [t = this, &total_size](stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy2.pooled_v_storage, obj);
					total_size += sizeof(uint16_t) + sizeof(int16_t) * (rng.second - rng.first);
				} );
				total_size += 8;
				dcon::record_header header(total_size, "stable_mk_2_tag", "thingy2", "pooled_v");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "int16_t", 8);
				output_buffer += 8;
				std::for_each(thingy2.m_pooled_v.vptr(), thingy2.m_pooled_v.vptr() + thingy2.size_used, [t = this, &output_buffer](stable_mk_2_tag obj) {
					auto rng = dcon::get_range(t->thingy2.pooled_v_storage, obj);
					*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(rng.second - rng.first);
					output_buffer += sizeof(uint16_t);
					std::memcpy(reinterpret_cast<int16_t*>(output_buffer), rng.first, sizeof(int16_t) * (rng.second - rng.first));
					output_buffer += sizeof(int16_t) * (rng.second - rng.first);
				} );
			}
			if(serialize_selection.thingy2_big_array) {
				dcon::record_header header(6 + sizeof(uint16_t) + sizeof(float) * thingy2.size_used, "$array", "thingy2", "big_array");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "float", 8);
				output_buffer += 8;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy2.m_big_array.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array.size); ++s) {
					std::memcpy(reinterpret_cast<float*>(output_buffer), thingy2.m_big_array.vptr(s), sizeof(float) * thingy2.size_used);
					output_buffer +=  sizeof(float) * thingy2.size_used;
				}
			}
			if(serialize_selection.thingy2_big_array_bf) {
				dcon::record_header header(9 + sizeof(uint16_t) + thingy2.m_big_array_bf.size * (thingy2.size_used + 7) / 8, "$array", "thingy2", "big_array_bf");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<char*>(output_buffer), "bitfield", 8);
				output_buffer += 8;
				*(reinterpret_cast<uint16_t*>(output_buffer)) = uint16_t(thingy2.m_big_array_bf.size);
				output_buffer += sizeof(uint16_t);
				for(int32_t s = 0; s < int32_t(thingy2.m_big_array_bf.size); ++s) {
					std::memcpy(reinterpret_cast<bitfield_type*>(output_buffer), thingy2.m_big_array_bf.vptr(s), (thingy2.size_used + 7) / 8);
					output_buffer += (thingy2.size_used + 7) / 8;
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
					if(header.is_object("thingy")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingy_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingy = true;
						}
						else if(header.is_property("some_value")) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), header.record_size));
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
						}
						else if(header.is_property("bf_value")) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy_bf_value = true;
							}
						}
						else if(header.is_property("bool_value")) {
							if(header.is_type("uint8_t")) {
								std::memcpy(thingy.m_bool_value.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(uint8_t), header.record_size));
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
						}
						else if(header.is_property("d_value")) {
						}
						else if(header.is_property("dbf_value")) {
						}
						else if(header.is_property("obj_value")) {
							if(header.is_type("std::vector<float>")) {
								std::byte const* icpy = input_buffer;
								for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy.size_used; ++i) {
									deserialize(icpy, thingy.m_obj_value.vptr()[i], input_buffer + header.record_size);
								}
								serialize_selection.thingy_obj_value = true;
							}
						}
						else if(header.is_property("pooled_v")) {
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy) + ii));
											icpy += sizeof(double);
										}
										++ix;
									}
									serialize_selection.thingy_pooled_v = true;
								}
							}
						}
						else if(header.is_property("big_array")) {
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
							}
						}
						else if(header.is_property("big_array_bf")) {
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
										std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy.size_used + 7) / 8;
									}
									serialize_selection.thingy_big_array_bf = true;
								}
							}
						}
					} else
					if(header.is_object("thingy2")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingy2_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingy2 = true;
						}
						else if(header.is_property("some_value")) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingy2.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy2.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
						}
						else if(header.is_property("bf_value")) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy2.m_bf_value.vptr(), reinterpret_cast<bitfield_type const*>(input_buffer), std::min(size_t(thingy2.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy2_bf_value = true;
							}
						}
						else if(header.is_property("d_value")) {
						}
						else if(header.is_property("dbf_value")) {
						}
						else if(header.is_property("obj_value")) {
							if(header.is_type("std::vector<float>")) {
								std::byte const* icpy = input_buffer;
								for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy2.size_used; ++i) {
									deserialize(icpy, thingy2.m_obj_value.vptr()[i], input_buffer + header.record_size);
								}
								serialize_selection.thingy2_obj_value = true;
							}
						}
						else if(header.is_property("pooled_v")) {
							if(header.is_type("stable_mk_2_tag")) {
								uint32_t ix = 0;
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int16_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::load_range(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], reinterpret_cast<int16_t const*>(icpy), reinterpret_cast<int16_t const*>(icpy) + sz);
										icpy += sz * sizeof(int16_t);
										++ix;
									}
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int8_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy) + ii));
											icpy += sizeof(int8_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint8_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy) + ii));
											icpy += sizeof(uint8_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint16_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy) + ii));
											icpy += sizeof(uint16_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int32_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy) + ii));
											icpy += sizeof(int32_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint32_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy) + ii));
											icpy += sizeof(uint32_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int64_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy) + ii));
											icpy += sizeof(int64_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint64_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy) + ii));
											icpy += sizeof(uint64_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(float) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy) + ii));
											icpy += sizeof(float);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(double) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy) + ii));
											icpy += sizeof(double);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
							}
						}
						else if(header.is_property("big_array")) {
							if(header.is_type("$array")) {
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								std::byte const* icpy = zero_pos + 1;
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
									if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
										thingy2.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy2.size_used);
										icpy += sizeof(uint16_t);
									} else {
										thingy2.m_big_array.resize(0, thingy2.size_used);
									}
									for(int32_t s = 0; s < int32_t(thingy2.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
										std::memcpy(thingy2.m_big_array.vptr(s), reinterpret_cast<float const*>(icpy), std::min(sizeof(float) * thingy2.size_used, size_t(input_buffer + header.record_size - icpy)));
										icpy += sizeof(float) * thingy2.size_used;
									}
									serialize_selection.thingy2_big_array = true;
								}
							}
						}
						else if(header.is_property("big_array_bf")) {
							if(header.is_type("$array")) {
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								std::byte const* icpy = zero_pos + 1;
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "bitfield")) {
									if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
										thingy2.m_big_array_bf.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy2.size_used);
										icpy += sizeof(uint16_t);
									} else {
										thingy2.m_big_array_bf.resize(0, thingy2.size_used);
									}
									for(int32_t s = 0; s < int32_t(thingy2.m_big_array_bf.size) && icpy < input_buffer + header.record_size; ++s) {
										std::memcpy(thingy2.m_big_array_bf.vptr(s), reinterpret_cast<bitfield_type const*>(icpy), std::min(size_t(thingy2.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy2.size_used + 7) / 8;
									}
									serialize_selection.thingy2_big_array_bf = true;
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
					if(header.is_object("thingy") && mask.thingy) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingy_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingy = true;
						}
						else if(header.is_property("some_value") && mask.thingy_some_value) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), header.record_size));
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
						}
						else if(header.is_property("bf_value") && mask.thingy_bf_value) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy_bf_value = true;
							}
						}
						else if(header.is_property("bool_value") && mask.thingy_bool_value) {
							if(header.is_type("uint8_t")) {
								std::memcpy(thingy.m_bool_value.vptr(), reinterpret_cast<uint8_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(uint8_t), header.record_size));
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_bool_value.vptr()[i] = bool(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_bool_value = true;
							}
						}
						else if(header.is_property("d_value") && mask.thingy_d_value) {
						}
						else if(header.is_property("dbf_value") && mask.thingy_dbf_value) {
						}
						else if(header.is_property("obj_value") && mask.thingy_obj_value) {
							if(header.is_type("std::vector<float>")) {
								std::byte const* icpy = input_buffer;
								for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy.size_used; ++i) {
									deserialize(icpy, thingy.m_obj_value.vptr()[i], input_buffer + header.record_size);
								}
								serialize_selection.thingy_obj_value = true;
							}
						}
						else if(header.is_property("pooled_v") && mask.thingy_pooled_v) {
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy) + ii));
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
											dcon::get(thingy.pooled_v_storage, thingy.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy) + ii));
											icpy += sizeof(double);
										}
										++ix;
									}
									serialize_selection.thingy_pooled_v = true;
								}
							}
						}
						else if(header.is_property("big_array") && mask.thingy_big_array) {
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
							}
						}
						else if(header.is_property("big_array_bf") && mask.thingy_big_array_bf) {
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
										std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy.size_used + 7) / 8;
									}
									serialize_selection.thingy_big_array_bf = true;
								}
							}
						}
					} else
					if(header.is_object("thingy2") && mask.thingy2) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingy2_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingy2 = true;
						}
						else if(header.is_property("some_value") && mask.thingy2_some_value) {
							if(header.is_type("int32_t")) {
								std::memcpy(thingy2.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy2.size_used) * sizeof(int32_t), header.record_size));
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy2.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy2.m_some_value.vptr()[i] = int32_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy2_some_value = true;
							}
						}
						else if(header.is_property("bf_value") && mask.thingy2_bf_value) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy2.m_bf_value.vptr(), reinterpret_cast<bitfield_type const*>(input_buffer), std::min(size_t(thingy2.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy2_bf_value = true;
							}
						}
						else if(header.is_property("d_value") && mask.thingy2_d_value) {
						}
						else if(header.is_property("dbf_value") && mask.thingy2_dbf_value) {
						}
						else if(header.is_property("obj_value") && mask.thingy2_obj_value) {
							if(header.is_type("std::vector<float>")) {
								std::byte const* icpy = input_buffer;
								for(uint32_t i = 0; icpy < input_buffer + header.record_size && i < thingy2.size_used; ++i) {
									deserialize(icpy, thingy2.m_obj_value.vptr()[i], input_buffer + header.record_size);
								}
								serialize_selection.thingy2_obj_value = true;
							}
						}
						else if(header.is_property("pooled_v") && mask.thingy2_pooled_v) {
							if(header.is_type("stable_mk_2_tag")) {
								uint32_t ix = 0;
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int16_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int16_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::load_range(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], reinterpret_cast<int16_t const*>(icpy), reinterpret_cast<int16_t const*>(icpy) + sz);
										icpy += sz * sizeof(int16_t);
										++ix;
									}
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int8_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int8_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int8_t const*>(icpy) + ii));
											icpy += sizeof(int8_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint8_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint8_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint8_t const*>(icpy) + ii));
											icpy += sizeof(uint8_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint16_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint16_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint16_t const*>(icpy) + ii));
											icpy += sizeof(uint16_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int32_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int32_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int32_t const*>(icpy) + ii));
											icpy += sizeof(int32_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint32_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint32_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint32_t const*>(icpy) + ii));
											icpy += sizeof(uint32_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "int64_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(int64_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<int64_t const*>(icpy) + ii));
											icpy += sizeof(int64_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "uint64_t")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(uint64_t) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<uint64_t const*>(icpy) + ii));
											icpy += sizeof(uint64_t);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(float) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<float const*>(icpy) + ii));
											icpy += sizeof(float);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
								else if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "double")) {
									for(std::byte const* icpy = zero_pos + 1; ix < thingy2.size_used && icpy < input_buffer + header.record_size; ) {
										uint16_t sz = 0;
										if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
											sz = uint16_t(std::min(size_t(*(reinterpret_cast<uint16_t const*>(icpy))), (input_buffer + header.record_size - (icpy + sizeof(uint16_t))) / sizeof(double) ));
											icpy += sizeof(uint16_t);
										}
										dcon::resize(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], sz);
										for(uint32_t ii = 0; ii < sz && icpy < input_buffer + header.record_size; ++ii) {
											dcon::get(thingy2.pooled_v_storage, thingy2.m_pooled_v.vptr()[ix], ii) = int16_t(*(reinterpret_cast<double const*>(icpy) + ii));
											icpy += sizeof(double);
										}
										++ix;
									}
									serialize_selection.thingy2_pooled_v = true;
								}
							}
						}
						else if(header.is_property("big_array") && mask.thingy2_big_array) {
							if(header.is_type("$array")) {
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								std::byte const* icpy = zero_pos + 1;
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "float")) {
									if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
										thingy2.m_big_array.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy2.size_used);
										icpy += sizeof(uint16_t);
									} else {
										thingy2.m_big_array.resize(0, thingy2.size_used);
									}
									for(int32_t s = 0; s < int32_t(thingy2.m_big_array.size) && icpy < input_buffer + header.record_size; ++s) {
										std::memcpy(thingy2.m_big_array.vptr(s), reinterpret_cast<float const*>(icpy), std::min(sizeof(float) * thingy2.size_used, size_t(input_buffer + header.record_size - icpy)));
										icpy += sizeof(float) * thingy2.size_used;
									}
									serialize_selection.thingy2_big_array = true;
								}
							}
						}
						else if(header.is_property("big_array_bf") && mask.thingy2_big_array_bf) {
							if(header.is_type("$array")) {
								std::byte const* zero_pos = std::find(input_buffer, input_buffer + header.record_size, std::byte(0));
								std::byte const* icpy = zero_pos + 1;
								if(dcon::char_span_equals_str(reinterpret_cast<char const*>(input_buffer), reinterpret_cast<char const*>(zero_pos), "bitfield")) {
									if(icpy + sizeof(uint16_t) <= input_buffer + header.record_size) {
										thingy2.m_big_array_bf.resize(*(reinterpret_cast<uint16_t const*>(icpy)), thingy2.size_used);
										icpy += sizeof(uint16_t);
									} else {
										thingy2.m_big_array_bf.resize(0, thingy2.size_used);
									}
									for(int32_t s = 0; s < int32_t(thingy2.m_big_array_bf.size) && icpy < input_buffer + header.record_size; ++s) {
										std::memcpy(thingy2.m_big_array_bf.vptr(s), reinterpret_cast<bitfield_type const*>(icpy), std::min(size_t(thingy2.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy2.size_used + 7) / 8;
									}
									serialize_selection.thingy2_big_array_bf = true;
								}
							}
						}
					}
				}
				input_buffer += header.record_size;
			}
		}
		

		int32_t counter = 0;
	};

}

#undef DCON_RELEASE_INLINE
#pragma warning( pop )

