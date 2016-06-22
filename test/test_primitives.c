#include "test_primitives.h"

CU_pSuite suite_objects() {
    CU_pSuite suite = CU_add_suite("objects", 0, 0);

    CU_ADD_TEST(suite, test_prmtv_null);
    CU_ADD_TEST(suite, test_prmtv_null);
    CU_ADD_TEST(suite, test_prmtv_noop);
    CU_ADD_TEST(suite, test_prmtv_true);
    CU_ADD_TEST(suite, test_prmtv_false);
    CU_ADD_TEST(suite, test_prmtv_int8);
    CU_ADD_TEST(suite, test_prmtv_uint8);
    CU_ADD_TEST(suite, test_prmtv_int16);
    CU_ADD_TEST(suite, test_prmtv_int32);
    CU_ADD_TEST(suite, test_prmtv_int64);
    CU_ADD_TEST(suite, test_prmtv_float32);
    CU_ADD_TEST(suite, test_prmtv_float64);
    CU_ADD_TEST(suite, test_prmtv_char);
    CU_ADD_TEST(suite, test_prmtv_str);
    CU_ADD_TEST(suite, test_prmtv_array);
    CU_ADD_TEST(suite, test_prmtv_object);

    return suite;
}

void test_prmtv_null()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;

    object = ubjs_prmtv_null();
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(object, ubjs_prmtv_null());
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_null(0, &ret));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_noop()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;

    object = ubjs_prmtv_noop();
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(object, ubjs_prmtv_noop());
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_noop(0, &ret));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_true()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;

    object = ubjs_prmtv_true();
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(object, ubjs_prmtv_true());
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_true(0, &ret));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_false()
{
    ubjs_prmtv *object = 0;
    ubjs_bool ret=0;

    object = ubjs_prmtv_false();
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(object, ubjs_prmtv_false());
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_false(0, &ret));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int8()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other = 0;
    int8_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int8(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_uint8()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    uint8_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_uint8(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int16()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    int16_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int16(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int32()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    int32_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int32(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int64()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    int64_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_int64(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_float32()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    float32_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float32(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_NOT_EQUAL(0, object);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_float64()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    float64_t v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_float64(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_NOT_EQUAL(0, object);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_char()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    char v;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(0, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char(0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char(1, &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_char(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(ubjs_prmtv_null(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(ubjs_prmtv_noop(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(ubjs_prmtv_true(), &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(ubjs_prmtv_false(), &v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(ubjs_prmtv_null(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(ubjs_prmtv_noop(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(ubjs_prmtv_true(), 2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(ubjs_prmtv_false(), 2));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(other, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(other, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_str()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(0, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(0, v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(0, 0, v));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str(3, "kra", &object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_str(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(ubjs_prmtv_null(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(ubjs_prmtv_noop(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(ubjs_prmtv_true(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(ubjs_prmtv_false(), &vl));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_null(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_noop(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_true(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(object, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(ubjs_prmtv_null(), vl, v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(ubjs_prmtv_noop(), vl, v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(ubjs_prmtv_true(), vl, v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(ubjs_prmtv_false(), vl, v));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_array(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(ubjs_prmtv_false(), v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(other, vl, v));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    CU_ASSERT_EQUAL(3, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    CU_ASSERT_NSTRING_EQUAL("kra", v, 3);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_set(object, 2, "ur"));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    CU_ASSERT_EQUAL(2, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    CU_ASSERT_NSTRING_EQUAL("ur", v, 2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_array()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other;
    ubjs_prmtv *other2;
    ubjs_prmtv *other3;
    ubjs_array_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(0, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(0, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(0, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(0, 0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(0, 0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(0, &iterator));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_free(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(0, &other2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array(&object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_array(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(ubjs_prmtv_null(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(ubjs_prmtv_noop(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(ubjs_prmtv_true(), &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(ubjs_prmtv_false(), &vl));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(ubjs_prmtv_null(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(ubjs_prmtv_noop(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(ubjs_prmtv_true(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(ubjs_prmtv_false(), &other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(ubjs_prmtv_null(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(ubjs_prmtv_noop(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(ubjs_prmtv_true(), &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(ubjs_prmtv_false(), &other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(ubjs_prmtv_null(), 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(ubjs_prmtv_noop(), 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(ubjs_prmtv_true(), 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(ubjs_prmtv_false(), 0, &other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(ubjs_prmtv_null(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(ubjs_prmtv_noop(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(ubjs_prmtv_true(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(ubjs_prmtv_false(), other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(ubjs_prmtv_null(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(ubjs_prmtv_noop(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(ubjs_prmtv_true(), other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(ubjs_prmtv_false(), other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 1, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(ubjs_prmtv_null(), 0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(ubjs_prmtv_noop(), 0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(ubjs_prmtv_true(), 0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(ubjs_prmtv_false(), 0,other));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(object));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(ubjs_prmtv_null()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(ubjs_prmtv_noop()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(ubjs_prmtv_true()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(ubjs_prmtv_false()));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(object));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(ubjs_prmtv_null()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(ubjs_prmtv_noop()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(ubjs_prmtv_true()));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(ubjs_prmtv_false()));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(ubjs_prmtv_null(), 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(ubjs_prmtv_noop(), 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(ubjs_prmtv_true(), 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(ubjs_prmtv_false(), 0));

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(ubjs_prmtv_null(), &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(ubjs_prmtv_noop(), &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(ubjs_prmtv_true(), &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(ubjs_prmtv_false(), &iterator));

    ubjs_prmtv_int8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_uint8(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int16(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_int64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float32(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_float64(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_str(0, "", &other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    ubjs_prmtv_object(&other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(other, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(other, 0, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(other, other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(other, 0,other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(other, &iterator));
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    ubjs_prmtv_char(0, &other);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_first(object, other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_first(object, &other2));
    CU_ASSERT_EQUAL(other, other2);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_last(object, &other2));
    CU_ASSERT_EQUAL(other, other2);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other2));
    CU_ASSERT_EQUAL(other, other2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, 0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other2));
    CU_ASSERT_EQUAL(other, other2);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_first(object));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, &other2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, &other2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_at(object, 0,other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_at(object, 0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    ubjs_prmtv_char(1, &other2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(2, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 0, &other3));
    CU_ASSERT_EQUAL(other, other3);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_at(object, 1, &other3));
    CU_ASSERT_EQUAL(other2, other3);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_first(object, &other3));
    CU_ASSERT_EQUAL(other, other3);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_last(object, &other3));
    CU_ASSERT_EQUAL(other2, other3);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other3));
    CU_ASSERT_EQUAL(other, other3);
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_get(iterator, &other3));
    CU_ASSERT_EQUAL(other2, other3);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_array_iterator_get(iterator, &other3));
    CU_ASSERT_EQUAL(UR_OK, ubjs_array_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    ubjs_prmtv_free(&other2);
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}


void test_prmtv_object()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other=0;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    char *key="a";
    ubjs_bool ret=0;
    void *nvalue=0;
    char *key2[10];

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, &vl,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,0,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, &vl,0,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,key,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, &vl,key,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,key,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, &vl,key,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, &vl,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, &vl,0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,key,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, &vl,key,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,key,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, &vl,key,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, &vl,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0,key));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, &vl,key));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_free(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0,&vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0,key2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0,&nvalue));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object(&object));
    CU_ASSERT_NOT_EQUAL(0, object);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);

}

