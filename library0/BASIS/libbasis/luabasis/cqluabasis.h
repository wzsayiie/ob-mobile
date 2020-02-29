#pragma once

#include "cqcbasis.h"

cq_struct(lua_State);
typedef int32_t (*lua_CFunction)(lua_State *);

CQ_C_LINK void cq_lua_register_tab (const char *tab, const char *base);
CQ_C_LINK void cq_lua_register_func(const char *tab, const char *func, lua_CFunction ptr);
CQ_C_LINK void cq_lua_do_string    (const char *str);

CQ_C_LINK bool        cq_lua_check_bool   (lua_State *state, int32_t index);
CQ_C_LINK int8_t      cq_lua_check_int8   (lua_State *state, int32_t index);
CQ_C_LINK int16_t     cq_lua_check_int16  (lua_State *state, int32_t index);
CQ_C_LINK int32_t     cq_lua_check_int32  (lua_State *state, int32_t index);
CQ_C_LINK int64_t     cq_lua_check_int64  (lua_State *state, int32_t index);
CQ_C_LINK float       cq_lua_check_float  (lua_State *state, int32_t index);
CQ_C_LINK double      cq_lua_check_double (lua_State *state, int32_t index);
CQ_C_LINK const char *cq_lua_check_string (lua_State *state, int32_t index);
CQ_C_LINK cq_obj     *cq_lua_check_object (lua_State *state, int32_t index);
CQ_C_LINK cq_int64s  *cq_lua_check_int64s (lua_State *state, int32_t index);
CQ_C_LINK cq_strings *cq_lua_check_strings(lua_State *state, int32_t index);
CQ_C_LINK cq_ss_map  *cq_lua_check_ss_map (lua_State *state, int32_t index);

CQ_C_LINK int32_t cq_lua_return_void   (lua_State *state);
CQ_C_LINK int32_t cq_lua_return_bool   (lua_State *state, bool        value);
CQ_C_LINK int32_t cq_lua_return_int8   (lua_State *state, int8_t      value);
CQ_C_LINK int32_t cq_lua_return_int16  (lua_State *state, int16_t     value);
CQ_C_LINK int32_t cq_lua_return_int32  (lua_State *state, int32_t     value);
CQ_C_LINK int32_t cq_lua_return_int64  (lua_State *state, int64_t     value);
CQ_C_LINK int32_t cq_lua_return_float  (lua_State *state, float       value);
CQ_C_LINK int32_t cq_lua_return_double (lua_State *state, double      value);
CQ_C_LINK int32_t cq_lua_return_string (lua_State *state, const char *value);
CQ_C_LINK int32_t cq_lua_return_object (lua_State *state, cq_obj     *value);

CQ_C_LINK int32_t cq_lua_return_int64s (lua_State *state, cq_int64s_sender  f, cq_int64s  *v);
CQ_C_LINK int32_t cq_lua_return_strings(lua_State *state, cq_strings_sender f, cq_strings *v);
CQ_C_LINK int32_t cq_lua_return_ss_map (lua_State *state, cq_ss_map_sender  f, cq_ss_map  *v);

//host need set these handlers ->

cq_struct(_cq_lua_handlers) {
    
    void (*register_tab )(const char *tab, const char *base);
    void (*register_func)(const char *tab, const char *func, lua_CFunction ptr);
    void (*do_string    )(const char *str);
    
    int64_t     (*check_integer )(lua_State *state, int32_t index);
    double      (*check_double  )(lua_State *state, int32_t index);
    const char *(*check_string  )(lua_State *state, int32_t index);
    cq_obj     *(*check_object  )(lua_State *state, int32_t index);
    cq_int64s  *(*check_integers)(lua_State *state, int32_t index);
    cq_strings *(*check_strings )(lua_State *state, int32_t index);
    cq_ss_map  *(*check_ss_table)(lua_State *state, int32_t index);
    
    void (*push_bool    )(lua_State *state, bool        value);
    void (*push_integer )(lua_State *state, int64_t     value);
    void (*push_double  )(lua_State *state, double      value);
    void (*push_string  )(lua_State *state, const char *value);
    void (*push_object  )(lua_State *state, cq_obj     *value);
    
    void (*push_integers)(lua_State *state, cq_int64s_sender  f, cq_int64s  *v);
    void (*push_strings )(lua_State *state, cq_strings_sender f, cq_strings *v);
    void (*push_ss_table)(lua_State *state, cq_ss_map_sender  f, cq_ss_map  *v);
};

CQ_C_LINK void _cq_lua_set_handlers(_cq_lua_handlers *handlers);
