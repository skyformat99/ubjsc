#include <stdlib.h>
#include <string.h>

#include "ubjs_writer.h"
#include "ubjs_writer_internal.h"

typedef struct __ubjs_writer_strategy_no_length __ubjs_writer_strategy_no_length;

int ubjs_writer_strategies_len = 12;
ubjs_writer_strategy ubjs_writer_strategies[] =
{
    (ubjs_writer_strategy)ubjs_writer_strategy_null,
    (ubjs_writer_strategy)ubjs_writer_strategy_noop,
    (ubjs_writer_strategy)ubjs_writer_strategy_true,
    (ubjs_writer_strategy)ubjs_writer_strategy_false,
    (ubjs_writer_strategy)ubjs_writer_strategy_int8,
    (ubjs_writer_strategy)ubjs_writer_strategy_uint8,
    (ubjs_writer_strategy)ubjs_writer_strategy_int16,
    (ubjs_writer_strategy)ubjs_writer_strategy_int32,
    (ubjs_writer_strategy)ubjs_writer_strategy_int64,
    (ubjs_writer_strategy)ubjs_writer_strategy_float32,
    (ubjs_writer_strategy)ubjs_writer_strategy_float64,
    (ubjs_writer_strategy)ubjs_writer_strategy_char
};

static void ubjs_writer_strategy_runner_run_no_length(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_free_no_length(ubjs_writer_strategy_runner *);
static void ubjs_writer_strategy_runner_run_int8(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_uint8(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_int16(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_int32(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_int64(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_float32(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_float64(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_run_char(ubjs_writer_strategy_runner *,uint8_t *);

struct ubjs_writer
{
    ubjs_writer_context *context;
};

struct __ubjs_writer_strategy_no_length {
    uint8_t marker;
};

ubjs_result ubjs_writer_alloc(ubjs_writer **pthis,ubjs_writer_context *context)
{
    ubjs_writer *this;

    if(0 == pthis || 0 == context)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer *)malloc(sizeof(struct ubjs_writer));
    if(this==0)
    {
        return UR_ERROR;
    }

    this->context=context;
    *pthis=this;

    return UR_OK;
}

ubjs_result ubjs_writer_free(ubjs_writer **pthis)
{
    ubjs_writer *this;

    if(0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;

    (this->context->free)(this->context);
    free(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_writer_get_context(ubjs_writer *this,ubjs_writer_context **context)
{
    if(0 == this || 0 == context)
    {
        return UR_ERROR;
    }
    *context = this->context;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_find_best(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    int i;
    ubjs_writer_strategy_runner *arunner = 0;

    for(i=0; i<ubjs_writer_strategies_len; i++)
    {
        ubjs_writer_strategy it = ubjs_writer_strategies[i];

        if(UR_OK == (it)(object, &arunner))
        {
            *runner=arunner;
            return UR_OK;
        }
    }

    //todo
    return UR_ERROR;
}

ubjs_result ubjs_writer_write(ubjs_writer *this,ubjs_object *object)
{
    if(0 == this || 0 == object)
    {
        return UR_ERROR;
    }

    ubjs_writer_strategy_runner *runner=0;

    if(UR_ERROR == ubjs_writer_strategy_find_best(object, &runner))
    {
        return UR_ERROR;
    }

    unsigned int len = runner->length;
    uint8_t *data=(uint8_t *)malloc(sizeof(uint8_t) * (len));
    if(0 == data)
    {
        return UR_ERROR;
    }

    (runner->run)(runner, data);
    (this->context->would_write)(this->context->userdata, data, len);
    free(data);
    (runner->free)(runner);

    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_no_length(ubjs_writer_strategy_runner *runner, uint8_t *data)
{
    __ubjs_writer_strategy_no_length *userdata=(__ubjs_writer_strategy_no_length *)runner->userdata;
    (*data) = userdata->marker;
}

static void ubjs_writer_strategy_runner_free_no_length(ubjs_writer_strategy_runner *this) {
    free(this->userdata);
    free(this);
}

ubjs_result ubjs_writer_strategy_null(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;
    __ubjs_writer_strategy_no_length *data;

    if(ubjs_object_null() == object)
    {
        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=(__ubjs_writer_strategy_no_length *)malloc(sizeof(struct __ubjs_writer_strategy_no_length));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        data->marker=MARKER_NULL;
        arunner->userdata=data;
        arunner->object=object;
        arunner->length=1;
        arunner->run=ubjs_writer_strategy_runner_run_no_length;
        arunner->free=ubjs_writer_strategy_runner_free_no_length;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

ubjs_result ubjs_writer_strategy_noop(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;
    __ubjs_writer_strategy_no_length *data;

    if(ubjs_object_noop() == object)
    {
        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=(__ubjs_writer_strategy_no_length *)malloc(sizeof(struct __ubjs_writer_strategy_no_length));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        data->marker=MARKER_NOOP;
        arunner->userdata=data;
        arunner->object=object;
        arunner->length=1;
        arunner->run=ubjs_writer_strategy_runner_run_no_length;
        arunner->free=ubjs_writer_strategy_runner_free_no_length;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

ubjs_result ubjs_writer_strategy_true(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;
    __ubjs_writer_strategy_no_length *data;

    if(ubjs_object_true() == object)
    {
        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=(__ubjs_writer_strategy_no_length *)malloc(sizeof(struct __ubjs_writer_strategy_no_length));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        data->marker=MARKER_TRUE;
        arunner->userdata=data;
        arunner->object=object;
        arunner->length=1;
        arunner->run=ubjs_writer_strategy_runner_run_no_length;
        arunner->free=ubjs_writer_strategy_runner_free_no_length;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

ubjs_result ubjs_writer_strategy_false(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;
    __ubjs_writer_strategy_no_length *data;

    if(ubjs_object_false() == object)
    {
        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=(__ubjs_writer_strategy_no_length *)malloc(sizeof(struct __ubjs_writer_strategy_no_length));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        data->marker=MARKER_FALSE;
        arunner->userdata=data;
        arunner->object=object;
        arunner->length=1;
        arunner->run=ubjs_writer_strategy_runner_run_no_length;
        arunner->free=ubjs_writer_strategy_runner_free_no_length;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

ubjs_result ubjs_writer_strategy_int8(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_int8(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=2;
        arunner->run=ubjs_writer_strategy_runner_run_int8;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_int8(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_object_int8_get(this->object, (int8_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);

    *(data) = MARKER_INT8;
    memcpy(data + 1, value2, 1);
}

ubjs_result ubjs_writer_strategy_uint8(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_uint8(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=2;
        arunner->run=ubjs_writer_strategy_runner_run_uint8;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_uint8(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_object_uint8_get(this->object, value);
    ubjs_endian_convert_native_to_big(value, value2, 1);

    *(data) = MARKER_UINT8;
    memcpy(data + 1, value2, 1);
}

ubjs_result ubjs_writer_strategy_int16(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_int16(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=3;
        arunner->run=ubjs_writer_strategy_runner_run_int16;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_int16(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[2];
    uint8_t value2[2];

    ubjs_object_int16_get(this->object, (int16_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 2);

    *(data) = MARKER_INT16;
    memcpy(data + 1, value2, 2);
}

ubjs_result ubjs_writer_strategy_int32(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_int32(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=5;
        arunner->run=ubjs_writer_strategy_runner_run_int32;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_int32(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_object_int32_get(this->object, (int32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);

    *(data) = MARKER_INT32;
    memcpy(data + 1, value2, 4);
}

ubjs_result ubjs_writer_strategy_int64(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_int64(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=9;
        arunner->run=ubjs_writer_strategy_runner_run_int64;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_int64(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_object_int64_get(this->object, (int64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);

    *(data) = MARKER_INT64;
    memcpy(data + 1, value2, 8);
}

ubjs_result ubjs_writer_strategy_float32(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_float32(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=5;
        arunner->run=ubjs_writer_strategy_runner_run_float32;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_float32(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_object_float32_get(this->object, (float32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);

    *(data) = MARKER_FLOAT32;
    memcpy(data + 1, value2, 4);
}

ubjs_result ubjs_writer_strategy_float64(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_float64(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=9;
        arunner->run=ubjs_writer_strategy_runner_run_float64;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_float64(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_object_float64_get(this->object, (float64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);

    *(data) = MARKER_FLOAT64;
    memcpy(data + 1, value2, 8);
}

ubjs_result ubjs_writer_strategy_char(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    if(UR_OK == ubjs_object_is_char(object, &ret) && UTRUE == ret) {

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        arunner->userdata=0;
        arunner->object=object;
        arunner->length=2;
        arunner->run=ubjs_writer_strategy_runner_run_char;
        arunner->free=(ubjs_writer_strategy_runner_free)free;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_char(ubjs_writer_strategy_runner *this,uint8_t *data) {
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_object_char_get(this->object, (unsigned char *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);

    *(data) = MARKER_CHAR;
    memcpy(data + 1, value2, 1);
}
