#pragma once

//
// This file provided as part of the DataContainer project
//

#include <immintrin.h>
#include <cstdint>
#include <cstddef>
#include <new>
#include <cassert>
#include <type_traits>
#include <cstdint>
#include "common_types.hpp"


#ifndef VE_NO_TBB
#ifdef PREFER_ONE_TBB
#include "oneapi/tbb.h"
namespace concurrency = oneapi::tbb;
#else
#include <ppl.h>
#endif
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

#ifdef _MSC_VER 
#define VE_RESTRICT __restrict
#else
#define VE_RESTRICT __restrict__
#endif

#ifdef __AVX512BW__
#include "ve_avx512.hpp"
#else
#ifdef __AVX2__
#include "ve_avx2.hpp"
#else
#ifdef __AVX__
#include "ve_avx.hpp"
#else
#ifdef __SSE4_2__ 
#include "ve_sse.hpp"
#else // Worst case, fallback to SSE3
#include "ve_sse3.hpp"
#endif
#endif
#endif
#endif


namespace ve {

	template<typename T, typename index_type>
	class vectorizable_buffer {
	private:
		T* VE_RESTRICT values = nullptr;
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
			return *this;
		}

		RELEASE_INLINE T* vptr() const noexcept { return values + uint64_t(64) / sizeof(T); }

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
				(std::min)(first_high_chunk + (high_chunk_index + 1) * (low_chunk_size + 1) * chunk_size, uint32_t(total_count))
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

	// value limited to [low, high]
	RELEASE_INLINE fp_vector clamp(fp_vector value, fp_vector low, fp_vector high) {
		return (ve::min)((ve::max)(value, low), high);
	}
	RELEASE_INLINE int_vector clamp(int_vector value, int_vector low, int_vector high) {
		return ve::select(value < low, low, ve::select(value > high, high, value));
	}

	//
	// Elementary and special functions
	//
	// Implemented here because std::sin and friends depend on the C library and do not vectorize.
	//
	// Results are NOT portable. Fused multiply-add is used where the backend has it (see ve::multiply_and_add), so
	// results may differ between backends, and different compilers or floating point flags may give different results
	// even on one backend: this is expected. Within one build of one backend the same input is meant to give the same
	// output in every lane. That assumes the default floating point environment (round to nearest, denormals enabled)
	// and no -ffast-math or similar reassociation.
	//
	// Everything here is plain vector code: no per-lane fallbacks and no branches on the data.
	//
	// Inputs outside a function's domain are invalid: NaN, infinities, poles such as log(0), values such as asin(2),
	// and |x| > 6000 for sin, cos, tan and sincos, or |x| > 2^23 for sind, cosd and tand. They are asserted in debug builds and assumed not to occur in release builds, where the result is
	// unspecified. That applies to every lane, including lanes that are later discarded.
	//
	// The _pi2 functions accept only |x| <= pi / 2 and skip range reduction.
	//

