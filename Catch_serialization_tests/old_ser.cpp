#include "old_ser.hpp"

uint64_t os::data_container::serialize_size(std::vector<float> const& obj) const {
	return sizeof(uint16_t) + sizeof(float) * obj.size();
}

void  os::data_container::serialize(std::byte*& output_buffer, std::vector<float> const& obj) const {
	*reinterpret_cast<uint16_t*>(output_buffer) = uint16_t(obj.size());
	output_buffer += sizeof(uint16_t);
	std::memcpy(output_buffer, obj.data(), sizeof(float) * obj.size());
	output_buffer += sizeof(float) * obj.size();
}

void  os::data_container::deserialize(std::byte const*& input_buffer, std::vector<float> & obj, std::byte const* end) const {
	uint16_t sz = input_buffer  + sizeof(uint16_t) <= end  ? 
		*reinterpret_cast<uint16_t const*>(input_buffer) : 0;
	obj.resize(sz);
	input_buffer += sizeof(uint16_t);
	std::memcpy(obj.data(), input_buffer, std::min(sizeof(float) * sz, size_t(end - input_buffer)));
	input_buffer += sizeof(float) * sz;
}