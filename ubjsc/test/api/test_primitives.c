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

TestSuite(primitives, .init = before, .fini = after);

#ifndef NDEBUG
Test(primitives, debug)
{
    ubjs_prmtv any = {0, 0};
    char text[1];
    unsigned int len;

    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_get_length(0, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(&any, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_debug_string_copy(0, text));
}
#endif

Test(primitives, ints)
{
    ubjs_prmtv *obj = 0;

    cr_expect_eq(UR_OK, ubjs_prmtv_int(instance_lib, 0, &obj));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&obj));

    cr_expect_eq(UR_OK, ubjs_prmtv_uint(instance_lib, 0, &obj));
    cr_expect_eq(UR_OK, ubjs_prmtv_free(&obj));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_uint(instance_lib, -1, &obj));
}
