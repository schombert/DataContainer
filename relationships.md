# Relationships

## Contents

Using the data container generator to manage objects and the properties can be a small win for you. It allows you to use memory in a way that is probably more cache and SIMD vectorization friendly, but it wouldn't be unreasonable to do everything the generator does by hand. Relationships, however, are a different story. Allowing the data container generator to manage the relationships between the objects contained within it can save you a great deal of tedious, and error prone boilerplate. And, more importantly, it allows you to evolve your design without having to update all of that boilerplate with every change.

A relationship models a connection between two or more object instances that needs to be tracked. From a programming perspective, every pointer or reference in a class or structure is (part of) a logical relationship. If you were migrating an existing collection of classes to be managed by a data container, each of those pointers or references would end up as part of a relationship, and the properties of the object itself would make no reference to other objects.

## Unique aspects of relationships

Relationships are, at least syntactically, a strict superset of objects, and anything that is found in an object definition can also be found in a relationship definition. Most importantly, relationships can contain their own properties, which can be used to represent values that only make sense in the context of an interaction between two or more objects. You may wonder, then, why you would bother using objects at all, and the simple answer is that relationships can only be between objects; a relationship cannot relate to another relationship. Thus there must be objects in order for relationships to do anything at all.

For the remainder of this document we will be concerned exclusively with the features of relationships that objects don't have, and with the occasional ways in which the behavior of relationships deviates from that of objects.

### Links

