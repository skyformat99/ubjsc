#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#include "../include/ubjs.h"

void ubjs2js_main_writer_context_would_print(ubjs_writer_context *context, char *data, unsigned int len)
{
    char *tmp;

    tmp=(char *)malloc(sizeof(char)*(len+1));
    strncpy(tmp, data, len);
    tmp[len] = 0;

    printf("%s\n", tmp);
    free(tmp);
}

void ubjs2js_main_writer_context_free(ubjs_writer_context *context)
{
}

void __encode(ubjs_prmtv *object, json_t **pjsoned);
void __encode(ubjs_prmtv *object, json_t **pjsoned)
{
    json_t *jsoned = 0;
    ubjs_prmtv_type type;
    int64_t v;
    float32_t f32;
    float64_t f64;
    ubjs_array_iterator *ait;
    ubjs_object_iterator *oit;
    ubjs_prmtv *item;
    json_t *item_jsoned;
    unsigned int str_length;
    char *str;
    
    ubjs_prmtv_get_type(object, &type);
    switch (type)
    {
        case UOT_NULL:
            jsoned = json_null();
            break;

        case UOT_NOOP:
            break;

        case UOT_TRUE:
            jsoned = json_true();
            break;

        case UOT_FALSE:
            jsoned = json_false();
            break;

        case UOT_UINT8:
        case UOT_INT8:
        case UOT_INT16:
        case UOT_INT32:
        case UOT_INT64:
            ubjs_prmtv_int_get(object, &v);
            jsoned = json_integer(v);
            break;
        
        case UOT_FLOAT32:
            ubjs_prmtv_float32_get(object, &f32);
            jsoned = json_real(f32);
            break;

        case UOT_FLOAT64:
            ubjs_prmtv_float64_get(object, &f64);
            jsoned = json_real(f64);
            break;

        case UOT_STR:
            ubjs_prmtv_str_get_length(object, &str_length);
            str = (char *) malloc(sizeof(char) * str_length);
            ubjs_prmtv_str_copy_text(object, str);

            jsoned = json_stringn(str, str_length);
            free(str);
            break;

        case UOT_ARRAY:
            jsoned = json_array();
            ubjs_prmtv_array_iterate(object, &ait);

            while (UR_OK == ubjs_array_iterator_next(ait))
            {
                ubjs_array_iterator_get(ait, &item);
                __encode(item, &item_jsoned);
                if (0 != item_jsoned)
                {
                    json_array_append(jsoned, item_jsoned);
                    json_decref(item_jsoned);
                }
            }

            ubjs_array_iterator_free(&ait);
            break;

        case UOT_OBJECT:
            jsoned = json_object();
            ubjs_prmtv_object_iterate(object, &oit);

            while (UR_OK == ubjs_object_iterator_next(oit))
            {
                unsigned int key_length;
                char *key;

                ubjs_object_iterator_get_key_length(oit, &key_length);
                key = (char *)malloc(sizeof(char) * (key_length + 1));
                ubjs_object_iterator_copy_key(oit, key);
                key[key_length] = 0;

                ubjs_object_iterator_get_value(oit, &item);
                __encode(item, &item_jsoned);
                if (0 != item_jsoned)
                {
                    json_object_set(jsoned, key, item_jsoned);
                    json_decref(item_jsoned);
                }
                free(key);
            }

            ubjs_object_iterator_free(&oit);
            break;

        default:
            printf("WTF\n");
            break;
    }
    
    *pjsoned = jsoned;
}

void ubjs2js_main_parser_context_parsed(ubjs_parser_context *context, ubjs_prmtv *object)
{
    json_t *jsoned;
    char *tmp;

    __encode(object, &jsoned);
    tmp = json_dumps(jsoned, JSON_ENCODE_ANY);
    printf("%s\n", tmp);
    free(tmp);
    json_decref(jsoned);
}

void ubjs2js_main_parser_context_error(ubjs_parser_context *context, ubjs_parser_error *error)
{
    unsigned int length;
    char *message;

    ubjs_parser_error_get_message_length(error, &length);
    message = (char *)malloc(sizeof(char) * (length+1));
    ubjs_parser_error_get_message_text(error, message);
    message[length] = 0;

    fprintf(stderr, "Parser error: %s\n", message);

    free(message);
}

void ubjs2js_main_parser_context_free(ubjs_parser_context *context)
{
}

int main(int argc, char **argv)
{
    ubjs_parser *parser=0;
    ubjs_parser_context parser_context;
    uint8_t bytes[4096];
    ubjs_prmtv *obj;
    size_t did_read;

    parser_context.userdata = 0;
    parser_context.parsed = ubjs2js_main_parser_context_parsed;
    parser_context.error = ubjs2js_main_parser_context_error;
    parser_context.free = ubjs2js_main_parser_context_free;
    ubjs_parser_new(&parser, &parser_context);

    while (0 == feof(stdin))
    {
        did_read = fread(bytes, sizeof(uint8_t), 4096, stdin);
        if (UR_OK != ubjs_parser_parse(parser, bytes, did_read))
        {
            break;
        }
    }

    ubjs_parser_free(&parser);
    return 0;
}
