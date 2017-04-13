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
#include "test_parser.h"
#include "test_parser_tools.h"

Test(parser, object_optimized_type_unknown_marker)
{
    uint8_t data[] = {123, 36, 0};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [0] unknown marker");
}

void __test_parser_object_optimized_type(ubjs_prmtv *obj)
{
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    cr_expect_eq(UTRUE, ret);
}

Test(parser, object_optimized_type_char_empty)
{
    uint8_t data[]= {123, 36, 67, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_int32_empty)
{
    uint8_t data[]= {123, 36, 108, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_int64_empty)
{
    uint8_t data[]= {123, 36, 76, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_float32_empty)
{
    uint8_t data[]= {123, 36, 100, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_float64_empty)
{
    uint8_t data[]= {123, 36, 68, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_str_empty)
{
    uint8_t data[]= {123, 36, 83, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_hpn_empty)
{
    uint8_t data[]= {123, 36, 72, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_array_empty)
{
    uint8_t data[]= {123, 36, 91, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_object_empty)
{
    uint8_t data[]= {123, 36, 123, 35, 85, 0};
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object_optimized_type);
}

Test(parser, object_optimized_type_char_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 67;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = '0';
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 1536, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_int32_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2301);
    data[0] = 123;
    data[1] = 36;
    data[2] = 108;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 9] = 85;
        data[7 + i * 9] = 3;
        strncpy((char *) data + 8 + i * 9, key, 3);
        data[11 + i * 9] = 0;
        data[12 + i * 9] = 129;
        data[13 + i * 9] = 0;
        data[14 + i * 9] = 129;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 2301, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_int64_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 3321);
    data[0] = 123;
    data[1] = 36;
    data[2] = 76;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 13] = 85;
        data[7 + i * 13] = 3;
        strncpy((char *) data + 8 + i * 13, key, 3);
        data[11 + i * 13] = 1;
        data[12 + i * 13] = 2;
        data[13 + i * 13] = 3;
        data[14 + i * 13] = 4;
        data[15 + i * 13] = 5;
        data[16 + i * 13] = 6;
        data[17 + i * 13] = 7;
        data[18 + i * 13] = 8;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 3321, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_float32_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2301);
    data[0] = 123;
    data[1] = 36;
    data[2] = 100;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 9] = 85;
        data[7 + i * 9] = 3;
        strncpy((char *) data + 8 + i * 9, key, 3);
        data[11 + i * 9] = 0;
        data[12 + i * 9] = 129;
        data[13 + i * 9] = 0;
        data[14 + i * 9] = 129;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 2301, data,
        __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_float64_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 3321);
    data[0] = 123;
    data[1] = 36;
    data[2] = 68;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 13] = 85;
        data[7 + i * 13] = 3;
        strncpy((char *) data + 8 + i * 13, key, 3);
        data[11 + i * 13] = 1;
        data[12 + i * 13] = 2;
        data[13 + i * 13] = 3;
        data[14 + i * 13] = 4;
        data[15 + i * 13] = 5;
        data[16 + i * 13] = 6;
        data[17 + i * 13] = 7;
        data[18 + i * 13] = 8;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 3321, data,
        __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_str_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1791);
    data[0] = 123;
    data[1] = 36;
    data[2] = 83;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 7] = 85;
        data[7 + i * 7] = 3;
        strncpy((char *) data + 8 + i * 7, key, 3);
        data[11 + i * 7] = 85;
        data[12 + i * 7] = 0;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 1791, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_hpn_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2046);
    data[0] = 123;
    data[1] = 36;
    data[2] = 72;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 8] = 85;
        data[7 + i * 8] = 3;
        strncpy((char *) data + 8 + i * 8, key, 3);
        data[11 + i * 8] = 85;
        data[12 + i * 8] = 1;
        data[13 + i * 8] = '1';
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 2046, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_array_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 91;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 93;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 1536, data, __test_parser_object_optimized_type);
    free(data);
}

Test(parser, object_optimized_type_object_lots)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 123;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 125;
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 1536, data,
        __test_parser_object_optimized_type);
    free(data);
}
