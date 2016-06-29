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
    tsuite *suite;
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
    tbefore_f before;
    tafter_f after;
    test_list *tests;
};

struct ttest {
    char *name;
    ttest_f test;
};

static void ttest_new(char *,ttest_f,ttest **);
static void ttest_free(ttest **);
static void ttest_run(ttest *);

void tresults_assert_new(tresults_assert **,char *,unsigned int,char *,char *,int,int);
void tresults_assert_free(tresults_assert **);
void tresults_assert_free_print(tresults_assert *);

void tresults_test_new(tresults_test **);
void tresults_test_free(tresults_test **);
void tresults_test_add_assert(tresults_test *, tresults_assert *);
void tresults_test_print(tresults_test *);

void tresults_suite_new(tresults_suite **);
void tresults_suite_free(tresults_suite **);
void tresults_suite_add_test(tresults_suite *,tresults_test *);
void tresults_suite_print(tresults_suite *);

void tresults_new(tresults **);
void tresults_free(tresults **);
void tresults_add_suite(tresults *,tresults_suite *);
void tresults_print(tresults *);

void tsuite_new(char *,tbefore_f,tafter_f,tsuite **);
void tsuite_free(tsuite **);
void tsuite_add_test(tsuite *,char *,ttest_f);

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

void tresults_suite_new(tresults_suite **pthis) {}
void tresults_suite_free(tresults_suite **pthis) {}
void tresults_suite_add_test(tresults_suite *this,tresults_test *test) {}
void tresults_suite_print(tresults_suite *this) {}

void tresults_new(tresults **pthis) {
    tresults *this=(tresults *)malloc(sizeof(struct tresults));
    this->failed=0;
    this->suites_run=0;
    this->suites_failed=0;
    this->tests_run=0;
    this->tests_failed=0;
    this->asserts_run=0;
    this->asserts_failed=0;
    this->suites=test_list_new();


    *pthis = this;
}

void tresults_free(tresults **pthis) {
    tresults *this=*pthis;

    test_list_free(this->suites);
    free(this);

    *pthis=0;
}

static void __tresults_suite_free(tresults_suite *this) {
    tresults_suite_free(&(this));
}


void tresults_add_suite(tresults *this,tresults_suite *suite) {
    test_list_add(this->suites, suite, (test_list_free_f)__tresults_suite_free);
}

void tresults_print(tresults *this) {
    test_list *it;
    tresults_suite *suite;
    unsigned int i;

    printf("========================================\n");
    printf("              RESULTS\n");
    printf("\n");
    printf("    Did tests failed?        %s\n", this->failed ? "YES!@#$" : "no :)");
    printf("    How many suites failed?  %d of %d\n", this->suites_failed, this->suites_run);
    printf("    How many suites tests?   %d of %d\n", this->tests_failed, this->tests_run);
    printf("    How many suites asserts? %d of %d\n", this->asserts_failed, this->asserts_run);
    printf("\n");
    printf("************\n");
    printf("              SUITES\n");
    printf("\n");

    for(it=this->suites->next, i=0; it != this->suites; it=it->next, i++) {
        suite=(tresults_suite *)it->obj;
        printf("[%d/%d] %s\n", suite->suite->name);
        tresults_suite_print(suite);
        printf("\n");
    }

    printf("========================================\n");

}

static void ttest_new(char *name,ttest_f test,ttest **pthis) {
    ttest *this=(ttest *)malloc(sizeof(struct ttest));

    this->name=(char *)malloc(sizeof(char)*(strlen(name)+1));
    strncpy(this->name, name, strlen(name)+1);
    this->test=test;

    *pthis=this;
}

static void ttest_free(ttest **pthis) {
    ttest *this=*pthis;

    free(this->name);
    free(this);
    *pthis=0;
}
static void ttest_run(ttest *this);

void tsuite_new(char *name,tbefore_f before,tafter_f after,tsuite **pthis) {
    tsuite *this=(tsuite *)malloc(sizeof(struct tsuite));

    this->name=(char *)malloc(sizeof(char)*(strlen(name)+1));
    strncpy(this->name,name,strlen(name)+1);

    this->before=before;
    this->after=after;

    this->tests=test_list_new();
    *pthis=this;
}

void tsuite_free(tsuite **pthis) {
    tsuite *this=*pthis;

    test_list_free(this->tests);
    free(this->name);
    free(this);
    *pthis=0;
}

static void __ttest_free(ttest *this) {
    ttest_free(&this);
}

void tsuite_add_test(tsuite *this,char *name,ttest_f test) {
    ttest *atest;
    ttest_new(name, test, &atest);
    test_list_add(this->tests, atest, (test_list_free_f)__ttest_free);
}

static void __tsuite_free(tsuite *this) {
    tsuite_free(&(this));
}

void tcontext_new(tcontext **pthis) {
    tcontext *this=(tcontext *)malloc(sizeof(struct tcontext));

    this->suites=test_list_new();

    *pthis=this;
}

void tcontext_free(tcontext **pthis) {
    tcontext *this=*pthis;

    test_list_free(this->suites);
    free(this);

    *pthis=0;
}

void tcontext_add_suite(tcontext *this,tsuite *suite) {
    test_list_add(this->suites, suite, (test_list_free_f)__tsuite_free);
}

int tcontext_run(tcontext *this) {
    tresults *results=0;
    int ret;

    tresults_new(&results);

    ret = results->failed;

    tresults_print(results);
    tresults_free(&results);

    return ret;
}
