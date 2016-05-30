#include "test.h"
#include "test_list.h"
#include "test_parser_tools.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

void test_parser_init_clean()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    ubjs_parser_context *parser_context=0;

    CU_ASSERT(UR_ERROR == ubjs_parser_alloc(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_parser_alloc(&parser, 0));
    CU_ASSERT(0 == parser);
    CU_ASSERT(UR_ERROR == ubjs_parser_alloc(0, &context));

    CU_ASSERT(UR_OK == ubjs_parser_alloc(&parser, &context));
    CU_ASSERT(0 != parser);

    CU_ASSERT(UR_ERROR == ubjs_parser_get_context(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_parser_get_context(parser, 0));
    CU_ASSERT(UR_ERROR == ubjs_parser_get_context(0, &parser_context));
    CU_ASSERT(0 == parser_context);
    CU_ASSERT(UR_OK == ubjs_parser_get_context(parser, &parser_context));
    CU_ASSERT(&context == parser_context);

    CU_ASSERT(UR_ERROR == ubjs_parser_free(0));
    CU_ASSERT(UR_OK == ubjs_parser_free(&parser));
    CU_ASSERT(0 == parser);
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    CU_ASSERT(UR_ERROR == ubjs_parser_free(&parser));
    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_alloc(&parser, &context));
    CU_ASSERT(UR_OK == ubjs_parser_free(&parser));
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    wrapped_parser_context_free(wrapped);
}

void test_parser_basics()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {};

    CU_ASSERT(UR_OK == ubjs_parser_alloc(&parser, &context));

    CU_ASSERT(UR_ERROR == ubjs_parser_parse(0, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_parser_parse(parser, 0, 0));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 0));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_unknown_marker()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {0};

    CU_ASSERT(UR_OK == ubjs_parser_alloc(&parser, &context));

    CU_ASSERT(UR_ERROR == ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 13 [0] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}
void test_parser_null()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {90,90,90,90,90};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_null() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(5 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_noop()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {78,78,78,78,78};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_noop() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(5 == test_list_len(wrapped->calls_parsed));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_true()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {84,84,84,84,84};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_true() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(5 == test_list_len(wrapped->calls_parsed));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_false()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {70,70,70,70,70};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_false() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(5 == test_list_len(wrapped->calls_parsed));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_int8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {105,129,105,0,105,255};
    int8_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_int8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int8_get(obj, &value));
        CU_ASSERT(-127 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));
    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_int8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int8_get(obj, &value));
        CU_ASSERT(0 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_int8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int8_get(obj, &value));
        CU_ASSERT(-1 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_uint8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {85,129,85,0,85,255};
    uint8_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_uint8_get(obj, &value));
        CU_ASSERT(129 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));
    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_uint8_get(obj, &value));
        CU_ASSERT(0 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_uint8_get(obj, &value));
        CU_ASSERT(255 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_int16()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {73,0,129,73,129,0,73,85,255};
    int16_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_int16(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int16_get(obj, &value));
        CU_ASSERT(-32512 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_int16(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int16_get(obj, &value));
        CU_ASSERT(129 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_int16(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int16_get(obj, &value));
        CU_ASSERT(-171 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_int32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {108,0,129,0,129,108,129,0,129,0,108,85,255,85,255};
    int32_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_int32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int32_get(obj, &value));
        CU_ASSERT(-2130673408 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 15));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_int32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int32_get(obj, &value));
        CU_ASSERT(8454273 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_int32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int32_get(obj, &value));
        CU_ASSERT(-11141291 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_int64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {76,1,2,3,4,5,6,7,8,
                     76,255,254,253,252,251,250,249,248,
                     76,0,255,1,254,2,253,3,252
                    };
    int64_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_int64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int64_get(obj, &value));
        CU_ASSERT(67305985 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 27));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_int64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int64_get(obj, &value));
        CU_ASSERT(4244504319 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_int64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_int64_get(obj, &value));
        CU_ASSERT(4261543680 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_float32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {100,0,0,128,64,100,0,0,255,194,100,0,0,128,65};
    float32_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_float32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float32_get(obj, &value));
        CU_ASSERT(4 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 15));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_float32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float32_get(obj, &value));
        CU_ASSERT(-127.5 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_float32(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float32_get(obj, &value));
        CU_ASSERT(16.0 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_float64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {68,0,0,0,0,0,0,128,64,
                     68,0,0,255,194,0,0,255,194,
                     68,0,0,128,65,0,0,128,65
                    };
    float64_t value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_float64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float64_get(obj, &value));
        CU_ASSERT(512.0 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 27));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_float64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float64_get(obj, &value));
        CU_ASSERT(-545357971845120.000000 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_float64(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_float64_get(obj, &value));
        CU_ASSERT(33554440.187500 == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_char()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {67,82,67,67,67,68};
    unsigned char value;
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_char(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_char_get(obj, &value));
        CU_ASSERT('R' == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT(UR_OK == ubjs_object_is_char(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_char_get(obj, &value));
        CU_ASSERT('C' == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT(UR_OK == ubjs_object_is_char(obj, &ret));
        CU_ASSERT(UTRUE == ret);

        CU_ASSERT(UR_OK == ubjs_object_char_get(obj, &value));
        CU_ASSERT('D' == value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_empty()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,85,0};
    unsigned int text_length;
    unsigned char text[1]= {0};
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_str(obj, &ret));
        CU_ASSERT(UTRUE == ret);
        CU_ASSERT(UR_OK == ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(0 == text_length);
        CU_ASSERT(UR_OK == ubjs_object_str_copy_text(obj, text));
        CU_ASSERT(0 == text[0]);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_uint8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,85,5,'r','o','w','e','r'};
    unsigned int text_length;
    unsigned char text[5];
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 8));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_str(obj, &ret));
        CU_ASSERT(UTRUE == ret);
        CU_ASSERT(UR_OK == ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT(UR_OK == ubjs_object_str_copy_text(obj, text));
        CU_ASSERT(0 == strncmp("rower", text, 5));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,105,5,'r','o','w','e','r'};
    unsigned int text_length;
    unsigned char text[5];
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 8));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_str(obj, &ret));
        CU_ASSERT(UTRUE == ret);
        CU_ASSERT(UR_OK == ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT(UR_OK == ubjs_object_str_copy_text(obj, text));
        CU_ASSERT(0 == strncmp("rower", text, 5));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int16()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,73,5,0,'r','o','w','e','r'};
    unsigned int text_length;
    unsigned char text[5];
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_str(obj, &ret));
        CU_ASSERT(UTRUE == ret);
        CU_ASSERT(UR_OK == ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT(UR_OK == ubjs_object_str_copy_text(obj, text));
        CU_ASSERT(0 == strncmp("rower", text, 5));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,108,5,0,0,0,'r','o','w','e','r'};
    unsigned int text_length;
    unsigned char text[5];
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 11));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT(UR_OK == ubjs_object_is_str(obj, &ret));
        CU_ASSERT(UTRUE == ret);
        CU_ASSERT(UR_OK == ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT(UR_OK == ubjs_object_str_copy_text(obj, text));
        CU_ASSERT(0 == strncmp("rower", text, 5));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int8_negative()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,105,128};
    unsigned int text_length;
    unsigned char text[5];
    ubjs_bool ret;
    ubjs_object *obj;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT(UR_OK == ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 13 [0] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}
