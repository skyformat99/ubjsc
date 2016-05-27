#ifndef HAVE_UBJS_WRITER
#define HAVE_UBJS_WRITER

#include "ubjs_common.h"
#include "ubjs_objects.h"

typedef struct ubjs_writer ubjs_writer;
typedef struct ubjs_writer_context ubjs_writer_context;

typedef void (*ubjs_writer_context_would_write)(ubjs_writer_context *,uint8_t *,unsigned int);
typedef void (*ubjs_writer_context_free)(ubjs_writer_context *);

struct ubjs_writer_context
{
    void *userdata;
    ubjs_writer_context_would_write would_write;
    ubjs_writer_context_free free;
};

struct ubjs_writer;

ubjs_result ubjs_writer_alloc(ubjs_writer **,ubjs_writer_context *);
ubjs_result ubjs_writer_free(ubjs_writer **);

ubjs_result ubjs_writer_get_context(ubjs_writer *,ubjs_writer_context **);
ubjs_result ubjs_writer_write(ubjs_writer *,ubjs_object *);

#endif

