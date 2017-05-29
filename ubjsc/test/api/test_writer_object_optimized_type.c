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

Test(writer, object_type_optimized_object)
{
    uint8_t bytes[18];
    char pretty[70];
    unsigned int i;
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_prmtv *value;
    ubjs_prmtv *items[3];

    bytes[0] = 123;
    bytes[1] = 36;
    bytes[2] = 123;
    bytes[3] = 35;
    bytes[4] = 85;
    bytes[5] = 3;
    snprintf(pretty, 19, "[{][$][{][#][U][3]");

    for (i=0; i<3; i++)
    {
        bytes[6 + i * 4] = 85;
        bytes[7 + i * 4] = 1;
        snprintf((char *)bytes + 8 + i * 4, 2, "%01u", i);
        bytes[9 + i * 4] = 125;
        ubjs_prmtv_object(lib, items + i);
        snprintf(pretty + 18 + i * 17, 18, "\n    [U][1][%01u][}]", i);
    }
    writer_mock_dict_will_return(3, items);

    ubjs_prmtv_object(lib, &value);
    sw_verify(lib, value,
              18, bytes,
              69, pretty);
    ubjs_prmtv_free(&value);
    writer_mock_free(3, items);
}
