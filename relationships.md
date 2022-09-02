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

| pet (animal id)    | owner (person id) | adopted on (some date type |
| ------------------ | ----------------- | -------------------------- |
| 1                  | 7                 | ...                        |
| 2                  | 3                 | ...                        |
| 5                  | 4                 | ...                        |
| 9                  | 3                 | ...                        |

A link of `type{unique}` means that the handle for the linked object may only appear once in the column for that link, while a link with `type{many}` may appear multiple times. And, leveraging those constraints, indexing data is stored for the linked objects that allows you to lookup the relationships that they are involved in. An object that is linked as `type{unique}` will have functions added that allow finding the unique relationship instance (if any) that it is in, while an object that is linked as `type{many}` will have functions added to iterate over all of the relationship instances that it is involved in. Leveraging this indexing data also allows the data container to keep relationships up to date with changes in the objects: an object that is deleted will be removed from any relationships it is in, and an object that is moved will have any relationships it is involved in updated to reflect its new location. And this helps to explain the purpose of `type{unindexed}`. As with `type{many}`, no constraints are placed on how many times the objects linked in this way may appear in a column. Additionally, no extra indexing data is stored at all. This has two effects. First, no functions will be created for looking up relationship instances from the object linked. And secondly, the relationship instances will not be updated with any changes to the objects; and so invalid or incorrect handles may end up stored in such a link. A `type{unindexed}` link, then, is only advisable when you know that you need the performance advantages that it brings, and when you know that the objects being related will be neither created, nor deleted, nor moved for the lifetime of the relationship instance.[^1] Further suggestions for making the best used of `type{unindexed}` links are found in [Primary keys](#rimary-keys) below.

### Storage of indexing data

### Primary keys

### Composite keys

### Try create and force create

### Getters and setters

in addition to those of properties.

#### Those in the relationship

#### Those added to the related objects

#### Implicit joins

[^1]: You can also work around some of these limitations with `hook{delete}` and `hook{move}`, but be sure to measure to make sure that this solution is actually better than `type{unique}` or `type{many}`.