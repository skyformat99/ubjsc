#include <stdlib.h>

#include "test_parser_tools.h"

void wrapped_parser_context_new(wrapped_parser_context **pthis)
{
    wrapped_parser_context *this;
    this=(wrapped_parser_context *)malloc(sizeof(struct wrapped_parser_context));
    this->calls_parsed = 0;
    this->calls_error = 0;
    this->calls_free = 0;

    test_list_new(&(this->calls_parsed));
    test_list_new(&(this->calls_error));
    test_list_new(&(this->calls_free));
    *pthis=this;
}

void wrapped_parser_context_free(wrapped_parser_context **pthis)
{
    wrapped_parser_context *this=*pthis;
    test_list_free(&(this->calls_parsed));
    test_list_free(&(this->calls_error));
    test_list_free(&(this->calls_free));
    free(this);
    *pthis=0;
}

void wrapped_parser_context_reset(wrapped_parser_context *this)
{
    test_list_free(&(this->calls_parsed));
    test_list_free(&(this->calls_error));
    test_list_free(&(this->calls_free));

    test_list_new(&(this->calls_parsed));
    test_list_new(&(this->calls_error));
    test_list_new(&(this->calls_free));
}

void parser_context_parsed(ubjs_parser_context *context, ubjs_prmtv *object)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)context->userdata;
    test_list_add(ctx->calls_parsed, object, (test_list_free_f)ubjs_prmtv_free);
}

static void __pfree(void **pthis) {
    free(*pthis);
}

void parser_context_error(ubjs_parser_context *context, ubjs_parser_error *error)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)context->userdata;
    unsigned int length;
    char *message;

    if(UR_OK == ubjs_parser_error_get_message_length(error, &length)) {
        message=(char *)malloc(sizeof(char) * (length+1));

        if(UR_OK == ubjs_parser_error_get_message_text(error, message)) {
            message[length]=0;
            test_list_add(ctx->calls_error, message, (test_list_free_f)__pfree);
        }
    }
}

void parser_context_free(ubjs_parser_context *context)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)context->userdata;
    test_list_add(ctx->calls_free, 0,0);
}
