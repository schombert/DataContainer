#pragma once

//
// This file was automatically generated from: color_container.txt
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

namespace dcon {
	struct load_record {
		bool colored_thing : 1;
		bool colored_thing_color : 1;
		load_record() {
			colored_thing = false;
			colored_thing_color = false;
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
	struct value_to_vector_type_s<dcon::colored_thing_id> {
		using type = ::ve::tagged_vector<dcon::colored_thing_id>;
	};
	
}

#endif
#include "color_tutorial.hpp"
namespace dcon {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class const_object_iterator_colored_thing;
		class object_iterator_colored_thing;

		class alignas(64) colored_thing_class {
			friend const_object_iterator_colored_thing;
			friend object_iterator_colored_thing;
			private:
			//
			// storage space for color of type rgb_color
			//
			struct alignas(64) dtype_color {
				uint8_t padding[(63 + sizeof(rgb_color)) & ~uint64_t(63)];
				rgb_color values[(sizeof(rgb_color) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(rgb_color))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(rgb_color)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_color() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(rgb_color) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(rgb_color))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(rgb_color)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_color;
			
			uint32_t size_used = 0;


			public:
			colored_thing_class() {
			}
			friend data_container;
		};

	}

	class colored_thing_const_fat_id;
	class colored_thing_fat_id;
	class colored_thing_fat_id {
		friend data_container;
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
		DCON_RELEASE_INLINE rgb_color& get_color() const noexcept;
		DCON_RELEASE_INLINE void set_color(rgb_color const& v) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		void set_red(float value) ;
		void set_green(float value) ;
		void set_blue(float value) ;
		inline float get_red();
		inline float get_green();
		inline float get_blue();
		
	};
	DCON_RELEASE_INLINE colored_thing_fat_id fatten(data_container& c, colored_thing_id id) noexcept {
		return colored_thing_fat_id(c, id);
	}
	
	class colored_thing_const_fat_id {
		friend data_container;
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
		DCON_RELEASE_INLINE rgb_color const& get_color() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		float get_red() ;
		float get_green() ;
		float get_blue() ;
		
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
	
