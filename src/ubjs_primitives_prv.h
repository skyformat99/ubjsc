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
#ifndef HAVE_UBJS_PRIMITIVES_PRV
#define HAVE_UBJS_PRIMITIVES_PRV

#include <ptrie.h>
#include <ubjs_primitives.h>

typedef struct ubjs_int8 ubjs_int8;
typedef struct ubjs_uint8 ubjs_uint8;
typedef struct ubjs_int16 ubjs_int16;
typedef struct ubjs_int32 ubjs_int32;
typedef struct ubjs_int64 ubjs_int64;
typedef struct ubjs_float32 ubjs_float32;
typedef struct ubjs_float64 ubjs_float64;
typedef struct ubjs_char ubjs_char;
typedef struct ubjs_str ubjs_str;
typedef struct ubjs_array ubjs_array;
typedef struct ubjs_object ubjs_object;

struct ubjs_prmtv
{
    ubjs_prmtv_type type;
};

struct ubjs_int8
{
    ubjs_prmtv super;
    int8_t value;
};

struct ubjs_uint8
{
    ubjs_prmtv super;
    uint8_t value;
};

struct ubjs_int16
{
    ubjs_prmtv super;
    int16_t value;
};

struct ubjs_int32
{
    ubjs_prmtv super;
    int32_t value;
};

struct ubjs_int64
{
    ubjs_prmtv super;
    int64_t value;
};

struct ubjs_float32
{
    ubjs_prmtv super;
    float32_t value;
};

struct ubjs_float64
{
    ubjs_prmtv super;
    float64_t value;
};

struct ubjs_char
{
    ubjs_prmtv super;
    char value;
};

struct ubjs_str
{
    ubjs_prmtv super;
    unsigned int length;
    char *text;
};

struct ubjs_array
{
    ubjs_prmtv super;
    unsigned int length;
    unsigned int allocated_length;
    ubjs_prmtv **data;
};

struct ubjs_object
{
    ubjs_prmtv super;
    ptrie *trie;
};

extern ubjs_prmtv __ubjs_prmtv_null;
extern ubjs_prmtv __ubjs_prmtv_noop;
extern ubjs_prmtv __ubjs_prmtv_true;
extern ubjs_prmtv __ubjs_prmtv_false;

#define UBJS_ARRAY_DEFAULT_SIZE 10
#define UBJS_ARRAY_MULTIPLY 3
#define UBJS_ARRAY_ADD 1
ubjs_result ubjs_array_expand_if_needed(ubjs_array *);
ubjs_result ubjs_array_shrink_if_needed(ubjs_array *);

void __ubjs_prmtv_free_trie(void *);

struct ubjs_array_iterator
{
    ubjs_array *array;
    ubjs_prmtv *current;
    unsigned int pos;
};

struct ubjs_object_iterator
{
    ubjs_object *object;
    ptrie_iterator *iterator;
};

ubjs_result ubjs_array_iterator_new(ubjs_array *, ubjs_array_iterator **);
ubjs_result ubjs_object_iterator_new(ubjs_object *, ubjs_object_iterator **);

/* \endinternal */

#endif
