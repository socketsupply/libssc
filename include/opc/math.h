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

#ifndef OPC_MATH_H
#define OPC_MATH_H

#include "platform.h"

/**
 * Computes a value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return A value between `min` and `max`
 */
// clang-format off
#define opc_math_clamp_value(value, min, max) ({                               \
  ((min) < (max))                                                              \
    ? (value) < (min)                                                          \
      ? (min)                                                                  \
      : (value) > (max)                                                        \
        ? (max)                                                                \
        : (value)                                                              \
    : (value) < (max)                                                          \
      ? (max)                                                                  \
      : (value) > (min)                                                        \
        ? (min)                                                                \
        : (value);                                                             \
})

/**
 * Computes absolute value of `value`
 * @param value
 * @return The absolute value of `value`
 */
#define opc_math_abs(value) (value) < 0 ? -(value) : (value)
// clang-format on

/**
 * Computes an unsigned value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return An unsigned value between `min` and `max`
 */
OPC_EXPORT unsigned long long
opc_math_uclamp (
  unsigned long long value,
  unsigned long long min,
  unsigned long long max
);

/**
 * Computes a signed value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return An signed value between `min` and `max`
 */
OPC_EXPORT long long
opc_math_clamp (long long value, long long min, long long max);

/**
 * Detects if an unsigned value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
OPC_EXPORT OPCBoolean
opc_math_in_urange (
  unsigned long long value,
  unsigned long long lo,
  unsigned long long hi
);

/**
 * Detects if a signed value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
OPC_EXPORT OPCBoolean
opc_math_in_range (int value, int lo, int hi);

#endif
