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

OPCBuffer
opc_buffer_slice (const OPCBuffer self, OPCUSize start, OPCUSize end) {
  OPCUSize size = opc_math_uclamp(end - start, 0, self.size);
  OPCUSize offset = opc_math_uclamp(start, 0, self.size - size);
  OPCBytes bytes = self.bytes + offset;

  return (OPCBuffer) { bytes, size };
}

const OPCResult
opc_buffer_compare (const OPCBuffer self, const OPCBuffer right) {
  return opc_string_compare_with_size(
    opc_string(self.bytes),
    self.size,
    opc_string(right.bytes),
    right.size
  );
}

const OPCUSize
opc_buffer_write (
  OPCBuffer *self,
  const OPCBytes bytes,
  const OPCUSize offset,
  const OPCUSize size
) {
  OPCUSize written = 0;

  if (offset + size > self->size) {
    return 0;
  }

  for (OPCUSize i = offset; i < offset + size; ++i) {
    self->bytes[i] = bytes[written++];
  }

  return written;
}

const OPCUSize
opc_buffer_write_string (
  OPCBuffer *self,
  const OPCString string,
  const OPCUSize offset
) {
  OPCUSize size = opc_string_size(string);
  return opc_buffer_write(self, opc_buffer_bytes(string), offset, size);
}

const OPCSize
opc_buffer_fill (
  OPCBuffer *self,
  const OPCByte byte,
  const OPCUSize offset,
  const OPCSize end
) {
  OPCSize filled = 0;

  if (self == 0) {
    return opc_throw(OPC_NULL_POINTER, "Output buffer pointer cannot be null.");
  }

  if (self->bytes == 0) {
    return opc_throw(
      OPC_NULL_POINTER, "Output buffer bytes pointer cannot be null."
    );
  }

  if (offset > self->size) {
    return opc_throw(
      OPC_OUT_OF_BOUNDS,
      "Start offset cannot be larger than output buffer size."
    );
  }

  if (end > self->size) {
    return opc_throw(
      OPC_OUT_OF_BOUNDS, "End offset cannot be larger than output buffer size."
    );
  }

  if (end != -1 && end < offset) {
    return opc_throw(
      OPC_OUT_OF_BOUNDS, "End offset cannot be smaller than start offset."
    );
  }

  for (OPCUSize i = offset; i < self->size; ++i) {
    if (end != -1 && i > end) {
      break;
    }

    self->bytes[i] = byte;
  }

  return filled;
}
