/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
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
#include <string.h>
#include "ubjs_primitives_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

ubjs_result ubjs_prmtv_object(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;
    this->super.ntype=0;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;
    this->super.ntype=0;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_OBJECT) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_object *uthis;
    if (0 == this || UOT_OBJECT != this->type || 0 == plen)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->get_length_f)(uthis->glue, plen);
}

ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv **pvalue)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key || 0==pvalue)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->get_f)(uthis->glue, key_length, key, (void **)pvalue);
}

ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv *value)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key || 0==value)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->set_f)(uthis->glue, key_length, key, value);
}

ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this, unsigned int key_length, char *key)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->delete_f)(uthis->glue, key_length, key);
}

ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this, ubjs_object_iterator **piterator)
{
    ubjs_object *uthis;
    ubjs_object_iterator *iterator;

    if (0==this || UOT_OBJECT != this->type|| 0==piterator)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    iterator=(ubjs_object_iterator *)(uthis->super.lib->alloc_f)(
        sizeof(struct ubjs_object_iterator));
    iterator->object=uthis;
    iterator->glue=0;
    (uthis->glue->iterate_f)(uthis->glue, &(iterator->glue));

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this)
{
    if (0==this)
    {
        return UR_ERROR;
    }

    return (this->glue->next_f)(this->glue);
}

ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this, unsigned int *plen)
{
    if (0==this || 0 == plen)
    {
        return UR_ERROR;
    }

    return (this->glue->get_key_length_f)(this->glue, plen);
}

ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *key)
{
    if (0==this || 0 == key)
    {
        return UR_ERROR;
    }

    return (this->glue->copy_key_f)(this->glue, key);
}

ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this, ubjs_prmtv **pvalue)
{
    if (0==this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    return (this->glue->get_value_f)(this->glue, (void **)pvalue);
}

ubjs_result ubjs_object_iterator_delete(ubjs_object_iterator *this)
{
    if (0==this)
    {
        return UR_ERROR;
    }

    return (this->glue->delete_f)(this->glue);
}

ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **pthis)
{
    ubjs_object_iterator *this;

    if (0==pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->glue->free_f)(&(this->glue));
    (this->object->super.lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}
