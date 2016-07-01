#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"


void suite_parser(tcontext *context) {
    tsuite *suite;
    tsuite_new("parser", 0, 0, &suite);
    tcontext_add_suite(context,suite);

    TTEST(suite, test_parser_bad_init);
    TTEST(suite, test_parser_init_clean);
    TTEST(suite, test_parser_basics);
    TTEST(suite, test_parser_unknown_marker);
    TTEST(suite, test_parser_null);
    TTEST(suite, test_parser_noop);
    TTEST(suite, test_parser_true);
    TTEST(suite, test_parser_false);
    TTEST(suite, test_parser_int8);
    TTEST(suite, test_parser_uint8);
    TTEST(suite, test_parser_int16);
    TTEST(suite, test_parser_int32);
    TTEST(suite, test_parser_int64);
    TTEST(suite, test_parser_float32);
    TTEST(suite, test_parser_float64);
    TTEST(suite, test_parser_char);

    TTEST(suite, test_parser_str_empty);
    TTEST(suite, test_parser_str_null);
    TTEST(suite, test_parser_str_noop);
    TTEST(suite, test_parser_str_true);
    TTEST(suite, test_parser_str_false);
    TTEST(suite, test_parser_str_uint8);
    TTEST(suite, test_parser_str_int8);
    TTEST(suite, test_parser_str_int8_negative);
    TTEST(suite, test_parser_str_int16);
    TTEST(suite, test_parser_str_int16_negative);
    TTEST(suite, test_parser_str_int32);
    TTEST(suite, test_parser_str_int32_negative);
    TTEST(suite, test_parser_str_int64);
    TTEST(suite, test_parser_str_float32);
    TTEST(suite, test_parser_str_float64);
    TTEST(suite, test_parser_str_char);
    TTEST(suite, test_parser_str_str);
    TTEST(suite, test_parser_str_array);
    TTEST(suite, test_parser_str_object);

    TTEST(suite, test_parser_array_empty);
    TTEST(suite, test_parser_array_uint8);
    TTEST(suite, test_parser_array_int8);
    TTEST(suite, test_parser_array_int16);
    TTEST(suite, test_parser_array_int32);
    TTEST(suite, test_parser_array_null);
    TTEST(suite, test_parser_array_noop);
    TTEST(suite, test_parser_array_true);
    TTEST(suite, test_parser_array_false);
    TTEST(suite, test_parser_array_char);
    TTEST(suite, test_parser_array_str);
    TTEST(suite, test_parser_array_int64);
    TTEST(suite, test_parser_array_float32);
    TTEST(suite, test_parser_array_float64);
    TTEST(suite, test_parser_array_array);
    TTEST(suite, test_parser_array_object);

    TTEST(suite, test_parser_object_empty);
    TTEST(suite, test_parser_object_uint8);
    TTEST(suite, test_parser_object_int8);
    TTEST(suite, test_parser_object_int16);
    TTEST(suite, test_parser_object_int32);
    TTEST(suite, test_parser_object_int64);
    TTEST(suite, test_parser_object_float32);
    TTEST(suite, test_parser_object_float64);
    TTEST(suite, test_parser_object_char);
    TTEST(suite, test_parser_object_str);
    TTEST(suite, test_parser_object_array);
    TTEST(suite, test_parser_object_object);
}

void test_parser_bad_init()
{
    ubjs_parser *parser=0;
    ubjs_parser_context context;
    context.parsed=0;
    context.error=0;
    context.free=0;

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=parser_context_error;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=0;
    context.free=parser_context_free;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=parser_context_error;
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, &context));
}

