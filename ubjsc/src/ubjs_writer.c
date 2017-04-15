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

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ubjs_writer_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

unsigned int ubjs_writer_prmtv_write_strategy_array_threshold=3;

unsigned int ubjs_writer_prmtv_write_strategies_top_len = 7;
ubjs_writer_prmtv_write_strategy ubjs_writer_prmtv_write_strategies_top[] =
{
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_ntype,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_float32,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_float64,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_str,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_hpn,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_array,
    (ubjs_writer_prmtv_write_strategy)ubjs_writer_prmtv_write_strategy_object
};

unsigned int ubjs_writer_prmtv_upgrade_strategies_len = 2;
ubjs_writer_prmtv_upgrade_strategy ubjs_writer_prmtv_upgrade_strategies[] =
{
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_array,
    (ubjs_writer_prmtv_upgrade_strategy)ubjs_writer_prmtv_upgrade_strategy_object
};

ubjs_result ubjs_writer_builder_new(ubjs_library *lib, ubjs_writer_builder **pthis)
{
    ubjs_writer_builder *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer_builder *)(lib->alloc_f)(sizeof(struct ubjs_writer_builder));
    this->lib=lib;
    this->userdata=0;
    this->free_f=0;
    this->would_write_f=0;
    this->would_print_f=0;
    this->free_primitives_early=UFALSE;
    this->debug_f=0;
    *pthis=this;

    return UR_OK;
}

