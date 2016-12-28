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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#include "test_common.h"
#include "test_glue_dict.h"

void suite_glue_dict(tcontext *context, char *name, ubjs_glue_dict_factory factory)
{
    tsuite *suite;
    TSUITEARG(name, suite_glue_dict_before, suite_glue_dict_after,
        factory, &suite);
    tcontext_add_suite(context, suite);

    TTESTARG(suite, test_glue_dict_allocation, factory);
    TTESTARG(suite, test_glue_dict_usage, factory);
    TTESTARG(suite, test_glue_dict_performance, factory);
}

void suite_glue_dict_before(void)
{
    ubjs_library_builder *builder=0;
    ubjs_library_builder_new(&builder);
    ubjs_library_builder_set_glue_dict_factory(builder,
        (ubjs_glue_dict_factory)tsuiteargs);
    ubjs_library_builder_build(builder, (ubjs_library **)&tstate);
    ubjs_library_builder_free(&builder);
}

void suite_glue_dict_after(void)
{
    ubjs_library_free((ubjs_library **)&tstate);
}

#define ITERATIONS 10
#define TRIE_LENGTH_MAX 10000
#define KEY_LENGTH_MAX 10

void test_glue_dict_allocation(void)
{
    ubjs_glue_dict_factory factory = (ubjs_glue_dict_factory)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_dict *this = 0;
    ubjs_glue_dict_iterator *iterator = 0;
    unsigned int length = -1;

    TASSERT_EQUAL(UR_OK, (factory)(lib, free, &this));
    TASSERT_NOT_EQUAL(0, this);

    TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &length));
    TASSERT_EQUALI(0, length);

    TASSERT_EQUAL(UR_OK, (this->iterate_f)(this, &iterator));
    TASSERT_NOT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_ERROR, (iterator->next_f)(iterator));
    TASSERT_EQUAL(UR_OK, (iterator->free_f)(&iterator));
    TASSERT_EQUAL(0, iterator);
    TASSERT_EQUAL(UR_OK, (this->free_f)(&this));
    TASSERT_EQUAL(0, this);
}

