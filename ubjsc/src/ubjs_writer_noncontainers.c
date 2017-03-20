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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_null;
    arunner->userdata=0;
    arunner->marker=MARKER_NULL;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 4, "null");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_noop;
    arunner->marker=MARKER_NOOP;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 4, "noop");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_true;
    arunner->marker=MARKER_TRUE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 4, "true");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_false;
    arunner->marker=MARKER_FALSE;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=0;
    arunner->write=ubjs_writer_prmtv_runner_write_no_length;

    arunner->length_print=0;
    arunner->print=ubjs_writer_prmtv_runner_print_no_length;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 5, "false");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int8;
    arunner->marker=MARKER_INT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_int8;

    ubjs_prmtv_int8_get(object, &value);
    arunner->length_print = sprintf(printed, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int8;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 4, "int8");
    }
#endif
    /* LCOV_EXCL_STOP */

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int8(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_int8_get(this->object, (int8_t *)value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early int8");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_int8(ubjs_writer_prmtv_runner *this, char *data)
{
    int8_t value;
    char printed[7];
    int length;

    ubjs_prmtv_int8_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early int8");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%d]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_uint8;
    arunner->marker=MARKER_UINT8;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_uint8;

    ubjs_prmtv_uint8_get(object, &value);
    arunner->length_print = sprintf(printed, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_uint8;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 5, "uint5");
    }
#endif
    /* LCOV_EXCL_STOP */

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_uint8(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[1];
    uint8_t value2[1];

    ubjs_prmtv_uint8_get(this->object, value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early uint8");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_uint8(ubjs_writer_prmtv_runner *this, char *data)
{
    uint8_t value;
    char printed[6];
    int length;

    ubjs_prmtv_uint8_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early uint8");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%d]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int16;
    arunner->marker=MARKER_INT16;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=2;
    arunner->write=ubjs_writer_prmtv_runner_write_int16;

    ubjs_prmtv_int16_get(object, &value);
    arunner->length_print = sprintf(printed, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int16;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 5, "int16");
    }
#endif
    /* LCOV_EXCL_STOP */

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int16(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[2];
    uint8_t value2[2];

    ubjs_prmtv_int16_get(this->object, (int16_t *)value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int16");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 2);
    memcpy(data, value2, 2);
}

void ubjs_writer_prmtv_runner_print_int16(ubjs_writer_prmtv_runner *this, char *data)
{
    int16_t value;
    char printed[9];
    int length;

    ubjs_prmtv_int16_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int16");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%d]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int32;
    arunner->marker=MARKER_INT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=4;
    arunner->write=ubjs_writer_prmtv_runner_write_int32;

    ubjs_prmtv_int32_get(object, &value);
    arunner->length_print = sprintf(printed, "[%d]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int32;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 5, "int32");
    }
#endif
    /* LCOV_EXCL_STOP */

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

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int32");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 4);

    memcpy(data, value2, 4);
}

void ubjs_writer_prmtv_runner_print_int32(ubjs_writer_prmtv_runner *this, char *data)
{
    int32_t value;
    char printed[14];
    int length;

    ubjs_prmtv_int32_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int32");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%d]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_int64;
    arunner->marker=MARKER_INT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=8;
    arunner->write=ubjs_writer_prmtv_runner_write_int64;

    ubjs_prmtv_int64_get(object, &value);
    arunner->length_print = sprintf(printed, "[%ld]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_int64;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 5, "int64");
    }
#endif
    /* LCOV_EXCL_STOP */

    arunner->free=(ubjs_writer_prmtv_runner_free)(writer->lib->free_f);
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_int64(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    uint8_t value[8];
    uint8_t value2[8];

    ubjs_prmtv_int64_get(this->object, (int64_t *)value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int64");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 8);

    memcpy(data, value2, 8);
}

void ubjs_writer_prmtv_runner_print_int64(ubjs_writer_prmtv_runner *this, char *data)
{
    int64_t value;
    char printed[22];
    int length;

    ubjs_prmtv_int64_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 18, "Freeing early int64");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%ld]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_float32;
    arunner->marker=MARKER_FLOAT32;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=4;
    arunner->write=ubjs_writer_prmtv_runner_write_float32;

    ubjs_prmtv_float32_get(object, &value);
    arunner->length_print = sprintf(printed, "[%f]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_float32;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 7, "float32");
    }
#endif
    /* LCOV_EXCL_STOP */

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

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 20, "Freeing early float32");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 4);
    memcpy(data, value2, 4);
}

void ubjs_writer_prmtv_runner_print_float32(ubjs_writer_prmtv_runner *this, char *data)
{
    float32_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float32_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 20, "Freeing early float32");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%f]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_float64;
    arunner->marker=MARKER_FLOAT64;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=8;
    arunner->write=ubjs_writer_prmtv_runner_write_float64;

    ubjs_prmtv_float64_get(object, &value);
    arunner->length_print = sprintf(printed, "[%f]", value);
    arunner->print=ubjs_writer_prmtv_runner_print_float64;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 7, "float64");
    }
