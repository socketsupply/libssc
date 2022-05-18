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

SSCUSize
ssc_string_size (const SSCString string) {
  const SSCString pointer = string;
  SSCString ref = string;

  while (ref != 0 && *ref) {
    ++ref;
  }

  return ref - pointer;
}

int
ssc_string_compare (const SSCString left, const SSCString right) {
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
ssc_string_compare_with_size (
  const SSCString left,
  const SSCUSize left_size,
  const SSCString right,
  const SSCUSize right_size
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

const SSCString
ssc_string_slice (const SSCString self, const SSCUSize offset) {
  if (self == 0) {
    return 0;
  }

  return self + offset;
}

SSCBoolean
ssc_string_equals (const SSCString left, const SSCString right) {
  return ssc_string_compare(left, right) == 0 ? true : false;
}
