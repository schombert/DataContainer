# The ve SIMD wrapper classes and functions

## Overview

The ve library provides a wrapper over SIMD data types and instructions for the x86_64 platform. The wrapper has two main features. First, it allows you to write an operation over array(s) of values that will automatically be compiled to one of the SSE4.2, AVX, or AVX2 instruction sets without making any alterations to the source code. This allows you to easily compile the same program once for each instruction set you want to target. Secondly, it provides support for strongly typed indexes (refereed to as "tags" in the source code for the sake of brevity). A strongly typed index provides the same type safety for looking up values / objects in an array by index that a pointer provides for normal data access. Supporting these strongly typed indexes is the real reason that the ve library exists, as there are a number of quality libraries that already support the first feature.

## Limitations

- There is no support for 32 bit compilation. Only x86_64 targets are supported.
- There is currently no support for AVX512 instructions. Support will be added if/when I get a machine supporting that instruction set to test on.
- Currently the instructions for operating on packed 8 byte data types (`double` and `int64_t`) are not supported, as my use case simply didn't require them. If you need support for these types, let me know (and explain why).
- When no instruction set is selected, the default target is SSE4.2 (technically SSE4.1, but I reserve the right to use `PCMPGTQ` someday). This means that there may be a tiny number of x86_64 machines that are not supported.

## Getting started

