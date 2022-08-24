# The ve SIMD wrapper classes and functions

## Overview

The ve library provides a wrapper over SIMD data types for the x86_64 platform. The wrapper has two main features. First, it allows you to write an operation over array(s) of values that will automatically be compiled to one of the SSE4.2, AVX, or AVX2 instruction sets without making any alterations to the source code. This allows you to easily compile the same program once for each instruction set you want to target. Secondly, it provides support for strongly typed indexes (refereed to as "tags" in the source code for the sake of brevity). A strongly typed index provides the same type safety for looking up values / objects in an array by index that a pointer provides for normal data access. Supporting these strongly typed indexes is the real reason that the ve library exists, as there are a number of quality libraries that already support the first feature.

## Limitations

- There is no support for 32 bit compilation. Only x86_64 targets are supported.
- There is currently no support for AVX512 instructions. Support will be added if/when I get a machine supporting that instruction set to test on.
- Currently the instructions for operating on packed 8 byte data types (`double` and `int64_t`) are not supported, as my use case simply didn't require them. If you need support for these types, let me know (and explain why).
- When no instruction set is selected, the default target is SSE4.2 (technically SSE4.1, but I reserve the right to use `PCMPGTQ` someday). This means that there may be a tiny number of x86_64 machines that are not supported.

## Getting started

Before you get started, you first need to decide if you want the built-in parallelism support that ve provides. By default ve includes `ppl` (Microsoft's parallel patterns library) in order to provide the ability to divide an operation into chunks and dispatch them to a thread pool. If you don't like the Microsoft version of the library (or are building on Linux) it is simple to edit this include to point to a copy of Intel's `oneTBB`, which provides the same functionality (and which `ppl` is essentially an implementation of). Alternatively, if you don't want the built-in parallelism, simply add `#define VE_NO_TBB` prior to including `ve.hpp` (and also before including any generated data container headers), which will allow you to use ve wihout either `ppl` or `oneTBB`.

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

`ve::int_vector` holds a packed SIMD vector of 32 bit integer values (4 values for SSE4.2 and 8 for AVX and AVX2. This is basically the same as `ve::fp_vector` but for integers, so I won't blame you if you skip to the next type. Two significant differences are that `ve::int_vector` does not come with a `reduce` function, and when targeting AVX, `ve::int_vector` is implemented as a pair of wrapped SIMD types due to missing support in AVX for some integer operations.

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

A `ve::mask_vector` can be thought of as like a `ve::fp_vector` or `ve::int_vector` that holds either 4 or 8 boolean values (internally their representation is governed by the SIMD instruction set). `ve::mask_vector`s may be created either from loading packed bits from an array or as the result of a comparison between two vectors. `ve::mask_vector`s can be used to selectively combine two vectors into a single result (see [mathematical operations](#mathematical-operations) below) and they can be used to mask load and store operations (see [loading and storing](#load-and-store-functions) below) in order to avoid reading and writing from undesired or invalid addresses.

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

Internally a `ve::tagged_vector` is just a `ve::int_vector`, except that the integers stored inside it represent indexes into some particular vector. Any type put into the template must satisfy the following four requirements: 1) It must contain a type alias named `value_base_t` as a member that resolves to the underlying integer type of the index, which is at most 4 bytes. 2) It must have an `index()` function that returns the stored index as a `int32_t` value (these returned values should be 0-based indexes as is customary for C++). 3) It must contain a type alias named `zero_is_null_t` that resolves to `std::true_type` if an invalid index is represented with the numerical value 0, and resolves to `std::false_type` if an invalid index is represented with the numerical value -1. 4) It must have a public member variable named `value` that stores the internal numerical representation of the index.

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

This type is define in `common_types.hpp`. An array of `dcon::bitfield_type` values represents a sequence of boolean values packed into bits. Helper functions `dcon::bit_vector_set` and `dcon::bit_vector_test` are provided to help test and set the nth bit of arbitrarily long packed bit arrays. When packed bits are loaded from such an array with a load function (see [loading and storing](#load-and-store-functions) below) they will loaded as either 4 or 8 bits into a `ve::vbitfield_type`.

#### `ve::vbitfield_type

This type contains an appropriate number of bits loaded from a packed array of bits. It can be converted implicitly into a `ve::mask_vector` for use in SIMD operations.

### Contiguous indexes

##### `template<typename tag_type> ve::contiguous_tags`

This type marks a position in an array of values. If you write a SIMD operation the main bulk of the work will be driven by the execution function (see [executing an operation](#executing-an-operation) below) repeatedly calling the `operator(auto index)` function you have written with this type of value (or a `ve::unaligned_contiguous_tags`, see below). Passing this value to a load function along with an array of values will return a full vector of values from the array at the appropriate position, and passing it to a store function can be used to put values into an array at the appropriate position. In contrast to the `ve::unaligned_contiguous_tags` type describe below, loads or stores driven by this type are assumed to be appropriately aligned (on 16 byte boundaries for SSE4.2 and on 32 byte boundaries for AVX and AVX2) and the instructions that benefit from that will be used.

No demands are made of the `tag_type`, which can be an `int32_t` if you are not working with strongly typed indexes.

##### `template<typename tag_type> ve::partial_contiguous_tags`

In many cases, you may want to execute a SIMD operation on arrays of values that are not a multiple of the vector size in length. If there are fewer than a full vector's worth of items left at the end, the execution function will call your `operator(auto index)` function with a`ve::partial_contiguous_tags` that contains both the position of those last values and the number of remaining values, stored in the `subcount` member variable. Any loads or stores driven by a `ve::partial_contiguous_tags` will only read or write `subcount` many items, not a full vector's worth.

##### `template<typename tag_type> ve::unaligned_contiguous_tags`

Identical to a `ve::contiguous_tags`, except that it is generated when the loads and stores can not be guaranteed to be appropriately aligned.

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

(`value_to_vector_type` is described in [helper functions](#helper-functions) below)

There are two items worth nothing about this interface. First, it is an example of how strongly typed indexes can be used to guard against certain errors, as trying to access its contents with an index of the wrong type is simply not possible. Secondly, even though the values contained are appropriately aligned, access via `unaligned_contiguous_tags` is still provided. Accessing properly aligned values with the generic instructions is fine, if perhaps slightly sub optimal. However, if the values contained were not guaranteed to be properly aligned (for example, if they were stored in a `std::vector`) then providing access via `contiguous_tags` would be an error, as it could allow instructions that require aligned values to be called on unaligned values.
		
#### member functions: setters

- `void set(index_type i, T value) noexcept`
- `void set(contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept`
- `void set(unaligned_contiguous_tags<index_type> i, value_to_vector_type<T> values)`
- `void set(partial_contiguous_tags<index_type> i, value_to_vector_type<T> values) noexcept`
- `void set(tagged_vector<index_type> i, value_to_vector_type<T> values) noexcept`

These functions operate in essentially the same way as the getters described above, except that they take as parameter either a single value or a vector of values to store.

## Mathematical operations

## Load and store functions

## Helper functions

vector size constant
rounding functions
meta-programming functions

## Executing an operation

## Supporting strongly typed indexes

### Alignment considerations

