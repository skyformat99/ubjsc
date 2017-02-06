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

#include <string.h>
#include <stdlib.h>

#include "test_glue_mock.h"

ubjs_result ubjs_glue_dict_mock_builder_new(ubjs_library *lib, ubjs_glue_dict_builder **pthis)
{
    ubjs_glue_dict_builder *this = 0;
    ubjs_glue_dict_mock_builder *data = 0;

    this = (ubjs_glue_dict_builder *)(lib->alloc_f)(sizeof(struct ubjs_glue_dict_builder));
    data = (ubjs_glue_dict_mock_builder *)(lib->alloc_f)(sizeof(
        struct ubjs_glue_dict_mock_builder));
    this->lib = lib;
    this->userdata = data;
    data->value_free = 0;

    this->set_value_free_f = ubjs_glue_dict_mock_builder_set_value_free;
    this->set_length_f = ubjs_glue_dict_mock_builder_set_length;
    this->set_item_size_f = ubjs_glue_dict_mock_builder_set_item_size;
    this->free_f = ubjs_glue_dict_mock_builder_free;
    this->build_f = ubjs_glue_dict_mock_builder_build;

    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_builder_free(ubjs_glue_dict_builder **pthis)
{
    ubjs_glue_dict_builder *this = *pthis;
    ubjs_glue_dict_mock_builder *data = (ubjs_glue_dict_mock_builder *)this->userdata;

    (this->lib->free_f)(data);
    (this->lib->free_f)(this);
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_builder_set_value_free(ubjs_glue_dict_builder *this,
    ubjs_glue_value_free value_free)
{
    ubjs_glue_dict_mock_builder *data = (ubjs_glue_dict_mock_builder *)this->userdata;
    data->value_free = value_free;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_builder_set_length(ubjs_glue_dict_builder *this,
    unsigned int length)
{
    ubjs_result ret = UR_ERROR;
    tmockui("dict_builder_set_length", &ret);
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_builder_set_item_size(ubjs_glue_dict_builder *this,
    unsigned int length)
{
    ubjs_result ret = UR_ERROR;
    tmockui("dict_builder_set_item_size", &ret);
    return UR_OK;
}

ubjs_result ubjs_glue_dict_mock_builder_build(ubjs_glue_dict_builder *this,
ubjs_glue_dict **parr)
{
    ubjs_glue_dict_mock_builder *data = (ubjs_glue_dict_mock_builder *)this->userdata;
    ubjs_glue_dict_mock *amock = 0;
    ubjs_glue_dict *arr = 0;

    arr = (ubjs_glue_dict *)(this->lib->alloc_f)(sizeof(struct ubjs_glue_dict));
    amock = (ubjs_glue_dict_mock *)(this->lib->alloc_f)(sizeof(struct ubjs_glue_dict_mock));
    amock->value_free = data->value_free;
    amock->lib = this->lib;

    arr->lib = this->lib;
    arr->userdata = (void *)amock;

    arr->free_f = ubjs_glue_dict_mock_free;
    arr->get_length_f = ubjs_glue_dict_mock_get_length;
    arr->get_f = ubjs_glue_dict_mock_get;
    arr->set_f = ubjs_glue_dict_mock_set;
    arr->delete_f = ubjs_glue_dict_mock_delete;
    arr->iterate_f = ubjs_glue_dict_mock_iterate;

    *parr=arr;
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

    if (tmockui("dict_get_length", &ret) && UR_OK == ret)
    {
        tmockui("dict_get_length", plen);
    }

    return ret;
}

ubjs_result ubjs_glue_dict_mock_get(ubjs_glue_dict *this, unsigned int klen,
    char *key, void **pvalue)
{
    ubjs_result ret = UR_ERROR;

    *pvalue=0;

    if (tmockui("dict_get", &ret) && UR_OK == ret)
    {
        tmocko("dict_get", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_dict_mock_set(ubjs_glue_dict *this, unsigned int klen,
    char *key, void *value)
{
    ubjs_glue_dict_mock *amock = (ubjs_glue_dict_mock *)this->userdata;
    ubjs_result ret = UR_ERROR;

    (amock->value_free)(value);
    tmockui("dict_set", &ret);
    return ret;
}

ubjs_result ubjs_glue_dict_mock_delete(ubjs_glue_dict *this, unsigned int klen,
    char *key)
{
    ubjs_result ret = UR_ERROR;
    tmockui("dict_delete", &ret);
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
    tmockui("dict_iterator_next", &ret);
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_get_key_length(ubjs_glue_dict_iterator *this,
    unsigned int *pklen)
{
    ubjs_result ret = UR_ERROR;
    *pklen=0;
    if (tmockui("dict_iterator_get_key_length", &ret) && UR_OK == ret)
    {
        tmockui("dict_iterator_get_key_length", pklen);
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_copy_key(ubjs_glue_dict_iterator *this, char *key)
{
    ubjs_result ret = UR_ERROR;
    unsigned int len;
    char *tmp;

    key[0] = 0;

    if (tmockui("dict_iterator_copy_key", &ret) && UR_OK == ret &&
        tmockui("dict_iterator_copy_key", &len) &&
        tmocko("dict_iterator_copy_key", (void **)&tmp))
    {
        memcpy(key, tmp, len * sizeof(char));
        free(tmp);
    }
    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_get_value(ubjs_glue_dict_iterator *this,
    void **pvalue)
{
    ubjs_result ret = UR_ERROR;

    *pvalue = 0;

    if (tmockui("dict_iterator_get_value", &ret) && UR_OK == ret)
    {
        tmocko("dict_iterator_get_value", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_dict_mock_iterator_free(ubjs_glue_dict_iterator **pthis)
{
    ubjs_glue_dict_iterator *this=*pthis;
    ubjs_glue_dict_mock_iterator *iterator = (ubjs_glue_dict_mock_iterator *)this->userdata;

    (this->object->lib->free_f)(iterator);
    (this->object->lib->free_f)(this);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_new(ubjs_library *lib, ubjs_glue_array_builder **pthis)
{
    ubjs_glue_array_builder *this = 0;
    ubjs_glue_array_mock_builder *data = 0;

    this = (ubjs_glue_array_builder *)(lib->alloc_f)(sizeof(struct ubjs_glue_array_builder));
    data = (ubjs_glue_array_mock_builder *)(lib->alloc_f)(sizeof(
        struct ubjs_glue_array_mock_builder));
    this->lib = lib;
    this->userdata = data;
    data->value_free = 0;

    this->set_value_free_f = ubjs_glue_array_mock_builder_set_value_free;
    this->set_length_f = ubjs_glue_array_mock_builder_set_length;
    this->set_item_size_f = ubjs_glue_array_mock_builder_set_item_size;
    this->free_f = ubjs_glue_array_mock_builder_free;
    this->build_f = ubjs_glue_array_mock_builder_build;

    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_free(ubjs_glue_array_builder **pthis)
{
    ubjs_glue_array_builder *this = *pthis;
    ubjs_glue_array_mock_builder *data = (ubjs_glue_array_mock_builder *)this->userdata;

    (this->lib->free_f)(data);
    (this->lib->free_f)(this);
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_set_value_free(ubjs_glue_array_builder *this,
    ubjs_glue_value_free value_free)
{
    ubjs_glue_array_mock_builder *data = (ubjs_glue_array_mock_builder *)this->userdata;
    data->value_free = value_free;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_set_length(ubjs_glue_array_builder *this,
    unsigned int length)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_builder_set_length", &ret);
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_set_item_size(ubjs_glue_array_builder *this,
    unsigned int length)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_builder_set_item_size", &ret);
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_builder_build(ubjs_glue_array_builder *this,
ubjs_glue_array **parr)
{
    ubjs_glue_array_mock_builder *data = (ubjs_glue_array_mock_builder *)this->userdata;
    ubjs_glue_array_mock *amock = 0;
    ubjs_glue_array *arr = 0;

    arr = (ubjs_glue_array *)(this->lib->alloc_f)(sizeof(struct ubjs_glue_array));
    amock = (ubjs_glue_array_mock *)(this->lib->alloc_f)(sizeof(struct ubjs_glue_array_mock));
    amock->value_free = data->value_free;
    amock->lib = this->lib;

    arr->lib = this->lib;
    arr->userdata = (void *)amock;

    arr->free_f = ubjs_glue_array_mock_free;
    arr->get_length_f = ubjs_glue_array_mock_get_length;
    arr->get_first_f = ubjs_glue_array_mock_get_first;
    arr->get_last_f = ubjs_glue_array_mock_get_last;
    arr->get_at_f = ubjs_glue_array_mock_get_at;
    arr->add_first_f = ubjs_glue_array_mock_add_first;
    arr->add_last_f = ubjs_glue_array_mock_add_last;
    arr->add_at_f = ubjs_glue_array_mock_add_at;
    arr->delete_first_f = ubjs_glue_array_mock_delete_first;
    arr->delete_last_f = ubjs_glue_array_mock_delete_last;
    arr->delete_at_f = ubjs_glue_array_mock_delete_at;
    arr->iterate_f = ubjs_glue_array_mock_iterate;

    *parr=arr;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_free(ubjs_glue_array **pthis)
{
    ubjs_glue_array *this = *pthis;
    ubjs_glue_array_mock *amock = (ubjs_glue_array_mock *)this->userdata;

    (this->lib->free_f)(amock);
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_get_length(ubjs_glue_array *this, unsigned int *plen)
{
    ubjs_result ret = UR_ERROR;
    if (tmockui("array_get_length", &ret) && UR_OK == ret)
    {
        tmockui("array_get_length", plen);
    }

    return ret;
}

ubjs_result ubjs_glue_array_mock_get_first(ubjs_glue_array *this, void **pvalue)
{
    ubjs_result ret = UR_ERROR;
    *pvalue=0;

    if (tmockui("array_get_first", &ret) && UR_OK == ret)
    {
        tmocko("array_get_first", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_array_mock_get_last(ubjs_glue_array *this, void **pvalue)
{
    ubjs_result ret = UR_ERROR;
    *pvalue=0;

    if (tmockui("array_get_last", &ret) && UR_OK == ret)
    {
        tmocko("array_get_last", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_array_mock_get_at(ubjs_glue_array *this, unsigned int at, void **pvalue)
{
    ubjs_result ret = UR_ERROR;
    *pvalue=0;

    if (tmockui("array_get_at", &ret) && UR_OK == ret)
    {
        tmocko("array_get_at", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_array_mock_add_first(ubjs_glue_array *this, void *value)
{
    ubjs_glue_array_mock *amock = (ubjs_glue_array_mock *)this->userdata;
    ubjs_result ret = UR_ERROR;

    (amock->value_free)(value);
    tmockui("array_add_first", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_add_last(ubjs_glue_array *this, void *value)
{
    ubjs_glue_array_mock *amock = (ubjs_glue_array_mock *)this->userdata;
    ubjs_result ret = UR_ERROR;

    (amock->value_free)(value);
    tmockui("array_add_last", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_add_at(ubjs_glue_array *this, unsigned int at, void *value)
{
    ubjs_glue_array_mock *amock = (ubjs_glue_array_mock *)this->userdata;
    ubjs_result ret = UR_ERROR;

    (amock->value_free)(value);
    tmockui("array_add_at", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_delete_first(ubjs_glue_array *this)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_delete_first", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_delete_last(ubjs_glue_array *this)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_delete_last", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_delete_at(ubjs_glue_array *this, unsigned int at)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_delete_at", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_iterate(ubjs_glue_array *this,
    ubjs_glue_array_iterator **piterator)
{
    ubjs_glue_array_mock_iterator *mock_iterator = 0;
    ubjs_glue_array_iterator *iterator = 0;

    mock_iterator = (ubjs_glue_array_mock_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_array_mock_iterator));

    iterator=(ubjs_glue_array_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_array_iterator));
    iterator->array=this;
    iterator->userdata=(void *)mock_iterator;

    iterator->free_f = ubjs_glue_array_mock_iterator_free;
    iterator->next_f = ubjs_glue_array_mock_iterator_next;
    iterator->get_f = ubjs_glue_array_mock_iterator_get;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_array_mock_iterator_next(ubjs_glue_array_iterator *this)
{
    ubjs_result ret = UR_ERROR;
    tmockui("array_iterator_next", &ret);
    return ret;
}

ubjs_result ubjs_glue_array_mock_iterator_get(ubjs_glue_array_iterator *this,
    void **pvalue)
{
    ubjs_result ret = UR_ERROR;
    *pvalue = 0;

    if (tmockui("array_iterator_get", &ret) && UR_OK == ret)
    {
        tmocko("array_iterator_get", pvalue);
    }

    return ret;
}

ubjs_result ubjs_glue_array_mock_iterator_free(ubjs_glue_array_iterator **pthis)
{
    ubjs_glue_array_iterator *this=*pthis;
    ubjs_glue_array_mock_iterator *iterator = (ubjs_glue_array_mock_iterator *)this->userdata;

    (this->array->lib->free_f)(iterator);
    (this->array->lib->free_f)(this);
    *pthis=0;
    return UR_OK;
}
