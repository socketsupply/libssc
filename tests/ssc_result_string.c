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

#include <ssc/test.h>

#define assert_result_string(code)                                             \
  assert(ssc_string_equals(SSC_PP_STRING(code), ssc_result_string(code)))

test("ssc_result_string") {
  assert_result_string(SSC_MISSING_CONTEXT);
  assert_result_string(SSC_INVALID_ARGUMENT);
  assert_result_string(SSC_OUT_OF_BOUNDS);
  assert_result_string(SSC_OUT_OF_MEMORY);
  assert_result_string(SSC_NULL_POINTER);
  assert_result_string(SSC_ERROR);
  assert_result_string(SSC_OK);
  assert_result_string(SSC_DETECTED);
  assert_result_string(SSC_NOT_DETECTED);
  assert_result_string(SSC_UNKNOWN);

  assert(ssc_string_equals("SSC_UNKNOWN", ssc_result_string(-3000)));
  assert(ssc_string_equals("SSC_UNKNOWN", ssc_result_string(1046)));
}
