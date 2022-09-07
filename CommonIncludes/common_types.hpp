#pragma once

//
// This file provided as part of the DataContainer project
//

#include <cstdint>
#include <utility>
#include <algorithm>
#include <intrin.h>
#include <atomic>
#include <cstddef>
#include <type_traits>
#include <new>
#include <array>
#include <cstring>

#ifdef NDEBUG 
#ifdef _MSC_VER 
#define COM_RELEASE_INLINE __forceinline
#else
#define COM_RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define COM_RELEASE_INLINE inline
#endif

namespace dcon {
	struct bitfield_type {
		uint8_t v = 0;

		bool operator[](int32_t i) const { return ((v >> i) & 1) != 0; }
	};

	static_assert(sizeof(bitfield_type) == 1);

	inline void bit_vector_set(bitfield_type* v, int32_t index, bool value) {
		const int32_t real_index = index >> 3;
		const uint32_t sub_index = uint32_t(index) & 7ui32;
		if(value)
			v[real_index].v |= uint8_t(1ui32 << sub_index);
		else
			v[real_index].v &= uint8_t(~(1ui32 << sub_index));
	}

	inline bool bit_vector_test(bitfield_type const* v, int32_t index) {
		const int32_t real_index = index >> 3;
		const uint32_t sub_index = uint32_t(index) & 7ui32;
		return (v[real_index].v & (1ui32 << sub_index)) != 0;
	}

	inline bool char_span_equals_str(char const* start, char const* end, char const* n) {
		while(start != end) {
			if(*start != *n)
				return false;
			++n;
			++start;
		}
		return *n == 0;
	}

	namespace detail {
		template<typename T>
		constexpr auto has_index_fn(int) -> std::enable_if_t<!std::is_same_v<decltype(std::declval<T>().index()), void>, bool> { return true; }
		template<typename T>
		constexpr auto has_index_fn(...) { return false; }
	}

	template<typename T>
	COM_RELEASE_INLINE int32_t get_index(T id) {
		if constexpr(detail::has_index_fn<T>(0)) {
			return static_cast<int32_t>(id.index());
		} else {
			using ref_removed_type = std::remove_cv_t<std::remove_reference_t<T>>;
			using signed_type = std::make_signed_t<ref_removed_type>;
			return static_cast<int32_t>(static_cast<signed_type>(id));
		}
	}

#ifdef DCON_USE_EXCEPTIONS
	struct out_of_space {};
#endif

	template<typename T>
	class local_vector {
		// yes, I am aware that boost has a better version of the small vector optimization,
		// but I didn't want to force anyone to take a dependency on boost just for that

		T* ptr_end = nullptr;
		std::vector<T> expanded_storage;
		T storage[128];
	public:
		template<typename it>
		local_vector(it first, it second) {
			if(second - first > 128) {
				expanded_storage.insert(expanded_storage.end(), first, second);
				ptr_end = storage + 129;
			} else {
				ptr_end = std::copy(first, second, storage);
			}
		}
		local_vector() {
			ptr_end = storage;
		}
		void push_back(T val) {
			if(ptr_end - storage < 128) {
				*ptr_end = val;
				++ptr_end;
			} else if(ptr_end - storage == 128) {
				expanded_storage.insert(expanded_storage.end(), storage, ptr_end);
				++ptr_end;
				expanded_storage.push_back(val);
			} else {
				expanded_storage.push_back(val);
			}
		}
		T* begin() { return (ptr_end - storage <= 128) ? storage : expanded_storage.data(); }
		T* end() { return (ptr_end - storage <= 128) ? ptr_end : expanded_storage.data() + expanded_storage.size(); }
	};

	template<size_t N>
	struct key_data_extended {
		std::array<uint8_t, N> values;

		key_data_extended() {
			values.fill(0);
		}
		bool operator==(key_data_extended<N> const& other) const noexcept {
			return std::memcmp(values.data(), other.values.data(), 7) == 0;
		}
		bool operator!=(key_data_extended<N> const& other) const noexcept {
			return std::memcmp(values.data(), other.values.data(), 7) != 0;
		}
	};