	// coefficients, lowest order first. Generated by a weighted minimax fit, then rounded to float.
	inline constexpr float sin_c[] = { -0x1.555556p-3f, 0x1.111108p-7f, -0x1.a00f12p-13f, 0x1.6cb804p-19f };
	inline constexpr float cos_c[] = { 0x1.555556p-5f, -0x1.6c16b8p-10f, 0x1.a0107ep-16f, -0x1.240b04p-22f };
	inline constexpr float sin_pi2_c[] = { -0x1.555556p-3f, 0x1.11110cp-7f, -0x1.a017b8p-13f, 0x1.716c04p-19f, -0x1.9a0202p-26f };
	inline constexpr float cos_pi2_c[] = { 0x1.9f02f6p-2f, -0x1.3a76a4p-5f, 0x1.5c7a82p-10f, -0x1.94e77ep-16f, 0x1.226f68p-22f, -0x1.1ae344p-29f, 0x1.8132eep-37f };
	inline constexpr float asin_c[] = { 0x1.55554cp-3f, 0x1.33388p-4f, 0x1.6cae5p-5f, 0x1.049628p-5f, 0x1.d8d72ap-7f, 0x1.337084p-5f };
	inline constexpr float atan_c[] = { -0x1.555554p-2f, 0x1.99990cp-3f, -0x1.247d7p-3f, 0x1.c43f6ap-4f, -0x1.5a5c46p-4f, 0x1.81186ep-5f };
	inline constexpr float exp_c[] = { 0x1.0p-1f, 0x1.555554p-3f, 0x1.55547ep-5f, 0x1.11128ep-7f, 0x1.6d9bd6p-10f, 0x1.9efce2p-13f };
	inline constexpr float exp2_c[] = { 0x1.62e43p-1f, 0x1.ebfbep-3f, 0x1.c6b08ap-5f, 0x1.3b29e4p-7f, 0x1.5d8abcp-10f, 0x1.446a2ep-13f, 0x1.fdd276p-17f };
	inline constexpr float exp10_c[] = { 0x1.26bb1cp+1f, 0x1.53524cp+1f, 0x1.047058p+1f, 0x1.2bd698p+0f, 0x1.142c2ap-1f, 0x1.a9bcd4p-3f, 0x1.15d166p-4f };
	inline constexpr float expm1_c[] = { 0x1.555554p-3f, 0x1.5554eap-5f, 0x1.1111dap-7f, 0x1.6d4c74p-10f, 0x1.9fba4ap-13f };
	inline constexpr float log_c[] = { 0x1.55557cp-1f, 0x1.995c48p-2f, 0x1.3229ep-2f };
	inline constexpr float pow_c[] = { 0x1.999998p-2f, 0x1.249386p-2f, 0x1.c65132p-3f, 0x1.8f417ep-3f };
	inline constexpr float sinh_c[] = { 0x1.555556p-3f, 0x1.111138p-7f, 0x1.9ffd76p-13f, 0x1.7a401ap-19f };
	inline constexpr float tanh_c[] = { -0x1.555554p-2f, 0x1.111066p-3f, -0x1.b9ee82p-5f, 0x1.638ac6p-6f, -0x1.0bf208p-7f, 0x1.18d6bp-9f };
	inline constexpr float cbrt_c[] = { 0x1.1b0bbep-1f, 0x1.2c9a18p-1f, -0x1.4dc29ep-3f, 0x1.7a8c78p-6f };
	inline constexpr float erf_c[] = { 0x1.20dd76p+0f, -0x1.812746p-2f, 0x1.ce2eb2p-4f, -0x1.b81e4p-6f, 0x1.556f5ep-8f, -0x1.b0a72ep-11f, 0x1.744992p-14f };
	inline constexpr float erfc_a[] = { 0x1.9531ep-2f, -0x1.e78b36p-3f, 0x1.05e732p-3f, -0x1.013422p-4f, 0x1.d4e0c4p-6f, -0x1.910e2cp-7f, 0x1.44f8fep-8f, -0x1.f37c74p-10f, 0x1.64e9b4p-11f, -0x1.015a7p-12f, 0x1.c4402ep-14f, -0x1.161d9ep-15f };
	inline constexpr float erfc_b[] = { 0x1.836928p-4f, 0x1.1528b6p-1f, -0x1.00f762p-3f, -0x1.81adbap-3f, 0x1.02c4bep-2f, -0x1.1a818cp-4f, -0x1.0934p-3f, 0x1.c5050cp-4f };
	inline constexpr float erfc_c[] = { 0x1.20dddep-1f, -0x1.2e0d64p-13f, -0x1.1df8cp-2f, -0x1.f2fa84p-6f, 0x1.3c2e4ep-1f, -0x1.72b006p-1f, 0x1.153944p-2f };
	inline constexpr float erfinv_a[] = { 0x1.c5bf8ap-1f, 0x1.db29ecp-3f, 0x1.7a7b64p-7f, -0x1.328608p-9f, -0x1.ff6f24p-14f, 0x1.532c9ep-15f, 0x1.8967bap-18f, -0x1.50580cp-19f, 0x1.4e3b48p-22f, -0x1.296726p-26f, 0x1.77fcf4p-32f };
	inline constexpr float erfinv_b[] = { 0x1.6a9942p+1f, 0x1.00ae7cp+0f, 0x1.c080bap-8f, -0x1.c39992p-9f, 0x1.2bafe4p-10f, -0x1.cc2462p-13f, -0x1.4ccf16p-15f, 0x1.bfe5e2p-15f, -0x1.3a23f6p-16f, 0x1.28ed1ep-19f };
	inline constexpr float erfinv_c[] = { 0x1.b79e04p+2f, 0x1.02335ep+0f, -0x1.0cd8a8p-11f, 0x1.6a80eap-18f, 0x1.9b85d2p-18f, -0x1.5ef7b2p-20f, 0x1.34ddb2p-22f, -0x1.905c32p-24f, 0x1.bbf958p-27f };

	inline constexpr int32_t sign_mask = int32_t(0x80000000);
	inline constexpr int32_t abs_mask = 0x7FFFFFFF;
	inline constexpr int32_t inf_bits = 0x7F800000;
	inline constexpr float large_radians = 6000.0f; // beyond this |n| no longer fits the 12 bit pieces of pi / 2
	inline constexpr float large_degrees = 8388608.0f; // beyond this x / 90 and x - 90 * n are no longer exact enough

	RELEASE_INLINE float_vector magnitude(float_vector x) {
		return float_vector(ve::bit_cast_to_float(ve::bit_cast_to_int(x) & int_vector(abs_mask)));
	}
	RELEASE_INLINE int_vector sign_of(float_vector x) {
		return ve::bit_cast_to_int(x) & int_vector(sign_mask);
	}
	RELEASE_INLINE float_vector flip_sign(float_vector x, int_vector sign) {
		return float_vector(ve::bit_cast_to_float(ve::bit_cast_to_int(x) ^ sign));
	}
	RELEASE_INLINE mask_vector is_zero(float_vector x) {
		return (ve::bit_cast_to_int(x) & int_vector(abs_mask)) == int_vector(0);
	}
	RELEASE_INLINE mask_vector is_finite(float_vector x) {
		return (ve::bit_cast_to_int(x) & int_vector(abs_mask)) < int_vector(inf_bits);
	}
	RELEASE_INLINE bool all(mask_vector m) {
		return ve::compress_mask(!m).v == 0;
	}
	RELEASE_INLINE bool all_finite(float_vector x) {
		return all(is_finite(x));
	}
	// x inside [low, high]; false for NaN
	RELEASE_INLINE bool all_within(float_vector x, float low, float high) {
		return all((x >= float_vector(low)) & (x <= float_vector(high)));
	}
	RELEASE_INLINE bool all_positive(float_vector x) {
		return all_finite(x) && all(x > float_vector(0.0f));
	}
	RELEASE_INLINE bool none_zero(float_vector x) {
		return all_finite(x) && all(!is_zero(x));
	}
	constexpr float below_one = 0x1.fffffep-1f;

