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
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;

    writer_mock_dict_will_return(0, 0);
    ubjs_prmtv_object(lib, &value);

    sw_verify(lib, value,
              2, bytes,
              6, "[{][}]");
    ubjs_prmtv_free(&value);
}

Test(writer, object_char)
{
    uint8_t bytes[] = {123, 85, 1, '0', 67, 'r', 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)instance_lib;
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

Test(writer, object_int32)
{
    uint8_t bytes[] = {123, 85, 1, '0', 108, 0, 0, 0, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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

Test(writer, object_str)
{
    uint8_t bytes[] = {123, 85, 1, '0', 83, 85, 0, 125};
    ubjs_prmtv *items[1];
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    ubjs_library *lib = (ubjs_library *)instance_lib;
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

Test(writer, object_count_optimized_int32)
{
    uint8_t *bytes;
    char *pretty;
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *items[100000];
    ubjs_prmtv *value;
    unsigned int ip;
    unsigned int iw;

    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 900008);
    bytes[0] = 123;
    bytes[1] = 35;
    bytes[2] = 108;
    bytes[3] = 160;
    bytes[4] = 134;
    bytes[5] = 1;
    bytes[6] = 0;
    pretty = (char *)malloc(sizeof(char) * 3000018);
    snprintf(pretty, 18, "[{][#][l][100000]");

    for (i=0, iw = 7, ip = 17; i<100000; i++)
    {
        bytes[iw++] = 85;
        bytes[iw++] = 5;
        iw += snprintf((char *)bytes + iw, 6, "%05u", i);
        ip += snprintf(pretty + ip, 19, "\n    [U][5][%05u]", i);

        if (i == 0)
        {
            mock_prmtv(lib, &mock_prmtv_ntype1, &(items[i]));
            bytes[iw++] = 32;
            bytes[iw++] = 'r';
            ip += snprintf(pretty + ip, 13, "[ ][<rower>]");
        }
        else
        {
            mock_prmtv(lib, &mock_prmtv_ntype2, &(items[i]));
            bytes[iw++] = 33;
            bytes[iw++] = 'r';
            ip += snprintf(pretty + ip, 13, "[!][<rower>]");
        }
    }
    writer_mock_dict_will_return(100000, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              900007, bytes,
              3000017, pretty);
    ubjs_prmtv_free(&value);
    free(pretty);
    free(bytes);
    writer_mock_free(100000, items);
}
