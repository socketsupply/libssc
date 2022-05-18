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

#include <ssc/ssc.h>

#include "internal.h"

struct Result {
  const SSCResult code;
  const SSCString string;
};

// clang-format off
static struct Result results[] = {
  { SSC_E_MAX, "SSC_E_MAX" },
  { SSC_MALFORMED_URI, "SSC_MALFORMED_URI" },
  { SSC_MISSING_CONTEXT, "SSC_MISSING_CONTEXT" },
  { SSC_BAD_STATE, "SSC_BAD_STATE" },
  { SSC_INVALID_ARGUMENT, "SSC_INVALID_ARGUMENT" },
  { SSC_OUT_OF_BOUNDS, "SSC_OUT_OF_BOUNDS" },
  { SSC_OUT_OF_MEMORY, "SSC_OUT_OF_MEMORY" },
  { SSC_NULL_POINTER, "SSC_NULL_POINTER" },
  { SSC_ERROR, "SSC_ERROR" },
  { SSC_OK, "SSC_OK" },
  { SSC_DETECTED, "SSC_DETECTED" },
  { SSC_NOT_DETECTED, "SSC_NOT_DETECTED" },
  { SSC_UNKNOWN, "SSC_UNKNOWN" }
};

// clang-format on

const SSCString
ssc_result_string (const SSCResult result) {
  unsigned long count = sizeof(results) / sizeof(struct Result);

  for (int i = 0; i < count; ++i) {
    if (results[i].code == result) {
      return results[i].string;
    }
  }

  return results[count - 1].string;
}
