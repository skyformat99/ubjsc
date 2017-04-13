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
#ifndef HAVE_UBJS_PRIMITIVES_PRV
#define HAVE_UBJS_PRIMITIVES_PRV

#include <ubjs_primitives.h>

typedef struct ubjs_int32 ubjs_int32;
typedef struct ubjs_int64 ubjs_int64;
typedef struct ubjs_float32 ubjs_float32;
typedef struct ubjs_float64 ubjs_float64;
typedef struct ubjs_char ubjs_char;
typedef struct ubjs_str ubjs_str;
typedef struct ubjs_hpn ubjs_hpn;
typedef struct ubjs_array ubjs_array;
typedef struct ubjs_object ubjs_object;

UBJS_NO_EXPORT extern unsigned int ubjs_prmtv_ntypes_len;
UBJS_NO_EXPORT extern ubjs_prmtv_ntype *ubjs_prmtv_ntypes[];

struct ubjs_int32
{
    ubjs_prmtv super;
    int32_t value;
};

struct ubjs_int64
{
    ubjs_prmtv super;
    int64_t value;
};

struct ubjs_float32
{
    ubjs_prmtv super;
    float32_t value;
};

struct ubjs_float64
{
    ubjs_prmtv super;
    float64_t value;
};

struct ubjs_char
{
    ubjs_prmtv super;
    char value;
};

struct ubjs_str
{
    ubjs_prmtv super;
    unsigned int length;
    char *text;
};

struct ubjs_hpn
{
    ubjs_prmtv super;
    unsigned int length;
    char *text;
};

struct ubjs_array
{
    ubjs_prmtv super;
    ubjs_glue_array *glue;
};

struct ubjs_object
{
    ubjs_prmtv super;
    ubjs_glue_dict *glue;
};

UBJS_NO_EXPORT void ubjs_prmtv_glue_item_free(void *);

struct ubjs_array_iterator
{
    ubjs_array *array;
    ubjs_glue_array_iterator *glue;
};

struct ubjs_object_iterator
{
    ubjs_object *object;
    ubjs_glue_dict_iterator *glue;
};

enum ubjs_prmtv_is_valid_hpn_state
{
    PMIVHS_BEGIN,
    PMIVHS_AFTER_MINUS,
    PMIVHS_AFTER_DIGIT,
    PMIVHS_AFTER_DIGITS,
    PMIVHS_AFTER_DOT_BEFORE_DIGITS,
    PMIVHS_AFTER_NUMBER,
    PMIVHS_AFTER_E,
    PMIVHS_AFTER_E_PLUS_MINUS,
    PMIVHS_AFTER_E_DIGIT,
    PMIVHS_END
};

typedef ubjs_result (*ubjs_prmtv_is_valid_hpn_state_processor_f)(char,
    enum ubjs_prmtv_is_valid_hpn_state *);

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_begin(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_minus(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_digit(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_digits(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_dot_before_digits(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_number(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e_plus_minus(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_e_digit(char,
    enum ubjs_prmtv_is_valid_hpn_state *);
UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn_state_processor_after_end(char,
    enum ubjs_prmtv_is_valid_hpn_state *);

extern unsigned int \
    ubjs_prmtv_is_valid_hpn_state_processor_matrix_length;
extern ubjs_prmtv_is_valid_hpn_state_processor_f \
    ubjs_prmtv_is_valid_hpn_state_processor_matrix[];

UBJS_NO_EXPORT ubjs_result ubjs_prmtv_is_valid_hpn(unsigned int, char *, ubjs_bool *);

#endif
/* \endinternal */
