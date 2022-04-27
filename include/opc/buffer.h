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

#ifndef OPC_BUFFER_H
#define OPC_BUFFER_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * @TODO
 */

/**
 * @TODO(jwerle)
 */
typedef struct OPCBuffer OPCBuffer;

struct OPCBuffer {
  OPCBytes bytes;
  OPCUSize size;
};

/**
 * Converts `bytes` to an `OPCBuffer` with `.size` set to `0`.
 * @param bytes
 * @return An `OPCBuffer` structure
 */
#define opc_buffer(bytes) ((OPCBuffer) { (OPCBytes) (bytes), 0 })

/**
 * Converts `value` to a suitable `OPCBuffer` bytes
 * @param value Bytes pointer
 */
#define opc_buffer_bytes(value) opc_bytes(value)

/**
 * @TODO
 * @param
 */
#define opc_buffer_from(bytes)                                                 \
  ((OPCBuffer) { (OPCBytes) bytes, sizeof(bytes) })

/**
 * @TODO
 * @param string The string
 */
#define opc_buffer_from_string(string)                                         \
  ((OPCBuffer) { (OPCBytes) (string),                                    \
                 opc_string_size((char *) (string)) })

/**
 * @TODO
 * @param bytes The bytes
 */
#define opc_buffer_from_bytes(bytes, size)                                     \
  ((OPCBuffer) { (OPCBytes) (bytes), (OPCUSize) size })

/**
 * @TODO
 * @param buffer
 */
#define opc_buffer_print(self)                                                 \
  opc_string_printf("%.*s\n", (int) (self).size, opc_string((self).bytes))

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCBuffer
opc_buffer_slice (const OPCBuffer self, OPCUSize start, OPCUSize end);

/**
 * @TODO
 * @param left
 * @param right
 */
OPC_EXPORT const OPCResult
opc_buffer_compare (const OPCBuffer self, const OPCBuffer right);

/**
 * @TODO
 */
OPC_EXPORT const OPCUSize
opc_buffer_write (
  OPCBuffer *self,
  const OPCBytes bytes,
  const OPCUSize offset,
  const OPCUSize size
);

/**
 * @TODO
 */
OPC_EXPORT const OPCUSize
opc_buffer_write_string (
  OPCBuffer *self,
  const OPCString string,
  const OPCUSize offset
);

/**
 * @TODO
 */
OPC_EXPORT const OPCSize
opc_buffer_fill (
  OPCBuffer *self,
  const OPCByte byte,
  const OPCUSize offset,
  const OPCSize end
);

#endif
