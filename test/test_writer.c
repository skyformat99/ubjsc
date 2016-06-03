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
    CU_ADD_TEST(suite, test_writer_array_int64);
    //CU_ADD_TEST(suite, test_writer_array_null);
    //CU_ADD_TEST(suite, test_writer_array_noop);
    //CU_ADD_TEST(suite, test_writer_array_true);
    //CU_ADD_TEST(suite, test_writer_array_false);
    //CU_ADD_TEST(suite, test_writer_array_char);
    //CU_ADD_TEST(suite, test_writer_array_str);
    CU_ADD_TEST(suite, test_writer_array_float32);
    CU_ADD_TEST(suite, test_writer_array_float64);
    //CU_ADD_TEST(suite, test_writer_array_array);

    return suite;
}

void test_writer_init_clean()
{
    ubjs_writer *writer=0;

    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_writer_context *writer_context=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_alloc(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_alloc(&writer, 0));
    CU_ASSERT_EQUAL(0, writer);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_alloc(0, &context));

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_alloc(&writer, &context));
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_alloc(&writer, &context));
    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_free));
    wrapped_writer_context_free(wrapped);
}

void test_writer_basics()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_alloc(&writer, &context));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(writer, 0));
    CU_ASSERT_EQUAL(0, test_list_len(wrapped->calls_would_write));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, (ubjs_object *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_object_null()));
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

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_object_noop()));
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

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_object_true()));
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

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_object_false()));
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
    ubjs_object *obj;

    ubjs_object_int8(value, &obj);

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(105, call->data[0]);
        CU_ASSERT_EQUAL(239, call->data[1]);
    }

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int8_t value=17;
    ubjs_object *obj;

    ubjs_object_uint8(value, &obj);

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(85, call->data[0]);
        CU_ASSERT_EQUAL(17, call->data[1]);
    }

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int16_t value=-32512;
    ubjs_object *obj;

    ubjs_object_int16(value, &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int32_t value=1048576 + 31337;
    ubjs_object *obj;

    ubjs_object_int32(value, &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    int64_t value=1048575L * 1048575L;
    ubjs_object *obj;

    ubjs_object_int64(value, &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    float32_t value=65535.95;
    ubjs_object *obj;

    ubjs_object_float32(value, &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    float64_t value=12345.6789;
    ubjs_object *obj;

    ubjs_object_float64(value, &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    char value='R';
    ubjs_object *obj;

    ubjs_object_char(value, &obj);

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(67, call->data[0]);
        CU_ASSERT_EQUAL(82, call->data[1]);
    }

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;

    ubjs_object_str(5, "rower", &obj);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;

    int i;
    int length=31337;
    char *text=(char *)malloc(sizeof(char)*length);
    for(i=0; length>i; i++)text[i]='r';

    ubjs_object_str(length, text, &obj);

    ubjs_writer_alloc(&writer, &context);

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
    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_str_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;

    int i;
    int length=1048576;
    char *text=(char *)malloc(sizeof(char)*length);
    for(i=0; length>i; i++)text[i]='r';

    ubjs_object_str(length, text, &obj);

    ubjs_writer_alloc(&writer, &context);

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
    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_empty()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;

    ubjs_object_array(&obj);

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    CU_ASSERT_EQUAL(1, test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT_EQUAL(2, call->len);
        CU_ASSERT_EQUAL(91, call->data[0]);
        CU_ASSERT_EQUAL(93, call->data[1]);
    }

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_uint8(240, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_int8(-5, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_int16(-32512, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_int32(1048576 + 31337, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_int64(1048575L * 1048575L, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_float32(65535.95, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_array_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_object *obj;
    ubjs_object *item;

    ubjs_object_float64(12345.6789, &item);
    ubjs_object_array(&obj);
    ubjs_object_array_add_last(obj, item);

    ubjs_writer_alloc(&writer, &context);

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

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

