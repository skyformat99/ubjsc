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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#include "test_common.h"
#include "test_glue_array.h"

void suite_glue_array(tcontext *context, char *name, ubjs_glue_array_factory factory)
{
    tsuite *suite;
    TSUITEARG(name, suite_glue_array_before, suite_glue_array_after,
        factory, &suite);
    tcontext_add_suite(context, suite);

    TTESTARG(suite, test_glue_array_allocation, factory);
    TTESTARG(suite, test_glue_array_usage, factory);
    TTESTARG(suite, test_glue_array_performance, factory);
}

void suite_glue_array_before(void)
{
    ubjs_library_builder *builder=0;
    ubjs_library_builder_new(&builder);
    ubjs_library_builder_set_glue_array_factory(builder,
        (ubjs_glue_array_factory)tsuiteargs);
    ubjs_library_builder_build(builder, (ubjs_library **)&tstate);
    ubjs_library_builder_free(&builder);
}

void suite_glue_array_after(void)
{
    ubjs_library_free((ubjs_library **)&tstate);
}

#define ITERATIONS 10
#define ARRAY_LENGTH_MAX 10000
#define VALUE_LENGTH_MAX 10

void test_glue_array_allocation(void)
{
    ubjs_glue_array_factory factory = (ubjs_glue_array_factory)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_array *this = 0;
    ubjs_glue_array_iterator *iterator = 0;
    unsigned int length = 0;
    void *value = 0;

    TASSERT_EQUAL(UR_OK, (factory)(lib, free, &this));
    TASSERT_NOT_EQUAL(0, this);

    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(0, length);

    TASSERT_EQUAL(UR_ERROR, (this->get_first_f)(this, &value));
    TASSERT_EQUAL(UR_ERROR, (this->get_last_f)(this, &value));
    TASSERT_EQUAL(UR_ERROR, (this->get_at_f)(this, 0, &value));
    TASSERT_EQUAL(UR_ERROR, (this->get_at_f)(this, 1, &value));

    TASSERT_EQUAL(UR_ERROR, (this->delete_first_f)(this));
    TASSERT_EQUAL(UR_ERROR, (this->delete_last_f)(this));
    TASSERT_EQUAL(UR_ERROR, (this->delete_at_f)(this, 0));

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);

    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));

    TASSERT_EQUAL(UR_ERROR, (iterator->get_f)(iterator, &value));
    TASSERT_EQUALI(0, value);

    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));
    TASSERT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_OK, (this->free_f)(&this));
    TASSERT_EQUAL(0, this);
}

void test_glue_array_usage(void)
{
    ubjs_glue_array_factory factory = (ubjs_glue_array_factory)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_array *this = 0;
    ubjs_glue_array_iterator *iterator = 0;
    unsigned int length = 0;
    void *value1 = (void *)strdup("aaa");
    void *value2 = (void *)strdup("bbb");
    void *value3 = (void *)strdup("ccc");
    void *it_value = 0;

    TASSERT_EQUAL(UR_OK, (factory)(lib, free, &this));
    TASSERT_EQUAL(UR_OK, (this->add_first_f)(this, value1));
    TASSERT_EQUAL(UR_OK, (this->get_first_f)(this, &it_value));
    TASSERT_EQUAL(value1, it_value);
    it_value = 0;
    TASSERT_EQUAL(UR_OK, (this->get_last_f)(this, &it_value));
    TASSERT_EQUAL(value1, it_value);
    it_value = 0;
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 0, &it_value));
    TASSERT_EQUAL(value1, it_value);
    it_value = 0;
    TASSERT_EQUAL(UR_ERROR, (this->get_at_f)(this, 1, &it_value));
    TASSERT_EQUAL(it_value, 0);

    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(1, length);

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_EQUAL(UR_OK, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->get_f)(iterator, &it_value));
    TASSERT_EQUAL(value1, it_value);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));

    TASSERT_EQUAL(UR_OK, (this->add_last_f)(this, value2));
    TASSERT_EQUAL(UR_OK, (this->get_last_f)(this, &it_value));
    TASSERT_EQUAL(value2, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 1, &it_value));
    TASSERT_EQUAL(value2, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(2, length);
    it_value = 0;
    TASSERT_EQUAL(UR_ERROR, (this->get_at_f)(this, 2, &it_value));
    TASSERT_EQUAL(it_value, 0);

    TASSERT_EQUAL(UR_OK, (this->add_at_f)(this, 1, value3));
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 1, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(3, length);
    it_value = 0;
    TASSERT_EQUAL(UR_ERROR, (this->get_at_f)(this, 3, &it_value));
    TASSERT_EQUAL(it_value, 0);

    TASSERT_EQUAL(UR_ERROR, (this->add_at_f)(this, 4, value3));
    TASSERT_EQUAL(UR_ERROR, (this->delete_at_f)(this, 3));

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_EQUAL(UR_OK, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->get_f)(iterator, &it_value));
    TASSERT_EQUAL(value1, it_value);
    TASSERT_EQUAL(UR_OK, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->get_f)(iterator, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->get_f)(iterator, &it_value));
    TASSERT_EQUAL(value2, it_value);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));

    TASSERT_EQUAL(UR_OK, (this->delete_first_f)(this));
    TASSERT_EQUAL(UR_OK, (this->get_first_f)(this, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 0, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_last_f)(this, &it_value));
    TASSERT_EQUAL(value2, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 1, &it_value));
    TASSERT_EQUAL(value2, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(2, length);

    TASSERT_EQUAL(UR_OK, (this->delete_at_f)(this, 1));
    TASSERT_EQUAL(UR_OK, (this->get_first_f)(this, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, 0, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_last_f)(this, &it_value));
    TASSERT_EQUAL(value3, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(1, length);

    TASSERT_EQUAL(UR_OK, (this->delete_last_f)(this));
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(0, length);

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));

    TASSERT_EQUAL(UR_OK, (this->free_f)(&this));
    TASSERT_EQUAL(0, this);
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

