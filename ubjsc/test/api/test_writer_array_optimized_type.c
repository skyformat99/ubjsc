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

Test(writer, array_type_optimized_array)
{
    uint8_t bytes[9];
    char pretty[43];
    unsigned int i;
    ubjs_prmtv *value;
    ubjs_prmtv *items[3];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 91;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][[][#][U][3]");

    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array((ubjs_library *)instance_lib, items + i);
        bytes[6 + i] = 93;
        snprintf(pretty + 18 + i * 8, 9, "\n    []]");
    }
    writer_mock_array_will_return(3, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              9, bytes,
              42, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(3, items);
}

Test(writer, array_type_optimized_object, .disabled = 1)
{
    uint8_t bytes[9];
    char pretty[43];
    unsigned int i;
    ubjs_prmtv *value;
    ubjs_prmtv *items[3];

    bytes[0] = 91;
    bytes[1] = 36;
    bytes[2] = 123;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[[][$][{][#][U][3]");

    for (i=0; i<3; i++)
    {
        ubjs_prmtv_object((ubjs_library *)instance_lib, items + i);
        bytes[6 + i] = 125;
        snprintf(pretty + 18 + i * 8, 9, "\n    [}]");
    }
    writer_mock_array_will_return(3, items);

    ubjs_prmtv_array((ubjs_library *)instance_lib, &value);
    sw_verify((ubjs_library *)instance_lib, value,
              9, bytes,
              42, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(3, items);
}
