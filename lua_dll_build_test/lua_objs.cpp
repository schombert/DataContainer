//
// This file was automatically generated from: objs.txt
// EDIT AT YOUR OWN RISK; all changes will be lost upon regeneration
// NOT SUITABLE FOR USE IN CRITICAL SOFTWARE WHERE LIVES OR LIVELIHOODS DEPEND ON THE CORRECT OPERATION
//

#define DCON_LUADLL_EXPORTS
#include "lua_objs.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

DCON_LUADLL_API dcon::data_container state;
void (*release_object_function)(int32_t) = nullptr;

void dcon_set_release_object_function(void (*fn)(int32_t)) {
	 release_object_function = fn;
}
bool dcon_thingy_is_valid(int32_t i) {
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 bool result = state.thingy_is_valid(index);
	 return result;
 }
uint32_t dcon_thingy_size() {
	 auto result = state.thingy_size();
	 return result;
 }
void dcon_thingy_resize(uint32_t sz) {
	 state.thingy_resize(sz);
 }
int32_t dcon_thingy_get_some_value(int32_t i) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 return state.thingy_get_some_value(index);
 }
void dcon_thingy_set_some_value(int32_t i,int32_t v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 state.thingy_set_some_value(index, v);
 }
bool dcon_thingy_get_bf_value(int32_t i) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 return state.thingy_get_bf_value(index);
 }
void dcon_thingy_set_bf_value(int32_t i, bool v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 state.thingy_set_bf_value(index, v);
 }
lua_reference_type dcon_thingy_get_lua_value(int32_t i) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 return state.thingy_get_lua_value(index);
 }
void dcon_thingy_set_lua_value(int32_t i,lua_reference_type v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 auto old_val = state.thingy_get_lua_value(index);
	 if(old_val) release_object_function(old_val);
	 state.thingy_set_lua_value(index, v);
 }
int16_t dcon_thingy_get_pooled_v(int32_t i, int32_t idx) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 return state.thingy_get_pooled_v(index).at(uint32_t(idx));
 }
int32_t dcon_thingy_size_pooled_v(int32_t i) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 return int32_t(state.thingy_get_pooled_v(index).size());
 }
void dcon_thingy_set_pooled_v(int32_t i, int32_t idx,int16_t v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 state.thingy_get_pooled_v(index).at(uint32_t(idx)) = v;
 }
void dcon_thingy_resize_pooled_v(int32_t i, int32_t sz) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 state.thingy_get_pooled_v(index).resize(uint32_t(sz));
 }
float dcon_thingy_get_big_array(int32_t i, int32_t idx) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 auto sub_index = dcon::thingy_id{dcon::thingy_id::value_base_t(idx)};
	 return state.thingy_get_big_array(index, sub_index);
 }
void dcon_thingy_set_big_array(int32_t i, int32_t idx,float v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 auto sub_index = dcon::thingy_id{dcon::thingy_id::value_base_t(idx)};
	 state.thingy_set_big_array(index, sub_index, v);
 }
uint32_t dcon_thingy_get_big_array_size() { 
	 return state.thingy_get_big_array_size();
 }
void dcon_thingy_resize_big_array(uint32_t sz) { 
	 state.thingy_resize_big_array(sz);
 }
bool dcon_thingy_get_big_array_bf(int32_t i, int32_t idx) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 auto sub_index = int32_t(idx);
	 return state.thingy_get_big_array_bf(index, sub_index);
 }
void dcon_thingy_set_big_array_bf(int32_t i, int32_t idx, bool v) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(i)};
	 auto sub_index = int32_t(idx);
	 state.thingy_set_big_array_bf(index, sub_index, v);
 }
uint32_t dcon_thingy_get_big_array_bf_size() { 
	 return state.thingy_get_big_array_bf_size();
 }
void dcon_thingy_resize_big_array_bf(uint32_t sz) { 
	 state.thingy_resize_big_array_bf(sz);
 }
bool dcon_pop_is_valid(int32_t i) {
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(i)};
	 bool result = state.pop_is_valid(index);
	 return result;
 }
uint32_t dcon_pop_size() {
	 auto result = state.pop_size();
	 return result;
 }
void dcon_pop_resize(uint32_t sz) {
	 state.pop_resize(sz);
 }
int32_t dcon_pop_get_range_negotiation_as_initiator(int32_t i) { 
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(i)};
	 auto rng = state.pop_get_negotiation_as_initiator(index);
	 return int32_t(rng.end() - rng.begin());
 }
int32_t dcon_pop_get_index_negotiation_as_initiator(int32_t i, int32_t subindex) { 
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(i)};
	 auto rng = state.pop_get_negotiation_as_initiator(index);
	 return rng.begin()[subindex].id.index();
 }
