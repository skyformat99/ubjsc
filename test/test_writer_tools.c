#include <stdlib.h>
#include <string.h>

#include "test_writer_tools.h"

static void would_write_print(would_write_call *);

void would_write_call_new(uint8_t *data,unsigned int len, would_write_call **pthis)
{
    would_write_call *this;
    this=(would_write_call *)malloc(sizeof(struct would_write_call));

    this->len=len;
    this->data=(uint8_t *)malloc(sizeof(uint8_t)*len);
    memcpy(this->data, data, sizeof(uint8_t) * len);

    *pthis=this;
}

void would_write_call_free(would_write_call **pthis)
{
    would_write_call *this=*pthis;

    free(this->data);
    free(this);

    *pthis=0;
}

void wrapped_writer_context_new(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this;
    this=(wrapped_writer_context *)malloc(sizeof(struct wrapped_writer_context));

    test_list_new(&(this->calls_would_write));
    test_list_new(&(this->calls_free));

    *pthis=this;
}

void wrapped_writer_context_free(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this = *pthis;

    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_free));

    free(this);
    *pthis=0;
}

void wrapped_writer_context_reset(wrapped_writer_context *this)
{
    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_free));

    test_list_new(&(this->calls_would_write));
    test_list_new(&(this->calls_free));
}

void writer_context_would_write(ubjs_writer_context *context,uint8_t *data,unsigned int len)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    would_write_call *call;
    would_write_call_new(data, len, &call);
    test_list_add(ctx->calls_would_write, call, (test_list_free_f)would_write_call_free);

    would_write_print(call);
}

#define __WOULD_WRITE_PRINT_OFFSET 8
static void would_write_print(would_write_call *this) {
    /*
    unsigned int i, j;
    unsigned int i_max = (this->len)/__WOULD_WRITE_PRINT_OFFSET;

    printf("Would write %d bytes:\n", this->len);
    for(i=0; i<i_max; i++) {
        printf("%d | ", i*__WOULD_WRITE_PRINT_OFFSET);
        for(j=0; j<__WOULD_WRITE_PRINT_OFFSET; j++) {
            printf("%d ", this->data[i*__WOULD_WRITE_PRINT_OFFSET+j]);
        }
        printf("\t");
        for(j=0; j<__WOULD_WRITE_PRINT_OFFSET; j++) {
            printf("[%c]", this->data[i*__WOULD_WRITE_PRINT_OFFSET+j]);
        }

        printf("\n");
    }
    printf("\n");
    */
}

void writer_context_free(ubjs_writer_context *context)
{
    wrapped_writer_context *ctx=(wrapped_writer_context *)context->userdata;

    test_list_add(ctx->calls_free, 0, 0);
}
