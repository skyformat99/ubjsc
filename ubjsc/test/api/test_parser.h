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

#ifndef HAVE_TEST_PARSER
#define HAVE_TEST_PARSER

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"

#define LOTS 255

typedef void (*sp_verify_parsed_callback)(ubjs_prmtv *);

void suite_parser_before(void);
void suite_parser_after(void);

void sp_verify_parsed(ubjs_library *, unsigned int, uint8_t *, sp_verify_parsed_callback);
void sp_verify_error(ubjs_library *, unsigned int, uint8_t *, char *);

void dsp_verify_parsed(ubjs_library *, unsigned int, uint8_t *, sp_verify_parsed_callback,
    ubjs_bool);
void dsp_verify_error(ubjs_library *, unsigned int, uint8_t *, char *, ubjs_bool);

#ifdef __cplusplus
}
#endif

#endif
