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
#include <string.h>

#include "ubjs_common_prv.h"

ubjs_endian_host_type __ubjs_endian_forced=UEFT_DEFAULT;

ubjs_result ubjs_endian_is_big(ubjs_bool *pret)
{
    volatile uint32_t i=0x01234567;

    if (0 == pret)
    {
        return UR_ERROR;
    }

    switch (__ubjs_endian_forced)
    {
    case UEFT_LITTLE:
        (*pret)=UFALSE;
        break;
    case UEFT_BIG:
        (*pret)=UTRUE;
        break;
    default:
        (*pret)=((*((uint8_t*)(&i))) == 0x67) ? UTRUE : UFALSE;
    }
    return UR_OK;
}

static void swap(uint8_t *in, uint8_t *out, unsigned int len)
{
    int i;

    for (i=0; len>i; i++)
    {
        out[len - i - 1] = in[i];
    }
}

static void copy(uint8_t *in, uint8_t *out, unsigned int len)
{
    int i;

    for (i=0; len>i; i++)
    {
        out[i] = in[i];
    }
}

ubjs_result ubjs_endian_convert_big_to_native(uint8_t *in, uint8_t *out, unsigned int len)
{
    ubjs_bool big;

    if (0 == in || 0 == out)
    {
        return UR_ERROR;
    }

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

ubjs_result ubjs_endian_convert_native_to_big(uint8_t *in, uint8_t *out, unsigned int len)
{
    ubjs_bool big;

    if (0 == in || 0 == out)
    {
        return UR_ERROR;
    }

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

ubjs_result ubjs_compact_sprintf(ubjs_library *lib, char **pthis, unsigned int *plen, char *format, ...)
{
    char *now = 0;
    int ret;
    unsigned int length;
    unsigned int offset = 0;
    va_list args;
    char *othis = 0;
    unsigned int olen = 0;

    if (0 != *pthis)
    {
        othis = *pthis;
        olen = *plen;
        offset = olen;
    }

    va_start(args, format);
    ret=vsnprintf(now, 0, format, args);
    va_end(args);

    length=offset + ret;
    now=(char *)(lib->alloc_f)(sizeof(char) * (length + 1));

    if (0 != othis)
    {
        memcpy(now, othis, olen * sizeof(char));
        (lib->free_f)(othis);
    }

    va_start(args, format);
    vsnprintf(now + offset, ret + 1, format, args);
    va_end(args);

    now[length] = 0;

    *plen=length;
    *pthis=now;
    return UR_OK;
}


ubjs_result ubjs_library_new(ubjs_library_alloc_f alloc_f, ubjs_library_free_f free_f,
    ubjs_library **pthis)
{
    ubjs_library *this;

    if (0 == pthis || 0 == alloc_f || 0 == free_f)
    {
        return UR_ERROR;
    }

    this = (alloc_f)(sizeof(struct ubjs_library));
    this->alloc_f=alloc_f;
    this->free_f=free_f;
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis)
{
    return ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, pthis);
}

ubjs_result ubjs_library_free(ubjs_library **pthis)
{
    ubjs_library *this;

    if (0 == pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->free_f)(this);

    *pthis=0;
    return UR_OK;
}
