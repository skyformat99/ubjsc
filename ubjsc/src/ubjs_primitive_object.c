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
#include <stdlib.h>

#include "ubjs_primitives_prv.h"
#include "ubjs_primitive_object_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"
#include "ubjs_glue_array_array.h"
#include "ubjs_primitive_str.h"

ubjs_prmtv_ntype ubjs_prmtv_object_ntype =
{
    123,

    ubjs_prmtv_object_free,

    0,
    0,

#ifndef NDEBUG
    ubjs_prmtv_object_debug_string_get_length,
    ubjs_prmtv_object_debug_string_copy,
#else
    0,
    0,
#endif

    ubjs_prmtv_object_parser_processor_new,
    ubjs_prmtv_object_parser_processor_free,

    ubjs_prmtv_object_parser_processor_got_present,
    ubjs_prmtv_object_parser_processor_got_marker,
    ubjs_prmtv_object_parser_processor_got_control,

    ubjs_prmtv_object_parser_processor_read_byte,

    ubjs_prmtv_object_writer_new,
    ubjs_prmtv_object_writer_free,
    ubjs_prmtv_object_writer_get_length,
    ubjs_prmtv_object_writer_do,

    ubjs_prmtv_object_printer_new,
    ubjs_prmtv_object_printer_free,
    ubjs_prmtv_object_printer_get_length,
    ubjs_prmtv_object_printer_do
};

ubjs_prmtv_ntype ubjs_prmtv_object_end_ntype =
{
    125,

    0,

    0,
    0,

    0,
    0,

    0,
    0,

    0,
    0,
    0,

    0,

    0,
    0,
    0,
    0,

    0,
    0,
    0,
    0
};

ubjs_prmtv_ntype ubjs_prmtv_object_type_ntype =
{
    36,

    0,

    0,
    0,

    0,
    0,

    0,
    0,

    0,
    0,
    0,

    0,

    0,
    0,
    0,
    0,

    0,
    0,
    0,
    0
};

ubjs_prmtv_ntype ubjs_prmtv_object_count_ntype =
{
    35,

    0,

    0,
    0,

    0,
    0,

    0,
    0,

    0,
    0,
    0,

    0,

    0,
    0,
    0,
    0,

    0,
    0,
    0,
    0
};

