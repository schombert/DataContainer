#pragma once

//
// This file was automatically generated from: old_ser.txt
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
#include "unordered_dense.h"

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

namespace os {
	struct load_record {
		bool thingy : 1;
		bool thingy_i_value : 1;
		bool thingy_f_value : 1;
		bool thingy_bf_value : 1;
		bool thingy_d_value : 1;
		bool thingy_obj_value : 1;
		bool thingy_pooled_v : 1;
		bool thingy_big_array : 1;
		bool thingy_big_array_bf : 1;
		bool thingy_custom_struct : 1;
		bool thingy2 : 1;
		bool thingy2_some_value : 1;
		bool dummy_rel : 1;
		bool dummy_rel_left : 1;
		bool dummy_rel_right : 1;
		load_record() {
			thingy = false;
			thingy_i_value = false;
			thingy_f_value = false;
			thingy_bf_value = false;
			thingy_d_value = false;
			thingy_obj_value = false;
			thingy_pooled_v = false;
			thingy_big_array = false;
			thingy_big_array_bf = false;
			thingy_custom_struct = false;
			thingy2 = false;
			thingy2_some_value = false;
			dummy_rel = false;
			dummy_rel_left = false;
			dummy_rel_right = false;
		}
	};
	//
	// definition of strongly typed index for thingy_id
	//
	class thingy_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr thingy_id() noexcept = default;
		explicit constexpr thingy_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr thingy_id(thingy_id const& v) noexcept = default;
		constexpr thingy_id(thingy_id&& v) noexcept = default;
		
		thingy_id& operator=(thingy_id const& v) noexcept = default;
		thingy_id& operator=(thingy_id&& v) noexcept = default;
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
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr thingy2_id() noexcept = default;
		explicit constexpr thingy2_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr thingy2_id(thingy2_id const& v) noexcept = default;
		constexpr thingy2_id(thingy2_id&& v) noexcept = default;
		
