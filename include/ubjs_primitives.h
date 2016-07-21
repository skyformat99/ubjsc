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
 *    For non-value types (null, no-op, true, false), ubjs_prmtv_<type>
 *    return singletons.
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
 *  - null - ubjs_prmtv_null returns a singleton.
 *  - no-op - ubjs_prmtv_noop returns a singleton.
 *
 *    ubjson.org says that "when parsed by the receiver, the no-op values are simply skipped
 *    and carry know meaningful value with them.". I've decided to leave this to the user
 *    and because of that, no-ops are parsed always and passed to the user.
 *
 *    For ubjsc these two arrays are NOT equal on the parse/write level:
 *
 *    - ["foo", "bar", "baz"]
 *    - ["foo", no-op, "bar", no-op, no-op, no-op, "baz", no-op, no-op]
 *
 *  - true - ubjs_prmtv_true.
 *  - false - ubjs_prmtv_true.
 *  - int8 - ubjs_prmtv_int8.
 *  - uint8 - ubjs_prmtv_uint8.
 *  - int16 - ubjs_prmtv_int16.
 *  - int32 - ubjs_prmtv_int32.
 *  - int64 - ubjs_prmtv_int64.
 *  - float32 - ubjs_prmtv_float32.
 *  - float64 - ubjs_prmtv_float64.
 *  - char - ubjs_prmtv_char. From 0 up to 127.
 *  - string - ubjs_prmtv_str. Internally stored as (char *).
 *
 *    Supported length markers: uint8, int8 (only parsing), int16, int32.
 *    Theoretically int64 will work too, but due to lack of example (who would like a 13TB string?)
 *    this is not not tested.
 *    When writing, the best length marker is choosen during runtime.
 *
 *  High-precision numbers are **NOT** supported.
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

#include "ubjs_common.h"

struct ubjs_prmtv;
struct ubjs_array_iterator;
struct ubjs_object_iterator;

/*!< Abstract struct for all ubjson primitives. */
typedef struct ubjs_prmtv ubjs_prmtv;
/*!< Struct for array's iterator. */
typedef struct ubjs_array_iterator ubjs_array_iterator;
/*!< Struct for objects's iterator. */
typedef struct ubjs_object_iterator ubjs_object_iterator;

/*!< Legal primitive types. */
typedef enum ubjs_prmtv_type
{
    UOT_NULL, /*!< null */
    UOT_NOOP, /*!< no-op */
    UOT_TRUE, /*!< true */
    UOT_FALSE, /*!< false */
    UOT_INT8, /*!< int8 */
    UOT_UINT8, /*!< uint8 */
    UOT_INT16, /*!< int16 */
    UOT_INT32, /*!< int32 */
    UOT_INT64, /*!< int64 */
    UOT_FLOAT32, /*!< float32 */
    UOT_FLOAT64, /*!< float64 */
    UOT_CHAR, /*!< char */
    UOT_STR, /*!< str */
    UOT_ARRAY, /*!< array */
    UOT_OBJECT, /*!< object */
    UOT_MAX /*!< Sentinel value. */
} ubjs_prmtv_type;

