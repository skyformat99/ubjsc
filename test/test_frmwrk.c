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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_frmwrk.h"
#include "test_list.h"

typedef struct ttest ttest;
typedef struct tresults tresults;
typedef struct tresults_suite tresults_suite;
typedef struct tresults_test tresults_test;
typedef struct tresults_assert tresults_assert;

tresults_test *current_test;

struct tresults
{
    int failed;
    unsigned int suites_run;
    unsigned int suites_failed;
    unsigned int tests_run;
    unsigned int tests_failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *suites;
};

struct tresults_suite
{
    tresults *results;
    tsuite *suite;
    int failed;
    unsigned int tests_run;
    unsigned int tests_failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *tests;
};

struct tresults_test
{
    tresults_suite *suite;
    ttest *test;
    int failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *asserts;
};

struct tresults_assert
{
    tresults_test *test;
    char *file;
    unsigned int line;
    char *comment;
};

struct tcontext
{
    test_list *suites;
};

struct tsuite
{
    char *name;
    char *file;
    tbefore_f before;
    tafter_f after;
    test_list *tests;
};

struct ttest
{
    char *name;
    ttest_f test;
};

static void ttest_new(char *, ttest_f, ttest **);
static void ttest_free(ttest **);
static void ttest_run(ttest *, tresults_test **);

static void tresults_assert_new(char *, unsigned int, char *, tresults_assert **);
static void tresults_assert_free(tresults_assert **);

static void tresults_test_new(ttest *, tresults_test **);
static void tresults_test_free(tresults_test **);
static void tresults_test_add_assert(tresults_test *, tresults_assert *);
static void tresults_test_print(tresults_test *);

static void tresults_suite_new(tsuite *, tresults_suite **);
static void tresults_suite_free(tresults_suite **);
static void tresults_suite_add_test(tresults_suite *, tresults_test *);
static void tresults_suite_print(tresults_suite *);

static void tresults_new(tresults **);
static void tresults_free(tresults **);
static void tresults_add_suite(tresults *, tresults_suite *);
static void tresults_print(tresults *);

void tresults_assert_new(char *file, unsigned int line, char *comment, tresults_assert **pthis)
{
    tresults_assert *this=(tresults_assert *)malloc(sizeof(struct tresults_assert));

    this->test=0;
    this->file=file;
    this->line=line;
    this->comment=comment;

    *pthis = this;
}

void tresults_assert_free(tresults_assert **pthis)
{
    tresults_assert *this=*pthis;

    free(this->comment);
    free(this);

    *pthis=0;
}

void tassert_equal(char *file, unsigned int line, char *left_expr, char *right_expr, int result)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (result==1)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

void tassert_equali(char *file, unsigned int line, char *left_expr, char *right_expr, long left,
    long right)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s. Actually %ld != %ld.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (left == right)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr, left, right);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, left, right);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

void tassert_equalc(char *file, unsigned int line, char *left_expr, char *right_expr, char left,
    char right)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s. Actually %c != %c.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (left == right)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr, left, right);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, left, right);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

void tassert_equalui(char *file, unsigned int line, char *left_expr, char *right_expr,
    unsigned long left, unsigned long right)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s. Actually %lu != %lu.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (left == right)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr, left, right);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, left, right);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

/*
void tassert_equalli(char *file, unsigned int line, char *left_expr, char *right_expr, long left,
    long right)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s. Actually %li != %li.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (left == right)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr, left, right);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, left, right);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}
*/

void tassert_nstring_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    char *len_expr, char *left_result, char *right_result, int slen)
{
    char *message=0;
    char *actually_left;
    char *actually_right;
    static char *fmt="Expected %s to equal %s up to %d bytes. Actually:\n<%s>\n !=\n<%s>";
    tresults_assert *result_assert=0;
    int ret = strncmp(left_result, right_result, slen);
    unsigned int len;

    if (ret==0)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    actually_left = (char *)malloc(sizeof(char) * (slen + 1));
    actually_right = (char *)malloc(sizeof(char) * (slen + 1));

    strncpy(actually_left, left_result, slen);
    actually_left[slen] = 0;

    strncpy(actually_right, right_result, slen);
    actually_right[slen] = 0;

    len=snprintf(0, 0, fmt, left_expr, right_expr, slen, actually_left, actually_right);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, slen, actually_left, actually_right);
    free(actually_left);
    free(actually_right);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

void tassert_string_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    char *left_result, char *right_result)
{
    char *message=0;
    static char *fmt="Expected %s to equal %s. Actually: <%s> != <%s>";
    tresults_assert *result_assert=0;
    int ret = strcmp(left_result, right_result);
    unsigned int len;

    if (ret==0)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr, left_result, right_result);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr, left_result, right_result);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

