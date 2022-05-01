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

OPCUSize
opc_string_size (const OPCString string) {
  const OPCString pointer = string;
  OPCString ref = string;

  while (ref != 0 && *ref) {
    ++ref;
  }

  return ref - pointer;
}

int
opc_string_compare (const OPCString left, const OPCString right) {
  if (left == 0 && right == 0) {
    return 0;
  }

  if (left == 0 && right != 0) {
    return -1;
  }

  if (left != 0 && right == 0) {
    return 1;
  }

  for (int i = 0; left[i] != 0 || right[i] != 0; ++i) {
    if (left[i] < right[i]) {
      return -1;
    }

    if (left[i] > right[i]) {
      return 1;
    }
  }

  return 0;
}

int
opc_string_compare_with_size (
  const OPCString left,
  const OPCUSize left_size,
  const OPCString right,
  const OPCUSize right_size
) {
  if (left == 0 && right == 0) {
    return 0;
  }

  if (left == 0 && right != 0) {
    return -1;
  }

  if (left != 0 && right == 0) {
    return 1;
  }

  for (int i = 0; i < left_size && i < right_size; ++i) {
    if (left[i] < right[i]) {
      return -1;
    }

    if (left[i] > right[i]) {
      return 1;
    }
  }

  return 0;
}

const OPCString
opc_string_slice (const OPCString self, const OPCUSize offset) {
  if (self == 0) {
    return 0;
  }

  return self + offset;
}

OPCBoolean
opc_string_equals (const OPCString left, const OPCString right) {
  return opc_string_compare(left, right) == 0 ? true : false;
}
