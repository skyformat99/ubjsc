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

#include "test_glue_mock.h"

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
    ubjs_result ret = UR_ERROR;

    if (tmockui("get_length", &ret) && UR_OK == ret)
    {
        tmockui("get_length", plen);
    }

    return ret;
}

ubjs_result ubjs_glue_dict_mock_get(ubjs_glue_dict *this, unsigned int klen,
    char *key, void **pvalue)
{
    ubjs_result ret = UR_ERROR;

    *pvalue=0;

    if (tmockui("get", &ret) && UR_OK == ret)
    {
        tmocko("get", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_dict_mock_set(ubjs_glue_dict *this, unsigned int klen,
    char *key, void *value)
{
    ubjs_glue_dict_mock *amock = (ubjs_glue_dict_mock *)this->userdata;
    ubjs_result ret = UR_ERROR;

    (amock->value_free)(value);
    tmockui("set", &ret);
    return ret;
}

ubjs_result ubjs_glue_dict_mock_delete(ubjs_glue_dict *this, unsigned int klen,
    char *key)
{
    ubjs_result ret = UR_ERROR;
    tmockui("delete", &ret);
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterate(ubjs_glue_dict *this,
    ubjs_glue_dict_iterator **piterator)
{
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
    ubjs_result ret = UR_ERROR;
    tmockui("iterator_next", &ret);
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_get_key_length(ubjs_glue_dict_iterator *this,
    unsigned int *pklen)
{
    ubjs_result ret = UR_ERROR;
    *pklen=0;
    if (tmockui("iterator_get_key_length", &ret) && UR_OK == ret)
    {
        tmockui("iterator_get_key_length", pklen);
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_copy_key(ubjs_glue_dict_iterator *this, char *key)
{
    ubjs_result ret = UR_ERROR;
    unsigned int len;
    char *tmp;

    key[0] = 0;

    if (tmockui("iterator_copy_key", &ret) && UR_OK == ret &&
        tmockui("iterator_copy_key", &len) &&
        tmocko("iterator_copy_key", (void **)&tmp))
    {
        memcpy(key, tmp, len * sizeof(char));
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_get_value(ubjs_glue_dict_iterator *this,
    void **pvalue)
{
    ubjs_result ret = UR_ERROR;

    *pvalue = 0;

    if (tmockui("iterator_get_value", &ret) && UR_OK == ret)
    {
        tmocko("iterator_get_value", pvalue);
    }

    return ret;
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
