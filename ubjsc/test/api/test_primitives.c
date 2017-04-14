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

#include "test_common.h"
#include "test_glue_mock.h"
#include "test_primitives.h"

static void before(void)
{
    ubjs_library_builder builder;

    tbefore();

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_set_glue_array_builder(&builder,
        ubjs_glue_array_mock_builder_new);
    ubjs_library_builder_set_glue_dict_builder(&builder,
        ubjs_glue_dict_mock_builder_new);
    ubjs_library_builder_build(&builder, (ubjs_library **)&instance_lib);
}

static void after(void)
{
    ubjs_library_free((ubjs_library **)&instance_lib);

    tafter();
}

Test(primitives, common, .init = before, .fini = after)
{
    ubjs_prmtv_type type = UOT_MAX;
    ubjs_bool ret;
    ubjs_prmtv any = {0, 0, 0};
#ifndef NDEBUG
    char text[1];
    unsigned int len;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_get_type(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_get_type(0, &type));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_get_type(&any, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_int(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_int(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_int(&any, 0));

#ifndef NDEBUG
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(&any, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(0, text));
#endif
}

Test(primitives, int, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    int64_t v;

    cr_expect_eq(UR_ERROR, ubjs_prmtv_int(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_int(instance_lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_int(0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(instance_lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(0, -1, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(instance_lib, -1, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_int_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_int_get(0, &v));

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_int_get(object, 0));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(0, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_uint(instance_lib, 0, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(0, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, -1, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(-1, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, 256, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(256, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_uint(instance_lib, 256, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(256, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, 32768, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(32768, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_uint(instance_lib, 32768, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(32768, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, 2147483648, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(2147483648, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_uint(instance_lib, 2147483648, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_int_get(object, &v));
    cr_expect_eq(2147483648, v);
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, float32, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    float32_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
#ifndef NDEBUG
    char debug[17];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32(instance_lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32(0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float32(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float32(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_get(0, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_set(0, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_float32(instance_lib, 1, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float32(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_get(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_set(0, 2));

    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_float32_get(object, &v));
    cr_expect_eq(1, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_float32_set(object, 2));
    cr_expect_eq(UR_OK, ubjs_prmtv_float32_get(object, &v));
    cr_expect_eq(2, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_FLOAT32, type);

#ifndef NDEBUG
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(16, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("float32 2.000000", debug, 16);
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_free(0));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, float64, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    float64_t v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
#ifndef NDEBUG
    char debug[17];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64(instance_lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64(0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float64(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float64(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_get(0, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_set(0, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_float64(instance_lib, 1, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_float64(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_get(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_set(0, 2));

    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, ubjs_prmtv_float64_get(object, &v));
    cr_expect_eq(1, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_float64_set(object, 2));
    cr_expect_eq(UR_OK, ubjs_prmtv_float64_get(object, &v));
    cr_expect_eq(2, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_FLOAT64, type);

#ifndef NDEBUG
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(16, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("float64 2.000000", debug, 16);
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_free(0));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, char, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    char v;
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
#ifndef NDEBUG
    char debug[7];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_char(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char(instance_lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char(0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_char(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_char(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_get(0, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_set(0, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_char(instance_lib, 1, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_char(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_get(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_set(0, 2));

    cr_expect_eq(UR_OK, ubjs_prmtv_char_get(object, &v));
    cr_expect_eq(1, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_char_get(object, &v));
    cr_expect_eq(1, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_char_set(object, 2));
    cr_expect_eq(UR_OK, ubjs_prmtv_char_get(object, &v));
    cr_expect_eq(2, v);

    cr_expect_eq(UR_OK, ubjs_prmtv_is_char(object, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_CHAR, type);

#ifndef NDEBUG
    ubjs_prmtv_char_set(object, 'r');
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(6, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("char r", debug, 6);
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_free(0));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, hpn, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
#ifndef NDEBUG
    char debug[13];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(instance_lib, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(instance_lib, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_hpn(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_hpn(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_get_length(0, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_copy_text(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_copy_text(0, v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(0, 0, v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(0, 1, "a", &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(instance_lib, 1, "a", &object));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn(0, 3, "2.3", &object));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn(instance_lib, 3, "2.3", &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_hpn(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_get_length(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_copy_text(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 0, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_get_length(object, &vl));
    cr_expect_eq(3, vl);

    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_copy_text(object, v));
    cr_expect_arr_eq("2.3", v, 3);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "a"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "-"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 1, "+"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "-a"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "1r"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "00"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, ".5"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 2, "1a"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "1.0a"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "0.."));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "0e+"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1e+"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "11e+"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 5, "1.1e+"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1e-"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 4, "1e-r"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 5, "1e-0r"));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(object, 3, "1er"));

    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 3, "500"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_get_length(object, &vl));
    cr_expect_eq(3, vl);

    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_copy_text(object, v));
    cr_expect_arr_eq("500", v, 3);

    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 1, "0"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 1, "1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 2, "-0"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 2, "-1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 1, "12"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 3, "-12"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 3, "0.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 3, "1.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "11.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "0.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "11.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "-0.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "-1.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-11.1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-0.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "-1.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 6, "-11.11"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 3, "1e1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "1.1e1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "111e1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 5, "1e111"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1e-1"));
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_set(object, 4, "1e+1"));

    cr_expect_eq(UR_OK, ubjs_prmtv_is_hpn(object, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_HPN, type);

#ifndef NDEBUG
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(12, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("hpn 4 <1e+1>", debug, 12);
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_free(0));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, str, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;
    ubjs_prmtv_type type = UOT_MAX;
#ifndef NDEBUG
    char debug[11];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(instance_lib, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(instance_lib, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_str(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_str(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(0, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(0, v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_set(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_set(0, 0, v));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 3, "kra", &object));
    cr_expect_eq(UR_OK, ubjs_prmtv_str(instance_lib, 3, "kra", &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_str(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_set(object, 0, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    cr_expect_eq(3, vl);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    cr_expect_arr_eq("kra", v, 3);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_set(object, 2, "ur"));
    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    cr_expect_eq(2, vl);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    cr_expect_arr_eq("ur", v, 2);

    cr_expect_eq(UR_OK, ubjs_prmtv_is_str(object, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_STR, type);

#ifndef NDEBUG
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(10, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("str 2 <ur>", debug, 10);
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_free(0));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, array, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    ubjs_prmtv *other2;
    ubjs_array_iterator *iterator;
    ubjs_prmtv_type type = UOT_MAX;
    unsigned int vl = -1;
    ubjs_bool ret=0;
#ifndef NDEBUG
    char debug[8];
    unsigned int dlen = 0;
#endif

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(instance_lib, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(0, &object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_array(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_array(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(0, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(0, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(0, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, &other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(0, &iterator));
    ubjs_prmtv_free(&other);

    cr_expect_eq(UR_ERROR, ubjs_array_iterator_next(0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_free(0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(0, &other2));

    cr_expect_eq(UR_OK, ubjs_prmtv_array(instance_lib, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_array(object, 0));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(object, 0));

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 0);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    cr_expect_eq(0, vl);
    vl = -1;

    twill_returnui("array_get_length", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(object, &vl));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    other2 = 0;
    twill_returnui("array_get_first", UR_OK);
    twill_returno("array_get_first", other);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_first(object, &other2));
    cr_expect_eq(other, other2);
    ubjs_prmtv_free(&other);

    other2 = 0;
    twill_returnui("array_get_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(object, &other2));
    cr_expect_eq(0, other2);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    other2 = 0;
    twill_returnui("array_get_last", UR_OK);
    twill_returno("array_get_last", other);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_last(object, &other2));
    cr_expect_eq(other, other2);
    ubjs_prmtv_free(&other);

    other2 = 0;
    twill_returnui("array_get_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(object, &other2));
    cr_expect_eq(0, other2);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    other2 = 0;
    twill_returnui("array_get_at", UR_OK);
    twill_returno("array_get_at", other);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other2));
    cr_expect_eq(other, other2);
    ubjs_prmtv_free(&other);

    other2 = 0;
    twill_returnui("array_get_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, &other2));
    cr_expect_eq(0, other2);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_first", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_first(object, other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(object, other));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_last(object, other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(object, other));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_at", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_at(object, 0, other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("array_add_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, other));

    twill_returnui("array_delete_first", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_first(object));

    twill_returnui("array_delete_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(object));

    twill_returnui("array_delete_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_last(object));

    twill_returnui("array_delete_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(object));

    twill_returnui("array_delete_at", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_at(object, 0));

    twill_returnui("array_delete_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));

    twill_returnui("array_iterator_next", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_next(iterator));

    twill_returnui("array_iterator_next", UR_OK);
    cr_expect_eq(UR_OK, ubjs_array_iterator_next(iterator));

    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(iterator, 0));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    other2 = 0;
    twill_returnui("array_iterator_get", UR_OK);
    twill_returno("array_iterator_get", other);
    cr_expect_eq(UR_OK, ubjs_array_iterator_get(iterator, &other2));
    cr_expect_eq(other, other2);
    ubjs_prmtv_free(&other);

    twill_returnui("array_iterator_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_array_iterator_delete(iterator));

    twill_returnui("array_iterator_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_delete(iterator));

    cr_expect_eq(UR_OK, ubjs_array_iterator_free(&iterator));

#ifndef NDEBUG
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_get_length(object, &dlen));
    cr_expect_eq(5, dlen);
    cr_expect_eq(UR_OK, ubjs_prmtv_debug_string_copy(object, debug));
    cr_expect_arr_eq("array", debug, 5);
#endif

    cr_expect_eq(UR_OK, ubjs_prmtv_get_type(object, &type));
    cr_expect_eq(UOT_ARRAY, type);

    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

Test(primitives, object, .init = before, .fini = after)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other=0;
    ubjs_prmtv *other2=0;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;
    char key2[2];

    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(instance_lib, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(0, &object));
    cr_expect_eq(0, object);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_object(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_object(0, &ret));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(0, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(0, 0, ""));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(0, &iterator));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_next(0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_free(0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(0, &vl));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(0, key2));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(0, &other));

    cr_expect_eq(UR_OK, ubjs_prmtv_object(instance_lib, &object));
    cr_expect_neq(0, object);

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_is_object(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(object, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(object, 0));
    ubjs_prmtv_free(&other);

    twill_returnui("dict_get_length", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(object, &vl));

    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 1);
    vl = -1;
    cr_expect_eq(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    cr_expect_eq(1, vl);

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("dict_set", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 1, "a", other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("dict_set", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_set(object, 1, "a", other));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("dict_get", UR_OK);
    twill_returno("dict_get", other);
    other2 = 0;
    cr_expect_eq(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other2));
    cr_expect_eq(other2, other);
    ubjs_prmtv_free(&other);

    twill_returnui("dict_get", UR_ERROR);
    other2 = 0;
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other2));
    cr_expect_eq(other2, 0);

    twill_returnui("dict_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(object, 1, "a"));

    twill_returnui("dict_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));

    cr_expect_eq(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    cr_expect_neq(0, iterator);

    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(iterator, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(iterator, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(iterator, 0));

    twill_returnui("dict_iterator_next", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_next(iterator));

    twill_returnui("dict_iterator_next", UR_OK);
    cr_expect_eq(UR_OK, ubjs_object_iterator_next(iterator));

    twill_returnui("dict_iterator_get_key_length", UR_ERROR);
    vl = 0;
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(iterator, &vl));
    cr_expect_eq(vl, 0);

    twill_returnui("dict_iterator_get_key_length", UR_OK);
    twill_returnui("dict_iterator_get_key_length", 1);
    vl = 0;
    cr_expect_eq(UR_OK, ubjs_object_iterator_get_key_length(iterator, &vl));
    cr_expect_eq(1, vl);

    twill_returnui("dict_iterator_copy_key", UR_ERROR);
    key2[0] = 0;
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(iterator, key2));
    cr_expect_eq(key2[0], 0);

    twill_returnui("dict_iterator_copy_key", UR_OK);
    twill_returnui("dict_iterator_copy_key", 1);
    twill_returno("dict_iterator_copy_key", strdup("a"));
    key2[0] = 0;
    cr_expect_eq(UR_OK, ubjs_object_iterator_copy_key(iterator, key2));
    cr_expect_arr_eq("a", key2, 1);

    twill_returnui("dict_iterator_get_value", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(iterator, &other2));

    mock_prmtv(instance_lib, &mock_prmtv_ntype1, &other);
    twill_returnui("dict_iterator_get_value", UR_OK);
    twill_returno("dict_iterator_get_value", other);
    cr_expect_eq(UR_OK, ubjs_object_iterator_get_value(iterator, &other2));
    cr_expect_eq(other2, other);
    ubjs_prmtv_free(&other);

    twill_returnui("dict_iterator_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_object_iterator_delete(iterator));

    twill_returnui("dict_iterator_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_delete(iterator));

    cr_expect_eq(UR_OK, ubjs_object_iterator_free(&iterator));
    cr_expect_eq(0, iterator);

    cr_expect_eq(UR_OK, ubjs_prmtv_free(&object));
    cr_expect_eq(0, object);
}

unsigned int ubjs_test_primitives_len=7;
ubjs_test_primitive ubjs_test_primitives[] =
{
    {(ubjs_test_primitives_create)0, ubjs_test_primitives_test_int},
    {ubjs_test_primitives_create_float32, ubjs_test_primitives_test_float32},
    {ubjs_test_primitives_create_float64, ubjs_test_primitives_test_float64},
    {ubjs_test_primitives_create_char, ubjs_test_primitives_test_char},
    {ubjs_test_primitives_create_str, ubjs_test_primitives_test_str},
    {ubjs_test_primitives_create_hpn, ubjs_test_primitives_test_hpn},
    {ubjs_test_primitives_create_array, ubjs_test_primitives_test_array},
    {ubjs_test_primitives_create_object, ubjs_test_primitives_test_object}
};

void ubjs_test_primitives_test_int(ubjs_prmtv *p)
{
    ubjs_bool ret;
    int64_t v;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_int(p, &ret));
    if (UTRUE == ret)
    {
        return;
    }

    cr_expect_eq(UR_ERROR, ubjs_prmtv_int_get(p, &v));
}

void ubjs_test_primitives_create_float32(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_float32(instance_lib, 0, p);
}

void ubjs_test_primitives_test_float32(ubjs_prmtv *p)
{
    ubjs_bool ret;
    float32_t v;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float32(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_get(p, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float32_set(p, v));
}

void ubjs_test_primitives_create_float64(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_float64(instance_lib, 0, p);
}

void ubjs_test_primitives_test_float64(ubjs_prmtv *p)
{
    ubjs_bool ret;
    float64_t v;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float64(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_get(p, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_float64_set(p, v));
}

void ubjs_test_primitives_create_char(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_char(instance_lib, 0, p);
}

void ubjs_test_primitives_test_char(ubjs_prmtv *p)
{
    ubjs_bool ret;
    char v;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_char(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_get(p, &v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_char_set(p, v));
}

void ubjs_test_primitives_create_str(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_str(instance_lib, 1, "a", p);
}

void ubjs_test_primitives_test_str(ubjs_prmtv *p)
{
    ubjs_bool ret;
    unsigned int vl;
    char v[1];

    cr_expect_eq(UR_OK, ubjs_prmtv_is_str(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(p, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(p, v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_set(p, vl, v));
}

void ubjs_test_primitives_create_hpn(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_hpn(instance_lib, 1, "1", p);
}

void ubjs_test_primitives_test_hpn(ubjs_prmtv *p)
{
    ubjs_bool ret;
    unsigned int vl;
    char v[1];

    cr_expect_eq(UR_OK, ubjs_prmtv_is_hpn(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_get_length(p, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_copy_text(p, v));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_hpn_set(p, vl, v));
}

void ubjs_test_primitives_create_array(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_array(instance_lib, p);
}

void ubjs_test_primitives_test_array(ubjs_prmtv *p)
{
    ubjs_bool ret;
    ubjs_array_iterator *iterator=0;
    unsigned int vl;
    ubjs_prmtv *other=0;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_array(p, &ret));
    cr_expect_eq(UFALSE, ret);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(p, &vl));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(p, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(p, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(p, 0, &other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(p, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(p, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(p, 0, other));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(p));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(p));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(p, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(p, &iterator));
}

void ubjs_test_primitives_create_object(ubjs_library *instance_lib, ubjs_prmtv **p)
{
    ubjs_prmtv_object(instance_lib, p);
}

void ubjs_test_primitives_test_object(ubjs_prmtv *p)
{
    ubjs_bool ret;
    ubjs_object_iterator *iterator = 0;
    unsigned int vl = -1;
    ubjs_prmtv *other=0;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_object(p, &ret));
    cr_expect_eq(UFALSE, ret);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(p, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(p, &vl));
    cr_expect_eq(vl, -1);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(p, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(p, 0, 0, &other));
    cr_expect_eq(other, 0);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(p, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(p, 0, "", &other));
    cr_expect_eq(other, 0);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(p, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(p, 0, 0, other));
    cr_expect_eq(other, 0);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(p, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(p, 0, "", other));
    cr_expect_eq(other, 0);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(p, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(p, 0, ""));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(p, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(p, &iterator));
    cr_expect_eq(iterator, 0);
}

Test(primitives, calls_for_wrong_primitives, .init = before, .fini = after)
{
    unsigned int it, it2;
    ubjs_prmtv *p=0;

    for (it=0; it<ubjs_test_primitives_len; it++)
    {
        if (0 == ubjs_test_primitives[it].create)
        {
            continue;
        }

        (ubjs_test_primitives[it].create)(instance_lib, &p);

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
