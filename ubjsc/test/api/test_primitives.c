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

unsigned int ubjs_test_primitives_len=2;
ubjs_test_primitive ubjs_test_primitives[] =
{
    {(ubjs_test_primitives_create)0, ubjs_test_primitives_test_int},
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
