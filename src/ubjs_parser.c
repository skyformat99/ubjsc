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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ubjs_parser_prv.h"

int ubjs_processor_factories_top_len=16;
ubjs_processor_factory ubjs_processor_factories_top[] =
{
    {MARKER_CHAR, (ubjs_processor_factory_create)ubjs_processor_char},
    {MARKER_FLOAT64, (ubjs_processor_factory_create)ubjs_processor_float64},
    {MARKER_FALSE, (ubjs_processor_factory_create)ubjs_processor_false},
    {MARKER_HPN, (ubjs_processor_factory_create)ubjs_processor_hpn},
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_INT64, (ubjs_processor_factory_create)ubjs_processor_int64},
    {MARKER_NOOP, (ubjs_processor_factory_create)ubjs_processor_noop},
    {MARKER_STR, (ubjs_processor_factory_create)ubjs_processor_str},
    {MARKER_TRUE, (ubjs_processor_factory_create)ubjs_processor_true},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_NULL, (ubjs_processor_factory_create)ubjs_processor_null},
    {MARKER_ARRAY_BEGIN, (ubjs_processor_factory_create)ubjs_processor_array},
    {MARKER_FLOAT32, (ubjs_processor_factory_create)ubjs_processor_float32},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32},
    {MARKER_OBJECT_BEGIN, (ubjs_processor_factory_create)ubjs_processor_object}
};

int ubjs_processor_factories_array_len=19;
ubjs_processor_factory ubjs_processor_factories_array[] =
{
    {MARKER_OPTIMIZE_COUNT, (ubjs_processor_factory_create)ubjs_processor_array_count},
    {MARKER_OPTIMIZE_TYPE, (ubjs_processor_factory_create)ubjs_processor_array_type},
    {MARKER_CHAR, (ubjs_processor_factory_create)ubjs_processor_char},
    {MARKER_FLOAT64, (ubjs_processor_factory_create)ubjs_processor_float64},
    {MARKER_FALSE, (ubjs_processor_factory_create)ubjs_processor_false},
    {MARKER_HPN, (ubjs_processor_factory_create)ubjs_processor_hpn},
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_INT64, (ubjs_processor_factory_create)ubjs_processor_int64},
    {MARKER_NOOP, (ubjs_processor_factory_create)ubjs_processor_noop},
    {MARKER_STR, (ubjs_processor_factory_create)ubjs_processor_str},
    {MARKER_TRUE, (ubjs_processor_factory_create)ubjs_processor_true},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_NULL, (ubjs_processor_factory_create)ubjs_processor_null},
    {MARKER_ARRAY_BEGIN, (ubjs_processor_factory_create)ubjs_processor_array},
    {MARKER_ARRAY_END, (ubjs_processor_factory_create)ubjs_processor_array_end},
    {MARKER_FLOAT32, (ubjs_processor_factory_create)ubjs_processor_float32},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32},
    {MARKER_OBJECT_BEGIN, (ubjs_processor_factory_create)ubjs_processor_object}
};

int ubjs_processor_factories_array_type_len=1;
ubjs_processor_factory ubjs_processor_factories_array_type[] =
{
    {MARKER_OPTIMIZE_COUNT, (ubjs_processor_factory_create)ubjs_processor_array_count},
};

int ubjs_processor_factories_array_count_len=16;
ubjs_processor_factory ubjs_processor_factories_array_count[] =
{
    {MARKER_CHAR, (ubjs_processor_factory_create)ubjs_processor_char},
    {MARKER_FLOAT64, (ubjs_processor_factory_create)ubjs_processor_float64},
    {MARKER_FALSE, (ubjs_processor_factory_create)ubjs_processor_false},
    {MARKER_HPN, (ubjs_processor_factory_create)ubjs_processor_hpn},
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_INT64, (ubjs_processor_factory_create)ubjs_processor_int64},
    {MARKER_NOOP, (ubjs_processor_factory_create)ubjs_processor_noop},
    {MARKER_STR, (ubjs_processor_factory_create)ubjs_processor_str},
    {MARKER_TRUE, (ubjs_processor_factory_create)ubjs_processor_true},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_NULL, (ubjs_processor_factory_create)ubjs_processor_null},
    {MARKER_ARRAY_BEGIN, (ubjs_processor_factory_create)ubjs_processor_array},
    {MARKER_FLOAT32, (ubjs_processor_factory_create)ubjs_processor_float32},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32},
    {MARKER_OBJECT_BEGIN, (ubjs_processor_factory_create)ubjs_processor_object}
};

