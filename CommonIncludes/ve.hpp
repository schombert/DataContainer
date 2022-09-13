#pragma once

//
// This file provided as part of the DataContainer project
//

#include <immintrin.h>
#include <cstdint>
#include <new>
#include <cassert>
#include <type_traits>
#include <cstdint>
#include "common_types.hpp"


#ifndef VE_NO_TBB
#include <ppl.h>
#endif

#ifdef NDEBUG 
#ifdef _MSC_VER 
#define RELEASE_INLINE __forceinline
#else
#define RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define RELEASE_INLINE inline
#endif


#ifdef __AVX2__
#include "ve_avx2.hpp"
#else
#ifdef __AVX__
#include "ve_avx.hpp"
#else // SSE
#include "ve_sse.hpp"
#endif
#endif


namespace ve {

	template<typename T, typename index_type>
	class vectorizable_buffer {
	private:
		T* values = nullptr;
	public:
		vectorizable_buffer(uint32_t count) {
			values = (T*)(::operator new(uint64_t(64) + ((count * sizeof(T) + uint64_t(63)) & ~uint64_t(63)), std::align_val_t{ 64 }));
			std::uninitialized_value_construct_n(values + uint64_t(64) / sizeof(T) - 1, ((count * sizeof(T) + uint64_t(63)) & ~uint64_t(63)) / sizeof(T) + 1);
		};
		vectorizable_buffer(vectorizable_buffer&& other) noexcept {
			std::swap(values, other.values);
		};
		~vectorizable_buffer() {
			::operator delete(values, std::align_val_t{ 64 });
			values = nullptr;
		}

		vectorizable_buffer& operator=(vectorizable_buffer&& other) noexcept {
			std::swap(values, other.values);
		}

		T* vptr() const noexcept { return values + uint64_t(64) / sizeof(T); }

