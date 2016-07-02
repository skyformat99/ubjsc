#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test_common.h"
#include "test_primitives.h"
#include "test_parser.h"
#include "test_writer.h"

int main(int argc, char **argv)
{
    tcontext *context;
    unsigned int exitcode;

    tcontext_new(&context);

    /*suite_common(context);
    suite_primitives(context);
    suite_parser(context);*/
    suite_writer(context);

    exitcode = (0 == tcontext_run(context) ? 0 : 1);
    tcontext_free(&context);

    return exitcode;
}
