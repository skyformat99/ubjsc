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

void test_writer_object_empty()
{
    uint8_t bytes[] = {123, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              2, bytes,
              6, "[{][}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_uint8()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 85, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_uint8(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][a][U][0]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_char()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 67, 'r', 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_char(lib, 'r', &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][a][C][r]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_int8()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 105, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int8(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][a][i][0]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_int16()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 73, 0, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int16(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              8, bytes,
              27, "[{]\n    [U][1][a][I][0]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_int32()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 108, 0, 0, 0, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int32(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              10, bytes,
              27, "[{]\n    [U][1][a][l][0]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_int64()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 76, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int64(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              14, bytes,
              27, "[{]\n    [U][1][a][L][0]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_float32()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 100, 0, 0, 0, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_float32(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              10, bytes,
              34, "[{]\n    [U][1][a][d][0.000000]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_float64()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 68, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_float64(lib, 0, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              14, bytes,
              34, "[{]\n    [U][1][a][D][0.000000]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_null()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 90, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", ubjs_prmtv_null());
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][a][Z]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_noop()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 78, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", ubjs_prmtv_noop());
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][a][N]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_true()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 84, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", ubjs_prmtv_true());
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][a][T]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_false()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 70, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", ubjs_prmtv_false());
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][a][F]\n[}]");

    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_str()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 83, 85, 0, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_str(lib, 0, "", &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              8, bytes,
              32, "[{]\n    [U][1][a][S][U][0][]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_hpn()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 72, 85, 1, '1', 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_hpn(lib, 1, "1", &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              9, bytes,
              33, "[{]\n    [U][1][a][H][U][1][1]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_array()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 91, 93, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_array(lib, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][a][[][]]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_object()
{
    uint8_t bytes[] = {123, 85, 1, 'a', 123, 125, 125};
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    ubjs_prmtv *item;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_object(lib, &item);
    ubjs_prmtv_object(lib, &value);
    ubjs_prmtv_object_set(value, 1, "a", item);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][a][{][}]\n[}]");
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_count_optimized_uint8()
{
    uint8_t bytes[44];
    char pretty[188];
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[2];

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 85;
    bytes[3] = 10;
    snprintf(pretty, 14, "[{][#][U][10]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        bytes[4 + i * 4] = 85;
        bytes[5 + i * 4] = 1;
        snprintf(bytes + 6 + i * 4, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_null());
            bytes[7 + i * 4] = 90;
            snprintf(pretty + 13 + i * 17, 18, "\n    [U][1][%01u][Z]", i);
        }
        else
        {
            ubjs_prmtv_object_set(value, 1, key, ubjs_prmtv_noop());
            bytes[7 + i * 4] = 78;
            snprintf(pretty + 13 + i * 17, 18, "\n    [U][1][%01u][N]", i);
        }
    }
    snprintf(pretty + 183, 5, "\n[}]");

    sw_verify(lib, value,
              44, bytes,
              187, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_object_count_optimized_int16()
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[5];

    ubjs_library_new_stdlib(&lib);
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 70005);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 73;
    bytes[3] = 16;
    bytes[4] = 39;
    pretty = (char *)malloc(sizeof(char) * 200021);
    snprintf(pretty, 17, "[{][#][I][10000]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<10000; i++)
    {
        snprintf(key, 5, "%04u", i);
        bytes[5 + i * 7] = 85;
        bytes[6 + i * 7] = 4;
        snprintf(bytes + 7 + i * 7, 5, "%04u", i);
        if (i == 0)
        {
            ubjs_prmtv_object_set(value, 4, key, ubjs_prmtv_null());
            bytes[11 + i * 7] = 90;
            snprintf(pretty + 16 + i * 20, 21, "\n    [U][4][%04u][Z]", i);
        }
        else
        {
            ubjs_prmtv_object_set(value, 4, key, ubjs_prmtv_noop());
            bytes[11 + i * 7] = 78;
            snprintf(pretty + 16 + i * 20, 21, "\n    [U][4][%04u][N]", i);
        }
    }
    snprintf(pretty + 200016, 5, "\n[}]");

    sw_verify(lib, value,
              70005, bytes,
              200020, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
    free(pretty);
    free(bytes);
}

void test_writer_object_count_optimized_int32()
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = 0;
    ubjs_prmtv *value;
    char key[6];

    ubjs_library_new_stdlib(&lib);
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 800007);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 108;
    bytes[3] = 160;
    bytes[4] = 134;
    bytes[5] = 1;
    bytes[6] = 0;
    pretty = (char *)malloc(sizeof(char) * 2100022);
    snprintf(pretty, 18, "[{][#][l][100000]");

    ubjs_prmtv_object(lib, &value);
    for (i=0; i<100000; i++)
    {
        snprintf(key, 6, "%05u", i);
        bytes[7 + i * 8] = 85;
        bytes[8 + i * 8] = 5;
        snprintf(bytes + 9 + i * 8, 6, "%05u", i);
        if (i == 0)
        {
            ubjs_prmtv_object_set(value, 5, key, ubjs_prmtv_null());
            bytes[14 + i * 8] = 90;
            snprintf(pretty + 17 + i * 21, 22, "\n    [U][5][%05u][Z]", i);
        }
        else
        {
            ubjs_prmtv_object_set(value, 5, key, ubjs_prmtv_noop());
            bytes[14 + i * 8] = 78;
            snprintf(pretty + 17 + i * 21, 22, "\n    [U][5][%05u][N]", i);
        }
    }
    snprintf(pretty + 2100017, 5, "\n[}]");

    sw_verify(lib, value,
              800007, bytes,
              2100021, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
    free(pretty);
    free(bytes);
}
