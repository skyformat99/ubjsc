#include <string.h>

#include "test.h"

int arrcmp(uint8_t *left,uint8_t *right,unsigned int len) {
    int i;
    for(i=0; i<len; i++) {
        if(left[i] != right[i]) {
            return 0;
        }
    }
    return 1;
}

void test_common_endian() {
    uint8_t abig[]= {1,2,3,4,5};
    uint8_t alittle[]= {5,4,3,2,1};
    uint8_t aout[5];
    ubjs_endian_host_type ret;
    ubjs_bool ret2;


    CU_ASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(-1));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(4));
    CU_ASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_get(0));

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_LITTLE));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    CU_ASSERT(UEFT_LITTLE == ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    CU_ASSERT_EQUAL(UFALSE, ret2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    CU_ASSERT(1 == arrcmp(alittle, aout, 5));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    CU_ASSERT(1 == arrcmp(abig, aout, 5));

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    CU_ASSERT(1 == arrcmp(alittle, aout, 5));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    CU_ASSERT(1 == arrcmp(abig, aout, 5));

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_BIG));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    CU_ASSERT(UEFT_BIG == ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    CU_ASSERT_EQUAL(UTRUE, ret2);

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    CU_ASSERT(1 == arrcmp(abig, aout, 5));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    CU_ASSERT(1 == arrcmp(alittle, aout, 5));

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    CU_ASSERT(1 == arrcmp(abig, aout, 5));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    CU_ASSERT(1 == arrcmp(alittle, aout, 5));

    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_DEFAULT));
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    CU_ASSERT(UEFT_DEFAULT == ret);
    CU_ASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));

    printf("endianness is %s\n", ret2==UTRUE ? "big" : "little");

    if(UFALSE == ret2) {
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        CU_ASSERT(1 == arrcmp(alittle, aout, 5));
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        CU_ASSERT(1 == arrcmp(abig, aout, 5));

        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        CU_ASSERT(1 == arrcmp(alittle, aout, 5));
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        CU_ASSERT(1 == arrcmp(abig, aout, 5));
    } else {
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        CU_ASSERT(1 == arrcmp(abig, aout, 5));
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        CU_ASSERT(1 == arrcmp(alittle, aout, 5));

        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        CU_ASSERT(1 == arrcmp(abig, aout, 5));
        CU_ASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        CU_ASSERT(1 == arrcmp(alittle, aout, 5));
    }
}

