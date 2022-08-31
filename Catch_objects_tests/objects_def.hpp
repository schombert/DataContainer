#pragma once
#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
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
		load_record() {
			thingy = false;
			thingy_some_value = false;
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
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::thingy_id> {
		using type = tagged_vector<dcon::thingy_id>;
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
				uint8_t padding[(sizeof(int32_t) + 63ui32) & ~63ui32];
				int32_t values[(sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_some_value() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(int32_t) <= 64 ? (uint32_t(1200) + (64ui32 / uint32_t(sizeof(int32_t))) - 1ui32) & ~(64ui32 / uint32_t(sizeof(int32_t)) - 1ui32) : uint32_t(1200))); }
			}
			m_some_value;
			
			uint32_t size_used = 0;

			public:
			friend class data_container;
		};

	}

	class alignas(64) data_container {
		public:
		internal::thingy_class thingy;

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
		
		void on_create_thingy(thingy_id id);
		void on_delete_thingy(thingy_id id);
		void on_move_thingy(thingy_id new_id,thingy_id old_id);
		uint32_t thingy_size() const noexcept { return thingy.size_used; }


		//
		// container pop_back for thingy
		//
		void pop_back_thingy() {
			if(thingy.size_used == 0) return;
			thingy_id id_removed(thingy_id::value_base_t(thingy.size_used - 1));
			on_delete_thingy(id_removed);
			thingy.m_some_value.vptr()[id_removed.index()] = int32_t{};
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
			--thingy.size_used;
			on_move_thingy(id_removed, last_id);
		}
		
		bool is_valid_thingy(thingy_id id) const {
			return bool(id) && uint32_t(id.index()) < thingy.size_used;
		}
		template <typename T>
		DCON_RELEASE_INLINE void for_each_thingy(T&& func) {
			for(uint32_t i = 0; i < thingy.size_used; ++i) {
				thingy_id tmp(thingy_id::value_base_t(i));
				func(tmp);
			}
		}
		


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
			ve::execute_serial(thingy.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_thingy(F&& functor) {
			ve::execute_parallel_exact(thingy.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.thingy = true;
			result.thingy_some_value = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.thingy) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "thingy", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.thingy_some_value) {
				dcon::record_header iheader(sizeof(int32_t) * thingy.size_used, "int32_t", "thingy", "some_value");
				total_size += iheader.serialize_size();
				total_size += sizeof(int32_t) * thingy.size_used;
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
				memcpy(reinterpret_cast<int32_t*>(output_buffer), thingy.m_some_value.vptr(), sizeof(int32_t) * thingy.size_used);
				output_buffer += sizeof(int32_t) * thingy.size_used;
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
								memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), header.record_size));
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
								memcpy(thingy.m_some_value.vptr(), reinterpret_cast<int32_t const*>(input_buffer), std::min(size_t(thingy.size_used) * sizeof(int32_t), header.record_size));
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