int ubjs_processor_factories_object_len=7;
ubjs_processor_factory ubjs_processor_factories_object[] =
{
    {MARKER_OPTIMIZE_COUNT, (ubjs_processor_factory_create)ubjs_processor_object_count},
    {MARKER_OPTIMIZE_TYPE, (ubjs_processor_factory_create)ubjs_processor_object_type},
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32},
    {MARKER_OBJECT_END, (ubjs_processor_factory_create)ubjs_processor_object_end}
};

int ubjs_processor_factories_object_type_len=1;
ubjs_processor_factory ubjs_processor_factories_object_type[] =
{
    {MARKER_OPTIMIZE_COUNT, (ubjs_processor_factory_create)ubjs_processor_object_count},
};

int ubjs_processor_factories_object_count_len=4;
ubjs_processor_factory ubjs_processor_factories_object_count[] =
{
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32}
};

int ubjs_processor_factories_ints_len=4;
ubjs_processor_factory ubjs_processor_factories_ints[] =
{
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_INT8, (ubjs_processor_factory_create)ubjs_processor_int8},
    {MARKER_INT32, (ubjs_processor_factory_create)ubjs_processor_int32}
};

ubjs_result ubjs_parser_error_new(char *message, unsigned int len, ubjs_parser_error **pthis)
{
    ubjs_parser_error *this;

    this=(ubjs_parser_error *)malloc(sizeof(struct ubjs_parser_error));

    this->message = (char *)malloc(sizeof(char) * len);
    strncpy(this->message, message, len);
    this->message_length=len;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_error_free(ubjs_parser_error **pthis)
{
    ubjs_parser_error *this;

    this=*pthis;
    free(this->message);
    free(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *this, unsigned int *length)
{
    if (0 == this || 0 == length)
    {
        return UR_ERROR;
    }

    *length=this->message_length;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *this, char *message)
{
    if (0 == this || 0 == message)
    {
        return UR_ERROR;
    }

    strncpy(message, this->message, this->message_length);
    return UR_OK;
}

ubjs_result ubjs_parser_new(ubjs_parser **pthis, ubjs_parser_context *context)
{
    ubjs_parser *this;

    if (0 == pthis || 0 == context)
    {
        return UR_ERROR;
    }

    if (0 == context->parsed || 0 == context->free || 0 == context->error)
    {
        return UR_ERROR;
    }

    this = (ubjs_parser *)malloc(sizeof(struct ubjs_parser));
    ubjs_processor_top(this, &(this->processor));

    this->context=context;

    /* Always processor_top, they have control */
    (this->processor->got_control)(this->processor, 0);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_free(ubjs_parser **pthis)
{
    ubjs_parser *this;
    ubjs_processor *processor;
    ubjs_processor *parent_processor;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;

    for (processor=this->processor; 0 != processor;)
    {
        parent_processor = processor->parent;
        (processor->free)(processor);
        processor=parent_processor;
    }

    (this->context->free)(this->context);

    free(this);
    (*pthis)=0;

    return UR_OK;
}

ubjs_result ubjs_parser_get_context(ubjs_parser *this, ubjs_parser_context **context)
{
    if (0 == this || 0 == context)
    {
        return UR_ERROR;
    }

    *context=this->context;
    return UR_OK;
}

ubjs_result ubjs_parser_parse(ubjs_parser *this, uint8_t *data, unsigned int length)
{
    unsigned int i;

    if (0 == this || 0 == data)
    {
        return UR_ERROR;
    }

    if (0 == length)
    {
        return UR_OK;
    }

    for (i=0; i<length; i++)
    {
        if (UR_ERROR == (this->processor->read_char)(this->processor, i, data[i]))
        {
            return UR_ERROR;
        }
    }

    return UR_OK;
}

ubjs_result ubjs_parser_give_control(ubjs_parser *this, ubjs_processor *processor,
    ubjs_prmtv *present)
{
    this->processor=processor;
    if (0 != processor->got_control)
    {
        return (processor->got_control)(processor, present);
    }
    return UR_OK;
}

ubjs_result ubjs_parser_emit_error(ubjs_parser *this, unsigned int len, char *message)
{
    ubjs_parser_error *error;

    ubjs_parser_error_new(message, len, &error);
    (this->context->error)(this->context, error);
    ubjs_parser_error_free(&error);
    return UR_ERROR;
}

ubjs_result ubjs_processor_top(ubjs_parser *parser, ubjs_processor**pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "top";
    this->parent=0;
    this->userdata=0;
    this->parser=parser;
    this->got_control=ubjs_processor_top_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_top_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        (this->parser->context->parsed)(this->parser->context, present);
    }

    ubjs_processor_next_object(this, ubjs_processor_factories_top, ubjs_processor_factories_top_len,
                               &nxt);
    return ubjs_parser_give_control(this->parser, nxt, 0);
}

ubjs_result ubjs_processor_ints(ubjs_processor *parent, ubjs_processor **pthis)
{
    return ubjs_processor_next_object(parent, ubjs_processor_factories_ints,
        ubjs_processor_factories_ints_len, pthis);
}

ubjs_result ubjs_processor_next_object(ubjs_processor *parent, ubjs_processor_factory *factories,
    int factories_len, ubjs_processor **pthis)
{
    ubjs_processor_next_objext *this;
    unsigned int length;
    char *name;
    char *name_template = "next object from %d factories";

    length=snprintf(0, 0, name_template, factories_len);
    name=(char *)malloc(sizeof(char)*(length + 1));
    snprintf(name, length + 1, name_template, factories_len);

    this = (ubjs_processor_next_objext *)malloc(sizeof(struct ubjs_processor_next_objext));
    this->super.name = name;
    this->super.parent=parent;
    this->super.parser=parent->parser;
    this->super.userdata=0;
    this->super.got_control=ubjs_processor_next_object_got_control;;
    this->super.read_char = ubjs_processor_next_object_read_char;
    this->super.free=ubjs_processor_next_object_free;
    this->factories=factories;
    this->factories_len=factories_len;

    *pthis=(ubjs_processor *)this;
    return UR_OK;
}

void ubjs_processor_next_object_free(ubjs_processor *this)
{
    free(this->name);
    free(this);
}

ubjs_result ubjs_processor_next_object_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
	return UR_OK;
}

ubjs_result ubjs_processor_next_object_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t c)
{
    ubjs_processor_next_objext *sub=(ubjs_processor_next_objext *)this;
    int i;
    ubjs_processor *next;
    ubjs_result ret;

    ubjs_parser_error *error;
    char *message;
    unsigned int message_length;

    for (i=0; i<sub->factories_len; i++)
    {
        ubjs_processor_factory *it=sub->factories + i;

        if (it->marker == c)
        {
            (it->create)(this->parent, &next);
            ret = ubjs_parser_give_control(this->parser, next, 0);
            (this->free)(this);
            return ret;
        }
    }

    ubjs_compact_sprintf(&message, &message_length, "At %d [%d] unknown marker", pos, c);
    ret = ubjs_parser_emit_error(this->parser, message_length, message);
    free(message);
    return ret;
}