ubjs_result ubjs_prmtv_object(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_prmtv_object_t *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_glue_dict_builder_new_f glue_dict_builder_new_f = 0;
    ubjs_glue_dict_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_object_t *)(alloc_f)(sizeof(struct ubjs_prmtv_object_t));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_object_ntype;

    ubjs_library_get_glue_dict_builder(lib, &glue_dict_builder_new_f);
    (glue_dict_builder_new_f)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    *pthis = (ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_prmtv_object_t *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_glue_dict_builder_new_f glue_dict_builder_new_f = 0;
    ubjs_glue_dict_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }


    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_object_t *)(alloc_f)(sizeof(struct ubjs_prmtv_object_t));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_object_ntype;

    ubjs_library_get_glue_dict_builder(lib, &glue_dict_builder_new_f);
    (glue_dict_builder_new_f)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_object_t *athis;

    if (0 == this || &ubjs_prmtv_object_ntype != this->ntype || 0 == plen)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_object_t *)this;
    return (athis->glue->get_length_f)(athis->glue, plen);
}

ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv **pvalue)
{
    ubjs_prmtv_object_t*uthis;

    if (0 == this || &ubjs_prmtv_object_ntype != this->ntype || 0==key || 0==pvalue)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_prmtv_object_t*)this;
    return (uthis->glue->get_f)(uthis->glue, key_length, key, (void **)pvalue);
}

ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv *value)
{
    ubjs_prmtv_object_t*uthis;

    if (0 == this || &ubjs_prmtv_object_ntype != this->ntype || 0==key || 0==value)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_prmtv_object_t*)this;
    return (uthis->glue->set_f)(uthis->glue, key_length, key, value);
}

ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this, unsigned int key_length, char *key)
{
    ubjs_prmtv_object_t*uthis;

    if (0 == this || &ubjs_prmtv_object_ntype != this->ntype || 0==key)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_prmtv_object_t*)this;
    return (uthis->glue->delete_f)(uthis->glue, key_length, key);
}


ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this, ubjs_object_iterator **piterator)
{
    ubjs_prmtv_object_t *athis;
    ubjs_object_iterator *iterator;
    ubjs_library_alloc_f alloc_f;

    if (0 == this || &ubjs_prmtv_object_ntype != this->ntype || 0 == piterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_object_t *)this;
    ubjs_library_get_alloc_f(athis->super.lib, &alloc_f);
    iterator=(ubjs_object_iterator *)(alloc_f)(sizeof(
        struct ubjs_object_iterator));
    iterator->object=athis;
    iterator->glue=0;
    (athis->glue->iterate_f)(athis->glue, &(iterator->glue));

    *piterator = iterator;
    return UR_OK;
}

ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    return (this->glue->next_f)(this->glue);
}


ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this, unsigned int *plen)
{
    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    return (this->glue->get_key_length_f)(this->glue, plen);
}

ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *key)
{
    if (0 == this || 0 == key)
    {
        return UR_ERROR;
    }

    return (this->glue->copy_key_f)(this->glue, key);
}

ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this, ubjs_prmtv **pvalue)
{
    if (0 == this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    return (this->glue->get_value_f)(this->glue, (void **)pvalue);
}

ubjs_result ubjs_object_iterator_delete(ubjs_object_iterator *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    return (this->glue->delete_f)(this->glue);
}

ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **pthis)
{
    ubjs_object_iterator *this;
    ubjs_library_free_f free_f;

    if (0 == pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    ubjs_library_get_free_f(this->object->super.lib, &free_f);
    (this->glue->free_f)(&(this->glue));
    (free_f)(*pthis);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv_object_t *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_object_t *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (this->glue->free_f)(&(this->glue));
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

#ifndef NDEBUG

ubjs_result ubjs_prmtv_object_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
/*    ubjs_prmtv_object_t *thisv;*/
    char tmp[30];
    unsigned int len = 0;
/*    ubjs_glue_dict_iterator *it = 0;*/

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

/*    thisv = (ubjs_prmtv_object_t *)this;*/
/*    (thisv->glue->get_length_f)(thisv->glue, &len);*/

    /* "str(%u, " + %s + ")"*/
    *plen = sprintf(tmp, "object(%u)", len);

/*
    (thisv->glue->iterate_f)(thisv->glue, &it);
    while (UR_OK == (it->next_f)(it))
    {
        unsigned int itlen = 0;
        ubjs_prmtv *child = 0;

        (it->get_f)(it, (void **)&child);
        ubjs_prmtv_debug_string_get_length(child, &itlen);
        *plen += 2 + itlen;
    }
    (it->free_f)(&it);
*/
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_debug_string_copy(ubjs_prmtv *this, char *str)
{
/*    ubjs_prmtv_object_t *thisv;*/
    unsigned int len = 0;
    unsigned int at = 0;
/*    ubjs_glue_dict_iterator *it = 0;*/

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

/*    thisv = (ubjs_prmtv_object_t *)this;*/
/*    (thisv->glue->get_length_f)(thisv->glue, &len);*/

    at = sprintf(str + at, "object(%u", len);
/*
    (thisv->glue->iterate_f)(thisv->glue, &it);
    while (UR_OK == (it->next_f)(it))
    {
        unsigned int itlen = 0;
        ubjs_prmtv *child = 0;

        (it->get_f)(it, (void **)&child);
        at += sprintf(str + at, ", ");

        ubjs_prmtv_debug_string_get_length(child, &itlen);
        ubjs_prmtv_debug_string_copy(child, str + at);

        at += itlen;
    }
    (it->free_f)(&it);
*/
    at += sprintf(str + at, ")");

    return UR_OK;
}
#endif

ubjs_result ubjs_prmtv_object_parser_processor_new(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_object_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_object_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_object_parser_processor));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_object_ntype;
    this->super.name = "object";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->data = 0;
    this->phase = UPOPPP_INIT;
    this->len = 0;
    this->expected_len = 0;
    this->type_marker = 0;
    this->count_marker = 0;

    this->key_length = 0;
    this->key_at = 0;
    this->key_value = 0;

    this->legal_markers_type_count_int64s_end = 0;
    this->legal_markers_count = 0;
    this->legal_markers_int64s = 0;
    this->legal_markers_int64s_end = 0;
    this->legal_markers_top = 0;

    {
        ubjs_glue_array_builder *glue_builder = 0;

        ubjs_glue_array_array_builder_new(lib, &glue_builder);
        (glue_builder->set_value_free_f)(glue_builder, 0);
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_type_count_int64s_end));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_count));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_int64s));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_int64s_end));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_top));
        (glue_builder->free_f)(&glue_builder);
    }
    {
        ubjs_glue_array_iterator *it = 0;
        ubjs_glue_array *ntypes = 0;
        ubjs_prmtv_ntype *n = 0;

        ubjs_library_get_ntypes(lib, &ntypes);
        (ntypes->iterate_f)(ntypes, &it);

        while (UR_OK == (it->next_f)(it))
        {
            (it->get_f)(it, (void **)&n);

            (this->legal_markers_top->add_last_f)(
                this->legal_markers_top, n);
            if (0 != n->new_from_int64_f)
            {
                (this->legal_markers_type_count_int64s_end->add_last_f)(
                    this->legal_markers_type_count_int64s_end, n);
                (this->legal_markers_int64s->add_last_f)(this->legal_markers_int64s, n);
                (this->legal_markers_int64s_end->add_last_f)(this->legal_markers_int64s_end, n);
            }
        }
        (it->free_f)(&it);

        (this->legal_markers_type_count_int64s_end->add_last_f)(
            this->legal_markers_type_count_int64s_end, &ubjs_prmtv_object_type_ntype);

        (this->legal_markers_type_count_int64s_end->add_last_f)(
            this->legal_markers_type_count_int64s_end, &ubjs_prmtv_object_count_ntype);
        (this->legal_markers_count->add_last_f)(
            this->legal_markers_count, &ubjs_prmtv_object_count_ntype);

        (this->legal_markers_type_count_int64s_end->add_last_f)(
            this->legal_markers_type_count_int64s_end, &ubjs_prmtv_object_end_ntype);
        (this->legal_markers_int64s_end->add_last_f)(
            this->legal_markers_int64s_end, &ubjs_prmtv_object_end_ntype);

    }
    *pthis = (ubjs_prmtv_ntype_parser_processor *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_object_parser_processor *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_object_parser_processor *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    if (0 != this->data)
    {
        ubjs_prmtv_free(&(this->data));
    }
    if (0 != this->key_value)
    {
        (free_f)(this->key_value);
    }

    (this->legal_markers_type_count_int64s_end->free_f)(&
        (this->legal_markers_type_count_int64s_end));
    (this->legal_markers_count->free_f)(&(this->legal_markers_count));
    (this->legal_markers_int64s->free_f)(&(this->legal_markers_int64s));
    (this->legal_markers_int64s_end->free_f)(&(this->legal_markers_int64s_end));
    (this->legal_markers_top->free_f)(&(this->legal_markers_top));

    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

static void ubjs_prmtv_object_parser_processor_got_present_want_count_prmtv_value(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    int64_t len = 0;

    ubjs_prmtv_int_get(present, &len);
    ubjs_prmtv_free(&present);
    if (0 > len)
    {
        this2->phase = UPOPPP_DONE;
        (this->glue->error_f)(this->glue, 14,
            "Invalid length");
        return;
    }

    (this->glue->debug_f)(this->glue, 9, "Got count");
    this2->expected_len = len;
    ubjs_prmtv_free(&present);

    if (this->glue->limit_container_length > 0 &&
        this->glue->limit_container_length < len)
    {
        this2->phase = UPOPPP_DONE;
        (this->glue->error_f)(this->glue, 33,
            "Reached limit of container length");
    }
    else if (this->glue->limit_recursion_level > 0 &&
        this->glue->limit_recursion_level == this->glue->recursion_level)
    {
        this2->phase = UPOPPP_DONE;
        (this->glue->error_f)(this->glue, 29,
            "Reached recursion level limit");
    }
    else
    {
        ubjs_prmtv_object_with_length(this->lib, len, &(this2->data));
        if (0 == len)
        {
            ubjs_prmtv *data = this2->data;

            (this->glue->debug_f)(this->glue, 11, "Empty - end");
            this2->data = 0;
            this2->phase = UPOPPP_DONE;
            (this->glue->return_control_f)(this->glue, data);
        }
        else
        {
            (this->glue->debug_f)(this->glue, 14, "Want child key");
            this2->phase = UPOPPP_WANT_KEY_LENGTH_PRMTV_MARKER;
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
        }
    }
}

static void ubjs_prmtv_object_parser_processor_want_child_value(
    ubjs_prmtv_ntype_parser_processor *this)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    if (0 != this2->type_marker)
    {
        (this->glue->debug_f)(this->glue, 31, "Want child value - we are typed");
        this2->phase = UPOPPP_WANT_CHILD_PRMTV_VALUE;
        (this->glue->want_child_f)(this->glue, this2->type_marker);
    }
    else
    {
        (this->glue->debug_f)(this->glue, 34, "Want child marker - we are untyped");
        this2->phase = UPOPPP_WANT_CHILD_PRMTV_MARKER;
        (this->glue->want_marker_f)(this->glue, this2->legal_markers_top);
    }
}

