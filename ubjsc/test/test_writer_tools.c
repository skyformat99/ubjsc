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

#include "test_writer_tools.h"
#include "test_frmwrk.h"
/*
static void would_write_print(would_write_call *);
static void would_print_print(would_print_call *);
*/

void would_write_call_new(uint8_t *data, unsigned int len, would_write_call **pthis)
{
    would_write_call *this;
    this=(would_write_call *)malloc(sizeof(struct would_write_call));

    this->len=len;
    this->data=(uint8_t *)malloc(sizeof(uint8_t)*len);
    memcpy(this->data, data, sizeof(uint8_t) * len);

    *pthis=this;
}

void would_write_call_free(would_write_call **pthis)
{
    would_write_call *this=*pthis;

    free(this->data);
    free(this);

    *pthis=0;
}

void would_print_call_new(char *data, unsigned int len, would_print_call **pthis)
{
    would_print_call *this;
    this=(would_print_call *)malloc(sizeof(struct would_print_call));

    this->len=len;
    this->data=(char *)malloc(sizeof(char)*len);
    memcpy(this->data, data, sizeof(char) * len);

    *pthis=this;
}

void would_print_call_free(would_print_call **pthis)
{
    would_print_call *this=*pthis;

    free(this->data);
    free(this);

    *pthis=0;
}

void wrapped_writer_context_new(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this;
    this=(wrapped_writer_context *)malloc(sizeof(struct wrapped_writer_context));
    this->calls_would_write = 0;
    this->calls_would_print = 0;
    this->calls_free = 0;

    test_list_new((test_list_free_f)would_write_call_free, &(this->calls_would_write));
    test_list_new((test_list_free_f)would_print_call_free, &(this->calls_would_print));
    test_list_new(0, &(this->calls_free));

    *pthis=this;
}

void wrapped_writer_context_free(wrapped_writer_context **pthis)
{
    wrapped_writer_context *this = *pthis;

    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_would_print));
    test_list_free(&(this->calls_free));

    free(this);
    *pthis=0;
}

/*
void wrapped_writer_context_reset(wrapped_writer_context *this)
{
    test_list_free(&(this->calls_would_write));
    test_list_free(&(this->calls_would_print));
    test_list_free(&(this->calls_free));

    test_list_new((test_list_free_f)would_write_call_free, &(this->calls_would_write));
    test_list_new((test_list_free_f)would_print_call_free, &(this->calls_would_print));
    test_list_new(0, &(this->calls_free));
}
*/

void writer_context_would_write(void *userdata, uint8_t *data, unsigned int len)
{
    wrapped_writer_context *this=(wrapped_writer_context *)userdata;

    would_write_call *call;
    would_write_call_new(data, len, &call);
    test_list_add(this->calls_would_write, call, 0);

    /*would_write_print(call);*/
}

void writer_context_would_print(void *userdata, char *data, unsigned int len)
{
    wrapped_writer_context *this=(wrapped_writer_context *)userdata;

    would_print_call *call;
    would_print_call_new(data, len, &call);
    test_list_add(this->calls_would_print, call, 0);

    /*would_print_print(call);*/
}

#define WOULD_WRITE_PRINT_OFFSET 8
/*
static void would_write_print(would_write_call *this)
{
    unsigned int i;

    printf("Would write %u bytes:\n", this->len);
    for (i=0; i<this->len; i++)
    {
        if (0 == (i % 8))
        {
            printf("%u | ", i/8);
        }
        printf("%u\t", this->data[i]);
        if (7 == (i % 8))
        {
            printf("\n");
        }
    }
    printf("\n");
}

static void would_print_print(would_print_call *this)
{
    unsigned int i;

    printf("Would print %u bytes:\n", this->len);
    for (i=0; i<this->len; i++)
    {
        if (0 == (i % 32))
        {
            printf("%u | ", i/32);
        }
        printf("%c", this->data[i]);
        if (31 == (i % 32))
        {
            printf("\n");
        }
    }
    printf("\n");
}
*/

void writer_context_free(void *userdata)
{
    wrapped_writer_context *this=(wrapped_writer_context *)userdata;
    test_list_add(this->calls_free, 0, 0);
}

void writer_mock_free(unsigned int length, ubjs_prmtv **items)
{
    unsigned int j;
    for (j=0; j<length; j++)
    {
        ubjs_prmtv_free(items + j);
    }
}

void writer_mock_dict_iterator_next(unsigned int k, unsigned int key_length, ubjs_prmtv *item,
    ubjs_bool with_key, ubjs_bool go_into_children)
{
    ubjs_prmtv_type type;
    twill_returnui("dict_iterator_next", 1, UR_OK);
    ubjs_prmtv_get_type(item, &type);

    if (UTRUE == with_key)
    {
        char *key;
        key = (char *)malloc(sizeof(char) * (key_length + 1));
        snprintf(key, key_length + 1, "%.*u", key_length, k);

        twill_returnui("dict_iterator_get_key_length", 1, UR_OK);
        twill_returnui("dict_iterator_get_key_length", 1, key_length);

        twill_returnui("dict_iterator_copy_key", 1, UR_OK);
        twill_returnui("dict_iterator_copy_key", 1, key_length);
        twill_returno("dict_iterator_copy_key", 1, key);
    }

    twill_returnui("dict_iterator_get_value", 1, UR_OK);
    twill_returno("dict_iterator_get_value", 1, (void *)item);

    if (UTRUE == go_into_children)
    {
        switch (type)
        {
            case UOT_ARRAY:
                twill_returnui("array_get_length", 1, UR_OK);
                twill_returnui("array_get_length", 1, 0);

                /* metrics */
                twill_returnui("array_iterator_next", 1, UR_ERROR);
                /* upgrade */
                twill_returnui("array_iterator_next", 1, UR_ERROR);
                break;

            case UOT_OBJECT:
                twill_returnui("dict_get_length", 1, UR_OK);
                twill_returnui("dict_get_length", 1, 0);

                /* metrics */
                twill_returnui("dict_iterator_next", 1, UR_ERROR);
                /* upgrade */
                twill_returnui("dict_iterator_next", 1, UR_ERROR);
                break;

            default:
                break;
        }
    }
}

