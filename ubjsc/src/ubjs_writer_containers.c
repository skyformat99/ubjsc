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
#include "ubjs_primitives_prv.h"
#include <ubjs_primitive_uint8.h>
#include <ubjs_primitive_int8.h>
#include <ubjs_primitive_int16.h>
#include <ubjs_primitive_int32.h>
#include <ubjs_primitive_int64.h>
#include <ubjs_primitive_str.h>

void ubjs_writer_prmtv_write_strategy_object_prepare_items(
    ubjs_writer *writer,
    ubjs_writer_prmtv_write_strategy_context_object *data,
    ubjs_prmtv *real_object,
    unsigned int object_length,
    unsigned int *pitems_length_write,
    unsigned int *pitems_length_print,
    unsigned int indent)
{
    ubjs_object_iterator *iterator=0;
    unsigned int i;
    ubjs_writer_prmtv_runner *key_runner=0;
    ubjs_writer_prmtv_runner *value_runner=0;

    ubjs_prmtv_object_iterate(real_object, &iterator);
    for (i=0; UR_OK == ubjs_object_iterator_next(iterator) && i < object_length; i++)
    {
        char *key_chr = 0;
        unsigned int key_length = 0;
        ubjs_prmtv *key = 0;
        ubjs_prmtv *value = 0;

        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != writer->debug_f)
        {
            char *msg = 0;
            unsigned int len = 0;

            ubjs_compact_sprints(writer->lib, &msg, &len, 7, "# Item ");
            ubjs_compact_sprintui(writer->lib, &msg, &len, i + 1);
            ubjs_compact_sprints(writer->lib, &msg, &len, 1, "/");
            ubjs_compact_sprintui(writer->lib, &msg, &len, object_length);

            (writer->debug_f)(writer->userdata, len, msg);
            (writer->lib->free_f)(msg);
        }
#endif
        /* LCOV_EXCL_STOP */

        ubjs_object_iterator_get_key_length(iterator, &key_length);
        key_chr=(char *)(writer->lib->alloc_f)(sizeof(char)*key_length);
        ubjs_object_iterator_copy_key(iterator, key_chr);
        ubjs_prmtv_str(writer->lib, key_length, key_chr, &key);
        ubjs_writer_prmtv_write_strategy_ntype(writer, key, 0, &key_runner);
        (writer->lib->free_f)(key_chr);

        ubjs_object_iterator_get_value(iterator, &value);
        ubjs_writer_prmtv_find_best_write_strategy(writer, value, indent + UBJS_SPACES_PER_INDENT,
            &value_runner);

        {
            unsigned int a, b;
            (key_runner->write_get_length)(key_runner, &a);
            (value_runner->write_get_length)(value_runner, &b);
            (*pitems_length_write) += a + b;
        }
        {
            unsigned int a, b;
            (key_runner->print_get_length)(key_runner, &a);
            (value_runner->print_get_length)(value_runner, &b);
            (*pitems_length_print) += a + b;
        }
        data->key_runners[i]=key_runner;
        data->value_runners[i]=value_runner;

        if (0 != data->count_strategy)
        {
            if (0 == i)
            {
                data->type_strategy = value_runner;
            }
            else if (0 != data->type_strategy &&
                value_runner->marker != data->type_strategy->marker)
            {
                data->type_strategy = 0;
            }
        }
    }

    ubjs_object_iterator_free(&iterator);
}

