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

SSCBuffer
ssc_buffer_slice (const SSCBuffer self, SSCUSize start, SSCUSize end) {
  SSCUSize size = ssc_math_uclamp(end - start, 0, self.size);
  SSCUSize offset = ssc_math_uclamp(start, 0, self.size - size);
  SSCBytes bytes = self.bytes + offset;

  return ssc_buffer_from(bytes, size, self.bytes, offset);
}

const SSCSize
ssc_buffer_compare (const SSCBuffer self, const SSCBuffer right) {
  if (self.bytes == 0 && right.bytes == 0) {
    return 0;
  }

  if (self.bytes == 0 && right.bytes != 0) {
    return -1;
  }

  if (self.bytes != 0 && right.bytes == 0) {
    return 1;
  }

  if (self.size > 0 && right.size == 0) {
    return 1;
  }

  if (self.size == 0 && right.size > 0) {
    return -1;
  }

  for (int i = 0; i < self.size && i < right.size; ++i) {
    if (self.bytes[i] < right.bytes[i]) {
      return -1;
    }

    if (self.bytes[i] > right.bytes[i]) {
      return 1;
    }
  }

  return 0;
}

SSCBoolean
ssc_buffer_equals (const SSCBuffer left, const SSCBuffer right) {
  return ssc_buffer_compare(left, right) == 0 ? true : false;
}

const SSCUSize
ssc_buffer_write (
  SSCBuffer *self,
  const SSCBytes bytes,
  const SSCUSize offset,
  const SSCUSize size
) {
  SSCUSize written = 0;

  if (self == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Output buffer pointer cannot be null.");
  }

  if (self->bytes == 0) {
    return ssc_throw(
      SSC_NULL_POINTER, "Output buffer bytes pointer cannot be null."
    );
  }

  if (offset + size > self->size) {
    return ssc_throw(
      SSC_OUT_OF_BOUNDS,
      "Start offset cannot be larger than output buffer size."
    );
  }

  for (SSCUSize i = offset; i < offset + size; ++i) {
    self->bytes[i] = bytes[written++];
  }

  return written;
}

const SSCUSize
ssc_buffer_write_string (
  SSCBuffer *self,
  const SSCString string,
  const SSCUSize offset
) {
  SSCUSize size = ssc_string_size(string);
  return ssc_buffer_write(self, ssc_bytes(string), offset, size);
}

const SSCUSize
ssc_buffer_write_buffer (
  SSCBuffer *self,
  const SSCBuffer buffer,
  const SSCUSize offset
) {
  return ssc_buffer_write(self, buffer.bytes, offset, buffer.size);
}

const SSCSize
ssc_buffer_fill (
  SSCBuffer *self,
  const SSCByte byte,
  const SSCUSize offset,
  const SSCSize end
) {
  SSCSize filled = 0;

  if (self == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Output buffer pointer cannot be null.");
  }

  if (self->bytes == 0) {
    return ssc_throw(
      SSC_NULL_POINTER, "Output buffer bytes pointer cannot be null."
    );
  }

  if (offset > self->size) {
    return ssc_throw(
      SSC_OUT_OF_BOUNDS,
      "Start offset cannot be larger than output buffer size."
    );
  }

  if (end >= 0 && end > self->size) {
    return ssc_throw(
      SSC_OUT_OF_BOUNDS, "End offset cannot be larger than output buffer size."
    );
  }

  if (end != -1 && end < offset) {
    return ssc_throw(
      SSC_OUT_OF_BOUNDS, "End offset cannot be smaller than start offset."
    );
  }

  for (SSCUSize i = offset; i < self->size; ++i) {
    if (end != -1 && i >= end) {
      break;
    }

    self->bytes[i] = byte;
    filled = filled + 1;
  }

  return filled;
}
