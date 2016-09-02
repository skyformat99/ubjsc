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

void suite_parser(tcontext *context)
{
    tsuite *suite;
    TSUITE("parser", 0, 0, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_parser_bad_init);
    TTEST(suite, test_parser_init_clean);
    TTEST(suite, test_parser_basics);
    TTEST(suite, test_parser_unknown_marker);
    TTEST(suite, test_parser_null);
    TTEST(suite, test_parser_noop);
    TTEST(suite, test_parser_true);
    TTEST(suite, test_parser_false);
    TTEST(suite, test_parser_int8);
    TTEST(suite, test_parser_uint8);
    TTEST(suite, test_parser_int16);
    TTEST(suite, test_parser_int32);
    TTEST(suite, test_parser_int64);
    TTEST(suite, test_parser_float32);
    TTEST(suite, test_parser_float64);
    TTEST(suite, test_parser_char);

    TTEST(suite, test_parser_str_empty);
    TTEST(suite, test_parser_str_null);
    TTEST(suite, test_parser_str_noop);
    TTEST(suite, test_parser_str_true);
    TTEST(suite, test_parser_str_false);
    TTEST(suite, test_parser_str_uint8);
    TTEST(suite, test_parser_str_int8);
    TTEST(suite, test_parser_str_int8_negative);
    TTEST(suite, test_parser_str_int16);
    TTEST(suite, test_parser_str_int16_negative);
    TTEST(suite, test_parser_str_int32);
    TTEST(suite, test_parser_str_int32_negative);
    TTEST(suite, test_parser_str_int64);
    TTEST(suite, test_parser_str_float32);
    TTEST(suite, test_parser_str_float64);
    TTEST(suite, test_parser_str_char);
    TTEST(suite, test_parser_str_str);
    TTEST(suite, test_parser_str_hpn);
    TTEST(suite, test_parser_str_array);
    TTEST(suite, test_parser_str_object);

    TTEST(suite, test_parser_hpn_empty);
    TTEST(suite, test_parser_hpn_null);
    TTEST(suite, test_parser_hpn_noop);
    TTEST(suite, test_parser_hpn_true);
    TTEST(suite, test_parser_hpn_false);
    TTEST(suite, test_parser_hpn_uint8);
    TTEST(suite, test_parser_hpn_int8);
    TTEST(suite, test_parser_hpn_int8_negative);
    TTEST(suite, test_parser_hpn_int16);
    TTEST(suite, test_parser_hpn_int16_negative);
    TTEST(suite, test_parser_hpn_int32);
    TTEST(suite, test_parser_hpn_int32_negative);
    TTEST(suite, test_parser_hpn_int64);
    TTEST(suite, test_parser_hpn_float32);
    TTEST(suite, test_parser_hpn_float64);
    TTEST(suite, test_parser_hpn_char);
    TTEST(suite, test_parser_hpn_str);
    TTEST(suite, test_parser_hpn_hpn);
    TTEST(suite, test_parser_hpn_array);
    TTEST(suite, test_parser_hpn_object);

    TTEST(suite, test_parser_array_empty);
    TTEST(suite, test_parser_array_uint8);
    TTEST(suite, test_parser_array_int8);
    TTEST(suite, test_parser_array_int16);
    TTEST(suite, test_parser_array_int32);
    TTEST(suite, test_parser_array_null);
    TTEST(suite, test_parser_array_noop);
    TTEST(suite, test_parser_array_true);
    TTEST(suite, test_parser_array_false);
    TTEST(suite, test_parser_array_char);
    TTEST(suite, test_parser_array_str);
    TTEST(suite, test_parser_array_hpn);
    TTEST(suite, test_parser_array_int64);
    TTEST(suite, test_parser_array_float32);
    TTEST(suite, test_parser_array_float64);
    TTEST(suite, test_parser_array_array);
    TTEST(suite, test_parser_array_object);
    TTEST(suite, test_parser_array_optimized_count_empty);
    TTEST(suite, test_parser_array_optimized_count_null);
    TTEST(suite, test_parser_array_optimized_count_noop);
    TTEST(suite, test_parser_array_optimized_count_true);
    TTEST(suite, test_parser_array_optimized_count_false);
    TTEST(suite, test_parser_array_optimized_count_uint8);
    TTEST(suite, test_parser_array_optimized_count_char);
    TTEST(suite, test_parser_array_optimized_count_int8);
    TTEST(suite, test_parser_array_optimized_count_int8_negative);
    TTEST(suite, test_parser_array_optimized_count_int16);
    TTEST(suite, test_parser_array_optimized_count_int16_negative);
    TTEST(suite, test_parser_array_optimized_count_int32);
    TTEST(suite, test_parser_array_optimized_count_int32_negative);
    TTEST(suite, test_parser_array_optimized_count_int64);
    TTEST(suite, test_parser_array_optimized_count_str);
    TTEST(suite, test_parser_array_optimized_count_hpn);
    TTEST(suite, test_parser_array_optimized_count_array);
    TTEST(suite, test_parser_array_optimized_count_object);
    TTEST(suite, test_parser_array_optimized_type_null_empty);
    TTEST(suite, test_parser_array_optimized_type_noop_empty);
    TTEST(suite, test_parser_array_optimized_type_true_empty);
    TTEST(suite, test_parser_array_optimized_type_false_empty);
    TTEST(suite, test_parser_array_optimized_type_uint8_empty);
    TTEST(suite, test_parser_array_optimized_type_char_empty);
    TTEST(suite, test_parser_array_optimized_type_int8_empty);
    TTEST(suite, test_parser_array_optimized_type_int16_empty);
    TTEST(suite, test_parser_array_optimized_type_int32_empty);
    TTEST(suite, test_parser_array_optimized_type_int64_empty);
    TTEST(suite, test_parser_array_optimized_type_str_empty);
    TTEST(suite, test_parser_array_optimized_type_hpn_empty);
    TTEST(suite, test_parser_array_optimized_type_array_empty);
    TTEST(suite, test_parser_array_optimized_type_object_empty);
    TTEST(suite, test_parser_array_optimized_type_null_lots);
    TTEST(suite, test_parser_array_optimized_type_noop_lots);
    TTEST(suite, test_parser_array_optimized_type_true_lots);
    TTEST(suite, test_parser_array_optimized_type_false_lots);
    TTEST(suite, test_parser_array_optimized_type_uint8_lots);
    TTEST(suite, test_parser_array_optimized_type_char_lots);
    TTEST(suite, test_parser_array_optimized_type_int8_lots);
    TTEST(suite, test_parser_array_optimized_type_int16_lots);
    TTEST(suite, test_parser_array_optimized_type_int32_lots);
    TTEST(suite, test_parser_array_optimized_type_int64_lots);
    TTEST(suite, test_parser_array_optimized_type_str_lots);
    TTEST(suite, test_parser_array_optimized_type_hpn_lots);
    TTEST(suite, test_parser_array_optimized_type_array_lots);
    TTEST(suite, test_parser_array_optimized_type_object_lots);

    TTEST(suite, test_parser_object_empty);
    TTEST(suite, test_parser_object_null);
    TTEST(suite, test_parser_object_noop);
    TTEST(suite, test_parser_object_false);
    TTEST(suite, test_parser_object_true);
    TTEST(suite, test_parser_object_uint8);
    TTEST(suite, test_parser_object_int8);
    TTEST(suite, test_parser_object_int16);
    TTEST(suite, test_parser_object_int32);
    TTEST(suite, test_parser_object_int64);
    TTEST(suite, test_parser_object_float32);
    TTEST(suite, test_parser_object_float64);
    TTEST(suite, test_parser_object_char);
    TTEST(suite, test_parser_object_str);
    TTEST(suite, test_parser_object_hpn);
    TTEST(suite, test_parser_object_array);
    TTEST(suite, test_parser_object_object);
    TTEST(suite, test_parser_object_optimized_count_empty);
    TTEST(suite, test_parser_object_optimized_count_null);
    TTEST(suite, test_parser_object_optimized_count_noop);
    TTEST(suite, test_parser_object_optimized_count_true);
    TTEST(suite, test_parser_object_optimized_count_false);
    TTEST(suite, test_parser_object_optimized_count_uint8);
    TTEST(suite, test_parser_object_optimized_count_char);
    TTEST(suite, test_parser_object_optimized_count_int8);
    TTEST(suite, test_parser_object_optimized_count_int8_negative);
    TTEST(suite, test_parser_object_optimized_count_int16);
    TTEST(suite, test_parser_object_optimized_count_int16_negative);
    TTEST(suite, test_parser_object_optimized_count_int32);
    TTEST(suite, test_parser_object_optimized_count_int32_negative);
    TTEST(suite, test_parser_object_optimized_count_int64);
    TTEST(suite, test_parser_object_optimized_count_str);
    TTEST(suite, test_parser_object_optimized_count_hpn);
    TTEST(suite, test_parser_object_optimized_count_array);
    TTEST(suite, test_parser_object_optimized_count_object);
    TTEST(suite, test_parser_object_optimized_type_null_empty);
    TTEST(suite, test_parser_object_optimized_type_noop_empty);
    TTEST(suite, test_parser_object_optimized_type_true_empty);
    TTEST(suite, test_parser_object_optimized_type_false_empty);
    TTEST(suite, test_parser_object_optimized_type_uint8_empty);
    TTEST(suite, test_parser_object_optimized_type_char_empty);
    TTEST(suite, test_parser_object_optimized_type_int8_empty);
    TTEST(suite, test_parser_object_optimized_type_int16_empty);
    TTEST(suite, test_parser_object_optimized_type_int32_empty);
    TTEST(suite, test_parser_object_optimized_type_int64_empty);
    TTEST(suite, test_parser_object_optimized_type_str_empty);
    TTEST(suite, test_parser_object_optimized_type_hpn_empty);
    TTEST(suite, test_parser_object_optimized_type_array_empty);
    TTEST(suite, test_parser_object_optimized_type_object_empty);
    TTEST(suite, test_parser_object_optimized_type_null_lots);
    TTEST(suite, test_parser_object_optimized_type_noop_lots);
    TTEST(suite, test_parser_object_optimized_type_true_lots);
    TTEST(suite, test_parser_object_optimized_type_false_lots);
    TTEST(suite, test_parser_object_optimized_type_uint8_lots);
    TTEST(suite, test_parser_object_optimized_type_char_lots);
    TTEST(suite, test_parser_object_optimized_type_int8_lots);
    TTEST(suite, test_parser_object_optimized_type_int16_lots);
    TTEST(suite, test_parser_object_optimized_type_int32_lots);
    TTEST(suite, test_parser_object_optimized_type_int64_lots);
    TTEST(suite, test_parser_object_optimized_type_str_lots);
    TTEST(suite, test_parser_object_optimized_type_hpn_lots);
    TTEST(suite, test_parser_object_optimized_type_array_lots);
    TTEST(suite, test_parser_object_optimized_type_object_lots);
}