ubjs_result ubjs_processor_child_produced_length(ubjs_processor *this, ubjs_prmtv *obj,
    unsigned int *plength)
{
    ubjs_parser_error *error;
    char *message;
    ubjs_bool ret;

    int8_t v8;
    uint8_t vu8;
    int16_t v16;
    int32_t v32;

    ubjs_bool got_length=UFALSE;
    unsigned int length=0;

    if (UR_OK == ubjs_prmtv_is_int8(obj, &ret) && UTRUE == ret)
    {
        ubjs_prmtv_int8_get(obj, &v8);
        if (0 <= v8)
        {
            got_length=UTRUE;
            length=(unsigned int)v8;
        }
        else
        {
            message = "Got int8 negative length";
        }
    }
    else if (UR_OK == ubjs_prmtv_is_uint8(obj, &ret) && UTRUE == ret)
    {
        ubjs_prmtv_uint8_get(obj, &vu8);
        got_length=UTRUE;
        length=(unsigned int)vu8;
    }
    else if (UR_OK == ubjs_prmtv_is_int16(obj, &ret) && UTRUE == ret)
    {
        ubjs_prmtv_int16_get(obj, &v16);
        if (0 <= v16)
        {
            got_length=UTRUE;
            length=(unsigned int)v16;
        }
        else
        {
            message = "Got int16 negative length";
        }
    }
    else if (UR_OK == ubjs_prmtv_is_int32(obj, &ret) && UTRUE == ret)
    {
        ubjs_prmtv_int32_get(obj, &v32);
        if (0 <= v32)
        {
            got_length=UTRUE;
            length=(unsigned int)v32;
        }
        else
        {
            message = "Got int32 negative length";
        }
    }

    ubjs_prmtv_free(&obj);

    if (UTRUE == got_length)
    {
        *plength = length;
        return UR_OK;
    }

    return ubjs_parser_emit_error(this->parser, (unsigned int)strlen(message), message);
}

