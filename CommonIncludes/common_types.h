#pragma once
#include <cstdint>
#include <utility>
#include <algorithm>
#include <intrin.h>
#include <atomic>

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

	using stable_mk_2_tag = uint32_t;

	template<typename object_type, uint32_t minimum_size, size_t memory_size>
	class stable_variable_vector_storage_mk_2;

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
		void shrink_capacity(stable_mk_2_tag& i)[
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
				std::copy(detail::to_data<object_type, align>(header), detail::to_data<object_type, align>(header) + header->size, detail::to_data<object_type, align>(new_header));

				release(i);
				i = new_item;
			}
		]
		void release(stable_mk_2_tag& i) {
			if(i == std::numeric_limits<stable_mk_2_tag>::max())
				return;

			detail::mk_2_header* header = (detail::mk_2_header*)(backing_storage + i);

			const uint32_t free_list_pos = rt_log2(header->capacity);

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
				std::abort();
			}


			new_header->capacity = uint16_t(real_capacity);
			new_header->size = 0ui16;
			new_header->next_free = null_value_of<stable_mk_2_tag>;

			object_type* objects = detail::to_data<object_type, align>(new_header);
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
		return *(detail::to_data<object_type, align>(header) + inner_index);
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
	uint32_t get_capacity(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i) {
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			return header->capacity;
		} else {
			return 0ui32;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
	uint32_t get_size(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i) {
		if(i != std::numeric_limits<stable_mk_2_tag>::max()) {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			return header->size;
		} else {
			return 0ui32;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
	void push_back(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag& i, object_type obj) {
		if(i == std::numeric_limits<stable_mk_2_tag>::max()) {
			storage.increase_capacity(i, 1);
			detail::mk_2_header*header = (detail::mk_2_header*)(storage.backing_storage + i);

			*detail::to_data<object_type, align>(header) = obj;
			header->size = 1ui16;
		} else {
			detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
			if(header->size >= header->capacity) {
				storage.increase_capacity(i, header->size + 1);
				header = (detail::mk_2_header*)(storage.backing_storage + i);
			}
			*(detail::to_data<object_type, align>(header) + header->size) = obj;
			++header->size;
		}
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
	void pop_back(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size>& storage, stable_mk_2_tag i) {
		detail::mk_2_header* header = (detail::mk_2_header*)(storage.backing_storage + i);
		if(header->size != 0)
			--header->size;
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
	bool contains_item(stable_variable_vector_storage_mk_2<object_type, minimum_size, memory_size> const& storage, stable_mk_2_tag i, object_type obj) {
		const auto range = get_range(storage, i);
		return std::find(range.first, range.second, obj) != range.second;
	}

	template<typename object_type, uint32_t minimum_size, size_t memory_size, int32_t align>
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

}

#undef COM_RELEASE_INLINE