Before you get started, you first need to decide if you want the built-in parallelism support that ve provides. By default ve includes `ppl` (Microsoft's parallel patterns library) in order to provide the ability to divide an operation into chunks and dispatch them to a thread pool. If you don't like the Microsoft version of the library (or are building on Linux) it is simple to edit this include to point to a copy of Intel's `oneTBB`, which provides the same functionality (and which `ppl` is essentially an implementation of). Alternatively, if you don't want the built-in parallelism, simply add `#define VE_NO_TBB` prior to including `ve.hpp` (and also before including any generated data container headers), which will allow you to use ve without either `ppl` or `oneTBB`.

Second, always use ve by including `ve.hpp`. That file will in turn include one of `ve_avx2.hpp`, `ve_avx.hpp`, or `ve_sse.hpp` depending on the instruction set the compiler is targeting.

Finally, using ve requires you to know how to change the instruction set that the compiler is targeting. In Visual Studio this can be done as follows: for the project in question go to `Properties > C/C++ > Code Generation` and then next to `Enable Enhanced Instruction Set` choose either `Not set` (for SSE4.2), `Advanced Vector Extensions` (for AVX), or `Advanced Vector Extensions 2` (for AVX2). Make sure that you set these properties for both release and debug configurations, and for the x64 build configuration. For gcc and clang setting the target instruction set can be done by the command line parameters `-msse4.2`, `-mavx`, and `-mavx2`.

## Types

### SIMD vector wrappers

#### `ve::fp_vector`

`ve::fp_vector` holds a packed SIMD vector of 32 bit floating point values (4 values for SSE4.2 and 8 for AVX and AVX2. This type serves primarily as an intermediate value for operations: as an operation progresses floating point values are loaded into `ve::fp_vector`s (see the description of [loading and storing](#load-and-store-functions) below). The `ve::fp_vector`s can then be manipulated by various mathematical operations, comparisons, and selection statements (see [mathematical operations](#mathematical-operations) below), and can then finally be stored back into some array.

##### `ve::fp_vector` constructors:

- `fp_vector()` creates a vector with each internal value set to 0.0f,
- `fp_vector(float v)` creates a vector with each internal value set to v, and
- `fp_vector(float a, float b, float c, ...)` creates a vector with the value in lane 0 equal to a, the value in lane 1 equal to b, and so on. Since the number of parameters depends on the instruction set being targeted, it is probably best to avoid this constructor in truly generic code.

##### `ve::fp_vector` member functions:

- `float operator[](uint32_t i)` returns the floating point value stored in slot `i`, starting from zero. Attempting to access a slot that the vector doesn't have (4 and greater for SSE4.2, 8 and greater for AVX and AVX2) is undefined behavior.
- `void set(uint32_t i, float v)` sets the floating point value in slot `i` to v. As above, attempting to access a nonexistent slot is undefined behavior.
- `float reduce()` not a particularly useful function, but uses a neat code snippet I found (source: Peter Cordes) to sum up the floating point values contained in the vector.

##### `ve::fp_vector` other:

- `wrapped_value` a type alias that resolves to `float`. Useful for meta-programming.
- `value` the wrapped SIMD type itself. The exact type of this member depends on the target instruction set.

#### `ve::int_vector`

`ve::int_vector` holds a packed SIMD vector of signed 32 bit integer values (4 values for SSE4.2 and 8 for AVX and AVX2. This is basically the same as `ve::fp_vector` but for integers, so I won't blame you if you skip to the next type. Two significant differences are that `ve::int_vector` does not come with a `reduce` function, and when targeting AVX, `ve::int_vector` is implemented as a pair of wrapped SIMD types due to missing support in AVX for some integer operations.

##### `ve::int_vector` constructors:

- `int_vector()` creates a vector with each internal value set to 0,
- `int_vector(int32_t v)` creates a vector with each internal value set to v, and
- `int_vector(int32_t a, int32_t b, int32_t c, ...)` creates a vector with the value in lane 0 equal to a, the value in lane 1 equal to b, and so on. Since the number of parameters depends on the instruction set being targeted, it is probably best to avoid this constructor in truly generic code.

##### `ve::int_vector` member functions:

- `int32_t operator[](uint32_t i)` returns the integer value stored in slot `i`, starting from zero. Attempting to access a slot that the vector doesn't have (4 and greater for SSE4.2, 8 and greater for AVX and AVX2) is undefined behavior.
- `void set(uint32_t i, int32_t v)` sets the integer value in slot `i` to v. As above, attempting to access a nonexistent slot is undefined behavior.

##### `ve::int_vector` other:

- `wrapped_value` a type alias that resolves to `int32_t`. Useful for meta-programming.
- `value` (or `value_low` and `value_high`) the wrapped SIMD type itself. The exact type of this member depends on the target instruction set.

#### `ve::mask_vector`

A `ve::mask_vector` can be thought of as like a `ve::fp_vector` or `ve::int_vector` that holds either 4 or 8 boolean values (internally their representation is governed by the SIMD instruction set). `ve::mask_vector`s may be created either from loading packed bits from an array or as the result of a comparison between two vectors. `ve::mask_vector`s can be used to selectively combine two vectors into a single result (see [selection](#selection) below) and they can be used to mask load and store operations (see [loading and storing](#load-and-store-functions) below) in order to avoid reading and writing from undesired or invalid addresses.

##### `ve::mask_vector` constructors:

- `mask_vector()` creates a vector with each internal value set to false,
- `mask_vector(bool v)` creates a vector with each internal value set to v,
- `mask_vector(vbitfield_type b)` creates a vector populated by the packed boolean values inside the `ve::vbitfield_type` (see `ve::vbitfield_type` below), and
- `mask_vector(bool a, bool b, bool c, ...)` creates a vector with the value in lane 0 equal to a, the value in lane 1 equal to b, and so on. Since the number of parameters depends on the instruction set being targeted, it is probably best to avoid this constructor in truly generic code.

##### `ve::mask_vector` member functions:

- `bool operator[](uint32_t i)` returns the boolean value stored in slot `i`, starting from zero. Attempting to access a slot that the vector doesn't have (4 and greater for SSE4.2, 8 and greater for AVX and AVX2) is undefined behavior.
- `void set(uint32_t i, bool v)` sets the boolean value in slot `i` to v. As above, attempting to access a nonexistent slot is undefined behavior.

##### `ve::mask_vector` other:

- `wrapped_value` a type alias that resolves to `bool`. Useful for meta-programming.
- `value` the wrapped SIMD type itself. The exact type of this member depends on the target instruction set.

#### `template<typename tag_type> ve::tagged_vector`

Internally a `ve::tagged_vector` is just a `ve::int_vector`, except that the integers stored inside it represent indexes into some particular array. Any type put into the template must satisfy the following four requirements: 1) It must contain a type alias named `value_base_t` as a member that resolves to the underlying integer type of the index, which is at most 4 bytes. 2) It must have an `index()` function that returns the stored index as an `int32_t` value (these returned values should be 0-based indexes as is customary for C++). 3) It must contain a type alias named `zero_is_null_t` that resolves to `std::true_type` if an invalid index is represented with the numerical value 0, and resolves to `std::false_type` if an invalid index is represented with the numerical value -1. 4) It must have a public member variable named `value` that stores the internal numerical representation of the index.

Internally the values stored in a `ve::tagged_vector` represent the invalid indexes with the numerical value -1. If this is not how the `tag_type` represents an invalid index, then when values are loaded from a source into a `ve::tagged_vector` they will be adjusted accordingly.

##### `ve::tagged_vector` constructors:

- `tagged_vector()` creates a vector with each internal index set to the invalid index representation,
- `tagged_vector(tag_type v)` creates a vector with each internal index set to v, and
- `tagged_vector(tag_type a, tag_type b, tag_type c, ...)` creates a vector with the index in lane 0 equal to a, the index in lane 1 equal to b, and so on. Since the number of parameters depends on the instruction set being targeted, it is probably best to avoid this constructor in truly generic code.

##### `ve::tagged_vector` member functions:

- `tag_type operator[](uint32_t i)` returns the index value stored in slot `i`, starting from zero. Attempting to access a slot that the vector doesn't have (4 and greater for SSE4.2, 8 and greater for AVX and AVX2) is undefined behavior.
- `void set(uint32_t i, tag_type v)` sets the index value in slot `i` to v. As above, attempting to access a nonexistent slot is undefined behavior.

##### `ve::tagged_vector` other:

- `wrapped_value` a type alias that resolves to `tag_type`. Useful for meta-programming.
- `value` the wrapped SIMD type itself. The exact type of this member depends on the target instruction set.

#### `ve::tagged_vector<int32_t>`

This specialization is for when you need to deal with indexes that are not contained in a strongly-typed wrapper. It functions as the standard `ve::tagged_vector` except that operates on plain `int32_t`s instead of a special index type. These `int32_t`s are treated as ordinary, 0-based C++ indexes, except that -1 is used to represent an invalid index.

### Bitfields

#### `dcon::bitfield_type`

This type is defined in `common_types.hpp`. An array of `dcon::bitfield_type` values represents a sequence of boolean values packed into bits. Helper functions `dcon::bit_vector_set` and `dcon::bit_vector_test` (see [Utility functions](#utility-functions) below) are provided to help test and set the nth bit of arbitrarily long packed-bit arrays. When packed bits are loaded from such an array with a load function (see [loading and storing](#load-and-store-functions) below) they will loaded as either 4 or 8 bits into a `ve::vbitfield_type`.

#### `ve::vbitfield_type`

This type contains an appropriate number of bits loaded from a packed array of bits. It can be converted implicitly into a `ve::mask_vector` for use in SIMD operations. It contains a type alias `storage` that resolves to the type that is used to store the bits. Currently this is always `uint8_t`, but if AVX512 support is ever added, it will resolve to `uint16_t` there. The bits themselves can be accessed through the member variable `v`;

### Contiguous indexes

##### `template<typename tag_type> ve::contiguous_tags`

This type marks a position in an array of values. If you write a SIMD operation, the main bulk of the work will be driven by the execution function (see [executing an operation](#executing-an-operation) below) repeatedly calling the `operator()(auto index)` function you have written with this type (or a `ve::unaligned_contiguous_tags`, see below). Passing this value to a load function along with an array of values will return a full vector of values from the array at the appropriate position, and passing it to a store function can be used to put values into an array at the appropriate position. In contrast to the `ve::unaligned_contiguous_tags` type described below, loads or stores driven by this type are assumed to be appropriately aligned (on 16 byte boundaries for SSE4.2 and on 32 byte boundaries for AVX and AVX2) and the instructions that benefit from that will be used.

No demands are made of the `tag_type`, which can be an `int32_t` if you are not working with strongly typed indexes.

##### `template<typename tag_type> ve::partial_contiguous_tags`

In many cases, you may want to execute a SIMD operation on arrays of values that are not a multiple of the vector size in length. If there are fewer than a full vector's worth of items left at the end, the execution function will call your `operator()(auto index)` function with a`ve::partial_contiguous_tags` that contains both the position of those last values and the number of remaining values, stored in the `subcount` member variable. Any loads or stores driven by a `ve::partial_contiguous_tags` will only read or write `subcount` many items, not a full vector's worth.

##### `template<typename tag_type> ve::unaligned_contiguous_tags`

Identical to a `ve::contiguous_tags`, except that it is generated when loads and stores can not be guaranteed to be appropriately aligned.

### Vectorizable buffer

`template<typename T, typename index_type> ve::vectorizable_buffer` is a convenience type intended as semi-temporary storage. Type `T` should be a type of 4 bytes or less that load and store operations can work on (such as `float`, `int32_t`, or a strongly typed index). `index_type` can be either a strongly typed index or an `int32_t`.

#### constructors

- `vectorizable_buffer(uint32_t count)` allocates and default initializes (with `std::uninitialized_value_construct_n`) an array containing at least `count` values of type `T`. This vector begins on a 64 byte boundary and contains enough items to end on a 64 byte boundary as well. It is also preceded by padding so that reads and writes to an invalid index (which resolve as reads and writes to index -1) are safe.
- `vectorizable_buffer(vectorizable_buffer&& other)` the move constructor. `ve::vectorizable_buffer`s can only be moved and move assigned; they cannot be copied.

#### member functions: getters

- `const& get(index_type i) const noexcept` returns a reference to the value at index `i`
- `T& get(index_type i) noexcept` as above, but mutably
- `value_to_vector_type<T> get(contiguous_tags<index_type> i) const noexcept` loads values into a vector starting at index `i`
- `value_to_vector_type<T> get(unaligned_contiguous_tags<index_type> i) const noexcept` as above, except without any alignment assumptions
- `value_to_vector_type<T> get(partial_contiguous_tags<index_type> i) const noexcept` as above, except only part of the vector is loaded
- `value_to_vector_type<T> get(tagged_vector<index_type> i) const noexcept` a vector filled with indexes is passed as an argument and a vector filled with the values found at those indexes (in the same order) is returned.

(`value_to_vector_type` is described in [Meta-programming utilities](#meta-programming-utilities) below)

There are two items worth nothing about this interface. First, it is an example of how strongly typed indexes can be used to guard against certain errors, as trying to access its contents with an index of the wrong type is simply not possible. Secondly, even though the values contained are appropriately aligned, access via `unaligned_contiguous_tags` is still provided. Accessing properly aligned values with the generic instructions is fine, if perhaps slightly suboptimal. However, if the values contained were not guaranteed to be properly aligned (for example, if they were stored in a `std::vector`) then providing access via `contiguous_tags` would be an error, as it could allow instructions that require aligned values to be called on unaligned values.
		
#### member functions: setters

- `void set(index_type i, T value) noexcept`
- `void set(contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept`
- `void set(unaligned_contiguous_tags<index_type> i, value_to_vector_type<T> values)`
- `void set(partial_contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept`
- `void set(tagged_vector<index_type> i, value_to_vector_type<T> values) noexcept`

These functions operate in essentially the same way as the getters described above, except that they take as parameter either a single value or a vector of values to store. In the case of the `tagged_vector` setter, the values to be stored are each placed at the index contained in the `tagged_vector` (it is undefined behavior if the `tagged_vector` contains duplicate indexes).

## Mathematical operations

### Algebraic operations

The `ve::fp_vector` and `ve::int_vector` types support the standard algebraic operations listed below. Note that if you want to add / subtract / multiply all the values in a vector by a scalar value you can do so by relying on implicit type conversion (e.g. `fp_vector * float` will work out of the box). Also note that the division of one integer vector by another is not supported.

```
fp_vector + fp_vector
fp_vector - fp_vector
fp_vector * fp_vector
fp_vector / fp_vector
-fp_vector
```

```
int_vector + int_vector
int_vector - int_vector
int_vector * int_vector
-int_vector
```

### Fused algebraic operations

- `ve::inverse(fp_vector)` yields a `ve::fp_vector` containing the multiplicative inverse of each value contained in the source vector. Note that while inverse may be a bit faster than division, it is only accurate to about 3 decimal places.
- `ve::sqrt(fp_vector)` yields a `ve::fp_vector` containing the square root of each value contained in the source vector.
- `inverse_sqrt::inverse_sqrt(fp_vector)` yields a `ve::fp_vector` containing the multiplicative inverse of the square root of each value contained in the source vector. As with inverse, this is less accurate than ordinary division by the square root.
- `ve::abs(fp_vector)` yields a `ve::fp_vector` containing the absolute value of each value contained in the source vector.
- `ve::abs(int_vector)` yields a `ve::int_vector` containing the absolute value of each value contained in the source vector.
- `ve::multiply_and_add(fp_vector a, fp_vector b, fp_vector c)` yields a `ve::fp_vector` containing the result of `(a * b) + c`. This will be implemented using a single instruction where possible. 
- `ve::multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c)` yields a `ve::fp_vector` containing the result of `(a * b) - c`. This will be implemented using a single instruction where possible.
- `ve::negate_multiply_and_add(fp_vector a, fp_vector b, fp_vector c)` yields a `ve::fp_vector` containing the result of `-(a * b) + c`. This will be implemented using a single instruction where possible.
- `ve::negate_multiply_and_subtract(fp_vector a, fp_vector b, fp_vector c)` yields a `ve::fp_vector` containing the result of `-(a * b) - c`. This will be implemented using a single instruction where possible.

### Conversions

- `ve::to_float(int_vector)` yields a `ve::fp_vector` containing the values stored in the `ve::int_vector` (for sufficiently large integer values some of the low bits may be lost by this conversion)
- `ve::to_int(fp_vector)` yields a `ve::int_vector` containing the values stored in the `ve::fp_vector` converted to integers
- `ve::floor(fp_vector)` yields a `ve::fp_vector` containing the values stored in the `ve::fp_vector` rounded down to the nearest integer
- `ve::ceil(fp_vector)` yields a `ve::fp_vector` containing the values stored in the `ve::fp_vector` rounded up to the nearest integer
- `ve::compress_mask(mask_vector)` converts a `ve::mask_vector` into a `ve::vbitfield_type` with bits set corresponding to the set mask positions

### Bitwise operations

The bitwise operations listed below allow operate on combine mask_vectors as if they were packed bits.

```
mask_vector & mask_vector
mask_vector | mask_vector
mask_vector ^ mask_vector
~mask_vector
!mask_vector
```

`ve::and_not(mask_vector a, mask_vector b)` computes `a & ~b` using a single instruction where possible. Note that the order of the parameters are reversed compared to the underlying intrinsic.

Bitwise operations for `ve::vbitfield_type` are also provided 

```
vbitfield_type & vbitfield_type
vbitfield_type | vbitfield_type
vbitfield_type ^ vbitfield_type
~vbitfield_type
!vbitfield_type
```

### Comparisons

Comparison operators yield `ve::mask_vector`s with each position set if the comparison between the values stored in the vector parameters would return true.

```
fp_vector < fp_vector
fp_vector > fp_vector
fp_vector <= fp_vector
fp_vector >= fp_vector
fp_vector == fp_vector
fp_vector != fp_vector
```

```
int_vector < int_vector
int_vector > int_vector
int_vector <= int_vector
int_vector >= int_vector
int_vector == int_vector
int_vector != int_vector
```

```
mask_vector == mask_vector
mask_vector != mask_vector
```

```
tagged_vector<tag_type> == tagged_vector<tag_type>
tagged_vector<tag_type> != tagged_vector<tag_type>
```

```
vbitfield_type == vbitfield_type
vbitfield_type != vbitfield_type
```

Note that the `ve::vbitfield_type` equality and inequality operators produce a packed sequence of bits stored in a `ve::vbitfield_type` as a result, not a boolean value.

- `ve::is_valid_index(tagged_vector<tag_type> a)` a convenience function equivalent to `a != tagged_vector<tag_type>()`
- `ve::is_invalid(tagged_vector<tag_type> a)` a convenience function equivalent to `a == tagged_vector<tag_type>()`

### Selection

Selection operations provide the ability to selectively combine values from two vectors into a single vector result. Often this is used to implement what amounts to `condition ? a : b`. However, unlike a C++ conditional, both results of the selection operation must be evaluated.

- `ve::min(fp_vector a, fp_vector b)` yields a `ve::fp_vector` containing in each slot the lesser of the values stored in `a` and `b` in that slot
- `ve::max(fp_vector a, fp_vector b)` yields a `ve::fp_vector` containing in each slot the greater of the values stored in `a` and `b` in that slot
- `ve::select(mask_vector, fp_vector a, fp_vector b)` yields a `ve::fp_vector` containing in each slot the value stored in `a` in that slot if that slot in the mask vector is set, and the value stored in `b` in that slot otherwise. (i.e. you get values from `a` if the condition that generated the `ve::mask_vector` is true and values form `b` if it is false)
- `ve::select(mask_vector, int_vector a, int_vector b)` as above for `ve::int_vector`s
- `ve::select(mask_vector, tagged_vector<tag_type>, tagged_vector<tag_type>)`as above for `ve::tagged_vector<tag_type>`s

## Load and store functions

The load family of functions is used to get data from an array source and put it into vector types where mathematical operations can be performed on it. When the final values have been computed, that data can be written to arrays using the store family of functions.

### Basic loads

The basic load instructions load a contiguous sequence of values from an array into a SIMD vector type. The `contiguous_tags` type indicates that the loaded values begin on an appropriate byte boundary (a 16 byte boundary for SSE4.2, and a 32 byte boundary for AVX and AVX2). In contrast, the `unaligned_contiguous_tags` type indicates that the values may not begin on such a boundary. And, finally, the `partial_contiguous_tags` type indicates that not only may the values begin at any byte boundary, but only the first `subcount` of those values should be loaded into the vector, and not necessarily a full vector's worth.

Signed 32-bit integer values are loaded into `ve::int_vector`s and floating point values are loaded into `ve::fp_vector`s as you would expect. Assuming that the `value_to_vector_type_s` structure has been specialized correctly (see [supporting strongly typed indexes](#supporting-strongly-typed-indexes) below), strongly typed indexes will be loaded into `tagged_vector<tag_type>`s of the appropriate type.

However, the instruction sets covered by this library do not support SIMD operations for unsigned integer types. Thus, unsigned 32-bit integer values are simply loaded as signed 32-bit integer values. For smaller integer values the situation is better. Signed 8-bit and 16-bit integer values are sign extended into 32-bit integer values on loading, and unsigned 8-bit and 16-bit integer values are zero extended into signed 32-bit integers.

```
ve::load(contiguous_tags<T>, float const*)
ve::load(unaligned_contiguous_tags<T>, float const*)
ve::load(partial_contiguous_tags<T>, float const*)

ve::load(contiguous_tags<T>, int32_t const*)
ve::load(unaligned_contiguous_tags<T>, int32_t const*)
ve::load(partial_contiguous_tags<T>, int32_t const*)

ve::load(contiguous_tags<T>, uint32_t const*)
ve::load(unaligned_contiguous_tags<T>, uint32_t const*)
ve::load(partial_contiguous_tags<T>, uint32_t const*)

ve::load(contiguous_tags<T>, int16_t const*)
ve::load(unaligned_contiguous_tags<T>, int16_t const*)
ve::load(partial_contiguous_tags<T>, int16_t const*)

ve::load(contiguous_tags<T>, uint16_t const*)
ve::load(unaligned_contiguous_tags<T>, uint16_t const*)
ve::load(partial_contiguous_tags<T>, uint16_t const*)

ve::load(contiguous_tags<T>, int8_t const*)
ve::load(unaligned_contiguous_tags<T>, int8_t const*)
ve::load(partial_contiguous_tags<T>, int8_t const*)

ve::load(contiguous_tags<T>, uint8_t const*)
ve::load(unaligned_contiguous_tags<T>, uint8_t const*)
ve::load(partial_contiguous_tags<T>, uint8_t const*)

ve::load(contiguous_tags<T>, tag_type const*)
ve::load(unaligned_contiguous_tags<T>, tag_type const*)
ve::load(partial_contiguous_tags<T>, tag_type const*)
```

Finally, the basic load instructions also have specialized versions for loading from `dcon::bitfield_type` arrays. These load functions return a `vbitfield_type` containing the loaded bits, which can then be converted into a `ve::masked_vector` if necessary.

```
ve::load(contiguous_tags<T>, dcon::bitfield_type const*)
ve::load(unaligned_contiguous_tags<T>, dcon::bitfield_type const*)
ve::load(partial_contiguous_tags<T>, dcon::bitfield_type const*)
```

### Basic stores

The basic store functions operate in the same way as the basic load functions described above. Integers are truncated when they are stored back into arrays of 16 or 8-bit integers

```
ve::store(contiguous_tags<T>, float*, fp_vector)
ve::store(unaligned_contiguous_tags<T>, float*, fp_vector)
ve::store(partial_contiguous_tags<T>, float*, fp_vector)

ve::store(contiguous_tags<T>, int32_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, int32_t*, int_vector)
ve::store(partial_contiguous_tags<T>, int32_t*, int_vector)

ve::store(contiguous_tags<T>, uint32_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, uint32_t*, int_vector)
ve::store(partial_contiguous_tags<T>, uint32_t*, int_vector)

ve::store(contiguous_tags<T>, int16_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, int16_t*, int_vector)
ve::store(partial_contiguous_tags<T>, int16_t*, int_vector)

ve::store(contiguous_tags<T>, uint16_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, uint16_t*, int_vector)
ve::store(partial_contiguous_tags<T>, uint16_t*, int_vector)

ve::store(contiguous_tags<T>, int8_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, int8_t*, int_vector)
ve::store(partial_contiguous_tags<T>, int8_t*, int_vector)

ve::store(contiguous_tags<T>, uint8_t*, int_vector)
ve::store(unaligned_contiguous_tags<T>, uint8_t*, int_vector)
ve::store(partial_contiguous_tags<T>, uint8_t*, int_vector)

ve::store(contiguous_tags<T>, tag_type*, tagged_vector<tag_type>)
ve::store(unaligned_contiguous_tags<T>, tag_type*, tagged_vector<tag_type>)
ve::store(partial_contiguous_tags<T>, tag_type*, tagged_vector<tag_type>)
```

Finally, the basic store instructions, like the basic load instructions, have specialized versions for storing to `dcon::bitfield_type` arrays.

```
ve::store(contiguous_tags<T>, dcon::bitfield_type*, mask_vector)
ve::store(unaligned_contiguous_tags<T>, dcon::bitfield_type*, mask_vector)
ve::store(partial_contiguous_tags<T>, dcon::bitfield_type*, mask_vector)

ve::store(contiguous_tags<T>, dcon::bitfield_type*, vbitfield_type)
ve::store(unaligned_contiguous_tags<T>, dcon::bitfield_type*, vbitfield_type)
ve::store(partial_contiguous_tags<T>, dcon::bitfield_type*, vbitfield_type)
```

### Gathering and scattering with loads and stores

The gathering family of load functions allows you to load a SIMD vector by populating each slot with the value from the array at the index stored in the corresponding slot of the first parameter. Thus, the gathering family of load functions allows you to go from a collection of indexes to the corresponding collection of values that they index. NOTE: only the AVX2 instruction set provides any built-in gather instructions.

```
ve::load(tagged_vector<tag_type>, float const*)
ve::load(tagged_vector<tag_type>, int32_t const*)
ve::load(tagged_vector<tag_type>, uint32_t const*)
ve::load(tagged_vector<tag_type>, int16_t const*)
ve::load(tagged_vector<tag_type>, uint16_t const*)
ve::load(tagged_vector<tag_type>, int8_t const*)
ve::load(tagged_vector<tag_type>, uint8_t const*)
ve::load(tagged_vector<tag_type>, tag_type_b const*)
ve::load(tagged_vector<tag_type>, dcon::bitfield_type const*)
```

The scattering family of store functions is the complement to the gathering loads family. It allows you to store values packed in a SIMD vector back into an array according to the indexes contained in the first parameter. HOWEVER, executing a scattering store when the first parameter contains two or more of the same index is undefined behavior. Thus the practical usefulness of scattering stores may be quite limited. NOTE: none of the currently supported instruction sets provide built-in scatter instructions.

```
ve::store(tagged_vector<tag_type>, float*, fp_vector)
ve::store(tagged_vector<tag_type>, int32_t*, int_vector)
ve::store(tagged_vector<tag_type>, uint32_t*, int_vector)
ve::store(tagged_vector<tag_type>, int16_t*, int_vector)
ve::store(tagged_vector<tag_type>, uint16_t*, int_vector)
ve::store(tagged_vector<tag_type>, int8_t*, int_vector)
ve::store(tagged_vector<tag_type>, uint8_t*, int_vector)
ve::store(tagged_vector<tag_type>, tag_type_b*, tagged_vector<tag_type_b>)
ve::store(tagged_vector<tag_type>, dcon::bitfield_type*, masked_vector)
ve::store(tagged_vector<tag_type>, dcon::bitfield_type*, vbitfield_type)
```

### Masked loads and stores

There may be circumstances in which it is necessary to conditionally not gather or scatter values for some of the indexes stored in a `ve::tagged_vector`, for example if some of the indexes contained within it may be invalid. In such a case you can use the masked gathering and scattering family of functions. These functions work as the normal gathering and scattering loads and stores, except that they only load or store values if the corresponding slot in the mask is set.

```
ve::load(tagged_vector<tag_type>, masked_vector, float const*)
ve::load(tagged_vector<tag_type>, masked_vector, int32_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, uint32_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, int16_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, uint16_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, int8_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, uint8_t const*)
ve::load(tagged_vector<tag_type>, masked_vector, tag_type_b const*)
ve::load(tagged_vector<tag_type>, masked_vector, dcon::bitfield_type const*)

ve::load(tagged_vector<tag_type>, vbitfield_type, float const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, int32_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, uint32_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, int16_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, uint16_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, int8_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, uint8_t const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, tag_type_b const*)
ve::load(tagged_vector<tag_type>, vbitfield_type, dcon::bitfield_type const*)

ve::store(tagged_vector<tag_type>, masked_vector, float*, fp_vector)
ve::store(tagged_vector<tag_type>, masked_vector, int32_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, uint32_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, int16_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, uint16_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, int8_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, uint8_t*, int_vector)
ve::store(tagged_vector<tag_type>, masked_vector, tag_type_b*, tagged_vector<tag_type_b>)
ve::store(tagged_vector<tag_type>, masked_vector, dcon::bitfield_type*, masked_vector)
ve::store(tagged_vector<tag_type>, masked_vector, dcon::bitfield_type*, vbitfield_type)

ve::store(tagged_vector<tag_type>, vbitfield_type, float*, fp_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, int32_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, uint32_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, int16_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, uint16_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, int8_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, uint8_t*, int_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, tag_type_b*, tagged_vector<tag_type_b>)
ve::store(tagged_vector<tag_type>, vbitfield_type, dcon::bitfield_type*, masked_vector)
ve::store(tagged_vector<tag_type>, vbitfield_type, dcon::bitfield_type*, vbitfield_type)
```

## Utilities

### Utility functions

- `dcon::bit_vector_test(dcon::bitfield_type const*, int32_t i)` returns a boolean indicating whether the `i`th bit in the array of packed bits is set. (index 8, for example, is the first bit in the second byte in the array)
- `dcon::bit_vector_set(dcon::bitfield_type*, int32_t i, bool)` sets the `i`th bit in the array of packed bits to the passed boolean value

### Vector size utilities

- `ve::vector_size` an `int32_t` constant equal to the number of 4 byte slots in a SIMD vector (4 for SSE4.2, 8 for AVX and AVX2)
- `ve::to_vector_size(uint32_t)` returns the least multiple of the `vector_size` constant greater than or equal to the passed value. This is useful for rounding up the number of items to be operated on when you wish to avoid creating `partial_contiguous_tags`s (see [Executing an operation](#executing-an-operation) below).

### Apply

- `ve::apply(function, ...)` Ideally, each of the functions called inside a SIMD operation could be written to take SIMD vectors as parameters. Sometimes, however, this is not possible, and in those situations you can use `apply`. The first parameter to `apply` must be either a function or an object that defines `operator()(...)` (including anonymous lambdas), which can be followed by one or more parameters of arbitrary type. When `apply` is called, it will call the passed function repeatedly to populate a SIMD vector (of a type derived from the passed function's return type) with the same parameters that were passed to the `apply` function. Additionally, if any of the parameters passed to `apply` are themselves a SIMD vector type (more precisely, a type that `ve::is_vector_type` maps to `true`), then they will be split up by `apply`, and each slot contained in the parameter will be passed to the function call that generates the corresponding slot in the return value. If the function passed to `apply` returns `void`, then `apply` will itself return `void`, but the function being applied will still be called once per slot and any SIMD vector parameters will still be divided accordingly. Finally, if any parameter is an instance of `partial_contiguous_tags`, apply will only call the passed function enough times to fill the first `subcount` slots in the returned vector.
- `ve::apply_with_indices(function, ...)` functions as `apply` except that the passed function is called with the slot index being filled as an additional first parameter

### Meta-programming utilities

- `template<typename T> ve::value_to_vector_type` this type alias allows you to convert a value type into the SIMD vector type that naturally holds it. `int`s, for example, are thus mapped to `ve::int_vector`s.
- `template<typename T> ve::value_to_vector_type_s` this structure is how the `ve::value_to_vector_type` alias is implemented. To extend it to custom types you must specialize it with the type in question and define a member type alias named `type` that resolves to the desired SIMD vector type.
- `template<typename T> ve::is_vector_type` this constant value is equal to true if the type in question is either a SIMD vector type, such as `ve::fp_vector`, or is a contiguous index type such as `unaligned_contiguous_tags`

## Executing an operation

### Core functions

The core of a SIMD operation is a function with signature `<typename T> void(T position)`, function-like object that defines `template <typename T> void operator()(T position)`, or an anonymous lambda such as `[](auto position){ ... }`. This function will be called repeatedly with `contiguous_tags<T>`, `unaligned_contiguous_tags<T>`, and `partial_contiguous_tags<T>` parameters (depending on the particularities of the way the operation is invoked, described below). The typical scenario is that, each time it is called, the operation will execute one or more `ve::load(position, data_source)` commands to populate SIMD vectors, operate upon those vectors, and then finally save the results with `ve::store(position, data_destination, values)` commands.

The uniform way to invoke a SIMD operation is with one of the six functions below:

```
template<typename tag_type, typename F> ve::serial_exact::execute<tag_type>(uint32_t count, F operation)
template<typename tag_type, typename F> ve::serial_unaligned::execute<tag_type>(uint32_t count, F operation)
template<typename tag_type, typename F> ve::serial::execute<tag_type>(uint32_t count, F operation)
template<typename tag_type, typename F> ve::par_exact::execute<tag_type>(uint32_t count, F operation)
template<typename tag_type, typename F> ve::par_unaligned::execute<tag_type>(uint32_t count, F operation)
template<typename tag_type, typename F> ve::par::execute<tag_type>(uint32_t count, F operation)
```

The `ve::serial_exact::execute` function is for operating on arrays that begin at an appropriately aligned address (on a 16 byte boundary for SSE4.2, and on a 32 byte boundary for AVX and AVX2) and contain an arbitrary amount of items. An operation launched by `serial_exact` will be called repeatedly with `contiguous_tags<tag_type>` starting at position 0 and increasing by a `ve::vector_size` stride. When there are fewer than `ve::vector_size` items left (as calculated based on the `count` parameter), the operation will be called one final time with a `partial_contiguous_tags<tag_type>` argument containing the position and number of any remaining items.

`ve::serial_unaligned::execute` works in the same was as `serial_exact::execute`, except that it is designed for working on arrays of values that are not necessarily properly aligned. The operation function is thus called with `unaligned_contiguous_tags<tag_type>`s instead of `contiguous_tags<tag_type>`s. 

`ve::serial::execute` assumes both that the arrays are appropriately aligned, and thus calls the operation function with `contiguous_tags<tag_type>`, and that the number of items in the arrays operated on are a multiple of `ve::vector_size` in number. Thus it does not make a final call to the operation function with `partial_contiguous_tags<tag_type>`; any remaining items are simply ignored.

Finally `ve::par_exact::execute`, `ve::par_unaligned::execute`, and `ve::par::execute<tag_type>` function as the serial versions described above, except that they also divide the work to be done using a thread pool. Note that unless there is a significant amount of work to be done (a very large number of items to process or a computationally expensive operations function), the overhead of starting the thread pool and then joining the worker threads may make the parallel version slower than the serial version. *If you care about performance, measure instead of making assumptions.* These functions are only available if `VE_NO_TBB` is not defined.

### Examples

The example below illustrates a simple operation that takes a value from array `a` and a value from array `b`, multiplies them together, and then adds them into the `destination` array. This example uses the `RELEASE_INLINE` macro (which you must define your own version of) to force the `operator()` to be inlined. Note also that `int32_t` is used here as the index type; strongly typed indexes are not required.

```
struct accumulate_product_operator {
	float* const dest;
	float const* const a;
	float const* const b;

	accumulate_product_operator(float* d, float const* va, float const* vb) : dest(d), a(va), b(vb) {};

	template<typename T>
	RELEASE_INLINE void operator()(T position) {
		ve::store(position, dest,
			ve::multiply_and_add(
				ve::load(position, a),
				ve::load(position, b),
				ve::load(position, dest))
		);
	}
};
	
void accumulate_product(uint32_t size, float* destination, float const* a, float const* b) {
	ve::serial_unaligned::template execute<int32_t>(
		size, accumulate_product_operator(destination, a, b));
}
```

The example below illustrates a slightly more complicated task. Here we are trying to sum up all the values in an array. And as an experiment we are also trying to avoid a problematic data dependency. If you add each vector of values loaded into a single accumulator you create a data dependency, as the result of adding new values into the accumulator must complete before the next set of values can be added. This example illustrates how you might mitigate that problem. (But whether this theoretical performance improvement is an actual performance improvement would require a measurement.) `dcon::ct_log2` is a `constexpr` function computing the base 2 logarithm of an integer. 

```
struct sum_all_operator {
	float const* const a;
	ve::fp_vector accumulators[4];
	
	sum_all_operator(float const* va) : a(va) {};

	template<typename T>
	RELEASE_INLINE void operator()(T position) {
		auto i = 0x03 & (position.value >> dcon::ct_log2(ve::vector_size));
		accumulators[i] = accumulators[i] + ve::load(position, a);
	}
};
	
float sum_vall_values(uint32_t size, float const* a) {
	sum_all_operator op(a);
	ve::serial_unaligned::template execute<int32_t>(size, op);
	auto intermediate_result = (op.accumulators[0] + op.accumulators[1])
		+ (op.accumulators[2] + op.accumulators[3]);
	return intermediate_result.reduce();
}
```

## Supporting strongly typed indexes

For reference, below is what the declaration of a strongly typed index could look like. Note that it is followed by a specialization of the `ve::value_to_vector_type_s` structure, which is necessary for the ve library to understand how it is supposed to work. For an example of how you can wrap arrays so that only indexes of the correct type can be used to access them, see [Vectorizable buffer](#vectorizable-buffer) above, as well as its implementation in `ve.hpp`.

```
class dummy_id {
public:
	using value_base_t = uint16_t;
	using zero_is_null_t = std::true_type;

	//value member declaration
	uint16_t value;

	//constructors
	explicit constexpr dummy_id(int16_t v) noexcept : value(v + 1) {}
	constexpr dummy_id(const dummy_id& v) noexcept = default;
	constexpr dummy_id(dummy_id&& v) noexcept = default;
	constexpr dummy_id() noexcept : value(uint16_t(0)) {}

	//operators
	dummy_id& operator=(dummy_id&& v) noexcept = default;
	dummy_id& operator=(dummy_id const& v) noexcept = default;
	bool operator==(dummy_id v) const noexcept { return value == v.value; }
	bool operator!=(dummy_id v) const noexcept { return value != v.value; }
	bool operator<(dummy_id v) const noexcept { return value < v.value; }
	bool operator<=(dummy_id v) const noexcept { return value <= v.value; }
	explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }

	//index_function
	constexpr int32_t index() const noexcept {
		return int32_t(value) - 1;
	}
};

template<>
struct ve::value_to_vector_type_s<dummy_id> {
	using type = tagged_vector<dummy_id>;
};
```

