/*
 * Copyright (c) 2016 Tomasz Sieprawski
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

#ifndef HAVE_TEST_GLUE_ARRAY
#define HAVE_TEST_GLUE_ARRAY

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs.h>
#include "test_frmwrk.h"
#include "test_glue_common.h"

void suite_glue_array(tcontext *, char *, ubjs_glue_array_factory);
void suite_glue_array_before(void);
void suite_glue_array_after(void);
void test_glue_array_allocation(void);
void test_glue_array_usage(void);
void test_glue_array_performance(void);

typedef struct test_array_expected test_array_expected;
struct test_array_expected
{
    test_array_expected *prev;
    test_array_expected *next;
    char *value;
};

void test_array_expected_free(test_array_expected *);
test_array_expected *test_array_expected_new(void);

#define TERROR_ARRAY_EXPECTED(it, trie, expected, pchr) terror_array_expected(__FILE__, __LINE__, \
    it, trie, expected, pchr)
void terror_array_expected(char *, unsigned int, unsigned int, ubjs_glue_array *,
    test_array_expected *, char *);
void test_glue_array_iteration(unsigned int);

#ifdef __cplusplus
}
#endif

#endif
