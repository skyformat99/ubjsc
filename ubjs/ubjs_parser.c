#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ubjs_parser.h"
#include "ubjs_parser_internal.h"

typedef struct __ubjs_userdata_longint __ubjs_userdata_longint;
typedef struct __ubjs_userdata_str __ubjs_userdata_str;
typedef struct __ubjs_processor_next_objext __ubjs_processor_next_objext;

int ubjs_processor_factories_top_len=13;
ubjs_processor_factory ubjs_processor_factories_top[] =
{
    {MARKER_CHAR, (ubjs_processor_factory_create)ubjs_processor_char},
    {MARKER_FLOAT64, (ubjs_processor_factory_create)ubjs_processor_float64},
    {MARKER_FALSE, (ubjs_processor_factory_create)ubjs_processor_false},
    {MARKER_INT16, (ubjs_processor_factory_create)ubjs_processor_int16},
    {MARKER_INT64, (ubjs_processor_factory_create)ubjs_processor_int64},
    {MARKER_NOOP, (ubjs_processor_factory_create)ubjs_processor_noop},
    {MARKER_STR, (ubjs_processor_factory_create)ubjs_processor_str},
    {MARKER_TRUE, (ubjs_processor_factory_create)ubjs_processor_true},
    {MARKER_UINT8, (ubjs_processor_factory_create)ubjs_processor_uint8},
    {MARKER_NULL, (ubjs_processor_factory_create)ubjs_processor_null},
    {MARKER_FLOAT32, (ubjs_processor_factory_create)ubjs_processor_float32},
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

static ubjs_result __ubjs_processor_top_gained_control(ubjs_processor *);
static void __ubjs_processor_top_child_produced_object(ubjs_processor *, ubjs_object *);

static ubjs_result __ubjs_processor_next_object_gained_control(ubjs_processor *);
static ubjs_result __ubjs_processor_next_object_read_char(ubjs_processor *,unsigned int,uint8_t);
static void __ubjs_processor_next_object_child_produced_object(ubjs_processor *,
        ubjs_object *);

static ubjs_result __ubjs_processor_no_length_gained_control(ubjs_processor *this);

static ubjs_result __ubjs_processor_int8_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_uint8_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_char_read_char(ubjs_processor *,unsigned int,uint8_t);

static void __ubjs_processor_longint_free(ubjs_processor *);
static ubjs_result __ubjs_processor_int16_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_int32_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_int64_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_float32_read_char(ubjs_processor *,unsigned int,uint8_t);
static ubjs_result __ubjs_processor_float64_read_char(ubjs_processor *,unsigned int,uint8_t);

static ubjs_result __ubjs_processor_str_gained_control(ubjs_processor *);
static void __ubjs_processor_str_free(ubjs_processor *);
static ubjs_result __ubjs_processor_str_read_char(ubjs_processor *,unsigned int,uint8_t);
static void __ubjs_processor_str_got_length(ubjs_processor *,unsigned int);
static void __ubjs_processor_str_complete(ubjs_processor *);
static void __ubjs_processor_str_child_produced_object(ubjs_processor *, ubjs_object *);

struct ubjs_parser_error {
    char *message;
    unsigned int message_length;
};

struct ubjs_parser
{
    ubjs_parser_context *context;
    ubjs_processor *processor;
};

struct __ubjs_processor_next_objext
{
    ubjs_processor super;
    ubjs_processor_factory *factories;
    int factories_len;
};

struct __ubjs_userdata_longint {
    uint8_t *data;
    unsigned int done;
};

struct __ubjs_userdata_str {
    ubjs_bool have_length;
    unsigned int length;
    unsigned int done;
    char *data;
};

ubjs_result ubjs_parser_error_new(char *message,unsigned int len, ubjs_parser_error **pthis) {
    ubjs_parser_error *this;

    if(0 == message  || 0 == pthis) {
        return UR_ERROR;
    }

    this=(ubjs_parser_error *)malloc(sizeof(struct ubjs_parser_error));
    if(0 == this) {
        return UR_ERROR;
    }

    this->message=(char *)malloc(sizeof(char)*len);
    if(0 == this->message) {
        free(this);
        return UR_ERROR;
    }

    strncpy(this->message,message,len);
    this->message_length=len;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_error_free(ubjs_parser_error **pthis) {
    ubjs_parser_error *this;

    if(0 == pthis) {
        return UR_ERROR;
    }

    this=*pthis;
    free(this->message);
    free(this);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *this,unsigned int *length) {
    if(0 == this) {
        return UR_ERROR;
    }

    *length=this->message_length;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *this,char *message) {
    if(0 == this || 0 == message) {
        return UR_ERROR;
    }

    strncpy(message,this->message,this->message_length);
    return UR_OK;
}

ubjs_result ubjs_parser_alloc(ubjs_parser **pthis, ubjs_parser_context *context)
{
    ubjs_parser *this;
    ubjs_processor *processor;

    if(0 == pthis || 0 == context)
    {
        return UR_ERROR;
    }

    if(0 == context->parsed || 0 == context->free || 0 == context->error) {
        return UR_ERROR;
    }

    this = (ubjs_parser *)malloc(sizeof(struct ubjs_parser));
    if(this==0)
    {
        return UR_ERROR;
    }

    if(UR_ERROR == ubjs_processor_top(this, &(this->processor))) {
        free(this);
        return UR_ERROR;
    }

    this->context=context;

    // Always processor_top, they have control
    (this->processor->gained_control)(this->processor);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_free(ubjs_parser **pthis)
{
    ubjs_parser *this;
    ubjs_processor *processor;
    ubjs_processor *parent_processor;

    if(0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;

    for(processor=this->processor; 0 != processor;)
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

ubjs_result ubjs_parser_get_context(ubjs_parser *this,ubjs_parser_context **context)
{
    if(0 == this || 0 == context)
    {
        return UR_ERROR;
    }

    *context=this->context;
    return UR_OK;
}

ubjs_result ubjs_parser_parse(ubjs_parser *this,uint8_t *data,unsigned int length)
{
    unsigned int i;

    ubjs_parser_error *error;
    char *message;
    int message_length;

    if(0 == this || data == 0)
    {
        return UR_ERROR;
    }

    if(0 == length)
    {
        return UR_OK;
    }

    for(i=0; i<length; i++)
    {
        if(0 == this->processor) {
            if(UR_OK == ubjs_compact_sprintf(&message, &message_length, "At %d [%d] no processor", i, data[i])) {
                if(UR_OK == ubjs_parser_error_new(message, message_length, &error)) {
                    (this->context->error)(this->context, error);
                    ubjs_parser_error_free(&error);
                }
                free(message);
            }
            return UR_ERROR;
        }

        if(0 == this->processor->read_char) {
            if(UR_OK == ubjs_compact_sprintf(&message, &message_length, "At %d [%d] processor for cannot read chars", i, data[i])) {
                if(UR_OK == ubjs_parser_error_new(message, message_length, &error)) {
                    (this->context->error)(this->context, error);
                    ubjs_parser_error_free(&error);
                }
                free(message);
            }
            return UR_ERROR;
        }

        if(UR_ERROR == (this->processor->read_char)(this->processor, i, data[i])) {
            return UR_ERROR;
        }
    }

    return UR_OK;
}

ubjs_result ubjs_parser_give_control(ubjs_parser *this,ubjs_processor *processor)
{
    this->processor=processor;

    if(0 != processor->gained_control && UR_ERROR == (processor->gained_control)(processor)) {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_processor_top(ubjs_parser *parser, ubjs_processor**pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    this->parent=0;
    this->userdata=0;
    this->parser=parser;
    this->gained_control=__ubjs_processor_top_gained_control;
    this->read_char = 0;
    this->child_produced_object = __ubjs_processor_top_child_produced_object;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_top_gained_control(ubjs_processor *this)
{
    ubjs_processor *nxt = 0;

    if(UR_ERROR == ubjs_processor_next_object(this, ubjs_processor_factories_top, ubjs_processor_factories_top_len,
            &nxt)) {
        return UR_ERROR;
    }

    if(UR_ERROR == ubjs_parser_give_control(this->parser, nxt)) {
        return UR_ERROR;
    }
    return UR_OK;
}

static void __ubjs_processor_top_child_produced_object(ubjs_processor *this, ubjs_object *object)
{
    ubjs_parser_give_control(this->parser, this);
    (this->parser->context->parsed)(this->parser->context, object);
}

ubjs_result ubjs_processor_ints(ubjs_processor *parent,ubjs_processor **pthis) {
    return ubjs_processor_next_object(parent, ubjs_processor_factories_ints, ubjs_processor_factories_ints_len, pthis);
}

ubjs_result ubjs_processor_next_object(ubjs_processor *parent, ubjs_processor_factory *factories, int factories_len,
                                       ubjs_processor **pthis)
{
    __ubjs_processor_next_objext *this;
    this = (__ubjs_processor_next_objext *)malloc(sizeof(struct __ubjs_processor_next_objext));

    if(0 == this)
    {
        return UR_ERROR;
    }

    this->super.parent=parent;
    this->super.parser=parent->parser;
    this->super.userdata=0;
    this->super.gained_control=0;
    this->super.read_char = __ubjs_processor_next_object_read_char;
    this->super.child_produced_object = __ubjs_processor_next_object_child_produced_object;
    this->super.free=(ubjs_processor_free)free;
    this->factories=factories;
    this->factories_len=factories_len;

    *pthis=(ubjs_processor *)this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_next_object_read_char(ubjs_processor *this,unsigned int pos, uint8_t c)
{
    __ubjs_processor_next_objext *sub=(__ubjs_processor_next_objext *)this;
    int i;
    ubjs_processor *next;

    ubjs_parser_error *error;
    char *message;
    int message_length;

    for(i=0; i<sub->factories_len; i++)
    {
        ubjs_processor_factory *it=sub->factories + i;

        if(it->marker == c)
        {
            if(UR_ERROR == (it->create)(this, &next)) {
                if(UR_OK == ubjs_compact_sprintf(&message, &message_length,
                                                 "At %d [%d] processor returned UR_ERROR",
                                                 i, c)) {
                    if(UR_OK == ubjs_parser_error_new(message, message_length, &error)) {
                        (this->parser->context->error)(this->parser->context, error);
                        ubjs_parser_error_free(&error);
                    }
                    free(message);
                }
                return UR_ERROR;
            }

            ubjs_parser_give_control(this->parser, next);
            return UR_OK;
        }
    }

    if(UR_OK == ubjs_compact_sprintf(&message, &message_length, "At %d [%d] unknown marker", i, c)) {
        if(UR_OK == ubjs_parser_error_new(message, message_length, &error)) {
            (this->parser->context->error)(this->parser->context, error);
            ubjs_parser_error_free(&error);
        }
        free(message);
    }

    return UR_ERROR;
}

static void __ubjs_processor_next_object_child_produced_object(ubjs_processor *this, ubjs_object *object)
{
    ubjs_parser_give_control(this->parser, this);
    (this->parent->child_produced_object)(this->parent, object);
    (this->free)(this);
}

ubjs_result ubjs_processor_null(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_object_null();
    this->gained_control=__ubjs_processor_no_length_gained_control;
    this->read_char = 0;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_noop(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_object_noop();
    this->gained_control=__ubjs_processor_no_length_gained_control;
    this->read_char = 0;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_true(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_object_true();
    this->gained_control=__ubjs_processor_no_length_gained_control;
    this->read_char = 0;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}


ubjs_result ubjs_processor_false(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_object_false();
    this->gained_control=__ubjs_processor_no_length_gained_control;
    this->read_char = 0;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_no_length_gained_control(ubjs_processor *this)
{
    ubjs_object *ret=(ubjs_object *)this->userdata;
    (this->parent->child_produced_object)(this->parent, ret);
    (this->free)(this);

    return UR_OK;
}


ubjs_result ubjs_processor_int8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->gained_control=0;
    this->read_char = __ubjs_processor_int8_read_char;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_int8_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    uint8_t value[]= {achar};
    uint8_t value2[1];

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_object *ret;

    ubjs_object_int8(*((int8_t *)value2), &ret);

    (this->parent->child_produced_object)(this->parent, ret);
    (this->free)(this);

    return UR_OK;
}

ubjs_result ubjs_processor_uint8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->gained_control=0;
    this->read_char = __ubjs_processor_uint8_read_char;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_uint8_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    uint8_t value[]= {achar};
    uint8_t value2[1];

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_object *ret;

    ubjs_object_uint8(*((uint8_t *)value2), &ret);

    (this->parent->child_produced_object)(this->parent, ret);
    (this->free)(this);

    return UR_OK;
}

ubjs_result ubjs_processor_char(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return 0;
    }

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->gained_control=0;
    this->read_char = __ubjs_processor_char_read_char;
    this->child_produced_object = 0;
    this->free=(ubjs_processor_free)free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_char_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    uint8_t value[]= {achar};
    uint8_t value2[1];

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_object *ret;

    ubjs_object_char(*((unsigned char *)value2), &ret);

    (this->parent->child_produced_object)(this->parent, ret);
    (this->free)(this);

    return UR_OK;
}

ubjs_result ubjs_processor_int16(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_longint *)malloc(sizeof(struct __ubjs_userdata_longint));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 2);
    if(0 == data->data) {
        free(data);
        free(this);
        return UR_ERROR;
    }

    data->done=0;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=0;
    this->read_char = __ubjs_processor_int16_read_char;
    this->child_produced_object = 0;
    this->free=__ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_int16_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    uint8_t value2[2];

    data->data[data->done++] = achar;
    if(2 <= data->done) {
        ubjs_endian_convert_big_to_native(data->data, value2, 2);
        ubjs_object *ret;

        ubjs_object_int16(*((int16_t *)value2), &ret);

        (this->parent->child_produced_object)(this->parent, ret);
        (this->free)(this);
    }

    return UR_OK;
}

static void __ubjs_processor_longint_free(ubjs_processor *this) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    free(data->data);
    free(this->userdata);
    free(this);
}

ubjs_result ubjs_processor_int32(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_longint *)malloc(sizeof(struct __ubjs_userdata_longint));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 4);
    if(0 == data->data) {
        free(data);
        free(this);
        return UR_ERROR;
    }

    data->done=0;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=0;
    this->read_char = __ubjs_processor_int32_read_char;
    this->child_produced_object = 0;
    this->free=__ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}


static ubjs_result __ubjs_processor_int32_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    uint8_t value2[4];

    data->data[data->done++] = achar;
    if(4 <= data->done) {
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_object *ret;

        ubjs_object_int32(*((int32_t *)value2), &ret);

        (this->parent->child_produced_object)(this->parent, ret);
        (this->free)(this);
    }

    return UR_OK;
}

ubjs_result ubjs_processor_int64(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_longint *)malloc(sizeof(struct __ubjs_userdata_longint));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 8);
    if(0 == data->data) {
        free(data);
        free(this);
        return UR_ERROR;
    }

    data->done=0;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=0;
    this->read_char = __ubjs_processor_int64_read_char;
    this->child_produced_object = 0;
    this->free=__ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_int64_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    uint8_t value2[8];

    data->data[data->done++] = achar;
    if(8 <= data->done) {
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_object *ret;

        ubjs_object_int64(*((int64_t *)value2), &ret);

        (this->parent->child_produced_object)(this->parent, ret);
        (this->free)(this);
    }

    return UR_OK;
}

ubjs_result ubjs_processor_float32(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_longint *)malloc(sizeof(struct __ubjs_userdata_longint));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 4);
    if(0 == data->data) {
        free(data);
        free(this);
        return UR_ERROR;
    }

    data->done=0;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=0;
    this->read_char = __ubjs_processor_float32_read_char;
    this->child_produced_object = 0;
    this->free=__ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_float32_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    uint8_t value2[4];

    data->data[data->done++] = achar;
    if(4 <= data->done) {
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_object *ret;

        ubjs_object_float32(*((float32_t *)value2), &ret);

        (this->parent->child_produced_object)(this->parent, ret);
        (this->free)(this);
    }

    return UR_OK;
}

