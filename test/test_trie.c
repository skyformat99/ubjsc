#include <stdlib.h>

#include "test_trie.h"

CU_pSuite suite_trie() {
    CU_pSuite suite = CU_add_suite("common", 0, 0);

    CU_ADD_TEST(suite, test_trie_new);

    return suite;
}

void test_trie_new() {
    ubjs_trie *trie=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_trie_new(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_trie_new(0, &trie));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_trie_new(free, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(free, &trie));
    CU_ASSERT_NOT_EQUAL(0, trie);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_trie_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));
    CU_ASSERT_EQUAL(0, trie);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_trie_free(&trie));
}

void test_trie_1_item();
