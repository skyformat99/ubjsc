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
    {"dump", ubjspy_dump, METH_VARARGS, ""},
    {"pretty_prints", ubjspy_pretty_prints, METH_VARARGS, ""},
    {"pretty_print", ubjspy_pretty_print, METH_VARARGS, ""},
    {"loads", ubjspy_loads, METH_VARARGS, ""},
    {"load", ubjspy_load, METH_VARARGS, ""},
    {0, 0, 0, 0}
};

struct PyModuleDef ubjspy_module =
{
   PyModuleDef_HEAD_INIT,
   "ubjspy",
   0,
   // @todo support subinterpreters
   -1,
   ubjspy_methods,
   0,
   0,
   0,
   ubjspy_free
};

struct ubjspy_dumps_context
{
    unsigned int length;
    char *data;
};

struct ubjspy_loads_context
{
    PyObject *captured;
    char *error;
};

PyObject *ubjspy_BufferedIOBase = 0;
PyObject *ubjspy_TextIOBase = 0;
PyObject *ubjspy_Decimal = 0;
PyObject *ubjspy_noop = 0;
PyObject *ubjspy_exception = 0;
ubjs_library *ubjspy_lib = 0;

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

PyMODINIT_FUNC PyInit_ubjspy()
{
    PyObject *module;
    PyObject *module_ext;

    module = PyModule_Create(&ubjspy_module);

    ubjs_library_new(malloc, free, ubjs_glue_dict_ptrie_factory, &ubjspy_lib);

    ubjspy_exception = PyErr_NewException("ubjspy.Exception", NULL, NULL);
    PyModule_AddObject(module, "Exception", ubjspy_exception);

    ubjspy_noop_type.tp_new = PyType_GenericNew;
    PyType_Ready(&ubjspy_noop_type);

    ubjspy_noop = PyType_GenericNew(&ubjspy_noop_type, 0, 0);
    PyObject_SetAttrString(module, "NOOP", ubjspy_noop);

    module_ext = PyImport_ImportModule("io");
    ubjspy_BufferedIOBase = PyObject_GetAttrString(module_ext, "BufferedIOBase");
    ubjspy_TextIOBase = PyObject_GetAttrString(module_ext, "TextIOBase");

    module_ext = PyImport_ImportModule("decimal");
    ubjspy_Decimal = PyObject_GetAttrString(module_ext, "Decimal");

    return module;
}

void ubjspy_free()
{
    Py_DECREF(ubjspy_exception);
    ubjs_library_free(&ubjspy_lib);
}

void ubjspy_dumps_context_new(ubjspy_dumps_context **pthis)
{
    ubjspy_dumps_context *this;

    this = (ubjspy_dumps_context *)malloc(sizeof(struct ubjspy_dumps_context));
    this->data = 0;
    this->length = 0;

    *pthis = this;
}

