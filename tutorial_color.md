# Tutorial: integrating a color struct

## Motivation

It is common to store a color as three values for red, green, blue. Let us say that you are storing the three color components as three floating point values. There is a good argument to be made that most operations on a color will want all three of those values at once, and if you don't plan on applying SIMD operations to colors, you would probably want the three color components to exist in adjacent memory locations so that they will be pulled into the cache together. This tutorial will cover how to accomplish this, and how the transition from an earlier version where the values were stored separately can be made less painful.

The code for this tutorial can be found in `Catch_color_tutorial_tests`.

## The basics

First you must define a class or structure that will hold the three color values. In our example this will be defined in `color_tutorial.hpp` as:

```
struct rgb_color {
	float red = 0.0f;
	float green  = 0.0f;
	float blue = 0.0f;
};
```

Then in our data container definition file `color_container.txt` we can write the following:

```
include{"color_tutorial.hpp"}

object{
	name{colored_thing}
	size{3000}
	storage_type{contiguous}
	
	property {
		name{color}
		type{rgb_color}
	}
}
```

If `handle` is a fat handle (of type `colored_thing_fat_id`) we can access the members of the `rgb_color` struct with expressions such as `handle.get_color().red`.

## Upgrading

Let us further suppose that `colored` thing used to have three `red`, `green`, and `blue` properties. To make the transition easier, we can create member functions that will expose getters and setters that look like the old ones for the `red`, `green`, and `blue` properties when accessed through a fat handle.

We do this by first making the following additions to the object definition:

```
object{
	name{colored_thing}
	size{3000}
	storage_type{contiguous}
	
	property {
		name{color}
		type{rgb_color}
	}
	
	function{void @set_red(float @value)}
	function{void @set_green(float @value)}
	function{void @set_blue(float @value)}
	const_function{float @get_red()}
	const_function{float @get_green()}
	const_function{float @get_blue()}
}
```

Then we add definitions for these functions in a `color_container.cpp` that we create (and which the generator will not touch).

```
void dcon::colored_thing_fat_id::set_red(float value) {
	get_color().red = value;
}
void dcon::colored_thing_fat_id::set_green(float value) {
	get_color().green = value;
}
void dcon::colored_thing_fat_id::set_blue(float value) {
	get_color().blue = value;
}
float dcon::colored_thing_const_fat_id::get_red() {
	return get_color().red;
}
float dcon::colored_thing_const_fat_id::get_green() {
	return get_color().green;
}
float dcon::colored_thing_const_fat_id::get_blue() {
	return get_color().blue;
}
```

And now statements such as `handle.set_red(0.0f);` written under the old definition will continue to work.

We would also need to update how we deserialize data written by the old version. Unfortunately, since we aren't converting a single property to a single property, we can't lean on the built in type-conversion facilities. Let us assume that we call the deserialize function as follows:

```
load_record record_out;
std::byte const* position = start;
ptr->deserialize(position, end, record_out);
```

What we need to do is first add a check to see if the color information has failed to deserialize. If it hasn't, we can then scan the records present in the data looking for the red, green, and blue values that an old version might have written out. And if we find them, then we can populate the new `rgb_color` structs with them. To promote better code organization, we will also sequester the logic to do this inside a new member function of the data container.

So first we add the line `global{void deserialize_rgb(std::byte const* start, std::byte const* end, load_record& record_in_out);}` to the data container definition file, which declares our new member function.

Then we add the following to the `color_container.cpp` file:

```
void dcon::data_container::deserialize_rgb(std::byte const* start, std::byte const* end, load_record& record_in_out) {
	if(!record_in_out.colored_thing_color) {
		float const* found_red = nullptr;
		float const* found_green = nullptr;
		float const* found_blue = nullptr;
		uint32_t smallest_count = colored_thing_size();
		
		for_each_record(start, end, 
			[&](dcon::record_header const& header, std::byte const* data_start, std::byte const* data_end){
				if(header.is_object("colored_thing") && header.is_type("float")) {
					if(header.is_property("red")) {
						found_red = reinterpret_cast<float const*>(data_start);
						smallest_count = std::min(smallest_count, uint32_t((data_end - data_start) / sizeof(float)));
					} else if(header.is_property("green")) {
						found_green = reinterpret_cast<float const*>(data_start);
						smallest_count = std::min(smallest_count, uint32_t((data_end - data_start) / sizeof(float)));
					} else if(header.is_property("blue")) {
						found_blue = reinterpret_cast<float const*>(data_start);
						smallest_count = std::min(smallest_count, uint32_t((data_end - data_start) / sizeof(float)));
					}
				}
			});
		if(found_red && found_green && found_blue) {
			for_each_colored_thing([&](auto id){
				if(id.index() < int32_t(smallest_count)) {
					colored_thing_set_color(id,
						rgb_color{ found_red[id.index()], found_green[id.index()], found_blue[id.index()]
					});
				}
			});
			record_in_out.colored_thing_color = true;
		}
	}
}
```

Finally, we call this new function in addition to the old deserialization routine:

```
load_record record_out;
std::byte const* position = start;
ptr->deserialize(position, end, record_out);
ptr->deserialize_rgb(start, end, record_out);

```

Note that there is some extra complexity here to check for the possibility of an incomplete data source (i.e. where one or more of the colors has had less information serialized than is necessary to fill all of the color values) and to make sure that we don't read outside the memory contained in each record. If you know for sure that you will never encounter incomplete records, then a lot of the complexity in the above example can be removed.

## SIMD integration

Putting the red, green, and blue values into their own struct does not prevent them from being used in a SIMD operation altogether, it merely makes accessing and storing those values less efficient. *If* there is enough work being done, writing a SIMD operation for those values may still be the best approach. (This is probably not the case for the example below).

Let us suppose that we had a SIMD operation that set all the blue values to the average of the red and green values as follows:

```
ptr->execute_serial_over_colored_thing([p = ptr.get()](auto position){
	p->colored_thing_set_blue(position,
		(p->colored_thing_get_red(position) + p->colored_thing_get_green(position)) / 2.0f);
});
```

(Note, that we can't use the nice syntax inside a SIMD operation, unfortunately)

We can translate this operation to work on the new design by using `ve::apply` to gather the desired values from the new struct and to store the result as follows:

```
ptr->execute_serial_over_colored_thing([p = ptr.get()](auto position){
	auto red_value = ve::apply(
		[p](dcon::colored_thing_id i){ return p->colored_thing_get_color(i).red; },
		position);
	auto green_value = ve::apply(
		[p](dcon::colored_thing_id i){ return p->colored_thing_get_color(i).green; },
		position);
	ve::apply(
		[p](dcon::colored_thing_id i, float v){ p->colored_thing_get_color(i).blue = v; },
		position, (red_value + green_value) / 2.0f);
});
```

Yes, this is significantly more verbose, but in cases where making this translation is reasonable, i.e. in cases where the operation is doing much more work than just loading and storing the values, the increase will be a much smaller proportion of the total length of the function.
