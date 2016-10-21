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
#include <stdlib.h>
#include <string.h>

#include <jansson.h>
#include <argtable2.h>
#include <ubjs.h>

typedef struct ctx ctx;

struct ctx
{
    ubjs_bool verbose;
    ubjs_bool pretty_print_input;

    unsigned int verbose_before;
    unsigned int verbose_after;
};

void ubjs2js_main_encode_ubjson_to_json(ubjs_prmtv *, json_t **);
void ubjs2js_main_writer_context_would_write(ubjs_writer_context *, uint8_t *, unsigned int);
void ubjs2js_main_writer_context_would_print(ubjs_writer_context *, char *, unsigned int);
void ubjs2js_main_writer_context_free(ubjs_writer_context *);

void ubjs2js_main_writer_context_would_write(ubjs_writer_context *context, uint8_t *data,
    unsigned int len)
{
    ctx *my_ctx = (ctx *)context->userdata;
    my_ctx->verbose_before = len;
    printf("Before: [%u]\n", len);
    fwrite((void *)data, sizeof(uint8_t), len, stdout);
    printf("\n");
}

void ubjs2js_main_writer_context_would_print(ubjs_writer_context *context, char *data,
    unsigned int len)
{
    char *tmp = (char *)malloc(sizeof(char) * (len + 1));

    strncpy(tmp, data, len);
    tmp[len] = 0;
    printf("Pretty-printed [%u]\n", len);
    fwrite((void *)data, sizeof(char), len, stdout);
    printf("\n");
    free(tmp);
}

void ubjs2js_main_writer_context_free(ubjs_writer_context *context)
{
}

void ubjs2js_main_encode_ubjson_to_json(ubjs_prmtv *object, json_t **pjsoned)
{
    json_t *jsoned = 0;
    ubjs_prmtv_type type;
    int64_t v;
    float32_t f32;
    float64_t f64;
    ubjs_array_iterator *ait;
    ubjs_object_iterator *oit;
    ubjs_prmtv *item;
    json_t *item_jsoned;
    unsigned int str_length;
    char *str;

    ubjs_prmtv_get_type(object, &type);
    switch (type)
    {
        case UOT_NULL:
            jsoned = json_null();
            break;

        case UOT_NOOP:
            break;

        case UOT_TRUE:
            jsoned = json_true();
            break;

        case UOT_FALSE:
            jsoned = json_false();
            break;

        case UOT_UINT8:
        case UOT_INT8:
        case UOT_INT16:
        case UOT_INT32:
        case UOT_INT64:
            ubjs_prmtv_int_get(object, &v);
            jsoned = json_integer(v);
            break;

        case UOT_FLOAT32:
            ubjs_prmtv_float32_get(object, &f32);
            jsoned = json_real(f32);
            break;

        case UOT_FLOAT64:
            ubjs_prmtv_float64_get(object, &f64);
            jsoned = json_real(f64);
            break;

        case UOT_STR:
            ubjs_prmtv_str_get_length(object, &str_length);
            str = (char *) malloc(sizeof(char) * str_length);
            ubjs_prmtv_str_copy_text(object, str);

            jsoned = json_stringn(str, str_length);
            free(str);
            break;

        case UOT_HPN:
            ubjs_prmtv_hpn_get_length(object, &str_length);
            str = (char *) malloc(sizeof(char) * str_length);
            ubjs_prmtv_hpn_copy_text(object, str);

            jsoned = json_stringn(str, str_length);
            free(str);
            break;

        case UOT_CHAR:
            str = (char *) malloc(sizeof(char) * 1);
            ubjs_prmtv_char_get(object, str);

            jsoned = json_stringn(str, 1);
            free(str);
            break;

        case UOT_ARRAY:
            jsoned = json_array();
            ubjs_prmtv_array_iterate(object, &ait);

            while (UR_OK == ubjs_array_iterator_next(ait))
            {
                ubjs_array_iterator_get(ait, &item);
                ubjs2js_main_encode_ubjson_to_json(item, &item_jsoned);
                if (0 != item_jsoned)
                {
                    json_array_append(jsoned, item_jsoned);
                    json_decref(item_jsoned);
                }
            }

            ubjs_array_iterator_free(&ait);
            break;

        case UOT_OBJECT:
            jsoned = json_object();
            ubjs_prmtv_object_iterate(object, &oit);

            while (UR_OK == ubjs_object_iterator_next(oit))
            {
                unsigned int key_length;
                char *key;

                ubjs_object_iterator_get_key_length(oit, &key_length);
                key = (char *)malloc(sizeof(char) * (key_length + 1));
                ubjs_object_iterator_copy_key(oit, key);
                key[key_length] = 0;

                ubjs_object_iterator_get_value(oit, &item);
                ubjs2js_main_encode_ubjson_to_json(item, &item_jsoned);
                if (0 != item_jsoned)
                {
                    json_object_set(jsoned, key, item_jsoned);
                    json_decref(item_jsoned);
                }
                free(key);
            }

            ubjs_object_iterator_free(&oit);
            break;

        default:
            printf("WTF\n");
            break;
    }

    *pjsoned = jsoned;
}