	template<size_t N>
	RELEASE_INLINE float_vector poly(float_vector x, float const (&c)[N]) {
		float_vector r = float_vector(c[N - 1]);
		for(size_t i = N - 1; i-- > 0;) {
			r = ve::multiply_and_add(r, x, float_vector(c[i]));
		}
		return r;
	}

	// round half away from zero; unlike ve::to_int this does not read the rounding mode
	RELEASE_INLINE int_vector round_to_int(float_vector x) {
		float_vector half = flip_sign(float_vector(0.5f), sign_of(x));
		return ve::truncate_to_int((x + half).v);
	}
	// 2^n for -126 <= n <= 127
	RELEASE_INLINE float_vector pow2(int_vector n) {
		return float_vector(ve::bit_cast_to_float(ve::shift_left<23>(n + int_vector(127))));
	}
	// x * 2^n in two steps, so that subnormal results and n up to about 250 work
	RELEASE_INLINE float_vector scale(float_vector x, int_vector n) {
		int_vector half = ve::shift_right_logical<1>(n + int_vector(512)) - int_vector(256);
		return x * pow2(half) * pow2(n - half);
	}
	// e^x * 2^extra, x must already be clamped
	RELEASE_INLINE float_vector exp_core(float_vector x, int_vector extra) {
		int_vector n = round_to_int(x * float_vector(0x1.715476p+0f));
		float_vector nf = float_vector(ve::to_float(n));
		float_vector r = ve::multiply_and_add(-nf, float_vector(0x1.62e4p-1f), x);
		r = ve::multiply_and_add(-nf, float_vector(0x1.7f7d1cp-20f), r);
		float_vector p = float_vector(1.0f) + (r + r * r * poly(r, exp_c));
		return scale(p, n + extra);
	}

	struct log_parts {
		float_vector e, f, s, z;
	};

	// splits a positive finite x into 2^e * (1 + f), sqrt(1/2) <= 1 + f < sqrt(2), s = f / (2 + f), z = s * s
	RELEASE_INLINE log_parts split_log(float_vector x) {
		mask_vector const subnormal = ve::bit_cast_to_int(x) < int_vector(0x00800000);
		float_vector const normal = ve::select(subnormal, x * float_vector(16777216.0f), x);
		int_vector const ix = ve::bit_cast_to_int(normal) - int_vector(0x3F3504F3) + int_vector(0x40000000);
		int_vector const e = ve::shift_right_logical<23>(ix) - int_vector(128) - ve::select(subnormal, int_vector(24), int_vector(0));
		float_vector const m = float_vector(ve::bit_cast_to_float((ix & int_vector(0x007FFFFF)) + int_vector(0x3F3504F3)));
		float_vector const f = m - float_vector(1.0f);
		float_vector const s = f / (float_vector(2.0f) + f);
		return log_parts{ float_vector(ve::to_float(e)), f, s, s * s };
	}
	// log((1 + s) / (1 - s)) - 2 * s
	RELEASE_INLINE float_vector log_tail(log_parts const& p) {
		return p.s * p.z * poly(p.z, log_c);
	}
	RELEASE_INLINE float_vector log_core(float_vector x) {
		auto p = split_log(x);
		return ve::multiply_and_add(p.e, float_vector(0x1.62e4p-1f), (p.s + p.s) + ve::multiply_and_add(p.e, float_vector(0x1.7f7d1cp-20f), log_tail(p)));
	}
	// log(1 + x) for x > -1
	RELEASE_INLINE float_vector log1p_core(float_vector x) {
		float_vector const u = float_vector(1.0f) + x;
		float_vector const c = (x - (u - float_vector(1.0f))) / u; // the part of x lost when adding 1
		auto p = split_log(u);
		float_vector const lo = ve::multiply_and_add(p.e, float_vector(0x1.7f7d1cp-20f), log_tail(p)) + c;
		float_vector const result = ve::multiply_and_add(p.e, float_vector(0x1.62e4p-1f), (p.s + p.s) + lo);
		return ve::select(magnitude(x) < float_vector(0x1.0p-25f), x, result);
	}

	struct reduced_angle {
		float_vector r;
		int_vector n;
	};

	// x = n * pi / 2 + r, |r| <= pi / 4 (approximately), for |x| <= large_radians
	RELEASE_INLINE reduced_angle reduce_radians(float_vector x) {
		int_vector const n = round_to_int(x * float_vector(0x1.45f306p-1f));
		float_vector const nf = float_vector(ve::to_float(n));
		float_vector r = ve::multiply_and_add(-nf, float_vector(0x1.92p+0f), x);
		r = ve::multiply_and_add(-nf, float_vector(0x1.fb4p-12f), r);
		r = ve::multiply_and_add(-nf, float_vector(0x1.444p-24f), r);
		r = ve::multiply_and_add(-nf, float_vector(0x1.68c234p-39f), r);
		return reduced_angle{ r, n };
	}

	// x = n * 90 + r degrees, then r in radians, for |x| <= large_degrees
	RELEASE_INLINE reduced_angle reduce_degrees(float_vector x) {
		int_vector const n = round_to_int(x / float_vector(90.0f));
		float_vector const r = x - float_vector(ve::to_float(n)) * float_vector(90.0f);
		return reduced_angle{ ve::multiply_and_add(r, float_vector(0x1.294e9cp-33f), r * float_vector(0x1.1df46ap-6f)), n };
	}

