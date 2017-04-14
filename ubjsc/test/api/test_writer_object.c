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
