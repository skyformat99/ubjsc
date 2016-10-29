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

void test_writer_array_type_optimized_null()
{
    uint8_t bytes[6];
    char pretty[22];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 90;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 22, "[[][$][Z][#][U][3][]]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(value, ubjs_prmtv_null());
    }

    sw_verify(lib, value,
              6, bytes,
              21, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_noop()
{
    uint8_t bytes[6];
    char pretty[22];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 78;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 22, "[[][$][N][#][U][3][]]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(value, ubjs_prmtv_noop());
    }

    sw_verify(lib, value,
              6, bytes,
              21, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_true()
{
    uint8_t bytes[6];
    char pretty[22];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 84;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 22, "[[][$][T][#][U][3][]]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(value, ubjs_prmtv_true());
    }

    sw_verify(lib, value,
              6, bytes,
              21, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_false()
{
    uint8_t bytes[6];
    char pretty[22];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 70;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 22, "[[][$][F][#][U][3][]]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(value, ubjs_prmtv_false());
    }

    sw_verify(lib, value,
              6, bytes,
              21, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_uint8()
{
    uint8_t bytes[9];
    char pretty[47];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 85;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][U][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_uint8(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              9, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_char()
{
    uint8_t bytes[9];
    char pretty[47];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 67;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][C][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_char('r', &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i] = 'r';
        snprintf(pretty + 18 + i * 8, 9, "\n    [r]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              9, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_int8()
{
    uint8_t bytes[9];
    char pretty[47];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 105;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][i][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int8(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              9, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_int16()
{
    uint8_t bytes[12];
    char pretty[47];
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
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][I][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int16(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 2] = 0;
        bytes[7 + i * 2] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              12, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_int32()
{
    uint8_t bytes[18];
    char pretty[47];
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
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][l][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int32(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 4] = 0;
        bytes[7 + i * 4] = 0;
        bytes[8 + i * 4] = 0;
        bytes[9 + i * 4] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              18, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_int64()
{
    uint8_t bytes[30];
    char pretty[47];
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
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][L][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int64(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 8] = 0;
        bytes[7 + i * 8] = 0;
        bytes[8 + i * 8] = 0;
        bytes[9 + i * 8] = 0;
        bytes[10 + i * 8] = 0;
        bytes[11 + i * 8] = 0;
        bytes[12 + i * 8] = 0;
        bytes[13 + i * 8] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              30, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_float32()
{
    uint8_t bytes[18];
    char pretty[68];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 100;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][d][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_float32(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 4] = 0;
        bytes[7 + i * 4] = 0;
        bytes[8 + i * 4] = 0;
        bytes[9 + i * 4] = 0;
        snprintf(pretty + 18 + i * 15, 16, "\n    [0.000000]");
    }
    snprintf(pretty + 63, 5, "\n[]]");

    sw_verify(lib, value,
              18, bytes,
              67, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_float64()
{
    uint8_t bytes[30];
    char pretty[68];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 68;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][D][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_float64(0, &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 8] = 0;
        bytes[7 + i * 8] = 0;
        bytes[8 + i * 8] = 0;
        bytes[9 + i * 8] = 0;
        bytes[10 + i * 8] = 0;
        bytes[11 + i * 8] = 0;
        bytes[12 + i * 8] = 0;
        bytes[13 + i * 8] = 0;
        snprintf(pretty + 18 + i * 15, 16, "\n    [0.000000]");
    }
    snprintf(pretty + 63, 5, "\n[]]");

    sw_verify(lib, value,
              30, bytes,
              67, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_str()
{
    uint8_t bytes[12];
    char pretty[62];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 83;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][S][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_str(lib, 0, "", &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 2] = 85;
        bytes[7 + i * 2] = 0;
        snprintf(pretty + 18 + i * 13, 14, "\n    [U][0][]");
    }
    snprintf(pretty + 57, 5, "\n[]]");

    sw_verify(lib, value,
              12, bytes,
              61, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_hpn()
{
    uint8_t bytes[15];
    char pretty[65];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);
    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 72;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][H][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_hpn(lib, 1, "0", &item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i * 3] = 85;
        bytes[7 + i * 3] = 1;
        bytes[8 + i * 3] = '0';
        snprintf(pretty + 18 + i * 14, 15, "\n    [U][1][0]");
    }
    snprintf(pretty + 60, 5, "\n[]]");

    sw_verify(lib, value,
              15, bytes,
              64, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_array()
{
    uint8_t bytes[9];
    char pretty[47];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 91;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][[][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array(&item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i] = 93;
        snprintf(pretty + 18 + i * 8, 9, "\n    []]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              9, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_array_type_optimized_object()
{
    uint8_t bytes[9];
    char pretty[47];
    unsigned int i;
    ubjs_library *lib;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 123;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][{][#][U][3]");

    ubjs_prmtv_array(&value);
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_object(&item);
        ubjs_prmtv_array_add_last(value, item);

        bytes[6 + i] = 125;
        snprintf(pretty + 18 + i * 8, 9, "\n    [}]");
    }
    snprintf(pretty + 42, 5, "\n[]]");

    sw_verify(lib, value,
              9, bytes,
              46, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}
