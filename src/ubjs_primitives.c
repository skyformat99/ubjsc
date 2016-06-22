#include <stdlib.h>
#include <string.h>

#include "../ptrie/include/ptrie.h"
#include "../include/ubjs_primitives.h"

typedef struct ubjs_int8 ubjs_int8;
typedef struct ubjs_uint8 ubjs_uint8;
typedef struct ubjs_int16 ubjs_int16;
typedef struct ubjs_int32 ubjs_int32;
typedef struct ubjs_int64 ubjs_int64;
typedef struct ubjs_float32 ubjs_float32;
typedef struct ubjs_float64 ubjs_float64;
typedef struct ubjs_char ubjs_char;
typedef struct ubjs_str ubjs_str;
typedef struct ubjs_array ubjs_array;
typedef struct ubjs_object ubjs_object;

enum ubjs_prmtv_type {
    UOT_CONSTANT,
    UOT_INT8,
    UOT_UINT8,
    UOT_INT16,
    UOT_INT32,
    UOT_INT64,
    UOT_FLOAT32,
    UOT_FLOAT64,
    UOT_CHAR,
    UOT_STR,
    UOT_ARRAY,
    UOT_OBJECT
};

struct ubjs_prmtv
{
    enum ubjs_prmtv_type type;
};

struct ubjs_int8 {
    ubjs_prmtv super;
    int8_t value;
};

struct ubjs_uint8 {
    ubjs_prmtv super;
    uint8_t value;
};

struct ubjs_int16 {
    ubjs_prmtv super;
    int16_t value;
};

struct ubjs_int32 {
    ubjs_prmtv super;
    int32_t value;
};

struct ubjs_int64 {
    ubjs_prmtv super;
    int64_t value;
};

struct ubjs_float32 {
    ubjs_prmtv super;
    float32_t value;
};

struct ubjs_float64 {
    ubjs_prmtv super;
    float64_t value;
};

struct ubjs_char {
    ubjs_prmtv super;
    char value;
};

struct ubjs_str {
    ubjs_prmtv super;
    unsigned int length;
    char *text;
};

struct ubjs_array {
    ubjs_prmtv super;
    unsigned int length;
    unsigned int allocated_length;
    ubjs_prmtv **data;
};

struct ubjs_object {
    ubjs_prmtv super;
    ptrie *trie;
};

static ubjs_prmtv __ubjs_prmtv_null = {UOT_CONSTANT};
static ubjs_prmtv __ubjs_prmtv_noop = {UOT_CONSTANT};
static ubjs_prmtv __ubjs_prmtv_true = {UOT_CONSTANT};
static ubjs_prmtv __ubjs_prmtv_false = {UOT_CONSTANT};

#define UBJS_ARRAY_DEFAULT_SIZE 10
#define UBJS_ARRAY_MULTIPLY 3
#define UBJS_ARRAY_ADD 1
static ubjs_result ubjs_array_expand(ubjs_array *);
static ubjs_result ubjs_array_should_expand(ubjs_array *,ubjs_bool *);
static ubjs_result ubjs_array_shrink(ubjs_array *);
static ubjs_result ubjs_array_should_shrink(ubjs_array *,ubjs_bool *);

static void __ubjs_prmtv_free_trie(void *);

struct ubjs_array_iterator {
    ubjs_array *array;
    ubjs_prmtv *current;
    int pos;
};

static ubjs_result ubjs_array_iterator_new(ubjs_array *,ubjs_array_iterator **);
struct ubjs_object_iterator {
    ubjs_object *object;
    ptrie_iterator *iterator;
};

static ubjs_result ubjs_object_iterator_new(ubjs_object *,ubjs_object_iterator **);



ubjs_prmtv *ubjs_prmtv_null()
{
    return &__ubjs_prmtv_null;
}

ubjs_result ubjs_prmtv_is_null(ubjs_prmtv *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_null) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_noop()
{
    return &__ubjs_prmtv_noop;
}

