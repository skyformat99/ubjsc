#ifndef HAVE_TEST_OBJECTS
#define HAVE_TEST_OBJECTS

#include "CUnit/Basic.h"
#include "../include/ubjs.h"

CU_pSuite suite_objects();

void test_object_null();
void test_object_noop();
void test_object_true();
void test_object_false();
void test_object_int8();
void test_object_uint8();
void test_object_int16();
void test_object_int32();
void test_object_int64();
void test_object_float32();
void test_object_float64();
void test_object_char();
void test_object_str();
void test_object_array();

#endif

