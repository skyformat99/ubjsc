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

#ifndef HAVE_TEST_GLUE_MOCK
#define HAVE_TEST_GLUE_MOCK

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs.h>
#include "test_frmwrk.h"

typedef struct ubjs_glue_dict_mock ubjs_glue_dict_mock;
typedef struct ubjs_glue_dict_mock_iterator ubjs_glue_dict_mock_iterator;

typedef struct ubjs_glue_array_mock ubjs_glue_array_mock;
typedef struct ubjs_glue_array_mock_builder ubjs_glue_array_mock_builder;
typedef struct ubjs_glue_array_mock_iterator ubjs_glue_array_mock_iterator;

struct ubjs_glue_dict_mock
{
    ubjs_library *lib;
    ubjs_glue_value_free value_free;
};

struct ubjs_glue_dict_mock_iterator
{
    int unused;
};

struct ubjs_glue_array_mock_builder
{
    ubjs_glue_value_free value_free;
};

struct ubjs_glue_array_mock
{
    ubjs_library *lib;
    ubjs_glue_value_free value_free;
};

struct ubjs_glue_array_mock_iterator
{
    int unused;
};

ubjs_result ubjs_glue_dict_mock_builder(ubjs_library *, ubjs_glue_value_free,
    ubjs_glue_dict **);
ubjs_result ubjs_glue_dict_mock_free(ubjs_glue_dict **);
ubjs_result ubjs_glue_dict_mock_get_length(ubjs_glue_dict *, unsigned int *);
ubjs_result ubjs_glue_dict_mock_get(ubjs_glue_dict *, unsigned int,
    char *, void **);
ubjs_result ubjs_glue_dict_mock_set(ubjs_glue_dict *, unsigned int,
    char *, void *);
ubjs_result ubjs_glue_dict_mock_delete(ubjs_glue_dict *, unsigned int,
    char *);
ubjs_result ubjs_glue_dict_mock_iterate(ubjs_glue_dict *,
    ubjs_glue_dict_iterator **);
ubjs_result ubjs_glue_dict_mock_iterator_next(ubjs_glue_dict_iterator *);
ubjs_result ubjs_glue_dict_mock_iterator_get_key_length(ubjs_glue_dict_iterator *,
    unsigned int *);
ubjs_result ubjs_glue_dict_mock_iterator_copy_key(ubjs_glue_dict_iterator *, char *);
ubjs_result ubjs_glue_dict_mock_iterator_get_value(ubjs_glue_dict_iterator *,
    void **);
ubjs_result ubjs_glue_dict_mock_iterator_free(ubjs_glue_dict_iterator **);

ubjs_result ubjs_glue_array_mock_builder_new(ubjs_library *, ubjs_glue_array_builder **);
ubjs_result ubjs_glue_array_mock_builder_free(ubjs_glue_array_builder **);
ubjs_result ubjs_glue_array_mock_builder_set_value_free(ubjs_glue_array_builder *,
    ubjs_glue_value_free);
ubjs_result ubjs_glue_array_mock_builder_set_length(ubjs_glue_array_builder *, unsigned int);
ubjs_result ubjs_glue_array_mock_builder_set_item_size(ubjs_glue_array_builder *, unsigned int);
ubjs_result ubjs_glue_array_mock_builder_build(ubjs_glue_array_builder *, ubjs_glue_array **);

ubjs_result ubjs_glue_array_mock_free(ubjs_glue_array **);
ubjs_result ubjs_glue_array_mock_get_length(ubjs_glue_array *, unsigned int *);
ubjs_result ubjs_glue_array_mock_get_first(ubjs_glue_array *, void **);
ubjs_result ubjs_glue_array_mock_get_last(ubjs_glue_array *, void **);
ubjs_result ubjs_glue_array_mock_get_at(ubjs_glue_array *, unsigned int, void **);
ubjs_result ubjs_glue_array_mock_add_first(ubjs_glue_array *, void *);
ubjs_result ubjs_glue_array_mock_add_last(ubjs_glue_array *, void *);
ubjs_result ubjs_glue_array_mock_add_at(ubjs_glue_array *, unsigned int, void *);
ubjs_result ubjs_glue_array_mock_delete_first(ubjs_glue_array *);
ubjs_result ubjs_glue_array_mock_delete_last(ubjs_glue_array *);
ubjs_result ubjs_glue_array_mock_delete_at(ubjs_glue_array *, unsigned int);
ubjs_result ubjs_glue_array_mock_iterate(ubjs_glue_array *,
    ubjs_glue_array_iterator **);
ubjs_result ubjs_glue_array_mock_iterator_next(ubjs_glue_array_iterator *);
ubjs_result ubjs_glue_array_mock_iterator_get(ubjs_glue_array_iterator *,
    void **);
ubjs_result ubjs_glue_array_mock_iterator_free(ubjs_glue_array_iterator **);

#ifdef __cplusplus
}
#endif

#endif