void tassert_not_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    int result)
{
    char *message=0;
    static char *fmt="Expected %s to not equal %s.";
    tresults_assert *result_assert=0;
    unsigned int len;

    if (result==1)
    {
        tresults_test_add_assert(current_test, 0);
        return;
    }

    len=snprintf(0, 0, fmt, left_expr, right_expr);
    message=(char *)malloc(sizeof(char)*(len+1));
    snprintf(message, len+1, fmt, left_expr, right_expr);

    tresults_assert_new(file, line, message, &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}

/*
void tnot_implemented(char *file, unsigned int line)
{
    tresults_assert *result_assert=0;

    tresults_assert_new(file, line, strdup("Not implemented"), &result_assert);
    tresults_test_add_assert(current_test, result_assert);
}
*/

void tresults_test_new(ttest *test, tresults_test **pthis)
{
    tresults_test *this=(tresults_test *)malloc(sizeof(struct tresults_test));

    this->failed=0;
    this->suite=0;
    this->test=test;
    this->asserts_run=0;
    this->asserts_failed=0;
    test_list_new(&(this->asserts));

    *pthis = this;
}

void tresults_test_free(tresults_test **pthis)
{
    tresults_test *this=*pthis;

    test_list_free(&(this->asserts));
    free(this);

    *pthis=0;
}

void tresults_test_add_assert(tresults_test *this, tresults_assert *assert)
{
    if (assert!=0)
    {
        assert->test=this;
        test_list_add(this->asserts, assert, (test_list_free_f)tresults_assert_free);
        this->failed=1;
        this->asserts_failed++;
    }

    this->asserts_run++;
}

void tresults_test_print(tresults_test *this)
{
    test_list *it;
    unsigned int i;

    if (1 == this->failed)
    {
        printf("      %s (asserts failed: %u/%u)\n",
            this->failed ? "FAILED" : "pass", this->asserts_failed, this->asserts_run);
    }

    for (it=this->asserts->next, i=0; it != this->asserts; it=it->next, i++)
    {
        tresults_assert *assert = (tresults_assert *)it->obj;
        printf("          [%u/%u][%s][%u] %s\n", i+1,
            this->asserts_failed, assert->file, assert->line, assert->comment);
    }
}

void tresults_suite_new(tsuite *suite, tresults_suite **pthis)
{
    tresults_suite *this=(tresults_suite *)malloc(sizeof(struct tresults_suite));

    this->failed=0;
    this->results=0;
    this->suite=suite;
    this->tests_run=0;
    this->tests_failed=0;
    this->asserts_run=0;
    this->asserts_failed=0;
    test_list_new(&(this->tests));

    *pthis = this;
}

void tresults_suite_free(tresults_suite **pthis)
{
    tresults_suite *this=*pthis;

    test_list_free(&(this->tests));
    free(this);

    *pthis=0;
}

void tresults_suite_add_test(tresults_suite *this, tresults_test *test)
{
    test->suite=this;
    test_list_add(this->tests, test, (test_list_free_f)tresults_test_free);

    if (1 == test->failed)
    {
        this->failed=1;
        this->tests_failed++;
    }

    this->tests_run++;
    this->asserts_run+=test->asserts_run;
    this->asserts_failed+=test->asserts_failed;
}

void tresults_suite_print(tresults_suite *this)
{
    test_list *it;
    unsigned int i;

    if (1 == this->failed)
    {
        printf("    How many tests   failed? %u of %u\n", this->tests_failed, this->tests_run);
        printf("    How many asserts failed? %u of %u\n", this->asserts_failed, this->asserts_run);
        printf("\n");
    }

    for (it=this->tests->next, i=0; it != this->tests; it=it->next, i++)
    {
        tresults_test *test = (tresults_test *)it->obj;
        if (1 == test->failed)
        {
            printf("    [%u/%u] %s\n", i+1, this->tests_run, test->test->name);
        }
        tresults_test_print(test);
    }
}

void tresults_new(tresults **pthis)
{
    tresults *this=(tresults *)malloc(sizeof(struct tresults));
    this->failed=0;
    this->suites_run=0;
    this->suites_failed=0;
    this->tests_run=0;
    this->tests_failed=0;
    this->asserts_run=0;
    this->asserts_failed=0;
    test_list_new(&(this->suites));

    *pthis = this;
}

void tresults_free(tresults **pthis)
{
    tresults *this=*pthis;

    test_list_free(&(this->suites));
    free(this);

    *pthis=0;
}

void tresults_add_suite(tresults *this, tresults_suite *suite)
{
    suite->results=this;
    test_list_add(this->suites, suite, (test_list_free_f)tresults_suite_free);

    if (1 == suite->failed)
    {
        this->failed=1;
        this->suites_failed++;
    }

    this->suites_run++;
    this->tests_run+=suite->tests_run;
    this->tests_failed+=suite->tests_failed;
    this->asserts_run+=suite->asserts_run;
    this->asserts_failed+=suite->asserts_failed;
}

void tresults_print(tresults *this)
{
    test_list *it;
    unsigned int i;

    printf("========================================\n");
    printf("              RESULTS\n");
    printf("\n");
    printf("    Did tests fail?          %s\n", this->failed ? "YES!@#$" : "no :)");

    if (1 == this->failed)
    {
        printf("    How many suites  failed? %u of %u\n", this->suites_failed, this->suites_run);
        printf("    How many tests   failed? %u of %u\n", this->tests_failed, this->tests_run);
        printf("    How many asserts failed? %u of %u\n", this->asserts_failed, this->asserts_run);
        printf("\n");

        for (it=this->suites->next, i=0; it != this->suites; it=it->next, i++)
        {
            tresults_suite *suite = (tresults_suite *)it->obj;
            if (1 == suite->failed)
            {
                printf("[%u/%u] %s\n", i+1, this->suites_run, suite->suite->name);
            }
            tresults_suite_print(suite);
        }
    }

    printf("========================================\n");
}

static void ttest_new(char *name, ttest_f test, ttest **pthis)
{
    ttest *this=(ttest *)malloc(sizeof(struct ttest));

    this->name=(char *)malloc(sizeof(char)*(strlen(name)+1));
    strncpy(this->name, name, strlen(name)+1);
    this->test=test;

    *pthis=this;
}

static void ttest_free(ttest **pthis)
{
    ttest *this=*pthis;

    free(this->name);
    free(this);
    *pthis=0;
}

static void ttest_run(ttest *this, tresults_test **presults)
{
    tresults_test *results;
    tresults_test_new(this, &results);

    current_test = results;
    (this->test)();

    *presults=results;
}

void tsuite_new(char *name, tbefore_f before, tafter_f after, char *file, tsuite **pthis)
{
    tsuite *this=(tsuite *)malloc(sizeof(struct tsuite));

    this->name=strdup(name);
    this->file=strdup(file);

    this->before=before;
    this->after=after;

    test_list_new(&(this->tests));
    *pthis=this;
}

void tsuite_free(tsuite **pthis)
{
    tsuite *this=*pthis;

    test_list_free(&(this->tests));
    free(this->name);
    free(this->file);
    free(this);
    *pthis=0;
}

void tsuite_add_test(tsuite *this, char *name, ttest_f test)
{
    ttest *atest;
    ttest_new(name, test, &atest);
    test_list_add(this->tests, atest, (test_list_free_f)ttest_free);
}

void tsuite_run(tsuite *this, tresults_suite **presults)
{
    tresults_suite *results;
    test_list *test_it=0;
    tresults_test *results_test=0;

    tresults_suite_new(this, &results);

    for (test_it=this->tests->next; test_it!=this->tests; test_it=test_it->next)
    {
        ttest *test = (ttest *)test_it->obj;
        ttest_run(test, &results_test);
        tresults_suite_add_test(results, results_test);
    }

    *presults=results;
}

void tcontext_new(tcontext **pthis)
{
    tcontext *this=(tcontext *)malloc(sizeof(struct tcontext));

    this->suites = 0;
    test_list_new(&(this->suites));

    *pthis=this;
}

void tcontext_free(tcontext **pthis)
{
    tcontext *this=*pthis;

    test_list_free(&(this->suites));
    free(this);

    *pthis=0;
}

void tcontext_add_suite(tcontext *this, tsuite *suite)
{
    test_list_add(this->suites, suite, (test_list_free_f)tsuite_free);
}

int tcontext_run(tcontext *this)
{
    tresults *results=0;

    test_list *suite_it=0;
    tresults_suite *results_suite=0;

    int ret;

    tresults_new(&results);

    for (suite_it=this->suites->next; suite_it!=this->suites; suite_it=suite_it->next)
    {
        tsuite *suite = (tsuite *)suite_it->obj;
        tsuite_run(suite, &results_suite);
        tresults_add_suite(results, results_suite);
    }

    ret = results->failed;

    tresults_print(results);
    tresults_free(&results);

    return ret;
}
