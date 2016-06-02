#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"
#include "test_list.h"

int main(int argc, char **argv)
{
    CU_pSuite suite = 0;
    int i;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    install_tests();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int exitcode = (0 == CU_get_number_of_tests_failed()) ? 0 : 1;

    CU_cleanup_registry();
    return exitcode;
}