ubjs_result ubjs_processor_float64(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_longint *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_longint *)malloc(sizeof(struct __ubjs_userdata_longint));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->data=(uint8_t *)malloc(sizeof(uint8_t) * 8);
    if(0 == data->data) {
        free(data);
        free(this);
        return UR_ERROR;
    }

    data->done=0;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=0;
    this->read_char = __ubjs_processor_float64_read_char;
    this->child_produced_object = 0;
    this->free=__ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_float64_read_char(ubjs_processor *this,unsigned int pos,uint8_t achar) {
    __ubjs_userdata_longint *data=(__ubjs_userdata_longint *)this->userdata;
    uint8_t value2[8];

    data->data[data->done++] = achar;
    if(8 <= data->done) {
        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        ubjs_object *ret;

        ubjs_object_float64(*((float64_t *)value2), &ret);

        (this->parent->child_produced_object)(this->parent, ret);
        (this->free)(this);
    }

    return UR_OK;
}

ubjs_result ubjs_processor_str(ubjs_processor *parent, ubjs_processor **pthis) {
    ubjs_processor *this;
    __ubjs_userdata_str *data;

    this = (ubjs_processor *)malloc(sizeof(struct ubjs_processor));

    if(0 == this)
    {
        return UR_ERROR;
    }

    data=(__ubjs_userdata_str *)malloc(sizeof(struct __ubjs_userdata_str));
    if(0 == data) {
        free(this);
        return UR_ERROR;
    }

    data->have_length=UFALSE;
    data->data=0;
    data->done=0;
    data->length=-1;

    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->gained_control=__ubjs_processor_str_gained_control;
    this->read_char = __ubjs_processor_str_read_char;
    this->child_produced_object = __ubjs_processor_str_child_produced_object;
    this->free=__ubjs_processor_str_free;

    *pthis=this;
    return UR_OK;
}

