/*
 * Copyright (c) 2017 Tomasz Sieprawski
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

#include <test_common.h>
#include <test_glue_dict_generic.h>

static void before(void)
{
    suite_glue_dict_before_generic(ubjs_glue_dict_list_builder_new);
}

static void after(void)
{
    suite_glue_dict_after_generic();
}

TestSuite(glue_dict_list, .init = before, .fini = after);

Test(glue_dict_list, allocation)
{
    test_glue_dict_allocation(ubjs_glue_dict_list_builder_new);
}

Test(glue_dict_list, usage)
{
    test_glue_dict_usage(ubjs_glue_dict_list_builder_new);
}

Test(glue_dict_list, performance)
{
    test_glue_dict_performance(ubjs_glue_dict_list_builder_new);
}