static void ubjs_prmtv_object_parser_processor_got_child_value(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    ubjs_library_free_f free_f;

    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    (this->glue->debug_f)(this->glue, 9, "Got child");
    ubjs_prmtv_object_set(this2->data, this2->key_length, this2->key_value, present);

    ubjs_library_get_free_f(this->lib, &free_f);
    (free_f)(this2->key_value);
    this2->key_value = 0;
    this2->len += 1;

    if (0 != this2->count_marker && this2->len == this2->expected_len)
    {
        ubjs_prmtv *data = this2->data;

        (this->glue->debug_f)(this->glue, 3, "End");
        this2->data = 0;
        this2->phase = UPOPPP_DONE;
        (this->glue->return_control_f)(this->glue, data);
    }
    else if (0 == this2->count_marker)
    {
        (this->glue->debug_f)(this->glue, 21, "Want child key or end");
        this2->phase = UPOPPP_WANT_KEY_LENGTH_PRMTV_MARKER_END;
        (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s_end);
    }
    else
    {
        (this->glue->debug_f)(this->glue, 14, "Want child key");
        this2->phase = UPOPPP_WANT_KEY_LENGTH_PRMTV_MARKER;
        (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
    }
}

void ubjs_prmtv_object_parser_processor_got_present(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    ubjs_library_alloc_f alloc_f;
    int64_t len = -1;

    switch (this2->phase)
    {
        case UPOPPP_WANT_COUNT_PRMTV_VALUE:
            ubjs_prmtv_object_parser_processor_got_present_want_count_prmtv_value(this, present);
            break;

        case UPOPPP_WANT_KEY_LENGTH_PRMTV_VALUE:
            ubjs_prmtv_int_get(present, &len);
            ubjs_prmtv_free(&present);
            if (0 > len)
            {
                this2->phase = UPOPPP_DONE;
                (this->glue->error_f)(this->glue, 18,
                    "Invalid key length");
                break;
            }

            ubjs_library_get_alloc_f(this->lib, &alloc_f);
            this2->key_length = len;
            this2->key_at = 0;
            this2->key_value = (char *)(alloc_f)(sizeof(char) * len);
            if (0 == len)
            {
                (this->glue->debug_f)(this->glue, 20, "Got empty key length");
                ubjs_prmtv_object_parser_processor_want_child_value(this);
            }
            else
            {
                (this->glue->debug_f)(this->glue, 14, "Got key length - want key value");
                this2->phase = UPOPPP_GATHERING_KEY_VALUE;
            }
            break;

        case UPOPPP_WANT_CHILD_PRMTV_VALUE:
            ubjs_prmtv_object_parser_processor_got_child_value(this, present);
            break;

        default:
            this2->phase = UPOPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got present");
            break;
    }
}

static void ubjs_prmtv_object_parser_processor_got_marker_want_type_count_key_end_marker(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv_ntype *marker)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    if (&ubjs_prmtv_object_type_ntype == marker)
    {
        (this->glue->debug_f)(this->glue, 16, "Want type marker");
        this2->phase = UPOPPP_WANT_TYPE_MARKER;
        (this->glue->want_marker_f)(this->glue, this2->legal_markers_top);
    }
    else if (&ubjs_prmtv_object_end_ntype == marker)
    {
        ubjs_prmtv *data = 0;
        (this->glue->debug_f)(this->glue, 3, "End");
        ubjs_prmtv_object(this->lib, &(data));
        this2->phase = UPOPPP_DONE;
        (this->glue->return_control_f)(this->glue, data);
    }
    else if (&ubjs_prmtv_object_count_ntype == marker)
    {
        (this->glue->debug_f)(this->glue, 20, "Want count marker");
        this2->phase = UPOPPP_WANT_COUNT_PRMTV_MARKER;
        (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
    }
    else if (this->glue->limit_recursion_level > 0 &&
        this->glue->limit_recursion_level == this->glue->recursion_level)
    {
        this2->phase = UPOPPP_DONE;
        (this->glue->error_f)(this->glue, 29,
            "Reached recursion level limit");
    }
    else
    {
        (this->glue->debug_f)(this->glue, 35, "Have key length marker - want value");
        this2->phase = UPOPPP_WANT_KEY_LENGTH_PRMTV_VALUE;
        ubjs_prmtv_object(this->lib, &(this2->data));
        (this->glue->want_child_f)(this->glue, marker);
    }
}

static void ubjs_prmtv_object_parser_processor_got_marker_want_key_length_marker(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv_ntype *marker)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    if (this->glue->limit_container_length > 0 &&
        this->glue->limit_container_length == this2->len)
    {
        this2->phase = UPOPPP_DONE;
        (this->glue->error_f)(this->glue, 33,
            "Reached limit of container length");
    }
    else
    {
        (this->glue->debug_f)(this->glue, 21, "Want key length value");
        this2->phase = UPOPPP_WANT_KEY_LENGTH_PRMTV_VALUE;
        (this->glue->want_child_f)(this->glue, marker);
    }

}
void ubjs_prmtv_object_parser_processor_got_marker(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv_ntype *marker)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    (this->glue->debug_f)(this->glue, 10, "Got marker");

    switch (this2->phase)
    {
        case UPOPPP_WANT_TYPE_COUNT_KEY_END_MARKER:
            ubjs_prmtv_object_parser_processor_got_marker_want_type_count_key_end_marker(
                this, marker);
            break;

        case UPOPPP_WANT_TYPE_MARKER:
            this2->phase = UPOPPP_WANT_COUNT_MARKER;
            this2->type_marker = marker;
            (this->glue->debug_f)(this->glue, 20, "We are typed");
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_count);
            break;

        case UPOPPP_WANT_COUNT_MARKER:
            (this->glue->debug_f)(this->glue, 20, "Want count marker");
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
            this2->phase = UPOPPP_WANT_COUNT_PRMTV_MARKER;
            break;

        case UPOPPP_WANT_COUNT_PRMTV_MARKER:
            (this->glue->debug_f)(this->glue, 20, "Want count primitive");
            this2->count_marker = marker;
            this2->phase = UPOPPP_WANT_COUNT_PRMTV_VALUE;
            (this->glue->want_child_f)(this->glue, this2->count_marker);
            break;

        case UPOPPP_WANT_KEY_LENGTH_PRMTV_MARKER_END:
            if (&ubjs_prmtv_object_end_ntype == marker)
            {
                ubjs_prmtv *data = this2->data;
                (this->glue->debug_f)(this->glue, 3, "End");
                this2->data = 0;
                this2->phase = UPOPPP_DONE;
                (this->glue->return_control_f)(this->glue, data);
            }
            else
            {
                ubjs_prmtv_object_parser_processor_got_marker_want_key_length_marker(this, marker);
            }
            break;

        case UPOPPP_WANT_KEY_LENGTH_PRMTV_MARKER:
            ubjs_prmtv_object_parser_processor_got_marker_want_key_length_marker(this, marker);
            break;

        case UPOPPP_WANT_CHILD_PRMTV_MARKER:
            (this->glue->debug_f)(this->glue, 26, "Want child value");
            this2->phase = UPOPPP_WANT_CHILD_PRMTV_VALUE;
            (this->glue->want_child_f)(this->glue, marker);
            break;

        default:
            this2->phase = UPOPPP_DONE;
            (this->glue->error_f)(this->glue, 21,
                "Unexpected got marker");
    }
}