	RELEASE_INLINE float_vector sin_kernel(float_vector r, float_vector z) {
		float_vector const a = magnitude(r); // keeps the sign of zero
		return flip_sign(a + a * z * poly(z, sin_c), sign_of(r));
	}
	RELEASE_INLINE float_vector cos_kernel(float_vector z) {
		return float_vector(1.0f) - (float_vector(0.5f) * z - z * z * poly(z, cos_c));
	}
	RELEASE_INLINE float_vector sin_from(reduced_angle a) {
		float_vector const z = a.r * a.r;
		float_vector const value = ve::select((a.n & int_vector(1)) == int_vector(1), cos_kernel(z), sin_kernel(a.r, z));
		return flip_sign(value, ve::shift_left<30>(a.n & int_vector(2)));
	}
	RELEASE_INLINE float_vector cos_from(reduced_angle a) {
		float_vector const z = a.r * a.r;
		float_vector const value = ve::select((a.n & int_vector(1)) == int_vector(1), sin_kernel(a.r, z), cos_kernel(z));
		return flip_sign(value, ve::shift_left<30>((a.n + int_vector(1)) & int_vector(2)));
	}
	RELEASE_INLINE float_vector tan_from(reduced_angle a) {
		float_vector const z = a.r * a.r;
		float_vector const s = sin_kernel(a.r, z);
		float_vector const c = cos_kernel(z);
		return ve::select((a.n & int_vector(1)) == int_vector(1), -c / s, s / c);
	}

	RELEASE_INLINE float_vector sin(float_vector x) { assert(all_within(x, -large_radians, large_radians)); return sin_from(reduce_radians(x)); }
	RELEASE_INLINE float_vector cos(float_vector x) { assert(all_within(x, -large_radians, large_radians)); return cos_from(reduce_radians(x)); }
	RELEASE_INLINE float_vector tan(float_vector x) { assert(all_within(x, -large_radians, large_radians)); return tan_from(reduce_radians(x)); }
	RELEASE_INLINE float_vector sind(float_vector x) { assert(all_within(x, -large_degrees, large_degrees)); return sin_from(reduce_degrees(x)); }
	RELEASE_INLINE float_vector cosd(float_vector x) { assert(all_within(x, -large_degrees, large_degrees)); return cos_from(reduce_degrees(x)); }
	RELEASE_INLINE float_vector tand(float_vector x) {
		assert(all_within(x, -large_degrees, large_degrees));
		auto const a = reduce_degrees(magnitude(x));
		assert(all(!(is_zero(a.r) & ((a.n & int_vector(1)) == int_vector(1))))); // 90 + 180 * k are poles
		return flip_sign(tan_from(a), sign_of(x));
	}

	// For |x| <= pi / 2: no range reduction
	constexpr float pi2_limit = 0x1.921fb6p+0f;
	RELEASE_INLINE float_vector sin_pi2_kernel(float_vector x, float_vector z) {
		float_vector const a = magnitude(x);
		return flip_sign(a + a * z * poly(z, sin_pi2_c), sign_of(x));
	}
	RELEASE_INLINE float_vector cos_pi2_kernel(float_vector x, float_vector z) { // factored, to stay accurate next to the zeros at +-pi / 2
		float_vector const a = magnitude(x);
		float_vector const to_zero = (float_vector(0x1.921fb6p+0f) - a) + float_vector(-0x1.777a5cp-25f);
		return to_zero * (float_vector(0x1.921fb6p+0f) + a) * poly(z, cos_pi2_c);
	}
	RELEASE_INLINE float_vector sin_pi2(float_vector x) { assert(all_within(x, -pi2_limit, pi2_limit)); return sin_pi2_kernel(x, x * x); }
	RELEASE_INLINE float_vector cos_pi2(float_vector x) { assert(all_within(x, -pi2_limit, pi2_limit)); return cos_pi2_kernel(x, x * x); }
	RELEASE_INLINE float_vector tan_pi2(float_vector x) {
		assert(all_within(x, -pi2_limit, pi2_limit));
		float_vector const z = x * x;
		return sin_pi2_kernel(x, z) / cos_pi2_kernel(x, z);
	}

