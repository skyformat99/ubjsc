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

#ifndef HAVE_UBJS_PARSER_INTERNAL
#define HAVE_UBJS_PARSER_INTERNAL

#include "../include/ubjs_common.h"
#include "../include/ubjs_parser.h"

typedef struct ubjs_processor ubjs_processor;
typedef struct ubjs_processor_factory ubjs_processor_factory;

typedef void (*ubjs_processor_free)(ubjs_processor *);
typedef ubjs_result (*ubjs_processor_gained_control)(ubjs_processor *);
typedef ubjs_result (*ubjs_processor_read_char)(ubjs_processor *, unsigned int, uint8_t);
typedef ubjs_result (*ubjs_processor_child_produced_object)(ubjs_processor *, ubjs_prmtv *);

struct ubjs_processor
{
    char *name;
    ubjs_processor *parent;
    ubjs_parser *parser;
    void *userdata;

    ubjs_processor_gained_control gained_control;
    ubjs_processor_read_char read_char;
    ubjs_processor_child_produced_object child_produced_object;
    ubjs_processor_free free;
};

typedef ubjs_result (*ubjs_processor_factory_create)(ubjs_processor *, ubjs_processor **);
struct ubjs_processor_factory
{
    int marker;
    ubjs_processor_factory_create create;
};

extern int ubjs_processor_factories_top_len;
extern ubjs_processor_factory ubjs_processor_factories_top[];

extern int ubjs_processor_factories_array_len;
extern ubjs_processor_factory ubjs_processor_factories_array[];

extern int ubjs_processor_factories_array_count_len;
extern ubjs_processor_factory ubjs_processor_factories_array_count[];

extern int ubjs_processor_factories_object_len;
extern ubjs_processor_factory ubjs_processor_factories_object[];

extern int ubjs_processor_factories_ints_len;
extern ubjs_processor_factory ubjs_processor_factories_ints[];

ubjs_result ubjs_parser_give_control(ubjs_parser *, ubjs_processor *,ubjs_bool);

ubjs_result ubjs_processor_top(ubjs_parser *, ubjs_processor **);
ubjs_result ubjs_processor_ints(ubjs_processor *, ubjs_processor **);

ubjs_result ubjs_processor_next_object(ubjs_processor *, ubjs_processor_factory *,
    int, ubjs_processor **);
ubjs_result ubjs_processor_child_produced_length(ubjs_processor *, ubjs_prmtv *,
    unsigned int *);

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
ubjs_result ubjs_processor_array(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_end(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_array_count(ubjs_processor *,ubjs_processor **);
ubjs_result ubjs_processor_object(ubjs_processor *, ubjs_processor **);
ubjs_result ubjs_processor_object_end(ubjs_processor *, ubjs_processor **);

ubjs_result ubjs_parser_error_new(char *message, unsigned int len, ubjs_parser_error **);
ubjs_result ubjs_parser_error_free(ubjs_parser_error **);

#endif
