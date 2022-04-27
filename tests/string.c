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

#include <opc/test.h>

test("string", 0) {
  assert(opc_string_size(opc_string("hello")) == 5);
  assert(opc_string_size(opc_string("world")) == 5);
  assert(opc_string_size(opc_string("h")) == 1);
  assert(opc_string_size(opc_string("")) == 0);
  assert(opc_string_compare(opc_string("hello"), opc_string("hello")) == 0);
  assert(opc_string_compare(opc_string("hello"), opc_string("world")) == -1);
  assert(opc_string_compare(opc_string("world"), opc_string("hello")) == 1);

  assert(opc_string_equals(opc_string("hello"), opc_string("hello")));

  assert_equal(
    0,
    opc_string_compare_with_size(
      opc_string("hello world"), 5, opc_string("hello moon"), 5
    )
  );

  assert_equal(
    0,
    opc_string_compare_with_size(
      opc_string_slice(opc_string("hello world"), 6),
      5,
      opc_string_slice(opc_string("goodbye world"), 8),
      5
    )
  );
}
