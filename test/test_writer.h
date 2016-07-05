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

#ifndef HAVE_TEST_WRITER
#define HAVE_TEST_WRITER

#include "test_frmwrk.h"
#include "../include/ubjs.h"

void suite_writer(tcontext *);

void test_writer_init_clean();
void test_writer_basics();

void test_writer_null();
void test_writer_noop();
void test_writer_true();
void test_writer_false();
void test_writer_int8();
void test_writer_uint8();
void test_writer_int16();
void test_writer_int32();
void test_writer_int64();
void test_writer_float32();
void test_writer_float64();
void test_writer_char();

void test_writer_str_uint8();
void test_writer_str_int16();
void test_writer_str_int32();

void test_writer_array_empty();
void test_writer_array_uint8();
void test_writer_array_int8();
void test_writer_array_int16();
void test_writer_array_int32();
void test_writer_array_null();
void test_writer_array_noop();
void test_writer_array_true();
void test_writer_array_false();
void test_writer_array_char();
void test_writer_array_str();
void test_writer_array_int64();
void test_writer_array_float32();
void test_writer_array_float64();
void test_writer_array_array();
void test_writer_array_object();

void test_writer_array_count_optimized_uint8();
void test_writer_array_count_optimized_int16();
void test_writer_array_count_optimized_int32();

void test_writer_object_empty();
void test_writer_object_uint8();
void test_writer_object_int8();
void test_writer_object_int16();
void test_writer_object_int32();
void test_writer_object_null();
void test_writer_object_noop();
void test_writer_object_true();
void test_writer_object_false();
void test_writer_object_char();
void test_writer_object_str();
void test_writer_object_int64();
void test_writer_object_float32();
void test_writer_object_float64();
void test_writer_object_array();
void test_writer_object_object();

void test_writer_object_count_optimized_uint8();
void test_writer_object_count_optimized_int16();
void test_writer_object_count_optimized_int32();

#endif
