#include "test.h"
#include "test_list.h"

#include "test_common.h"
#include "test_primitives.h"
#include "test_parser.h"
#include "test_writer.h"

void install_tests(tcontext **pcontext) {
    tcontext *context;

    tcontext_new(&context);
    suite_common(context);
    suite_primitives(context);
    suite_parser(context);
    suite_writer(context);

    *pcontext=context;
}

