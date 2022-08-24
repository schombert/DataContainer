#pragma once

//
// This file provided as part of the DataContainer project
//

#include <intrin.h>
#include <cstdint>
#include <new>
#include <cassert>
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

#pragma warning( push )
#pragma warning( disable : 4324)

#ifdef __AVX2__
#include "ve_avx2.hpp"
#else
#ifdef __AVX__
#include "ve_avx.hpp"
#else // SSE
#include "ve_sse.hpp"
#endif
#endif

#pragma warning( pop ) 

namespace ve {

	template<typename T, typename index_type>
	class vectorizable_buffer {
	private:
		T* values = nullptr;
	public:
		vectorizable_buffer(uint32_t count) {
			values = (T*)(::operator new(64ui64 + ((count * sizeof(T) + 63ui64) & ~63ui64), std::align_val_t{ 64 }));
			std::uninitialized_value_construct_n(values + 64ui64 / sizeof(T) - 1, ((count * sizeof(T) + 63ui64) & ~63ui64) / sizeof(T) + 1);
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

		T* vptr() const noexcept { return values + 64ui64 / sizeof(T); }

		RELEASE_INLINE T const& get(index_type i) const noexcept { return vptr()[i.index()]; }
		RELEASE_INLINE T& get(index_type i) noexcept { return vptr()[i.index()]; }
		RELEASE_INLINE value_to_vector_type<T> get(contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(unaligned_contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(partial_contiguous_tags<index_type> i) const noexcept { return ve::load(i, vptr()); }
		RELEASE_INLINE value_to_vector_type<T> get(tagged_vector<index_type> i) const noexcept { return ve::load(i.value, vptr()); }

		RELEASE_INLINE void set(index_type i, T value) noexcept { vptr()[i.index()] = value; }
		RELEASE_INLINE void set(contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept { ve::store(i, vptr(), values); }
		RELEASE_INLINE void set(unaligned_contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept { ve::store(i, vptr(), values); }
		RELEASE_INLINE void set(partial_contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept { ve::store(i, vptr(), values); }
		RELEASE_INLINE void set(tagged_vector<index_type> i, value_to_vector_type<T> values) noexcept { ve::store(i.value, vptr(), values); }

	};


	RELEASE_INLINE constexpr float to_float(int32_t value) { return float(value); }
	RELEASE_INLINE constexpr bool and_not(bool a, bool b) { return (!b) && a; }
	RELEASE_INLINE constexpr float inverse(float a) { return 1.0f / a; }
	RELEASE_INLINE float sqrt(float a) { return std::sqrt(a); }
	RELEASE_INLINE float inverse_sqrt(float a) { return 1.0f / std::sqrt(a); }

	RELEASE_INLINE constexpr float multiply_and_add(float a, float b, float c) { return a * b + c; }
	RELEASE_INLINE constexpr float multiply_and_subtract(float a, float b, float c) { return a * b - c; }
	RELEASE_INLINE float negate_multiply_and_add(float a, float b, float c) { return c - (a * b); }
	RELEASE_INLINE float negate_multiply_and_subtract(float a, float b, float c) { return -(a * b) - c; }
	RELEASE_INLINE constexpr float min(float a, float b) { return std::min(a,b); }
	RELEASE_INLINE constexpr float max(float a, float b) { return std::max(a,b); }
	RELEASE_INLINE float ceil(float a) { return std::ceil(a); }
	RELEASE_INLINE float floor(float a) { return std::floor(a); }
	RELEASE_INLINE bool compress_mask(bool mask) { return mask; }

	RELEASE_INLINE constexpr float select(bool t, float a, float b) { return t ? a : b; }
	RELEASE_INLINE constexpr int32_t select(bool t, int32_t a, int32_t b) { return t ? a : b; }
	RELEASE_INLINE mask_vector widen_mask(mask_vector mask) { return mask; }
	RELEASE_INLINE bool widen_mask(bool mask) { return mask; }
	RELEASE_INLINE bool bit_test(int32_t val, int32_t bits) { return (val & bits) == bits; }

	template<typename T>
	RELEASE_INLINE auto improved_inverse(T a) {
		auto i = inverse(a);
		//return  -(a * i * i) + (i + i);
		return negate_multiply_and_add(a, i * i, i + i);
	}

	
	RELEASE_INLINE bool load(int32_t e, dcon::bitfield_type const* source) {
		return dcon::bit_vector_test(source, uint32_t(e));
	}

	template<typename U>
	RELEASE_INLINE auto load(int32_t e, U const* source) -> std::enable_if_t < !std::is_same_v<std::remove_cv_t<U>, dcon::bitfield_type>, U> {
		return source[e];
	}

	RELEASE_INLINE void store(int32_t e, float* dest, float value) {
		dest[e] = value;
	}

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
	RELEASE_INLINE void execute_serial_fast(uint32_t count, F functor) {
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
	RELEASE_INLINE void execute_serial(uint32_t count, F functor) {
		const uint32_t full_units = count & ~uint32_t(vector_size - 1);
		const uint32_t remainder = count & uint32_t(vector_size - 1);

		execute_serial_fast<tag_type>(full_units, std::forward<F>(functor));

		if(remainder != 0) {
			functor(partial_contiguous_tags<tag_type>(full_units, remainder));
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_serial_unaligned(uint32_t count, F functor) {
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

	template<typename index_type, typename F>
	RELEASE_INLINE void execute_single(index_type offset, F functor) {
		functor(offset);
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_subsequence(uint32_t start, uint32_t end, F functor) {
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
	RELEASE_INLINE void execute_parallel(uint32_t start, uint32_t count, F functor) {
		const uint32_t full_units = (count + 15ui32) & ~15ui32;
		concurrency::parallel_for(start, full_units, 16ui32, [&functor](uint32_t offset) {
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
	RELEASE_INLINE void execute_parallel_exact(uint32_t start, uint32_t count, F functor) {
		const uint32_t full_units = count & ~15ui32;
		const uint32_t remainder = count - full_units;
		concurrency::parallel_for(start, full_units, 16ui32, [&functor](uint32_t offset) {
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
			if(remainder > 8ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + 8ui32, remainder - 8ui32));
			} else if(remainder == 8ui32) {
				functor(contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 4) {
			if(remainder > 12ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + 4ui32));
				functor(contiguous_tags<tag_type>(full_units + 8ui32));
				functor(partial_contiguous_tags<tag_type>(full_units + 12ui32, remainder - 12ui32));
			} else if(remainder == 12ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + 4ui32));
				functor(contiguous_tags<tag_type>(full_units + 8ui32));
			} else if(remainder > 8ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + 4ui32));
				functor(partial_contiguous_tags<tag_type>(full_units + 8ui32, remainder - 8ui32));
			} else if(remainder == 8ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(contiguous_tags<tag_type>(full_units + 4ui32));
			} else if(remainder > 4ui32) {
				functor(contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + 4ui32, remainder - 4ui32));
			} else if(remainder == 4ui32) {
				functor(contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel_unaligned(uint32_t start, uint32_t count, F functor) {
		const uint32_t full_units = count & ~15ui32;
		const uint32_t remainder = count - full_units;
		concurrency::parallel_for(start, full_units, 16ui32, [&functor](uint32_t offset) {
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
			if(remainder > 8ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + 8ui32, remainder - 8ui32));
			} else if(remainder == 8ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		} else if constexpr(vector_size == 4) {
			if(remainder > 12ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 4ui32));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 8ui32));
				functor(partial_contiguous_tags<tag_type>(full_units + 12ui32, remainder - 12ui32));
			} else if(remainder == 12ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 4ui32));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 8ui32));
			} else if(remainder > 8ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 4ui32));
				functor(partial_contiguous_tags<tag_type>(full_units + 8ui32, remainder - 8ui32));
			} else if(remainder == 8ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(unaligned_contiguous_tags<tag_type>(full_units + 4ui32));
			} else if(remainder > 4ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
				functor(partial_contiguous_tags<tag_type>(full_units + 4ui32, remainder - 4ui32));
			} else if(remainder == 4ui32) {
				functor(unaligned_contiguous_tags<tag_type>(full_units));
			} else if(remainder != 0) {
				functor(partial_contiguous_tags<tag_type>(full_units, remainder));
			}
		}
	}

	template<typename tag_type, typename F>
	RELEASE_INLINE void execute_parallel_exact(uint32_t count, F functor) {
		execute_parallel_exact<tag_type>(0, count, functor);
	}
#endif

	struct serial_exact {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			execute_serial<tag_type>(count, functor);
		}
	};
	struct serial_unaligned {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			execute_serial_unaligned<tag_type>(count, functor);
		}
	};
	struct serial {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			assert(count % ve::vector_size == 0);
			execute_serial_fast<tag_type>(count, functor);
		}
	};

#ifndef VE_NO_TBB
	struct par {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			assert(count % ve::vector_size == 0);
			execute_parallel<tag_type>(count, functor);
		}
	};
	struct par_exact {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			execute_parallel_exact<tag_type>(count, functor);
		}
	};
	struct par_unaligned {
		template<typename tag_type, typename F>
		RELEASE_INLINE static void execute(uint32_t count, F functor) {
			execute_parallel_unaligned<tag_type>(count, functor);
		}
	};
