# Feature overview and basic usage guide

## Contents

This document is intended to both explain the main features of the generated data containers and to be an introductory guide to creating a simple data container. Information on how to build the code generation tool, which files you may need to include in your projects, and how to integrate the code generation tool into your build process are covered in [getting started](getting_started.md).

## Core concepts: objects, properties, and relationships

### Objects and properties

The data managed by the data container is divided into objects and relationships, which themselves are composed of individual properties which represent the values that constitute an instance of the object or relationship. For example, suppose you wanted your data container to contains cars, each of which is defined by two values: the number of wheels it has and its resale value. To express this you could add the following to the file that you send to the data container generator.

```
object{
	name{car}
	storage_type{contiguous}
	size{ 1200 }
	
	property{
		name{wheels}
		type{int32_t}
	}
	property{
		name{resale_value}
		type{float}
	}
}
```

Upon reading this entry, the data container generator understands the following things: that you want a collection of objects named `car`, that these cars should be stored contiguously with each other, that room should be made to store up to 1,200 of them, and that each `car` needs to store two values: the number of wheels as an integer and the resale value as a floating point value[^1]. Conceptually this is similar to adding the following to your C++ program.

```
struct car {
	int32_t wheels = 0;
	float resale_value = 0.0f
};
car all_the_cars[1200];
```

(And if this were all you could do with the generated data container, it would be of very little use).

Now let us turn to how you can interact with the data container produced by the generator. The first thing to note is that, unless you have specified otherwise, everything produced by the generator will be put in the `dcon` namespace. To use the data container we must first create an instance of it. This can be done either with a global variable or by allocating room for it on the heap (avoid creating a data container on the stack, as it will typically not fit). For our example, we will assume that we have created our container with `auto ptr = std::make_unique< dcon::data_container >();`

A newly created data container is empty, which you can check by inspecting the result of `ptr->car_size()`. The first thing to do, then, is to create a new car instance, which we can do with `dcon::car_id new_car = ptr->create_car();` The `create_car` function makes a new car object inside the data container and returns a handle to it. Since values are stored internally in arrays in, this handle is actually a strongly typed index. You can check that this index is not set to the special *invalid index* value by explicitly casting it to bool. Assuming that nothing has gone terribly wrong, `new_car` will contain valid index, and thus `bool(new_car)` will be true. You can also check a car index by calling `ptr->car_is_valid(new_car)`. This will check both that the internal index is not set to the invalid value and that there is a valid car object at that index in the data container. Prior to calling `create_car` the first time, there were no valid indexes, and so `ptr->car_is_valid` would have returned false for every handle passed to it.

The next thing to do with a new car is to get and set the values. All values for a newly created object in the data container are initialized with their default constructor. In our case, this means that wheels and resale_value will both be set to zero. We can change this by calling `ptr->car_set_resale_value(new_car, 100.5f);` which will use the second parameter to set the value of the relevant property. And we can access the stored property value by calling `ptr->car_get_resale_value(new_car)`. For most types, the get function return a reference to the stored value, so you can change a value with an expression such as `ptr->car_get_wheels(new_car) = 4;` or you can temporarily take a reference to it to the avoid the verbosity of repeatedly calling the get function. (But do not hold such a reference over the deletion of objects stored as `compactable` or over the creation and deletion of objects with an `expandable` size.) Note that you can also safely read from the invalid index value (`ptr->car_get_wheels(dcon::car_id()))` will return 0, for example), which can be useful for avoiding unnecessary branching in some cases, but you should never write to an invalid handle.

Finally, you can delete car instances. Since the cars have been declared to be `contiguous`, and hence the valid car indexes form an uninterrupted sequence, the only way to get rid of cars is by `ptr->car_pop_back();` which will remove the instance with the greatest index and will reset every property value to whatever it would be after default construction.

### The nice syntax

