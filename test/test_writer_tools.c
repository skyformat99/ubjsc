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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_writer_tools.h"

/* static void would_write_print(would_write_call *); */

void would_write_call_new(uint8_t *data, unsigned int len, would_write_call **pthis)
{
    would_write_call *this;
    this=(would_write_call *)malloc(sizeof(struct would_write_call));

    this->len=len;
    this->data=(uint8_t *)malloc(sizeof(uint8_t)*len);
    memcpy(this->data, data, sizeof(uint8_t) * len);

    *pthis=this;
}

void would_write_call_free(would_write_call **pthis)
{
    would_write_call *this=*pthis;

    free(this->data);
    free(this);

    *pthis=0;
}

void wrapped_writer_context_new(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this;
    this=(wrapped_writer_context *)malloc(sizeof(struct wrapped_writer_context));
    this->calls_would_write = 0;
    this->calls_free = 0;

    test_list_new(&(this->calls_would_write));
    test_list_new(&(this->calls_free));

    *pthis=this;
}

void wrapped_writer_context_free(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this = *pthis;

    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_free));

    free(this);
    *pthis=0;
}

void wrapped_writer_context_reset(wrapped_writer_context *this)
{
    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_free));

    test_list_new(&(this->calls_would_write));
    test_list_new(&(this->calls_free));
}

void writer_context_would_write(ubjs_writer_context *context, uint8_t *data, unsigned int len)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    would_write_call *call;
    would_write_call_new(data, len, &call);
    test_list_add(ctx->calls_would_write, call, (test_list_free_f)would_write_call_free);

    /*would_write_print(call);*/
}

#define WOULD_WRITE_PRINT_OFFSET 8
/*
static void would_write_print(would_write_call *this)
{
    unsigned int i;

    printf("Would write %d bytes:\n", this->len);
    for (i=0; i<this->len; i++)
    {
        if (0 == (i % 8))
        {
            printf("%d | ", i/8);
        }
        printf("%d\t", this->data[i]);
        if (7 == (i % 8))
        {
            printf("\n");
        }
    }
    printf("\n");
}
*/

void writer_context_free(ubjs_writer_context *context)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    test_list_add(ctx->calls_free, 0, 0);
}
