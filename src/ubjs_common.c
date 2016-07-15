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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/ubjs_common.h"

ubjs_endian_host_type __ubjs_endian_forced=UEFT_DEFAULT;

ubjs_result ubjs_endian_host_type_get(ubjs_endian_host_type *type)
{
    if (0 == type)
    {
        return UR_ERROR;
    }

    (*type)=__ubjs_endian_forced;
    return UR_OK;
}

ubjs_result ubjs_endian_host_type_set(ubjs_endian_host_type type)
{
    switch (type)
    {
    case UEFT_DEFAULT:
    case UEFT_LITTLE:
    case UEFT_BIG:
        __ubjs_endian_forced=type;
        return UR_OK;
    }

    return UR_ERROR;
}

ubjs_result ubjs_endian_is_big(ubjs_bool *ret)
{
    volatile uint32_t i=0x01234567;

    switch (__ubjs_endian_forced)
    {
    case UEFT_LITTLE:
        (*ret)=UFALSE;
        break;
    case UEFT_BIG:
        (*ret)=UTRUE;
        break;
    default:
        (*ret)=((*((uint8_t*)(&i))) == 0x67) ? UTRUE : UFALSE;
    }
    return UR_OK;
}

static void swap(uint8_t *in, uint8_t *out, int len)
{
    int i;

    for (i=0; len>i; i++)
    {
        out[len - i - 1] = in[i];
    }
}

static void copy(uint8_t *in, uint8_t *out, int len)
{
    int i;

    for (i=0; len>i; i++)
    {
        out[i] = in[i];
    }
}

ubjs_result ubjs_endian_convert_big_to_native(uint8_t *in, uint8_t *out, int len)
{
    ubjs_bool big;
    ubjs_endian_is_big(&big);

    if (UTRUE == big)
    {
        copy(in, out, len);
    }
    else
    {
        swap(in, out, len);
    }
    return UR_OK;
}

ubjs_result ubjs_endian_convert_native_to_big(uint8_t *in, uint8_t *out, int len)
{
    ubjs_bool big;
    ubjs_endian_is_big(&big);

    if (UTRUE == big)
    {
        copy(in, out, len);
    }
    else
    {
        swap(in, out, len);
    }
    return UR_OK;
}

ubjs_result ubjs_compact_sprintf(char **pthis, unsigned int *this_len, char *format, ...)
{
    char *now = 0;
    int ret;
    int length;
    va_list args;

    va_start(args, format);
    ret=vsnprintf(now, 0, format, args);
    va_end(args);

    length=ret + 1;
    now=(char *)malloc(sizeof(char)*length);

    va_start(args, format);
    vsnprintf(now, length, format, args);
    va_end(args);

    *this_len=length;
    *pthis=now;
    return UR_OK;
}
