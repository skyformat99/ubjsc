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

void test_writer_array_upgraded_from_uint8_to_int16()
{
    uint8_t bytes[16];
    char pretty[63];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    snprintf(pretty, 19, "[[][$][I][#][U][5]");

    ubjs_prmtv_array(&value);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(0, &item);
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
        }
        bytes[6 + 2 * i] = 0;
        bytes[7 + 2 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 58, 5, "\n[]]");

    sw_verify(lib, value,
              16, bytes,
              62, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_upgraded_from_int8_to_int16()
{
    uint8_t bytes[16];
    char pretty[63];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    snprintf(pretty, 19, "[[][$][I][#][U][5]");

    ubjs_prmtv_array(&value);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
        }
        bytes[6 + 2 * i] = 0;
        bytes[7 + 2 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 58, 5, "\n[]]");

    sw_verify(lib, value,
              16, bytes,
              62, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_to_int16_too_little()
{
    uint8_t bytes[15];
    ubjs_library *lib;
    char pretty[61];
    unsigned int i;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 4;
    snprintf(pretty, 13, "[[][#][U][4]");

    ubjs_prmtv_array(&value);
    for (i=0; i<4; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 56, 5, "\n[]]");

    sw_verify(lib, value,
              15, bytes,
              60, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_int32()
{
    uint8_t bytes[20];
    char pretty[72];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    ubjs_prmtv_array(&value);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [l][0]");
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 67, 5, "\n[]]");

    sw_verify(lib, value,
              20, bytes,
              71, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_int64()
{
    uint8_t bytes[24];
    char pretty[72];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    ubjs_prmtv_array(&value);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int64(0, &item);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [L][0]");
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 67, 5, "\n[]]");

    sw_verify(lib, value,
              24, bytes,
              71, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_other_types()
{
    uint8_t bytes[17];
    char pretty[72];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    ubjs_prmtv_array(&value);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_char('r', &item);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 12 + i * 11, 12, "\n    [C][r]");
        }
        else
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 67, 5, "\n[]]");

    sw_verify(lib, value,
              17, bytes,
              71, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_upgraded_from_int8_int16_to_int32()
{
    uint8_t bytes[42];
    char pretty[95];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    snprintf(pretty, 19, "[[][$][l][#][U][9]");

    ubjs_prmtv_array(&value);
    for (i=0; i<9; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
        }
        else
        {
            ubjs_prmtv_int32(0, &item);
        }
        bytes[6 + 4 * i] = 0;
        bytes[7 + 4 * i] = 0;
        bytes[8 + 4 * i] = 0;
        bytes[9 + 4 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 90, 5, "\n[]]");

    sw_verify(lib, value,
              42, bytes,
              94, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_upgraded_from_uint8_int16_to_int32()
{
    uint8_t bytes[42];
    char pretty[95];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    snprintf(pretty, 19, "[[][$][l][#][U][9]");

    ubjs_prmtv_array(&value);
    for (i=0; i<9; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(0, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
        }
        else
        {
            ubjs_prmtv_int32(0, &item);
        }
        bytes[6 + 4 * i] = 0;
        bytes[7 + 4 * i] = 0;
        bytes[8 + 4 * i] = 0;
        bytes[9 + 4 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 90, 5, "\n[]]");

    sw_verify(lib, value,
              42, bytes,
              94, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_too_little()
{
    uint8_t bytes[39];
    char pretty[105];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 8;
    snprintf(pretty, 13, "[[][#][U][8]");

    ubjs_prmtv_array(&value);
    for (i=0; i<8; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
        else
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [l][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 100, 5, "\n[]]");

    sw_verify(lib, value,
              39, bytes,
              104, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_int64()
{
    uint8_t bytes[53];
    char pretty[128];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    snprintf(pretty, 14, "[[][#][U][10]");

    ubjs_prmtv_array(&value);
    for (i=0; i<10; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_int64(0, &item);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }
        else
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 123, 5, "\n[]]");

    sw_verify(lib, value,
              53, bytes,
              127, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_other_types()
{
    uint8_t bytes[46];
    char pretty[128];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    snprintf(pretty, 14, "[[][#][U][10]");

    ubjs_prmtv_array(&value);
    for (i=0; i<10; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_char('r', &item);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 11, 12, "\n    [C][r]");
        }
        else
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 123, 5, "\n[]]");

    sw_verify(lib, value,
              46, bytes,
              127, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_upgraded_from_uint8_int16_int32_to_int64()
{
    uint8_t bytes[174];
    char pretty[192];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    snprintf(pretty, 20, "[[][$][L][#][U][21]");

    ubjs_prmtv_array(&value);
    for (i=0; i<21; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(0, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(0, &item);
        }
        else
        {
            ubjs_prmtv_int64(0, &item);
        }
        bytes[6 + 8 * i] = 0;
        bytes[7 + 8 * i] = 0;
        bytes[8 + 8 * i] = 0;
        bytes[9 + 8 * i] = 0;
        bytes[10 + 8 * i] = 0;
        bytes[11 + 8 * i] = 0;
        bytes[12 + 8 * i] = 0;
        bytes[13 + 8 * i] = 0;
        snprintf(pretty + 19 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 187, 5, "\n[]]");

    sw_verify(lib, value,
              174, bytes,
              191, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_upgraded_from_int8_int16_int32_to_int64()
{
    uint8_t bytes[174];
    char pretty[192];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    snprintf(pretty, 20, "[[][$][L][#][U][21]");

    ubjs_prmtv_array(&value);
    for (i=0; i<21; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(0, &item);
        }
        else
        {
            ubjs_prmtv_int64(0, &item);
        }
        bytes[6 + 8 * i] = 0;
        bytes[7 + 8 * i] = 0;
        bytes[8 + 8 * i] = 0;
        bytes[9 + 8 * i] = 0;
        bytes[10 + 8 * i] = 0;
        bytes[11 + 8 * i] = 0;
        bytes[12 + 8 * i] = 0;
        bytes[13 + 8 * i] = 0;
        snprintf(pretty + 19 + i * 8, 9, "\n    [0]");

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 187, 5, "\n[]]");

    sw_verify(lib, value,
              174, bytes,
              191, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_too_little()
{
    uint8_t bytes[167];
    char pretty[238];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 20;
    snprintf(pretty, 14, "[[][#][U][20]");

    ubjs_prmtv_array(&value);
    for (i=0; i<20; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }
        else
        {
            ubjs_prmtv_int64(0, &item);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 233, 5, "\n[]]");

    sw_verify(lib, value,
              167, bytes,
              237, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types()
{
    uint8_t bytes[178];
    char pretty[260];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    unsigned int at = 0;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 22;
    snprintf(pretty, 14, "[[][#][U][22]");

    ubjs_prmtv_array(&value);
    for (i=0; i<22; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(0, &item);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(0, &item);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(0, &item);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }
        else if (i == 3)
        {
            ubjs_prmtv_char('r', &item);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 11, 12, "\n    [C][r]");
        }
        else
        {
            ubjs_prmtv_int64(0, &item);
            bytes[at++] = 76;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }

        ubjs_prmtv_array_add_last(value, item);
    }
    snprintf(pretty + 255, 5, "\n[]]");

    sw_verify(lib, value,
              178, bytes,
              259, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}
