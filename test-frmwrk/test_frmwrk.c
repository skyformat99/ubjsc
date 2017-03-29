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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test_frmwrk.h"
#include "test_list.h"

typedef struct twill_return_method twill_return_method;
typedef struct twill_return_item twill_return_item;
typedef struct ttest ttest;

test_list *current_mocks = 0;

struct twill_return_method
{
    char *method;
    test_list *list;
};

enum twill_return_item_type
{
    TRIT_O,
    TRIT_UI
};

struct twill_return_item
{
    enum twill_return_item_type type;
    union value
    {
        void *vo;
        unsigned int vui;
    } value;
    char *comment;
};

void twill_return_method_free(void **x)
{
    unsigned int len;

    twill_return_method *m = (twill_return_method *)*x;

    test_list_len(m->list, &len);
    if (0 != len)
    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unused %u mocks exist for method %s", len, m->method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unused %u mocks exist for method %s", len, m->method);
        cr_expect_fail("%s", x);
        free(x);
    }

    test_list_free(&(m->list));
    free(m->method);
    free(m);
    *x=0;
}

void twill_return_item_free(void **x)
{
    twill_return_item *it = (twill_return_item *)*x;
    free(it->comment);
    free(it);
    *x=0;
}

void twill_return_add(char *method, twill_return_item* item)
{
    test_list_item *at = current_mocks->sentinel->next;
    twill_return_method *m = 0;

    while (at != current_mocks->sentinel)
    {
        m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_add(m->list, item, 0);
            return;
        }
        at = at->next;
    }

    m = (twill_return_method *)malloc(sizeof(struct twill_return_method));
    m->method = strdup(method);
    test_list_new(twill_return_item_free, &(m->list));
    test_list_add(current_mocks, m, 0);
    test_list_add(m->list, item, 0);
}

int tmockui(char *method, unsigned int *value)
{
    test_list_item *at = current_mocks->sentinel->next;
    *value = 0;

    while (at != current_mocks->sentinel)
    {
        twill_return_method *m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_item *b = m->list->sentinel->next;
            twill_return_item *item = (twill_return_item *)b->obj;
            unsigned int len;

            *value = item->value.vui;
            //printf("TMOCKUI %s %d (%s)\n", method, *value, item->comment);

            test_list_remove(m->list, b);
            test_list_len(m->list, &len);

            if (0 == len)
            {
                test_list_remove(current_mocks, at);
            }

            return 1;
        }
        at = at->next;
    }

    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unexpected mock for method %s", method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unexpected mock for method %s", method);
        cr_expect_eq("%s", x);
        free(x);
    }

    return 0;
}

int tmocko(char *method, void **value)
{
    test_list_item *at = current_mocks->sentinel->next;
    *value = 0;

    while (at != current_mocks->sentinel)
    {
        twill_return_method *m = (twill_return_method *)at->obj;
        if (0 == strcmp(method, m->method))
        {
            test_list_item *b = m->list->sentinel->next;
            twill_return_item *item = (twill_return_item *)b->obj;
            unsigned int len;

            *value = item->value.vo;
            //printf("TMOCKO %s %p (%s)\n", method, *value, item->comment);

            test_list_remove(m->list, b);
            test_list_len(m->list, &len);

            if (0 == len)
            {
                test_list_remove(current_mocks, at);
            }

            return 1;
        }
        at = at->next;
    }

    {
        char *x;
        unsigned int xl;
        xl = snprintf(0, 0, "Unexpected mock for method %s", method);
        x = (char *)malloc(sizeof(char) * (xl + 1));
        snprintf(x, xl + 1, "Unexpected mock for method %s", method);
        cr_expect_fail("%s", x);
        free(x);
    }

    return 0;
}

void twill_returno(char *method, void *value)
{
    twill_returnoc(method, value, 0);
}

void twill_returnoc(char *method, void *value, char *comment)
{
    twill_return_item *ri;
    ri = (twill_return_item *)malloc(sizeof(struct twill_return_item));
    ri->type=TRIT_O;
    ri->value.vo=value;
    ri->comment = comment != 0 ? strdup(comment) : 0;
    twill_return_add(method, ri);
}

void twill_returnui(char *method, unsigned int value)
{
    twill_returnuic(method, value, 0);
}

void twill_returnuic(char *method, unsigned int value, char *comment)
{
    twill_return_item *ri;
    ri = (twill_return_item *)malloc(sizeof(struct twill_return_item));
    ri->type=TRIT_UI;
    ri->value.vui=value;
    ri->comment = comment != 0 ? strdup(comment) : 0;
    twill_return_add(method, ri);
}

void tbefore(void)
{
    test_list_new(twill_return_method_free, &current_mocks);
}

void tafter(void)
{
    test_list_free(&current_mocks);
}