	struct record_header {
		uint64_t record_size;

		char const* type_name_start;
		char const* type_name_end;

		char const* object_name_start;
		char const* object_name_end;

		char const* property_name_start;
		char const* property_name_end;

		record_header() {}
		record_header(uint64_t sz, char  const* type, char  const* object, char const* property) :
			record_size(uint32_t(sz)), type_name_start(type), object_name_start(object), property_name_start(property) {
			type_name_end = type_name_start + strlen(type_name_start);
			object_name_end = object_name_start + strlen(object_name_start);
			property_name_end = property_name_start + strlen(property_name_start);
		}

		uint64_t serialize_size() const {
			return sizeof(uint64_t) + (type_name_end - type_name_start) + (object_name_end - object_name_start) + (property_name_end - property_name_start) + 3;
		}
		void serialize(std::byte*& output_buffer) const {
			uint64_t* sz = reinterpret_cast<uint64_t*>(output_buffer);
			*sz = record_size;


			char* output = reinterpret_cast<char*>(output_buffer + sizeof(uint64_t));
			memcpy(output, type_name_start, type_name_end - type_name_start);
			output += (type_name_end - type_name_start);
			*output = 0;
			++output;
			memcpy(output, object_name_start, object_name_end - object_name_start);
			output += (object_name_end - object_name_start);
			*output = 0;
			++output;
			memcpy(output, property_name_start, property_name_end - property_name_start);
			output += (property_name_end - property_name_start);
			*output = 0;
			++output;

			output_buffer += sizeof(uint64_t) + (type_name_end - type_name_start) + (object_name_end - object_name_start) + (property_name_end - property_name_start) + 3;
		}
		void deserialize(std::byte const*& input_buffer, std::byte const* end) {
			record_size = 0;
			type_name_start = nullptr;
			type_name_end = nullptr;
			object_name_start = nullptr;
			object_name_end = nullptr;
			property_name_start = nullptr;
			property_name_end = nullptr;

			if(end - input_buffer < sizeof(uint64_t)) {
				return;
			}
			uint64_t const* sz = reinterpret_cast<uint64_t const*>(input_buffer);
			record_size = *sz;
			input_buffer += sizeof(uint64_t);
			type_name_start = reinterpret_cast<char const*>(input_buffer);
			while(input_buffer < end && *input_buffer != std::byte(0)) {
				++input_buffer;
			}
			type_name_end = reinterpret_cast<char const*>(input_buffer);
			++input_buffer;

			object_name_start = reinterpret_cast<char const*>(input_buffer);
			while(input_buffer < end && *input_buffer != std::byte(0)) {
				++input_buffer;
			}
			object_name_end = reinterpret_cast<char const*>(input_buffer);
			++input_buffer;

			property_name_start = reinterpret_cast<char const*>(input_buffer);
			while(input_buffer < end && *input_buffer != std::byte(0)) {
				++input_buffer;
			}
			property_name_end = reinterpret_cast<char const*>(input_buffer);
			++input_buffer;
		}

		bool is_type(char const* n) const {
			char const* i = type_name_start;
			while(i != type_name_end) {
				if(*i != *n)
					return false;
				++n;
				++i;
			}
			return *i == *n;
		}
		bool is_object(char const* n) const {
			char const* i = object_name_start;
			while(i != object_name_end) {
				if(*i != *n)
					return false;
				++n;
				++i;
			}
			return *i == *n;
		}
		bool is_property(char const* n) const {
			char const* i = property_name_start;
			while(i != property_name_end) {
				if(*i != *n)
					return false;
				++n;
				++i;
			}
			return *i == *n;
		}
	};

