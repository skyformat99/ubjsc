/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
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

#include "test_glue_common.h"

typedef struct test_dict_expected test_dict_expected;
struct test_dict_expected
{
    test_dict_expected *prev;
    test_dict_expected *next;
    char *key;
    unsigned int key_length;
};

void test_dict_expected_free(test_dict_expected *);
test_dict_expected *test_dict_expected_new(void);

void cr_expect_fail_dict(unsigned int, ubjs_glue_dict *,
    test_dict_expected *, char *);
void test_glue_dict_iteration(unsigned int,
    ubjs_glue_dict_builder_new_f builder_new_f);

void suite_glue_dict_before_generic(ubjs_glue_dict_builder_new_f builder_new_f)
{
    ubjs_library_builder builder;

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_set_glue_dict_builder(&builder,
        (ubjs_glue_dict_builder_new_f)builder_new_f);
    ubjs_library_builder_build(&builder, (ubjs_library **)&instance_lib);
}

void suite_glue_dict_after_generic(void)
{
    ubjs_library_free((ubjs_library **)&instance_lib);
}

#define ITERATIONS 100
#define DICT_LENGTH_MAX 10000
#define KEY_LENGTH_MAX 10

void test_glue_dict_allocation(ubjs_glue_dict_builder_new_f builder_new_f)
{
    ubjs_glue_dict_builder *builder = 0;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_dict *this = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    unsigned int length = -1;
    char key[1] = {0};
    void *value = 0;

    cr_expect_eq(UR_OK, (builder_new_f)(lib, &builder));
    cr_expect_neq(0, builder);
    cr_expect_eq(UR_OK, (builder->set_value_free_f)(builder, free));
    cr_expect_eq(UR_OK, (builder->build_f)(builder, &this));
    cr_expect_neq(0, this);
    cr_expect_eq(UR_OK, (builder->free_f)(&builder));
    cr_expect_eq(0, builder);

    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(0, length);

    cr_expect_eq(UR_ERROR, (this->delete_f)(this, 1, "a"));

    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_neq(0, iterator);

    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));

    cr_expect_eq(UR_ERROR, (iterator->get_key_length_f)(iterator, &length));
    cr_expect_eq(0, length);
    cr_expect_eq(UR_ERROR, (iterator->copy_key_f)(iterator, key));
    cr_expect_eq(0, key[0]);
    cr_expect_eq(UR_ERROR, (iterator->get_value_f)(iterator, &value));
    cr_expect_eq(0, value);

    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));
    cr_expect_eq(0, iterator);
    cr_expect_eq(UR_OK, (this->free_f)(&this));
    cr_expect_eq(0, this);
}

void test_glue_dict_usage(ubjs_glue_dict_builder_new_f builder_new_f)
{
    ubjs_glue_dict_builder *builder = 0;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_dict *this = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    unsigned int length = 0;
    void *value = (void *)strdup("aaa");
    void *it_value = 0;
    char it_key[4];
    unsigned int it_key_length=0;
    char *key = "aaa";
    unsigned int key_length = strlen(key);

    cr_expect_eq(UR_OK, (builder_new_f)(lib, &builder));
    cr_expect_neq(0, builder);
    cr_expect_eq(UR_OK, (builder->set_value_free_f)(builder, free));
    cr_expect_eq(UR_OK, (builder->build_f)(builder, &this));
    cr_expect_neq(0, this);
    cr_expect_eq(UR_OK, (builder->free_f)(&builder));
    cr_expect_eq(0, builder);

    cr_expect_eq(UR_OK, (this->set_f)(this, key_length, key, value));
    cr_expect_eq(UR_OK, (this->get_f)(this, key_length, key, &it_value));
    cr_expect_eq(value, it_value);
    it_value = 0;

    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(1, length);

    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_eq(UR_OK, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->get_key_length_f)(iterator,
        &it_key_length));
    cr_expect_eq(key_length, it_key_length);
    cr_expect_eq(UR_OK, (iterator->copy_key_f)(iterator, it_key));
    cr_assert_arr_eq(it_key, key, 1);
    cr_expect_eq(UR_OK, (iterator->get_value_f)(iterator, &it_value));
    cr_expect_eq(value, it_value);
    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));

    value = strdup("bbb");
    cr_expect_eq(UR_OK, (this->set_f)(this, key_length, key, value));
    cr_expect_eq(UR_OK, (this->get_f)(this, key_length, key, &it_value));
    cr_expect_eq(value, it_value);
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(1, length);

    cr_expect_eq(UR_OK, (this->delete_f)(this, key_length, key));
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(0, length);
    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_neq(0, iterator);
    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));

    cr_expect_eq(UR_OK, (this->free_f)(&this));
    cr_expect_eq(0, this);

    cr_expect_eq(UR_OK, (builder_new_f)(lib, &builder));
    cr_expect_neq(0, builder);
    cr_expect_eq(UR_OK, (builder->set_value_free_f)(builder, free));
    cr_expect_eq(UR_OK, (builder->set_length_f)(builder, 1));
    cr_expect_eq(UR_OK, (builder->build_f)(builder, &this));
    cr_expect_neq(0, this);
    cr_expect_eq(UR_OK, (builder->free_f)(&builder));
    cr_expect_eq(0, builder);
    cr_expect_eq(UR_OK, (this->free_f)(&this));
    cr_expect_eq(0, this);
}

