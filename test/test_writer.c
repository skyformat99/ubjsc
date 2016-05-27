#include "test.h"
#include "test_list.h"
#include "test_writer_tools.h"

void test_writer_init_clean()
{
    ubjs_writer *writer=0;

    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};
    ubjs_writer_context *writer_context=0;

    CU_ASSERT(UR_ERROR == ubjs_writer_alloc(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_writer_alloc(&writer, 0));
    CU_ASSERT(0 == writer);
    CU_ASSERT(UR_ERROR == ubjs_writer_alloc(0, &context));

    CU_ASSERT(UR_OK == ubjs_writer_alloc(&writer, &context));
    CU_ASSERT(0 != writer);

    CU_ASSERT(UR_ERROR == ubjs_writer_get_context(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_writer_get_context(writer, 0));
    CU_ASSERT(UR_ERROR == ubjs_writer_get_context(0, &writer_context));
    CU_ASSERT(0 == writer_context);
    CU_ASSERT(UR_OK == ubjs_writer_get_context(writer, &writer_context));
    CU_ASSERT(&context == writer_context);

    CU_ASSERT(UR_ERROR == ubjs_writer_free(0));
    CU_ASSERT(UR_OK == ubjs_writer_free(&writer));
    CU_ASSERT(0 == writer);
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    CU_ASSERT(UR_ERROR == ubjs_writer_free(&writer));
    wrapped_writer_context_reset(wrapped);

    CU_ASSERT(UR_OK == ubjs_writer_alloc(&writer, &context));
    CU_ASSERT(UR_OK == ubjs_writer_free(&writer));
    CU_ASSERT(1 == test_list_len(wrapped->calls_free));
    wrapped_writer_context_free(wrapped);
}

void test_writer_basics()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    CU_ASSERT(UR_OK == ubjs_writer_alloc(&writer, &context));

    CU_ASSERT(UR_ERROR == ubjs_writer_write(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_writer_write(writer, 0));
    CU_ASSERT(0 == test_list_len(wrapped->calls_would_write));
    CU_ASSERT(UR_ERROR == ubjs_writer_write(0, (ubjs_object *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}

void test_writer_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped=wrapped_writer_context_new();
    ubjs_writer_context context = {wrapped, writer_context_would_write, writer_context_free};

    ubjs_writer_alloc(&writer, &context);

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, ubjs_object_null()));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(1 == call->len);
        CU_ASSERT(90 == call->data[0]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, ubjs_object_noop()));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(1 == call->len);
        CU_ASSERT(78 == call->data[0]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, ubjs_object_true()));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(1 == call->len);
        CU_ASSERT(84 == call->data[0]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, ubjs_object_false()));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(1 == call->len);
        CU_ASSERT(70 == call->data[0]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(2 == call->len);
        CU_ASSERT(105 == call->data[0]);
        CU_ASSERT(239 == call->data[1]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(2 == call->len);
        CU_ASSERT(85 == call->data[0]);
        CU_ASSERT(17 == call->data[1]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(3 == call->len);
        CU_ASSERT(73 == call->data[0]);
        CU_ASSERT(0 == call->data[1]);
        CU_ASSERT(129 == call->data[2]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(5 == call->len);
        CU_ASSERT(108 == call->data[0]);
        CU_ASSERT(105 == call->data[1]);
        CU_ASSERT(122 == call->data[2]);
        CU_ASSERT(16 == call->data[3]);
        CU_ASSERT(0 == call->data[4]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(9 == call->len);
        CU_ASSERT(76 == call->data[0]);
        CU_ASSERT(1 == call->data[1]);
        CU_ASSERT(0 == call->data[2]);
        CU_ASSERT(224 == call->data[3]);
        CU_ASSERT(255 == call->data[4]);
        CU_ASSERT(255 == call->data[5]);
        CU_ASSERT(0 == call->data[6]);
        CU_ASSERT(0 == call->data[7]);
        CU_ASSERT(0 == call->data[8]);
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

    CU_ASSERT(UR_OK == ubjs_writer_write(writer, obj));
    CU_ASSERT(1 == test_list_len(wrapped->calls_would_write));

    if(1 == test_list_len(wrapped->calls_would_write))
    {
        would_write_call *call=test_list_get(wrapped->calls_would_write, 0);
        CU_ASSERT(5 == call->len);
        CU_ASSERT(100 == call->data[0]);
        CU_ASSERT(243 == call->data[1]);
        CU_ASSERT(255 == call->data[2]);
        CU_ASSERT(127 == call->data[3]);
        CU_ASSERT(71 == call->data[4]);
    }

    ubjs_object_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(wrapped);
}
