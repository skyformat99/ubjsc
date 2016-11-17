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

#include "ubjs_glue_dict_list_prv.h"

ubjs_result ubjs_glue_dict_list_factory(ubjs_library *lib, ubjs_glue_value_free value_free,
    ubjs_glue_dict **pthis)
{
    ubjs_dict_list *list = 0;
    ubjs_dict_list_item *sentinel = 0;
    ubjs_glue_dict *this = 0;

    this = (ubjs_glue_dict *)(lib->alloc_f)(sizeof(struct ubjs_glue_dict));

    list = (ubjs_dict_list *)(lib->alloc_f)(sizeof(struct ubjs_dict_list));
    list->value_free = value_free;
    list->length = 0;
    list->lib=lib;

    sentinel = (ubjs_dict_list_item *)(lib->alloc_f)(sizeof(struct ubjs_dict_list_item));
    sentinel->key_length = 0;
    sentinel->key = 0;
    sentinel->value = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    list->sentinel=sentinel;

    this->lib=lib;
    this->userdata = (void *)list;

    this->free_f = ubjs_glue_dict_list_free;
    this->get_length_f = ubjs_glue_dict_list_get_length;
    this->get_f = ubjs_glue_dict_list_get;
    this->set_f = ubjs_glue_dict_list_set;
    this->delete_f = ubjs_glue_dict_list_delete;
    this->iterate_f = ubjs_glue_dict_list_iterate;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_free(ubjs_glue_dict **pthis)
{
    ubjs_glue_dict *this = *pthis;
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    ubjs_dict_list_item *sentinel = list->sentinel;
    ubjs_dict_list_item *at = sentinel->next;

    while (at != sentinel)
    {
        sentinel->next = at->next;
        (this->lib->free_f)(at->key);
        (list->value_free)(at->value);
        at = sentinel->next;
    }

    (this->lib->free_f)(sentinel);
    (this->lib->free_f)(list);
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_get_length(ubjs_glue_dict *this, unsigned int *plen)
{
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    *plen = list->length;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_get(ubjs_glue_dict *this, unsigned int klen,
    char *key, void **pvalue)
{
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    ubjs_dict_list_item *sentinel = list->sentinel;
    ubjs_dict_list_item *at = sentinel->next;

    while (at != sentinel)
    {
        if (at->key_length == klen && 0 == strncmp(key, at->key, klen))
        {
            *pvalue = at->value;
            return UR_OK;
        }
        at = at->next;
    }
    return UR_ERROR;
}

ubjs_result ubjs_glue_dict_list_set(ubjs_glue_dict *this, unsigned int klen,
    char *key, void *value)
{
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    ubjs_dict_list_item *sentinel = list->sentinel;
    ubjs_dict_list_item *at = sentinel->next;
    ubjs_dict_list_item *anew = 0;

    while (at != sentinel)
    {
        int ret;
        unsigned int common_length = klen;

        if (at->key_length < klen)
        {
            common_length = at->key_length;
        }

        ret = strncmp(key, at->key, common_length);

        if (ret < 0 || (ret == 0 && klen < common_length))
        {
            anew = (ubjs_dict_list_item *)(list->lib->alloc_f)(sizeof(struct ubjs_dict_list_item));
            anew->key_length = klen;
            anew->key = (char *)(list->lib->alloc_f)(sizeof(char) * klen);
            memcpy(anew->key, key, sizeof(char) * klen);
            anew->value = value;
            anew->prev = at->prev;
            anew->next = at;
            anew->prev->next=anew;
            at->prev=anew;
            list->length++;
            return UR_OK;
        }
        else if (ret == 0 && at->key_length == klen)
        {
            (list->value_free)(at->value);
            at->value = value;
            return UR_OK;
        }
        at = at->next;
    }

    anew = (ubjs_dict_list_item *)(list->lib->alloc_f)(sizeof(struct ubjs_dict_list_item));
    anew->key_length = klen;
    anew->key = (char *)(list->lib->alloc_f)(sizeof(char) * klen);
    memcpy(anew->key, key, sizeof(char) * klen);
    anew->value = value;
    anew->prev = sentinel->prev;
    anew->next = sentinel;
    anew->prev->next=anew;
    sentinel->prev=anew;
    list->length++;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_delete(ubjs_glue_dict *this, unsigned int klen,
    char *key)
{
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    ubjs_dict_list_item *sentinel = list->sentinel;
    ubjs_dict_list_item *at = sentinel->next;

    while (at != sentinel)
    {
        if (at->key_length == klen && 0 == strncmp(key, at->key, klen))
        {
            at->prev->next = at->next;
            at->next->prev = at->prev;

            (this->lib->free_f)(at->key);
            (list->value_free)(at->value);
            (this->lib->free_f)(at);
            list->length--;
            return UR_OK;
        }
        at = at->next;
    }
    return UR_ERROR;
}

ubjs_result ubjs_glue_dict_list_iterate(ubjs_glue_dict *this,
    ubjs_glue_dict_iterator **piterator)
{
    ubjs_dict_list *list = (ubjs_dict_list *)this->userdata;
    ubjs_dict_list_item *sentinel = list->sentinel;
    ubjs_dict_list_iterator *list_iterator = 0;
    ubjs_glue_dict_iterator *iterator = 0;

    list_iterator = (ubjs_dict_list_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_dict_list_iterator));
    list_iterator->at = sentinel;
    list_iterator->list = list;

    iterator=(ubjs_glue_dict_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_dict_iterator));
    iterator->object=this;
    iterator->userdata=(void *)list_iterator;

    iterator->free_f = ubjs_glue_dict_list_iterator_free;
    iterator->next_f = ubjs_glue_dict_list_iterator_next;
    iterator->get_key_length_f = ubjs_glue_dict_list_iterator_get_key_length;
    iterator->copy_key_f = ubjs_glue_dict_list_iterator_copy_key;
    iterator->get_value_f = ubjs_glue_dict_list_iterator_get_value;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_iterator_free(ubjs_glue_dict_iterator **pthis)
{
    ubjs_glue_dict_iterator *this = *pthis;
    ubjs_dict_list_iterator *iterator = (ubjs_dict_list_iterator *)this->userdata;

    (this->object->lib->free_f)(iterator);
    (this->object->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_iterator_next(ubjs_glue_dict_iterator *this)
{
    ubjs_dict_list_iterator *iterator = (ubjs_dict_list_iterator *)this->userdata;

    iterator->at = iterator->at->next;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_iterator_get_key_length(ubjs_glue_dict_iterator *this,
    unsigned int *klen)
{
    ubjs_dict_list_iterator *iterator = (ubjs_dict_list_iterator *)this->userdata;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    *klen = iterator->at->key_length;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_iterator_copy_key(ubjs_glue_dict_iterator *this, char *key)
{
    ubjs_dict_list_iterator *iterator = (ubjs_dict_list_iterator *)this->userdata;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    memcpy(key, iterator->at->key, sizeof(char) * iterator->at->key_length);
    return UR_OK;
}

ubjs_result ubjs_glue_dict_list_iterator_get_value(ubjs_glue_dict_iterator *this,
    void **pvalue)
{
    ubjs_dict_list_iterator *iterator = (ubjs_dict_list_iterator *)this->userdata;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    *pvalue = iterator->at->value;
    return UR_OK;
}
