#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

int main(int argc, char **argv)
{
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    suite_trie();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int exitcode = (0 == CU_get_number_of_tests_failed()) ? 0 : 1;

    CU_cleanup_registry();
    return exitcode;
}