	template<typename T>
	void for_each_record(std::byte const* input_buffer, std::byte const* end, T&& functor) {
		while(input_buffer < end) {
			dcon::record_header header;
			header.deserialize(input_buffer, end);
			if(input_buffer + header.record_size <= end) {
				functor(header, input_buffer, input_buffer + header.record_size <= end ? input_buffer + header.record_size : end);
			}
			input_buffer += header.record_size;
		}
	}

	using stable_mk_2_tag = uint32_t;

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	class stable_variable_vector_storage_mk_2;

	constexpr uint32_t ct_log2(uint32_t n) {
		return ((n < 2) ? 0 : 1 + ct_log2(n / 2));
	}

	namespace detail {
		struct alignas(8) mk_2_header {
			stable_mk_2_tag next_free;
			uint16_t size;
			uint16_t capacity;
		};
		static_assert(sizeof(mk_2_header) == 8);

		template<typename T>
		constexpr T* to_data(mk_2_header* h) {
			return (T*)(h + 1);
		}
	

		union concurrent_key_pair_helper {
			struct {
				uint32_t index;
				uint32_t counter;
			} parts;
			uint64_t value;

			constexpr explicit concurrent_key_pair_helper(uint32_t i, uint32_t c) : parts{ i, c } {}
			constexpr explicit concurrent_key_pair_helper(uint64_t v) : value{ v } {}
		};

		inline uint32_t rt_log2_round_up(uint32_t n) {
#ifndef _MSC_VER
			return n > 1ui32 ? 32ui32 - uint32_t(__builtin_clz(n - 1ui32)) : 0ui32;
#else
			return n > 1ui32 ? 32ui32 - uint32_t(__lzcnt(n - 1ui32)) : 0ui32;
#endif
		}

		inline uint32_t rt_log2(uint32_t n) {
#ifndef _MSC_VER
			return 31ui32 - uint32_t(__builtin_clz(n | 1ui32));
#else
			return 31ui32 - uint32_t(__lzcnt(n | 1ui32));
#endif
		}

		inline stable_mk_2_tag try_pop_free_list(std::atomic<uint64_t>& free_list_head, uint64_t* backing_storage) {
			uint64_t free_list_value = free_list_head.load(std::memory_order_acquire);
			detail::mk_2_header* ptr = nullptr;

			do {
				auto index = concurrent_key_pair_helper(free_list_value).parts.index;
				if(index == std::numeric_limits<stable_mk_2_tag>::max())
					return std::numeric_limits<stable_mk_2_tag>::max();
				ptr = (detail::mk_2_header*)(backing_storage + index);

			} while(!free_list_head.compare_exchange_strong(
				free_list_value,
				concurrent_key_pair_helper(ptr->next_free, concurrent_key_pair_helper(free_list_value).parts.counter + 1).value, std::memory_order_acq_rel));

			ptr->size = 0ui16;
			return concurrent_key_pair_helper(free_list_value).parts.index;
		}