ubjs_result ubjs_processor_null(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "null";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_null();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_noop(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "noop";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_noop();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_true(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "true";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_true();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}


ubjs_result ubjs_processor_false(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "false";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_false();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_no_length_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv *ret=(ubjs_prmtv *)this->userdata;
    ubjs_result aret;

    aret = ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_int8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "int8";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char = ubjs_processor_int8_read_char;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_int8_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_result aret;
    ubjs_prmtv *ret;
    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);

    ubjs_prmtv_int8(*((int8_t *)value2), &ret);
    aret = ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_uint8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "uint8";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char = ubjs_processor_uint8_read_char;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_uint8_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_result aret;
    ubjs_prmtv *ret;

    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);

    ubjs_prmtv_uint8(*((uint8_t *)value2), &ret);
    aret = ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_char(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "char";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char = ubjs_processor_char_read_char;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_char_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_result aret;
    ubjs_prmtv *ret;
    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);

    ubjs_prmtv_char(*((char *)value2), &ret);
    aret = ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_int16(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)malloc(sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 2);
    data->done=0;
    this->name = "int16";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_int16_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_int16_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_result aret=UR_OK;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (2 <= data->done)
    {
        uint8_t value2[2];
        ubjs_endian_convert_big_to_native(data->data, value2, 2);
        ubjs_prmtv_int16(*((int16_t *)value2), &ret);
        aret = ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }

    return aret;
}

void ubjs_processor_longint_free(ubjs_processor *this)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    free(data->data);
    free(this->userdata);
    free(this);
}

ubjs_result ubjs_processor_int32(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)malloc(sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 4);
    data->done=0;
    this->name = "int32";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_int32_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_int32_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_result aret=UR_OK;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (4 <= data->done)
    {
        uint8_t value2[4];
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_prmtv_int32(*((int32_t *)value2), &ret);
        aret = ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }

    return aret;
}

ubjs_result ubjs_processor_int64(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)malloc(sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 8);
    data->done=0;
    this->name = "int64";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_int64_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_int64_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_result aret=UR_OK;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_prmtv_int64(*((int64_t *)value2), &ret);
        aret = ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }

    return aret;
}

ubjs_result ubjs_processor_float32(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)malloc(sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 4);
    data->done=0;
    this->name = "float32";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_float32_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_float32_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_result aret=UR_OK;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (4 <= data->done)
    {
        uint8_t value2[4];
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_prmtv_float32(*((float32_t *)value2), &ret);
        aret = ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }

    return aret;
}

ubjs_result ubjs_processor_float64(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)malloc(sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 8);
    data->done=0;
    this->name = "float64";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_float64_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_float64_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_result aret=UR_OK;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        ubjs_prmtv_float64(*((float64_t *)value2), &ret);
        aret = ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }

    return aret;
}

