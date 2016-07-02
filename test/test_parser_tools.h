#ifndef HAVE_TEST_PARSER_TOOLS
#define HAVE_TEST_PARSER_TOOLS

#include "../include/ubjs.h"
#include "test_list.h"

typedef struct wrapped_parser_context wrapped_parser_context;

struct wrapped_parser_context
{
    test_list *calls_parsed;
    test_list *calls_error;
    test_list *calls_free;
};

void wrapped_parser_context_new(wrapped_parser_context **);
void wrapped_parser_context_free(wrapped_parser_context **);
void wrapped_parser_context_reset(wrapped_parser_context *);

void wrapper_free(ubjs_prmtv *object);
void parser_context_parsed(ubjs_parser_context *context, ubjs_prmtv *object);
void parser_context_error(ubjs_parser_context *context, ubjs_parser_error *error);
void parser_context_free(ubjs_parser_context *context);

#endif
