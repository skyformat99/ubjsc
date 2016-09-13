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

#include <ubjs_common.h>
#include <ubjs_parser.h>
#include "ubjs_list.h"

typedef struct ubjs_processor ubjs_processor;
typedef struct ubjs_processor_factory ubjs_processor_factory;
typedef struct ubjs_userdata_longint ubjs_userdata_longint;
typedef struct ubjs_userdata_str ubjs_userdata_str;
typedef struct ubjs_userdata_hpn ubjs_userdata_hpn;
typedef struct ubjs_userdata_array ubjs_userdata_array;
typedef struct ubjs_userdata_object ubjs_userdata_object;
typedef struct ubjs_processor_next_objext ubjs_processor_next_objext;
typedef struct ubjs_parser_counters ubjs_parser_counters;
typedef enum ubjs_object_state ubjs_object_state;
typedef void (*ubjs_processor_free)(ubjs_processor *);

typedef ubjs_result (*ubjs_processor_got_control)(ubjs_processor *, ubjs_prmtv *);
typedef ubjs_result (*ubjs_processor_read_char)(ubjs_processor *, unsigned int, uint8_t);
typedef ubjs_result (*ubjs_processor_factory_create)(ubjs_processor *, ubjs_processor **);
typedef ubjs_result (*ubjs_processor_next_object_selected_factory)(ubjs_processor *,
    ubjs_processor_factory *);

enum ubjs_object_state
{
    WANT_KEY_LENGTH,
    WANT_KEY,
    WANT_VALUE
};

struct ubjs_processor
{
    char *name;
    ubjs_processor *parent;
    ubjs_parser *parser;
    void *userdata;

    ubjs_processor_got_control got_control;
    ubjs_processor_read_char read_char;
    ubjs_processor_free free;
};

struct ubjs_processor_factory
{
    int marker;
    ubjs_processor_factory_create create;
};

struct ubjs_parser_error
{
    char *message;
    unsigned int message_length;
};

struct ubjs_parser_counters
{
    unsigned int bytes_since_last_callback;
    unsigned int recursion_level;
};

struct ubjs_parser
{
    ubjs_parser_context *context;
    ubjs_parser_settings *settings;

    ubjs_processor *processor;
    ubjs_parser_counters counters;

    ubjs_list *factories_top;
    ubjs_list *factories_array_unoptimized;
    ubjs_list *factories_array_unoptimized_first;
    ubjs_list *factories_array_type;
    ubjs_list *factories_array_optimized;
    ubjs_list *factories_object_unoptimized;
    ubjs_list *factories_object_unoptimized_first;
    ubjs_list *factories_object_type;
    ubjs_list *factories_object_optimized;
    ubjs_list *factories_int;
};

struct ubjs_processor_next_objext
{
    ubjs_processor super;
    ubjs_list *factories;
    ubjs_processor_next_object_selected_factory selected_factory;
};

struct ubjs_userdata_longint
{
    uint8_t *data;
    unsigned int done;
};

struct ubjs_userdata_str
{
    ubjs_bool have_length;
    unsigned int length;
    unsigned int done;
    char *data;
};

struct ubjs_userdata_hpn
{
    ubjs_bool have_length;
    unsigned int length;
    unsigned int done;
    char *data;
};

struct ubjs_userdata_array
{
    ubjs_prmtv *array;

    ubjs_bool have_type;
    ubjs_processor_factory *type_factory;

    ubjs_bool have_length;
    unsigned int length;
};

struct ubjs_userdata_object
{
    ubjs_prmtv *object;

    ubjs_bool have_type;
    ubjs_processor_factory *type_factory;

    ubjs_bool have_length;
    unsigned int length;

    ubjs_object_state state;
    unsigned int key_length;
    char *key;
};

