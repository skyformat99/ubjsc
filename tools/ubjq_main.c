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

#include <argtable2.h>
#include <ubjs.h>

typedef struct ctx ctx;

struct ctx
{
    int unused;
};

void ubjq_main_writer_context_would_print(ubjs_writer_context *, char *, unsigned int);
void ubjq_main_writer_context_free(ubjs_writer_context *);

void ubjq_main_writer_context_would_print(ubjs_writer_context *context, char *data,
    unsigned int len)
{
    fwrite((void *)data, sizeof(char), len, stdout);
    printf("\n");
}

void ubjq_main_writer_context_free(ubjs_writer_context *context)
{
}

void ubjq_main_parser_context_parsed(ubjs_parser_context *context, ubjs_prmtv *object)
{
    ctx *my_ctx = (ctx *)context->userdata;

    ubjs_writer *writer = 0;
    ubjs_writer_context writer_context;

    writer_context.userdata = (void *)my_ctx;
    writer_context.would_write = 0;
    writer_context.would_print = ubjq_main_writer_context_would_print;
    writer_context.free = ubjq_main_writer_context_free;

    ubjs_writer_new(&writer, &writer_context);
    ubjs_writer_print(writer, object);
    ubjs_writer_free(&writer);
    ubjs_prmtv_free(&object);
}

void ubjq_main_parser_context_error(ubjs_parser_context *context, ubjs_parser_error *error)
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

void ubjq_main_parser_context_free(ubjs_parser_context *context)
{
}

int main(int argc, char **argv)
{
    uint8_t bytes[4096];
    size_t did_read;

    struct arg_lit *arg_help;
    struct arg_end *end = arg_end(20);
    unsigned int arg_errors;
    void *argtable[4];

    unsigned int exit_code = 0;

    arg_help = arg_lit0("h", "help", "print this help and exit");
    argtable[0] = arg_help;
    argtable[1] = end;
    if (0 != arg_nullcheck(argtable))
    {
        return 1;
    }

    arg_errors = arg_parse(argc, argv, argtable);

    if (0 < arg_help->count)
    {
        printf("Usage: %s", argv[0]);
        arg_print_syntax(stdout, argtable, "\n");
        printf("This program pretty-prints UBJSON objects to stdout.\n");
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
        printf("    printf 'SU\\x05rower' | %s\n", argv[0]);
        printf("    printf 'HU\\x0512345' | %s\n", argv[0]);
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
        ubjs_library *lib;
        ubjs_parser *parser=0;
        ubjs_parser_context parser_context;
        ctx my_ctx = {0};

        ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free, &lib);

        parser_context.userdata = (void *)&my_ctx;
        parser_context.parsed = ubjq_main_parser_context_parsed;
        parser_context.error = ubjq_main_parser_context_error;
        parser_context.free = ubjq_main_parser_context_free;
        ubjs_parser_new(lib, 0, &parser_context, &parser);

        while (0 == feof(stdin))
        {
            did_read = fread(bytes, sizeof(uint8_t), 4096, stdin);
            if (UR_OK != ubjs_parser_parse(parser, bytes, did_read))
            {
                break;
            }
        }

        ubjs_parser_free(&parser);
        ubjs_library_free(&lib);
    }

    arg_freetable(argtable, 4);
    return exit_code;
}