#endif

	constexpr inline uint32_t to_vector_size(uint32_t i) {
		return (i + (ve::vector_size - 1ui32)) & ~(ve::vector_size - 1ui32);
	}


	namespace ve_impl {
		struct rescale_operator {
			float* const vector;
			float const scale;

			rescale_operator(float* v, float s) : vector(v), scale(s) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, vector, scale * load(executor, vector));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void rescale(uint32_t size, float* vector, float scale_factor, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::rescale_operator(vector, scale_factor));
	}

	namespace ve_impl {
		struct vector_accumulate_operator {
			float* const dest;
			float const* const accumulated;

			vector_accumulate_operator(float* d, float const* a) : dest(d), accumulated(a) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, load(executor, accumulated) + load(executor, dest));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void accumulate(uint32_t size, float* destination, float const* accumulated, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_accumulate_operator(destination, accumulated));
	}

	namespace ve_impl {
		struct vector_subtract_operator {
			float* const dest;
			float const* const subtracted;

			vector_subtract_operator(float* d, float const* a) : dest(d), subtracted(a) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, load(executor, dest) - load(executor, subtracted));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void subtract(uint32_t size, float* destination, float const* subtracted, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_subtract_operator(destination, subtracted));
	}

	namespace ve_impl {
	   struct vector_copy_operator {
		   float* const dest;
		   float const* const a;

		   vector_copy_operator(float* d, float const* a) : dest(d), a(a) {};

		   template<typename T>
		   RELEASE_INLINE void operator()(T executor) {
			   store(executor, dest, load(executor, a));
		   }
	   };
	}

	template<typename policy = serial>
	RELEASE_INLINE void copy(uint32_t size, float* destination, float const* source, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_copy_operator(destination, source));
	}

	namespace ve_impl {
		struct vector_accumulate_scaled_operator {
			float* const dest;
			float const* const accumulated;
			float const scale;

			vector_accumulate_scaled_operator(float* d, float const* a, float s) : dest(d), accumulated(a), scale(s) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, ve::multiply_and_add(scale, load(executor, accumulated), load(executor, dest)));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void accumulate_scaled(uint32_t size, float* destination, float const* accumulated, float scale, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_accumulate_scaled_operator(destination, accumulated, scale));
	}

	namespace ve_impl {
		struct vector_accumulate_ui8_scaled_operator {
			float* const dest;
			uint8_t const* const accumulated;
			float const scale;

			vector_accumulate_ui8_scaled_operator(float* d, uint8_t const* a, float s) : dest(d), accumulated(a), scale(s) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, ve::multiply_and_add(scale, to_float(load(executor, accumulated)), load(executor, dest)));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void accumulate_ui8_scaled(uint32_t size, float* destination, uint8_t const* accumulated, float scale, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_accumulate_ui8_scaled_operator(destination, accumulated, scale));
	}

	namespace ve_impl {
		struct vector_accumulate_product_operator {
			float* const dest;
			float const* const a;
			float const* const b;

			vector_accumulate_product_operator(float* d, float const* va, float const* vb) : dest(d), a(va), b(vb) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, ve::multiply_and_add(load(executor, a), load(executor, b), load(executor, dest)));
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void accumulate_product(uint32_t size, float* destination, float const* a, float const* b, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_accumulate_product_operator(destination, a, b));
	}

	namespace ve_impl {
		struct vector_zero_operator {
			float* const dest;
			vector_zero_operator(float* d) : dest(d) {};

			template<typename T>
			RELEASE_INLINE void operator()(T executor) {
				store(executor, dest, 0.0f);
			}
		};
	}

	template<typename policy = serial>
	RELEASE_INLINE void set_zero(uint32_t size, float* destination, policy p = serial()) {
		policy::template execute<int32_t>(size, ve_impl::vector_zero_operator(destination));
	}
}

#undef RELEASE_INLINE
