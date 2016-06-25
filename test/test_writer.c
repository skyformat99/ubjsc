#include <stdlib.h>

#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

CU_pSuite suite_writer() {
    CU_pSuite suite = CU_add_suite("writer", 0, 0);
    CU_ADD_TEST(suite, test_writer_init_clean);
    CU_ADD_TEST(suite, test_writer_basics);
    CU_ADD_TEST(suite, test_writer_null);
    CU_ADD_TEST(suite, test_writer_noop);
    CU_ADD_TEST(suite, test_writer_true);
    CU_ADD_TEST(suite, test_writer_false);
    CU_ADD_TEST(suite, test_writer_int8);
    CU_ADD_TEST(suite, test_writer_uint8);
    CU_ADD_TEST(suite, test_writer_int16);
    CU_ADD_TEST(suite, test_writer_int32);
    CU_ADD_TEST(suite, test_writer_int64);
    CU_ADD_TEST(suite, test_writer_float32);
    CU_ADD_TEST(suite, test_writer_float64);
    CU_ADD_TEST(suite, test_writer_char);

    CU_ADD_TEST(suite, test_writer_str_uint8);
    CU_ADD_TEST(suite, test_writer_str_int16);
    CU_ADD_TEST(suite, test_writer_str_int32);

    CU_ADD_TEST(suite, test_writer_array_empty);
    CU_ADD_TEST(suite, test_writer_array_uint8);
    CU_ADD_TEST(suite, test_writer_array_int8);
    CU_ADD_TEST(suite, test_writer_array_int16);
    CU_ADD_TEST(suite, test_writer_array_int32);
    CU_ADD_TEST(suite, test_writer_array_null);
    CU_ADD_TEST(suite, test_writer_array_noop);
    CU_ADD_TEST(suite, test_writer_array_true);
    CU_ADD_TEST(suite, test_writer_array_false);
    CU_ADD_TEST(suite, test_writer_array_char);
    CU_ADD_TEST(suite, test_writer_array_str);
    CU_ADD_TEST(suite, test_writer_array_float32);
    CU_ADD_TEST(suite, test_writer_array_float64);
    CU_ADD_TEST(suite, test_writer_array_array);
    CU_ADD_TEST(suite, test_writer_array_object);
    CU_ADD_TEST(suite, test_writer_array_count_optimized_uint8);
    CU_ADD_TEST(suite, test_writer_array_count_optimized_int16);
    CU_ADD_TEST(suite, test_writer_array_count_optimized_int32);

    CU_ADD_TEST(suite, test_writer_object_empty);
    CU_ADD_TEST(suite, test_writer_object_uint8);
    CU_ADD_TEST(suite, test_writer_object_int8);
    CU_ADD_TEST(suite, test_writer_object_int16);
    CU_ADD_TEST(suite, test_writer_object_int32);
    CU_ADD_TEST(suite, test_writer_object_int64);
    CU_ADD_TEST(suite, test_writer_object_null);
    CU_ADD_TEST(suite, test_writer_object_noop);
    CU_ADD_TEST(suite, test_writer_object_true);
    CU_ADD_TEST(suite, test_writer_object_false);
    CU_ADD_TEST(suite, test_writer_object_char);
    CU_ADD_TEST(suite, test_writer_object_str);
    CU_ADD_TEST(suite, test_writer_object_float32);
    CU_ADD_TEST(suite, test_writer_object_float64);
    CU_ADD_TEST(suite, test_writer_object_array);
    CU_ADD_TEST(suite, test_writer_object_object);
    CU_ADD_TEST(suite, test_writer_object_count_optimized_uint8);
    CU_ADD_TEST(suite, test_writer_object_count_optimized_int16);
    CU_ADD_TEST(suite, test_writer_object_count_optimized_int32);
    return suite;
}

