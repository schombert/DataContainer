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

### Bitfields

### Contiguous indexes

### Vectorizable buffer

## Mathematical operations

## Load and store functions

## Helper functions

## Executing an operation

## Supporting strongly typed indexes

### Alignment considerations

