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

Test(writer, object_empty)
{
    uint8_t bytes[] = {123, 125};
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(0, 0);
    ubjs_prmtv_object(lib, &value);

    sw_verify(lib, value,
              2, bytes,
              6, "[{][}]");
    ubjs_prmtv_free(&value);
}

Test(writer, object_uint8)
{
    uint8_t bytes[] = {123, 85, 1, '0', 85, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_uint8(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][0][U][0]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_char)
{
    uint8_t bytes[] = {123, 85, 1, '0', 67, 'r', 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_char(lib, 'r', items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][0][C][r]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_int8)
{
    uint8_t bytes[] = {123, 85, 1, '0', 105, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_int8(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][0][i][0]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_int16)
{
    uint8_t bytes[] = {123, 85, 1, '0', 73, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_int16(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);

    sw_verify(lib, value,
              8, bytes,
              27, "[{]\n    [U][1][0][I][0]\n[}]");

    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_int32)
{
    uint8_t bytes[] = {123, 85, 1, '0', 108, 0, 0, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_int32(lib, 0, items + 0);
    ubjs_prmtv_object(lib, &value);
    writer_mock_dict_will_return(1, items);

    sw_verify(lib, value,
              10, bytes,
              27, "[{]\n    [U][1][0][l][0]\n[}]");

    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_int64)
{
    uint8_t bytes[] = {123, 85, 1, '0', 76, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_int64(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              14, bytes,
              27, "[{]\n    [U][1][0][L][0]\n[}]");

    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_float32)
{
    uint8_t bytes[] = {123, 85, 1, '0', 100, 0, 0, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_float32(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              10, bytes,
              34, "[{]\n    [U][1][0][d][0.000000]\n[}]");

    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_float64)
{
    uint8_t bytes[] = {123, 85, 1, '0', 68, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_float64(lib, 0, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              14, bytes,
              34, "[{]\n    [U][1][0][D][0.000000]\n[}]");

    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_null)
{
    uint8_t bytes[] = {123, 85, 1, '0', 90, 125};
    ubjs_prmtv *items[1] = {ubjs_prmtv_null()};
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][0][Z]\n[}]");

    ubjs_prmtv_free(&value);
}

Test(writer, object_noop)
{
    uint8_t bytes[] = {123, 85, 1, '0', 78, 125};
    ubjs_prmtv *items[1] = {ubjs_prmtv_noop()};
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][0][N]\n[}]");

    ubjs_prmtv_free(&value);
}

Test(writer, object_true)
{
    uint8_t bytes[] = {123, 85, 1, '0', 84, 125};
    ubjs_prmtv *items[1] = {ubjs_prmtv_true()};
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][0][T]\n[}]");

    ubjs_prmtv_free(&value);
}

Test(writer, object_false)
{
    uint8_t bytes[] = {123, 85, 1, '0', 70, 125};
    ubjs_prmtv *items[1] = {ubjs_prmtv_false()};
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              6, bytes,
              24, "[{]\n    [U][1][0][F]\n[}]");

    ubjs_prmtv_free(&value);
}

Test(writer, object_str)
{
    uint8_t bytes[] = {123, 85, 1, '0', 83, 85, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_str(lib, 0, "", items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              8, bytes,
              32, "[{]\n    [U][1][0][S][U][0][]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_hpn)
{
    uint8_t bytes[] = {123, 85, 1, '0', 72, 85, 1, '1', 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_hpn(lib, 1, "1", items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              9, bytes,
              33, "[{]\n    [U][1][0][H][U][1][1]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_array)
{
    uint8_t bytes[] = {123, 85, 1, '0', 91, 93, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_array(lib, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][0][[][]]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_object)
{
    uint8_t bytes[] = {123, 85, 1, '0', 123, 125, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *value;

    ubjs_prmtv_object(lib, items + 0);
    writer_mock_dict_will_return(1, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              7, bytes,
              27, "[{]\n    [U][1][0][{][}]\n[}]");
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, object_count_optimized_uint8)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *items[10];
    ubjs_prmtv *value;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 44);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 85;
    bytes[3] = 10;
    pretty = (char *)malloc(sizeof(char) * 184);
    snprintf(pretty, 14, "[{][#][U][10]");

    for (i=0; i<10; i++)
    {
        bytes[4 + i * 4] = 85;
        bytes[5 + i * 4] = 1;
        snprintf((char *)bytes + 6 + i * 4, 2, "%01u", i);
        if (i == 0)
        {
            items[i] = ubjs_prmtv_null();
            bytes[7 + i * 4] = 90;
            snprintf(pretty + 13 + i * 17, 18, "\n    [U][1][%01u][Z]", i);
        }
        else
        {
            items[i] = ubjs_prmtv_noop();
            bytes[7 + i * 4] = 78;
            snprintf(pretty + 13 + i * 17, 18, "\n    [U][1][%01u][N]", i);
        }
    }
    writer_mock_dict_will_return(10, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              44, bytes,
              183, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10, items);
}

Test(writer, object_count_optimized_int16)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *items[10000];
    ubjs_prmtv *value;
    char key[5];

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 70005);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 73;
    bytes[3] = 16;
    bytes[4] = 39;
    pretty = (char *)malloc(sizeof(char) * 200017);
    snprintf(pretty, 17, "[{][#][I][10000]");

    for (i=0; i<10000; i++)
    {
        snprintf(key, 5, "%04u", i);
        bytes[5 + i * 7] = 85;
        bytes[6 + i * 7] = 4;
        snprintf((char *)bytes + 7 + i * 7, 5, "%04u", i);

        if (i == 0)
        {
            items[i] = ubjs_prmtv_null();
            bytes[11 + i * 7] = 90;
            snprintf(pretty + 16 + i * 20, 21, "\n    [U][4][%04u][Z]", i);
        }
        else
        {
            items[i] = ubjs_prmtv_noop();
            bytes[11 + i * 7] = 78;
            snprintf(pretty + 16 + i * 20, 21, "\n    [U][4][%04u][N]", i);
        }
    }
    writer_mock_dict_will_return(10000, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              70005, bytes,
              200016, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(10000, items);
}

Test(writer, object_count_optimized_int32)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_prmtv *items[100000];
    ubjs_prmtv *value;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 800007);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 108;
    bytes[3] = 160;
    bytes[4] = 134;
    bytes[5] = 1;
    bytes[6] = 0;
    pretty = (char *)malloc(sizeof(char) * 2100018);
    snprintf(pretty, 18, "[{][#][l][100000]");

    for (i=0; i<100000; i++)
    {
        bytes[7 + i * 8] = 85;
        bytes[8 + i * 8] = 5;
        snprintf((char *)bytes + 9 + i * 8, 6, "%05u", i);
        if (i == 0)
        {
            items[i] = ubjs_prmtv_null();
            bytes[14 + i * 8] = 90;
            snprintf(pretty + 17 + i * 21, 22, "\n    [U][5][%05u][Z]", i);
        }
        else
        {
            items[i] = ubjs_prmtv_noop();
            bytes[14 + i * 8] = 78;
            snprintf(pretty + 17 + i * 21, 22, "\n    [U][5][%05u][N]", i);
        }
    }
    writer_mock_dict_will_return(100000, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              800007, bytes,
              2100017, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(100000, items);
}