void ubjs2js_main_parser_context_parsed(ubjs_parser_context *context, ubjs_prmtv *object)
{
    ctx *my_ctx = (ctx *)context->userdata;
    json_t *jsoned;
    char *tmp;

    if (UTRUE == my_ctx->verbose)
    {
        ubjs_writer *writer=0;
        ubjs_writer_context writer_context;

        writer_context.userdata = (void *)my_ctx;
        writer_context.would_write = ubjs2js_main_writer_context_would_write;
        writer_context.would_print = ubjs2js_main_writer_context_would_print;
        writer_context.free = ubjs2js_main_writer_context_free;

        ubjs_writer_new(&writer, &writer_context);
        ubjs_writer_write(writer, object);

        if (UTRUE == my_ctx->pretty_print_input)
        {
            ubjs_writer_print(writer, object);
        }
        ubjs_writer_free(&writer);

        printf("\n");
    }

    ubjs2js_main_encode_ubjson_to_json(object, &jsoned);
    tmp = json_dumps(jsoned, JSON_ENCODE_ANY);

    if (UTRUE == my_ctx->verbose)
    {
        printf("After: [%u]\n", (unsigned int)strlen(tmp));
    }

    printf("%s", tmp);

    if (UTRUE == my_ctx->verbose && 0 < my_ctx->verbose_before)
    {
        my_ctx->verbose_after = strlen(tmp);
        printf("\nCompression/expansion: [%u percent]\n",
            100 * my_ctx->verbose_after / my_ctx->verbose_before);
    }

    free(tmp);
    json_decref(jsoned);
    ubjs_prmtv_free(&object);
}

void ubjs2js_main_parser_context_error(ubjs_parser_context *context, ubjs_parser_error *error)
{
    unsigned int length;
    char *message;

    ubjs_parser_error_get_message_length(error, &length);
    message = (char *)malloc(sizeof(char) * (length+1));
    ubjs_parser_error_get_message_text(error, message);
    message[length] = 0;

    fprintf(stderr, "Parser error: %s\n", message);

    free(message);
}

void ubjs2js_main_parser_context_free(ubjs_parser_context *context)
{
}

int main(int argc, char **argv)
{
    ubjs_parser *parser=0;
    ubjs_parser_context parser_context;
    uint8_t bytes[4096];
    size_t did_read;

    struct arg_lit *arg_verbose;
    struct arg_lit *arg_pretty_print_input;
    struct arg_lit *arg_help;
    struct arg_end *end = arg_end(20);
    unsigned int arg_errors;
    void *argtable[4];

    unsigned int exit_code = 0;

    arg_verbose = arg_lit0("v", "verbose", "verbosily print input, both input's and output's"
        " lengths and compression/expansion rate");
    arg_help = arg_lit0("h", "help", "print this help and exit");
    arg_pretty_print_input = arg_lit0(NULL, "pretty-print-input", "if verbose, then also"
        " pretty-print the input");
    argtable[0] = arg_verbose;
    argtable[1] = arg_pretty_print_input;
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
        printf("This program converts UBJSON objects from stdin to JSON objects to stdout.\n");
        printf("\n");
        printf("Examples:\n");
        printf("    printf Z | %s\n", argv[0]);
        printf("    printf T | %s\n", argv[0]);
        printf("    printf F | %s\n", argv[0]);
        printf("    printf 'U\\x96' | %s\n", argv[0]);
        printf("    printf 'i\\xF0' | %s\n", argv[0]);
        printf("    printf 'I\\xDE\\xAD' | %s\n", argv[0]);
        printf("    printf 'l\\xDE\\xAD\\xBE\\xEF' | %s\n", argv[0]);
        printf("    printf 'L\\xDE\\xAD\\xBE\\xEF\\xCA\\xFE\\xBA\\xBE' | %s\n", argv[0]);
        printf("    printf 'd\\xDE\\xAD\\xBE\\xEF' | %s\n", argv[0]);
        printf("    printf 'D\\xDE\\xAD\\xBE\\xEF\\xCA\\xFE\\xBA\\xBE' | %s\n", argv[0]);
        printf("    printf 'Cr' | %s\n", argv[0]);
        printf("    printf 'HU\\x0512345' | %s\n", argv[0]);
        printf("    printf 'SU\\x05rower' | %s\n", argv[0]);
        printf("    printf '[]' | %s\n", argv[0]);
        printf("    printf '[#U\\x03ZTF' | %s\n", argv[0]);
        printf("    printf '[$Z#U\\xFF' | %s\n", argv[0]);
        printf("    printf \"{U\\x03youSU\\x04suckU\\x05and ISU\\x05don't}\" | %s\n", argv[0]);
        printf("    printf '{U\\x03youSU\\x04suck}' | %s\n", argv[0]);
        printf("    printf '[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]' | %s\n", argv[0]);
        printf("\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        arg_freetable(argtable, 4);
    }
    else if (0 != arg_errors)
    {
        arg_print_errors(stdout, end, argv[0]);
        exit_code = 1;
    }
    else
    {
        ctx my_ctx;
        my_ctx.verbose = (0 != arg_verbose->count) ? UTRUE : UFALSE;
        my_ctx.pretty_print_input = (0 != arg_pretty_print_input->count) ? UTRUE : UFALSE;

        parser_context.userdata = (void *)&my_ctx;
        parser_context.parsed = ubjs2js_main_parser_context_parsed;
        parser_context.error = ubjs2js_main_parser_context_error;
        parser_context.free = ubjs2js_main_parser_context_free;
        ubjs_parser_new(0, &parser_context, &parser);

        while (0 == feof(stdin))
        {
            did_read = fread(bytes, sizeof(uint8_t), 4096, stdin);
            if (UR_OK != ubjs_parser_parse(parser, bytes, did_read))
            {
                break;
            }
        }

        ubjs_parser_free(&parser);
    }

    arg_freetable(argtable, 4);
    return exit_code;
}
