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

#include "ubjs_glue_array_list_prv.h"

ubjs_result ubjs_glue_array_list_factory(ubjs_library *lib, ubjs_glue_value_free value_free,
    ubjs_glue_array **pthis)
{
    ubjs_array_list *list = 0;
    ubjs_array_list_item *sentinel = 0;
    ubjs_glue_array *this = 0;

    this = (ubjs_glue_array *)(lib->alloc_f)(sizeof(struct ubjs_glue_array));

    list = (ubjs_array_list *)(lib->alloc_f)(sizeof(struct ubjs_array_list));
    list->value_free = value_free;
    list->length = 0;
    list->lib=lib;

    sentinel = (ubjs_array_list_item *)(lib->alloc_f)(sizeof(struct ubjs_array_list_item));
    sentinel->value = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    list->sentinel=sentinel;

    this->lib=lib;
    this->userdata = (void *)list;

    this->free_f = ubjs_glue_array_list_free;
    this->get_length_f = ubjs_glue_array_list_get_length;
    this->get_first_f = ubjs_glue_array_list_get_first;
    this->get_last_f = ubjs_glue_array_list_get_last;
    this->get_at_f = ubjs_glue_array_list_get_at;
    this->add_first_f = ubjs_glue_array_list_add_first;
    this->add_last_f = ubjs_glue_array_list_add_last;
    this->add_at_f = ubjs_glue_array_list_add_at;
    this->delete_first_f = ubjs_glue_array_list_delete_first;
    this->delete_last_f = ubjs_glue_array_list_delete_last;
    this->delete_at_f = ubjs_glue_array_list_delete_at;
    this->iterate_f = ubjs_glue_array_list_iterate;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_free(ubjs_glue_array **pthis)
{
    ubjs_glue_array *this = *pthis;
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *sentinel = list->sentinel;
    ubjs_array_list_item *at = sentinel->next;

    while (at != sentinel)
    {
        sentinel->next = at->next;
        (list->value_free)(at->value);
        (this->lib->free_f)(at);
        at = sentinel->next;
    }

    (this->lib->free_f)(sentinel);
    (this->lib->free_f)(list);
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_get_length(ubjs_glue_array *this, unsigned int *plen)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    *plen = list->length;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_get_first(ubjs_glue_array *this, void **pvalue)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    if (0 == list->length)
    {
        return UR_ERROR;
    }

    *pvalue = list->sentinel->next->value;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_get_last(ubjs_glue_array *this, void **pvalue)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    if (0 == list->length)
    {
        return UR_ERROR;
    }

    *pvalue = list->sentinel->prev->value;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_get_at(ubjs_glue_array *this, unsigned int at,
    void **pvalue)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *it;
    unsigned int i;

    if (0 == list->length || at >= list->length)
    {
        return UR_ERROR;
    }

    for (i = 0, it = list->sentinel->next; i < at; i++, it = it->next)
    {
    }

    *pvalue = it->value;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_add_first(ubjs_glue_array *this, void *value)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *anew;

    anew = (ubjs_array_list_item *)(list->lib->alloc_f)(sizeof(struct ubjs_array_list_item));
    anew->value = value;
    anew->prev = list->sentinel;
    anew->next = list->sentinel->next;
    anew->prev->next=anew;
    anew->next->prev=anew;
    list->length++;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_add_last(ubjs_glue_array *this, void *value)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *anew;

    anew = (ubjs_array_list_item *)(list->lib->alloc_f)(sizeof(struct ubjs_array_list_item));
    anew->value = value;
    anew->prev = list->sentinel->prev;
    anew->next = list->sentinel;
    anew->prev->next=anew;
    anew->next->prev=anew;
    list->length++;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_add_at(ubjs_glue_array *this, unsigned int at,
    void *value)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *after;
    ubjs_array_list_item *anew;
    unsigned int i;

    if (at > list->length)
    {
        return UR_ERROR;
    }

    for (i = 0, after = list->sentinel; i < at; i++, after = after->next)
    {
    }

    anew = (ubjs_array_list_item *)(list->lib->alloc_f)(sizeof(struct ubjs_array_list_item));
    anew->value = value;
    anew->prev = after;
    anew->next = after->next;
    anew->prev->next=anew;
    anew->next->prev=anew;
    list->length++;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_delete_first(ubjs_glue_array *this)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *at;

    if (0 == list->length)
    {
        return UR_ERROR;
    }

    at = list->sentinel->next;
    at->prev->next = at->next;
    at->next->prev = at->prev;

    (list->value_free)(at->value);
    (this->lib->free_f)(at);
    list->length--;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_delete_last(ubjs_glue_array *this)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *at;

    if (0 == list->length)
    {
        return UR_ERROR;
    }

    at = list->sentinel->prev;
    at->prev->next = at->next;
    at->next->prev = at->prev;

    (list->value_free)(at->value);
    (this->lib->free_f)(at);
    list->length--;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_delete_at(ubjs_glue_array *this, unsigned int at)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *it;
    unsigned int i;

    if (0 == list->length || at >= list->length)
    {
        return UR_ERROR;
    }

    for (i = 0, it = list->sentinel->next; i < at; i++, it = it->next)
    {
    }

    it->prev->next = it->next;
    it->next->prev = it->prev;

    (list->value_free)(it->value);
    (this->lib->free_f)(it);
    list->length--;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_iterate(ubjs_glue_array *this,
    ubjs_glue_array_iterator **piterator)
{
    ubjs_array_list *list = (ubjs_array_list *)this->userdata;
    ubjs_array_list_item *sentinel = list->sentinel;
    ubjs_array_list_iterator *list_iterator = 0;
    ubjs_glue_array_iterator *iterator = 0;

    list_iterator = (ubjs_array_list_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_array_list_iterator));
    list_iterator->at = sentinel;
    list_iterator->list = list;

    iterator=(ubjs_glue_array_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_array_iterator));
    iterator->object=this;
    iterator->userdata=(void *)list_iterator;

    iterator->free_f = ubjs_glue_array_list_iterator_free;
    iterator->next_f = ubjs_glue_array_list_iterator_next;
    iterator->get_value_f = ubjs_glue_array_list_iterator_get_value;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_iterator_free(ubjs_glue_array_iterator **pthis)
{
    ubjs_glue_array_iterator *this = *pthis;
    ubjs_array_list_iterator *iterator = (ubjs_array_list_iterator *)this->userdata;

    (this->object->lib->free_f)(iterator);
    (this->object->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_array_list_iterator_next(ubjs_glue_array_iterator *this)
{
    ubjs_array_list_iterator *iterator = (ubjs_array_list_iterator *)this->userdata;

    iterator->at = iterator->at->next;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    return UR_OK;
}

ubjs_result ubjs_glue_array_list_iterator_get_value(ubjs_glue_array_iterator *this,
    void **pvalue)
{
    ubjs_array_list_iterator *iterator = (ubjs_array_list_iterator *)this->userdata;
    if (iterator->at == iterator->list->sentinel)
    {
        return UR_ERROR;
    }

    *pvalue = iterator->at->value;
    return UR_OK;
}
