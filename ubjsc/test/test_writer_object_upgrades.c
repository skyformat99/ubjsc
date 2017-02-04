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

#include <ubjs.h>

#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

void test_writer_object_upgraded_from_uint8_to_int16(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    ubjs_prmtv *upgraded_items[5];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 31);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    pretty = (char *)malloc(sizeof(char) * 108);
    snprintf(pretty, 19, "[{][$][I][#][U][5]");

    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        ubjs_prmtv_int16(lib, 0, upgraded_items + i);

        bytes[6 + 5 * i] = 85;
        bytes[7 + 5 * i] = 1;
        snprintf((char *)bytes + 8 + 5 * i, 2, "%01u", i);
        bytes[9 + 5 * i] = 0;
        bytes[10 + 5 * i] = 0;
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    writer_mock_dict_will_return2(5, items, upgraded_items);
    snprintf(pretty + 103, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              31, bytes,
              107, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(5, items);
    writer_mock_free(5, upgraded_items);
}

void test_writer_object_upgraded_from_int8_to_int16(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    ubjs_prmtv *upgraded_items[5];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 31);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    pretty = (char *)malloc(sizeof(char) * 108);
    snprintf(pretty, 19, "[{][$][I][#][U][5]");

    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        ubjs_prmtv_int16(lib, 0, upgraded_items + i);

        bytes[6 + 5 * i] = 85;
        bytes[7 + 5 * i] = 1;
        snprintf((char *)bytes + 8 + 5 * i, 2, "%01u", i);
        bytes[9 + 5 * i] = 0;
        bytes[10 + 5 * i] = 0;
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    writer_mock_dict_will_return2(5, items, upgraded_items);
    snprintf(pretty + 103, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              31, bytes,
              107, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(5, items);
    writer_mock_free(5, upgraded_items);
}

void test_writer_object_not_upgraded_from_int8_to_int16_too_little(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[4];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 27);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 4;
    pretty = (char *)malloc(sizeof(char) * 97);
    snprintf(pretty, 13, "[{][#][U][4]");

    for (i=0; i<4; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
    }
    writer_mock_dict_will_return(4, items);
    snprintf(pretty + 92, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              27, bytes,
              96, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(4, items);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_int32(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[6];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 41);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 6;
    pretty = (char *)malloc(sizeof(char) * 137);
    snprintf(pretty, 13, "[{][#][U][6]");

    for (i=0; i<6; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][l][0]", i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
    }
    writer_mock_dict_will_return(6, items);
    snprintf(pretty + 132, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              41, bytes,
              136, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(6, items);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_int64(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[6];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 45);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 6;
    pretty = (char *)malloc(sizeof(char) * 137);
    snprintf(pretty, 13, "[{][#][U][6]");

    for (i=0; i<6; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int64(lib, 0, items + i);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][L][0]", i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
    }
    writer_mock_dict_will_return(6, items);
    snprintf(pretty + 132, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              45, bytes,
              136, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(6, items);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_other_types(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[6];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 38);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 6;
    pretty = (char *)malloc(sizeof(char) * 137);
    snprintf(pretty, 13, "[{][#][U][6]");

    for (i=0; i<6; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][C][r]", i);
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
    }
    writer_mock_dict_will_return(6, items);
    snprintf(pretty + 132, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              38, bytes,
              136, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(6, items);
}

void test_writer_object_upgraded_from_int8_int16_to_int32(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[9];
    ubjs_prmtv *upgraded_items[9];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 69);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    pretty = (char *)malloc(sizeof(char) * 176);
    snprintf(pretty, 19, "[{][$][l][#][U][9]");

    for (i=0; i<9; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
        }
        ubjs_prmtv_int32(lib, 0, upgraded_items + i);

        bytes[6 + 7 * i] = 85;
        bytes[7 + 7 * i] = 1;
        snprintf((char *)bytes + 8 + 7 * i, 2, "%01u", i);
        bytes[9 + 7 * i] = 0;
        bytes[10 + 7 * i] = 0;
        bytes[11 + 7 * i] = 0;
        bytes[12 + 7 * i] = 0;
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    writer_mock_dict_will_return2(9, items, upgraded_items);
    snprintf(pretty + 171, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              69, bytes,
              175, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(9, items);
    writer_mock_free(9, upgraded_items);
}

void test_writer_object_upgraded_from_uint8_int16_to_int32(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[9];
    ubjs_prmtv *upgraded_items[9];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 69);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    pretty = (char *)malloc(sizeof(char) * 176);
    snprintf(pretty, 19, "[{][$][l][#][U][9]");

    for (i=0; i<9; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
        }

        ubjs_prmtv_int32(lib, 0, upgraded_items + i);
        bytes[6 + 7 * i] = 85;
        bytes[7 + 7 * i] = 1;
        snprintf((char *)bytes + 8 + 7 * i, 2, "%01u", i);
        bytes[9 + 7 * i] = 0;
        bytes[10 + 7 * i] = 0;
        bytes[11 + 7 * i] = 0;
        bytes[12 + 7 * i] = 0;
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    writer_mock_dict_will_return2(9, items, upgraded_items);
    snprintf(pretty + 171, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              69, bytes,
              175, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(9, items);
    writer_mock_free(9, upgraded_items);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_too_little(void)
{
    uint8_t *bytes;
    char *pretty;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *items[8];
    ubjs_prmtv *value;
    unsigned int i;
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 63);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 8;
    pretty = (char *)malloc(sizeof(char) * 177);
    snprintf(pretty, 13, "[{][#][U][8]");

    for (i=0; i<8; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 20, 21, "\n    [U][1][%01u][l][0]", i);
        }
    }
    writer_mock_dict_will_return(8, items);
    snprintf(pretty + 172, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              63, bytes,
              176, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(8, items);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_int64(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[10];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 83);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    pretty = (char *)malloc(sizeof(char) * 218);
    snprintf(pretty, 14, "[{][#][U][10]");

    for (i=0; i<10; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int64(lib, 0, items + i);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][L][0]", i);
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][l][0]", i);
        }
    }
    writer_mock_dict_will_return(10, items);
    snprintf(pretty + 213, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              83, bytes,
              217, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10, items);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_other_types(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[10];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 76);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    pretty = (char *)malloc(sizeof(char) * 218);
    snprintf(pretty, 14, "[{][#][U][10]");

    for (i=0; i<10; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 1;
        at += snprintf((char *)bytes + at, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][I][0]", i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][C][r]", i);
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 20, 21, "\n    [U][1][%01u][l][0]", i);
        }
    }
    writer_mock_dict_will_return(10, items);
    snprintf(pretty + 213, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              76, bytes,
              217, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10, items);
}

