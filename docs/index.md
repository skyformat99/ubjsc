\mainpage

\tableofcontents

\section main_what_is_ubjsc What is ubjsc?

ubjsc is a C library for manipulating data in [UBJSON](http://www.ubjson.org/) format.

\section wain_what_is_included What is included?

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

Building @ VSC 2015
===================

- Build jansson and argtable2 using CMake and INSTALL them somewhere (note where). Do not ask me how to do it.
- Run CMake-GUI (probably from Z:\WHERE_YOU_INSTALLED_CMAKE\bin\cmake-gui.exe).
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

\section main_how_do_i_use_it_tools How do I use it right away?

There are 3 tools that you can use right away.

\subsection js2ubj js2ubj

    $ js2ubj  -h
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
    ubjs_prmtv_uint8(5, &obj); /* JS: 5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int8(-5, &obj); /* JS: -5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int16(1888, &obj); /* JS: 1888 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int32(188888, &obj); /* JS: 188888 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_int64(104857611, &obj); /* JS: 104857611 */
    ubjs_prmtv_free(&obj);

    /* This chooses the best int type for your value. */
    ubjs_prmtv *obj;
    ubjs_prmtv_int(5, &obj); /* JS: 5 */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_float32(5.11f, &obj); /* JS: 5.11f */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_float64(10.234, &obj); /* JS: 10.234 */
    ubjs_prmtv_free(&obj);
    
    ubjs_prmtv *obj;
    ubjs_prmtv_char('r, &obj); /* JS: 'r' */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_str(11, "niesamowite", &obj); /* JS: "niesamowite" */
    ubjs_prmtv_free(&obj);

    /* Containers.
       Of course other item types are allowed.
     */
    ubjs_prmtv *obj;
    ubjs_prmtv_array(&obj); /* JS: [] */
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null()); /* JS: [null] */
    ubjs_prmtv_array_add_first(obj, ubjs_prmtv_noop()); /* JS: [noop, null] */
    ubjs_prmtv_array_add_at(obj, 1, ubjs_prmtv_true()); /* JS: [noop, true, null] */
    ubjs_prmtv_free(&obj);

    ubjs_prmtv *obj;
    ubjs_prmtv_object(&obj); /* JS: {} */
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

    ubjs_writer_new(&writer, &writer_context);
    
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
    ubjs_parser_new(&parser, &parser_context);
    
    /* Now you would get some data. */
    
    uint8_t data = "GET / HTTP/1.0\r\nConnection: close\r\n\r\n";
    ubjs_parser_parse(parser, 37, data);
    
    /* Now you would get even more data. 
       And someday... */

    ubjs_parser_free(&parser);

\section main_licences Licences

For docs, include, src, test, tools, everything top:

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

For argtable2/*:

              GNU LIBRARY GENERAL PUBLIC LICENSE
                   Version 2, June 1991

     Copyright (C) 1991 Free Software Foundation, Inc.
     59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
     Everyone is permitted to copy and distribute verbatim copies
     of this license document, but changing it is not allowed.

    [This is the first released version of the library GPL.  It is
     numbered 2 because it goes with version 2 of the ordinary GPL.]

                    Preamble

      The licenses for most software are designed to take away your
    freedom to share and change it.  By contrast, the GNU General Public
    Licenses are intended to guarantee your freedom to share and change
    free software--to make sure the software is free for all its users.

      This license, the Library General Public License, applies to some
    specially designated Free Software Foundation software, and to any
    other libraries whose authors decide to use it.  You can use it for
    your libraries, too.

      When we speak of free software, we are referring to freedom, not
    price.  Our General Public Licenses are designed to make sure that you
    have the freedom to distribute copies of free software (and charge for
    this service if you wish), that you receive source code or can get it
    if you want it, that you can change the software or use pieces of it
    in new free programs; and that you know you can do these things.

      To protect your rights, we need to make restrictions that forbid
    anyone to deny you these rights or to ask you to surrender the rights.
    These restrictions translate to certain responsibilities for you if
    you distribute copies of the library, or if you modify it.

      For example, if you distribute copies of the library, whether gratis
    or for a fee, you must give the recipients all the rights that we gave
    you.  You must make sure that they, too, receive or can get the source
    code.  If you link a program with the library, you must provide
    complete object files to the recipients so that they can relink them
    with the library, after making changes to the library and recompiling
    it.  And you must show them these terms so they know their rights.

      Our method of protecting your rights has two steps: (1) copyright
    the library, and (2) offer you this license which gives you legal
    permission to copy, distribute and/or modify the library.

      Also, for each distributor's protection, we want to make certain
    that everyone understands that there is no warranty for this free
    library.  If the library is modified by someone else and passed on, we
    want its recipients to know that what they have is not the original
    version, so that any problems introduced by others will not reflect on
    the original authors' reputations.
    
      Finally, any free program is threatened constantly by software
    patents.  We wish to avoid the danger that companies distributing free
    software will individually obtain patent licenses, thus in effect
    transforming the program into proprietary software.  To prevent this,
    we have made it clear that any patent must be licensed for everyone's
    free use or not licensed at all.

      Most GNU software, including some libraries, is covered by the ordinary
    GNU General Public License, which was designed for utility programs.  This
    license, the GNU Library General Public License, applies to certain
    designated libraries.  This license is quite different from the ordinary
    one; be sure to read it in full, and don't assume that anything in it is
    the same as in the ordinary license.

      The reason we have a separate public license for some libraries is that
    they blur the distinction we usually make between modifying or adding to a
    program and simply using it.  Linking a program with a library, without
    changing the library, is in some sense simply using the library, and is
    analogous to running a utility program or application program.  However, in
    a textual and legal sense, the linked executable is a combined work, a
    derivative of the original library, and the ordinary General Public License
    treats it as such.

      Because of this blurred distinction, using the ordinary General
    Public License for libraries did not effectively promote software
    sharing, because most developers did not use the libraries.  We
    concluded that weaker conditions might promote sharing better.

      However, unrestricted linking of non-free programs would deprive the
    users of those programs of all benefit from the free status of the
    libraries themselves.  This Library General Public License is intended to
    permit developers of non-free programs to use free libraries, while
    preserving your freedom as a user of such programs to change the free
    libraries that are incorporated in them.  (We have not seen how to achieve
    this as regards changes in header files, but we have achieved it as regards
    changes in the actual functions of the Library.)  The hope is that this
    will lead to faster development of free libraries.

      The precise terms and conditions for copying, distribution and
    modification follow.  Pay close attention to the difference between a
    "work based on the library" and a "work that uses the library".  The
    former contains code derived from the library, while the latter only
    works together with the library.

      Note that it is possible for a library to be covered by the ordinary
    General Public License rather than by this special one.
    
              GNU LIBRARY GENERAL PUBLIC LICENSE
       TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

      0. This License Agreement applies to any software library which
    contains a notice placed by the copyright holder or other authorized
    party saying it may be distributed under the terms of this Library
    General Public License (also called "this License").  Each licensee is
    addressed as "you".

      A "library" means a collection of software functions and/or data
    prepared so as to be conveniently linked with application programs
    (which use some of those functions and data) to form executables.

      The "Library", below, refers to any such software library or work
    which has been distributed under these terms.  A "work based on the
    Library" means either the Library or any derivative work under
    copyright law: that is to say, a work containing the Library or a
    portion of it, either verbatim or with modifications and/or translated
    straightforwardly into another language.  (Hereinafter, translation is
    included without limitation in the term "modification".)

      "Source code" for a work means the preferred form of the work for
    making modifications to it.  For a library, complete source code means
    all the source code for all modules it contains, plus any associated
    interface definition files, plus the scripts used to control compilation
    and installation of the library.

      Activities other than copying, distribution and modification are not
    covered by this License; they are outside its scope.  The act of
    running a program using the Library is not restricted, and output from
    such a program is covered only if its contents constitute a work based
    on the Library (independent of the use of the Library in a tool for
    writing it).  Whether that is true depends on what the Library does
    and what the program that uses the Library does.
      
      1. You may copy and distribute verbatim copies of the Library's
    complete source code as you receive it, in any medium, provided that
    you conspicuously and appropriately publish on each copy an
    appropriate copyright notice and disclaimer of warranty; keep intact
    all the notices that refer to this License and to the absence of any
    warranty; and distribute a copy of this License along with the
    Library.

      You may charge a fee for the physical act of transferring a copy,
    and you may at your option offer warranty protection in exchange for a
    fee.
    
      2. You may modify your copy or copies of the Library or any portion
    of it, thus forming a work based on the Library, and copy and
    distribute such modifications or work under the terms of Section 1
    above, provided that you also meet all of these conditions:

        a) The modified work must itself be a software library.

        b) You must cause the files modified to carry prominent notices
        stating that you changed the files and the date of any change.

        c) You must cause the whole of the work to be licensed at no
        charge to all third parties under the terms of this License.

        d) If a facility in the modified Library refers to a function or a
        table of data to be supplied by an application program that uses
        the facility, other than as an argument passed when the facility
        is invoked, then you must make a good faith effort to ensure that,
        in the event an application does not supply such function or
        table, the facility still operates, and performs whatever part of
        its purpose remains meaningful.

        (For example, a function in a library to compute square roots has
        a purpose that is entirely well-defined independent of the
        application.  Therefore, Subsection 2d requires that any
        application-supplied function or table used by this function must
        be optional: if the application does not supply it, the square
        root function must still compute square roots.)

    These requirements apply to the modified work as a whole.  If
    identifiable sections of that work are not derived from the Library,
    and can be reasonably considered independent and separate works in
    themselves, then this License, and its terms, do not apply to those
    sections when you distribute them as separate works.  But when you
    distribute the same sections as part of a whole which is a work based
    on the Library, the distribution of the whole must be on the terms of
    this License, whose permissions for other licensees extend to the
    entire whole, and thus to each and every part regardless of who wrote
    it.

    Thus, it is not the intent of this section to claim rights or contest
    your rights to work written entirely by you; rather, the intent is to
    exercise the right to control the distribution of derivative or
    collective works based on the Library.

    In addition, mere aggregation of another work not based on the Library
    with the Library (or with a work based on the Library) on a volume of
    a storage or distribution medium does not bring the other work under
    the scope of this License.

      3. You may opt to apply the terms of the ordinary GNU General Public
    License instead of this License to a given copy of the Library.  To do
    this, you must alter all the notices that refer to this License, so
    that they refer to the ordinary GNU General Public License, version 2,
    instead of to this License.  (If a newer version than version 2 of the
    ordinary GNU General Public License has appeared, then you can specify
    that version instead if you wish.)  Do not make any other change in
    these notices.
    
      Once this change is made in a given copy, it is irreversible for
    that copy, so the ordinary GNU General Public License applies to all
    subsequent copies and derivative works made from that copy.

      This option is useful when you wish to copy part of the code of
    the Library into a program that is not a library.

      4. You may copy and distribute the Library (or a portion or
    derivative of it, under Section 2) in object code or executable form
    under the terms of Sections 1 and 2 above provided that you accompany
    it with the complete corresponding machine-readable source code, which
    must be distributed under the terms of Sections 1 and 2 above on a
    medium customarily used for software interchange.

      If distribution of object code is made by offering access to copy
    from a designated place, then offering equivalent access to copy the
    source code from the same place satisfies the requirement to
    distribute the source code, even though third parties are not
    compelled to copy the source along with the object code.

      5. A program that contains no derivative of any portion of the
    Library, but is designed to work with the Library by being compiled or
    linked with it, is called a "work that uses the Library".  Such a
    work, in isolation, is not a derivative work of the Library, and
    therefore falls outside the scope of this License.

      However, linking a "work that uses the Library" with the Library
    creates an executable that is a derivative of the Library (because it
    contains portions of the Library), rather than a "work that uses the
    library".  The executable is therefore covered by this License.
    Section 6 states terms for distribution of such executables.

      When a "work that uses the Library" uses material from a header file
    that is part of the Library, the object code for the work may be a
    derivative work of the Library even though the source code is not.
    Whether this is true is especially significant if the work can be
    linked without the Library, or if the work is itself a library.  The
    threshold for this to be true is not precisely defined by law.

      If such an object file uses only numerical parameters, data
    structure layouts and accessors, and small macros and small inline
    functions (ten lines or less in length), then the use of the object
    file is unrestricted, regardless of whether it is legally a derivative
    work.  (Executables containing this object code plus portions of the
    Library will still fall under Section 6.)

      Otherwise, if the work is a derivative of the Library, you may
    distribute the object code for the work under the terms of Section 6.
    Any executables containing that work also fall under Section 6,
    whether or not they are linked directly with the Library itself.
    
      6. As an exception to the Sections above, you may also compile or
    link a "work that uses the Library" with the Library to produce a
    work containing portions of the Library, and distribute that work
    under terms of your choice, provided that the terms permit
    modification of the work for the customer's own use and reverse
    engineering for debugging such modifications.

      You must give prominent notice with each copy of the work that the
    Library is used in it and that the Library and its use are covered by
    this License.  You must supply a copy of this License.  If the work
    during execution displays copyright notices, you must include the
    copyright notice for the Library among them, as well as a reference
    directing the user to the copy of this License.  Also, you must do one
    of these things:

        a) Accompany the work with the complete corresponding
        machine-readable source code for the Library including whatever
        changes were used in the work (which must be distributed under
        Sections 1 and 2 above); and, if the work is an executable linked
        with the Library, with the complete machine-readable "work that
        uses the Library", as object code and/or source code, so that the
        user can modify the Library and then relink to produce a modified
        executable containing the modified Library.  (It is understood
        that the user who changes the contents of definitions files in the
        Library will not necessarily be able to recompile the application
        to use the modified definitions.)

        b) Accompany the work with a written offer, valid for at
        least three years, to give the same user the materials
        specified in Subsection 6a, above, for a charge no more
        than the cost of performing this distribution.

        c) If distribution of the work is made by offering access to copy
        from a designated place, offer equivalent access to copy the above
        specified materials from the same place.

        d) Verify that the user has already received a copy of these
        materials or that you have already sent this user a copy.

      For an executable, the required form of the "work that uses the
    Library" must include any data and utility programs needed for
    reproducing the executable from it.  However, as a special exception,
    the source code distributed need not include anything that is normally
    distributed (in either source or binary form) with the major
    components (compiler, kernel, and so on) of the operating system on
    which the executable runs, unless that component itself accompanies
    the executable.

      It may happen that this requirement contradicts the license
    restrictions of other proprietary libraries that do not normally
    accompany the operating system.  Such a contradiction means you cannot
    use both them and the Library together in an executable that you
    distribute.
    
      7. You may place library facilities that are a work based on the
    Library side-by-side in a single library together with other library
    facilities not covered by this License, and distribute such a combined
    library, provided that the separate distribution of the work based on
    the Library and of the other library facilities is otherwise
    permitted, and provided that you do these two things:

        a) Accompany the combined library with a copy of the same work
        based on the Library, uncombined with any other library
        facilities.  This must be distributed under the terms of the
        Sections above.

        b) Give prominent notice with the combined library of the fact
        that part of it is a work based on the Library, and explaining
        where to find the accompanying uncombined form of the same work.

      8. You may not copy, modify, sublicense, link with, or distribute
    the Library except as expressly provided under this License.  Any
    attempt otherwise to copy, modify, sublicense, link with, or
    distribute the Library is void, and will automatically terminate your
    rights under this License.  However, parties who have received copies,
    or rights, from you under this License will not have their licenses
    terminated so long as such parties remain in full compliance.

      9. You are not required to accept this License, since you have not
    signed it.  However, nothing else grants you permission to modify or
    distribute the Library or its derivative works.  These actions are
    prohibited by law if you do not accept this License.  Therefore, by
    modifying or distributing the Library (or any work based on the
    Library), you indicate your acceptance of this License to do so, and
    all its terms and conditions for copying, distributing or modifying
    the Library or works based on it.

      10. Each time you redistribute the Library (or any work based on the
    Library), the recipient automatically receives a license from the
    original licensor to copy, distribute, link with or modify the Library
    subject to these terms and conditions.  You may not impose any further
    restrictions on the recipients' exercise of the rights granted herein.
    You are not responsible for enforcing compliance by third parties to
    this License.
    
      11. If, as a consequence of a court judgment or allegation of patent
    infringement or for any other reason (not limited to patent issues),
    conditions are imposed on you (whether by court order, agreement or
    otherwise) that contradict the conditions of this License, they do not
    excuse you from the conditions of this License.  If you cannot
    distribute so as to satisfy simultaneously your obligations under this
    License and any other pertinent obligations, then as a consequence you
    may not distribute the Library at all.  For example, if a patent
    license would not permit royalty-free redistribution of the Library by
    all those who receive copies directly or indirectly through you, then
    the only way you could satisfy both it and this License would be to
    refrain entirely from distribution of the Library.

    If any portion of this section is held invalid or unenforceable under any
    particular circumstance, the balance of the section is intended to apply,
    and the section as a whole is intended to apply in other circumstances.

    It is not the purpose of this section to induce you to infringe any
    patents or other property right claims or to contest validity of any
    such claims; this section has the sole purpose of protecting the
    integrity of the free software distribution system which is
    implemented by public license practices.  Many people have made
    generous contributions to the wide range of software distributed
    through that system in reliance on consistent application of that
    system; it is up to the author/donor to decide if he or she is willing
    to distribute software through any other system and a licensee cannot
    impose that choice.

    This section is intended to make thoroughly clear what is believed to
    be a consequence of the rest of this License.

      12. If the distribution and/or use of the Library is restricted in
    certain countries either by patents or by copyrighted interfaces, the
    original copyright holder who places the Library under this License may add
    an explicit geographical distribution limitation excluding those countries,
    so that distribution is permitted only in or among countries not thus
    excluded.  In such case, this License incorporates the limitation as if
    written in the body of this License.

      13. The Free Software Foundation may publish revised and/or new
    versions of the Library General Public License from time to time.
    Such new versions will be similar in spirit to the present version,
    but may differ in detail to address new problems or concerns.

    Each version is given a distinguishing version number.  If the Library
    specifies a version number of this License which applies to it and
    "any later version", you have the option of following the terms and
    conditions either of that version or of any later version published by
    the Free Software Foundation.  If the Library does not specify a
    license version number, you may choose any version ever published by
    the Free Software Foundation.
    
      14. If you wish to incorporate parts of the Library into other free
    programs whose distribution conditions are incompatible with these,
    write to the author to ask for permission.  For software which is
    copyrighted by the Free Software Foundation, write to the Free
    Software Foundation; we sometimes make exceptions for this.  Our
    decision will be guided by the two goals of preserving the free status
    of all derivatives of our free software and of promoting the sharing
    and reuse of software generally.

                    NO WARRANTY

      15. BECAUSE THE LIBRARY IS LICENSED FREE OF CHARGE, THERE IS NO
    WARRANTY FOR THE LIBRARY, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
    EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
    OTHER PARTIES PROVIDE THE LIBRARY "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
    LIBRARY IS WITH YOU.  SHOULD THE LIBRARY PROVE DEFECTIVE, YOU ASSUME
    THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

      16. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
    WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY
    AND/OR REDISTRIBUTE THE LIBRARY AS PERMITTED ABOVE, BE LIABLE TO YOU
    FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE
    LIBRARY (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
    RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A
    FAILURE OF THE LIBRARY TO OPERATE WITH ANY OTHER SOFTWARE), EVEN IF
    SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
    DAMAGES.

                 END OF TERMS AND CONDITIONS
    
         Appendix: How to Apply These Terms to Your New Libraries

      If you develop a new library, and you want it to be of the greatest
    possible use to the public, we recommend making it free software that
    everyone can redistribute and change.  You can do so by permitting
    redistribution under these terms (or, alternatively, under the terms of the
    ordinary General Public License).

      To apply these terms, attach the following notices to the library.  It is
    safest to attach them to the start of each source file to most effectively
    convey the exclusion of warranty; and each file should have at least the
    "copyright" line and a pointer to where the full notice is found.

        <one line to give the library's name and a brief idea of what it does.>
        Copyright (C) <year>  <name of author>

        This library is free software; you can redistribute it and/or
        modify it under the terms of the GNU Library General Public
        License as published by the Free Software Foundation; either
        version 2 of the License, or (at your option) any later version.

        This library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Library General Public License for more details.

        You should have received a copy of the GNU Library General Public
        License along with this library; if not, write to the Free
        Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
        MA 02111-1307, USA

    Also add information on how to contact you by electronic and paper mail.

    You should also get your employer (if you work as a programmer) or your
    school, if any, to sign a "copyright disclaimer" for the library, if
    necessary.  Here is a sample; alter the names:

      Yoyodyne, Inc., hereby disclaims all copyright interest in the
      library `Frob' (a library for tweaking knobs) written by James Random Hacker.

      <signature of Ty Coon>, 1 April 1990
      Ty Coon, President of Vice

    That's all there is to it!


\section main_contact Contact

You can post your suggestions/ideas/issues to https://bitbucket.org/tsieprawski/ubjsc/issues .

Of course all pull requests are fine to be discussed and probably someday merged!

Contact me at:

    Tomasz Sieprawski <tomasz@sieprawski.eu>
