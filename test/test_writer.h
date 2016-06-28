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

#endif

