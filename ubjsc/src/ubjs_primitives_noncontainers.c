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

#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

#include "ubjs_primitives_prv.h"

ubjs_result ubjs_prmtv_int(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    unsigned int i;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    for (i = 0; i < ubjs_prmtv_ntypes_len; i++)
    {
        ubjs_prmtv_ntype *ntype;
        ntype = ubjs_prmtv_ntypes[i];
        if (0 != ntype->new_from_int64_f &&
            UR_OK == (ntype->new_from_int64_f)(lib, value, pthis))
        {
            return UR_OK;
        }
    }

    if (INT16_MAX >= value && INT16_MIN <= value)
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

    return ubjs_prmtv_int(lib, value, pthis);
}

ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue)
{
    int16_t v16;
    int32_t v32;

    if (0 == this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    if (0 != this->ntype)
    {
        return (this->ntype->get_value_int64_f)(this, pvalue);
    }

    switch (this->type)
    {
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

    *result = (this->ntype != 0 && 0 != this->ntype->new_from_int64_f)
        || (this->ntype == 0 && (this->type == UOT_INT16
            || this->type == UOT_INT32
            || this->type == UOT_INT64)
        ) ? UTRUE : UFALSE;

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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
    this->super.ntype=0;
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
