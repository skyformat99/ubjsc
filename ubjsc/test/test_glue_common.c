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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "test_glue_common.h"

void random_str(unsigned int length, char *str)
{
    unsigned int i;

    for (i=0; i<length; i++)
    {
        unsigned int pick;
        pick = rand() % 26;
        str[i] = (char) ('a' + pick);
    }
}

void pstrcat(char **pthis, char *format, ...)
{
    char *now = 0;
    int ret;
    unsigned int length;
    va_list args;
    char *othis = 0;
    unsigned int olen = 0;

    if (0 != *pthis)
    {
        othis = *pthis;
        olen = strlen(othis);
    }

    va_start(args, format);
    ret=vsnprintf(now, 0, format, args);
    va_end(args);

    length=olen + ret;
    now=(char *)malloc(sizeof(char) * (length + 1));

    if (0 != othis)
    {
        memcpy(now, othis, olen * sizeof(char));
        free(othis);
    }

    va_start(args, format);
    vsnprintf(now + olen, ret + 1, format, args);
    va_end(args);

    now[length] = 0;
    *pthis=now;
}
