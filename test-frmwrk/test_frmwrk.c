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
#include <time.h>

#include "test_frmwrk.h"
#include "test_list.h"

typedef struct twill_return_method twill_return_method;
typedef struct twill_return_item twill_return_item;
typedef struct ttest ttest;

test_list *current_mocks = 0;
void *tstate = 0;
void *tsuiteargs = 0;
void *targs = 0;

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
    void *args;
    test_list *tests;
};

struct ttest
{
    char *name;
    void *args;
    tbefore_f before;
    ttest_f test;
    tafter_f after;
};

struct twill_return_method
{
    char *method;
    test_list *list;
};

enum twill_return_item_type
{
    TRIT_O,
    TRIT_UI
};

struct twill_return_item
{
    enum twill_return_item_type type;
    union value
    {
        void *vo;
        unsigned int vui;
    } value;
    char *comment;
};

static void ttest_new(char *, tbefore_f, ttest_f, tafter_f, void *, ttest **);
static void ttest_free(ttest **);
static void ttest_run(ttest *);

void twill_return_method_free(void **x)
{
    unsigned int len;

    twill_return_method *m = (twill_return_method *)*x;

    test_list_len(m->list, &len);
    if (0 != len)
    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unused %u mocks exist for method %s", len, m->method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unused %u mocks exist for method %s", len, m->method);
        cr_expect_fail("%s", x);
        free(x);
    }

    test_list_free(&(m->list));
    free(m->method);
    free(m);
    *x=0;
}

void twill_return_item_free(void **x)
{
    twill_return_item *it = (twill_return_item *)*x;
    free(it->comment);
    free(it);
    *x=0;
}

void twill_return_add(char *method, twill_return_item* item)
{
    test_list_item *at = current_mocks->sentinel->next;
    twill_return_method *m = 0;

    while (at != current_mocks->sentinel)
    {
        m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_add(m->list, item, 0);
            return;
        }
        at = at->next;
    }

    m = (twill_return_method *)malloc(sizeof(struct twill_return_method));
    m->method = strdup(method);
    test_list_new(twill_return_item_free, &(m->list));
    test_list_add(current_mocks, m, 0);
    test_list_add(m->list, item, 0);
}

int tmockui(char *method, unsigned int *value)
{
    test_list_item *at = current_mocks->sentinel->next;
    *value = 0;

    while (at != current_mocks->sentinel)
    {
        twill_return_method *m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_item *b = m->list->sentinel->next;
            twill_return_item *item = (twill_return_item *)b->obj;
            unsigned int len;

            *value = item->value.vui;
            //printf("TMOCKUI %s %d (%s)\n", method, *value, item->comment);

            test_list_remove(m->list, b);
            test_list_len(m->list, &len);

            if (0 == len)
            {
                test_list_remove(current_mocks, at);
            }

            return 1;
        }
        at = at->next;
    }

    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unexpected mock for method %s", method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unexpected mock for method %s", method);
        cr_expect_eq("%s", x);
        free(x);
    }

    return 0;
}

int tmocko(char *method, void **value)
{
    test_list_item *at = current_mocks->sentinel->next;
    *value = 0;

    while (at != current_mocks->sentinel)
    {
        twill_return_method *m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_item *b = m->list->sentinel->next;
            twill_return_item *item = (twill_return_item *)b->obj;
            unsigned int len;

            *value = item->value.vo;
            //printf("TMOCKO %s %p (%s)\n", method, *value, item->comment);

            test_list_remove(m->list, b);
            test_list_len(m->list, &len);

            if (0 == len)
            {
                test_list_remove(current_mocks, at);
            }

            return 1;
        }
        at = at->next;
    }

    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unexpected mock for method %s", method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unexpected mock for method %s", method);
        cr_expect_fail("%s", x);
        free(x);
    }

    return 0;
}

void twill_returno(char *method, void *value)
{
    twill_returnoc(method, value, 0);
}

void twill_returnoc(char *method, void *value, char *comment)
{
    twill_return_item *ri;
    ri = (twill_return_item *)malloc(sizeof(struct twill_return_item));
    ri->type=TRIT_O;
    ri->value.vo=value;
    ri->comment = comment != 0 ? strdup(comment) : 0;
    twill_return_add(method, ri);
}

void twill_returnui(char *method, unsigned int value)
{
    twill_returnuic(method, value, 0);
}

void twill_returnuic(char *method, unsigned int value, char *comment)
{
    twill_return_item *ri;
    ri = (twill_return_item *)malloc(sizeof(struct twill_return_item));
    ri->type=TRIT_UI;
    ri->value.vui=value;
    ri->comment = comment != 0 ? strdup(comment) : 0;
    twill_return_add(method, ri);
}

int tassert_equal(char *file, unsigned int line, char *left_expr, char *right_expr, int result)
{
    cr_expect_eq(1, result, "Expected %s to equal %s", left_expr, right_expr);
    return 1 != result;
}

