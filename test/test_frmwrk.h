#ifndef HAVE_TEST_FRAMEWORK
#define HAVE_TEST_FRAMEWORK

typedef struct tcontext tcontext;
typedef struct tsuite tsuite;

typedef void (*tbefore_f)();
typedef void (*ttest_f)();
typedef void (*tafter_f)();

#define TASSERT_EQUAL(left,right) tassert_equal(__FILE__,__LINE__,#left,#right,(int)(left),(int)(right));
#define TASSERT_NSTRING_EQUAL(left,right,len) tassert_nstring_equal(__FILE__,__LINE__,#left,#right,#len,(char *)(left),(char *)(right),(int)(len));
#define TASSERT_NOT_EQUAL(left,right) tassert_not_equal(__FILE__,__LINE__,#left,#right,(left),(right));
#define TTEST(suite,test) tsuite_add_test((suite),#test, (test));

void tassert_equal(char *,unsigned int,char *,char *,int,int);
void tassert_nstring_equal(char *,unsigned int,char *,char *,char*,char *,char *,int);
void tassert_not_equal(char *,unsigned int,char *,char *,int,int);

struct tcontext;
struct tsuite;

void tcontext_new(tcontext **);
void tcontext_free(tcontext **);
void tcontext_add_suite(tcontext *,char *,tsuite *);
int tcontext_run(tcontext *);

void tsuite_new(tbefore_f,tafter_f,tsuite **);
void tsuite_free(tsuite **);
void tsuite_add_test(tsuite *,char *,ttest_f);

#endif

