#include "test_primitives.h"

CU_pSuite suite_objects() {
    CU_pSuite suite = CU_add_suite("objects", 0, 0);

    CU_ADD_TEST(suite, test_prmtv_common);
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
    CU_ADD_TEST(suite, test_prmtv_calls_for_wrong_primitives);

    return suite;
}

void test_prmtv_common()
{
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

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

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

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

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

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int8()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int8_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_uint8()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_uint8_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int16()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int16_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int32()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int32_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_int64()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_int64_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_float32()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(0, 2));

    CU_ASSERT_NOT_EQUAL(0, object);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float32_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_float64()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(0, 2));

    CU_ASSERT_NOT_EQUAL(0, object);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_float64_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_char()
{
    ubjs_prmtv *object = 0;
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(0, 2));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(1, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_set(object, 2));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_char_get(object, &v));
    CU_ASSERT_EQUAL(2, v);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_free(0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_str()
{
    ubjs_prmtv *object = 0;
    unsigned int vl;
    char v[3];
    ubjs_bool ret=0;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str(0, "", 0));
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(object, 0, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    CU_ASSERT_EQUAL(3, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    CU_ASSERT_NSTRING_EQUAL("kra", v, 3);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_set(object, 2, "ur"));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_get_length(object, &vl));
    CU_ASSERT_EQUAL(2, vl);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_str_copy_text(object, v));
    CU_ASSERT_NSTRING_EQUAL("ur", v, 2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

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
    unsigned int it;

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array(0));
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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(object, 1, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(object));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(object));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));

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
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(object, 1, &other2));

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

    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_first(object, other));
    }
    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_at(object, 0, other));
    }
    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_add_last(object, other));
    }
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(300, vl);

    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_first(object));
    }
    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_at(object, 0));
    }
    for(it=0; it<100; it++) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_delete_last(object));
    }
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_array_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    ubjs_prmtv_free(&other2);
    ubjs_prmtv_free(&other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

void test_prmtv_object()
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *other=0;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_bool ret=0;
    char key2[10];

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(0, &ret));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(0, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,0,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(0, 0,"",&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(0, 0,"",other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(0, 0,""));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(0, &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_free(0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(0,&vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(0,key2));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(0,&other));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object(&object));
    CU_ASSERT_NOT_EQUAL(0, object);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(object, 0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_is_object(object, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0,0,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0,0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(object, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(object, 0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(object, 0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_NOT_EQUAL(0, iterator);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_key_length(iterator,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_copy_key(iterator,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_get_value(iterator,0));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    // 1 item
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other));
    CU_ASSERT_EQUAL(ubjs_prmtv_null(), other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator,&vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator,key2));
    CU_ASSERT_EQUAL(0, strncmp("a", key2, 1));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator,&other));
    CU_ASSERT_EQUAL(ubjs_prmtv_null(), other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    // 2 items
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "a", ubjs_prmtv_null()));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_set(object, 1, "b", ubjs_prmtv_noop()));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(2, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &other));
    CU_ASSERT_EQUAL(ubjs_prmtv_null(), other);
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "b", &other));
    CU_ASSERT_EQUAL(ubjs_prmtv_noop(), other);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator,&vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator,key2));
    CU_ASSERT_EQUAL(0, strncmp("a", key2, 1));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator,&other));
    CU_ASSERT_EQUAL(ubjs_prmtv_null(), other);
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator,&vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator,key2));
    CU_ASSERT_EQUAL(0, strncmp("b", key2, 1));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_value(iterator,&other));
    CU_ASSERT_EQUAL(ubjs_prmtv_noop(), other);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get(object, 1, "b", &other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_get_key_length(iterator,&vl));
    CU_ASSERT_EQUAL(1, vl);
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_copy_key(iterator,key2));
    CU_ASSERT_EQUAL(0, strncmp("b", key2, 1));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_delete(object, 1, "b"));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_get_length(object, &vl));
    CU_ASSERT_EQUAL(0, vl);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(object, 1, "b", &other));
    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_object_iterate(object, &iterator));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_object_iterator_next(iterator));
    CU_ASSERT_EQUAL(UR_OK, ubjs_object_iterator_free(&iterator));

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(object, &ret));
    CU_ASSERT_EQUAL(UTRUE, ret);

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_free(&object));
    CU_ASSERT_EQUAL(0, object);
}

unsigned int __primitives_len=15;
struct __primitive __primitives[] = {
    {__create_null, __test_null},
    {__create_noop, __test_noop},
    {__create_false, __test_false},
    {__create_true, __test_true},
    {__create_int8, __test_int8},
    {__create_uint8, __test_uint8},
    {__create_int16, __test_int16},
    {__create_int32, __test_int32},
    {__create_int64, __test_int64},
    {__create_float32, __test_float32},
    {__create_float64, __test_float64},
    {__create_char, __test_char},
    {__create_str, __test_str},
    {__create_array, __test_array},
    {__create_object, __test_object}
};