ubjs_result ubjs_writer_prmtv_write_strategy_object(ubjs_writer *writer, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    ubjs_writer_prmtv_runner *arunner = 0;
    ubjs_bool ret = UFALSE;
    ubjs_writer_prmtv_write_strategy_context_object *data;
    unsigned int object_length;
    unsigned int items_length_write=0;
    unsigned int items_length_print=0;
    ubjs_prmtv *real_object = object;
    ubjs_prmtv *upgraded = 0;

    ubjs_prmtv_is_object(object, &ret);
    if (UFALSE == ret)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_object_get_length(object, &object_length);

    arunner=(ubjs_writer_prmtv_runner *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_runner));
    data=(ubjs_writer_prmtv_write_strategy_context_object *)(writer->lib->alloc_f)(
        sizeof(struct ubjs_writer_prmtv_write_strategy_context_object));
    data->key_runners=(ubjs_writer_prmtv_runner **)(writer->lib->alloc_f)(
        sizeof(ubjs_writer_prmtv_runner *) * object_length);
    data->value_runners=(ubjs_writer_prmtv_runner **)(writer->lib->alloc_f)(
        sizeof(ubjs_writer_prmtv_runner *) * object_length);
    data->length=object_length;
    data->type_strategy=0;
    data->count_strategy=0;
    data->count=0;
    data->was_upgraded=UFALSE;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 6, "object");
    }
#endif
    /* LCOV_EXCL_STOP */

    if (UR_OK == ubjs_writer_prmtv_try_upgrade(writer, object, &upgraded))
    {
        real_object = upgraded;
        data->was_upgraded=UTRUE;
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != writer->debug_f)
        {
            (writer->debug_f)(writer->userdata, 12, "Was upgraded");
        }
#endif
        /* LCOV_EXCL_STOP */

    }

    if (object_length >= 3)
    {
        ubjs_prmtv_uint(writer->lib, object_length, &(data->count));
        ubjs_writer_prmtv_find_best_write_strategy(writer, data->count, 0, &(data->count_strategy));
    /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != writer->debug_f && 0 != data->type_strategy)
        {
            (writer->debug_f)(writer->userdata, 23, "Will be count optimized");
        }
#endif
    /* LCOV_EXCL_STOP */
    }

    ubjs_writer_prmtv_write_strategy_object_prepare_items(writer, data, real_object,
        object_length, &items_length_write, &items_length_print, indent);

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f && 0 != data->type_strategy)
    {
        (writer->debug_f)(writer->userdata, 22, "Will be type optimized");
    }
#endif
    /* LCOV_EXCL_STOP */

    arunner->writer=writer;
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
        data->length_write=1 + object_length + items_length_write;
        data->length_print=3;
        if (0 < object_length)
        {
            data->length_print += items_length_print + object_length * 3 + object_length + 1
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else if (0 == data->type_strategy)
    {
        /*
         * "#" + count marker + count + items markers + items content.
         * print: length * "\n" + (length + 1) * indent * " ".
         */
        unsigned int a = 0;
        unsigned int b = 0;
        (data->count_strategy->write_get_length)(data->count_strategy, &a);
        (data->count_strategy->print_get_length)(data->count_strategy, &b);
        data->length_write = 2 + a + object_length +
            items_length_write;
        data->length_print = 6 + b;
        if (0 < object_length)
        {
            data->length_print += items_length_print + object_length * 3 + object_length
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }
    else
    {
        /*
         * "$" + type marker + "#" + length marker + length + items content.
         * print: length * "\n" + (length + 1) * indent * " ".
         */
        unsigned int a = 0;
        unsigned int b = 0;
        (data->count_strategy->write_get_length)(data->count_strategy, &a);
        (data->count_strategy->print_get_length)(data->count_strategy, &b);
        data->length_write=4 + a + items_length_write;
        data->length_print=12 + b;
        if (0 < object_length)
        {
            data->length_print += items_length_print + object_length
                + object_length * (indent + UBJS_SPACES_PER_INDENT) + indent;
            data->do_indents = UTRUE;
        }
    }

    arunner->write=ubjs_writer_prmtv_runner_write_object;
    arunner->write_get_length=ubjs_writer_prmtv_runner_write_get_length_object;
    arunner->print=ubjs_writer_prmtv_runner_print_object;
    arunner->print_get_length=ubjs_writer_prmtv_runner_print_get_length_object;

    arunner->free=ubjs_writer_prmtv_runner_free_object;
    *runner=arunner;
    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_get_length_object(ubjs_writer_prmtv_runner *this,
    unsigned int *plen)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_object *)this->userdata;
    *plen = userdata->length_write;
}

