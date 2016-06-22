#ifndef HAVE_UBJS_OBJECTS
#define HAVE_UBJS_OBJECTS

#include "ubjs_common.h"

typedef struct ubjs_prmtv ubjs_prmtv;
typedef struct ubjs_array_iterator ubjs_array_iterator;
typedef struct ubjs_prmtv_iterator ubjs_prmtv_iterator;

struct ubjs_prmtv;
struct ubjs_array_iterator;
struct ubjs_prmtv_iterator;

ubjs_prmtv *ubjs_prmtv_null();
ubjs_result ubjs_prmtv_is_null(ubjs_prmtv *, ubjs_bool *);

ubjs_prmtv *ubjs_prmtv_noop();
ubjs_result ubjs_prmtv_is_noop(ubjs_prmtv *, ubjs_bool *);

ubjs_prmtv *ubjs_prmtv_true();
ubjs_result ubjs_prmtv_is_true(ubjs_prmtv *, ubjs_bool *);

ubjs_prmtv *ubjs_prmtv_false();
ubjs_result ubjs_prmtv_is_false(ubjs_prmtv *, ubjs_bool *);

ubjs_result ubjs_prmtv_int8(int8_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_int8(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_int8_get(ubjs_prmtv *,int8_t *);
ubjs_result ubjs_prmtv_int8_set(ubjs_prmtv *,int8_t);

ubjs_result ubjs_prmtv_uint8(uint8_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_uint8(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *,uint8_t *);
ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *,uint8_t);

ubjs_result ubjs_prmtv_int16(int16_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_int16(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *,int16_t *);
ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *,int16_t);

ubjs_result ubjs_prmtv_int32(int32_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_int32(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_int32_get(ubjs_prmtv *,int32_t *);
ubjs_result ubjs_prmtv_int32_set(ubjs_prmtv *,int32_t);

ubjs_result ubjs_prmtv_int64(int64_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_int64(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_int64_get(ubjs_prmtv *,int64_t *);
ubjs_result ubjs_prmtv_int64_set(ubjs_prmtv *,int64_t);

ubjs_result ubjs_prmtv_float32(float32_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_float32(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_float32_get(ubjs_prmtv *,float32_t *);
ubjs_result ubjs_prmtv_float32_set(ubjs_prmtv *,float32_t);

ubjs_result ubjs_prmtv_float64(float64_t, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *,float64_t *);
ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *,float64_t);

ubjs_result ubjs_prmtv_char(char, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_char(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *,char *);
ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *,char);

ubjs_result ubjs_prmtv_str(unsigned int, char *, ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_str(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *,unsigned int *);
ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *,char *);
ubjs_result ubjs_prmtv_str_set(ubjs_prmtv *,unsigned int, char *);

ubjs_result ubjs_prmtv_array(ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *,unsigned int *);
ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *,ubjs_prmtv **);
ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *,ubjs_prmtv **);
ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *,unsigned int,ubjs_prmtv **);
ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *,ubjs_prmtv *);
ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *,ubjs_prmtv *);
ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *,unsigned int,ubjs_prmtv *);
ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *);
ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *);
ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *,unsigned int);

ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *,ubjs_array_iterator **);
ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *);
ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *,ubjs_prmtv **);

ubjs_result ubjs_prmtv_object(ubjs_prmtv **);
ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *, ubjs_bool *);
ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *,unsigned int *);
ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *,unsigned int,char *,ubjs_prmtv **);
ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *,unsigned int,char *,ubjs_prmtv *);
ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *,unsigned int,char *);

ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *,ubjs_prmtv_iterator **);
ubjs_result ubjs_prmtv_iterator_next(ubjs_prmtv_iterator *);
ubjs_result ubjs_prmtv_iterator_get_key_length(ubjs_prmtv_iterator *, unsigned int *);
ubjs_result ubjs_prmtv_iterator_copy_key(ubjs_prmtv_iterator *, char *);
ubjs_result ubjs_prmtv_iterator_get_vaue(ubjs_prmtv_iterator *, ubjs_prmtv **);

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **);
ubjs_result ubjs_prmtv_iterator_free(ubjs_prmtv_iterator **);

ubjs_result ubjs_prmtv_free(ubjs_prmtv **);

#endif

