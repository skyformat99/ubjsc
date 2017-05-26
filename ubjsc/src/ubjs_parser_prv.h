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

#ifndef HAVE_UBJS_PARSER_PRV
#define HAVE_UBJS_PARSER_PRV

#include <ubjs_parser.h>
#include <ubjs_common.h>
#include "ubjs_selfemptying_list_prv.h"
#include "ubjs_primitives_prv.h"

typedef struct ubjs_parser_give_control_request ubjs_parser_give_control_request;
typedef struct ubjs_processor ubjs_processor;
typedef struct ubjs_processor_factory ubjs_processor_factory;
typedef struct ubjs_userdata_ntype ubjs_userdata_ntype;
typedef struct ubjs_userdata_longint ubjs_userdata_longint;
typedef struct ubjs_userdata_array ubjs_userdata_array;
typedef struct ubjs_userdata_object ubjs_userdata_object;
typedef struct ubjs_processor_next_objext ubjs_processor_next_objext;
typedef struct ubjs_parser_counters ubjs_parser_counters;
typedef enum ubjs_object_state ubjs_object_state;
typedef void (*ubjs_processor_free)(ubjs_processor *);

typedef void (*ubjs_processor_got_control)(ubjs_processor *, ubjs_parser_give_control_request *);
typedef void (*ubjs_processor_read_byte)(ubjs_processor *, unsigned int, uint8_t);
typedef ubjs_result (*ubjs_processor_factory_create)(ubjs_processor *, ubjs_processor **);
typedef ubjs_result (*ubjs_processor_next_object_selected_factory)(ubjs_processor *,
    ubjs_processor_factory_create);
typedef ubjs_result (*ubjs_processor_next_object_selected_factory_ntype)(ubjs_processor *,
    ubjs_prmtv_ntype *);

enum ubjs_object_state
{
    WANT_KEY_LENGTH,
    WANT_KEY,
    WANT_VALUE
};

struct ubjs_parser_give_control_request
{
    ubjs_library *lib;
    ubjs_processor *processor;

    ubjs_prmtv *present;
    ubjs_prmtv_ntype *marker;
};

struct ubjs_processor
{
    char *name;
    ubjs_processor *parent;
    ubjs_parser *parser;
    void *userdata;

    ubjs_processor_got_control got_control;
    ubjs_processor_read_byte read_byte;
    ubjs_processor_free free;
};

struct ubjs_processor_factory
{
    int marker;
    ubjs_processor_factory_create create;
};

struct ubjs_parser_error
{
    ubjs_library *lib;
    char *message;
    unsigned int message_length;
};

struct ubjs_parser_counters
{
    unsigned int bytes_since_last_callback;
    unsigned int recursion_level;
};

struct ubjs_parser_builder
{
    ubjs_library *lib;

    void *userdata;
    ubjs_parser_parsed_f parsed_f;
    ubjs_parser_error_f error_f;
    ubjs_parser_free_f free_f;
    ubjs_parser_debug_f debug_f;
    unsigned int limit_bytes_since_last_callback;
    unsigned int limit_container_length;
    unsigned int limit_string_length;
    unsigned int limit_recursion_level;
    ubjs_bool silently_ignore_toplevel_noops;
};

struct ubjs_parser
{
    ubjs_library *lib;

    void *userdata;
    ubjs_parser_parsed_f parsed_f;
    ubjs_parser_error_f error_f;
    ubjs_parser_free_f free_f;
    ubjs_parser_debug_f debug_f;
    unsigned int limit_bytes_since_last_callback;
    unsigned int limit_container_length;
    unsigned int limit_string_length;
    unsigned int limit_recursion_level;
    ubjs_bool silently_ignore_toplevel_noops;

    ubjs_selfemptying_list *give_control_fifo;
    unsigned int errors;

    ubjs_processor *processor;
    ubjs_parser_counters counters;

