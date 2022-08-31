# Objects and properties

## Contents

This document contains a complete description of all the options available for an object and its properties. Any information in this document also applies to relationships, as they provide a superset of the functionality that an object offers.

## Objects

### Object name

An object name must be a valid C++ identifier. Additionally, the following identifiers will be defined internally: *`object name`*`_class`, *`object name`*`_id`, and *`object name`*`_id_pair`.

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

For each object definition, the data container provides a  `create_`*`object name`*`()`. This function creates a new instance of the desired object (storage space permitting) and returns a handle to it. If the storage type is `contiguous` or `compactable`, the data container will provide a `pop_back_`*`object name`*`()` function, which removes the instance with the greatest index. (In the case of `contiguous` storage, this is always the object most recently created.) If the storage type is `compactable` or `erasable`, the data container will provide a `delete_`*`object name`*`(id_type)` function. This function will remove the object corresponding to the handle given to it as a parameter. It is your responsibility to ensure that only valid handles are deleted. Trying to delete a handle that does not correspond to a valid object may leave the data container in an inconsistent state.

### Hooks

The object instances managed by a data container are not implemented as proper C++ objects, which means that they cannot have conventional constructors or destructors. However, it is possible to access the same functionality provided by a constructor or destructor through different means. If an object definition contains a `hook{create}` or `hook{delete}` entry it will declare an `on_create_`*`object name`*`(id_type)` or `on_delete_`*`object name`*`(id_type)` member function, respectively, without an implementation. You may then provide an implementation of these member functions in a .cpp file. The `on_create_`*`object name`* member function, if it exists, is called every time a new instance of the object is created, with a handle to that new object as a parameter. The handle is valid at the time that the member function is called, and all operations on it are permitted. Similarly, the `on_delete_`*`object name`* member function will be called with a handle immediately before removing the object with that handle.

A third hook is also possible for objects with `compactable` storage: `hook{move}`. As with hooks for creation and deletion, the data container will declare an `on_move_`*`object name`*`(new_handle, old_handle)` member function. This member function will be called after an object is moved from one index to another. The first parameter will be the new, valid handle for the object, while the second parameter will be its old handle, which will no longer be valid. It is possible to keep any handles stored outside the data container up to date even as they change internally. But writing updates to every such stored handle and keeping them up to date with changes in the rest of the program is an error-prone process, and not recommended.

### Utility functions

(is_valid, for each, get size. accessing invalid)

### Ve integration

(buffer creation, operator application)

## Properties

### Property name

### Property type

#### bitfield

#### derived

#### object

#### vector_pool

#### Other types

### Tags

### Accessing values

### Hooks

[^1]: At one point there were also strongly typed indexes that represented invalid indexes as -1 (or the maximum value for an unsigned integer type). Currently such indexes cannot be generated, but some of the machinery required to support them remains.