ubjs_result ubjs_processor_str(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_str *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_str *)malloc(sizeof(struct ubjs_userdata_str));
    data->have_length=UFALSE;
    data->length=-1;
    data->data=0;
    data->done=0;
    this->name = "str";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_str_got_control;
    this->read_char = ubjs_processor_str_read_char;
    this->free=ubjs_processor_str_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_str_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;

    if (0 != present)
    {
        unsigned int length = 0;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return UR_ERROR;
        }

        this->name = "str with length";
        data->have_length = UTRUE;
        data->length=length;
        data->data=(char *)malloc(sizeof(char) * length);
        if (0 == length)
        {
            return ubjs_processor_str_complete(this);
        }
    }

    if (UFALSE == data->have_length)
    {
        ubjs_processor_ints(this, &nxt);
        return ubjs_parser_give_control(this->parser, nxt, 0);
    }

    return UR_OK;
}

void ubjs_processor_str_free(ubjs_processor *this)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;

    if (UTRUE == data->have_length)
    {
        free(data->data);
    }

    free(data);
    free(this);
}

ubjs_result ubjs_processor_str_read_char(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;

    data->data[data->done++] = (char)c;

    if (data->done == data->length)
    {
        return ubjs_processor_str_complete(this);
    }
    return UR_OK;
}

ubjs_result ubjs_processor_str_complete(ubjs_processor *this)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;
    ubjs_prmtv *product;
    ubjs_result ret;

    ubjs_prmtv_str(data->done, data->data, &product);

    ret = ubjs_parser_give_control(this->parser, this->parent, product);
    (this->free)(this);
    return ret;
}

ubjs_result ubjs_processor_hpn(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_hpn *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_hpn *)malloc(sizeof(struct ubjs_userdata_hpn));
    data->have_length=UFALSE;
    data->length=-1;
    data->data=0;
    data->done=0;
    this->name = "hpn";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_hpn_got_control;
    this->read_char = ubjs_processor_hpn_read_char;
    this->free=ubjs_processor_hpn_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_hpn_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;

    if (0 != present)
    {
        unsigned int length = 0;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return UR_ERROR;
        }

        this->name = "hpn with length";
        data->have_length = UTRUE;
        data->length=length;
        data->data=(char *)malloc(sizeof(char) * length);
        if (0 == length)
        {
            return ubjs_processor_hpn_complete(this);
        }
    }

    if (UFALSE == data->have_length)
    {
        ubjs_processor_ints(this, &nxt);
        return ubjs_parser_give_control(this->parser, nxt, 0);
    }

    return UR_OK;
}

void ubjs_processor_hpn_free(ubjs_processor *this)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;

    if (UTRUE == data->have_length)
    {
        free(data->data);
    }

    free(data);
    free(this);
}

ubjs_result ubjs_processor_hpn_read_char(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;

    data->data[data->done++] = (char)c;

    if (data->done == data->length)
    {
        return ubjs_processor_hpn_complete(this);
    }
    return UR_OK;
}

ubjs_result ubjs_processor_hpn_complete(ubjs_processor *this)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;
    ubjs_prmtv *product;
    ubjs_result ret;

    if (UR_ERROR == ubjs_prmtv_hpn(data->done, data->data, &product))
    {
        return ubjs_parser_emit_error(this->parser, 39, "Syntax error for high-precision number.");
    }

    ret = ubjs_parser_give_control(this->parser, this->parent, product);
    (this->free)(this);
    return ret;
}

