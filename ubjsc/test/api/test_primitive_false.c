/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or su`bstantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include "test_common.h"

static ubjs_library *lib;
static void before(void)
{
    ubjs_library_builder builder;
    ubjs_library_builder_init(&builder);
    ubjs_library_builder_build(&builder, &lib);
}

static void after(void)
{
    ubjs_library_free(&lib);
}

TestSuite(prmtv_false, .init = before, .fini = after);
Test(prmtv_false, ntype)
{
    ubjs_prmtv_ntype *n = &ubjs_prmtv_false_ntype;
    cr_expect_eq(70, n->marker);
    cr_expect_neq(0, n->free_f);
    cr_expect_eq(0, n->new_from_int64_f);
    cr_expect_eq(0, n->get_value_int64_f);
    cr_expect_neq(0, n->debug_string_get_length_f);
    cr_expect_neq(0, n->debug_string_copy_f);
    cr_expect_neq(0, n->parser_processor_new_f);
    cr_expect_neq(0, n->parser_processor_free_f);
    cr_expect_eq(0, n->parser_processor_got_child_f);
    cr_expect_eq(0, n->parser_processor_got_marker_f);
    cr_expect_neq(0, n->parser_processor_got_control_f);
    cr_expect_eq(0, n->parser_processor_read_byte_f);
    cr_expect_neq(0, n->writer_new_f);
    cr_expect_neq(0, n->writer_free_f);
    cr_expect_neq(0, n->writer_get_length_f);
    cr_expect_neq(0, n->writer_do_f);
    cr_expect_neq(0, n->printer_new_f);
    cr_expect_neq(0, n->printer_free_f);
    cr_expect_neq(0, n->printer_get_length_f);
    cr_expect_neq(0, n->printer_do_f);
}

Test(prmtv_false, object)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv_ntype *ntype = 0;
    char tmp[6];
    unsigned int len = -1;

    object = ubjs_prmtv_false();
    cr_expect_neq(0, object);
    cr_expect_eq(object, ubjs_prmtv_false());

    cr_expect_eq(UR_OK, ubjs_prmtv_get_ntype(object, &ntype));
    cr_expect_eq(&ubjs_prmtv_false_ntype, ntype);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_get_length_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_get_length_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_get_length_f)(0, &len));
    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.debug_string_get_length_f)(object, &len));
    cr_expect_eq(len, 5);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_copy_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_copy_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.debug_string_copy_f)(0, tmp));
    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.debug_string_copy_f)(object, tmp));
    cr_expect_arr_eq("false", tmp, 5);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.free_f)(0));
    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.free_f)(&object));
    cr_expect_eq(0, object);
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.free_f)(&object));
}

static ubjs_bool parser_glue_return_control_called = UFALSE;
static ubjs_bool parser_glue_want_marker_called = UFALSE;
static ubjs_bool parser_glue_want_child_called = UFALSE;
static ubjs_bool parser_glue_error_called = UFALSE;
static ubjs_bool parser_glue_debug_called = UFALSE;

static void parser_glue_return_control(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    parser_glue_return_control_called = UTRUE;
    cr_expect_eq(present, ubjs_prmtv_false());
}

static void parser_glue_want_marker_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    cr_expect_fail("%s", "Unexpected");
}

static void parser_glue_want_child_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_prmtv_ntype *marker)
{
    parser_glue_want_marker_called = UTRUE;
    cr_expect_fail("Unexpected want child: %p", marker);
}

static void parser_glue_error_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected error: %.*s", len, msg);
}

static void parser_glue_debug_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

static void parser_glue_reset(ubjs_prmtv_ntype_parser_glue *glue)
{
    parser_glue_return_control_called = UFALSE;
    parser_glue_want_marker_called = UFALSE;
    parser_glue_want_child_called = UFALSE;
    parser_glue_error_called = UFALSE;
    parser_glue_debug_called = UFALSE;

    glue->want_marker_f = parser_glue_want_marker_unexpected;
    glue->want_child_f = parser_glue_want_child_unexpected;
    glue->error_f = parser_glue_error_unexpected;
    glue->debug_f = parser_glue_debug_unexpected;
}

Test(prmtv_false, parser)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(0, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(lib, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_new_f)(0, &glue,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.parser_processor_free_f)(&parser_processor));

    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));
    cr_expect_neq(0, parser_processor);
    cr_expect_eq(&ubjs_prmtv_false_ntype, parser_processor->ntype);
    cr_expect_eq(lib, parser_processor->lib);
    cr_expect_str_eq("false", parser_processor->name);
    cr_expect_eq(&glue, parser_processor->glue);
    cr_expect_eq(0, parser_processor->userdata);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    glue.want_marker_f = parser_glue_want_marker_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_false_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(parser_glue_return_control_called, UTRUE);

    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void writer_glue_debug_unexpected(ubjs_prmtv_ntype_writer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_false, writer)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};
    unsigned int len = -1;
    uint8_t data[1] = {0};

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(0, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(lib, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(0, &glue, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_free_f)(&writer));

    glue.prmtv = &wrong_prmtv;
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.writer_new_f)(lib, &glue, &writer));

    glue.prmtv = ubjs_prmtv_false();
    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.writer_new_f)(lib, &glue, &writer));
    cr_expect_neq(0, writer);
    cr_expect_eq(lib, writer->lib);
    cr_expect_eq(&ubjs_prmtv_false_ntype, writer->ntype);
    cr_expect_str_eq("false", writer->name);
    cr_expect_eq(&glue, writer->glue);
    cr_expect_eq(0, writer->userdata);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_false_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(0, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_false_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 0); /* Unchanged */

    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.writer_free_f)(&writer));
    cr_expect_eq(0, writer);
}

static void printer_glue_debug_unexpected(ubjs_prmtv_ntype_printer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_false, printer)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};
    unsigned int len = -1;
    char data[1] = {0};

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.indent = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(0, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(lib, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(0, &glue, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_free_f)(&printer));

    glue.prmtv = &wrong_prmtv;
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_false_ntype.printer_new_f)(lib, &glue, &printer));

    glue.prmtv = ubjs_prmtv_false();
    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.printer_new_f)(lib, &glue, &printer));
    cr_expect_neq(0, printer);
    cr_expect_eq(lib, printer->lib);
    cr_expect_eq(&ubjs_prmtv_false_ntype, printer->ntype);
    cr_expect_str_eq("false", printer->name);
    cr_expect_eq(&glue, printer->glue);
    cr_expect_eq(0, printer->userdata);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_false_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(0, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_false_ntype.printer_do_f)(printer, data);
    cr_expect_eq(data[0], 0); /* Unchanged */

    cr_expect_eq(UR_OK, (ubjs_prmtv_false_ntype.printer_free_f)(&printer));
    cr_expect_eq(0, printer);
}