void test_dict_expected_free(test_dict_expected *this)
{
    if (0 != this->key)
    {
        free(this->key);
    }
    free(this);
}

test_dict_expected *test_dict_expected_new(void)
{
    test_dict_expected *this;

    this = (test_dict_expected *)malloc(sizeof(test_dict_expected));
    this->prev=this;
    this->next=this;
    this->key=0;
    this->key_length=0;
    return this;
}

void cr_expect_fail_dict_pstrcat_expected(char **pmsg, test_dict_expected *expected)
{
    test_dict_expected *iexpected;

    pstrcat(pmsg, "Items in expected:");
    for (iexpected = expected->next; iexpected != expected; iexpected = iexpected->next)
    {
        pstrcat(pmsg, "\n # %u %.*s", iexpected->key_length, iexpected->key_length,
            iexpected->key);
    }
}

void cr_expect_fail_dict_pstrcat_actual(char **pmsg, ubjs_glue_dict *this)
{
    ubjs_glue_dict_iterator *pit;

    pstrcat(pmsg, "\n\nItems in dict:");
    (this->iterate_f)(this, &pit);
    while (UR_OK == (pit->next_f)(pit))
    {
        char *pitk;
        unsigned int pitkl;

        (pit->get_key_length_f)(pit, &pitkl);
        pitk = (char *)malloc(sizeof(char) * pitkl);
        (pit->copy_key_f)(pit, pitk);

        pstrcat(pmsg, "\n # %u %.*s", pitkl, pitkl, pitk);
        free(pitk);
    }
    (pit->free_f)(&pit);
}

void cr_expect_fail_dict(unsigned int iteration,
    ubjs_glue_dict *this, test_dict_expected *expected,
    char *message)
{
    char *msg = 0;
    pstrcat(&msg, "Iteration %u: %s\n\n", iteration, message);
    cr_expect_fail_dict_pstrcat_expected(&msg, expected);
    cr_expect_fail_dict_pstrcat_actual(&msg, this);
    cr_expect_fail("%s", msg);
    free(msg);
}

void test_glue_dict_iteration_prepare_dict(ubjs_library *lib,
    ubjs_glue_dict_builder_new_f builder_new_f, ubjs_glue_dict **pthis)
{
    ubjs_glue_dict_builder *builder = 0;

    cr_expect_eq(UR_OK, (builder_new_f)(lib, &builder));
    cr_expect_neq(0, builder);
    cr_expect_eq(UR_OK, (builder->set_value_free_f)(builder, free));
    cr_expect_eq(UR_OK, (builder->build_f)(builder, pthis));
    cr_expect_neq(0, *pthis);
    cr_expect_eq(UR_OK, (builder->free_f)(&builder));
    cr_expect_eq(0, builder);
}

void test_glue_dict_iteration_verify_dict(unsigned int iteration, ubjs_glue_dict *this,
    unsigned int dict_length, char *value, test_dict_expected *root)
{
    test_dict_expected *expected_tmp;
    unsigned int tmp_length = -1;
    char *nvalue = 0;

    if (UR_OK != (this->get_length_f)(this, &tmp_length) ||
        tmp_length != dict_length)
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            dict_length, tmp_length);
        cr_expect_fail_dict(iteration, this, root, message);
        free(message);
    }

    for (expected_tmp = root->next; expected_tmp != root; expected_tmp = expected_tmp->next)
    {
        if (UR_OK != (this->get_f)(this, expected_tmp->key_length,
            expected_tmp->key, (void **)&nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_f %u %.*s",
                expected_tmp->key_length, expected_tmp->key_length, expected_tmp->key);
            cr_expect_fail_dict(iteration, this, root, message);
            free(message);
        }
        else if (0 != nvalue && 0 != strcmp(value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f but keys did not match: %s vs %s", value, nvalue);
            cr_expect_fail_dict(iteration, this, root, message);
            free(message);
        }
    }
}

