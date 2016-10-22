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

#ifndef HAVE_UBJS_RUDEFIFO
#define HAVE_UBJS_RUDEFIFO

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_common.h>
#include "ubjs_list.h"

typedef struct ubjs_rudefifo ubjs_rudefifo;
typedef void (*ubjs_rudefifo_callback)(ubjs_rudefifo *, void *);

struct ubjs_rudefifo
{
    ubjs_list *list;
    ubjs_rudefifo_callback callback;
    ubjs_bool is_in_callback;
};

ubjs_result ubjs_rudefifo_new(ubjs_list_free_f, ubjs_rudefifo_callback, ubjs_rudefifo **);
ubjs_result ubjs_rudefifo_free(ubjs_rudefifo **);
ubjs_result ubjs_rudefifo_add(ubjs_rudefifo *, void *);

#ifdef __cplusplus
}
#endif

#endif