	namespace internal {
		class object_iterator_colored_thing {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_colored_thing(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_colored_thing& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_colored_thing& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_colored_thing const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_colored_thing const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE colored_thing_fat_id operator*() const noexcept {
				return colored_thing_fat_id(container, colored_thing_id(colored_thing_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE object_iterator_colored_thing& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_colored_thing& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE object_iterator_colored_thing operator+(int32_t n) const noexcept {
				return object_iterator_colored_thing(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE object_iterator_colored_thing operator-(int32_t n) const noexcept {
				return object_iterator_colored_thing(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(object_iterator_colored_thing const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(object_iterator_colored_thing const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(object_iterator_colored_thing const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(object_iterator_colored_thing const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(object_iterator_colored_thing const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE colored_thing_fat_id operator[](int32_t n) const noexcept {
				return colored_thing_fat_id(container, colored_thing_id(colored_thing_id::value_base_t(int32_t(index) + n)));
			}
		};
		class const_object_iterator_colored_thing {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_colored_thing(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_colored_thing& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_colored_thing& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_colored_thing const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_colored_thing const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE colored_thing_const_fat_id operator*() const noexcept {
				return colored_thing_const_fat_id(container, colored_thing_id(colored_thing_id::value_base_t(index)));
			}
			DCON_RELEASE_INLINE const_object_iterator_colored_thing& operator+=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) + n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_colored_thing& operator-=(int32_t n) noexcept {
				index = uint32_t(int32_t(index) - n);
				return *this;
			}
			DCON_RELEASE_INLINE const_object_iterator_colored_thing operator+(int32_t n) const noexcept {
				return const_object_iterator_colored_thing(container, uint32_t(int32_t(index) + n));
			}
			DCON_RELEASE_INLINE const_object_iterator_colored_thing operator-(int32_t n) const noexcept {
				return const_object_iterator_colored_thing(container, uint32_t(int32_t(index) - n));
			}
			DCON_RELEASE_INLINE int32_t operator-(const_object_iterator_colored_thing const& o) const noexcept {
				return int32_t(index) - int32_t(o.index);
			}
			DCON_RELEASE_INLINE bool operator>(const_object_iterator_colored_thing const& o) const noexcept {
				return index > o.index;
			}
			DCON_RELEASE_INLINE bool operator>=(const_object_iterator_colored_thing const& o) const noexcept {
				return index >= o.index;
			}
			DCON_RELEASE_INLINE bool operator<(const_object_iterator_colored_thing const& o) const noexcept {
				return index < o.index;
			}
			DCON_RELEASE_INLINE bool operator<=(const_object_iterator_colored_thing const& o) const noexcept {
				return index <= o.index;
			}
			DCON_RELEASE_INLINE colored_thing_const_fat_id operator[](int32_t n) const noexcept {
				return colored_thing_const_fat_id(container, colored_thing_id(colored_thing_id::value_base_t(int32_t(index) + n)));
			}
		};
		
	}

	class alignas(64) data_container {
		public:
		internal::colored_thing_class colored_thing;

		//
		// Functions for colored_thing:
		//
		//
		// accessors for colored_thing: color
		//
		DCON_RELEASE_INLINE rgb_color const& colored_thing_get_color(colored_thing_id id) const noexcept {
			return colored_thing.m_color.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE rgb_color& colored_thing_get_color(colored_thing_id id) noexcept {
			return colored_thing.m_color.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE void colored_thing_set_color(colored_thing_id id, rgb_color const& value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			colored_thing.m_color.vptr()[id.index()] = value;
		}
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
			colored_thing.m_color.vptr()[id_removed.index()] = rgb_color{};
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
				std::fill_n(colored_thing.m_color.vptr() + new_size, old_size - new_size, rgb_color{});
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
		friend internal::const_object_iterator_colored_thing;
		friend internal::object_iterator_colored_thing;
		struct {
			internal::object_iterator_colored_thing begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_colored_thing));
				return internal::object_iterator_colored_thing(*container, uint32_t(0));
			}
			internal::object_iterator_colored_thing end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_colored_thing));
				return internal::object_iterator_colored_thing(*container, container->colored_thing_size());
			}
			internal::const_object_iterator_colored_thing begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_colored_thing));
				return internal::const_object_iterator_colored_thing(*container, uint32_t(0));
			}
			internal::const_object_iterator_colored_thing end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_colored_thing));
				return internal::const_object_iterator_colored_thing(*container, container->colored_thing_size());
			}
		}  in_colored_thing ;
		



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
			result.colored_thing_color = true;
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
			if(serialize_selection.colored_thing_color) {
				dcon::record_header iheader(0, "rgb_color", "colored_thing", "color");
				total_size += iheader.serialize_size();
				total_size += sizeof(rgb_color) * colored_thing.size_used;
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
			if(serialize_selection.colored_thing_color) {
				dcon::record_header header(sizeof(rgb_color) * colored_thing.size_used, "rgb_color", "colored_thing", "color");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<rgb_color*>(output_buffer), colored_thing.m_color.vptr(), sizeof(rgb_color) * colored_thing.size_used);
				output_buffer += sizeof(rgb_color) * colored_thing.size_used;
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
						if(header.is_object("colored_thing")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									colored_thing_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.colored_thing = true;
									break;
								}
								if(header.is_property("color")) {
									if(header.is_type("rgb_color")) {
										std::memcpy(colored_thing.m_color.vptr(), reinterpret_cast<rgb_color const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(rgb_color), header.record_size));
										serialize_selection.colored_thing_color = true;
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
						if(header.is_object("colored_thing") && mask.colored_thing) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									colored_thing_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.colored_thing = true;
									break;
								}
								if(header.is_property("color") && mask.colored_thing_color) {
									if(header.is_type("rgb_color")) {
										std::memcpy(colored_thing.m_color.vptr(), reinterpret_cast<rgb_color const*>(input_buffer), std::min(size_t(colored_thing.size_used) * sizeof(rgb_color), header.record_size));
										serialize_selection.colored_thing_color = true;
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
		

		void deserialize_rgb(std::byte const* start, std::byte const* end, load_record& record_in_out);
	};

	DCON_RELEASE_INLINE rgb_color& colored_thing_fat_id::get_color() const noexcept {
		return container.colored_thing_get_color(id);
	}
	DCON_RELEASE_INLINE void colored_thing_fat_id::set_color(rgb_color const& v) const noexcept {
		container.colored_thing_set_color(id, v);
	}
	DCON_RELEASE_INLINE bool colored_thing_fat_id::is_valid() const noexcept {
		return container.colored_thing_is_valid(id);
	}
	inline float colored_thing_fat_id::get_red() {
		return colored_thing_const_fat_id(container, id).get_red();
	}
	inline float colored_thing_fat_id::get_green() {
		return colored_thing_const_fat_id(container, id).get_green();
	}
	inline float colored_thing_fat_id::get_blue() {
		return colored_thing_const_fat_id(container, id).get_blue();
	}
	
	DCON_RELEASE_INLINE rgb_color const& colored_thing_const_fat_id::get_color() const noexcept {
		return container.colored_thing_get_color(id);
	}
	DCON_RELEASE_INLINE bool colored_thing_const_fat_id::is_valid() const noexcept {
		return container.colored_thing_is_valid(id);
	}
	

	namespace internal {
		DCON_RELEASE_INLINE object_iterator_colored_thing::object_iterator_colored_thing(data_container& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE const_object_iterator_colored_thing::const_object_iterator_colored_thing(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
		}
		DCON_RELEASE_INLINE object_iterator_colored_thing& object_iterator_colored_thing::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_colored_thing& const_object_iterator_colored_thing::operator++() noexcept {
			++index;
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_colored_thing& object_iterator_colored_thing::operator--() noexcept {
			--index;
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_colored_thing& const_object_iterator_colored_thing::operator--() noexcept {
			--index;
			return *this;
		}
		
	};


}

#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif

