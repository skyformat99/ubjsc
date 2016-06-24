#ifndef HAVE_TEST_PARSER
#define HAVE_TEST_PARSER

#include "CUnit/Basic.h"
#include "../include/ubjs.h"

CU_pSuite suite_parser();

void test_parser_bad_init();
void test_parser_init_clean();
void test_parser_basics();
void test_parser_unknown_marker();

void test_parser_null();
void test_parser_noop();
void test_parser_true();
void test_parser_false();
void test_parser_int8();
void test_parser_uint8();
void test_parser_int16();
void test_parser_int32();
void test_parser_int64();
void test_parser_float32();
void test_parser_float64();
void test_parser_char();

void test_parser_str_empty();
void test_parser_str_null();
void test_parser_str_noop();
void test_parser_str_true();
void test_parser_str_false();
void test_parser_str_uint8();
void test_parser_str_int8();
void test_parser_str_int8_negative();
void test_parser_str_int16();
void test_parser_str_int16_negative();
void test_parser_str_int32();
void test_parser_str_int32_negative();
void test_parser_str_int64();
void test_parser_str_char();
void test_parser_str_str();
void test_parser_str_float32();
void test_parser_str_float64();
void test_parser_str_array();
void test_parser_str_object();

void test_parser_array_empty();
void test_parser_array_null();
void test_parser_array_noop();
void test_parser_array_true();
void test_parser_array_false();
void test_parser_array_uint8();
void test_parser_array_int8();
void test_parser_array_int16();
void test_parser_array_int32();
void test_parser_array_int64();
void test_parser_array_float32();
void test_parser_array_float64();
void test_parser_array_char();
void test_parser_array_str();
void test_parser_array_array();
void test_parser_array_object();

void test_parser_object_empty();
void test_parser_object_null();
void test_parser_object_noop();
void test_parser_object_true();
void test_parser_object_false();
void test_parser_object_uint8();
void test_parser_object_int8();
void test_parser_object_int16();
void test_parser_object_int32();
void test_parser_object_int64();
void test_parser_object_float32();
void test_parser_object_float64();
void test_parser_object_char();
void test_parser_object_str();
void test_parser_object_array();
void test_parser_object_object();

#endif
