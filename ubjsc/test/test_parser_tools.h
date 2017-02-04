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

#ifndef HAVE_TEST_PARSER_TOOLS
#define HAVE_TEST_PARSER_TOOLS

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs.h>

#include "test_list.h"

typedef struct wrapped_parser_context wrapped_parser_context;

struct wrapped_parser_context
{
    test_list *calls_parsed;
    test_list *calls_error;
    test_list *calls_free;
};

void wrapped_parser_context_new(wrapped_parser_context **);
void wrapped_parser_context_free(wrapped_parser_context **);
/*
void wrapped_parser_context_reset(wrapped_parser_context *);
*/

void wrapper_free(ubjs_prmtv *object);
void parser_context_parsed(void *, ubjs_prmtv *object);
void parser_context_error(void *, ubjs_parser_error *error);
void parser_context_free(void *);

#ifdef __cplusplus
}
#endif

#endif
