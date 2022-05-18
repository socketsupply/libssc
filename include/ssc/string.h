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

#ifndef SSC_STRING_H
#define SSC_STRING_H

#include "platform.h"

/**
 * `fprintf` library function.
 */
#define ssc_string_fprintf(stream, value, ...)                                 \
  SSC_FPRINTF(stream, ssc_string(value), ##__VA_ARGS__)

/**
 * `sprintf` library function.
 */
#define ssc_string_sprintf(string, format, ...)                                \
  SSC_SPRINTF(string, ssc_string(format), ##__VA_ARGS__)

/**
 * `snprintf` library function.
 */
#define ssc_string_snprintf(string, size, format, ...)                         \
  SSC_SNPRINTF(string, size, ssc_string(format), ##__VA_ARGS__)

/**
 * `vsprintf` library function.
 */
#define ssc_string_vsprintf(string, ...) SSC_VSPRINTF(string, __VA_ARGS__)

/**
 * `vsnprintf` library function.
 */
#define ssc_string_vsnprintf(string, ...) SSC_VSNPRINTF(string, __VA_ARGS__)

/**
 * `printf` library function.
 */
#define ssc_string_printf(value, ...)                                          \
  SSC_PRINTF(ssc_string(value), ##__VA_ARGS__)

/**
 * `print` library function.
 */
#define ssc_string_print(value) ssc_string_printf("%s\n", ssc_string(value))

/**
 * Format a string like `sprintf`.
 */
#define ssc_string_format(string, ...) ssc_string_sprintf(string, __VA_ARGS__)

/**
 * Format a string with a variadic argument list like `vsprintf`.
 */
#define ssc_string_vformat(string, ...) ssc_string_vsprintf(string, __VA_ARGS__)

/**
 * Format a string like `snprintf`.
 */
#define ssc_string_nformat(string, size, ...)                                  \
  ssc_string_snprintf(string, size, __VA_ARGS__)

/**
 * Format a string with a variadic argument list like `vsnprintf`.
 */
#define ssc_string_vnformat(string, ...)                                       \
  ssc_string_vsnprintf(string, __VA_ARGS__)

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
SSC_EXPORT SSCUSize
ssc_string_size (const SSCString string);

/**
 * Compares `left` and `right` string
 * @param left
 * @param right
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
SSC_EXPORT int
ssc_string_compare (const SSCString left, const SSCString right);

/**
 * Compares `left` and `right` string equality
 * @param left
 * @param right
 * @return Returns `SSC_TRUE` if strings are equal, otherwise `SSC_FALSE`
 */
SSC_EXPORT SSCBoolean
ssc_string_equals (const SSCString left, const SSCString right);

/**
 * Compares `left` string of `left_size` length and `right` string of
 * `right_size` length.
 * @param left
 * @param left_size
 * @param right
 * @param right_size
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
SSC_EXPORT int
ssc_string_compare_with_size (
  const SSCString left,
  const SSCUSize left_size,
  const SSCString right,
  const SSCUSize right_size
);

/**
 * Slice a `string` returning a pointer at `offset`.
 * @notice `string` is checked for `NULL`, but not for nullterm.
 * @param string
 * @param offset
 * @return A pointer at `string + offset`
 */
SSC_EXPORT const SSCString
ssc_string_slice (const SSCString string, const SSCUSize offset);

#endif