The examples presented so far are all in what I call the "ugly" syntax, for obvious reasons. There is also a much nicer syntax available, but there are some trade offs. The nice syntax is built around "fat" handles, which contain not just an index to an object (or relationship) instance, but a reference to the data container as well. To construct such a handle you can use the `fatten` function, which takes two parameters, the first a reference to the data container and the second an ordinary handle. For example `auto new_car = dcon::fatten(*ptr, ptr->create_car());` would create a fat handle to the new car instance. Now, instead of calling an `𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_𝘧𝘶𝘯𝘤𝘵𝘪𝘰𝘯 𝘯𝘢𝘮𝘦(...)` function from the data container, you can simply call `new_car.𝘧𝘶𝘯𝘤𝘵𝘪𝘰𝘯 𝘯𝘢𝘮𝘦(...)` as a member function from the fat handle (if you come across a function that is missing from that fat handle, please let me know). If the object instance happens to store a handle to another object, then any `get_` function accessing it will automatically upgrade its return value to a fat handle, allowing you to chain nice-syntax function calls together. 

The downside to the nice syntax is the extra overhead of storing a reference to the data container in each handle. Many handles will be only two bytes in size, and the largest will be four bytes, so adding an additional 8 bytes to hold a reference is a significant size increase. Thus, you should avoid storing fat handles *en masse*. (The underlying ordinary handle can be obtained from a a fat handle through its `id` member variable.) Even passing multiple fat handles to the same function is intrinsically somewhat wasteful, as it results in passing one or more redundant references to the data container.

If you need to refer to the type of a fat handle explicitly, they are `𝘯𝘢𝘮𝘦𝘴𝘱𝘢𝘤𝘦::𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_fat_id` and `𝘯𝘢𝘮𝘦𝘴𝘱𝘢𝘤𝘦::𝘰𝘣𝘫𝘦𝘤𝘵 𝘯𝘢𝘮𝘦_const_fat_id`. The `const` version, which you can get from a `const` data container reference, exposes as member functions only those operations that can be called on a `const` data container.

### Relationships

Getting the data container to do useful work for you probably means defining not just one object, but many, along with the relationships that exist between them. For the sake of illustration, we will first add the definition for a person to our file as follows:

```
object{
	name{person}
	storage_type{contiguous}
	size{100}
	
	property{
		name{age}
		type{int32_t}
	}
}
```

along with a definition describing the relationship of of car ownership

```
relationship{
	name{car_ownership}
	
	link{
		object{person}
		name{owner}
		type{many}
		index_storage{std_vector}
	}
	link{
		object{car}
		name{owned_car}
		type{unique}
	}
	
	property{
		name{ownership_date}
		type{int32_t}
	}
}
```

This relationship contains two `link`s, with each `link` describing one of the objects involved in the relationship. These tell us that each relationship will be between a person and a car and that the person will be referred to as the `owner` in the context of the relationship while the car will be referred to as the `owned_car`. (These additional names are required because the same type of object could appear in multiple places within a single relationship.) To understand what `unique` and `many` mean in this context let's first talk a little bit about the way that relationships are represented internally. You can think of relationship instances as rows in a table:

| owned_car (car id) | owner (person id) |
| ------------------ | ----------------- |
| 1                  | 7                 |
| 2                  | 3                 |
| 5                  | 4                 |
| 9                  | 3                 |

Each row in this table, then, indicates the ownership of the car on the left by the person on the right.

What `unique` and `many` do is tell us how many times each particular car or person id may appear in its column in the table. In our example car, ids may appear at most once, while person ids may appear many times. What this means, practically, is that cars may have at most one owner (they are owned uniquely), while a single person is allowed to own many cars.

