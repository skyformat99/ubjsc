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
#include "ubjs_primitive_array_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"
#include "ubjs_glue_array_array.h"

ubjs_prmtv_ntype ubjs_prmtv_array_ntype =
{
    91,

    ubjs_prmtv_array_free,

    0,
    0,

    ubjs_prmtv_array_debug_string_get_length,
    ubjs_prmtv_array_debug_string_copy,

    ubjs_prmtv_array_parser_processor_new,
    ubjs_prmtv_array_parser_processor_free,

    ubjs_prmtv_array_parser_processor_got_present,
    ubjs_prmtv_array_parser_processor_got_marker,
    ubjs_prmtv_array_parser_processor_got_control,

    ubjs_prmtv_array_parser_processor_read_byte,

    ubjs_prmtv_array_writer_new,
    ubjs_prmtv_array_writer_free,
    ubjs_prmtv_array_writer_get_length,
    ubjs_prmtv_array_writer_do,

    ubjs_prmtv_array_printer_new,
    ubjs_prmtv_array_printer_free,
    ubjs_prmtv_array_printer_get_length,
    ubjs_prmtv_array_printer_do
};

ubjs_prmtv_ntype ubjs_prmtv_array_end_ntype =
{
    93,

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

ubjs_prmtv_ntype ubjs_prmtv_array_type_ntype =
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

ubjs_prmtv_ntype ubjs_prmtv_array_count_ntype =
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

ubjs_result ubjs_prmtv_array(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_prmtv_array_t *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_glue_array_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_array_t *)(alloc_f)(sizeof(struct ubjs_prmtv_array_t));
    this->super.lib = lib;
    this->super.type = 0;
    this->super.ntype = &ubjs_prmtv_array_ntype;

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    *pthis = (ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_prmtv_array_t *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_glue_array_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }


    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_array_t *)(alloc_f)(sizeof(struct ubjs_prmtv_array_t));
    this->super.lib = lib;
    this->super.type = 0;
    this->super.ntype = &ubjs_prmtv_array_ntype;

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == plen)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->get_length_f)(athis->glue, plen);
}

ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->get_first_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->get_last_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv **pitem)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->get_at_f)(athis->glue, pos, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->add_first_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->add_last_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv *item)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->add_at_f)(athis->glue, pos, item);
}

ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->delete_first_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->delete_last_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this, unsigned int pos)
{
    ubjs_prmtv_array_t *athis;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
    return (athis->glue->delete_at_f)(athis->glue, pos);
}

ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this, ubjs_array_iterator **piterator)
{
    ubjs_prmtv_array_t *athis;
    ubjs_array_iterator *iterator;

    if (0 == this || &ubjs_prmtv_array_ntype != this->ntype || 0 == piterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_prmtv_array_t *)this;
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

ubjs_result ubjs_prmtv_array_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv_array_t *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_array_t *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (this->glue->free_f)(&(this->glue));
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
/*    ubjs_prmtv_array_t *thisv;*/
    char tmp[30];
    unsigned int len = 0;
/*    ubjs_glue_array_iterator *it = 0;*/

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

/*    thisv = (ubjs_prmtv_array_t *)this;*/
/*    (thisv->glue->get_length_f)(thisv->glue, &len);*/

    /* "str(%u, " + %s + ")"*/
    *plen = sprintf(tmp, "array(%u)", len);

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

ubjs_result ubjs_prmtv_array_debug_string_copy(ubjs_prmtv *this, char *str)
{
/*    ubjs_prmtv_array_t *thisv;*/
    unsigned int len = 0;
    unsigned int at = 0;
/*    ubjs_glue_array_iterator *it = 0;*/

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

/*    thisv = (ubjs_prmtv_array_t *)this;*/
/*    (thisv->glue->get_length_f)(thisv->glue, &len);*/

    at = sprintf(str + at, "array(%u", len);
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

ubjs_result ubjs_prmtv_array_parser_processor_new(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_array_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_array_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_array_parser_processor));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_array_ntype;
    this->super.name = "array";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->data = 0;
    this->phase = UPAPPP_INIT;
    this->len = 0;
    this->expected_len = 0;
    this->type_marker = 0;
    this->count_marker = 0;

    this->legal_markers_type_count_top_end = 0;
    this->legal_markers_count = 0;
    this->legal_markers_int64s = 0;
    this->legal_markers_top = 0;
    this->legal_markers_top_end = 0;

    {
        ubjs_glue_array_builder *glue_builder = 0;

        ubjs_glue_array_array_builder_new(lib, &glue_builder);
        (glue_builder->set_value_free_f)(glue_builder, 0);
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_type_count_top_end));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_count));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_int64s));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_top));
        (glue_builder->build_f)(glue_builder, &(this->legal_markers_top_end));
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

            (this->legal_markers_type_count_top_end->add_last_f)(
                this->legal_markers_type_count_top_end, n);
            (this->legal_markers_top->add_last_f)(
                this->legal_markers_top, n);
            (this->legal_markers_top_end->add_last_f)(
                this->legal_markers_top_end, n);
            if (0 != n->new_from_int64_f)
            {
                (this->legal_markers_int64s->add_last_f)(this->legal_markers_int64s, n);
            }
        }
        (it->free_f)(&it);

        (this->legal_markers_type_count_top_end->add_last_f)(
            this->legal_markers_type_count_top_end, &ubjs_prmtv_array_type_ntype);

        (this->legal_markers_type_count_top_end->add_last_f)(
            this->legal_markers_type_count_top_end, &ubjs_prmtv_array_count_ntype);
        (this->legal_markers_count->add_last_f)(
            this->legal_markers_count, &ubjs_prmtv_array_count_ntype);

        (this->legal_markers_type_count_top_end->add_last_f)(
            this->legal_markers_type_count_top_end, &ubjs_prmtv_array_end_ntype);
        (this->legal_markers_top_end->add_last_f)(
            this->legal_markers_top_end, &ubjs_prmtv_array_end_ntype);

    }
    *pthis = (ubjs_prmtv_ntype_parser_processor *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_array_parser_processor *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_array_parser_processor *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    if (0 != this->data)
    {
        ubjs_prmtv_free(&(this->data));
    }

    (this->legal_markers_type_count_top_end->free_f)(&(this->legal_markers_type_count_top_end));
    (this->legal_markers_count->free_f)(&(this->legal_markers_count));
    (this->legal_markers_int64s->free_f)(&(this->legal_markers_int64s));
    (this->legal_markers_top->free_f)(&(this->legal_markers_top));
    (this->legal_markers_top_end->free_f)(&(this->legal_markers_top_end));

    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_array_parser_processor_got_present(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv_array_parser_processor *this2 = (ubjs_prmtv_array_parser_processor *)this;
    switch (this2->phase)
    {
        case UPAPPP_WANT_COUNT_PRMTV_VALUE:
            {
                int64_t len = 0;
                ubjs_prmtv_int_get(present, &len);
                if (0 > len)
                {
                    this2->phase = UPAPPP_DONE;
                    ubjs_prmtv_free(&present);
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
                    this2->phase = UPAPPP_DONE;
                    (this->glue->error_f)(this->glue, 33,
                        "Reached limit of container length");
                    return;
                }
                else if (this->glue->limit_recursion_level > 0 &&
                    this->glue->limit_recursion_level == this->glue->recursion_level)
                {
                    this2->phase = UPAPPP_DONE;
                    (this->glue->error_f)(this->glue, 29,
                        "Reached recursion level limit");
                    return;
                }
                else
                {
                    ubjs_prmtv_array_with_length(this->lib, len, &(this2->data));
                    if (0 == len)
                    {
                        ubjs_prmtv *data = this2->data;

                        (this->glue->debug_f)(this->glue, 11, "Empty - end");
                        this2->data = 0;
                        this2->phase = UPAPPP_DONE;
                        (this->glue->return_control_f)(this->glue, data);
                    }
                    else if (0 != this2->type_marker)
                    {
                        (this->glue->debug_f)(this->glue, 42,
                            "Want child marker - we are typed + counted");
                        this2->phase = UPAPPP_WANT_CHILD_PRMTV_VALUE;
                        (this->glue->want_child_f)(this->glue, this2->type_marker);
                    }
                    else
                    {
                        (this->glue->debug_f)(this->glue, 27, "Want child - we are counted");
                        this2->phase = UPAPPP_WANT_CHILD_PRMTV_MARKER;
                        (this->glue->want_marker_f)(this->glue, this2->legal_markers_top);
                    }
                }
            }
            break;

        case UPAPPP_WANT_CHILD_PRMTV_VALUE:
            (this->glue->debug_f)(this->glue, 9, "Got child");
            ubjs_prmtv_array_add_last(this2->data, present);
            this2->len += 1;

            if (0 != this2->count_marker && this2->len == this2->expected_len)
            {
                ubjs_prmtv *data = this2->data;

                (this->glue->debug_f)(this->glue, 3, "End");
                this2->data = 0;
                this2->phase = UPAPPP_DONE;
                (this->glue->return_control_f)(this->glue, data);
            }
            else
            {
                if (0 != this2->type_marker)
                {
                    (this->glue->debug_f)(this->glue, 23, "Want child - type+count");
                    this2->phase = UPAPPP_WANT_CHILD_PRMTV_VALUE;
                    (this->glue->want_child_f)(this->glue, this2->type_marker);
                }
                else if (0 != this2->count_marker)
                {
                    (this->glue->debug_f)(this->glue, 18, "Want child - count");
                    this2->phase = UPAPPP_WANT_CHILD_PRMTV_MARKER;
                    (this->glue->want_marker_f)(this->glue, this2->legal_markers_top);
                }
                else
                {
                    (this->glue->debug_f)(this->glue, 20, "Want child - untyped");
                    this2->phase = UPAPPP_WANT_CHILD_PRMTV_MARKER;
                    (this->glue->want_marker_f)(this->glue, this2->legal_markers_top_end);
                }
            }

            break;

        default:
            this2->phase = UPAPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got present");
            break;
    }
}

void ubjs_prmtv_array_parser_processor_got_marker(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv_ntype *marker)
{
    ubjs_prmtv_array_parser_processor *this2 = (ubjs_prmtv_array_parser_processor *)this;
    (this->glue->debug_f)(this->glue, 10, "Got marker");

    switch (this2->phase)
    {
        case UPAPPP_WANT_TYPE_COUNT_TOP_END_MARKER:
            if (&ubjs_prmtv_array_type_ntype == marker)
            {
                (this->glue->debug_f)(this->glue, 16, "Want type marker");
                this2->phase = UPAPPP_WANT_TYPE_MARKER;
                (this->glue->want_marker_f)(this->glue, this2->legal_markers_top);
            }
            else if (&ubjs_prmtv_array_end_ntype == marker)
            {
                ubjs_prmtv *data = 0;
                (this->glue->debug_f)(this->glue, 3, "End");
                ubjs_prmtv_array(this->lib, &(data));
                this2->phase = UPAPPP_DONE;
                (this->glue->return_control_f)(this->glue, data);
            }
            else if (&ubjs_prmtv_array_count_ntype == marker)
            {
                (this->glue->debug_f)(this->glue, 20, "Want count marker");
                this2->phase = UPAPPP_WANT_COUNT_PRMTV_MARKER;
                (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
            }
            else if (this->glue->limit_recursion_level > 0 &&
                this->glue->limit_recursion_level == this->glue->recursion_level)
            {
                this2->phase = UPAPPP_DONE;
                (this->glue->error_f)(this->glue, 29,
                    "Reached recursion level limit");
            }
            else
            {
                (this->glue->debug_f)(this->glue, 15, "We are untyped");
                this2->phase = UPAPPP_WANT_CHILD_PRMTV_VALUE;
                ubjs_prmtv_array(this->lib, &(this2->data));
                (this->glue->want_child_f)(this->glue, marker);
            }
            break;

        case UPAPPP_WANT_TYPE_MARKER:
            this2->phase = UPAPPP_WANT_COUNT_MARKER;
            this2->type_marker = marker;
            (this->glue->debug_f)(this->glue, 20, "We are typed");
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_count);
            break;

        case UPAPPP_WANT_COUNT_MARKER:
            (this->glue->debug_f)(this->glue, 20, "Want count marker");
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_int64s);
            this2->phase = UPAPPP_WANT_COUNT_PRMTV_MARKER;
            break;

        case UPAPPP_WANT_COUNT_PRMTV_MARKER:
            (this->glue->debug_f)(this->glue, 20, "Want count primitive");
            this2->count_marker = marker;
            this2->phase = UPAPPP_WANT_COUNT_PRMTV_VALUE;
            (this->glue->want_child_f)(this->glue, this2->count_marker);
            break;

        case UPAPPP_WANT_CHILD_PRMTV_MARKER:
            if (&ubjs_prmtv_array_end_ntype == marker)
            {
                ubjs_prmtv *data = this2->data;
                (this->glue->debug_f)(this->glue, 3, "End");
                this2->data = 0;
                this2->phase = UPAPPP_DONE;
                (this->glue->return_control_f)(this->glue, data);

            }
            else if (this->glue->limit_container_length > 0 &&
                this->glue->limit_container_length == this2->len)
            {
                this2->phase = UPAPPP_DONE;
                (this->glue->error_f)(this->glue, 33,
                    "Reached limit of container length");
            }
            else
            {
                (this->glue->debug_f)(this->glue, 15, "We are untyped");
                this2->phase = UPAPPP_WANT_CHILD_PRMTV_VALUE;
                (this->glue->want_child_f)(this->glue, marker);
            }
            break;

        default:
            this2->phase = UPAPPP_DONE;
            (this->glue->error_f)(this->glue, 21,
                "Unexpected got marker");
    }
}

