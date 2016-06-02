#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"
#include "test_list.h"

atest tests[] =
{
    {"common: endian", test_common_endian},

    {"parser: init clean", test_parser_init_clean},
    {"parser: basics", test_parser_basics},
    {"parser: unknown marker", test_parser_unknown_marker},

    {"writer: init clean", test_writer_init_clean},
    {"writer: basics", test_writer_basics},

    {"object: null", test_object_null},
    {"parser: null", test_parser_null},
    {"writer: null", test_writer_null},

    {"object: noop", test_object_noop},
    {"parser: noop", test_parser_noop},
    {"writer: noop", test_writer_noop},

    {"object: true", test_object_true},
    {"parser: true", test_parser_true},
    {"writer: true", test_writer_true},

    {"object: false", test_object_false},
    {"parser: false", test_parser_false},
    {"writer: false", test_writer_false},

    {"object: int8", test_object_int8},
    {"parser: int8", test_parser_int8},
    {"writer: int8", test_writer_int8},

    {"object: uint8", test_object_uint8},
    {"parser: uint8", test_parser_uint8},
    {"writer: uint8", test_writer_uint8},

    {"object: int16", test_object_int16},
    {"parser: int16", test_parser_int16},
    {"writer: int16", test_writer_int16},

    {"object: int32", test_object_int32},
    {"parser: int32", test_parser_int32},
    {"writer: int32", test_writer_int32},

    {"object: int64", test_object_int64},
    {"parser: int64", test_parser_int64},
    {"writer: int64", test_writer_int64},

    {"object: float32", test_object_float32},
    {"parser: float32", test_parser_float32},
    {"writer: float32", test_writer_float32},

    {"object: float64", test_object_float64},
    {"parser: float64", test_parser_float64},
    {"writer: float64", test_writer_float64},

    {"object: char", test_object_char},
    {"parser: char", test_parser_char},
    {"writer: char", test_writer_char},

    {"object: str", test_object_str},
    {"parser: str empty", test_parser_str_empty},
    {"parser: str with length uint8", test_parser_str_uint8},
    {"parser: str with length int8", test_parser_str_int8},
    {"parser: str with bad length negative int8", test_parser_str_int8_negative},
    {"parser: str with length int16", test_parser_str_int16},
    {"parser: str with bad length negative int16", test_parser_str_int16_negative},
    {"parser: str with length int32", test_parser_str_int32},
    {"parser: str with bad length negative int32", test_parser_str_int32_negative},
    {"parser: str with bad length null", test_parser_str_null},
    {"parser: str with bad length noop", test_parser_str_noop},
    {"parser: str with bad length true", test_parser_str_true},
    {"parser: str with bad length false", test_parser_str_false},
    {"parser: str with bad length char", test_parser_str_char},
    {"parser: str with bad length str", test_parser_str_str},
    {"parser: str with bad length int64", test_parser_str_int64},
    {"parser: str with bad length float32", test_parser_str_float32},
    {"parser: str with bad length float64", test_parser_str_float64},
    {"writer: str with length uint8", test_writer_str_uint8},
    {"writer: str with length int16", test_writer_str_int16},
    {"writer: str with length int32", test_writer_str_int32},

    {"object: array", test_object_array},

    {"parser: array empty", test_parser_array_empty},
    {"parser: array with 1 uint8", test_parser_array_uint8},
    /*void test_parser_array_int8();
    void test_parser_array_int16();
    void test_parser_array_int32();
    void test_parser_array_null();
    void test_parser_array_noop();
    void test_parser_array_true();
    void test_parser_array_false();
    void test_parser_array_char();
    void test_parser_array_str();
    void test_parser_array_int64();
    void test_parser_array_float32();
    void test_parser_array_float64();
    */
    {0, 0}
};

int main(int argc, char **argv)
{
    CU_pSuite suite = 0;
    int i;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    suite = CU_add_suite("tests", 0, 0);
    if (NULL == suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(i=0; 0 != tests[i].name; i++)
    {
        if (NULL == CU_add_test(suite, tests[i].name, tests[i].method))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0 == CU_get_number_of_tests_failed() ? 0 : 1;
}