int tassert_equali(char *file, unsigned int line, char *left_expr, char *right_expr, long left,
    long right)
{
    cr_expect_eq(left, right, "Expected %s to equal %s. Actually %ld != %ld.",
        left_expr, right_expr, left, right);
    return left != right;
}

int tassert_equalc(char *file, unsigned int line, char *left_expr, char *right_expr, char left,
    char right)
{
    cr_expect_eq(left, right, "Expected %s to equal %s. Actually %c != %c.",
        left_expr, right_expr, left, right);
    return left != right;
}

int tassert_equalui(char *file, unsigned int line, char *left_expr, char *right_expr,
    unsigned long left, unsigned long right)
{
    cr_expect_eq(left, right, "Expected %s to equal %s. Actually %lu != %lu.",
        left_expr, right_expr, left, right);
    return left != right;
}

int tassert_nstring_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    char *len_expr, char *left_result, char *right_result, int slen)
{
    int ret = strncmp(left_result, right_result, slen);
    cr_expect_eq(0, ret, "Expected %s to equal %s up to %d bytes. Actually:\n<%.*s>\n !=\n<%.*s>",
        left_expr, right_expr, slen, slen, left_result, slen, right_result);
    return ret != 0;
}

int tassert_string_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    char *left_result, char *right_result)
{
    int ret = strcmp(left_result, right_result);
    cr_expect_eq(0, ret, "Expected %s to equal %s. Actually: <%s> != <%s>",
        left_expr, right_expr, left_result, right_result);
    return 0 != ret;
}

int tassert_not_equal(char *file, unsigned int line, char *left_expr, char *right_expr,
    int result)
{
    cr_expect_eq(1, result, "Expected %s to not equal %s.", left_expr, right_expr);
    return result != 1;
}

/*
void tnot_implemented(char *file, unsigned int line)
{
    cr_expect_fail("%s", "Not implemented");
}
*/

void terror(char *file, unsigned int line, char *error)
{
    cr_log_error("%s", error);
    cr_expect_fail("%s", error);
}

static void ttest_new(char *name, tbefore_f before, ttest_f test, tafter_f after,
    void *args, ttest **pthis)
{
    ttest *this=(ttest *)malloc(sizeof(struct ttest));

    this->name=(char *)malloc(sizeof(char)*(strlen(name)+1));
    strncpy(this->name, name, strlen(name)+1);
    this->before=before;
    this->test=test;
    this->after=after;
    this->args=args;

    *pthis=this;
}

static void ttest_free(ttest **pthis)
{
    ttest *this=*pthis;

    free(this->name);
    free(this);
    *pthis=0;
}

static void ttest_run(ttest *this)
{
    test_list_new(twill_return_method_free, &current_mocks);
    tstate = 0;
    targs = this->args;

    if (0 != this->before)
    {
        (this->before)();
    }
    (this->test)();
    if (0 != this->after)
    {
        (this->after)();
    }
    test_list_free(&current_mocks);
}

void tsuite_new(char *name, tbefore_f before, tafter_f after, void *args,
     char *file, tsuite **pthis)
{
    tsuite *this=(tsuite *)malloc(sizeof(struct tsuite));

    this->name=strdup(name);
    this->file=strdup(file);
    this->args=args;
    this->before=before;
    this->after=after;

    test_list_new((test_list_free_f)ttest_free, &(this->tests));
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

void tsuite_add_test(tsuite *this, char *name, ttest_f test, void *args)
{
    ttest *atest;
    ttest_new(name, this->before, test, this->after, args, &atest);
    test_list_add(this->tests, atest, 0);
}

void tsuite_run(tsuite *this)
{
    test_list_item *test_it=0;
    tsuiteargs = this->args;

    for (test_it=this->tests->sentinel->next; test_it!=this->tests->sentinel; test_it=test_it->next)
    {
        ttest *test = (ttest *)test_it->obj;
        fprintf(stderr, "    [%s] ...\n", test->name);

        ttest_run(test);
    }
}

void tcontext_new(tcontext **pthis)
{
    tcontext *this=(tcontext *)malloc(sizeof(struct tcontext));

    this->suites = 0;
    test_list_new((test_list_free_f)tsuite_free, &(this->suites));

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
    test_list_add(this->suites, suite, 00);
}

void tcontext_run(tcontext *this)
{
    test_list_item *suite_it=0;

    for (suite_it=this->suites->sentinel->next;
        suite_it!=this->suites->sentinel;
        suite_it=suite_it->next)
    {
        tsuite *suite = (tsuite *)suite_it->obj;
        fprintf(stderr, "... [%s]\n", suite->name);

        tsuite_run(suite);
    }
}

void tbefore(void)
{
    test_list_new(twill_return_method_free, &current_mocks);
    tstate = 0;
}

void tafter(void)
{
    test_list_free(&current_mocks);
    tstate = 0;
}