void ubjs_prmtv_array_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this)
{
    ubjs_prmtv_array_parser_processor *this2 = (ubjs_prmtv_array_parser_processor *)this;
    switch (this2->phase)
    {
        case UPAPPP_INIT:
            this2->phase = UPAPPP_WANT_TYPE_COUNT_TOP_END_MARKER;
            (this->glue->want_marker_f)(this->glue, this2->legal_markers_type_count_top_end);
            break;

        default:
            this2->phase = UPAPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got control");
            break;
    }
}

void ubjs_prmtv_array_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t achr)
{
}

ubjs_result ubjs_prmtv_array_writer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_array_writer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_array_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_array_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_array_writer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_array_ntype;
    this->super.name = "array";
    this->super.glue = glue;
    this->super.userdata = 0;

    this->type_marker = 0;

    this->count_writer_glue = 0;
    this->count_writer = 0;

    {
        ubjs_glue_array_iterator *it = 0;
        ubjs_prmtv_array_t *prmtv = (ubjs_prmtv_array_t *)glue->prmtv;
        unsigned int len = 0;

        (prmtv->glue->get_length_f)(prmtv->glue, &len);
        this->len = len;

        this->item_writers = (ubjs_prmtv_ntype_writer **)(alloc_f)(
            sizeof(struct ubjs_prmtv_ntype_writer *) * len);
        this->item_lengths = (unsigned int *)(alloc_f)(
            sizeof(unsigned int) * len);
        this->item_writers_glues = (ubjs_prmtv_ntype_writer_glue **)(alloc_f)(
            sizeof(struct ubjs_prmtv_ntype_writer_glue *) * len);

        if (0 < len)
        {
            unsigned int i = 0;
            (prmtv->glue->iterate_f)(prmtv->glue, &it);
            while (UR_OK == (it->next_f)(it))
            {
                ubjs_prmtv *child = 0;
                ubjs_prmtv_ntype *cntype = 0;
                ubjs_prmtv_ntype_writer *child_writer = 0;
                ubjs_prmtv_ntype_writer_glue *child_glue = 0;

                child_glue = (ubjs_prmtv_ntype_writer_glue *)(alloc_f)(sizeof(
                    struct ubjs_prmtv_ntype_writer_glue));
                child_glue->debug_f = 0;
                child_glue->userdata = 0;

                (it->get_f)(it, (void *)&child);
                child_glue->prmtv = child;

                ubjs_prmtv_get_ntype(child, &cntype);
                (cntype->writer_new_f)(lib, child_glue, &(child_writer));

                this->item_writers[i] = child_writer;
                this->item_writers_glues[i] = child_glue;
                (cntype->writer_get_length_f)(child_writer, this->item_lengths + i);

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

                ubjs_prmtv_int(lib, i, &count);
                count_glue->prmtv = count;

                ubjs_prmtv_get_ntype(count, &cntype);
                (cntype->writer_new_f)(lib, count_glue, &(count_writer));

                this->count_writer = count_writer;
                this->count_writer_glue = count_glue;
                (cntype->writer_get_length_f)(count_writer, &(this->count_length));
            }
            (it->free_f)(&it);
        }
    }

    *pthis = (ubjs_prmtv_ntype_writer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_writer_free(ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_array_writer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *antype = 0;
    unsigned int i = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_array_writer *)*pthis;
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
        (free_f)(this->item_writers_glues[i]);
        (this->item_writers[i]->ntype->writer_free_f)(&(this->item_writers[i]));
    }
    (free_f)(this->item_writers);
    (free_f)(this->item_lengths);
    (free_f)(this->item_writers_glues);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_array_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    ubjs_prmtv_array_writer *this2 = (ubjs_prmtv_array_writer *)this;;
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
            /* marker + prmtv */
            *plen += this2->item_lengths[i] + (this2->type_marker != 0 ? 0 : 1);
        }
    }
}

