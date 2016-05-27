#ifndef HAVE_TEST_LIST
#define HAVE_TEST_LIST

typedef struct test_list test_list;
typedef void (*test_list_free_f)(void *it);

struct test_list
{
    test_list *prev;
    test_list *next;

    void *obj;
    test_list_free_f free;
};

test_list *test_list_new();
void test_list_free(test_list *);
void test_list_add(test_list *,void *,test_list_free_f);
int test_list_len(test_list *);
void *test_list_get(test_list *,int);

#endif

