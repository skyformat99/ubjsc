#ifndef HAVE_UBJS_PARSER_INTERNAL
#define HAVE_UBJS_PARSER_INTERNAL

#include "../include/ubjs_common.h"
#include "../include/ubjs_parser.h"

typedef struct ubjs_processor ubjs_processor;
typedef struct ubjs_processor_factory ubjs_processor_factory;

typedef ubjs_result (*ubjs_processor_gained_control)(ubjs_processor *);
typedef ubjs_result (*ubjs_processor_read_char)(ubjs_processor *,unsigned int, uint8_t);
typedef ubjs_result (*ubjs_processor_child_produced_object)(ubjs_processor *, ubjs_prmtv *);
typedef void (*ubjs_processor_free)(ubjs_processor *);

struct ubjs_processor
{
    ubjs_processor *parent;
    ubjs_parser *parser;
    void *userdata;

    ubjs_processor_gained_control gained_control;
    ubjs_processor_read_char read_char;
    ubjs_processor_child_produced_object child_produced_object;
    ubjs_processor_free free;
};

typedef ubjs_result (*ubjs_processor_factory_create)(ubjs_processor *, ubjs_processor **);
struct ubjs_processor_factory
{
    int marker;
    ubjs_processor_factory_create create;
};

extern int ubjs_processor_factories_top_len;
extern ubjs_processor_factory ubjs_processor_factories_top[];

extern int ubjs_processor_factories_array_len;
extern ubjs_processor_factory ubjs_processor_factories_array[];

extern int ubjs_processor_factories_object_len;
extern ubjs_processor_factory ubjs_processor_factories_object[];

extern int ubjs_processor_factories_ints_len;
extern ubjs_processor_factory ubjs_processor_factories_ints[];

ubjs_result ubjs_parser_give_control(ubjs_parser *,ubjs_processor *);

ubjs_result ubjs_processor_top(ubjs_parser *, ubjs_processor **);
ubjs_result ubjs_processor_ints(ubjs_processor *, ubjs_processor **);

ubjs_result ubjs_processor_next_object(ubjs_processor *, ubjs_processor_factory *factories, int factories_len, ubjs_processor **);

ubjs_result ubjs_processor_null(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_noop(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_true(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_false(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int8(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_uint8(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int16(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int32(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int64(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_float32(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_float64(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_char(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_str(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_end(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object_end(ubjs_processor *, ubjs_processor **);

ubjs_result ubjs_parser_error_new(char *message,unsigned int len, ubjs_parser_error **);
ubjs_result ubjs_parser_error_free(ubjs_parser_error **);

#endif

