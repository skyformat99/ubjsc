/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
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

Test(writer, array_empty)
{
    uint8_t bytes[]={91, 93};
    char *pretty="[[][]]";
    ubjs_prmtv *value;

    writer_mock_array_will_return(0, 0);
    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, array_uint8)
{
    uint8_t bytes[]={91, 85, 0, 93};
    char *pretty="[[]\n    [U][0]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_uint8((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              4, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_char)
{
    uint8_t bytes[]={91, 67, 'r', 93};
    char *pretty="[[]\n    [C][r]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_char((ubjs_library *)instance_lib, 'r', items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              4, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_int8)
{
    uint8_t bytes[]={91, 105, 0, 93};
    char *pretty="[[]\n    [i][0]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_int8((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              4, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_int16)
{
    uint8_t bytes[]={91, 73, 0, 0, 93};
    char *pretty="[[]\n    [I][0]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_int16((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              5, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_int32)
{
    uint8_t bytes[]={91, 108, 0, 0, 0, 0, 93};
    char *pretty="[[]\n    [l][0]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_int32((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              7, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_int64)
{
    uint8_t bytes[]={91, 76, 0, 0, 0, 0, 0, 0, 0, 0, 93};
    char *pretty="[[]\n    [L][0]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_int64((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              11, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_float32)
{
    uint8_t bytes[]={91, 100, 0, 0, 0, 0, 93};
    char *pretty="[[]\n    [d][0.000000]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_float32((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              7, bytes,
              25, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_float64)
{
    uint8_t bytes[]={91, 68, 0, 0, 0, 0, 0, 0, 0, 0, 93};
    char *pretty="[[]\n    [D][0.000000]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_float64((ubjs_library *)instance_lib, 0, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              11, bytes,
              25, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_true)
{
    uint8_t bytes[]={91, 84, 93};
    char *pretty="[[]\n    [T]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    items[0] = ubjs_prmtv_true();
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              3, bytes,
              15, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, array_false)
{
    uint8_t bytes[]={91, 70, 93};
    char *pretty="[[]\n    [F]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    items[0] = ubjs_prmtv_false();
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              3, bytes,
              15, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, array_str)
{
    uint8_t bytes[]={91, 83, 85, 5, 'r', 'o', 'w', 'e', 'r', 93};
    char *pretty="[[]\n    [S][U][5][rower]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_str((ubjs_library *)instance_lib, 5, "rower", items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              10, bytes,
              28, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_hpn)
{
    uint8_t bytes[]={91, 72, 85, 5, '1', '2', '3', '4', '5', 93};
    char *pretty="[[]\n    [H][U][5][12345]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_hpn((ubjs_library *)instance_lib, 5, "12345", items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              10, bytes,
              28, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_array)
{
    uint8_t bytes[]={91, 91, 93, 93};
    char *pretty="[[]\n    [[][]]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_array((ubjs_library *)instance_lib, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              4, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

Test(writer, array_object)
{
    uint8_t bytes[]={91, 123, 125, 93};
    char *pretty="[[]\n    [{][}]\n[]]";
    ubjs_prmtv *value;
    ubjs_prmtv *items[1];

    ubjs_prmtv_object((ubjs_library *)instance_lib, items + 0);
    writer_mock_array_will_return(1, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              4, bytes,
              18, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(1, items);
}

