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

static const unsigned long long UMAX = -1;

test("math") {
  assert(opc_math_clamp(1, 0, 2) == 1);
  assert(opc_math_clamp(-2, -3, 3) == -2);
  assert(opc_math_clamp(-128, -128, 128) == -128);
  assert(opc_math_uclamp(-2, -1, 2) == UMAX - 1);

  assert(opc_math_in_range(1, 0, 2));
  assert(opc_math_in_range(0, 0, 2));
  assert(opc_math_in_range(2, 0, 2));
  assert(!opc_math_in_range(-1, 0, 2));
  assert(!opc_math_in_range(3, 0, 2));
  assert(opc_math_in_urange(1, 0, 2));
  assert(opc_math_in_urange(0, 0, 2));
  assert(opc_math_in_urange(-1, 0, UMAX));
  assert(!opc_math_in_urange(-1, 0, UMAX - 2));
  assert(!opc_math_in_urange(-1, 0, 16));

  assert_equal(2, opc_math_abs(-2));
  assert_equal(2, opc_math_abs(2));
}