void ubjs_prmtv_array_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    ubjs_prmtv_array_writer *this2 = (ubjs_prmtv_array_writer *)this;;
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
            ubjs_prmtv_ntype_writer *child_writer = this2->item_writers[i];

            (child_writer->ntype->writer_get_length_f)(child_writer, &len);

            if (0 == this2->type_marker)
            {
                data[at++] = child_writer->ntype->marker;
            }
            (child_writer->ntype->writer_do_f)(child_writer, data + at);
            at += len;
        }
    }
    if (this2->type_marker == 0 && this2->count_writer == 0)
    {
        /* ]*/
        data[at] = 93;
    }
}

ubjs_result ubjs_prmtv_array_printer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue, ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_array_printer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_array_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_array_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_array_printer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_array_ntype;
    this->super.name = "array";
    this->super.glue = glue;
    this->super.userdata = 0;

    this->type_marker = 0;

    this->count_printer_glue = 0;
    this->count_printer = 0;

    {
        ubjs_glue_array_iterator *it = 0;
        ubjs_prmtv_array_t *prmtv = (ubjs_prmtv_array_t *)glue->prmtv;
        unsigned int len = 0;

        (prmtv->glue->get_length_f)(prmtv->glue, &len);
        this->len = len;

        this->item_printers = (ubjs_prmtv_ntype_printer **)(alloc_f)(
            sizeof(struct ubjs_prmtv_ntype_printer *) * len);
        this->item_lengths = (unsigned int *)(alloc_f)(
            sizeof(unsigned int *) * len);
        this->item_printers_glues = (ubjs_prmtv_ntype_printer_glue **)(alloc_f)(
            sizeof(struct ubjs_prmtv_ntype_printer_glue *) * len);

        if (0 < len)
        {
            unsigned int i = 0;
            (prmtv->glue->iterate_f)(prmtv->glue, &it);
            while (UR_OK == (it->next_f)(it))
            {
                ubjs_prmtv *child = 0;
                ubjs_prmtv_ntype *cntype = 0;
                ubjs_prmtv_ntype_printer *child_printer = 0;
                ubjs_prmtv_ntype_printer_glue *child_glue = 0;

                child_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
                    struct ubjs_prmtv_ntype_printer_glue));
                child_glue->debug_f = 0;
                child_glue->userdata = 0;

                (it->get_f)(it, (void *)&child);
                child_glue->prmtv = child;

                ubjs_prmtv_get_ntype(child, &cntype);
                (cntype->printer_new_f)(lib, child_glue, &(child_printer));

                this->item_printers[i] = child_printer;
                this->item_printers_glues[i] = child_glue;
                (cntype->printer_get_length_f)(child_printer, this->item_lengths + i);

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

            if (i >= 3)
            {
                ubjs_prmtv *count = 0;
                ubjs_prmtv_ntype *cntype = 0;
                ubjs_prmtv_ntype_printer_glue *count_glue = 0;
                ubjs_prmtv_ntype_printer *count_printer = 0;

                count_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
                    struct ubjs_prmtv_ntype_printer_glue));
                count_glue->debug_f = 0;
                count_glue->userdata = 0;

                ubjs_prmtv_int(lib, i, &count);
                count_glue->prmtv = count;

                ubjs_prmtv_get_ntype(count, &cntype);
                (cntype->printer_new_f)(lib, count_glue, &(count_printer));

                this->count_printer = count_printer;
                this->count_printer_glue = count_glue;
                (cntype->printer_get_length_f)(count_printer, &(this->count_length));
            }

            (it->free_f)(&it);
        }
    }

    *pthis = (ubjs_prmtv_ntype_printer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_printer_free(ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_array_printer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *antype = 0;
    unsigned int i = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_array_printer *)*pthis;
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
        (free_f)(this->item_printers_glues[i]);
        (this->item_printers[i]->ntype->printer_free_f)(&(this->item_printers[i]));
    }
    (free_f)(this->item_printers);
    (free_f)(this->item_lengths);
    (free_f)(this->item_printers_glues);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_array_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    ubjs_prmtv_array_writer *this2 = (ubjs_prmtv_array_writer *)this;;
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
            /* \n + indent + [marker] + prmtv */
            *plen += 1 + ((1 + this->glue->indent) * 4) + this2->item_lengths[i] + (this2->type_marker != 0 ? 0 : 3);
        }
    }

    if (this2->type_marker == 0 && this2->count_writer == 0)
    {
        /* \n + indent + []] */
        *plen += 3 + (this2->len > 0 ? 1 + (this->glue->indent) * 4 : 0);
    }
}

void ubjs_prmtv_array_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    ubjs_prmtv_array_printer *this2 = (ubjs_prmtv_array_printer *)this;;
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
            ubjs_prmtv_ntype_printer *child_printer = this2->item_printers[i];

            (child_printer->ntype->printer_get_length_f)(child_printer, &len);

            data[at++] = '\n';
            for (j = 0; j < (1 + this->glue->indent) * 4; j++, data[at++] = ' ')
            {
            }

            if (0 == this2->type_marker)
            {
                data[at++] = '[';
                data[at++] = child_printer->ntype->marker;
                data[at++] = ']';
            }
            (child_printer->ntype->printer_do_f)(child_printer, data + at);
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
        data[at++] = 93;
        data[at++] = ']';
    }
}
