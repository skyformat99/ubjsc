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
 *  \brief Library handle, allocation callbacks, glues.
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
typedef void *(*ubjs_library_alloc_f)(unsigned long len);

/*! \brief Deallocation functor.
 *
 * This roughly follows the prototype for free().
 *  \param ptr Allocated pointer.
 *
 * \since 0.4
 */
typedef void (*ubjs_library_free_f)(void *ptr);

/*! \brief Library handle builder.
 *
 * \since 0.5
 */
typedef struct ubjs_library_builder ubjs_library_builder;

/*! \brief Library handle.
 *
 * \since 0.4
 */
typedef struct ubjs_library ubjs_library;

/*! \brief Glue to a array.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_array ubjs_glue_array;

typedef struct ubjs_glue_array_builder ubjs_glue_array_builder;

/*! \brief Glue to a arry iterator.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_array_iterator ubjs_glue_array_iterator;

/*! \brief Glue to a dictionary.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_dict ubjs_glue_dict;

/*! \brief Glue to a dictionary iterator.
 *
 * \since 0.5
 */
typedef struct ubjs_glue_dict_iterator ubjs_glue_dict_iterator;

/*! \brief Callback that frees the value held in a glue.
 * Note that this is a generic callback, not related to actual
 * ubjs_prmtv_object()-s.
 * \param pvalue Pointer to value to be freed.
 * \since 0.5
 */
typedef void (*ubjs_glue_value_free)(void *pvalue);

/*! \brief Callback that creates a new array glue.
 * \param lib Library handle.
 * \param vfree Value free callback.
 * \param pthis Pointer to where put new glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */

typedef ubjs_result (*ubjs_glue_array_builder_new_f)(ubjs_library *lib, ubjs_glue_array_builder **pthis);
typedef ubjs_result (*ubjs_glue_array_builder_free_f)(ubjs_glue_array_builder **);
typedef ubjs_result (*ubjs_glue_array_builder_set_value_free_f)(ubjs_glue_array_builder *, ubjs_glue_value_free);
typedef ubjs_result (*ubjs_glue_array_builder_set_length_f)(ubjs_glue_array_builder *, unsigned int);
typedef ubjs_result (*ubjs_glue_array_builder_build_f)(ubjs_glue_array_builder *, ubjs_glue_array **);

/*! \brief Frees the array glue.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *
 * \param pthis Pointer to where glue is.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_free)(ubjs_glue_array **);

/*! \brief Gets the length of the array under a glue.
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the length.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_get_length)(ubjs_glue_array *this, unsigned int *pvalue);

/*! \brief Gets the value of first item.
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the value.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_get_first)(ubjs_glue_array *this, void **pvalue);

/*! \brief Gets the value of last item.
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the value.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_get_last)(ubjs_glue_array *this, void **pvalue);

/*! \brief Gets the value of item under an index.
 *
 *  After this returns UR_OK, it is guaranteed that pvalue contains the value.
 *
 * \param this Glue.
 * \param index Index.
 * \param pvalue Pointer to where put value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_get_at)(ubjs_glue_array *this, unsigned int index,
    void **pvalue);

/*! \brief Add the value at beginning.
 *
 * \param this Glue.
 * \param value Value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_add_first)(ubjs_glue_array *this, void *value);

/*! \brief Add the value at end.
 *
 * \param this Glue.
 * \param value Value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_add_last)(ubjs_glue_array *this, void *value);

/*! \brief Add the value of item at an index.
 *
 * \param this Glue.
 * \param index Index.
 * \param value Value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_add_at)(ubjs_glue_array *this, unsigned int index,
    void *value);

/*! \brief Delete the first item.
 *
 * \param this Glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_delete_first)(ubjs_glue_array *this);

/*! \brief Delete the last item.
 *
 * \param this Glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_delete_last)(ubjs_glue_array *this);

/*! \brief Delete the item at index.
 *
 * \param this Glue.
 * \param index Index.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_delete_at)(ubjs_glue_array *this, unsigned int index);


/*! \brief Creates an iterator over glued array.
 *
 * \param this Glue.
 * \param piterator Pointer to where put iterator.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_iterate)(ubjs_glue_array *this,
    ubjs_glue_array_iterator **piterator);

/*! \brief Tries to iterate to next item.
 *
 * \param this Glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_iterator_next)(ubjs_glue_array_iterator *this);

/*! \brief Gets current item's value.
 *
 * \param this Glue.
 * \param pvalue Pointer to where put the value.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_iterator_get)(ubjs_glue_array_iterator *this,
    void **pvalue);

/*! \brief Frees the array iterator glue.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *
 * \param pthis Pointer to where glue is.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_array_iterator_free)(ubjs_glue_array_iterator **pthis);

/*! \brief Callback that creates a new dictionary glue.
 * \param lib Library handle.
 * \param vfree Value free callback.
 * \param pthis Pointer to where put new glue.
 * \return UR_OK if succedeed, otherwise UR_ERROR.
 * \since 0.5
 */