ubjs_result ubjs_processor_array(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_array *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_array *)malloc(sizeof(struct ubjs_userdata_array));
    data->array=0;
    data->have_length=UFALSE;
    data->have_type=UFALSE;
    data->length=-1;
    data->type_factory=0;
    ubjs_prmtv_array(&(data->array));
    this->name = "array";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_array_got_control;
    this->read_char = 0;
    this->free=ubjs_processor_array_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_end(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "array end";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_array_end_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_count(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "optimized by count";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_array_count_got_control;
    this->read_char=0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "optimized by type";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char=ubjs_processor_array_type_read_char;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_type_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t c)
{
    ubjs_processor *parent = this->parent;
    ubjs_processor *next = 0;
    ubjs_userdata_array *data=(ubjs_userdata_array *)parent->userdata;
    int i;
    ubjs_result ret;

    ubjs_parser_error *error;
    char *message;
    unsigned int message_length;

    for (i=0; i<ubjs_processor_factories_top_len; i++)
    {
        ubjs_processor_factory *it=ubjs_processor_factories_top + i;

        if (it->marker == c)
        {
            data->have_type=UTRUE;
            data->type_factory = it;

            ubjs_processor_next_object(parent, ubjs_processor_factories_array_type,
                ubjs_processor_factories_array_type_len, &next);
            ret = ubjs_parser_give_control(this->parser, next, 0);
            (this->free)(this);
            return ret;
        }
    }

    ubjs_compact_sprintf(&message, &message_length, "At %d [%d] unknown marker", pos, c);
    ret = ubjs_parser_emit_error(this->parser, message_length, message);
    free(message);
    return ret;
}

ubjs_result ubjs_processor_array_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        unsigned int length;
        ubjs_prmtv_array_add_last(data->array, present);

        if (UTRUE == data->have_length)
        {
            ubjs_prmtv_array_get_length(data->array, &length);
            if (length == data->length)
            {
                return ubjs_processor_array_child_produced_end(this);
            }
        }
    }

    if (UTRUE == data->have_type)
    {
        (data->type_factory->create)(this, &nxt);
        return ubjs_parser_give_control(this->parser, nxt, 0);
    }

    if (UTRUE == data->have_length)
    {
        ubjs_processor_next_object(this, ubjs_processor_factories_array_count,
            ubjs_processor_factories_array_count_len, &nxt);
    }
    else
    {
        ubjs_processor_next_object(this, ubjs_processor_factories_array,
            ubjs_processor_factories_array_len, &nxt);
    }
    return ubjs_parser_give_control(this->parser, nxt, 0);
}

ubjs_result ubjs_processor_array_child_produced_end(ubjs_processor *this)
{
    ubjs_userdata_array *data;
    ubjs_result aret;

    data=(ubjs_userdata_array *)this->userdata;

    aret = ubjs_parser_give_control(this->parser, this->parent, data->array);
    data->array=0;
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_array_end_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_result ret = ubjs_processor_array_child_produced_end(this->parent);
    (this->free)(this);
    return ret;
}

ubjs_result ubjs_processor_array_count_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        unsigned int length = 0;
        ubjs_processor *parent = this->parent;
        ubjs_userdata_array *data;
        ubjs_result ret;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return UR_ERROR;
        }

        data = (ubjs_userdata_array *)parent->userdata;
        data->have_length = UTRUE;
        data->length=length;

        if (0 == length)
        {
            ret = ubjs_processor_array_child_produced_end(parent);
        }
        else
        {
            ret = ubjs_parser_give_control(this->parser, parent, 0);
        }
        (this->free)(this);
        return ret;
    }

    ubjs_processor_ints(this, &nxt);
    return ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_array_free(ubjs_processor *this)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;

    ubjs_prmtv_free(&(data->array));
    free(data);
    free(this);
}

