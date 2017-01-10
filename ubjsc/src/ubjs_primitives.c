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

#include <stdio.h>
#include <string.h>

#include "ubjs_primitives_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

ubjs_prmtv __ubjs_prmtv_null = {0, UOT_NULL};
ubjs_prmtv __ubjs_prmtv_noop = {0, UOT_NOOP};
ubjs_prmtv __ubjs_prmtv_true = {0, UOT_TRUE};
ubjs_prmtv __ubjs_prmtv_false = {0, UOT_FALSE};

ubjs_prmtv *ubjs_prmtv_null(void)
{
    return &__ubjs_prmtv_null;
}

ubjs_result ubjs_prmtv_is_null(ubjs_prmtv *this, ubjs_bool* result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_null) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_noop(void)
{
    return &__ubjs_prmtv_noop;
}

ubjs_result ubjs_prmtv_is_noop(ubjs_prmtv *this, ubjs_bool* result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_noop) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_true(void)
{
    return &__ubjs_prmtv_true;
}

ubjs_result ubjs_prmtv_is_true(ubjs_prmtv *this, ubjs_bool* result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_true) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_prmtv *ubjs_prmtv_false(void)
{
    return &__ubjs_prmtv_false;
}

ubjs_result ubjs_prmtv_is_false(ubjs_prmtv *this, ubjs_bool* result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this == &__ubjs_prmtv_false) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    if (0 == lib)
    {
        return UR_ERROR;
    }

    if (UINT8_MAX >= value && 0 <= value)
    {
        return ubjs_prmtv_uint8(lib, (uint8_t)value, pthis);
    }
    else if (INT8_MAX >= value && INT8_MIN <= value)
    {
        return ubjs_prmtv_int8(lib, (int8_t)value, pthis);
    }
    else if (INT16_MAX >= value && INT16_MIN <= value)
    {
        return ubjs_prmtv_int16(lib, (int16_t)value, pthis);
    }
    else if (INT32_MAX >= value && INT32_MIN <= value)
    {
        return ubjs_prmtv_int32(lib, (int32_t)value, pthis);
    }

    return ubjs_prmtv_int64(lib, value, pthis);
}

ubjs_result ubjs_prmtv_uint(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    if (0 == lib || 0 > value)
    {
        return UR_ERROR;
    }

    if (UINT8_MAX >= value)
    {
        return ubjs_prmtv_uint8(lib, (uint8_t)value, pthis);
    }
    else if (INT16_MAX >= value)
    {
        return ubjs_prmtv_int16(lib, (int16_t)value, pthis);
    }
    else if (INT32_MAX >= value)
    {
        return ubjs_prmtv_int32(lib, (int32_t)value, pthis);
    }

    return ubjs_prmtv_int64(lib, value, pthis);
}

ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue)
{
    int8_t v8;
    uint8_t vu8;
    int16_t v16;
    int32_t v32;

    if (0 == this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    switch (this->type)
    {
    case UOT_INT8:
        ubjs_prmtv_int8_get(this, &v8);
        *pvalue = (int64_t)v8;
        return UR_OK;

    case UOT_UINT8:
        ubjs_prmtv_uint8_get(this, &vu8);
        *pvalue = (int64_t)vu8;
        return UR_OK;

    case UOT_INT16:
        ubjs_prmtv_int16_get(this, &v16);
        *pvalue = (int64_t)v16;
        return UR_OK;

    case UOT_INT32:
        ubjs_prmtv_int32_get(this, &v32);
        *pvalue = (int64_t)v32;
        return UR_OK;

    case UOT_INT64:
        return ubjs_prmtv_int64_get(this, pvalue);

    default:
       break;
    }

    return UR_ERROR;
}

ubjs_result ubjs_prmtv_is_int(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT8
        || this->type == UOT_UINT8
        || this->type == UOT_INT16
        || this->type == UOT_INT32
        || this->type == UOT_INT64)
        ? UTRUE : UFALSE;

    return UR_OK;
}

