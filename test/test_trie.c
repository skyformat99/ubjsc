#include <stdlib.h>

#include "test_trie.h"

CU_pSuite suite_trie() {
    CU_pSuite suite = CU_add_suite("common", 0, 0);

    CU_ADD_TEST(suite, test_trie_new);
    CU_ADD_TEST(suite, test_trie_1_item);

    return suite;
}

void test_trie_new() {
    ubjs_trie *trie = 0;

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

void nothing(void *value) {
}

void test_trie_1_item() {
    ubjs_trie *trie = 0;
    char *value = "123";
    char *nvalue;

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 10, "abcdefghij", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 10, "abcdefghij", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "b", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "c", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "b", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "c", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 2, "aa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 3, "aaa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 2, "aa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 3, "aaa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 2, "aa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 6, "aabbbb", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 14, "aabbbbcccccccc", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 2, "aa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 6, "aabbbb", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 14, "aabbbbcccccccc", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 2, "bb", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 3, "ccc", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 2, "bb", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 3, "ccc", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "c", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "b", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "b", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "c", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 1, "a", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 2, "ab", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "abbbb", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "aaaaa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "abbaa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 3, "aaa", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 1, "a", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 2, "ab", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 3, "aaa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 5, "abbbb", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 5, "aaaaa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_get(trie, 5, "abbaa", &nvalue));
    CU_ASSERT_EQUAL(nvalue, value);
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));

    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_new(nothing, &trie));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 10, "rubicundus", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 7, "rubicon", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "ruber", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 6, "rubens", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 7, "romanus", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 6, "romane", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "roman", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 5, "rubic", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_put(trie, 7, "romulus", value));
    CU_ASSERT_EQUAL(UR_OK, ubjs_trie_free(&trie));
}
