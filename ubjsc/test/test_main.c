/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <test_frmwrk.h>
#include "test_common.h"
#include "test_primitives.h"
#include "test_parser.h"
#include "test_writer.h"
#include "test_glue_dict.h"
#include "test_glue_array.h"

#include <ubjs_glue_dict_list.h>
#include <ubjs_glue_array_list.h>

int main(int argc, char **argv)
{
    tcontext *context;
    unsigned int exitcode;

    tcontext_new(&context);

    suite_common(context);
    suite_primitives(context);
    suite_parser(context);
    suite_writer(context);
    suite_glue_dict(context, "glue_dict_list", ubjs_glue_dict_list_factory);
    suite_glue_array(context, "glue_array_list", ubjs_glue_array_list_factory);

    exitcode = (0 == tcontext_run(context) ? 0 : 1);
    tcontext_free(&context);

    return exitcode;
}
