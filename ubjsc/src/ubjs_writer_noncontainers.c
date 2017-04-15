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

#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"
#include "ubjs_writer_prv.h"

#include "ubjs_primitives_prv.h"

ubjs_result ubjs_writer_prmtv_write_strategy_ntype(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **pthis)
{
    ubjs_writer_prmtv_runner *this;
    ubjs_prmtv_ntype *ntype = 0;
    ubjs_writer_prmtv_write_strategy_context_ntype *context;

    ubjs_prmtv_get_ntype(object, &ntype);
    if (0 == ntype)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    context=(ubjs_writer_prmtv_write_strategy_context_ntype *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_ntype));
    this->writer=writer;
    this->strategy=ubjs_writer_prmtv_write_strategy_ntype;
    this->userdata=(void *)context;
    this->marker=ntype->marker;
    this->object=object;
    this->indent=indent;

    context->writer_glue.userdata = (void *)this;
    context->writer_glue.prmtv = object;
    context->writer_glue.debug_f = ubjs_writer_write_ntype_glue_debug;
    (ntype->writer_new_f)(writer->lib, &(context->writer_glue), &(context->writer));

    context->printer_glue.userdata = (void *)this;
    context->printer_glue.prmtv = object;
    context->printer_glue.indent = indent;
    context->printer_glue.debug_f = ubjs_writer_print_ntype_glue_debug;
    (ntype->printer_new_f)(writer->lib, &(context->printer_glue), &(context->printer));

    (context->writer->ntype->writer_get_length_f)(context->writer, &(this->length_write));
    (context->printer->ntype->printer_get_length_f)(context->printer, &(this->length_print));
    this->write=ubjs_writer_prmtv_runner_write_ntype;
    this->print=ubjs_writer_prmtv_runner_print_ntype;
    this->free = ubjs_writer_prmtv_runner_free_ntype;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        char *msg = 0;
        unsigned int len = 0;

        ubjs_compact_sprints(writer->lib, &msg, &len, 14, "ntype: writer=");
        ubjs_compact_sprints(writer->lib, &msg, &len, strlen(context->writer->name),
            context->writer->name);
        ubjs_compact_sprints(writer->lib, &msg, &len, 10, ", printer=");
        ubjs_compact_sprints(writer->lib, &msg, &len, strlen(context->printer->name),
            context->printer->name);

        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
    }
#endif
    /* LCOV_EXCL_STOP */

    *pthis=this;
    return UR_OK;
}

void ubjs_writer_write_ntype_glue_debug(ubjs_prmtv_ntype_writer_glue *this,
    unsigned int len, char *msg)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_writer_prmtv_runner *this2 = (ubjs_writer_prmtv_runner *)this->userdata;
    if (0 != this2->writer->debug_f)
    {
        ubjs_writer_prmtv_write_strategy_context_ntype *context = \
            (ubjs_writer_prmtv_write_strategy_context_ntype *)this2->userdata;

        char *msg2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, 1, "[");
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, strlen(context->writer->name),
            context->writer->name);
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, 2, "] ");
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, len, msg);
        (this2->writer->debug_f)(this2->writer->userdata, len2, msg2);
        (this2->writer->lib->free_f)(msg2);
    }
#endif
    /* LCOV_EXCL_STOP */
}

void ubjs_writer_print_ntype_glue_debug(ubjs_prmtv_ntype_printer_glue *this,
    unsigned int len, char *msg)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_writer_prmtv_runner *this2 = (ubjs_writer_prmtv_runner *)this->userdata;
    if (0 != this2->writer->debug_f)
    {
        ubjs_writer_prmtv_write_strategy_context_ntype *context = \
            (ubjs_writer_prmtv_write_strategy_context_ntype *)this2->userdata;
        char *msg2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, 1, "[");
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, strlen(context->printer->name),
            context->printer->name);
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, 2, "] ");
        ubjs_compact_sprints(this2->writer->lib, &msg2, &len2, len, msg);
        (this2->writer->debug_f)(this2->writer->userdata, len2, msg2);
        (this2->writer->lib->free_f)(msg2);
    }
#endif
    /* LCOV_EXCL_STOP */
}

void ubjs_writer_prmtv_runner_write_ntype(ubjs_writer_prmtv_runner *this, uint8_t *data)
{
    ubjs_writer_prmtv_write_strategy_context_ntype *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_ntype *)this->userdata;

    (userdata->writer->ntype->writer_do_f)(userdata->writer, data);
}

void ubjs_writer_prmtv_runner_print_ntype(ubjs_writer_prmtv_runner *this, char *data)
{
    ubjs_writer_prmtv_write_strategy_context_ntype *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_ntype *)this->userdata;

    (userdata->printer->ntype->printer_do_f)(userdata->printer, data);
}

void ubjs_writer_prmtv_runner_free_ntype(ubjs_writer_prmtv_runner *this)
{
    ubjs_writer_prmtv_write_strategy_context_ntype *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_ntype *)this->userdata;

    (userdata->writer->ntype->writer_free_f)(&(userdata->writer));
    (userdata->printer->ntype->printer_free_f)(&(userdata->printer));

    (this->writer->lib->free_f)(userdata);
    (this->writer->lib->free_f)(this);
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

    ubjs_endian_convert_native_to_big(value, value2, 4);
    memcpy(data, value2, 4);
}

void ubjs_writer_prmtv_runner_print_float32(ubjs_writer_prmtv_runner *this, char *data)
{
    float32_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float32_get(this->object, &value);

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

    ubjs_endian_convert_native_to_big(value, value2, 8);
    memcpy(data, value2, 8);
}

void ubjs_writer_prmtv_runner_print_float64(ubjs_writer_prmtv_runner *this, char *data)
{
    float64_t value;
    char printed[1082];
    int length;

    ubjs_prmtv_float64_get(this->object, &value);

    length = sprintf(printed, "[%f]", value);
    strncpy(data, printed, length);
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
    ubjs_prmtv_free(&(userdata->length_obj));
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
    ubjs_prmtv_free(&(userdata->length_obj));
    (this->writer->lib->free_f)(userdata);
    (this->writer->lib->free_f)(this);
}
