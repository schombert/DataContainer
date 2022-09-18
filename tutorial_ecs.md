# Tutorial: making a data container act like an ECS

The code for this tutorial can be found in `Catch_ecs_tutorial_tests`.

## Motivation

To be clear, some of the things discussed in this tutorial are bad ideas, and it is worth explaining why. The data container exists in more or less the same design space as an ECS. Both aim to give you better performance by providing efficient ways of organizing data in memory that C++ does not directly support via its language constructs. An ECS does this by grouping components (typically expressed as small structs) together in memory, under the idea that the prefetcher will automatically grab nearby components, giving you better performance when you iterate over them. A data container does the same thing, but with greater granularity: it groups property values together in memory so that, when you access a value, the prefetcher will automatically grab the values for nearby objects. This increased granularity means that you don't have to worry about dividing your data into the right components. An ECS works best when your algorithm uses every value in the components it iterates over, as not using one or more values means that you pay the cost of fetching them without benefiting from it (and it also consumes cache space, potentially pushing out values you do need). But you may very well iterate over the same component in different algorithms, and so it may be impossible to avoid some wasted fetching. This problem is avoided completely in a data container; the prefetcher will only grab the values that the algorithm is using as it iterates over objects, and this happens automatically so you don't need to make any decisions about how to group properties together (which means both that you can't make the wrong decision and that changing how your algorithms work doesn't require you to restructure your data). So slicing objects into components will complicate your design unnecessarily.

Both an ECS and a data container struggle to some degree with polymorphism. An ECS approximates polymorphism by treating different combinations of components as different kinds of objects. This approach can work in a data container as well (see the contents of the tutorial for how to implement it), but a data container also offers more granularity in this respect. Rather than a single entity that may bear any combination of components, it is more natural to have different types of objects that may each bear a more limited, and more appropriate, set of optional components. So while an ECS is fundamentally built around a single base class, the entity, that can be essentially anything, a data container supports more strongly typed inheritance schemes.

## The entity and its components

Putting those caveats aside, let us get down to the business of creating an ECS out of a data container. The first thing to make, then, is an entity that we can attach components to. You could make the entity an object with no properties, but I think it is better to just cut right to the chase: conceptually an entity is simply a collection of components, and that means it is simply a relationship between components, so why not make it just a relationship?[^1]

```
relationship {
	name{entity}
	size{3000}
	storage_type{erasable}
	
	...
}
```

The choice of erasable storage reflects the typical implementation of an ECS, which manage empty slots in their arrays with a free list.

Next we will need some components to attach to our entities. Following the standard ECS tutorial, we introduce the following

```
object {
	name{position}
	size{3000}
	storage_type{erasable}
	
	property{
		name{x}
		type{float}
	}
	property{
		name{y}
		type{float}
	}
	property{
		name{rotation}
		type{float}
	}
}

object {
	name{sprite}
	size{3000}
	storage_type{erasable}
	
	property{
		name{sprite_id}
		type{uint16_t}
	}
}
```

Your typical ECS tutorial might store the position as a vector of two floats (such as in a `vector2f`). If you have read the documentation, you know that the data container supports this as well. However, leaving the position components as independent properties makes them directly accessible to SIMD operations, and they are extremely obvious targets for such operations.

Finally, we have to make sure that our entity can be optionally connected to these components. We do this by adding one optional link per component, which is of type `unique` since each component can be attached only to a single entity.

```
relationship {
	name{entity}
	size{3000}
	storage_type{erasable}
	
	link{
		object{position}
		name{position_component}
		type{unique}{optional}
	}
	link{
		object{sprite}
		name{sprite_component}
		type{unique}{optional}
	}
}
```

### Constructor and destructor

To make entities more user friendly, it is nice to wrap their creation in a small factory function.

```
dcon::entity_id make_entity(dcon::data_container& dc) {
	return dc.try_create_entity(dcon::position_id(), dcon::sprite_id());
}
```

Note that we have to feed one empty component id to `try_create` for each entity, so having a factory function reduces repetition and makes it easier to add or remove components from the design later.

We also need to handle deleting components. The standard `delete_entity` function works, of course, but may leave you with dangling components (i.e. components that outlive the entity that they belonged to). There are two ways to handle this. Here we will choose the "clever" way of adding `hook{delete}` to the definition of our entity relationship, and then define the following function:

```
void dcon::data_container::on_delete_entity(entity_id e) {
	if(auto c = entity_get_position_component(e); bool(c)) {
		delete_position(c);
	}
	if(auto c = entity_get_sprite_component(e); bool(c)) {
		delete_sprite(c);
	}
}
```

Again, this would have to be expanded for every component added. This method, however, is somewhat fragile. It works here because each of the components are linked optionally. If they were not optional, then deleting the component would result in deleting the relationship, which would call the on_delete function again, which would lead to an infinite loop (not to mention deleting the same relationship multiple times, which would also put the data container in an invalid state). In that case, we would have to make a function that is the opposite of our factory function to handle deletion.[^2] In that function we would first make a local copy of all the components in the relationship, then we would delete the relationship, and then we would delete each of the components.

## A "system"

In the terminology of an ECS, a system is a routine for iterating over, and executing an update on, all of the entities containing some collection of components. If we want to iterate over a single component, then the data container already provides us with `for_each_position` and `for_each_sprite`, so there is nothing more to do. But if you want to iterate over entities with some combination of components, it is simple as writing a query, such as:

```
query{
	name{sprites_with_position}
	select{sprite.id as sprite, position.id as position
		from sprite, join entity, join position}
}
```

This query will expose handles to pairs of sprites and positions that are components for the same entity. We can thus operate on the sprites with positions as simply as:

```
for(auto& q : container.query_sprites_with_position()) {
	// do something with q.get_sprite() and q.get_position()
}
```

As always with queries, it is often worth thinking a bit about how to optimize their performance. In this case there are two factors to consider. First, starting with the component that you expect there to be the least of will result in the fewest iterations. However, it is also the case that, even if the query skips as many as three fourths of the components, the prefetcher will help you with the values from the first component in the query and none of the others (because the ids from the other components may come in any order, while those of the first component will be looked at in a strictly increasing order). Thus you could also argue that the best performance will come from starting with the component that you manipulate the most data from. As with all things performance related, the only thing you can really do is measure.

And now,
![](iamtheecs.jpg)

[^1]: There is one good reason not to make it a relationship: if you wanted to support relationships between entities then the entity would have to be an object, and the relationship that connected the components would use that entity object as its primary key. We aren't doing that here for two reasons: 1) it makes our simple tutorial less simple 2) it is also a valid design decision to make relationships only between the components, as relating entities means relating generic "it could be anything" objects. For example, if some entities have spatial extent (are regions), it may make sense to relate the component describing the spatial extent to the position component (in a relationship of is-inside-of), but it makes less sense to involve entities without location in this relationship.

[^2]: What is the opposite of a factory?