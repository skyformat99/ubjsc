/*
 * Copyright (c) 2016 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <stdlib.h>
#include <string.h>

#include "../include/ubjs_writer.h"
#include "ubjs_writer_internal.h"

typedef struct ubjs_writer_strategy_context_no_length ubjs_writer_strategy_context_no_length;
typedef struct ubjs_writer_strategy_context_str ubjs_writer_strategy_context_str;
typedef struct ubjs_writer_strategy_context_array ubjs_writer_strategy_context_array;
typedef struct ubjs_writer_strategy_context_object ubjs_writer_strategy_context_object;

unsigned int ubjs_writer_strategy_array_threshold=3;

unsigned int ubjs_writer_strategies_top_len = 15;
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
    (ubjs_writer_strategy)ubjs_writer_strategy_array,
    (ubjs_writer_strategy)ubjs_writer_strategy_object
};

static void ubjs_writer_strategy_runner_run_no_length(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_free_no_length(ubjs_writer_strategy_runner *);
static void ubjs_writer_strategy_runner_run_int8(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_uint8(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_int16(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_int32(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_int64(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_float32(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_float64(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_run_char(ubjs_writer_strategy_runner *, uint8_t *);

static void ubjs_writer_strategy_runner_run_str(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_free_str(ubjs_writer_strategy_runner *);

static void ubjs_writer_strategy_runner_run_array(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_free_array(ubjs_writer_strategy_runner *);

static void ubjs_writer_strategy_runner_run_object(ubjs_writer_strategy_runner *, uint8_t *);
static void ubjs_writer_strategy_runner_free_object(ubjs_writer_strategy_runner *);

struct ubjs_writer
{
    ubjs_writer_context *context;
};

struct ubjs_writer_strategy_context_no_length
{
    uint8_t marker;
};

struct ubjs_writer_strategy_context_str
{
    ubjs_writer_strategy_runner *length_strategy;
    unsigned int length;
    ubjs_prmtv *length_obj;
};

struct ubjs_writer_strategy_context_array
{
    ubjs_writer_strategy_runner **item_runners;
    unsigned int length;
    ubjs_prmtv *count;
    ubjs_writer_strategy_runner *type_strategy;
    ubjs_writer_strategy_runner *count_strategy;
};

struct ubjs_writer_strategy_context_object
{
    ubjs_writer_strategy_runner **key_runners;
    ubjs_writer_strategy_runner **value_runners;
    unsigned int length;
    ubjs_prmtv *count;
    ubjs_writer_strategy_runner *count_strategy;
};

ubjs_result ubjs_writer_new(ubjs_writer **pthis, ubjs_writer_context *context)
{
    ubjs_writer *this;

    if (0 == pthis || 0 == context)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer *)malloc(sizeof(struct ubjs_writer));

    this->context=context;
    *pthis=this;

    return UR_OK;
}

ubjs_result ubjs_writer_free(ubjs_writer **pthis)
{
    ubjs_writer *this;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;

    (this->context->free)(this->context);
    free(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_writer_get_context(ubjs_writer *this, ubjs_writer_context **context)
{
    if (0 == this || 0 == context)
    {
        return UR_ERROR;
    }
    *context = this->context;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_find_best_top(ubjs_prmtv *object,
    ubjs_writer_strategy_runner **runner)
{
    unsigned int i;
    ubjs_writer_strategy_runner *arunner = 0;

    for (i=0; i<ubjs_writer_strategies_top_len; i++)
    {
        ubjs_writer_strategy it = ubjs_writer_strategies_top[i];

        if (UR_OK == (it)(object, &arunner))
        {
            *runner=arunner;
            return UR_OK;
        }
    }

    /* todo */
    return UR_ERROR;
}

ubjs_result ubjs_writer_strategy_find_best_length(unsigned int value, ubjs_prmtv **obj)
{
    if (255 >= value)
    {
        return ubjs_prmtv_uint8((uint8_t)value, obj);
    }
    else if (32767 >= value)
    {
        return ubjs_prmtv_int16((int16_t)value, obj);
    }
    else if (2147483647 >= value)
    {
        return ubjs_prmtv_int32((int32_t)value, obj);
    }

    return UR_ERROR;
}

