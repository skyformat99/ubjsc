#include <stdlib.h>
#include <string.h>

#include "../include/ubjs_writer.h"
#include "ubjs_writer_internal.h"

typedef struct __ubjs_writer_strategy_no_length __ubjs_writer_strategy_no_length;
typedef struct __ubjs_writer_strategy_str __ubjs_writer_strategy_str;
typedef struct __ubjs_writer_strategy_array __ubjs_writer_strategy_array;

int ubjs_writer_strategies_top_len = 14;
ubjs_writer_strategy ubjs_writer_strategies_top[] =
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
    (ubjs_writer_strategy)ubjs_writer_strategy_char,
    (ubjs_writer_strategy)ubjs_writer_strategy_str,
    (ubjs_writer_strategy)ubjs_writer_strategy_array
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

static void ubjs_writer_strategy_runner_run_str(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_free_str(ubjs_writer_strategy_runner *);

static void ubjs_writer_strategy_runner_run_array(ubjs_writer_strategy_runner *,uint8_t *);
static void ubjs_writer_strategy_runner_free_array(ubjs_writer_strategy_runner *);

struct ubjs_writer
{
    ubjs_writer_context *context;
};

struct __ubjs_writer_strategy_no_length {
    uint8_t marker;
};

struct __ubjs_writer_strategy_str {
    ubjs_writer_strategy_runner *length_strategy;
    int length;
    ubjs_object *length_obj;
};

struct __ubjs_writer_strategy_array {
    ubjs_writer_strategy_runner **item_runners;
    int length;
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

ubjs_result ubjs_writer_strategy_find_best_top(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    int i;
    ubjs_writer_strategy_runner *arunner = 0;

    for(i=0; i<ubjs_writer_strategies_top_len; i++)
    {
        ubjs_writer_strategy it = ubjs_writer_strategies_top[i];

        if(UR_OK == (it)(object, &arunner))
        {
            *runner=arunner;
            return UR_OK;
        }
    }

    //todo
    return UR_ERROR;
}


ubjs_result ubjs_writer_strategy_find_best_length(unsigned int value, ubjs_object **obj) {
    if(255 >= value) {
        return ubjs_object_uint8((uint8_t)value, obj);
    } else if(32767 >= value) {
        return ubjs_object_int16((int16_t)value, obj);
    } else if(2147483647 >= value) {
        return ubjs_object_int32((int32_t)value, obj);
    }

    return UR_ERROR;
}

ubjs_result ubjs_writer_write(ubjs_writer *this,ubjs_object *object)
{
    if(0 == this || 0 == object)
    {
        return UR_ERROR;
    }

    ubjs_writer_strategy_runner *runner=0;

    if(UR_ERROR == ubjs_writer_strategy_find_best_top(object, &runner))
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

    ubjs_object_char_get(this->object, (char *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);

    *(data) = MARKER_CHAR;
    memcpy(data + 1, value2, 1);
}

ubjs_result ubjs_writer_strategy_str(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;
    __ubjs_writer_strategy_str *data;
    ubjs_object *obj_length;
    unsigned int str_length;

    if(UR_OK == ubjs_object_is_str(object, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_object_str_get_length(object, &str_length)) {
            return UR_ERROR;
        }

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=( __ubjs_writer_strategy_str *)malloc(sizeof(struct __ubjs_writer_strategy_str));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        if(UR_ERROR == ubjs_writer_strategy_find_best_length(str_length, &obj_length)) {
            free(data);
            free(arunner);
            return UR_ERROR;
        }

        if(UR_ERROR == ubjs_writer_strategy_find_best_top(obj_length, &(data->length_strategy))) {
            ubjs_object_free(&obj_length);
            free(data);
            free(arunner);
            return UR_ERROR;
        }

        data->length=str_length;
        data->length_obj=obj_length;

        arunner->userdata=data;
        arunner->object=object;
        arunner->length=1 + data->length_strategy->length + str_length;
        arunner->run=ubjs_writer_strategy_runner_run_str;
        arunner->free=ubjs_writer_strategy_runner_free_str;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_str(ubjs_writer_strategy_runner *this,uint8_t *data) {
    __ubjs_writer_strategy_str *userdata=(__ubjs_writer_strategy_str *)this->userdata;
    char *text=(char *)malloc(sizeof(char)*(userdata->length));

    ubjs_object_str_copy_text(this->object, text);

    *(data) = MARKER_STR;
    (userdata->length_strategy->run)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length + 1), text, userdata->length);

    free(text);
}

static void ubjs_writer_strategy_runner_free_str(ubjs_writer_strategy_runner *this) {
    __ubjs_writer_strategy_str *data=(__ubjs_writer_strategy_str *)this->userdata;

    (data->length_strategy->free)(data->length_strategy);
    ubjs_object_free(&(data->length_obj));
    free(data);
    free(this);
}

ubjs_result ubjs_writer_strategy_array(ubjs_object *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;
    __ubjs_writer_strategy_array *data;
    unsigned int array_length;
    unsigned int items_length=0;
    unsigned int i=0;

    ubjs_array_iterator *iterator;
    ubjs_object *item;
    ubjs_writer_strategy_runner *item_runner;

    if(UR_OK == ubjs_object_is_array(object, &ret) && UTRUE == ret) {
        if(UR_ERROR == ubjs_object_array_get_length(object, &array_length)) {
            return UR_ERROR;
        }

        arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
        if(arunner == 0) {
            return UR_ERROR;
        }

        data=( __ubjs_writer_strategy_array *)malloc(sizeof(struct __ubjs_writer_strategy_array));
        if(data==0) {
            free(arunner);
            return UR_ERROR;
        }

        data->item_runners=(ubjs_writer_strategy_runner **)malloc(sizeof(ubjs_writer_strategy_runner *) * array_length);
        if(0 == data->item_runners) {
            free(data);
            free(arunner);
            return UR_ERROR;
        }

        data->length=array_length;

        if(UR_ERROR == ubjs_object_array_iterate_forward(object, &iterator)) {
            free(data->item_runners);
            free(data);
            free(arunner);
            return UR_ERROR;
        }

        while(UR_OK == ubjs_array_iterator_next(iterator)) {
            if(UR_ERROR == ubjs_array_iterator_get(iterator, &item)) {
                free(data);
                free(arunner);
                ubjs_array_iterator_free(&iterator);
                return UR_ERROR;
            }

            if(UR_ERROR == ubjs_writer_strategy_find_best_top(item, &item_runner)) {
                free(data);
                free(arunner);
                ubjs_array_iterator_free(&iterator);
                return UR_ERROR;
            }

            items_length += item_runner->length;
            data->item_runners[i]=item_runner;
            i++;
        }

        ubjs_array_iterator_free(&iterator);

        arunner->userdata=data;
        arunner->object=object;
        arunner->length=2 + items_length;
        arunner->run=ubjs_writer_strategy_runner_run_array;
        arunner->free=ubjs_writer_strategy_runner_free_array;
        *runner=arunner;
        return UR_OK;
    }
    return UR_ERROR;
}

static void ubjs_writer_strategy_runner_run_array(ubjs_writer_strategy_runner *this,uint8_t *data) {
    __ubjs_writer_strategy_array *userdata=(__ubjs_writer_strategy_array *)this->userdata;
    unsigned int i;
    unsigned int at = 1;

    *(data) = MARKER_ARRAY_BEGIN;

    for(i=0; i<userdata->length; i++) {
        (userdata->item_runners[i]->run)(userdata->item_runners[i], data + at);
        at += userdata->item_runners[i]->length;
    }

    *(data + at) = MARKER_ARRAY_END;
}

static void ubjs_writer_strategy_runner_free_array(ubjs_writer_strategy_runner *this) {
    __ubjs_writer_strategy_array *userdata=(__ubjs_writer_strategy_array *)this->userdata;
    unsigned int i;

    for(i=0; i<userdata->length; i++) {
        (userdata->item_runners[i]->free)(userdata->item_runners[i]);
    }

    free(userdata->item_runners);
    free(userdata);
    free(this);
}