ubjs_result ubjs_prmtv_is_noop(ubjs_prmtv *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_noop) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_true()
{
    return &__ubjs_prmtv_true;
}

ubjs_result ubjs_prmtv_is_true(ubjs_prmtv *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_true) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_false()
{
    return &__ubjs_prmtv_false;
}

ubjs_result ubjs_prmtv_is_false(ubjs_prmtv *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_false) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int8(int8_t value, ubjs_prmtv **pthis) {
    ubjs_int8 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int8 *)malloc(sizeof(struct ubjs_int8));

    this->super.type=UOT_INT8;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int8(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int8_get(ubjs_prmtv *this,int8_t *result)  {
    ubjs_int8 *rthis;
    if(0 == this || UOT_INT8 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int8_set(ubjs_prmtv *this,int8_t value) {
    ubjs_int8 *rthis;
    if(0 == this || UOT_INT8 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8(uint8_t value, ubjs_prmtv **pthis) {
    ubjs_uint8 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_uint8 *)malloc(sizeof(struct ubjs_uint8));

    this->super.type=UOT_UINT8;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_uint8(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_UINT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *this,uint8_t *result)  {
    ubjs_uint8 *rthis;
    if(0 == this || UOT_UINT8 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *this,uint8_t value) {
    ubjs_uint8 *rthis;
    if(0 == this || UOT_UINT8 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16(int16_t value, ubjs_prmtv **pthis) {
    ubjs_int16 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int16 *)malloc(sizeof(struct ubjs_int16));

    this->super.type=UOT_INT16;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int16(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT16) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *this,int16_t *result)  {
    ubjs_int16 *rthis;
    if(0 == this || UOT_INT16 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *this,int16_t value) {
    ubjs_int16 *rthis;
    if(0 == this || UOT_INT16 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32(int32_t value, ubjs_prmtv **pthis) {
    ubjs_int32 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int32 *)malloc(sizeof(struct ubjs_int32));

    this->super.type=UOT_INT32;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int32(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32_get(ubjs_prmtv *this,int32_t *result)  {
    ubjs_int32 *rthis;
    if(0 == this || UOT_INT32 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32_set(ubjs_prmtv *this,int32_t value) {
    ubjs_int32 *rthis;
    if(0 == this || UOT_INT32 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64(int64_t value, ubjs_prmtv **pthis) {
    ubjs_int64 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int64 *)malloc(sizeof(struct ubjs_int64));

    this->super.type=UOT_INT64;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int64(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64_get(ubjs_prmtv *this,int64_t *result)  {
    ubjs_int64 *rthis;
    if(0 == this || UOT_INT64 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64_set(ubjs_prmtv *this,int64_t value) {
    ubjs_int64 *rthis;
    if(0 == this || UOT_INT64 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32(float32_t value, ubjs_prmtv **pthis) {
    ubjs_float32 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_float32 *)malloc(sizeof(struct ubjs_float32));

    this->super.type=UOT_FLOAT32;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_float32(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32_get(ubjs_prmtv *this,float32_t *result)  {
    ubjs_float32 *rthis;

    if(0 == this || UOT_FLOAT32 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32_set(ubjs_prmtv *this,float32_t value) {
    ubjs_float32 *rthis;
    if(0 == this || UOT_FLOAT32 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64(float64_t value, ubjs_prmtv **pthis) {
    ubjs_float64 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_float64 *)malloc(sizeof(struct ubjs_float64));

    this->super.type=UOT_FLOAT64;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *this,float64_t *result)  {
    ubjs_float64 *rthis;

    if(0 == this || UOT_FLOAT64 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *this,float64_t value) {
    ubjs_float64 *rthis;
    if(0 == this || UOT_FLOAT64 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char(char value, ubjs_prmtv **pthis) {
    ubjs_char *this;

    if(0 == pthis || value > 127) {
        return UR_ERROR;
    }

    this=(ubjs_char *)malloc(sizeof(struct ubjs_char));

    this->super.type=UOT_CHAR;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_char(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_CHAR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *this,char *result)  {
    ubjs_char *rthis;

    if(0 == this || UOT_CHAR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *this,char value) {
    ubjs_char *rthis;
    if(0 == this || UOT_CHAR != this->type || value > 127)  {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str(unsigned int length, char *text, ubjs_prmtv **pthis) {
    ubjs_str *this;
    char *cpy;

    if(0 == pthis || 0 == text) {
        return UR_ERROR;
    }

    this=(ubjs_str *)malloc(sizeof(struct ubjs_str));
    cpy = (char *)malloc(sizeof(char) * length);

    strncpy(cpy, text, length);

    this->super.type=UOT_STR;
    this->length=length;
    this->text=cpy;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_str(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_STR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *this,unsigned int *result) {
    ubjs_str *rthis;

    if(0 == this || UOT_STR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    (*result) = rthis->length;

    return UR_OK;
}

ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *this,char *result) {
    ubjs_str *rthis;

    if(0 == this || UOT_STR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    strncpy(result, rthis->text, rthis->length);

    return UR_OK;
}

ubjs_result ubjs_prmtv_str_set(ubjs_prmtv *this,unsigned int length, char *text) {
    ubjs_str *rthis;
    char *cpy;

    if(0 == this || UOT_STR != this->type || 0 == text) {
        return UR_ERROR;
    }

    cpy = (char *)malloc(sizeof(char) * length);

    rthis=(ubjs_str *)this;

    free(rthis->text);
    strncpy(cpy, text, length);
    rthis->text=cpy;
    rthis->length=length;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array(ubjs_prmtv **pthis) {
    ubjs_array *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_array *)malloc(sizeof(struct ubjs_array));

    this->data=(ubjs_prmtv **)malloc(sizeof(ubjs_prmtv *) * UBJS_ARRAY_DEFAULT_SIZE);

    this->super.type=UOT_ARRAY;
    this->length=0;
    this->allocated_length=UBJS_ARRAY_DEFAULT_SIZE;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}


ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_ARRAY) ? UTRUE : UFALSE;
    return UR_OK;
}


ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this,unsigned int *length) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == length)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    *length = athis->length;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this,ubjs_prmtv **pitem) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(0 == athis->length) {
        return UR_ERROR;
    }
    *pitem=athis->data[0];
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this,ubjs_prmtv **pitem) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(0 == athis->length) {
        return UR_ERROR;
    }
    *pitem=athis->data[athis->length-1];
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this,unsigned int pos, ubjs_prmtv **pitem) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;

    if(athis->length <= pos) {
        return UR_ERROR;
    }

    *pitem=athis->data[pos];
    return UR_OK;
}

static ubjs_result ubjs_array_expand(ubjs_array *this) {
    unsigned int newlength=this->length * UBJS_ARRAY_MULTIPLY + UBJS_ARRAY_ADD;
    ubjs_prmtv **new_data;

    new_data=(ubjs_prmtv **)realloc(this->data, sizeof(ubjs_prmtv *) * newlength);
    if(0 == new_data) {
        return UR_ERROR;
    }

    this->data=new_data;
    this->allocated_length=newlength;
    return UR_OK;
}

static ubjs_result ubjs_array_should_expand(ubjs_array *this,ubjs_bool *ret) {
    *ret = (this->length==this->allocated_length ? UTRUE : UFALSE);
    return UR_OK;
}


static ubjs_result ubjs_array_shrink(ubjs_array *this) {
    unsigned int newlength=this->length;
    ubjs_prmtv **new_data;

    new_data=(ubjs_prmtv **)realloc(this->data, sizeof(ubjs_prmtv *) * newlength);
    if(0 == new_data) {
        return UR_ERROR;
    }

    this->data=new_data;
    this->allocated_length=newlength;
    return UR_OK;
}

static ubjs_result ubjs_array_should_shrink(ubjs_array *this,ubjs_bool *ret) {
    *ret = (UBJS_ARRAY_DEFAULT_SIZE < this->length && this->length * UBJS_ARRAY_MULTIPLY + UBJS_ARRAY_ADD < this->allocated_length) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this,ubjs_prmtv *item) {
    ubjs_array *athis;
    ubjs_bool ret;
    unsigned int it;

    if(0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(UR_OK == ubjs_array_should_expand(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_expand(athis)) {
            return UR_ERROR;
        }
    }

    for(it=athis->length; 0<it; it--) {
        athis->data[it]=athis->data[it-1];
    }

    athis->data[0]=item;
    athis->length++;

    return UR_OK;
}

ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this,ubjs_prmtv *item) {
    ubjs_array *athis;
    ubjs_bool ret;

    if(0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(UR_OK == ubjs_array_should_expand(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_expand(athis)) {
            return UR_ERROR;
        }
    }

    athis->data[athis->length++]=item;

    return UR_OK;
}


ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this,unsigned int pos, ubjs_prmtv *item) {
    ubjs_array *athis;
    ubjs_bool ret;
    unsigned int it;

    if(0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(athis->length < pos) {
        return UR_ERROR;
    }

    if(UR_OK == ubjs_array_should_expand(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_expand(athis)) {
            return UR_ERROR;
        }
    }

    for(it=athis->length; pos<it; it--) {
        athis->data[it]=athis->data[it-1];
    }

    athis->data[pos]=item;
    athis->length++;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this) {
    ubjs_array *athis;
    ubjs_bool ret;
    unsigned int it;

    if(0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(0 == athis->length) {
        return UR_ERROR;
    }

    if(UR_OK == ubjs_array_should_shrink(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_shrink(athis)) {
            return UR_ERROR;
        }
    }

    for(it=0; athis->length > it - 1; it++) {
        athis->data[it]=athis->data[it+1];
    }

    athis->length--;

    return UR_OK;
}

ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this) {
    ubjs_array *athis;
    ubjs_bool ret;

    if(0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(0 == athis->length) {
        return UR_ERROR;
    }

    if(UR_OK == ubjs_array_should_shrink(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_shrink(athis)) {
            return UR_ERROR;
        }
    }

    athis->length--;

    return UR_OK;
}

ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this,unsigned int pos) {
    ubjs_array *athis;
    ubjs_bool ret;
    unsigned int it;

    if(0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    if(athis->length <= pos) {
        return UR_ERROR;
    }

    if(UR_OK == ubjs_array_should_shrink(athis, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_array_shrink(athis)) {
            return UR_ERROR;
        }
    }

    for(it=pos; athis->length > it - 1; it++) {
        athis->data[it]=athis->data[it+1];
    }

    athis->length--;

    return UR_OK;
}

static ubjs_result ubjs_array_iterator_new(ubjs_array *array,ubjs_array_iterator **pthis) {
    ubjs_array_iterator *this;

    this=(ubjs_array_iterator *)malloc(sizeof(struct ubjs_array_iterator));
    this->array=array;
    this->current=0;
    this->pos=0;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this,ubjs_array_iterator **iterator) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == iterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return ubjs_array_iterator_new(athis, iterator);
}

ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this) {
    if(0 == this) {
        return UR_ERROR;
    }

    this->current = 0;

    if(this->pos >= this->array->length) {
        return UR_ERROR;
    }

    this->current=this->array->data[this->pos];
    this->pos++;

    return UR_OK;
}

ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this,ubjs_prmtv **item) {
    if(0 == this || 0 == item || 0 == this->current) {
        return UR_ERROR;
    }

    *item = this->current;
    return UR_OK;
}

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis) {
    if(0 == pthis) {
        return UR_ERROR;
    }

    free(*pthis);
    *pthis=0;
    return UR_OK;
}

static void __ubjs_prmtv_free_trie(void *item) {
    ubjs_prmtv_free((ubjs_prmtv **)&item);
}

ubjs_result ubjs_prmtv_object(ubjs_prmtv **pthis) {
    ubjs_object *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_object *)malloc(sizeof(struct ubjs_object));
    ptrie_new(__ubjs_prmtv_free_trie, &(this->trie));

    this->super.type=UOT_OBJECT;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_OBJECT) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this,unsigned int *plen) {
    ubjs_object *uthis;
    if(0 == this || UOT_OBJECT != this->type || 0 == plen) {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return ptrie_get_length(uthis->trie, plen);
}

ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this,unsigned int key_length,char *key,ubjs_prmtv **pvalue) {
    ubjs_object *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key || 0==pvalue) {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return ptrie_get(uthis->trie,key_length,key,(void **)pvalue);
}

ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this,unsigned int key_length,char *key,ubjs_prmtv *value) {
    ubjs_object *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key || 0==value) {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return PR_OK == ptrie_set(uthis->trie,key_length,key,(void *)value) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this,unsigned int key_length,char *key) {
    ubjs_object *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key) {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return PR_OK == ptrie_delete(uthis->trie,key_length,key) ? UR_OK : UR_ERROR;
}

static ubjs_result ubjs_object_iterator_new(ubjs_object *object,ubjs_object_iterator **pthis) {
    ubjs_object_iterator *this;

    if(0==object || 0==pthis) {
        return UR_ERROR;
    }

    this=(ubjs_object_iterator *)malloc(sizeof(struct ubjs_object_iterator));
    this->object=object;
    ptrie_iterate(object->trie, &(this->iterator));

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this,ubjs_object_iterator **piterator) {
    if(0==this || UOT_OBJECT != this->type|| 0==piterator) {
        return UR_ERROR;
    }

    return ubjs_object_iterator_new((ubjs_object *)this, piterator);
}

ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this) {
    if(0==this) {
        return UR_ERROR;
    }

    return PR_OK == ptrie_iterator_next(this->iterator) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this, unsigned int *plen) {
    if(0==this || 0 == plen) {
        return UR_ERROR;
    }

    return PR_OK == ptrie_iterator_get_key_length(this->iterator, plen) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *key) {
    if(0==this || 0 == key) {
        return UR_ERROR;
    }

    return PR_OK == ptrie_iterator_copy_key(this->iterator, key) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this, ubjs_prmtv **pvalue) {
    if(0==this || 0 == pvalue) {
        return UR_ERROR;
    }

    return PR_OK == ptrie_iterator_get_value(this->iterator, (void **)pvalue) ? UR_OK : UR_ERROR;

}

ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **piterator) {
    ubjs_object_iterator *iterator;
    if(0==piterator) {
        return UR_ERROR;
    }

    iterator=*piterator;
    ptrie_iterator_free(&(iterator->iterator));
    free(iterator);

    *piterator=0;
    return UR_OK;
}
ubjs_result ubjs_prmtv_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv *this;
    ubjs_str *sthis;
    ubjs_array *athis;
    ubjs_prmtv *ait;
    ubjs_object *oit;
    unsigned int it;

    if(0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    switch(this->type) {
    case UOT_CONSTANT:
        break;

    case UOT_INT8:
    case UOT_UINT8:
    case UOT_INT16:
    case UOT_INT32:
    case UOT_INT64:
    case UOT_FLOAT32:
    case UOT_FLOAT64:
    case UOT_CHAR:
        free(this);
        break;

    case UOT_STR:
        sthis=(ubjs_str *)this;
        free(sthis->text);
        free(this);
        break;

    case UOT_ARRAY:
        athis=(ubjs_array *)this;

        for(it=0; athis->length>it; it++) {
            ait=athis->data[it];
            ubjs_prmtv_free(&ait);
        }

        free(athis->data);
        free(athis);
        break;

    case UOT_OBJECT:
        oit=(ubjs_object *)this;
        ptrie_free(&(oit->trie));
        free(oit);
        break;

    default:
        return UR_ERROR;
    }

    *pthis=0;
    return UR_OK;
}
