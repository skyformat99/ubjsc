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
 *  \brief Definitions of common types, ubjson markers and some utilities.
 *
 * \since 0.2
 */
 
#ifndef HAVE_UBJS_LIBRARY
#define HAVE_UBJS_LIBRARY

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_common.h>

/*! \brief Allocation functor.
 *
 * This roughly follows the prototype for malloc().
 *  \param len Length.
 *  \return Allocated pointer.
 *
 * \since 0.4
 */
typedef void *(*ubjs_library_alloc_f)(unsigned int len);

/*! \brief Deallocation functor.
 *
 * This roughly follows the prototype for free().
 *  \param ptr Allocated pointer.
 *
 * \since 0.4
 */
typedef void (*ubjs_library_free_f)(void *ptr);

/*! \brief Library handle.
 *
 * \since 0.4
 */
typedef struct ubjs_library ubjs_library;

/*! \brief Glue to dictionary.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_dict ubjs_glue_dict;

/*! \brief Glue to dictionary iterator.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_dict_iterator ubjs_glue_dict_iterator;

/*! \brief Library handle.
 *
 * \since 0.4
 */
struct ubjs_library;

/*! \brief Callback that frees the value held in an object.
 * Note that this is a generic callback, not related to actual
 * ubjs_prmtv_object()-s.
 * \param pvalue Pointer to value to be freed.
 * \since 0.5
 */
typedef void (*ubjs_glue_value_free)(void *pvalue);

/*! \brief Callback that creates a new dictionary glue.
 * \param lib Library handle.
 * \param vfree Value free callback.
 * \param pthis Pointer to where put new glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_factory)(ubjs_library *lib, ubjs_glue_value_free vfree,
    ubjs_glue_dict **pthis);

/*! \brief Frees the dictionary glue.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *
 * \param pthis Pointer to where glue is.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_free)(ubjs_glue_dict **);

/*! \brief Gets the length of the dictionary under a glue
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the length.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_get_length)(ubjs_glue_dict *this, unsigned int *pvalue);

/*! \brief Gets the value under a key.
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the value.
 *
 * \param this Glue.
 * \param key_length Key length.
 * \param key Key.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_get)(ubjs_glue_dict *this, unsigned int key_length,
    char *key, void **pvalue);

/*! \brief Sets the value under a key.
 *
 * \param this Glue.
 * \param key_length Key length.
 * \param key Key.
 * \param value Value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_set)(ubjs_glue_dict *this, unsigned int key_length,
    char *key, void *value);

/*! \brief Deletes a key, with its value.
 *
 * \param this Glue.
 * \param key_length Key length.
 * \param key Key.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_delete)(ubjs_glue_dict *this, unsigned int key_length,
    char *key);

/*! \brief Creates an iterator over glued dictionary.
 *
 * \param this Glue.
 * \param piterator Pointer to where put iterator.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterate)(ubjs_glue_dict *this,
    ubjs_glue_dict_iterator **piterator);

/*! \brief Tries to iterate to next item.
 *
 * \param this Glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterator_next)(ubjs_glue_dict_iterator *this);

/*! \brief Gets current key's length.
 *
 * \param this Glue.
 * \param plen Pointer to where put key's length.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterator_get_key_length)(ubjs_glue_dict_iterator *this,
    unsigned int *plen);

/*! \brief Copies the key to specified array.
 *
 * \param this Glue.
 * \param text Allocated array.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterator_copy_key)(ubjs_glue_dict_iterator *this, char *text);

/*! \brief Gets current value.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put the value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterator_get_value)(ubjs_glue_dict_iterator *this,
    void **pvalue);

/*! \brief Frees the dictionary iterator glue.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *
 * \param pthis Pointer to where glue is.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_iterator_free)(ubjs_glue_dict_iterator **pthis);

/*! \brief Glue to object.
 *
 * \since 0.5
 */
struct ubjs_glue_dict
{
    /*! Library. */
    ubjs_library *lib;

    /*! Userdata, possibly with actual implementation. */
    void *userdata;

    /*! Free callback */
    ubjs_glue_dict_free free_f;

    /*! Get length callback. */
    ubjs_glue_dict_get_length get_length_f;

    /*! Get callback. */
    ubjs_glue_dict_get get_f;

    /*! Set callback. */
    ubjs_glue_dict_set set_f;

    /*! Delete callback. */
    ubjs_glue_dict_delete delete_f;

    /*! Iterate callback. */
    ubjs_glue_dict_iterate iterate_f;
};


/*! \brief Glue to object iterator.
 *
 * \since 0.5
 */
struct ubjs_glue_dict_iterator
{
    /*! Parent glue. */
    ubjs_glue_dict *object;

    /*! Userdata, probably with iterator implementation. */
    void *userdata;

    /*! Free callback. */
    ubjs_glue_dict_iterator_free free_f;

    /*! Next calback. */
    ubjs_glue_dict_iterator_next next_f;

    /*! Get key length callback. */
    ubjs_glue_dict_iterator_get_key_length get_key_length_f;

    /*! Copy callback. */
    ubjs_glue_dict_iterator_copy_key copy_key_f;

    /*! Get value callback. */
    ubjs_glue_dict_iterator_get_value get_value_f;
};

/*! \brief Initializes the library handle.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already allocated
 *  library handle.
 *
 *  Required for most operations.
 *  \param alloc Allocation function.
 *  \param free Deallocation function.
 *  \param glue_factory Glue factory.
 *  \param pthis Pointer to where put new library handle.
 *  \return UR_ERROR if any of alloc/free is 0, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_new(ubjs_library_alloc_f alloc, ubjs_library_free_f free,
    ubjs_glue_dict_factory glue_factory, ubjs_library **pthis);

/*! \brief Initializes the library handle using:
 *
 * - stdlib's malloc() and free(),
 * - object glue to ptrie library.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already allocated
 *  library handle.
 *
 *  Required for most operations.
 *  \param pthis Pointer to where put new library handle.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis);

/*! \brief Deinitializes the library handle.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *  \param pthis Pointer to library handle.
 *  \return UR_ERROR if any of pthis is not 0, otherwise UR_OK.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_library_free(ubjs_library **pthis);

#ifdef __cplusplus
}
#endif

#endif
