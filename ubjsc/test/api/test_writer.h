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

#ifndef HAVE_TEST_WRITER
#define HAVE_TEST_WRITER

#ifdef __cplusplus
extern "C"
{
#endif

#include "test_frmwrk.h"

void suite_writer_before(void);
void suite_writer_after(void);

void sw_verify(ubjs_library *lib, ubjs_prmtv *, unsigned unt, uint8_t *, unsigned int, char *);
void sw_verify_free_primitives_early(ubjs_library *lib, ubjs_prmtv *);

void sw_verifyd(ubjs_library *lib, ubjs_prmtv *, unsigned unt, uint8_t *, unsigned int, char *,
    ubjs_bool);
void sw_verifyd_free_primitives_early(ubjs_library *lib, ubjs_prmtv *, ubjs_bool);

#ifdef __cplusplus
}
#endif

#endif
