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
 * Emits core `OPCBuffer` properties.
 * @prop bytes Pointer to memory for the buffer
 * @prop size Size of memory in `bytes`
 * @prop parent Optional parent if `OPCBuffer` is a slice of `parent`
 * @prop offset Optional offset in `parent` where `bytes` begins if it is a
 * child of `parent`
 */
#define OPCBufferCoreProperties()                                              \
  OPCBytes bytes;                                                              \
  OPCUSize size;                                                               \
  OPCBytes parent;                                                             \
  OPCUSize offset;

/**
 * Emits static `OPCBuffer` properties of `static_size` bytes of memory.
 * @param static_size Number of bytes for static `OPCByte` array.
 * @prop bytes Static `OPCByte` array of `static_size` size
 * @prop size Size of static memory in `bytes`
 * @prop parent Should always be `NULL` as the buffer is static
 * @prop offset Should always be `0` as the buffer is static
 */
#define OPCBufferProperties(static_size)                                       \
  OPCByte bytes[static_size];                                                  \
  OPCUSize size;                                                               \
  OPCBytes parent;                                                             \
  OPCUSize offset;

/**
 * Inline static struct with `OPCBuffer` properties.
 * @param static_size Number of bytes for static `OPCByte` array.
 * @see `OPCBufferProperties(static_size)`
 */
#define OPCBuffer(static_size)                                                 \
  struct {                                                                     \
    OPCBufferProperties(static_size)                                           \
  }

/**
 * Inline struct for a static map of `OPCBuffer` types by name.
 * @example
 * OPCBufferStaticMap(hello, world) map;
 * opc_buffer_set(&map.hello, "hello", 5);
 * opc_buffer_set(&map.world, "world", 5);
 * opc_buffer_print(map.hello); // "hello"
 * opc_buffer_print(map.wrodl); // "world"
 */
#define OPCBufferStaticMap(...)                                                \
  struct {                                                                     \
    OPCBuffer __VA_ARGS__;                                                     \
  }

/**
 * A container for a bytes pointer with size.
 * @see `OPCBufferProperties(static_size)`
 */
typedef struct OPCBuffer OPCBuffer;

struct OPCBuffer {
  OPCBufferCoreProperties()
};

/**
 * Casts `value` to a `OPCBuffer`
 * @param value
 * @return `value` casted to `OPCBuffer`
 */
#define opc_buffer(value) (*((OPCBuffer *) &((value))))

/**
 * Emits struct initialization for a static `OPCBuffer(size)` with
 * an optional `parent` and `offset` values.
 * @param self
 * @param parent Optional parent bytes pointer
 * @param offset Optional offset in parent bytes pointer
 * @return An initialized `OPCBuffer(size)` static buffer.
 */
#define opc_buffer_static_init(self, ...)                                      \
  .bytes = { 0 }, .size = sizeof(self.bytes), ##__VA_ARGS__

/**
 * Converts `bytes` to an `OPCBuffer` with optional `size` and `parent`
 * properties.
 * @param bytes Bytes pointer
 * @param [parent = 0] Optional parent to bytes
 * @param [offset = 0] Optional byte offset in parent bytes
 * @return An `OPCBuffer` structure
 */