static ubjs_result __ubjs_processor_str_gained_control(ubjs_processor *this)
{
    ubjs_processor *nxt = 0;
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;

    if(UFALSE == data->have_length) {

        if(UR_ERROR == ubjs_processor_ints(this, &nxt)) {
            return UR_ERROR;
        }

        if(UR_ERROR == ubjs_parser_give_control(this->parser, nxt)) {
            return UR_ERROR;
        }
    }

    return UR_OK;
}

static void __ubjs_processor_str_free(ubjs_processor *this) {
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;

    if(UTRUE == data->have_length) {
        free(data->data);
    }

    free(this);
}

static ubjs_result __ubjs_processor_str_read_char(ubjs_processor *this,unsigned int pos,uint8_t c) {
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;

    ubjs_parser_error *error;
    char *message;
    int message_length;

    if(UFALSE == data->have_length) {
        if(UR_OK == ubjs_compact_sprintf(&message, &message_length, "At %d [%d] processor_str does not have length, yet in str_read_char", pos, c)) {
            if(UR_OK == ubjs_parser_error_new(message, message_length, &error)) {
                (this->parser->context->error)(this->parser->context, error);
                ubjs_parser_error_free(&error);
            }
            free(message);
        }

        return UR_ERROR;
    }

    data->data[data->done++] = (char)c;

    if(data->done == data->length) {
        __ubjs_processor_str_complete(this);
    }
    return UR_OK;
}

