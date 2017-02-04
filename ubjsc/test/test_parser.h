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

#ifndef HAVE_TEST_PARSER
#define HAVE_TEST_PARSER

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"

#define LOTS 255

typedef void (*sp_verify_parsed_callback)(ubjs_prmtv *);

void suite_parser(tcontext *);
void suite_parser_before(void);
void suite_parser_after(void);

void sp_verify_parsed(ubjs_library *, unsigned int, uint8_t *, sp_verify_parsed_callback);
void sp_verify_error(ubjs_library *, unsigned int, uint8_t *, char *);

/*
void dsp_verify_parsed(ubjs_library *, unsigned int, uint8_t *, sp_verify_parsed_callback);
void dsp_verify_error(ubjs_library *, unsigned int, uint8_t *, char *);
*/

void test_parser_builder(void);
void test_parser_basics(void);
void test_parser_no_error_f(void);
void test_parser_unknown_marker(void);

void test_parser_silently_ignore_toplevel_noops(void);
void test_parser_limit_bytes_since_last_callback_below(void);
void test_parser_limit_bytes_since_last_callback_above(void);
void test_parser_limit_container_length_array_unoptimized_below(void);
void test_parser_limit_container_length_array_unoptimized_above(void);
void test_parser_limit_container_length_array_optimized_below(void);
void test_parser_limit_container_length_array_optimized_above(void);
void test_parser_limit_container_length_object_unoptimized_below(void);
void test_parser_limit_container_length_object_unoptimized_above(void);
void test_parser_limit_container_length_object_optimized_below(void);
void test_parser_limit_container_length_object_optimized_above(void);
void test_parser_limit_string_length_optimized_below(void);
void test_parser_limit_string_length_optimized_above(void);
void test_parser_limit_hpn_length_optimized_below(void);
void test_parser_limit_hpn_length_optimized_above(void);
void test_parser_limit_recursion_level_array_below(void);
void test_parser_limit_recursion_level_array_above(void);
void test_parser_limit_recursion_level_object_below(void);
void test_parser_limit_recursion_level_object_above(void);

void test_parser_null(void);
void test_parser_noop(void);
void test_parser_true(void);
void test_parser_false(void);
void test_parser_int8(void);
void test_parser_uint8(void);
void test_parser_int16(void);
void test_parser_int32(void);
void test_parser_int64(void);
void test_parser_float32(void);
void test_parser_float64(void);
void test_parser_char(void);

void test_parser_str_empty(void);
void test_parser_str_null(void);
void test_parser_str_noop(void);
void test_parser_str_true(void);
void test_parser_str_false(void);
void test_parser_str_uint8(void);
void test_parser_str_int8(void);
void test_parser_str_int8_negative(void);
void test_parser_str_int16(void);
void test_parser_str_int16_negative(void);
void test_parser_str_int32(void);
void test_parser_str_int32_negative(void);
void test_parser_str_int64(void);
void test_parser_str_char(void);
void test_parser_str_str(void);
void test_parser_str_hpn(void);
void test_parser_str_float32(void);
void test_parser_str_float64(void);
void test_parser_str_array(void);
void test_parser_str_object(void);

void test_parser_hpn_empty(void);
void test_parser_hpn_null(void);
void test_parser_hpn_noop(void);
void test_parser_hpn_true(void);
void test_parser_hpn_false(void);
void test_parser_hpn_uint8(void);
void test_parser_hpn_int8(void);
void test_parser_hpn_int8_negative(void);
void test_parser_hpn_int16(void);
void test_parser_hpn_int16_negative(void);
void test_parser_hpn_int32(void);
void test_parser_hpn_int32_negative(void);
void test_parser_hpn_int64(void);
void test_parser_hpn_char(void);
void test_parser_hpn_str(void);
void test_parser_hpn_hpn(void);
void test_parser_hpn_float32(void);
void test_parser_hpn_float64(void);
void test_parser_hpn_array(void);
void test_parser_hpn_object(void);

