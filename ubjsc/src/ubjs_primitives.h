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

/*! Legal primitive types. */
enum ubjs_prmtv_type
{
    UOT_ARRAY, /*! array */
    UOT_OBJECT, /*! object */
    UOT_MAX /*! Sentinel value. */
};

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

/*! Legal primitive types. */
typedef enum ubjs_prmtv_type ubjs_prmtv_type;

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
typedef void (*ubjs_prmtv_ntype_parser_processor_got_present_f)
    (ubjs_prmtv_ntype_parser_processor *, ubjs_prmtv *);
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
typedef void (*ubjs_prmtv_ntype_parser_glue_want_number_f)(ubjs_prmtv_ntype_parser_glue *);
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
    ubjs_prmtv_type type;
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

    ubjs_prmtv_ntype_parser_processor_got_present_f parser_processor_got_present_f;
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
    ubjs_prmtv_ntype_parser_glue_want_number_f want_number_f;
    ubjs_prmtv_ntype_parser_glue_debug_f debug_f;
    ubjs_prmtv_ntype_parser_glue_error_f error_f;

    unsigned int limit_container_length;
    unsigned int limit_string_length;
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
/*! \brief Checks whether the primitive is any integer primitive.
 *
 * Any integer primitive means (u)int8/int16/int32/int64.
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the integer primitive, regardless of its type.
 *
 * Recognized primitive types are (u)int8/int16/int32/int64.
 * The output value is upcasted to int64_t.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue);

/*! \brief Returns array primitive for an empty array.
 *
 * After this returns UR_OK, *pthis points to a valid array primitive.
 * \param lib Library handle.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array(ubjs_library *lib, ubjs_prmtv **pthis);

/*! \brief Returns array primitive for an empty array, with initial size known.
 *
 * Call this if you know you will add n-items.
 *
 * After this returns UR_OK, *pthis points to a valid array primitive.
 * \param lib Library handle.
 * \param length Initial length.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis);

/*! \brief Checks whether the primitive is an array primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the array primitive's length.
 * \param this Primitive.
 * \param length Pointer to where set the value.
 * \return UR_ERROR if any of this/result is 0, or this is not an array, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this, unsigned int *length);
/*! \brief Gets reference to first item of the array primitive.
*
 * This is the internal reference to an item and must not be ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param pitem Pointer to where set the item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or array is empty.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this, ubjs_prmtv **pitem);
/*! \brief Gets reference to last item of the array primitive.
 *
 * This is the internal reference to an item and must not be ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param pitem Pointer to where set the item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or array is empty.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this, ubjs_prmtv **pitem);
/*! \brief Gets reference to n-th item of the array primitive.
 *
 * This is the internal reference to an item and must not be ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param pos Position of the item. Must be within 0..(ubjs_prmtv_array_get_length - 1).
 * \param pitem Pointer to where set the item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or pos is not within
 * range 0..(ubjs_prmtv_array_get_length - 1). Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this, unsigned int pos,
    ubjs_prmtv **pitem);
/*! \brief Inserts an item into array primitive as a first one.
 *
 * This means that the existing first item becomes the second.
 * What happens when iterating over the array during adding items - this is undefined behavior.
 * \param this Primitive.
 * \param item New item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this, ubjs_prmtv *item);
/*! \brief Inserts an item into array primitive as a last one.
 *
 * This means that the existing last item becomes the second-last.
 * What happens when iterating over the array during adding items - this is undefined behavior.
 * \param this Primitive.
 * \param item New item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this, ubjs_prmtv *item);
/*! \brief Inserts an item into array primitive before an existing n-th one.
 *
 * This means that existing n-th item will become (n + 1)-th.
 * pos == 0 is the same as ubjs_prmtv_array_add_first.
 * pos == ubjs_prmtv_array_get_length is the same as ubjs_prmtv_array_add_last.
 * What happens when iterating over the array during adding items - this is undefined behavior.
 * \param this Primitive.
 * \param pos Position of the item. Must be within 0..(ubjs_prmtv_array_get_length).
 * \param item New item.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or pos is not within
 * range 0..(ubjs_prmtv_array_get_length). Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this, unsigned int pos,
    ubjs_prmtv *item);
/*! \brief Deletes the first item from array primitive.
 *
 * This means that the existing second item becomes the first.
 * What happens when iterating over the array during deleting items - this is undefined behavior.
 *
 * The item does get ubjs_prmtv_free-d.
 * \param this Primitive.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or the array is empty.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this);
/*! \brief Deletes the last item from array primitive.
 *
 * This means that the existing second-last item becomes the last.
 * What happens when iterating over the array during deleting items - this is undefined behavior.
 *
 * The item does get ubjs_prmtv_free-d.
 * \param this Primitive.
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or the array is empty.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this);
/*! \brief Deletes the n-th item from array primitive.
 *
 * This means that the (n + 1)-th item becomes the n-th.
 * What happens when iterating over the array during deleting items - this is undefined behavior.
 *
 * The item does get ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param pos Position of the item. Must be within 0..(ubjs_prmtv_array_get_length - 1).
 * \return UR_ERROR if any of this/pitem is 0, this is not an array, or pos is not within
 * range 0..(ubjs_prmtv_array_get_length - 1). Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this, unsigned int pos);

/*! \brief Returns iterator over this array.
 *
 * The array must exist thru the life of the iterator. If you ubjs_prmtv_free the array
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * After this returns UR_OK, *pthis points to new iterator. First call to ubjs_array_iterator_next
 * will point to 0-th item.
 * \param this Existing array primitive.
 * \param iterator Pointer to where put newly created iterator.
 * \return UR_ERROR if any of this/iterator are 0, or this is not an array. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this, ubjs_array_iterator **iterator);
/*! \brief Tries to advance the array iterator.
 *
 * The array must exist thru the life of the iterator. If you ubjs_prmtv_free the array
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If this returns UR_OK, you can safely call ubjs_array_iterator_get to get the item
 * at this position.
 * \param this Iterator.
 * \return UR_ERROR if iterator are 0, or the iterator would go beyond the array's bounds.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this);
/*! \brief Gets the item from the array iterator.
 *
 * The array must exist thru the life of the iterator. If you ubjs_prmtv_free the array
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_array_iterator_delete was done
 * before on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *item gets a value.
 * \param this Iterator.
 * \param item Pointer to where put the item.
 * \return UR_ERROR if any of this/item are 0, or previous call to ubjs_array_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this, ubjs_prmtv **item);
/*! \brief Deletes the item under array iterator.
 *
 * The array must exist thru the life of the iterator. If you ubjs_prmtv_free the array
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_array_iterator_delete was done
 * before on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *item gets a value.
 * \param this Iterator.
 * \return UR_ERROR if any of this/item are 0, or previous call to ubjs_array_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_delete(ubjs_array_iterator *this);

/*! \brief Returns object primitive for an empty object.
 *
 * After this returns UR_OK, *pthis points to a valid object primitive.
 * \param lib Library handle.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object(ubjs_library *lib, ubjs_prmtv **pthis);

/*! \brief Returns object primitive for an empty object, with initial size known.
 *
 * Call this if you know you will add n-items.
 *
 * After this returns UR_OK, *pthis points to a valid object primitive.
 * \param lib Library handle.
 * \param length Initial length.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis);

/*! \brief Checks whether the primitive is an object primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the object primitive's length.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/result is 0, or this is not an object, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this, unsigned int *pvalue);
/*! \brief Gets the value for specified key.
 * \param this Primitive.
 * \param key_length Length of the key.
 * \param key Key.
 * \param pvalue Pointer to where put the value.
 * \return UR_ERROR if any of this/key/pvalue is 0, this is not an object, or there is no
 * such key in object. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this, unsigned int key_length,
    char *key, ubjs_prmtv **pvalue);
/*! \brief Sets the value for specified key.
 *
 * If there already exists such key in object, its value gets ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param key_length Length of the key.
 * \param key Key.
 * \param value New value.
 * \return UR_ERROR if any of this/key is 0, this is not an object. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this, unsigned int key_length,
    char *key, ubjs_prmtv *value);
/*! \brief Deletes the value for specified key.
 *
 * The value gets ubjs_prmtv_free-d.
 * \param this Primitive.
 * \param key_length Length of the key.
 * \param key Key.
 * \return UR_ERROR if any of this/key is 0, this is not an object, or there is no
 * such key in object. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this, unsigned int key_length,
    char *key);

/*! \brief Returns iterator over this object.
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_object_iterator_free, behavior is undefined.
 *
 * After this returns UR_OK, *pthis points to new iterator. First call to ubjs_object_iterator_next
 * will point to 0-th item.
 * \param this Existing object primitive.
 * \param iterator Pointer to where put newly created iterator.
 * \return UR_ERROR if any of this/iterator are 0, or this is not an object. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this,
    ubjs_object_iterator **iterator);
/*! \brief Tries to advance the object iterator.
 *
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If this returns UR_OK, you can safely call ubjs_object_iterator_get to get the item
 * at this position.
 * \param this Iterator.
 * \return UR_ERROR if iterator are 0, or the iterator would go beyond the object's bounds.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this);
/*! \brief Gets the key's length from the object iterator.
 *
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_object_iterator_get_value was done
 * on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *plen gets a value.
 * \param this Iterator.
 * \param plen Pointer to where put key's length.
 * \return UR_ERROR if any of this/plen are 0, or previous call to ubjs_object_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this,
    unsigned int *plen);
/*! \brief Copies the key from the object iterator to provided array.
 *
 * Target array must be preallocated. Before the call, you may want to ubjs_prmtv_str_get_length
 * and allocate the target array.
 *
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_object_iterator_get_value was done
 * on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *text gets a value.
 * \param this Iterator.
 * \param text Target array.
 * \return UR_ERROR if any of this/text are 0, or previous call to ubjs_object_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *text);

/*! \brief Gets the value from the object iterator.
 *
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_object_iterator_get_value was done
 * on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *pvalue gets a value.
 * \param this Iterator.
 * \param pvalue Pointer to where put value.
 * \return UR_ERROR if any of this/plen are 0, or previous call to ubjs_object_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this,
    ubjs_prmtv **pvalue);
/*! \brief Deletes the item under the object iterator.
 *
 * The object must exist thru the life of the iterator. If you ubjs_prmtv_free the object
 * before you ubjs_array_iterator_free, behavior is undefined.
 *
 * If ubjs_array_iterator_next returned UR_ERROR, or ubjs_object_iterator_get_value was done
 * on this item, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *pvalue gets a value.
 * \param this Iterator.
 * \return UR_ERROR if any of this/plen are 0, or previous call to ubjs_object_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_delete(ubjs_object_iterator *this);

/*! \brief Frees the iterator.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing iterator.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis);

/*! \brief Frees the iterator.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing iterator.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **pthis);

/*! \brief Gets the primitive's type.
 * After this returns UR_OK, *ptype has a value.
 * \param this Existing primitive.
 * \param ptype Pointer to where put primitive's type.
 * \return UR_ERROR if any of this/ptype is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_get_type(ubjs_prmtv *this, ubjs_prmtv_type *ptype);

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
