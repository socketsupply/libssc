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
#include <string.h>

static OPCByte stack[4096] = {0};

test("opc_buffer_from(bytes)", 0) {
  OPCBuffer hello = opc_buffer_from_string("hello");
  OPCBuffer bytes = opc_buffer_from(stack, sizeof(stack));

  assert(0 == strncmp(opc_string(hello.bytes), "hello", hello.size));
  assert(bytes.bytes == opc_bytes(stack));

  stack[64] = opc_byte('w');
  stack[65] = opc_byte('o');
  stack[66] = opc_byte('r');
  stack[67] = opc_byte('l');
  stack[68] = opc_byte('d');

  assert(bytes.bytes + 64 == opc_bytes(stack + 64));
  assert(0 == strncmp(opc_string(bytes.bytes + 64), "world", 5));

  OPCBuffer buffer = opc_buffer_from(stack, sizeof(stack));

  assert(opc_bytes(buffer.bytes) == opc_bytes(stack));
  assert(buffer.size == sizeof(stack));

  OPCBuffer slice = opc_buffer_from(
    opc_bytes(stack) + 1024,
    4096 - 1024,
    opc_bytes(stack),
    1024
  );

  assert(slice.parent == opc_bytes(stack));
  assert(slice.size == 4096 - 1024);
  assert(slice.offset = 1024);

  OPCBuffer with_members = opc_buffer_from(
    slice.bytes + 1024,
    .parent = slice.bytes,
    .offset = 1024,
    .size = 1024
  );

  assert(with_members.bytes  == slice.bytes + 1024);
  assert(with_members.parent == slice.bytes);
  assert(with_members.offset == 1024);
  assert(with_members.size == 1024);
}