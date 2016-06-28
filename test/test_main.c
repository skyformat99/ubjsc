#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

int main(int argc, char **argv)
{
    tcontext *ctx;
    install_tests(&ctx);

    unsigned int exitcode = (0 == tcontext_run(ctx) ? 0 : 1);
    tcontext_free(&ctx);
    return exitcode;
}
