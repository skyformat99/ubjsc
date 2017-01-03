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

#ifndef HAVE_TEST_GLUE_DICT
#define HAVE_TEST_GLUE_DICT

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs.h>
#include "test_frmwrk.h"
#include "test_glue_common.h"

void suite_glue_dict(tcontext *, char *, ubjs_glue_dict_factory);
void suite_glue_dict_before(void);
void suite_glue_dict_after(void);
void test_glue_dict_allocation(void);
void test_glue_dict_usage(void);
void test_glue_dict_performance(void);

typedef struct test_dict_expected test_dict_expected;
struct test_dict_expected
{
    test_dict_expected *prev;
    test_dict_expected *next;
    char *key;
    unsigned int key_length;
};

void test_dict_expected_free(test_dict_expected *);
test_dict_expected *test_dict_expected_new(void);

#define TERROR_DICT_EXPECTED(it, dict, expected, pchr) terror_dict_expected(__FILE__, __LINE__, \
    it, dict, expected, pchr)
void terror_dict_expected(char *, unsigned int, unsigned int, ubjs_glue_dict *,
    test_dict_expected *, char *);
void test_glue_dict_iteration(unsigned int);

#ifdef __cplusplus
}
#endif

#endif
