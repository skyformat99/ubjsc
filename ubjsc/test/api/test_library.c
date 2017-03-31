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

Test(library, version)
{
    ubjs_bool ret;
    unsigned long version;

    ubjs_get_version(&version);

    ubjs_is_compatible(0x000000, &ret);
    cr_expect_eq(UFALSE, ret);
    ubjs_is_compatible(version, &ret);
    cr_expect_eq(UTRUE, ret);
    ubjs_is_compatible(version + 0x010000, &ret);
    cr_expect_eq(UFALSE, ret);

    /* We are 0.x */
    if (version < 0x010000)
    {
        ubjs_is_compatible(version + 0x000100, &ret);
        cr_expect_eq(UFALSE, ret);
        ubjs_is_compatible(version + 0x000001, &ret);
        cr_expect_eq(UTRUE, ret);
    }
    else
    {
        ubjs_is_compatible(version + 0x000100, &ret);
        cr_expect_eq(UTRUE, ret);
        ubjs_is_compatible(version + 0x000001, &ret);
        cr_expect_eq(UTRUE, ret);
    }
}

Test(library, library)
{
    ubjs_library *lib=0;
    ubjs_library_builder builder;

    cr_expect_eq(UR_ERROR, ubjs_library_builder_init(0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_alloc_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_alloc_f(0, malloc));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_free_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_free_f(0, free));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_array_builder(
        0, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_array_builder(
        0, ubjs_glue_array_mock_builder_new));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_dict_builder(
        0, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_dict_builder(
        0, ubjs_glue_dict_mock_builder_new));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_build(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_free(0));

    cr_expect_eq(UR_OK, ubjs_library_builder_init(&builder));

    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_alloc_f(&builder, 0));
    cr_expect_eq(UR_OK, ubjs_library_builder_set_alloc_f(&builder, malloc));

    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_free_f(&builder, 0));
    cr_expect_eq(UR_OK, ubjs_library_builder_set_free_f(&builder, free));

    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_array_builder(
        &builder, 0));
    cr_expect_eq(UR_OK, ubjs_library_builder_set_glue_array_builder(
        &builder, ubjs_glue_array_mock_builder_new));

    cr_expect_eq(UR_ERROR, ubjs_library_builder_set_glue_dict_builder(
        &builder, 0));
    cr_expect_eq(UR_OK, ubjs_library_builder_set_glue_dict_builder(
        &builder, ubjs_glue_dict_mock_builder_new));

    cr_expect_eq(UR_ERROR, ubjs_library_builder_build(&builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_library_builder_build(0, &lib));
    cr_expect_eq(0, lib);
    cr_expect_eq(UR_OK, ubjs_library_builder_build(&builder, &lib));
    cr_expect_neq(0, lib);
    cr_expect_eq(UR_ERROR, ubjs_library_builder_build(&builder, &lib));

    cr_expect_eq(UR_OK, ubjs_library_free(&lib));
    cr_expect_eq(0, lib);
    cr_expect_eq(UR_ERROR, ubjs_library_free(&lib));
}
