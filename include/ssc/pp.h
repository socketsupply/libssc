/**
 * `libssc` - Socket SDK Client Library
 *
 * This file is part of libssc.
 *
 * MIT License
 *
 * Copyright (c) 2022 Socket Supply Co.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#ifndef SSC_PP_H
#define SSC_PP_H

/**
 * Converts static macro `value` to a string.
 * @param value Static value to convert to string
 * @return A `const char *` static pointer
 */
#define SSC_PP_STRING(value) SSC_PP_STRINGX(value)
#define SSC_PP_STRINGX(value) #value

/**
 * Computes number of variadic arguments count given to a preprocessor.
 * @param ...
 * @return The number of variadic arguments from 0 - 127.
 * @notice If the first argument is wrapped in `()` then it is
 *         not counted.This is a known bu
 * @example
 *   printf("%d\n", SSC_PP_VARG_COUNT()); // 0
 *   printf("%d\n", SSC_PP_VARG_COUNT(1)); // 1
 *   printf("%d\n", SSC_PP_VARG_COUNT(1, 2)); // 2
 *   printf("%d\n", SSC_PP_VARG_COUNT(1, 2, 3)); // 3
 *   printf("%d\n", SSC_PP_VARG_COUNT(1, 2, 3, 4)); // 4
 */
#define SSC_PP_VARG_COUNT(...)                                                 \
  SSC_PP_VARG_COUNT_INTERNAL_HELPER1(                                          \
    SSC_PP_VARG_HAS_COMMA(__VA_ARGS__),                                        \
    SSC_PP_VARG_HAS_COMMA(SSC_PP_VARG_COMMA __VA_ARGS__()),                    \
    SSC_PP_VARG_COUNT_INTERNAL(__VA_ARGS__, SSC_PP_VARG_128_SEQ_N())           \
  )

/**
 * Polyfills the macro used to determine the call site function name.
 */
#ifdef _WIN32
#define SSC_PP_CALLSITE_FUNCTION_NAME() __FUNCTION__
#else
#define SSC_PP_CALLSITE_FUNCTION_NAME() __func__
#endif

/**
 * Simple callsite variadic args with format suitable to pass to
 * `ssc_printf(...)`
 * @param format
 */
#define SSC_PP_CALLSITE_VARGS_WITH_FORMAT(format, ...)                         \
  SSC_PP_CALLSITE_ARGS_FORMAT() format, SSC_PP_CALLSITE_ARGS(), ##__VA_ARGS__

/**
 * Simple callsite variadic args suitable to pass to `ssc_printf(...)`
 */
#define SSC_PP_CALLSITE_VARGS()                                                \
  SSC_PP_CALLSITE_ARGS_FORMAT(), SSC_PP_CALLSITE_ARGS()

/**
 * Simple callsite static string
 */
#define SSC_PP_CALLSITE_FILE_LOCATION_STRING()                                 \
  "(" __FILE__ ":" SSC_PP_STRING(__LINE__) ")"

/**
 * Simple call site format string suitable for usage with `SSC_PP_CALLSITE_ARGS`
 */
#define SSC_PP_CALLSITE_ARGS_FORMAT() "%s (%s:%llu)"

/**
 * Simple call site arguments suitable for format strings
 */
#define SSC_PP_CALLSITE_ARGS()                                                 \
  ssc_string(__PRETTY_FUNCTION__), ssc_string(__FILE__), ssc_usize(__LINE__)

/**
 * Internal
 */
#define SSC_PP_VARG_COMMA(...) ,

/**
 * Internal preprocessor macro for counting up to 128 variadic arguments
 */
#define SSC_PP_VARG_COUNT_INTERNAL(...) SSC_PP_VARG_128_INTERNAL(__VA_ARGS__)

/**
 * Internal
 */
#define SSC_PP_VARG_COUNT_INTERNAL_HELPER1(a, b, N)                            \
  SSC_PP_VARG_COUNT_INTERNAL_HELPER2(a, b, N)

/**
 * Internal
 */
#define SSC_PP_VARG_COUNT_INTERNAL_HELPER2(a, b, N)                            \
  SSC_PP_VARG_COUNT_INTERNAL_HELPER3_##a##b(N)

/**
 * Internal
 */
#define SSC_PP_VARG_COUNT_INTERNAL_HELPER3_01(N) 0
#define SSC_PP_VARG_COUNT_INTERNAL_HELPER3_00(N) 1
#define SSC_PP_VARG_COUNT_INTERNAL_HELPER3_11(N) N

/**
 * Internal
 */
#define SSC_PP_VARG_HAS_COMMA(...)                                             \
  SSC_PP_VARG_COUNT_INTERNAL(__VA_ARGS__, SSC_PP_COMMA_128_SEQ_N())

// clang-format off

/**
 * Internal
 */
#define SSC_PP_VARG_128_SEQ_N()                                                \
  127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113,   \
  112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,   \
    97,  96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  \
    82,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  \
    67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  \
    52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  \
    37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  \
    22,  21,  20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,   9,   8,  \
    7,   6,   5,   4,  3,    2,   1,   0

/**
 * Internal
 */
#define SSC_PP_COMMA_128_SEQ_N()                                               \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 0, 0


/**
 * Internal
 */
#define SSC_PP_VARG_128_INTERNAL(                                              \
  _1,   _2,   _3,   _4,   _5,   _6,   _7,   _8,   _9,   _10,                   \
  _11,  _12,  _13,  _14,  _15,  _16,  _17,  _18,  _19,  _20,                   \
  _21,  _22,  _23,  _24,  _25,  _26,  _27,  _28,  _29,  _30,                   \
  _31,  _32,  _33,  _34,  _35,  _36,  _37,  _38,  _39,  _40,                   \
  _41,  _42,  _43,  _44,  _45,  _46,  _47,  _48,  _49,  _50,                   \
  _51,  _52,  _53,  _54,  _55,  _56,  _57,  _58,  _59,  _60,                   \
  _61,  _62,  _63,  _64,  _65,  _66,  _67,  _68,  _69,  _70,                   \
  _71,  _72,  _73,  _74,  _75,  _76,  _77,  _78,  _79,  _80,                   \
  _81,  _82,  _83,  _84,  _85,  _86,  _87,  _88,  _89,  _90,                   \
  _91,  _92,  _93,  _94,  _95,  _96,  _97,  _98,  _99,  _100,                  \
  _101, _102, _103, _104, _105, _106, _107, _108, _109, _110,                  \
  _111, _112, _113, _114, _115, _116, _117, _118, _119, _120,                  \
  _121, _122, _123, _124, _125, _126, _127, N, ...                             \
) N

// clang-format on

#endif
