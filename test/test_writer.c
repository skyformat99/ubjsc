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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ubjs.h>

#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

void suite_writer(tcontext *context)
{
    tsuite *suite;
    TSUITE("writer", 0, 0, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_writer_init_clean);
    TTEST(suite, test_writer_basics);
    TTEST(suite, test_writer_null);
    TTEST(suite, test_writer_noop);
    TTEST(suite, test_writer_true);
    TTEST(suite, test_writer_false);
    TTEST(suite, test_writer_int8);
    TTEST(suite, test_writer_uint8);
    TTEST(suite, test_writer_int16);
    TTEST(suite, test_writer_int32);
    TTEST(suite, test_writer_int64);
    TTEST(suite, test_writer_float32);
    TTEST(suite, test_writer_float64);
    TTEST(suite, test_writer_char);

    TTEST(suite, test_writer_str_uint8);
    TTEST(suite, test_writer_str_int16);
    TTEST(suite, test_writer_str_int32);
    TTEST(suite, test_writer_hpn_uint8);
    TTEST(suite, test_writer_hpn_int16);
    TTEST(suite, test_writer_hpn_int32);

    TTEST(suite, test_writer_array_empty);
    TTEST(suite, test_writer_array_uint8);
    TTEST(suite, test_writer_array_int8);
    TTEST(suite, test_writer_array_int16);
    TTEST(suite, test_writer_array_int32);
    TTEST(suite, test_writer_array_int64);
    TTEST(suite, test_writer_array_null);
    TTEST(suite, test_writer_array_noop);
    TTEST(suite, test_writer_array_true);
    TTEST(suite, test_writer_array_false);
    TTEST(suite, test_writer_array_char);
    TTEST(suite, test_writer_array_str);
    TTEST(suite, test_writer_array_hpn);
    TTEST(suite, test_writer_array_float32);
    TTEST(suite, test_writer_array_float64);
    TTEST(suite, test_writer_array_array);
    TTEST(suite, test_writer_array_object);
    TTEST(suite, test_writer_array_count_optimized_uint8);
    TTEST(suite, test_writer_array_count_optimized_int16);
    TTEST(suite, test_writer_array_count_optimized_int32);
    TTEST(suite, test_writer_array_type_optimized_null);
    TTEST(suite, test_writer_array_type_optimized_noop);
    TTEST(suite, test_writer_array_type_optimized_true);
    TTEST(suite, test_writer_array_type_optimized_false);
    TTEST(suite, test_writer_array_type_optimized_uint8);
    TTEST(suite, test_writer_array_type_optimized_char);
    TTEST(suite, test_writer_array_type_optimized_int8);
    TTEST(suite, test_writer_array_type_optimized_int16);
    TTEST(suite, test_writer_array_type_optimized_int32);
    TTEST(suite, test_writer_array_type_optimized_int64);
    TTEST(suite, test_writer_array_type_optimized_float32);
    TTEST(suite, test_writer_array_type_optimized_float64);
    TTEST(suite, test_writer_array_type_optimized_str);
    TTEST(suite, test_writer_array_type_optimized_hpn);
    TTEST(suite, test_writer_array_type_optimized_array);
    TTEST(suite, test_writer_array_type_optimized_object);
    TTEST(suite, test_writer_array_upgraded_from_uint8_to_int16);
    TTEST(suite, test_writer_array_upgraded_from_int8_to_int16);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_int32);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_other_types);
    TTEST(suite, test_writer_array_upgraded_from_int8_int16_to_int32);
    TTEST(suite, test_writer_array_upgraded_from_uint8_int16_to_int32);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_are_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_are_other_types);
    TTEST(suite, test_writer_array_upgraded_from_int8_int16_int32_to_int64);
    TTEST(suite, test_writer_array_upgraded_from_uint8_int16_int32_to_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types);

    TTEST(suite, test_writer_object_empty);
    TTEST(suite, test_writer_object_uint8);
    TTEST(suite, test_writer_object_int8);
    TTEST(suite, test_writer_object_int16);
    TTEST(suite, test_writer_object_int32);
    TTEST(suite, test_writer_object_int64);
    TTEST(suite, test_writer_object_null);
    TTEST(suite, test_writer_object_noop);
    TTEST(suite, test_writer_object_true);
    TTEST(suite, test_writer_object_false);
    TTEST(suite, test_writer_object_char);
    TTEST(suite, test_writer_object_str);
    TTEST(suite, test_writer_object_hpn);
    TTEST(suite, test_writer_object_float32);
    TTEST(suite, test_writer_object_float64);
    TTEST(suite, test_writer_object_array);
    TTEST(suite, test_writer_object_object);
    TTEST(suite, test_writer_object_count_optimized_uint8);
    TTEST(suite, test_writer_object_count_optimized_int16);
    TTEST(suite, test_writer_object_count_optimized_int32);
    TTEST(suite, test_writer_object_type_optimized_null);
    TTEST(suite, test_writer_object_type_optimized_noop);
    TTEST(suite, test_writer_object_type_optimized_true);
    TTEST(suite, test_writer_object_type_optimized_false);
    TTEST(suite, test_writer_object_type_optimized_uint8);
    TTEST(suite, test_writer_object_type_optimized_char);
    TTEST(suite, test_writer_object_type_optimized_int8);
    TTEST(suite, test_writer_object_type_optimized_int16);
    TTEST(suite, test_writer_object_type_optimized_int32);
    TTEST(suite, test_writer_object_type_optimized_int64);
    TTEST(suite, test_writer_object_type_optimized_float32);
    TTEST(suite, test_writer_object_type_optimized_float64);
    TTEST(suite, test_writer_object_type_optimized_str);
    TTEST(suite, test_writer_object_type_optimized_hpn);
    TTEST(suite, test_writer_object_type_optimized_array);
    TTEST(suite, test_writer_object_type_optimized_object);
    TTEST(suite, test_writer_object_upgraded_from_uint8_to_int16);
    TTEST(suite, test_writer_object_upgraded_from_int8_to_int16);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_int32);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_other_types);
    TTEST(suite, test_writer_object_upgraded_from_int8_int16_to_int32);
    TTEST(suite, test_writer_object_upgraded_from_uint8_int16_to_int32);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_are_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_are_other_types);
    TTEST(suite, test_writer_object_upgraded_from_int8_int16_int32_to_int64);
    TTEST(suite, test_writer_object_upgraded_from_uint8_int16_int32_to_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_are_other_types);
}

void sw_verify(ubjs_prmtv *obj, unsigned int bytes_len, uint8_t *bytes,
    unsigned int pretty_len, char *pretty)
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    unsigned int len;
    would_write_call *call_write;
    would_print_call *call_print;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        unsigned int i;

        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(bytes_len, call_write->len);
        for (i = 0; i < bytes_len; i++)
        {
            TASSERT_EQUALUI(bytes[i], call_write->data[i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(pretty_len, call_print->len);
        TASSERT_NSTRING_EQUAL(pretty, call_print->data, pretty_len);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
