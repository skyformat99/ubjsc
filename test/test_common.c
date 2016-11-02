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

#include <string.h>
#include <ubjs.h>
#include "test_common.h"

void suite_common(tcontext *context)
{
    tsuite *suite;
    TSUITE("common", 0, 0, &suite);
    tcontext_add_suite(context, suite);
    TTEST(suite, test_version);
}

void test_version()
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