		thingy2_id& operator=(thingy2_id const& v) noexcept = default;
		thingy2_id& operator=(thingy2_id&& v) noexcept = default;
		constexpr bool operator==(thingy2_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(thingy2_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
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
	
	//
	// definition of strongly typed index for dummy_rel_id
	//
	class dummy_rel_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr dummy_rel_id() noexcept = default;
		explicit constexpr dummy_rel_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr dummy_rel_id(dummy_rel_id const& v) noexcept = default;
		constexpr dummy_rel_id(dummy_rel_id&& v) noexcept = default;
		
		dummy_rel_id& operator=(dummy_rel_id const& v) noexcept = default;
		dummy_rel_id& operator=(dummy_rel_id&& v) noexcept = default;
		constexpr bool operator==(dummy_rel_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(dummy_rel_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class dummy_rel_id_pair {
		public:
		dummy_rel_id left;
		dummy_rel_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(dummy_rel_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<os::thingy_id> {
		using type = tagged_vector<os::thingy_id>;
	};
	
	template<>
	struct value_to_vector_type_s<os::thingy2_id> {
		using type = tagged_vector<os::thingy2_id>;
	};
	
	template<>
	struct value_to_vector_type_s<os::dummy_rel_id> {
		using type = tagged_vector<os::dummy_rel_id>;
	};
	
}

#endif
namespace os {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class alignas(64) thingy_class {
			private:
			//
			// storage space for i_value of type int16_t
			//
			struct alignas(64) dtype_i_value {
				uint8_t padding[(63 + sizeof(int16_t)) & ~uint64_t(63)];
				int16_t values[(sizeof(int16_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int16_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int16_t)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_i_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int16_t) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(int16_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int16_t)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_i_value;
			
			//
			// storage space for f_value of type float
			//
			struct alignas(64) dtype_f_value {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_f_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_f_value;
			
			//
			// storage space for bf_value of type dcon::bitfield_type
			//
			struct alignas(64) dtype_bf_value {
				uint8_t padding[(63 + sizeof(dcon::bitfield_type)) & ~uint64_t(63)];
				dcon::bitfield_type values[((uint32_t(1200 + 7)) / uint32_t(8) + uint32_t(63)) & ~uint32_t(63)];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_bf_value() { std::uninitialized_value_construct_n(values - 1, 1 + ((uint32_t(1200 + 7)) / uint32_t(8) + uint32_t(63)) & ~uint32_t(63)); }
			}
			m_bf_value;
			
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
					return reinterpret_cast<float const*>(values + ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + i * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
				}
				DCON_RELEASE_INLINE auto vptr(int32_t i) {
					return reinterpret_cast<float*>(values + ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + i * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
				}
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t) {
					std::byte* temp = (std::byte*)(::operator new(((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + sz * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))), std::align_val_t{ 64 }));
					if(sz > size) {
						if(values) {
							std::memcpy(temp, values, ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + size * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
							std::memset(temp + ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + size * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))), 0, (sz - size) * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
						} else {
							std::memset(temp, 0, ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + sz * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
						}
					} else {
						std::memcpy(temp, values, ((uint64_t(63) + sizeof(float)) & ~uint64_t(63)) + sz * (sizeof(float) * 1200 + uint64_t(64) - ((sizeof(float) * 1200) & uint64_t(63)) + ((sizeof(float) + uint64_t(63)) & ~uint64_t(63))));
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
					return reinterpret_cast<dcon::bitfield_type const*>(values + ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + i * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
				}
				DCON_RELEASE_INLINE auto vptr(int32_t i) {
					return reinterpret_cast<dcon::bitfield_type*>(values + ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + i * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
				}
				DCON_RELEASE_INLINE void resize(uint32_t sz, uint32_t) {
					std::byte* temp = (std::byte*)(::operator new(((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + sz * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ), std::align_val_t{ 64 }));
					if(sz > size) {
						if(values) {
							std::memcpy(temp, values, ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + size * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
							std::memset(temp + ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + size * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ), 0, (sz - size) * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
						} else {
							std::memset(temp, 0, ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + sz * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
						}
					} else {
						std::memcpy(temp, values, ((uint64_t(63) + sizeof(dcon::bitfield_type)) & ~uint64_t(63)) + sz * ( (1200 + 7) / 8 + uint64_t(64) - (( (1200 + 7) / 8) & uint64_t(63)) ));
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
			
			//
			// storage space for custom_struct of type c_struct
			//
			struct alignas(64) dtype_custom_struct {
				uint8_t padding[(63 + sizeof(c_struct)) & ~uint64_t(63)];
				c_struct values[(sizeof(c_struct) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(c_struct))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(c_struct)) - uint32_t(1)) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_custom_struct() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(c_struct) <= 64 ? (uint32_t(1200) + (uint32_t(64) / uint32_t(sizeof(c_struct))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(c_struct)) - uint32_t(1)) : uint32_t(1200))); }
			}
			m_custom_struct;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class alignas(64) thingy2_class {
			private:
			//
			// storage space for some_value of type int32_t
			//
			struct alignas(64) dtype_some_value {
				uint8_t padding[(63 + sizeof(int32_t)) & ~uint64_t(63)];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(300) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(300))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_some_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(300) + (uint32_t(64) / uint32_t(sizeof(int32_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(int32_t)) - uint32_t(1)) : uint32_t(300))); }
			}
			m_some_value;
			
			uint32_t size_used = 0;


			public:
			friend data_container;
		};

		class alignas(64) dummy_rel_class {
			private:
			//
			// storage space for left of type thingy_id
			//
			struct alignas(64) dtype_left {
				uint8_t padding[(63 + sizeof(thingy_id)) & ~uint64_t(63)];
				thingy_id values[(sizeof(thingy_id) <= 64 ? (uint32_t(300) + (uint32_t(64) / uint32_t(sizeof(thingy_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingy_id)) - uint32_t(1)) : uint32_t(300))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_left() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(thingy_id) <= 64 ? (uint32_t(300) + (uint32_t(64) / uint32_t(sizeof(thingy_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(thingy_id)) - uint32_t(1)) : uint32_t(300))); }
			}
			m_left;
			
			//
			// storage space for array_left of type std::vector<dummy_rel_id>
			//
			struct dtype_array_left {
				std::vector<dummy_rel_id> values[1200];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_array_left() { std::uninitialized_value_construct_n(values, 1200); }
			}
			m_array_left;
			
			uint32_t size_used = 0;

			ankerl::unordered_dense::map<uint32_t, dummy_rel_id, ankerl::unordered_dense::hash<uint32_t>> hashm_joint;
			uint32_t to_joint_keydata(thingy_id left_p, thingy2_id right_p) {
				uint32_t result = 0;
				result |= (uint32_t(left_p.value) << 0);
				result |= (uint32_t(right_p.value) << 9);
				return result;
			}
			

			public:
			friend data_container;
		};

	}

	class thingy_const_fat_id;
	class thingy_fat_id;
	class thingy2_const_fat_id;
	class thingy2_fat_id;
	class dummy_rel_const_fat_id;
	class dummy_rel_fat_id;
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
		DCON_RELEASE_INLINE int16_t& get_i_value() const noexcept;
		DCON_RELEASE_INLINE void set_i_value(int16_t v) const noexcept;
		DCON_RELEASE_INLINE float& get_f_value() const noexcept;
		DCON_RELEASE_INLINE void set_f_value(float v) const noexcept;
		DCON_RELEASE_INLINE bool get_bf_value() const noexcept;
		DCON_RELEASE_INLINE void set_bf_value(bool v) const noexcept;
		DCON_RELEASE_INLINE std::vector<float>& get_obj_value() const noexcept;
		DCON_RELEASE_INLINE void set_obj_value(std::vector<float> const& v) const noexcept;
		DCON_RELEASE_INLINE dcon::dcon_vv_fat_id<int16_t> get_pooled_v() const noexcept;
		DCON_RELEASE_INLINE float& get_big_array(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_size() const noexcept;
		DCON_RELEASE_INLINE void set_big_array(int32_t i, float v) const noexcept;
		DCON_RELEASE_INLINE void resize_big_array(uint32_t sz) const noexcept;
		DCON_RELEASE_INLINE bool get_big_array_bf(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_bf_size() const noexcept;
		DCON_RELEASE_INLINE void set_big_array_bf(int32_t i, bool v) const noexcept;
		DCON_RELEASE_INLINE void resize_big_array_bf(uint32_t sz) const noexcept;
		DCON_RELEASE_INLINE c_struct& get_custom_struct() const noexcept;
		DCON_RELEASE_INLINE void set_custom_struct(c_struct const& v) const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_dummy_rel_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> range_of_dummy_rel_as_left() const;
		DCON_RELEASE_INLINE void remove_all_dummy_rel_as_left() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_dummy_rel(T&& func) const;
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> range_of_dummy_rel() const;
		DCON_RELEASE_INLINE void remove_all_dummy_rel() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_dummy_rel(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_dummy_rel(thingy2_id target) const;
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
		DCON_RELEASE_INLINE int16_t get_i_value() const noexcept;
		DCON_RELEASE_INLINE float get_f_value() const noexcept;
		DCON_RELEASE_INLINE bool get_bf_value() const noexcept;
		DCON_RELEASE_INLINE std::vector<float> const& get_obj_value() const noexcept;
		DCON_RELEASE_INLINE dcon::dcon_vv_const_fat_id<int16_t> get_pooled_v() const noexcept;
		DCON_RELEASE_INLINE float get_big_array(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_size() const noexcept;
		DCON_RELEASE_INLINE bool get_big_array_bf(int32_t i) const noexcept;
		DCON_RELEASE_INLINE uint32_t get_big_array_bf_size() const noexcept;
		DCON_RELEASE_INLINE c_struct const& get_custom_struct() const noexcept;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_dummy_rel_as_left(T&& func) const;
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> range_of_dummy_rel_as_left() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_dummy_rel(T&& func) const;
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> range_of_dummy_rel() const;
		template<typename T>
		DCON_RELEASE_INLINE void for_each_right_from_dummy_rel(T&& func) const;
		DCON_RELEASE_INLINE bool has_right_from_dummy_rel(thingy2_id target) const;
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
	
	class thingy2_fat_id {
		friend data_container;
		public:
		data_container& container;
		thingy2_id id;
		thingy2_fat_id(data_container& c, thingy2_id i) noexcept : container(c), id(i) {}
		thingy2_fat_id(thingy2_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingy2_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingy2_fat_id& operator=(thingy2_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy2_fat_id& operator=(thingy2_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingy2_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy2_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy2_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy2_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t& get_some_value() const noexcept;
		DCON_RELEASE_INLINE void set_some_value(int32_t v) const noexcept;
		DCON_RELEASE_INLINE dummy_rel_fat_id get_dummy_rel_as_right() const noexcept;
		DCON_RELEASE_INLINE void remove_dummy_rel_as_right() const noexcept;
		DCON_RELEASE_INLINE dummy_rel_fat_id get_dummy_rel() const noexcept;
		DCON_RELEASE_INLINE void remove_dummy_rel() const noexcept;
		DCON_RELEASE_INLINE thingy_fat_id get_left_from_dummy_rel() const noexcept;
		DCON_RELEASE_INLINE void set_left_from_dummy_rel(thingy_id v) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE thingy2_fat_id fatten(data_container& c, thingy2_id id) noexcept {
		return thingy2_fat_id(c, id);
	}
	
	class thingy2_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		thingy2_id id;
		thingy2_const_fat_id(data_container const& c, thingy2_id i) noexcept : container(c), id(i) {}
		thingy2_const_fat_id(thingy2_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		thingy2_const_fat_id(thingy2_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator thingy2_id() const noexcept { return id; }
		DCON_RELEASE_INLINE thingy2_const_fat_id& operator=(thingy2_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy2_const_fat_id& operator=(thingy2_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE thingy2_const_fat_id& operator=(thingy2_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(thingy2_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy2_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(thingy2_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy2_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy2_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(thingy2_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE int32_t get_some_value() const noexcept;
		DCON_RELEASE_INLINE dummy_rel_const_fat_id get_dummy_rel_as_right() const noexcept;
		DCON_RELEASE_INLINE dummy_rel_const_fat_id get_dummy_rel() const noexcept;
		DCON_RELEASE_INLINE thingy_const_fat_id get_left_from_dummy_rel() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(thingy2_fat_id const& l, thingy2_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(thingy2_fat_id const& l, thingy2_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE thingy2_const_fat_id fatten(data_container const& c, thingy2_id id) noexcept {
		return thingy2_const_fat_id(c, id);
	}
	
	class dummy_rel_fat_id {
		friend data_container;
		public:
		data_container& container;
		dummy_rel_id id;
		dummy_rel_fat_id(data_container& c, dummy_rel_id i) noexcept : container(c), id(i) {}
		dummy_rel_fat_id(dummy_rel_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator dummy_rel_id() const noexcept { return id; }
		DCON_RELEASE_INLINE dummy_rel_fat_id& operator=(dummy_rel_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE dummy_rel_fat_id& operator=(dummy_rel_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(dummy_rel_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(dummy_rel_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(dummy_rel_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(dummy_rel_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingy_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE void set_left(thingy_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_left(thingy_id val) const noexcept;
		DCON_RELEASE_INLINE thingy2_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE void set_right(thingy2_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_right(thingy2_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE dummy_rel_fat_id fatten(data_container& c, dummy_rel_id id) noexcept {
		return dummy_rel_fat_id(c, id);
	}
	
	class dummy_rel_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		dummy_rel_id id;
		dummy_rel_const_fat_id(data_container const& c, dummy_rel_id i) noexcept : container(c), id(i) {}
		dummy_rel_const_fat_id(dummy_rel_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		dummy_rel_const_fat_id(dummy_rel_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator dummy_rel_id() const noexcept { return id; }
		DCON_RELEASE_INLINE dummy_rel_const_fat_id& operator=(dummy_rel_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE dummy_rel_const_fat_id& operator=(dummy_rel_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE dummy_rel_const_fat_id& operator=(dummy_rel_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(dummy_rel_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(dummy_rel_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(dummy_rel_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(dummy_rel_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(dummy_rel_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(dummy_rel_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE thingy_const_fat_id get_left() const noexcept;
		DCON_RELEASE_INLINE thingy2_const_fat_id get_right() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(dummy_rel_fat_id const& l, dummy_rel_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(dummy_rel_fat_id const& l, dummy_rel_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE dummy_rel_const_fat_id fatten(data_container const& c, dummy_rel_id id) noexcept {
		return dummy_rel_const_fat_id(c, id);
	}
	
	class alignas(64) data_container {
		public:
		internal::thingy_class thingy;
		internal::thingy2_class thingy2;
		internal::dummy_rel_class dummy_rel;

		//
		// Functions for thingy:
		//
		//
		// accessors for thingy: i_value
		//
		DCON_RELEASE_INLINE int16_t const& thingy_get_i_value(thingy_id id) const noexcept {
			return thingy.m_i_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int16_t& thingy_get_i_value(thingy_id id) noexcept {
			return thingy.m_i_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int16_t> thingy_get_i_value(ve::contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_i_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int16_t> thingy_get_i_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_i_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int16_t> thingy_get_i_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_i_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_i_value(thingy_id id, int16_t value) noexcept {
			thingy.m_i_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_i_value(ve::contiguous_tags<thingy_id> id, ve::value_to_vector_type<int16_t> values) noexcept {
			ve::store(id, thingy.m_i_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_i_value(ve::partial_contiguous_tags<thingy_id> id, ve::value_to_vector_type<int16_t> values) noexcept {
			ve::store(id, thingy.m_i_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_i_value(ve::tagged_vector<thingy_id> id, ve::value_to_vector_type<int16_t> values) noexcept {
			ve::store(id, thingy.m_i_value.vptr(), values);
		}
		#endif
		//
		// accessors for thingy: f_value
		//
		DCON_RELEASE_INLINE float const& thingy_get_f_value(thingy_id id) const noexcept {
			return thingy.m_f_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& thingy_get_f_value(thingy_id id) noexcept {
			return thingy.m_f_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_f_value(ve::contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_f_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_f_value(ve::partial_contiguous_tags<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_f_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> thingy_get_f_value(ve::tagged_vector<thingy_id> id) const noexcept {
			return ve::load(id, thingy.m_f_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingy_set_f_value(thingy_id id, float value) noexcept {
			thingy.m_f_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy_set_f_value(ve::contiguous_tags<thingy_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_f_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_f_value(ve::partial_contiguous_tags<thingy_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_f_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy_set_f_value(ve::tagged_vector<thingy_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, thingy.m_f_value.vptr(), values);
		}
		#endif
		//
		// accessors for thingy: bf_value
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
		// accessors for thingy: d_value
		//
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
		// accessors for thingy: big_array_bf
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
		DCON_RELEASE_INLINE void thingy_set_big_array_bf(thingy_id id, int32_t n, bool value) noexcept {
			dcon::bit_vector_set(thingy.m_big_array_bf.vptr(dcon::get_index(n)), id.index(), value);
		}
		DCON_RELEASE_INLINE void thingy_resize_big_array_bf(uint32_t size) noexcept {
			thingy.m_big_array_bf.resize(size, thingy.size_used);
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
		//
		// accessors for thingy: custom_struct
		//
		DCON_RELEASE_INLINE c_struct const& thingy_get_custom_struct(thingy_id id) const noexcept {
			return thingy.m_custom_struct.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE c_struct& thingy_get_custom_struct(thingy_id id) noexcept {
			return thingy.m_custom_struct.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE void thingy_set_custom_struct(thingy_id id, c_struct const& value) noexcept {
			thingy.m_custom_struct.vptr()[id.index()] = value;
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingy_for_each_dummy_rel_as_left(thingy_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = dummy_rel.m_array_left.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_range_of_dummy_rel_as_left(thingy_id id) const {
			if(bool(id)) {
				auto& vref = dummy_rel.m_array_left.vptr()[id.index()];
				return std::pair<dummy_rel_id const*, dummy_rel_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<dummy_rel_id const*, dummy_rel_id const*>(nullptr, nullptr);
			}
		}
		void thingy_remove_all_dummy_rel_as_left(thingy_id id) noexcept {
			auto rng = thingy_range_of_dummy_rel_as_left(id);
			dcon::local_vector<dummy_rel_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](dummy_rel_id i) { t->dummy_rel_set_left(i, thingy_id()); });
		}
		template<typename T>
		DCON_RELEASE_INLINE void thingy_for_each_dummy_rel(thingy_id id, T&& func) const {
			if(bool(id)) {
				auto& vref = dummy_rel.m_array_left.vptr()[id.index()];
				std::for_each(vref.begin(), vref.end(), func);
			}
		}
		DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_range_of_dummy_rel(thingy_id id) const {
			if(bool(id)) {
				auto& vref = dummy_rel.m_array_left.vptr()[id.index()];
				return std::pair<dummy_rel_id const*, dummy_rel_id const*>(vref.data(), vref.data() + vref.size());
			} else {
				return std::pair<dummy_rel_id const*, dummy_rel_id const*>(nullptr, nullptr);
			}
		}
		void thingy_remove_all_dummy_rel(thingy_id id) noexcept {
			auto rng = thingy_range_of_dummy_rel_as_left(id);
			dcon::local_vector<dummy_rel_id> temp(rng.first, rng.second);
			std::for_each(temp.begin(), temp.end(), [t = this](dummy_rel_id i) { t->dummy_rel_set_left(i, thingy_id()); });
		}
		template<typename T>
		void thingy_for_each_right_from_dummy_rel(thingy_id id, T&& func) const {
			thingy_for_each_dummy_rel_as_left(id, [&](dummy_rel_id i) {
				func(dummy_rel_get_right(i));
			} );
		}
		bool thingy_has_right_from_dummy_rel(thingy_id id, thingy2_id target) const {
			auto& vref = dummy_rel.m_array_left.vptr()[id.index()];
			for(auto pos = vref.begin(); pos != vref.end(); ++pos) {
				if(pos->index() == target.index()) return true;
			}
			return false;
		}
		DCON_RELEASE_INLINE bool thingy_is_valid(thingy_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < thingy.size_used;
		}
		
		uint32_t thingy_size() const noexcept { return thingy.size_used; }

		//
		// Functions for thingy2:
		//
		//
		// accessors for thingy2: some_value
		//
		DCON_RELEASE_INLINE int32_t const& thingy2_get_some_value(thingy2_id id) const noexcept {
			return thingy2.m_some_value.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE int32_t& thingy2_get_some_value(thingy2_id id) noexcept {
			return thingy2.m_some_value.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::partial_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<int32_t> thingy2_get_some_value(ve::tagged_vector<thingy2_id> id) const noexcept {
			return ve::load(id, thingy2.m_some_value.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void thingy2_set_some_value(thingy2_id id, int32_t value) noexcept {
			thingy2.m_some_value.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::contiguous_tags<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::partial_contiguous_tags<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		DCON_RELEASE_INLINE void thingy2_set_some_value(ve::tagged_vector<thingy2_id> id, ve::value_to_vector_type<int32_t> values) noexcept {
			ve::store(id, thingy2.m_some_value.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE dummy_rel_id thingy2_get_dummy_rel_as_right(thingy2_id id) const noexcept {
			return (id.value <= dummy_rel.size_used) ? dummy_rel_id(dummy_rel_id::value_base_t(id.index())) : dummy_rel_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<dummy_rel_id> thingy2_get_dummy_rel_as_right(ve::contiguous_tags<thingy2_id> id) const noexcept {
			return ve::contiguous_tags<dummy_rel_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<dummy_rel_id> thingy2_get_dummy_rel_as_right(ve::partial_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::partial_contiguous_tags<dummy_rel_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<dummy_rel_id> thingy2_get_dummy_rel_as_right(ve::tagged_vector<thingy2_id> id) const noexcept {
			return ve::tagged_vector<dummy_rel_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingy2_remove_dummy_rel_as_right(thingy2_id id) noexcept {
			if(dummy_rel_is_valid(dummy_rel_id(dummy_rel_id::value_base_t(id.index())))) {
				dummy_rel_set_right(dummy_rel_id(dummy_rel_id::value_base_t(id.index())), thingy2_id());
			}
		}
		DCON_RELEASE_INLINE dummy_rel_id thingy2_get_dummy_rel(thingy2_id id) const noexcept {
			return (id.value <= dummy_rel.size_used) ? dummy_rel_id(dummy_rel_id::value_base_t(id.index())) : dummy_rel_id();
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<dummy_rel_id> thingy2_get_dummy_rel(ve::contiguous_tags<thingy2_id> id) const noexcept {
			return ve::contiguous_tags<dummy_rel_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<dummy_rel_id> thingy2_get_dummy_rel(ve::partial_contiguous_tags<thingy2_id> id) const noexcept {
			return ve::partial_contiguous_tags<dummy_rel_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<dummy_rel_id> thingy2_get_dummy_rel(ve::tagged_vector<thingy2_id> id) const noexcept {
			return ve::tagged_vector<dummy_rel_id>(id, std::true_type{});
		}
		#endif
		DCON_RELEASE_INLINE void thingy2_remove_dummy_rel(thingy2_id id) noexcept {
			if(dummy_rel_is_valid(dummy_rel_id(dummy_rel_id::value_base_t(id.index())))) {
				dummy_rel_set_right(dummy_rel_id(dummy_rel_id::value_base_t(id.index())), thingy2_id());
			}
		}
		DCON_RELEASE_INLINE thingy_id thingy2_get_left_from_dummy_rel(thingy2_id ref_id) const {
			return dummy_rel_get_left(dummy_rel_id(dummy_rel_id::value_base_t(ref_id.index())));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> thingy2_get_left_from_dummy_rel(ve::contiguous_tags<thingy2_id> ref_id) const {
			return dummy_rel_get_left(ve::contiguous_tags<dummy_rel_id>(ref_id.value));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> thingy2_get_left_from_dummy_rel(ve::partial_contiguous_tags<thingy2_id> ref_id) const {
			return dummy_rel_get_left(ve::partial_contiguous_tags<dummy_rel_id>(ref_id.value, ref_id.subcount));
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> thingy2_get_left_from_dummy_rel(ve::tagged_vector<thingy2_id> ref_id) const {
			return dummy_rel_get_left(ve::tagged_vector<dummy_rel_id>(ref_id, std::true_type{}));
		}
		#endif
		void thingy2_set_left_from_dummy_rel(thingy2_id ref_id, thingy_id val) {
			dummy_rel_set_left(dummy_rel_id(dummy_rel_id::value_base_t(ref_id.index())), val);
		}
		DCON_RELEASE_INLINE bool thingy2_is_valid(thingy2_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < thingy2.size_used;
		}
		
		uint32_t thingy2_size() const noexcept { return thingy2.size_used; }

		//
		// Functions for dummy_rel:
		//
		DCON_RELEASE_INLINE thingy_id dummy_rel_get_left(dummy_rel_id id) const noexcept {
			return dummy_rel.m_left.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> dummy_rel_get_left(ve::contiguous_tags<dummy_rel_id> id) const noexcept {
			return ve::load(id, dummy_rel.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> dummy_rel_get_left(ve::partial_contiguous_tags<dummy_rel_id> id) const noexcept {
			return ve::load(id, dummy_rel.m_left.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<thingy_id> dummy_rel_get_left(ve::tagged_vector<dummy_rel_id> id) const noexcept {
			return ve::load(id, dummy_rel.m_left.vptr());
		}
		#endif
		private:
		void internal_dummy_rel_set_left(dummy_rel_id id, thingy_id value) noexcept {
			if(auto old_value = dummy_rel.m_left.vptr()[id.index()]; bool(old_value)) {
				auto& vref = dummy_rel.m_array_left.vptr()[old_value.index()];
				if(auto it = std::find(vref.begin(), vref.end(), id); it != vref.end()) {
					*it = vref.back();
					vref.pop_back();
				}
			}
			if(bool(value)) {
				dummy_rel.m_array_left.vptr()[value.index()].push_back(id);
			}
			dummy_rel.m_left.vptr()[id.index()] = value;
		}
		public:
		void dummy_rel_set_left(dummy_rel_id id, thingy_id value) noexcept {
			if(!bool(value)) {
				delete_dummy_rel(id);
				return;
			}
			dummy_rel.hashm_joint.erase( dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id.index()], thingy2_id(thingy2_id::value_base_t(id.index()))) );
			internal_dummy_rel_set_left(id, value);
			if(auto it = dummy_rel.hashm_joint.find( dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id.index()], thingy2_id(thingy2_id::value_base_t(id.index()))) ); it != dummy_rel.hashm_joint.end()) {
				delete_dummy_rel(it->second);
			}
			dummy_rel.hashm_joint.insert_or_assign(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id.index()], thingy2_id(thingy2_id::value_base_t(id.index()))), id);
		}
		bool dummy_rel_try_set_left(dummy_rel_id id, thingy_id value) noexcept {
			if(!bool(value)) {
				return false;
			}
			if(dummy_rel.hashm_joint.find( dummy_rel.to_joint_keydata(value, thingy2_id(thingy2_id::value_base_t(id.index()))) ) != dummy_rel.hashm_joint.end()) return false;
			internal_dummy_rel_set_left(id, value);
			dummy_rel.hashm_joint.insert_or_assign(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id.index()], thingy2_id(thingy2_id::value_base_t(id.index()))), id);
			return true;
		}
		DCON_RELEASE_INLINE thingy2_id dummy_rel_get_right(dummy_rel_id id) const noexcept {
			return thingy2_id(thingy2_id::value_base_t(id.index()));
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::contiguous_tags<thingy2_id> dummy_rel_get_right(ve::contiguous_tags<dummy_rel_id> id) const noexcept {
			return ve::contiguous_tags<thingy2_id>(id.value);
		}
		DCON_RELEASE_INLINE ve::partial_contiguous_tags<thingy2_id> dummy_rel_get_right(ve::partial_contiguous_tags<dummy_rel_id> id) const noexcept {
			return ve::partial_contiguous_tags<thingy2_id>(id.value, id.subcount);
		}
		DCON_RELEASE_INLINE ve::tagged_vector<thingy2_id> dummy_rel_get_right(ve::tagged_vector<dummy_rel_id> id) const noexcept {
			return ve::tagged_vector<thingy2_id>(id, std::true_type{});
		}
		#endif
		private:
		void internal_dummy_rel_set_right(dummy_rel_id id, thingy2_id value) noexcept {
			if(bool(value)) {
				delete_dummy_rel( dummy_rel_id(dummy_rel_id::value_base_t(value.index())) );
				internal_move_relationship_dummy_rel(id, dummy_rel_id(dummy_rel_id::value_base_t(value.index())) );
			}
		}
		public:
		void dummy_rel_set_right(dummy_rel_id id, thingy2_id value) noexcept {
			if(bool(value)) {
				delete_dummy_rel( dummy_rel_id(dummy_rel_id::value_base_t(value.index())) );
				internal_move_relationship_dummy_rel(id, dummy_rel_id(dummy_rel_id::value_base_t(value.index())) );
			} else {
				delete_dummy_rel(id);
			}
		}
		bool dummy_rel_try_set_right(dummy_rel_id id, thingy2_id value) noexcept {
			if(bool(value)) {
				if(dummy_rel_is_valid( dummy_rel_id(dummy_rel_id::value_base_t(value.index())) )) return false;
				internal_move_relationship_dummy_rel(id, dummy_rel_id(dummy_rel_id::value_base_t(value.index())) );
				return true;
			} else {
				return false;
			}
		}
		DCON_RELEASE_INLINE bool dummy_rel_is_valid(dummy_rel_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < dummy_rel.size_used && thingy2_is_valid(thingy2_id(thingy2_id::value_base_t(id.index()))) && (bool(dummy_rel.m_left.vptr()[id.index()]) || false);
		}
		
		uint32_t dummy_rel_size() const noexcept { return dummy_rel.size_used; }


		//
		// container pop_back for thingy
		//
		void pop_back_thingy() {
			if(thingy.size_used == 0) return;
			thingy_id id_removed(thingy_id::value_base_t(thingy.size_used - 1));
			thingy_remove_all_dummy_rel_as_left(id_removed);
			thingy.m_i_value.vptr()[id_removed.index()] = int16_t{};
			thingy.m_f_value.vptr()[id_removed.index()] = float{};
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), false);
			thingy.m_obj_value.vptr()[id_removed.index()] = std::vector<float>{};
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_big_array.zero_at(id_removed.index());
			thingy.m_big_array_bf.zero_at(id_removed.index());
			thingy.m_custom_struct.vptr()[id_removed.index()] = c_struct{};
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
				std::fill_n(thingy.m_i_value.vptr() + new_size, old_size - new_size, int16_t{});
				std::fill_n(thingy.m_f_value.vptr() + new_size, old_size - new_size, float{});
				for(uint32_t i = new_size; i < 8 * (((new_size + 7) / 8)); ++i) {
					dcon::bit_vector_set(thingy.m_bf_value.vptr(), i, false);
				}
				std::fill_n(thingy.m_bf_value.vptr() + (new_size + 7) / 8, (new_size + old_size - new_size + 7) / 8 - (new_size + 7) / 8, dcon::bitfield_type{0});
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
				std::fill_n(thingy.m_custom_struct.vptr() + new_size, old_size - new_size, c_struct{});
				dummy_rel_resize(0);
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
			return new_id;
		}
		
		//
		// container compactable delete for thingy
		//
		void delete_thingy(thingy_id id) {
			thingy_id id_removed = id;
			thingy_id last_id(thingy_id::value_base_t(thingy.size_used - 1));
			if(id_removed == last_id) { pop_back_thingy(); return; }
			thingy_remove_all_dummy_rel_as_left(id_removed);
			thingy_for_each_dummy_rel_as_left(last_id, [this, id_removed, last_id](dummy_rel_id i) {
				dummy_rel.hashm_joint.erase(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[i.index()], thingy2_id(thingy2_id::value_base_t(i.index()))));
				dummy_rel.m_left.vptr()[i.index()] = id_removed;
				dummy_rel.hashm_joint.insert_or_assign(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[i.index()], thingy2_id(thingy2_id::value_base_t(i.index()))), i);
			} );
			dummy_rel.m_array_left.vptr()[id_removed.index()] = std::move(dummy_rel.m_array_left.vptr()[last_id.index()]);
			dummy_rel.m_array_left.vptr()[last_id.index()] = std::vector<dummy_rel_id>{};
			thingy.m_i_value.vptr()[id_removed.index()] = std::move(thingy.m_i_value.vptr()[last_id.index()]);
			thingy.m_i_value.vptr()[last_id.index()] = int16_t{};
			thingy.m_f_value.vptr()[id_removed.index()] = std::move(thingy.m_f_value.vptr()[last_id.index()]);
			thingy.m_f_value.vptr()[last_id.index()] = float{};
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), id_removed.index(), dcon::bit_vector_test(thingy.m_bf_value.vptr(), last_id.index()));
			dcon::bit_vector_set(thingy.m_bf_value.vptr(), last_id.index(), false);
			thingy.m_obj_value.vptr()[id_removed.index()] = std::move(thingy.m_obj_value.vptr()[last_id.index()]);
			thingy.m_obj_value.vptr()[last_id.index()] = std::vector<float>{};
			thingy.pooled_v_storage.release(thingy.m_pooled_v.vptr()[id_removed.index()]);
			thingy.m_pooled_v.vptr()[id_removed.index()] = std::move(thingy.m_pooled_v.vptr()[last_id.index()]);
			thingy.m_pooled_v.vptr()[last_id.index()] = std::numeric_limits<dcon::stable_mk_2_tag>::max();
			thingy.m_big_array.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array.zero_at(last_id.index());
			thingy.m_big_array_bf.copy_value(id_removed.index(), last_id.index());
			thingy.m_big_array_bf.zero_at(last_id.index());
			thingy.m_custom_struct.vptr()[id_removed.index()] = std::move(thingy.m_custom_struct.vptr()[last_id.index()]);
			thingy.m_custom_struct.vptr()[last_id.index()] = c_struct{};
			--thingy.size_used;
		}
		
		//
		// container pop_back for thingy2
		//
		void pop_back_thingy2() {
			if(thingy2.size_used == 0) return;
			thingy2_id id_removed(thingy2_id::value_base_t(thingy2.size_used - 1));
			delete_dummy_rel(dummy_rel_id(dummy_rel_id::value_base_t(id_removed.index())));
			dummy_rel.size_used = thingy2.size_used - 1;
			thingy2.m_some_value.vptr()[id_removed.index()] = int32_t{};
			--thingy2.size_used;
		}
		
		//
		// container resize for thingy2
		//
		void thingy2_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 300) std::abort();
			#else
			if(new_size > 300) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = thingy2.size_used;
			if(new_size < old_size) {
				std::fill_n(thingy2.m_some_value.vptr() + new_size, old_size - new_size, int32_t{});
				dummy_rel_resize(std::min(new_size, dummy_rel.size_used));
			} else if(new_size > old_size) {
			}
			thingy2.size_used = new_size;
		}
		
		//
		// container create for thingy2
		//
		thingy2_id create_thingy2() {
			thingy2_id new_id(thingy2_id::value_base_t(thingy2.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(thingy2.size_used >= 300) std::abort();
			#else
			if(thingy2.size_used >= 300) throw dcon::out_of_space{};
			#endif
			dummy_rel.size_used = thingy2.size_used + 1;
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
			delete_dummy_rel(dummy_rel_id(dummy_rel_id::value_base_t(id_removed.index())));
			internal_move_relationship_dummy_rel(dummy_rel_id(dummy_rel_id::value_base_t(last_id.index())), dummy_rel_id(dummy_rel_id::value_base_t(id_removed.index())));
			dummy_rel.size_used = thingy2.size_used - 1;
			thingy2.m_some_value.vptr()[id_removed.index()] = std::move(thingy2.m_some_value.vptr()[last_id.index()]);
			thingy2.m_some_value.vptr()[last_id.index()] = int32_t{};
			--thingy2.size_used;
		}
		
		//
		// container resize for dummy_rel
		//
		void dummy_rel_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 300) std::abort();
			#else
			if(new_size > 300) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = dummy_rel.size_used;
			if(new_size < old_size) {
				dummy_rel.hashm_joint.clear();
				std::fill_n(dummy_rel.m_left.vptr() + 0, old_size, thingy_id{});
				std::fill_n(dummy_rel.m_array_left.vptr() + 0, thingy.size_used, std::vector<dummy_rel_id>{});
			} else if(new_size > old_size) {
			}
			dummy_rel.size_used = new_size;
		}
		
		//
		// container delete for dummy_rel
		//
		void delete_dummy_rel(dummy_rel_id id_removed) {
			dummy_rel.hashm_joint.erase( dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id_removed.index()], thingy2_id(thingy2_id::value_base_t(id_removed.index()))) );
			internal_dummy_rel_set_left(id_removed, thingy_id());
		}
		
		//
		// container pop_back for dummy_rel
		//
		void pop_back_dummy_rel() {
			if(dummy_rel.size_used == 0) return;
			dummy_rel_id id_removed(dummy_rel_id::value_base_t(dummy_rel.size_used - 1));
			dummy_rel.hashm_joint.erase( dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id_removed.index()], thingy2_id(thingy2_id::value_base_t(id_removed.index()))) );
			internal_dummy_rel_set_left(id_removed, thingy_id());
			--dummy_rel.size_used;
		}
		
		private:
		//
		// container move relationship for dummy_rel
		//
		void internal_move_relationship_dummy_rel(dummy_rel_id last_id, dummy_rel_id id_removed) {
			dummy_rel.hashm_joint.erase(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[last_id.index()], thingy2_id(thingy2_id::value_base_t(last_id.index()))));
			internal_dummy_rel_set_left(id_removed, thingy_id());
			if(auto tmp = dummy_rel.m_left.vptr()[last_id.index()]; bool(tmp)) {
				auto& vref = dummy_rel.m_array_left.vptr()[tmp.index()];
				if(auto pos = std::find(vref.begin(), vref.end(), last_id); pos != vref.end()) {
					*pos = id_removed;
				}
			}
			dummy_rel.m_left.vptr()[id_removed.index()] = std::move(dummy_rel.m_left.vptr()[last_id.index()]);
			dummy_rel.m_left.vptr()[last_id.index()] = thingy_id();
			dummy_rel.hashm_joint.erase(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id_removed.index()], thingy2_id(thingy2_id::value_base_t(last_id.index()))));
			dummy_rel.hashm_joint.insert_or_assign(dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[id_removed.index()], thingy2_id(thingy2_id::value_base_t(id_removed.index()))), id_removed);
		}
		
		public:
		//
		// container try create relationship for dummy_rel
		//
		dummy_rel_id try_create_dummy_rel(thingy_id left_p, thingy2_id right_p) {
			if(!bool(left_p)) return dummy_rel_id();
			if(!bool(right_p)) return dummy_rel_id();
			if(dummy_rel_is_valid(dummy_rel_id(dummy_rel_id::value_base_t(right_p.index())))) return dummy_rel_id();
			dummy_rel_id new_id(dummy_rel_id::value_base_t(right_p.index()));
			if(dummy_rel.size_used < uint32_t(right_p.value)) dummy_rel_resize(uint32_t(right_p.value));
			internal_dummy_rel_set_left(new_id, left_p);
			dummy_rel.hashm_joint.insert_or_assign(dummy_rel.to_joint_keydata(left_p, right_p), new_id);
			return new_id;
		}
		
		//
		// container force create relationship for dummy_rel
		//
		dummy_rel_id force_create_dummy_rel(thingy_id left_p, thingy2_id right_p) {
			dummy_rel_id new_id(dummy_rel_id::value_base_t(right_p.index()));
			if(dummy_rel.size_used < uint32_t(right_p.value)) dummy_rel_resize(uint32_t(right_p.value));
			 {
				auto key_dat = dummy_rel.to_joint_keydata(left_p, right_p);
				if(auto it = dummy_rel.hashm_joint.find(key_dat); it !=  dummy_rel.hashm_joint.end()) {
					delete_dummy_rel(it->second);
				}
				dummy_rel.hashm_joint.insert_or_assign(key_dat, new_id);
			}
			internal_dummy_rel_set_left(new_id, left_p);
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy(T&& func) {
			for(uint32_t i = 0; i < thingy.size_used; ++i) {
				thingy_id tmp = thingy_id(thingy_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy2(T&& func) {
			for(uint32_t i = 0; i < thingy2.size_used; ++i) {
				thingy2_id tmp = thingy2_id(thingy2_id::value_base_t(i));
				func(tmp);
			}
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_dummy_rel(T&& func) {
			for(uint32_t i = 0; i < dummy_rel.size_used; ++i) {
				dummy_rel_id tmp = dummy_rel_id(dummy_rel_id::value_base_t(i));
				func(tmp);
			}
		}
		


		uint64_t serialize_size(std::vector<float> const& obj) const;
		void serialize(std::byte*& output_buffer, std::vector<float> const& obj) const;
		void deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const;

		void reset() {
			dummy_rel_resize(0);
			thingy_resize(0);
			thingy2_resize(0);
		}
		dummy_rel_id get_dummy_rel_by_joint(thingy_id left_p, thingy2_id right_p) {
			if(auto it = dummy_rel.hashm_joint.find(dummy_rel.to_joint_keydata(left_p, right_p)); it != dummy_rel.hashm_joint.end()) {
				return it->second;
			}
			return dummy_rel_id();
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
			ve::execute_serial<thingy_id>(thingy.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy(F&& functor) {
			ve::execute_parallel_exact<thingy_id>(thingy.size_used, functor);
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
			ve::execute_serial<thingy2_id>(thingy2.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy2(F&& functor) {
			ve::execute_parallel_exact<thingy2_id>(thingy2.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, dummy_rel_id> dummy_rel_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, dummy_rel_id>(dummy_rel.size_used);
		}
		ve::vectorizable_buffer<int32_t, dummy_rel_id> dummy_rel_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, dummy_rel_id>(dummy_rel.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_dummy_rel(F&& functor) {
			ve::execute_serial<dummy_rel_id>(dummy_rel.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_dummy_rel(F&& functor) {
			ve::execute_parallel_exact<dummy_rel_id>(dummy_rel.size_used, functor);
		}
#endif
		#endif

		load_record make_serialize_record_store_simple() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_i_value = true;
			result.thingy_f_value = true;
			result.thingy_bf_value = true;
			return result;
		}
		
		load_record make_serialize_record_store_left() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_i_value = true;
			result.thingy_f_value = true;
			result.thingy_bf_value = true;
			result.thingy_d_value = true;
			result.thingy_obj_value = true;
			result.thingy_pooled_v = true;
			result.thingy_big_array = true;
			result.thingy_big_array_bf = true;
			result.thingy_custom_struct = true;
			return result;
		}
		
		load_record make_serialize_record_store_right() const noexcept {
			load_record result;
			result.thingy2 = true;
			result.thingy2_some_value = true;
			result.dummy_rel = true;
			result.dummy_rel_left = true;
			result.dummy_rel_right = true;
			return result;
		}
		
		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_i_value = true;
			result.thingy_f_value = true;
			result.thingy_bf_value = true;
			result.thingy_d_value = true;
			result.thingy_obj_value = true;
			result.thingy_pooled_v = true;
			result.thingy_big_array = true;
			result.thingy_big_array_bf = true;
			result.thingy_custom_struct = true;
			result.thingy2 = true;
			result.thingy2_some_value = true;
			result.dummy_rel = true;
			result.dummy_rel_left = true;
			result.dummy_rel_right = true;
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
			if(serialize_selection.thingy_i_value) {
				dcon::record_header iheader(0, "int16_t", "thingy", "i_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int16_t) * thingy.size_used;
			}
			if(serialize_selection.thingy_f_value) {
				dcon::record_header iheader(0, "float", "thingy", "f_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * thingy.size_used;
			}
			if(serialize_selection.thingy_bf_value) {
				dcon::record_header iheader(0, "bitfield", "thingy", "bf_value");
				total_size += iheader.serialize_size();
				total_size += (thingy.size_used + 7) / 8;
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
				total_size += thingy.m_big_array_bf.size * (thingy.size_used + 7) / 8;
				dcon::record_header iheader(0, "$array", "thingy", "big_array_bf");
				total_size += iheader.serialize_size();
			}
			if(serialize_selection.thingy_custom_struct) {
				dcon::record_header iheader(0, "c_struct", "thingy", "custom_struct");
				total_size += iheader.serialize_size();
				total_size += sizeof(c_struct) * thingy.size_used;
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
			if(serialize_selection.dummy_rel) {
				dcon::record_header header(0, "uint32_t", "dummy_rel", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.dummy_rel_left) {
					dcon::record_header iheader(0, "uint16_t", "dummy_rel", "left");
					total_size += iheader.serialize_size();
					total_size += sizeof(thingy_id) * dummy_rel.size_used;
				}
				dcon::record_header headerb(0, "$", "dummy_rel", "$index_end");
				total_size += headerb.serialize_size();
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
			if(serialize_selection.thingy_i_value) {
				dcon::record_header header(sizeof(int16_t) * thingy.size_used, "int16_t", "thingy", "i_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<int16_t*>(output_buffer), thingy.m_i_value.vptr(), sizeof(int16_t) * thingy.size_used);
				output_buffer += sizeof(int16_t) * thingy.size_used;
			}
			if(serialize_selection.thingy_f_value) {
				dcon::record_header header(sizeof(float) * thingy.size_used, "float", "thingy", "f_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), thingy.m_f_value.vptr(), sizeof(float) * thingy.size_used);
				output_buffer += sizeof(float) * thingy.size_used;
			}
			if(serialize_selection.thingy_bf_value) {
				dcon::record_header header((thingy.size_used + 7) / 8, "bitfield", "thingy", "bf_value");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<dcon::bitfield_type*>(output_buffer), thingy.m_bf_value.vptr(), (thingy.size_used + 7) / 8);
				output_buffer += (thingy.size_used + 7) / 8;
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
				dcon::record_header header(9 + sizeof(uint16_t) + thingy.m_big_array_bf.size * (thingy.size_used + 7) / 8, "$array", "thingy", "big_array_bf");
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
			if(serialize_selection.thingy_custom_struct) {
				dcon::record_header header(sizeof(c_struct) * thingy.size_used, "c_struct", "thingy", "custom_struct");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<c_struct*>(output_buffer), thingy.m_custom_struct.vptr(), sizeof(c_struct) * thingy.size_used);
				output_buffer += sizeof(c_struct) * thingy.size_used;
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
			if(serialize_selection.dummy_rel) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "dummy_rel", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = dummy_rel.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(thingy_id) * dummy_rel.size_used, "uint16_t", "dummy_rel", "left");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<thingy_id*>(output_buffer), dummy_rel.m_left.vptr(), sizeof(thingy_id) * dummy_rel.size_used);
					output_buffer += sizeof(thingy_id) *  dummy_rel.size_used;
				}
				dcon::record_header headerb(0, "$", "dummy_rel", "$index_end");
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
					if(header.is_object("thingy")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							thingy_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.thingy = true;
						}
						else if(header.is_property("i_value")) {
							if(header.is_type("int16_t")) {
								std::memcpy(thingy.m_i_value.vptr(), reinterpret_cast<int16_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int16_t), header.record_size));
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
						}
						else if(header.is_property("f_value")) {
							if(header.is_type("float")) {
								std::memcpy(thingy.m_f_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(float), header.record_size));
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
						}
						else if(header.is_property("bf_value")) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<dcon::bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy_bf_value = true;
							}
						}
						else if(header.is_property("d_value")) {
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
										std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<dcon::bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy.size_used + 7) / 8;
									}
									serialize_selection.thingy_big_array_bf = true;
								}
							}
						}
						else if(header.is_property("custom_struct")) {
							if(header.is_type("c_struct")) {
								std::memcpy(thingy.m_custom_struct.vptr(), reinterpret_cast<c_struct const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(c_struct), header.record_size));
								serialize_selection.thingy_custom_struct = true;
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
					} else
					if(header.is_object("dummy_rel")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= dummy_rel.size_used) {
								dummy_rel_resize(0);
							}
							dummy_rel_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.dummy_rel = true;
						}
						else if(header.is_property("left")) {
							if(header.is_type("uint16_t")) {
								std::memcpy(dummy_rel.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(dummy_rel.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.dummy_rel_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(dummy_rel.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									dummy_rel.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.dummy_rel_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(dummy_rel.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									dummy_rel.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.dummy_rel_left = true;
							}
						}
						else if(header.is_property("$index_end")) {
							if(serialize_selection.dummy_rel_left == true) {
								for(uint32_t i = 0; i < dummy_rel.size_used; ++i) {
									auto tmp = dummy_rel.m_left.vptr()[i];
									dummy_rel.m_left.vptr()[i] = thingy_id();
									internal_dummy_rel_set_left(dummy_rel_id(dummy_rel_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < dummy_rel.size_used; ++idx) {
								auto this_key = dummy_rel_id(dummy_rel_id::value_base_t(idx));
								if(dummy_rel_is_valid(dummy_rel_id(dummy_rel_id::value_base_t(idx)))) {
									auto key_dat = dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[idx], thingy2_id(thingy2_id::value_base_t(idx)));
									if(auto it = dummy_rel.hashm_joint.find(key_dat); it !=  dummy_rel.hashm_joint.end()) {
										delete_dummy_rel(it->second);
									}
									dummy_rel.hashm_joint.insert_or_assign(key_dat, this_key);
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
						else if(header.is_property("i_value") && mask.thingy_i_value) {
							if(header.is_type("int16_t")) {
								std::memcpy(thingy.m_i_value.vptr(), reinterpret_cast<int16_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int16_t), header.record_size));
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("float")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<float const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_i_value.vptr()[i] = int16_t(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_i_value = true;
							}
						}
						else if(header.is_property("f_value") && mask.thingy_f_value) {
							if(header.is_type("float")) {
								std::memcpy(thingy.m_f_value.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(float), header.record_size));
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(thingy.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									thingy.m_f_value.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.thingy_f_value = true;
							}
						}
						else if(header.is_property("bf_value") && mask.thingy_bf_value) {
							if(header.is_type("bitfield")) {
								std::memcpy(thingy.m_bf_value.vptr(), reinterpret_cast<dcon::bitfield_type const*>(input_buffer), std::min(size_t(thingy.size_used + 7) / 8, header.record_size));
								serialize_selection.thingy_bf_value = true;
							}
						}
						else if(header.is_property("d_value") && mask.thingy_d_value) {
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
										std::memcpy(thingy.m_big_array_bf.vptr(s), reinterpret_cast<dcon::bitfield_type const*>(icpy), std::min(size_t(thingy.size_used + 7) / 8, size_t(input_buffer + header.record_size - icpy)));
										icpy += (thingy.size_used + 7) / 8;
									}
									serialize_selection.thingy_big_array_bf = true;
								}
							}
						}
						else if(header.is_property("custom_struct") && mask.thingy_custom_struct) {
							if(header.is_type("c_struct")) {
								std::memcpy(thingy.m_custom_struct.vptr(), reinterpret_cast<c_struct const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(c_struct), header.record_size));
								serialize_selection.thingy_custom_struct = true;
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
					} else
					if(header.is_object("dummy_rel") && mask.dummy_rel) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= dummy_rel.size_used) {
								dummy_rel_resize(0);
							}
							dummy_rel_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.dummy_rel = true;
						}
						else if(header.is_property("left") && mask.dummy_rel_left) {
							if(header.is_type("uint16_t")) {
								std::memcpy(dummy_rel.m_left.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(dummy_rel.size_used) * sizeof(uint16_t), header.record_size));
								serialize_selection.dummy_rel_left = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(dummy_rel.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									dummy_rel.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.dummy_rel_left = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(dummy_rel.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									dummy_rel.m_left.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.dummy_rel_left = true;
							}
						}
						else if(header.is_property("$index_end") && mask.dummy_rel) {
							if(serialize_selection.dummy_rel_left == true) {
								for(uint32_t i = 0; i < dummy_rel.size_used; ++i) {
									auto tmp = dummy_rel.m_left.vptr()[i];
									dummy_rel.m_left.vptr()[i] = thingy_id();
									internal_dummy_rel_set_left(dummy_rel_id(dummy_rel_id::value_base_t(i)), tmp);
								}
							}
							for(uint32_t idx = 0; idx < dummy_rel.size_used; ++idx) {
								auto this_key = dummy_rel_id(dummy_rel_id::value_base_t(idx));
								if(dummy_rel_is_valid(dummy_rel_id(dummy_rel_id::value_base_t(idx)))) {
									auto key_dat = dummy_rel.to_joint_keydata(dummy_rel.m_left.vptr()[idx], thingy2_id(thingy2_id::value_base_t(idx)));
									if(auto it = dummy_rel.hashm_joint.find(key_dat); it !=  dummy_rel.hashm_joint.end()) {
										delete_dummy_rel(it->second);
									}
									dummy_rel.hashm_joint.insert_or_assign(key_dat, this_key);
								}
							}
						}
					}
				}
				input_buffer += header.record_size;
			}
		}
		

	};

	DCON_RELEASE_INLINE int16_t& thingy_fat_id::get_i_value() const noexcept {
		return container.thingy_get_i_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_i_value(int16_t v) const noexcept {
		container.thingy_set_i_value(id, v);
	}
	DCON_RELEASE_INLINE float& thingy_fat_id::get_f_value() const noexcept {
		return container.thingy_get_f_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_f_value(float v) const noexcept {
		container.thingy_set_f_value(id, v);
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::get_bf_value() const noexcept {
		return container.thingy_get_bf_value(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_bf_value(bool v) const noexcept {
		container.thingy_set_bf_value(id, v);
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
	DCON_RELEASE_INLINE float& thingy_fat_id::get_big_array(int32_t i) const noexcept {
		return container.thingy_get_big_array(id, i);
	}
	DCON_RELEASE_INLINE uint32_t thingy_fat_id::get_big_array_size() const noexcept {
		return container.thingy_get_big_array_size();
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_big_array(int32_t i, float v) const noexcept {
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
	DCON_RELEASE_INLINE c_struct& thingy_fat_id::get_custom_struct() const noexcept {
		return container.thingy_get_custom_struct(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::set_custom_struct(c_struct const& v) const noexcept {
		container.thingy_set_custom_struct(id, v);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_fat_id::for_each_dummy_rel_as_left(T&& func) const {
		container.thingy_for_each_dummy_rel_as_left(id, [&, t = this](dummy_rel_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_fat_id::range_of_dummy_rel_as_left() const {
		return container.thingy_range_of_dummy_rel_as_left(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::remove_all_dummy_rel_as_left() const noexcept {
		container.thingy_remove_all_dummy_rel_as_left(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_fat_id::for_each_dummy_rel(T&& func) const {
		container.thingy_for_each_dummy_rel(id, [&, t = this](dummy_rel_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_fat_id::range_of_dummy_rel() const {
		return container.thingy_range_of_dummy_rel(id);
	}
	DCON_RELEASE_INLINE void thingy_fat_id::remove_all_dummy_rel() const noexcept {
		container.thingy_remove_all_dummy_rel(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_fat_id::for_each_right_from_dummy_rel(T&& func) const {
		container.thingy_for_each_right_from_dummy_rel(id, [&, t = this](thingy2_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::has_right_from_dummy_rel(thingy2_id target) const {
		return container.thingy_has_right_from_dummy_rel(id, target);
	}
	DCON_RELEASE_INLINE bool thingy_fat_id::is_valid() const noexcept {
		return container.thingy_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int16_t thingy_const_fat_id::get_i_value() const noexcept {
		return container.thingy_get_i_value(id);
	}
	DCON_RELEASE_INLINE float thingy_const_fat_id::get_f_value() const noexcept {
		return container.thingy_get_f_value(id);
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::get_bf_value() const noexcept {
		return container.thingy_get_bf_value(id);
	}
	DCON_RELEASE_INLINE std::vector<float> const& thingy_const_fat_id::get_obj_value() const noexcept {
		return container.thingy_get_obj_value(id);
	}
	DCON_RELEASE_INLINE dcon::dcon_vv_const_fat_id<int16_t> thingy_const_fat_id::get_pooled_v() const noexcept {
		return container.thingy_get_pooled_v(id);
	}
	DCON_RELEASE_INLINE float thingy_const_fat_id::get_big_array(int32_t i) const noexcept {
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
	DCON_RELEASE_INLINE c_struct const& thingy_const_fat_id::get_custom_struct() const noexcept {
		return container.thingy_get_custom_struct(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_const_fat_id::for_each_dummy_rel_as_left(T&& func) const {
		container.thingy_for_each_dummy_rel_as_left(id, [&, t = this](dummy_rel_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_const_fat_id::range_of_dummy_rel_as_left() const {
		return container.thingy_range_of_dummy_rel_as_left(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_const_fat_id::for_each_dummy_rel(T&& func) const {
		container.thingy_for_each_dummy_rel(id, [&, t = this](dummy_rel_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE std::pair<dummy_rel_id const*, dummy_rel_id const*> thingy_const_fat_id::range_of_dummy_rel() const {
		return container.thingy_range_of_dummy_rel(id);
	}
	template<typename T>
	DCON_RELEASE_INLINE void thingy_const_fat_id::for_each_right_from_dummy_rel(T&& func) const {
		container.thingy_for_each_right_from_dummy_rel(id, [&, t = this](thingy2_id i){func(fatten(t->container, i));});
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::has_right_from_dummy_rel(thingy2_id target) const {
		return container.thingy_has_right_from_dummy_rel(id, target);
	}
	DCON_RELEASE_INLINE bool thingy_const_fat_id::is_valid() const noexcept {
		return container.thingy_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t& thingy2_fat_id::get_some_value() const noexcept {
		return container.thingy2_get_some_value(id);
	}
	DCON_RELEASE_INLINE void thingy2_fat_id::set_some_value(int32_t v) const noexcept {
		container.thingy2_set_some_value(id, v);
	}
	DCON_RELEASE_INLINE dummy_rel_fat_id thingy2_fat_id::get_dummy_rel_as_right() const noexcept {
		return dummy_rel_fat_id(container, container.thingy2_get_dummy_rel_as_right(id));
	}
	DCON_RELEASE_INLINE void thingy2_fat_id::remove_dummy_rel_as_right() const noexcept {
		container.thingy2_remove_dummy_rel_as_right(id);
	}
	DCON_RELEASE_INLINE dummy_rel_fat_id thingy2_fat_id::get_dummy_rel() const noexcept {
		return dummy_rel_fat_id(container, container.thingy2_get_dummy_rel(id));
	}
	DCON_RELEASE_INLINE void thingy2_fat_id::remove_dummy_rel() const noexcept {
		container.thingy2_remove_dummy_rel(id);
	}
	DCON_RELEASE_INLINE thingy_fat_id thingy2_fat_id::get_left_from_dummy_rel() const noexcept {
		return thingy_fat_id(container, container.thingy2_get_left_from_dummy_rel(id));
	}
	DCON_RELEASE_INLINE void thingy2_fat_id::set_left_from_dummy_rel(thingy_id v) const noexcept {
		container.thingy2_set_left_from_dummy_rel(id, v);
	}
	DCON_RELEASE_INLINE bool thingy2_fat_id::is_valid() const noexcept {
		return container.thingy2_is_valid(id);
	}
	
	DCON_RELEASE_INLINE int32_t thingy2_const_fat_id::get_some_value() const noexcept {
		return container.thingy2_get_some_value(id);
	}
	DCON_RELEASE_INLINE dummy_rel_const_fat_id thingy2_const_fat_id::get_dummy_rel_as_right() const noexcept {
		return dummy_rel_const_fat_id(container, container.thingy2_get_dummy_rel_as_right(id));
	}
	DCON_RELEASE_INLINE dummy_rel_const_fat_id thingy2_const_fat_id::get_dummy_rel() const noexcept {
		return dummy_rel_const_fat_id(container, container.thingy2_get_dummy_rel(id));
	}
	DCON_RELEASE_INLINE thingy_const_fat_id thingy2_const_fat_id::get_left_from_dummy_rel() const noexcept {
		return thingy_const_fat_id(container, container.thingy2_get_left_from_dummy_rel(id));
	}
	DCON_RELEASE_INLINE bool thingy2_const_fat_id::is_valid() const noexcept {
		return container.thingy2_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingy_fat_id dummy_rel_fat_id::get_left() const noexcept {
		return thingy_fat_id(container, container.dummy_rel_get_left(id));
	}
	DCON_RELEASE_INLINE void dummy_rel_fat_id::set_left(thingy_id val) const noexcept {
		container.dummy_rel_set_left(id, val);
	}
	DCON_RELEASE_INLINE bool dummy_rel_fat_id::try_set_left(thingy_id val) const noexcept {
		return container.dummy_rel_try_set_left(id, val);
	}
	DCON_RELEASE_INLINE thingy2_fat_id dummy_rel_fat_id::get_right() const noexcept {
		return thingy2_fat_id(container, container.dummy_rel_get_right(id));
	}
	DCON_RELEASE_INLINE void dummy_rel_fat_id::set_right(thingy2_id val) const noexcept {
		container.dummy_rel_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool dummy_rel_fat_id::try_set_right(thingy2_id val) const noexcept {
		return container.dummy_rel_try_set_right(id, val);
	}
	DCON_RELEASE_INLINE bool dummy_rel_fat_id::is_valid() const noexcept {
		return container.dummy_rel_is_valid(id);
	}
	
	DCON_RELEASE_INLINE thingy_const_fat_id dummy_rel_const_fat_id::get_left() const noexcept {
		return thingy_const_fat_id(container, container.dummy_rel_get_left(id));
	}
	DCON_RELEASE_INLINE thingy2_const_fat_id dummy_rel_const_fat_id::get_right() const noexcept {
		return thingy2_const_fat_id(container, container.dummy_rel_get_right(id));
	}
	DCON_RELEASE_INLINE bool dummy_rel_const_fat_id::is_valid() const noexcept {
		return container.dummy_rel_is_valid(id);
	}
	

	namespace internal {
	};


}

#undef DCON_RELEASE_INLINE
#pragma warning( pop )