ubjs_result ubjs_processor_object(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_object *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_object *)malloc(sizeof(struct ubjs_userdata_object));
    data->object=0;
    data->have_length=UFALSE;
    data->have_type=UFALSE;
    data->length=-1;
    data->type_factory=0;
    ubjs_prmtv_object(&(data->object));
    data->key_length=0;
    data->key=0;
    data->state=WANT_KEY_LENGTH;
    this->name = "object";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_object_got_control;
    this->free=ubjs_processor_object_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_end(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "object end";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_object_end_got_control;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_count(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "optimized by count";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_object_count_got_control;
    this->read_char=0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));
    this->name = "optimized by type";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char=ubjs_processor_object_type_read_char;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_type_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t c)
{
    ubjs_processor *parent = this->parent;
    ubjs_processor *next = 0;
    ubjs_userdata_object *data=(ubjs_userdata_object *)parent->userdata;
    int i;
    ubjs_result ret;

    ubjs_parser_error *error;
    char *message;
    unsigned int message_length;

    for (i=0; i<ubjs_processor_factories_top_len; i++)
    {
        ubjs_processor_factory *it=ubjs_processor_factories_top + i;

        if (it->marker == c)
        {
            data->have_type=UTRUE;
            data->type_factory = it;

             ubjs_processor_next_object(parent, ubjs_processor_factories_object_type,
                ubjs_processor_factories_object_type_len, &next);
            ret = ubjs_parser_give_control(this->parser, next, 0);
            (this->free)(this);
            return ret;
        }
    }

    ubjs_compact_sprintf(&message, &message_length, "At %d [%d] unknown marker", pos, c);
    ret = ubjs_parser_emit_error(this->parser, message_length, message);
    free(message);
    return ret;
}

ubjs_result ubjs_processor_object_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        unsigned int length = 0;

        switch (data->state)
        {
        case WANT_KEY_LENGTH:
            data->state=WANT_KEY;
            ubjs_processor_str(this, &nxt);
            return ubjs_parser_give_control(this->parser, nxt, present);

        case WANT_KEY:
            ubjs_prmtv_str_get_length(present, &(data->key_length));
            data->key=(char *)malloc(sizeof(char)*(data->key_length));
            ubjs_prmtv_str_copy_text(present, data->key);
            ubjs_prmtv_free(&present);
            data->state=WANT_VALUE;
            break;

        case WANT_VALUE:
            ubjs_prmtv_object_set(data->object, data->key_length, data->key, present);
            free(data->key);
            data->key=0;
            data->key_length=0;
            data->state=WANT_KEY_LENGTH;

            if (UTRUE == data->have_length)
            {
                ubjs_prmtv_object_get_length(data->object, &length);
                if (length == data->length)
                {
                    return ubjs_processor_object_child_produced_end(this);
                }
            }
            break;
        }
    }

    switch (data->state)
    {
    case WANT_KEY_LENGTH:
        if (UTRUE == data->have_length)
        {
            ubjs_processor_next_object(this, ubjs_processor_factories_object_count,
                ubjs_processor_factories_object_count_len, &nxt);
        }
        else
        {
            ubjs_processor_next_object(this, ubjs_processor_factories_object,
                ubjs_processor_factories_object_len, &nxt);
        }
        break;

    case WANT_VALUE:
        if (UTRUE == data->have_type)
        {
            (data->type_factory->create)(this, &nxt);
        }
        else
        {
            ubjs_processor_next_object(this, ubjs_processor_factories_top,
                ubjs_processor_factories_top_len, &nxt);
        }
        break;
    }

    return ubjs_parser_give_control(this->parser, nxt, 0);
}

ubjs_result ubjs_processor_object_child_produced_end(ubjs_processor *this)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_result aret;

    aret = ubjs_parser_give_control(this->parser, this->parent, data->object);
    data->object=0;
    (this->free)(this);
    return aret;
}

ubjs_result ubjs_processor_object_end_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_result ret = ubjs_processor_object_child_produced_end(this->parent);
    (this->free)(this);
    return ret;
}

ubjs_result ubjs_processor_object_count_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        unsigned int length = 0;
        ubjs_processor *parent = this->parent;
        ubjs_userdata_object *data;
        ubjs_result ret;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return UR_ERROR;
        }

        data = (ubjs_userdata_object *)parent->userdata;
        data->have_length = UTRUE;
        data->length=length;

        if (0 == length)
        {
            ret = ubjs_processor_object_child_produced_end(parent);
        }
        else
        {
            ret = ubjs_parser_give_control(this->parser, parent, 0);
        }
        (this->free)(this);
        return ret;
    }

    ubjs_processor_ints(this, &nxt);
    return ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_object_free(ubjs_processor *this)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    ubjs_prmtv_free(&(data->object));
    free(data->key);
    free(data);
    free(this);
}
