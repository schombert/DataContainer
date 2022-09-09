# Getting started

## Building the generator

To use the DataContainer project, the first thing you have to do is build the generator which turns the text file that determines what the data container will hold into the C++ header file that implements it. In Visual Studio you can do this by building the DataContainerGenerator sub-project (either in release or debug). If you aren't using Visual Studio, building the project is still easy: throw the `.cpp` and `.hpp` files from the DataContainerGenerator directory together and build them in whatever way you prefer; there are no dependencies except the standard library and no requirements except C++17 support.

## Running the generator

Once you have compiled the generator and written a specification file describing your data container, it is time to figure out how to turn that file into a C++ header. In Visual Studio you can do this with a custom build tool. First, right click on the project within your solution that you want to generate the data container for and select `Add > Existing Item` to add the text file that you have written. Then, right click on the text file to view its properties. First find the `Item Type` property and change its value from `Text` to `Custom Build Tool`. After hitting apply, you should see new properties appear (under `Custom Build Tool > General` on the left). Change the `Command Line` setting to `𝘸𝘩𝘦𝘳𝘦 𝘺𝘰𝘶 𝘣𝘶𝘪𝘭𝘵 𝘵𝘩𝘦 𝘨𝘦𝘯𝘦𝘳𝘢𝘵𝘰𝘳\DataContainerGenerator 𝘺𝘰𝘶𝘳 𝘧𝘪𝘭𝘦 𝘯𝘢𝘮𝘦.txt`. Change the `Outputs` property to `𝘺𝘰𝘶𝘳 𝘧𝘪𝘭𝘦 𝘯𝘢𝘮𝘦.hpp`, and change `Add Outputs to Item Type` to `C/C++ header`. Don't forget to set these properties for *both* the debug and release configurations. Finally, right click on the specification file again and select `Compile` to make sure that you have done everything correctly. If you have, you can use `Add > Existing Item` again to make the generated header file part of the project.

If you are using CMake ... I don't use CMake myself, but my understanding is that you can use [add_custom_command](https://cmake.org/cmake/help/latest/command/add_custom_command.html) to run the generator.

For Meson ... probably [custom_target](https://mesonbuild.com/Reference-manual_functions.html#custom_target) will do the trick.

If you use either CMake or Meson, please feel free to contribute detailed instructions for them.

## What to include

Once you have generated the header file for your data container, there are a few final things you need to do before you can successfully compile and use it. First, you will need to include the `common_types.hpp` file in your project (found in the CommonIncludes directory). Second, you will need `ve.hpp` and the other `ve_....hpp` header files, as described in [the documentation for using the ve library](ve_documentation.md). If you don't want to use the ve library, simply define `DCON_NO_VE` before including either the generated file or `common_types.hpp`. Finally, if you have declared one or more composite keys, (see [composite keys](relationships.md#composite-keys)) you will need to include the `unordered_dense.h` file from CommonIncludes in your project. This is a copy, provided for the sake of convenience, of the hash map header from [Martin Leitner-Ankerl's unordered_dense project](https://github.com/martinus/unordered_dense), and you may want to go directly to the source for a more up-to-date version. These files are all simple enough that I suggest just making copies of them and dropping them into your project directly, rather than trying to depend on DataContainer in some way (and I don't support that approach anyways).

Also, don't forget to define `NDEBUG` for your release versions, which not only turns off the standard C asserts, but will also direct the compiler to force inline the trivial functions (the intent is to help the compiler see through them).

## Compiler support

The generated data container files require at least C++17 support to use, and are intended to work for msvc, clang, and gcc (there are a few compiler extensions used). I test almost exclusively with msvc, so if you encounter issues elsewhere, please let me know. In particular, the alignment of the data_container class is defined to be larger than the standard types. `new` in C++17 and later, as well as `std::make_unique` and `std::make_shared`, should support this over-alignment, but you may want to double check to make sure that the requested alignment is being respected.
