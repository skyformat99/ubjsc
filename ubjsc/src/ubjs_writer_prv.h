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
typedef struct ubjs_writer_prmtv_write_strategy_context_ntype
    ubjs_writer_prmtv_write_strategy_context_ntype;

typedef void (*ubjs_writer_prmtv_runner_write_get_length)(ubjs_writer_prmtv_runner *,
    unsigned int *);
typedef void (*ubjs_writer_prmtv_runner_print_get_length)(ubjs_writer_prmtv_runner *,
    unsigned int *);
typedef void (*ubjs_writer_prmtv_runner_write)(ubjs_writer_prmtv_runner *, uint8_t *);
typedef void (*ubjs_writer_prmtv_runner_print)(ubjs_writer_prmtv_runner *, char *);
typedef void (*ubjs_writer_prmtv_runner_free)(ubjs_writer_prmtv_runner *);
typedef ubjs_result (*ubjs_writer_prmtv_write_strategy)(ubjs_writer *, ubjs_prmtv *,
    unsigned int, ubjs_writer_prmtv_runner **);
typedef ubjs_result (*ubjs_writer_prmtv_upgrade_strategy)(ubjs_writer *,
    ubjs_prmtv *, ubjs_prmtv **);

struct ubjs_writer_prmtv_runner
{
    ubjs_writer *writer;

    void *userdata;
    ubjs_writer_prmtv_write_strategy strategy;
    ubjs_prmtv *object;
    unsigned int indent;

    uint8_t marker;
    ubjs_writer_prmtv_runner_write_get_length write_get_length;
    ubjs_writer_prmtv_runner_print_get_length print_get_length;
    ubjs_writer_prmtv_runner_write write;
    ubjs_writer_prmtv_runner_print print;
    ubjs_writer_prmtv_runner_free free;
};

struct ubjs_writer_builder
{
    ubjs_library *lib;

    void *userdata;
    ubjs_writer_would_write_f would_write_f;
    ubjs_writer_would_print_f would_print_f;
    ubjs_writer_debug_f debug_f;
    ubjs_bool free_primitives_early;
    ubjs_writer_free_f free_f;
};

struct ubjs_writer
{
    ubjs_library *lib;

    void *userdata;
    ubjs_writer_would_write_f would_write_f;
    ubjs_writer_would_print_f would_print_f;
    ubjs_writer_debug_f debug_f;
    ubjs_bool free_primitives_early;
    ubjs_writer_free_f free_f;
};

struct ubjs_writer_prmtv_write_strategy_context_ntype
{
    ubjs_prmtv_ntype *ntype;
    ubjs_prmtv_ntype_writer_glue writer_glue;
    ubjs_prmtv_ntype_writer *writer;

    ubjs_prmtv_ntype_printer_glue printer_glue;
    ubjs_prmtv_ntype_printer *printer;
};

extern unsigned int ubjs_writer_prmtv_write_strategies_top_len;
extern ubjs_writer_prmtv_write_strategy ubjs_writer_prmtv_write_strategies_top[];

extern unsigned int ubjs_writer_prmtv_upgrade_strategies_len;
extern ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[];

UBJS_NO_EXPORT ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_writer *, ubjs_prmtv *,
    unsigned int, ubjs_writer_prmtv_runner **);

UBJS_NO_EXPORT ubjs_result ubjs_writer_prmtv_try_upgrade(ubjs_writer *, ubjs_prmtv *,
    ubjs_prmtv **);

UBJS_NO_EXPORT ubjs_result ubjs_writer_prmtv_write_strategy_ntype(ubjs_writer *, ubjs_prmtv *,
    unsigned int, ubjs_writer_prmtv_runner **);
UBJS_NO_EXPORT void ubjs_writer_write_ntype_glue_debug(ubjs_prmtv_ntype_writer_glue *,
    unsigned int, char *);
UBJS_NO_EXPORT void ubjs_writer_print_ntype_glue_debug(ubjs_prmtv_ntype_printer_glue *,
    unsigned int, char *);

UBJS_NO_EXPORT void ubjs_writer_prmtv_runner_write_ntype(ubjs_writer_prmtv_runner *, uint8_t *);
UBJS_NO_EXPORT void ubjs_writer_prmtv_runner_write_get_length_ntype(ubjs_writer_prmtv_runner *,
    unsigned int *);
UBJS_NO_EXPORT void ubjs_writer_prmtv_runner_print_ntype(ubjs_writer_prmtv_runner *, char *);
UBJS_NO_EXPORT void ubjs_writer_prmtv_runner_print_get_length_ntype(ubjs_writer_prmtv_runner *,
    unsigned int *);
UBJS_NO_EXPORT void ubjs_writer_prmtv_runner_free_ntype(ubjs_writer_prmtv_runner *);

/* \endinternal */

#endif
