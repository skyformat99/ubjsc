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

#include "test_common.h"
#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

Test(writer, array_upgraded_from_uint8_to_int16, .disabled = 1)
{
    uint8_t bytes[16];
    char pretty[59];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    ubjs_prmtv *upgraded_items[5];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    snprintf(pretty, 19, "[[][$][I][#][U][5]");

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
        bytes[6 + 2 * i] = 0;
        bytes[7 + 2 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    writer_mock_array_will_return2(5, items, upgraded_items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              16, bytes,
              58, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(5, items);
    writer_mock_free(5, upgraded_items);
}

Test(writer, array_upgraded_from_int8_to_int16, .disabled = 1)
{
    uint8_t bytes[16];
    char pretty[59];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    ubjs_prmtv *upgraded_items[5];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 73;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 5;
    snprintf(pretty, 19, "[[][$][I][#][U][5]");

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
        bytes[6 + 2 * i] = 0;
        bytes[7 + 2 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    ubjs_prmtv_array(lib, &value);
    writer_mock_array_will_return2(5, items, upgraded_items);

    sw_verify(lib, value,
              16, bytes,
              58, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(5, items);
    writer_mock_free(5, upgraded_items);
}

Test(writer, array_not_upgraded_from_int8_to_int16_too_little, .disabled = 1)
{
    uint8_t bytes[15];
    ubjs_library *lib = (ubjs_library *)instance_lib;
    char pretty[57];
    unsigned int i;
    ubjs_prmtv *value;
    ubjs_prmtv *items[4];
    unsigned int at = 0;

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 4;
    snprintf(pretty, 13, "[[][#][U][4]");

    for (i=0; i<4; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
    }
    writer_mock_array_will_return(4, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              15, bytes,
              56, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(4, items);
}

Test(writer, array_not_upgraded_from_int8_to_int16_are_int32, .disabled = 1)
{
    uint8_t bytes[20];
    char pretty[68];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    unsigned int at = 0;

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [l][0]");
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
    }
    writer_mock_array_will_return(5, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              20, bytes,
              67, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(5, items);
}

Test(writer, array_not_upgraded_from_int8_to_int16_are_int64, .disabled = 1)
{
    uint8_t bytes[24];
    char pretty[68];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    unsigned int at = 0;

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
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
            snprintf(pretty + 12 + i * 11, 12, "\n    [L][0]");
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
    }
    writer_mock_array_will_return(5, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              24, bytes,
              67, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(5, items);
}

Test(writer, array_not_upgraded_from_int8_to_int16_are_other_types, .disabled = 1)
{
    uint8_t bytes[17];
    char pretty[68];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[5];
    unsigned int at = 0;

    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 5;
    snprintf(pretty, 13, "[[][#][U][5]");

    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 12 + i * 11, 12, "\n    [C][r]");
        }
        else
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
    }
    writer_mock_array_will_return(5, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              17, bytes,
              67, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(5, items);
}

Test(writer, array_upgraded_from_int8_int16_to_int32, .disabled = 1)
{
    uint8_t bytes[42];
    char pretty[91];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[9];
    ubjs_prmtv *upgraded_items[9];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    snprintf(pretty, 19, "[[][$][l][#][U][9]");

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

        bytes[6 + 4 * i] = 0;
        bytes[7 + 4 * i] = 0;
        bytes[8 + 4 * i] = 0;
        bytes[9 + 4 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    writer_mock_array_will_return2(9, items, upgraded_items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              42, bytes,
              90, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(9, items);
    writer_mock_free(9, upgraded_items);
}

Test(writer, array_upgraded_from_uint8_int16_to_int32, .disabled = 1)
{
    uint8_t bytes[42];
    char pretty[91];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[9];
    ubjs_prmtv *upgraded_items[9];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 108;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 9;
    snprintf(pretty, 19, "[[][$][l][#][U][9]");

    for (i=0; i<9; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(lib, 0, items + i);
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
        bytes[6 + 4 * i] = 0;
        bytes[7 + 4 * i] = 0;
        bytes[8 + 4 * i] = 0;
        bytes[9 + 4 * i] = 0;
        snprintf(pretty + 18 + i * 8, 9, "\n    [0]");
    }
    writer_mock_array_will_return2(9, items, upgraded_items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              42, bytes,
              90, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(9, items);
    writer_mock_free(9, upgraded_items);
}

Test(writer, array_not_upgraded_from_int8_int16_to_int32_too_little, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[8];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 39);
    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 8;
    pretty = (char *)malloc(sizeof(char) * 101);
    snprintf(pretty, 13, "[[][#][U][8]");

    for (i=0; i<8; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [I][0]");
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 12 + i * 11, 12, "\n    [l][0]");
        }
    }
    writer_mock_array_will_return(8, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              39, bytes,
              100, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(8, items);
}

Test(writer, array_not_upgraded_from_int8_int16_to_int32_are_int64, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[10];
    unsigned int at = 0;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 53);
    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    pretty = (char *)malloc(sizeof(char) * 124);
    snprintf(pretty, 14, "[[][#][U][10]");

    for (i=0; i<10; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
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
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }
    }
    writer_mock_array_will_return(10, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              53, bytes,
              123, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10, items);
}

Test(writer, array_not_upgraded_from_int8_int16_to_int32_are_other_types, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[10];
    unsigned int at = 0;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 46);
    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 10;
    pretty = (char *)malloc(sizeof(char) * 128);
    snprintf(pretty, 14, "[[][#][U][10]");

    for (i=0; i<10; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 11, 12, "\n    [C][r]");
        }
        else
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }
    }
    writer_mock_array_will_return(10, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              46, bytes,
              123, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10, items);
}