void writer_mock_dict_will_return2(unsigned int length, ubjs_prmtv **items,
    ubjs_prmtv **upgraded_items)
{
    unsigned int i;
    unsigned int j;
    unsigned int key_length;

    key_length = snprintf(0, 0, "%u", length == 0 ? 0 : length - 1);

    /* write, print */
    for (i=0; i<2; i++)
    {
        twill_returnui("dict_get_length", 1, UR_OK);
        twill_returnui("dict_get_length", 1, length);

        /* metrics */
        for (j=0; j<length; j++)
        {
            writer_mock_dict_iterator_next(j, key_length, items[j], UFALSE, UFALSE);
        }
        twill_returnui("dict_iterator_next", 1, UR_ERROR);

        /* upgrade */
        if (0 != upgraded_items)
        {
            for (j=0; j<length; j++)
            {
                writer_mock_dict_iterator_next(j, key_length, upgraded_items[j], UTRUE, UFALSE);

                /* in upgraded */
                twill_returnui("dict_set", 1, UR_OK);
            }
            twill_returnui("dict_iterator_next", 1, UR_ERROR);
        }

        /* length */
        for (j=0; j<length; j++)
        {
            writer_mock_dict_iterator_next(j, key_length,
                 0 != upgraded_items ? upgraded_items[j] : items[j], UTRUE, UTRUE);
        }
        twill_returnui("dict_iterator_next", 1, UR_ERROR);
    }
}

void writer_mock_dict_will_return(unsigned int length, ubjs_prmtv **items)
{
    writer_mock_dict_will_return2(length, items, UFALSE);
}

void writer_mock_array_iterator_next(unsigned int k, unsigned int key_length, ubjs_prmtv *item,
    ubjs_bool go_into_children)
{
    ubjs_prmtv_type type;
    twill_returnui("array_iterator_next", 1, UR_OK);
    ubjs_prmtv_get_type(item, &type);

    twill_returnui("array_iterator_get", 1, UR_OK);
    twill_returno("array_iterator_get", 1, (void *)item);

    if (UTRUE == go_into_children)
    {
        switch (type)
        {
            case UOT_ARRAY:
                twill_returnui("array_get_length", 1, UR_OK);
                twill_returnui("array_get_length", 1, 0);

                /* metrics */
                twill_returnui("array_iterator_next", 1, UR_ERROR);
                /* upgrade */
                twill_returnui("array_iterator_next", 1, UR_ERROR);
                break;

            case UOT_OBJECT:
                twill_returnui("dict_get_length", 1, UR_OK);
                twill_returnui("dict_get_length", 1, 0);

                /* metrics */
                twill_returnui("dict_iterator_next", 1, UR_ERROR);
                /* upgrade */
                twill_returnui("dict_iterator_next", 1, UR_ERROR);
                break;

            default:
                break;
        }
    }
}

void writer_mock_array_will_return2(unsigned int length, ubjs_prmtv **items,
    ubjs_prmtv **upgraded_items)
{
    unsigned int i;
    unsigned int j;
    unsigned int key_length;

    key_length = snprintf(0, 0, "%u", length == 0 ? 0 : length - 1);

    /* write, print */
    for (i=0; i<2; i++)
    {
        twill_returnui("array_get_length", 1, UR_OK);
        twill_returnui("array_get_length", 1, length);

        /* metrics */
        for (j=0; j<length; j++)
        {
            writer_mock_array_iterator_next(j, key_length, items[j], UFALSE);
        }
        twill_returnui("array_iterator_next", 1, UR_ERROR);

        /* upgrade */
        if (0 != upgraded_items)
        {
            twill_returnui("array_builder_set_length", 1, UR_OK);
            twill_returnui("array_builder_set_item_size", 1, UR_OK);

            for (j=0; j<length; j++)
            {
                writer_mock_array_iterator_next(j, key_length, upgraded_items[j], UFALSE);

                /* in upgraded */
                twill_returnui("array_add_last", 1, UR_OK);
            }
            twill_returnui("array_iterator_next", 1, UR_ERROR);
        }

        /* length */
        for (j=0; j<length; j++)
        {
            writer_mock_array_iterator_next(j, key_length,
                 0 != upgraded_items ? upgraded_items[j] : items[j], UTRUE);
        }
        twill_returnui("array_iterator_next", 1, UR_ERROR);
    }
}

void writer_mock_array_will_return(unsigned int length, ubjs_prmtv **items)
{
    writer_mock_array_will_return2(length, items, UFALSE);
}