		RELEASE_INLINE T const& get(index_type i) const noexcept { return vptr()[i.index()]; }
		RELEASE_INLINE T& get(index_type i) noexcept { return vptr()[i.index()]; }
		RELEASE_INLINE value_to_vector_type<T> get(contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(unaligned_contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(partial_contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(tagged_vector<index_type> i) const noexcept { return ve::load(i, vptr()); }

		RELEASE_INLINE void set(index_type i, T value) noexcept { vptr()[i.index()] = value; }
		RELEASE_INLINE void set(contiguous_tags<index_type> i, value_to_vector_type<T> vin) noexcept { ve::store(i, vptr(), vin); }
		RELEASE_INLINE void set(unaligned_contiguous_tags<index_type> i, value_to_vector_type<T> vin) noexcept { ve::store(i, vptr(), vin); }
		RELEASE_INLINE void set(partial_contiguous_tags<index_type> i, value_to_vector_type<T> vin) noexcept { ve::store(i, vptr(), vin); }
		RELEASE_INLINE void set(tagged_vector<index_type> i, value_to_vector_type<T> vin) noexcept { ve::store(i, vptr(), vin); }

	};


	struct partition_range {
		uint32_t low;
		uint32_t high;
	};

	template<uint32_t divisions_count, uint32_t chunk_size>
	partition_range generate_partition_range(int32_t partition_index, int32_t total_count) {
		uint32_t const total_chunks = uint32_t((total_count + chunk_size - 1) / chunk_size);
		uint32_t const low_chunk_size = total_chunks / divisions_count;
		uint32_t const high_chunks_count = total_chunks - low_chunk_size * divisions_count;

		if(uint32_t(partition_index) < divisions_count - high_chunks_count) {
			return partition_range{ uint32_t(partition_index) * low_chunk_size * chunk_size, uint32_t(partition_index + 1) * low_chunk_size * chunk_size };
		} else {
			uint32_t const first_high_chunk = (divisions_count - high_chunks_count) * low_chunk_size * chunk_size;
			uint32_t const high_chunk_index = uint32_t(partition_index) - (divisions_count - high_chunks_count);

			return partition_range{
				first_high_chunk + high_chunk_index * (low_chunk_size + 1) * chunk_size,
				std::min(first_high_chunk + (high_chunk_index + 1) * (low_chunk_size + 1) * chunk_size, uint32_t(total_count))
			};
		}
	}

	constexpr int32_t block_repitition = 4;

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_serial_fast(uint32_t count, F&& functor) {
		const uint32_t full_units = (count + uint32_t(vector_size - 1)) & ~uint32_t(vector_size - 1);
		const uint32_t reps = full_units / vector_size;
		const uint32_t quad_reps = reps / uint32_t(block_repitition);

		int32_t i = 0;
		for(; i < int32_t(quad_reps); ++i) {
			functor(contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 2));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 3));
		}
		if((reps & 3) == 1) {
			functor(contiguous_tags<tag_type>(i * (vector_size * 4)));
		} else if((reps & 3) == 2) {
			functor(contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
		} else if((reps & 3) == 3) {
			functor(contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
			functor(contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 2));
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_serial(uint32_t count, F&& functor) {
		const uint32_t full_units = count & ~uint32_t(vector_size - 1);
		const uint32_t remainder = count & uint32_t(vector_size - 1);

		execute_serial_fast<tag_type>(full_units, std::forward<F>(functor));

		if(remainder != 0) {
			functor(partial_contiguous_tags<tag_type>(full_units, remainder));
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_serial_unaligned(uint32_t count, F&& functor) {
		const uint32_t full_units = count & ~uint32_t(vector_size - 1);
		const uint32_t remainder = count & uint32_t(vector_size - 1);

		const uint32_t reps = full_units / vector_size;
		const uint32_t quad_reps = reps / uint32_t(block_repitition);

		int32_t i = 0;
		for(; i < int32_t(quad_reps); ++i) {
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 2));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 3));
		}
		if((reps & 3) == 1) {
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4)));
		} else if((reps & 3) == 2) {
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
		} else if((reps & 3) == 3) {
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4)));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size));
			functor(unaligned_contiguous_tags<tag_type>(i * (vector_size * 4) + vector_size * 2));
		}

		if(remainder != 0) {
			functor(partial_contiguous_tags<tag_type>(full_units, remainder));
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_subsequence(uint32_t start, uint32_t end, F&& functor) {
		const auto count = start - end;
		const uint32_t full_units = count & ~uint32_t(vector_size - 1);
		const uint32_t remainder = count - full_units;

		for(int32_t i = 0; i < int32_t(full_units); i += vector_size) {
			functor(unaligned_contiguous_tags<tag_type>(start + i));
		}
		if(remainder != 0) {
			functor(partial_contiguous_tags<tag_type>(full_units + start, remainder));
		}
	}

#ifndef VE_NO_TBB
	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel(uint32_t start, uint32_t count, F&& functor) {
		const uint32_t full_units = (count + uint32_t(15)) & ~uint32_t(15);
		concurrency::parallel_for(start, full_units, uint32_t(16), [&functor](uint32_t offset) {
			if constexpr(vector_size == 16) {
				functor(contiguous_tags<tag_type>(offset));
			} else if constexpr(vector_size == 8) {
				functor(contiguous_tags<tag_type>(offset));
				functor(contiguous_tags<tag_type>(offset + 8));
			} else if constexpr(vector_size == 4) {
				functor(contiguous_tags<tag_type>(offset));
				functor(contiguous_tags<tag_type>(offset + 4));
				functor(contiguous_tags<tag_type>(offset + 8));
				functor(contiguous_tags<tag_type>(offset + 12));
			} else {
				static_assert(vector_size == 16 || vector_size == 8 || vector_size == 4);
			}
		}, concurrency::static_partitioner());
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel(uint32_t count, F functor) {
		execute_parallel<tag_type>(0, count, functor);
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel_exact(uint32_t start, uint32_t count, F&& functor) {
		const uint32_t full_units = count & ~uint32_t(15);
		const uint32_t remainder = count - full_units;
		concurrency::parallel_for(start, full_units, uint32_t(16), [&functor](uint32_t offset) {
			if constexpr(vector_size == 16) {
				functor(contiguous_tags<tag_type>(offset));
			} else if constexpr(vector_size == 8) {
				functor(contiguous_tags<tag_type>(offset));
				functor(contiguous_tags<tag_type>(offset + 8));
			} else if constexpr(vector_size == 4) {
				functor(contiguous_tags<tag_type>(offset));
				functor(contiguous_tags<tag_type>(offset + 4));
				functor(contiguous_tags<tag_type>(offset + 8));
				functor(contiguous_tags<tag_type>(offset + 12));
			} else {
				static_assert(vector_size == 16 || vector_size == 8 || vector_size == 4);
			}
		}, concurrency::static_partitioner());
		if constexpr(vector_size == 16) {
			if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 8) {
			if(remainder > uint32_t(8)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(8), remainder - uint32_t(8)));
			} else if(remainder == uint32_t(8)) {
				functor(contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 4) {
			if(remainder > uint32_t(12)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(8)));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(12), remainder - uint32_t(12)));
			} else if(remainder == uint32_t(12)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(8)));
			} else if(remainder > uint32_t(8)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(8), remainder - uint32_t(8)));
			} else if(remainder == uint32_t(8)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + uint32_t(4)));
			} else if(remainder > uint32_t(4)) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(4), remainder - uint32_t(4)));
			} else if(remainder == uint32_t(4)) {
				functor(contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel_unaligned(uint32_t start, uint32_t count, F&& functor) {
		const uint32_t full_units = count & ~uint32_t(15);
		const uint32_t remainder = count - full_units;
		concurrency::parallel_for(start, full_units, uint32_t(16), [&functor](uint32_t offset) {
			if constexpr(vector_size == 16) {
				functor(unaligned_contiguous_tags<tag_type>(offset));
			} else if constexpr(vector_size == 8) {
				functor(unaligned_contiguous_tags<tag_type>(offset));
				functor(unaligned_contiguous_tags<tag_type>(offset + 8));
			} else if constexpr(vector_size == 4) {
				functor(unaligned_contiguous_tags<tag_type>(offset));
				functor(unaligned_contiguous_tags<tag_type>(offset + 4));
				functor(unaligned_contiguous_tags<tag_type>(offset + 8));
				functor(unaligned_contiguous_tags<tag_type>(offset + 12));
			} else {
				static_assert(vector_size == 16 || vector_size == 8 || vector_size == 4);
			}
		}, concurrency::static_partitioner());
		if constexpr(vector_size == 16) {
			if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 8) {
			if(remainder > uint32_t(8)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(8), remainder - uint32_t(8)));
			} else if(remainder == uint32_t(8)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 4) {
			if(remainder > uint32_t(12)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(8)));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(12), remainder - uint32_t(12)));
			} else if(remainder == uint32_t(12)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(8)));
			} else if(remainder > uint32_t(8)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(4)));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(8), remainder - uint32_t(8)));
			} else if(remainder == uint32_t(8)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + uint32_t(4)));
			} else if(remainder > uint32_t(4)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + uint32_t(4), remainder - uint32_t(4)));
			} else if(remainder == uint32_t(4)) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel_exact(uint32_t count, F&& functor) {
		execute_parallel_exact<tag_type>(0, count, functor);
	}
#endif

	struct serial_exact {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			execute_serial<tag_type>(count, functor);
		}
	};
	struct serial_unaligned {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			execute_serial_unaligned<tag_type>(count, functor);
		}
	};
	struct serial {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			assert(count % ve::vector_size == 0);
			execute_serial_fast<tag_type>(count, functor);
		}
	};

#ifndef VE_NO_TBB
	struct par {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			assert(count % ve::vector_size == 0);
			execute_parallel<tag_type>(count, functor);
		}
	};
	struct par_exact {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			execute_parallel_exact<tag_type>(count, functor);
		}
	};
	struct par_unaligned {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F&& functor) {
			execute_parallel_unaligned<tag_type>(count, functor);
		}
	};
#endif

	constexpr inline uint32_t to_vector_size(uint32_t i) {
		return (i + (ve::vector_size - uint32_t(1))) & ~(ve::vector_size - uint32_t(1));
	}

}

#undef RELEASE_INLINE
