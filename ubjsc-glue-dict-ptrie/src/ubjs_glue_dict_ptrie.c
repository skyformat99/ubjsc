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

#include "ubjs_glue_dict_ptrie_prv.h"

ubjs_result ubjs_glue_dict_ptrie_builder_new(ubjs_library *lib, ubjs_glue_dict_builder **pthis)
{
    ubjs_glue_dict_builder *this = 0;
    ubjs_glue_dict_ptrie_builder *data = 0;
    ubjs_library_alloc_f alloc_f;

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_glue_dict_builder *)(alloc_f)(sizeof(struct ubjs_glue_dict_builder));
    data = (ubjs_glue_dict_ptrie_builder *)(alloc_f)(sizeof(
        struct ubjs_glue_dict_ptrie_builder));
    this->lib = lib;
    this->userdata = data;
    data->value_free = 0;

    this->set_value_free_f = ubjs_glue_dict_ptrie_builder_set_value_free;
    this->set_length_f = ubjs_glue_dict_ptrie_builder_set_length;
    this->free_f = ubjs_glue_dict_ptrie_builder_free;
    this->build_f = ubjs_glue_dict_ptrie_builder_build;

    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_builder_free(ubjs_glue_dict_builder **pthis)
{
    ubjs_glue_dict_builder *this = *pthis;
    ubjs_glue_dict_ptrie_builder *data = (ubjs_glue_dict_ptrie_builder *)this->userdata;
    ubjs_library_free_f free_f;

    ubjs_library_get_free_f(this->lib, &free_f);
    (free_f)(data);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_builder_set_value_free(ubjs_glue_dict_builder *this,
    ubjs_glue_value_free value_free)
{
    ubjs_glue_dict_ptrie_builder *data = (ubjs_glue_dict_ptrie_builder *)this->userdata;
    data->value_free = value_free;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_builder_set_length(ubjs_glue_dict_builder *this,
    unsigned int length)
{
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_builder_build(ubjs_glue_dict_builder *this,
    ubjs_glue_dict **pdict)
{
    ubjs_glue_dict_ptrie_builder *data = (ubjs_glue_dict_ptrie_builder *)this->userdata;
    ubjs_glue_dict *dict = 0;
    ptrie *trie = 0;
    ubjs_library_alloc_f alloc_f;

    ubjs_library_get_alloc_f(this->lib, &alloc_f);
    dict = (ubjs_glue_dict *)(alloc_f)(sizeof(struct ubjs_glue_dict));
    ptrie_new(data->value_free, &(trie));
    dict->lib = this->lib;
    dict->userdata = (void *)trie;

    dict->free_f = ubjs_glue_dict_ptrie_free;
    dict->get_length_f = ubjs_glue_dict_ptrie_get_length;
    dict->get_f = ubjs_glue_dict_ptrie_get;
    dict->set_f = ubjs_glue_dict_ptrie_set;
    dict->delete_f = ubjs_glue_dict_ptrie_delete;
    dict->iterate_f = ubjs_glue_dict_ptrie_iterate;

    *pdict=dict;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_free(ubjs_glue_dict **pthis)
{
    ubjs_glue_dict *this = *pthis;
    ubjs_library_free_f free_f;

    ubjs_library_get_free_f(this->lib, &free_f);
    ptrie_free((ptrie **) &(this->userdata));
    (free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_get_length(ubjs_glue_dict *this, unsigned int *plen)
{
    return PR_OK == ptrie_get_length((ptrie *)this->userdata, plen) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_get(ubjs_glue_dict *this, unsigned int klen,
    char *key, void **pvalue)
{
    return PR_OK == ptrie_get((ptrie *)this->userdata, klen, key, pvalue) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_set(ubjs_glue_dict *this, unsigned int klen,
    char *key, void *value)
{
    return PR_OK == ptrie_set((ptrie *)this->userdata, klen, key, value) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_delete(ubjs_glue_dict *this, unsigned int klen,
    char *key)
{
    return PR_OK == ptrie_delete((ptrie *)this->userdata, klen, key) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_iterate(ubjs_glue_dict *this,
    ubjs_glue_dict_iterator **piterator)
{
    ptrie *trie = (ptrie *)this->userdata;
    ptrie_iterator *trie_iterator = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    ubjs_library_alloc_f alloc_f;

    ubjs_library_get_alloc_f(this->lib, &alloc_f);
    ptrie_iterate(trie, &(trie_iterator));
    iterator=(ubjs_glue_dict_iterator *)(alloc_f)(
        sizeof(struct ubjs_glue_dict_iterator));
    iterator->object=this;
    iterator->userdata=(void *)trie_iterator;

    iterator->free_f = ubjs_glue_dict_ptrie_iterator_free;
    iterator->next_f = ubjs_glue_dict_ptrie_iterator_next;
    iterator->get_key_length_f = ubjs_glue_dict_ptrie_iterator_get_key_length;
    iterator->copy_key_f = ubjs_glue_dict_ptrie_iterator_copy_key;
    iterator->get_value_f = ubjs_glue_dict_ptrie_iterator_get_value;
    iterator->delete_f = ubjs_glue_dict_ptrie_iterator_delete;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_free(ubjs_glue_dict_iterator **pthis)
{
    ubjs_glue_dict_iterator *this = *pthis;
    ubjs_library_free_f free_f;

    ubjs_library_get_free_f(this->object->lib, &free_f);
    ptrie_iterator_free((ptrie_iterator **) &(this->userdata));
    (free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_next(ubjs_glue_dict_iterator *this)
{
    return PR_OK == ptrie_iterator_next((ptrie_iterator *)this->userdata) ? UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_get_key_length(ubjs_glue_dict_iterator *this,
    unsigned int *klen)
{
    return PR_OK == ptrie_iterator_get_key_length((ptrie_iterator *)this->userdata, klen) ?
        UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_copy_key(ubjs_glue_dict_iterator *this, char *key)
{
    return PR_OK == ptrie_iterator_copy_key((ptrie_iterator *)this->userdata, key) ?
        UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_get_value(ubjs_glue_dict_iterator *this,
    void **pvalue)
{
    return PR_OK == ptrie_iterator_get_value((ptrie_iterator *)this->userdata, pvalue) ?
        UR_OK : UR_ERROR;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_delete(ubjs_glue_dict_iterator *this)
{
    return PR_OK == ptrie_iterator_delete((ptrie_iterator *)this->userdata) ?
        UR_OK : UR_ERROR;
}
