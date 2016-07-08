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

#ifndef HAVE_TEST_PRIMITIVES
#define HAVE_TEST_PRIMITIVES

#include "test_frmwrk.h"
#include "../include/ubjs.h"

typedef void (*__create_primitive)(ubjs_prmtv **);
typedef void (*__test_primitive)(ubjs_prmtv *);

struct __primitive
{
    __create_primitive create;
    __test_primitive test;
};

extern unsigned int __primitives_len;
extern struct __primitive __primitives[];

void __create_null(ubjs_prmtv **);
void __create_noop(ubjs_prmtv **);
void __create_false(ubjs_prmtv **);
void __create_true(ubjs_prmtv **);
void __create_int8(ubjs_prmtv **);
void __create_uint8(ubjs_prmtv **);
void __create_int16(ubjs_prmtv **);
void __create_int32(ubjs_prmtv **);
void __create_int64(ubjs_prmtv **);
void __create_float32(ubjs_prmtv **);
void __create_float64(ubjs_prmtv **);
void __create_char(ubjs_prmtv **);
void __create_str(ubjs_prmtv **);
void __create_array(ubjs_prmtv **);
void __create_object(ubjs_prmtv **);

void __test_null(ubjs_prmtv *);
void __test_noop(ubjs_prmtv *);
void __test_false(ubjs_prmtv *);
void __test_true(ubjs_prmtv *);
void __test_int8(ubjs_prmtv *);
void __test_uint8(ubjs_prmtv *);
void __test_int16(ubjs_prmtv *);
void __test_int32(ubjs_prmtv *);
void __test_int64(ubjs_prmtv *);
void __test_float32(ubjs_prmtv *);
void __test_float64(ubjs_prmtv *);
void __test_char(ubjs_prmtv *);
void __test_str(ubjs_prmtv *);
void __test_array(ubjs_prmtv *);
void __test_object(ubjs_prmtv *);

void suite_primitives(tcontext *);

void test_prmtv_common();
void test_prmtv_null();
void test_prmtv_noop();
void test_prmtv_true();
void test_prmtv_false();
void test_prmtv_int8();
void test_prmtv_uint8();
void test_prmtv_int16();
void test_prmtv_int32();
void test_prmtv_int64();
void test_prmtv_float32();
void test_prmtv_float64();
void test_prmtv_char();
void test_prmtv_str();
void test_prmtv_array();
void test_prmtv_object();
void test_prmtv_calls_for_wrong_primitives();

#endif
