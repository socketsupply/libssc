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

// clang-format off
static const char DEC2HEX[16 + 1] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'A', 'B',
  'C', 'D', 'E', 'F',
  '0'
};

static const char HEX2DEC[256] = {
  /*       0   1   2   3   4   5   6   7   8   9   A   B   C   D    E  F */
  /* 0 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 1 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 2 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 3 */  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
  /* 4 */ -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 5 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 6 */ -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 7 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 8 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 9 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* A */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* B */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* C */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* D */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* E */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* F */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

// clang-format on

OPCResult
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input) {
  OPCSize size = 0;

  if (output->bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Output bytes pointer cannot be NULL.");
  }

  if (input.bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Input bytes pointer cannot be NULL.");
  }

  for (int i = 0; i < input.size; ++i) {
    if (size >= output->size) {
      return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
    }

    const long status = opc_utf8_detect(opc_buffer_slice(input, i, i + 1));

    if (status < OPC_OK) {
      return status;
    }

    if (status == OPC_NOT_DETECTED) {
      output->bytes[size++] = input.bytes[i];
    } else {
      output->bytes[size++] = '%';

      if (size >= output->size) {
        return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[input.bytes[i] >> 4];

      if (size >= output->size) {
        return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[input.bytes[i] & 0x0f];
    }
  }

  return OPC_OK;
}

OPCSize
opc_uri_component_encode_size (const OPCBuffer input) {
  OPCSize size = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  for (int i = 0; i < input.size && input.bytes[i] != 0; ++i) {
    long status = opc_utf8_detect(opc_buffer_slice(input, i, i + 1));

    switch (status) {
      case OPC_NOT_DETECTED:
        size++;
        break;
      case OPC_DETECTED:
        size = size + 3; // %XX
        break;
      default:
        return status;
    }
  }

  return (long) size;
}

OPCResult
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input) {
  OPCSize size = 0;

  if (output->bytes == 0 || input.bytes == 0) {
    return OPC_NULL_POINTER;
  }

  for (int i = 0; i < input.size; ++i) {
    if (input.bytes[i] == 0)
      break;

    if (size >= output->size) {
      return OPC_OUT_OF_MEMORY;
    }

    if (input.bytes[i] == '%') {
      OPCSize x = HEX2DEC[input.bytes[i + 1]];
      OPCSize y = HEX2DEC[input.bytes[i + 2]];

      i = i + 2;

      output->bytes[size++] = (x << 4) + y;
    } else {
      output->bytes[size++] = input.bytes[i];
    }
  }

  return OPC_OK;
}

OPCSize
opc_uri_component_decode_size (const OPCBuffer input) {
  OPCSize size = 0;
  OPCSize length = input.size;
  int i = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  while (length-- && i < input.size) {
    if (input.bytes[i] == '%') {
      i = i + 3;
    } else {
      i = i + 1;
    }

    size = size + 1;
  }

  return size;
}
