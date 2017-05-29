/*
 * Copyright (c) 2016 Tomasz Sieprawski
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

#include "test_common.h"
#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

Test(writer, free_primitives_early_object)
{
    ubjs_prmtv *value = 0;

    twill_returnuic("dict_get_length", UR_OK, "write");
    twill_returnuic("dict_get_length", 0, "write");
    twill_returnuic("dict_iterator_next", UR_ERROR, "metrics");
    twill_returnuic("dict_iterator_next", UR_ERROR, "write");
    twill_returnuic("dict_iterator_next", UR_ERROR, "free early");

    ubjs_prmtv_object(instance_lib, &value);
    sw_verify_free_primitives_early(instance_lib, value);
}

Test(writer, free_primitives_early_object_frees_item)
{
    ubjs_prmtv *value = 0;
    ubjs_prmtv *item = 0;
    ubjs_prmtv_str(instance_lib, 5, "rower", &item);

    twill_returnuic("dict_get_length", UR_OK, "write");
    twill_returnuic("dict_get_length", 1, "write");

    twill_returnuic("dict_iterator_next", UR_OK, "metrics 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "metrics 1");
    twill_returnoc("dict_iterator_get_value", item, "metrics 1");
    twill_returnuic("dict_iterator_next", UR_ERROR, "metrics");

    twill_returnuic("dict_iterator_next", UR_OK, "write 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "write 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "write 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "write 1");
    twill_returnuic("dict_iterator_copy_key", 1, "write 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "write 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "write 1");
    twill_returnoc("dict_iterator_get_value", item, "write 1");
    twill_returnuic("dict_iterator_next", UR_ERROR, "write");

    twill_returnuic("dict_iterator_next", UR_OK, "free early 1");
    twill_returnuic("dict_iterator_delete", UR_OK, "free early 1");
    twill_returnuic("dict_iterator_next", UR_ERROR, "free early");

    ubjs_prmtv_object(instance_lib, &value);
    sw_verify_free_primitives_early(instance_lib, value);
    ubjs_prmtv_free(&item);
}
