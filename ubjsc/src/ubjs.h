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
 *  \brief God-file that includes everything from ubjs and mechanisms to verify version.
 *
 * \since 0.2
 */

#ifndef HAVE_UBJS
#define HAVE_UBJS

#ifdef __cplusplus
extern "C"
{
#endif

#include "ubjs_common.h"
#include "ubjs_primitives.h"
#include "ubjs_parser.h"
#include "ubjs_writer.h"

/*! \brief Library version from the time your project got compiled.
 *
 *  This numbering follows the semantic versioning scheme, in this manner:
 *
 *    UBJS_VERSION = dec(MAJOR) << 16 + dec(MINOR) << 8 + dec(PATCH)
 *
 *  For example, if it ever happens here, 0x112233 equals to version 11.22.33.
 *
 * \since 0.2
 */
#define UBJS_VERSION 0x000400

/*! \brief Gets library runtime version.
 *
 *  Use this to get the version of the library runtime.
 *  After this returns, it is guaranteed that (*pversion) gets a value.
 *  \param pversion Pointer under which to place library version.
 *
 * \since 0.2
 */
UBJS_EXPORT void ubjs_get_version(unsigned long *pversion);

/*! \brief Compares library runtime version with supplied.
 *
 *  Use this to verify whether your project is compatible with current library runtime.
 *  In general, ubjs follows semantic versioning scheme.
 *
 *  After this returns, it is guaranteed that (*pret) is equal to either UTRUE/UFALSE,
 *  depending on these conditions:
 *
 *  - If the minors are 0, and the minors match, UTRUE, else UFALSE.
 *
 *    Aka your code built with version 0.1.0 is compatible with library runtime 0.1.2,
 *    but 0.1.0 is not compatible with 0.2.0.
 *  - Otherwise if the majors match, UTRUE, else UFALSE.
 *
 *    Aka 1.0.0 and 1.2.0 are good. The newer library probably will have more features than
 *    the one used in your project at the time of compilation.
 *    But 2.0.0 and 3.0.0 are not compatible. The API changed and you must either fallback to
 *    older version, or realign your code to fit the new library.
 *
 *  \param version Pointer under which to place library version.
 *  \param pret Pointer under which to place the result.
 *
 * \since 0.2
 */
 UBJS_EXPORT void ubjs_is_compatible(unsigned long version, ubjs_bool *pret);

#ifdef __cplusplus
}
#endif

#endif