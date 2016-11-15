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

#include "ubjs_list_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

ubjs_result ubjs_list_new(ubjs_library *lib, ubjs_list_free_f free_f, ubjs_list **pthis)
{
    ubjs_list *this;
    this=(ubjs_list *)(lib->alloc_f)(sizeof(struct ubjs_list));
    this->lib=lib;

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

    this=*pthis;
    it=this->next;

    while (this!=it)
    {
        this->next=it->next;
        if (0 != it->free_f)
        {
            (it->free_f)(it->obj);
        }
        (this->lib->free_f)(it);
        it = this->next;
    }

    (this->lib->free_f)(this);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_list_add(ubjs_list *this, void *obj)
{
    ubjs_list *it;

    ubjs_list_new(this->lib, this->free_f, &it);
    it->obj=obj;

    this->prev->next=it;
    it->prev=this->prev;
    this->prev=it;
    it->next=this;
    return UR_OK;
}

ubjs_result ubjs_list_remove_first_and_get(ubjs_list *this, void **pobj)
{
    ubjs_list *it;

    it=this->next;
    this->next=it->next;
    this->next->prev=this;
    *pobj = it->obj;
    (this->lib->free_f)(it);
    return UR_OK;
}

ubjs_result ubjs_list_len(ubjs_list *this, unsigned int *plen)
{
    ubjs_list *it;
    int i=0;

    it=this->next;

    while (this != it)
    {
        i++;
        it=it->next;
    }

    *plen=i;
    return UR_OK;
}