	RELEASE_INLINE float_vector asin_kernel(float_vector a, float_vector z) {
		return a + a * z * poly(z, asin_c);
	}
	RELEASE_INLINE float_vector asin(float_vector x) {
		assert(all_within(x, -1.0f, 1.0f));
		float_vector const a = magnitude(x);
		mask_vector const small = a <= float_vector(0.5f);
		float_vector const z = ve::select(small, a * a, (float_vector(1.0f) - a) * float_vector(0.5f));
		float_vector const y = asin_kernel(ve::select(small, a, ve::sqrt(z)), z);
		float_vector const result = ve::select(small, y, float_vector(0x1.921fb6p+0f) - ((y + y) - float_vector(-0x1.777a5cp-25f)));
		return flip_sign(result, sign_of(x));
	}
	RELEASE_INLINE float_vector acos(float_vector x) {
		assert(all_within(x, -1.0f, 1.0f));
		float_vector const a = magnitude(x);
		mask_vector const small = a <= float_vector(0.5f);
		float_vector const z = ve::select(small, a * a, (float_vector(1.0f) - a) * float_vector(0.5f));
		float_vector const y = asin_kernel(ve::select(small, a, ve::sqrt(z)), z);
		float_vector const centre = float_vector(0x1.921fb6p+0f) - (flip_sign(y, sign_of(x)) - float_vector(-0x1.777a5cp-25f));
		float_vector const outer = ve::select(x < float_vector(0.0f), float_vector(0x1.921fb6p+1f) - ((y + y) - float_vector(-0x1.777a5cp-24f)), y + y);
		return ve::select(small, centre, outer);
	}
	// atan for a >= 0; an infinite a comes from atan2
	RELEASE_INLINE float_vector atan_core(float_vector a) {
		mask_vector const high = a > float_vector(0x1.3504f4p+1f); // tan(3 pi / 8)
		mask_vector const middle = a > float_vector(0x1.a827ap-2f); // tan(pi / 8)
		float_vector const t = ve::select(high, float_vector(-1.0f) / a, ve::select(middle, (a - float_vector(1.0f)) / (a + float_vector(1.0f)), a));
		float_vector const offset = ve::select(high, float_vector(0x1.921fb6p+0f), ve::select(middle, float_vector(0x1.921fb6p-1f), float_vector(0.0f)));
		float_vector const offset_low = ve::select(high, float_vector(-0x1.777a5cp-25f), ve::select(middle, float_vector(-0x1.777a5cp-26f), float_vector(0.0f)));
		float_vector const z = t * t;
		return offset + (t + (t * z * poly(z, atan_c) + offset_low));
	}
	RELEASE_INLINE float_vector atan(float_vector x) {
		assert(all_finite(x));
		return flip_sign(atan_core(magnitude(x)), sign_of(x));
	}
	RELEASE_INLINE float_vector atan2(float_vector y, float_vector x) {
		assert(all_finite(x) && all_finite(y) && all(!(is_zero(x) & is_zero(y))));
		float_vector const a = atan_core(magnitude(y) / magnitude(x));
		float_vector const left = float_vector(0x1.921fb6p+1f) - (a - float_vector(-0x1.777a5cp-24f));
		return flip_sign(ve::select(sign_of(x) != int_vector(0), left, a), sign_of(y));
	}

	RELEASE_INLINE float_vector to_degrees(float_vector r) { return ve::multiply_and_add(r, float_vector(-0x1.670f82p-21f), r * float_vector(0x1.ca5dc2p+5f)); }
	RELEASE_INLINE float_vector asind(float_vector x) { return to_degrees(asin(x)); }
	RELEASE_INLINE float_vector acosd(float_vector x) { return to_degrees(acos(x)); }
	RELEASE_INLINE float_vector atand(float_vector x) { return to_degrees(atan(x)); }
	RELEASE_INLINE float_vector atan2d(float_vector y, float_vector x) { return to_degrees(atan2(y, x)); }

	RELEASE_INLINE float_vector exp(float_vector x) {
		assert(all_finite(x));
		return exp_core(ve::detail::clamp(x, -110.0f, 90.0f), int_vector(0));
	}
	RELEASE_INLINE float_vector exp2(float_vector x) {
		assert(all_finite(x));
		float_vector const c = ve::detail::ve::clamp(x, -160.0f, 130.0f);
		int_vector const n = round_to_int(c);
		float_vector const r = c - float_vector(ve::to_float(n));
		return scale(float_vector(1.0f) + r * poly(r, exp2_c), n);
	}
	RELEASE_INLINE float_vector exp10(float_vector x) {
		assert(all_finite(x));
		float_vector const c = ve::detail::ve::clamp(x, -48.0f, 40.0f);
		int_vector const n = round_to_int(c * float_vector(0x1.a934fp+1f));
		float_vector const nf = float_vector(ve::to_float(n));
		float_vector r = ve::multiply_and_add(-nf, float_vector(0x1.344p-2f), c);
		r = ve::multiply_and_add(-nf, float_vector(0x1.3509f8p-18f), r);
		return scale(float_vector(1.0f) + r * poly(r, exp10_c), n);
	}
	RELEASE_INLINE float_vector expm1_core(float_vector x) {
		float_vector const c = ve::detail::ve::clamp(x, -30.0f, 90.0f);
		int_vector n = round_to_int(c * float_vector(0x1.715476p+0f));
		float_vector const nf = float_vector(ve::to_float(n));
		float_vector r = ve::multiply_and_add(-nf, float_vector(0x1.62e4p-1f), c);
		r = ve::multiply_and_add(-nf, float_vector(0x1.7f7d1cp-20f), r);
		float_vector const p = r + r * r * (float_vector(0.5f) + r * poly(r, expm1_c));
		mask_vector const large = n > int_vector(24);
		int_vector const safe_n = ve::select(large, int_vector(0), n);
		float_vector const t = pow2(safe_n);
		float_vector const moderate = t * p + (t - float_vector(1.0f));
		float_vector const big = scale(p + float_vector(1.0f), n);
		return ve::select(n == int_vector(0), p, ve::select(large, big, moderate));
	}
	RELEASE_INLINE float_vector expm1(float_vector x) {
		assert(all_finite(x));
		return ve::select(magnitude(x) < float_vector(0x1.0p-25f), x, expm1_core(x));
	}

