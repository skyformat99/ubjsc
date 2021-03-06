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

#ifndef HAVE_TEST_WRITER_TOOLS
#define HAVE_TEST_WRITER_TOOLS

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs.h>
#include "test_list.h"

typedef struct wrapped_writer_context wrapped_writer_context;
typedef struct would_write_call would_write_call;
typedef struct would_print_call would_print_call;

struct would_write_call
{
    uint8_t *data;
    unsigned int len;
};

void would_write_call_new(uint8_t *, unsigned int, would_write_call **);
void would_write_call_free(would_write_call **);

struct would_print_call
{
    char *data;
    unsigned int len;
};
void would_print_call_new(char *, unsigned int, would_print_call **);
void would_print_call_free(would_print_call **);

struct wrapped_writer_context
{
    test_list *calls_would_write;
    test_list *calls_would_print;
    test_list *calls_free;
};

void wrapped_writer_context_new(wrapped_writer_context **);
void wrapped_writer_context_free(wrapped_writer_context **);
/*
void wrapped_writer_context_reset(wrapped_writer_context *);
*/

void writer_context_would_write(void *userdata, uint8_t *data, unsigned int len);
void writer_context_would_print(void *userdata, char *data, unsigned int len);
void writer_context_debug(void *userdata, unsigned int len, char *message);
void writer_context_free(void *userdata);

void writer_mock_free(unsigned int, ubjs_prmtv **);
void writer_mock_dict_iterator_next(unsigned int, unsigned int, ubjs_prmtv *, ubjs_bool,
    ubjs_bool, ubjs_bool);
void writer_mock_dict_will_return(unsigned int, ubjs_prmtv **);
void writer_mock_dict_will_returnd(unsigned int, ubjs_prmtv **, ubjs_bool);
void writer_mock_dict_will_return2(unsigned int, ubjs_prmtv **, ubjs_prmtv **);
void writer_mock_dict_will_return2d(unsigned int, ubjs_prmtv **, ubjs_prmtv **, ubjs_bool);

void writer_mock_array_iterator_next(unsigned int, unsigned int, ubjs_prmtv *, ubjs_bool,
    ubjs_bool);
void writer_mock_array_will_return(unsigned int, ubjs_prmtv **);
void writer_mock_array_will_returnd(unsigned int, ubjs_prmtv **, ubjs_bool);
void writer_mock_array_will_return2(unsigned int, ubjs_prmtv **, ubjs_prmtv **);
void writer_mock_array_will_return2d(unsigned int, ubjs_prmtv **, ubjs_prmtv **, ubjs_bool);

#ifdef __cplusplus
}
#endif

#endif
