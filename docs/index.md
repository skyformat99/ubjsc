\mainpage

\tableofcontents

\section main_what_is_ubjsc What is ubjsc?

ubjsc is a C library for manipulating data in [UBJSON](http://www.ubjson.org/) format.

\section wain_what_is_included What is included?

Right now, you can:
- parse UBJSON to C "objects",
- dump these C "objects" to UBJSON,

\section main_how_do_i_install_it How do I build/install it?

\todo Mac OS X

\subsection main_how_do_i_install_it_windows Windows

Prerequisites
=============

- Install (CMake >= 3.3)[https://cmake.org].
- Have a C compiler. Visual Studio Community 2015 works fine.
- Install library & developer headers of (jansson)[http://www.digip.org/jansson/].
    Don't ask me how to do it.
- Install library & developer headers of (argtable2)[https://bitbucket.org/tsieprawski/argtable2].
    Do not use original from http://argtable.sourceforge.net/. It lacks some neccessary CMake exports
    stuff.

Other compilers (like blind cygwin/clang) should work, but I did not test'em.

Optional: Python
----------------

Optionaly if you want to generate Python wheel, you need:
  - (Python >=3.4)[https://python.org].

Building @ VSC 2015 ===================

- Build jansson and argtable2 using CMake and INSTALL them somewhere (note where). Do not ask me how to do it.
- Run CMake-GUI (probably from Z:\\WHERE_YOU_INSTALLED_CMAKE\\bin\\cmake-gui.exe).
- In "Where is the source code" point to ubjsc.
- In "Where to build the binaries" point to ubjsc/build. Or anywhere you like.
- Click "Configure".
- In "Specify the generator for the project" select "Visual Studio 14 2015 Win64".
- Configure JANSSON_EXPORT_DIR and ARGTABLE2_EXPORT_DIR variables to point to INSTALL folders.
- Click "Finish".
- If everything goes ok, "Generate" button gets un-greyed.
- Probably you want to configure CMAKE_INSTALL_PREFIX variable.
- Click "Generate".
- Open ubjsc/build/ubjsc.sln.
- Build "ALL" target.

Install:

- Build "INSTALL" target.

If you want to run test suite:

- Build "RUN_TESTS" target.

\subsection main_how_do_i_install_it_linux Linux

Prerequisites
=============

- Install (CMake >= 3.3)[https://cmake.org]. If you know how to use CMake, you do not have to read
- Have at least `gcc` and `make` commands available. Probably this involves installing GCC and
  Autotools, but I won't direct you to correct packages.
- Install library & developer headers of (jansson)[http://www.digip.org/jansson/].
    Don't ask me how to do it.
- Install library & developer headers of (argtable2)[https://bitbucket.org/tsieprawski/argtable2].
    If you like, use original sources from http://argtable.sourceforge.net/.
    Don't ask me how to do it.

Other compilers (like clang) should work, but I did not test'em.

Optional: Python
----------------

Optionaly if you want to generate Python wheel, you need (Python >=3.4)[https://python.org].
  - (Python >=3.4)[https://python.org].

Building GNU+Autotools 
======================

Prepare project:

     ubjsc $ mkdir build && cd build
     ubjsc/build $ cmake ..

Build it:

     ubjsc/build $ make

Install:

     ubjsc/build $ sudo make install

If you want to run test suite:

    ubjsc/build $ ctest . # Or $ make test

Python
------

After building, Python .whl should lie in the build folder. You can import it with:

    pip3 install ubjspy*.whl

\section main_how_do_i_use_it_tools How do I use it right away?

There are 3 tools that you can use right away.

\subsection js2ubj js2ubj

    $ js2ubj -h
    Usage: build/tools/js2ubj [-vh] [--pretty-print-output]
    This program converts JSON objects from stdin to UBJSON objects to stdout.

      -v, --verbose             verbosily print input, both input's and output's lengths and compression/expansion rate
      --pretty-print-output     if verbose, then also pretty-print the output
      -h, --help                print this help and exit

    $ echo "[null, 1, 2.2, \"as\"]" | js2ubj | hexdump -c
    0000000   [   #   U 004   Z   U 001   D 232 231 231 231 231 231 001   @
    0000010   S   U 002   a   s
    0000015

    $ echo "[null, 1, 2.2, \"as\"]" | js2ubj --verbose --pretty-print-output
    Before: [35]
    [null, 1, 2.2000000000000002, "as"]
    After: [21]
    [#UZUD------@SUas
    Compression/expansion: [60%]
    Pretty-printed [71]: [[][#][U][4]
        [Z]
        [U][1]
        [D][2.200000]
        [S][U][2][as]
    []]


\subsection ubj2js ubj2js

    $ ubj2js -h
    Usage: ubj2js [-vh] [--pretty-print-input]
    This program converts UBJSON objects from stdin to JSON objects to stdout.

    Examples:
        printf Z | ubj2js
        printf T | ubj2js
        printf F | ubj2js
        printf 'U\x96' | ubj2js
        printf 'i\xF0' | ubj2js
        printf 'I\xDE\xAD' | ubj2js
        printf 'l\xDE\xAD\xBE\xEF' | ubj2js
        printf 'L\xDE\xAD\xBE\xEF\xCA\xFE\xBA\xBE' | ubj2js
        printf 'd\xDE\xAD\xBE\xEF' | ubj2js
        printf 'D\xDE\xAD\xBE\xEF\xCA\xFE\xBA\xBE' | ubj2js
        printf 'Cr' | ubj2js
        printf 'HU\x0512345' | ubj2js
        printf 'SU\x05rower' | ubj2js
        printf '[]' | ubj2js
        printf '[#U\x03ZTF' | ubj2js
        printf '[$Z#U\xFF' | ubj2js
        printf "{U\x03youSU\x04suckU\x05and ISU\x05don't}" | ubj2js
        printf '{U\x03youSU\x04suck}' | ubj2js
        printf '[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]' | ubj2js

      -v, --verbose             verbosily print input, both input's and output's lengths and compression/expansion rate
      --pretty-print-input      if verbose, then also pretty-print the input
      -h, --help                print this help and exit


    $ printf Z | (ubj2js; echo)
    null

    $ printf 'SU\x05rower' | (ubj2js; echo)
    "rower"
    
    $ printf "{U\x03youSU\x04suckU\x05and ISU\x05don't}" | (ubj2js; echo)
    {"you": "suck", "and I": "don't"}

    $ echo "[null, 1, 2.2, \"as\"]" | js2ubj | (ubj2js; echo)
    [null, 1, 2.2000000000000002, "as"]

    $ echo "[null, 1, 2.2, \"as\"]" | js2ubj | (ubj2js -v --pretty-print; echo)
    Before: [21]
    [#UZUD------@SUas
    Pretty-printed [71]
    [[][#][U][4]
        [Z]
        [U][1]
        [D][2.200000]
        [S][U][2][as]
    []]

    After: [35]
    [null, 1, 2.2000000000000002, "as"]
    Compression/expansion: [166%]

\subsection ubjq ubjq

    $ ubjq -h
    Usage: ubjq [-h]
    This program pretty-prints UBJSON objects to stdout.

    Examples:
        printf Z | ubjq
        printf T | ubjq
        printf F | ubjq
        printf 'U\x96' | ubjq
        printf 'i\xF0' | ubjq
        printf 'I\xDE\xAD' | ubjq
        printf 'l\xDE\xAD\xBE\xEF' | ubjq
        printf 'L\xDE\xAD\xBE\xEF\xCA\xFE\xBA\xBE' | ubjq
        printf 'd\xDE\xAD\xBE\xEF' | ubjq
        printf 'D\xDE\xAD\xBE\xEF\xCA\xFE\xBA\xBE' | ubjq
        printf 'Cr' | ubjq
        printf 'SU\x05rower' | ubjq
        printf 'HU\x0512345' | ubj2js
        printf '[]' | ubjq
        printf '[#U\x03ZTF' | ubjq
        printf '[$Z#U\xFF' | ubjq
        printf "{U\x03youSU\x04suckU\x05and ISU\x05don't}" | ubjq
        printf '{U\x03youSU\x04suck}' | ubjq
        printf '[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]' | ubjq

      -h, --help                print this help and exit


    $ printf "{U\x03youSU\x04suckU\x05and ISU\x05don't}" | ubjq
    [{]
        [U][5][and I][S][U][5][don't]
        [U][3][you][S][U][4][suck]
    [}]
    $ printf "{U\x03youSU\x04suckU\x05and ISU\x05don'tU\x01eSU\x02kr}" | ubjq
    [{][$][S][#][U][3]
        [U][5][and I][U][5][don't]
        [U][1][e][U][2][kr]
        [U][3][you][U][4][suck]
    [}]

\section main_how_do_i_use_it_library How do I use it in my code?

I assume you know how to write a C code, how to include, how to link.

Best examples are in test/test_*.c, these are the unittests that cover >=95% of use cases.
Every test_* method represents a single unittest and you should be able to easily deduct
what happens in the test (what is invoked and what is expected). Even though most of it
is C magic.

First include @ref ubjs.h "ubjs.h":

    #include <ubjs.h>

Then build the library handle. It will be used in 99% method calls:

    ubjs_library_builder *builder = 0;
    ubjs_library *lib = 0;

    ubjs_library_builder_new(&builder);
    ubjs_library_builder_build(builder, &lib);
    ubjs_library_builder_free(&builder);

Or if you customize the library underlyings:
- custom allocators
  By default, library uses malloc() and free().
- implementation of key-value objects.
  Built-in one is based on doubly-linked list,
  with obvious computational complexity of O(n * k) for operations get/put/delete, where n is number of items, and k is length of key!
  Keys are compared with naive strncmp()!
- implementation of arrays.
  Built-in one bases on plain array, expanding/shrinking on demand.

This is how you can customize the library via builder. These are also the defaults:

    ubjs_library_builder_set_alloc_f(builder, malloc);
    ubjs_library_builder_set_free_f(builder, free);
    ubjs_library_builder_set_glue_array_builder(builder,
        ubjs_glue_array_array_builder_new);
    ubjs_library_builder_set_glue_dict_builder(builder,
        ubjs_glue_dict_list_builder);

Then use some code:

\subsection main_how_do_i_use_it_library_alloc Construction and deconstruction of primitives

    ubjs_prmtv *obj;
    obj = ubjs_prmtv_null(); /* JS: null */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    obj = ubjs_prmtv_noop(); /* No-op */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    obj = ubjs_prmtv_true(); /* JS: true */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    obj = ubjs_prmtv_false(); /* JS: false */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_uint8(lib, 5, &obj); /* JS: 5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int8(lib, -5, &obj); /* JS: -5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int16(lib, 1888, &obj); /* JS: 1888 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int32(lib, 188888, &obj); /* JS: 188888 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int64(lib, 104857611, &obj); /* JS: 104857611 */
    ubjs_prmtv_free(&obj);

    /* This chooses the best int type for your value. */
    ubjs_prmtv *obj;
    ubjs_prmtv_int(lib, 5, &obj); /* JS: 5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_float32(lib, 5.11f, &obj); /* JS: 5.11f */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_float64(lib, 10.234, &obj); /* JS: 10.234 */
    ubjs_prmtv_free(&obj);
    
    ubjs_prmtv *obj;
    ubjs_prmtv_char(lib, 'r, &obj); /* JS: 'r' */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_str(lib, 11, "niesamowite", &obj); /* JS: "niesamowite" */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_hpn(lib, 6, "123.45", &obj); /* JS: "123.45" */
    ubjs_prmtv_free(&obj);

    /* Containers.
       Of course other item types are allowed.
     */
    ubjs_prmtv *obj;
    ubjs_prmtv_array_with_length(lib, 0, &obj); /* JS: [] */
    /* Or, if you do not know the desired length ahead... */
    ubjs_prmtv_array(lib, &obj); /* JS: [] */
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null()); /* JS: [null] */
    ubjs_prmtv_array_add_first(obj, ubjs_prmtv_noop()); /* JS: [noop, null] */
    ubjs_prmtv_array_add_at(obj, 1, ubjs_prmtv_true()); /* JS: [noop, true, null] */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_object(lib, &obj); /* JS: {} */
    ubjs_prmtv_object_set(5, "krowa", ubjs_prmtv_null()); /* JS: {"krowa": null} */
    ubjs_prmtv_free(&obj);

\subsection main_how_do_i_use_it_library_get Getters & setters

    /* All below assume you have somehow ubjs_prmtv *obj allocated. */

    uint8_t value;
    ubjs_prmtv_uint8_get(obj, &value);
    ubjs_prmtv_uint8_set(obj, 5);

    int8_t value;
    ubjs_prmtv_int8_get(obj, &value);
    ubjs_prmtv_int8_set(obj, -5);

    int16_t value;
    ubjs_prmtv_int16_get(obj, &value);
    ubjs_prmtv_int16_set(obj, 1000);

    int32_t value;
    ubjs_prmtv_int32_get(obj, &value);
    ubjs_prmtv_int32_set(obj, 100000);
    
    int64_t value;
    ubjs_prmtv_int64_get(obj, &value);
    ubjs_prmtv_int64_set(obj, 999999999);

    /* Regardless of underlying int-type, always returns int64. */
    int64_t value;
    ubjs_prmtv_int64_get(obj, &value);

    float32_t value;
    ubjs_prmtv_float32_get(obj, &value);
    ubjs_prmtv_float32_set(obj, 10.25f);
    
    float64_t value;
    ubjs_prmtv_float64_get(obj, &value);
    ubjs_prmtv_float64_set(obj, 10.25111111);

    char value;
    ubjs_prmtv_char_get(obj, &value);
    ubjs_prmtv_char_set(obj, 'a');

    unsigned int length;
    char *txt;
    ubjs_prmtv_str_get_length(obj, &length);
    txt = (char *)malloc(sizeof(char) * length);
    /* Note that this string is NOT null terminated. */
    ubjs_prmtv_str_copy_text(obj, txt);
    ubjs_prmtv_str_set(obj, 2, "mu");

    unsigned int length;
    char *txt;
    ubjs_prmtv_hpn_get_length(obj, &length);
    txt = (char *)malloc(sizeof(char) * length);
    /* Note that this string is NOT null terminated. */
    ubjs_prmtv_hpn_copy_text(obj, txt);
    ubjs_prmtv_hpn_set(obj, 3, "-69");

    unsigned int length;
    ubjs_prmtv *item;
    ubjs_prmtv_array_get_length(obj, &length);
    ubjs_prmtv_array_get_first(obj, &item);
    ubjs_prmtv_array_get_last(obj, &item);
    ubjs_prmtv_array_get_at(obj, 555, &item);
    /* You have already seen setters here. */
    ubjs_prmtv_array_delete_first(obj);
    ubjs_prmtv_array_delete_last(obj);
    ubjs_prmtv_array_delete_at(obj, 555);

    unsigned int length;
    ubjs_prmtv *item;
    ubjs_prmtv_object_get_length(obj, &length);
    ubjs_prmtv_object_get_at(obj, 33, "konstantynopolitanczykowianeczka", &item);
    ubjs_prmtv_object_delete(obj, "2", "mu");

\subsection main_how_do_i_use_it_library_iter Iteration over containers

    ubjs_array_iterator *i;
    ubjs_array_iterate(obj, &i);

    while (UR_OK == ubjs_array_iterator_next(i))
    {
        ubjs_prmtv *item;
        ubjs_array_iterator_get(i, &item);

        /* Do something */
    }

    ubjs_array_iterator_free(&i);

    ubjs_object_iterator *i;
    ubjs_object_iterate(obj, &i);

    while (UR_OK == ubjs_object_iterator_next(i))
    {
        unsigned int key_length;
        char *key;
        ubjs_prmtv *item;

        ubjs_object_iterator_get_key_length(i, &key_length);
        key = (char *)malloc(sizeof(char) * length);
        /* Note that this string is NOT null terminated. */
        ubjs_object_iterator_copy_key(i, key);
        ubjs_object_iterator_get_value(i, &item);

        /* Do something */

        /* Of course... */
        free(key);
    }

    ubjs_object_iterator_free(&i);

\subsection main_how_do_i_use_it_library_write Serializing primitives to streams

    struct hyper_context;
    typedef struct hyper_context hyper_context;

    void would_write(ubjs_writer_context *context, uint8_t *data,
        unsigned int len)
    {
        hyper_context *my_context = (hyper_context *)context->userdata;

        /* Now you probably want to write this to a file, socket, something. */
    }

    void afree(ubjs_writer_context *context)
    {
        hyper_context *my_context = (hyper_context *)context->userdata;

        /* Here free your context->userdata. */
        free(my_context);
    }

    /* ... */

    hyper_context *my_context;
    ubjs_writer *writer;
    ubjs_writer_context writer_context;
    
    my_context = (my_context *)malloc(0);

    writer_context.userdata = (void *)my_context;
    writer_context.would_write = would_write;
    writer_context.would_print = 0;
    writer_context.free = afree;

    ubjs_writer_new(lib, &writer, &writer_context);
    
    /* ... */
    
    ubjs_writer_write(writer, ubjs_prmtv_null());
    
    ubjs_prmtv *array;
    ubjs_prmtv_array(&array);
    /* ... */
    ubjs_writer_write(writer, array);
    ubjs_prmtv_free(&array);
    
    /* ... */
    
    ubjs_writer_free(&writer);

If you want to pretty-print the primitive, use ubjs_writer_print() instead and implemented
writer_context.would_print method.

\subsection main_how_do_i_use_it_library_parse Parsing primitives from a stream

    void parsed(ubjs_parser_context *context, ubjs_prmtv *object)
    {
        hyper_context *my_context = (hyper_context *)context->userdata;

        /* Now you would do something with the primitive. */

        ubjs_prmtv_free(&object);
    }

    void aerror(ubjs_parser_context *context, ubjs_parser_error *error)
    {
        hyper_context *my_context = (hyper_context *)context->userdata;

        unsigned int length;
        char *message;

        ubjs_parser_error_get_message_length(error, &length);
        message = (char *)malloc(sizeof(char) * (length+1));
        ubjs_parser_error_get_message_text(error, message);
        message[length] = 0;

        fprintf(stderr, "Parser error: %s\n", message);

        free(message);
    }

    void afree(ubjs_parser_context *context)
    {
        hyper_context *my_context = (hyper_context *)context->userdata;

        /* Here free your context->userdata. */
        free(my_context);
    }

    /* ... */

    hyper_context *my_context;
    ubjs_parser *parser;
    ubjs_parser_context parser_context;
    
    my_context = (my_context *)malloc(0);
    
    parser_context.userdata = (void *)my_context;
    parser_context.parsed = parsed;
    parser_context.error = aerror;
    parser_context.free = afree;

    ubjs_parser_new(lib, 0, &parser_context, &parser);

    #ifdef OR
    /* Optionally... */
    ubjs_parser_settings settings;

    settings.limit_bytes_since_last_callback = 3;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;

    ubjs_parser_new(lib, &settings, &parser_context, &parser);
    #endif
    
    /* Now you would get some data. */
    
    uint8_t data = "GET / HTTP/1.0\r\nConnection: close\r\n\r\n";
    ubjs_parser_parse(parser, 37, data);
    
    /* Now you would get even more data. 
       And someday... */

    ubjs_parser_free(&parser);

\section main_deinitialize_library Do not forget to uninitialize library handle!

    ubjs_library_free(&lib);

\subsection main_how_do_i_use_it_python Python

You can use generated ubjspy library in Python. It contains compiled library of ubjsc
and linkage stuff for Python. Library exposes ubjspy module with exposed methods
dump()/dumps()/pretty_print()/pretty_prints()/load()/loads(), that follow the example
of (json)[https://docs.python.org/3/library/json.html].

- dump() and dumps() converts Python object from parameter 1 to UBJSON.
- pretty_print() and pretty_prints() converts Python object from parameter 1 to UBJSON pretty print.
- load() and loads() reads UBJSON input and returns Python objects.
- dumps(), pretty_prints() and loads() respectively return bytes() and string, and expects bytes.
- dump(), pretty_print() and load() respectively expect BufferedIOBase and TextIOBase (especially
  BytesIO and StringIO) and expects a BytesIO.

    Python 3.5.2+ (default, Sep 22 2016, 12:18:14) 
    [GCC 6.2.0 20160927] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import ubjspy
    >>> ubjspy
    <module 'ubjspy' from '/opt/atlassian/bitbucketci/agent/build/build/env/lib/python3.5/site-packages/ubjspy.cpython-35m-x86_64-linux-gnu.so'>
    >>> ubjspy.loads(b'Z')
    >>> ubjspy.loads(b'N')
    <ubjspy.NoopType object at 0x7f38a19e2080>
    >>> ubjspy.loads(b'T')
    True
    >>> ubjspy.loads(b'F')
    False
    >>> ubjspy.loads(b'U\x96')
    150
    >>> ubjspy.loads(b'i\xF0')
    -16
    >>> ubjspy.loads(b'I\xDE\xAD')
    -21026
    >>> ubjspy.loads(b'Cr')
    'r'
    >>> ubjspy.loads(b'SU\x05rower')
    'rower'
    >>> ubjspy.loads(b'{U\x03youSU\x04suckU\x05and ISU\x05don"t}')
    {'you': 'suck', 'and I': 'don"t'}    

        printf '[$Z#U\xFF' | ubjq
        printf "{U\x03youSU\x04suckU\x05and ISU\x05don't}" | ubjq
        printf '{U\x03youSU\x04suck}' | ubjq
        printf '[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]' | ubjq
    >>> ubjspy.dumps(ubjspy.loads(b'[$Z#U\xFF'))
    b'[$Z#U\xff'
    >>> ubjspy.dumps([[None] * 10000])
    b"[[$Z#I\x10']"
    >>> ubjspy.pretty_prints(ubjspy.loads(b'[$Z#U\xFF'))
    '[[][$][Z][#][U][255][]]'

    >>> from io import BytesIO
    >>> data = BytesIO()
    >>> ubjspy.dump([[[[[]]]]], data)
    >>> data.getvalue()
    b'[[[[[]]]]]'
    >>> ubjspy.load(BytesIO(data.getvalue()))
    [[[[[]]]]]

    >>> from io import StringIO
    >>> data = StringIO()
    >>> ubjspy.pretty_print([[[[[]]]]], data)
    >>> data.getvalue()
    '[[]\n    [[]\n        [[]\n            [[]\n                [[][]]\n            []]\n        []]\n    []]\n[]]'
    >>> print(data.getvalue())
    [[]
        [[]
            [[]
                [[]
                    [[][]]
                []]
            []]
        []]
    []]

\section main_how_do_i_upgrade How do I upgrade?

\subsection main_how_do_i_upgrade_04_05 From 0.4 to 0.5

Debugging stuff now does real work only when compiled with debugging symbols, as they impact performance a lot.
Build the library with CMAKE_BUILD_TYPE=Debug to have them back.

You can use HPN-s now in Python (via decimal.Decimal).

Previously introduced library initialization via ubjs_library_new() was removed, in favor of a builder pattern - ubjs_library_builder.
Use it to initialize the library.

In the future there are no plans to remove it, only to expand into new methods.

Via library builder you can choose a custom dictionary/array implementation - so called dict/array glue,
via methods ubjs_library_builder_set_glue_dict_factory() and ubjs_library_builder_set_glue_array_factory.
Ubjsc contains default glues:
- dictionary is based on doubly-linked list, keys are naive C-strings,
- arrays are based on array expanding/shrinking on demand.
keys are naive C-strings).
Watch out for their complexities:
- dictionary get/put/delete are is O(n * k)! Of course n is size of the container, k is size of key in characters,
- array get is O(1), put and delete are O(n).

For development of custom glues, you can re-use the default API test suite for both dictionary and array glues.
This is far from ideal, but this can be any help. The test suite checks basic API calls
and runs a short performance test.
See ubjsc/src/ubjs_glue_*.{c,h} and ubjsc/test/test_main_glues.c for examples.

For now, previous linkage to ptrie library is retained via ubjs-glue-dict-ptrie library, and right now it lies in same repository.
To use this glue, you need to explicitely link to the library and pass the factory to library builder.
Temporarily ubjspy also embeds ptrie glue.
The plan is to move ptrie glue to separate repository.

\subsection main_how_do_i_upgrade_03_04 From 0.3 to 0.4

You must initialize the library handle via ubjs_library_new() (or, if you are using defaults anyway - ubjs_library_stdlib()), and the library handle must be passed to
ubjs_parser_new(), ubjs_writer_new() and ubjs_prmtv_*(). Thus they all have changed syntax.

ubjs_parser_new() accepts now security settings, that can partially prevent from crashing your app
when malicious input arrives.

Added basic support for high-precision numbers.

In case you run into problems while parsing, you can turn on the debugger. See ubjs_parser_settings.debug.

\subsection main_how_do_i_upgrade_02_03 From 0.2 to 0.3

Argtable2 and jansson libraries are no longer included nor fetched as subrepositories.
You need to get them separately, either getting binaries or building them. Especially on Windows.

Indentations were introduced in pretty-printouts.

\section main_licences Licences

    MIT License

    Copyright (c) 2016 Tomasz Sieprawski

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

\section main_contact Contact

You can post your suggestions/ideas/issues to https://bitbucket.org/tsieprawski/ubjsc/issues .

Of course all pull requests are fine to be discussed and probably someday merged!

Contact me at:

    Tomasz Sieprawski <tomasz@sieprawski.eu>
