# Queries

## Contents

This document describes how to define LINQ-esque / SQL-esque queries and how to take advantage of them in your C++ code. Queries are intended primarily as a convenience feature rather than a high-performance feature. They do not currently expose any SIMD vectorization features, and there are a number of possible performance pitfalls (see [Performance considerations](#performance-considerations) below).

## Overview

A query allows you to turn a single logical construct that is spread out over multiple objects and relationships into something that you can manipulate as if it was its own distinct object within your data container.

For example, suppose that your data container contains people who may own one or more cars via a relationship of car-ownership as depicted below:

```
┌────────┐  many   ┌───────────────┐  unique   ┌───────┐ 
│ person ├─────────┤ car-ownership ├───────────┤  car  │
╞════════╡  owner  └───────────────┘ owned-car ╞═══════╡
│  age   │                                     │ value │
└────────┘                                     └───────┘
```

Each combination of person combined with a car that they own can be thought of as a single logical entity, one that has both the properties of having an age (the age of the owner) and value (the value of the owned car). A query can allow you to iterate over the these person-owned car combinations *as if* they were their own object within your data container.

Admittedly, the example given above is not very useful, practically speaking. You could simply iterate over the car-ownership relations, and trivially look up the associated person and car as needed. But queries are not limited to such simple examples. Consider the connection between objects depicted below:

```
         x2, distinct, many
     ┌─────────────────────────┐
┌────┴───┐     parent          │
│ person │               ┌─────┴─────┐
╞════════╡               │ parentage │
│  age   │               └─────┬─────┘ 
└────┬───┘     unique          │
     └─────────────────────────┘
               child
```

Here parentage relationships link each person with two (biological) parents. Even though there is only one object and one relationship in this diagram, there are many logical objects that we could construct from it. For example, We could start from a person, move through the parentage relationship to find a parent, and then move through the parentage relationship again to find a grandparent. Thus there is a logical object consisting of tuples of person-parent-grandparent implicit in this structure. And a query can allow you to iterate over those tuples effortlessly, without either the nested loops or the conditional logic for detecting people without parents or parents without grandparents that would be required if you were expressing that iteration manually.

## Defining a query

A query is defined by adding a `query{...}` key at the top level of the file. Like objects and relationships, the details of the query are determined by a number of sub keys that appear within it.

### Name

Again, like objects and relationships, each query definition must contain a `name{...}` sub-key, itself containing a valid C++ identifier.

### Parameters

A query definition may also contain a `parameters{...}` sub-key. This sub-key must itself consist of a sequence of `name{type}` sub-keys. Each of these sub-sub-keys results in a named parameter (named by `name`) of type `type` that must be provided when you ask for an instance of the query. These parameters allow you to filter the results of the query using them, which allows you to reuse the same query definition with variations on its filters determined at run time (see [Where clause](#where-clause) below). 

### Select statement

The last, and most important sub-key is `select{...}`. The parameter for this key defines the logic of the query, and its contents and format are the bulk of the remainder of this document.

### Usage

Once a query has been defined and the generator has been run, you can access it through the `query_𝘲𝘶𝘦𝘳𝘺 𝘯𝘢𝘮𝘦` function provided by the data container. This function takes as its parameters then parameters you have defined for the query and returns an instance of the query. On this instance you can call the `begin()` and `end()` functions to obtain a pair of (very limited) iterators that allow you to step through the logical items contained in the query. The intended usage is something like the following:

```
for(auto& item_in_query : ptr->query_𝘲𝘶𝘦𝘳𝘺 𝘯𝘢𝘮𝘦(𝘱𝘢𝘳𝘢𝘮𝘦𝘵𝘦𝘳𝘴)) {
	𝘤𝘢𝘭𝘭 𝘮𝘦𝘮𝘣𝘦𝘳 𝘧𝘶𝘯𝘤𝘵𝘪𝘰𝘯𝘴 𝘰𝘧 item_in_query 𝘩𝘦𝘳𝘦
}
```

## Selected values

Each select statement begins with a list or one or more values that the query should make accessible as part of the logical object that it implicitly constructs. These values will be made available through `get_...` and `set_...` functions. In the example above, for instance, one could call `item_in_query.get_...` to access one of them.

Specifically the select statement begins with `name, name, ... from ...`, with each name being a value to expose and the word `from` ending the list and beginning the [from clause](#from-clause). Strictly speaking, the commas are optional, but I find that they help readability.

Each name may be a single term (a single valid C++ identifier, so no internal spaces or punctuation). If so, then it will expose a property or link with that name from one of the involved object or relationship types in the query. And if the name is `id`, it will expose the handle to one of the objects or relationships involved in the query.

Since a different objects and relationships may have properties and / or links with the same name (not to mention the use of `id` or the fact that the same type of object or relationship may appear multiple times in a query) it may be necessary to disambiguate which value exactly you mean to expose. You can do this be prefixing a name with `𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦.` where 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 is the reference name of some type of object or relationship as defined in the from clause (see below).

### Reference names

Finally, you may want to control the name under which an exposed value appears as. By default if `X` appears as a selected value then the functions `get_X` and `set_X` will be generated. If X needs to be disambiguated as `W.X`, then the function `get_W_X` and `set_W_X` will be generated. And if those defaults are undesirable, you can follow a name in a select statement with `as 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦`. For a name followed by an `as` suffix, the functions `get_𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦` and `set_𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦` will be generated.

## From clause

The from clause is the heart of the query, and describes the structure of the logical object that the query is constructing from the objects and relationships managed by the data container. A simple from clause may look like the following: `... from name, join name, join name, ...` Each of the names denotes an object or relationship that is to be joined together in the query. In the simplest queries each name after the first is preceded by the word `join` (and optionally a comma for clarity) and must be either a relationship that has a link to the preceding object in the from clause or an object where the preceding item in the from clause is a relationship that is linked to it.

For example, if `car_ownership` is a relationship containing a link to a `person` as `owner` and a link to a `car` as `owned_car`, then `... from car, join car_ownership` is a valid from clause, where the join connects the car to car ownership via the `owned_car` link. Such a query would represent the valid `car` and `car_ownership` pairs that can be found in the data container. Another join from car ownership, such as `... from car, join car_ownership, join person` would then represent a logical triple of people related by car ownership to some car. Thus the first example given in the overview could be expressed in a query as `person.age, car.value from car, join car_ownership, join person`, and iterating over it would allow you to operate on all of the person-age and car-value combinations present in the data container.

But what happens if a particular kind of object and relationship are connected by more than one link? For example, a person can be linked to the parentage relationship as either a child or as one of the parents. In this case it is not possible to implicitly determine which link should be used, and so you must add `on 𝘭𝘪𝘯𝘬 𝘯𝘢𝘮𝘦` after the `join` keyword to specify the link. For example, a from clause could contain `person, join on child parentage` to describe the logical pair of people and parentage relationships where they are the child, or it could contain `person, join on parent parentage` describe the logical pair of people and parentage relationships where they are one of the parents.

### Reference names

In more complicated queries, the same kind of object or relationship may need to occur more than once. For example, to capture the logical structure of being a grandparent, the query would need to go through the parentage relationship twice and include the person object three times (such as `... from person, join on child parentage, join on parent person, join on child parentage, join on parent person`). Visually this looks like the following:

```
┌────────┐ child ┌───────────┐ parent ┌────────┐ child ┌───────────┐ parent ┌────────┐
│ person ├───────┤ parentage ├────────┤ person ├───────┤ parentage ├────────┤ person │
└────────┘       └───────────┘        └────────┘       └───────────┘        └────────┘
```

The problem becomes how to get the information you want out, because simply referring to `person.id` in the selected values is ambiguous between the selected person, parent, and grandparent. To remedy this, anything introduced in the from clause may be given a reference name, just as selected values can be. This is done by adding an `as 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦` suffix to the name of the object or relationship. This 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦 can then be used to refer that the instance of the object or relationship that fills that specific slot in the logical object constructed by the query. In the case of a query that iterates over grandparents, this could be done as follows: `base.id, grandparent.id from person as base, join on child parentage, join on parent person, join on child parentage, join on parent person as grandparent`. At this point adding additional whitespace also becomes helpful, such as:

```
base.id, grandparent.id
	from person as base,
		join on child parentage, join on parent person,
			join on child parentage, join on parent person as grandparent
```

### How iteration happens within a query

Before we proceed to more complicated variations of the from clause, it is useful to have a basic understanding of how a query iterates through the various combinations of objects and relationships that could constitute one of its logical objects. Take the grandparent example discussed in the previous section and imagine that the query iterator currently holds an instance, meaning that each of its three person slots and two parentage slots are all filled with handles to object and relationship instances that are linked appropriately to each other. To advance this iterator to the next valid combination, it first tries to find the next possible instance of the rightmost item. In our example, since every parentage relationship involves two parents, it would try the second parent if the first parent was currently in the slot. If there are no more candidates, then it moves left one slot and repeats the process. In our example, since each person is the child of exactly one set of parents, there are no other options for a parentage slot, and so the algorithm must immediately move to the left again to look for new options. When some slot is successfully incremented, then every slot to the right of it must be "reset". If in our example the middle person was incremented to the second parent, then the fourth parentage slot and fifth person slot would have to be filled with the appropriate items. If this resetting process fails (for example, if the person is not a child in any parentage relationship), then the algorithm returns to trying to increment some slot. Eventually this process terminates, either with a new, valid combination of objects and relationships, or by running out of possibilities, in which case the iterator will compare equal to the return value of `end()`.

### Starting from a parameter

Since the first item in a from clause is not joined to anything, every object instance is a valid possibility for it, and so a query will eventually try every valid id in that slot. This may be very inefficient if, for example, you want to look at the grandparents of a particular person. For that reason, there is another special option for the first item in the from clause; instead of the name of a type of relationship or object, you may instead write `@name` where `name` is the name of one of the parameters of the query.[^1] This parameter must be of type `𝘵𝘺𝘱𝘦_id` where 𝘵𝘺𝘱𝘦 is the name of some type of relationship or object. Syntactically, the first position in the from clause will then function as if it were declared as 𝘵𝘺𝘱𝘦, but when the query is executed, instead of trying every valid object instance in the first slot, only the provided parameter will be used to fill that slot.

This option is only valid for the first item in a from clause. To limit the instances that may fill the other slots, see [Where clause](#where-clause) below.

### `join+`

As discussed above, cases where there are no linked instances of the item on the right of a join result in the item on the left of a join being skipped when incrementing a query. There may be rare cases in which you still want to see the options in which the right hand side of some join statement could not be filled. In those cases you can replace the word `join` with `join+`, which treats the inability to fill a slot as a valid combination of items. This means that when iterating over a query you could encounter cases in which the slots corresponding to the right hand side of a `join+`, or anything transitively joined through it, are empty, and thus any selected values that come from those items will be returned as if you had accessed them through a handle containing the invalid index.

To test whether any slot is actually filled in a query, or has been left empty by a `join+`, you can call `has_𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦()` for any item in the from clause, which will return true if and only if that slot is populated by a valid option.

Note that, for performance reasons, there are some complications when the link being `join+`ed over is a primary key. Because telling whether a primary key is valid can be slightly expensive, the query iterator will assume that it is valid in most cases. And this typically is not a problem because in an invalid relationship the other links will not go anywhere, and so the possibility will be pruned when it gets to those links. The problem is that, if the primary key relationship isn't seen as invalid, then a `join+` with it will mean the same thing as a `join` and the other invalid links will still cause the possibility to be discarded. The solution to this is simply to mark any subsequent joins out as `join+` as well, and you will get the expected results.

### Non-sequential joins

By default, every item in a from clause is joined to the preceding item. However, that doesn't have to be the case. You can also write a join as `𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦.join`. In this case the item following the join will be joined to the item named by 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦, assuming that it has been defined at some point prior in the from statement.

For example, you could iterate over pair of siblings of a person with a query such as 

```
base.id, sibling_a.id, sibling_b.id
	from @person_param as base,
		join on parent parentage, join on child person as sibling_a,
			base.join on parent parentage, join on child person as sibling_b
```

Visually this would look like the following

```
┌────────┐ parent ┌───────────┐ child ┌─────────┐ 
│ person ├────────┤ parentage ├───────┤ person  │
│   as   │        └───────────┘       │   as    │
│  base  │                            │sibling_a│
└────┬───┘           parent           └─────────┘ ┌───────────┐ child ┌─────────┐
     └────────────────────────────────────────────┤ parentage ├───────┤ person  │
                                                  └───────────┘       │   as    │
                                                                      │sibling_b│
                                                                      └─────────┘
```

Note that the standard rules for incrementing through the possibilities still apply; options are tried from right to left. Thus, after the options for `sibling_b` are tried, eventually a new option will be tried for `sibling_a`, and when that happens everything to the right of it (thus `sibling_b`) will be reset. The ultimate result is that you will see every possible pair of siblings in every order (see below for how to filter the redundant possibilities out, if you wish). Note also that we could not construct this query as a simpler linear one, because to start from a parameter the common parent, `base`, had to come first.

## Where clause

A where clause is optional. If present, it must come after the from clause and before the optional group clause (see [Grouping and aggregates](grouping-and-aggregates) below). A where clause looks like the following: `... where ... @term ... @term ...`. The contents of the where clause must be a valid C++ statement that can evaluate to a boolean true or false once the terms prefixed by `@`s are replaced (as described below). The result of executing this statement will be used to exclude possible results from being seen when you iterate through a query.[^2]

Each term must be in the form of either `@𝘱𝘢𝘳𝘢𝘮𝘦𝘵𝘦𝘳 𝘯𝘢𝘮𝘦`, `@𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦`, or `@𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦.𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦`. In the first case, the term will be replaced by the parameter with the given name. In the second case, the term will be replaced by the selected value that the reference name refers to. The third case is the most general, as it replaces the term with the named property, including named links in relationships and `id`, drawn from the item in the from clause identified by 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦 (which may be the standard name of the object or relationship if no new reference name is assigned with `as`).

For example, the following where clause could be added to the example above to filter out duplicate possibilities with the order reversed or the same person being presented as a sibling to themselves: `where @sibling_a.id .index() < @sibling_b.id .index()`.

In principle, the where clause is totally unnecessary; you could add a conditional within your iteration over the query that would filter out the same results. However, to do so you would have to expose as a value every property that evaluating the filter would require. The advantage of a where clause, then, is that you can refer to anything you want inside it without needing to expose any additional values, which makes the query interface cleaner. Where clauses also allow you to filter the values that go into computing an aggregate (see below).

### `array` type properties

One special exception is made for accessing a property that has a type of `array` inside a where clause. For such properties a `@𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦.𝘱𝘳𝘰𝘱𝘦𝘳𝘵𝘺 𝘯𝘢𝘮𝘦[...]` expression will be replaced by a `get` call where the contents inside the brackets will be passed as the index.

## Grouping and aggregates

The final clause that may appear in a select statement is the optional group clause, which must appear last, after any where clause. The group clause consists of just `... group 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦` where 𝘳𝘦𝘧𝘦𝘳𝘦𝘯𝘤𝘦 𝘯𝘢𝘮𝘦 is any item that appears in the from clause (up to and including a parameter as the first item, which has as its reference name the name of the parameter without any `@`). Since the start of the group clause is determined by the appearance of the word `group`, `group` may not appear within the where clause unless it is enclosed by parentheses (you may enclose the entire contents of the where clause in parentheses if you so wish).

To understand what the group clause does, you must first understand aggregates. An aggregate is, syntactically, an expression that looks like a function call enclosing one of the exposed values of the select statement. For example `count(grandparent.id as gp_id) from ...` (note that the `as` suffix goes inside the parentheses if it is present). Instead of exposing the value from a single instance, the value exposed by an aggregate is instead derived from multiple items as governed by the group clause.

When a group clause is present, instead of advancing through the logical items one by one, the query will instead increment through as many items as it would take to make the value stored in the slot named in the group clause to change. While automatically advancing in this way, the aggregate values are updated based on the instances that are not rejected by the where clause (if any). Thus, when you iterate through a query with a group clause, you will only see the results of the aggregation on values derived from slots to the right of the group slot; exposing any values from those slots is undefined behavior (except in the case of min and max, as described below).

### Count

The `count` aggregate is one of the few built-in aggregates. `count(name)` attached to any value belonging to a slot right of the group slot will return the number of items that were incremented through before the group slot would change. For example, you can use the `count` aggregate to easily compute how many grandchildren a person has by simply using `count(grandchild.id as num_grandchildren)` while grouping by the person to count the grandchildren of. Note that this counts the number of logical items that fall under the group, not the number of times the value in parentheses would change. Also note that, except in very rare cases, the `count` aggregate will not return a result of zero. Zero would mean that no combination of options could complete the logical structure described in the query, and unless instructed otherwise, the query simply steps over such cases, and there is no opportunity for zero to be reported at all.

### Min and max

Min and max (as well as `std::min` and `std::max`) also have built-in special handling. First, they function as you might expect, with such aggregates yielding the least or greatest value seen while iterating over the group (as determined by a `<` comparison). However, unlike all other aggregates, if a min or max aggregate is present then any exposed values from slots to the right of the group slot have a special meaning. Instead of being undefined behavior to access, those values will instead be the values drawn from the logical item that had the greatest or least value returned by the aggregate (and in the case of ties, the first seen).

### Custom aggregates

Any other valid C++ identifier enclosing an exposed value will be assumed to be a custom aggregate. A custom aggregate works as follows: If only a single logical item falls under the group, then the values for that item will be stored without alteration as the aggregate value. When there are two or more logical items in the group then the aggregate will be calculated by calling for each item after the first the named function with the previous value stored in the aggregate and the new value from the item as parameters and then storing the result back as the value for the aggregate. Thus it is easy to write, for example, a sum function that you can use to calculate totals over a group.

## Performance considerations

As mentioned in the introduction, queries are not a high-performance feature. This is not a full-featured database and there is no clever query planner that will dynamically optimize your query based on current conditions. And making complicated queries perform well may require clever caching and updating of data and indexes into it that the query interface does not support. However, there are some things you can still do to get better performance out of your queries, or at least to avoid really bad performance.

### `unindexed` links

Joining an object and a relationship via an `unindexed` link is supported by the query interface. However, if the query has to look up the relationship containing the `unindexed` link from the object that it references, it must do so by searching through all the relationship instances, which is extremely inefficient. To avoid this you must either ensure that the relationship containing the `unindexed` link occurs to the *left*  in the from clause of any object joined to it by that link.

### `many` links

Similarly, there is a small performance benefit to having the relationship to the *left* of the object it is joined to when it is joined though a `many` link. Sometimes you can achieve this by a technique I think of a "folding" the query. Suppose that you wanted to query all the pair of nodes connected by an edge define as follows:

```
relationship {
	name{edge}
	...
	link{
		object{node}
		name{connected_node}
		type{many}
		index_storage{array}
		multiple{2}
	}
	...
}
```

One way to do this would be to write `... from node as left, join edge, join node as right`. This would create something looking like the diagram below:

```
┌──────┐      ┌──────┐      ┌──────┐ 
│ node ├──────┤ edge ├──────┤ node │
└──────┘      └──────┘      └──────┘
```

To put both nodes on the right side of the edge relationship, you could instead express the from statement as `... from edge, join node as left, edge.join node as right`. This folds the diagram over the central item, producing something like the following:

```
┌──────┐      ┌──────┐ 
│ edge ├──────┤ node │
└──┬───┘      └──────┘      ┌──────┐
   └────────────────────────┤ node │
                            └──────┘
```

### Starting from the smallest

Another way to help minimize the running time of a query is to try to pick as the leftmost item in the from statement a type of object or relationship that you estimate will have significantly fewer instances than the other items. For example, if you are looking at people and their parents, but you also know that the relationship of parentage has not been defined for most of the people in your data set, then starting a query with a person will probably be inefficient. Since most people won't be linked to any parentage relationship, the query will waste time considering people for the first slot only to discard them for not having parents/children. In such a situation it would be more efficient to begin the from statement with a parentage relationship (by folding it if necessary) so that the unconnected people never have to be looked at in the first place.

### Hidden complexity

It is also important to understand that, while a query may be relatively simple to write, every time it passes through a link of type `many` or with multiplicity greater than one, the query will ultimately be looking at multiple combinations for each item considered for the leftmost slot. Considering 4 combinations per person (for looking at grandparent, for example) may be manageable, but a hastily written query can easily result in an infeasible number of combinations per base object, so try to keep in mind what the execution of the query will require when you write it.

[^1]: The `@` is because the syntax allows the parameters to be declared after the select statement, and so some way is needed to identify what is the name of a parameter without drawing upon a list of those parameters.

[^2]: As an extra trick, you can access anything from the data container itself via `m_container` which is a reference to the data container that will be visible at the point where the where clause is executed.