#include <string.h>

#include "test_common.h"

void suite_common(tcontext *context) {
    tsuite *suite;
    tsuite_new("common", 0, 0, &suite);
    tcontext_add_suite(context,suite);
    TTEST(suite, test_common_endian);
}

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

    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(-1));
    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_set(4));
    TASSERT_EQUAL(UR_ERROR, ubjs_endian_host_type_get(0));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_LITTLE));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_LITTLE, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    TASSERT_EQUAL(UFALSE, ret2);

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_BIG));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_BIG, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));
    TASSERT_EQUAL(UTRUE, ret2);

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
    TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
    TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_set(UEFT_DEFAULT));
    TASSERT_EQUAL(UR_OK, ubjs_endian_host_type_get(&ret));
    TASSERT_EQUAL(UEFT_DEFAULT, ret);
    TASSERT_EQUAL(UR_OK, ubjs_endian_is_big(&ret2));

    if(UFALSE == ret2) {
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));

        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
    } else {
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_big_to_native(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));

        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(abig, aout, 5));
        TASSERT_EQUAL(1, arrcmp(abig, aout, 5));
        TASSERT_EQUAL(UR_OK, ubjs_endian_convert_native_to_big(alittle, aout, 5));
        TASSERT_EQUAL(1, arrcmp(alittle, aout, 5));
    }
}

