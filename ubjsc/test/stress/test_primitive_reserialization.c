/*
 * Copyright (c) 2017 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <test_common.h>

struct serialized_primitive
{
    unsigned int len;
    uint8_t *ser;
};

struct deserialized_primitive
{
    ubjs_prmtv *obj;
};

static ubjs_library *lib;
static ubjs_parser *parser;
static ubjs_writer *writer;
static struct deserialized_primitive deserialized;
static struct serialized_primitive serialized;

static void generate_primitive(unsigned int, ubjs_prmtv **);
static void generate_large_array(unsigned int, ubjs_prmtv **);
static void generate_large_object(unsigned int, ubjs_prmtv **);

static void would_write(void *userdata, uint8_t *, unsigned int);
static void parsed(void *userdata, ubjs_prmtv *object);
/*
static void parser_debug(void *userdata, unsigned int, char *);
static void writer_debug(void *userdata, unsigned int, char *);
*/
static void serialize_primitive(ubjs_prmtv *, unsigned int *, uint8_t **);

static void deserialize_primitive(unsigned int, uint8_t *, ubjs_prmtv **);
static void verify_same_primitives(ubjs_prmtv *, ubjs_prmtv *);

TestSuite(primitive_reserialization);

Test(primitive_reserialization, normal)
{
    unsigned int i;
    int iterations = 1000;

    srand(time(0));

    {
        ubjs_library_builder builder;
        ubjs_library_builder_init(&builder);
        ubjs_library_builder_build(&builder, (ubjs_library **)&lib);
    }
    {
        ubjs_parser_builder *builder;
        ubjs_parser_builder_new(lib, &builder);
        ubjs_parser_builder_set_userdata(builder, &deserialized);
        ubjs_parser_builder_set_parsed_f(builder, parsed);
        ubjs_parser_builder_build(builder, &parser);
        ubjs_parser_builder_free(&builder);
    }
    {
        ubjs_writer_builder *builder=0;
        ubjs_writer_builder_new(lib, &builder);
        ubjs_writer_builder_set_userdata(builder, &serialized);
        ubjs_writer_builder_set_would_write_f(builder, would_write);
        ubjs_writer_builder_build(builder, &writer);
        ubjs_writer_builder_free(&builder);
    }

    for (i = 0; i < iterations; i++)
    {
        ubjs_prmtv *first = 0;
        unsigned int ser_len = 0;
        uint8_t *ser = 0;
        ubjs_prmtv *second = 0;

        cr_log_error("## Iteration %u/%u", i, iterations);

        serialized.len = 0;
        serialized.ser = 0;
        deserialized.obj = 0;

        generate_primitive(10, &first);
        serialize_primitive(first, &ser_len, &ser);
        deserialize_primitive(ser_len, ser, &second);
        ubjs_prmtv_free(&first);
        if (0 != ser)
        {
            free(ser);
            ser = 0;
        }
        first = second;
        second = 0;

        serialize_primitive(first, &ser_len, &ser);
        deserialize_primitive(ser_len, ser, &second);
        verify_same_primitives(first, second);
        ubjs_prmtv_free(&first);
        ubjs_prmtv_free(&second);
        if (0 != ser)
        {
            free(ser);
        }
    }

    ubjs_writer_free(&writer);
    ubjs_parser_free(&parser);
    ubjs_library_free(&lib);
}

Test(primitive_reserialization, large_array)
{
    unsigned int i;
    int iterations = 100;

    srand(time(0));

    {
        ubjs_library_builder builder;
        ubjs_library_builder_init(&builder);
        ubjs_library_builder_build(&builder, (ubjs_library **)&lib);
    }
    {
        ubjs_parser_builder *builder;
        ubjs_parser_builder_new(lib, &builder);
        ubjs_parser_builder_set_userdata(builder, &deserialized);
        ubjs_parser_builder_set_parsed_f(builder, parsed);
        ubjs_parser_builder_build(builder, &parser);
        ubjs_parser_builder_free(&builder);
    }
    {
        ubjs_writer_builder *builder=0;
        ubjs_writer_builder_new(lib, &builder);
        ubjs_writer_builder_set_userdata(builder, &serialized);
        ubjs_writer_builder_set_would_write_f(builder, would_write);
        ubjs_writer_builder_set_free_primitives_early(builder, UTRUE);
        ubjs_writer_builder_build(builder, &writer);
        ubjs_writer_builder_free(&builder);
    }

    for (i = 0; i < iterations; i++)
    {
        ubjs_prmtv *first = 0;
        unsigned int ser_len = 0;
        uint8_t *ser = 0;
        ubjs_prmtv *second = 0;

        cr_log_error("## Iteration %u/%u", i, iterations);

        serialized.len = 0;
        serialized.ser = 0;
        deserialized.obj = 0;

        generate_large_array(3, &first);
        serialize_primitive(first, &ser_len, &ser);
        deserialize_primitive(ser_len, ser, &second);
        cr_expect_neq(second, 0);
        ubjs_prmtv_free(&second);
        if (0 != ser)
        {
            free(ser);
        }
    }

    ubjs_writer_free(&writer);
    ubjs_parser_free(&parser);
    ubjs_library_free(&lib);
}

