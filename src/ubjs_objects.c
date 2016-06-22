#include <stdlib.h>
#include <string.h>

#include "../ptrie/include/ptrie.h"
#include "../include/ubjs_objects.h"

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
typedef struct ubjs_uobject ubjs_uobject;

enum ubjs_object_type {
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

struct ubjs_object
{
    enum ubjs_object_type type;
};

struct ubjs_int8 {
    ubjs_object super;
    int8_t value;
};

struct ubjs_uint8 {
    ubjs_object super;
    uint8_t value;
};

struct ubjs_int16 {
    ubjs_object super;
    int16_t value;
};

struct ubjs_int32 {
    ubjs_object super;
    int32_t value;
};

struct ubjs_int64 {
    ubjs_object super;
    int64_t value;
};

struct ubjs_float32 {
    ubjs_object super;
    float32_t value;
};

struct ubjs_float64 {
    ubjs_object super;
    float64_t value;
};

struct ubjs_char {
    ubjs_object super;
    char value;
};

struct ubjs_str {
    ubjs_object super;
    unsigned int length;
    char *text;
};

struct ubjs_array {
    ubjs_object super;
    unsigned int length;
    unsigned int allocated_length;
    ubjs_object **data;
};


struct ubjs_uobject {
    ubjs_object super;
    ptrie *trie;
};

static ubjs_object __ubjs_object_null = {UOT_CONSTANT};
static ubjs_object __ubjs_object_noop = {UOT_CONSTANT};
static ubjs_object __ubjs_object_true = {UOT_CONSTANT};
static ubjs_object __ubjs_object_false = {UOT_CONSTANT};

#define UBJS_ARRAY_DEFAULT_SIZE 10
#define UBJS_ARRAY_MULTIPLY 3
#define UBJS_ARRAY_ADD 1
static ubjs_result ubjs_array_expand(ubjs_array *);
static ubjs_result ubjs_array_should_expand(ubjs_array *,ubjs_bool *);
static ubjs_result ubjs_array_shrink(ubjs_array *);
static ubjs_result ubjs_array_should_shrink(ubjs_array *,ubjs_bool *);

static void __ubjs_object_free_trie(void *);

struct ubjs_array_iterator {
    ubjs_array *array;
    ubjs_object *current;
    int pos;
};

static ubjs_result ubjs_array_iterator_new(ubjs_array *,ubjs_array_iterator **);
struct ubjs_object_iterator {
    ubjs_uobject *object;
    ptrie_iterator *iterator;
};

static ubjs_result ubjs_uobject_iterator_new(ubjs_uobject *,ubjs_object_iterator **);



ubjs_object *ubjs_object_null()
{
    return &__ubjs_object_null;
}

ubjs_result ubjs_object_is_null(ubjs_object *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_object_null) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_object *ubjs_object_noop()
{
    return &__ubjs_object_noop;
}

ubjs_result ubjs_object_is_noop(ubjs_object *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_object_noop) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_object *ubjs_object_true()
{
    return &__ubjs_object_true;
}

ubjs_result ubjs_object_is_true(ubjs_object *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_object_true) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_object *ubjs_object_false()
{
    return &__ubjs_object_false;
}

ubjs_result ubjs_object_is_false(ubjs_object *this, ubjs_bool* result)
{
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_object_false) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_int8(int8_t value, ubjs_object **pthis) {
    ubjs_int8 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int8 *)malloc(sizeof(struct ubjs_int8));

