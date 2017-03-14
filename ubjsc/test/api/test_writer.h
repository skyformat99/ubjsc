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

#ifndef HAVE_TEST_WRITER
#define HAVE_TEST_WRITER

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"

void suite_writer_before(void);
void suite_writer_after(void);

void sw_verify(ubjs_library *lib, ubjs_prmtv *, unsigned unt, uint8_t *, unsigned int, char *);
void sw_verifyd(ubjs_library *lib, ubjs_prmtv *, unsigned unt, uint8_t *, unsigned int, char *,
    ubjs_bool);

void test_writer_init_clean(void);
void test_writer_basics(void);

void test_writer_null(void);
void test_writer_noop(void);
void test_writer_true(void);
void test_writer_false(void);
void test_writer_int8(void);
void test_writer_uint8(void);
void test_writer_int16(void);
void test_writer_int32(void);
void test_writer_int64(void);
void test_writer_float32(void);
void test_writer_float64(void);
void test_writer_char(void);

void test_writer_str_uint8(void);
void test_writer_str_int16(void);
void test_writer_str_int32(void);
void test_writer_hpn_uint8(void);
void test_writer_hpn_int16(void);
void test_writer_hpn_int32(void);

void test_writer_array_empty(void);
void test_writer_array_uint8(void);
void test_writer_array_int8(void);
void test_writer_array_int16(void);
void test_writer_array_int32(void);
void test_writer_array_null(void);
void test_writer_array_noop(void);
void test_writer_array_true(void);
void test_writer_array_false(void);
void test_writer_array_char(void);
void test_writer_array_str(void);
void test_writer_array_hpn(void);
void test_writer_array_int64(void);
void test_writer_array_float32(void);
void test_writer_array_float64(void);
void test_writer_array_array(void);
void test_writer_array_object(void);
void test_writer_array_count_optimized_uint8(void);
void test_writer_array_count_optimized_int16(void);
void test_writer_array_count_optimized_int32(void);
void test_writer_array_type_optimized_null(void);
void test_writer_array_type_optimized_noop(void);
void test_writer_array_type_optimized_false(void);
void test_writer_array_type_optimized_true(void);
void test_writer_array_type_optimized_char(void);
void test_writer_array_type_optimized_uint8(void);
void test_writer_array_type_optimized_int8(void);
void test_writer_array_type_optimized_int16(void);
void test_writer_array_type_optimized_int32(void);
void test_writer_array_type_optimized_int64(void);
void test_writer_array_type_optimized_float32(void);
void test_writer_array_type_optimized_float64(void);
void test_writer_array_type_optimized_str(void);
void test_writer_array_type_optimized_hpn(void);
void test_writer_array_type_optimized_array(void);
void test_writer_array_type_optimized_object(void);
void test_writer_array_upgraded_from_uint8_to_int16(void);
void test_writer_array_upgraded_from_int8_to_int16(void);
void test_writer_array_not_upgraded_from_int8_to_int16_too_little(void);
void test_writer_array_not_upgraded_from_int8_to_int16_are_int32(void);
void test_writer_array_not_upgraded_from_int8_to_int16_are_int64(void);
void test_writer_array_not_upgraded_from_int8_to_int16_are_other_types(void);
void test_writer_array_upgraded_from_int8_int16_to_int32(void);
void test_writer_array_upgraded_from_uint8_int16_to_int32(void);
void test_writer_array_not_upgraded_from_int8_int16_to_int32_too_little(void);
void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_int64(void);
void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_other_types(void);
void test_writer_array_upgraded_from_int8_int16_int32_to_int64(void);
void test_writer_array_upgraded_from_uint8_int16_int32_to_int64(void);
void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_too_little(void);
void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_no_int8_no_int16_no_int32(
    void **);
void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types(void);

void test_writer_object_empty(void);
void test_writer_object_uint8(void);
void test_writer_object_int8(void);
void test_writer_object_int16(void);
void test_writer_object_int32(void);
void test_writer_object_null(void);
void test_writer_object_noop(void);
void test_writer_object_true(void);
void test_writer_object_false(void);
void test_writer_object_char(void);
void test_writer_object_str(void);
void test_writer_object_hpn(void);
void test_writer_object_int64(void);
void test_writer_object_float32(void);
void test_writer_object_float64(void);
void test_writer_object_array(void);
void test_writer_object_object(void);
void test_writer_object_count_optimized_uint8(void);
void test_writer_object_count_optimized_int16(void);
void test_writer_object_count_optimized_int32(void);
void test_writer_object_type_optimized_null(void);
void test_writer_object_type_optimized_noop(void);
void test_writer_object_type_optimized_false(void);
void test_writer_object_type_optimized_true(void);
void test_writer_object_type_optimized_char(void);
void test_writer_object_type_optimized_uint8(void);
void test_writer_object_type_optimized_int8(void);
void test_writer_object_type_optimized_int16(void);
void test_writer_object_type_optimized_int32(void);
void test_writer_object_type_optimized_int64(void);
void test_writer_object_type_optimized_float32(void);
void test_writer_object_type_optimized_float64(void);
void test_writer_object_type_optimized_str(void);
void test_writer_object_type_optimized_hpn(void);
void test_writer_object_type_optimized_array(void);
void test_writer_object_type_optimized_object(void);
void test_writer_object_upgraded_from_uint8_to_int16(void);
void test_writer_object_upgraded_from_int8_to_int16(void);
void test_writer_object_not_upgraded_from_int8_to_int16_too_little(void);
void test_writer_object_not_upgraded_from_int8_to_int16_are_int32(void);
void test_writer_object_not_upgraded_from_int8_to_int16_are_int64(void);
void test_writer_object_not_upgraded_from_int8_to_int16_are_other_types(void);
void test_writer_object_upgraded_from_int8_int16_to_int32(void);
void test_writer_object_upgraded_from_uint8_int16_to_int32(void);
void test_writer_object_not_upgraded_from_int8_int16_to_int32_too_little(void);
void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_int64(void);
void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_other_types(void);
void test_writer_object_upgraded_from_int8_int16_int32_to_int64(void);
void test_writer_object_upgraded_from_uint8_int16_int32_to_int64(void);
void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_too_little(void);
void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_are_other_types(void);

#ifdef __cplusplus
}
#endif

#endif
