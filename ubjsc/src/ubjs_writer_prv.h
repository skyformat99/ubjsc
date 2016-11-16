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
/* \internal */

#ifndef HAVE_UBJS_WRITER_PRV
#define HAVE_UBJS_WRITER_PRV

#include <ubjs_writer.h>

#define UBJS_SPACES_PER_INDENT 4

typedef struct ubjs_writer_prmtv_runner ubjs_writer_prmtv_runner;
typedef struct ubjs_writer_prmtv_write_strategy_context_no_length
    ubjs_writer_prmtv_write_strategy_context_no_length;
typedef struct ubjs_writer_prmtv_write_strategy_context_str
    ubjs_writer_prmtv_write_strategy_context_str;
typedef struct ubjs_writer_prmtv_write_strategy_context_hpn
    ubjs_writer_prmtv_write_strategy_context_hpn;
typedef struct ubjs_writer_prmtv_write_strategy_context_array
    ubjs_writer_prmtv_write_strategy_context_array;
typedef struct ubjs_writer_prmtv_write_strategy_context_object
    ubjs_writer_prmtv_write_strategy_context_object;
typedef struct ubjs_writer_prmtv_upgrade_strategy_ints_metrics
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics;

typedef void (*ubjs_writer_prmtv_runner_write)(ubjs_writer_prmtv_runner *, uint8_t *);
typedef void (*ubjs_writer_prmtv_runner_print)(ubjs_writer_prmtv_runner *, char *);
typedef void (*ubjs_writer_prmtv_runner_free)(ubjs_writer_prmtv_runner *);
typedef ubjs_result (*ubjs_writer_prmtv_write_strategy)(ubjs_writer *, ubjs_prmtv *,
    unsigned int, ubjs_writer_prmtv_runner **);
typedef ubjs_result (*ubjs_writer_prmtv_upgrade_strategy)(ubjs_prmtv *, ubjs_prmtv **);

struct ubjs_writer_prmtv_runner
{
    void *userdata;
    ubjs_library *lib;
    ubjs_writer_prmtv_write_strategy strategy;
    ubjs_prmtv *object;
    unsigned int indent;

    unsigned int length_write;
    unsigned int length_print;

    uint8_t marker;
    ubjs_writer_prmtv_runner_write write;
    ubjs_writer_prmtv_runner_print print;
    ubjs_writer_prmtv_runner_free free;
};

struct ubjs_writer
{
    ubjs_library *lib;
    ubjs_writer_context *context;
};

struct ubjs_writer_prmtv_write_strategy_context_no_length
{
    uint8_t marker;
};

struct ubjs_writer_prmtv_write_strategy_context_str
{
    ubjs_writer_prmtv_runner *length_strategy;
    unsigned int length;
    ubjs_prmtv *length_obj;
};

struct ubjs_writer_prmtv_write_strategy_context_hpn
{
    ubjs_writer_prmtv_runner *length_strategy;
    unsigned int length;
    ubjs_prmtv *length_obj;
};

struct ubjs_writer_prmtv_write_strategy_context_array
{
    ubjs_writer_prmtv_runner **item_runners;

    unsigned int length;
    ubjs_bool was_upgraded;
    ubjs_bool do_indents;

    ubjs_writer_prmtv_runner *type_strategy;

    ubjs_prmtv *count;
    ubjs_writer_prmtv_runner *count_strategy;
};

struct ubjs_writer_prmtv_write_strategy_context_object
{
    ubjs_writer_prmtv_runner **key_runners;
    ubjs_writer_prmtv_runner **value_runners;

    unsigned int length;
    ubjs_bool was_upgraded;
    ubjs_bool do_indents;

    ubjs_writer_prmtv_runner *type_strategy;

    ubjs_prmtv *count;
    ubjs_writer_prmtv_runner *count_strategy;
};

struct ubjs_writer_prmtv_upgrade_strategy_ints_metrics
{
    unsigned int count_of_8;
    unsigned int count_of_16;
    unsigned int count_of_32;
    unsigned int count_of_64;
    unsigned int count_of_rest;
    unsigned int count;
};

extern unsigned int ubjs_writer_prmtv_write_strategy_array_threshold;

extern unsigned int ubjs_writer_prmtv_write_strategies_top_len;
extern ubjs_writer_prmtv_write_strategy ubjs_writer_prmtv_write_strategies_top[];

extern unsigned int ubjs_writer_prmtv_upgrade_strategies_len;
extern ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[];

ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);

ubjs_result ubjs_writer_prmtv_try_upgrade(ubjs_prmtv *, ubjs_prmtv **);

ubjs_result ubjs_writer_prmtv_write_strategy_null(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_noop(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_true(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_false(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int8(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_uint8(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int16(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int32(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_int64(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_float32(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_float64(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_char(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_str(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_hpn(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_array(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);
ubjs_result ubjs_writer_prmtv_write_strategy_object(ubjs_writer *, ubjs_prmtv *, unsigned int,
    ubjs_writer_prmtv_runner **);

ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int16(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int32(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_array_ints_to_int64(ubjs_prmtv *, ubjs_prmtv **);

ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int16(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int32(ubjs_prmtv *, ubjs_prmtv **);
ubjs_result ubjs_writer_prmtv_upgrade_strategy_object_ints_to_int64(ubjs_prmtv *, ubjs_prmtv **);

void ubjs_writer_prmtv_runner_write_no_length(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_free_no_length(ubjs_writer_prmtv_runner *);

void ubjs_writer_prmtv_runner_write_int8(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_int8(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_uint8(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_uint8(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_int16(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_int16(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_int32(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_int32(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_int64(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_int64(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_float32(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_float32(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_float64(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_float64(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_char(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_char(ubjs_writer_prmtv_runner *, char *);

void ubjs_writer_prmtv_runner_write_str(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_str(ubjs_writer_prmtv_runner *, char *);
void ubjs_writer_prmtv_runner_free_str(ubjs_writer_prmtv_runner *);

void ubjs_writer_prmtv_runner_write_hpn(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_hpn(ubjs_writer_prmtv_runner *, char *);
void ubjs_writer_prmtv_runner_free_hpn(ubjs_writer_prmtv_runner *);

void ubjs_writer_prmtv_runner_write_array(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_array(ubjs_writer_prmtv_runner *, char *);
void ubjs_writer_prmtv_runner_free_array(ubjs_writer_prmtv_runner *);

void ubjs_writer_prmtv_runner_write_object(ubjs_writer_prmtv_runner *, uint8_t *);
void ubjs_writer_prmtv_runner_print_object(ubjs_writer_prmtv_runner *, char *);
void ubjs_writer_prmtv_runner_free_object(ubjs_writer_prmtv_runner *);

void ubjs_writer_prmtv_upgrade_strategy_ints_array_calculate_metrics(ubjs_prmtv *,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *);
void ubjs_writer_prmtv_upgrade_strategy_ints_object_calculate_metrics(ubjs_prmtv *,
    ubjs_writer_prmtv_upgrade_strategy_ints_metrics *);

/* \endinternal */

#endif