Test(primitive_reserialization, large_object)
{
    unsigned int i;
    int iterations = 100;

    srand(time(0));

    {
        ubjs_library_builder builder;
        ubjs_library_builder_init(&builder);
        ubjs_library_builder_build(&builder, (ubjs_library **)&lib);
    }
    {
        ubjs_parser_builder *builder;
        ubjs_parser_builder_new(lib, &builder);
        ubjs_parser_builder_set_userdata(builder, &deserialized);
        ubjs_parser_builder_set_parsed_f(builder, parsed);
        ubjs_parser_builder_build(builder, &parser);
        ubjs_parser_builder_free(&builder);
    }
    {
        ubjs_writer_builder *builder=0;
        ubjs_writer_builder_new(lib, &builder);
        ubjs_writer_builder_set_userdata(builder, &serialized);
        ubjs_writer_builder_set_would_write_f(builder, would_write);
        ubjs_writer_builder_set_free_primitives_early(builder, UTRUE);
        ubjs_writer_builder_build(builder, &writer);
        ubjs_writer_builder_free(&builder);
    }

    for (i = 0; i < iterations; i++)
    {
        ubjs_prmtv *first = 0;
        unsigned int ser_len = 0;
        uint8_t *ser = 0;
        ubjs_prmtv *second = 0;

        cr_log_error("## Iteration %u/%u", i, iterations);

        serialized.len = 0;
        serialized.ser = 0;
        deserialized.obj = 0;

        generate_large_object(2, &first);
        serialize_primitive(first, &ser_len, &ser);
        deserialize_primitive(ser_len, ser, &second);
        cr_expect_neq(second, 0);
        ubjs_prmtv_free(&second);
        if (0 != ser)
        {
            free(ser);
        }
    }

    ubjs_writer_free(&writer);
    ubjs_parser_free(&parser);
    ubjs_library_free(&lib);
}

static void generate_primitive(unsigned int level, ubjs_prmtv **pthis)
{
    unsigned int type;
    ubjs_prmtv *this = 0;
    unsigned int i;
    unsigned int len = 0;
    char *str = 0;

    type = rand() % (UOT_MAX + 13);

    switch (type)
    {
        case UOT_MAX:
            this = ubjs_prmtv_null();
            break;

        case UOT_MAX + 1:
            this = ubjs_prmtv_noop();
            break;

        case UOT_MAX + 2:
            this = ubjs_prmtv_true();
            break;

        case UOT_MAX + 3:
            this = ubjs_prmtv_false();
            break;

        case UOT_MAX + 4:
            ubjs_prmtv_uint8(lib, rand() % 0x100, &this);
            break;

        case UOT_MAX + 5:
            ubjs_prmtv_int8(lib, rand() % 0x100 - 0x80, &this);
            break;

        case UOT_MAX + 6:
            ubjs_prmtv_int16(lib, rand() % 0x10000 - 0x8000, &this);
            break;

        case UOT_MAX + 7:
            ubjs_prmtv_int32(lib, rand() % 0x100000000 - 0x80000000, &this);
            break;

        case UOT_MAX + 8:
            ubjs_prmtv_int64(lib, rand(), &this);
            break;

        case UOT_MAX + 9:
            ubjs_prmtv_float32(lib, rand() % 0x100000000 - 0x800000000, &this);
            break;

        case UOT_FLOAT64:
            ubjs_prmtv_float64(lib, rand(), &this);
            break;

        case UOT_MAX + 10:
            ubjs_prmtv_char(lib, (char)(rand() % ('Z' - 'A') + 'A'), &this);
            break;

        case UOT_MAX + 11:
            len = rand() % 0xFF;
            str = (char *)malloc(sizeof(char) * len);
            for (i = 0; i < len; i++)
            {
                str[i] = (char)(rand() % ('Z' - 'A') + 'A');
            }
            ubjs_prmtv_str(lib, len, str, &this);
            free(str);
            break;

        case UOT_MAX + 12:
            len = rand() % 0xFE + 1;
            str = (char *)malloc(sizeof(char) * len);
            for (i = 0; i < len; i++)
            {
                str[i] = (i == 0 ? rand() % 9 + '1' : rand() % 10 + '0');
            }
            ubjs_prmtv_hpn(lib, len, str, &this);
            free(str);
            break;

        case UOT_ARRAY:
            len = level == 0 ? 0 : 1 + rand() % 0x10;
            ubjs_prmtv_array_with_length(lib, len, &this);
            for (i = 0; i < len; i++)
            {
                ubjs_prmtv *child = 0;
                generate_primitive(level - 1, &child);
                ubjs_prmtv_array_add_last(this, child);
            }
            break;

        case UOT_OBJECT:
            len = level == 0 ? 0 : 1 + rand() % 0x10;
            ubjs_prmtv_object_with_length(lib, len, &this);

            for (i = 0; i < len; i++)
            {
                ubjs_prmtv *child = 0;
                unsigned int keylen = rand() % 0x10;
                char *key = (char *)malloc(sizeof(char) * keylen);
                unsigned int j;
                for (j = 0; j < keylen; j++)
                {
                    key[j] = (char)(rand() % ('Z' - 'A') + 'A');
                }
                generate_primitive(level - 1, &child);
                ubjs_prmtv_object_set(this, keylen, key, child);
            }
            break;

        default:
            break;
    }

    if (this == 0)
    {
        cr_expect_fail("%s", "Did not generate a primitive");
        return;
    }
    *pthis = this;
}

