#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"
#include "test_list.h"

int main(int argc, char **argv)
{
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    install_tests();

    CU_curses_run_tests();
    CU_cleanup_registry();
    return 0;
}
