#include "color_container.hpp"

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


void dcon::data_container::deserialize_rgb(std::byte const* start, std::byte const* end, load_record& record_in_out) {
	if(!record_in_out.colored_thing_color) {
		float const* found_red = nullptr;
		float const* found_green = nullptr;
		float const* found_blue = nullptr;
		uint32_t smallest_count = colored_thing_size();

		for_each_record(start, end,
			[&](dcon::record_header const& header, std::byte const* data_start, std::byte const* data_end) {
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
			for_each_colored_thing([&](auto id) {
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