static void generate_large_array(unsigned int level, ubjs_prmtv **pthis)
{
    ubjs_prmtv *this = 0;
    unsigned int i;
    unsigned int len = 0;

    len = level == 0 ? 0 : 1 + rand() % 0xFF;
    ubjs_prmtv_array_with_length(lib, len, &this);
    for (i = 0; i < len; i++)
    {
        ubjs_prmtv *child = 0;
        generate_large_array(level - 1, &child);
        ubjs_prmtv_array_add_last(this, child);
    }
    *pthis = this;
}

static void generate_large_object(unsigned int level, ubjs_prmtv **pthis)
{
    ubjs_prmtv *this = 0;
    unsigned int i;
    unsigned int len = 0;

    len = level == 0 ? 0 : 1 + rand() % 0xFF;
    ubjs_prmtv_object_with_length(lib, len, &this);
    for (i = 0; i < len; i++)
    {
        ubjs_prmtv *child = 0;
        unsigned int keylen = rand() % 0x80 + 1;
        char *key = (char *)malloc(sizeof(char) * keylen);
        unsigned int j;
        for (j = 0; j < keylen; j++)
        {
            key[j] = (char)(rand() % ('Z' - 'A') + 'A');
        }
        generate_large_object(level - 1, &child);
        ubjs_prmtv_object_set(this, keylen, key, child);
    }
    *pthis = this;
}

void would_write(void *userdata, uint8_t *bytes, unsigned int len)
{
    struct serialized_primitive *puserdata = (struct serialized_primitive *)userdata;
    puserdata->len = len;
    puserdata->ser = (uint8_t *)malloc(sizeof(uint8_t) * len);
    memcpy(puserdata->ser, bytes, sizeof(uint8_t) * len);
}

static void serialize_primitive(ubjs_prmtv *this, unsigned int *plen, uint8_t **pser)
{
    if (this == 0)
    {
        cr_expect_fail("%s", "No primitive to serialize");
        return;
    }

    cr_expect_eq(UR_OK, ubjs_writer_write(writer, this));

    cr_expect_neq(serialized.ser, 0, "%s", "ubjs_writer_write failed");
    if (serialized.ser == 0)
    {
        return;
    }

    *plen = serialized.len;
    *pser = serialized.ser;
}

/*
static void parser_debug(void *userdata, unsigned int len, char *message)
{
    cr_log_info("parser: %s", message);
}

static void writer_debug(void *userdata, unsigned int len, char *message)
{
    cr_log_info("writer: %s", message);
}
*/

static void parsed(void *userdata, ubjs_prmtv *object)
{
    struct deserialized_primitive *puserdata = (struct deserialized_primitive *)userdata;
    puserdata->obj = object;
}

static void deserialize_primitive(unsigned int len, uint8_t *ser, ubjs_prmtv **pthis)
{
    if (ser == 0)
    {
        cr_expect_fail("%s", "No data to deserialize");
        return;
    }

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, ser, len));
    cr_expect_neq(deserialized.obj, 0, "%s", "ubjs_parser_parse failed");

    if (deserialized.obj == 0)
    {
        return;
    }
    *pthis = deserialized.obj;
}

