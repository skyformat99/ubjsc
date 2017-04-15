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
/* \internal */
#ifndef HAVE_UBJS_PRIMITIVE_UINT8_PRV
#define HAVE_UBJS_PRIMITIVE_UINT8_PRV

#include <ubjs_primitive_uint8.h>

typedef struct ubjs_prmtv_uint8_t ubjs_prmtv_uint8_t;
struct ubjs_prmtv_uint8_t
{
    ubjs_prmtv super;
    uint8_t value;
};

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_free(ubjs_prmtv **);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_new_from_int64(ubjs_library *, int64_t, ubjs_prmtv **);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_get_value_int64(ubjs_prmtv *, int64_t *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_set_value_int64(ubjs_prmtv *, int64_t);

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_debug_string_get_length(ubjs_prmtv *, unsigned int *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_debug_string_copy(ubjs_prmtv *, char *);

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_parser_processor_new(ubjs_library *,
     ubjs_prmtv_ntype_parser_glue *, ubjs_prmtv_ntype_parser_processor **);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *, ubjs_prmtv *);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *, uint8_t);

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_writer_new(ubjs_library *,
    ubjs_prmtv_ntype_writer_glue *, ubjs_prmtv_ntype_writer **);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_writer_free(ubjs_prmtv_ntype_writer **);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_writer_get_length(ubjs_prmtv_ntype_writer *,
    unsigned int *);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_writer_do(ubjs_prmtv_ntype_writer *, uint8_t *);

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_printer_new(ubjs_library *,
    ubjs_prmtv_ntype_printer_glue *, ubjs_prmtv_ntype_printer **);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_uint8_printer_free(ubjs_prmtv_ntype_printer **);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_printer_get_length(ubjs_prmtv_ntype_printer *,
    unsigned int *);
UBJS_NO_EXPORT void ubjs_prmtv_uint8_printer_do(ubjs_prmtv_ntype_printer *, char *);

#endif
/* \endinternal */
