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
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <ubjs.h>
#include "test_glue_mock.h"
#include "test_common.h"

void suite_common(tcontext *context)
{
    tsuite *suite;
    TSUITE("common", 0, 0, &suite);
    tcontext_add_suite(context, suite);
    TTEST(suite, test_version);
    TTEST(suite, test_library);
}

void test_version(void)
{
    ubjs_bool ret;
    unsigned long version;

    ubjs_get_version(&version);

    ubjs_is_compatible(0x000000, &ret);
    TASSERT_EQUAL(UFALSE, ret);
    ubjs_is_compatible(version, &ret);
    TASSERT_EQUAL(UTRUE, ret);
    ubjs_is_compatible(version + 0x010000, &ret);
    TASSERT_EQUAL(UFALSE, ret);

    /* We are 0.x */
    if (version < 0x010000)
    {
        ubjs_is_compatible(version + 0x000100, &ret);
        TASSERT_EQUAL(UFALSE, ret);
        ubjs_is_compatible(version + 0x000001, &ret);
        TASSERT_EQUAL(UTRUE, ret);
    }
    else
    {
        ubjs_is_compatible(version + 0x000100, &ret);
        TASSERT_EQUAL(UTRUE, ret);
        ubjs_is_compatible(version + 0x000001, &ret);
        TASSERT_EQUAL(UTRUE, ret);
    }
}

void test_library(void)
{
    ubjs_library *lib=0;
    ubjs_library_builder *builder=0;

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_new(0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_alloc_f(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_alloc_f(0, malloc));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_free_f(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_free_f(0, free));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_array_factory(
        0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_array_factory(
        0, ubjs_glue_array_mock_factory));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_dict_factory(
        0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_dict_factory(
        0, ubjs_glue_dict_mock_factory));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_build(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_free(0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new_stdlib(0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_free(0));

    TASSERT_EQUALI(UR_OK, ubjs_library_builder_new(&builder));
    TASSERT_NOT_EQUAL(0, builder);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_new(&builder));

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_alloc_f(builder, 0));
    TASSERT_EQUALI(UR_OK, ubjs_library_builder_set_alloc_f(builder, malloc));

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_free_f(builder, 0));
    TASSERT_EQUALI(UR_OK, ubjs_library_builder_set_free_f(builder, free));

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_array_factory(
        builder, 0));
    TASSERT_EQUALI(UR_OK, ubjs_library_builder_set_glue_array_factory(
        builder, ubjs_glue_array_mock_factory));

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_set_glue_dict_factory(
        builder, 0));
    TASSERT_EQUALI(UR_OK, ubjs_library_builder_set_glue_dict_factory(
        builder, ubjs_glue_dict_mock_factory));

    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_build(builder, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_build(0, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_OK, ubjs_library_builder_build(builder, &lib));
    TASSERT_NOT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_build(builder, &lib));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new_stdlib(&lib));

    TASSERT_EQUALI(UR_OK, ubjs_library_free(&lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_free(&lib));

    TASSERT_EQUALI(UR_OK, ubjs_library_builder_free(&builder));
    TASSERT_EQUAL(0, builder);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_builder_free(&builder));

    TASSERT_EQUALI(UR_OK, ubjs_library_new_stdlib(&lib));
    TASSERT_NOT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_OK, ubjs_library_free(&lib));
    TASSERT_EQUAL(0, lib);
}
