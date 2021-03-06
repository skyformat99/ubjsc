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
#include "test_parser.h"
#include "test_parser_tools.h"

Test(parser, array_optimized_type_unknown_marker)
{
    uint8_t data[] = {91, 36, 0};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [0] unknown marker");
}

void __test_parser_array_optimized_type(ubjs_prmtv *obj)
{
}

Test(parser, array_optimized_type_array_empty)
{
    uint8_t data[]= {91, 36, 91, 35, 85, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_array_optimized_type);
}

Test(parser, array_optimized_type_object_empty)
{
    uint8_t data[]= {91, 36, 123, 35, 85, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_array_optimized_type);
}

Test(parser, array_optimized_type_array_lots)
{
    uint8_t *data;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 91;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 93;
    }

    twill_returnui("array_builder_set_length", UR_OK);
    for (i = 0; i < LOTS; i++)
    {
        twill_returnui("array_add_last", UR_OK);
    }
    sp_verify_parsed((ubjs_library *)instance_lib, 261, data, __test_parser_array_optimized_type);
    free(data);
}

Test(parser, array_optimized_type_object_lots)
{
    uint8_t *data;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 123;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 125;
    }

    twill_returnui("array_builder_set_length", UR_OK);
    for (i = 0; i < LOTS; i++)
    {
        twill_returnui("array_add_last", UR_OK);
    }
    sp_verify_parsed((ubjs_library *)instance_lib, 261, data, __test_parser_array_optimized_type);
    free(data);
}
