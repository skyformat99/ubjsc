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
#include "test_parser.h"
#include "test_parser_tools.h"

void test_parser_security_limit_string_length_optimized_below()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[3];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 83;
    data[1] = 85;
    data[2] = 3;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_string_length_optimized_above()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[3];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 83;
    data[1] = 85;
    data[2] = 4;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL("Reached limit of string length",
            real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_hpn_length_optimized_below()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[3];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 72;
    data[1] = 85;
    data[2] = 3;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_hpn_length_optimized_above()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[3];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 72;
    data[1] = 85;
    data[2] = 4;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL("Reached limit of string length",
            real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void __test_parser_str_empty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(obj, &length));
    TASSERT_EQUALI(0, length);
}

void test_parser_str_empty()
{
    uint8_t data[]= {83, 85, 0};
    sp_verify_parsed(3, data, __test_parser_str_empty);
}

void __test_parser_str_nonempty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;
    char text[6];

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(obj, &length));
    TASSERT_EQUALI(5, length);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
    TASSERT_NSTRING_EQUAL("rower", text, 5);
}

void test_parser_str_uint8()
{
    uint8_t data[]= {83, 85, 5, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed(8, data, __test_parser_str_nonempty);
}

void test_parser_str_int8()
{
    uint8_t data[]= {83, 105, 5, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed(8, data, __test_parser_str_nonempty);
}

void test_parser_str_int16()
{
    uint8_t data[]= {83, 73, 5, 0, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed(9, data, __test_parser_str_nonempty);
}

void test_parser_str_int32()
{
    uint8_t data[]= {83, 108, 5, 0, 0, 0, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed(11, data, __test_parser_str_nonempty);
}

void test_parser_str_int8_negative()
{
    uint8_t data[]= {83, 105, 255};
    sp_verify_error(3, data, "Got int8 negative length");
}

void test_parser_str_int32_negative()
{
    uint8_t data[]= {83, 108, 0, 0, 0, 255};
    sp_verify_error(6, data, "Got int32 negative length");
}

void test_parser_str_int16_negative()
{
    uint8_t data[]= {83, 73, 0, 255};
    sp_verify_error(4, data, "Got int16 negative length");
}

void test_parser_str_null()
{
    uint8_t data[]= {83, 90};
    sp_verify_error(2, data, "At 1 [90] unknown marker");
}

void test_parser_str_noop()
{
    uint8_t data[]= {83, 78};
    sp_verify_error(2, data, "At 1 [78] unknown marker");
}

void test_parser_str_true()
{
    uint8_t data[]= {83, 84};
    sp_verify_error(2, data, "At 1 [84] unknown marker");
}

void test_parser_str_false()
{
    uint8_t data[]= {83, 70};
    sp_verify_error(2, data, "At 1 [70] unknown marker");
}

void test_parser_str_char()
{
    uint8_t data[]= {83, 67};
    sp_verify_error(2, data, "At 1 [67] unknown marker");
}

void test_parser_str_str()
{
    uint8_t data[]= {83, 83};
    sp_verify_error(2, data, "At 1 [83] unknown marker");
}

void test_parser_str_int64()
{
    uint8_t data[]= {83, 76};
    sp_verify_error(2, data, "At 1 [76] unknown marker");
}

void test_parser_str_float32()
{
    uint8_t data[]= {83, 100};
    sp_verify_error(2, data, "At 1 [100] unknown marker");
}

void test_parser_str_float64()
{
    uint8_t data[]= {83, 68};
    sp_verify_error(2, data, "At 1 [68] unknown marker");
}

void test_parser_str_array()
{
    uint8_t data[]= {83, 91};
    sp_verify_error(2, data, "At 1 [91] unknown marker");
}

void test_parser_str_object()
{
    uint8_t data[]= {83, 123};
    sp_verify_error(2, data, "At 1 [123] unknown marker");
}

void test_parser_str_hpn()
{
    uint8_t data[]= {83, 72};
    sp_verify_error(2, data, "At 1 [72] unknown marker");
}

void test_parser_hpn_empty()
{
    uint8_t data[]= {72, 85, 0};
    sp_verify_error(3, data, "Syntax error for high-precision number.");
}

void __test_parser_hpn_nonempty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;
    char text[6];

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_get_length(obj, &length));
    TASSERT_EQUALI(5, length);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_copy_text(obj, text));
    TASSERT_NSTRING_EQUAL("12345", text, 5);
}

void test_parser_hpn_uint8()
{
    uint8_t data[]= {72, 85, 5, '1', '2', '3', '4', '5'};
    sp_verify_parsed(8, data, __test_parser_hpn_nonempty);
}

void test_parser_hpn_int8()
{
    uint8_t data[]= {72, 105, 5, '1', '2', '3', '4', '5'};
    sp_verify_parsed(8, data, __test_parser_hpn_nonempty);
}

void test_parser_hpn_int16()
{
    uint8_t data[]= {72, 73, 5, 0, '1', '2', '3', '4', '5'};
    sp_verify_parsed(9, data, __test_parser_hpn_nonempty);
}

void test_parser_hpn_int32()
{
    uint8_t data[]= {72, 108, 5, 0, 0, 0, '1', '2', '3', '4', '5'};
    sp_verify_parsed(11, data, __test_parser_hpn_nonempty);
}

void test_parser_hpn_int8_negative()
{
    uint8_t data[]= {72, 105, 255};
    sp_verify_error(3, data, "Got int8 negative length");
}

void test_parser_hpn_int32_negative()
{
    uint8_t data[]= {72, 108, 0, 0, 0, 255};
    sp_verify_error(6, data, "Got int32 negative length");
}

void test_parser_hpn_int16_negative()
{
    uint8_t data[]= {72, 73, 0, 255};
    sp_verify_error(4, data, "Got int16 negative length");
}

void test_parser_hpn_null()
{
    uint8_t data[]= {72, 90};
    sp_verify_error(2, data, "At 1 [90] unknown marker");
}

void test_parser_hpn_noop()
{
    uint8_t data[]= {72, 78};
    sp_verify_error(2, data, "At 1 [78] unknown marker");
}

void test_parser_hpn_true()
{
    uint8_t data[]= {72, 84};
    sp_verify_error(2, data, "At 1 [84] unknown marker");
}

void test_parser_hpn_false()
{
    uint8_t data[]= {72, 70};
    sp_verify_error(2, data, "At 1 [70] unknown marker");
}

void test_parser_hpn_char()
{
    uint8_t data[]= {72, 67};
    sp_verify_error(2, data, "At 1 [67] unknown marker");
}

void test_parser_hpn_str()
{
    uint8_t data[]= {72, 83};
    sp_verify_error(2, data, "At 1 [83] unknown marker");
}

void test_parser_hpn_int64()
{
    uint8_t data[]= {72, 76};
    sp_verify_error(2, data, "At 1 [76] unknown marker");
}

void test_parser_hpn_float32()
{
    uint8_t data[]= {72, 100};
    sp_verify_error(2, data, "At 1 [100] unknown marker");
}

void test_parser_hpn_float64()
{
    uint8_t data[]= {72, 68};
    sp_verify_error(2, data, "At 1 [68] unknown marker");
}

void test_parser_hpn_array()
{
    uint8_t data[]= {72, 91};
    sp_verify_error(2, data, "At 1 [91] unknown marker");
}

void test_parser_hpn_object()
{
    uint8_t data[]= {72, 123};
    sp_verify_error(2, data, "At 1 [123] unknown marker");
}

void test_parser_hpn_hpn()
{
    uint8_t data[]= {72, 72};
    sp_verify_error(2, data, "At 1 [72] unknown marker");
}
