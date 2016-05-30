#ifndef HAVE_UBJS_WRITER_INTERNAL
#define HAVE_UBJS_WRITER_INTERNAL

#include "../include/ubjs_writer.h"

typedef struct ubjs_writer_strategy_runner ubjs_writer_strategy_runner;
typedef void (*ubjs_writer_strategy_runner_run)(ubjs_writer_strategy_runner *,uint8_t *);
typedef void (*ubjs_writer_strategy_runner_free)(ubjs_writer_strategy_runner *);
typedef ubjs_result (*ubjs_writer_strategy)(ubjs_object *, ubjs_writer_strategy_runner **);

struct ubjs_writer_strategy_runner {
    void *userdata;
    ubjs_object *object;
    unsigned int length;

    ubjs_writer_strategy_runner_run run;
    ubjs_writer_strategy_runner_free free;
};

extern int ubjs_writer_strategies_top_len;
extern ubjs_writer_strategy ubjs_writer_strategies_top[];

ubjs_result ubjs_writer_strategy_find_best_top(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_find_best_length(unsigned int, ubjs_object **);

ubjs_result ubjs_writer_strategy_null(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_noop(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_true(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_false(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_int8(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_uint8(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_int16(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_int32(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_int64(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_float32(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_float64(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_char(ubjs_object *, ubjs_writer_strategy_runner **);
ubjs_result ubjs_writer_strategy_str(ubjs_object *, ubjs_writer_strategy_runner **);

#endif