void ubjs_prmtv_object_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    switch (this2->phase)
    {
        case UPOPPP_INIT:
            this2->phase = UPOPPP_WANT_TYPE_COUNT_KEY_END_MARKER;
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_type_count_int64s_end);
            break;

        default:
            this2->phase = UPOPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got control");
            break;
    }
}

void ubjs_prmtv_object_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t achr)
{
    ubjs_prmtv_object_parser_processor *this2 = (ubjs_prmtv_object_parser_processor *)this;
    switch (this2->phase)
    {
        case UPOPPP_GATHERING_KEY_VALUE:
            this2->key_value[this2->key_at++] = achr;
            if (this2->key_at == this2->key_length)
            {
                (this->glue->debug_f)(this->glue, 12, "Got full key");
                ubjs_prmtv_object_parser_processor_want_child_value(this);
            }
            break;

        default:
            this2->phase = UPOPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got control");
            break;
    }
}

static void ubjs_prmtv_object_writer_calculate_lenghts(ubjs_prmtv_object_writer *this)
{
    ubjs_glue_dict_iterator *it = 0;
    ubjs_prmtv_object_t *prmtv = (ubjs_prmtv_object_t *)this->super.glue->prmtv;
    unsigned int len = 0;
    ubjs_library_alloc_f alloc_f = 0;
    ubjs_library_free_f free_f = 0;
    unsigned int i = 0;

    ubjs_library_get_alloc_f(this->super.lib, &alloc_f);
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (prmtv->glue->get_length_f)(prmtv->glue, &len);
    this->len = len;

    this->key_writers = (ubjs_prmtv_ntype_writer **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_writer *) * len);
    this->key_lengths = (unsigned int *)(alloc_f)(
        sizeof(unsigned int) * len);
    this->key_writers_glues = (ubjs_prmtv_ntype_writer_glue **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_writer_glue *) * len);
    this->value_writers = (ubjs_prmtv_ntype_writer **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_writer *) * len);
    this->value_lengths = (unsigned int *)(alloc_f)(
        sizeof(unsigned int) * len);
    this->value_writers_glues = (ubjs_prmtv_ntype_writer_glue **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_writer_glue *) * len);

    if (0 == len)
    {
        return;
    }

    (prmtv->glue->iterate_f)(prmtv->glue, &it);
    while (UR_OK == (it->next_f)(it))
    {
        ubjs_prmtv *value = 0;
        ubjs_prmtv_ntype *cntype = 0;
        unsigned int key_length = 0;
        char *key = 0;

        ubjs_prmtv_ntype_writer *key_writer = 0;
        ubjs_prmtv_ntype_writer_glue *key_glue = 0;
        ubjs_prmtv_ntype_writer *value_writer = 0;
        ubjs_prmtv_ntype_writer_glue *value_glue = 0;

        key_glue = (ubjs_prmtv_ntype_writer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_writer_glue));
        key_glue->debug_f = 0;
        key_glue->userdata = 0;
        (it->get_key_length_f)(it, &key_length);
        key = (char *)(alloc_f)(sizeof(char) * key_length);
        (it->copy_key_f)(it, key);
        (it->get_value_f)(it, (void *)&value);
        ubjs_prmtv_str(this->super.lib, key_length, key, &(key_glue->prmtv));
        (free_f)(key);
        (ubjs_prmtv_str_ntype.writer_new_f)(this->super.lib, key_glue, &(key_writer));
        this->key_writers[i] = key_writer;
        this->key_writers_glues[i] = key_glue;
        (ubjs_prmtv_str_ntype.writer_get_length_f)(key_writer, this->key_lengths + i);

        value_glue = (ubjs_prmtv_ntype_writer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_writer_glue));
        value_glue->debug_f = 0;
        value_glue->userdata = 0;
        value_glue->prmtv = value;
        ubjs_prmtv_get_ntype(value, &cntype);
        (cntype->writer_new_f)(this->super.lib, value_glue, &(value_writer));
        this->value_writers[i] = value_writer;
        this->value_writers_glues[i] = value_glue;
        (cntype->writer_get_length_f)(value_writer, this->value_lengths + i);

        if (len >= 3 && i == 0)
        {
            this->type_marker = cntype;
        }
        else if (cntype != this->type_marker)
        {
            this->type_marker = 0;
        }
        i++;
    }

    (it->free_f)(&it);

    if (len >= 3)
    {
        ubjs_prmtv *count = 0;
        ubjs_prmtv_ntype *cntype = 0;
        ubjs_prmtv_ntype_writer_glue *count_glue = 0;
        ubjs_prmtv_ntype_writer *count_writer = 0;

        count_glue = (ubjs_prmtv_ntype_writer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_writer_glue));
        count_glue->debug_f = 0;
        count_glue->userdata = 0;

        ubjs_prmtv_int(this->super.lib, i, &count);
        count_glue->prmtv = count;

        ubjs_prmtv_get_ntype(count, &cntype);
        (cntype->writer_new_f)(this->super.lib, count_glue, &(count_writer));

        this->count_writer = count_writer;
        this->count_writer_glue = count_glue;
        (cntype->writer_get_length_f)(count_writer, &(this->count_length));
    }
}

