#ifndef HAVE_TEST_OBJECTS
#define HAVE_TEST_OBJECTS

#include "CUnit/Basic.h"
#include "../include/ubjs.h"

CU_pSuite suite_objects();

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

#endif

