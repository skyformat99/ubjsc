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

#ifndef HAVE_UBJS_WRITER
#define HAVE_UBJS_WRITER

#ifdef __cplusplus
extern "C"
{
#endif

#include "ubjs_common.h"
#include "ubjs_primitives.h"

struct ubjs_writer;
struct ubjs_writer_context;

typedef struct ubjs_writer ubjs_writer;
typedef struct ubjs_writer_context ubjs_writer_context;

typedef void (*ubjs_writer_context_would_write)(ubjs_writer_context *, uint8_t *, unsigned int);
typedef void (*ubjs_writer_context_would_print)(ubjs_writer_context *, char *, unsigned int);
typedef void (*ubjs_writer_context_free)(ubjs_writer_context *);

struct ubjs_writer_context
{
    void *userdata;
    ubjs_writer_context_would_write would_write;
    ubjs_writer_context_would_print would_print;
    ubjs_writer_context_free free;
};

UBJS_EXPORT ubjs_result ubjs_writer_new(ubjs_writer **, ubjs_writer_context *);
UBJS_EXPORT ubjs_result ubjs_writer_free(ubjs_writer **);

UBJS_EXPORT ubjs_result ubjs_writer_get_context(ubjs_writer *, ubjs_writer_context **);
UBJS_EXPORT ubjs_result ubjs_writer_write(ubjs_writer *, ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_writer_print(ubjs_writer *, ubjs_prmtv *);

#ifdef __cplusplus
}
#endif

#endif
