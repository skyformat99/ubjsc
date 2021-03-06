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

#ifndef HAVE_TEST_LIST
#define HAVE_TEST_LIST

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct test_list test_list;
typedef struct test_list_item test_list_item;
typedef void (*test_list_free_f)(void **);

struct test_list
{
    test_list_item *sentinel;
    unsigned int len;
    test_list_free_f free_f;
};

void test_list_new(test_list_free_f, test_list **);
void test_list_free(test_list **);

struct test_list_item
{
    test_list *list;
    test_list_item *prev;
    test_list_item *next;
    void *obj;
};

void test_list_item_new(test_list *, void *, test_list_item **);
void test_list_item_free(test_list_item **);

int test_list_add(test_list *, void *, test_list_item **);
int test_list_get(test_list *, int, test_list_item **);
void test_list_remove(test_list *, test_list_item *);
void test_list_len(test_list *, unsigned int *);

#ifdef __cplusplus
}
#endif

#endif
