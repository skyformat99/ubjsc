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

#include <stdlib.h>
#include "test_list.h"

void test_list_new(test_list_free_f free_f, test_list **pthis)
{
    test_list *this;
    this=(test_list *)malloc(sizeof(struct test_list));

    this->free_f=free_f;
    this->len=0;
    this->sentinel=0;
    test_list_item_new(this, 0, &(this->sentinel));

    *pthis=this;
}

void test_list_free(test_list **pthis)
{
    test_list *this = 0;
    test_list_item *it = 0;

    this=*pthis;
    it = this->sentinel->next;

    while (it != this->sentinel)
    {
        test_list_remove(this, it);
        it = this->sentinel->next;
    }

    test_list_item_free(&(this->sentinel));
    free(this);
    *pthis=0;
}

void test_list_item_new(test_list *list, void *obj, test_list_item **pthis)
{
    test_list_item *this;
    this=(test_list_item *)malloc(sizeof(struct test_list_item));

    this->obj=obj;
    this->prev=this;
    this->next=this;
    this->list=list;

    *pthis=this;
}

void test_list_item_free(test_list_item **pthis)
{
    test_list_item *this = 0;

    this=*pthis;
    if (0 != this->obj && 0 != this->list->free_f)
    {
        (this->list->free_f)(&(this->obj));
    }

    free(this);
    *pthis=0;
}

int test_list_add(test_list *this, void *obj, test_list_item **pit)
{
    test_list_item *it;

    if (0 == this)
    {
        return 0;
    }

    test_list_item_new(this, obj, &it);

    this->sentinel->prev->next=it;
    it->prev=this->sentinel->prev;
    this->sentinel->prev=it;
    it->next=this->sentinel;

    if (0 != pit)
    {
        *pit=it;
    }
    this->len++;
    return 1;
}

void test_list_len(test_list *this, unsigned int *plen)
{
    *plen = this->len;
}

int test_list_get(test_list *this, int pos, test_list_item **pit)
{
    test_list_item *it;
    int i=0;

    it=this->sentinel->next;
    while (it != this->sentinel && i < pos)
    {
        i++;
        it=it->next;
    }

    if (it==this->sentinel)
    {
        return 0;
    }

    *pit = it;
    return 1;
}

void test_list_remove(test_list *this, test_list_item *it)
{
    it->prev->next=it->next;
    it->next->prev=it->prev;
    test_list_item_free(&it);
    this->len--;
}