ubjs_result ubjs_prmtv_int8(ubjs_library *lib, int8_t value, ubjs_prmtv **pthis)
{
    ubjs_int8 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_int8 *)(lib->alloc_f)(sizeof(struct ubjs_int8));
    this->super.lib=lib;
    this->super.type=UOT_INT8;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int8(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int8_get(ubjs_prmtv *this, int8_t *result)
{
    ubjs_int8 *rthis;
    if (0 == this || UOT_INT8 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int8_set(ubjs_prmtv *this, int8_t value)
{
    ubjs_int8 *rthis;
    if (0 == this || UOT_INT8 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8(ubjs_library *lib, uint8_t value, ubjs_prmtv **pthis)
{
    ubjs_uint8 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_uint8 *)(lib->alloc_f)(sizeof(struct ubjs_uint8));
    this->super.lib=lib;
    this->super.type=UOT_UINT8;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_uint8(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_UINT8) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *this, uint8_t *result)
{
    ubjs_uint8 *rthis;
    if (0 == this || UOT_UINT8 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *this, uint8_t value)
{
    ubjs_uint8 *rthis;
    if (0 == this || UOT_UINT8 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_uint8 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16(ubjs_library *lib, int16_t value, ubjs_prmtv **pthis)
{
    ubjs_int16 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_int16 *)(lib->alloc_f)(sizeof(struct ubjs_int16));
    this->super.lib=lib;
    this->super.type=UOT_INT16;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int16(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT16) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *this, int16_t *result)
{
    ubjs_int16 *rthis;
    if (0 == this || UOT_INT16 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *this, int16_t value)
{
    ubjs_int16 *rthis;
    if (0 == this || UOT_INT16 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int16 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32(ubjs_library *lib, int32_t value, ubjs_prmtv **pthis)
{
    ubjs_int32 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_int32 *)(lib->alloc_f)(sizeof(struct ubjs_int32));
    this->super.lib=lib;
    this->super.type=UOT_INT32;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int32(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32_get(ubjs_prmtv *this, int32_t *result)
{
    ubjs_int32 *rthis;
    if (0 == this || UOT_INT32 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int32_set(ubjs_prmtv *this, int32_t value)
{
    ubjs_int32 *rthis;
    if (0 == this || UOT_INT32 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    ubjs_int64 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_int64 *)(lib->alloc_f)(sizeof(struct ubjs_int64));
    this->super.lib=lib;
    this->super.type=UOT_INT64;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_int64(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_INT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64_get(ubjs_prmtv *this, int64_t *result)
{
    ubjs_int64 *rthis;
    if (0 == this || UOT_INT64 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int64_set(ubjs_prmtv *this, int64_t value)
{
    ubjs_int64 *rthis;
    if (0 == this || UOT_INT64 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_int64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32(ubjs_library *lib, float32_t value, ubjs_prmtv **pthis)
{
    ubjs_float32 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_float32 *)(lib->alloc_f)(sizeof(struct ubjs_float32));
    this->super.lib=lib;
    this->super.type=UOT_FLOAT32;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_float32(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT32) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32_get(ubjs_prmtv *this, float32_t *result)
{
    ubjs_float32 *rthis;

    if (0 == this || UOT_FLOAT32 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float32_set(ubjs_prmtv *this, float32_t value)
{
    ubjs_float32 *rthis;
    if (0 == this || UOT_FLOAT32 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float32 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64(ubjs_library *lib, float64_t value, ubjs_prmtv **pthis)
{
    ubjs_float64 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_float64 *)(lib->alloc_f)(sizeof(struct ubjs_float64));
    this->super.lib=lib;
    this->super.type=UOT_FLOAT64;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *this, float64_t *result)
{
    ubjs_float64 *rthis;

    if (0 == this || UOT_FLOAT64 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *this, float64_t value)
{
    ubjs_float64 *rthis;
    if (0 == this || UOT_FLOAT64 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char(ubjs_library *lib, char value, ubjs_prmtv **pthis)
{
    ubjs_char *this;

    if (0 == lib || 0 == pthis || value > 127)
    {
        return UR_ERROR;
    }

    this=(ubjs_char *)(lib->alloc_f)(sizeof(struct ubjs_char));
    this->super.lib=lib;
    this->super.type=UOT_CHAR;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_char(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_CHAR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *this, char *result)
{
    ubjs_char *rthis;

    if (0 == this || UOT_CHAR != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *this, char value)
{
    ubjs_char *rthis;
    if (0 == this || UOT_CHAR != this->type || value > 127)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_char *)this;
    rthis->value=value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str(ubjs_library *lib, unsigned int length, char *text, ubjs_prmtv **pthis)
{
    ubjs_str *this;
    char *cpy;

    if (0 == lib || 0 == pthis || 0 == text)
    {
        return UR_ERROR;
    }

    this = (ubjs_str *)(lib->alloc_f)(sizeof(struct ubjs_str));
    cpy = (char *)(lib->alloc_f)(sizeof(char) * length);
    strncpy(cpy, text, length);

    this->super.lib=lib;
    this->super.type=UOT_STR;
    this->length=length;
    this->text=cpy;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_str(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_STR) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *this, unsigned int *result)
{
    ubjs_str *rthis;

    if (0 == this || UOT_STR != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    (*result) = rthis->length;

    return UR_OK;
}

ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *this, char *result)
{
    ubjs_str *rthis;

    if (0 == this || UOT_STR != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;

    strncpy(result, rthis->text, rthis->length);

    return UR_OK;
}

ubjs_result ubjs_prmtv_str_set(ubjs_prmtv *this, unsigned int length, char *text)
{
    ubjs_str *rthis;
    char *cpy;

    if (0 == this || UOT_STR != this->type || 0 == text)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_str *)this;
    (this->lib->free_f)(rthis->text);

    cpy = (char *)(this->lib->alloc_f)(sizeof(char) * length);
    strncpy(cpy, text, length);
    rthis->text=cpy;
    rthis->length=length;
    return UR_OK;
}

unsigned int ubjs_prmtv_is_valid_hpn_state_processor_matrix_length = 10;
ubjs_prmtv_is_valid_hpn_state_processor_f \
     ubjs_prmtv_is_valid_hpn_state_processor_matrix[] =
{
    ubjs_prmtv_is_valid_hpn_state_processor_begin,
    ubjs_prmtv_is_valid_hpn_state_processor_after_minus,
    ubjs_prmtv_is_valid_hpn_state_processor_after_digit,
    ubjs_prmtv_is_valid_hpn_state_processor_after_digits,
    ubjs_prmtv_is_valid_hpn_state_processor_after_dot_before_digits,
    ubjs_prmtv_is_valid_hpn_state_processor_after_number,
    ubjs_prmtv_is_valid_hpn_state_processor_after_e,
    ubjs_prmtv_is_valid_hpn_state_processor_after_e_plus_minus,
    ubjs_prmtv_is_valid_hpn_state_processor_after_e_digit,
    ubjs_prmtv_is_valid_hpn_state_processor_after_end
};


ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_begin(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c == '-')
    {
        *pstate = PMIVHS_AFTER_MINUS;
    }
    else if (c == '0')
    {
        *pstate = PMIVHS_AFTER_DIGITS;
    }
    else if (c >= '1' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_DIGIT;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_minus(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c == '0')
    {
        *pstate = PMIVHS_AFTER_DIGITS;
    }
    else if (c >= '1' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_DIGIT;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_digit(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_DIGIT;
    }
    else if (c == '.')
    {
        *pstate = PMIVHS_AFTER_DOT_BEFORE_DIGITS;
    }
    else if (c == 'e' || c == 'E')
    {
        *pstate = PMIVHS_AFTER_E;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_digits(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c == '.')
    {
        *pstate = PMIVHS_AFTER_DOT_BEFORE_DIGITS;
    }
    else if (c == 'e' || c == 'E')
    {
        *pstate = PMIVHS_AFTER_E;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_dot_before_digits(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_NUMBER;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_number(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_NUMBER;
    }
    else if (c == 'e' || c == 'E')
    {
        *pstate = PMIVHS_AFTER_E;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_E_DIGIT;
    }
    else if (c == '+' || c == '-')
    {
        *pstate = PMIVHS_AFTER_E_PLUS_MINUS;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e_plus_minus(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_E_DIGIT;
    }
    else if (c == '+' || c == '-')
    {
        *pstate = PMIVHS_AFTER_E_PLUS_MINUS;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e_digit(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_E_DIGIT;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_end(char c,
    enum ubjs_prmtv_is_valid_hpn_state *pstate)
{
    if (c >= '0' && c <= '9')
    {
        *pstate = PMIVHS_AFTER_E_DIGIT;
    }
    else
    {
        return UR_ERROR;
    }
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_valid_hpn(unsigned int length, char *text, ubjs_bool *presult)
{
    enum ubjs_prmtv_is_valid_hpn_state state = PMIVHS_BEGIN;
    unsigned int i;

    *presult = UTRUE;

    for (i = 0; length > i; i++)
    {
        char c = text[i];
        if (UR_ERROR == (ubjs_prmtv_is_valid_hpn_state_processor_matrix[state])(c, &state))
        {
            *presult = UFALSE;
            break;
        }
    }

    if (UTRUE == *presult)
    {
        *presult = (state == PMIVHS_AFTER_DIGIT || state == PMIVHS_AFTER_DIGITS
            || state == PMIVHS_AFTER_NUMBER || state == PMIVHS_AFTER_E_DIGIT);
    }

    return UR_OK;
}

ubjs_result ubjs_prmtv_hpn(ubjs_library *lib, unsigned int length, char *text, ubjs_prmtv **pthis)
{
    ubjs_hpn *this;
    ubjs_bool is_valid;
    char *cpy;

    if (0 == lib || 0 == pthis || 0 == text)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_is_valid_hpn(length, text, &is_valid);
    if (UFALSE == is_valid)
    {
        return UR_ERROR;
    }

    this = (ubjs_hpn *)(lib->alloc_f)(sizeof(struct ubjs_str));
    cpy = (char *)(lib->alloc_f)(sizeof(char) * length);
    strncpy(cpy, text, length);

    this->super.lib=lib;
    this->super.type=UOT_HPN;
    this->length=length;
    this->text=cpy;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_hpn(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_HPN) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_hpn_get_length(ubjs_prmtv *this, unsigned int *result)
{
    ubjs_hpn *rthis;

    if (0 == this || UOT_HPN != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_hpn *)this;

    (*result) = rthis->length;

    return UR_OK;
}

ubjs_result ubjs_prmtv_hpn_copy_text(ubjs_prmtv *this, char *result)
{
    ubjs_hpn *rthis;

    if (0 == this || UOT_HPN != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_hpn *)this;

    strncpy(result, rthis->text, rthis->length);

    return UR_OK;
}

ubjs_result ubjs_prmtv_hpn_set(ubjs_prmtv *this, unsigned int length, char *text)
{
    ubjs_hpn *rthis;
    char *cpy;
    ubjs_bool is_valid;

    if (0 == this || UOT_HPN != this->type || 0 == text)
    {
        return UR_ERROR;
    }

    ubjs_prmtv_is_valid_hpn(length, text, &is_valid);
    if (UFALSE == is_valid)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_hpn *)this;
    (this->lib->free_f)(rthis->text);

    cpy = (char *)(this->lib->alloc_f)(sizeof(char) * length);
    strncpy(cpy, text, length);
    rthis->text=cpy;
    rthis->length=length;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_with_length_and_type(ubjs_library *lib, ubjs_prmtv_type type,
    unsigned int length, ubjs_prmtv **pthis)
{
    ubjs_array *this;
    ubjs_glue_array_builder *glue_builder;
    unsigned int item_size = 0;

    if (0 == lib || 0 == pthis || type >= UOT_MAX)
    {
        return UR_ERROR;
    }

    switch (type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        item_size = sizeof(struct ubjs_prmtv);
        break;

    case UOT_INT8:
        item_size = sizeof(struct ubjs_int8);
        break;

    case UOT_UINT8:
        item_size = sizeof(struct ubjs_uint8);
        break;

    case UOT_INT16:
        item_size = sizeof(struct ubjs_int16);
        break;

    case UOT_INT32:
        item_size = sizeof(struct ubjs_int32);
        break;

    case UOT_INT64:
        item_size = sizeof(struct ubjs_int64);
        break;

    case UOT_FLOAT32:
        item_size = sizeof(struct ubjs_float32);
        break;

    case UOT_FLOAT64:
        item_size = sizeof(struct ubjs_float64);
        break;

    case UOT_CHAR:
        item_size = sizeof(struct ubjs_char);
        break;

    case UOT_STR:
        item_size = sizeof(struct ubjs_str);
        break;

    case UOT_HPN:
        item_size = sizeof(struct ubjs_hpn);
        break;

    case UOT_ARRAY:
        item_size = sizeof(struct ubjs_array);
        break;

    case UOT_OBJECT:
        item_size = sizeof(struct ubjs_object);
        break;
    /* LCOV_EXCL_START */
    default:
        break;
    /* LCOV_EXCL_STOP */

    }

    this=(ubjs_array *)(lib->alloc_f)(sizeof(struct ubjs_array));

    (lib->glue_array_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->set_item_size_f)(glue_builder, item_size);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_ARRAY;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_ARRAY) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == plen)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_length_f)(athis->glue, plen);
}

ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_first_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_last_f)(athis->glue, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv **pitem)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == pitem)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->get_at_f)(athis->glue, pos, (void **)pitem);
}

ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_first_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_last_f)(athis->glue, item);
}

ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this, unsigned int pos, ubjs_prmtv *item)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type || 0 == item)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->add_at_f)(athis->glue, pos, item);
}

ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_first_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_last_f)(athis->glue);
}

ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this, unsigned int pos)
{
    ubjs_array *athis;

    if (0 == this || UOT_ARRAY != this->type)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    return (athis->glue->delete_at_f)(athis->glue, pos);
}

ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this, ubjs_array_iterator **piterator)
{
    ubjs_array *athis;
    ubjs_array_iterator *iterator;

    if (0 == this || UOT_ARRAY != this->type || 0 == piterator)
    {
        return UR_ERROR;
    }

    athis=(ubjs_array *)this;
    iterator=(ubjs_array_iterator *)(athis->super.lib->alloc_f)(sizeof(struct ubjs_array_iterator));
    iterator->array=athis;
    iterator->glue=0;
    (athis->glue->iterate_f)(athis->glue, &(iterator->glue));

    *piterator = iterator;
    return UR_OK;
}

ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    return (this->glue->next_f)(this->glue);
}

ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this, ubjs_prmtv **pitem)
{
    if (0 == this || 0 == pitem)
    {
        return UR_ERROR;
    }

    return (this->glue->get_f)(this->glue, (void **)pitem);
}

ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis)
{
    ubjs_array_iterator *this;

    if (0 == pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->glue->free_f)(&(this->glue));
    (this->array->super.lib->free_f)(*pthis);
    *pthis=0;
    return UR_OK;
}

void ubjs_prmtv_glue_item_free(void *item)
{
    ubjs_prmtv_free((ubjs_prmtv **)&item);
}

ubjs_result ubjs_prmtv_object(ubjs_library *lib, ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_with_length_and_type(ubjs_library *lib, ubjs_prmtv_type type,
    unsigned int length, ubjs_prmtv **pthis)
{
    ubjs_object *this;
    ubjs_glue_dict_builder *glue_builder;
    unsigned int item_size = 0;

    if (0 == lib || 0 == pthis || type >= UOT_MAX)
    {
        return UR_ERROR;
    }

    switch (type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        item_size = sizeof(struct ubjs_prmtv);
        break;

    case UOT_INT8:
        item_size = sizeof(struct ubjs_int8);
        break;

    case UOT_UINT8:
        item_size = sizeof(struct ubjs_uint8);
        break;

    case UOT_INT16:
        item_size = sizeof(struct ubjs_int16);
        break;

    case UOT_INT32:
        item_size = sizeof(struct ubjs_int32);
        break;

    case UOT_INT64:
        item_size = sizeof(struct ubjs_int64);
        break;

    case UOT_FLOAT32:
        item_size = sizeof(struct ubjs_float32);
        break;

    case UOT_FLOAT64:
        item_size = sizeof(struct ubjs_float64);
        break;

    case UOT_CHAR:
        item_size = sizeof(struct ubjs_char);
        break;

    case UOT_STR:
        item_size = sizeof(struct ubjs_str);
        break;

    case UOT_HPN:
        item_size = sizeof(struct ubjs_hpn);
        break;

    case UOT_ARRAY:
        item_size = sizeof(struct ubjs_array);
        break;

    case UOT_OBJECT:
        item_size = sizeof(struct ubjs_object);
        break;
    /* LCOV_EXCL_START */
    default:
        break;
    /* LCOV_EXCL_STOP */

    }

    this=(ubjs_object *)(lib->alloc_f)(sizeof(struct ubjs_object));

    (lib->glue_dict_builder)(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_prmtv_glue_item_free);
    (glue_builder->set_length_f)(glue_builder, length);
    (glue_builder->set_item_size_f)(glue_builder, item_size);
    (glue_builder->build_f)(glue_builder, &(this->glue));
    (glue_builder->free_f)(&glue_builder);

    this->super.lib=lib;
    this->super.type=UOT_OBJECT;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_OBJECT) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_object *uthis;
    if (0 == this || UOT_OBJECT != this->type || 0 == plen)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->get_length_f)(uthis->glue, plen);
}

ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv **pvalue)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key || 0==pvalue)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->get_f)(uthis->glue, key_length, key, (void **)pvalue);
}

ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this, unsigned int key_length, char *key,
    ubjs_prmtv *value)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key || 0==value)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->set_f)(uthis->glue, key_length, key, value);
}

ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this, unsigned int key_length, char *key)
{
    ubjs_object *uthis;

    if (0==this || UOT_OBJECT != this->type|| 0==key)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    return (uthis->glue->delete_f)(uthis->glue, key_length, key);
}

ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this, ubjs_object_iterator **piterator)
{
    ubjs_object *uthis;
    ubjs_object_iterator *iterator;

    if (0==this || UOT_OBJECT != this->type|| 0==piterator)
    {
        return UR_ERROR;
    }

    uthis=(ubjs_object *)this;
    iterator=(ubjs_object_iterator *)(uthis->super.lib->alloc_f)(
        sizeof(struct ubjs_object_iterator));
    iterator->object=uthis;
    iterator->glue=0;
    (uthis->glue->iterate_f)(uthis->glue, &(iterator->glue));

    *piterator=iterator;
    return UR_OK;
}

ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this)
{
    if (0==this)
    {
        return UR_ERROR;
    }

    return (this->glue->next_f)(this->glue);
}

ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this, unsigned int *plen)
{
    if (0==this || 0 == plen)
    {
        return UR_ERROR;
    }

    return (this->glue->get_key_length_f)(this->glue, plen);
}

ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *key)
{
    if (0==this || 0 == key)
    {
        return UR_ERROR;
    }

    return (this->glue->copy_key_f)(this->glue, key);
}

ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this, ubjs_prmtv **pvalue)
{
    if (0==this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    return (this->glue->get_value_f)(this->glue, (void **)pvalue);
}

ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **pthis)
{
    ubjs_object_iterator *this;

    if (0==pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->glue->free_f)(&(this->glue));
    (this->object->super.lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_get_type(ubjs_prmtv *this, ubjs_prmtv_type *ptype)
{
    if (0 == this || 0 == ptype)
    {
        return UR_ERROR;
    }

    *ptype = this->type;
    return UR_OK;
}

ubjs_result ubjs_prmtv_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv *this;
    ubjs_str *sthis;
    ubjs_hpn *hthis;
    ubjs_array *athis;
    ubjs_object *oit;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    switch (this->type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        break;

    case UOT_INT8:
    case UOT_UINT8:
    case UOT_INT16:
    case UOT_INT32:
    case UOT_INT64:
    case UOT_FLOAT32:
    case UOT_FLOAT64:
    case UOT_CHAR:
        (this->lib->free_f)(this);
        break;

    case UOT_STR:
        sthis=(ubjs_str *)this;
        (this->lib->free_f)(sthis->text);
        (this->lib->free_f)(sthis);
        break;

    case UOT_HPN:
        hthis=(ubjs_hpn *)this;
        (this->lib->free_f)(hthis->text);
        (this->lib->free_f)(hthis);
        break;

    case UOT_ARRAY:
        athis=(ubjs_array *)this;
        (athis->glue->free_f)(&(athis->glue));
        (this->lib->free_f)(athis);
        break;

    case UOT_OBJECT:
        oit=(ubjs_object *)this;
        (oit->glue->free_f)(&(oit->glue));
        (this->lib->free_f)(oit);
        break;
    default:
        return UR_ERROR;
    }

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_int8 *i8this = 0;
    ubjs_uint8 *u8this = 0;
    ubjs_int16 *i16this = 0;
    ubjs_int32 *i32this = 0;
    ubjs_int64 *i64this = 0;
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_char *cthis = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;
    unsigned int len = 0;

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    switch (this->type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
        *plen=4;
        break;

    case UOT_FALSE:
        *plen=5;
        break;

    case UOT_INT8:
        i8this = (ubjs_int8 *)this;
        *plen = snprintf(0, 0, "int8 %d", i8this->value);
        break;

    case UOT_UINT8:
        u8this = (ubjs_uint8 *)this;
        *plen = snprintf(0, 0, "uint8 %u", u8this->value);
        break;

    case UOT_INT16:
        i16this = (ubjs_int16 *)this;
        *plen = snprintf(0, 0, "int16 %d", i16this->value);
        break;

    case UOT_INT32:
        i32this = (ubjs_int32 *)this;
        *plen = snprintf(0, 0, "int32 %d", i32this->value);
        break;

    case UOT_INT64:
        i64this = (ubjs_int64 *)this;
        *plen = snprintf(0, 0, "int64 %ld", i64this->value);
        break;

    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        *plen = snprintf(0, 0, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        *plen = snprintf(0, 0, "float64 %f", f64this->value);
        break;

    case UOT_CHAR:
        cthis = (ubjs_char *)this;
        *plen = snprintf(0, 0, "char %c", cthis->value);
        break;

    case UOT_STR:
        sthis = (ubjs_str *)this;
        *plen = snprintf(0, 0, "str %u <%.*s>", sthis->length,
            sthis->length, sthis->text);
        break;

    case UOT_HPN:
        hthis = (ubjs_hpn *)this;
        *plen = snprintf(0, 0, "hpn %u <%.*s>", hthis->length,
            hthis->length, hthis->text);
        break;

    case UOT_ARRAY:
        ubjs_prmtv_array_get_length(this, &len);
        *plen = snprintf(0, 0, "array %u", len);
        break;

    case UOT_OBJECT:
        ubjs_prmtv_object_get_length(this, &len);
        *plen = snprintf(0, 0, "object %u", len);
        break;
    default:
        break;
    }
    /* LCOV_EXCL_STOP */
#else
    *plen = 0;
#endif
    return UR_OK;
}

ubjs_result ubjs_prmtv_debug_string_copy(ubjs_prmtv *this, char *str)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_int8 *i8this = 0;
    ubjs_uint8 *u8this = 0;
    ubjs_int16 *i16this = 0;
    ubjs_int32 *i32this = 0;
    ubjs_int64 *i64this = 0;
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_char *cthis = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;
    unsigned int len = 0;

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    switch (this->type)
    {
    case UOT_NULL:
        sprintf(str, "null");
        break;

    case UOT_NOOP:
        sprintf(str, "noop");
        break;

    case UOT_TRUE:
        sprintf(str, "true");
        break;

    case UOT_FALSE:
        sprintf(str, "false");
        break;

    case UOT_INT8:
        i8this = (ubjs_int8 *)this;
        sprintf(str, "int8 %d", i8this->value);
        break;

    case UOT_UINT8:
        u8this = (ubjs_uint8 *)this;
        sprintf(str, "uint8 %u", u8this->value);
        break;

    case UOT_INT16:
        i16this = (ubjs_int16 *)this;
        sprintf(str, "int16 %d", i16this->value);
        break;

    case UOT_INT32:
        i32this = (ubjs_int32 *)this;
        sprintf(str, "int32 %d", i32this->value);
        break;

    case UOT_INT64:
        i64this = (ubjs_int64 *)this;
        sprintf(str, "int64 %ld", i64this->value);
        break;

    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        sprintf(str, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        sprintf(str, "float64 %f", f64this->value);
        break;

    case UOT_CHAR:
        cthis = (ubjs_char *)this;
        sprintf(str, "char %c", cthis->value);
        break;

    case UOT_STR:
        sthis = (ubjs_str *)this;
        sprintf(str, "str %u <%.*s>", sthis->length,
            sthis->length, sthis->text);
        break;

    case UOT_HPN:
        hthis = (ubjs_hpn *)this;
        sprintf(str, "hpn %u <%.*s>", hthis->length,
            hthis->length, hthis->text);
        break;

    case UOT_ARRAY:
        ubjs_prmtv_array_get_length(this, &len);
        sprintf(str, "array %u", len);
        break;

    case UOT_OBJECT:
        ubjs_prmtv_object_get_length(this, &len);
        sprintf(str, "object %u", len);
        break;
    default:
        break;
    }
    /* LCOV_EXCL_STOP */
#endif
    return UR_OK;
}

ubjs_result ubjs_prmtv_convert_marker_to_type(unsigned int marker, ubjs_prmtv_type *ptype)
{
    switch (marker)
    {
        case MARKER_NULL: *ptype = UOT_NULL; break;
        case MARKER_NOOP: *ptype = UOT_NOOP; break;
        case MARKER_TRUE: *ptype = UOT_TRUE; break;
        case MARKER_FALSE: *ptype = UOT_FALSE; break;
        case MARKER_UINT8: *ptype = UOT_UINT8; break;
        case MARKER_INT8: *ptype = UOT_INT8; break;
        case MARKER_INT16: *ptype = UOT_INT16; break;
        case MARKER_INT32: *ptype = UOT_INT32; break;
        case MARKER_INT64: *ptype = UOT_INT64; break;
        case MARKER_FLOAT32: *ptype = UOT_FLOAT32; break;
        case MARKER_FLOAT64: *ptype = UOT_FLOAT64; break;
        case MARKER_STR: *ptype = UOT_STR; break;
        case MARKER_CHAR: *ptype = UOT_CHAR; break;
        case MARKER_HPN: *ptype = UOT_HPN; break;
        case MARKER_ARRAY_BEGIN: *ptype = UOT_ARRAY; break;
        case MARKER_OBJECT_BEGIN: *ptype = UOT_OBJECT; break;
        default: return UR_ERROR;
    }
    return UR_OK;
}