		template<typename object_type, uint32_t minimum_size, size_t memory_size>
		stable_mk_2_tag return_new_memory(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, uint32_t requested_capacity);
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	class stable_variable_vector_storage_mk_2 {
	public:
		using contents_type = object_type;

		uint64_t backing_storage[memory_size];
		std::atomic<uint32_t> first_free = 0ui32;

		std::atomic<uint64_t> free_lists[17] = {
			detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value,
			detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value,
			detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value,
			detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value,
			detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value };


		void reset() {
			first_free = 0ui32;
			for(uint32_t i = 0; i < std::extent_v<decltype(free_lists)>; ++i)
				free_lists[i].store(detail::concurrent_key_pair_helper(std::numeric_limits<stable_mk_2_tag>::max(), 0).value, std::memory_order_release);
		}
		stable_mk_2_tag make_new(uint32_t capacity) {
			const uint32_t free_list_pos = detail::rt_log2_round_up(capacity > minimum_size ? capacity : minimum_size);

			if(auto res = detail::try_pop_free_list(free_lists[free_list_pos], backing_storage); res != std::numeric_limits<stable_mk_2_tag>::max()) {
				return res;
			} else if(auto resb = detail::try_pop_free_list(free_lists[free_list_pos + 1], backing_storage); resb != std::numeric_limits<stable_mk_2_tag>::max()) {
				return resb;
			} else {
				return detail::return_new_memory(*this, capacity);
			}
		}
		void increase_capacity(stable_mk_2_tag& i, uint32_t new_capacity) {
			if(i == std::numeric_limits<stable_mk_2_tag>::max()) {
				i = make_new(new_capacity);
			} else {
				detail::mk_2_header* header = (detail::mk_2_header*)(backing_storage + i);
				if(new_capacity > header->capacity) {
					const auto new_item = make_new(new_capacity);

					detail::mk_2_header* new_header = (detail::mk_2_header*)(backing_storage + new_item);
					new_header->size = header->size;
					std::copy(detail::to_data<object_type>(header), detail::to_data<object_type>(header) + header->size, detail::to_data<object_type>(new_header));

					release(i);
					i = new_item;
				}
			}
		}
		void shrink_capacity(stable_mk_2_tag& i) {
			detail::mk_2_header* header = (detail::mk_2_header*)(backing_storage + i);

			if(header->size == 0ui16) {
				release(i);
				return;
			}

			const uint32_t target_free_list_pos = detail::rt_log2_round_up(header->size > minimum_size ? header->size : minimum_size);
			const uint32_t free_list_pos = detail::rt_log2(header->capacity);

			if(target_free_list_pos + 1 < free_list_pos) {
				const auto new_item = make_new(header->size);

				detail::mk_2_header* new_header = (detail::mk_2_header*)(backing_storage + new_item);
				new_header->size = header->size;
				std::copy(detail::to_data<object_type>(header), detail::to_data<object_type>(header) + header->size, detail::to_data<object_type>(new_header));

				release(i);
				i = new_item;
			}
		}
		void release(stable_mk_2_tag& i) {
			if(i == std::numeric_limits<stable_mk_2_tag>::max())
				return;

			detail::mk_2_header* header = (detail::mk_2_header*)(backing_storage + i);

			const uint32_t free_list_pos = detail::rt_log2(header->capacity);

			uint64_t free_list_value = free_lists[free_list_pos].load(std::memory_order_acquire);
			do {
				header->next_free = detail::concurrent_key_pair_helper(free_list_value).parts.index;
				header->size = 0ui16;
			} while(!free_lists[free_list_pos].compare_exchange_strong(
				free_list_value,
				detail::concurrent_key_pair_helper(i, detail::concurrent_key_pair_helper(free_list_value).parts.counter + 1).value, std::memory_order_acq_rel));


			i = std::numeric_limits<stable_mk_2_tag>::max();
		}
	};

	namespace detail {
		template<typename object_type, uint32_t minimum_size, size_t memory_size>
		stable_mk_2_tag return_new_memory(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, uint32_t requested_capacity) {
			const uint32_t real_capacity = 1ui32 << rt_log2_round_up(requested_capacity > minimum_size ? requested_capacity : minimum_size);

			mk_2_header* new_header;
			stable_mk_2_tag new_mem;


			const uint32_t qword_size = 1ui32 + (real_capacity * sizeof(object_type) + 7ui32) / 8ui32;
			auto old_position = storage.first_free.fetch_add(qword_size, std::memory_order_acq_rel);

			new_mem = old_position;
			new_header = (mk_2_header*)(storage.backing_storage + old_position);


			if(storage.first_free >= memory_size) {
#ifndef DCON_USE_EXCEPTIONS
				std::abort();
#else
				throw out_of_space{};
#endif
			}


			new_header->capacity = uint16_t(real_capacity);
			new_header->size = 0ui16;
			new_header->next_free = std::numeric_limits<stable_mk_2_tag>::max();

			object_type* objects = detail::to_data<object_type>(new_header);
			for(int32_t i = int32_t(real_capacity) - 1; i >= 0; --i)
				new (objects + i) object_type();

			return new_mem;
		}
	}

