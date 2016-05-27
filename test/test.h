#ifndef HAVE_TEST
#define HAVE_TEST

#include "CUnit/Basic.h"
#include "../ubjs/ubjs.h"

void test_common_endian();

void test_parser_init_clean();
void test_parser_basics();

void test_writer_init_clean();
void test_writer_basics();

void test_object_null();
void test_parser_null();
void test_writer_null();

void test_object_noop();
void test_parser_noop();
void test_writer_noop();

void test_object_true();
void test_parser_true();
void test_writer_true();

void test_object_false();
void test_parser_false();
void test_writer_false();

void test_object_int8();
void test_parser_int8();
void test_writer_int8();

void test_object_uint8();
void test_parser_uint8();
void test_writer_uint8();

void test_object_int16();
void test_parser_int16();
void test_writer_int16();

void test_object_int32();
void test_parser_int32();
void test_writer_int32();

void test_object_int64();
void test_parser_int64();
void test_writer_int64();

void test_object_float32();
void test_parser_float32();
void test_writer_float32();

void test_object_float64();
void test_parser_float64();
void test_writer_float64();

void test_object_char();
void test_parser_char();
void test_writer_char();

typedef struct
{
    char *name;
    CU_TestFunc method;
} atest;

extern atest tests[];

#endif

