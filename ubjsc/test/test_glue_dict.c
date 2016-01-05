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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#include "test_common.h"
#include "test_glue_dict.h"

void suite_glue_dict(tcontext *context, char *name, ubjs_glue_dict_builder builder)
{
    tsuite *suite;
    TSUITEARG(name, suite_glue_dict_before, suite_glue_dict_after,
        builder, &suite);
    tcontext_add_suite(context, suite);

    TTESTARG(suite, test_glue_dict_allocation, builder);
    TTESTARG(suite, test_glue_dict_usage, builder);
    TTESTARG(suite, test_glue_dict_performance, builder);
}

void suite_glue_dict_before(void)
{
    ubjs_library_builder *builder=0;
    ubjs_library_builder_new(&builder);
    ubjs_library_builder_set_glue_dict_builder(builder,
        (ubjs_glue_dict_builder)tsuiteargs);
    ubjs_library_builder_build(builder, (ubjs_library **)&tstate);
    ubjs_library_builder_free(&builder);
}

void suite_glue_dict_after(void)
{
    ubjs_library_free((ubjs_library **)&tstate);
}

#define ITERATIONS 10
#define DICT_LENGTH_MAX 10000
#define KEY_LENGTH_MAX 10

void test_glue_dict_allocation(void)
{
    ubjs_glue_dict_builder builder = (ubjs_glue_dict_builder)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_dict *this = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    unsigned int length = -1;
    char key[1] = {0};
    void *value = 0;

    TASSERT_EQUAL(UR_OK, (builder)(lib, free, &this));
    TASSERT_NOT_EQUAL(0, this);

    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(0, length);

    TASSERT_EQUAL(UR_ERROR, (this->delete_f)(this, 1, "a"));

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);

    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));

    TASSERT_EQUAL(UR_ERROR, (iterator->get_key_length_f)(iterator, &length));
    TASSERT_EQUALI(0, length);
    TASSERT_EQUAL(UR_ERROR, (iterator->copy_key_f)(iterator, key));
    TASSERT_EQUALI(0, key[0]);
    TASSERT_EQUAL(UR_ERROR, (iterator->get_value_f)(iterator, &value));
    TASSERT_EQUALI(0, value);

    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));
    TASSERT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_OK, (this->free_f)(&this));
    TASSERT_EQUAL(0, this);
}

void test_glue_dict_usage(void)
{
    ubjs_glue_dict_builder builder = (ubjs_glue_dict_builder)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_dict *this = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    unsigned int length = 0;
    void *value = (void *)strdup("aaa");
    void *it_value = 0;
    char it_key[4];
    unsigned int it_key_length=0;
    char *key = "aaa";
    unsigned int key_length = strlen(key);

    TASSERT_EQUAL(UR_OK, (builder)(lib, free, &this));
    TASSERT_EQUAL(UR_OK, (this->set_f)(this, key_length, key, value));
    TASSERT_EQUAL(UR_OK, (this->get_f)(this, key_length, key, &it_value));
    TASSERT_EQUAL(value, it_value);
    it_value = 0;

    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(1, length);

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_EQUAL(UR_OK, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->get_key_length_f)(iterator,
        &it_key_length));
    TASSERT_EQUAL(key_length, it_key_length);
    TASSERT_EQUAL(UR_OK, (iterator->copy_key_f)(iterator, it_key));
    TASSERT_NSTRING_EQUAL(it_key, key, 1);
    TASSERT_EQUAL(UR_OK, (iterator->get_value_f)(iterator, &it_value));
    TASSERT_EQUAL(value, it_value);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));

    value = strdup("bbb");
    TASSERT_EQUAL(UR_OK, (this->set_f)(this, key_length, key, value));
    TASSERT_EQUAL(UR_OK, (this->get_f)(this, key_length, key, &it_value));
    TASSERT_EQUAL(value, it_value);
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(1, length);

    TASSERT_EQUAL(UR_OK, (this->delete_f)(this, key_length, key));
    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(0, length);
    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));

    TASSERT_EQUAL(UR_OK, (this->free_f)(&this));
    TASSERT_EQUAL(0, this);
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