	//general interface, safe from any thread
	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	std::pair<object_type*, object_type*> get_range(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i) {
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			return std::pair<object_type*, object_type*>(detail::to_data<object_type>(header), detail::to_data<object_type>(header) + header->size);
		} else {
			return std::pair<object_type*, object_type*>(nullptr, nullptr);
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	object_type& get(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i, uint32_t inner_index) {
		detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
		return *(detail::to_data<object_type>(header) + inner_index);
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	uint32_t get_capacity(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i) {
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			return header->capacity;
		} else {
			return 0ui32;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	uint32_t get_size(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i) {
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			return header->size;
		} else {
			return 0ui32;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void push_back(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag& i, object_type obj) {
		if(i == std::numeric_limits<stable_mk_2_tag>::max()) {
			storage.increase_capacity(i, 1);
			detail::mk_2_header*header = (detail::mk_2_header*)(storage.backing_storage + i);

			*detail::to_data<object_type>(header) = obj;
			header->size = 1ui16;
		} else {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			if(header->size >= header->capacity) {
				storage.increase_capacity(i, header->size + 1);
				header = (detail::mk_2_header*)(storage.backing_storage + i);
			}
			*(detail::to_data<object_type>(header) + header->size) = obj;
			++header->size;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void pop_back(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag i) {
		detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
		if(header->size != 0)
			--header->size;
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void remove_at(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag i, uint32_t inner_index) {
		detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);

		*(detail::to_data<object_type>(header) + inner_index) = *(detail::to_data<object_type>(header) + header->size - 1);

		if(header->size != 0)
			--header->size;
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	bool contains_item(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i, object_type obj) {
		const auto range = get_range(storage, i);
		return std::find(range.first, range.second, obj) != range.second;
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void add_unique_item(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag& i, object_type obj) {
		if(!contains_item(storage, i, obj))
			push_back(storage, i, obj);
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void remove_unique_item(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag i, object_type obj) {
		const auto range = get_range(storage, i);
		if(auto pos = std::find(range.first, range.second, obj); pos != range.second) {
			*pos = *(range.second - 1);
			pop_back(storage, i);
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void replace_unique_item(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag i, object_type obj, object_type new_val) {
		const auto range = get_range(storage, i);
		if(auto pos = std::find(range.first, range.second, obj); pos != range.second) {
			*pos = new_val;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void load_range(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag& i, object_type const* first, object_type const* last) {
		storage.increase_capacity(i, static_cast<uint32_t>(last - first));
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			header->size = static_cast<uint16_t>(last - first);
			memcpy(detail::to_data<object_type>(header), first, (last - first) * sizeof(object_type));
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	void resize(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag& i, uint32_t new_size) {
		auto old_size = get_size(storage, i);
		if(new_size < old_size) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			header->size = uint16_t(new_size);
		} else if(new_size > old_size) {
			storage.increase_capacity(i, new_size);
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			std::fill(detail::to_data<object_type>(header) + header->size, detail::to_data<object_type>(header) + new_size, object_type());
			header->size = uint16_t(new_size);
		}

	}

	template <typename T>
	struct cache_aligned_allocator {
		using value_type = T;

		cache_aligned_allocator() noexcept {}
		template<class U> cache_aligned_allocator(const cache_aligned_allocator<U>&) noexcept {}
		template<class U> bool operator==(const cache_aligned_allocator<U>&) const noexcept {
			return true;
		}
		template<class U> bool operator!=(const cache_aligned_allocator<U>&) const noexcept {
			return false;
		}

		T* allocate(size_t n) {
			return (T*)(::operator new(n * sizeof(T), std::align_val_t{ 64 }));
		}
		void deallocate(T* p, size_t ) {
			::operator delete(p, std::align_val_t{ 64 });
		}
	};
}

#undef COM_RELEASE_INLINE
