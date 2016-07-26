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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ubjs_writer_prv.h"

unsigned int ubjs_writer_prmtv_write_strategy_array_threshold=3;

unsigned int ubjs_writer_prmtv_write_strategies_top_len = 15;
ubjs_writer_prmtv_write_strategy ubjs_writer_prmtv_write_strategies_top[] =
{
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_null,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_noop,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_true,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_false,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_int8,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_uint8,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_int16,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_int32,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_int64,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_float32,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_float64,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_char,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_str,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_array,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_object
};

unsigned int ubjs_writer_prmtv_upgrade_strategies_len = 6;
ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[] =
{
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int16,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int32,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int64,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64
};

ubjs_result ubjs_writer_new(ubjs_writer **pthis, ubjs_writer_context *context)
{
    ubjs_writer *this;

    if (0 == pthis || 0 == context || 0 == context->free)
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

ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    unsigned int i;
    ubjs_writer_prmtv_runner *arunner = 0;

    for (i=0; i<ubjs_writer_prmtv_write_strategies_top_len; i++)
    {
        ubjs_writer_prmtv_write_strategy it = ubjs_writer_prmtv_write_strategies_top[i];

        if (UR_OK == (it)(object, indent, &arunner))
        {
            *runner=arunner;
            return UR_OK;
        }
    }

    /* todo */
    return UR_ERROR;
}

ubjs_result ubjs_writer_prmtv_try_upgrade(ubjs_prmtv *original, ubjs_prmtv **pupgraded)
{
    unsigned int i;

    for (i=0; i<ubjs_writer_prmtv_upgrade_strategies_len; i++)
    {
        ubjs_writer_prmtv_upgrade_strategy it = ubjs_writer_prmtv_upgrade_strategies[i];

        if (UR_OK == (it)(original, pupgraded))
        {
            return UR_OK;
        }
    }

    return UR_ERROR;
}

ubjs_result ubjs_writer_write(ubjs_writer *this, ubjs_prmtv *object)
{
    ubjs_writer_prmtv_runner *runner=0;
    unsigned int len;
    uint8_t *data;

    if (0 == this || 0 == object || 0 == this->context->would_write)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_find_best_write_strategy(object, 0, &runner);

    len = runner->length_write + 1;
    data=(uint8_t *)malloc(sizeof(uint8_t) * (len));

    *(data) = runner->marker;
    (runner->write)(runner, data + 1);
    (this->context->would_write)(this->context, data, len);
    free(data);
    (runner->free)(runner);

    return UR_OK;
}

