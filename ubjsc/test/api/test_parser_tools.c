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

#include "test_common.h"
#include "test_parser_tools.h"

static void __pfree(void **pthis)
{
    free(*pthis);
}

void wrapped_parser_context_new(wrapped_parser_context **pthis)
{
    wrapped_parser_context *this;
    this=(wrapped_parser_context *)malloc(sizeof(struct wrapped_parser_context));
    this->calls_parsed = 0;
    this->calls_error = 0;
    this->calls_free = 0;

    test_list_new((test_list_free_f)ubjs_prmtv_free, &(this->calls_parsed));
    test_list_new((test_list_free_f)__pfree, &(this->calls_error));
    test_list_new(0, &(this->calls_free));
    *pthis=this;
}

void wrapped_parser_context_free(wrapped_parser_context **pthis)
{
    wrapped_parser_context *this=*pthis;
    test_list_free(&(this->calls_parsed));
    test_list_free(&(this->calls_error));
    test_list_free(&(this->calls_free));
    free(this);
    *pthis=0;
}

/*
void wrapped_parser_context_reset(wrapped_parser_context *this)
{
    test_list_free(&(this->calls_parsed));
    test_list_free(&(this->calls_error));
    test_list_free(&(this->calls_free));

    test_list_new((test_list_free_f)ubjs_prmtv_free, &(this->calls_parsed));
    test_list_new((test_list_free_f)__pfree, &(this->calls_error));
    test_list_new(0, &(this->calls_free));
}
*/

void parser_context_parsed(void *userdata, ubjs_prmtv *object)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)userdata;
    test_list_add(ctx->calls_parsed, object, 0);
}

void parser_context_error(void *userdata, unsigned int len, char *message)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)userdata;
    char *msg2;

    cr_log_info("Parser error: %.*s", len, message);

    msg2 = (char *)malloc(sizeof(char) * (len+ 1));
    strncpy(msg2, message, len);
    msg2[len] = 0;
    test_list_add(ctx->calls_error, msg2, 0);
}

void parser_context_debug(void *userdata, unsigned int len, char *message)
{
    cr_log_info("Parser debug: %.*s", len, message);
}

void parser_context_free(void *userdata)
{
    wrapped_parser_context *ctx=(wrapped_parser_context *)userdata;
    test_list_add(ctx->calls_free, 0, 0);
}
