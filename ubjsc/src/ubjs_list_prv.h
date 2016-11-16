/*
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

#ifndef HAVE_UBJS_LIST
#define HAVE_UBJS_LIST

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_common.h>
#include <ubjs_library.h>

typedef struct ubjs_list ubjs_list;
typedef void (*ubjs_list_free_f)(void *);

struct ubjs_list
{
    ubjs_library *lib;

    ubjs_list *prev;
    ubjs_list *next;

    void *obj;
    ubjs_list_free_f free_f;
};

ubjs_result ubjs_list_new(ubjs_library *lib, ubjs_list_free_f, ubjs_list **);
ubjs_result ubjs_list_free(ubjs_list **);
ubjs_result ubjs_list_add(ubjs_list *, void *);
ubjs_result ubjs_list_remove_first_and_get(ubjs_list *, void **);
ubjs_result ubjs_list_len(ubjs_list *, unsigned int *);

#ifdef __cplusplus
}
#endif

#endif