Test(writer, array_upgraded_from_uint8_int16_int32_to_int64, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[21];
    ubjs_prmtv *upgraded_items[21];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 174);
    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    pretty = (char *)malloc(sizeof(char) * 188);
    snprintf(pretty, 20, "[[][$][L][#][U][21]");

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

        bytes[6 + 8 * i] = 0;
        bytes[7 + 8 * i] = 0;
        bytes[8 + 8 * i] = 0;
        bytes[9 + 8 * i] = 0;
        bytes[10 + 8 * i] = 0;
        bytes[11 + 8 * i] = 0;
        bytes[12 + 8 * i] = 0;
        bytes[13 + 8 * i] = 0;
        snprintf(pretty + 19 + i * 8, 9, "\n    [0]");
    }
    writer_mock_array_will_return2(21, items, upgraded_items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              174, bytes,
              187, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(21, items);
    writer_mock_free(21, upgraded_items);
}

Test(writer, array_upgraded_from_int8_int16_int32_to_int64, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[21];
    ubjs_prmtv *upgraded_items[21];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 174);
    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 76;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 21;
    pretty = (char *)malloc(sizeof(char) * 188);
    snprintf(pretty, 20, "[[][$][L][#][U][21]");

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

        bytes[6 + 8 * i] = 0;
        bytes[7 + 8 * i] = 0;
        bytes[8 + 8 * i] = 0;
        bytes[9 + 8 * i] = 0;
        bytes[10 + 8 * i] = 0;
        bytes[11 + 8 * i] = 0;
        bytes[12 + 8 * i] = 0;
        bytes[13 + 8 * i] = 0;
        snprintf(pretty + 19 + i * 8, 9, "\n    [0]");
    }
    writer_mock_array_will_return2(21, items, upgraded_items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              174, bytes,
              187, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(21, items);
    writer_mock_free(21, upgraded_items);
}

Test(writer, array_not_upgraded_from_int8_int16_int32_to_int64_too_little, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[20];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 167);
    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 20;
    pretty = (char *)malloc(sizeof(char) * 234);
    snprintf(pretty, 14, "[[][#][U][20]");

    for (i=0; i<20; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
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
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }
    }
    writer_mock_array_will_return(20, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              167, bytes,
              233, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(20, items);
}

Test(writer, array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types, .disabled = 1)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[22];
    unsigned int at = 0;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 178);
    bytes[at++] = 91;
    bytes[at++] = 35;
    bytes[at++] = 85;
    bytes[at++] = 22;
    pretty = (char *)malloc(sizeof(char) * 256);
    snprintf(pretty, 14, "[[][#][U][22]");

    for (i=0; i<22; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(lib, 0, items + i);
            bytes[at++] = 105;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [i][0]");
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(lib, 0, items + i);
            bytes[at++] = 73;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [I][0]");
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(lib, 0, items + i);
            bytes[at++] = 108;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            bytes[at++] = 0;
            snprintf(pretty + 13 + i * 11, 12, "\n    [l][0]");
        }
        else if (i == 3)
        {
            ubjs_prmtv_char(lib, 'r', items + i);
            bytes[at++] = 67;
            bytes[at++] = 'r';
            snprintf(pretty + 13 + i * 11, 12, "\n    [C][r]");
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
            snprintf(pretty + 13 + i * 11, 12, "\n    [L][0]");
        }
    }
    writer_mock_array_will_return(22, items);

    ubjs_prmtv_array(lib, &value);
    sw_verify(lib, value,
              178, bytes,
              255, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(22, items);
}
