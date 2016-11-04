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

#include "ubjspy.h"

PyMethodDef ubjspy_methods[] =
{
    {"dumps", ubjspy_dumps, METH_VARARGS, ""},
    {"pretty_print", ubjspy_pretty_print, METH_VARARGS, ""},
    {"loads", ubjspy_loads, METH_VARARGS, ""},
    {0, 0, 0, 0}
};

struct PyModuleDef ubjspy_module =
{
   PyModuleDef_HEAD_INIT,
   "ubjs",
   0,
   -1,
   ubjspy_methods
};

struct ubjspy_dumps_context
{
    unsigned int length;
    char *data;

    char *error;
};

PyObject *ubjspy_exception = 0;

struct ubjspy_noop_content
{
    PyObject_HEAD
};

static PyTypeObject ubjspy_noop_type =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    "ubjspy.NoopType",
    sizeof(struct ubjspy_noop_content), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "",           /* tp_doc */
};

PyObject *ubjspy_noop = 0;

PyMODINIT_FUNC PyInit_ubjspy()
{
    PyObject *module;

    module = PyModule_Create(&ubjspy_module);

    ubjspy_exception = PyErr_NewException("ubjspy.Exception", NULL, NULL);
    Py_INCREF(ubjspy_exception);
    PyModule_AddObject(module, "Exception", ubjspy_exception);

    ubjspy_noop_type.tp_new = PyType_GenericNew;
    PyType_Ready(&ubjspy_noop_type);
    Py_INCREF(&ubjspy_noop_type);

    ubjspy_noop = PyType_GenericNew(&ubjspy_noop_type, 0, 0);
    PyObject_SetAttrString(module, "NOOP", ubjspy_noop);
    return module;
}

void ubjspy_dumps_context_new(ubjspy_dumps_context **pthis)
{
    ubjspy_dumps_context *this;

    this = (ubjspy_dumps_context *)malloc(sizeof(struct ubjspy_dumps_context));
    this->data = 0;
    this->length = 0;
    this->error = 0;

    *pthis = this;
}

void ubjspy_dumps_context_free(ubjspy_dumps_context **pthis)
{
    ubjspy_dumps_context *this = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return;
    }

    this = *pthis;

    if (0 != this->data)
    {
        free(this->data);
    }

    if (0 != this->error)
    {
        free(this->error);
    }

    free(this);
    *pthis=0;
}

void ubjspy_dumps_context_error(ubjspy_dumps_context *this, char *error)
{
    this->error = strdup(error);
}

void ubjspy_dumps_context_set(ubjspy_dumps_context *this, unsigned int length, char *data)
{
    this->length = length;
    this->data = (char *)malloc(sizeof(char) * length);
    memcpy(this->data, data, length * sizeof(char));
}

void ubjspy_dumps_writer_context_would_write(ubjs_writer_context *context, uint8_t *data,
    unsigned int len)
{
    ubjspy_dumps_context *userdata = (ubjspy_dumps_context *)context->userdata;
    ubjspy_dumps_context_set(userdata, len, (char *)data);
}

void ubjspy_dumps_writer_context_would_print(ubjs_writer_context *context, char *data,
    unsigned int len)
{
    ubjspy_dumps_context *userdata = (ubjspy_dumps_context *)context->userdata;
    ubjspy_dumps_context_set(userdata, len, data);
}

void ubjspy_dumps_writer_context_free(ubjs_writer_context *context)
{
    ubjspy_dumps_context_free((ubjspy_dumps_context **) &(context->userdata));
}

