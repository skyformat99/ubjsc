#include <stdlib.h>
#include <string.h>

#include "test_frmwrk.h"
#include "test_list.h"

typedef struct tresults tresults;
typedef struct tresults_suite tresults_suite;
typedef struct tresults_test tresults_test;
typedef struct tresults_assert tresults_assert;

tresults_test *current_test;

struct tresults {
    int failed;
    unsigned int suites_run;
    unsigned int suites_failed;
    unsigned int tests_run;
    unsigned int tests_failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *suites;
};

struct tresults_suite {
    int failed;
    unsigned int tests_run;
    unsigned int tests_failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *tests;
};

struct tresults_test {
    int failed;
    unsigned int asserts_run;
    unsigned int asserts_failed;
    test_list *asserts;
};

struct tresults_assert {
    char *file;
    unsigned int line;
    char *left_expr;
    char *right_expr;
    int left;
    int right;
};

struct tcontext {
    test_list *suites;
};

struct tsuite {
    char *name;
    test_list *tests;
};

void tresults_assert_new(tresults_assert **,char *,unsigned int,char *,char *,int,int);
void tresults_assert_free(tresults_assert **);
void tresults_assert_free_print(tresults_assert *);

void tassert_equal(char *file,unsigned int line,char *left_expr,char *right_expr,int left_result,int right_result);
void tassert_nstring_equal(char *,unsigned int,char *,char *,char*,char *,char *,int);
void tassert_not_equal(char *file,unsigned int line,char *left_expr,char *right_expr,int left_result,int right_result);

void tresults_test_new(tresults_test **);
void tresults_test_free(tresults_test **);
void tresults_test_add_assert(tresults_test *, tresults_assert *);
void tresults_test_print(tresults_test *);

void tresults_new(tresults **);
void tresults_free(tresults **);
void tresults_add_test(tresults *,tresults_test *);
void tresults_print(tresults *);

void tsuite_new(tbefore_f,tafter_f,tsuite **);
void tsuite_free(tsuite **);
void tsuite_add_test(tsuite *,char *,ttest_f);

void tcontext_new(tcontext **);
void tcontext_new(tcontext **);
void tcontext_add_suite(tcontext *,char *,tsuite *);
int tcontext_run(tcontext *);


void tresults_assert_new(tresults_assert **pthis,char *file,unsigned int line,char *left_expr,char *right_expr,int left_result,int right_result) {}
void tresults_assert_free(tresults_assert **pthis) {}
void tresults_assert_free_print(tresults_assert *);

void tassert_equal(char *file,unsigned int line,char *left_expr,char *right_expr,int left_result,int right_result) {}
void tassert_nstring_equal(char *file,unsigned int line,char *left_expr,char *right_expr,char *len_expr,char * left_result,char *right_result,int len) {}
void tassert_not_equal(char *file,unsigned int line,char *left_expr,char *right_expr,int left_result,int right_result) {}

void tresults_test_new(tresults_test **pthis) {}
void tresults_test_free(tresults_test **pthis) {}
void tresults_test_add_assert(tresults_test *this, tresults_assert *assert) {}
void tresults_test_print(tresults_test *this) {}

void tresults_new(tresults **pthis) {}
void tresults_free(tresults **pthis) {}
void tresults_add_test(tresults *this,tresults_test *test) {}
void tresults_print(tresults *this) {}

void tsuite_new(tbefore_f before,tafter_f after,tsuite **pthis) {}
void tsuite_free(tsuite **pthis) {}
void tsuite_add_test(tsuite *this,char *name,ttest_f test) {}

void tcontext_new(tcontext **pthis) {}
void tcontext_free(tcontext **pthis) {}
void tcontext_add_suite(tcontext *this,char *name,tsuite *suite) {}
int tcontext_run(tcontext *this) {
    return -1;
}