ubjs_result ubjs_writer_print(ubjs_writer *this, ubjs_prmtv *object)
{
    ubjs_writer_prmtv_runner *runner=0;
    unsigned int len;
    char *data;

    if (0 == this || 0 == object || 0 == this->context->would_print)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_find_best_write_strategy(object, 0, &runner);

    len = runner->length_print + 3;
    data=(char *)malloc(sizeof(char) * (len));

    *(data + 0) = '[';
    *(data + 1) = runner->marker;
    *(data + 2) = ']';
    (runner->print)(runner, data + 3);
    (this->context->would_print)(this->context, data, len);
    free(data);
    (runner->free)(runner);

    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_no_length(ubjs_writer_prmtv_runner *runner,
    uint8_t *data)
{
}

void ubjs_writer_prmtv_runner_print_no_length(ubjs_writer_prmtv_runner *runner,
    char *data)
{
}

void ubjs_writer_prmtv_runner_free_no_length(ubjs_writer_prmtv_runner *this)
{
    free(this);
}

ubjs_result ubjs_writer_prmtv_write_strategy_null(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_null() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_null;
    arunner->userdata=0;
    arunner->marker=MARKER_NULL;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    arunner->free=ubjs_writer_prmtv_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_write_strategy_noop(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_noop() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_noop;
    arunner->marker=MARKER_NOOP;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    arunner->free=ubjs_writer_prmtv_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_write_strategy_true(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_true() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_true;
    arunner->marker=MARKER_TRUE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    arunner->free=ubjs_writer_prmtv_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_write_strategy_false(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_false() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_false;
    arunner->marker=MARKER_FALSE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    arunner->free=ubjs_writer_prmtv_runner_free_no_length;
    *runner=arunner;
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_write_strategy_int8(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    int8_t value;
    char printed[7];

    ubjs_prmtv_is_int8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int8;
    arunner->marker=MARKER_INT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_int8;
    
    ubjs_prmtv_int8_get(object, &value);
    arunner->length_print = snprintf(printed, 7, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int8;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int8(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_int8_get(this->object, (int8_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_int8(ubjs_writer_prmtv_runner *this, char *data)
{
    int8_t value;
    char printed[7];
    int length;

    ubjs_prmtv_int8_get(this->object, &value);
    length = snprintf(printed, 7, "[%d]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_uint8(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    uint8_t value;
    char printed[6];

    ubjs_prmtv_is_uint8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_uint8;
    arunner->marker=MARKER_UINT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_uint8;

    ubjs_prmtv_uint8_get(object, &value);
    arunner->length_print = snprintf(printed, 6, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_uint8;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_uint8(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_uint8_get(this->object, value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_uint8(ubjs_writer_prmtv_runner *this, char *data)
{
    uint8_t value;
    char printed[6];
    int length;

    ubjs_prmtv_uint8_get(this->object, &value);
    length = snprintf(printed, 6, "[%d]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_int16(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    int16_t value;
    char printed[9];

    ubjs_prmtv_is_int16(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int16;
    arunner->marker=MARKER_INT16;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=2;
    arunner->write=ubjs_writer_prmtv_runner_write_int16;

    ubjs_prmtv_int16_get(object, &value);
    arunner->length_print = snprintf(printed, 9, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int16;
    
    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int16(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[2];
    uint8_t value2[2];

    ubjs_prmtv_int16_get(this->object, (int16_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 2);
    memcpy(data, value2, 2);
}

void ubjs_writer_prmtv_runner_print_int16(ubjs_writer_prmtv_runner *this, char *data)
{
    int16_t value;
    char printed[9];
    int length;

    ubjs_prmtv_int16_get(this->object, &value);
    length = snprintf(printed, 9, "[%d]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_int32(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    int32_t value;
    char printed[14];

    ubjs_prmtv_is_int32(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int32;
    arunner->marker=MARKER_INT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=4;
    arunner->write=ubjs_writer_prmtv_runner_write_int32;

    ubjs_prmtv_int32_get(object, &value);
    arunner->length_print = snprintf(printed, 14, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int32;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int32(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_prmtv_int32_get(this->object, (int32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);

    memcpy(data, value2, 4);
}

void ubjs_writer_prmtv_runner_print_int32(ubjs_writer_prmtv_runner *this, char *data)
{
    int32_t value;
    char printed[14];
    int length;

    ubjs_prmtv_int32_get(this->object, &value);
    length = snprintf(printed, 14, "[%d]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_int64(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    int64_t value;
    char printed[22];

    ubjs_prmtv_is_int64(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int64;
    arunner->marker=MARKER_INT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=8;
    arunner->write=ubjs_writer_prmtv_runner_write_int64;

    ubjs_prmtv_int64_get(object, &value);
    arunner->length_print = snprintf(printed, 22, "[%ld]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int64;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int64(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_prmtv_int64_get(this->object, (int64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);

    memcpy(data, value2, 8);
}

void ubjs_writer_prmtv_runner_print_int64(ubjs_writer_prmtv_runner *this, char *data)
{
    int64_t value;
    char printed[22];
    int length;

    ubjs_prmtv_int64_get(this->object, &value);
    length = snprintf(printed, 22, "[%ld]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_float32(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    float32_t value;
    /*
     * http://goo.gl/3Ajsif
     * I believe them. 1079 + null + brackets
     */
    char printed[1082];

    ubjs_prmtv_is_float32(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_float32;
    arunner->marker=MARKER_FLOAT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=4;
    arunner->write=ubjs_writer_prmtv_runner_write_float32;

    ubjs_prmtv_float32_get(object, &value);
    arunner->length_print = snprintf(printed, 1082, "[%f]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_float32;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_float32(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    uint8_t value[4];
    uint8_t value2[4];

    ubjs_prmtv_float32_get(this->object, (float32_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 4);
    memcpy(data, value2, 4);
}

void ubjs_writer_prmtv_runner_print_float32(ubjs_writer_prmtv_runner *this, char *data)
{
    float32_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float32_get(this->object, &value);
    length = snprintf(printed, 1082, "[%f]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_float64(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    float64_t value;
    /*
     * http://goo.gl/3Ajsif
     * I believe them. 1079 + null + brackets
     */
    char printed[1082];

    ubjs_prmtv_is_float64(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_float64;
    arunner->marker=MARKER_FLOAT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=8;
    arunner->write=ubjs_writer_prmtv_runner_write_float64;

    ubjs_prmtv_float64_get(object, &value);
    arunner->length_print = snprintf(printed, 1082, "[%f]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_float64;
    
    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_float64(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_prmtv_float64_get(this->object, (float64_t *)value);
    ubjs_endian_convert_native_to_big(value, value2, 8);
    memcpy(data, value2, 8);
}

void ubjs_writer_prmtv_runner_print_float64(ubjs_writer_prmtv_runner *this, char *data)
{
    float64_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float64_get(this->object, &value);
    length = snprintf(printed, 1082, "[%f]", value);
    strncpy(data, printed, length);
}

ubjs_result ubjs_writer_prmtv_write_strategy_char(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;

    ubjs_prmtv_is_char(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    arunner->strategy=ubjs_writer_prmtv_write_strategy_char;
    arunner->marker=MARKER_CHAR;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_char;

    arunner->length_print=3;
    arunner->print=ubjs_writer_prmtv_runner_print_char;

    arunner->free=(ubjs_writer_prmtv_runner_free)free;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_char(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_char_get(this->object, (char *)value);
    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_char(ubjs_writer_prmtv_runner *this, char *data)
{
    char value;

    ubjs_prmtv_char_get(this->object, &value);
    *(data + 0) = '[';
    *(data + 1) = value;
    *(data + 2) = ']';
}

ubjs_result ubjs_writer_prmtv_write_strategy_str(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_prmtv_write_strategy_context_str *data;
    ubjs_prmtv *obj_length;
    unsigned int str_length;

    ubjs_prmtv_is_str(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_str_get_length(object, &str_length);
    ubjs_prmtv_uint(str_length, &obj_length);

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_str *)malloc(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_str));
    data->length_strategy = 0;

    ubjs_writer_prmtv_find_best_write_strategy(obj_length, 0, &(data->length_strategy));

    data->length=str_length;
    data->length_obj=obj_length;

    arunner->strategy=ubjs_writer_prmtv_write_strategy_str;
    arunner->marker=MARKER_STR;
    arunner->userdata=data;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1 + data->length_strategy->length_write + str_length;
    arunner->write=ubjs_writer_prmtv_runner_write_str;

    /*
     * length marker + length + "[" + text + "]".
     */
    arunner->length_print=5 + data->length_strategy->length_print + str_length;
    arunner->print=ubjs_writer_prmtv_runner_print_str;
    
    arunner->free=ubjs_writer_prmtv_runner_free_str;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_str(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    char *text;
    
    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;
    text = (char *)malloc(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->write)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length_write + 1), text, userdata->length);

    free(text);
}

void ubjs_writer_prmtv_runner_print_str(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    char *text;
    
    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;
    text = (char *)malloc(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);
    
    *(data + 0) = '[';
    *(data + 1) = userdata->length_strategy->marker;
    *(data + 2) = ']';

    (userdata->length_strategy->print)(userdata->length_strategy, data + 3);
    *(data + 3 + userdata->length_strategy->length_print) = '[';
    strncpy((char *)(data + userdata->length_strategy->length_print + 4), text, userdata->length);
    *(data + 4 + userdata->length_strategy->length_print + userdata->length) = ']';
    
    free(text);
}

void ubjs_writer_prmtv_runner_free_str(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;

    (userdata->length_strategy->free)(userdata->length_strategy);
    ubjs_prmtv_free(&(userdata->length_obj));
    free(userdata);
    free(this);
}

ubjs_result ubjs_writer_prmtv_write_strategy_array(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_prmtv_write_strategy_context_array *data;
    unsigned int array_length;
    unsigned int items_length_write=0;
    unsigned int items_length_print=0;
    unsigned int i=0;

    ubjs_array_iterator *iterator;
    ubjs_prmtv *real_object = object;
    ubjs_prmtv *item;
    ubjs_writer_prmtv_runner *item_runner;
    ubjs_prmtv *upgraded = 0;

    ubjs_prmtv_is_array(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_array_get_length(object, &array_length);
    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_array *)malloc(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_array));
    data->item_runners=(ubjs_writer_prmtv_runner **)malloc(
        sizeof(ubjs_writer_prmtv_runner *) * array_length);
    data->length=array_length;
    data->count_strategy=0;
    data->count=0;
    data->type_strategy=0;
    data->was_upgraded=UFALSE;

    if (UR_OK == ubjs_writer_prmtv_try_upgrade(object, &upgraded))
    {
        real_object = upgraded;
        data->was_upgraded=UTRUE;
    }

    if (array_length >= ubjs_writer_prmtv_write_strategy_array_threshold)
    {
        ubjs_prmtv_uint(array_length, &(data->count));
        ubjs_writer_prmtv_find_best_write_strategy(data->count, indent, &(data->count_strategy));
    }

    ubjs_prmtv_array_iterate(real_object, &iterator);

    while (UR_OK == ubjs_array_iterator_next(iterator))
    {
        ubjs_array_iterator_get(iterator, &item);
        ubjs_writer_prmtv_find_best_write_strategy(item, indent + UBJS_SPACES_PER_INDENT,
            &item_runner);
        items_length_write += item_runner->length_write;
        items_length_print += item_runner->length_print;
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

    arunner->strategy=ubjs_writer_prmtv_write_strategy_array;
    arunner->marker=MARKER_ARRAY_BEGIN;
    arunner->userdata=data;
    arunner->object=real_object;
    arunner->indent=indent;
    data->do_indents=UFALSE;

    if (0==data->count_strategy)
    {
        /*
         * Trailing "]" + items markers + items content.
         * print: (length + 1) * "\n" + (length + 1) * indent * " "
         */
        arunner->length_write=1 + items_length_write + array_length;
        arunner->length_print=3;
        if (0 < array_length)
        {
            arunner->length_print += items_length_print + array_length * 3 + array_length + 1
                + array_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else if (0==data->type_strategy)
    {
        /*
         * "#" + length marker + length + items markers + items content.
         * print: trailing "]" + (length + 1) * "\n" + (length + 1) * indent * " ".
         */
        arunner->length_write=2 + data->count_strategy->length_write + items_length_write +
            array_length;
        arunner->length_print=9 + data->count_strategy->length_print;
        if (0 < array_length)
        {
            arunner->length_print += items_length_print + array_length * 3 + array_length + 1
                + array_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else
    {
        /*
         * "$" + type marker + "#" + length marker + length + items content.
         * print: trailing "]" + (length + 1) * "\n" + (length + 1) * indent * " "..
         */
        arunner->length_write=4 + data->count_strategy->length_write + items_length_write;
        arunner->length_print=15 + data->count_strategy->length_print;
        if (0 < array_length && 0 < items_length_print)
        {
            arunner->length_print += items_length_print + array_length + 1
                + array_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }

    arunner->write=ubjs_writer_prmtv_runner_write_array;
    arunner->print=ubjs_writer_prmtv_runner_print_array;

    arunner->free=ubjs_writer_prmtv_runner_free_array;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_array(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    ubjs_writer_prmtv_write_strategy_context_array *userdata;
    unsigned int i;
    unsigned int at = 0;

    userdata=(ubjs_writer_prmtv_write_strategy_context_array *)this->userdata;

    if (0!=userdata->type_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_TYPE;
        *(data + (at++)) = userdata->type_strategy->marker;
    }

    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = userdata->count_strategy->marker;
        (userdata->count_strategy->write)(userdata->count_strategy, data+at);
        at+=userdata->count_strategy->length_write;
    }

    for (i=0; i<userdata->length; i++)
    {
        if (0==userdata->type_strategy)
        {
            *(data + (at++)) = userdata->item_runners[i]->marker;
        }
        (userdata->item_runners[i]->write)(userdata->item_runners[i], data + at);
        at += userdata->item_runners[i]->length_write;
    }

    if (0==userdata->count_strategy)
    {
        *(data + at) = MARKER_ARRAY_END;
    }
}

void ubjs_writer_prmtv_runner_print_array(ubjs_writer_prmtv_runner *this,
    char *data)
{
    ubjs_writer_prmtv_write_strategy_context_array *userdata;
    unsigned int i, j;
    unsigned int at = 0;

    userdata=(ubjs_writer_prmtv_write_strategy_context_array *)this->userdata;

    if (0!=userdata->type_strategy)
    {
        *(data + (at++)) = '[';
        *(data + (at++)) = MARKER_OPTIMIZE_TYPE;
        *(data + (at++)) = ']';
        *(data + (at++)) = '[';
        *(data + (at++)) = userdata->type_strategy->marker;
        *(data + (at++)) = ']';
    }

    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = '[';
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = ']';
        *(data + (at++)) = '[';
        *(data + (at++)) = userdata->count_strategy->marker;
        *(data + (at++)) = ']';

        (userdata->count_strategy->print)(userdata->count_strategy, data + at);
        at+=userdata->count_strategy->length_print;
    }

    if (0 < userdata->length)
    {
        for (i=0; i<userdata->length; i++)
        {
            if (UTRUE == userdata->do_indents)
            {
                *(data + (at++)) = '\n';
                for (j=0; j < this->indent + UBJS_SPACES_PER_INDENT; j++)
                {
                    *(data + (at++)) = ' ';
                }
            }

            if (0==userdata->type_strategy)
            {
                *(data + (at++)) = '[';
                *(data + (at++)) = userdata->item_runners[i]->marker;
                *(data + (at++)) = ']';
            }
            (userdata->item_runners[i]->print)(userdata->item_runners[i], data + at);
            at += userdata->item_runners[i]->length_print;
        }

        if (UTRUE == userdata->do_indents)
        {
            *(data + (at++)) = '\n';
            for (j=0; j < this->indent; j++)
            {
                *(data + (at++)) = ' ';
            }
        }
    }

    /*
     * Yeah, this is ridicolous...
     */
    *(data + (at++)) = '[';
    *(data + (at++)) = ']';
    *(data + (at++)) = ']';
}

void ubjs_writer_prmtv_runner_free_array(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_array *userdata;
    unsigned int i;

    userdata=(ubjs_writer_prmtv_write_strategy_context_array *)this->userdata;

    for (i=0; i<userdata->length; i++)
    {
        (userdata->item_runners[i]->free)(userdata->item_runners[i]);
    }

    if (0!=userdata->count_strategy)
    {
        (userdata->count_strategy->free)(userdata->count_strategy);
    }
    
    if (UTRUE == userdata->was_upgraded)
    {
        ubjs_prmtv_free(&(this->object));
    }

    ubjs_prmtv_free(&(userdata->count));
    free(userdata->item_runners);
    free(userdata);
    free(this);
}

ubjs_result ubjs_writer_prmtv_write_strategy_object(ubjs_prmtv *object, unsigned int indent,
    ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret;
    ubjs_writer_prmtv_write_strategy_context_object *data;
    unsigned int object_length;
    unsigned int items_length_write=0;
    unsigned int items_length_print=0;
    unsigned int i=0;

    unsigned int key_length;

    ubjs_object_iterator *iterator=0;
    ubjs_prmtv *real_object = object;
    ubjs_prmtv *key = 0;
    ubjs_prmtv *value = 0;
    ubjs_writer_prmtv_runner *key_runner=0;
    ubjs_writer_prmtv_runner *value_runner=0;
    ubjs_prmtv *upgraded = 0;

    ubjs_prmtv_is_object(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object_get_length(object, &object_length);

    arunner=(ubjs_writer_prmtv_runner *)malloc(sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_object *)malloc(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_object));
    data->key_runners=(ubjs_writer_prmtv_runner **)malloc(
        sizeof(ubjs_writer_prmtv_runner *) * object_length);
    data->value_runners=(ubjs_writer_prmtv_runner **)malloc(
        sizeof(ubjs_writer_prmtv_runner *) * object_length);
    data->length=object_length;
    data->type_strategy=0;
    data->count_strategy=0;
    data->count=0;
    data->was_upgraded=UFALSE;
    
    if (UR_OK == ubjs_writer_prmtv_try_upgrade(object, &upgraded))
    {
        real_object = upgraded;
        data->was_upgraded=UTRUE;
    }

    if (object_length >= ubjs_writer_prmtv_write_strategy_array_threshold)
    {
        ubjs_prmtv_uint(object_length, &(data->count));
        ubjs_writer_prmtv_find_best_write_strategy(data->count, 0, &(data->count_strategy));
    }

    ubjs_prmtv_object_iterate(real_object, &iterator);

    while (UR_OK == ubjs_object_iterator_next(iterator))
    {
        char *key_chr;

        ubjs_object_iterator_get_key_length(iterator, &key_length);
        key_chr=(char *)malloc(sizeof(char)*key_length);
        ubjs_object_iterator_copy_key(iterator, key_chr);
        ubjs_prmtv_str(key_length, key_chr, &key);
        ubjs_writer_prmtv_write_strategy_str(key, 0, &key_runner);
        free(key_chr);

        ubjs_object_iterator_get_value(iterator, &value);
        ubjs_writer_prmtv_find_best_write_strategy(value, indent + UBJS_SPACES_PER_INDENT,
            &value_runner);

        items_length_write += key_runner->length_write + value_runner->length_write;
        items_length_print += key_runner->length_print + value_runner->length_print;
        data->key_runners[i]=key_runner;
        data->value_runners[i]=value_runner;
        
        if (0 != data->count_strategy)
        {
            if (0 == i)
            {
                data->type_strategy = value_runner;
            }
            else if (0 != data->type_strategy &&
                value_runner->strategy != data->type_strategy->strategy)
            {
                data->type_strategy = 0;
            }
        }

        i++;
    }

    ubjs_object_iterator_free(&iterator);

    arunner->strategy=ubjs_writer_prmtv_write_strategy_object;
    arunner->marker=MARKER_OBJECT_BEGIN;
    arunner->userdata=data;
    arunner->object=real_object;
    arunner->indent=indent;
    data->do_indents=UFALSE;

    if (0==data->count_strategy)
    {
        /*
         * Trailing "}" + items markers + items content.
         * print: (length + 1) * "\n" + (length + 1) * indent * " "
         */
        arunner->length_write=1 + object_length + items_length_write;
        arunner->length_print=3;
        if (0 < object_length)
        {
            arunner->length_print += items_length_print + object_length * 3 + object_length + 1
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else if (0 == data->type_strategy)
    {
        /*
         * "#" + count marker + count + items markers + items content.
         * print: trailing "}" + (length + 1) * "\n" + (length + 1) * indent * " ".
         */
        arunner->length_write=2 + data->count_strategy->length_write + object_length +
            items_length_write;
        arunner->length_print=9 + data->count_strategy->length_print;
        if (0 < object_length)
        {
            arunner->length_print += items_length_print + object_length * 3 + object_length + 1
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else
    {
        /*
         * "$" + type marker + "#" + length marker + length + items content.
         * print: trailing "}" + (length + 1) * "\n" + (length + 1) * indent * " ".
         */
        arunner->length_write=4 + data->count_strategy->length_write + items_length_write;
        arunner->length_print=15 + data->count_strategy->length_print;
        if (0 < object_length)
        {
            arunner->length_print += items_length_print + object_length + 1
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }

    arunner->write=ubjs_writer_prmtv_runner_write_object;
    arunner->print=ubjs_writer_prmtv_runner_print_object;

    arunner->free=ubjs_writer_prmtv_runner_free_object;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_object(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
    unsigned int i;
    unsigned int at = 0;

    userdata = (ubjs_writer_prmtv_write_strategy_context_object *)this->userdata;

    if (0!=userdata->type_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_TYPE;
        *(data + (at++)) = userdata->type_strategy->marker;
    }

    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = userdata->count_strategy->marker;
        (userdata->count_strategy->write)(userdata->count_strategy, data+at);
        at+=userdata->count_strategy->length_write;
    }

    for (i=0; i<userdata->length; i++)
    {
        (userdata->key_runners[i]->write)(userdata->key_runners[i], data + at);
        at += userdata->key_runners[i]->length_write;

        if (0==userdata->type_strategy)
        {
            *(data + (at++)) = userdata->value_runners[i]->marker;
        }
        (userdata->value_runners[i]->write)(userdata->value_runners[i], data + at);
        at += userdata->value_runners[i]->length_write;
    }

    if (0==userdata->count_strategy)
    {
        *(data + at) = MARKER_OBJECT_END;
    }
}

void ubjs_writer_prmtv_runner_print_object(ubjs_writer_prmtv_runner *this,
    char *data)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
    unsigned int i, j;
    unsigned int at = 0;

    userdata = (ubjs_writer_prmtv_write_strategy_context_object *)this->userdata;

    if (0!=userdata->type_strategy)
    {
        *(data + (at++)) = '[';
        *(data + (at++)) = MARKER_OPTIMIZE_TYPE;
        *(data + (at++)) = ']';
        *(data + (at++)) = '[';
        *(data + (at++)) = userdata->type_strategy->marker;
        *(data + (at++)) = ']';
    }

    if (0!=userdata->count_strategy)
    {
        *(data + (at++)) = '[';
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = ']';
        *(data + (at++)) = '[';
        *(data + (at++)) = userdata->count_strategy->marker;
        *(data + (at++)) = ']';

        (userdata->count_strategy->print)(userdata->count_strategy, data+at);
        at+=userdata->count_strategy->length_print;
    }

    if (0 < userdata->length)
    {
        for (i=0; i<userdata->length; i++)
        {
            if (UTRUE == userdata->do_indents)
            {
                *(data + (at++)) = '\n';
                for (j=0; j < this->indent + UBJS_SPACES_PER_INDENT; j++)
                {
                    *(data + (at++)) = ' ';
                }
            }

            (userdata->key_runners[i]->print)(userdata->key_runners[i], data + at);
            at += userdata->key_runners[i]->length_print;

            if (0==userdata->type_strategy)
            {
                *(data + (at++)) = '[';
                *(data + (at++)) = userdata->value_runners[i]->marker;
                *(data + (at++)) = ']';
            }

            (userdata->value_runners[i]->print)(userdata->value_runners[i], data + at);
            at += userdata->value_runners[i]->length_print;

        }
    
        if (UTRUE == userdata->do_indents)
        {
            *(data + (at++)) = '\n';
            for (j=0; j < this->indent; j++)
            {
                *(data + (at++)) = ' ';
            }
        }
    }

    /*
     * Yeah, this is ridicolous...
     */
    *(data + (at++)) = '[';
    *(data + (at++)) = '}';
    *(data + (at++)) = ']';
}

void ubjs_writer_prmtv_runner_free_object(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
    unsigned int i;

    userdata = (ubjs_writer_prmtv_write_strategy_context_object *)this->userdata;
    for (i=0; i<userdata->length; i++)
    {
        ubjs_prmtv_free(&(userdata->key_runners[i]->object));
        (userdata->key_runners[i]->free)(userdata->key_runners[i]);
        (userdata->value_runners[i]->free)(userdata->value_runners[i]);
    }

    if (UTRUE == userdata->was_upgraded)
    {
        ubjs_prmtv_free(&(this->object));
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

void ubjs_writer_prmtv_upgrade_strategy_ints_array_calculate_metrics(ubjs_prmtv *object,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *pmetrics)
{
    ubjs_array_iterator *iterator = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv_type type = 0;

    pmetrics->count_of_8=0;
    pmetrics->count_of_16=0;
    pmetrics->count_of_32=0;
    pmetrics->count_of_64=0;
    pmetrics->count_of_rest=0;
    pmetrics->count=0;

    ubjs_prmtv_array_iterate(object, &iterator);

    while (UR_OK == ubjs_array_iterator_next(iterator))
    {
        pmetrics->count++;

        ubjs_array_iterator_get(iterator, &item);
        ubjs_prmtv_get_type(item, &type);

        switch (type)
        {
            case UOT_INT8:
            case UOT_UINT8:
                pmetrics->count_of_8++;
                break;
                
            case UOT_INT16:
                pmetrics->count_of_16++;
                break;
                
            case UOT_INT32:
                pmetrics->count_of_32++;
                break;
                
            case UOT_INT64:
                pmetrics->count_of_64++;
                break;
                
            default:
                pmetrics->count_of_rest++;
                break;
        }
    }

    ubjs_array_iterator_free(&iterator);
}

void ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(ubjs_prmtv *object,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *pmetrics)
{
    ubjs_object_iterator *iterator = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv_type type = 0;

    pmetrics->count_of_8=0;
    pmetrics->count_of_16=0;
    pmetrics->count_of_32=0;
    pmetrics->count_of_64=0;
    pmetrics->count_of_rest=0;
    pmetrics->count=0;

    ubjs_prmtv_object_iterate(object, &iterator);

    while (UR_OK == ubjs_object_iterator_next(iterator))
    {
        pmetrics->count++;

        ubjs_object_iterator_get_value(iterator, &item);
        ubjs_prmtv_get_type(item, &type);

        switch (type)
        {
            case UOT_INT8:
            case UOT_UINT8:
                pmetrics->count_of_8++;
                break;
                
            case UOT_INT16:
                pmetrics->count_of_16++;
                break;
                
            case UOT_INT32:
                pmetrics->count_of_32++;
                break;
                
            case UOT_INT64:
                pmetrics->count_of_64++;
                break;
                
            default:
                pmetrics->count_of_rest++;
                break;
        }
    }

    ubjs_object_iterator_free(&iterator);
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int16(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_array_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;
    
    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_ARRAY != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_array_calculate_metrics(original, &metrics);

    /*
     * Do not optimize when there is nothing to
     * Optimize integer-only arrays.
     * Not applicable when there are any int32/int64s.
     * Not applicable when there are NO int16.
     * Not applicable when there are NO (u)int8 either.
     */
    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_32 > 0
        || metrics.count_of_64 > 0 || metrics.count_of_16 == 0  || metrics.count_of_8 == 0)
    {
        return UR_ERROR;
    }
    
    /*
     * Empirical calculation.
     * Upgrade will be fine when after upgrade there are less bytes generated then before.
     * In this case, array after upgrade will be type-optimized (=one type), and this sould
     * take less bytes then array before upgrade, that is not optimized at all
     * This is (n-k) lower-types + k high-types.
     *
     * For int8 & int16 array, the before unoptimized length is:
     *   2 + (1 + hb) * hn + (1 + lb) * ln
     *   "[" + him + lim + "]"
     * Where
     *   hb = 2 - bytes per int16
     *   hb = 1 - bytes per int8
     *   hn - count of int16
     *   ln - count of int8
     *   him - int16 primitives with markers
     *   lim - int8 primitives with markers
     *
     * After type-optimized length is:
     *   4 + count + hb * (hn + ln)
     *   "[$I#" + countm + hi
     * Where
     *   count = 1 + ceil(log256(hn + ln + 1)) - uint8/int16/int32 with length + marker
     *
     * When equaled both (of course in appropriate form), wolframalpha says that:
     *   hn >= count + 2
     */
    if (metrics.count_of_16 < ceil(log2(metrics.count + 1.0) / 8 + 3))
    {
        return UR_ERROR;
    }

    ubjs_prmtv_array(&upgraded);
    ubjs_prmtv_array_iterate(original, &it);
    
    while (UR_OK == ubjs_array_iterator_next(it))
    {
        ubjs_array_iterator_get(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int16((int16_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int16((int16_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int16(v16, &upgraded_item);
                break;

            default:
                break;
        }

        ubjs_prmtv_array_add_last(upgraded, upgraded_item);
    }
    
    ubjs_array_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int32(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_array_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;
    int32_t v32;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_ARRAY != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_array_calculate_metrics(original, &metrics);

    /*
     * Do not optimize when there is nothing to
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_64 > 0
        || metrics.count_of_32 == 0 || (metrics.count_of_16 == 0 && metrics.count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics.count_of_32 < 3 + metrics.count_of_8 + 2 * metrics.count_of_16
        + ceil(log2(metrics.count + 1.0) / 8))
    {
        return UR_ERROR;
    }

    ubjs_prmtv_array(&upgraded);
    ubjs_prmtv_array_iterate(original, &it);
    
    while (UR_OK == ubjs_array_iterator_next(it))
    {
        ubjs_array_iterator_get(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int32((int32_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int32((int32_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int32((int32_t)v16, &upgraded_item);
                break;

            case UOT_INT32:
                ubjs_prmtv_int32_get(item, &v32);
                ubjs_prmtv_int32(v32, &upgraded_item);
                break;
            default:
                break;
        }

        ubjs_prmtv_array_add_last(upgraded, upgraded_item);
    }
    
    ubjs_array_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int64(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_array_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;
    int32_t v32;
    int64_t v64;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_ARRAY != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_array_calculate_metrics(original, &metrics);

    /*
     * Do not optimize when there is nothing to.
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_64 == 0
        || (metrics.count_of_32 == 0 && metrics.count_of_16 == 0
        && metrics.count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics.count_of_64 < 3 + 3 * metrics.count_of_8 + 5 * metrics.count_of_16
        + 6 * metrics.count_of_32 + ceil(log2(metrics.count + 1.0) / 8))
    {
        return UR_ERROR;
    }

    ubjs_prmtv_array(&upgraded);
    ubjs_prmtv_array_iterate(original, &it);
    
    while (UR_OK == ubjs_array_iterator_next(it))
    {
        ubjs_array_iterator_get(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int64((int32_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int64((int32_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int64((int32_t)v16, &upgraded_item);
                break;

            case UOT_INT32:
                ubjs_prmtv_int32_get(item, &v32);
                ubjs_prmtv_int64((int64_t)v32, &upgraded_item);
                break;
                
            case UOT_INT64:
                ubjs_prmtv_int64_get(item, &v64);
                ubjs_prmtv_int64(v64, &upgraded_item);
                break;
            default:
                break;
        }

        ubjs_prmtv_array_add_last(upgraded, upgraded_item);
    }
    
    ubjs_array_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_OBJECT != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(original, &metrics);

    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_32 > 0
        || metrics.count_of_64 > 0 || metrics.count_of_16 == 0  || metrics.count_of_8 == 0)
    {
        return UR_ERROR;
    }

    if (metrics.count_of_16 < ceil(log2(metrics.count + 1.0) / 8) + 3)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object(&upgraded);
    ubjs_prmtv_object_iterate(original, &it);
    
    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        unsigned char *key;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)malloc(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int16((int16_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int16((int16_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int16(v16, &upgraded_item);
                break;

            default:
                break;
        }

        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        free(key);
    }
    
    ubjs_object_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;
    int32_t v32;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_OBJECT != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(original, &metrics);

    /*
     * Do not optimize when there is nothing to
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_64 > 0
        || metrics.count_of_32 == 0 || (metrics.count_of_16 == 0 && metrics.count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics.count_of_32 < 3 + metrics.count_of_8 + 2 * metrics.count_of_16
        + ceil(log2(metrics.count + 1.0) / 8))
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object(&upgraded);
    ubjs_prmtv_object_iterate(original, &it);
    
    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        unsigned char *key;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)malloc(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int32((int32_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int32((int32_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int32((int32_t)v16, &upgraded_item);
                break;

            case UOT_INT32:
                ubjs_prmtv_int32_get(item, &v32);
                ubjs_prmtv_int32(v32, &upgraded_item);
                break;
            default:
                break;
        }

        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        free(key);
    }
    
    ubjs_object_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64(ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;
    ubjs_prmtv_type item_type;

    uint8_t v8u;
    int8_t v8;
    int16_t v16;
    int32_t v32;
    int64_t v64;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_OBJECT != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(original, &metrics);

    /*
     * Do not optimize when there is nothing to.
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics.count < 2 || metrics.count_of_rest > 0 || metrics.count_of_64 == 0
        || (metrics.count_of_32 == 0 && metrics.count_of_16 == 0
        && metrics.count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics.count_of_64 < 3 + 3 * metrics.count_of_8 + 5 * metrics.count_of_16
     + 6 * metrics.count_of_32 + ceil(log2(metrics.count + 1.0) / 8))
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object(&upgraded);
    ubjs_prmtv_object_iterate(original, &it);
    
    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        unsigned char *key;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)malloc(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_get_type(item, &item_type);
        
        switch (item_type)
        {
            case UOT_UINT8:
                ubjs_prmtv_uint8_get(item, &v8u);
                ubjs_prmtv_int64((int32_t) v8u, &upgraded_item);
                break;

            case UOT_INT8:
                ubjs_prmtv_int8_get(item, &v8);
                ubjs_prmtv_int64((int32_t) v8, &upgraded_item);
                break;

            case UOT_INT16:
                ubjs_prmtv_int16_get(item, &v16);
                ubjs_prmtv_int64((int32_t)v16, &upgraded_item);
                break;

            case UOT_INT32:
                ubjs_prmtv_int32_get(item, &v32);
                ubjs_prmtv_int64((int64_t)v32, &upgraded_item);
                break;
                
            case UOT_INT64:
                ubjs_prmtv_int64_get(item, &v64);
                ubjs_prmtv_int64(v64, &upgraded_item);
                break;
            default:
                break;
        }

        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        free(key);
    }
    
    ubjs_object_iterator_free(&it);
    
    *pupgraded = upgraded;
    
    return UR_OK;
}