void ubjs_writer_prmtv_runner_print_get_length_object(ubjs_writer_prmtv_runner *this,
    unsigned int *plen)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
    userdata = (ubjs_writer_prmtv_write_strategy_context_object *)this->userdata;
    *plen = userdata->length_print;
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
        unsigned int a;
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = userdata->count_strategy->marker;
        (userdata->count_strategy->write_get_length)(userdata->count_strategy, &a);
        (userdata->count_strategy->write)(userdata->count_strategy, data + at);
        at += a;
    }

    for (i=0; i<userdata->length; i++)
    {
        unsigned int a;
        (userdata->key_runners[i]->write_get_length)(userdata->key_runners[i], &a);
        (userdata->key_runners[i]->write)(userdata->key_runners[i], data + at);
        at += a;

        if (0==userdata->type_strategy)
        {
            *(data + (at++)) = userdata->value_runners[i]->marker;
        }
        (userdata->value_runners[i]->write_get_length)(userdata->value_runners[i], &a);
        (userdata->value_runners[i]->write)(userdata->value_runners[i], data + at);
        at += a;
    }

    if (0==userdata->count_strategy)
    {
        *(data + at) = MARKER_OBJECT_END;
    }

    if (UTRUE == this->writer->free_primitives_early)
    {
        ubjs_object_iterator *it = 0;
        ubjs_prmtv_object_iterate(this->object, &it);
        while (UR_OK == ubjs_object_iterator_next(it))
        {
            ubjs_object_iterator_delete(it);
        }
        ubjs_object_iterator_free(&it);
    }
}

void ubjs_writer_prmtv_runner_print_object(ubjs_writer_prmtv_runner *this,
    char *data)
{
    ubjs_writer_prmtv_write_strategy_context_object *userdata;
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
        unsigned int a;
        *(data + (at++)) = '[';
        *(data + (at++)) = MARKER_OPTIMIZE_COUNT;
        *(data + (at++)) = ']';
        *(data + (at++)) = '[';
        *(data + (at++)) = userdata->count_strategy->marker;
        *(data + (at++)) = ']';

        (userdata->count_strategy->print_get_length)(userdata->count_strategy, &a);
        (userdata->count_strategy->print)(userdata->count_strategy, data + at);
        at += a;
    }

    if (0 < userdata->length)
    {
        unsigned int i, j;
        for (i=0; i<userdata->length; i++)
        {
            unsigned int a;
            if (UTRUE == userdata->do_indents)
            {
                *(data + (at++)) = '\n';
                for (j=0; j < this->indent + UBJS_SPACES_PER_INDENT; j++)
                {
                    *(data + (at++)) = ' ';
                }
            }

            (userdata->key_runners[i]->print_get_length)(userdata->key_runners[i], &a);
            (userdata->key_runners[i]->print)(userdata->key_runners[i], data + at);
            at += a;

            if (0==userdata->type_strategy)
            {
                *(data + (at++)) = '[';
                *(data + (at++)) = userdata->value_runners[i]->marker;
                *(data + (at++)) = ']';
            }

            (userdata->value_runners[i]->print_get_length)(userdata->value_runners[i], &a);
            (userdata->value_runners[i]->print)(userdata->value_runners[i], data + at);
            at += a;

        }
    }

    if (0 == userdata->count_strategy)
    {
        if (UTRUE == userdata->do_indents && 0 < userdata->length)
        {
            unsigned int j;
            *(data + (at++)) = '\n';
            for (j=0; j < this->indent; j++)
            {
                *(data + (at++)) = ' ';
            }
        }
        *(data + (at++)) = '[';
        *(data + (at++)) = '}';
        *(data + (at++)) = ']';
    }

    if (UTRUE == this->writer->free_primitives_early)
    {
        ubjs_object_iterator *it = 0;
        ubjs_prmtv_object_iterate(this->object, &it);
        while (UR_OK == ubjs_object_iterator_next(it))
        {
            ubjs_object_iterator_delete(it);
        }
        ubjs_object_iterator_free(&it);
    }
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

    (this->writer->lib->free_f)(userdata->key_runners);
    (this->writer->lib->free_f)(userdata->value_runners);

    (this->writer->lib->free_f)(userdata);
    (this->writer->lib->free_f)(this);
}

void ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(ubjs_writer *writer,
    ubjs_prmtv *object, ubjs_writer_prmtv_upgrade_strategy_ints_metrics *pmetrics)
{
    ubjs_object_iterator *iterator = 0;
    ubjs_prmtv *item = 0;

    pmetrics->count_of_8=0;
    pmetrics->count_of_16=0;
    pmetrics->count_of_32=0;
    pmetrics->count_of_64=0;
    pmetrics->count_of_rest=0;
    pmetrics->count=0;

    ubjs_prmtv_object_iterate(object, &iterator);
    while (UR_OK == ubjs_object_iterator_next(iterator))
    {
        ubjs_prmtv_ntype *ntype;

        pmetrics->count++;

        ubjs_object_iterator_get_value(iterator, &item);
        ubjs_prmtv_get_ntype(item, &ntype);
        if (ntype == &ubjs_prmtv_uint8_ntype
            || ntype == &ubjs_prmtv_int8_ntype)
        {
            pmetrics->count_of_8++;
        }
        else if (ntype == &ubjs_prmtv_int16_ntype)
        {
            pmetrics->count_of_16++;
        }
        else if (ntype == &ubjs_prmtv_int32_ntype)
        {
            pmetrics->count_of_32++;
        }
        else if (ntype == &ubjs_prmtv_int64_ntype)
        {
            pmetrics->count_of_64++;
        }
        else
        {
            pmetrics->count_of_rest++;
        }
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        char *msg = 0;
        unsigned int len = 0;

        (writer->debug_f)(writer->userdata, 8, "Metrics:");
        ubjs_compact_sprints(writer->lib, &msg, &len, 7, "# 8-s: ");
        ubjs_compact_sprintui(writer->lib, &msg, &len, pmetrics->count_of_8);
        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
        msg = 0;

        ubjs_compact_sprints(writer->lib, &msg, &len, 8, "# 16-s: ");
        ubjs_compact_sprintui(writer->lib, &msg, &len, pmetrics->count_of_16);
        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
        msg = 0;

        ubjs_compact_sprints(writer->lib, &msg, &len, 8, "# 32-s: ");
        ubjs_compact_sprintui(writer->lib, &msg, &len, pmetrics->count_of_32);
        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
        msg = 0;

        ubjs_compact_sprints(writer->lib, &msg, &len, 8, "# 64-s: ");
        ubjs_compact_sprintui(writer->lib, &msg, &len, pmetrics->count_of_64);
        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
        msg = 0;

        ubjs_compact_sprints(writer->lib, &msg, &len, 8, "# Rest: ");
        ubjs_compact_sprintui(writer->lib, &msg, &len, pmetrics->count_of_rest);
        (writer->debug_f)(writer->userdata, len, msg);
        (writer->lib->free_f)(msg);
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_object_iterator_free(&iterator);
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object(
    ubjs_writer *writer, ubjs_prmtv *original, ubjs_prmtv **pupgraded)
{
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics metrics;
    ubjs_prmtv_type item_type;
    ubjs_result ret;

    ubjs_prmtv_get_type(original, &item_type);
    if (UOT_OBJECT != item_type)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(writer, original, &metrics);

    ret = ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16(writer, &metrics, original,
        pupgraded);
    if (UR_ERROR == ret)
    {
        ret = ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32(writer, &metrics, original,
            pupgraded);
    }
    if (UR_ERROR == ret)
    {
        ret = ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64(writer, &metrics, original,
            pupgraded);
    }

    return ret;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16(
    ubjs_writer *writer,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *metrics,
    ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;

    if (metrics->count < 2 || metrics->count_of_rest > 0 || metrics->count_of_32 > 0
        || metrics->count_of_64 > 0 || metrics->count_of_16 == 0  || metrics->count_of_8 == 0)
    {
        return UR_ERROR;
    }

    if (metrics->count_of_16 < ubjs_digits(metrics->count) + 3)
    {
        return UR_ERROR;
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 30, "Will upgrade all ints to int16");
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_prmtv_object(original->lib, &upgraded);
    ubjs_prmtv_object_iterate(original, &it);

    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        char *key;
        int64_t v;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)(original->lib->alloc_f)(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_int_get(item, &v);
        ubjs_prmtv_int16(original->lib, (int16_t) v, &upgraded_item);
        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        (original->lib->free_f)(key);
    }

    ubjs_object_iterator_free(&it);

    *pupgraded = upgraded;

    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32(
    ubjs_writer *writer,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *metrics,
    ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;

    /*
     * Do not optimize when there is nothing to
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics->count < 2 || metrics->count_of_rest > 0 || metrics->count_of_64 > 0
        || metrics->count_of_32 == 0 || (metrics->count_of_16 == 0 && metrics->count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics->count_of_32 < 3 + metrics->count_of_8 + 2 * metrics->count_of_16
        + ubjs_digits(metrics->count))
    {
        return UR_ERROR;
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 30, "Will upgrade all ints to int32");
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_prmtv_object(original->lib, &upgraded);
    ubjs_prmtv_object_iterate(original, &it);

    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        char *key;
        int64_t v;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)(original->lib->alloc_f)(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_int_get(item, &v);
        ubjs_prmtv_int32(original->lib, (int32_t) v, &upgraded_item);
        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        (original->lib->free_f)(key);
    }

    ubjs_object_iterator_free(&it);

    *pupgraded = upgraded;

    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64(
    ubjs_writer *writer,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *metrics,
    ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    ubjs_prmtv *upgraded = 0;
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv *upgraded_item = 0;

    /*
     * Do not optimize when there is nothing to.
     * Optimize integer-only arrays.
     * Not applicable when there are any int64s.
     * Not applicable when there are NO int32.
     * Not applicable when there are NO (u)int8/int16 either.
     */
    if (metrics->count < 2 || metrics->count_of_rest > 0 || metrics->count_of_64 == 0
        || (metrics->count_of_32 == 0 && metrics->count_of_16 == 0
        && metrics->count_of_8 == 0))
    {
        return UR_ERROR;
    }

    if (metrics->count_of_64 < 3 + 3 * metrics->count_of_8 + 5 * metrics->count_of_16
     + 6 * metrics->count_of_32 + ubjs_digits(metrics->count))
    {
        return UR_ERROR;
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 30, "Will upgrade all ints to int64");
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_prmtv_object(original->lib, &upgraded);
    ubjs_prmtv_object_iterate(original, &it);

    while (UR_OK == ubjs_object_iterator_next(it))
    {
        unsigned int key_length;
        char *key;
        int64_t v;

        ubjs_object_iterator_get_key_length(it, &key_length);
        key = (char *)(original->lib->alloc_f)(sizeof(char) * key_length);
        ubjs_object_iterator_copy_key(it, key);
        ubjs_object_iterator_get_value(it, &item);
        ubjs_prmtv_int_get(item, &v);
        ubjs_prmtv_int64(original->lib, v, &upgraded_item);
        ubjs_prmtv_object_set(upgraded, key_length, key, upgraded_item);
        (original->lib->free_f)(key);
    }

    ubjs_object_iterator_free(&it);

    *pupgraded = upgraded;

    return UR_OK;
}