void terror_array_expected(char *file, unsigned int line, unsigned int iteration,
    ubjs_glue_array *this, test_array_expected *expected,
    char *message)
{
    test_array_expected *iexpected;
    ubjs_glue_array_iterator *pit;
    char *msg = 0;

    pstrcat(&msg, "Iteration %u: %s", iteration, message);
    free(message);

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

    terror(file, line, msg);
}

void test_glue_array_iteration(unsigned int iteration)
{
    ubjs_glue_array_factory factory = (ubjs_glue_array_factory)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_array *this;
    test_array_expected *root;

    unsigned int i, j;
    unsigned int array_length;
    char key_tmp[10];
    test_array_expected *kv_tmp;
    char value[] = "rower";
    char *nvalue = 0;
    unsigned int items_to_do;
    unsigned int tmp_length = -1;

    printf("Iteration %u\n", iteration);

    root = test_array_expected_new();
    (factory)(lib, free, &this);

    array_length = rand() % ARRAY_LENGTH_MAX + 1;

    for (i=0; i<array_length; i++)
    {
        unsigned int value_length = rand() % VALUE_LENGTH_MAX + 1;
        random_str(value_length, key_tmp);

        kv_tmp = test_array_expected_new();
        kv_tmp->value = strndup(key_tmp, value_length);
        kv_tmp->next=root;
        kv_tmp->prev=root->prev;
        root->prev->next=kv_tmp;
        root->prev=kv_tmp;

        (this->add_last_f)(this, strdup(value));
    }

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, array_length)))
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            array_length, tmp_length);
        TERROR_ARRAY_EXPECTED(iteration, this, root, message);
    }

    for (j=0, kv_tmp = root->next; kv_tmp != root; j++, kv_tmp = kv_tmp->next)
    {
        if (0 != TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, j, (void **)&nvalue)))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_at_f %u", j);
            TERROR_ARRAY_EXPECTED(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f %u but keys did not match", j);
            TERROR_ARRAY_EXPECTED(iteration, this, root, message);
        }
    }

    items_to_do = rand() % ((int)sqrt(array_length));

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

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, array_length)))
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            array_length, tmp_length);
        TERROR_ARRAY_EXPECTED(iteration, this, root, message);
    }

    for (j=0, kv_tmp = root->next; kv_tmp != root; j++, kv_tmp = kv_tmp->next)
    {
       if (0 != TASSERT_EQUAL(UR_OK, (this->get_at_f)(this, j, (void **)&nvalue)))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_at_f %u", j);
            TERROR_ARRAY_EXPECTED(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f but keys did not match");
            TERROR_ARRAY_EXPECTED(iteration, this, root, message);
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

void test_glue_array_performance(void)
{
    unsigned int i;

    srand(time(0));
    for (i=0; i<ITERATIONS; i++)
    {
        test_glue_array_iteration(i);
    }
}
