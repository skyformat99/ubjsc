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

#ifndef HAVE_UBJS_PARSER
#define HAVE_UBJS_PARSER

#ifdef __cplusplus
extern "C"
{
#endif

#include "ubjs_common.h"
#include "ubjs_primitives.h"

typedef struct ubjs_parser ubjs_parser;
typedef struct ubjs_parser_error ubjs_parser_error;
typedef struct ubjs_parser_context ubjs_parser_context;

typedef UBJS_EXPORT void (*ubjs_parser_context_parsed)(ubjs_parser_context *, ubjs_prmtv *);
typedef UBJS_EXPORT void (*ubjs_parser_context_error)(ubjs_parser_context *, ubjs_parser_error *);
typedef UBJS_EXPORT void (*ubjs_parser_context_free)(ubjs_parser_context *);

struct ubjs_parser_error;

UBJS_EXPORT ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *, unsigned int *);
UBJS_EXPORT ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *, char *);

struct ubjs_parser_context
{
    void *userdata;
    ubjs_parser_context_parsed parsed;
    ubjs_parser_context_error error;
    ubjs_parser_context_free free;
};

struct ubjs_parser;

UBJS_EXPORT ubjs_result ubjs_parser_new(ubjs_parser **, ubjs_parser_context *);
UBJS_EXPORT ubjs_result ubjs_parser_free(ubjs_parser **);

UBJS_EXPORT ubjs_result ubjs_parser_get_context(ubjs_parser *, ubjs_parser_context **);
UBJS_EXPORT ubjs_result ubjs_parser_parse(ubjs_parser *, uint8_t *, unsigned int);

#ifdef __cplusplus
}
#endif

#endif
