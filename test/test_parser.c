#include "test.h"
#include "test_list.h"
#include "test_parser_tools.h"

void test_parser_init_clean()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    ubjs_parser_context *parser_context=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_alloc(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_alloc(&parser, 0));
    CU_ASSERT(0 == parser);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_alloc(0, &context));

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_alloc(&parser, &context));
    CU_ASSERT(0 != parser);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(parser, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(0, &parser_context));
    CU_ASSERT(0 == parser_context);
    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_get_context(parser, &parser_context));
    CU_ASSERT(&context == parser_context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_free(&parser));
    CU_ASSERT(0 == parser);
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_free(&parser));
    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_alloc(&parser, &context));
    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_free(&parser));
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    wrapped_parser_context_free(wrapped);
}

void test_parser_basics()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data;
    unsigned int message_length;
    unsigned char *message_text;
    void *mock_error;

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_alloc(&parser, &context));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(0, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, 0, 0));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, &data, 0));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length(0, &message_length));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length(&mock_error, 0));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text(0, &message_text));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text(&mock_error, 0));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_unknown_marker()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {0};

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_alloc(&parser, &context));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 0 [0] unknown marker", test_list_get(wrapped->calls_error, 0)));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_null() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_noop() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_true() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        CU_ASSERT(ubjs_object_false() == test_list_get(wrapped->calls_parsed, 0));
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int8_get(obj, &value));
        CU_ASSERT(-127 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));
    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int8_get(obj, &value));
        CU_ASSERT(0 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int8_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_uint8_get(obj, &value));
        CU_ASSERT(129 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));
    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_uint8_get(obj, &value));
        CU_ASSERT(0 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_uint8(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_uint8_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int16(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int16_get(obj, &value));
        CU_ASSERT(-32512 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int16(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int16_get(obj, &value));
        CU_ASSERT(129 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int16(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int16_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int32_get(obj, &value));
        CU_ASSERT(-2130673408 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 15));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int32_get(obj, &value));
        CU_ASSERT(8454273 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int32_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int64_get(obj, &value));
        CU_ASSERT(67305985 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 27));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int64_get(obj, &value));
        CU_ASSERT(4244504319 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_int64_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float32_get(obj, &value));
        CU_ASSERT(4 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 15));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float32_get(obj, &value));
        CU_ASSERT(-127.5 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float32(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float32_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float64_get(obj, &value));
        CU_ASSERT(512.0 == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 27));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float64_get(obj, &value));
        CU_ASSERT(-545357971845120.000000 == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float64(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_float64_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_char(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_char_get(obj, &value));
        CU_ASSERT('R' == value);
    }

    wrapped_parser_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(3 == test_list_len(wrapped->calls_parsed));

    if(3 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 1);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_char(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_char_get(obj, &value));
        CU_ASSERT('C' == value);

        obj = test_list_get(wrapped->calls_parsed, 2);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_char(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);

        CU_ASSERT_EQUAL(UR_OK, ubjs_object_char_get(obj, &value));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(0 == text_length);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(obj, text));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 8));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(obj, text));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 8));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(obj, text));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(obj, text));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(obj, &text_length));
        CU_ASSERT(5 == text_length)
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(obj, text));
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
    uint8_t data[]= {83,105,255};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("Processor_str got int8 negative length", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int32_negative()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,108,0,0,0,255};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 6));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("Processor_str got int32 negative length", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int16_negative()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,73,0,255};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("Processor_str got int16 negative length", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_null()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,90};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [90] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_noop()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,78};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [78] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_true()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,84};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [84] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_false()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,70};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [70] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_char()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,67};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [67] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_str()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,83};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [83] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_int64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,76};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [76] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_float32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,100};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [100] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_str_float64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {83,68};

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(1 == test_list_len(wrapped->calls_error));
    CU_ASSERT(0 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_error))
    {
        CU_ASSERT(0 == strcmp("At 1 [68] unknown marker", test_list_get(wrapped->calls_error, 0)));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_empty()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(0 == length)
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_uint8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,85,5,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    uint8_t vu8;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {

            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_uint8(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_uint8_get(item, &vu8));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(5 == vu8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_int8()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,105,255,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    int8_t v8;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int8(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_int8_get(item, &v8));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(-1 == v8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_int16()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,73,0,129,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    int16_t v16;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int16(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_int16_get(item, &v16));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(-32512 == v16);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_int32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,108,0,129,0,129,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    int32_t v32;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int32(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_int32_get(item, &v32));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(-2130673408 == v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_int64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,76,1,2,3,4,5,6,7,8,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    int64_t v64;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_int64(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_int64_get(item, &v64));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(67305985 == v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_float32()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,100,0,0,128,64,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    float32_t v32;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float32(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_float32_get(item, &v32));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(4 == v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_float64()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,68,0,0,0,0,0,0,128,64,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    float64_t v64;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_float64(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_float64_get(item, &v64));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(512 == v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_null()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,90,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_null(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_noop()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,78,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_noop(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_true()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,84,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_true(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_false()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,70,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {
            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_false(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_char()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,67,(uint8_t)'r',93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    unsigned char v;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {

            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_char(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_char_get(item, &v));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT('r' == v);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_str()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,83,85,5,'r','o','w','e','r',93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;
    char strung[5];

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 10));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {

            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_str(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);

                CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_get_length(item, &length));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(5 == length);

                CU_ASSERT_EQUAL(UR_OK, ubjs_object_str_copy_text(item, strung));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(0 == strncmp("rower", strung, 5));
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}

void test_parser_array_array()
{
    ubjs_parser *parser=0;

    wrapped_parser_context *wrapped=wrapped_parser_context_new();
    ubjs_parser_context context = {wrapped, parser_context_parsed, parser_context_error, parser_context_free};
    uint8_t data[]= {91,91,93,93};
    unsigned int length;
    ubjs_object *obj;
    ubjs_object *item=0;
    ubjs_bool ret;

    ubjs_parser_alloc(&parser, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 10));
    CU_ASSERT(0 == test_list_len(wrapped->calls_error));
    CU_ASSERT(1 == test_list_len(wrapped->calls_parsed));

    if(1 == test_list_len(wrapped->calls_parsed))
    {
        obj = test_list_get(wrapped->calls_parsed, 0);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(obj, &ret));
        CU_ASSERT_EQUAL(UTRUE, ret);
        CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(obj, &length));
        CU_ASSERT(1 == length);

        if(1 == length) {

            CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_at(obj, 0, &item));
            CU_ASSERT(0 != item);

            if(0 != item) {
                CU_ASSERT_EQUAL(UR_OK, ubjs_object_is_array(item, &ret));
                CU_ASSERT_EQUAL(UTRUE, ret);

                CU_ASSERT_EQUAL(UR_OK, ubjs_object_array_get_length(item, &length));
                CU_ASSERT_EQUAL(UTRUE, ret);
                CU_ASSERT(0 == length);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(wrapped);
}