typedef ubjs_result (*ubjs_glue_dict_builder)(ubjs_library *lib, ubjs_glue_value_free vfree,
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

struct ubjs_glue_array_builder
{
    ubjs_library *lib;
    void *userdata;

    ubjs_glue_array_builder_free_f free_f;
    ubjs_glue_array_builder_set_value_free_f set_value_free_f;
    ubjs_glue_array_builder_set_length_f set_length_f;
    ubjs_glue_array_builder_build_f build_f;
};

/*! \brief Glue to an array.
 *
 * \since 0.5
 */
struct ubjs_glue_array
{
    /*! Library. */
    ubjs_library *lib;

    /*! Userdata, possibly with actual implementation. */
    void *userdata;

    /*! Free callback */
    ubjs_glue_array_free free_f;

    /*! Get length callback. */
    ubjs_glue_array_get_length get_length_f;

    /*! Get first callback. */
    ubjs_glue_array_get_first get_first_f;

    /*! Get last callback. */
    ubjs_glue_array_get_last get_last_f;

    /*! Get at callback. */
    ubjs_glue_array_get_at get_at_f;

    /*! Add first callback. */
    ubjs_glue_array_add_first add_first_f;

    /*! Add last callback. */
    ubjs_glue_array_add_last add_last_f;

    /*! Add at callback. */
    ubjs_glue_array_add_at add_at_f;

    /*! Delete first callback. */
    ubjs_glue_array_delete_first delete_first_f;

    /*! Delete last callback. */
    ubjs_glue_array_delete_last delete_last_f;

    /*! Delete at callback. */
    ubjs_glue_array_delete_at delete_at_f;

    /*! Iterate callback. */
    ubjs_glue_array_iterate iterate_f;
};


/*! \brief Glue to array iterator.
 *
 * \since 0.5
 */
struct ubjs_glue_array_iterator
{
    /*! Parent glue. */
    ubjs_glue_array *array;

    /*! Userdata, probably with iterator implementation. */
    void *userdata;

    /*! Free callback. */
    ubjs_glue_array_iterator_free free_f;

    /*! Next calback. */
    ubjs_glue_array_iterator_next next_f;

    /*! Get callback. */
    ubjs_glue_array_iterator_get get_f;
};


/*! \brief Glue to a dictionary.
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


/*! \brief Glue to dictionary iterator.
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

/*! \brief Library handle builder.
 *
 * \since 0.5
 */
struct ubjs_library_builder;

/*! \brief Initializes the library handle builder.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already
 *  allocated builder. Builder is allocated with stdlib's malloc.
 *
 *  Required once to initialize library.
 *  \param pthis Pointer to where put new builder.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_new(ubjs_library_builder **pthis);

/*! \brief Frees the library handle builder.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to 0.
 *  Builder is freed with stdlib's free.
 *
 *  Required once after initializing the library.
 *  \param pthis Pointer to where put new builder.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_free(ubjs_library_builder **pthis);

/*! \brief Sets the allocation functor for to use for everything.
 *
 *  By default, ubjs uses stdlib's malloc().
 *
 *  \param this Builder.
 *  \param alloc_f Allocation functor.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_set_alloc_f(ubjs_library_builder * this,
    ubjs_library_alloc_f alloc_f);

/*! \brief Sets the deallocation functor for to use for everything.
 *
 *  By default, ubjs uses stdlib's free().
 *
 *  \param this Builder.
 *  \param free_f Deallocation functor.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_set_free_f(
    ubjs_library_builder *this,
    ubjs_library_free_f free_f);

/*! \brief Sets the array glue builder.
 *  This allows to select a different implementation of actual key-value
 *  store used in arrays.
 *
 *  By default, ubjs uses ubjs_glue_array_list_builder - built-in
 *  doubly-linked list.
 *
 *  \param this Builder.
 *  \param builder Glue array builder.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_set_glue_array_builder(
    ubjs_library_builder *this, ubjs_glue_array_builder_new_f builder);

/*! \brief Sets the dict glue builder.
 *  This allows to select a different implementation of actual key-value
 *  store used in dictionaries.
 *
 *  By default, ubjs uses ubjs_glue_dict_list_builder - built-in
 *  doubly-linked list.
 *
 *  \param this Builder.
 *  \param builder Glue dict builder.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_set_glue_dict_builder(
    ubjs_library_builder *this,
    ubjs_glue_dict_builder builder);

/*! \brief Builds the library and returns it.
 *
 *  After this returns UR_OK, it is guaranteed that plib points to newly
 *  initialized library handle.
 *  Library is allocated using stdlib's malloc, and deallocated
 *  with free.
 *
 *  \param this Builder.
 *  \param plib Pointer to where put newly created library handle.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_library_builder_build(ubjs_library_builder *this,
    ubjs_library **plib);

/*! \brief Library handle.
 *
 * \since 0.5
 */
struct ubjs_library
{
    /*! \brief Allocation callback. */
    ubjs_library_alloc_f alloc_f;

    /*! \brief Free callback. */
    ubjs_library_free_f free_f;

    /*! \brief Builder for array glue */
    ubjs_glue_array_builder_new_f glue_array_builder;

    /*! \brief Builder for dictionary glue */
    ubjs_glue_dict_builder glue_dict_builder;
};

/*! \brief Initializes the library handle using stdlib's malloc() and free().
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already allocated
 *  library handle.
 *
 *  Required for most operations.
 *  \param pthis Pointer to where put new library handle.
 *  \return UR_ERROR if universe exploded, otherwise UR_OK.
 *
 * \deprecated Use ubjs_library_builder to build library.
 *
 * \since 0.4
 */
UBJS_EXPORT ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis);

/*! \brief Deinitializes the library handle.
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already
 *  allocated library handle.
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