ubjs_result ubjs_prmtv_object_writer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_object_writer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_object_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_object_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_object_writer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_object_ntype;
    this->super.name = "object";
    this->super.glue = glue;
    this->super.userdata = 0;

    this->type_marker = 0;
    this->count_writer_glue = 0;
    this->count_writer = 0;

    ubjs_prmtv_object_writer_calculate_lenghts(this);

    *pthis = (ubjs_prmtv_ntype_writer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_writer_free(ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_object_writer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *antype = 0;
    unsigned int i = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_object_writer *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);

    if (0 != this->count_writer)
    {
        ubjs_prmtv_get_ntype(this->count_writer->glue->prmtv, &antype);
        ubjs_prmtv_free(&(this->count_writer->glue->prmtv));
        (free_f)(this->count_writer->glue);
        (antype->writer_free_f)(&this->count_writer);
    }

    for (i = 0; i < this->len; i++)
    {
        ubjs_prmtv_free(&(this->key_writers_glues[i]->prmtv));
        (free_f)(this->key_writers_glues[i]);
        (this->key_writers[i]->ntype->writer_free_f)(&(this->key_writers[i]));
        (free_f)(this->value_writers_glues[i]);
        (this->value_writers[i]->ntype->writer_free_f)(&(this->value_writers[i]));
    }
    (free_f)(this->key_writers);
    (free_f)(this->key_lengths);
    (free_f)(this->key_writers_glues);
    (free_f)(this->value_writers);
    (free_f)(this->value_lengths);
    (free_f)(this->value_writers_glues);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_object_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    ubjs_prmtv_object_writer *this2 = (ubjs_prmtv_object_writer *)this;;
    *plen = 0;

    if (this2->type_marker != 0)
    {
        /* # + marker */
        *plen += 2;
    }

    if (this2->count_writer != 0)
    {
        /* $ + marker + prmtv */
        *plen += 2 + this2->count_length;
    }

    if (this2->type_marker == 0 && this2->count_writer == 0)
    {
        /* ]*/
        *plen += 1;
    }

    {
        unsigned int i = 0;
        for (i = 0; i < this2->len; i++)
        {
            /* marker + key + prmtv */
            *plen += this2->key_lengths[i] + this2->value_lengths[i] +
                (this2->type_marker != 0 ? 0 : 1);
        }
    }
}

