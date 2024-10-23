#pragma once

//
// This file was automatically generated from: objs.txt
// EDIT AT YOUR OWN RISK; all changes will be lost upon regeneration
// NOT SUITABLE FOR USE IN CRITICAL SOFTWARE WHERE LIVES OR LIVELIHOODS DEPEND ON THE CORRECT OPERATION
//

#include <stdint.h>
using lua_reference_type = int32_t;
#include "objs.hpp"
#ifdef DCON_LUADLL_EXPORTS
#define DCON_LUADLL_API __declspec(dllexport)
#else
#define DCON_LUADLL_API __declspec(dllimport)
#endif

extern DCON_LUADLL_API dcon::data_container state;

extern "C" {
DCON_LUADLL_API void dcon_set_release_object_function(void (*fn)(int32_t));
DCON_LUADLL_API bool dcon_thingy_is_valid(int32_t i);
DCON_LUADLL_API uint32_t dcon_thingy_size();
DCON_LUADLL_API void dcon_thingy_resize(uint32_t sz);
DCON_LUADLL_API int32_t dcon_thingy_get_some_value(int32_t i); 
DCON_LUADLL_API void dcon_thingy_set_some_value(int32_t i,int32_t v); 
DCON_LUADLL_API bool dcon_thingy_get_bf_value(int32_t i); 
DCON_LUADLL_API void dcon_thingy_set_bf_value(int32_t i, bool v); 
DCON_LUADLL_API lua_reference_type dcon_thingy_get_lua_value(int32_t i); 
DCON_LUADLL_API void dcon_thingy_set_lua_value(int32_t i,lua_reference_type v); 
DCON_LUADLL_API int16_t dcon_thingy_get_pooled_v(int32_t i, int32_t idx); 
DCON_LUADLL_API int32_t dcon_thingy_size_pooled_v(int32_t i); 
DCON_LUADLL_API void dcon_thingy_set_pooled_v(int32_t i, int32_t idx,int16_t v); 
DCON_LUADLL_API void dcon_thingy_resize_pooled_v(int32_t i, int32_t sz); 
DCON_LUADLL_API float dcon_thingy_get_big_array(int32_t i, int32_t idx); 
DCON_LUADLL_API void dcon_thingy_set_big_array(int32_t i, int32_t idx,float v); 
DCON_LUADLL_API uint32_t dcon_thingy_get_big_array_size(); 
DCON_LUADLL_API void dcon_thingy_resize_big_array(uint32_t sz); 
DCON_LUADLL_API bool dcon_thingy_get_big_array_bf(int32_t i, int32_t idx); 
DCON_LUADLL_API void dcon_thingy_set_big_array_bf(int32_t i, int32_t idx, bool v); 
DCON_LUADLL_API uint32_t dcon_thingy_get_big_array_bf_size(); 
DCON_LUADLL_API void dcon_thingy_resize_big_array_bf(uint32_t sz); 
DCON_LUADLL_API bool dcon_pop_is_valid(int32_t i);
DCON_LUADLL_API uint32_t dcon_pop_size();
DCON_LUADLL_API void dcon_pop_resize(uint32_t sz);
DCON_LUADLL_API bool dcon_negotiation_is_valid(int32_t i);
DCON_LUADLL_API uint32_t dcon_negotiation_size();
DCON_LUADLL_API void dcon_negotiation_resize(uint32_t sz);
DCON_LUADLL_API int32_t dcon_negotiation_get_initiator(int32_t i); 
DCON_LUADLL_API void dcon_negotiation_set_initiator(int32_t i, int32_t v); 
DCON_LUADLL_API void dcon_negotiation_try_set_initiator(int32_t i, int32_t v); 
DCON_LUADLL_API int32_t dcon_negotiation_get_target(int32_t i); 
DCON_LUADLL_API void dcon_negotiation_set_target(int32_t i, int32_t v); 
DCON_LUADLL_API void dcon_negotiation_try_set_target(int32_t i, int32_t v); 
DCON_LUADLL_API void dcon_pop_back_thingy(); 
DCON_LUADLL_API int32_t dcon_create_thingy(); 
DCON_LUADLL_API void dcon_delete_thingy(int32_t j); 
DCON_LUADLL_API void dcon_delete_pop(int32_t j); 
DCON_LUADLL_API int32_t dcon_create_pop(); 
DCON_LUADLL_API void dcon_delete_negotiation(int32_t j); 
DCON_LUADLL_API int32_t dcon_try_create_negotiation(int32_t p1, int32_t p2); 
DCON_LUADLL_API int32_t dcon_force_create_negotiation(int32_t p1, int32_t p2); 
DCON_LUADLL_API int32_t dcon_reset(); 
DCON_LUADLL_API void dcon_store_simple_write_file(char const* name); 
DCON_LUADLL_API void dcon_store_simple_read_file(char const* name); 
}