static void verify_same_primitives(ubjs_prmtv *left, ubjs_prmtv *right)
{
    ubjs_prmtv_ntype *lntype, *rntype;
    ubjs_prmtv_type ltype, rtype;

    if (left == 0 || right == 0)
    {
        cr_expect_fail("%s", "One of primitives is null");
        return;
    }

    ubjs_prmtv_get_ntype(left, &lntype);
    ubjs_prmtv_get_ntype(right, &rntype);
    ubjs_prmtv_get_type(left, &ltype);
    ubjs_prmtv_get_type(right, &rtype);

    if (0 != lntype && lntype == rntype)
    {
        if (lntype == &ubjs_prmtv_null_ntype
            || lntype == &ubjs_prmtv_noop_ntype
            || lntype == &ubjs_prmtv_true_ntype
            || lntype == &ubjs_prmtv_false_ntype)
        {
            return;
        }
        else if (lntype == &ubjs_prmtv_uint8_ntype)
        {
            uint8_t lvalue, rvalue;
            ubjs_prmtv_uint8_get(left, &lvalue);
            ubjs_prmtv_uint8_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both uint8 but values %u vs %u", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_char_ntype)
        {
            char lvalue, rvalue;
            ubjs_prmtv_char_get(left, &lvalue);
            ubjs_prmtv_char_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both char but values %u vs %u", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_int8_ntype)
        {
            int8_t lvalue, rvalue;
            ubjs_prmtv_int8_get(left, &lvalue);
            ubjs_prmtv_int8_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both int8 but values %d vs %d", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_int16_ntype)
        {
            int16_t lvalue, rvalue;
            ubjs_prmtv_int16_get(left, &lvalue);
            ubjs_prmtv_int16_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both int16 but values %d vs %d", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_int32_ntype)
        {
            int32_t lvalue, rvalue;
            ubjs_prmtv_int32_get(left, &lvalue);
            ubjs_prmtv_int32_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both int32 but values %ld vs %ld", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_float32_ntype)
        {
            float32_t lvalue, rvalue;
            ubjs_prmtv_float32_get(left, &lvalue);
            ubjs_prmtv_float32_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both float32 but values %ld vs %ld", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_int64_ntype)
        {
            int64_t lvalue, rvalue;
            ubjs_prmtv_int64_get(left, &lvalue);
            ubjs_prmtv_int64_get(right, &rvalue);
            cr_expect_eq(lvalue, rvalue,
                 "Primitives different, both int64 but values %ld vs %ld", lvalue, rvalue);
        }
        else if (lntype == &ubjs_prmtv_str_ntype)
        {
            unsigned int lstrlen, rstrlen;
            ubjs_prmtv_str_get_length(left, &lstrlen);
            ubjs_prmtv_str_get_length(right, &rstrlen);
            cr_expect_eq(lstrlen, rstrlen,
                 "Primitives different, both str but lenghts %f vs %f", lstrlen, rstrlen);

            if (lstrlen == rstrlen)
            {
                char *lstr = (char *)malloc(sizeof(char) * (lstrlen + 1));
                char *rstr = (char *)malloc(sizeof(char) * (lstrlen + 1));
                ubjs_prmtv_str_copy_text(left, lstr);
                ubjs_prmtv_str_copy_text(right, rstr);
                lstr[lstrlen] = 0;
                rstr[rstrlen] = 0;
                cr_expect_str_eq(lstr, rstr,
                    "Primitivies different, both str but content <%.*s> vs <%.*s>",
                    lstrlen, lstr, rstrlen, rstr);
                free(lstr);
                free(rstr);
            }
        }
        else if (lntype == &ubjs_prmtv_hpn_ntype)
        {
            unsigned int lhpnlen, rhpnlen;
            ubjs_prmtv_hpn_get_length(left, &lhpnlen);
            ubjs_prmtv_hpn_get_length(right, &rhpnlen);
            cr_expect_eq(lhpnlen, rhpnlen,
                 "Primitives different, both hpn but lenghts %f vs %f", lhpnlen, rhpnlen);

            if (lhpnlen == rhpnlen)
            {
                char *lhpn = (char *)malloc(sizeof(char) * (lhpnlen + 1));
                char *rhpn = (char *)malloc(sizeof(char) * (lhpnlen + 1));
                ubjs_prmtv_hpn_copy_text(left, lhpn);
                ubjs_prmtv_hpn_copy_text(right, rhpn);
                lhpn[lhpnlen] = 0;
                rhpn[rhpnlen] = 0;
                cr_expect_str_eq(lhpn, rhpn,
                    "Primitivies different, both hpn but content <%.*s> vs <%.*s>",
                    lhpnlen, lhpn, rhpnlen, rhpn);
                free(lhpn);
                free(rhpn);
            }
        }
    }
    else if (ltype == rtype)
    {
        switch (ltype)
        {
            case UOT_FLOAT64:
                {
                    float64_t lvalue, rvalue;
                    ubjs_prmtv_float64_get(left, &lvalue);
                    ubjs_prmtv_float64_get(right, &rvalue);
                    cr_expect_eq(lvalue, rvalue,
                         "Primitives different, both float64 but values %f vs %f",
                         lvalue, rvalue);
                }
                return;

            case UOT_ARRAY:
                {
                    unsigned int larraylen, rarraylen;
                    ubjs_prmtv_array_get_length(left, &larraylen);
                    ubjs_prmtv_array_get_length(right, &rarraylen);
                    cr_expect_eq(larraylen, rarraylen,
                         "Primitives different, both array but lenghts %f vs %f",
                         larraylen, rarraylen);

                    if (larraylen == rarraylen)
                    {
                        ubjs_array_iterator *lit = 0;
                        ubjs_array_iterator *rit = 0;

                        ubjs_prmtv_array_iterate(left, &lit);
                        ubjs_prmtv_array_iterate(right, &rit);

                        while (UR_OK == ubjs_array_iterator_next(lit)
                            && UR_OK == ubjs_array_iterator_next(rit))
                        {
                            ubjs_prmtv *lvalue, *rvalue;

                            ubjs_array_iterator_get(lit, &lvalue);
                            ubjs_array_iterator_get(rit, &rvalue);
                            verify_same_primitives(lvalue, rvalue);
                        }

                        ubjs_array_iterator_free(&lit);
                        ubjs_array_iterator_free(&rit);
                    }
                }
                break;

            case UOT_OBJECT:
                {
                    unsigned int lstrlen, rstrlen;
                    ubjs_prmtv_object_get_length(left, &lstrlen);
                    ubjs_prmtv_object_get_length(right, &rstrlen);
                    cr_expect_eq(lstrlen, rstrlen,
                         "Primitives different, both object but lenghts %f vs %f",
                         lstrlen, rstrlen);

                    if (lstrlen == rstrlen)
                    {
                        ubjs_object_iterator *lit = 0;
                        ubjs_object_iterator *rit = 0;
                        unsigned int i = 0;

                        ubjs_prmtv_object_iterate(left, &lit);
                        ubjs_prmtv_object_iterate(right, &rit);

                        while (UR_OK == ubjs_object_iterator_next(lit)
                            && UR_OK == ubjs_object_iterator_next(rit))
                        {
                            unsigned int lkeylen = 0, rkeylen = 0;
                            ubjs_prmtv *lkeyvalue, *rkeyvalue;

                            ubjs_object_iterator_get_key_length(lit, &lkeylen);
                            ubjs_object_iterator_get_key_length(rit, &rkeylen);
                            cr_expect_eq(lkeylen, rkeylen,
                                 "Primitives different, both object, "
                                     "but %u-th key lenghts %u vs %u",
                                 i, lkeylen, rkeylen);

                            if (lkeylen == rkeylen)
                            {
                                char *lkey = (char *)malloc(sizeof(char) * (lkeylen + 1));
                                char *rkey = (char *)malloc(sizeof(char) * (lkeylen + 1));
                                ubjs_object_iterator_copy_key(lit, lkey);
                                ubjs_object_iterator_copy_key(rit, rkey);
                                lkey[lkeylen] = 0;
                                rkey[rkeylen] = 0;
                                cr_expect_str_eq(lkey, rkey,
                                    "Primitivies different, both object, but %u-th "
                                        "key <%.*s> vs <%.*s>",
                                    lkeylen, lkey, rkeylen, rkey);
                                free(lkey);
                                free(rkey);
                            }

                            ubjs_object_iterator_get_value(lit, &lkeyvalue);
                            ubjs_object_iterator_get_value(rit, &rkeyvalue);
                            verify_same_primitives(lkeyvalue, rkeyvalue);

                            i++;
                        }
                        ubjs_object_iterator_free(&lit);
                        ubjs_object_iterator_free(&rit);
                    }
                }
                break;

            default:
                break;
        }
    }
    else
    {
        cr_expect_fail("Primitives different");
    }
}
