#include "test.h"

void test_object_null()
{
    ubjs_object *object = 0;
    ubjs_bool ret=0;

    object = ubjs_object_null();
    CU_ASSERT(0 != object);

    CU_ASSERT(object == ubjs_object_null());
    CU_ASSERT(UR_ERROR == ubjs_object_is_null(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_null(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_null(0, &ret));

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_noop()
{
    ubjs_object *object = 0;
    ubjs_bool ret=0;

    object = ubjs_object_noop();
    CU_ASSERT(0 != object);

    CU_ASSERT(object == ubjs_object_noop());
    CU_ASSERT(UR_ERROR == ubjs_object_is_noop(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_noop(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_noop(0, &ret));

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_true()
{
    ubjs_object *object = 0;
    ubjs_bool ret=0;

    object = ubjs_object_true();
    CU_ASSERT(0 != object);

    CU_ASSERT(object == ubjs_object_true());
    CU_ASSERT(UR_ERROR == ubjs_object_is_true(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_true(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_true(0, &ret));

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_false()
{
    ubjs_object *object = 0;
    ubjs_bool ret=0;

    object = ubjs_object_false();
    CU_ASSERT(0 != object);

    CU_ASSERT(object == ubjs_object_false());
    CU_ASSERT(UR_ERROR == ubjs_object_is_false(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_false(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_false(0, &ret));

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_int8()
{
    ubjs_object *object = 0;
    ubjs_object *other = 0;
    int8_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_int8(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int8(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int8(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_int8(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_int8(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(ubjs_object_false(), 2));

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_int8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int8_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_int8_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_int8_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_int8_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_uint8()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    uint8_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_uint8(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_uint8(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_uint8(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_uint8(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_uint8(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_uint8_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_uint8_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_uint8_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_uint8_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_int16()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    int16_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_int16(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int16(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int16(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_int16(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_int16(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_int16_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int16_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_int16_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_int16_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_int16_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_int32()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    int32_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_int32(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int32(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int32(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_int32(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_int32(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_int32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int32_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_int32_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_int32_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_int32_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_int64()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    int64_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_int64(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int64(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_int64(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_int64(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_int64(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_int64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_int64_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_int64_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_int64_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_int64_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_float32()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    float32_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_float32(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_float32(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_float32(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_float32(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_float32(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_float32_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float32_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(0 != object);
    CU_ASSERT(UR_OK == ubjs_object_float32_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_float32_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_float32_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_float64()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    float64_t v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_float64(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_float64(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_float64(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(0, 0));

    CU_ASSERT(UR_OK == ubjs_object_float64(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_float64(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_float64_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_float64_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(0 != object);
    CU_ASSERT(UR_OK == ubjs_object_float64_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_float64_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_float64_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_uint8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_char()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    unsigned char v;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_char(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_char(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_char(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(0, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_char(0, 0));

    CU_ASSERT(UR_ERROR == ubjs_object_char(128, &object));

    CU_ASSERT(UR_OK == ubjs_object_char(1, &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_char(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(ubjs_object_null(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(ubjs_object_noop(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(ubjs_object_true(), &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(ubjs_object_false(), &v));

    CU_ASSERT(UR_ERROR == ubjs_object_char_set(0, 2));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(ubjs_object_null(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(ubjs_object_noop(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(ubjs_object_true(), 2));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(ubjs_object_false(), 2));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_char_get(other, &v));
    CU_ASSERT(UR_ERROR == ubjs_object_char_set(other, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_char_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_ERROR == ubjs_object_char_set(object, 128));
    CU_ASSERT(UR_OK == ubjs_object_char_get(object, &v));
    CU_ASSERT(1 == v);

    CU_ASSERT(UR_OK == ubjs_object_char_set(object, 2));
    CU_ASSERT(UR_OK == ubjs_object_char_get(object, &v));
    CU_ASSERT(2 == v);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_str()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    unsigned int vl;
    unsigned char v[3];
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_str(0, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_str(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_str(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(0, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(0, v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(0, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(0, 0, v));

    CU_ASSERT(UR_OK == ubjs_object_str(3, "kra", &object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_str(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(ubjs_object_null(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(ubjs_object_noop(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(ubjs_object_true(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(ubjs_object_false(), &vl));

    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_null(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_noop(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_true(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));

    CU_ASSERT(UR_ERROR == ubjs_object_str_set(object, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(ubjs_object_null(), vl, v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(ubjs_object_noop(), vl, v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(ubjs_object_true(), vl, v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(ubjs_object_false(), vl, v));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    ubjs_object_array(&other);
    CU_ASSERT(UR_ERROR == ubjs_object_str_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_str_copy_text(ubjs_object_false(), v));
    CU_ASSERT(UR_ERROR == ubjs_object_str_set(other, vl, v));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_str_get_length(object, &vl));
    CU_ASSERT(3 == vl);

    CU_ASSERT(UR_OK == ubjs_object_str_copy_text(object, v));
    CU_ASSERT(0 == strncmp("kra", v, 3));

    CU_ASSERT(UR_OK == ubjs_object_str_set(object, 2, "ur"));
    CU_ASSERT(UR_OK == ubjs_object_str_get_length(object, &vl));
    CU_ASSERT(2 == vl);

    CU_ASSERT(UR_OK == ubjs_object_str_copy_text(object, v));
    CU_ASSERT(0 == strncmp("ur", v, 2));

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UFALSE == ret);

    CU_ASSERT(UR_ERROR == ubjs_object_free(0));
    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

void test_object_array()
{
    ubjs_object *object = 0;
    ubjs_object *other;
    ubjs_object *other2;
    ubjs_object *other3;
    ubjs_array_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;

    CU_ASSERT(UR_ERROR == ubjs_object_is_array(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_is_array(0, &ret));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(0, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(0, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(0, 0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(0, other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(0, other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(0, 0,0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(0, 0,other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(0, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(0, &iterator));

    CU_ASSERT(UR_OK == ubjs_object_array(&object));
    CU_ASSERT(0 != object);

    CU_ASSERT(UR_ERROR == ubjs_object_is_array(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(ubjs_object_null(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(ubjs_object_noop(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(ubjs_object_true(), &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(ubjs_object_false(), &vl));

    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(ubjs_object_null(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(ubjs_object_noop(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(ubjs_object_true(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(ubjs_object_false(), &other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(ubjs_object_null(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(ubjs_object_noop(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(ubjs_object_true(), &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(ubjs_object_false(), &other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(object, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(object, 0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(ubjs_object_null(), 0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(ubjs_object_noop(), 0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(ubjs_object_true(), 0, &other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(ubjs_object_false(), 0, &other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(ubjs_object_null(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(ubjs_object_noop(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(ubjs_object_true(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(ubjs_object_false(), other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(ubjs_object_null(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(ubjs_object_noop(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(ubjs_object_true(), other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(ubjs_object_false(), other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(object, 0, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(object, 1, other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(ubjs_object_null(), 0,other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(ubjs_object_noop(), 0,other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(ubjs_object_true(), 0,other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(ubjs_object_false(), 0,other));

    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(object));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(ubjs_object_null()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(ubjs_object_noop()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(ubjs_object_true()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(ubjs_object_false()));

    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(object));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(ubjs_object_null()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(ubjs_object_noop()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(ubjs_object_true()));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(ubjs_object_false()));

    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(ubjs_object_null(), 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(ubjs_object_noop(), 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(ubjs_object_true(), 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(ubjs_object_false(), 0));

    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(ubjs_object_null(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(ubjs_object_noop(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(ubjs_object_true(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(ubjs_object_false(), &iterator));

    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(object, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(ubjs_object_null(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(ubjs_object_noop(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(ubjs_object_true(), &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(ubjs_object_false(), &iterator));

    ubjs_object_int8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_uint8(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_int16(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_int32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_int64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_float32(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_float64(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    ubjs_object_str(0, "", &other);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_length(other, &vl));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(other, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_at(other, 0, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_first(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_last(other, other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_add_at(other, 0,other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_first(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_last(other));
    CU_ASSERT(UR_ERROR == ubjs_object_array_remove_at(other, 0));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_forward(other, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_object_array_iterate_backward(other, &iterator));
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(0 == vl);

    ubjs_object_char(0, &other);
    CU_ASSERT(UR_OK == ubjs_object_array_add_first(object, other));
    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(1 == vl);
    CU_ASSERT(UR_OK == ubjs_object_array_get_first(object, &other2));
    CU_ASSERT(other==other2);
    CU_ASSERT(UR_OK == ubjs_object_array_get_last(object, &other2));
    CU_ASSERT(other==other2);
    CU_ASSERT(UR_OK == ubjs_object_array_get_at(object, 0, &other2));
    CU_ASSERT(other==other2);

    CU_ASSERT(UR_OK == ubjs_object_array_iterate_forward(object, &iterator));
    CU_ASSERT(UR_OK == ubjs_array_iterator_next(iterator, &other2));
    CU_ASSERT(other==other2);
    CU_ASSERT(UR_ERROR == ubjs_array_iterator_next(iterator, &other2));
    CU_ASSERT(UR_OK==ubjs_array_iterator_free(&iterator));

    CU_ASSERT(UR_OK == ubjs_object_array_remove_first(object));
    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(0 == vl);
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_first(object, &other2));
    CU_ASSERT(UR_ERROR == ubjs_object_array_get_last(object, &other2));

    CU_ASSERT(UR_OK == ubjs_object_array_iterate_forward(object, &iterator));
    CU_ASSERT(UR_ERROR == ubjs_array_iterator_next(iterator, &other2));
    CU_ASSERT(UR_OK==ubjs_array_iterator_free(&iterator));

    CU_ASSERT(UR_OK == ubjs_object_array_add_last(object, other));
    CU_ASSERT(UR_OK == ubjs_object_array_remove_last(object));
    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(0 == vl);

    CU_ASSERT(UR_OK == ubjs_object_array_add_at(object, 0,other));
    CU_ASSERT(UR_OK == ubjs_object_array_remove_at(object, 0));
    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(0 == vl);

    ubjs_object_char(1, &other2);

    CU_ASSERT(UR_OK == ubjs_object_array_add_last(object, other));
    CU_ASSERT(UR_OK == ubjs_object_array_add_last(object, other2));
    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(2 == vl);

    CU_ASSERT(UR_OK == ubjs_object_array_get_at(object, 0, &other3));
    CU_ASSERT(other==other3);
    CU_ASSERT(UR_OK == ubjs_object_array_get_at(object, 1, &other3));
    CU_ASSERT(other2==other3);

    CU_ASSERT(UR_OK == ubjs_object_array_get_first(object, &other3));
    CU_ASSERT(other==other3);
    CU_ASSERT(UR_OK == ubjs_object_array_get_last(object, &other3));
    CU_ASSERT(other2==other3);

    CU_ASSERT(UR_OK == ubjs_object_array_iterate_forward(object, &iterator));
    CU_ASSERT(UR_OK == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(other==other3);
    CU_ASSERT(UR_OK == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(other2==other3);
    CU_ASSERT(UR_ERROR == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(UR_OK==ubjs_array_iterator_free(&iterator));

    CU_ASSERT(UR_OK == ubjs_object_array_iterate_backward(object, &iterator));
    CU_ASSERT(UR_OK == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(other2==other3);
    CU_ASSERT(UR_OK == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(other==other3);
    CU_ASSERT(UR_ERROR == ubjs_array_iterator_next(iterator, &other3));
    CU_ASSERT(UR_OK==ubjs_array_iterator_free(&iterator));

    CU_ASSERT(UR_OK == ubjs_object_array_remove_last(object));
    CU_ASSERT(UR_OK == ubjs_object_array_remove_last(object));

    CU_ASSERT(UR_OK == ubjs_object_array_get_length(object, &vl));
    CU_ASSERT(0 == vl);

    ubjs_object_free(&other2);
    ubjs_object_free(&other);

    CU_ASSERT(UR_OK == ubjs_object_is_null(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_noop(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_true(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_false(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int8(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UTRUE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int16(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_int64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float32(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_float64(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_char(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_str(object, &ret));
    CU_ASSERT(UFALSE == ret);
    CU_ASSERT(UR_OK == ubjs_object_is_array(object, &ret));
    CU_ASSERT(UTRUE == ret);

    CU_ASSERT(UR_OK == ubjs_object_free(&object));
    CU_ASSERT(0 == object);
}