static void __ubjs_processor_str_complete(ubjs_processor *this) {
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;
    ubjs_object *product;

    if(UR_ERROR == ubjs_object_str(data->done, data->data, &product)) {
        // @todo
        return;
    }

    (this->parent->child_produced_object)(this->parent, product);
    (this->free)(this);
}

static void __ubjs_processor_str_got_length(ubjs_processor *this,unsigned int length) {
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;

    ubjs_parser_error *error;
    char *message;
    ubjs_bool ret;

    data->have_length=UTRUE;
    data->length=length;
    data->data=(char *)malloc(sizeof(char) * length);

    if(0 == data->data) {
        // @todo
        return;
    }

    if(0 == length) {
        __ubjs_processor_str_complete(this);
        return;
    }

    if(UR_ERROR == ubjs_parser_give_control(this->parser, this)) {
        message = "Processor_str got length and cannot recover control";
        if(UR_OK == ubjs_parser_error_new(message, strlen(message), &error)) {
            (this->parser->context->error)(this->parser->context, error);
            ubjs_parser_error_free(&error);
        }
    }
}

static void __ubjs_processor_str_child_produced_object(ubjs_processor *this, ubjs_object *obj) {
    __ubjs_userdata_str *data=(__ubjs_userdata_str *)this->userdata;

    ubjs_parser_error *error;
    char *message;
    ubjs_bool ret;

    int8_t v8;
    uint8_t vu8;
    int16_t v16;
    int32_t v32;
    int64_t v64;

    if(UTRUE == data->have_length) {
        message = "Processor_str got length, yet already have length";
    } else {
        if(UR_OK == ubjs_object_is_int8(obj, &ret) && UTRUE == ret) {
            if(UR_OK == ubjs_object_int8_get(obj, &v8)) {
                if(0 <= v8) {
                    __ubjs_processor_str_got_length(this, (unsigned int)v8);
                    return;
                }
                message = "Processor_str got int8 negative length";
            }
            message = "Processor_str got int8 length but cannot get value.";
        } else if(UR_OK == ubjs_object_is_uint8(obj, &ret) && UTRUE == ret) {
            if(UR_OK == ubjs_object_uint8_get(obj, &vu8)) {
                __ubjs_processor_str_got_length(this, (unsigned int)vu8);
                return;
            }
            message = "Processor_str got uint8 length but cannot get value.";
        } else if(UR_OK == ubjs_object_is_int16(obj, &ret) && UTRUE == ret) {
            if(UR_OK == ubjs_object_int16_get(obj, &v16)) {
                if(0 <= v8) {
                    __ubjs_processor_str_got_length(this, (unsigned int)v16);
                    return;
                }
                message = "Processor_str got int16 negative length";
            }
            message = "Processor_str got int16 length but cannot get value.";
        } else if(UR_OK == ubjs_object_is_int32(obj, &ret) && UTRUE == ret) {
            if(UR_OK == ubjs_object_int32_get(obj, &v32)) {
                if(0 <= v8) {
                    __ubjs_processor_str_got_length(this, (unsigned int)v32);
                    return;
                }
                message = "Processor_str got int32 negative length";
            }
            message = "Processor_str got int16 length but cannot get value.";
        }
        else {
            // This should not happen...
            message = "Processor_str got non-int length!!!";
        }
    }

    if(UR_OK == ubjs_parser_error_new(message, strlen(message), &error)) {
        (this->parser->context->error)(this->parser->context, error);
        ubjs_parser_error_free(&error);
    }
}