#endif
    /* LCOV_EXCL_STOP */

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

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 20, "Freeing early float64");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 8);
    memcpy(data, value2, 8);
}

void ubjs_writer_prmtv_runner_print_float64(ubjs_writer_prmtv_runner *this, char *data)
{
    float64_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float64_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 20, "Freeing early float64");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    length = sprintf(printed, "[%f]", value);
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
    arunner->writer=writer;
    arunner->strategy=ubjs_writer_prmtv_write_strategy_char;
    arunner->marker=MARKER_CHAR;
    arunner->userdata=0;
    arunner->object=object;
    arunner->indent=indent;

    arunner->length_write=1;
    arunner->write=ubjs_writer_prmtv_runner_write_char;

    arunner->length_print=3;
    arunner->print=ubjs_writer_prmtv_runner_print_char;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 4, "char");
    }
#endif
    /* LCOV_EXCL_STOP */

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

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early char");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    ubjs_endian_convert_native_to_big(value, value2, 1);
    memcpy(data, value2, 1);
}

void ubjs_writer_prmtv_runner_print_char(ubjs_writer_prmtv_runner *this, char *data)
{
    char value;

    ubjs_prmtv_char_get(this->object, &value);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early char");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

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

    arunner->writer=writer;
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

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 3, "str");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    text = (char *)(this->writer->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early str");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->write)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length_write + 1), text, userdata->length);

    (this->writer->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_print_str(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    char *text;

    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;
    text = (char *)(this->writer->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_str_copy_text(this->object, text);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early str");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    *(data + 0) = '[';
    *(data + 1) = userdata->length_strategy->marker;
    *(data + 2) = ']';

    (userdata->length_strategy->print)(userdata->length_strategy, data + 3);
    *(data + 3 + userdata->length_strategy->length_print) = '[';
    strncpy((char *)(data + userdata->length_strategy->length_print + 4), text, userdata->length);
    *(data + 4 + userdata->length_strategy->length_print + userdata->length) = ']';

    (this->writer->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_free_str(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_str *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_str *)this->userdata;

    (userdata->length_strategy->free)(userdata->length_strategy);
    if (UFALSE == this->writer->free_primitives_early)
    {
        /* Not freed yet. */
        ubjs_prmtv_free(&(userdata->length_obj));
    }
    (this->writer->lib->free_f)(userdata);
    (this->writer->lib->free_f)(this);
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

    arunner->writer=writer;
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

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 3, "hpn");
    }
#endif
    /* LCOV_EXCL_STOP */

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
    text = (char *)(this->writer->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_hpn_copy_text(this->object, text);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early hpn");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    *(data + 0) = userdata->length_strategy->marker;
    (userdata->length_strategy->write)(userdata->length_strategy, data + 1);
    strncpy((char *)(data + userdata->length_strategy->length_write + 1), text, userdata->length);

    (this->writer->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_print_hpn(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_hpn *userdata;
    char *text;

    userdata = (ubjs_writer_prmtv_write_strategy_context_hpn *)this->userdata;
    text = (char *)(this->writer->lib->alloc_f)(sizeof(char)*(userdata->length));
    ubjs_prmtv_hpn_copy_text(this->object, text);

    if (UTRUE == this->writer->free_primitives_early)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->writer->debug_f)
        {
            (this->writer->debug_f)(this->writer->userdata, 17, "Freeing early hpn");
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_prmtv_free(&(this->object));
    }

    *(data + 0) = '[';
    *(data + 1) = userdata->length_strategy->marker;
    *(data + 2) = ']';

    (userdata->length_strategy->print)(userdata->length_strategy, data + 3);
    *(data + 3 + userdata->length_strategy->length_print) = '[';
    strncpy((char *)(data + userdata->length_strategy->length_print + 4), text, userdata->length);
    *(data + 4 + userdata->length_strategy->length_print + userdata->length) = ']';

    (this->writer->lib->free_f)(text);
}

void ubjs_writer_prmtv_runner_free_hpn(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_hpn *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_hpn *)this->userdata;

    (userdata->length_strategy->free)(userdata->length_strategy);
    if (UFALSE == this->writer->free_primitives_early)
    {
        /* Not freed yet. */
        ubjs_prmtv_free(&(userdata->length_obj));
    }
    (this->writer->lib->free_f)(userdata);
    (this->writer->lib->free_f)(this);
}
