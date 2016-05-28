#ifndef HAVE_UBJS_PARSER
#define HAVE_UBJS_PARSER

#include "ubjs_common.h"
#include "ubjs_objects.h"

typedef struct ubjs_parser ubjs_parser;
typedef struct ubjs_parser_error ubjs_parser_error;
typedef struct ubjs_parser_context ubjs_parser_context;

typedef void (*ubjs_parser_context_parsed)(ubjs_parser_context *,ubjs_object *);
typedef void (*ubjs_parser_context_error)(ubjs_parser_context *,ubjs_parser_error *);
typedef void (*ubjs_parser_context_free)(ubjs_parser_context *);

struct ubjs_parser_error;

ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *,unsigned int *);
ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *,char *);

struct ubjs_parser_context
{
    void *userdata;
    ubjs_parser_context_parsed parsed;
    ubjs_parser_context_error error;
    ubjs_parser_context_free free;
};

struct ubjs_parser;

ubjs_result ubjs_parser_alloc(ubjs_parser **, ubjs_parser_context *);
ubjs_result ubjs_parser_free(ubjs_parser **);

ubjs_result ubjs_parser_get_context(ubjs_parser *,ubjs_parser_context **);
ubjs_result ubjs_parser_parse(ubjs_parser *,uint8_t *,unsigned int);

#endif

