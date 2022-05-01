/**
 * `libopc` - Operator Framework Client Library
 *
 * This file is part of libopc.
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

#ifndef OPC_STRING_H
#define OPC_STRING_H

#include "platform.h"

/**
 * `fprintf` library function.
 */
#define opc_string_fprintf(stream, value, ...)                                 \
  OPC_FPRINTF(stream, opc_string(value), ##__VA_ARGS__)

/**
 * `sprintf` library function.
 */
#define opc_string_sprintf(string, format, ...)                                \
  OPC_SPRINTF(string, opc_string(format), ##__VA_ARGS__)

/**
 * `snprintf` library function.
 */
#define opc_string_snprintf(string, size, format, ...)                         \
  OPC_SNPRINTF(string, size, opc_string(format), ##__VA_ARGS__)

/**
 * `vsprintf` library function.
 */
#define opc_string_vsprintf(string, ...) OPC_VSPRINTF(string, __VA_ARGS__)

/**
 * `vsnprintf` library function.
 */
#define opc_string_vsnprintf(string, ...) OPC_VSNPRINTF(string, __VA_ARGS__)

/**
 * `printf` library function.
 */
#define opc_string_printf(value, ...)                                          \
  OPC_PRINTF(opc_string(value), ##__VA_ARGS__)

/**
 * `print` library function.
 */
#define opc_string_print(value) opc_string_printf("%s\n", opc_string(value))

/**
 * Format a string like `sprintf`.
 */
#define opc_string_format(string, ...) opc_string_sprintf(string, __VA_ARGS__)

/**
 * Format a string with a variadic argument list like `vsprintf`.
 */
#define opc_string_vformat(string, ...) opc_string_vsprintf(string, __VA_ARGS__)

/**
 * Format a string like `snprintf`.
 */
#define opc_string_nformat(string, size, ...)                                  \
  opc_string_snprintf(string, size, __VA_ARGS__)

/**
 * Format a string with a variadic argument list like `vsnprintf`.
 */
#define opc_string_vnformat(string, ...)                                       \
  opc_string_vsnprintf(string, __VA_ARGS__)

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
OPC_EXPORT OPCUSize
opc_string_size (const OPCString string);

/**
 * Compares `left` and `right` string
 * @param left
 * @param right
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare (const OPCString left, const OPCString right);

/**
 * Compares `left` and `right` string equality
 * @param left
 * @param right
 * @return Returns `OPC_TRUE` if strings are equal, otherwise `OPC_FALSE`
 */
OPC_EXPORT OPCBoolean
opc_string_equals (const OPCString left, const OPCString right);

/**
 * Compares `left` string of `left_size` length and `right` string of
 * `right_size` length.
 * @param left
 * @param left_size
 * @param right
 * @param right_size
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare_with_size (
  const OPCString left,
  const OPCUSize left_size,
  const OPCString right,
  const OPCUSize right_size
);

/**
 * Slice a `string` returning a pointer at `offset`.
 * @notice `string` is checked for `NULL`, but not for nullterm.
 * @param string
 * @param offset
 * @return A pointer at `string + offset`
 */
OPC_EXPORT const OPCString
opc_string_slice (const OPCString string, const OPCUSize offset);

#endif