ubjs_result ubjspy_dumps_from_python_to_ubjs(PyObject *object, ubjs_library *lib, ubjs_prmtv **pret)
{
    PyObject *pyitem;
    ubjs_prmtv *item;
    PyObject *pykey, *pyvalue;
    Py_ssize_t i = 0;
    Py_ssize_t length;

    if (Py_None == object)
    {
        *pret = ubjs_prmtv_null();
    }
    else if (ubjspy_noop == object)
    {
        *pret = ubjs_prmtv_noop();
    }
    else if (Py_False == object)
    {
        *pret = ubjs_prmtv_false();
    }
    else if (Py_True == object)
    {
        *pret = ubjs_prmtv_true();
    }
    else if (0 != PyLong_Check(object))
    {
        ubjs_prmtv_int(lib, PyLong_AsLong(object), pret);
    }
    else if (0 != PyFloat_Check(object))
    {
        ubjs_prmtv_float64(lib, PyFloat_AsDouble(object), pret);
    }
    else if (0 != PyUnicode_Check(object))
    {
        PyUnicode_READY(object);
        ubjs_prmtv_str(lib, (unsigned int)PyUnicode_GET_LENGTH(object), (char *)PyUnicode_1BYTE_DATA(object),
            pret);
    }
    else if (0 != PyBytes_Check(object))
    {
        ubjs_prmtv_str(lib, (unsigned int)PyBytes_Size(object), (char *)PyBytes_AsString(object),
            pret);
    }
    else if (0 != PyByteArray_Check(object))
    {
        ubjs_prmtv_str(lib, (unsigned int)PyByteArray_Size(object), (char *)PyByteArray_AsString(object),
            pret);
    }
    else if (0 != PyTuple_Check(object))
    {
        ubjs_prmtv_array(lib, pret);
        length = (unsigned int)PyTuple_GET_SIZE(object);
        for (i = 0; i < length; i++)
        {
            pyitem = PyTuple_GetItem(object, i);
            if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(pyitem, lib, &item))
            {
                ubjs_prmtv_free(pret);
                return UR_ERROR;
            }

            ubjs_prmtv_array_add_last(*pret, item);
        }
    }
    else if (0 != PyList_Check(object))
    {
        ubjs_prmtv_array(lib, pret);
        length = PyList_GET_SIZE(object);
        for (i = 0; i < length; i++)
        {
            pyitem = PyList_GetItem(object, i);
            if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(pyitem, lib, &item))
            {
                ubjs_prmtv_free(pret);
                return UR_ERROR;
            }

            ubjs_prmtv_array_add_last(*pret, item);
        }
    }
    else if (0 != PyDict_Check(object))
    {
        ubjs_prmtv_object(lib, pret);
        while (0 != PyDict_Next(object, &i, &pykey, &pyvalue))
        {
            if (0 == PyUnicode_Check(pykey))
            {
                ubjs_prmtv_free(pret);
                return UR_ERROR;
            }

            if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(pyvalue, lib, &item))
            {
                ubjs_prmtv_free(pret);
                return UR_ERROR;
            }

            PyUnicode_READY(pykey);
            ubjs_prmtv_object_set(*pret, PyUnicode_GET_LENGTH(pykey),
                (char *)PyUnicode_1BYTE_DATA(pykey), item);
        }
    }
    else
    {
        return UR_ERROR;
    }

    return UR_OK;
}

PyObject *ubjspy_dumps(PyObject *self, PyObject *args)
{
    PyObject *object = 0;
    PyObject *ret = 0;
    ubjs_prmtv *primitive = 0;
    ubjs_library *lib;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &object))
    {
        PyErr_SetString(ubjspy_exception, "Cannot parse args.");
        return NULL;
    }

    ubjs_library_new_stdlib(&lib);

    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, lib, &primitive))
    {
        PyErr_SetString(ubjspy_exception, "Don't know how to dumps this object.");
    }
    else
    {
        ubjspy_dumps_context_new(&userdata);
        writer_context.userdata = (void *)userdata;
        writer_context.would_write = ubjspy_dumps_writer_context_would_write;
        writer_context.would_print = 0;
        writer_context.free = ubjspy_dumps_writer_context_free;

        ubjs_writer_new(lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_write(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            ret = PyBytes_FromStringAndSize(userdata->data, userdata->length);
            Py_INCREF(ret);
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    ubjs_library_free(&lib);
    return ret;
}

PyObject *ubjspy_pretty_print(PyObject *self, PyObject *args)
{
    PyObject *object = 0;
    PyObject *ret = 0;
    ubjs_prmtv *primitive = 0;
    ubjs_library *lib;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &object))
    {
        PyErr_SetString(ubjspy_exception, "Cannot parse args.");
        return NULL;
    }

    ubjs_library_new_stdlib(&lib);
    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, lib, &primitive))
    {
        PyErr_SetString(ubjspy_exception, "Don't know how to dumps this object.");
    }
    else
    {
        ubjspy_dumps_context_new(&userdata);
        writer_context.userdata = (void *)userdata;
        writer_context.would_write = 0;
        writer_context.would_print = ubjspy_dumps_writer_context_would_print;
        writer_context.free = ubjspy_dumps_writer_context_free;

        ubjs_writer_new(lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_print(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            ret = PyUnicode_FromStringAndSize(userdata->data, userdata->length);
            Py_INCREF(ret);
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    ubjs_library_free(&lib);
    return ret;
}

PyObject *ubjspy_loads(PyObject *self, PyObject *args)
{
    PyErr_SetString(ubjspy_exception, "Not implemented yet.");
    return NULL;
}