	RELEASE_INLINE float_vector log(float_vector x) {
		assert(all_positive(x));
		return log_core(x);
	}
	RELEASE_INLINE float_vector log2(float_vector x) {
		assert(all_positive(x));
		auto p = split_log(x);
		float_vector const y = (p.s + p.s) + log_tail(p);
		return p.e + ve::multiply_and_add(y, float_vector(0x1.4ae0cp-26f), y * float_vector(0x1.715476p+0f));
	}
	RELEASE_INLINE float_vector log10(float_vector x) {
		assert(all_positive(x));
		auto p = split_log(x);
		float_vector const y = (p.s + p.s) + log_tail(p);
		return ve::multiply_and_add(p.e, float_vector(0x1.344p-2f), y * float_vector(0x1.bcb7b2p-2f) + p.e * float_vector(0x1.3509f8p-18f));
	}
	RELEASE_INLINE float_vector log1p(float_vector x) {
		assert(all_finite(x) && all(x > float_vector(-1.0f)));
		return log1p_core(x);
	}
	RELEASE_INLINE float_vector logb(float_vector x) {
		assert(none_zero(x));
		float_vector const a = magnitude(x);
		mask_vector const subnormal = ve::bit_cast_to_int(a) < int_vector(0x00800000);
		float_vector const normal = ve::select(subnormal, a * float_vector(16777216.0f), a);
		return float_vector(ve::to_float(ve::shift_right_logical<23>(ve::bit_cast_to_int(normal)) - int_vector(127) - ve::select(subnormal, int_vector(24), int_vector(0))));
	}

	RELEASE_INLINE float_vector sinh(float_vector x) {
		assert(all_finite(x));
		float_vector const a = magnitude(x);
		float_vector const z = a * a;
		float_vector const small = a + a * z * poly(z, sinh_c);
		float_vector const h = exp_core(ve::detail::ve::clamp(a, 0.0f, 90.0f), int_vector(-1)); // e^a / 2
		float_vector const large = h - float_vector(0.25f) / h;
		return flip_sign(ve::select(a <= float_vector(1.0f), small, large), sign_of(x));
	}
	RELEASE_INLINE float_vector cosh(float_vector x) {
		assert(all_finite(x));
		float_vector const h = exp_core(ve::detail::ve::clamp(magnitude(x), 0.0f, 90.0f), int_vector(-1));
		return h + float_vector(0.25f) / h;
	}
	RELEASE_INLINE float_vector tanh(float_vector x) {
		assert(all_finite(x));
		float_vector const a = magnitude(x);
		float_vector const z = a * a;
		float_vector const small = a + a * z * poly(z, tanh_c);
		float_vector const e = expm1_core(ve::detail::ve::clamp(a + a, 0.0f, 40.0f));
		float_vector const large = e / (e + float_vector(2.0f));
		return flip_sign(ve::select(a < float_vector(0.625f), small, large), sign_of(x));
	}
	RELEASE_INLINE float_vector asinh(float_vector x) {
		assert(all_finite(x));
		float_vector const a = magnitude(x);
		float_vector const z = a * a;
		float_vector const moderate = log1p_core(a + z / (float_vector(1.0f) + ve::sqrt(z + float_vector(1.0f))));
		float_vector const huge = log_core(a) + float_vector(0x1.62e43p-1f);
		return flip_sign(ve::select(a >= float_vector(8192.0f), huge, moderate), sign_of(x));
	}
	RELEASE_INLINE float_vector acosh(float_vector x) {
		assert(all_finite(x) && all(x >= float_vector(1.0f)));
		float_vector const t = x - float_vector(1.0f);
		float_vector const moderate = log1p_core(t + ve::sqrt((t + t) + t * t));
		float_vector const huge = log_core(x) + float_vector(0x1.62e43p-1f);
		return ve::select(x >= float_vector(8192.0f), huge, moderate);
	}
	RELEASE_INLINE float_vector atanh(float_vector x) {
		assert(all_within(x, -below_one, below_one));
		float_vector const a = magnitude(x);
		return flip_sign(float_vector(0.5f) * log1p_core((a + a) / (float_vector(1.0f) - a)), sign_of(x));
	}

	RELEASE_INLINE float_vector cbrt(float_vector x) {
		assert(all_finite(x));
		float_vector const a = magnitude(x);
		mask_vector const subnormal = ve::bit_cast_to_int(a) < int_vector(0x00800000);
		float_vector const normal = ve::select(subnormal, a * float_vector(16777216.0f), a);
		int_vector const e = ve::shift_right_logical<23>(ve::bit_cast_to_int(normal)) - int_vector(127) - ve::select(subnormal, int_vector(24), int_vector(0));
		float_vector const m = float_vector(ve::bit_cast_to_float((ve::bit_cast_to_int(normal) & int_vector(0x007FFFFF)) | int_vector(0x3F800000)));
		// floor(e / 3), kept positive while dividing because truncation rounds towards zero
		int_vector const q = ve::truncate_to_int(((float_vector(ve::to_float(e + int_vector(300)))) / float_vector(3.0f)).v) - int_vector(100);
		int_vector const rem = e - q * int_vector(3);
		mask_vector const r1 = rem == int_vector(1);
		mask_vector const r2 = rem == int_vector(2);
		float_vector const scaled = ve::select(r2, m * float_vector(4.0f), ve::select(r1, m * float_vector(2.0f), m));
		float_vector y = poly(m, cbrt_c) * ve::select(r2, float_vector(0x1.965feap+0f), ve::select(r1, float_vector(0x1.428a3p+0f), float_vector(1.0f)));
		float_vector const y3 = y * y * y;
		y = y * (y3 + scaled + scaled) / (y3 + y3 + scaled); // Halley
		return ve::select(is_zero(x), x, flip_sign(scale(y, q), sign_of(x)));
	}
	RELEASE_INLINE float_vector invcbrt(float_vector x) {
		assert(none_zero(x));
		return float_vector(1.0f) / cbrt(x);
	}
	RELEASE_INLINE float_vector hypot(float_vector x, float_vector y) {
		assert(all_finite(x) && all_finite(y));
		float_vector const ax = magnitude(x);
		float_vector const ay = magnitude(y);
		float_vector const big = float_vector((ve::max)(ax.v, ay.v));
		float_vector const little = float_vector((ve::min)(ax.v, ay.v));
		int_vector k = ve::shift_right_logical<23>(ve::bit_cast_to_int(big)) - int_vector(127);
		k = ve::select(k < int_vector(-126), int_vector(-126), ve::select(k > int_vector(126), int_vector(126), k));
		float_vector const down = pow2(-k);
		float_vector const a = big * down;
		float_vector const b = little * down;
		return ve::sqrt(a * a + b * b) * pow2(k);
	}