/*! \brief Returns null primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_null();
/*! \brief Checks whether the primitive is a null primitive.
 *
 * \param result Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_null(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns no-op primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_noop();
/*! \brief Checks whether the primitive is a no-op primitive.
 *
 * \param result Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_noop(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns true primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_true();
/*! \brief Checks whether the primitive is a true primitive.
 *
 * \param result Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_true(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns false primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_false();
/*! \brief Checks whether the primitive is a false primitive.
 *
 * \param result Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_false(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns the best int primitive wrapping given value.
 *
 * After this returns UR_OK, *pthis points to a valid (u)int8/int16/int32/int64 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int(int64_t value, ubjs_prmtv **pthis);
/*! \brief Returns the best unsigned int primitive wrapping given value.
 *
 * After this returns UR_OK, *pthis points to a valid uint8/int16/int32/int64 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if universe exploded, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint(int64_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is any integer primitive.
 *
 * Any integer primitive means (u)int8/int16/int32/int64.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the integer primitive, regardless of its type.
 *
 * Recognized primitive types are (u)int8/int16/int32/int64.
 * The output value is upcasted to int64_t.
 * \param result Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue);

/*! \brief Returns int8 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int8 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int8(int8_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int8(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int8_get(ubjs_prmtv *, int8_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int8_set(ubjs_prmtv *, int8_t);

/*! \brief Returns uint8 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid uint8 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8(uint8_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_uint8(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *, uint8_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *, uint8_t);

/*! \brief Returns int16 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int16 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int16(int16_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int16(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *, int16_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *, int16_t);

/*! \brief Returns int32 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int32 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int32(int32_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int32(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int32_get(ubjs_prmtv *, int32_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int32_set(ubjs_prmtv *, int32_t);

/*! \brief Returns int64 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int64 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int64(int64_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int64(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int64_get(ubjs_prmtv *, int64_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_int64_set(ubjs_prmtv *, int64_t);

/*! \brief Returns float32 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid float32 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float32(float32_t value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_float32(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_float32_get(ubjs_prmtv *, float32_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_float32_set(ubjs_prmtv *, float32_t);

/*! \brief Returns float64 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid float64 primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float64(float64_t, ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *, float64_t *);
UBJS_EXPORT ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *, float64_t);

/*! \brief Returns char primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid char primitive.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_char(char value, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_char(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *, char *);
UBJS_EXPORT ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *, char);

/*! \brief Returns str primitive for given string.
 *
 * The string does not need to be null terminated. In fact, you must provide its length
 * at first. Only bytes (0..length-1) will make into final primitive.
 *
 * After this returns UR_OK, *pthis points to a valid str primitive.
 * \param length The length of the original string.
 * \param text Original string.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of text/pthis are 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_str(unsigned int length, char *text, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_str(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *, unsigned int *);
UBJS_EXPORT ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *, char *);
UBJS_EXPORT ubjs_result ubjs_prmtv_str_set(ubjs_prmtv *, unsigned int, char *);

/*! \brief Returns array primitive for an empty array.
 *
 * After this returns UR_OK, *pthis points to a valid array primitive.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of pthis are 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array(ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_array(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *, unsigned int *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *, ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *, ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *, unsigned int, ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *, ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *, ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *, unsigned int, ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *, unsigned int);

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
UBJS_EXPORT ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *);
UBJS_EXPORT ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *, ubjs_prmtv **);

/*! \brief Returns object primitive for an empty object.
 *
 * After this returns UR_OK, *pthis points to a valid object primitive.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of pthis are 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object(ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_is_object(ubjs_prmtv *, ubjs_bool *);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *, unsigned int *);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *, unsigned int, char *, ubjs_prmtv **);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *, unsigned int, char *, ubjs_prmtv *);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *, unsigned int, char *);

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
UBJS_EXPORT ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *, ubjs_object_iterator **);
UBJS_EXPORT ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *);
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *, unsigned int *);
UBJS_EXPORT ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *, char *);
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *, ubjs_prmtv **);

/*! \brief Frees the iterator.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing iterator.
 * \return UR_ERROR if any of pthis/*pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_free(ubjs_array_iterator **pthis);
/*! \brief Frees the iterator.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing iterator.
 * \return UR_ERROR if any of pthis/*pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **pthis);

/*! \brief Gets the primitive's type.
 * After this returns UR_OK, *ptype has a value.
 * \param this Existing primitive.
 * \return UR_ERROR if any of this/ptype is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_get_type(ubjs_prmtv *this, ubjs_prmtv_type *ptype);
/*! \brief Frees the primitive.
 * After this returns UR_OK, *pthis is equal to 0.
 * \param pthis Pointer to existing primitive.
 * \return UR_ERROR if any of pthis/*pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_free(ubjs_prmtv **pthis);

#ifdef __cplusplus
}
#endif

#endif
