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
    TTEST(suite, test_common_endian);
    TTEST(suite, test_version);
}

int arrcmp(uint8_t *left, uint8_t *right, unsigned int len)
{
    unsigned int i;
    for (i=0; i<len; i++)
    {
        if (left[i] != right[i])
        {
            return 0;
        }
    }
    return 1;
}

void test_common_endian()
{
    uint8_t abig[] = {1, 2, 3, 4, 5};
    uint8_t alittle[] = {5, 4, 3, 2, 1};
    uint8_t aout[5];
    ubjs_endian_host_type ret;
    ubjs_bool ret2;

    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(-1));
    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(4));
    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_get(0));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_LITTLE));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_LITTLE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    TASSERT_EQUAL(UFALSE, ret2);

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_BIG));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_BIG, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    TASSERT_EQUAL(UTRUE, ret2);

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_DEFAULT));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_DEFAULT, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));

    if (UFALSE == ret2)
    {
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    }
    else
    {
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    }
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
