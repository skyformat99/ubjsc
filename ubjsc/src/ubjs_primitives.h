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
/*! \file
 *  \brief Wrappers over ubjson primitive types.
 *
 *  Ubjson defines a number of types and they all are wrapped over an umbrella
 *  ubjs_prmtv structure.
 *
 *  Common operations:
 *
 *  - construction.
 *
 *    For "valued" types, especially containers, ubjs_prmtv_<type> construct new structs.
 *
 *    For integer values, there is also a helper ubjs_prmtv_int that decides the type
 *    of final wrapper in runtime, depending on the value. This ensures that the least memory
 *    is taken for the wrapper.
 *
 *  - deconstruction.
 *
 *    Call ubjs_prmtv_free(&value). This works on all types, both valueless and "valued".
 *
 *  - checking type
 *
 *    ubjs_prmtv_get_type returns the wrapper's type. Also each type has its own
 *    ubjs_prmtv_is_<type> method.
 *
 *    This applies also to ubjs_prmtv_is_int that returns UTRUE when the wrapper is of
 *    any int type.
 *
 *  - getters/setters
 *
 *    Most valued types has its own ubjs_prmtv_<type>_get and ubjs_prmtv_<type>_set methods.
 *
 *    String, array and object wrappers also have ubjs_prmtv_<type>_get_length methods for getting
 *    the number of items (or, in case of str, characters) in the value.
 *
 *  - manipulating container's content
 *
 *    Strings are mutable. Arrays have methods for inserting, getting and
 *    removing items, and same for objects.
 *
 *  - iterating over container
 *
 *    Array and object have their own iterators. Arrays are iterated from front (from 0
 *    to ubjs_array_get_length() - 1), objects are iterated in-order (from the lowest key
 *    to the highest).
 *
 *  Types supported:
 *
 *  - array - ubjs_prmtv_array.
 *
 *    This is stored internally as an... array of pointers to items. Its real size is maintained
 *    using something similar to exponential backoff algorithm. The real size is expanded and
 *    shrunk on demand. The items are **NOT** stored in single memory block, and for now this is
 *    true even though we have implemented count and typed optimizations of containers.
 *
 *  - object - ubjs_prmtv_object.
 *
 *    This is stored internally as a patricia trie, by in-house library. I know, another reinvented
 *    wheel in this world... But so far it works great. The items are **NOT** stored in single
 *    memory block, and for now this is true even though we have implemented count and typed
 *    optimizations of containers.
 *
 * \since 0.2
 */

#ifndef HAVE_UBJS_PRIMITIVES
#define HAVE_UBJS_PRIMITIVES

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_library.h>

/*! Abstract struct for all ubjson primitives. */
struct ubjs_prmtv;

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype;

/*! Struct for array's iterator. */
struct ubjs_array_iterator;

/*! Struct for objects's iterator. */
struct ubjs_object_iterator;

/*! Abstract struct for all ubjson primitives. */
typedef struct ubjs_prmtv ubjs_prmtv;

/*!
 * \since 0.7
 */
typedef struct ubjs_prmtv_ntype ubjs_prmtv_ntype;

/*! Struct for array's iterator. */
typedef struct ubjs_array_iterator ubjs_array_iterator;

/*! Struct for objects's iterator. */
typedef struct ubjs_object_iterator ubjs_object_iterator;

/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_parser_glue ubjs_prmtv_ntype_parser_glue;
/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_parser_processor ubjs_prmtv_ntype_parser_processor;

/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_writer_glue ubjs_prmtv_ntype_writer_glue;
/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_writer ubjs_prmtv_ntype_writer;

/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_printer_glue ubjs_prmtv_ntype_printer_glue;
/*!
 * /since 0.7
 */
typedef struct ubjs_prmtv_ntype_printer ubjs_prmtv_ntype_printer;

