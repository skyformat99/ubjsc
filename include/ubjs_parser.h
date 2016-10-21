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
 *  \brief Incremental parser of bytestream to ubjson primitives.
 *
 * This file describes ubjs_parser structure, that parses incoming bytes and produces
 * ubjs_prmtv object.
 *
 * \since 0.2
 */

#ifndef HAVE_UBJS_PARSER
#define HAVE_UBJS_PARSER

#ifdef __cplusplus
extern "C"
{
#endif

#include "ubjs_common.h"
#include "ubjs_primitives.h"

/*!< \brief Parser itself. */
struct ubjs_parser;

/*!< \brief User-provided context - callbacks and userdata. */
struct ubjs_parser_context;

/*!< \brief Parser settings. */
struct ubjs_parser_settings;

/*!< \brief Holder for parser errors. */
struct ubjs_parser_error;

/*!< \brief Parser itself. */
typedef struct ubjs_parser ubjs_parser;

/*!< \brief User-provided context - callbacks and userdata. */
typedef struct ubjs_parser_context ubjs_parser_context;

/*!< \brief Parser settings. */
typedef struct ubjs_parser_settings ubjs_parser_settings;

/*!< \brief Holder for parser errors. */
typedef struct ubjs_parser_error ubjs_parser_error;

/*! \brief Callback to be executed just when parser parsed a first-citizen primitive.
 *
 * You should ubjs_prmtv_free(&primitive) by yourself.
 * \param context Context object you passed to ubjs_parser_new.
 * \param primitive Newly parsed primitive.
 */
typedef void (*ubjs_parser_context_parsed)(ubjs_parser_context *context, ubjs_prmtv *primitive);
/*! \brief Callback when encountered a parsing error.
 *
 * The current call to ubjs_parser_parse will return UR_ERROR. The parser is still functional,
 * but it remains at last valid state, before the error appeared.
 * \param context Context object you passed to ubjs_parser_new.
 * \param error Error.
 */
typedef void (*ubjs_parser_context_error)(ubjs_parser_context *context, ubjs_parser_error *error);
/*! \brief Callback when parser is about to be free-d.
 *
 * Here you can cleanup your userdata.
 * \param context Context object you passed to ubjs_parser_new.
 */
typedef void (*ubjs_parser_context_free)(ubjs_parser_context *);

/*! \brief Gets the error message's length.
 * \param this Error.
 * \param plength Pointer to where set the value.
 * \return UR_ERROR if any of this/presult is 0,  else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *this,
    unsigned int *plength);
/*! \brief Copies the error message's content to provided array.
 *
 * Target array must be preallocated. Before the call, you may want to
 * ubjs_parser_error_get_message_length and allocate the target array.
 * \param this Error.
 * \param text Target array.
 * \return UR_ERROR if any of this/text is 0,  else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *this, char *text);

/*! \brief Settings for parser.
 *
 * Most options limit some abilities to process data after reaching a threshold.
 * These can prevent the library from crashing upon well-performed denial-of-service
 * attack.
 */
struct ubjs_parser_settings
{
    /*!< \brief Max number of bytes to process since last callback.
     * If this is 0, limit is effectively off.
     * Else parser errors will occur once you process this-th byte.
     * This setting is global to whole parser.
     */
    unsigned int limit_bytes_since_last_callback;

    /*!< \brief Max number of items in container.
     * This applies to arrays and objects.
     * If this is 0, limit is effectively off.
     * Else parser errors when:
     * - for unoptimized containers, n+1-th item is not an end marker,
     * - for optimized containers, when received length and it exceeds the limit.
     * This setting is global to whole parser.
     */
    unsigned int limit_container_length;

    /*!< \brief Max number of characters in string or HPN.
     * If this is 0, limit is effectively off.
     * Else parser errors when expected length exceeds the limit.
     * This setting is global to whole parser.
     */
    unsigned int limit_string_length;

    /*!< \brief Max recursion level for containers.
     * If this is 0, limit is effectively off.
     * Else parser errors when recursion level exceeds the limit.
     * This setting is global to whole parser.
     */
    unsigned int limit_recursion_level;

    /*!< \brief Debugging mode.
     * If this is UTRUE, parser will fprintf(stderr) lots of
     * internal messages about how and what is being parsed.
     *
     * This is useful only for development or debugging.
     */
    ubjs_bool debug;
};

/*! \brief User-provided context - callbacks and userdata. */
struct ubjs_parser_context
{
    void *userdata; /*!< User context. */

    ubjs_parser_context_parsed parsed; /*!< Callback when parsed a primitive. */
    ubjs_parser_context_error error; /*!< Callback when encountered a parsing error. */
    ubjs_parser_context_free free; /*!< Callback when about to free the parser. */
};

/*! \brief Creates new parser.
 *
 * \param settings Settings. Can be 0.
 * \param context User context.
 * \param pthis Pointer to where put newly created parser.
 * \return UR_ERROR if any of pthis/context/context->parsed/context->error/context->free
 * is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_new(ubjs_parser_settings *settings,
    ubjs_parser_context *context, ubjs_parser **pthis);

/*! \brief Frees the parser.
 *
 * The call to context->free will occur here.
 * After this, *pthis will be equal to 0.
 * \param pthis Pointer to the parser.
 * \return UR_ERROR if pthis is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_free(ubjs_parser **pthis);

/*! \brief Gets user context from the parser.
 *
 * \param this Parser.
 * \param pcontext Pointer to where put user context.
 * \return UR_ERROR if any of this/pcontext is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_get_context(ubjs_parser *this, ubjs_parser_context **pcontext);

/*! \brief Gets settings from the parser.
 *
 * \param this Parser.
 * \param psettings Pointer to where put settings.
 * \return UR_ERROR if any of this/psettings is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_get_settings(ubjs_parser *this,
    ubjs_parser_settings **psettings);

/*! \brief Parses the incoming data.
 *
 * This may produce the call (or calls) to context->parsed with just-parsed primitive,
 * or context->error, or none of them.
 *
 * In case there are many primitives parsed in single ubjs_parser_parse call, these many
 * calls to context->parsed will be issues for each new primitive.
 *
 * In case there is too little data to issue any callback, this method will not issue any callback.
 *
 * If len == 0, this method does nothing and simply returns UR_OK.
 * \param this Parser.
 * \param data Incoming data.
 * \param len Length of the data.
 * \return UR_ERROR if any of this/data is 0, else UR_OK.
 */
UBJS_EXPORT ubjs_result ubjs_parser_parse(ubjs_parser *this, uint8_t *data, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