void ubjspy_dumps_context_free(ubjspy_dumps_context **pthis)
{
    ubjspy_dumps_context *this = 0;

    this = *pthis;

    if (0 != this->data)
    {
        free(this->data);
    }

    free(this);
    *pthis=0;
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
    {-
        PyUnicode_READY(object);
        ubjs_prmtv_str(lib, (unsigned int)PyUnicode_GET_LENGTH(object),
            (char *)PyUnicode_1BYTE_DATA(object), pret);
    }
    else if (0 != PyBytes_Check(object))
    {
        ubjs_prmtv_str(lib, (unsigned int)PyBytes_Size(object), (char *)PyBytes_AsString(object),
            pret);
    }
    else if (0 != PyByteArray_Check(object))
    {
        ubjs_prmtv_str(lib, (unsigned int)PyByteArray_Size(object),
            (char *)PyByteArray_AsString(object), pret);
    }
    else if (0 != PyObject_IsInstance(object, ubjspy_Decimal))
    {
        PyObject *strvalue;
        strvalue = PyObject_Str(object);
        PyUnicode_READY(strvalue);
        ubjs_prmtv_hpn(lib, (unsigned int)PyUnicode_GET_LENGTH(strvalue),
            (char *)PyUnicode_1BYTE_DATA(strvalue), pret);
        Py_DECREF(strvalue);
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
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &object))
    {
        return 0;
    }

    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, ubjspy_lib, &primitive))
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

        ubjs_writer_new(ubjspy_lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_write(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            ret = PyBytes_FromStringAndSize(userdata->data, userdata->length);
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    return ret;
}

PyObject *ubjspy_pretty_prints(PyObject *self, PyObject *args)
{
    PyObject *object = 0;
    PyObject *ret = 0;
    ubjs_prmtv *primitive = 0;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &object))
    {
        return 0;
    }

    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, ubjspy_lib, &primitive))
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

        ubjs_writer_new(ubjspy_lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_print(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            ret = PyUnicode_FromStringAndSize(userdata->data, userdata->length);
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    return ret;
}

void ubjspy_loads_context_new(ubjspy_loads_context **pthis)
{
    ubjspy_loads_context *this;

    this = (ubjspy_loads_context *)malloc(sizeof(struct ubjspy_loads_context));
    this->captured = 0;
    this->error = 0;

    *pthis = this;
}

void ubjspy_loads_context_free(ubjspy_loads_context **pthis)
{
    ubjspy_loads_context *this = 0;
    this = *pthis;

    if (0 != this->error)
    {
        free(this->error);
    }

    free(this);
    *pthis=0;
}

void ubjspy_loads_parser_context_parsed(ubjs_parser_context *ctx, ubjs_prmtv *prmtv)
{
    ubjspy_loads_context *lctx = (ubjspy_loads_context *) ctx->userdata;

    if (0 != lctx->captured)
    {
        // @todo
        return;
    }

    ubjspy_loads_from_ubjs_to_python(prmtv, &(lctx->captured));
}

void ubjspy_loads_parser_context_error(ubjs_parser_context *ctx,
    ubjs_parser_error *error)
{
    ubjspy_loads_context *lctx = (ubjspy_loads_context *) ctx->userdata;
    unsigned int length;
    char *message;

    ubjs_parser_error_get_message_length(error, &length);
    message = (char *)malloc(sizeof(char) * (length+1));
    ubjs_parser_error_get_message_text(error, message);
    message[length] = 0;

    lctx->error=message;
}

void ubjspy_loads_parser_context_free(ubjs_parser_context *ctx)
{
    ubjspy_loads_context_free((ubjspy_loads_context **) &(ctx->userdata));
}

ubjs_result ubjspy_loads_from_ubjs_to_python(ubjs_prmtv *prmtv, PyObject **pret)
{
    ubjs_prmtv_type type;
    int64_t v;
    float32_t f32;
    float64_t f64;
    ubjs_array_iterator *ait;
    ubjs_object_iterator *oit;
    ubjs_prmtv *item;
    PyObject *pitem = 0;
    unsigned int str_length;
    char *str;

    ubjs_prmtv_get_type(prmtv, &type);
    switch (type)
    {
        case UOT_NULL:
            *pret = Py_None;
            break;

        case UOT_NOOP:
            *pret = ubjspy_noop;
            break;

        case UOT_TRUE:
            *pret = Py_True;
            break;

        case UOT_FALSE:
            *pret = Py_False;
            break;

        case UOT_UINT8:
        case UOT_INT8:
        case UOT_INT16:
        case UOT_INT32:
        case UOT_INT64:
            ubjs_prmtv_int_get(prmtv, &v);
            *pret = PyLong_FromLong(v);
            break;

        case UOT_FLOAT32:
            ubjs_prmtv_float32_get(prmtv, &f32);
            *pret = PyFloat_FromDouble(f32);
            break;

        case UOT_FLOAT64:
            ubjs_prmtv_float64_get(prmtv, &f64);
            *pret = PyFloat_FromDouble(f64);
            break;

        case UOT_STR:
            ubjs_prmtv_str_get_length(prmtv, &str_length);
            str = (char *) malloc(sizeof(char) * str_length);
            ubjs_prmtv_str_copy_text(prmtv, str);

            *pret = PyUnicode_FromStringAndSize(str, str_length);
            free(str);
            break;

        case UOT_HPN:
            ubjs_prmtv_hpn_get_length(prmtv, &str_length);
            str = (char *) malloc(sizeof(char) * str_length);
            ubjs_prmtv_hpn_copy_text(prmtv, str);

            *pret = PyObject_CallFunction(ubjspy_Decimal, "s#", str, str_length);
            free(str);

            if (0 == PyErr_Occurred())
            {
                return 0;
            }
            break;

        case UOT_CHAR:
            str = (char *) malloc(sizeof(char) * 1);
            ubjs_prmtv_char_get(prmtv, str);

            *pret = PyUnicode_FromStringAndSize(str, 1);
            free(str);
            break;

        case UOT_ARRAY:
            *pret = PyList_New(0);
            ubjs_prmtv_array_iterate(prmtv, &ait);

            while (UR_OK == ubjs_array_iterator_next(ait))
            {
                ubjs_array_iterator_get(ait, &item);
                ubjspy_loads_from_ubjs_to_python(item, &pitem);
                if (0 != pitem)
                {
                    PyList_Append(*pret, pitem);
                }
            }

            ubjs_array_iterator_free(&ait);
            break;

        case UOT_OBJECT:
            *pret = PyDict_New();
            ubjs_prmtv_object_iterate(prmtv, &oit);

            while (UR_OK == ubjs_object_iterator_next(oit))
            {
                unsigned int key_length;
                char *key;

                ubjs_object_iterator_get_key_length(oit, &key_length);
                key = (char *)malloc(sizeof(char) * (key_length + 1));
                ubjs_object_iterator_copy_key(oit, key);
                key[key_length] = 0;

                ubjs_object_iterator_get_value(oit, &item);
                ubjspy_loads_from_ubjs_to_python(item, &pitem);
                if (0 != pitem)
                {
                    PyDict_SetItemString(*pret, key, pitem);
                }
                free(key);
            }

            ubjs_object_iterator_free(&oit);
            break;

        default:
            return UR_ERROR;
    }

    return UR_OK;
}

PyObject *ubjspy_loads(PyObject *self, PyObject *args)
{
    PyObject *object = 0;
    PyObject *ret = 0;
    ubjs_parser *parser=0;
    ubjs_parser_context parser_context;
    ubjs_parser_settings settings;

    unsigned int data_length = 0;
    char *data = 0;

    ubjspy_loads_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &object))
    {
        return 0;
    }

    if (0 != PyBytes_Check(object))
    {
        data_length = (unsigned int)PyBytes_Size(object);
        data = PyBytes_AsString(object);
    }
    else if (0 != PyByteArray_Check(object))
    {
        data_length = (unsigned int)PyByteArray_Size(object);
        data = (char *)PyByteArray_AsString(object);
    }
    else
    {
        PyErr_SetString(ubjspy_exception, "You must provide exactly 1 byte(array)s");
        return 0;
    }

    ubjspy_loads_context_new(&userdata);
    parser_context.userdata = (void *)userdata;
    parser_context.parsed = ubjspy_loads_parser_context_parsed;
    parser_context.error = ubjspy_loads_parser_context_error;
    parser_context.free = ubjspy_loads_parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(ubjspy_lib, &settings, &parser_context, &parser);

    if (UR_OK != ubjs_parser_parse(parser, data, data_length))
    {
        PyErr_SetString(ubjspy_exception, userdata->error);
    }
    else
    {
        ret = userdata->captured;
        if (0 == ret)
        {
            PyErr_SetString(ubjspy_exception, "No complete object parsed");
        }
    }

    ubjs_parser_free(&parser);
    return ret;
}

