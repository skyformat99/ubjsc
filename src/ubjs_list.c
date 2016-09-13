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
#include "ubjs_list.h"

ubjs_result ubjs_list_new(ubjs_list_free_f free_f, ubjs_list **pthis)
{
    ubjs_list *this;
    this=(ubjs_list *)malloc(sizeof(struct ubjs_list));

    this->obj=0;
    this->free_f = free_f;

    this->prev=this;
    this->next=this;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_list_free(ubjs_list **pthis)
{
    ubjs_list *this;
    ubjs_list *it;

    if (0 == pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    it=this->next;

    while (this!=it)
    {
        this->next=it->next;
        if (0 != it->free_f)
        {
            (it->free_f)(it->obj);
        }
        free(it);
        it = this->next;
    }

    free(this);
    *pthis=0;
    return UR_OK;
}


ubjs_result ubjs_list_add(ubjs_list *this, void *obj)
{
    ubjs_list *it;

    if (0 == this)
    {
        return UR_ERROR;
    }

    ubjs_list_new(this->free_f, &it);
    it->obj=obj;

    this->prev->next=it;
    it->prev=this->prev;
    this->prev=it;
    it->next=this;
    return UR_OK;
}

ubjs_result ubjs_list_len(ubjs_list *this, unsigned int *plen)
{
    ubjs_list *it;
    int i=0;

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    it=this->next;

    while (this != it)
    {
        i++;
        it=it->next;
    }

    *plen=i;
    return UR_OK;
}
