#ifndef HAVE_UBJS_OBJECTS
#define HAVE_UBJS_OBJECTS

#include "ubjs_common.h"

typedef struct ubjs_object ubjs_object;

struct ubjs_object;

ubjs_object *ubjs_object_null();
ubjs_result ubjs_object_is_null(ubjs_object *, ubjs_bool *);

ubjs_object *ubjs_object_noop();
ubjs_result ubjs_object_is_noop(ubjs_object *, ubjs_bool *);

ubjs_object *ubjs_object_true();
ubjs_result ubjs_object_is_true(ubjs_object *, ubjs_bool *);

ubjs_object *ubjs_object_false();
ubjs_result ubjs_object_is_false(ubjs_object *, ubjs_bool *);

ubjs_result ubjs_object_int8(int8_t, ubjs_object **);
ubjs_result ubjs_object_is_int8(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_int8_get(ubjs_object *,int8_t *);
ubjs_result ubjs_object_int8_set(ubjs_object *,int8_t);

ubjs_result ubjs_object_uint8(uint8_t, ubjs_object **);
ubjs_result ubjs_object_is_uint8(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_uint8_get(ubjs_object *,uint8_t *);
ubjs_result ubjs_object_uint8_set(ubjs_object *,uint8_t);

ubjs_result ubjs_object_int16(int16_t, ubjs_object **);
ubjs_result ubjs_object_is_int16(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_int16_get(ubjs_object *,int16_t *);
ubjs_result ubjs_object_int16_set(ubjs_object *,int16_t);

ubjs_result ubjs_object_int32(int32_t, ubjs_object **);
ubjs_result ubjs_object_is_int32(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_int32_get(ubjs_object *,int32_t *);
ubjs_result ubjs_object_int32_set(ubjs_object *,int32_t);

ubjs_result ubjs_object_int64(int64_t, ubjs_object **);
ubjs_result ubjs_object_is_int64(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_int64_get(ubjs_object *,int64_t *);
ubjs_result ubjs_object_int64_set(ubjs_object *,int64_t);

ubjs_result ubjs_object_float32(float32_t, ubjs_object **);
ubjs_result ubjs_object_is_float32(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_float32_get(ubjs_object *,float32_t *);
ubjs_result ubjs_object_float32_set(ubjs_object *,float32_t);

ubjs_result ubjs_object_float64(float64_t, ubjs_object **);
ubjs_result ubjs_object_is_float64(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_float64_get(ubjs_object *,float64_t *);
ubjs_result ubjs_object_float64_set(ubjs_object *,float64_t);

ubjs_result ubjs_object_free(ubjs_object **);

#endif