void test_glue_dict_iteration_fill_dict(ubjs_glue_dict *this,
    unsigned int dict_length, char *value, test_dict_expected *root)
{
    unsigned int i;
    unsigned int key_length;
    char key_tmp[10];
    test_dict_expected *expected_tmp;
    char *nvalue = 0;

    for (i=0; i<dict_length; i++)
    {
        while (1)
        {
            key_length = rand() % KEY_LENGTH_MAX + 1;
            random_str(key_length, key_tmp);
            if (UR_ERROR == (this->get_f)(this, key_length, key_tmp, (void **)&nvalue))
            {
                break;
            }
        }

        expected_tmp = test_dict_expected_new();
        expected_tmp->key = strndup(key_tmp, key_length);
        expected_tmp->key_length = key_length;
        expected_tmp->next=root;
        expected_tmp->prev=root->prev;
        root->prev->next=expected_tmp;
        root->prev=expected_tmp;

        (this->set_f)(this, key_length, key_tmp, strdup(value));
    }
}

void test_glue_dict_iteration(unsigned int iteration,
    ubjs_glue_dict_builder_new_f builder_new_f)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_dict *this = 0;
    test_dict_expected *root;
    test_dict_expected *expected_tmp;
    unsigned int i, j;
    unsigned int dict_length;
    unsigned int items_to_do;
    unsigned int item_delete;
    char value[] = "rower";
    char *nvalue = 0;
    unsigned int key_length;
    char key_tmp[10];

    cr_log_error("## Iteration %u/%u\n", iteration, ITERATIONS);

    root = test_dict_expected_new();
    dict_length = rand() % DICT_LENGTH_MAX + 1;

    test_glue_dict_iteration_prepare_dict(lib, builder_new_f, &this);
    test_glue_dict_iteration_fill_dict(this, dict_length, value, root);
    test_glue_dict_iteration_verify_dict(iteration, this, dict_length, value, root);
    items_to_do = rand() % ((int)sqrt(dict_length));

    for (j=0; j<items_to_do; j++)
    {
        if (iteration < ITERATIONS / 2)
        {
            item_delete = rand() % dict_length;
            for (i=0, expected_tmp = root->next; i < item_delete;
                i++, expected_tmp = expected_tmp->next)
            {
            }
            (this->delete_f)(this, expected_tmp->key_length, expected_tmp->key);

            if (UR_ERROR != (this->get_f)(this, expected_tmp->key_length,
                expected_tmp->key, (void **)&nvalue))
            {
                char *message = 0;
                pstrcat(&message, "Did get_f %u %.*s when expected not to",
                    expected_tmp->key_length, expected_tmp->key_length, expected_tmp->key);
                cr_expect_fail_dict(iteration, this, root, message);
                free(message);
            }

            expected_tmp->prev->next = expected_tmp->next;
            expected_tmp->next->prev = expected_tmp->prev;
            test_dict_expected_free(expected_tmp);
            dict_length--;
        }
        else
        {
            while (1)
            {
                key_length = rand() % KEY_LENGTH_MAX + 1;
                random_str(key_length, key_tmp);
                if (UR_ERROR == (this->get_f)(this, key_length, key_tmp, (void **)&nvalue))
                {
                    break;
                }
            }

            expected_tmp = test_dict_expected_new();
            expected_tmp->key = strndup(key_tmp, key_length);
            expected_tmp->key_length = key_length;
            expected_tmp->next=root;
            expected_tmp->prev=root->prev;
            root->prev->next=expected_tmp;
            root->prev=expected_tmp;

            (this->set_f)(this, key_length, key_tmp, strdup(value));
            dict_length++;
        }
    }

    test_glue_dict_iteration_verify_dict(iteration, this, dict_length, value, root);

    (this->free_f)(&this);

    while (root->next != root)
    {
        expected_tmp = root->next;
        root->next = expected_tmp->next;
        test_dict_expected_free(expected_tmp);
    }
    test_dict_expected_free(root);
}

void test_glue_dict_performance(ubjs_glue_dict_builder_new_f builder_new_f)
{
    unsigned int i;

    srand(time(0));
    for (i=0; i<ITERATIONS; i++)
    {
        test_glue_dict_iteration(i, builder_new_f);
    }
}
