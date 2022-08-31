# Objects and properties

## Contents

This document contains a complete description of all the options available for an object and its properties. Any information in this document also applies to relationships, as they provide a superset of the functionality that an object offers.

## Objects

### Object name

An object name must be a valid C++ identifier. Additionally, the following identifiers will be defined internally: *`object name`*`_class`, *`object name`*`_id`, and *`object name`*`_id_pair`.

### Object ids

For every object defined, an *`object name`*`_id` class will be created. Instances of this class serve as handles for accessing an object's properties and for identifying an object in relationships. Internally, these classes are strongly typed indexes that are used to access the internal arrays of values that store the information for the objects managed by the data container.

Each such id contains `value_base_t`, an alias to the underlying type of the index (either `uint8_t`, `uint16_t`, or `uint32_t`, depending on the number of objects to be stored), `zero_is_null_t`, an alias to `std::true_type`[^1], a member variable `value` that stores the internal numerical representation of the index, and `index()` a member function that converts the internal value into an `int32_t`zero-based index.

Each id be put into a state indicating that it contains no valid index (internally this is represented by the value zero). Explicitly casting an id to bool will result in true if the index is not in this state, and false if it is. For more robust checking of which ids are valid, the data container provides the functions `is_valid`*`object name`* which returns true only if the id is not storing the invalid value and if its index is a valid object in the container.

### Storage types

The storage type for an object is specified by use of the `object{...}` key, with a parameter of `contiguous`, `compactable`, or  `erasable`. If no storage type is specified, it defaults to contiguous. The storage type of an object determines how each property value is stored internally. In all cases, each property is stored as an array, where the value for each object can be found by looking it up by index in that array.

If the storage type of an object is `contiguous`, this means that the indexes currently in use are an unbroken sequence from 0 up to some maximum value. This in turn means that new objects can only be appended to the end of this array and that an object can be removed only by dropping it from the back of the array (via the *`object name`*`_pop_back()` function).

If the storage type of an object is `compactable`, the indexes remain an unbroken sequence as they are for `compactable` storage. However, support is also added for deleting an object with any index. This is accomplished by moving the object with the last index into the position of the object to be deleted and then dropping the last object in the container.  The downside of this is that the same handle may not represent the same object after a deletion operation. Internally, this isn't a problem, as all references to the moved object stored in any relationships will be updated automatically. However, if you want to store handles outside of the data container, you will have to hook the `on_move_`*`object name`* function (see below) and manually update any handles you have stored. You also must take extra care not to hold on to any handles in local variables across a call that may delete an object.

Finally, if the storage type of an object is `erasable` then, like `compactable` objects, it is possible to delete an object with any index. Unlike `compactable` objects, however, no objects are moved by the deletion. Instead, empty holes are created within the underlying storage that are managed by a free list (so that any later creation of new objects will first fill them in). This makes life much easier if you want to store handles outside the data container. However, the downside is that iteration over the contained objects is more complicated as the dead values, and any vector operations will still be applied to these deleted objects (see [ve integration](#ve-integration) below).

### Size

### Tags

### Creation and deletion

### Hooks

### Utility functions

(is_valid, for each, get size)

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

### Hooks

[^1]: At one point there were also strongly typed indexes that represented invalid indexes as -1 (or the maximum value for an unsigned integer type). Currently such indexes cannot be generated, but some of the machinery required to support them remains.