    ubjs_glue_array *ntypes_top;
    ubjs_glue_array *ntypes_array_unoptimized;
    ubjs_glue_array *ntypes_array_unoptimized_first;
    ubjs_glue_array *ntypes_array_type;
    ubjs_glue_array *ntypes_array_optimized;
    ubjs_glue_array *ntypes_object_unoptimized;
    ubjs_glue_array *ntypes_object_unoptimized_first;
    ubjs_glue_array *ntypes_object_type;
    ubjs_glue_array *ntypes_object_optimized;
    ubjs_glue_array *ntypes_int;

    ubjs_glue_array *factories_top;
    ubjs_glue_array *factories_array_unoptimized;
    ubjs_glue_array *factories_array_unoptimized_first;
    ubjs_glue_array *factories_array_type;
    ubjs_glue_array *factories_array_optimized;
    ubjs_glue_array *factories_object_unoptimized;
    ubjs_glue_array *factories_object_unoptimized_first;
    ubjs_glue_array *factories_object_type;
    ubjs_glue_array *factories_object_optimized;
};

struct ubjs_processor_next_objext
{
    ubjs_processor super;

    ubjs_glue_array *ntypes;
    ubjs_processor_next_object_selected_factory_ntype selected_factory_ntype;

    ubjs_glue_array *factories;
    ubjs_processor_next_object_selected_factory selected_factory;
};

struct ubjs_userdata_ntype
{
    ubjs_prmtv_ntype *ntype;
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *processor;

    unsigned int pos;
};

struct ubjs_userdata_longint
{
    uint8_t *data;
    unsigned int done;
};

struct ubjs_userdata_array
{
    ubjs_prmtv *array;

    ubjs_bool have_type;
    ubjs_processor_factory_create type_create;
    ubjs_prmtv_ntype *ntype;

    ubjs_bool have_length;
    unsigned int length;
    unsigned int real_length;
};

struct ubjs_userdata_object
{
    ubjs_prmtv *object;

    ubjs_bool have_type;
    ubjs_processor_factory_create type_create;
    ubjs_prmtv_ntype *ntype;

    ubjs_bool have_length;
    unsigned int length;
    unsigned int real_length;

    ubjs_object_state state;
    unsigned int key_length;
    char *key;
};

