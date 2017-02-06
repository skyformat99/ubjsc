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
 *  - high precision numbers - ubjs_prmtv_hpn. Internally stored as (char *).
 *
 *    Currently no all-precision manipulation library is employed.
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
#include "ubjs_library.h"

/*! Abstract struct for all ubjson primitives. */
struct ubjs_prmtv;

/*! Struct for array's iterator. */
struct ubjs_array_iterator;

/*! Struct for objects's iterator. */
struct ubjs_object_iterator;

/*! Legal primitive types. */
enum ubjs_prmtv_type
{
    UOT_NULL, /*! null */
    UOT_NOOP, /*! no-op */
    UOT_TRUE, /*! true */
    UOT_FALSE, /*! false */
    UOT_INT8, /*! int8 */
    UOT_UINT8, /*! uint8 */
    UOT_INT16, /*! int16 */
    UOT_INT32, /*! int32 */
    UOT_INT64, /*! int64 */
    UOT_FLOAT32, /*! float32 */
    UOT_FLOAT64, /*! float64 */
    UOT_HPN, /*! high-precision number */
    UOT_CHAR, /*! char */
    UOT_STR, /*! str */
    UOT_ARRAY, /*! array */
    UOT_OBJECT, /*! object */
    UOT_MAX /*! Sentinel value. */
};

/*! Abstract struct for all ubjson primitives. */
typedef struct ubjs_prmtv ubjs_prmtv;

/*! Struct for array's iterator. */
typedef struct ubjs_array_iterator ubjs_array_iterator;

/*! Struct for objects's iterator. */
typedef struct ubjs_object_iterator ubjs_object_iterator;

/*! Legal primitive types. */
typedef enum ubjs_prmtv_type ubjs_prmtv_type;

