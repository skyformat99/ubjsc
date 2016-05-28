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
    //{"parser: str", test_parser_str},
    //{"writer: str", test_writer_str},

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
