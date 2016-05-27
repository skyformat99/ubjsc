#include "ubjs_objects.h"

#include <stdlib.h>

typedef struct ubjs_int8 ubjs_int8;
typedef struct ubjs_uint8 ubjs_uint8;
typedef struct ubjs_int16 ubjs_int16;
typedef struct ubjs_int32 ubjs_int32;
typedef struct ubjs_int64 ubjs_int64;
typedef struct ubjs_float32 ubjs_float32;
typedef struct ubjs_float64 ubjs_float64;
typedef struct ubjs_char ubjs_char;

enum ubjs_object_type {
    UOT_CONSTANT,
    UOT_INT8,
    UOT_UINT8,
    UOT_INT16,
    UOT_INT32,
    UOT_INT64,
    UOT_FLOAT32,
    UOT_FLOAT64,
    UOT_CHAR
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
    unsigned char value;
};

static ubjs_object __ubjs_object_null = {UOT_CONSTANT};
static ubjs_object __ubjs_object_noop = {UOT_CONSTANT};
static ubjs_object __ubjs_object_true = {UOT_CONSTANT};
static ubjs_object __ubjs_object_false = {UOT_CONSTANT};

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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
    if(this == 0) {
        return UR_ERROR;
    }

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


ubjs_result ubjs_object_char(unsigned char value, ubjs_object **pthis) {
    ubjs_char *this;

    if(0 == pthis || value > 127) {
        return UR_ERROR;
    }

    this=(ubjs_char *)malloc(sizeof(struct ubjs_char));
    if(this == 0) {
        return UR_ERROR;
    }

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

ubjs_result ubjs_object_char_get(ubjs_object *this,unsigned char *result)  {
    ubjs_char *rthis;

    if(0 == this || UOT_CHAR != this->type || 0 == result) {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_object_char_set(ubjs_object *this,unsigned char value) {
    ubjs_char *rthis;
    if(0 == this || UOT_CHAR != this->type || value > 127)  {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_object_free(ubjs_object **pthis)
{
    ubjs_object *this;

    if(0 == pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;

    if(UOT_CONSTANT != this->type) {
        free(this);
    }

    *pthis=0;
    return UR_OK;
}
