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
#ifndef HAVE_UBJS_GLUE_DICT_PTRIE_PRV
#define HAVE_UBJS_GLUE_DICT_PTRIE_PRV

#include <ptrie.h>
#include <ubjs_glue_dict_ptrie.h>

typedef struct ubjs_glue_dict_ptrie_builder ubjs_glue_dict_ptrie_builder;
struct ubjs_glue_dict_ptrie_builder
{
    ubjs_glue_value_free value_free;
};

UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_builder_free(ubjs_glue_dict_builder **);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_builder_set_value_free(ubjs_glue_dict_builder *,
    ubjs_glue_value_free);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_builder_set_length(ubjs_glue_dict_builder *,
    unsigned int);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_builder_build(ubjs_glue_dict_builder *,
    ubjs_glue_dict **);

UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_free(ubjs_glue_dict **);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_get_length(ubjs_glue_dict *, unsigned int *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_get(ubjs_glue_dict *, unsigned int,
    char *, void **);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_set(ubjs_glue_dict *, unsigned int,
    char *, void *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_delete(ubjs_glue_dict *, unsigned int,
    char *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterate(ubjs_glue_dict *,
    ubjs_glue_dict_iterator **);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_next(ubjs_glue_dict_iterator *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_get_key_length(ubjs_glue_dict_iterator *,
    unsigned int *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_copy_key(ubjs_glue_dict_iterator *,
    char *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_get_value(ubjs_glue_dict_iterator *,
    void **);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_delete(ubjs_glue_dict_iterator *);
UBJS_NO_EXPORT ubjs_result ubjs_glue_dict_ptrie_iterator_free(ubjs_glue_dict_iterator **);

#endif
