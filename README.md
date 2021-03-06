[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/534/badge)](https://bestpractices.coreinfrastructure.org/projects/534)
[![Coverage Status](https://coveralls.io/repos/bitbucket/tsieprawski/ubjsc/badge.svg?branch=default)](https://coveralls.io/bitbucket/tsieprawski/ubjsc?branch=default)

# What is ubjsc?

ubjsc is an enterprise grade-wannabe C library for manipulating and streaming data in [UBJSON](http://www.ubjson.org/) format.

Right now, you can:

- asynchronously parse UBJSON stream to C "objects",
- dump these C "objects" to UBJSON streams,
- pretty-print them,
- "manipulate" them as first class citizens.

For real-life examples of UBJSON that are supported, go to [working examples](#example).

# How do I build/install it?

\todo Mac OS X

## Windows
### Prerequisites

- Install [CMake >= 3.3](https://cmake.org).
- Have a C compiler. Visual Studio Community 2015 works fine.
- Install library & developer headers of [jansson](http://www.digip.org/jansson/) >= 2.10.
    Don't ask me how to do it.
- Install library & developer headers of [argtable2](http://bitbucket.org/tsieprawski/argtable2).
    Don't ask me how to do it.
- If you want to run API tests, install library & developer headers of [criterion](https://github.com/Snaipe/Criterion) >= 2.3.1.
    Don't ask me how to do it.

For development purposes:

- Install library & developer headers of [criterion]https://github.com/Snaipe/Criterion/).
    Don't ask me how to do it.

Other compilers (like cygwin/clang) should work, but I did not test them.

#### Optional: Python

Optionally if you want to generate Python wheel, you need:
  - [Python >=3.4](https://python.org).

### Building @ VSC 2015

- Build jansson, argtable2 and criterion and INSTALL them somewhere (note where). Do not ask me how to do it.
- Run CMake-GUI (probably from `Z:\\WHERE_YOU_INSTALLED_CMAKE\\bin\\cmake-gui.exe`.
- In `Where is the source code` point to ubjsc.
- In `Where to build the binaries` point to ubjsc/build. Or anywhere you like.
- Click `Configure`.
- In "Specify the generator for the project" select `Visual Studio 14 2015 Win64`.
- Configure `JANSSON_EXPORT_DIR` and `ARGTABLE2_EXPORT_DIR` variables to point to `INSTALL` folders.
- Click `Finish`.
- If everything goes fine, "Generate" button gets active.
- Probably you want to configure `CMAKE_INSTALL_PREFIX` variable.
- Click `Generate`.
- Open `ubjsc/build/ubjsc.sln`.
- Build "ALL" target.

Install:

- Build `INSTALL` target.

If you want to run test suite:

- Build `RUN_TESTS` target.

## Linux
### Prerequisites

- Install [CMake >= 3.3](https://cmake.org). If you know how to use CMake, you do not have to read
- Have at least `gcc` and `make` commands available. Probably this involves installing GCC and
  Autotools, but I won't direct you to correct packages.
- Install library & developer headers of [jansson](http://www.digip.org/jansson/) >= 2.10.
    Don't ask me how to do it.
- Install library & developer headers of [argtable2](http://bitbucket.org/tsieprawski/argtable2).
    Don't ask me how to do it.
- If you want to run API tests, install library & developer headers of [criterion](https://github.com/Snaipe/Criterion) >= 2.3.1.
    Don't ask me how to do it.

For development purposes:

- Install library & developer headers of [criterion]https://github.com/Snaipe/Criterion/).
    Don't ask me how to do it.

Other compilers (like clang) should work, but I did not test them.

#### Optional: Python

Optionally if you want to generate Python wheel, you need [Python >=3.4](https://python.org).

### Building GNU+Autotools

Prepare project:

     ubjsc $ mkdir build && cd build
     ubjsc/build $ cmake ..

Build it:

     ubjsc/build $ make

Install:

     ubjsc/build $ sudo make install

If you want to run tests:

#### API tests

    ubjsc/build $ cmake -DWITH_TESTING=ON ..
    ubjsc/build $ ctest . # Or $ make test

#### Stress tests

Be warned, that these should, and are taking a lot of time.

    ubjsc/build $ cmake -DWITH_TESTING=ON -DWITH_API_TESTING=OFF -DWITH_STRESS_TESTING=ON ..
    ubjsc/build $ ctest . # Or $ make test

### Python

After building, Python .whl should be in the build folder. You can import it with:

    pip3 install ubjspy*.whl

# How do I use it right away?

There are 3 tools that you can use right away.

## js2ubj

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
    Pretty-printed [67]: [[][#][U][4]
        [Z]
        [U][1]
        [D][2.200000]
        [S][U][2][as]


## ubj2js

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
    Pretty-printed [67]
    [[][#][U][4]
        [Z]
        [U][1]
        [D][2.200000]
        [S][U][2][as]

    After: [35]
    [null, 1, 2.2000000000000002, "as"]
    Compression/expansion: [166%]

## ubjq

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

## Working examples<a name='example'></a>

See `tools/test` folder, that facilitaties various tests for these tools.
Yeah, these are cryptic, but you should figure out them using `*.sh` test scripts.

# How do I use it in my code?

I assume you know how to write a C code, how to include, how to link.

Best examples are in `ubjsc/test/api/test_*.c`. These are the API tests that cover >=95% of use cases.
Every `test_*` method represents a single API test and you should be able to easily deduct
what happens in the test (what is invoked and what is expected). Even though most of it
is C magic.

First include `ubjs.h`:

    #include <ubjs.h>

Then build the library handle. It will be used in 99% method calls:

    ubjs_library_builder builder;
    ubjs_library *lib = 0;

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_build(&builder, &lib);

You can customize the library underlyings:

- custom allocators.

  By default, library uses `malloc()` and `free()`.

- implementation of key-value objects.

  Built-in one is based on doubly-linked list,
  with obvious computational complexity of O(n * k) for operations get/put/delete, where n is number of items, and k is length of key!
  Keys are compared with naive strncmp()!

- implementation of arrays.

  Built-in one bases on plain array, expanding/shrinking on demand.

This is how you can customize the library via builder. These are also the defaults:

    ubjs_library_builder_set_alloc_f(&builder, malloc);
    ubjs_library_builder_set_free_f(&builder, free);
    ubjs_library_builder_set_glue_array_builder(&builder,
        ubjs_glue_array_array_builder_new);
    ubjs_library_builder_set_glue_dict_builder(&builder,
        ubjs_glue_dict_list_builder);

Of course nothing prevents you from building more than 1 library from a builder.
Just not sure why.

Then use some code:

## Construction and deconstruction of primitives

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

## Getters & setters

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

## Iteration over containers

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

## Writing primitives to streams

    struct hyper_context;
    typedef struct hyper_context hyper_context;

    void would_write(void *userdata, uint8_t *data,
        unsigned int len)
    {
        hyper_context *my_context = (hyper_context *)userdata;

        /* Now you probably want to write this to a file, socket, something. */
    }

    void afree(void *context)
    {
        hyper_context *my_context = (hyper_context *)userdata;

        /* Here free your context->userdata. */
        free(my_context);
    }

    /* ... */

    hyper_context *my_context;
    ubjs_writer_builder *builder = 0;
    ubjs_writer *writer = 0;
    ubjs_writer_context writer_context;

    my_context = (my_context *)malloc(0);

    ubjs_writer_builder_new(lib, &builder);
    ubjs_writer_builder_set_userdata(builder, my_context);
    ubjs_writer_builder_set_would_write_f(builder, would_write);
    ubjs_writer_builder_set_would_print_f(builder, ubj2js_main_writer_context_would_print);
    ubjs_writer_builder_set_free_f(builder, afree);

    /* You may want to debug that writer is writing and how.
     * ubjsc must be build with debugging symbols, and then you can set
     * this callback.
     * Note that this obviously has a serious performance impact. */
    void adebug(void *context, unsigned int len, char *message)
    {
        fprintf(stderr, "Debug: %.*s\n", len, message);
    }

    ubjs_writer_builder_set_debug_f(builder, adebug);

    ubjs_writer_builder_build(builder, &writer);
    ubjs_writer_builder_free(&builder);

    /* ... */

    ubjs_writer_write(writer, ubjs_prmtv_null());

    ubjs_prmtv *array;
    ubjs_prmtv_array(&array);
    /* ... */
    ubjs_writer_write(writer, array);
    ubjs_prmtv_free(&array);

    /* ... */

    ubjs_writer_free(&writer);

If you want to pretty-print the primitive, use `ubjs_writer_print()` instead and implemend
`writer_context.would_print` method.

## Parsing primitives from a stream

    void parsed(void *context, ubjs_prmtv *object)
    {
        hyper_context *my_context = (hyper_context *)context;

        /* Now you would do something with the primitive. */
        ubjs_prmtv_free(&object);
    }

    void aerror(void *context, ubjs_parser_error *error)
    {
        hyper_context *my_context = (hyper_context *)context;

        unsigned int length;
        char *message;

        ubjs_parser_error_get_message_length(error, &length);
        message = (char *)malloc(sizeof(char) * (length+1));
        ubjs_parser_error_get_message_text(error, message);
        message[length] = 0;

        fprintf(stderr, "Parser error: %s\n", message);

        free(message);
    }

    void afree(void *context)
    {
        hyper_context *my_context = (hyper_context *)context;

        /* Here free your context->userdata. */
        free(my_context);
    }

    /* ... */

    hyper_context *my_context;
    ubjs_parser_builder *builder = 0;
    ubjs_parser *parser = 0;
    ubjs_parser_context parser_context;

    my_context = (my_context *)malloc(0);

    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, my_context);
    ubjs_parser_builder_set_parsed_f(builder, my_context);

    /* Optionally... */
    #ifdef OR
    ubjs_parser_builder_set_error_f(builder, aerror);
    ubjs_parser_builder_set_free_f(builder, afree);
    ubjs_parser_builder_set_limit_bytes_since_last_callback(builder, 3);
    ubjs_parser_builder_set_limit_container_length(builder, 3);
    ubjs_parser_builder_set_limit_string_length(builder, 3);
    ubjs_parser_builder_set_recursion_level(builder, 3);

    /* You may want to debug that parser is parsing and how.
     * ubjsc must be build with debugging symbols, and then you can set
     * this callback.
     * Note that this obviously has a serious performance impact. */
    void adebug(void *context, unsigned int len, char *message)
    {
        fprintf(stderr, "Debug: %.*s\n", len, message);
    }

    ubjs_parser_builder_set_debug_f(builder, adebug);
    #endif

    ubjs_parser_builder_build(builder, &parser);

    /* Of course you can build as many parsers as you want, from a single builder.
       Still you want to destroy it as soon as possible. */
    ubjs_parser_builder_free(&builder);

    /* Now you would get some data. */
    uint8_t data = "GET / HTTP/1.0\r\nConnection: close\r\n\r\n";
    ubjs_parser_parse(parser, 37, data);

    /* Now you would get even more data.
       And someday... */
    ubjs_parser_free(&parser);

## Do not forget to uninitialize library handle!

    ubjs_library_free(&lib);

# Python

You can use generated ubjspy library in Python. It contains compiled library of ubjsc
and linkage stuff for Python. Library exposes ubjspy module with exposed methods
`dump()`/`dumps()`/`pretty_print()`/`pretty_prints()`/`load()`/`loads()`, that follow the example
of [json](https://docs.python.org/3/library/json.html).

- `dump()` and `dumps()` converts Python object from parameter 1 to UBJSON.
- `pretty_print()` and `pretty_prints()` converts Python object from parameter 1 to UBJSON pretty print.
- `load()` and `loads()` reads UBJSON input and returns Python objects.
- `dumps()`, `pretty_prints()` and `loads()` respectively return `bytes` and `string`, and expects `bytes`.
- `dump()`, `pretty_print()` and `load()` respectively expect `BufferedIOBase` and `TextIOBase` (especially
  `BytesIO` and `StringIO`) and expects a `BytesIO`.

<!--alex disable retext-equality retext-profanities-->

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
    >>> ubjspy.dumps(ubjspy.loads(b'[$Z#U\xFF'))
    b'[$Z#U\xff'
    >>> ubjspy.dumps([[None] * 10000])
    b"[[$Z#I\x10']"
    >>> ubjspy.pretty_prints(ubjspy.loads(b'[$Z#U\xFF'))
    '[[][$][Z][#][U][255]'
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

<!--alex enable retext-equality retext-profanities-->

# Technical stuff
## Compatibility
- `ubjsc` alone is ANSI-C-compatible, while tools and `ubjspy` are >=C99 compatible
## Memory management
- By default, all code uses stdlib's `malloc()` and `free()`. You can pass custom allocator to library builder.
- Allocation errors are **NOT** handled in any way. If `malloc()` fails, code will happily go on (probably crashing).
## Threading-ness
- There is no implicit global context of the library. User creates context objects and passes them everywhere.
- Library does not use threading at all. So... There should be no problems with threading.
- Same with forking - it should work, because code does not rely on any global state.
- Thus library does not use private worker threads.
## I/O
- Library does not use any input/output. Although this library parses and serializes stuff, nothing actually
is performed to any I/O layer. User is responsible for inputting data to parse and outputting serialized data
to the world.

# Licenses

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

# Contact

You can post your suggestions/ideas/issues to https://bitbucket.org/tsieprawski/ubjsc/issues .

Of course all pull requests are fine to be discussed and probably someday merged!

Contact me at:

    Tomasz Sieprawski <tomasz@sieprawski.eu>
