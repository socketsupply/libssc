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

#ifndef SSC_RESULT_H
#define SSC_RESULT_H

#include "platform.h"
#include "string.h"

/**
 * Enumerated result types for various `libssc` function
 * return values.
 */
typedef enum {
  SSC_E_MAX = -SSC_MAX_ENUM,
  SSC_MALFORMED_URI = -100,
  SSC_MISSING_CONTEXT = -40,
  SSC_BAD_STATE = -30,
  SSC_INVALID_ARGUMENT = -20,
  SSC_OUT_OF_BOUNDS = -11,
  SSC_OUT_OF_MEMORY = -10,
  SSC_NULL_POINTER = -2,
  SSC_ERROR = -1,

  SSC_OK = 0,
  SSC_DETECTED = 10,
  SSC_NOT_DETECTED = 11,
  SSC_UNKNOWN = SSC_MAX_ENUM
} SSCResult;

/**
 * Alias for `ssc_is_error()`
 */
#define ssc_notok ssc_is_error

/**
 * Predicate helper to determine if `value` is an error result code
 * @param value
 * @return `SSC_TRUE` if `value` is an error result code
 */
#define ssc_is_error(value) (value) < SSC_OK

/**
 * Returns string version of an `SSCResult` code.
 * @param result `SSCResult` code value
 * @return String of `result`
 */
SSC_EXPORT const SSCString
ssc_result_string (const SSCResult result);

#endif