	// e^(-k * x * x) for x >= 0, k = 1 or 0.5. The square is split so that it is exact
	RELEASE_INLINE float_vector exp_minus_square(float_vector x, float_vector k) {
		float_vector const h = float_vector(ve::bit_cast_to_float(ve::bit_cast_to_int(x) & int_vector(int32_t(0xFFFFF000))));
		float_vector const first = ve::detail::ve::clamp(-(k * h * h), -110.0f, 90.0f);
		float_vector const second = ve::detail::ve::clamp(-(k * (x - h) * (x + h)), -110.0f, 90.0f);
		return exp_core(first, int_vector(0)) * exp_core(second, int_vector(0));
	}
	// erfc(t) for t >= 0.25, given e^(-t * t) = e^(-k * a * a)
	RELEASE_INLINE float_vector erfc_core(float_vector t, float_vector a, float_vector k) {
		float_vector const u = float_vector(1.0f) / float_vector((ve::min)(t.v, fp_vector(14.0f)));
		float_vector const near_part = poly(t - float_vector(1.125f), erfc_a);
		float_vector const middle_part = poly(u - float_vector(0.17f), erfc_b);
		float_vector const far_part = u * poly(u, erfc_c);
		float_vector const r = ve::select(t < float_vector(2.0f), near_part, ve::select(t < float_vector(4.0f), middle_part, far_part));
		return exp_minus_square(float_vector((ve::min)(a.v, fp_vector(20.0f))), k) * r;
	}
	RELEASE_INLINE float_vector erf(float_vector x) {
		assert(all_finite(x));
		float_vector const a = magnitude(x);
		float_vector const z = a * a;
		float_vector const low = a * poly(z, erf_c);
		float_vector const high = float_vector(1.0f) - erfc_core(a, a, float_vector(1.0f));
		return flip_sign(ve::select(a < float_vector(0.84375f), low, high), sign_of(x));
	}
	// erfc(t), a and k as for erfc_core
	RELEASE_INLINE float_vector erfc_signed(float_vector t, float_vector a, float_vector k) {
		float_vector const at = magnitude(t);
		float_vector const z = t * t;
		float_vector const low = float_vector(1.0f) - t * poly(z, erf_c);
		float_vector const core = erfc_core(at, a, k);
		return ve::select(at < float_vector(0.25f), low, ve::select(t < float_vector(0.0f), float_vector(2.0f) - core, core));
	}
	RELEASE_INLINE float_vector erfc(float_vector x) {
		assert(all_finite(x));
		return erfc_signed(x, magnitude(x), float_vector(1.0f));
	}
	RELEASE_INLINE float_vector cdfnorm(float_vector x) {
		assert(all_finite(x));
		float_vector const t = -x * float_vector(0x1.6a09e6p-1f);
		return float_vector(0.5f) * erfc_signed(t, magnitude(x), float_vector(0.5f));
	}
	// erfinv given t and w = -log((1 - t) * (1 + t)), where (1 - t) * (1 + t) was computed without cancellation
	RELEASE_INLINE float_vector erfinv_core(float_vector t, float_vector w) {
		auto const s = ve::sqrt(w);
		auto const centre = t * poly(w, erfinv_a);
		auto const shoulder = flip_sign(poly(s - float_vector(3.0f), erfinv_b), sign_of(t));
		auto const tail = flip_sign(poly(s - float_vector(7.0f), erfinv_c), sign_of(t));
		return ve::select(w < float_vector(5.0f), centre, ve::select(s < float_vector(4.1f), shoulder, tail));
	}
	RELEASE_INLINE float_vector erfinv(float_vector x) {
		assert(all_within(x, -below_one, below_one));
		auto const a = magnitude(x);
		return erfinv_core(x, -log_core((float_vector(1.0f) - a) * (float_vector(1.0f) + a)));
	}
	RELEASE_INLINE float_vector erfcinv(float_vector x) {
		assert(all_finite(x) && all((x > float_vector(0.0f)) & (x < float_vector(2.0f))));
		auto const c = ve::select(x > float_vector(1.0f), float_vector(2.0f) - x, x);
		return erfinv_core(float_vector(1.0f) - x, -log_core(c * (float_vector(2.0f) - c)));
	}
	RELEASE_INLINE float_vector cdfnorminv(float_vector x) {
		assert(all_finite(x) && all((x > float_vector(0.0f)) & (x < float_vector(1.0f))));
		return -(erfcinv(x + x) * float_vector(0x1.6a09e6p+0f));
	}