/*! \brief Returns null primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_null(void);
/*! \brief Checks whether the primitive is a null primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_null(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns no-op primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_noop(void);
/*! \brief Checks whether the primitive is a no-op primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_noop(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns true primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_true(void);
/*! \brief Checks whether the primitive is a true primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_true(ubjs_prmtv *this, ubjs_bool *result);

/*! \brief Returns false primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_prmtv *ubjs_prmtv_false(void);
/*! \brief Checks whether the primitive is a false primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_false(ubjs_prmtv *this, ubjs_bool *result);

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

/*! \brief Returns int8 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int8 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int8(ubjs_library *lib, int8_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is an int8 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int8(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int8 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not an int8, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int8_get(ubjs_prmtv *this, int8_t *pvalue);
/*! \brief Sets the value of the int8 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not an int8, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int8_set(ubjs_prmtv *this, int8_t value);

/*! \brief Returns uint8 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid uint8 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of pthis/lib is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8(ubjs_library *lib, uint8_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is an uint8 primitive.
 *
 * \param this Primitive.
 * \param presult Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_uint8(ubjs_prmtv *this, ubjs_bool *presult);
/*! \brief Gets the value of the uint8 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not an uint8, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *this, uint8_t *pvalue);
/*! \brief Sets the value of the uint8 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not an uint8, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *this, uint8_t value);

/*! \brief Returns int16 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int16 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int16(ubjs_library *lib, int16_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is an int16 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int16(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int16 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not an int16, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *this, int16_t *pvalue);
/*! \brief Sets the value of the int16 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not an int16, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *this, int16_t value);

/*! \brief Returns int32 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int32 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int32(ubjs_library *lib, int32_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is an int32 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int32(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int32 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not an int32, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int32_get(ubjs_prmtv *this, int32_t *pvalue);
/*! \brief Sets the value of the int32 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not an int32, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int32_set(ubjs_prmtv *this, int32_t value);

/*! \brief Returns int64 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid int64 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int64(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is an int64 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_int64(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int8 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not an int64, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int64_get(ubjs_prmtv *this, int64_t *pvalue);
/*! \brief Sets the value of the int64 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not an int64, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_int64_set(ubjs_prmtv *this, int64_t value);

/*! \brief Returns float32 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid float32 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float32(ubjs_library *lib, float32_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is a float32 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_float32(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int32 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not a float32, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float32_get(ubjs_prmtv *this, float32_t *pvalue);
/*! \brief Sets the value of the float32 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not a float32, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float32_set(ubjs_prmtv *this, float32_t value);

/*! \brief Returns float64 primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid float64 primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float64(ubjs_library *lib, float64_t value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is a float64 primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the int64 primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not a float64, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *this, float64_t *pvalue);
/*! \brief Sets the value of the float64 primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not a float64, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *this, float64_t value);

/*! \brief Returns high-precision number primitive for given string.
 *
 * The string does not need to be null terminated. In fact, you must provide its length
 * at first. Only bytes (0..length-1) will make into final primitive.
 *
 * The string is parsed the same as json "number" type.
 * See http://www.json.org/number.gif.
 * If the string does not conform to the format, this method returns UR_ERROR.
 *
 * After this returns UR_OK, *pthis points to a valid str primitive.
 * \param lib Library handle.
 * \param length The length of the original string.
 * \param text Original string.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/text/pthis are 0, or string is invalid number. Else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_hpn(ubjs_library *lib, unsigned int length, char *text,
    ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is a high-precision number primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_hpn(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the high-precision number primitive's string length.
 * \param this Primitive.
 * \param result Pointer to where set the value.
 * \return UR_ERROR if any of this/result is 0, or this is not a hpn, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_hpn_get_length(ubjs_prmtv *this, unsigned int *result);
/*! \brief Copies the high-precision number primitive's string content to provided array.
 *
 * Target array must be preallocated. Before the call, you may want to ubjs_prmtv_str_get_length
 * and allocate the target array.
 * \param this Primitive.
 * \param result Target array.
 * \return UR_ERROR if any of this/result is 0, or this is not a hpn, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_hpn_copy_text(ubjs_prmtv *this, char *result);
/*! \brief Sets the string value of the high-precision number primitive.
 *
 * The string is parsed the same as json "number" type.
 * See http://www.json.org/number.gif.
 * If the string does not conform to the format, this method returns UR_ERROR.
 * \param this Primitive.
 * \param length New length of the string.
 * \param text New string.
 * \return UR_ERROR if of any of this/text is 0, string is invalid number, or this is not a hpn.
 * Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_hpn_set(ubjs_prmtv *this, unsigned int length, char *text);

/*! \brief Returns char primitive for given value.
 *
 * After this returns UR_OK, *pthis points to a valid char primitive.
 * \param lib Library handle.
 * \param value The value.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if lib/pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_char(ubjs_library *lib, char value, ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is a char primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_char(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the value of the char primitive.
 * \param this Primitive.
 * \param pvalue Pointer to where set the value.
 * \return UR_ERROR if any of this/pvalue is 0, or this is not a char, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *this, char *pvalue);
/*! \brief Sets the value of the char primitive.
 * \param this Primitive.
 * \param value New value.
 * \return UR_ERROR if of this is 0, or this is not a char, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *this, char value);

/*! \brief Returns str primitive for given string.
 *
 * The string does not need to be null terminated. In fact, you must provide its length
 * at first. Only bytes (0..length-1) will make into final primitive.
 *
 * After this returns UR_OK, *pthis points to a valid str primitive.
 * \param lib Library handle.
 * \param length The length of the original string.
 * \param text Original string.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/text/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_str(ubjs_library *lib, unsigned int length, char *text,
    ubjs_prmtv **pthis);
/*! \brief Checks whether the primitive is a str primitive.
 *
 * \param this Primitive.
 * \param result Pointer to where set the result - UTRUE/UFALSE.
 * \return UR_ERROR if any of this/result is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_is_str(ubjs_prmtv *this, ubjs_bool *result);
/*! \brief Gets the string primitive's length.
 * \param this Primitive.
 * \param result Pointer to where set the value.
 * \return UR_ERROR if any of this/result is 0, or this is not a str, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *this, unsigned int *result);
/*! \brief Copies the string primitive's content to provided array.
 *
 * Target array must be preallocated. Before the call, you may want to ubjs_prmtv_str_get_length
 * and allocate the target array.
 * \param this Primitive.
 * \param result Target array.
 * \return UR_ERROR if any of this/result is 0, or this is not a str, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *this, char *result);
/*! \brief Sets the value of the string primitive.
 * \param this Primitive.
 * \param length New length of the string.
 * \param text New string.
 * \return UR_ERROR if of any of this/text is 0, or this is not a str, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_str_set(ubjs_prmtv *this, unsigned int length, char *text);

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

/*! \brief Returns array primitive for an empty array, with initial size known and item type.
 *
 * Call this if you know you will add n-items of exactly one type.
 *
 * After this returns UR_OK, *pthis points to a valid array primitive.
 * \param lib Library handle.
 * \param type Item type.
 * \param length Initial length.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_with_length_and_type(ubjs_library *lib,
    ubjs_prmtv_type type, unsigned int length, ubjs_prmtv **pthis);
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
 * If ubjs_array_iterator_next returned UR_ERROR, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *item gets a value.
 * \param this Iterator.
 * \param item Pointer to where put the item.
 * \return UR_ERROR if any of this/item are 0, or previous call to ubjs_array_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this, ubjs_prmtv **item);

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
/*! \brief Returns object primitive for an empty objecty, with initial size known and item type.
 *
 * Call this if you know you will add n-items of exactly one type.
 *
 * After this returns UR_OK, *pthis points to a valid object primitive.
 * \param lib Library handle.
 * \param type Item type.
 * \param length Length.
 * \param pthis Pointer to where put newly created primitive.
 * \return UR_ERROR if any of lib/pthis are 0, else UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object_with_length_and_type(ubjs_library *lib,
    ubjs_prmtv_type type, unsigned int length, ubjs_prmtv **pthis);


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
 * If ubjs_array_iterator_next returned UR_ERROR, this will also return UR_ERROR.
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
 * If ubjs_array_iterator_next returned UR_ERROR, this will also return UR_ERROR.
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
 * If ubjs_array_iterator_next returned UR_ERROR, this will also return UR_ERROR.
 * Else after this method returns UR_OK, and *pvalue gets a value.
 * \param this Iterator.
 * \param pvalue Pointer to where put value.
 * \return UR_ERROR if any of this/plen are 0, or previous call to ubjs_object_iterator_next
 * returned UR_ERROR. Else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this,
    ubjs_prmtv **pvalue);

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

/*! \brief Calculates the length of would-be-serialized debug string for the primitive.
 * After this returns UR_OK, *this gets a malloc()-d null-terminated string.
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
