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

#define from_macro(...) SSC_PP_VARG_COUNT(__VA_ARGS__)

test("pp") {
  assert(0 == SSC_PP_VARG_COUNT());
  assert(1 == SSC_PP_VARG_COUNT(1));
  assert(2 == SSC_PP_VARG_COUNT(1, 2));
  assert(3 == SSC_PP_VARG_COUNT(1, 2, 3));
  assert(4 == SSC_PP_VARG_COUNT(1, 2, 3, 4));
  assert(5 == SSC_PP_VARG_COUNT(1, 2, 3, 4, 5));

  assert_equal(0, from_macro());
  assert_equal(1, from_macro(1));
  assert_equal(2, from_macro(1, 2));
  assert_equal(3, from_macro(1, 2, 3));
  assert_equal(4, from_macro(1, 2, 3, 4));
  assert_equal(5, from_macro(1, 2, 3, 4, 5));

  assert_equal(2, from_macro("foo", ("foo", 123)));

  // defects
  assert_equal(0, SSC_PP_VARG_COUNT(("a", "b")));
  assert_equal(0, SSC_PP_VARG_COUNT(("x", "y", "z")));
  assert_equal(0, from_macro((1, 2)));
  assert_equal(0, from_macro((1, 2, 3)));
}