void ubjs_prmtv_object_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    ubjs_prmtv_object_writer *this2 = (ubjs_prmtv_object_writer *)this;;
    unsigned int at = 0;

    if (this2->type_marker != 0)
    {
        /* # + marker */
        data[at++] = 36;
        data[at++] = this2->type_marker->marker;
    }

    if (this2->count_writer != 0)
    {
        unsigned int len = 0;
        /* $ + marker + prmtv */

        data[at++] = 35;
        data[at++] = this2->count_writer->ntype->marker;

        (this2->count_writer->ntype->writer_get_length_f)(this2->count_writer, &len);
        (this2->count_writer->ntype->writer_do_f)(this2->count_writer, data + at);
        at += len;
    }

    {
        unsigned int i = 0;
        for (i = 0; i < this2->len; i++)
        {
            unsigned int len = 0;
            ubjs_prmtv_ntype_writer *key_writer = this2->key_writers[i];
            ubjs_prmtv_ntype_writer *value_writer = this2->value_writers[i];

            (key_writer->ntype->writer_get_length_f)(key_writer, &len);
            (key_writer->ntype->writer_do_f)(key_writer, data + at);
            at += len;

            (value_writer->ntype->writer_get_length_f)(value_writer, &len);
            if (0 == this2->type_marker)
            {
                data[at++] = value_writer->ntype->marker;
            }
            (value_writer->ntype->writer_do_f)(value_writer, data + at);
            at += len;
        }
    }
    if (this2->type_marker == 0 && this2->count_writer == 0)
    {
        /* ]*/
        data[at] = 125;
    }
}

