/*
 * Copyright (c) 2016 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#ifndef HAVE_UBJS_WRITER_INTERNAL
#define HAVE_UBJS_WRITER_INTERNAL

#include "../include/ubjs_writer.h"

typedef struct ubjs_writer_prmtv_runner ubjs_writer_prmtv_runner;
typedef void (*ubjs_writer_prmtv_runner_write)(ubjs_writer_prmtv_runner *, uint8_t *);
typedef void (*ubjs_writer_prmtv_runner_print)(ubjs_writer_prmtv_runner *, char *);
typedef void (*ubjs_writer_prmtv_runner_free)(ubjs_writer_prmtv_runner *);
typedef ubjs_result (*ubjs_writer_prmtv_write_strategy)(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
typedef ubjs_result (*ubjs_writer_prmtv_upgrade_strategy)(ubjs_prmtv *, ubjs_prmtv **);

struct ubjs_writer_prmtv_runner
{
    void *userdata;
    ubjs_writer_prmtv_write_strategy strategy;
    ubjs_prmtv *object;

    unsigned int length_write;
    unsigned int length_print;

    uint8_t marker;
    ubjs_writer_prmtv_runner_write write;
    ubjs_writer_prmtv_runner_print print;
    ubjs_writer_prmtv_runner_free free;
};

extern unsigned int ubjs_writer_prmtv_write_strategy_array_threshold;

extern unsigned int ubjs_writer_prmtv_write_strategies_top_len;
extern ubjs_writer_prmtv_write_strategy ubjs_writer_prmtv_write_strategies_top[];

extern unsigned int ubjs_writer_prmtv_upgrade_strategies_len;
extern ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[];

ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_prmtv *, ubjs_writer_prmtv_runner **);

ubjs_result ubjs_writer_prmtv_try_upgrade(ubjs_prmtv *, ubjs_prmtv **);

ubjs_result ubjs_writer_prmtv_write_strategy_null(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_noop(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_true(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_false(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int8(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_uint8(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int16(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int32(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int64(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_float32(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_float64(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_char(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_str(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_array(ubjs_prmtv *, ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_object(ubjs_prmtv *, ubjs_writer_prmtv_runner **);

ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int16(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int32(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int64(ubjs_prmtv *, ubjs_prmtv **);

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64(ubjs_prmtv *, ubjs_prmtv **);

#endif