	// x + y with the rounding error, and x * y with the rounding error
	struct two_float {
		float_vector hi, lo;
	};
	RELEASE_INLINE two_float two_sum(float_vector a, float_vector b) {
		auto const s = a + b;
		auto const b2 = s - a;
		return two_float{ s, (a - (s - b2)) + (b - b2) };
	}
#if defined(__AVX2__) || defined(__AVX512BW__)
	RELEASE_INLINE two_float two_prod(float_vector a, float_vector b) { // these backends have FMA, which gives the error directly
		fp_vector const p = a.v * b.v;
		return two_float{ float_vector(p), float_vector(ve::multiply_and_subtract(a.v, b.v, p)) };
	}
#else
	RELEASE_INLINE two_float two_prod(float_vector a, float_vector b) { // Veltkamp splitting, only sound where nothing can fuse it
		auto const ca = a * float_vector(4097.0f);
		auto const ah = ca - (ca - a);
		auto const al = a - ah;
		auto const cb = b * float_vector(4097.0f);
		auto const bh = cb - (cb - b);
		auto const bl = b - bh;
		auto const p = a * b;
		return two_float{ p, ((ah * bh - p) + ah * bl + al * bh) + al * bl };
	}
#endif

	// log2(x) for positive finite x to about 36 ve::bit_cast_to_int
	RELEASE_INLINE two_float log2_extended(float_vector x) {
		auto p = split_log(x);
		auto const t = float_vector(2.0f) + p.f;
		auto const t_low = (float_vector(2.0f) - t) + p.f;
		auto const s = p.s;
		auto const st = two_prod(s, t);
		auto const s_low = (((p.f - st.hi) - st.lo) - s * t_low) / t;
		auto const sq = two_prod(s, s);
		auto const cube = two_prod(sq.hi, s);
		auto const third = two_prod(cube.hi, float_vector(0x1.555556p-1f));
		auto const third_low = third.lo + (cube.lo + sq.lo * s) * float_vector(0x1.555556p-1f) + cube.hi * float_vector(-0x1.555556p-26f);
		auto const rest = s * sq.hi * sq.hi * poly(sq.hi, pow_c);
		auto const sum = two_sum(s + s, third.hi);
		auto const low = sum.lo + (s_low + s_low) + third_low + rest;
		auto const normal = two_sum(sum.hi, low);
		auto const scaled = two_prod(normal.hi, float_vector(0x1.715476p+0f));
		auto const scaled_low = scaled.lo + normal.lo * float_vector(0x1.715476p+0f) + normal.hi * float_vector(0x1.4ae0cp-26f);
		auto const total = two_sum(p.e, scaled.hi);
		return two_float{ total.hi, total.lo + scaled_low };
	}

	RELEASE_INLINE float_vector pow(float_vector x, float_vector y) {
		auto const ax = magnitude(x);
		auto const ay = magnitude(y);
		auto const yc = ve::detail::ve::clamp(y, -0x1.0p+60f, 0x1.0p+60f);

		auto const y_large = ay >= float_vector(16777216.0f); // all such values are even
		auto const yi = ve::truncate_to_int(ve::select(y_large, float_vector(0.0f), y).v);
		auto const y_integer = y_large | (float_vector(ve::to_float(yi)) == y);
		auto const y_odd = (!y_large) & y_integer & ((yi & int_vector(1)) == int_vector(1));

		// a negative base needs a whole exponent, and zero a non negative one
		assert(all_finite(x) && all_finite(y));
		assert(all(y_integer | (x >= float_vector(0.0f))));
		assert(all(!is_zero(x) | (y >= float_vector(0.0f))));

		auto const l = log2_extended(ve::select(is_zero(x), float_vector(1.0f), ax));
		auto const w0 = two_prod(yc, l.hi);
		auto const w = two_sum(w0.hi, w0.lo + yc * l.lo);
		auto const wh = ve::detail::ve::clamp(w.hi, -200.0f, 200.0f);
		auto const n = round_to_int(wh);
		auto const r = ve::detail::ve::clamp((wh - float_vector(ve::to_float(n))) + w.lo, -1.0f, 1.0f); // limited for exponents that saturated above
		auto result = scale(float_vector(1.0f) + r * poly(r, exp2_c), n);

		result = ve::select(is_zero(x), float_vector(0.0f), result);
		result = flip_sign(result, ve::select(y_odd, sign_of(x), int_vector(0)));
		return ve::select(is_zero(y) | (x == float_vector(1.0f)), float_vector(1.0f), result);
	}

	struct sincos_result {
		fp_vector sine;
		fp_vector cosine;
	};
	RELEASE_INLINE sincos_result sincos(fp_vector x) {
		float_vector const v(x);
		assert(detail::all_within(v, -detail::large_radians, detail::large_radians));
		auto const a = detail::reduce_radians(v);
		return sincos_result{ detail::sin_from(a).v, detail::cos_from(a).v };
	}
	RELEASE_INLINE sincos_result sincos_pi2(fp_vector x) {
		float_vector const v(x);
		assert(detail::all_within(v, -detail::pi2_limit, detail::pi2_limit));
		auto const z = v * v;
		return sincos_result{ detail::sin_pi2_kernel(v, z).v, detail::cos_pi2_kernel(v, z).v };
	}
}

#undef RELEASE_INLINE
#undef VE_RESTRICT