static void ubjs_prmtv_object_printer_calculate_lenghts(ubjs_prmtv_object_printer *this)
{
    ubjs_glue_dict_iterator *it = 0;
    ubjs_prmtv_object_t *prmtv = (ubjs_prmtv_object_t *)this->super.glue->prmtv;
    unsigned int len = 0;
    ubjs_library_alloc_f alloc_f = 0;
    ubjs_library_free_f free_f = 0;
    unsigned int i = 0;

    ubjs_library_get_alloc_f(this->super.lib, &alloc_f);
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (prmtv->glue->get_length_f)(prmtv->glue, &len);
    this->len = len;

    this->key_printers = (ubjs_prmtv_ntype_printer **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_printer *) * len);
    this->key_lengths = (unsigned int *)(alloc_f)(
        sizeof(unsigned int) * len);
    this->key_printers_glues = (ubjs_prmtv_ntype_printer_glue **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_printer_glue *) * len);
    this->value_printers = (ubjs_prmtv_ntype_printer **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_printer *) * len);
    this->value_lengths = (unsigned int *)(alloc_f)(
        sizeof(unsigned int) * len);
    this->value_printers_glues = (ubjs_prmtv_ntype_printer_glue **)(alloc_f)(
        sizeof(struct ubjs_prmtv_ntype_printer_glue *) * len);

    if (0 == len)
    {
        return;
    }

    (prmtv->glue->iterate_f)(prmtv->glue, &it);
    while (UR_OK == (it->next_f)(it))
    {
        ubjs_prmtv *value = 0;
        ubjs_prmtv_ntype *cntype = 0;
        unsigned int key_length = 0;
        char *key = 0;

        ubjs_prmtv_ntype_printer *key_printer = 0;
        ubjs_prmtv_ntype_printer_glue *key_glue = 0;
        ubjs_prmtv_ntype_printer *value_printer = 0;
        ubjs_prmtv_ntype_printer_glue *value_glue = 0;

        key_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_printer_glue));
        key_glue->debug_f = 0;
        key_glue->userdata = 0;
        (it->get_key_length_f)(it, &key_length);
        key = (char *)(alloc_f)(sizeof(char) * key_length);
        (it->copy_key_f)(it, key);
        (it->get_value_f)(it, (void *)&value);
        ubjs_prmtv_str(this->super.lib, key_length, key, &(key_glue->prmtv));
        (free_f)(key);
        (ubjs_prmtv_str_ntype.printer_new_f)(this->super.lib, key_glue, &(key_printer));
        this->key_printers[i] = key_printer;
        this->key_printers_glues[i] = key_glue;
        (ubjs_prmtv_str_ntype.printer_get_length_f)(key_printer, this->key_lengths + i);

        value_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_printer_glue));
        value_glue->debug_f = 0;
        value_glue->userdata = 0;
        value_glue->prmtv = value;
        ubjs_prmtv_get_ntype(value, &cntype);
        (cntype->printer_new_f)(this->super.lib, value_glue, &(value_printer));
        this->value_printers[i] = value_printer;
        this->value_printers_glues[i] = value_glue;
        (cntype->printer_get_length_f)(value_printer, this->value_lengths + i);

        if (len >= 3 && i == 0)
        {
            this->type_marker = cntype;
        }
        else if (cntype != this->type_marker)
        {
            this->type_marker = 0;
        }
        i++;
    }

    (it->free_f)(&it);

    if (len >= 3)
    {
        ubjs_prmtv *count = 0;
        ubjs_prmtv_ntype *cntype = 0;
        ubjs_prmtv_ntype_printer_glue *count_glue = 0;
        ubjs_prmtv_ntype_printer *count_printer = 0;

        count_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
            struct ubjs_prmtv_ntype_printer_glue));
        count_glue->debug_f = 0;
        count_glue->userdata = 0;

        ubjs_prmtv_int(this->super.lib, i, &count);
        count_glue->prmtv = count;

        ubjs_prmtv_get_ntype(count, &cntype);
        (cntype->printer_new_f)(this->super.lib, count_glue, &(count_printer));

        this->count_printer = count_printer;
        this->count_printer_glue = count_glue;
        (cntype->printer_get_length_f)(count_printer, &(this->count_length));
    }
}

