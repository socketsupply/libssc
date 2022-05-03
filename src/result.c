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

#include <opc/opc.h>
#include "types.h"

struct Result {
  const OPCResult code;
  const OPCString string;
};

// clang-format off
static struct Result results[] = {
  { OPC_E_MAX, "OPC_E_MAX" },
  { OPC_MISSING_CONTEXT, "OPC_MISSING_CONTEXT" },
  { OPC_BAD_STATE, "OPC_BAD_STATE" },
  { OPC_INVALID_ARGUMENT, "OPC_INVALID_ARGUMENT" },
  { OPC_OUT_OF_BOUNDS, "OPC_OUT_OF_BOUNDS" },
  { OPC_OUT_OF_MEMORY, "OPC_OUT_OF_MEMORY" },
  { OPC_NULL_POINTER, "OPC_NULL_POINTER" },
  { OPC_ERROR, "OPC_ERROR" },
  { OPC_OK, "OPC_OK" },
  { OPC_DETECTED, "OPC_DETECTED" },
  { OPC_NOT_DETECTED, "OPC_NOT_DETECTED" },
  { OPC_UNKNOWN, "OPC_UNKNOWN" }
};

// clang-format on

const OPCString
opc_result_string (const OPCResult result) {
  unsigned long count = sizeof(results) / sizeof(struct Result);

  for (int i = 0; i < count; ++i) {
    if (results[i].code == result) {
      return results[i].string;
    }
  }

  return results[count - 1].string;
}
