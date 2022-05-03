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

// includes decoded unicode characters
#define SOURCE_STRING "betty aime le fromage français"
// includes encoded unicode characters
#define EXPECTED_STRING "betty%20aime%20le%20fromage%20fran%C3%A7ais"

static OPCByte stack[4096] = { 0 };

test("opc_uri_component_encode(output, input)") {
  const OPCString expected = opc_string(EXPECTED_STRING);
  const OPCString source = opc_string(SOURCE_STRING);

  const OPCUSize expected_size = opc_string_size(expected);
  const OPCUSize source_size = opc_string_size(source);

  OPCBuffer memory = opc_buffer_from(stack, sizeof(stack));
  OPCBuffer output = opc_buffer_slice(memory, 0, expected_size);
  OPCBuffer input =
    opc_buffer_slice(memory, output.size + 1, output.size + source_size + 1);

  // write source to input buffer
  assert(opc_buffer_write_string(&input, source, 0) > 0);

  // verify successful encode of input into output
  assert_equal(
    opc_string_size(EXPECTED_STRING), opc_uri_component_encode(&output, input)
  );
}