PyObject *ubjspy_dump(PyObject *self, PyObject *args)
{
    PyObject *ret = 0;
    PyObject *object = 0;
    PyObject *io = 0;
    ubjs_prmtv *primitive = 0;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "OO", &object, &io))
    {
        return 0;
    }

    if (Py_None == io || 0 == PyObject_IsInstance(io, ubjspy_BufferedIOBase))
    {
        PyErr_SetString(ubjspy_exception, "Second parameter not a valid BufferedIOBase");
	return 0;
    }

    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, ubjspy_lib, &primitive))
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

        ubjs_writer_new(ubjspy_lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_write(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            PyObject_CallMethod(io, "write", "y#", userdata->data, userdata->length);
            ret = Py_None;
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    return ret;
}

PyObject *ubjspy_pretty_print(PyObject *self, PyObject *args)
{
    PyObject *object = 0;
    PyObject *io = 0;
    PyObject *ret = 0;
    ubjs_prmtv *primitive = 0;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    ubjspy_dumps_context *userdata;

    if (0 == PyArg_ParseTuple(args, "OO", &object, &io))
    {
        return 0;
    }

    if (Py_None == io || 0 == PyObject_IsInstance(io, ubjspy_TextIOBase))
    {
        PyErr_SetString(ubjspy_exception, "Second parameter not a valid TextIOBase");
	return 0;
    }

    if (UR_ERROR == ubjspy_dumps_from_python_to_ubjs(object, ubjspy_lib, &primitive))
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

        ubjs_writer_new(ubjspy_lib, &writer, &writer_context);
        if (UR_ERROR == ubjs_writer_print(writer, primitive))
        {
            PyErr_SetString(ubjspy_exception, "Internal error.");
        }
        else
        {
            PyObject_CallMethod(io, "write", "s#", userdata->data, userdata->length);
            ret = Py_None;
        }

        ubjs_prmtv_free(&primitive);
        ubjs_writer_free(&writer);
    }
    return ret;
}

PyObject *ubjspy_load(PyObject *self, PyObject *args)
{
    PyObject *io = 0;
    PyObject *ret = 0;
    PyObject *read_ret = 0;
    ubjs_parser *parser=0;
    ubjs_parser_context parser_context;
    ubjs_parser_settings settings;

    ubjspy_loads_context *userdata;

    if (0 == PyArg_ParseTuple(args, "O", &io))
    {
        return 0;
    }

    if (Py_None == io || 0 == PyObject_IsInstance(io, ubjspy_BufferedIOBase))
    {
        PyErr_SetString(ubjspy_exception, "Second parameter not a valid BufferedIOBase");
	return 0;
    }

    ubjspy_loads_context_new(&userdata);
    parser_context.userdata = (void *)userdata;
    parser_context.parsed = ubjspy_loads_parser_context_parsed;
    parser_context.error = ubjspy_loads_parser_context_error;
    parser_context.free = ubjspy_loads_parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(ubjspy_lib, &settings, &parser_context, &parser);

    read_ret = PyObject_CallMethod(io, "read", 0);
    if (0 == PyErr_Occurred())
    {
        if (UR_OK != ubjs_parser_parse(parser, (uint8_t *)PyBytes_AsString(read_ret),
             (unsigned int)PyBytes_Size(read_ret)))
        {
            PyErr_SetString(ubjspy_exception, userdata->error);
        }
        else
        {
            ret = userdata->captured;
            if (0 == ret)
            {
                PyErr_SetString(ubjspy_exception, "No complete object parsed");
            }
        }
    }

    ubjs_parser_free(&parser);
    return ret;
}