int32_t dcon_pop_get_range_negotiation_as_target(int32_t i) { 
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(i)};
	 auto rng = state.pop_get_negotiation_as_target(index);
	 return int32_t(rng.end() - rng.begin());
 }
int32_t dcon_pop_get_index_negotiation_as_target(int32_t i, int32_t subindex) { 
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(i)};
	 auto rng = state.pop_get_negotiation_as_target(index);
	 return rng.begin()[subindex].id.index();
 }
bool dcon_negotiation_is_valid(int32_t i) {
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 bool result = state.negotiation_is_valid(index);
	 return result;
 }
uint32_t dcon_negotiation_size() {
	 auto result = state.negotiation_size();
	 return result;
 }
void dcon_negotiation_resize(uint32_t sz) {
	 state.negotiation_resize(sz);
 }
int32_t dcon_negotiation_get_initiator(int32_t i) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 return state.negotiation_get_initiator(index).index();
 }
void dcon_negotiation_set_initiator(int32_t i, int32_t v) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 state.negotiation_set_initiator(index, dcon::pop_id{dcon::pop_id::value_base_t(v)});
 }
void dcon_negotiation_try_set_initiator(int32_t i, int32_t v) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 state.negotiation_try_set_initiator(index, dcon::pop_id{dcon::pop_id::value_base_t(v)});
 }
int32_t dcon_negotiation_get_target(int32_t i) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 return state.negotiation_get_target(index).index();
 }
void dcon_negotiation_set_target(int32_t i, int32_t v) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 state.negotiation_set_target(index, dcon::pop_id{dcon::pop_id::value_base_t(v)});
 }
void dcon_negotiation_try_set_target(int32_t i, int32_t v) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(i)};
	 state.negotiation_try_set_target(index, dcon::pop_id{dcon::pop_id::value_base_t(v)});
 }

void dcon_pop_back_thingy() { 
	 if(state.thingy_size() > 0) {
		 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(state.thingy_size() - 1)};
		 if(auto result = state.thingy_get_lua_value(index); result != 0) release_object_function(result);
	 state.pop_back_thingy();
	 }
 }
int32_t dcon_create_thingy() { 
	 auto result = state.create_thingy();
	 return result.index();
 }
void dcon_delete_thingy(int32_t j) { 
	 auto index = dcon::thingy_id{dcon::thingy_id::value_base_t(j)};
		 if(auto result = state.thingy_get_lua_value(index); result != 0) release_object_function(result);
	 state.delete_thingy(index);
 }
void dcon_delete_pop(int32_t j) { 
	 auto index = dcon::pop_id{dcon::pop_id::value_base_t(j)};
	 state.delete_pop(index);
 }
int32_t dcon_create_pop() { 
	 auto result = state.create_pop();
	 return result.index();
 }
void dcon_delete_negotiation(int32_t j) { 
	 auto index = dcon::negotiation_id{dcon::negotiation_id::value_base_t(j)};
	 state.delete_negotiation(index);
 }
int32_t dcon_try_create_negotiation(int32_t p1, int32_t p2) { 
	 auto result = state.try_create_negotiation(dcon::pop_id{dcon::pop_id::value_base_t(p1)}, dcon::pop_id{dcon::pop_id::value_base_t(p2)});
	 return result.index();
 }
int32_t dcon_force_create_negotiation(int32_t p1, int32_t p2) { 
	 auto result = state.force_create_negotiation(dcon::pop_id{dcon::pop_id::value_base_t(p1)}, dcon::pop_id{dcon::pop_id::value_base_t(p2)});
	 return result.index();
 }

int32_t dcon_reset() { 
	 state.reset();
	 return 0;
 }
void dcon_store_simple_write_file(char const* name) { 
	 std::ofstream file_out(name, std::ios::binary);
	 dcon::load_record selection = state.make_serialize_record_store_simple();
	 auto sz = state.serialize_size(selection);
	 std::byte* temp_buffer = new std::byte[sz];
	 auto ptr = temp_buffer;
	 state.serialize(ptr, selection); 
	 file_out.write((char*)temp_buffer, sz);
	 delete[] temp_buffer;
 }
void dcon_store_simple_read_file(char const* name) { 
	 std::ifstream file_in(name, std::ios::binary);
	 file_in.unsetf(std::ios::skipws);
	 file_in.seekg(0, std::ios::end);
	 auto sz = file_in.tellg();
	 file_in.seekg(0, std::ios::beg);
	 std::vector<unsigned char> vec;
	 vec.reserve(sz);
	 vec.insert(vec.begin(), std::istream_iterator<unsigned char>(file_in),  std::istream_iterator<unsigned char>());
	 std::byte const* ptr = (std::byte const*)(vec.data());
	 dcon::load_record loaded;
	 dcon::load_record selection = state.make_serialize_record_store_simple();
	 state.deserialize(ptr, ptr + sz, loaded, selection); 
 }