Specifying the objects involved in a relationship is done by adding `link` keys to the relationship definition (and there must be at least two for the definition to be valid). Like the `property` key, a `link` key contains a number of sub-keys. The `object{𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦}` sub-key determines which object is being connected by this particular link. While `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦` must be an object defined somewhere else in the file, it does not have to be defined prior to defining the relationship. The `name{...}` sub-key determines how this link will be referred to in the context of the relationship. It must be a valid C++ identifier, but there are no other restrictions placed upon it. (However, for the sake of everyone's sanity, try to choose a name as descriptive as possible of the role that the linked object plays in the relationship.) The `type{...}` sub-key determines some of the constraints placed on the relationship (more on this in a moment). Its parameter must be one of `unique`, `many`, or `unindexed`. Finally, the forth possible sub-key is `index_storage{...}`. This is the only optional sub-key, and is required only when `type` is set to `many`. Its parameter must be one of `list`, `array`, or `std_vector`, the meaning of which is discussed in [Storage of indexing data](#storage-of-indexing-data) below.

It was already mentioned in the [overview](overview.md) that relationship instances can be thought of as entries in a table. (e.g. the the table below of a relationship between two objects with a single property.)

| pet (animal id)    | owner (person id) | adopted on (some date type) |
| ------------------ | ----------------- | --------------------------- |
| 1                  | 7                 | ...                         |
| 2                  | 3                 | ...                         |
| 5                  | 4                 | ...                         |
| 9                  | 3                 | ...                         |

A link of `type{unique}` means that the handle for the linked object may only appear once in the column for that link, while a link with `type{many}` may appear multiple times. And, leveraging those constraints, indexing data is stored for the linked objects that allows you to lookup the relationships that they are involved in. An object that is linked as `type{unique}` will have functions added that allow finding the unique relationship instance (if any) that it is in, while an object that is linked as `type{many}` will have functions added to iterate over all of the relationship instances that it is involved in. Leveraging this indexing data also allows the data container to keep relationships up to date with changes in the objects: an object that is deleted will result in any relationship instances that it is involved in being deleted as well, and an object that is moved will have any relationships it is involved in updated to reflect its new location. And this helps to explain the purpose of `type{unindexed}`. As with `type{many}`, no constraints are placed on how many times the objects linked in this way may appear in a column. Additionally, no extra indexing data is stored at all. This has two effects. First, no functions will be created for looking up relationship instances from the object linked. And secondly, the relationship instances will not be updated with any changes to the objects; and so invalid or incorrect handles may end up stored in such a link. A `type{unindexed}` link, then, is only advisable when you know that you need the performance advantages that it brings, and when you know that the objects being related will be neither created, nor deleted, nor moved for the lifetime of the relationship instance.[^1] Further suggestions for making the best used of `type{unindexed}` links are found in [Primary keys](#primary-keys) below.

### Storage of indexing data

For `type{unique}` keys (except primary keys, see next section) the indexing data required is a simple handle back to the relationship they are involved in (if any) that is logically managed as part of the object. (Note: the management of this data is entirely invisible to the end user, this is simply a description of how it is implemented.) For `type{many}`, however, the indexing data is more complicated; efficiency demands that each object maintain a list of the relationships it is involved in, and this list needs some kind of dynamic storage. I haven't been able to come up with a solution that is obviously best in all cases, so instead you can pick among three options for how these lists are to be stored on a case-by-case basis: `index_storage{array}`, `index_storage{std_vector}`, and `index_storage{list}`.

If you choose `array`, the lists of relationships will be stored as dynamically sized arrays backed by a fixed-size memory pool. Internally this is implemented in the same way that `vector_pool` type properties are, as described in (Objects and properties)[objects_and_properties.md#vector_pool]. The advantage of this approach are that the general memory allocator does not have to be called in order to manage the indexes. The disadvantages are two fold. First, the memory pool backing the lists is a fixed size, and it is possible to exhaust it. Currently the size of this pool is 16 times the maximum number of relationship instances bytes. Secondly, because the maximum number of relationship instances is used to estimate the size of the memory pool, it cannot be used in conjunction with relationships that are defined as `size{expandable}` (including those that are implicitly `size{expandable}` because of their primary key, as described below).

If you choose `std_vector`, the lists of relationships will each be stored in a `std::vector`. This is more flexible than arrays backed by a fixed-size memory pool, but it also incurs more overhead, both in storing each `std::vector` (24 bytes in many implementations), and in the performance costs incurred by using the general memory allocator to grow the underlying storage of these `std::vector`s.

Finally there is `list`, which is probably just a bad option .[^2] If you choose `list` the lists of relationships will be stored in a doubly linked list that is managed logically as an intrusive list inside the relationship instances themselves. Theoretically, this has the same trade-offs as any linked list as compared to an array: it has better insertion and deletion performance at the cost of slower traversal times. But given that the individual lists of relationships will probably be small, I suspect that it doesn't really provide better insertion an deletion performance.[^3] The one advantage it does provide, and the reason it is still available as an option, is that the implementation, like `array`, never calls the general memory allocator. But, unlike `array`, it can be used with relationships stored as `size{expandable}`, and its design guarantees that it will never run out of space (the storage space required to place each relationship instance in a list is logically allocated as part of the memory backing the potential relationship instance itself, so if you have enough room to store the relationships, you have enough room to store any configuration of the lists involving them).

### Primary keys

Primary keys are an aspect of relationships that the generator attempts to manage automatically, and to hide from the end user as much as possible. However, there are performance implications to primary keys, as well as some implications for behavior, so you probably still need to be aware of them.

Every relationship is automatically assigned a primary key, when possible, as a performance optimization. The primary key must be one of the `type{unique}` links in the relationship; if there are no such links then no primary key can be assigned. When choosing a primary key automatically, object definitions that specify fixed size are strictly preferred to `expandable` ones. Then, object definitions with `contiguous` storage type are chosen over those with `erasable` which are chosen over those with `compactable`. Finally, all other things being equal, the object definition that has the smallest defined size is preferred. If you don't like the way this automatic choice is made, or if you come to rely on any of the behavioral differences associated with the unique key and don't want your program to break if something in the definition of the objects or relationship changes, you can add `primary_key{link_name}` to the definition of a relationship, which will force the named `type{unique}` link to be used as the primary key.

If a relationship has a primary key, then instances of it are stored as a logical part of the object instances of the primary key type (you can think of this as the relationship adding extra members to the class or struct definition for the primary key). In particular, this means that the indexes used to access the relationship instances are logically identical to those that are used to access the object instances (although they still have distinct types). And so no actual storage space is allocated for relationship instances to store a handle to the object instance for its primary key link, nor do object instances of that type have storage allocated to store the handle of the relationships instance of this type (as both can be calculated directly from the handles themselves). This means that a relationship that has one link of type `unique` is more efficient than it would be if that link were turned into type `unindexed`, even though in general such links require less storage.

This also has implications for converting existing objects to be managed by a data container. It might seem natural to convert a pointer from type `object_a` to `object_b` such as:

```
class object_a {
	...
	public:
	object_b* member_pointer;
	...
};
```

to something like:

```
object{
	name{object_a}
	...
	property{
		name{member_pointer}
		type{object_b_id}
	}
	...
}
```

However, it is just as efficient (and will be essentially represented in the same way internally) to convert it to:

```
object{
	name{object_a}
	...
}

relationship{
	name{...}
	link{
		object{object_a}
		name{...}
		type{unique}
	}
	link{
		object{object_b}
		name{member_pointer}
		type{unindexed}
	}
}
```

This requires you to add some additional names describing the relationship from `object_a` to `object_b`, but you don't lose anything by making an explicit relationship in this way, and you gain the additional flexibility of being able to add indexing information later for `member_pointer` if you so choose.

Ideally, there would be no differences between the way the primary keys behave and the behavior of other links, but unfortunately some compromises have been made for the sake of performance. For every object linked with `unique` you can get a handle back to the relationship it is involved in with `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` (more details and slightly less verbose function names are described below). For a non primary, but `unique`, key this function may return a handle containing the invalid index value if no relationship has been created involving the object. Thus, you could cast this return value to bool to test whether such a relationship exists. On the other hand, if the object is linked as a primary key, `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` called with a valid object handle will never return an invalid index. To test whether the returned value represents an existing relationship, the best you can do is check it with `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_is_valid(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id)`. For a relationship with a primary key, that function returns true if at least one link other than the primary key contains a potentially valid object handle.

Finally, if a relationship has a primary key, any `size` or `storage_type` keys in its description will be ignored. It will be given a `size` to match that of the primary key, and its storage type will function as `contiguous`, except that its current size will always be adjusted to match that of the primary key. For relationships without a primary key, `size` and `storage_type` function as they do with objects, except that storage types of `contiguous` are not allowed (as it must always be possible to delete an arbitrary relationship).

### Composite keys

The first thing to note is that using one or more composite keys brings in an additional dependency, namely [this hash map](https://github.com/martinus/unordered_dense). A copy of the single header file necessary to use it is in CommonIncludes, but you can (and probably should) grab a copy of the most up-to-date version yourself.

Composite keys are added to a relationship by adding `composite_key{...}` as an additional key inside the relationship definition. `composite_key` expects a single parameter that will be parsed as a sequence of sub-keys. Like a link or a property, each `composite_key` must contain a `name{...}` sub-key that contains in its single parameter a valid C++ identifier. Each composite key must also include two or more `index{𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦}` sub-keys, where each link name is a link previously defined for the relationship.

Defining a composite key does two things. First, it allows you to find an instance of the relationship based on the combination of indexes in the composite key. Specifically, the data container will provide the function `get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_by_𝘤𝘰𝘮𝘱𝘰𝘴𝘪𝘵𝘦 𝘬𝘦𝘺 𝘯𝘢𝘮𝘦(...)` taking as parameters a handle for each of the links involved in the composite key. For example, a composite key defined as

```
composite_key{
	name{owner_pet_key}
	index{owner}
	index{owned_pet}
}
```

would generate the function `get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_by_owner_pet_key(person_id owner_p, pet_id owned_pet_p)` This function returns a handle to the relationship instance between handles that match those passed as parameters, or an invalid handle if there is no such relationship instance. Secondly, it forces each relationship instance to contain a unique combination of the linked objects involved in the composite key.

Multiple composite keys may be defined for the same relationship. If they are, the uniqueness requirement will be enforced for each composite key independently of the others. For example if the first composite key is between links `A`, `B`, and `C` and the second composite key is between links `B`, `C`, and `D`, then each relationship instance will required to have both an A-B-C combination that is unique to it and a B-C-D combination that is unique to it.

### Try create and force create

Unlike objects, there are two ways to create a new relationship: `try_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(...)` and `force_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(...)`. Both take as parameters one handle for each link in the relationship. `try_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦` first checks whether the new relationship can be created without violating any of the relationship constraints (i.e. it checks whether any of the object instances involved in a `unique` link are already involved in some other relationship and whether any of the composite keys that would be created already index another relationship). If the new relationship would violate any of those constraints, `try_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦` returns an invalid handle. Otherwise, it will create the new relationship instance as specified and return a handle to it.

`force_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦`, like `try_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦`, checks whether the new relationship would violate any of the relationship constraints. Unlike `try_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦`, it will call `delete_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦` to remove any existing relationship instances that would conflict with the new relationship instance. `force_create_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦` then creates the new relationship instance as specified and returns a handle to it.

### Deleting relationships

A relationship can be deleted in the same way that an object can with `delete_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id)` Additionally, if any of the objects linked by a relationship instance with type `unique` or `many` links are deleted, then the relationship instance will automatically be deleted as well.

### Getters and setters

If a relationship has any properties, it will have the standard getters and setters for them. Additionally, relationships generate the following getters and setters:

#### Those in the relationship

For every link in a relationship definition a getter will be created to access the handle stored in that link as `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_get_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id)` (as well as the SIMD vectorization friendly versions). For `type{many}` and `type{unindexed}` links *not* involved in a composite key, a setter for those links as `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_set_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id, 𝘭𝘪𝘯𝘬 𝘰𝘣𝘫𝘦𝘤𝘵 𝘵𝘺𝘱𝘦_id)` will also be generated. For `type{unique}` links *not* involved in a composite key *two* setters will be generated: `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_set_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id, 𝘭𝘪𝘯𝘬 𝘰𝘣𝘫𝘦𝘤𝘵 𝘵𝘺𝘱𝘦_id)` and `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_try_set_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id, 𝘭𝘪𝘯𝘬 𝘰𝘣𝘫𝘦𝘤𝘵 𝘵𝘺𝘱𝘦_id)`. This is because changing the value of such a link may violate the relationship constraints if the new value you wish to set it to is already involved in some relationship instance. The `set` version of the setter resolves this by calling `delete_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦` on any conflicting relationships, while the `try_set` version will change the value only if it can be done without violating the relationship constraint, and will return a `bool` to indicate whether the change was made.

#### Those added to the related objects

A relationship also generates additional getter and setters that are a logical part of the objects linked to the relationship (and in their fat handles, if you are using the nice syntax). If the object is linked as `unique`, an `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` that returns the relationship it is linked to (or an invalid handle if there is no such relationship), along with SIMD vectorization friendly versions, will be generated. In addition, an `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_remove_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` function will be generated that will delete the relationship the object instance is linked to, if any.

If the object is linked as `many` a different collection of getters and setters will be generated for it. First there is `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_for_each_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id, T&& functor)` which will call the provided function once for each relationship that the object instance is linked to. This function will be called with the handle of each such relationship as its parameter if the function is called from the data container itself, or a fat handle if it is called from a fat handle using the nice syntax. If the index storage is either `array` or `std_vector`, a `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_range of_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)`, which returns a `std::pair` of `𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_id const*` that span the underlying array containing the relationship handles linked to the object. Finally, an `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_remove_all_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` function will be generated that will delete all of the relationships that the object instance is linked to.

Note that the names of these function can be quite verbose, in part because of the `_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦` suffix. This suffix must exist to cover the possibility that the same type of object is linked into a relationship via two or more different links. If the object is not linked into a relationship via multiple different links, convenience versions of all the functions described in this section without the `_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦` suffix will also be generated.

#### Implicit joins

Finally, there are a small collection of functions that can save you the trouble of writing things like `𝘰𝘣𝘫𝘦𝘤𝘵 𝘩𝘢𝘯𝘥𝘭𝘦_id.get_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦().get_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦/𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦()` (not to mention the terrifyingly more verbose syntax for the ugly version). (Note: for the remainder of this section "property" also includes the links to individual object instances contained in a relation.) However, this collection is small because there are some limitations. First, there is the question of what happens when the object instance is not involved in a relationship. For properties involving simple types the easy answer is just to return a default constructed value (so zero for the numerical types and an invalid handle for handles). For larger types and objects, however, you really want a reference to the stored value, and not a copy. Thus the natural return type would be a `std::optional` wrapping a reference. But the standard library doesn't provide that type, and it isn't fair to require boost, so the best we could do would be to return a possibly-null pointer. And since that is inconsistent with the rest of the syntax, the functions simply aren't generated for now. Secondly, these function are only generated when the corresponding `_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦` suffix can be dropped from the getter that they are hiding. This is simply because the point of generating these functions is to provide shorter, more convenient access, and adding additional `_as_𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦` qualifiers rather defeats the purpose.

An additional pitfall of leaning on these functions is that they require repeatedly looking up the relationship that the object is involved in. It is more efficient to get the relationship once and then access properties through it if you need to access more than a single property.

With all that said, here are the generated functions themselves: For an object linked as `unique`, for every property in the relationship `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_get_𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦_from_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id)` and `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_set_𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦_from_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id, 𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘵𝘺𝘱𝘦)` functions will be generated. For an object linked as `many`, the functions `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_for_each_𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦_from_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id, T&& functor)` and `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_has_𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦_from_𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_id, 𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘵𝘺𝘱𝘦)`. The first calls the provided function once for each relationship that the object instance is linked to, with the value stored for the specified property in those relationship instances passed to the function. The second returns `true` if any of the relationships linked to the object instance contain a value stored in the specified property that compares as equal to the value passed as the second parameter, and `false` otherwise.

[^1]: You can also work around some of these limitations with `hook{delete}` and `hook{move}`, but be sure to measure to make sure that this solution is actually better than `type{unique}` or `type{many}`.

[^2]: Look, it felt clever when I was designing it, and leaving it in doesn't really hurt anything, so get off my back.

[^3]: Please feel free to contribute a measurement confirming this.