ubjs_result ubjs_parser_give_control(ubjs_parser *, ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_parser_emit_error(ubjs_parser *, unsigned int, char *);
ubjs_result ubjs_parser_up_recursion_level(ubjs_parser *);
ubjs_result ubjs_parser_down_recursion_level(ubjs_parser *);

ubjs_result ubjs_processor_top(ubjs_parser *);
ubjs_result ubjs_processor_ints(ubjs_processor *);

ubjs_result ubjs_processor_next_object(ubjs_processor *, ubjs_list *,
    ubjs_processor_next_object_selected_factory, ubjs_processor **);
ubjs_result ubjs_processor_child_produced_length(ubjs_processor *, ubjs_prmtv *,
    unsigned int *);

void ubjs_processor_factory_free(ubjs_processor_factory *);
ubjs_processor_factory *ubjs_processor_factory_null();
ubjs_processor_factory *ubjs_processor_factory_noop();
ubjs_processor_factory *ubjs_processor_factory_true();
ubjs_processor_factory *ubjs_processor_factory_false();
ubjs_processor_factory *ubjs_processor_factory_int8();
ubjs_processor_factory *ubjs_processor_factory_uint8();
ubjs_processor_factory *ubjs_processor_factory_int16();
ubjs_processor_factory *ubjs_processor_factory_int32();
ubjs_processor_factory *ubjs_processor_factory_int64();
ubjs_processor_factory *ubjs_processor_factory_float32();
ubjs_processor_factory *ubjs_processor_factory_float64();
ubjs_processor_factory *ubjs_processor_factory_char();
ubjs_processor_factory *ubjs_processor_factory_str();
ubjs_processor_factory *ubjs_processor_factory_hpn();
ubjs_processor_factory *ubjs_processor_factory_array();
ubjs_processor_factory *ubjs_processor_factory_array_end();
ubjs_processor_factory *ubjs_processor_factory_array_type();
ubjs_processor_factory *ubjs_processor_factory_array_count();
ubjs_processor_factory *ubjs_processor_factory_object();
ubjs_processor_factory *ubjs_processor_factory_object_end();
ubjs_processor_factory *ubjs_processor_factory_object_type();
ubjs_processor_factory *ubjs_processor_factory_object_count();

ubjs_result ubjs_processor_null(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_noop(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_true(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_false(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int8(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_uint8(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int16(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int32(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_int64(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_float32(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_float64(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_char(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_str(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_hpn(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_end(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_type(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_count(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object_end(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object_type(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object_count(ubjs_processor *, ubjs_processor **);

ubjs_result ubjs_parser_error_new(char *message, unsigned int len, ubjs_parser_error **);
ubjs_result ubjs_parser_error_free(ubjs_parser_error **);

ubjs_result ubjs_processor_top_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_top_selected_factory(ubjs_processor *, ubjs_processor_factory *);
ubjs_result ubjs_processor_next_object_read_char(ubjs_processor *, unsigned int, uint8_t);
void ubjs_processor_next_object_free(ubjs_processor *);
ubjs_result ubjs_processor_no_length_got_control(ubjs_processor *this, ubjs_prmtv *);

ubjs_result ubjs_processor_int8_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_uint8_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_char_read_char(ubjs_processor *, unsigned int, uint8_t);

void ubjs_processor_longint_free(ubjs_processor *);
ubjs_result ubjs_processor_int16_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_int32_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_int64_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_float32_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_float64_read_char(ubjs_processor *, unsigned int, uint8_t);

ubjs_result ubjs_processor_str_got_control(ubjs_processor *, ubjs_prmtv *);
void ubjs_processor_str_free(ubjs_processor *);
ubjs_result ubjs_processor_str_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_str_complete(ubjs_processor *);

ubjs_result ubjs_processor_hpn_got_control(ubjs_processor *, ubjs_prmtv *);
void ubjs_processor_hpn_free(ubjs_processor *);
ubjs_result ubjs_processor_hpn_read_char(ubjs_processor *, unsigned int, uint8_t);
ubjs_result ubjs_processor_hpn_complete(ubjs_processor *);

void ubjs_processor_array_free(ubjs_processor *);
ubjs_result ubjs_processor_array_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_array_child_produced_end(ubjs_processor *);
ubjs_result ubjs_processor_array_end_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_array_count_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_array_type_selected_factory(ubjs_processor *, ubjs_processor_factory *);

void ubjs_processor_object_free(ubjs_processor *);
ubjs_result ubjs_processor_object_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_object_child_produced_end(ubjs_processor *);
ubjs_result ubjs_processor_object_end_got_control(ubjs_processor *this, ubjs_prmtv *);
ubjs_result ubjs_processor_object_count_got_control(ubjs_processor *, ubjs_prmtv *);
ubjs_result ubjs_processor_object_type_selected_factory(ubjs_processor *, ubjs_processor_factory *);

/* \endinternal */

#endif
