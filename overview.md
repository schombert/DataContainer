# Feature overview and basic usage guide

## Contents

This document is intended to both explain the main features of the generated data containers and to be an introductory guide to creating a simple data container. Information on how to build the code generation tool, which files you may need to include in your projects, and how to integrate the code generation tool into your build process are covered in [getting started](getting_started.md).

## Core concepts: objects, properties, and relationships

### Objects and properties

The data managed by the data container is divided into objects and relationships, which themselves are composed of individual properties which represent the values that define the object or relationship. For example, suppose you wanted your data container to contains cars, each of which is defined by two values: the number of wheels it has and its resale value. To express this you could add the following entry to the file that you send to the data container generator.

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

Upon reading this entry the data container generator understands the following things: that you want a family of objects named `car`, that these cars should be stored contiguously with each other, that room should be made to store up to 1,200 of them, and that each `car` needs to store two values, the number of wheels as an integer and the resale value as a floating point value[^1]. Conceptually this is similar to adding the following to your C++ program.

```
struct car {
	int32_t wheels = 0;
	float resale_svalue = 0.0f
};
car all_the_cars[1200];
```

(And if this were all you could do with the generated data container, it would be of very little use).

Now let us turn to how you can interact with the data container produced by the generator. The first thing to note is that, unless you have specified otherwise, everything produced by the generator will be put in the `dcon` namespace. To use the data container we must first create an instance of it. This can be done either with a global variable or by allocating room for it on the heap, but you should avoid creating them on the stack, as they will typically be quite large, and will not fit. For our example let us assume that we have created our container with `auto ptr = std::make_unique< dcon::data_container >();`

A newly created data container is empty, which you can check by inspecting the result of `ptr->car_size()`. The first thing to do, then, is to create a new car object, which we can do with `dcon::car_id new_car = ptr->create_car();` The `create_car` function makes a new car object inside the data container and returns a handle to it. Since values are stored internally in arrays in the data container, this handle is actually a strongly typed index. You can check that this index is not set to the special *invalid index* value by explicitly casting it to bool. Assuming nothing has gone terribly wrong, `new_car` will be a valid index, and thus `bool(new_car)` will be true. You can also check a car index by calling `ptr->is_valid_car(new_car)`. This will check both that the internal index is not set to the invalid value and that there is a valid car object at that index in the data container. Prior to calling `create_car` the first time, there were no valid indexes, and so `ptr->is_valid_car` would have returned false for every index passed to it.

The next thing to do with a new car is to get and set the values. All values for a newly created object in the data container are initialized with their default constructor. In our case, this means that wheels and resale_value will both be set to zero. We can change this by calling `ptr->car_set_resale_value(new_car, 100.5f);` which will use the second parameter to set the value of the relevant property. And we can see the stored property value by calling `ptr->car_get_resale_value(new_car)`. For most types, the get function return a reference to the stored value, so you can change a value with an expression such as `ptr->car_get_wheels(new_car) = 4;` or you can temporarily take a reference to it to the avoid the verbosity of repeatedly calling the get function. (But do not hold such a reference over the deletion of objects stored as `compactable` or over the creation and deletion of objects with an `expandable` size.) Note that you can also safely read from the invalid index value (`ptr->car_get_wheels(dcon::car_id()))` will return 0, for example), which can be useful for avoiding unnecessary branching in some cases, but you should not write to it.

Finally, you can delete car objects. Since the cars have been declared to be `contiguous`, and hence that all the valid car indexes form an uninterrupted sequence, the only way to get rid of cars is by `ptr->car_pop_back();` which will remove the car with the greatest index and will reset every property value to whatever it would be after default construction. 

### Relationships

Getting the data container to do useful work for you probably means defining not just one object, but many, along with the relationships between two or more of them. For the sake of illustration, we will first add the definition for a person object to our file as follows:

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

along with a definition describing the relation of of car ownership

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

This relationship contains two `link`s, with each `link` describing one of the objects involved in the relationship. These tell us that each relationship will be between a person object and a car object and that the person will be referred to as the `owner` in the context of the relationship while the car will be referred to as the `owned_car`. (These additional names are required because the same type of object could appear in multiple places within a single relationship.) To understand what `unique` and `many` mean in this context let's first talk a little bit about the way that relationships are represented internally. You can think of relationships as like entries in a table:

| owned_car (car id) | owner (person id) |
| ------------------ | ----------------- |
| 1                  | 7                 |
| 2                  | 3                 |
| 5                  | 4                 |
| 9                  | 3                 |

What `unique` and `many` do is tell us how many times each particular car or person id may appear in its column in the table. In our example car ids may appear at most once, while person ids may appear many times. What this means, practically, is that cars may have at most one owner, while a single person is allowed to own many cars.

If at least one of the links in a relationship is marked as `unique`, then the relationship will be stored internally as having a primary key. What this means exactly is covered in detail in [relationships](relationships.md), but for now what is important is that when a primary key can be found for a relationship the amount of storage and how to arrange that storage will be determined automatically, and hence that this relationship does not need `size` or `storage_type` definitions the way the objects do. (A relationship without a primary key does need them, however.)

Finally, note that a relationship may also store information in the form of properties in the same way that an object can.

Unlike objects, there are two ways to create a new relationship. First, we can create a new car_ownership relationship via `auto r1 = ptr->try_create_car_ownership(person_a, car_a);`, where person_a and car_a are two objects that have been created earlier. This will return a newly created relationship with the owner set to person_a and the owned car set to car_a, assuming that car_a does not already have an owner. Since cars can participate in at most one ownership relation, a new relationship involving car_a could not be created without changing something else, and in such a case `try_create_car_ownership` will return a handle that is false when cast to a boolean value. The second way to create a new relationship is with `ptr->force_create_car_ownership(person_a, car_a)`. In cases where `try_create_car_ownership` would fail, `force_create_car_ownership` will first set any conflicting links to the invalid handle value. This means that if the car handle appears in any other row in the table of relationships, then the owned_car entry in that row will be modified to contain the invalid handle value.[^2] This ensures that `force_create_car_ownership` can always return a handle to a valid relationship, but it also means that creating a new relationship could result in unexpected changes to other relationships.





[^1]: You should never store real currency values as floating point. This is just for the sake of an example.

[^2]: Actually, since the car would be the primary key for this relationship something slightly different would happen: namely all the other values in that row of the table would be changed to the values passed to `force_create_car_ownership`, since it is not possible to change the primary key value in a row of our imaginary relationship table.