/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_new_from_int64_f)(ubjs_library *, int64_t, ubjs_prmtv **);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_free_f)(ubjs_prmtv **);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_debug_string_get_length_f)(ubjs_prmtv *, unsigned int *);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_debug_string_copy_f)(ubjs_prmtv *, char *);

/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_get_value_int64_f)(ubjs_prmtv *, int64_t *);

/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_parser_processor_new_f)(ubjs_library *,
     ubjs_prmtv_ntype_parser_glue *, ubjs_prmtv_ntype_parser_processor **);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_parser_processor_free_f)(
    ubjs_prmtv_ntype_parser_processor **);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_processor_got_child_f)
    (ubjs_prmtv_ntype_parser_processor *, ubjs_prmtv *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_processor_got_marker_f)
    (ubjs_prmtv_ntype_parser_processor *, ubjs_prmtv_ntype *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_processor_got_control_f)
    (ubjs_prmtv_ntype_parser_processor *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_processor_read_byte_f)
    (ubjs_prmtv_ntype_parser_processor *, uint8_t);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_glue_return_control_f)(ubjs_prmtv_ntype_parser_glue *,
    void *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_glue_want_marker_f)(ubjs_prmtv_ntype_parser_glue *,
    ubjs_glue_array *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_glue_want_child_f)(ubjs_prmtv_ntype_parser_glue *,
    ubjs_prmtv_ntype *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_glue_debug_f)(ubjs_prmtv_ntype_parser_glue *,
    unsigned int, char *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_parser_glue_error_f)(ubjs_prmtv_ntype_parser_glue *,
    unsigned int, char *);

/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_writer_new_f)(ubjs_library *,
    ubjs_prmtv_ntype_writer_glue *, ubjs_prmtv_ntype_writer **);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_writer_free_f)(ubjs_prmtv_ntype_writer **);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_writer_get_length_f)(ubjs_prmtv_ntype_writer *,
    unsigned int *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_writer_do_f)(ubjs_prmtv_ntype_writer *, uint8_t *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_writer_glue_debug_f)(ubjs_prmtv_ntype_writer_glue *,
    unsigned int, char *);

/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_printer_new_f)(ubjs_library *,
    ubjs_prmtv_ntype_printer_glue *, ubjs_prmtv_ntype_printer **);
/*!
 * /since 0.7
 */
typedef ubjs_result (*ubjs_prmtv_ntype_printer_free_f)(ubjs_prmtv_ntype_printer **);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_printer_get_length_f)(ubjs_prmtv_ntype_printer *,
    unsigned int *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_printer_do_f)(ubjs_prmtv_ntype_printer *, char *);
/*!
 * /since 0.7
 */
typedef void (*ubjs_prmtv_ntype_printer_glue_debug_f)(ubjs_prmtv_ntype_printer_glue *,
    unsigned int, char *);

/*!
 * /since 0.7
 */