void test_parser_array_empty(void);
void test_parser_array_unknown_marker(void);
void test_parser_array_null(void);
void test_parser_array_noop(void);
void test_parser_array_true(void);
void test_parser_array_false(void);
void test_parser_array_uint8(void);
void test_parser_array_int8(void);
void test_parser_array_int16(void);
void test_parser_array_int32(void);
void test_parser_array_int64(void);
void test_parser_array_float32(void);
void test_parser_array_float64(void);
void test_parser_array_char(void);
void test_parser_array_str(void);
void test_parser_array_hpn(void);
void test_parser_array_array(void);
void test_parser_array_object(void);
void test_parser_array_optimized_count_empty(void);
void test_parser_array_optimized_count_null(void);
void test_parser_array_optimized_count_noop(void);
void test_parser_array_optimized_count_true(void);
void test_parser_array_optimized_count_false(void);
void test_parser_array_optimized_count_uint8(void);
void test_parser_array_optimized_count_char(void);
void test_parser_array_optimized_count_int8(void);
void test_parser_array_optimized_count_int8_negative(void);
void test_parser_array_optimized_count_int16(void);
void test_parser_array_optimized_count_int16_negative(void);
void test_parser_array_optimized_count_int32(void);
void test_parser_array_optimized_count_int32_negative(void);
void test_parser_array_optimized_count_int64(void);
void test_parser_array_optimized_count_str(void);
void test_parser_array_optimized_count_hpn(void);
void test_parser_array_optimized_count_array(void);
void test_parser_array_optimized_count_object(void);
void test_parser_array_optimized_type_unknown_marker(void);
void test_parser_array_optimized_type_null_empty(void);
void test_parser_array_optimized_type_noop_empty(void);
void test_parser_array_optimized_type_true_empty(void);
void test_parser_array_optimized_type_false_empty(void);
void test_parser_array_optimized_type_uint8_empty(void);
void test_parser_array_optimized_type_char_empty(void);
void test_parser_array_optimized_type_int8_empty(void);
void test_parser_array_optimized_type_int16_empty(void);
void test_parser_array_optimized_type_int32_empty(void);
void test_parser_array_optimized_type_int64_empty(void);
void test_parser_array_optimized_type_float32_empty(void);
void test_parser_array_optimized_type_float64_empty(void);
void test_parser_array_optimized_type_str_empty(void);
void test_parser_array_optimized_type_hpn_empty(void);
void test_parser_array_optimized_type_array_empty(void);
void test_parser_array_optimized_type_object_empty(void);
void test_parser_array_optimized_type_null_lots(void);
void test_parser_array_optimized_type_noop_lots(void);
void test_parser_array_optimized_type_true_lots(void);
void test_parser_array_optimized_type_false_lots(void);
void test_parser_array_optimized_type_uint8_lots(void);
void test_parser_array_optimized_type_char_lots(void);
void test_parser_array_optimized_type_int8_lots(void);
void test_parser_array_optimized_type_int16_lots(void);
void test_parser_array_optimized_type_int32_lots(void);
void test_parser_array_optimized_type_int64_lots(void);
void test_parser_array_optimized_type_float32_lots(void);
void test_parser_array_optimized_type_float64_lots(void);
void test_parser_array_optimized_type_str_lots(void);
void test_parser_array_optimized_type_hpn_lots(void);
void test_parser_array_optimized_type_array_lots(void);
void test_parser_array_optimized_type_object_lots(void);

void test_parser_object_empty(void);
void test_parser_object_unknown_marker(void);
void test_parser_object_null(void);
void test_parser_object_noop(void);
void test_parser_object_true(void);
void test_parser_object_false(void);
void test_parser_object_uint8(void);
void test_parser_object_int8(void);
void test_parser_object_int16(void);
void test_parser_object_int32(void);
void test_parser_object_int64(void);
void test_parser_object_float32(void);
void test_parser_object_float64(void);
void test_parser_object_char(void);
void test_parser_object_str(void);
void test_parser_object_hpn(void);
void test_parser_object_array(void);
void test_parser_object_object(void);
void test_parser_object_optimized_count_null(void);
void test_parser_object_optimized_count_noop(void);
void test_parser_object_optimized_count_true(void);
void test_parser_object_optimized_count_false(void);
void test_parser_object_optimized_count_uint8(void);
void test_parser_object_optimized_count_uint8(void);
void test_parser_object_optimized_count_char(void);
void test_parser_object_optimized_count_int8(void);
void test_parser_object_optimized_count_int8_negative(void);
void test_parser_object_optimized_count_int16(void);
void test_parser_object_optimized_count_int16_negative(void);
void test_parser_object_optimized_count_int32(void);
void test_parser_object_optimized_count_int32_negative(void);
void test_parser_object_optimized_count_int64(void);
void test_parser_object_optimized_count_str(void);
void test_parser_object_optimized_count_hpn(void);
void test_parser_object_optimized_count_array(void);
void test_parser_object_optimized_count_object(void);
void test_parser_object_optimized_type_unknown_marker(void);
void test_parser_object_optimized_type_null_empty(void);
void test_parser_object_optimized_type_noop_empty(void);
void test_parser_object_optimized_type_true_empty(void);
void test_parser_object_optimized_type_false_empty(void);
void test_parser_object_optimized_type_uint8_empty(void);
void test_parser_object_optimized_type_char_empty(void);
void test_parser_object_optimized_type_int8_empty(void);
void test_parser_object_optimized_type_int16_empty(void);
void test_parser_object_optimized_type_int32_empty(void);
void test_parser_object_optimized_type_int64_empty(void);
void test_parser_object_optimized_type_float32_empty(void);
void test_parser_object_optimized_type_float64_empty(void);
void test_parser_object_optimized_type_str_empty(void);
void test_parser_object_optimized_type_hpn_empty(void);
void test_parser_object_optimized_type_array_empty(void);
void test_parser_object_optimized_type_object_empty(void);
void test_parser_object_optimized_type_null_lots(void);
void test_parser_object_optimized_type_noop_lots(void);
void test_parser_object_optimized_type_true_lots(void);
void test_parser_object_optimized_type_false_lots(void);
void test_parser_object_optimized_type_uint8_lots(void);
void test_parser_object_optimized_type_char_lots(void);
void test_parser_object_optimized_type_int8_lots(void);
void test_parser_object_optimized_type_int16_lots(void);
void test_parser_object_optimized_type_int32_lots(void);
void test_parser_object_optimized_type_int64_lots(void);
void test_parser_object_optimized_type_float32_lots(void);
void test_parser_object_optimized_type_float64_lots(void);
void test_parser_object_optimized_type_str_lots(void);
void test_parser_object_optimized_type_hpn_lots(void);
void test_parser_object_optimized_type_array_lots(void);
void test_parser_object_optimized_type_object_lots(void);

#ifdef __cplusplus
}
#endif

#endif