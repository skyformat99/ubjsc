#include <stdlib.h>

#include "test_parser_tools.h"

wrapped_parser_context *wrapped_parser_context_new()
{
    wrapped_parser_context *this;
    this=(wrapped_parser_context *)malloc(sizeof(struct wrapped_parser_context));
    this->calls_parsed=test_list_new();
    this->calls_free=test_list_new();
    return this;
}

void wrapped_parser_context_free(wrapped_parser_context *this)
{
    test_list_free(this->calls_parsed);
    test_list_free(this->calls_free);
    free(this);
}

void wrapped_parser_context_reset(wrapped_parser_context *this)
{
    test_list_free(this->calls_parsed);
    test_list_free(this->calls_free);

    this->calls_parsed=test_list_new();
    this->calls_free=test_list_new();
}

void wrapper_free(ubjs_object *object)
{
    ubjs_object_free(&object);
}

void parser_context_parsed(ubjs_parser_context *context, ubjs_object *object)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)context->userdata;
    test_list_add(ctx->calls_parsed, object, (test_list_free_f)wrapper_free);
}

void parser_context_free(ubjs_parser_context *context)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)context->userdata;
    test_list_add(ctx->calls_free, 0,0);
}
