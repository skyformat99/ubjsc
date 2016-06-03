#ifndef HAVE_TEST
#define HAVE_TEST

#include "CUnit/Basic.h"
#include "../include/ubjs.h"

CU_pSuite *suite_writer();

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
void test_writer_str_int8();
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

#endif

