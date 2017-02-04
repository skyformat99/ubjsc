/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or su`bstantial portions of the Software.
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

#include "test_glue_mock.h"
#include "test_primitives.h"

void suite_primitives(tcontext *context)
{
    tsuite *suite;
    TSUITE("primitives", suite_primitives_before, suite_primitives_after, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_prmtv_common);
    TTEST(suite, test_prmtv_null);
    TTEST(suite, test_prmtv_noop);
    TTEST(suite, test_prmtv_true);
    TTEST(suite, test_prmtv_false);
    TTEST(suite, test_prmtv_int);
    TTEST(suite, test_prmtv_int8);
    TTEST(suite, test_prmtv_uint8);
    TTEST(suite, test_prmtv_int16);
    TTEST(suite, test_prmtv_int32);
    TTEST(suite, test_prmtv_int64);
    TTEST(suite, test_prmtv_float32);
    TTEST(suite, test_prmtv_float64);
    TTEST(suite, test_prmtv_char);
    TTEST(suite, test_prmtv_str);
    TTEST(suite, test_prmtv_hpn);
    TTEST(suite, test_prmtv_array);
    TTEST(suite, test_prmtv_object);
    TTEST(suite, test_prmtv_calls_for_wrong_primitives);
}

void suite_primitives_before(void)
{
    ubjs_library_builder *builder=0;
    ubjs_library_builder_new(&builder);
    ubjs_library_builder_set_glue_array_builder(builder,
        ubjs_glue_array_mock_builder_new);
    ubjs_library_builder_set_glue_dict_builder(builder,
        ubjs_glue_dict_mock_builder_new);
    ubjs_library_builder_build(builder, (ubjs_library **)&tstate);
    ubjs_library_builder_free(&builder);
}

void suite_primitives_after(void)
{
    ubjs_library_free((ubjs_library **)&tstate);
}

void test_prmtv_common(void)
{
    ubjs_prmtv_type type = UOT_MAX;
    ubjs_bool ret;
    char text[1];
    unsigned int len;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(0, &type));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(ubjs_prmtv_null(), 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int(ubjs_prmtv_null(), 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, &len));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_debug_string_copy(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_debug_string_copy(ubjs_prmtv_null(), 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_debug_string_copy(0, text));
}

void test_prmtv_null(void)
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[5];
    unsigned int dlen = 0;

    object = ubjs_prmtv_null();
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(object, ubjs_prmtv_null());
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(0, &ret));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_NULL, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(4, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("null", debug, 4);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_noop(void)
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[5];
    unsigned int dlen = 0;

    object = ubjs_prmtv_noop();
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(object, ubjs_prmtv_noop());
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(0, &ret));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_NOOP, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(4, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("noop", debug, 4);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_true(void)
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[5];
    unsigned int dlen = 0;

    object = ubjs_prmtv_true();
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(object, ubjs_prmtv_true());
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(0, &ret));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_TRUE, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(4, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("true", debug, 4);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_false(void)
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[6];
    unsigned int dlen = 0;

    object = ubjs_prmtv_false();
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(object, ubjs_prmtv_false());
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(0, &ret));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_FALSE, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(5, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("false", debug, 5);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    int64_t v;
    ubjs_bool ret=0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(0, -1, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(lib, -1, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(0, &v));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(lib, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(object, 0));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(0, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(lib, 0, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(0, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(lib, -1, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(-1, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(lib, 256, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(256, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(lib, 256, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(256, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(lib, 32768, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(32768, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(lib, 32768, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(32768, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(lib, 2147483648, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(2147483648, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(lib, 2147483648, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(2147483648, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int8(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    int8_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[7];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_INT8, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(6, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("int8 2", debug, 6);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_uint8(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    uint8_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[8];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_UINT8, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(7, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("uint8 2", debug, 7);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int16(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    int16_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[8];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_INT16, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(7, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("int16 2", debug, 7);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int32(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    int32_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[8];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_INT32, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(7, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("int32 2", debug, 7);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int64(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    int64_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[8];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_INT64, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(7, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("int64 2", debug, 7);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_float32(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    float32_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[17];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 2));

    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_FLOAT32, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(16, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("float32 2.000000", debug, 16);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_float64(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    float64_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[17];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 2));

    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_FLOAT64, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(16, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("float64 2.000000", debug, 16);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_char(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    char v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[7];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char(lib, 1, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    TASSERT_EQUAL(1, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_set(object, 2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    TASSERT_EQUAL(2, v);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_CHAR, type);

    ubjs_prmtv_char_set(object, 'r');
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(6, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("char r", debug, 6);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_hpn(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[13];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(lib, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(lib, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(0, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(0, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_hpn(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_hpn(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_get_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_copy_text(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_copy_text(0, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(0, 0, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(0, 1, "a", &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(lib, 1, "a", &object));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn(0, 3, "2.3", &object));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn(lib, 3, "2.3", &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_hpn(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_get_length(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_copy_text(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_get_length(object, &vl));
    TASSERT_EQUAL(3, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_copy_text(object, v));
    TASSERT_NSTRING_EQUAL("2.3", v, 3);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "a"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "-"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "+"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "-a"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "1r"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "00"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, ".5"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "1a"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "1.0a"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "0.."));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "0e+"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1e+"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "11e+"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 5, "1.1e+"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1e-"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "1e-r"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 5, "1e-0r"));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1er"));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 3, "500"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_get_length(object, &vl));
    TASSERT_EQUAL(3, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_copy_text(object, v));
    TASSERT_NSTRING_EQUAL("500", v, 3);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 1, "0"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 1, "1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 2, "-0"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 2, "-1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 1, "12"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 3, "-12"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 3, "0.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 3, "1.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "11.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "0.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "11.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "-0.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "-1.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-11.1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-0.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-1.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 6, "-11.11"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 3, "1e1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "1.1e1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "111e1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 5, "1e111"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1e-1"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1e+1"));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_hpn(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_HPN, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(12, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("hpn 4 <1e+1>", debug, 12);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_str(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
    char debug[11];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(lib, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(lib, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, v));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 3, "kra", &object));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str(lib, 3, "kra", &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(object, 0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    TASSERT_EQUAL(3, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    TASSERT_NSTRING_EQUAL("kra", v, 3);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_set(object, 2, "ur"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    TASSERT_EQUAL(2, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    TASSERT_NSTRING_EQUAL("ur", v, 2);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_STR, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(10, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("str 2 <ur>", debug, 10);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_array(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    ubjs_prmtv *other2;
    ubjs_array_iterator *iterator;
    ubjs_prmtv_type type = UOT_MAX;
    unsigned int vl = -1;
    ubjs_bool ret=0;
    char debug[8];
    unsigned int dlen = 0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array(lib, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array(0, &object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, &other));
    other = ubjs_prmtv_null();
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(0, &iterator));

    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_free(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(0, &other2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array(lib, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(object, 0));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(object, 0));

    twill_returnui("array_get_length", 1, UR_OK);
    twill_returnui("array_get_length", 1, 0);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);
    vl = -1;

    twill_returnui("array_get_length", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(object, &vl));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));

    other = ubjs_prmtv_null();
    other2 = 0;
    twill_returnui("array_get_first", 1, UR_OK);
    twill_returno("array_get_first", 1, other);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_first(object, &other2));
    TASSERT_EQUAL(other, other2);

    other2 = 0;
    twill_returnui("array_get_first", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, &other2));
    TASSERT_EQUAL(0, other2);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));

    other = ubjs_prmtv_null();
    other2 = 0;
    twill_returnui("array_get_last", 1, UR_OK);
    twill_returno("array_get_last", 1, other);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_last(object, &other2));
    TASSERT_EQUAL(other, other2);

    other2 = 0;
    twill_returnui("array_get_last", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, &other2));
    TASSERT_EQUAL(0, other2);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));

    other = ubjs_prmtv_null();
    other2 = 0;
    twill_returnui("array_get_at", 1, UR_OK);
    twill_returno("array_get_at", 1, other);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other2));
    TASSERT_EQUAL(other, other2);

    other2 = 0;
    twill_returnui("array_get_at", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, &other2));
    TASSERT_EQUAL(0, other2);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));

    twill_returnui("array_add_first", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_first(object, other));

    twill_returnui("array_add_first", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(object, other));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));

    twill_returnui("array_add_last", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));

    twill_returnui("array_add_last", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(object, other));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));

    twill_returnui("array_add_at", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_at(object, 0, other));

    twill_returnui("array_add_at", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, other));

    twill_returnui("array_delete_first", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_first(object));

    twill_returnui("array_delete_first", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(object));

    twill_returnui("array_delete_last", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));

    twill_returnui("array_delete_last", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(object));

    twill_returnui("array_delete_at", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_at(object, 0));

    twill_returnui("array_delete_at", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));

    twill_returnui("array_iterator_next", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));

    twill_returnui("array_iterator_next", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));

    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, 0));

    other = ubjs_prmtv_null();
    other2 = 0;
    twill_returnui("array_iterator_get", 1, UR_OK);
    twill_returno("array_iterator_get", 1, other);
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other2));
    TASSERT_EQUAL(other, other2);

    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    twill_returnui("array_get_length", 1, UR_OK);
    twill_returnui("array_get_length", 1, 0);
    twill_returnui("array_get_length", 1, UR_OK);
    twill_returnui("array_get_length", 1, 0);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    TASSERT_EQUALUI(7, dlen);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    TASSERT_NSTRING_EQUAL("array 0", debug, 7);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_ARRAY, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_object(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other=0;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;
    char key2[2];

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(lib, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(0, &object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0, ""));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, &iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_free(0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0, key2));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0, &other));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object(lib, &object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(object, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(object, 0));

    twill_returnui("dict_get_length", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(object, &vl));

    twill_returnui("dict_get_length", 1, UR_OK);
    twill_returnui("dict_get_length", 1, 1);
    vl = -1;
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUALUI(1, vl);

    twill_returnui("dict_set", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));

    twill_returnui("dict_set", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));

    twill_returnui("dict_get", 1, UR_OK);
    twill_returno("dict_get", 1, ubjs_prmtv_null());
    other = 0;
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);

    twill_returnui("dict_get", 1, UR_ERROR);
    other = 0;
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(other, 0);

    twill_returnui("dict_delete", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(object, 1, "a"));

    twill_returnui("dict_delete", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);

    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(iterator, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(iterator, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(iterator, 0));

    twill_returnui("dict_iterator_next", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));

    twill_returnui("dict_iterator_next", 1, UR_OK);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));

    twill_returnui("dict_iterator_get_key_length", 1, UR_ERROR);
    vl = 0;
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUALUI(vl, 0);

    twill_returnui("dict_iterator_get_key_length", 1, UR_OK);
    twill_returnui("dict_iterator_get_key_length", 1, 1);
    vl = 0;
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUALUI(1, vl);

    twill_returnui("dict_iterator_copy_key", 1, UR_ERROR);
    key2[0] = 0;
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_EQUAL(key2[0], 0);

    twill_returnui("dict_iterator_copy_key", 1, UR_OK);
    twill_returnui("dict_iterator_copy_key", 1, 1);
    twill_returno("dict_iterator_copy_key", 1, strdup("a"));
    key2[0] = 0;
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_NSTRING_EQUAL("a", key2, 1);

    twill_returnui("dict_iterator_get_value", 1, UR_ERROR);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(iterator, &other));

    twill_returnui("dict_iterator_get_value", 1, UR_OK);
    twill_returno("dict_iterator_get_value", 1, ubjs_prmtv_null());
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator, &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);

    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));
    TASSERT_EQUAL(0, iterator);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

unsigned int ubjs_test_primitives_len=16;
ubjs_test_primitive ubjs_test_primitives[] =
{
    {ubjs_test_primitives_create_null, ubjs_test_primitives_test_null},
    {ubjs_test_primitives_create_noop, ubjs_test_primitives_test_noop},
    {ubjs_test_primitives_create_false, ubjs_test_primitives_test_false},
    {ubjs_test_primitives_create_true, ubjs_test_primitives_test_true},
    {(ubjs_test_primitives_create)0, ubjs_test_primitives_test_int},
    {ubjs_test_primitives_create_int8, ubjs_test_primitives_test_int8},
    {ubjs_test_primitives_create_uint8, ubjs_test_primitives_test_uint8},
    {ubjs_test_primitives_create_int16, ubjs_test_primitives_test_int16},
    {ubjs_test_primitives_create_int32, ubjs_test_primitives_test_int32},
    {ubjs_test_primitives_create_int64, ubjs_test_primitives_test_int64},
    {ubjs_test_primitives_create_float32, ubjs_test_primitives_test_float32},
    {ubjs_test_primitives_create_float64, ubjs_test_primitives_test_float64},
    {ubjs_test_primitives_create_char, ubjs_test_primitives_test_char},
    {ubjs_test_primitives_create_str, ubjs_test_primitives_test_str},
    {ubjs_test_primitives_create_hpn, ubjs_test_primitives_test_hpn},
    {ubjs_test_primitives_create_array, ubjs_test_primitives_test_array},
    {ubjs_test_primitives_create_object, ubjs_test_primitives_test_object}
};

void ubjs_test_primitives_create_null(ubjs_library *lib, ubjs_prmtv **p)
{
    *p=ubjs_prmtv_null();
}

void ubjs_test_primitives_test_null(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_noop(ubjs_library *lib, ubjs_prmtv **p)
{
    *p=ubjs_prmtv_noop();
}

void ubjs_test_primitives_test_noop(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_false(ubjs_library *lib, ubjs_prmtv **p)
{
    *p=ubjs_prmtv_false();
}

void ubjs_test_primitives_test_false(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_true(ubjs_library *lib, ubjs_prmtv **p)
{
    *p=ubjs_prmtv_true();
}

void ubjs_test_primitives_test_true(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_int8(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_int8(lib, 0, p);
}

void ubjs_test_primitives_test_int8(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int8_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(p, v));
}

void ubjs_test_primitives_test_int(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int64_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int(p, &ret));
    if (UTRUE == ret)
    {
        return;
    }

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(p, &v));
}

void ubjs_test_primitives_create_uint8(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_uint8(lib, 0, p);
}

void ubjs_test_primitives_test_uint8(ubjs_prmtv *p)
{
    ubjs_bool ret;
    uint8_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(p, v));
}

void ubjs_test_primitives_create_int16(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_int16(lib, 0, p);
}

void ubjs_test_primitives_test_int16(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int16_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(p, v));
}

void ubjs_test_primitives_create_int32(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_int32(lib, 0, p);
}

void ubjs_test_primitives_test_int32(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int32_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(p, v));
}

void ubjs_test_primitives_create_int64(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_int64(lib, 0, p);
}

void ubjs_test_primitives_test_int64(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int64_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(p, v));
}

void ubjs_test_primitives_create_float32(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_float32(lib, 0, p);
}

void ubjs_test_primitives_test_float32(ubjs_prmtv *p)
{
    ubjs_bool ret;
    float32_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(p, v));
}

void ubjs_test_primitives_create_float64(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_float64(lib, 0, p);
}

void ubjs_test_primitives_test_float64(ubjs_prmtv *p)
{
    ubjs_bool ret;
    float64_t v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(p, v));
}

void ubjs_test_primitives_create_char(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_char(lib, 0, p);
}

void ubjs_test_primitives_test_char(ubjs_prmtv *p)
{
    ubjs_bool ret;
    char v;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(p, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(p, v));
}

void ubjs_test_primitives_create_str(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_str(lib, 1, "a", p);
}

void ubjs_test_primitives_test_str(ubjs_prmtv *p)
{
    ubjs_bool ret;
    unsigned int vl;
    char v[1];

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(p, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(p, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(p, vl, v));
}

void ubjs_test_primitives_create_hpn(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_hpn(lib, 1, "1", p);
}

void ubjs_test_primitives_test_hpn(ubjs_prmtv *p)
{
    ubjs_bool ret;
    unsigned int vl;
    char v[1];

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_hpn(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_get_length(p, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_copy_text(p, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_hpn_set(p, vl, v));
}

void ubjs_test_primitives_create_array(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_array(lib, p);
}

void ubjs_test_primitives_test_array(ubjs_prmtv *p)
{
    ubjs_bool ret;
    ubjs_array_iterator *iterator=0;
    unsigned int vl;
    ubjs_prmtv *other=0;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(p, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(p, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(p, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(p, 0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(p, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(p, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(p, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(p));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(p));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(p, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(p, &iterator));
}

void ubjs_test_primitives_create_object(ubjs_library *lib, ubjs_prmtv **p)
{
    ubjs_prmtv_object(lib, p);
}

void ubjs_test_primitives_test_object(ubjs_prmtv *p)
{
    ubjs_bool ret;
    ubjs_object_iterator *iterator = 0;
    unsigned int vl = -1;
    ubjs_prmtv *other=0;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(p, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(p, &vl));
    TASSERT_EQUAL(vl, -1);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(p, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(p, 0, 0, &other));
    TASSERT_EQUAL(other, 0);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(p, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(p, 0, "", &other));
    TASSERT_EQUAL(other, 0);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(p, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(p, 0, 0, other));
    TASSERT_EQUAL(other, 0);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(p, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(p, 0, "", other));
    TASSERT_EQUAL(other, 0);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(p, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(p, 0, ""));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(p, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(p, &iterator));
    TASSERT_EQUAL(iterator, 0);
}

void test_prmtv_calls_for_wrong_primitives(void)
{
    unsigned int it, it2;
    ubjs_prmtv *p=0;
    ubjs_library *lib = (ubjs_library *)tstate;

    for (it=0; it<ubjs_test_primitives_len; it++)
    {
        if (0 == ubjs_test_primitives[it].create)
        {
            continue;
        }

        (ubjs_test_primitives[it].create)(lib, &p);

        for (it2=0; it2<ubjs_test_primitives_len; it2++)
        {
            if (it==it2)
            {
                continue;
            }
            (ubjs_test_primitives[it2].test)(p);
        }

        ubjs_prmtv_free(&p);
    }
}