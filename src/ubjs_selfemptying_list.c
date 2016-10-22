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
#include "ubjs_selfemptying_list.h"

ubjs_result ubjs_selfemptying_list_new(ubjs_list_free_f free_f,
    ubjs_selfemptying_list_callback callback, void *userdata, ubjs_selfemptying_list **pthis)
{
    ubjs_selfemptying_list *this;
    this=(ubjs_selfemptying_list *)malloc(sizeof(struct ubjs_selfemptying_list));

    ubjs_list_new(free_f, &(this->list));
    this->callback=callback;
    this->is_in_callback=UFALSE;
    this->userdata=userdata;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_selfemptying_list_free(ubjs_selfemptying_list **pthis)
{
    ubjs_selfemptying_list *this=*pthis;

    ubjs_list_free(&(this->list));
    free(this);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_selfemptying_list_add(ubjs_selfemptying_list *this, void *obj)
{
    unsigned int len = 0;
    void *lobj = 0;

    if (UR_ERROR == ubjs_list_add(this->list, obj))
    {
        return UR_ERROR;
    }

    if (UTRUE == this->is_in_callback)
    {
        return UR_OK;
    }

    this->is_in_callback=UTRUE;
    ubjs_list_len(this->list, &len);
    while (0 < len)
    {
        ubjs_list_remove_first_and_get(this->list, &lobj);
        (this->callback)(this, lobj);
        (this->list->free_f)(lobj);
        ubjs_list_len(this->list, &len);
    }
    this->is_in_callback=UFALSE;
    return UR_OK;
}