ubjs_result ubjs_prmtv_object_printer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue, ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_object_printer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_object_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_object_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_object_printer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_object_ntype;
    this->super.name = "object";
    this->super.glue = glue;
    this->super.userdata = 0;

    this->type_marker = 0;
    this->count_printer_glue = 0;
    this->count_printer = 0;

    ubjs_prmtv_object_printer_calculate_lenghts(this);

    *pthis = (ubjs_prmtv_ntype_printer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_printer_free(ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_object_printer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *antype = 0;
    unsigned int i = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_object_printer *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);

    if (0 != this->count_printer)
    {
        ubjs_prmtv_get_ntype(this->count_printer->glue->prmtv, &antype);
        ubjs_prmtv_free(&(this->count_printer->glue->prmtv));
        (free_f)(this->count_printer->glue);
        (antype->printer_free_f)(&this->count_printer);
    }

    for (i = 0; i < this->len; i++)
    {
        ubjs_prmtv_free(&(this->key_printers_glues[i]->prmtv));
        (free_f)(this->key_printers_glues[i]);
        (this->key_printers[i]->ntype->printer_free_f)(&(this->key_printers[i]));
        (free_f)(this->value_printers_glues[i]);
        (this->value_printers[i]->ntype->printer_free_f)(&(this->value_printers[i]));
    }
    (free_f)(this->key_printers);
    (free_f)(this->key_lengths);
    (free_f)(this->key_printers_glues);
    (free_f)(this->value_printers);
    (free_f)(this->value_lengths);
    (free_f)(this->value_printers_glues);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_object_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    ubjs_prmtv_object_writer *this2 = (ubjs_prmtv_object_writer *)this;;
    *plen = 0;

    if (this2->type_marker != 0)
    {
        /* [#] + [marker] */
        *plen += 6;
    }

    if (this2->count_writer != 0)
    {
        /* [$] + [marker] + prmtv */
        *plen += 6 + this2->count_length;
    }

    {
        unsigned int i = 0;
        for (i = 0; i < this2->len; i++)
        {
            /* \n + indent + key + [marker] + prmtv */
            *plen += 1 + ((1 + this->glue->indent) * 4) + this2->key_lengths[i] +
                this2->value_lengths[i] + (this2->type_marker != 0 ? 0 : 3);
        }
    }

    if (this2->type_marker == 0 && this2->count_writer == 0)
    {
        /* \n + indent + []] */
        *plen += 3 + (this2->len > 0 ? 1 + (this->glue->indent) * 4 : 0);
    }
}

void ubjs_prmtv_object_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    ubjs_prmtv_object_printer *this2 = (ubjs_prmtv_object_printer *)this;;
    unsigned int at = 0;

    if (this2->type_marker != 0)
    {
        /* # + marker */
        data[at++] = '[';
        data[at++] = 36;
        data[at++] = ']';
        data[at++] = '[';
        data[at++] = this2->type_marker->marker;
        data[at++] = ']';
    }

    if (this2->count_printer != 0)
    {
        unsigned int len = 0;
        /* $ + marker + prmtv */

        data[at++] = '[';
        data[at++] = 35;
        data[at++] = ']';
        data[at++] = '[';
        data[at++] = this2->count_printer->ntype->marker;
        data[at++] = ']';

        (this2->count_printer->ntype->printer_get_length_f)(this2->count_printer, &len);
        (this2->count_printer->ntype->printer_do_f)(this2->count_printer, data + at);
        at += len;
    }

    {
        unsigned int i = 0, j;
        for (i = 0; i < this2->len; i++)
        {
            unsigned int len = 0;
            ubjs_prmtv_ntype_printer *key_printer = this2->key_printers[i];
            ubjs_prmtv_ntype_printer *value_printer = this2->value_printers[i];

            data[at++] = '\n';
            for (j = 0; j < (1 + this->glue->indent) * 4; j++, data[at++] = ' ')
            {
            }

            (key_printer->ntype->printer_get_length_f)(key_printer, &len);
            (key_printer->ntype->printer_do_f)(key_printer, data + at);
            at += len;

            (value_printer->ntype->printer_get_length_f)(value_printer, &len);
            if (0 == this2->type_marker)
            {
                data[at++] = '[';
                data[at++] = value_printer->ntype->marker;
                data[at++] = ']';
            }
            (value_printer->ntype->printer_do_f)(value_printer, data + at);
            at += len;
        }
    }
    if (this2->type_marker == 0 && this2->count_printer == 0)
    {
        /* \n + indent + ]*/
        if (0 < this2->len)
        {
            unsigned int j;
            data[at++] = '\n';
            for (j = 0; j < this->glue->indent * 4; j++, data[at++] = ' ')
            {
            }
        }
        data[at++] = '[';
        data[at++] = 125;
        data[at++] = ']';
    }
}
