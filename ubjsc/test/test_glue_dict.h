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

#ifndef HAVE_TEST_GLUE_DICT
#define HAVE_TEST_GLUE_DICT

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"
#include <ubjs.h>

void suite_glue_dict(tcontext *, char *, ubjs_glue_dict_factory);
void test_glue_dict_allocation();
void test_glue_dict_usage();
void test_glue_dict_performance();

typedef struct test_kv test_kv;
struct test_kv
{
    test_kv *prev;
    test_kv *next;
    char *key;
    unsigned int key_length;
};

void test_kv_free(test_kv *);
test_kv *test_kv_new();

#define TERROR_DICT_KV(it, trie, kv, pchr) terror_dict_kv(__FILE__, __LINE__, \
    it, trie, kv, pchr)
void terror_dict_kv(char *, unsigned int, unsigned int, ubjs_glue_dict *,
    test_kv *, char *);
void random_str(unsigned int, char *);
void scrum(char **, char *, ...);

void test_iteration(unsigned int);

#ifdef __cplusplus
}
#endif

#endif
