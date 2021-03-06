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

#include <stdio.h>
#include <string.h>

#include <jansson.h>
#include <argtable2.h>
#include <ubjs.h>

typedef struct ctx ctx;

struct ctx
{
    ubjs_bool verbose;
    ubjs_bool pretty_print_output;

    unsigned int verbose_before;
    unsigned int verbose_after;
};

static void js2ubj_main_encode_json_to_ubjson(json_t *, ubjs_library *, ubjs_prmtv **);
static void js2ubj_main_writer_context_would_write(void *, uint8_t *,
    unsigned int);
static void js2ubj_main_writer_context_would_print(void *, char *,
    unsigned int);
static void js2ubj_main_writer_context_free(void *);
static void do_it(json_t *, int, int);

static void js2ubj_main_encode_json_to_ubjson(json_t *jsoned, ubjs_library *lib, ubjs_prmtv **pobj)
{
    size_t index;
    const char *key;
    json_t *jsoned_item;
    ubjs_prmtv *item;

    switch (json_typeof(jsoned))
    {
        case JSON_NULL:
            *pobj = ubjs_prmtv_null();
            break;

        case JSON_TRUE:
            *pobj = ubjs_prmtv_true();
            break;

        case JSON_FALSE:
            *pobj = ubjs_prmtv_false();
            break;

        case JSON_INTEGER:
            ubjs_prmtv_int(lib, json_integer_value(jsoned), pobj);;
            break;

        case JSON_REAL:
            ubjs_prmtv_float64(lib, json_real_value(jsoned), pobj);
            break;

        case JSON_STRING:
            ubjs_prmtv_str(lib, json_string_length(jsoned), (char *)json_string_value(jsoned),
                pobj);
            break;

        case JSON_ARRAY:
            ubjs_prmtv_array(lib, pobj);
            json_array_foreach(jsoned, index, jsoned_item)
            {
                js2ubj_main_encode_json_to_ubjson(jsoned_item, lib, &item);
                ubjs_prmtv_array_add_last(*pobj, item);
            }
            break;

        case JSON_OBJECT:
            ubjs_prmtv_object(lib, pobj);
            json_object_foreach(jsoned, key, jsoned_item)
            {
                js2ubj_main_encode_json_to_ubjson(jsoned_item, lib, &item);
                ubjs_prmtv_object_set(*pobj, strlen(key), (char *)key, item);
            }
            break;

        default:
            break;
    }
}

static void js2ubj_main_writer_context_would_write(void *userdata, uint8_t *data,
    unsigned int len)
{
    ctx *my_ctx = (ctx *)userdata;

    if (UTRUE == my_ctx->verbose)
    {
        printf("After: [%u]\n", len);
    }

    fwrite((void *)data, sizeof(uint8_t), len, stdout);

    if (UTRUE == my_ctx->verbose)
    {
        my_ctx->verbose_after = len;
        printf("\nCompression/expansion: [%u percent]\n",
            100 * my_ctx->verbose_after / my_ctx->verbose_before);
    }
}

static void js2ubj_main_writer_context_would_print(void *userdata, char *data,
    unsigned int len)
{
    char *tmp = (char *)malloc(sizeof(char) * (len + 1));

    strncpy(tmp, data, len);
    tmp[len] = 0;
    printf("Pretty-printed [%u]: %s\n", len, tmp);
    free(tmp);
}

static void js2ubj_main_writer_context_free(void *userdata)
{
}

static void do_it(json_t *value, int verbose, int pretty_print_output)
{
    ubjs_library_builder library_builder;
    ubjs_library *lib = 0;
    ubjs_writer_builder *writer_builder = 0;
    ubjs_writer *writer = 0;
    ctx my_ctx;
    ubjs_prmtv *obj = 0;

    my_ctx.verbose = verbose ? UTRUE : UFALSE;
    my_ctx.pretty_print_output = pretty_print_output ? UTRUE : UFALSE;

    if (UTRUE == my_ctx.verbose)
    {
        char *tmp = json_dumps(value, JSON_ENCODE_ANY);
        my_ctx.verbose_before = strlen(tmp);
        printf("Before: [%u]\n%s\n", (unsigned int) strlen(tmp), tmp);
        free(tmp);
    }

    ubjs_library_builder_init(&library_builder);
    ubjs_library_builder_build(&library_builder, &lib);

    js2ubj_main_encode_json_to_ubjson(value, lib, &obj);

    ubjs_writer_builder_new(lib, &writer_builder);
    ubjs_writer_builder_set_userdata(writer_builder, &my_ctx);
    ubjs_writer_builder_set_would_write_f(writer_builder,
        js2ubj_main_writer_context_would_write);
    ubjs_writer_builder_set_would_print_f(writer_builder,
        js2ubj_main_writer_context_would_print);
    ubjs_writer_builder_set_free_f(writer_builder, js2ubj_main_writer_context_free);
    ubjs_writer_builder_build(writer_builder, &writer);
    ubjs_writer_builder_free(&writer_builder);

    ubjs_writer_write(writer, obj);
    if (UTRUE == my_ctx.pretty_print_output)
    {
        ubjs_writer_print(writer, obj);
    }

    ubjs_writer_free(&writer);
    ubjs_prmtv_free(&obj);
    ubjs_library_free(&lib);
}

int main(int argc, char **argv)
{
    json_error_t error;
    json_t *value = 0;

    struct arg_lit *arg_verbose;
    struct arg_lit *arg_pretty_print_output;
    struct arg_lit *arg_help;
    struct arg_end *end = arg_end(20);
    unsigned int arg_errors;
    void *argtable[4];

    unsigned int exit_code = 0;

    arg_verbose = arg_lit0("v", "verbose", "verbosily print input, both input's and output's"
        " lengths and compression/expansion rate");
    arg_help = arg_lit0("h", "help", "print this help and exit");
    arg_pretty_print_output = arg_lit0(NULL, "pretty-print-output", "if verbose, then also"
        " pretty-print the output");
    argtable[0] = arg_verbose;
    argtable[1] = arg_pretty_print_output;
    argtable[2] = arg_help;
    argtable[3] = end;
    if (0 != arg_nullcheck(argtable))
    {
        return 1;
    }

    arg_errors = arg_parse(argc, argv, argtable);

    if (0 < arg_help->count)
    {
        printf("Usage: %s", argv[0]);
        arg_print_syntax(stdout, argtable, "\n");
        printf("This program converts JSON objects from stdin to UBJSON objects to stdout.\n");
        printf("\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
    }
    else if (0 != arg_errors)
    {
        arg_print_errors(stdout, end, argv[0]);
        exit_code = 1;
    }
    else
    {
        value = json_loadf(stdin, JSON_DECODE_ANY, &error);
        if (0 == value)
        {
            fprintf(stderr, "JSON error: %s\n", error.text);
            fprintf(stderr, "    line: %u\n", error.line);
            fprintf(stderr, "    column: %u\n", error.column);
            fprintf(stderr, "    pos: %u\n", error.position);
        }
        else
        {
            do_it(value, 0 != arg_verbose->count, 0 != arg_pretty_print_output->count);
            json_decref(value);
        }
    }

    arg_freetable(argtable, 4);
    return exit_code;
}
