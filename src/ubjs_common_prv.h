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
/* \internal */
#ifndef HAVE_UBJS_COMMON_PRV
#define HAVE_UBJS_COMMON_PRV

#include <ubjs_common.h>

ubjs_result ubjs_endian_is_big(ubjs_bool *pret);
ubjs_result ubjs_endian_host_type_get(ubjs_endian_host_type *ptype);
ubjs_result ubjs_endian_host_type_set(ubjs_endian_host_type type);
ubjs_result ubjs_endian_convert_big_to_native(uint8_t *in, uint8_t *out,
    unsigned int len);
ubjs_result ubjs_endian_convert_native_to_big(uint8_t *in, uint8_t *out,
    unsigned int len);
ubjs_result ubjs_compact_sprintf(ubjs_library *lib, char **pthis, unsigned int *plen,
    char *format, ...);

struct ubjs_library
{
    ubjs_library_alloc_f alloc_f;
    ubjs_library_free_f free_f;
};

#endif
