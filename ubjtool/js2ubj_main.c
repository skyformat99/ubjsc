#include <stdio.h>
#include <string.h>

#include <jansson.h>

#include "../include/ubjs.h"

void __encode(json_t *,ubjs_prmtv **);
void __encode(json_t *jsoned,ubjs_prmtv **pobj)
{
    size_t index;
    const char *key;
    json_t *jsoned_item;
    ubjs_prmtv *item;

    switch (json_typeof(jsoned))
    {
        case JSON_NULL:
            *pobj = ubjs_prmtv_null();
            break;

        case JSON_TRUE:
            *pobj = ubjs_prmtv_true();
            break;

        case JSON_FALSE:
            *pobj = ubjs_prmtv_false();
            break;

        case JSON_INTEGER:
            ubjs_prmtv_int(json_integer_value(jsoned), pobj);;
            break;

        case JSON_REAL:
            ubjs_prmtv_float64(json_real_value(jsoned), pobj);
            break;

        case JSON_STRING:
            ubjs_prmtv_str(json_string_length(jsoned), json_string_value(jsoned), pobj);
            break;

        case JSON_ARRAY:
            ubjs_prmtv_array(pobj);
            json_array_foreach(jsoned, index, jsoned_item)
            {
                __encode(jsoned_item, &item);
                ubjs_prmtv_array_add_last(*pobj, item);
            }
            break;

        case JSON_OBJECT:
            ubjs_prmtv_object(pobj);
            json_object_foreach(jsoned, key, jsoned_item)
            {
                __encode(jsoned_item, &item);
                ubjs_prmtv_object_set(*pobj, strlen(key), key, item);
            }
            break;

        default:
            break;
    }
}

void js2ubj_main_writer_context_would_write(ubjs_writer_context *context, uint8_t *data, unsigned int len)
{
    fwrite((void *)data, sizeof(uint8_t), len, stdout);
}

void js2ubj_main_writer_context_free(ubjs_writer_context *context)
{    
}

int main(int argc, char **argv)
{
    json_error_t error;
    json_t *value = 0;
    ubjs_prmtv *obj = 0;
    ubjs_writer *writer=0;
    ubjs_writer_context writer_context;
    
    value = json_loadf(stdin, JSON_DECODE_ANY, &error);
    if(0 == value)
    {
        printf("JSON error: %s\n", error.text);
        printf("    line: %u\n", error.line);
        printf("    column: %u\n", error.column);
        printf("    pos: %u\n", error.position);
    }
    else
    {
        __encode(value, &obj);

        writer_context.userdata = 0;
        writer_context.would_write = js2ubj_main_writer_context_would_write;
        writer_context.would_print = 0;
        writer_context.free = js2ubj_main_writer_context_free;

        ubjs_writer_new(&writer, &writer_context);
        
        ubjs_writer_write(writer, obj);
        
        ubjs_writer_free(&writer);
        ubjs_prmtv_free(&obj);
        
        json_decref(value);
    }
    return 0;
}