void test_glue_dict_usage(void)
{
    ubjs_glue_dict_factory factory = (ubjs_glue_dict_factory)targs;
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

    TASSERT_EQUAL(UR_OK, (factory)(lib, free, &this));
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

void test_kv_free(test_kv *this)
{
    if (0 != this->key)
    {
        free(this->key);
    }
    free(this);
}

test_kv *test_kv_new(void)
{
    test_kv *this;

    this = (test_kv *)malloc(sizeof(test_kv));
    this->prev=this;
    this->next=this;
    this->key=0;
    return this;
}

void random_str(unsigned int length, char *str)
{
    unsigned int i;

    for (i=0; i<length; i++)
    {
        unsigned int pick;
        pick = rand() % 26;
        str[i] = (char) ('a' + pick);
    }
}

void scrum(char **pthis, char *format, ...)
{
    char *now = 0;
    int ret;
    unsigned int length;
    va_list args;
    char *othis = 0;
    unsigned int olen = 0;

    if (0 != *pthis)
    {
        othis = *pthis;
        olen = strlen(othis);
    }

    va_start(args, format);
    ret=vsnprintf(now, 0, format, args);
    va_end(args);

    length=olen + ret;
    now=(char *)malloc(sizeof(char) * (length + 1));

    if (0 != othis)
    {
        memcpy(now, othis, olen * sizeof(char));
        free(othis);
    }

    va_start(args, format);
    vsnprintf(now + olen, ret + 1, format, args);
    va_end(args);

    now[length] = 0;
    *pthis=now;
}

void terror_dict_kv(char *file, unsigned int line, unsigned int iteration,
    ubjs_glue_dict *this, test_kv *kv,
    char *message)
{
    test_kv *ikv;
    ubjs_glue_dict_iterator *pit;
    char *msg = 0;

    scrum(&msg, "Iteration %u: %s", iteration, message);
    free(message);

    scrum(&msg, "\n\nItems in KV:");
    for (ikv = kv->next; ikv != kv; ikv = ikv->next)
    {
        scrum(&msg, "\n # %u %.*s", ikv->key_length, ikv->key_length,
            ikv->key);
    }

    scrum(&msg, "\n\nItems in trie:");
    (this->iterate_f)(this, &pit);
    while (UR_OK == (pit->next_f)(pit))
    {
        char *pitk;
        unsigned int pitkl;

        (pit->get_key_length_f)(pit, &pitkl);
        pitk = (char *)malloc(sizeof(char) * pitkl);
        (pit->copy_key_f)(pit, pitk);

        scrum(&msg, "\n # %u %.*s", pitkl, pitkl, pitk);
        free(pitk);
    }
    (pit->free_f)(&pit);

    terror(file, line, msg);
}

void test_iteration(unsigned int iteration)
{
    ubjs_glue_dict_factory factory = (ubjs_glue_dict_factory)targs;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_glue_dict *this;
    int ret=1;
    test_kv *root;

    unsigned int i, j;
    unsigned int trie_length;
    unsigned int key_length;
    char key_tmp[10];
    test_kv *kv_tmp;
    char value[] = "rower";
    char *nvalue = 0;
    unsigned int items_to_do;
    unsigned int item_delete;
    unsigned int tmp_length = -1;

    printf("Iteration %u\n", iteration);

    root = test_kv_new();
    (factory)(lib, free, &this);

    trie_length = rand() % TRIE_LENGTH_MAX + 1;

    for (i=0; i<trie_length; i++)
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

        kv_tmp = test_kv_new();
        kv_tmp->key = strndup(key_tmp, key_length);
        kv_tmp->key_length = key_length;
        kv_tmp->next=root;
        kv_tmp->prev=root->prev;
        root->prev->next=kv_tmp;
        root->prev=kv_tmp;

        (this->set_f)(this, key_length, key_tmp, strdup(value));
    }

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, trie_length)))
    {
        char *message = 0;
        scrum(&message, "Wrong lengths: expected %u, actual %u",
            trie_length, tmp_length);
        TERROR_DICT_KV(iteration, this, root, message);
    }

    for (kv_tmp = root->next; kv_tmp != root; kv_tmp = kv_tmp->next)
    {
        if (0 != TASSERT_EQUAL(UR_OK, (this->get_f)(this, kv_tmp->key_length, kv_tmp->key,
            (void **)&nvalue)))
        {
            char *message = 0;
            scrum(&message, "Cannot get_f %u %.*s",
                kv_tmp->key_length, kv_tmp->key_length, kv_tmp->key);
            TERROR_DICT_KV(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            scrum(&message, "Did get_f but keys did not match");
            TERROR_DICT_KV(iteration, this, root, message);
        }
    }

    items_to_do = rand() % ((int)sqrt(trie_length));

    for (j=0; j<items_to_do; j++)
    {
        if (iteration < ITERATIONS / 2)
        {
            item_delete = rand() % trie_length;
            for (i=0, kv_tmp = root->next; i < item_delete; i++, kv_tmp = kv_tmp->next)
            {
            }
            (this->delete_f)(this, kv_tmp->key_length, kv_tmp->key);

            if (0 != TASSERT_EQUAL(UR_ERROR, (this->get_f)(this, kv_tmp->key_length, kv_tmp->key,
                (void **)&nvalue)))
            {
                char *message = 0;
                scrum(&message, "Did get_f %u %.*s when expected not to",
                    kv_tmp->key_length, kv_tmp->key_length, kv_tmp->key);
                TERROR_DICT_KV(iteration, this, root, message);
            }

            kv_tmp->prev->next = kv_tmp->next;
            kv_tmp->next->prev = kv_tmp->prev;
            test_kv_free(kv_tmp);
            trie_length--;
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

            kv_tmp = test_kv_new();
            kv_tmp->key = strndup(key_tmp, key_length);
            kv_tmp->key_length = key_length;
            kv_tmp->next=root;
            kv_tmp->prev=root->prev;
            root->prev->next=kv_tmp;
            root->prev=kv_tmp;

            (this->set_f)(this, key_length, key_tmp, strdup(value));
            trie_length++;
        }
    }

    if (0 != TASSERT_EQUAL(UR_OK, (this->get_length_f)(this, &tmp_length) ||
        0 != TASSERT_EQUALI(tmp_length, trie_length)))
    {
        char *message = 0;
        scrum(&message, "Wrong lengths: expected %u, actual %u",
            trie_length, tmp_length);
        TERROR_DICT_KV(iteration, this, root, message);
    }

    for (kv_tmp = root->next; kv_tmp != root; kv_tmp = kv_tmp->next)
    {
        if (0 != TASSERT_EQUAL(UR_OK, (this->get_f)(this, kv_tmp->key_length, kv_tmp->key,
            (void **)&nvalue)))
        {
            char *message = 0;
            scrum(&message, "Cannot get_f %u %.*s",
                kv_tmp->key_length, kv_tmp->key_length, kv_tmp->key);
            TERROR_DICT_KV(iteration, this, root, message);
        }
        else if (0 != TASSERT_STRING_EQUAL(value, nvalue))
        {
            char *message = 0;
            scrum(&message, "Did get_f but keys did not match");
            TERROR_DICT_KV(iteration, this, root, message);
        }
    }

    (this->free_f)(&this);

    while (root->next != root)
    {
        kv_tmp = root->next;
        root->next = kv_tmp->next;
        test_kv_free(kv_tmp);
    }
    test_kv_free(root);
}

void test_glue_dict_performance(void)
{
    unsigned int i;

    srand(time(0));
    for (i=0; i<ITERATIONS; i++)
    {
        test_iteration(i);
    }
}