struct ubjs_prmtv
{
    ubjs_library *lib;
    ubjs_prmtv_ntype *ntype;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype
{
    uint8_t marker;

    ubjs_prmtv_ntype_free_f free_f;

    ubjs_prmtv_ntype_new_from_int64_f new_from_int64_f;
    ubjs_prmtv_ntype_get_value_int64_f get_value_int64_f;

    ubjs_prmtv_ntype_debug_string_get_length_f debug_string_get_length_f;
    ubjs_prmtv_ntype_debug_string_copy_f debug_string_copy_f;

    ubjs_prmtv_ntype_parser_processor_new_f parser_processor_new_f;
    ubjs_prmtv_ntype_parser_processor_free_f parser_processor_free_f;

    ubjs_prmtv_ntype_parser_processor_got_child_f parser_processor_got_child_f;
    ubjs_prmtv_ntype_parser_processor_got_marker_f parser_processor_got_marker_f;
    ubjs_prmtv_ntype_parser_processor_got_control_f parser_processor_got_control_f;

    ubjs_prmtv_ntype_parser_processor_read_byte_f parser_processor_read_byte_f;

    ubjs_prmtv_ntype_writer_new_f writer_new_f;
    ubjs_prmtv_ntype_writer_free_f writer_free_f;
    ubjs_prmtv_ntype_writer_get_length_f writer_get_length_f;
    ubjs_prmtv_ntype_writer_do_f writer_do_f;

    ubjs_prmtv_ntype_printer_new_f printer_new_f;
    ubjs_prmtv_ntype_printer_free_f printer_free_f;
    ubjs_prmtv_ntype_printer_get_length_f printer_get_length_f;
    ubjs_prmtv_ntype_printer_do_f printer_do_f;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_parser_processor
{
    ubjs_library *lib;
    ubjs_prmtv_ntype *ntype;
    char *name;
    ubjs_prmtv_ntype_parser_glue *glue;
    void *userdata;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_parser_glue
{
    void *userdata;
    void *parent;

    ubjs_prmtv_ntype_parser_glue_return_control_f return_control_f;
    ubjs_prmtv_ntype_parser_glue_want_marker_f want_marker_f;
    ubjs_prmtv_ntype_parser_glue_want_child_f want_child_f;
    ubjs_prmtv_ntype_parser_glue_debug_f debug_f;
    ubjs_prmtv_ntype_parser_glue_error_f error_f;

    unsigned int limit_container_length;
    unsigned int limit_string_length;
    unsigned int limit_recursion_level;

    unsigned int recursion_level;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_writer
{
    ubjs_library *lib;
    ubjs_prmtv *prmtv;
    ubjs_prmtv_ntype *ntype;
    char *name;
    ubjs_prmtv_ntype_writer_glue *glue;
    void *userdata;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_writer_glue
{
    void *userdata;
    ubjs_prmtv *prmtv;

    ubjs_prmtv_ntype_writer_glue_debug_f debug_f;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_printer
{
    ubjs_library *lib;
    ubjs_prmtv_ntype *ntype;
    ubjs_prmtv *prmtv;
    ubjs_prmtv_ntype_printer_glue *glue;
    char *name;
    void *userdata;
};

/*!
 * /since 0.7
 */
struct ubjs_prmtv_ntype_printer_glue
{
    void *userdata;
    ubjs_prmtv *prmtv;
    unsigned int indent;

    ubjs_prmtv_ntype_printer_glue_debug_f debug_f;
};

/*! \brief Returns the best int primitive wrapping given value.
 *
 * After this returns UR_OK, *pthis points to a valid (u)int8/int16/int32/int64 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis);
/*! \brief Returns the best unsigned int primitive wrapping given value.
 *
 * After this returns UR_OK, *pthis points to a valid uint8/int16/int32/int64 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if lib is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis);
/*! \brief Gets the value of the integer primitive, regardless of its type.
 *
 * Recognized primitive types are (u)int8/int16/int32/int64.
 * The output value is upcasted to int64_t.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue);

/*!
 * \since 0.7
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_get_ntype(ubjs_prmtv *this, ubjs_prmtv_ntype **pntype);

/*! \brief Calculates the length of would-be-serialized debug string for the primitive.
 * After this returns UR_OK, *this gets a dynamically allocated null-terminated string.
 * \param this Existing primitive.
 * \param plen Pointer to where put debug string's length.
 * \return UR_ERROR if any of this/pstr is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen);

/*! \brief Serializes the primitive and copies the debug string to provided array.
 *
 * Target array must be preallocated. Before the call, you may want to
 * ubjs_prmtv_debug_string_get_length and allocate the target array.
 * \param this Existing primitive.
 * \param str Pointer to where put debug string.
 * \return UR_ERROR if any of this/str is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_debug_string_copy(ubjs_prmtv *this, char *str);

/*! \brief Frees the primitive.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing primitive.
 * \return UR_ERROR if any of pthis / *pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_free(ubjs_prmtv **pthis);

#ifdef __cplusplus
}
#endif

#endif
