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
#include <string.h>

static SSCByte stack[4096] = {0};
typedef struct CustomBuffer CustomBuffer;
struct CustomBuffer {
  SSCBuffer buffer;
};

test("ssc_buffer(value)") {
  // clang-format off
  CustomBuffer custom_buffer = {
    .buffer = ssc_buffer_from(stack, sizeof(stack))
  };
  // clang-format on

  SSCString string = "hello world";
  SSCUSize offset = 32;
  SSCUSize size = ssc_string_size(string);

  assert_equal(
    size, ssc_buffer_write_string(&ssc_buffer(custom_buffer), string, offset)
  );

  assert_equal(
    SSC_TRUE,
    ssc_buffer_equals(
      ssc_buffer_from_string(string),
      ssc_buffer_slice(ssc_buffer(custom_buffer), offset, offset + size)
    )
  );
}
