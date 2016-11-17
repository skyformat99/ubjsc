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
#include <stdlib.h>

#include <ubjs.h>
#include "test_common.h"

void suite_common(tcontext *context)
{
    tsuite *suite;
    TSUITE("common", 0, 0, &suite);
    tcontext_add_suite(context, suite);
    TTEST(suite, test_version);
    TTEST(suite, test_library);
}

void test_version(void **state)
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

void test_library(void **state)
{
    ubjs_library *lib=0;
    ubjs_glue_dict_factory mock_glue_dict_factory = (ubjs_glue_dict_factory)1;

    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, 0, 0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc, 0, 0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, free, 0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc,
        (ubjs_library_free_f)free, 0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, 0, 0, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc, 0, 0, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, (ubjs_library_free_f)free, 0, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc,
        (ubjs_library_free_f)free, 0, &lib));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, 0, mock_glue_dict_factory, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc, 0,
        mock_glue_dict_factory, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, free, mock_glue_dict_factory, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc,
        (ubjs_library_free_f)free, mock_glue_dict_factory, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, 0, mock_glue_dict_factory, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new((ubjs_library_alloc_f)malloc, 0,
        mock_glue_dict_factory, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_new(0, (ubjs_library_free_f)free,
        mock_glue_dict_factory, &lib));
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_ERROR, ubjs_library_free(0));

    TASSERT_EQUALI(UR_OK, ubjs_library_new((ubjs_library_alloc_f)malloc,
        (ubjs_library_free_f)free, mock_glue_dict_factory, &lib));
    TASSERT_NOT_EQUAL(0, lib);
    TASSERT_EQUALI(UR_OK, ubjs_library_free(&lib));
    TASSERT_EQUAL(0, lib);
}

ubjs_result ubjs_glue_dict_mock_factory(ubjs_library *lib, ubjs_glue_value_free value_free,
    ubjs_glue_dict **pthis)
{
    ubjs_glue_dict_mock *amock = 0;
    ubjs_glue_dict *this = 0;

    this = (ubjs_glue_dict *)(lib->alloc_f)(sizeof(struct ubjs_glue_dict));
    amock = (ubjs_glue_dict_mock *)(lib->alloc_f)(sizeof(struct ubjs_glue_dict_mock));
    amock->value_free = value_free;
    amock->lib=lib;

    this->lib=lib;
    this->userdata = (void *)amock;

    this->free_f = ubjs_glue_dict_mock_free;
    this->get_length_f = ubjs_glue_dict_mock_get_length;
    this->get_f = ubjs_glue_dict_mock_get;
    this->set_f = ubjs_glue_dict_mock_set;
    this->delete_f = ubjs_glue_dict_mock_delete;
    this->iterate_f = ubjs_glue_dict_mock_iterate;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_free(ubjs_glue_dict **pthis)
{
    ubjs_glue_dict *this = *pthis;
    ubjs_glue_dict_mock *amock = (ubjs_glue_dict_mock *)this->userdata;

    (this->lib->free_f)(amock);
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_get_length(ubjs_glue_dict *this, unsigned int *plen)
{
    ubjs_result ret = (ubjs_result) tmock();
    if (UR_OK == ret)
    {
        *plen = (unsigned int) tmock();
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_get(ubjs_glue_dict *this, unsigned int klen,
    char *key, void **pvalue)
{
    ubjs_result ret = (ubjs_result) tmock();
    if (UR_OK == ret)
    {
        *pvalue = (unsigned int) tmock();
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_set(ubjs_glue_dict *this, unsigned int klen,
    char *key, void *value)
{
    ubjs_glue_dict_mock *amock = (ubjs_glue_dict_mock *)this->userdata;
    (amock->value_free)(value);
    return (ubjs_result) tmock();
}

ubjs_result ubjs_glue_dict_mock_delete(ubjs_glue_dict *this, unsigned int klen,
    char *key)
{
    return (ubjs_result)tmock();
}

ubjs_result ubjs_glue_dict_mock_iterate(ubjs_glue_dict *this,
    ubjs_glue_dict_iterator **piterator)
{
    ubjs_glue_dict_mock *amock = (ubjs_glue_dict_mock *)this->userdata;
    ubjs_glue_dict_mock_iterator *mock_iterator = 0;
    ubjs_glue_dict_iterator *iterator = 0;

    mock_iterator = (ubjs_glue_dict_mock_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_dict_mock_iterator));

    iterator=(ubjs_glue_dict_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_dict_iterator));
    iterator->object=this;
    iterator->userdata=(void *)mock_iterator;

    iterator->free_f = ubjs_glue_dict_mock_iterator_free;
    iterator->next_f = ubjs_glue_dict_mock_iterator_next;
    iterator->get_key_length_f = ubjs_glue_dict_mock_iterator_get_key_length;
    iterator->copy_key_f = ubjs_glue_dict_mock_iterator_copy_key;
    iterator->get_value_f = ubjs_glue_dict_mock_iterator_get_value;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_iterator_next(ubjs_glue_dict_iterator *this)
{
    return (ubjs_result) tmock();
}

ubjs_result ubjs_glue_dict_mock_iterator_get_key_length(ubjs_glue_dict_iterator *this,
    unsigned int *pklen)
{
    *pklen = (unsigned int)tmock();
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_iterator_copy_key(ubjs_glue_dict_iterator *this, char *key)
{
    unsigned int len = (unsigned int)tmock();
    char *tmp = (char *)tmock();
    memcpy(key, tmp, len * sizeof(char));
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_iterator_get_value(ubjs_glue_dict_iterator *this,
    void **pvalue)
{
    *pvalue = (void *)tmock();
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_iterator_free(ubjs_glue_dict_iterator **piterator)
{
    ubjs_glue_dict_iterator *this=*piterator;
    ubjs_glue_dict_mock_iterator *iterator = (ubjs_glue_dict_mock_iterator *)this->userdata;

    (this->object->lib->free_f)(iterator);
    (this->object->lib->free_f)(this);
    *piterator=0;
    return UR_OK;
}

