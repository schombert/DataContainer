# Objects and properties

## Contents

This document contains a complete description of all the options available for an object and its properties. Any information in this document also applies to relationships, as they provide a superset of the functionality that an object offers.

## Objects

### Object name

An object name must be a valid C++ identifier. Additionally, the following identifiers will be used internally: *`object name`*`_class`, *`object name`*`_id`, and *`object name`*`_id_pair`.

### Object ids

For every object defined, an *`object name`*`_id` class will be created. Instances of this class serve as handles for accessing an object's properties and for identifying an object in relationships. Internally, these classes are strongly typed indexes that are used to access the internal arrays of values that store the information for the objects managed by the data container.

Each such id contains `value_base_t`, an alias to the underlying type of the index (either `uint8_t`, `uint16_t`, or `uint32_t`, depending on the number of objects to be stored), `zero_is_null_t`, an alias to `std::true_type`[^1], a member variable `value` that stores the internal numerical representation of the index, and `index()` a member function that converts the internal value into an `int32_t`zero-based index.

Each id be put into a state indicating that it contains no valid index (internally this is represented by the value zero). Explicitly casting an id to bool will result in true if the index is not in this state, and false if it is. For more robust checking of which ids are valid, the data container provides the functions `is_valid_`*`object name`* which returns true only if the id is not storing the invalid value and if its index is a valid object in the container.

### Storage types

The storage type for an object is specified by use of the `storage_type{...}` key, with a parameter of `contiguous`, `compactable`, or  `erasable`. If no storage type is specified, it defaults to contiguous. The storage type of an object determines how each property value is stored internally. In all cases, each property is stored as an array, where the value for each object can be found by looking it up by index in that array.

If the storage type of an object is `contiguous`, this means that the indexes currently in use are an unbroken sequence from 0 up to some maximum value. This in turn means that new objects can only be appended to the end of this array and that an object can be removed only by dropping it from the back of the array (via the *`object name`*`_pop_back()` function).

If the storage type of an object is `compactable`, the indexes remain an unbroken sequence as they are for `compactable` storage. However, support is also added for deleting an object with any index. This is accomplished by moving the object with the last index into the position of the object to be deleted and then dropping the last object in the container.  The downside of this is that the same handle may not represent the same object after a deletion operation. Internally, this isn't a problem, as all references to the moved object stored in any relationships will be updated automatically. However, if you want to store handles outside of the data container, you will have to hook the `on_move_`*`object name`* function (see below) and manually update any handles you have stored. You also must take extra care not to hold on to any handles in local variables across a call that may delete an object.

