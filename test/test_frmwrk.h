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

#ifndef HAVE_TEST_FRAMEWORK
#define HAVE_TEST_FRAMEWORK

typedef struct tcontext tcontext;
typedef struct tsuite tsuite;

typedef void (*tbefore_f)();
typedef void (*ttest_f)();
typedef void (*tafter_f)();

#define TASSERT_EQUAL(left, right) tassert_equal(__FILE__, __LINE__, #left, \
    #right, (left)==(right))
#define TASSERT_STRING_EQUAL(left, right) tassert_string_equal(__FILE__, \
    __LINE__, #left, #right, (left), (right))
#define TASSERT_NSTRING_EQUAL(left, right, len) tassert_nstring_equal(__FILE__, \
    __LINE__, #left, #right, #len, (left), (right), (len))
#define TASSERT_NOT_EQUAL(left, right) tassert_not_equal(__FILE__, __LINE__, \
    #left, #right, (left)!=(right))
#define TTEST(suite, test) tsuite_add_test((suite), #test, (test))
#define TSUITE(name, before, after, psuite) tsuite_new(name, before, after, \
    __FILE__, psuite)

void tassert_equal(char *, unsigned int, char *, char *, int);
void tassert_nstring_equal(char *, unsigned int, char *, char *, char *, char *, char *, int);
void tassert_string_equal(char *, unsigned int, char *, char *, char *, char *);
void tassert_not_equal(char *, unsigned int, char *, char *, int);

struct tcontext;
struct tsuite;

void tcontext_new(tcontext **);
void tcontext_free(tcontext **);
void tcontext_add_suite(tcontext *, tsuite *);
int tcontext_run(tcontext *);

void tsuite_new(char *, tbefore_f, tafter_f, char *, tsuite **);
void tsuite_free(tsuite **);
void tsuite_add_test(tsuite *, char *, ttest_f);

#endif
