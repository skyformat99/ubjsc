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

#ifndef HAVE_UBJSPY
#define HAVE_UBJSPY

#ifdef __cplusplus
extern "C"
{
#endif

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <ubjs.h>

PyMethodDef ubjspy_methods[];
struct PyModuleDef ubjspy_module;
PyMODINIT_FUNC PyInit_ubjspy();

extern PyObject *ubjspy_exception;

struct ubjspy_noop_content;
static PyTypeObject ubjspy_noop_type;
extern PyObject *ubjspy_noop;

struct ubjspy_dumps_context;
typedef struct ubjspy_dumps_context ubjspy_dumps_context;

void ubjspy_dumps_context_new(ubjspy_dumps_context **);
void ubjspy_dumps_context_free(ubjspy_dumps_context **);
void ubjspy_dumps_context_set(ubjspy_dumps_context *, unsigned int, char *);

void ubjspy_dumps_writer_context_would_write(ubjs_writer_context *, uint8_t *, unsigned int len);
void ubjspy_dumps_writer_context_would_print(ubjs_writer_context *, char *, unsigned int len);
void ubjspy_dumps_writer_context_free(ubjs_writer_context *);
ubjs_result ubjspy_dumps_from_python_to_ubjs(PyObject *, ubjs_library *, ubjs_prmtv **);
PyObject *ubjspy_dumps(PyObject *self, PyObject *args);

PyObject *ubjspy_pretty_print(PyObject *self, PyObject *args);
PyObject *ubjspy_loads(PyObject *self, PyObject *args);

#ifdef __cplusplus
}
#endif

#endif