Finally, if the storage type of an object is `erasable` then, like `compactable` objects, it is possible to delete an object with any index. Unlike `compactable` objects, however, no objects are moved by the deletion. Instead, empty holes are created within the underlying storage that are managed by a free list (so that any later creation of new objects will first fill them in). This makes life much easier if you want to store handles outside the data container. However, the downside is that iteration over the contained objects is more complicated as the dead values, and any vector operations will still be applied to these deleted objects (see [ve integration](#ve-integration) below).

### Size

Each object definition must have a `size{...}` key. The size that is part of an object definition determines the maximum number of object instances that the data container can manage. Internally, properties are stored as a collection of arrays, each of which has enough room to store at least size many values. Thus, the size must be carefully chosen to be large enough to store as many objects as you could possibly want, but also to be as small as reasonably possible, as a the larger the size is the more memory the data container will require, almost all of which will be allocated up front.

The default behavior when trying to create a new object when there is no more space available is for `std::abort()` to be called. This is the default because I frequently work with exceptions turned off. If you prefer exceptions, simply define `DCON_USE_EXCEPTIONS` before including either the `common_types.hpp` file or any generated container files. If `DCON_USE_EXCEPTIONS` is defined, a `dcon::out_of_space` structure will be thrown instead upon attempting to create a new object in a full container.

Finally, there may be times when predetermining a size really is impossible. In such cases an object can instead be defined with `size{expandable}`. When the size is set to `expandable`, each property will instead be backed by a `std::vector`, instead of being backed by statically sized arrays. This vector can grow as necessary which means that the data container will run out of space only when the program as a whole has run out of memory to allocate. While this sounds great, there are a number of downsides to this approach. First, every property access will have to go though an additional layer of indirection, which I would expect to more or less double the cost of reading and writing values (but I have not measured this effect, it is just my gut feeling). More importantly, it means giving up on some of the multi-threaded safety that having all the values at fixed locations for the lifetime of the data container provides (see [Multithreading](multithreading.md)). Thus, I think that `expandable` is best saved for when it is absolutely necessary, and should not be your default choice.

### Tags

An object definition can be given any number of `tag{...}` keys. The sole function of these tags are to aid in selecting objects for serialization (see [Serialization](serialization.md)). If you don't plan on using the provided serialization facilities, they can be ignored completely.

### Creation and deletion

For each object definition, the data container provides a  `create_`*`object name`*`()`. This function creates a new instance of the desired object (storage space permitting) and returns a handle to it. If the storage type is `contiguous` or `compactable`, the data container will provide a `pop_back_`*`object name`*`()` function, which removes the instance with the greatest index. (In the case of `contiguous` storage, this is always the object most recently created.) If the storage type is `compactable` or `erasable`, the data container will provide a `delete_`*`object name`*`(`*`object name`*`_id)` function. This function will remove the object corresponding to the handle given to it as a parameter. It is your responsibility to ensure that only valid handles are deleted. Trying to delete a handle that does not correspond to a valid object may leave the data container in an inconsistent state.

### Hooks

The object instances managed by a data container are not implemented as proper C++ objects, which means that they cannot have conventional constructors or destructors. However, it is possible to access the same functionality provided by a constructor or destructor through different means. If an object definition contains a `hook{create}` or `hook{delete}` entry it will declare an `on_create_`*`object name`*`(`*`object name`*`_id)` or `on_delete_`*`object name`*`(`*`object name`*`_id)` member function, respectively, without an implementation. You may then provide an implementation of these member functions in a .cpp file. The `on_create_`*`object name`* member function, if it exists, is called every time a new instance of the object is created, with a handle to that new object as a parameter. The handle is valid at the time that the member function is called, and all operations on it are permitted. Similarly, the `on_delete_`*`object name`* member function will be called with a handle immediately before removing the object with that handle.

A third hook is also possible for objects with `compactable` storage: `hook{move}`. As with hooks for creation and deletion, the data container will declare an `on_move_`*`object name`*`(`*`object name`*`_id new_handle, `*`object name`*`_id old_handle)` member function. This member function will be called after an object is moved from one index to another. The first parameter will be the new, valid handle for the object, while the second parameter will be its old handle, which will no longer be valid. It is possible to keep any handles stored outside the data container up to date even as they change internally. But writing updates to every such stored handle and keeping them up to date with changes in the rest of the program is an error-prone process, and not recommended.

### Utility features

For each object definition, the data container provides a number of utility functions:

- *`object name`*`_size()` returns a `unint32_t`, which for objects stored as `compactable` or `contiguous` is the number of objects of that type currently managed by the data container. For objects stored as `erasable` this is instead an upper bound on the number of objects managed (specifically, there are no valid indexes greater than or equal to the value returned).
- `template<typename T> for_each_`*`object name`*`(T&& functor)` will call the provided function once for each object managed by the data container, passing it a handle to that object. If the object are stored as `erasable`, the function *will not* be called with handles that correspond to empty positions in the underlying storage arrays.
- `is_valid_`*`object name`*`(`*`object name`*`_id)` returns true if the parameter is a handle to a valid object managed by the data container. For objects stored as `compactable` or `contiguous` this amounts to checking that the index contained in it does not represent that invalid value, and that it is less than the number of objects currently managed. For objects stored as `erasable` this function also checks whether the handle corresponds to an empty position created by some prior deletion.

### Ve integration

(This section assumes that you are already familiar with the [ve documentation](ve_documentation.md). While depending on the ve library is the default, all integration can be removed by defining `DCON_NO_VE` before including any generated file.)

Support for the ve library is provided via the following functions:

- *`object name`*`_make_vectorizable_float_buffer()` returns a `ve::vectorizable_buffer<float, `*`object name`*`_id>` with sufficient space to store one floating point value for each object managed by the data container. This is intended as a convenience function for generating intermediate storage buffers for SIMD operations carried out on the object.
- *`object name`*`_make_vectorizable_int_buffer()` as above, but returns a `ve::vectorizable_buffer<int32_t, `*`object name`*`_id>` 
- `template<typename T> execute_serial_over_`*`object name`*`(T&& functor)` calls `ve::serial_exact::execute<`*`object name`*`_id>(count, functor)` with `count` equal to the number of objects managed by the data container, unless the size of the objects has been declared to be `expandable`, in which case `ve::serial_unaligned::execute<`*`object name`*`_id>(..., functor)` is called instead. The effect of this is to run the SIMD operation `functor` on all the objects managed by the data container of this type. Note that in the case of objects stored as `erasable`, this may also result in the SIMD operation being called with the values corresponding to some of the empty slots. If this would be a problem, it is your responsibility to mask out operations on those slots as necessary.
- `template<typename T> execute_parallel_over_`*`object name`*`(T&& functor)` As above, but with `ve::par_exact::execute` and `ve::par_unaligned::execute`. This function will not be available if `VE_NO_TBB` is defined prior to including the generated file.
 
## Properties

Properties are added to an object definition by adding `property{...}` keys to it, with each property key containing sub-keys (`name{...}`, `type{...}`, and `hook{...}`) that define it. Each property must have a name and a type, but the `hook` keys are optional. Each property creates an additional logical value that will be associated with each object instance; you can think of them as corresponding to the member variables of a standard C++ structure or class.

### Accessing values

For most properties a basic getter and setter, *`object name`*`_get_`*`property name`*`(`*`object name`*`_id)` and *`object name`*`_set_`*`property name`*`(`*`object name`*`_id, property_value_type)` are generated to permit access to the stored values. These functions may be supplemented or slightly modified depending on `type` defined for the property (see [Property type](#property-type) below). Where possible, the getter returns are reference to the stored value. This is useful in two ways. First, you may wish to capture the reference in some cases to save yourself some typing, as repeatedly calling getters and setters can be quite verbose. Secondly it makes storing complicated values, such as a `std::vector` possible, as you can access their member functions without making a copy of them.

As an additional convenience feature, it is (usually) safe to invoke a getter even with a handle that represents an invalid index. The index for such handles resolves to -1, and the space immediately proceeding the arrays that store the values is also allocated and default constructed. (Thus reading from it will yield some version of 0 for the basic types). The advantage of this is that in some cases a branch testing for the invalid index value can be omitted, which can sometimes make life much easier when writing SIMD operations. The two exceptions to this feature are properties defined with a type of `object` and `vector_pool`, neither of which have the necessary extra space allocated for them.

### Property name

A property name must be a valid C++ identifier. Additionally, the following identifiers will be used internally: `m_`*`property name`*, *`property name`*`_p`, and possibly *`property name`*`_storage`. The property name `_index` is also reserved for internal use.

### Property type

The type of value that a property will hold is determined by the `type{...}` key. The parameter to the type key can be a data type, for example `type{int32_t}` means that the property will contain `int32_t` integers, or can be one of the special types described below.

#### bitfield

A property defined as `type{bitfield}` represents a logical boolean value, and its getters and setters will take and return `bool`s. However, internally the boolean values for all instances of this type of object will be stored together as a packed array of bits. This significantly reduces the amount of space requires to store these values (by a factor of 8), but adds some overhead to accessing them. If you want a boolean value that is not stored as a packed array of bits, you can define a property as `type{bool}`, which will store them as a standard array of boolean values (unless the object definition has a size of `expandable`, because in that case the values are stored in `std::vector`s and `std::vector<bool>` manages to make life harder for all of us). (Note: `sizeof(bool)` is assumed to be 1, even though the C++ standard does not guarantee this. If `bool` is larger in your implementation, bad things will happen. In that case, use `uint8_t` instead.)

#### derived

A property defined as `type{derived{type_name}}` represents a logical value of type `type_name`, but which has no underlying storage allocated for it at all. Instead, you must declare a hook for the getter and/or setter (see [Property hooks](#property-hooks) below), which will allow you to define how the property value should be calculated when it is accessed. `derived` properties are provided primarily to accommodate a scenario in which you are changing the definition of an object to no longer store a particular value. Turning that value into a derived value can allow you make that change without making major changes to the rest of the code base. `derived{bitfield}` properties will result in getters and setters that match those for a `type{bitfield}`. Properties that were previously defined as `type{object{...}}` should be turned into `type{derived{...}}`. `vector_pool` and `array` types cannot be converted into derived types in this way.[^2]

#### object

A property defined as `type{object{type_name}}` represents a value of type `type_name`. In addition, it also informs the generator that `type_name` cannot moved around with `memcpy`, and that its default constructor and destructor must be run. This also results in the generator providing the declarations for user-defined serialization and deserialization routines for objects of type `type_name` (since obviously they are not safe to copy directly into and out of a `std::byte` buffer), which you will have to provide (see [Serialization](serialization.md) for more details).

#### vector_pool

A property defined as `type{vector_pool{size}{type_name}}` represents a variable-length array of values of type `type_name` (each object instance has its own array of values, and the size of these arrays may vary from instance to instance). This is provided as an alternative to properties of type `type{object{std::vector<type_name>}}`. The difference are: The underlying value stored for each `vector_pool{size}{type_name}` property is four bytes, while about 24 bytes (three pointers) would be stored per instance for a `object{std::vector<type_name>}}` (depending on its implementation). However, the arrays for the `vector_pool{size}{type_name}` are drawn from a fixed pool of `size * 8` bytes, which will be allocated as part of the data container. This puts a limit to how many values may be stored in these arrays in total (reduced even further by the overhead requires to track the current size and capacity of these arrays, as well as manage the free list that exists within the pool, all of which consume memory allocated to the pool itself). A further restriction is that any type stored in one of these special arrays must be safe to move around by `memcpy`; constructors and destructors will typically not be called. Finally, because the data container "understands" the special `vector_pool` type in a way that it doesn't understand `std::vector<type_name>}` there are a number of unique getters and setters provided for properties of this type, as follows:

- *`object name`*`_get_`*`property name`*`_range(`*`object name`*`_id)` returns a `std::pair` containing two pointers, the first to the beginning of the stored array, and the second to the element one past its end (or possibly two null pointers if there is no storage assigned to the array yet)
- *`object name`*`_get_`*`property name`*`_at(`*`object name`*`_id, uint32_t n)` returns the value stored at the nth index of the array (this is a zero-based index)
- *`object name`*`_get_`*`property name`*`_capacity(`*`object name`*`_id)` returns the maximum size the array can be grown two before it will have to be internally reallocated within the memory pool
- *`object name`*`_get_`*`property name`*`_size(`*`object name`*`_id)` returns the current size of the array
- *`object name`*`_`*`property name`*`_contains(`*`object name`*`_id, type_name)` returns `true` if the value passed compares as equal to one of the values in the array, and `false` otherwise
- *`object name`*`_`*`property name`*`_push_back(`*`object name`*`_id, type_name)` adds the passed value to the end of the array, increasing its size by one
- *`object name`*`_`*`property name`*`_pop_back(`*`object name`*`_id)` removes the last value of the array, decreasing its size by one. Nothing happens if the array is already empty
- *`object name`*`_`*`property name`*`_add_unique(`*`object name`*`_id, type_name)` adds the passed value to the end of the array, increasing its size by one, if no value currently in the array compares equal to it
- *`object name`*`_`*`property name`*`_remove_unique(`*`object name`*`_id, type_name)` removes a single copy of an item in the array that compares equal to the passed value, decreasing its size by one. If no item compares equal to the passed value, the array will not be changed. The order of the items in the array may be changed by this operation.
- *`object name`*`_`*`property name`*`_clear(`*`object name`*`_id)` removes all of the items in the array and resets its size to zero
- *`object name`*`_`*`property name`*`_remove_at(`*`object name`*`_id, uint32_t n)` remove the item at the nth index from the array (as a zero-based index), by replacing it with what is currently the last value in the array and then shrinks the size of the array by one. Calling this function with an invalid index into the array will make bad things happen, so don't do it.
	
#### array

A property defined as `type{array{index_type}{value_type}}` or `type{array{value_type}}`, like `vector_pool`, represents a variable-length array of values. However, unlike a `vector_pool` property, the length of the array is the same for all of the object instances in the data container. This allows the values a particular logical index in this array to be stored contiguously across different object instances, which in turn facilitates SIMD operations on these arrays. The designed purpose of properties of this type is to model collections of values the number of which cannot be determined at compile time, but which is expected to be fixed for most of the runtime of the program. For example, if an object represents a mass value associated with some N-dimensional point, we may not want to fix N at compile time. However, we can expect N to remain constant for the lifetime of the objects, and so a `type{array{int32_t}{float}}` may be a good choice to represent the coordinates of those objects. Resizing the array is done by calling *`object name`*`_resize_`*`property name`*`(uint32_t)`, while the current size can be checked by calling *`object name`*`_get_`*`property name`*`_size()`.

In the two parameter version of the key, the first parameter given to `array` is the type of value that will be used to index into the array (which defaults to `uint32_t` in the one parameter version). This can be any integer type or strongly typed index, including one created by `make_index` (see [File format documentation](file_format_documentation.md)). The second parameter in the two parameter version or the only parameter in one parameter version is the type of value to be stored in the array. This can be any type that can be safely moved by `memcpy` or `bitfield`.[^3]

The getters and setters for a property defined as an `array` are as follows:
- *`object name`*`_get_`*`property name`*`(`*`object name`*`_id, index_type)`
- *`object name`*`_set_`*`property name`*`(`*`object name`*`_id, index_type, property_value_type)`
Both require an index into the array as well as a handle to the object. Any SIMD getters and setters generated (see [Ve integration for properties](ve-integration-for-properties) below) will also require this index parameter.

#### Other types

Finally, any C++ type that can be moved by `memcpy` can be passed as a parameter to `type`. (Although if this is a user defined type, it must be defined before the data container is. This is easiest to guarantee by using the `include ` key, see [File format documentation](file_format_documentation.md).) The expected usage pattern is to define all of the properties in terms of primitive C++ types, and rely minimally on user-defined data types, as the values inside a user-defined data type will not be easily available to SIMD operations. Sometimes, however, your expected usage patterns may conflict with the data container's default assumptions. By storing the values for each property together, the data container is optimized under the assumption that when you need a value, you will likely also need that same value from other, nearby, object instances. Sometimes, however, you know that some subset of the properties will usually be accessed together, and hence that you would like the values for those properties to all be stored together for any given object instance (ideally on the same cache line). In that situation, you can get the result you want by defining a structure that contains the values that you know belong together and then making a single property that stores instances of that structure.

#### Ve integration for properties

If the type stored in a property is detected by the data container to be amenable to SIMD operations (i.e. a `char`, `unsigned char`, `signed char`, `bool`, `int`, `unsigned int`, `short`, `unsigned short`, `float`, `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, the type of a handle to an object, or a type created by `make_index`[^4]), the data container will contain additional getters and setters for these properties that will allow you to access multiple of those values at the same time (assuming, again, that `DCON_NO_VE` is undefined). Specifically, in addition to the standard getters and setters for the property, versions  will be generated with the single handle identifying the object replaced by one of `ve::tagged_vector<object_id>`, `ve::partial_contiguous_tags<object_id>`, `ve::contiguous_tags<object_id>`, or `ve::unaligned_contiguous_tags<object_id>` that will operate on the range of object handles passed rather than on a single object instance at a time.

### Tags

As with an object definition, a property definition can be given any number of `tag{...}` keys, which aid in selecting properties for serialization (see [Serialization](serialization.md)). If you don't plan on using the provided serialization facilities, they can be ignored completely.

### Property hooks

If a property definition contains a `hook{get}` or `hook{set}` entry it will not generate the usual getter or setter functions, respectively. Instead it will only declare those functions, and the user is thus required to provide an implementation of them in some other file. For properties defined as `derived`, this is the only way in which getters or setters will be generated at all. For convenience, the SIMD getters and setters will still be generated if they would have been in the absence of the `hook` key, but they will be implemented by repeatedly calling the user-defined getter and setter.

[^1]: At one point there were also strongly typed indexes that represented invalid indexes as -1 (or the maximum value for an unsigned integer type). Currently such indexes cannot be generated, but some of the machinery required to support them remains.

[^2]: At least, not yet. If you need this functionality, let me know why and I will consider adding it.

[^3]: There is nothing stopping more kinds of things from being stuffed into an array, I just didn't feel like writing more special cases.

[^4]: Yes, it must be one of those types verbatim, and not some other alias that will evaluate to one of them. The generator runs before the compiler, and hence does not have a sophisticated understanding of C++ types. While the generator could produce the ve integration functions in all cases, and then make them unavailable based on the types as resolved at compile time with template magic, I decided faster compile times for projects including the generated data container were more important than supporting user-defined / more obscure aliases for these types.