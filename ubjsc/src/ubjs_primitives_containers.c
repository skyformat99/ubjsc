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

ubjs_result ubjs_prmtv_array(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_with_length_and_type(ubjs_library *lib, ubjs_prmtv_type type,
    unsigned int length, ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;
    unsigned int item_size = 0;

    if (0 == lib || 0 == pthis || type >= UOT_MAX)
    {
        return UR_ERROR;
    }

    switch (type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        item_size = sizeof(struct ubjs_prmtv);
        break;

    case UOT_INT8:
        item_size = sizeof(struct ubjs_int8);
        break;

    case UOT_UINT8:
        item_size = sizeof(struct ubjs_uint8);
        break;

    case UOT_INT16:
        item_size = sizeof(struct ubjs_int16);
        break;

    case UOT_INT32:
        item_size = sizeof(struct ubjs_int32);
        break;

    case UOT_INT64:
        item_size = sizeof(struct ubjs_int64);
        break;

    case UOT_FLOAT32:
        item_size = sizeof(struct ubjs_float32);
        break;

    case UOT_FLOAT64:
        item_size = sizeof(struct ubjs_float64);
        break;

    case UOT_CHAR:
        item_size = sizeof(struct ubjs_char);
        break;

    case UOT_STR:
        item_size = sizeof(struct ubjs_str);
        break;

    case UOT_HPN:
        item_size = sizeof(struct ubjs_hpn);
        break;

    case UOT_ARRAY:
        item_size = sizeof(struct ubjs_array);
        break;

    case UOT_OBJECT:
        item_size = sizeof(struct ubjs_object);
        break;
    /* LCOV_EXCL_START */
    default:
        break;
    /* LCOV_EXCL_STOP */

    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->set_item_size_f)(glue_builder, item_size);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_ARRAY) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == plen)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_length_f)(athis->glue, plen);
}

ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_first_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_last_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_at_f)(athis->glue, pos, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_first_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_last_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_at_f)(athis->glue, pos, item);
}

ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_first_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_last_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this, unsigned int pos)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_at_f)(athis->glue, pos);
}

ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this, ubjs_array_iterator **piterator)
{
    ubjs_array *athis;
    ubjs_array_iterator *iterator;

    if (0 == this || UOT_ARRAY != this->type || 0 == piterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    iterator=(ubjs_array_iterator *)(athis->super.lib->alloc_f)(sizeof(struct ubjs_array_iterator));
    iterator->array=athis;
    iterator->glue=0;
    (athis->glue->iterate_f)(athis->glue, &(iterator->glue));

    *piterator = iterator;
    return UR_OK;
}

ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    return (this->glue->next_f)(this->glue);
}

ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this, ubjs_prmtv **pitem)
{
    if (0 == this || 0 == pitem)
    {
        return UR_ERROR;
    }

    return (this->glue->get_f)(this->glue, (void **)pitem);
}

ubjs_result ubjs_array_iterator_delete(ubjs_array_iterator *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    return (this->glue->delete_f)(this->glue);
}

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis)
{
    ubjs_array_iterator *this;

    if (0 == pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->glue->free_f)(&(this->glue));
    (this->array->super.lib->free_f)(*pthis);
    *pthis=0;
    return UR_OK;
}

void ubjs_prmtv_glue_item_free(void *item)
{
    ubjs_prmtv_free((ubjs_prmtv **)&item);
}

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

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_with_length_and_type(ubjs_library *lib, ubjs_prmtv_type type,
    unsigned int length, ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder;
    unsigned int item_size = 0;

    if (0 == lib || 0 == pthis || type >= UOT_MAX)
    {
        return UR_ERROR;
    }

    switch (type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        item_size = sizeof(struct ubjs_prmtv);
        break;

    case UOT_INT8:
        item_size = sizeof(struct ubjs_int8);
        break;

    case UOT_UINT8:
        item_size = sizeof(struct ubjs_uint8);
        break;

    case UOT_INT16:
        item_size = sizeof(struct ubjs_int16);
        break;

    case UOT_INT32:
        item_size = sizeof(struct ubjs_int32);
        break;

    case UOT_INT64:
        item_size = sizeof(struct ubjs_int64);
        break;

    case UOT_FLOAT32:
        item_size = sizeof(struct ubjs_float32);
        break;

    case UOT_FLOAT64:
        item_size = sizeof(struct ubjs_float64);
        break;

    case UOT_CHAR:
        item_size = sizeof(struct ubjs_char);
        break;

    case UOT_STR:
        item_size = sizeof(struct ubjs_str);
        break;

    case UOT_HPN:
        item_size = sizeof(struct ubjs_hpn);
        break;

    case UOT_ARRAY:
        item_size = sizeof(struct ubjs_array);
        break;

    case UOT_OBJECT:
        item_size = sizeof(struct ubjs_object);
        break;
    /* LCOV_EXCL_START */
    default:
        break;
    /* LCOV_EXCL_STOP */

    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->set_item_size_f)(glue_builder, item_size);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;

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