If at least one of the links in a relationship is marked as `unique` (without also being designated as `optional`), then the relationship will be stored internally as having a primary key. What this means exactly is covered in detail in [relationships](relationships.md#primary-keys), but for now what is important is that when a primary key can be found for a relationship the amount of storage and how to arrange that storage will be determined automatically, and hence that this relationship does not need `size` or `storage_type` definitions the way the objects do. (A relationship without a primary key does need them, however.)

Finally, note that a relationship may also store information in the form of properties in the same way that an object can.

Unlike objects, there are two ways to create a new relationship. First, we can create a new car_ownership relationship via `auto car_relation = ptr->try_create_car_ownership(person_a, car_a);`, where person_a and car_a are handles to a person and a car that have been created earlier. This will return a newly created relationship with the owner set to person_a and the owned car set to car_a, assuming that car_a does not already have an owner. Since cars can participate in at most one ownership relation, a new relationship involving car_a could not be created without changing something else, and in such a case `try_create_car_ownership` will return a handle that is false when cast to a boolean value. The second way to create a new relationship is with `ptr->force_create_car_ownership(person_a, car_a)`. In cases where `try_create_car_ownership` would fail, `force_create_car_ownership` will delete any conflicting relationships. This means that if the car handle appears in any other row in the table of relationships, then that row would be removed.[^2] This ensures that `force_create_car_ownership` can always return a handle to a valid relationship, but it also means that creating a new relationship in this way could result in unexpected changes to other relationships.

As with an object instance, you can get and set the properties of a relationship instance, which also extends to the property of being linked to a specific object. This means that in our example we can use `ptr->car_ownership_get_owner( car_relation )` to recover the handle of the owner and `ptr->car_ownership_get_owned_car( car_relation )` to recover the handle of the owned car. A relationship also creates additional getters and setters in the objects linked by the relationship, allowing you to find and alter the relationship via the objects. For a car, which is `unique`, this means that you can use `ptr->car_get_car_ownership_as_owned_car( valid_car_id )` to get the instance of car ownership that it is involved in, if any. (If the car is not involved in such a relationship, an invalid handle will be returned.)  Note the cumbersome `as_owned_car`. This exists because it is possible for the same type of object to be linked multiple times in a single relationship, and thus it may be necessary to specify which link to find the relationship by. Since there is only a single car linked to car ownership, an additional convenience function is generated in this case: `ptr->car_get_car_ownership( valid_car_id )`. A car can also be removed from an ownership relation with `ptr->car_remove_car_ownership_as_owned_car( valid_car_id )` (which will result in any relationship instance it is in being deleted). Likewise, getters and setters are added by the relationship to person, but since a person may appear in multiple car-ownership instances, the form of these functions is slightly different. Instead we have `ptr->person_for_each_car_ownership_as_owner( valid_person_id, [](dcon::car_ownership_id i) { ... });`, which calls the user-provided function once for each car-ownership instance containing the handle to that person. And all car-ownership instances involving a particular person can be delete with `ptr->person_remove_all_car_ownership_as_owner( valid_person_id );`

As is already evident, working with relationships can become a bit cumbersome. For example, you may find yourself repeatedly starting from a handle to a car, finding its ownership relationship, and then using that to obtain some property from the relationship. A common example of this would be getting the person who owns a car, which could be done as `ptr->car_ownership_get_owner( ptr->car_get_car_ownership( valid_car_id ) );` (or as `valid_car_id.get_car_ownership().get_owner()` with the nice syntax) Since doing this repeatedly is a pain, there are some convenience functions provided that allow you to get the value of a property in a relationship instance directly from the handle to an object instance. Since cars are linked by `unique`, their convenience function to get the owner out of a relationship starting from a car has the form `ptr->car_get_owner_from_car_ownership( valid_car_id )`. People, being of type `many`, have convenience functions in the form `ptr->person_for_each_owned_car_from_car_ownership( valid_person_id, []( dcon::car_id i ){ ... });` and `ptr->person_has_owned_car_from_car_ownership( valid_person_id, valid_car_id);` (which returns a boolean value indicating whether any relationship involving that person instance also involves an owned car with the specified id).

## Basic utility functions

The examples given so far have worked with individual object and relationship instances. Often, however, you will want to operate on the managed objects and relationships as a whole, for which the following functions are provided:

- `𝘰𝘣𝘫𝘦𝘤𝘵/𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦_size()` Returns the number of objects or relationships currently in the data container of the given type. (Note that this may be an overestimation if the storage type of the object or relationship is `erasable` or if the relationship has a primary key.)
- `template<typename T> for_each_𝘰𝘣𝘫𝘦𝘤𝘵/𝘳𝘦𝘭𝘢𝘵𝘪𝘰𝘯𝘴𝘩𝘪𝘱 𝘯𝘢𝘮𝘦(T&& functor)` calls the passed function once with the handle for each object or relationships currently in the data container.
- `reset()` Removes all objects and relationships from the data container


[^1]: You should never store real currency values as floating point. This is just for the sake of an example.

[^2]: Actually, since the car would be the primary key for this relationship something slightly different would happen: namely all the other values in that row of the table would be changed to the values passed to `force_create_car_ownership`, since it is not possible to change the primary key value in a row of our imaginary relationship table.