#define opc_buffer_from(bytes, ...)                                            \
  ((OPCBuffer) { opc_bytes(bytes), ##__VA_ARGS__ })

/**
 * Converts static `OPCBuffer(size)` to `OPCBuffer`.
 * @param value
 * @return An `OPCBuffer` structure
 */
#define opc_buffer_from_static(value, ...)                                     \
  ((OPCBuffer) { value.bytes, sizeof(value.bytes), ##__VA_ARGS__ })

// clang-format on
/**
 * Converts `string` to an `OPCBuffer` with `size` computed dynamically.
 * @param string The string
 */
#define opc_buffer_from_string(string)                                         \
  opc_buffer_from(                                                             \
    opc_bytes(opc_string(string)), opc_string_size(opc_string(string))         \
  )

/**
 * Prints a buffer to stdout.
 * @param buffer
 */
#define opc_buffer_print(buffer)                                               \
  {                                                                            \
    OPCBuffer self = (OPCBuffer) (buffer);                                     \
    opc_string_fprintf(                                                        \
      opc_stdout(), "%.*s\n", opc_int(self.size), opc_string(self.bytes)       \
    );                                                                         \
  }

/**
 * Writes zeros to `buffer` up to `size` bytes.
 * @param buffer
 * @param size
 */
#define opc_buffer_zero(buffer, size) opc_buffer_fill(&(buffer), 0, 0, size)

/**
 * @param buffer A pointer to a `OPCBuffer`
 * @param bytes A pointer to the `bytes` memory
 * @param size Size of memory in `bytes`
 */
#define opc_buffer_set(buffer, _bytes, _size)                                  \
  ({                                                                           \
    OPCBuffer *_self = (buffer);                                               \
    _self->bytes = opc_bytes(_bytes);                                          \
    _self->size = opc_usize(_size);                                            \
    *(_self);                                                                  \
  })

/**
 * Set `input` buffer on `buffer` instance replaceing `bytes` and `size.
 * @param buffer
 * @param input
 */
#define opc_buffer_set_buffer(self, buffer)                                    \
  opc_buffer_set(self, buffer.bytes, buffer.size)

/**
 * Computes a new buffer with slice
 * @param buffer
 * @param start
 * @param end
 * @return A new `OPCBuffer` that points to memory in `buffer`
 */
OPC_EXPORT OPCBuffer
opc_buffer_slice (const OPCBuffer buffer, OPCUSize start, OPCUSize end);

/**
 * Compares `left` and `right` buffers returning `-1`, `0`, or `1` if the left
 * buffer is less than the `right` buffer`, the buffers are the equal, or the
 * `left` buffer is greater than the `right` buffer.
 * @param left
 * @param right
 * @return `-1`, `0`, or `1` indicating the buffer difference or equality.
 */
OPC_EXPORT const OPCSize
opc_buffer_compare (const OPCBuffer buffer, const OPCBuffer right);

/**
 * Compares `left` and `right` buffer equality
 * @param left
 * @param right
 * @return Returns `OPC_TRUE` if buffers are equal, otherwise `OPC_FALSE`
 */
OPC_EXPORT OPCBoolean
opc_buffer_equals (const OPCBuffer left, const OPCBuffer right);

/**
 * Write `size` bytes at `offset` in `buffer`.
 * @param buffer
 * @param bytes
 * @param offset
 * @param size
 * @return Number of bytes written to `buffer`.
 */
OPC_EXPORT const OPCUSize
opc_buffer_write (
  OPCBuffer *buffer,
  const OPCBytes bytes,
  const OPCUSize offset,
  const OPCUSize size
);

/**
 * Write nullterm `string` at `offset` in `buffer`.
 * @param buffer
 * @param string
 * @param offset
 * @return Number of bytes written to `buffer`.
 */
OPC_EXPORT const OPCUSize
opc_buffer_write_string (
  OPCBuffer *buffer,
  const OPCString string,
  const OPCUSize offset
);

/**
 * Write `input_buffer` to `buffer` at `offset`.
 * @param buffer
 * @param input_buffer
 * @param offset
 * @return Number of bytes written to `buffer`.
 */
OPC_EXPORT const OPCUSize
opc_buffer_write_buffer (
  OPCBuffer *buffer,
  const OPCBuffer input_buffer,
  const OPCUSize offset
);

/**
 * Fill `buffer` with `byte` starting at `offset` and stopping at `end`
 * @param byte
 * @param offset
 * @param end
 * @return The number of bytes written to `buffer`
 */
OPC_EXPORT const OPCSize
opc_buffer_fill (
  OPCBuffer *buffer,
  const OPCByte byte,
  const OPCUSize offset,
  const OPCSize end
);

#endif
