#include "test.h"
#include "test_list.h"

#include "test_common.h"
#include "test_primitives.h"
#include "test_parser.h"
#include "test_writer.h"

void install_tests() {
    /*suite_common();
    suite_objects();
    suite_parser();*/
    suite_writer();
}

