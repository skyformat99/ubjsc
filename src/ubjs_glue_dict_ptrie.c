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
#include "ubjs_library_prv.h"

ubjs_result ubjs_glue_dict_ptrie_factory(ubjs_library *lib, ubjs_glue_value_free value_free,
    ubjs_glue_dict **pthis)
{
    ptrie *trie = 0;
    ubjs_glue_dict *this;

    this = (ubjs_glue_dict *)(lib->alloc_f)(sizeof(struct ubjs_glue_dict));
    ptrie_new(value_free, &(trie));
    this->lib=lib;
    this->userdata = (void *)trie;

    this->free_f = ubjs_glue_dict_ptrie_free;
    this->get_length_f = ubjs_glue_dict_ptrie_get_length;
    this->get_f = ubjs_glue_dict_ptrie_get;
    this->set_f = ubjs_glue_dict_ptrie_set;
    this->delete_f = ubjs_glue_dict_ptrie_delete;
    this->iterate_f = ubjs_glue_dict_ptrie_iterate;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_free(ubjs_glue_dict **pthis)
{
    ubjs_glue_dict *this = *pthis;

    ptrie_free((ptrie **) &(this->userdata));
    (this->lib->free_f)(this);

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

    ptrie_iterate(trie, &(trie_iterator));
    iterator=(ubjs_glue_dict_iterator *)(this->lib->alloc_f)(
        sizeof(struct ubjs_glue_dict_iterator));
    iterator->object=this;
    iterator->userdata=(void *)trie_iterator;

    iterator->free_f = ubjs_glue_dict_ptrie_iterator_free;
    iterator->next_f = ubjs_glue_dict_ptrie_iterator_next;
    iterator->get_key_length_f = ubjs_glue_dict_ptrie_iterator_get_key_length;
    iterator->copy_key_f = ubjs_glue_dict_ptrie_iterator_copy_key;
    iterator->get_value_f = ubjs_glue_dict_ptrie_iterator_get_value;

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_glue_dict_ptrie_iterator_free(ubjs_glue_dict_iterator **pthis)
{
    ubjs_glue_dict_iterator *this = *pthis;

    ptrie_iterator_free((ptrie_iterator **) &(this->userdata));
    (this->object->lib->free_f)(this);

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