void test_writer_init_clean()
{
    ubjs_writer *writer=0;

    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_writer_context *writer_context=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_new(&writer, 0));
    CU_ASSERT_EQUAL(0, writer);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, &context));

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));
    CU_ASSERT_NOT_EQUAL(0, writer);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(writer, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, &writer_context));
    CU_ASSERT_EQUAL(0, writer_context);
    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_get_context(writer, &writer_context));
    CU_ASSERT_EQUAL(&context, writer_context);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    CU_ASSERT_EQUAL(0, writer);
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_free));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_free(&writer));
    wrapped_writer_context_reset(wrapped);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));
    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_free));
    wrapped_writer_context_free(wrapped);
}

void test_writer_basics()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(writer, 0));
    CU_ASSERT_EQUAL(0, test_list_len(wrapped->calls_would_write));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, (ubjs_prmtv *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_null()));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(1, call->len);
        CU_ASSERT_EQUAL(90, call->data[0]);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_noop()));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(1, call->len);
        CU_ASSERT_EQUAL(78, call->data[0]);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_true()));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(1, call->len);
        CU_ASSERT_EQUAL(84, call->data[0]);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_false()));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(1, call->len);
        CU_ASSERT_EQUAL(70, call->data[0]);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int8_t value=-17;
    ubjs_prmtv *obj;

    ubjs_prmtv_int8(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(105, call->data[0]);
        CU_ASSERT_EQUAL(239, call->data[1]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int8_t value=17;
    ubjs_prmtv *obj;

    ubjs_prmtv_uint8(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(85, call->data[0]);
        CU_ASSERT_EQUAL(17, call->data[1]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int16_t value=-32512;
    ubjs_prmtv *obj;

    ubjs_prmtv_int16(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(3, call->len);
        CU_ASSERT_EQUAL(73, call->data[0]);
        CU_ASSERT_EQUAL(0, call->data[1]);
        CU_ASSERT_EQUAL(129, call->data[2]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int32_t value=100000;
    ubjs_prmtv *obj;

    ubjs_prmtv_int32(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(5, call->len);
        CU_ASSERT_EQUAL(108, call->data[0]);
        CU_ASSERT_EQUAL(105, call->data[1]);
        CU_ASSERT_EQUAL(122, call->data[2]);
        CU_ASSERT_EQUAL(16, call->data[3]);
        CU_ASSERT_EQUAL(0, call->data[4]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int64_t value=1048575L * 1048575L;
    ubjs_prmtv *obj;

    ubjs_prmtv_int64(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(9, call->len);
        CU_ASSERT_EQUAL(76, call->data[0]);
        CU_ASSERT_EQUAL(1, call->data[1]);
        CU_ASSERT_EQUAL(0, call->data[2]);
        CU_ASSERT_EQUAL(224, call->data[3]);
        CU_ASSERT_EQUAL(255, call->data[4]);
        CU_ASSERT_EQUAL(255, call->data[5]);
        CU_ASSERT_EQUAL(0, call->data[6]);
        CU_ASSERT_EQUAL(0, call->data[7]);
        CU_ASSERT_EQUAL(0, call->data[8]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    float32_t value=65535.95;
    ubjs_prmtv *obj;

    ubjs_prmtv_float32(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(5, call->len);
        CU_ASSERT_EQUAL(100, call->data[0]);
        CU_ASSERT_EQUAL(243, call->data[1]);
        CU_ASSERT_EQUAL(255, call->data[2]);
        CU_ASSERT_EQUAL(127, call->data[3]);
        CU_ASSERT_EQUAL(71, call->data[4]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    float64_t value=12345.6789;
    ubjs_prmtv *obj;

    ubjs_prmtv_float64(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(9, call->len);
        CU_ASSERT_EQUAL(68, call->data[0]);
        CU_ASSERT_EQUAL(161, call->data[1]);
        CU_ASSERT_EQUAL(248, call->data[2]);
        CU_ASSERT_EQUAL(49, call->data[3]);
        CU_ASSERT_EQUAL(230, call->data[4]);
        CU_ASSERT_EQUAL(214, call->data[5]);
        CU_ASSERT_EQUAL(28, call->data[6]);
        CU_ASSERT_EQUAL(200, call->data[7]);
        CU_ASSERT_EQUAL(64, call->data[8]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    char value='R';
    ubjs_prmtv *obj;

    ubjs_prmtv_char(value, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(67, call->data[0]);
        CU_ASSERT_EQUAL(82, call->data[1]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_str(5, "rower", &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(8, call->len);
        CU_ASSERT_EQUAL(83, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(5, call->data[2]);
        CU_ASSERT_NSTRING_EQUAL(call->data + 3, "rower", 5);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    int i;
    int length=10000;
    char *text=(char *)malloc(sizeof(char)*length);
    for(i=0; length>i; i++)text[i]='r';

    ubjs_prmtv_str(length, text, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(length + 4, call->len);
        CU_ASSERT_EQUAL(83, call->data[0]);
        CU_ASSERT_EQUAL(73, call->data[1]);
        CU_ASSERT_EQUAL(105, call->data[2]);
        CU_ASSERT_EQUAL(122, call->data[3]);
        CU_ASSERT_NSTRING_EQUAL(call->data + 4, text, length);
    }

    free(text);
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    int i;
    int length=100000;
    char *text=(char *)malloc(sizeof(char)*length);
    for(i=0; length>i; i++)text[i]='r';

    ubjs_prmtv_str(length, text, &obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(length + 6, call->len);
        CU_ASSERT_EQUAL(83, call->data[0]);
        CU_ASSERT_EQUAL(108, call->data[1]);
        CU_ASSERT_EQUAL(0, call->data[2]);
        CU_ASSERT_EQUAL(0, call->data[3]);
        CU_ASSERT_EQUAL(16, call->data[4]);
        CU_ASSERT_EQUAL(0, call->data[5]);
        CU_ASSERT_NSTRING_EQUAL(call->data + 6, text, length);
    }

    free(text);
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_empty()
{
    ubjs_writer *writer=0;

    wrapped_writer_context *wrapped=wrapped_writer_context_new();

    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_prmtv *obj;


    ubjs_prmtv_array(&obj);


    ubjs_writer_new(&writer, &context);


    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));

    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));


    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);

        CU_ASSERT_EQUAL(2, call->len);

        CU_ASSERT_EQUAL(91, call->data[0]);

        CU_ASSERT_EQUAL(93, call->data[1]);

    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_uint8(240, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(240, call->data[2]);
        CU_ASSERT_EQUAL(93, call->data[3]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_char('r', &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(67, call->data[1]);
        CU_ASSERT_EQUAL('r', call->data[2]);
        CU_ASSERT_EQUAL(93, call->data[3]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int8(-5, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(105, call->data[1]);
        CU_ASSERT_EQUAL(251, call->data[2]);
        CU_ASSERT_EQUAL(93, call->data[3]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int16(-32512, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(5, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(73, call->data[1]);
        CU_ASSERT_EQUAL(0, call->data[2]);
        CU_ASSERT_EQUAL(129, call->data[3]);
        CU_ASSERT_EQUAL(93, call->data[4]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int32(100000, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(108, call->data[1]);
        CU_ASSERT_EQUAL(105, call->data[2]);
        CU_ASSERT_EQUAL(122, call->data[3]);
        CU_ASSERT_EQUAL(16, call->data[4]);
        CU_ASSERT_EQUAL(0, call->data[5]);
        CU_ASSERT_EQUAL(93, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int64(1048575L * 1048575L, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(11, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(76, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL(0, call->data[3]);
        CU_ASSERT_EQUAL(224, call->data[4]);
        CU_ASSERT_EQUAL(255, call->data[5]);
        CU_ASSERT_EQUAL(255, call->data[6]);
        CU_ASSERT_EQUAL(0, call->data[7]);
        CU_ASSERT_EQUAL(0, call->data[8]);
        CU_ASSERT_EQUAL(0, call->data[9]);
        CU_ASSERT_EQUAL(93, call->data[10]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_float32(65535.95, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(100, call->data[1]);
        CU_ASSERT_EQUAL(243, call->data[2]);
        CU_ASSERT_EQUAL(255, call->data[3]);
        CU_ASSERT_EQUAL(127, call->data[4]);
        CU_ASSERT_EQUAL(71, call->data[5]);
        CU_ASSERT_EQUAL(93, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_float64(12345.6789, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(11, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(68, call->data[1]);
        CU_ASSERT_EQUAL(161, call->data[2]);
        CU_ASSERT_EQUAL(248, call->data[3]);
        CU_ASSERT_EQUAL(49, call->data[4]);
        CU_ASSERT_EQUAL(230, call->data[5]);
        CU_ASSERT_EQUAL(214, call->data[6]);
        CU_ASSERT_EQUAL(28, call->data[7]);
        CU_ASSERT_EQUAL(200, call->data[8]);
        CU_ASSERT_EQUAL(64, call->data[9]);
        CU_ASSERT_EQUAL(93, call->data[10]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(3, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(90, call->data[1]);
        CU_ASSERT_EQUAL(93, call->data[2]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(3, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(78, call->data[1]);
        CU_ASSERT_EQUAL(93, call->data[2]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_true());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(3, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(84, call->data[1]);
        CU_ASSERT_EQUAL(93, call->data[2]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_false());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(3, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(70, call->data[1]);
        CU_ASSERT_EQUAL(93, call->data[2]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_str()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char *rower="rower";

    ubjs_prmtv_str(5, rower, &item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(10, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(83, call->data[1]);
        CU_ASSERT_EQUAL(85, call->data[2]);
        CU_ASSERT_EQUAL(5, call->data[3]);
        CU_ASSERT_NSTRING_EQUAL(rower, call->data + 4, 5);
        CU_ASSERT_EQUAL(93, call->data[9]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_array()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_array(&item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(91, call->data[1]);
        CU_ASSERT_EQUAL(93, call->data[2]);
        CU_ASSERT_EQUAL(93, call->data[3]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_object()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_object(&item);
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(123, call->data[1]);
        CU_ASSERT_EQUAL(125, call->data[2]);
        CU_ASSERT_EQUAL(93, call->data[3]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_count_optimized_uint8() {
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    unsigned int i;

    ubjs_prmtv_array(&obj);
    for(i=0; i<10; i++) {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(4+10, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);
        CU_ASSERT_EQUAL(85, call->data[2]);
        CU_ASSERT_EQUAL(10, call->data[3]);
        for(i=0; i<10; i++) {
            CU_ASSERT_EQUAL(90, call->data[4+i]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_count_optimized_int16() {
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    unsigned int i;

    ubjs_prmtv_array(&obj);
    for(i=0; i<10000; i++) {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(5+10000, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);
        CU_ASSERT_EQUAL(73, call->data[2]);
        CU_ASSERT_EQUAL(105, call->data[3]);
        CU_ASSERT_EQUAL(122, call->data[4]);
        for(i=0; i<10000; i++) {
            CU_ASSERT_EQUAL(90, call->data[5+i]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_count_optimized_int32() {
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    unsigned int i;

    ubjs_prmtv_array(&obj);
    for(i=0; i<100000; i++) {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7+100000, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);

        CU_ASSERT_EQUAL(108, call->data[2]);
        CU_ASSERT_EQUAL(0, call->data[3]);
        CU_ASSERT_EQUAL(0, call->data[4]);
        CU_ASSERT_EQUAL(16, call->data[5]);
        CU_ASSERT_EQUAL(0, call->data[6]);
        for(i=0; i<100000; i++) {
            CU_ASSERT_EQUAL(90, call->data[7+i]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_empty()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_object(&obj);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(125, call->data[1]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_uint8(240, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(85, call->data[4]);
        CU_ASSERT_EQUAL(240, call->data[5]);
        CU_ASSERT_EQUAL(125, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_char('r', &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(67, call->data[4]);
        CU_ASSERT_EQUAL('r', call->data[5]);
        CU_ASSERT_EQUAL(125, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}


void test_writer_object_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int8(-5, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(105, call->data[4]);
        CU_ASSERT_EQUAL(251, call->data[5]);
        CU_ASSERT_EQUAL(125, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int16(-32512, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(8, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(73, call->data[4]);
        CU_ASSERT_EQUAL(0, call->data[5]);
        CU_ASSERT_EQUAL(129, call->data[6]);
        CU_ASSERT_EQUAL(125, call->data[7]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int32(100000, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(10, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(108, call->data[4]);
        CU_ASSERT_EQUAL(105, call->data[5]);
        CU_ASSERT_EQUAL(122, call->data[6]);
        CU_ASSERT_EQUAL(16, call->data[7]);
        CU_ASSERT_EQUAL(0, call->data[8]);
        CU_ASSERT_EQUAL(125, call->data[9]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_int64(1048575L * 1048575L, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(14, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(76, call->data[4]);
        CU_ASSERT_EQUAL(1, call->data[5]);
        CU_ASSERT_EQUAL(0, call->data[6]);
        CU_ASSERT_EQUAL(224, call->data[7]);
        CU_ASSERT_EQUAL(255, call->data[8]);
        CU_ASSERT_EQUAL(255, call->data[9]);
        CU_ASSERT_EQUAL(0, call->data[10]);
        CU_ASSERT_EQUAL(0, call->data[11]);
        CU_ASSERT_EQUAL(0, call->data[12]);
        CU_ASSERT_EQUAL(125, call->data[13]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_float32(65535.95, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(10, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(100, call->data[4]);
        CU_ASSERT_EQUAL(243, call->data[5]);
        CU_ASSERT_EQUAL(255, call->data[6]);
        CU_ASSERT_EQUAL(127, call->data[7]);
        CU_ASSERT_EQUAL(71, call->data[8]);
        CU_ASSERT_EQUAL(125, call->data[9]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_float64(12345.6789, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(14, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(68, call->data[4]);
        CU_ASSERT_EQUAL(161, call->data[5]);
        CU_ASSERT_EQUAL(248, call->data[6]);
        CU_ASSERT_EQUAL(49, call->data[7]);
        CU_ASSERT_EQUAL(230, call->data[8]);
        CU_ASSERT_EQUAL(214, call->data[9]);
        CU_ASSERT_EQUAL(28, call->data[10]);
        CU_ASSERT_EQUAL(200, call->data[11]);
        CU_ASSERT_EQUAL(64, call->data[12]);
        CU_ASSERT_EQUAL(125, call->data[13]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", ubjs_prmtv_null());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(6, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(90, call->data[4]);
        CU_ASSERT_EQUAL(125, call->data[5]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", ubjs_prmtv_noop());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(6, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(78, call->data[4]);
        CU_ASSERT_EQUAL(125, call->data[5]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", ubjs_prmtv_true());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(6, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(84, call->data[4]);
        CU_ASSERT_EQUAL(125, call->data[5]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", ubjs_prmtv_false());

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(6, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(70, call->data[4]);
        CU_ASSERT_EQUAL(125, call->data[5]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_str()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char *rower="rower";

    ubjs_prmtv_str(5, rower, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(13, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(83, call->data[4]);
        CU_ASSERT_EQUAL(85, call->data[5]);
        CU_ASSERT_EQUAL(5, call->data[6]);
        CU_ASSERT_NSTRING_EQUAL(rower, call->data + 7, 5);
        CU_ASSERT_EQUAL(125, call->data[12]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_array()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_array(&item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(91, call->data[4]);
        CU_ASSERT_EQUAL(93, call->data[5]);
        CU_ASSERT_EQUAL(125, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_object()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    ubjs_prmtv_object(&item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj,1, "a", item);

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(7, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(85, call->data[1]);
        CU_ASSERT_EQUAL(1, call->data[2]);
        CU_ASSERT_EQUAL('a', call->data[3]);
        CU_ASSERT_EQUAL(123, call->data[4]);
        CU_ASSERT_EQUAL(125, call->data[5]);
        CU_ASSERT_EQUAL(125, call->data[6]);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_count_optimized_uint8() {
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
	char key[10];
    unsigned int i;
	unsigned int at;
	unsigned long expected_length=4;
	unsigned int klen;

    ubjs_prmtv_object(&obj);
    for(i=0; i<10; i++) {
		klen=snprintf(key, 10, "%05d", i);
		expected_length += 3 + klen;
		ubjs_prmtv_object_set(obj, klen, key, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
		
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(expected_length, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);
        CU_ASSERT_EQUAL(85, call->data[2]);
        CU_ASSERT_EQUAL(10, call->data[3]);

        for(i=0, at=4; i<10; i++) {
			klen=snprintf(key, 10, "%05d", i);
			CU_ASSERT_EQUAL(85, call->data[at++]);
			CU_ASSERT_EQUAL(klen, call->data[at++]);
			CU_ASSERT_EQUAL(0, strncmp(key, call->data + at, klen));
			at+=klen;
            CU_ASSERT_EQUAL(90, call->data[at++]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_count_optimized_int16() {
	ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
	char key[10];
    unsigned int i;
	unsigned int at;
	unsigned long expected_length=5;

    ubjs_prmtv_object(&obj);
    for(i=0; i<10000; i++) {
		snprintf(key, 10, "%04d", i);
		expected_length += 7;
		ubjs_prmtv_object_set(obj, 4, key, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(expected_length, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);
        CU_ASSERT_EQUAL(73, call->data[2]);
        CU_ASSERT_EQUAL(16, call->data[3]);
        CU_ASSERT_EQUAL(39, call->data[4]);

        for(i=0, at=5; i<10000; i++) {
			snprintf(key, 10, "%04d", i);
			
			CU_ASSERT_EQUAL(85, call->data[at++]);
			CU_ASSERT_EQUAL(4, call->data[at++]);
			CU_ASSERT_EQUAL(0, strncmp(key, call->data + at, 4));
			at+=4;
			CU_ASSERT_EQUAL(90, call->data[at++]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_object_count_optimized_int32() {
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_prmtv *obj;
	char key[10];
    unsigned int i;
	unsigned int at;
	unsigned long expected_length=5;

    ubjs_prmtv_object(&obj);
    for(i=0; i<100000; i++) {
		snprintf(key, 10, "%05d", i);
		expected_length += 8;
		ubjs_prmtv_object_set(obj, 5, key, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(expected_length, call->len);
        CU_ASSERT_EQUAL(123, call->data[0]);
        CU_ASSERT_EQUAL(35, call->data[1]);
      
        CU_ASSERT_EQUAL(108, call->data[0]);
        CU_ASSERT_EQUAL(105, call->data[1]);
        CU_ASSERT_EQUAL(122, call->data[2]);
        CU_ASSERT_EQUAL(16, call->data[3]);
        CU_ASSERT_EQUAL(0, call->data[4]);

        for(i=0, at=6; i<100000; i++) {
			snprintf(key, 10, "%05d", i);
			if(0==(i % 1000)){printf("at %d %s\n", i, key);}
			
			CU_ASSERT_EQUAL(85, call->data[at++]);
			CU_ASSERT_EQUAL(5, call->data[at++]);
			CU_ASSERT_EQUAL(0, strncmp(key, call->data + at, 5));
			at+=5;
			CU_ASSERT_EQUAL(90, call->data[at++]);
        }
    }
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}
