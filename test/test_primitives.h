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

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"
#include "../include/ubjs.h"

typedef void (*ubjs_test_primitives_create)(ubjs_prmtv **);
typedef void (*ubjs_test_primitives_test)(ubjs_prmtv *);

struct ubjs_test_primitive
{
    ubjs_test_primitives_create create;
    ubjs_test_primitives_test test;
};

typedef struct ubjs_test_primitive ubjs_test_primitive;

extern unsigned int ubjs_test_primitives_len;
extern ubjs_test_primitive ubjs_test_primitives[];

void ubjs_test_primitives_create_null(ubjs_prmtv **);
void ubjs_test_primitives_create_noop(ubjs_prmtv **);
void ubjs_test_primitives_create_false(ubjs_prmtv **);
void ubjs_test_primitives_create_true(ubjs_prmtv **);
void ubjs_test_primitives_create_int8(ubjs_prmtv **);
void ubjs_test_primitives_create_uint8(ubjs_prmtv **);
void ubjs_test_primitives_create_int16(ubjs_prmtv **);
void ubjs_test_primitives_create_int32(ubjs_prmtv **);
void ubjs_test_primitives_create_int64(ubjs_prmtv **);
void ubjs_test_primitives_create_float32(ubjs_prmtv **);
void ubjs_test_primitives_create_float64(ubjs_prmtv **);
void ubjs_test_primitives_create_char(ubjs_prmtv **);
void ubjs_test_primitives_create_str(ubjs_prmtv **);
void ubjs_test_primitives_create_array(ubjs_prmtv **);
void ubjs_test_primitives_create_object(ubjs_prmtv **);

void ubjs_test_primitives_test_null(ubjs_prmtv *);
void ubjs_test_primitives_test_noop(ubjs_prmtv *);
void ubjs_test_primitives_test_false(ubjs_prmtv *);
void ubjs_test_primitives_test_true(ubjs_prmtv *);
void ubjs_test_primitives_test_int8(ubjs_prmtv *);
void ubjs_test_primitives_test_uint8(ubjs_prmtv *);
void ubjs_test_primitives_test_int16(ubjs_prmtv *);
void ubjs_test_primitives_test_int32(ubjs_prmtv *);
void ubjs_test_primitives_test_int64(ubjs_prmtv *);
void ubjs_test_primitives_test_float32(ubjs_prmtv *);
void ubjs_test_primitives_test_float64(ubjs_prmtv *);
void ubjs_test_primitives_test_char(ubjs_prmtv *);
void ubjs_test_primitives_test_str(ubjs_prmtv *);
void ubjs_test_primitives_test_array(ubjs_prmtv *);
void ubjs_test_primitives_test_object(ubjs_prmtv *);

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


#ifdef __cplusplus
}
#endif

#endif
