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

void test_writer_object_type_optimized_null()
{
    uint8_t bytes[15];
    char pretty[65];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 90;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][Z][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 3] = 85;
        bytes[7 + i * 3] = 1;
        snprintf(bytes + 8 + i * 3, 2, "%01u", i);
        ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_null());
        snprintf(pretty + 18 + i * 14, 15, "\n    [U][1][%01u]", i);
    }
    snprintf(pretty + 60, 5, "\n[}]");

    sw_verify(lib, value,
              15, bytes,
              64, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_noop()
{
    uint8_t bytes[15];
    char pretty[65];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 78;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][N][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 3] = 85;
        bytes[7 + i * 3] = 1;
        snprintf(bytes + 8 + i * 3, 2, "%01u", i);
        ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_noop());
        snprintf(pretty + 18 + i * 14, 15, "\n    [U][1][%01u]", i);
    }
    snprintf(pretty + 60, 5, "\n[}]");

    sw_verify(lib, value,
              15, bytes,
              64, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_true()
{
    uint8_t bytes[15];
    char pretty[65];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 84;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][T][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 3] = 85;
        bytes[7 + i * 3] = 1;
        snprintf(bytes + 8 + i * 3, 2, "%01u", i);
        ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_true());
        snprintf(pretty + 18 + i * 14, 15, "\n    [U][1][%01u]", i);
    }
    snprintf(pretty + 60, 5, "\n[}]");

    sw_verify(lib, value,
              15, bytes,
              64, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_false()
{
    uint8_t bytes[15];
    char pretty[65];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 70;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][F][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 3] = 85;
        bytes[7 + i * 3] = 1;
        snprintf(bytes + 8 + i * 3, 2, "%01u", i);
        ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_false());
        snprintf(pretty + 18 + i * 14, 15, "\n    [U][1][%01u]", i);
    }
    snprintf(pretty + 60, 5, "\n[}]");

    sw_verify(lib, value,
              15, bytes,
              64, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_uint8()
{
    uint8_t bytes[18];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 85;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][U][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf(bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 0;
        ubjs_prmtv_uint8(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              18, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_char()
{
    uint8_t bytes[18];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 67;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][C][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf(bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 'r';
        ubjs_prmtv_char(lib, 'r', &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][r]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              18, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_int8()
{
    uint8_t bytes[18];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 105;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][i][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf(bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 0;
        ubjs_prmtv_int8(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              18, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_int16()
{
    uint8_t bytes[21];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][I][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 5] = 85;
        bytes[7 + i * 5] = 1;
        snprintf(bytes + 8 + i * 5, 2, "%01u", i);
        bytes[9 + i * 5] = 0;
        bytes[10 + i * 5] = 0;
        ubjs_prmtv_int16(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              21, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_int32()
{
    uint8_t bytes[27];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][l][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 7] = 85;
        bytes[7 + i * 7] = 1;
        snprintf(bytes + 8 + i * 7, 2, "%01u", i);
        bytes[9 + i * 7] = 0;
        bytes[10 + i * 7] = 0;
        bytes[11 + i * 7] = 0;
        bytes[12 + i * 7] = 0;
        ubjs_prmtv_int32(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              27, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_int64()
{
    uint8_t bytes[39];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][L][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 11] = 85;
        bytes[7 + i * 11] = 1;
        snprintf(bytes + 8 + i * 11, 2, "%01u", i);
        bytes[9 + i * 11] = 0;
        bytes[10 + i * 11] = 0;
        bytes[11 + i * 11] = 0;
        bytes[12 + i * 11] = 0;
        bytes[13 + i * 11] = 0;
        bytes[14 + i * 11]= 0;
        bytes[15 + i * 11] = 0;
        bytes[16 + i * 11] = 0;
        ubjs_prmtv_int64(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][0]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              39, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_float32()
{
    uint8_t bytes[27];
    char pretty[95];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 100;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][d][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 7] = 85;
        bytes[7 + i * 7] = 1;
        snprintf(bytes + 8 + i * 7, 2, "%01u", i);
        bytes[9 + i * 7] = 0;
        bytes[10 + i * 7] = 0;
        bytes[11 + i * 7] = 0;
        bytes[12 + i * 7] = 0;
        ubjs_prmtv_float32(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 24, 25, "\n    [U][1][%01u][0.000000]", i);
    }
    snprintf(pretty + 90, 5, "\n[}]");

    sw_verify(lib, value,
              27, bytes,
              94, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_float64()
{
    uint8_t bytes[39];
    char pretty[95];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 68;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][D][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 11] = 85;
        bytes[7 + i * 11] = 1;
        snprintf(bytes + 8 + i * 11, 2, "%01u", i);
        bytes[9 + i * 11] = 0;
        bytes[10 + i * 11] = 0;
        bytes[11 + i * 11] = 0;
        bytes[12 + i * 11] = 0;
        bytes[13 + i * 11] = 0;
        bytes[14 + i * 11]= 0;
        bytes[15 + i * 11] = 0;
        bytes[16 + i * 11] = 0;
        ubjs_prmtv_float64(lib, 0, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 24, 25, "\n    [U][1][%01u][0.000000]", i);
    }
    snprintf(pretty + 90, 5, "\n[}]");

    sw_verify(lib, value,
              39, bytes,
              94, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_str()
{
    uint8_t bytes[21];
    char pretty[89];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 83;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][S][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 5] = 85;
        bytes[7 + i * 5] = 1;
        snprintf(bytes + 8 + i * 5, 2, "%01u", i);
        bytes[9 + i * 5] = 85;
        bytes[10 + i * 5] = 0;
        ubjs_prmtv_str(lib, 0, "", &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 22, 23, "\n    [U][1][%01u][U][0][]", i);
    }
    snprintf(pretty + 84, 5, "\n[}]");

    sw_verify(lib, value,
              21, bytes,
              88, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_hpn()
{
    uint8_t bytes[24];
    char pretty[92];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 72;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][H][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 6] = 85;
        bytes[7 + i * 6] = 1;
        snprintf(bytes + 8 + i * 6, 2, "%01u", i);
        bytes[9 + i * 6] = 85;
        bytes[10 + i * 6] = 1;
        bytes[11 + i * 6] = '0';
        ubjs_prmtv_hpn(lib, 1, "0", &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 23, 24, "\n    [U][1][%01u][U][1][0]", i);
    }
    snprintf(pretty + 87, 5, "\n[}]");

    sw_verify(lib, value,
              24, bytes,
              91, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_array()
{
    uint8_t bytes[18];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 91;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][[][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf(bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 93;
        ubjs_prmtv_array(lib, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][]]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              18, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_type_optimized_object()
{
    uint8_t bytes[18];
    char pretty[74];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 123;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][{][#][U][3]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf(bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 125;
        ubjs_prmtv_object(lib, &item);
        ubjs_prmtv_object_set(value, 1, key, item);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][}]", i);
    }
    snprintf(pretty + 69, 5, "\n[}]");

    sw_verify(lib, value,
              18, bytes,
              73, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}