void test_writer_object_upgraded_from_uint8_int16_int32_to_int64(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[21];
    ubjs_prmtv *upgraded_items[21];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 258);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    pretty = (char *)malloc(sizeof(char) * 402);
    snprintf(pretty, 20, "[{][$][L][#][U][21]");

    for (i=0; i<21; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(lib, 0, items + i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int64(lib, 0, items + i);
        }
        ubjs_prmtv_int64(lib, 0, upgraded_items + i);

        bytes[6 + 12 * i] = 85;
        bytes[7 + 12 * i] = 2;
        snprintf((char *)bytes + 8 + 12 * i, 3, "%02u", i);
        bytes[10 + 12 * i] = 0;
        bytes[11 + 12 * i] = 0;
        bytes[12 + 12 * i] = 0;
        bytes[13 + 12 * i] = 0;
        bytes[14 + 12 * i] = 0;
        bytes[15 + 12 * i] = 0;
        bytes[16 + 12 * i] = 0;
        bytes[17 + 12 * i] = 0;
        snprintf(pretty + 19 + i * 18, 19, "\n    [U][2][%02u][0]", i);
    }
    writer_mock_dict_will_return2(21, items, upgraded_items);
    snprintf(pretty + 397, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              258, bytes,
              401, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(21, items);
    writer_mock_free(21, upgraded_items);
}

void test_writer_object_upgraded_from_int8_int16_int32_to_int64(void)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *value;
    ubjs_prmtv *items[21];
    ubjs_prmtv *upgraded_items[21];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 258);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    pretty = (char *)malloc(sizeof(char) * 402);
    snprintf(pretty, 20, "[{][$][L][#][U][21]");

    for (i=0; i<21; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
        }
        else
        {
            ubjs_prmtv_int64(lib, 0, items + i);
        }
        ubjs_prmtv_int64(lib, 0, upgraded_items + i);

        bytes[6 + 12 * i] = 85;
        bytes[7 + 12 * i] = 2;
        snprintf((char *)bytes + 8 + 12 * i, 3, "%02u", i);
        bytes[10 + 12 * i] = 0;
        bytes[11 + 12 * i] = 0;
        bytes[12 + 12 * i] = 0;
        bytes[13 + 12 * i] = 0;
        bytes[14 + 12 * i] = 0;
        bytes[15 + 12 * i] = 0;
        bytes[16 + 12 * i] = 0;
        bytes[17 + 12 * i] = 0;
        snprintf(pretty + 19 + i * 18, 19, "\n    [U][2][%02u][0]", i);
    }
    writer_mock_dict_will_return2(21, items, upgraded_items);
    snprintf(pretty + 397, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              258, bytes,
              401, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(21, items);
    writer_mock_free(21, upgraded_items);
}

void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_too_little(void)
{
    uint8_t *bytes;
    char *pretty;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *items[20];
    ubjs_prmtv *value;
    unsigned int i;
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 247);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 20;
    pretty = (char *)malloc(sizeof(char) * 438);
    snprintf(pretty, 14, "[{][#][U][20]");

    for (i=0; i<20; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 2;
        at += snprintf((char *)bytes + at, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][I][0]", i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][l][0]", i);
        }
        else
        {
            ubjs_prmtv_int64(lib, 0, items + i);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][L][0]", i);
        }
    }
    writer_mock_dict_will_return(20, items);
    snprintf(pretty + 433, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              247, bytes,
              437, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(20, items);
}

void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_are_other_types(void)
{
    uint8_t *bytes;
    char *pretty;
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_prmtv *items[22];
    ubjs_prmtv *value;
    unsigned int i;
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 266);
    bytes[at++] = 123;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 22;
    pretty = (char *)malloc(sizeof(char) * 480);
    snprintf(pretty, 14, "[{][#][U][22]");

    for (i=0; i<22; i++)
    {
        bytes[at++] = 85;
        bytes[at++] = 2;
        at += snprintf((char *)bytes + at, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][i][0]", i);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][I][0]", i);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][l][0]", i);
        }
        else if (i == 3)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][C][r]", i);
        }
        else
        {
            ubjs_prmtv_int64(lib, 0, items + i);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 21, 22, "\n    [U][2][%02u][L][0]", i);
        }
    }
    writer_mock_dict_will_return(22, items);
    snprintf(pretty + 475, 5, "\n[}]");

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              266, bytes,
              479, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(22, items);
}