void terror_dict_expected(char *file, unsigned int line, unsigned int iteration,
    ubjs_glue_dict *this, test_dict_expected *expected,
    char *message)
{
    test_dict_expected *iexpected;
    ubjs_glue_dict_iterator *pit;
    char *msg = 0;

    pstrcat(&msg, "Iteration %u: %s", iteration, message);
    free(message);

    pstrcat(&msg, "\n\nItems in expected:");
    for (iexpected = expected->next; iexpected != expected; iexpected = iexpected->next)
    {
        pstrcat(&msg, "\n # %u %.*s", iexpected->key_length, iexpected->key_length,
            iexpected->key);
    }

    pstrcat(&msg, "\n\nItems in dict:");
    (this->iterate_f)(this, &pit);
    while (UR_OK == (pit->next_f)(pit))
    {
        char *pitk;
        unsigned int pitkl;

        (pit->get_key_length_f)(pit, &pitkl);
        pitk = (char *)malloc(sizeof(char) * pitkl);
        (pit->copy_key_f)(pit, pitk);

        pstrcat(&msg, "\n # %u %.*s", pitkl, pitkl, pitk);
        free(pitk);
    }
    (pit->free_f)(&pit);

    terror(file, line, msg);
}

void test_glue_dict_iteration(unsigned int iteration)
{
    ubjs_glue_dict_builder builder = (ubjs_glue_dict_builder)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_dict *this;
    int ret=1;
    test_dict_expected *root;

    unsigned int i, j;
    unsigned int DICT_length;
    unsigned int key_length;
    char key_tmp[10];
    test_dict_expected *expected_tmp;
    char value[] = "rower";
    char *nvalue = 0;
    unsigned int items_to_do;
    unsigned int item_delete;
    unsigned int tmp_length = -1;

    printf("Iteration %u\n", iteration);

    root = test_dict_expected_new();
    (builder)(lib, free, &this);

    DICT_length = rand() % DICT_LENGTH_MAX + 1;

    for (i=0; i<DICT_length; i++)
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

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, DICT_length)))
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            DICT_length, tmp_length);
        TERROR_DICT_EXPECTED(iteration, this, root, message);
    }

    for (expected_tmp = root->next; expected_tmp != root; expected_tmp = expected_tmp->next)
    {
        if (0 != TASSERT_EQUAL(UR_OK, (this->get_f)(this, expected_tmp->key_length,
            expected_tmp->key, (void **)&nvalue)))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_f %u %.*s",
                expected_tmp->key_length, expected_tmp->key_length, expected_tmp->key);
            TERROR_DICT_EXPECTED(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f but keys did not match");
            TERROR_DICT_EXPECTED(iteration, this, root, message);
        }
    }

    items_to_do = rand() % ((int)sqrt(DICT_length));

    for (j=0; j<items_to_do; j++)
    {
        if (iteration < ITERATIONS / 2)
        {
            item_delete = rand() % DICT_length;
            for (i=0, expected_tmp = root->next; i < item_delete;
                i++, expected_tmp = expected_tmp->next)
            {
            }
            (this->delete_f)(this, expected_tmp->key_length, expected_tmp->key);

            if (0 != TASSERT_EQUAL(UR_ERROR, (this->get_f)(this, expected_tmp->key_length,
                expected_tmp->key, (void **)&nvalue)))
            {
                char *message = 0;
                pstrcat(&message, "Did get_f %u %.*s when expected not to",
                    expected_tmp->key_length, expected_tmp->key_length, expected_tmp->key);
                TERROR_DICT_EXPECTED(iteration, this, root, message);
            }

            expected_tmp->prev->next = expected_tmp->next;
            expected_tmp->next->prev = expected_tmp->prev;
            test_dict_expected_free(expected_tmp);
            DICT_length--;
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
            DICT_length++;
        }
    }

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, DICT_length)))
    {
        char *message = 0;
        pstrcat(&message, "Wrong lengths: expected %u, actual %u",
            DICT_length, tmp_length);
        TERROR_DICT_EXPECTED(iteration, this, root, message);
    }

    for (expected_tmp = root->next; expected_tmp != root; expected_tmp = expected_tmp->next)
    {
        if (0 != TASSERT_EQUAL(UR_OK, (this->get_f)(this, expected_tmp->key_length,
            expected_tmp->key, (void **)&nvalue)))
        {
            char *message = 0;
            pstrcat(&message, "Cannot get_f %u %.*s",
                expected_tmp->key_length, expected_tmp->key_length, expected_tmp->key);
            TERROR_DICT_EXPECTED(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            pstrcat(&message, "Did get_f but keys did not match");
            TERROR_DICT_EXPECTED(iteration, this, root, message);
        }
    }

    (this->free_f)(&this);

    while (root->next != root)
    {
        expected_tmp = root->next;
        root->next = expected_tmp->next;
        test_dict_expected_free(expected_tmp);
    }
    test_dict_expected_free(root);
}

void test_glue_dict_performance(void)
{
    unsigned int i;

    srand(time(0));
    for (i=0; i<ITERATIONS; i++)
    {
        test_glue_dict_iteration(i);
    }
}