void __create_null(ubjs_prmtv **p) {
    *p=ubjs_prmtv_null();
}

void __test_null(ubjs_prmtv *p) {
    ubjs_bool ret;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_null(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
}

void __create_noop(ubjs_prmtv **p) {
    *p=ubjs_prmtv_noop();
}

void __test_noop(ubjs_prmtv *p) {
    ubjs_bool ret;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_noop(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
}

void __create_false(ubjs_prmtv **p) {
    *p=ubjs_prmtv_false();
}

void __test_false(ubjs_prmtv *p) {
    ubjs_bool ret;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_false(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
}

void __create_true(ubjs_prmtv **p) {
    *p=ubjs_prmtv_true();
}

void __test_true(ubjs_prmtv *p) {
    ubjs_bool ret;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_true(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
}

void __create_int8(ubjs_prmtv **p) {
    ubjs_prmtv_int8(0, p);
}

void __test_int8(ubjs_prmtv *p) {
    ubjs_bool ret;
    int8_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int8(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int8_set(p, v));
}

void __create_uint8(ubjs_prmtv **p) {
    ubjs_prmtv_uint8(0, p);
}

void __test_uint8(ubjs_prmtv *p) {
    ubjs_bool ret;
    uint8_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_uint8(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_uint8_set(p, v));
}

void __create_int16(ubjs_prmtv **p) {
    ubjs_prmtv_int16(0, p);
}

void __test_int16(ubjs_prmtv *p) {
    ubjs_bool ret;
    int16_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int16(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int16_set(p, v));
}

void __create_int32(ubjs_prmtv **p) {
    ubjs_prmtv_int32(0, p);
}

void __test_int32(ubjs_prmtv *p) {
    ubjs_bool ret;
    int32_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int32(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int32_set(p, v));
}

void __create_int64(ubjs_prmtv **p) {
    ubjs_prmtv_int64(0, p);
}

void __test_int64(ubjs_prmtv *p) {
    ubjs_bool ret;
    int64_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_int64(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_int64_set(p, v));
}

void __create_float32(ubjs_prmtv **p) {
    ubjs_prmtv_float32(0, p);
}

void __test_float32(ubjs_prmtv *p) {
    ubjs_bool ret;
    float32_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float32(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float32_set(p, v));
}

void __create_float64(ubjs_prmtv **p) {
    ubjs_prmtv_float64(0, p);
}

void __test_float64(ubjs_prmtv *p) {
    ubjs_bool ret;
    float64_t v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_float64(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_float64_set(p, v));
}

void __create_char(ubjs_prmtv **p) {
    ubjs_prmtv_char(0, p);
}

void __test_char(ubjs_prmtv *p) {
    ubjs_bool ret;
    char v;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_char(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_get(p, &v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_char_set(p, v));
}

void __create_str(ubjs_prmtv **p) {
    ubjs_prmtv_str(1, "a", p);
}

void __test_str(ubjs_prmtv *p) {
    ubjs_bool ret;
    unsigned int vl;
    char v[1];

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_str(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_get_length(p, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_copy_text(p, v));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_str_set(p, vl, v));
}


void __create_array(ubjs_prmtv **p) {
    ubjs_prmtv_array(p);
}

void __test_array(ubjs_prmtv *p) {
    ubjs_bool ret;
    ubjs_array_iterator *iterator=0;
    unsigned int vl;
    ubjs_prmtv *other=0;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_array(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);

    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_length(p, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_first(p, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_last(p, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_get_at(p, 0, &other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_first(p, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_last(p, other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_add_at(p, 0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_first(p));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_last(p));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_delete_at(p, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_array_iterate(p, &iterator));
}

void __create_object(ubjs_prmtv **p) {
    ubjs_prmtv_object(p);
}

void __test_object(ubjs_prmtv *p) {
    ubjs_bool ret;
    ubjs_object_iterator *iterator;
    unsigned int vl;
    ubjs_prmtv *other=0;

    CU_ASSERT_EQUAL(UR_OK, ubjs_prmtv_is_object(p, &ret));
    CU_ASSERT_EQUAL(UFALSE, ret);
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get_length(other, &vl));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0,0,&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_get(other, 0,"",&other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0,0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0,0,other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0,"",0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_set(other, 0,"",other));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(other, 0,0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_delete(other, 0,""));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(other, 0));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_prmtv_object_iterate(other, &iterator));
}

void test_prmtv_calls_for_wrong_primitives() {
    unsigned int it, it2;
    ubjs_prmtv *p=0;

    for(it=0; it<__primitives_len; it++) {
        (__primitives[it].create)(&p);

        for(it2=0; it2<__primitives_len; it2++) {
            if(it==it2) {
                continue;
            }
            (__primitives[it2].test)(p);
        }

        ubjs_prmtv_free(&p);
    }

}

