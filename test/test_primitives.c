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

#include "test_primitives.h"

void suite_primitives(tcontext *context)
{
    tsuite *suite;
    TSUITE("primitives", 0, 0, &suite);
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
    TTEST(suite, test_prmtv_array);
    TTEST(suite, test_prmtv_object);
    TTEST(suite, test_prmtv_calls_for_wrong_primitives);
}

void test_prmtv_common()
{
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(0, &type));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_get_type(ubjs_prmtv_null(), 0));
}

void test_prmtv_null()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_noop()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_true()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_false()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int()
{
    ubjs_prmtv *object = 0;
    int64_t v;
    ubjs_bool ret=0;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint(-1, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(0, &v));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(0, &object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int_get(object, 0));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(0, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(0, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(0, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(-1, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(-1, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(256, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(256, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(256, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(256, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(32768, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(32768, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(32768, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(32768, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int(2147483648, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(2147483648, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint(2147483648, &object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int_get(object, &v));
    TASSERT_EQUAL(2147483648, v);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int8()
{
    ubjs_prmtv *object = 0;
    int8_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_uint8()
{
    ubjs_prmtv *object = 0;
    uint8_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int16()
{
    ubjs_prmtv *object = 0;
    int16_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int32()
{
    ubjs_prmtv *object = 0;
    int32_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_int64()
{
    ubjs_prmtv *object = 0;
    int64_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_float32()
{
    ubjs_prmtv *object = 0;
    float32_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_float64()
{
    ubjs_prmtv *object = 0;
    float64_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_char()
{
    ubjs_prmtv *object = 0;
    char v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, &v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_char(1, &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_str()
{
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, &ret));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, v));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, v));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_str(3, "kra", &object));
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

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_array()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    ubjs_prmtv *other2;
    ubjs_prmtv *other3;
    ubjs_array_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;
    unsigned int it;
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array(0));
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

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array(&object));
    TASSERT_NOT_EQUAL(0, object);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 1, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(object));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    ubjs_prmtv_char(0, &other);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_first(object, other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_first(object, &other2));
    TASSERT_EQUAL(other, other2);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_last(object, &other2));
    TASSERT_EQUAL(other, other2);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other2));
    TASSERT_EQUAL(other, other2);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 1, &other2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, 0));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other2));
    TASSERT_EQUAL(other, other2);
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other2));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_first(object));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, &other2));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, &other2));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other2));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_at(object, 0, other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_at(object, 0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    ubjs_prmtv_char(1, &other2);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other2));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(2, vl);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other3));
    TASSERT_EQUAL(other, other3);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 1, &other3));
    TASSERT_EQUAL(other2, other3);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_first(object, &other3));
    TASSERT_EQUAL(other, other3);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_last(object, &other3));
    TASSERT_EQUAL(other2, other3);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other3));
    TASSERT_EQUAL(other, other3);
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other3));
    TASSERT_EQUAL(other2, other3);
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other3));
    TASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_first(object, other));
    }
    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_at(object, 0, other));
    }
    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    }
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(300, vl);

    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_first(object));
    }
    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_at(object, 0));
    }
    for (it=0; it<100; it++)
    {
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    }
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    ubjs_prmtv_free(&other2);
    ubjs_prmtv_free(&other);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_ARRAY, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

void test_prmtv_object()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other=0;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;
    char key2[10];
    ubjs_prmtv_type type = UOT_MAX;

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(0));
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

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object(&object));
    TASSERT_NOT_EQUAL(0, object);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(object, 0));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);

    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(object, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(object, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(object, 0));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(iterator, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(iterator, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(iterator, 0));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_NSTRING_EQUAL("a", key2, 1);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator, &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "b", ubjs_prmtv_noop()));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(2, vl);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "b", &other));
    TASSERT_EQUAL(ubjs_prmtv_noop(), other);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_NSTRING_EQUAL("a", key2, 1);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator, &other));
    TASSERT_EQUAL(ubjs_prmtv_null(), other);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_NSTRING_EQUAL("b", key2, 1);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator, &other));
    TASSERT_EQUAL(ubjs_prmtv_noop(), other);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "b", &other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    TASSERT_EQUAL(1, vl);
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    TASSERT_NSTRING_EQUAL("b", key2, 1);
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "b"));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    TASSERT_EQUAL(0, vl);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "b", &other));
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    TASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    TASSERT_EQUAL(UTRUE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_prmtv_get_type(object, &type));
    TASSERT_EQUALUI(UOT_OBJECT, type);

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    TASSERT_EQUAL(0, object);
}

unsigned int ubjs_test_primitives_len=15;
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
    {ubjs_test_primitives_create_array, ubjs_test_primitives_test_array},
    {ubjs_test_primitives_create_object, ubjs_test_primitives_test_object}
};

void ubjs_test_primitives_create_null(ubjs_prmtv **p)
{
    *p=ubjs_prmtv_null();
}

void ubjs_test_primitives_test_null(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_noop(ubjs_prmtv **p)
{
    *p=ubjs_prmtv_noop();
}

void ubjs_test_primitives_test_noop(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_false(ubjs_prmtv **p)
{
    *p=ubjs_prmtv_false();
}

void ubjs_test_primitives_test_false(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_true(ubjs_prmtv **p)
{
    *p=ubjs_prmtv_true();
}

void ubjs_test_primitives_test_true(ubjs_prmtv *p)
{
    ubjs_bool ret;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
}

void ubjs_test_primitives_create_int8(ubjs_prmtv **p)
{
    ubjs_prmtv_int8(0, p);
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

void ubjs_test_primitives_create_uint8(ubjs_prmtv **p)
{
    ubjs_prmtv_uint8(0, p);
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

void ubjs_test_primitives_create_int16(ubjs_prmtv **p)
{
    ubjs_prmtv_int16(0, p);
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

void ubjs_test_primitives_create_int32(ubjs_prmtv **p)
{
    ubjs_prmtv_int32(0, p);
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

void ubjs_test_primitives_create_int64(ubjs_prmtv **p)
{
    ubjs_prmtv_int64(0, p);
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

void ubjs_test_primitives_create_float32(ubjs_prmtv **p)
{
    ubjs_prmtv_float32(0, p);
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

void ubjs_test_primitives_create_float64(ubjs_prmtv **p)
{
    ubjs_prmtv_float64(0, p);
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

void ubjs_test_primitives_create_char(ubjs_prmtv **p)
{
    ubjs_prmtv_char(0, p);
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

void ubjs_test_primitives_create_str(ubjs_prmtv **p)
{
    ubjs_prmtv_str(1, "a", p);
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


void ubjs_test_primitives_create_array(ubjs_prmtv **p)
{
    ubjs_prmtv_array(p);
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

void ubjs_test_primitives_create_object(ubjs_prmtv **p)
{
    ubjs_prmtv_object(p);
}

void ubjs_test_primitives_test_object(ubjs_prmtv *p)
{
    ubjs_bool ret;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_prmtv *other=0;

    TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(p, &ret));
    TASSERT_EQUAL(UFALSE, ret);
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(other, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(other, &vl));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0, 0, &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0, "", &other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0, 0, other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0, "", 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0, "", other));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(other, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(other, 0, ""));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(other, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(other, &iterator));
}

void test_prmtv_calls_for_wrong_primitives()
{
    unsigned int it, it2;
    ubjs_prmtv *p=0;

    for (it=0; it<ubjs_test_primitives_len; it++)
    {
        if (0 == ubjs_test_primitives[it].create)
        {
            continue;
        }

        (ubjs_test_primitives[it].create)(&p);

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