ubjs_result ubjs_writer_builder_free(ubjs_writer_builder **pthis)
{
    ubjs_writer_builder *this;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->lib->free_f)(this);
    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_userdata(ubjs_writer_builder *this, void *userdata)
{
    if (0 == this || 0 == userdata)
    {
        return UR_ERROR;
    }

    this->userdata = userdata;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_would_write_f(ubjs_writer_builder *this,
    ubjs_writer_would_write_f would_write_f)
{
    if (0 == this || 0 == would_write_f)
    {
        return UR_ERROR;
    }

    this->would_write_f = would_write_f;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_would_print_f(ubjs_writer_builder *this,
    ubjs_writer_would_print_f would_print_f)
{
    if (0 == this || 0 == would_print_f)
    {
        return UR_ERROR;
    }

    this->would_print_f = would_print_f;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_free_primitives_early(ubjs_writer_builder *this,
    ubjs_bool free_primitives_early)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    this->free_primitives_early = free_primitives_early;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_debug_f(ubjs_writer_builder *this,
    ubjs_writer_debug_f debug_f)
{
    if (0 == this || 0 == debug_f)
    {
        return UR_ERROR;
    }

    this->debug_f = debug_f;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_set_free_f(ubjs_writer_builder *this,
    ubjs_writer_free_f free_f)
{
    if (0 == this || 0 == free_f)
    {
        return UR_ERROR;
    }

    this->free_f = free_f;
    return UR_OK;
}

ubjs_result ubjs_writer_builder_build(ubjs_writer_builder *builder, ubjs_writer **pthis)
{
    ubjs_writer *this;

    if (0 == builder || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_writer *)(builder->lib->alloc_f)(sizeof(struct ubjs_writer));
    this->lib=builder->lib;
    this->userdata=builder->userdata;
    this->would_write_f=builder->would_write_f;
    this->would_print_f=builder->would_print_f;
    this->debug_f=builder->debug_f;
    this->free_primitives_early=builder->free_primitives_early;
    this->free_f=builder->free_f;
    *pthis=this;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        (this->debug_f)(this->userdata, 13, "### ALIVE ###");
    }
#endif
    /* LCOV_EXCL_STOP */

    return UR_OK;
}

ubjs_result ubjs_writer_free(ubjs_writer **pthis)
{
    ubjs_writer *this;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        (this->debug_f)(this->userdata, 12, "### DEAD ###");
    }
#endif
    /* LCOV_EXCL_STOP */

    if (0 != this->free_f)
    {
        (this->free_f)(this->userdata);
    }
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_writer_get_userdata(ubjs_writer *this, void **puserdata)
{
    if (0 == this || 0 == puserdata)
    {
        return UR_ERROR;
    }

    *puserdata = this->userdata;;
    return UR_OK;
}

ubjs_result ubjs_writer_prmtv_find_best_write_strategy(ubjs_writer *this, ubjs_prmtv *object,
    unsigned int indent, ubjs_writer_prmtv_runner **runner)
{
    unsigned int i;
    ubjs_writer_prmtv_runner *arunner = 0;

    for (i=0; i<ubjs_writer_prmtv_write_strategies_top_len; i++)
    {
        ubjs_writer_prmtv_write_strategy it = ubjs_writer_prmtv_write_strategies_top[i];

        if (UR_OK == (it)(this, object, indent, &arunner))
        {
            *runner=arunner;
            return UR_OK;
        }
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        (this->debug_f)(this->userdata, 18, "No strategy found!");
    }
#endif
    /* LCOV_EXCL_STOP */

    /* todo */
    return UR_ERROR;
}

ubjs_result ubjs_writer_prmtv_try_upgrade(ubjs_writer *writer, ubjs_prmtv *original,
    ubjs_prmtv **pupgraded)
{
    unsigned int i;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 23, "Is it worth to upgrade?");
    }
#endif
    /* LCOV_EXCL_STOP */

    for (i=0; i<ubjs_writer_prmtv_upgrade_strategies_len; i++)
    {
        ubjs_writer_prmtv_upgrade_strategy it = ubjs_writer_prmtv_upgrade_strategies[i];

        if (UR_OK == (it)(writer, original, pupgraded))
        {
            return UR_OK;
        }
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != writer->debug_f)
    {
        (writer->debug_f)(writer->userdata, 17, "No upgrade needed");
    }
#endif
    /* LCOV_EXCL_STOP */
    return UR_ERROR;
}

ubjs_result ubjs_writer_write(ubjs_writer *this, ubjs_prmtv *object)
{
    ubjs_writer_prmtv_runner *runner=0;
    unsigned int len;
    uint8_t *data;

    if (0 == this || 0 == object || 0 == this->would_write_f)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_find_best_write_strategy(this, object, 0, &runner);

    len = runner->length_write + 1;
    data=(uint8_t *)(this->lib->alloc_f)(sizeof(uint8_t) * (len));

    *(data) = runner->marker;
    (runner->write)(runner, data + 1);
    if (UTRUE == this->free_primitives_early)
    {
        ubjs_prmtv_free(&(object));
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        char *msg = 0;
        unsigned int mlen = 0;
        unsigned int i;
        unsigned int pages = (len + 7) / 8;

        ubjs_compact_sprints(this->lib, &msg, &mlen, 12, "Would write ");
        ubjs_compact_sprintui(this->lib, &msg, &mlen, len);
        ubjs_compact_sprints(this->lib, &msg, &mlen, 8, " bytes:");
        (this->debug_f)(this->userdata, mlen, msg);
        (this->lib->free_f)(msg);
        msg = 0;
        mlen=0;

        for (i = 0; i < len; i++)
        {
            unsigned int data_i_len = (data[i] > 99 ? 3 : (data[i] > 9 ? 2 : 1));
            if (0 == (i % 8))
            {
                unsigned int pages_len = 0;
                unsigned int page_len = 0;
                char tmp[10];

                pages_len = sprintf(tmp, "%u", pages);
                page_len = sprintf(tmp, "%u", i / 8 + 1);

                ubjs_compact_sprints(this->lib, &msg, &mlen, pages_len - page_len,
                    "                         ");
                ubjs_compact_sprintui(this->lib, &msg, &mlen, i / 8 + 1);
                ubjs_compact_sprints(this->lib, &msg, &mlen, 1, "/");
                ubjs_compact_sprintui(this->lib, &msg, &mlen, pages);
                ubjs_compact_sprints(this->lib, &msg, &mlen, 3, " | ");
            }

            ubjs_compact_sprints(this->lib, &msg, &mlen, 1, "[");
            ubjs_compact_sprintui(this->lib, &msg, &mlen, data[i]);
            ubjs_compact_sprints(this->lib, &msg, &mlen, 1 + 4 - data_i_len, "]   ");

            if (7 == (i % 8))
            {
                (this->debug_f)(this->userdata, mlen, msg);
                (this->lib->free_f)(msg);
                msg = 0;
                mlen = 0;
            }
        }

        if (0 != msg)
        {
            (this->debug_f)(this->userdata, mlen, msg);
            (this->lib->free_f)(msg);
        }
    }
#endif
    /* LCOV_EXCL_STOP */

    (this->would_write_f)(this->userdata, data, len);
    (this->lib->free_f)(data);
    (runner->free)(runner);

    return UR_OK;
}

ubjs_result ubjs_writer_print(ubjs_writer *this, ubjs_prmtv *object)
{
    ubjs_writer_prmtv_runner *runner=0;
    unsigned int len;
    char *data;

    if (0 == this || 0 == object || 0 == this->would_print_f)
    {
        return UR_ERROR;
    }

    ubjs_writer_prmtv_find_best_write_strategy(this, object, 0, &runner);

    len = runner->length_print + 3;
    data=(char *)(this->lib->alloc_f)(sizeof(char) * (len));

    *(data + 0) = '[';
    *(data + 1) = runner->marker;
    *(data + 2) = ']';
    (runner->print)(runner, data + 3);
    (this->would_print_f)(this->userdata, data, len);
    if (UTRUE == this->free_primitives_early)
    {
        ubjs_prmtv_free(&(object));
    }


    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        char *msg = 0;
        unsigned int mlen = 0;

        ubjs_compact_sprints(this->lib, &msg, &mlen, 12, "Would print ");
        ubjs_compact_sprintui(this->lib, &msg, &mlen, len);
        ubjs_compact_sprints(this->lib, &msg, &mlen, 8, " bytes:");
        (this->debug_f)(this->userdata, mlen, msg);
        (this->lib->free_f)(msg);
        msg = 0;
        mlen = 0;

        ubjs_compact_sprints(this->lib, &msg, &mlen, len, data);
        (this->debug_f)(this->userdata, mlen, msg);
        (this->lib->free_f)(msg);
    }
#endif
    /* LCOV_EXCL_STOP */


    (this->lib->free_f)(data);
    (runner->free)(runner);

    return UR_OK;
}

void ubjs_writer_prmtv_runner_write_no_length(ubjs_writer_prmtv_runner *this,
    uint8_t *data)
{
}

void ubjs_writer_prmtv_runner_print_no_length(ubjs_writer_prmtv_runner *this,
    char *data)
{
}

void ubjs_writer_prmtv_runner_free_no_length(ubjs_writer_prmtv_runner *this)
{
    (this->writer->lib->free_f)(this);
}
