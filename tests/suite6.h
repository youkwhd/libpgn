/* suite6.h - libpgn test suite
 *
 * youkwhd <lolywk@tutanota.com>
 * GPLv2 Licensed, See COPYING.
 *
 * Colorful test assertions
 */

#ifndef SUITE6_H
#define SUITE6_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ANSI color codes */
#define R "\033[31m"
#define G "\033[32m"
#define B "\033[34;4m"
#define C "\033[0m"

#define suite6_pass(expr)                                                         \
    do {                                                                          \
        printf("%s[PASS] %s%s:%d%s :: %s\n", G, B, __FILE__, __LINE__, C, #expr); \
    } while (0)                                                                   \

#define suite6_fail(expr)                                                         \
    do {                                                                          \
        printf("%s[FAIL] %s%s:%d%s :: %s\n", R, B, __FILE__, __LINE__, C, #expr); \
        abort();                                                                  \
    } while (0)                                                                   \

#define suite6_assert(expr)              \
    if ((bool)(expr)) suite6_pass(expr); \
    else suite6_fail(expr);              \

#endif // SUITE6_H
