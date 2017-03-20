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

#include "test_common.h"
#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

Test(writer, free_primitives_early_null)
{
    sw_verifyd_free_primitives_early(instance_lib, ubjs_prmtv_null(), UTRUE);
}

Test(writer, free_primitives_early_noop)
{
    sw_verifyd_free_primitives_early(instance_lib, ubjs_prmtv_noop(), UTRUE);
}

Test(writer, free_primitives_early_true)
{
    sw_verifyd_free_primitives_early(instance_lib, ubjs_prmtv_true(), UTRUE);
}

Test(writer, free_primitives_early_false)
{
    sw_verifyd_free_primitives_early(instance_lib, ubjs_prmtv_false(), UTRUE);
}

Test(writer, free_primitives_early_int8)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_int8(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_uint8)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_uint8(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_int16)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_int16(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_int32)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_int32(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_int64)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_int64(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_float32)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_float32(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_float64)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_float64(instance_lib, 0, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_char)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_char(instance_lib, 'R', &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_str)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_str(instance_lib, 5, "rower", &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

Test(writer, free_primitives_early_hpn)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_hpn(instance_lib, 5, "11111", &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
}

/*
Test(writer, free_primitives_early_array)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_array(instance_lib, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}

Test(writer, free_primitives_early_array_deep)
{
    ubjs_prmtv *value = 0;
    unsigned int i;

    ubjs_prmtv_array(instance_lib, &value);
    for (i = 0; i < 32; i++)
    {
        ubjs_prmtv *v2 = 0;
        ubjs_prmtv_array(instance_lib, &v2);
        ubjs_prmtv_array_add_last(v2, value);
        value = v2;
    }

    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}


Test(writer, free_primitives_early_array_long)
{
    ubjs_prmtv *value = 0;
    unsigned int i;

    ubjs_prmtv_array(instance_lib, &value);
    for (i = 0; i < 32; i++)
    {
        ubjs_prmtv_array_add_last(value, ubjs_prmtv_null());
    }

    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}

Test(writer, free_primitives_early_object)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv_object(instance_lib, &value);
    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}

Test(writer, free_primitives_early_object_deep)
{
    ubjs_prmtv *value = 0;
    unsigned int i;

    ubjs_prmtv_object(instance_lib, &value);
    for (i = 0; i < 32; i++)
    {
        ubjs_prmtv *v2 = 0;
        ubjs_prmtv_object(instance_lib, &v2);
        ubjs_prmtv_object_set(v2, 1, "a", value);
        value = v2;
    }

    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}


Test(writer, free_primitives_early_object_long)
{
    ubjs_prmtv *value = 0;
    unsigned int i;
    char key[3];

    ubjs_prmtv_object(instance_lib, &value);
    for (i = 0; i < 32; i++)
    {
        sprintf(key, "%u", i);
        ubjs_prmtv_object_set(value, strlen(key), key, ubjs_prmtv_null());
    }

    sw_verifyd_free_primitives_early(instance_lib, value, UTRUE);
    cr_assert_eq(0, value);
}

*/