    this->super.type=UOT_INT8;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_int8(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_int8_get(ubjs_object *this,int8_t *result)  {
    ubjs_int8 *rthis;
    if(0 == this || UOT_INT8 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_int8_set(ubjs_object *this,int8_t value) {
    ubjs_int8 *rthis;
    if(0 == this || UOT_INT8 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_uint8(uint8_t value, ubjs_object **pthis) {
    ubjs_uint8 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_uint8 *)malloc(sizeof(struct ubjs_uint8));

    this->super.type=UOT_UINT8;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_uint8(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_UINT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_uint8_get(ubjs_object *this,uint8_t *result)  {
    ubjs_uint8 *rthis;
    if(0 == this || UOT_UINT8 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_uint8_set(ubjs_object *this,uint8_t value) {
    ubjs_uint8 *rthis;
    if(0 == this || UOT_UINT8 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_int16(int16_t value, ubjs_object **pthis) {
    ubjs_int16 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int16 *)malloc(sizeof(struct ubjs_int16));

    this->super.type=UOT_INT16;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_int16(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT16) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_int16_get(ubjs_object *this,int16_t *result)  {
    ubjs_int16 *rthis;
    if(0 == this || UOT_INT16 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_int16_set(ubjs_object *this,int16_t value) {
    ubjs_int16 *rthis;
    if(0 == this || UOT_INT16 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_int32(int32_t value, ubjs_object **pthis) {
    ubjs_int32 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int32 *)malloc(sizeof(struct ubjs_int32));

    this->super.type=UOT_INT32;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_int32(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_int32_get(ubjs_object *this,int32_t *result)  {
    ubjs_int32 *rthis;
    if(0 == this || UOT_INT32 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_int32_set(ubjs_object *this,int32_t value) {
    ubjs_int32 *rthis;
    if(0 == this || UOT_INT32 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_int64(int64_t value, ubjs_object **pthis) {
    ubjs_int64 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_int64 *)malloc(sizeof(struct ubjs_int64));

    this->super.type=UOT_INT64;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_int64(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_int64_get(ubjs_object *this,int64_t *result)  {
    ubjs_int64 *rthis;
    if(0 == this || UOT_INT64 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_int64_set(ubjs_object *this,int64_t value) {
    ubjs_int64 *rthis;
    if(0 == this || UOT_INT64 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_float32(float32_t value, ubjs_object **pthis) {
    ubjs_float32 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_float32 *)malloc(sizeof(struct ubjs_float32));

    this->super.type=UOT_FLOAT32;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_float32(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_float32_get(ubjs_object *this,float32_t *result)  {
    ubjs_float32 *rthis;

    if(0 == this || UOT_FLOAT32 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_float32_set(ubjs_object *this,float32_t value) {
    ubjs_float32 *rthis;
    if(0 == this || UOT_FLOAT32 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_float64(float64_t value, ubjs_object **pthis) {
    ubjs_float64 *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_float64 *)malloc(sizeof(struct ubjs_float64));

    this->super.type=UOT_FLOAT64;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_float64(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_float64_get(ubjs_object *this,float64_t *result)  {
    ubjs_float64 *rthis;

    if(0 == this || UOT_FLOAT64 != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_float64_set(ubjs_object *this,float64_t value) {
    ubjs_float64 *rthis;
    if(0 == this || UOT_FLOAT64 != this->type)  {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_char(char value, ubjs_object **pthis) {
    ubjs_char *this;

    if(0 == pthis || value > 127) {
        return UR_ERROR;
    }

    this=(ubjs_char *)malloc(sizeof(struct ubjs_char));

    this->super.type=UOT_CHAR;
    this->value = value;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_char(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_CHAR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_char_get(ubjs_object *this,char *result)  {
    ubjs_char *rthis;

    if(0 == this || UOT_CHAR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_char_set(ubjs_object *this,char value) {
    ubjs_char *rthis;
    if(0 == this || UOT_CHAR != this->type || value > 127)  {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_str(unsigned int length, char *text, ubjs_object **pthis) {
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

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_is_str(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_STR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_object_str_get_length(ubjs_object *this,unsigned int *result) {
    ubjs_str *rthis;

    if(0 == this || UOT_STR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    (*result) = rthis->length;

    return UR_OK;
}

ubjs_result ubjs_object_str_copy_text(ubjs_object *this,char *result) {
    ubjs_str *rthis;

    if(0 == this || UOT_STR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    strncpy(result, rthis->text, rthis->length);

    return UR_OK;
}

ubjs_result ubjs_object_str_set(ubjs_object *this,unsigned int length, char *text) {
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

ubjs_result ubjs_object_array(ubjs_object **pthis) {
    ubjs_array *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_array *)malloc(sizeof(struct ubjs_array));

    this->data=(ubjs_object **)malloc(sizeof(ubjs_object *) * UBJS_ARRAY_DEFAULT_SIZE);

    this->super.type=UOT_ARRAY;
    this->length=0;
    this->allocated_length=UBJS_ARRAY_DEFAULT_SIZE;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}


ubjs_result ubjs_object_is_array(ubjs_object *this, ubjs_bool *result) {
    if(0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_ARRAY) ? UTRUE : UFALSE;
    return UR_OK;
}


ubjs_result ubjs_object_array_get_length(ubjs_object *this,unsigned int *length) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == length)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    *length = athis->length;
    return UR_OK;
}

ubjs_result ubjs_object_array_get_first(ubjs_object *this,ubjs_object **pitem) {
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

ubjs_result ubjs_object_array_get_last(ubjs_object *this,ubjs_object **pitem) {
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

ubjs_result ubjs_object_array_get_at(ubjs_object *this,unsigned int pos, ubjs_object **pitem) {
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
    ubjs_object **new_data;

    new_data=(ubjs_object **)realloc(this->data, sizeof(ubjs_object *) * newlength);
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
    ubjs_object **new_data;

    new_data=(ubjs_object **)realloc(this->data, sizeof(ubjs_object *) * newlength);
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

ubjs_result ubjs_object_array_add_first(ubjs_object *this,ubjs_object *item) {
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

ubjs_result ubjs_object_array_add_last(ubjs_object *this,ubjs_object *item) {
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


ubjs_result ubjs_object_array_add_at(ubjs_object *this,unsigned int pos, ubjs_object *item) {
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

ubjs_result ubjs_object_array_delete_first(ubjs_object *this) {
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

ubjs_result ubjs_object_array_delete_last(ubjs_object *this) {
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

ubjs_result ubjs_object_array_delete_at(ubjs_object *this,unsigned int pos) {
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

ubjs_result ubjs_object_array_iterate(ubjs_object *this,ubjs_array_iterator **iterator) {
    ubjs_array *athis;

    if(0 == this || UOT_ARRAY != this->type || 0 == iterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return ubjs_array_iterator_new(athis, iterator);
}

ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this) {
    this->current = 0;

    if(this->pos >= this->array->length) {
        return UR_ERROR;
    }

    this->current=this->array->data[this->pos];
    this->pos++;

    return UR_OK;
}

ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this,ubjs_object **item) {
    if(0 == this->current) {
        return UR_ERROR;
    }

    *item = this->current;
    return UR_OK;
}

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis) {
    free(*pthis);
    *pthis=0;
    return UR_OK;
}

static void __ubjs_object_free_trie(void *item) {
    ubjs_object_free((ubjs_object **)&item);
}

ubjs_result ubjs_object_object(ubjs_object **pthis) {
    ubjs_uobject *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_uobject *)malloc(sizeof(struct ubjs_uobject));
    ptrie_new(__ubjs_object_free_trie, &(this->trie));

    this->super.type=UOT_OBJECT;

    *pthis=(ubjs_object *)this;
    return UR_OK;
}

ubjs_result ubjs_object_object_get_length(ubjs_object *this,unsigned int *plen) {
    ubjs_uobject *uthis;
    if(0 == this || UOT_OBJECT != this->type || 0 == plen) {
        return UR_ERROR;
    }

    uthis=(ubjs_uobject *)this;
    return ptrie_get_length(uthis->trie, plen);
}

ubjs_result ubjs_object_object_get(ubjs_object *this,unsigned int key_length,char *key,ubjs_object **pvalue) {
    ubjs_uobject *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key || 0==pvalue) {
        return UR_ERROR;
    }

    uthis=(ubjs_uobject *)this;
    return ptrie_get(uthis->trie,key_length,key,(void **)pvalue);
}

ubjs_result ubjs_object_object_set(ubjs_object *this,unsigned int key_length,char *key,ubjs_object *value) {
    ubjs_uobject *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key || 0==value) {
        return UR_ERROR;
    }

    uthis=(ubjs_uobject *)this;
    return PR_OK == ptrie_set(uthis->trie,key_length,key,(void *)value) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_object_object_delete(ubjs_object *this,unsigned int key_length,char *key) {
    ubjs_uobject *uthis;

    if(0==this || UOT_OBJECT != this->type|| 0==key) {
        return UR_ERROR;
    }

    uthis=(ubjs_uobject *)this;
    return PR_OK == ptrie_delete(uthis->trie,key_length,key) ? UR_OK : UR_ERROR;
}

static ubjs_result ubjs_uobject_iterator_new(ubjs_uobject *object,ubjs_object_iterator **pthis) {
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

ubjs_result ubjs_object_object_iterate(ubjs_object *this,ubjs_object_iterator **piterator) {
    if(0==this || UOT_OBJECT != this->type|| 0==piterator) {
        return UR_ERROR;
    }

    return ubjs_uobject_iterator_new((ubjs_uobject *)this, piterator);
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

ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this, ubjs_object **pvalue) {
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
ubjs_result ubjs_object_free(ubjs_object **pthis)
{
    ubjs_object *this;
    ubjs_str *sthis;
    ubjs_array *athis;
    ubjs_object *ait;
    ubjs_uobject *oit;
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
            ubjs_object_free(&ait);
        }

        free(athis->data);
        free(athis);
        break;

    case UOT_OBJECT:
        oit=(ubjs_uobject *)this;
        ptrie_free(&(oit->trie));
        free(oit);
    }

    *pthis=0;
    return UR_OK;
}