UBJS_NO_EXPORT void ubjs_parser_configure_factories(ubjs_parser *);
UBJS_NO_EXPORT void ubjs_parser_give_control_request_free(ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_parser_give_control_fifo_callback(ubjs_selfemptying_list *, void *);
UBJS_NO_EXPORT void ubjs_parser_give_control(ubjs_parser *, ubjs_processor *, ubjs_prmtv *,
    ubjs_prmtv_ntype *);

UBJS_NO_EXPORT void ubjs_parser_emit_error(ubjs_parser *, unsigned int, char *);
UBJS_NO_EXPORT ubjs_result ubjs_parser_up_recursion_level(ubjs_parser *);
UBJS_NO_EXPORT ubjs_result ubjs_parser_down_recursion_level(ubjs_parser *);

UBJS_NO_EXPORT void ubjs_processor_top(ubjs_parser *);
UBJS_NO_EXPORT void ubjs_processor_ints(ubjs_processor *);

UBJS_NO_EXPORT ubjs_result ubjs_processor_next_object(ubjs_processor *,
    ubjs_glue_array *, ubjs_processor_next_object_selected_factory_ntype,
    ubjs_glue_array *,
    ubjs_processor_next_object_selected_factory, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_child_produced_length(ubjs_processor *, ubjs_prmtv *,
    unsigned int *);

extern ubjs_processor_factory ubjs_processor_factory_array;
extern ubjs_processor_factory ubjs_processor_factory_array_end;
extern ubjs_processor_factory ubjs_processor_factory_array_type;
extern ubjs_processor_factory ubjs_processor_factory_array_count;
extern ubjs_processor_factory ubjs_processor_factory_object;
extern ubjs_processor_factory ubjs_processor_factory_object_end;
extern ubjs_processor_factory ubjs_processor_factory_object_type;
extern ubjs_processor_factory ubjs_processor_factory_object_count;

UBJS_NO_EXPORT void ubjs_processor_factory_free(void *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_ntype(ubjs_processor *, ubjs_prmtv_ntype *,
    ubjs_processor **);
UBJS_NO_EXPORT void ubjs_processor_ntype_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_processor_ntype_free(ubjs_processor *);
UBJS_NO_EXPORT void ubjs_processor_ntype_read_byte(ubjs_processor *, unsigned int, uint8_t);
UBJS_NO_EXPORT void ubjs_processor_ntype_return_control(ubjs_prmtv_ntype_parser_glue *,
    void *);
UBJS_NO_EXPORT void ubjs_processor_ntype_want_marker(ubjs_prmtv_ntype_parser_glue *,
    ubjs_glue_array *);
UBJS_NO_EXPORT void ubjs_processor_ntype_want_child(ubjs_prmtv_ntype_parser_glue *,
    ubjs_prmtv_ntype *);
UBJS_NO_EXPORT void ubjs_processor_ntype_debug(ubjs_prmtv_ntype_parser_glue *,
    unsigned int, char *);
UBJS_NO_EXPORT void ubjs_processor_ntype_error(ubjs_prmtv_ntype_parser_glue *,
    unsigned int, char *);

UBJS_NO_EXPORT ubjs_result ubjs_processor_array(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_end(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_type(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_count(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_end(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_type(ubjs_processor *, ubjs_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_count(ubjs_processor *, ubjs_processor **);

UBJS_NO_EXPORT ubjs_result ubjs_parser_error_new(ubjs_library *, char *, unsigned int,
    ubjs_parser_error **);
UBJS_NO_EXPORT ubjs_result ubjs_parser_error_free(ubjs_parser_error **);

UBJS_NO_EXPORT void ubjs_processor_top_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_top_selected_factory(ubjs_processor *,
    ubjs_processor_factory_create);
UBJS_NO_EXPORT ubjs_result ubjs_processor_top_selected_factory_ntype(ubjs_processor *,
    ubjs_prmtv_ntype *);
UBJS_NO_EXPORT void ubjs_processor_next_object_read_byte(ubjs_processor *, unsigned int, uint8_t);
UBJS_NO_EXPORT void ubjs_processor_next_object_free(ubjs_processor *);

UBJS_NO_EXPORT void ubjs_processor_array_free(ubjs_processor *);
UBJS_NO_EXPORT void ubjs_processor_array_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_processor_array_child_produced_end(ubjs_processor *);
UBJS_NO_EXPORT void ubjs_processor_array_end_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_processor_array_count_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_selected_factory(ubjs_processor *,
    ubjs_processor_factory_create);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_selected_factory_ntype(ubjs_processor *,
    ubjs_prmtv_ntype *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_type_selected_factory(ubjs_processor *,
    ubjs_processor_factory_create);
UBJS_NO_EXPORT ubjs_result ubjs_processor_array_type_selected_factory_ntype(ubjs_processor *,
    ubjs_prmtv_ntype *);

UBJS_NO_EXPORT void ubjs_processor_object_free(ubjs_processor *);
UBJS_NO_EXPORT void ubjs_processor_object_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_processor_object_child_produced_end(ubjs_processor *);
UBJS_NO_EXPORT void ubjs_processor_object_end_got_control(ubjs_processor *this,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT void ubjs_processor_object_count_got_control(ubjs_processor *,
    ubjs_parser_give_control_request *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_selected_factory(ubjs_processor *,
    ubjs_processor_factory_create);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_selected_factory_ntype(ubjs_processor *,
    ubjs_prmtv_ntype *);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_type_selected_factory(ubjs_processor *,
    ubjs_processor_factory_create);
UBJS_NO_EXPORT ubjs_result ubjs_processor_object_type_selected_factory_ntype(ubjs_processor *,
    ubjs_prmtv_ntype *);

/* \endinternal */

#endif