void test_parser_init_clean()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_context *parser_context=0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(&parser, 0));
    TASSERT_EQUAL(0, parser);
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_new(0, &context));

    TASSERT_EQUAL(UR_OK, ubjs_parser_new(&parser, &context));
    TASSERT_NOT_EQUAL(0, parser);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(parser, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_get_context(0, &parser_context));
    TASSERT_EQUAL(0, parser_context);
    TASSERT_EQUAL(UR_OK, ubjs_parser_get_context(parser, &parser_context));
    TASSERT_EQUAL(&context, parser_context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_free(0));
    TASSERT_EQUAL(UR_OK, ubjs_parser_free(&parser));
    TASSERT_EQUAL(0, parser);
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUAL(1, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_free(&parser));
    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_new(&parser, &context));
    TASSERT_EQUAL(UR_OK, ubjs_parser_free(&parser));
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUAL(1, len);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_basics()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data;
    unsigned int message_length;
    unsigned int len;
    char message_text[] = {0};
    void *mock_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUAL(UR_OK, ubjs_parser_new(&parser, &context));

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, 0, 0));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, &data, 0));

    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length(0, &message_length));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_length((ubjs_parser_error *)&mock_error, 0));

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text(0, message_text));
    TASSERT_EQUAL(UR_ERROR, ubjs_parser_error_get_message_text((ubjs_parser_error *)&mock_error, 0));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_unknown_marker()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {0};
    unsigned int len;
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUAL(UR_OK, ubjs_parser_new(&parser, &context));

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 0 [0] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
void test_parser_null()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {90,90,90,90,90};
    unsigned int len;
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_null(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(5, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {78,78,78,78,78};
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_noop(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(5, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {84,84,84,84,84};

    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_true(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(5, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {70,70,70,70,70};
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_false(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(5, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    uint8_t data[]= {105,129,105,0,105,255};
    int8_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    ubjs_parser_context context;
    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUAL(-127, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);
    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUAL(0, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUAL(-1, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {85,129,85,0,85,255};
    uint8_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUAL(129, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);
    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUAL(0, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUAL(255, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {73,0,129,73,129,0,73,85,255};
    int16_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUAL(-32512, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUAL(129, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUAL(-171, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {108,0,129,0,129,108,129,0,129,0,108,85,255,85,255};
    int32_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUAL(-2130673408, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 15));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUAL(8454273, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUAL(-11141291, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {76,1,2,3,4,5,6,7,8,
                     76,255,254,253,252,251,250,249,248,
                     76,0,255,1,254,2,253,3,252
                    };
    int64_t value=0;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUAL(67305985, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 27));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUAL(4244504319, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUAL(4261543680, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {100,0,0,128,64,100,0,0,255,194,100,0,0,128,65};
    float32_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUAL(4, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 15));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUAL(-127.5, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUAL(16.0, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {68,0,0,0,0,0,0,128,64,
                     68,0,0,255,194,0,0,255,194,
                     68,0,0,128,65,0,0,128,65
                    };
    float64_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUAL(512.0, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 27));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUAL(-545357971845120.000000, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUAL(33554440.187500, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {67,82,67,67,67,68};
    char value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('R', value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(3, len);

    if(3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('C', value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('D', value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,85,0};
    unsigned int text_length;
    char text[1]= {0};
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(obj, &text_length));
        TASSERT_EQUAL(0, text_length);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
        TASSERT_EQUAL(0, text[0]);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,85,5,'r','o','w','e','r'};
    unsigned int text_length;
    char text[5];
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 8));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(obj, &text_length));
        TASSERT_EQUAL(5, text_length);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
        TASSERT_NSTRING_EQUAL("rower", text, 5);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,105,5,'r','o','w','e','r'};
    unsigned int text_length;
    char text[5];
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 8));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(obj, &text_length));
        TASSERT_EQUAL(5, text_length);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
        TASSERT_NSTRING_EQUAL("rower", text, 5);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,73,5,0,'r','o','w','e','r'};
    unsigned int text_length;
    char text[5];
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(obj, &text_length));
        TASSERT_EQUAL(5, text_length);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
        TASSERT_NSTRING_EQUAL("rower", text, 5);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,108,5,0,0,0,'r','o','w','e','r'};
    unsigned int text_length;
    char text[5];
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(obj, &text_length));
        TASSERT_EQUAL(5, text_length);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
        TASSERT_NSTRING_EQUAL("rower", text, 5);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int8_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,105,255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Processor_str got int8 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int32_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,108,0,0,0,255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Processor_str got int32 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int16_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,73,0,255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Processor_str got int16 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_null()
{
    ubjs_parser *parser=0;
    unsigned int len;
    char *error;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,90};

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [90] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;
    char *error;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,78};

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [78] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_true()
{
    ubjs_parser *parser=0;
    unsigned int len;
    char *error;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,84};

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [84] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,70};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [70] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,67};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [67] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,83};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [83] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,76};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [76] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,100};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [100] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,68};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [68] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,91};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [91] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_str_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {83,123};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_ERROR, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 1 [123] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,85,5,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    uint8_t vu8;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(item, &vu8));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(5, vu8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,105,255,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int8_t v8;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(item, &v8));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(-1, v8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}


