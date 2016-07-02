#ifndef HAVE_TEST_FRAMEWORK
#define HAVE_TEST_FRAMEWORK

typedef struct tcontext tcontext;
typedef struct tsuite tsuite;

typedef void (*tbefore_f)();
typedef void (*ttest_f)();
typedef void (*tafter_f)();

#define TASSERT_EQUAL(left,right) tassert_equal(__FILE__,__LINE__,#left,#right,(left)==(right))
#define TASSERT_STRING_EQUAL(left,right) tassert_string_equal(__FILE__,__LINE__,#left,#right,(left),(right))
#define TASSERT_NSTRING_EQUAL(left,right,len) tassert_nstring_equal(__FILE__,__LINE__,#left,#right,#len,(left),(right),(len))
#define TASSERT_NOT_EQUAL(left,right) tassert_not_equal(__FILE__,__LINE__,#left,#right,(left)!=(right))
#define TTEST(suite,test) tsuite_add_test((suite),#test, (test))
#define TSUITE(name,before,after,psuite) tsuite_new(name,before,after,__FILE__,psuite)

void tassert_equal(char *,unsigned int,char *,char *,int);
void tassert_nstring_equal(char *,unsigned int,char *,char *,char*,char *,char *,int);
void tassert_string_equal(char *,unsigned int,char *,char *,char *,char *);
void tassert_not_equal(char *,unsigned int,char *,char *,int);

struct tcontext;
struct tsuite;

void tcontext_new(tcontext **);
void tcontext_free(tcontext **);
void tcontext_add_suite(tcontext *,tsuite *);
int tcontext_run(tcontext *);

void tsuite_new(char *,tbefore_f,tafter_f,char *,tsuite **);
void tsuite_free(tsuite **);
void tsuite_add_test(tsuite *,char *,ttest_f);

#endif