ubjs_result ubjs_writer_write(ubjs_writer *this, ubjs_prmtv *object)
{
    ubjs_writer_strategy_runner *runner=0;
    unsigned int len;
    uint8_t *data;

    if (0 == this || 0 == object)
    {
        return UR_ERROR;
    }

    ubjs_writer_strategy_find_best_top(object, &runner);

    len = runner->length + 1;
    data=(uint8_t *)malloc(sizeof(uint8_t) * (len));

    *(data + 0) = runner->marker;
    (runner->run)(runner, data + 1);
    (this->context->would_write)(this->context->userdata, data, len);
    free(data);
    (runner->free)(runner);

    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_no_length(ubjs_writer_strategy_runner *runner,
    uint8_t *data)
{
}

static void ubjs_writer_strategy_runner_free_no_length(ubjs_writer_strategy_runner *this)
{
    free(this);
}

ubjs_result ubjs_writer_strategy_null(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;

    if (ubjs_prmtv_null() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_null;
    arunner->userdata=0;
    arunner->marker=MARKER_NULL;
    arunner->object=object;
    arunner->length=0;
    arunner->run=ubjs_writer_strategy_runner_run_no_length;
    arunner->free=ubjs_writer_strategy_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_noop(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;

    if (ubjs_prmtv_noop() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_noop;
    arunner->marker=MARKER_NOOP;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=0;
    arunner->run=ubjs_writer_strategy_runner_run_no_length;
    arunner->free=ubjs_writer_strategy_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_true(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;

    if (ubjs_prmtv_true() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_true;
    arunner->marker=MARKER_TRUE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=0;
    arunner->run=ubjs_writer_strategy_runner_run_no_length;
    arunner->free=ubjs_writer_strategy_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_false(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner;

    if (ubjs_prmtv_false() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_false;
    arunner->marker=MARKER_FALSE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=0;
    arunner->run=ubjs_writer_strategy_runner_run_no_length;
    arunner->free=ubjs_writer_strategy_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_strategy_int8(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_int8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_int8;
    arunner->marker=MARKER_INT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=1;
    arunner->run=ubjs_writer_strategy_runner_run_int8;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_int8(ubjs_writer_strategy_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_int8_get(this->object, (int8_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

ubjs_result ubjs_writer_strategy_uint8(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_uint8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_uint8;
    arunner->marker=MARKER_UINT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=1;
    arunner->run=ubjs_writer_strategy_runner_run_uint8;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_uint8(ubjs_writer_strategy_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_uint8_get(this->object, value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

ubjs_result ubjs_writer_strategy_int16(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_int16(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_int16;
    arunner->marker=MARKER_INT16;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=2;
    arunner->run=ubjs_writer_strategy_runner_run_int16;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_int16(ubjs_writer_strategy_runner *this, uint8_t *data)
{
    uint8_t value[2];
    uint8_t value2[2];

    ubjs_prmtv_int16_get(this->object, (int16_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 2);
    memcpy(data, value2, 2);
}

ubjs_result ubjs_writer_strategy_int32(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_int32(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_int32;
    arunner->marker=MARKER_INT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=4;
    arunner->run=ubjs_writer_strategy_runner_run_int32;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_int32(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_prmtv_int32_get(this->object, (int32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);

    memcpy(data, value2, 4);
}

ubjs_result ubjs_writer_strategy_int64(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_int64(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_int64;
    arunner->marker=MARKER_INT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=8;
    arunner->run=ubjs_writer_strategy_runner_run_int64;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_int64(ubjs_writer_strategy_runner *this, uint8_t *data)
{
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_prmtv_int64_get(this->object, (int64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);

    memcpy(data, value2, 8);
}

ubjs_result ubjs_writer_strategy_float32(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_float32(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_float32;
    arunner->marker=MARKER_FLOAT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=4;
    arunner->run=ubjs_writer_strategy_runner_run_float32;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_float32(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_prmtv_float32_get(this->object, (float32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);
    memcpy(data, value2, 4);
}

ubjs_result ubjs_writer_strategy_float64(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_float64(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_float64;
    arunner->marker=MARKER_FLOAT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=8;
    arunner->run=ubjs_writer_strategy_runner_run_float64;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_float64(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_prmtv_float64_get(this->object, (float64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);
    memcpy(data, value2, 8);
}

ubjs_result ubjs_writer_strategy_char(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_char(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    arunner->strategy=ubjs_writer_strategy_char;
    arunner->marker=MARKER_CHAR;
    arunner->userdata=0;
    arunner->object=object;
    arunner->length=1;
    arunner->run=ubjs_writer_strategy_runner_run_char;
    arunner->free=(ubjs_writer_strategy_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_char(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_char_get(this->object, (char *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

ubjs_result ubjs_writer_strategy_str(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_strategy_context_str *data;
    ubjs_prmtv *obj_length;
    unsigned int str_length;

    ubjs_prmtv_is_str(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_str_get_length(object, &str_length);
    ubjs_writer_strategy_find_best_length(str_length, &obj_length);

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    data=(ubjs_writer_strategy_context_str *)malloc(
        sizeof(struct ubjs_writer_strategy_context_str));
    data->length_strategy = 0;

    ubjs_writer_strategy_find_best_top(obj_length, &(data->length_strategy));

    data->length=str_length;
    data->length_obj=obj_length;

    arunner->strategy=ubjs_writer_strategy_str;
    arunner->marker=MARKER_STR;
    arunner->userdata=data;
    arunner->object=object;
    arunner->length=1 + data->length_strategy->length + str_length;
    arunner->run=ubjs_writer_strategy_runner_run_str;
    arunner->free=ubjs_writer_strategy_runner_free_str;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_str(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    ubjs_writer_strategy_context_str *userdata=(ubjs_writer_strategy_context_str *)this->userdata;
    char *text=(char *)malloc(sizeof(char)*(userdata->length));

    ubjs_prmtv_str_copy_text(this->object, text);

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->run)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length + 1), text, userdata->length);

    free(text);
}

static void ubjs_writer_strategy_runner_free_str(ubjs_writer_strategy_runner *this)
{
    ubjs_writer_strategy_context_str *data=(ubjs_writer_strategy_context_str *)this->userdata;

    (data->length_strategy->free)(data->length_strategy);
    ubjs_prmtv_free(&(data->length_obj));
    free(data);
    free(this);
}

ubjs_result ubjs_writer_strategy_array(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_strategy_context_array *data;
    unsigned int array_length;
    unsigned int items_length=0;
    unsigned int i=0;

    ubjs_array_iterator *iterator;
    ubjs_prmtv *item;
    ubjs_writer_strategy_runner *item_runner;

    ubjs_prmtv_is_array(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_array_get_length(object, &array_length);
    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    data=(ubjs_writer_strategy_context_array *)malloc(
        sizeof(struct ubjs_writer_strategy_context_array));
    data->item_runners=(ubjs_writer_strategy_runner **)malloc(
        sizeof(ubjs_writer_strategy_runner *) * array_length);
    data->length=array_length;
    data->count_strategy=0;
    data->count=0;
    data->type_strategy=0;

    if (array_length >= ubjs_writer_strategy_array_threshold)
    {
        ubjs_writer_strategy_find_best_length(array_length, &(data->count));
        ubjs_writer_strategy_find_best_top(data->count, &(data->count_strategy));
    }

    ubjs_prmtv_array_iterate(object, &iterator);

    while (UR_OK == ubjs_array_iterator_next(iterator))
    {
        ubjs_array_iterator_get(iterator, &item);
        ubjs_writer_strategy_find_best_top(item, &item_runner);
        items_length += item_runner->length;
        data->item_runners[i]=item_runner;

        if (0 != data->count_strategy)
        {
            if (0 == i)
            {
                data->type_strategy = item_runner;
            }
            else if (0 != data->type_strategy &&
                item_runner->strategy != data->type_strategy->strategy)
            {
                data->type_strategy = 0;
            }
        }
        i++;
    }

    ubjs_array_iterator_free(&iterator);

    arunner->strategy=ubjs_writer_strategy_array;
    arunner->marker=MARKER_ARRAY_BEGIN;
    arunner->userdata=data;
    arunner->object=object;

    if (0==data->count_strategy)
    {
        arunner->length=1 + items_length + array_length;
    }
    else if (0==data->type_strategy)
    {
        arunner->length=2 + items_length + data->count_strategy->length + array_length;
    }
    else
    {
        arunner->length=4 + items_length + data->count_strategy->length;
    }

    arunner->run=ubjs_writer_strategy_runner_run_array;
    arunner->free=ubjs_writer_strategy_runner_free_array;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_array(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    ubjs_writer_strategy_context_array *userdata;
    unsigned int i;
    unsigned int at = 0;

    userdata=(ubjs_writer_strategy_context_array *)this->userdata;

    if (0!=userdata->type_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_TYPE;
        *(data + (at++)) = userdata->type_strategy->marker;
    }

    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = userdata->count_strategy->marker;
        (userdata->count_strategy->run)(userdata->count_strategy, data+at);
        at+=userdata->count_strategy->length;
    }

    for (i=0; i<userdata->length; i++)
    {
        if (0==userdata->type_strategy)
        {
            *(data + (at++)) = userdata->item_runners[i]->marker;
        }
        (userdata->item_runners[i]->run)(userdata->item_runners[i], data + at);
        at += userdata->item_runners[i]->length;
    }

    if (0==userdata->count_strategy)
    {
        *(data + at) = MARKER_ARRAY_END;
    }
}

static void ubjs_writer_strategy_runner_free_array(ubjs_writer_strategy_runner *this)
{
    ubjs_writer_strategy_context_array *userdata;
    unsigned int i;

    userdata=(ubjs_writer_strategy_context_array *)this->userdata;

    for (i=0; i<userdata->length; i++)
    {
        (userdata->item_runners[i]->free)(userdata->item_runners[i]);
    }

    if (0!=userdata->count_strategy)
    {
        (userdata->count_strategy->free)(userdata->count_strategy);
    }

    ubjs_prmtv_free(&(userdata->count));
    free(userdata->item_runners);
    free(userdata);
    free(this);
}

ubjs_result ubjs_writer_strategy_object(ubjs_prmtv *object, ubjs_writer_strategy_runner **runner)
{
    ubjs_writer_strategy_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_strategy_context_object *data;
    unsigned int object_length;
    unsigned int items_length=0;
    unsigned int i=0;

    unsigned int key_length;
    char *key_chr;

    ubjs_object_iterator *iterator=0;
    ubjs_prmtv *key = 0;
    ubjs_prmtv *value=0;
    ubjs_writer_strategy_runner *key_runner=0;
    ubjs_writer_strategy_runner *value_runner=0;

    ubjs_prmtv_is_object(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object_get_length(object, &object_length);

    arunner=(ubjs_writer_strategy_runner *)malloc(sizeof(struct ubjs_writer_strategy_runner));
    data=(ubjs_writer_strategy_context_object *)malloc(
        sizeof(struct ubjs_writer_strategy_context_object));
    data->key_runners=(ubjs_writer_strategy_runner **)malloc(
        sizeof(ubjs_writer_strategy_runner *) * object_length);
    data->value_runners=(ubjs_writer_strategy_runner **)malloc(
        sizeof(ubjs_writer_strategy_runner *) * object_length);
    data->length=object_length;
    data->count_strategy=0;
    data->count=0;

    if (object_length >= ubjs_writer_strategy_array_threshold)
    {
        ubjs_writer_strategy_find_best_length(object_length, &(data->count));
        ubjs_writer_strategy_find_best_top(data->count, &(data->count_strategy));
    }

    ubjs_prmtv_object_iterate(object, &iterator);

    while (UR_OK == ubjs_object_iterator_next(iterator))
    {
        ubjs_object_iterator_get_key_length(iterator, &key_length);
        key_chr=(char *)malloc(sizeof(char)*key_length);
        ubjs_object_iterator_copy_key(iterator, key_chr);
        ubjs_prmtv_str(key_length, key_chr, &key);
        ubjs_writer_strategy_str(key, &key_runner);
        free(key_chr);

        ubjs_object_iterator_get_value(iterator, &value);
        ubjs_writer_strategy_find_best_top(value, &value_runner);

        items_length += 1 + key_runner->length + value_runner->length;
        data->key_runners[i]=key_runner;
        data->value_runners[i]=value_runner;
        i++;
    }

    ubjs_object_iterator_free(&iterator);

    arunner->strategy=ubjs_writer_strategy_object;
    arunner->marker=MARKER_OBJECT_BEGIN;
    arunner->userdata=data;
    arunner->object=object;
    if (0!=data->count_strategy)
    {
        arunner->length=2 + items_length + data->count_strategy->length;
    }
    else
    {
        arunner->length=1 + items_length;
    }

    arunner->run=ubjs_writer_strategy_runner_run_object;
    arunner->free=ubjs_writer_strategy_runner_free_object;
    *runner=arunner;
    return UR_OK;
}

static void ubjs_writer_strategy_runner_run_object(ubjs_writer_strategy_runner *this,
    uint8_t *data)
{
    ubjs_writer_strategy_context_object *userdata;
    unsigned int i;
    unsigned int at = 0;

    userdata = (ubjs_writer_strategy_context_object *)this->userdata;
    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = userdata->count_strategy->marker;
        (userdata->count_strategy->run)(userdata->count_strategy, data+at);
        at+=userdata->count_strategy->length;
    }

    for (i=0; i<userdata->length; i++)
    {
        (userdata->key_runners[i]->run)(userdata->key_runners[i], data + at);
        at += userdata->key_runners[i]->length;

        *(data + (at++)) = userdata->value_runners[i]->marker;
        (userdata->value_runners[i]->run)(userdata->value_runners[i], data + at);
        at += userdata->value_runners[i]->length;
    }

    if (0==userdata->count_strategy)
    {
        *(data + at) = MARKER_OBJECT_END;
    }
}

static void ubjs_writer_strategy_runner_free_object(ubjs_writer_strategy_runner *this)
{
    ubjs_writer_strategy_context_object *userdata;
    unsigned int i;

    userdata = (ubjs_writer_strategy_context_object *)this->userdata;
    for (i=0; i<userdata->length; i++)
    {
        ubjs_prmtv_free(&(userdata->key_runners[i]->object));
        (userdata->key_runners[i]->free)(userdata->key_runners[i]);
        (userdata->value_runners[i]->free)(userdata->value_runners[i]);
    }

    if (0!=userdata->count_strategy)
    {
        (userdata->count_strategy->free)(userdata->count_strategy);
    }

    ubjs_prmtv_free(&(userdata->count));

    free(userdata->key_runners);
    free(userdata->value_runners);

    free(userdata);
    free(this);
}
