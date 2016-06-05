#ifndef HAVE_UBJS_OBJECTS
#define HAVE_UBJS_OBJECTS

#include "ubjs_common.h"

typedef struct ubjs_object ubjs_object;
typedef struct ubjs_array_iterator ubjs_array_iterator;
typedef struct ubjs_object_iterator ubjs_object_iterator;

struct ubjs_object;
struct ubjs_array_iterator;
struct ubjs_object_iterator;

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

ubjs_result ubjs_object_char(char, ubjs_object **);
ubjs_result ubjs_object_is_char(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_char_get(ubjs_object *,char *);
ubjs_result ubjs_object_char_set(ubjs_object *,char);

ubjs_result ubjs_object_str(unsigned int, char *, ubjs_object **);
ubjs_result ubjs_object_is_str(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_str_get_length(ubjs_object *,unsigned int *);
ubjs_result ubjs_object_str_copy_text(ubjs_object *,char *);
ubjs_result ubjs_object_str_set(ubjs_object *,unsigned int, char *);

ubjs_result ubjs_object_array(ubjs_object **);
ubjs_result ubjs_object_is_array(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_array_get_length(ubjs_object *,unsigned int *);
ubjs_result ubjs_object_array_get_first(ubjs_object *,ubjs_object **);
ubjs_result ubjs_object_array_get_last(ubjs_object *,ubjs_object **);
ubjs_result ubjs_object_array_get_at(ubjs_object *,unsigned int,ubjs_object **);
ubjs_result ubjs_object_array_add_first(ubjs_object *,ubjs_object *);
ubjs_result ubjs_object_array_add_last(ubjs_object *,ubjs_object *);
ubjs_result ubjs_object_array_add_at(ubjs_object *,unsigned int,ubjs_object *);
ubjs_result ubjs_object_array_remove_first(ubjs_object *);
ubjs_result ubjs_object_array_remove_last(ubjs_object *);
ubjs_result ubjs_object_array_remove_at(ubjs_object *,unsigned int);

ubjs_result ubjs_object_array_iterate_forward(ubjs_object *,ubjs_array_iterator **);
ubjs_result ubjs_object_array_iterate_backward(ubjs_object *,ubjs_array_iterator **);
ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *);
ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *,ubjs_object **);

ubjs_result ubjs_object_object(ubjs_object **);
ubjs_result ubjs_object_is_object(ubjs_object *, ubjs_bool *);
ubjs_result ubjs_object_object_get_length(ubjs_object *,unsigned int *);
ubjs_result ubjs_object_object_get(ubjs_object *,unsigned int,char *,ubjs_object **);
ubjs_result ubjs_object_object_set(ubjs_object *,unsigned int,char *,ubjs_object *);
ubjs_result ubjs_object_object_remove(ubjs_object *,unsigned int,char *);

ubjs_result ubjs_object_object_iterate_forward(ubjs_object *,ubjs_array_iterator **);
ubjs_result ubjs_object_object_iterate_backward(ubjs_object *,ubjs_array_iterator **);
ubjs_result ubjs_object_iterator_next(ubjs_array_iterator *);
ubjs_result ubjs_object_iterator_get_key_length(ubjs_array_iterator *, unsigned int *);
ubjs_result ubjs_object_iterator_copy_key(ubjs_array_iterator *, char *);
ubjs_result ubjs_object_iterator_get_vaue(ubjs_array_iterator *, ubjs_object **);

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **);
ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **);

ubjs_result ubjs_object_free(ubjs_object **);

#endif

