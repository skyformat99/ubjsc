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
#include <string.h>

#include "ubjs_writer_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

unsigned int ubjs_writer_prmtv_write_strategy_array_threshold=3;

unsigned int ubjs_writer_prmtv_write_strategies_top_len = 16;
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
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_hpn,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_array,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_object
};

unsigned int ubjs_writer_prmtv_upgrade_strategies_len = 2;
ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[] =
{
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_array,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_object
};

ubjs_result ubjs_writer_new(ubjs_library *lib, ubjs_writer **pthis, ubjs_writer_context *context)
{
    ubjs_writer *this;

    if (0 == lib || 0 == pthis || 0 == context || 0 == context->free)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer *)(lib->alloc_f)(sizeof(struct ubjs_writer));
    this->lib=lib;
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
    (this->lib->free_f)(this);

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

ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_writer *this, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    unsigned int i;
    ubjs_writer_prmtv_runner *arunner = 0;

    for (i=0; i<ubjs_writer_prmtv_write_strategies_top_len; i++)
    {
        ubjs_writer_prmtv_write_strategy it = ubjs_writer_prmtv_write_strategies_top[i];

        if (UR_OK == (it)(this, object, indent, &arunner))
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

    ubjs_writer_prmtv_find_best_write_strategy(this, object, 0, &runner);

    len = runner->length_write + 1;
    data=(uint8_t *)(this->lib->alloc_f)(sizeof(uint8_t) * (len));

    *(data) = runner->marker;
    (runner->write)(runner, data + 1);
    (this->context->would_write)(this->context, data, len);
    (this->lib->free_f)(data);
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

    ubjs_writer_prmtv_find_best_write_strategy(this, object, 0, &runner);

    len = runner->length_print + 3;
    data=(char *)(this->lib->alloc_f)(sizeof(char) * (len));

    *(data + 0) = '[';
    *(data + 1) = runner->marker;
    *(data + 2) = ']';
    (runner->print)(runner, data + 3);
    (this->context->would_print)(this->context, data, len);
    (this->lib->free_f)(data);
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
    (this->lib->free_f)(this);
}

ubjs_result ubjs_writer_prmtv_write_strategy_null(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_null() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

ubjs_result ubjs_writer_prmtv_write_strategy_noop(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_noop() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

ubjs_result ubjs_writer_prmtv_write_strategy_true(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_true() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

ubjs_result ubjs_writer_prmtv_write_strategy_false(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner;

    if (ubjs_prmtv_false() != object)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

ubjs_result ubjs_writer_prmtv_write_strategy_int8(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    int8_t value;
    char printed[7];

    ubjs_prmtv_is_int8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_uint8(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    uint8_t value;
    char printed[6];

    ubjs_prmtv_is_uint8(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_int16(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    int16_t value;
    char printed[9];

    ubjs_prmtv_is_int16(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_int32(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    int32_t value;
    char printed[14];

    ubjs_prmtv_is_int32(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_int64(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    int64_t value;
    char printed[22];

    ubjs_prmtv_is_int64(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_float32(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

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

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_float64(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

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

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
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

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_char(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;

    ubjs_prmtv_is_char(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    arunner->lib=writer->lib;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_char;
    arunner->marker=MARKER_CHAR;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_char;

    arunner->length_print=3;
    arunner->print=ubjs_writer_prmtv_runner_print_char;

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
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

ubjs_result ubjs_writer_prmtv_write_strategy_str(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;
    ubjs_writer_prmtv_write_strategy_context_str *data;
    ubjs_prmtv *obj_length;
    unsigned int str_length;

    ubjs_prmtv_is_str(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_str_get_length(object, &str_length);
    ubjs_prmtv_uint(writer->lib, str_length, &obj_length);

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_str *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_str));
    data->length_strategy = 0;

    ubjs_writer_prmtv_find_best_write_strategy(writer, obj_length, 0, &(data->length_strategy));

    data->length=str_length;
    data->length_obj=obj_length;

    arunner->lib=writer->lib;
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
    text = (char *)(this->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->write)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length_write + 1), text, userdata->length);

    (this->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_print_str(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    char *text;

    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;
    text = (char *)(this->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);

    *(data + 0) = '[';
    *(data + 1) = userdata->length_strategy->marker;
    *(data + 2) = ']';

    (userdata->length_strategy->print)(userdata->length_strategy, data + 3);
    *(data + 3 + userdata->length_strategy->length_print) = '[';
    strncpy((char *)(data + userdata->length_strategy->length_print + 4), text, userdata->length);
    *(data + 4 + userdata->length_strategy->length_print + userdata->length) = ']';

    (this->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_free_str(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;

    (userdata->length_strategy->free)(userdata->length_strategy);
    ubjs_prmtv_free(&(userdata->length_obj));
    (this->lib->free_f)(userdata);
    (this->lib->free_f)(this);
}

ubjs_result ubjs_writer_prmtv_write_strategy_hpn(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;
    ubjs_writer_prmtv_write_strategy_context_hpn *data;
    ubjs_prmtv *obj_length;
    unsigned int str_length;

    ubjs_prmtv_is_hpn(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_hpn_get_length(object, &str_length);
    ubjs_prmtv_uint(writer->lib, str_length, &obj_length);

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_hpn *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_hpn));
    data->length_strategy = 0;

    ubjs_writer_prmtv_find_best_write_strategy(writer, obj_length, 0, &(data->length_strategy));

    data->length=str_length;
    data->length_obj=obj_length;

    arunner->lib=writer->lib;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_hpn;
    arunner->marker=MARKER_HPN;
    arunner->userdata=data;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1 + data->length_strategy->length_write + str_length;
    arunner->write=ubjs_writer_prmtv_runner_write_hpn;

    /*
     * length marker + length + "[" + text + "]".
     */
    arunner->length_print=5 + data->length_strategy->length_print + str_length;
    arunner->print=ubjs_writer_prmtv_runner_print_hpn;

    arunner->free=ubjs_writer_prmtv_runner_free_hpn;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_hpn(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
    ubjs_writer_prmtv_write_strategy_context_hpn *userdata;
    char *text;

    userdata = (ubjs_writer_prmtv_write_strategy_context_hpn *)this->userdata;
    text = (char *)(this->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_hpn_copy_text(this->object, text);

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->write)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length_write + 1), text, userdata->length);

    (this->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_print_hpn(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_hpn *userdata;
    char *text;

    userdata = (ubjs_writer_prmtv_write_strategy_context_hpn *)this->userdata;
    text = (char *)(this->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_hpn_copy_text(this->object, text);

    *(data + 0) = '[';
    *(data + 1) = userdata->length_strategy->marker;
    *(data + 2) = ']';

    (userdata->length_strategy->print)(userdata->length_strategy, data + 3);
    *(data + 3 + userdata->length_strategy->length_print) = '[';
    strncpy((char *)(data + userdata->length_strategy->length_print + 4), text, userdata->length);
    *(data + 4 + userdata->length_strategy->length_print + userdata->length) = ']';

    (this->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_free_hpn(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_hpn *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_hpn *)this->userdata;

    (userdata->length_strategy->free)(userdata->length_strategy);
    ubjs_prmtv_free(&(userdata->length_obj));
    (this->lib->free_f)(userdata);
    (this->lib->free_f)(this);
}
