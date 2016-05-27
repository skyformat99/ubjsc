#include <stdlib.h>
#include <string.h>

#include "test_writer_tools.h"

would_write_call *would_write_call_new(uint8_t *data,unsigned int len)
{
    would_write_call *this;
    this=(would_write_call *)malloc(sizeof(struct would_write_call));
    if(0 == this)
    {
        return 0;
    }

    this->len=len;
    this->data=(uint8_t *)malloc(sizeof(uint8_t)*len);
    memcpy(this->data, data, sizeof(uint8_t) * len);

    return this;
}

void would_write_call_free(would_write_call *this)
{
    free(this->data);
    free(this);
}

wrapped_writer_context *wrapped_writer_context_new()
{
    wrapped_writer_context *this;
    this=(wrapped_writer_context *)malloc(sizeof(struct wrapped_writer_context));

    this->calls_would_write=test_list_new();
    this->calls_free=test_list_new();

    return this;
}

void wrapped_writer_context_free(wrapped_writer_context *this)
{
    test_list_free(this->calls_would_write);
    test_list_free(this->calls_free);

    free(this);
}

void wrapped_writer_context_reset(wrapped_writer_context *this)
{
    test_list_free(this->calls_would_write);
    test_list_free(this->calls_free);

    this->calls_would_write=test_list_new();
    this->calls_free=test_list_new();
}

void writer_context_would_write(ubjs_writer_context *context,uint8_t *data,unsigned int len)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    would_write_call *call=would_write_call_new(data, len);
    test_list_add(ctx->calls_would_write, call, (test_list_free_f)would_write_call_free);
}

void writer_context_free(ubjs_writer_context *context)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    test_list_add(ctx->calls_free, 0, 0);
}
