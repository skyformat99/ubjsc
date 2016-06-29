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
    ttest *test;
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

void tresults_suite_new(tsuite *,tresults_suite **);
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
void tsuite_run(tsuite *,tresults_suite **);

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

void tresults_suite_new(tsuite *suite,tresults_suite **pthis) {
    tresults_suite *this=(tresults_suite *)malloc(sizeof(struct tresults_suite));

    this->failed=0;
    this->suite=suite;
    this->tests_run=0;
    this->tests_failed=0;
    this->asserts_run=0;
    this->asserts_failed=0;
    this->tests=test_list_new();

    *pthis = this;
}

void tresults_suite_free(tresults_suite **pthis) {
    tresults_suite *this=*pthis;

    test_list_free(this->tests);
    free(this);

    *pthis=0;
}

void tresults_suite_add_test(tresults_suite *this,tresults_test *test) {}

void tresults_suite_print(tresults_suite *this) {
    test_list *it;
    tresults_test *test;
    unsigned int i;

    printf("    Did tests fail?          %s\n", this->failed ? "YES!@#$" : "no :)");
    printf("    How many tests   failed? %d of %d\n", this->tests_failed, this->tests_run);
    printf("    How many asserts failed? %d of %d\n", this->asserts_failed, this->asserts_run);
    printf("\n");

    for(it=this->tests->next, i=0; it != this->tests; it=it->next, i++) {
        test=(tresults_test *)it->obj;
        printf("[%d/%d] %s\n", i+1, this->tests_run, test->test->name);
        tresults_test_print(test);
        printf("\n");
    }
}

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

    if(suite->failed==1) {
        this->failed=0;
        this->suites_failed++;
    }

    this->suites_run++;
    this->tests_run+=suite->tests_run;
    this->tests_failed+=suite->tests_failed;
    this->asserts_run+=suite->asserts_run;
    this->asserts_failed+=suite->asserts_failed;
}

void tresults_print(tresults *this) {
    test_list *it;
    tresults_suite *suite;
    unsigned int i;

    printf("========================================\n");
    printf("              RESULTS\n");
    printf("\n");
    printf("    Did tests fail?          %s\n", this->failed ? "YES!@#$" : "no :)");
    printf("    How many suites  failed? %d of %d\n", this->suites_failed, this->suites_run);
    printf("    How many tests   failed? %d of %d\n", this->tests_failed, this->tests_run);
    printf("    How many asserts failed? %d of %d\n", this->asserts_failed, this->asserts_run);
    printf("\n");

    for(it=this->suites->next, i=0; it != this->suites; it=it->next, i++) {
        suite=(tresults_suite *)it->obj;
        printf("[%d/%d] %s\n", i+1, this->suites_run,suite->suite->name);
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

void tsuite_run(tsuite *this,tresults_suite **presults) {
    tresults_suite *results;
    tresults_suite_new(this,&results);

    *presults=results;
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

    test_list *suite_it=0;
    tsuite *suite=0;
    tresults_suite *results_suite=0;

    int ret;

    tresults_new(&results);

    for(suite_it=this->suites->next; suite_it!=this->suites; suite_it=suite_it->next) {
        suite=(tsuite *)suite_it->obj;
        tsuite_run(suite, &results_suite);
        tresults_add_suite(results, results_suite);
    }

    ret = results->failed;

    tresults_print(results);
    tresults_free(&results);

    return ret;
}