void test_parser_array_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,73,0,129,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int16_t v16;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);


    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(item, &v16));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(-32512, v16);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,108,0,129,0,129,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(item, &v32));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(-2130673408, v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,76,1,2,3,4,5,6,7,8,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int64_t v64=0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(item, &v64));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(67305985, v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,100,0,0,128,64,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    float32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(item, &v32));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(4, v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,68,0,0,0,0,0,0,128,64,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    float64_t v64;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 11));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(item, &v64));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(512, v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,90,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,78,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,84,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,70,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,67,(uint8_t)'r',93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    char v;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {

            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(item, &v));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL('r', v);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,83,85,5,'r','o','w','e','r',93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    char strung[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 10));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {

            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);

                TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(item, &length));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(5, length);

                TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(item, strung));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_NSTRING_EQUAL("rower", strung, 5);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,91,93,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {

            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);

                TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(item, &length));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(0, length);;
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91,123,125,93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        if(1 == length) {

            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if(0 != item) {
                TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(item, &ret));
                TASSERT_EQUAL(UTRUE, ret);

                TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(item, &length));
                TASSERT_EQUAL(UTRUE, ret);
                TASSERT_EQUAL(0, length);;
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',90,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));

    }
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',78,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));

    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',84,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;


    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',70,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;


    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',85,130,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    uint8_t vu8;


    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(other, &vu8));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(130, vu8);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',105,2,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    int8_t v8;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(other, &v8));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(2, v8);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',73,0,129,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    int16_t v16;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 8));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(other, &v16));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(-32512, v16);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',108,0,129,0,129,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    int32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 10));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(other, &v32));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(-2130673408, v32);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',76,1,2,3,4,5,6,7,8,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    int64_t v64;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 14));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(other, &v64));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(67305985, v64);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',100,0,0,128,64,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    float32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 10));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(other, &v32));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(4, v32);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',68,0,0,0,0,0,0,128,64,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    float64_t v64;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 14));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(other, &v64));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(512.0, v64);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',67,'r',125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;
    char v;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(other, &v));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL('r', v);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',83,85,5,'r','o','w','e','r',125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 13));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(other, &length));
            TASSERT_EQUAL(5, length);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(other, akey));
            TASSERT_NSTRING_EQUAL("rower", akey, 5);
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',91,93,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(other, &length));
            TASSERT_EQUAL(0, length);;
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123,85,1,'a',123,125,125};
    char akey[10];
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    ubjs_result ret2;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUAL(UR_OK, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUAL(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUAL(1, len);

    if(1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUAL(UTRUE, ret);
        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUAL(1, length);

        TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUAL(UR_OK, ret2);
        if(UR_OK == ret2) {
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUAL(1, length);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(other, &ret));
            TASSERT_EQUAL(UTRUE, ret);
            TASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(other, &length));
            TASSERT_EQUAL(0, length);;
        }
        TASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

