#pragma once

//
// This file was automatically generated from: old_color_container.txt
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

namespace old {
	struct load_record {
		bool colored_thing : 1;
		bool colored_thing_red : 1;
		bool colored_thing_green : 1;
		bool colored_thing_blue : 1;
		load_record() {
			colored_thing = false;
			colored_thing_red = false;
			colored_thing_green = false;
			colored_thing_blue = false;
		}
	};
	//
	// definition of strongly typed index for colored_thing_id
	//
	class colored_thing_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr colored_thing_id() noexcept = default;
		explicit constexpr colored_thing_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr colored_thing_id(colored_thing_id const& v) noexcept = default;
		constexpr colored_thing_id(colored_thing_id&& v) noexcept = default;
		
		colored_thing_id& operator=(colored_thing_id const& v) noexcept = default;
		colored_thing_id& operator=(colored_thing_id&& v) noexcept = default;
		constexpr bool operator==(colored_thing_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(colored_thing_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class colored_thing_id_pair {
		public:
		colored_thing_id left;
		colored_thing_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(colored_thing_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<old::colored_thing_id> {
		using type = tagged_vector<old::colored_thing_id>;
	};
	
}

#endif
namespace old {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class alignas(64) colored_thing_class {
			private:
			//
			// storage space for red of type float
			//
			struct alignas(64) dtype_red {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_red() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_red;
			
			//
			// storage space for green of type float
			//
			struct alignas(64) dtype_green {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_green() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_green;
			
			//
			// storage space for blue of type float
			//
			struct alignas(64) dtype_blue {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_blue() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_blue;
			
			uint32_t size_used = 0;


			public:
			friend class data_container;
		};

	}

	class colored_thing_const_fat_id;
	class colored_thing_fat_id;
	class colored_thing_fat_id {
		friend class data_container;
		public:
		data_container& container;
		colored_thing_id id;
		colored_thing_fat_id(data_container& c, colored_thing_id i) noexcept : container(c), id(i) {}
		colored_thing_fat_id(colored_thing_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator colored_thing_id() const noexcept { return id; }
		DCON_RELEASE_INLINE colored_thing_fat_id& operator=(colored_thing_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE colored_thing_fat_id& operator=(colored_thing_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(colored_thing_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(colored_thing_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(colored_thing_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(colored_thing_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE float& get_red() const noexcept;
		DCON_RELEASE_INLINE void set_red(float v) const noexcept;
		DCON_RELEASE_INLINE float& get_green() const noexcept;
		DCON_RELEASE_INLINE void set_green(float v) const noexcept;
		DCON_RELEASE_INLINE float& get_blue() const noexcept;
		DCON_RELEASE_INLINE void set_blue(float v) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE colored_thing_fat_id fatten(data_container& c, colored_thing_id id) noexcept {
		return colored_thing_fat_id(c, id);
	}
	
	class colored_thing_const_fat_id {
		friend class data_container;
		public:
		data_container const& container;
		colored_thing_id id;
		colored_thing_const_fat_id(data_container const& c, colored_thing_id i) noexcept : container(c), id(i) {}
		colored_thing_const_fat_id(colored_thing_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		colored_thing_const_fat_id(colored_thing_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator colored_thing_id() const noexcept { return id; }
		DCON_RELEASE_INLINE colored_thing_const_fat_id& operator=(colored_thing_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE colored_thing_const_fat_id& operator=(colored_thing_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE colored_thing_const_fat_id& operator=(colored_thing_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(colored_thing_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(colored_thing_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(colored_thing_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(colored_thing_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(colored_thing_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(colored_thing_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE float get_red() const noexcept;
		DCON_RELEASE_INLINE float get_green() const noexcept;
		DCON_RELEASE_INLINE float get_blue() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(colored_thing_fat_id const& l, colored_thing_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(colored_thing_fat_id const& l, colored_thing_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE colored_thing_const_fat_id fatten(data_container const& c, colored_thing_id id) noexcept {
		return colored_thing_const_fat_id(c, id);
	}
	
	class alignas(64) data_container {
		public:
		internal::colored_thing_class colored_thing;

		//
		// Functions for colored_thing:
		//
		//
		// accessors for colored_thing: red
		//
		DCON_RELEASE_INLINE float const& colored_thing_get_red(colored_thing_id id) const noexcept {
			return colored_thing.m_red.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& colored_thing_get_red(colored_thing_id id) noexcept {
			return colored_thing.m_red.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_red(ve::contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_red.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_red(ve::partial_contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_red.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_red(ve::tagged_vector<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_red.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void colored_thing_set_red(colored_thing_id id, float value) noexcept {
			colored_thing.m_red.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void colored_thing_set_red(ve::contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_red.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_red(ve::partial_contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_red.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_red(ve::tagged_vector<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_red.vptr(), values);
		}
		#endif
		//
		// accessors for colored_thing: green
		//
		DCON_RELEASE_INLINE float const& colored_thing_get_green(colored_thing_id id) const noexcept {
			return colored_thing.m_green.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& colored_thing_get_green(colored_thing_id id) noexcept {
			return colored_thing.m_green.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_green(ve::contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_green.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_green(ve::partial_contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_green.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_green(ve::tagged_vector<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_green.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void colored_thing_set_green(colored_thing_id id, float value) noexcept {
			colored_thing.m_green.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void colored_thing_set_green(ve::contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_green.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_green(ve::partial_contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_green.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_green(ve::tagged_vector<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_green.vptr(), values);
		}
		#endif
		//
		// accessors for colored_thing: blue
		//
		DCON_RELEASE_INLINE float const& colored_thing_get_blue(colored_thing_id id) const noexcept {
			return colored_thing.m_blue.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& colored_thing_get_blue(colored_thing_id id) noexcept {
			return colored_thing.m_blue.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_blue(ve::contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_blue.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_blue(ve::partial_contiguous_tags<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_blue.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> colored_thing_get_blue(ve::tagged_vector<colored_thing_id> id) const noexcept {
			return ve::load(id, colored_thing.m_blue.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void colored_thing_set_blue(colored_thing_id id, float value) noexcept {
			colored_thing.m_blue.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void colored_thing_set_blue(ve::contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_blue.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_blue(ve::partial_contiguous_tags<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_blue.vptr(), values);
		}
		DCON_RELEASE_INLINE void colored_thing_set_blue(ve::tagged_vector<colored_thing_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, colored_thing.m_blue.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE bool colored_thing_is_valid(colored_thing_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < colored_thing.size_used;
		}
		
		uint32_t colored_thing_size() const noexcept { return colored_thing.size_used; }


		//
		// container pop_back for colored_thing
		//
		void pop_back_colored_thing() {
			if(colored_thing.size_used == 0) return;
			colored_thing_id id_removed(colored_thing_id::value_base_t(colored_thing.size_used - 1));
			colored_thing.m_red.vptr()[id_removed.index()] = float{};
			colored_thing.m_green.vptr()[id_removed.index()] = float{};
			colored_thing.m_blue.vptr()[id_removed.index()] = float{};
			--colored_thing.size_used;
		}
		
		//
		// container resize for colored_thing
		//
		void colored_thing_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 3000) std::abort();
			#else
			if(new_size > 3000) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = colored_thing.size_used;
			if(new_size < old_size) {
				std::fill_n(colored_thing.m_red.vptr() + new_size, old_size - new_size, float{});
				std::fill_n(colored_thing.m_green.vptr() + new_size, old_size - new_size, float{});
				std::fill_n(colored_thing.m_blue.vptr() + new_size, old_size - new_size, float{});
			} else if(new_size > old_size) {
			}
			colored_thing.size_used = new_size;
		}
		
		//
		// container create for colored_thing
		//
		colored_thing_id create_colored_thing() {
			colored_thing_id new_id(colored_thing_id::value_base_t(colored_thing.size_used));
			#ifndef DCON_USE_EXCEPTIONS
			if(colored_thing.size_used >= 3000) std::abort();
			#else
			if(colored_thing.size_used >= 3000) throw dcon::out_of_space{};
			#endif
			++colored_thing.size_used;
			return new_id;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_colored_thing(T&& func) {
			for(uint32_t i = 0; i < colored_thing.size_used; ++i) {
				colored_thing_id tmp = colored_thing_id(colored_thing_id::value_base_t(i));
				func(tmp);
			}
		}
		


		void reset() {
			colored_thing_resize(0);
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, colored_thing_id> colored_thing_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, colored_thing_id>(colored_thing.size_used);
		}
		ve::vectorizable_buffer<int32_t, colored_thing_id> colored_thing_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, colored_thing_id>(colored_thing.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_colored_thing(F&& functor) {
			ve::execute_serial<colored_thing_id>(colored_thing.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_colored_thing(F&& functor) {
			ve::execute_parallel_exact<colored_thing_id>(colored_thing.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.colored_thing = true;
			result.colored_thing_red = true;
			result.colored_thing_green = true;
			result.colored_thing_blue = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.colored_thing) {
				dcon::record_header header(0, "uint32_t", "colored_thing", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.colored_thing_red) {
				dcon::record_header iheader(0, "float", "colored_thing", "red");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * colored_thing.size_used;
			}
			if(serialize_selection.colored_thing_green) {
				dcon::record_header iheader(0, "float", "colored_thing", "green");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * colored_thing.size_used;
			}
			if(serialize_selection.colored_thing_blue) {
				dcon::record_header iheader(0, "float", "colored_thing", "blue");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * colored_thing.size_used;
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.colored_thing) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "colored_thing", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = colored_thing.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.colored_thing_red) {
				dcon::record_header header(sizeof(float) * colored_thing.size_used, "float", "colored_thing", "red");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), colored_thing.m_red.vptr(), sizeof(float) * colored_thing.size_used);
				output_buffer += sizeof(float) * colored_thing.size_used;
			}
			if(serialize_selection.colored_thing_green) {
				dcon::record_header header(sizeof(float) * colored_thing.size_used, "float", "colored_thing", "green");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), colored_thing.m_green.vptr(), sizeof(float) * colored_thing.size_used);
				output_buffer += sizeof(float) * colored_thing.size_used;
			}
			if(serialize_selection.colored_thing_blue) {
				dcon::record_header header(sizeof(float) * colored_thing.size_used, "float", "colored_thing", "blue");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), colored_thing.m_blue.vptr(), sizeof(float) * colored_thing.size_used);
				output_buffer += sizeof(float) * colored_thing.size_used;
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
					if(header.is_object("colored_thing")) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							colored_thing_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.colored_thing = true;
						}
						else if(header.is_property("red")) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_red.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
						}
						else if(header.is_property("green")) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_green.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
						}
						else if(header.is_property("blue")) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_blue.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
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
					if(header.is_object("colored_thing") && mask.colored_thing) {
						if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
							colored_thing_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
							serialize_selection.colored_thing = true;
						}
						else if(header.is_property("red") && mask.colored_thing_red) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_red.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_red.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_red = true;
							}
						}
						else if(header.is_property("green") && mask.colored_thing_green) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_green.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_green.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_green = true;
							}
						}
						else if(header.is_property("blue") && mask.colored_thing_blue) {
							if(header.is_type("float")) {
								std::memcpy(colored_thing.m_blue.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(float), header.record_size));
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint8_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint16_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint32_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("int64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("uint64_t")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
							else if(header.is_type("double")) {
								for(uint32_t i = 0; i < std::min(colored_thing.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
									colored_thing.m_blue.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
								}
								serialize_selection.colored_thing_blue = true;
							}
						}
					}
				}
				input_buffer += header.record_size;
			}
		}
		

	};

	DCON_RELEASE_INLINE float& colored_thing_fat_id::get_red() const noexcept {
		return container.colored_thing_get_red(id);
	}
	DCON_RELEASE_INLINE void colored_thing_fat_id::set_red(float v) const noexcept {
		container.colored_thing_set_red(id, v);
	}
	DCON_RELEASE_INLINE float& colored_thing_fat_id::get_green() const noexcept {
		return container.colored_thing_get_green(id);
	}
	DCON_RELEASE_INLINE void colored_thing_fat_id::set_green(float v) const noexcept {
		container.colored_thing_set_green(id, v);
	}
	DCON_RELEASE_INLINE float& colored_thing_fat_id::get_blue() const noexcept {
		return container.colored_thing_get_blue(id);
	}
	DCON_RELEASE_INLINE void colored_thing_fat_id::set_blue(float v) const noexcept {
		container.colored_thing_set_blue(id, v);
	}
	DCON_RELEASE_INLINE bool colored_thing_fat_id::is_valid() const noexcept {
		return container.colored_thing_is_valid(id);
	}
	
	DCON_RELEASE_INLINE float colored_thing_const_fat_id::get_red() const noexcept {
		return container.colored_thing_get_red(id);
	}
	DCON_RELEASE_INLINE float colored_thing_const_fat_id::get_green() const noexcept {
		return container.colored_thing_get_green(id);
	}
	DCON_RELEASE_INLINE float colored_thing_const_fat_id::get_blue() const noexcept {
		return container.colored_thing_get_blue(id);
	}
	DCON_RELEASE_INLINE bool colored_thing_const_fat_id::is_valid() const noexcept {
		return container.colored_thing_is_valid(id);
	}
	
}

#undef DCON_RELEASE_INLINE
#pragma warning( pop )

