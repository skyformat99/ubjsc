/*
 * Copyright (c) 2017 Tomasz Sieprawski
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

#include "test_glue_array_generic.h"

typedef struct test_array_expected test_array_expected;
struct test_array_expected
{
    test_array_expected *prev;
    test_array_expected *next;
    char *value;
};

void test_array_expected_free(test_array_expected *);
test_array_expected *test_array_expected_new(void);

void cr_expect_fail_array(unsigned int, ubjs_glue_array *,
    test_array_expected *, char *);
void test_glue_array_iteration(unsigned int,
    ubjs_glue_array_builder_new_f);

void suite_glue_array_before_generic(ubjs_glue_array_builder_new_f builder_new_f)
{
    ubjs_library_builder builder;

    tbefore();

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_set_glue_array_builder(&builder, builder_new_f);
    ubjs_library_builder_build(&builder, (ubjs_library **)&instance_lib);
}

void suite_glue_array_after_generic(void)
{
    ubjs_library_free((ubjs_library **)&instance_lib);

    tafter();
}

#define ITERATIONS 100
#define ARRAY_LENGTH_MAX 10000
#define VALUE_LENGTH_MAX 10

void test_glue_array_allocation(ubjs_glue_array_builder_new_f builder_new_f)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_array_builder *builder = 0;
    ubjs_glue_array *this = 0;
    ubjs_glue_array_iterator *iterator = 0;
    unsigned int length = 0;
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

    cr_expect_eq(UR_ERROR, (this->get_first_f)(this, &value));
    cr_expect_eq(UR_ERROR, (this->get_last_f)(this, &value));
    cr_expect_eq(UR_ERROR, (this->get_at_f)(this, 0, &value));
    cr_expect_eq(UR_ERROR, (this->get_at_f)(this, 1, &value));

    cr_expect_eq(UR_ERROR, (this->delete_first_f)(this));
    cr_expect_eq(UR_ERROR, (this->delete_last_f)(this));
    cr_expect_eq(UR_ERROR, (this->delete_at_f)(this, 0));

    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_neq(0, iterator);

    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));

    cr_expect_eq(UR_ERROR, (iterator->get_f)(iterator, &value));
    cr_expect_eq(0, value);

    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));
    cr_expect_eq(0, iterator);
    cr_expect_eq(UR_OK, (this->free_f)(&this));
    cr_expect_eq(0, this);
}

void test_glue_array_usage(ubjs_glue_array_builder_new_f builder_new_f)
{
    ubjs_glue_array_builder *builder = 0;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_array *this = 0;
    ubjs_glue_array_iterator *iterator = 0;
    unsigned int length = 0;
    void *value1 = (void *)strdup("aaa");
    void *value2 = (void *)strdup("bbb");
    void *value3 = (void *)strdup("ccc");
    void *it_value = 0;

    cr_expect_eq(UR_OK, (builder_new_f)(lib, &builder));
    cr_expect_neq(0, builder);
    cr_expect_eq(UR_OK, (builder->set_value_free_f)(builder, free));
    cr_expect_eq(UR_OK, (builder->build_f)(builder, &this));
    cr_expect_neq(0, this);
    cr_expect_eq(UR_OK, (builder->free_f)(&builder));
    cr_expect_eq(0, builder);

    cr_expect_eq(UR_OK, (this->add_first_f)(this, value1));
    cr_expect_eq(UR_OK, (this->get_first_f)(this, &it_value));
    cr_expect_eq(value1, it_value);
    it_value = 0;
    cr_expect_eq(UR_OK, (this->get_last_f)(this, &it_value));
    cr_expect_eq(value1, it_value);
    it_value = 0;
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 0, &it_value));
    cr_expect_eq(value1, it_value);
    it_value = 0;
    cr_expect_eq(UR_ERROR, (this->get_at_f)(this, 1, &it_value));
    cr_expect_eq(it_value, 0);

    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(1, length);

    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_eq(UR_OK, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->get_f)(iterator, &it_value));
    cr_expect_eq(value1, it_value);
    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));

    cr_expect_eq(UR_OK, (this->add_last_f)(this, value2));
    cr_expect_eq(UR_OK, (this->get_last_f)(this, &it_value));
    cr_expect_eq(value2, it_value);
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 1, &it_value));
    cr_expect_eq(value2, it_value);
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(2, length);
    it_value = 0;
    cr_expect_eq(UR_ERROR, (this->get_at_f)(this, 2, &it_value));
    cr_expect_eq(it_value, 0);

    cr_expect_eq(UR_OK, (this->add_at_f)(this, 1, value3));
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 1, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(3, length);
    it_value = 0;
    cr_expect_eq(UR_ERROR, (this->get_at_f)(this, 3, &it_value));
    cr_expect_eq(it_value, 0);

    cr_expect_eq(UR_ERROR, (this->add_at_f)(this, 4, value3));
    cr_expect_eq(UR_ERROR, (this->delete_at_f)(this, 3));

    cr_expect_eq(UR_OK, (this->iterate_f)(this, &iterator));
    cr_expect_eq(UR_OK, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->get_f)(iterator, &it_value));
    cr_expect_eq(value1, it_value);
    cr_expect_eq(UR_OK, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->get_f)(iterator, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->get_f)(iterator, &it_value));
    cr_expect_eq(value2, it_value);
    cr_expect_eq(UR_ERROR, (iterator->next_f)(iterator));
    cr_expect_eq(UR_OK, (iterator->free_f)(&iterator));

    cr_expect_eq(UR_OK, (this->delete_first_f)(this));
    cr_expect_eq(UR_OK, (this->get_first_f)(this, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 0, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_last_f)(this, &it_value));
    cr_expect_eq(value2, it_value);
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 1, &it_value));
    cr_expect_eq(value2, it_value);
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(2, length);

    cr_expect_eq(UR_OK, (this->delete_at_f)(this, 1));
    cr_expect_eq(UR_OK, (this->get_first_f)(this, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_at_f)(this, 0, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_last_f)(this, &it_value));
    cr_expect_eq(value3, it_value);
    cr_expect_eq(UR_OK, (this->get_length_f)(this, &length));
    cr_expect_eq(1, length);

    cr_expect_eq(UR_OK, (this->delete_last_f)(this));
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

void test_array_expected_free(test_array_expected *this)
{
    if (0 != this->value)
    {
        free(this->value);
    }
    free(this);
}

test_array_expected *test_array_expected_new(void)
{
    test_array_expected *this;

    this = (test_array_expected *)malloc(sizeof(test_array_expected));
    this->prev=this;
    this->next=this;
    this->value=0;
    return this;
}

void cr_expect_fail_array(unsigned int iteration,
    ubjs_glue_array *this, test_array_expected *expected,
    char *message)
{
    test_array_expected *iexpected;
    ubjs_glue_array_iterator *pit;
    char *msg = 0;

    pstrcat(&msg, "Iteration %u: %s", iteration, message);
    cr_free(message);

    pstrcat(&msg, "\n\nItems in expected:");
    for (iexpected = expected->next; iexpected != expected; iexpected = iexpected->next)
    {
        pstrcat(&msg, "\n # %s", iexpected->value);
    }

    pstrcat(&msg, "\n\nItems in array:");
    (this->iterate_f)(this, &pit);
    while (UR_OK == (pit->next_f)(pit))
    {
        char *value = 0;
        (pit->get_f)(pit, (void **)&value);
        pstrcat(&msg, "\n # %s", value);
    }
    (pit->free_f)(&pit);

    cr_expect_fail("%s", msg);
}

void test_glue_array_iteration(unsigned int iteration,
    ubjs_glue_array_builder_new_f builder_new_f)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_glue_array_builder *builder = 0;
    ubjs_glue_array *this = 0;
    test_array_expected *root;

    unsigned int i, j;
    unsigned int array_length;
    char key_tmp[10];
    test_array_expected *kv_tmp;
    char *nvalue = 0;
    unsigned int items_to_do;
    unsigned int tmp_length = -1;

    cr_log_error("## Iteration %u/%u\n", iteration, ITERATIONS);

    array_length = rand() % ARRAY_LENGTH_MAX + 1;
    root = test_array_expected_new();

    (builder_new_f)(lib, &builder);
    (builder->set_value_free_f)(builder, free);
    if (rand() % 16 > 8)
    {
        (builder->set_length_f)(builder, array_length);
    }
    (builder->build_f)(builder, &this);
    (builder->free_f)(&builder);

    for (i=0; i<array_length; i++)
    {
        unsigned int value_length = rand() % VALUE_LENGTH_MAX + 1;
        random_str(value_length, key_tmp);

        kv_tmp = test_array_expected_new();
        kv_tmp->value = strndup(key_tmp, value_length);

        kv_tmp->next = root;
        kv_tmp->prev = root->prev;
        root->prev->next = kv_tmp;
        root->prev = kv_tmp;

        (this->add_last_f)(this, strdup(kv_tmp->value));
    }

    if (UR_OK != (this->get_length_f)(this, &tmp_length) ||
        tmp_length != array_length)
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            array_length, tmp_length);
        cr_expect_fail_array(iteration, this, root, message);
    }

    for (j=0, kv_tmp = root->next; kv_tmp != root; j++, kv_tmp = kv_tmp->next)
    {
        if (UR_OK != (this->get_at_f)(this, j, (void **)&nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_at_f %u", j);
            cr_expect_fail_array(iteration, this, root, message);
        }
        else if (0 != strcmp(kv_tmp->value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f %u but keys did not match", j);
            cr_expect_fail_array(iteration, this, root, message);
        }
    }

    items_to_do = rand() % (int)(sqrt(array_length));

    for (j=0; j<items_to_do; j++)
    {
        unsigned int item_delete = rand() % array_length;
        for (i=0, kv_tmp = root->next; i < item_delete; i++, kv_tmp = kv_tmp->next)
        {
        }

        (this->delete_at_f)(this, item_delete);

        kv_tmp->prev->next = kv_tmp->next;
        kv_tmp->next->prev = kv_tmp->prev;
        test_array_expected_free(kv_tmp);
        array_length--;
    }

    if (UR_OK != (this->get_length_f)(this, &tmp_length) ||
        tmp_length != array_length)
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            array_length, tmp_length);
        cr_expect_fail_array(iteration, this, root, message);
    }

    for (j=0, kv_tmp = root->next; kv_tmp != root; j++, kv_tmp = kv_tmp->next)
    {
        if (UR_OK != (this->get_at_f)(this, j, (void **)&nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_at_f %u", j);
            cr_expect_fail_array(iteration, this, root, message);
        }
        else if (0 != strcmp(kv_tmp->value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f but keys did not match");
            cr_expect_fail_array(iteration, this, root, message);
        }
    }

    (this->free_f)(&this);

    while (root->next != root)
    {
        kv_tmp = root->next;
        root->next = kv_tmp->next;
        test_array_expected_free(kv_tmp);
    }
    test_array_expected_free(root);
}

void test_glue_array_performance(ubjs_glue_array_builder_new_f builder_new_f)
{
    unsigned int i;

    srand(time(0));
    for (i=0; i<ITERATIONS; i++)
    {
        test_glue_array_iteration(i, builder_new_f);
    }
}
