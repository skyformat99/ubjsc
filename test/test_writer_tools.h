#ifndef HAVE_TEST_WRITER_TOOLS
#define HAVE_TEST_WRITER_TOOLS

#include "../include/ubjs.h"
#include "test_list.h"

typedef struct wrapped_writer_context wrapped_writer_context;
typedef struct would_write_call would_write_call;

struct would_write_call
{
    uint8_t *data;
    unsigned int len;
};

would_write_call *would_write_call_new(uint8_t *,unsigned int);
void would_write_call_free(would_write_call *);

struct wrapped_writer_context
{
    test_list *calls_would_write;
    test_list *calls_free;
};

wrapped_writer_context *wrapped_writer_context_new();
void wrapped_writer_context_free(wrapped_writer_context *this);
void wrapped_writer_context_reset(wrapped_writer_context *this);

void writer_context_would_write(ubjs_writer_context *context,uint8_t *data,unsigned int len);
void writer_context_free(ubjs_writer_context *context);

#endif
