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

#ifndef SSC_BUFFER_H
#define SSC_BUFFER_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * Emits core `SSCBuffer` properties.
 * @prop bytes Pointer to memory for the buffer
 * @prop size Size of memory in `bytes`
 * @prop parent Optional parent if `SSCBuffer` is a slice of `parent`
 * @prop offset Optional offset in `parent` where `bytes` begins if it is a
 * child of `parent`
 */
#define SSCBufferCoreProperties()                                              \
  SSCBytes bytes;                                                              \
  SSCUSize size;                                                               \
  SSCBytes parent;                                                             \
  SSCUSize offset;

/**
 * Emits static `SSCBuffer` properties of `static_size` bytes of memory.
 * @param static_size Number of bytes for static `SSCByte` array.
 * @prop bytes Static `SSCByte` array of `static_size` size
 * @prop size Size of static memory in `bytes`
 * @prop parent Should always be `NULL` as the buffer is static
 * @prop offset Should always be `0` as the buffer is static
 */
#define SSCBufferProperties(static_size)                                       \
  SSCByte bytes[static_size];                                                  \
  SSCUSize size;                                                               \
  SSCBytes parent;                                                             \
  SSCUSize offset;

/**
 * Inline static struct with `SSCBuffer` properties.
 * @param static_size Number of bytes for static `SSCByte` array.
 * @see `SSCBufferProperties(static_size)`
 */
#define SSCBuffer(static_size)                                                 \
  struct {                                                                     \
    SSCBufferProperties(static_size)                                           \
  }

/**
 * Inline struct for a static map of `SSCBuffer` types by name.
 * @example
 * SSCBufferStaticMap(hello, world) map;
 * ssc_buffer_set(&map.hello, "hello", 5);
 * ssc_buffer_set(&map.world, "world", 5);
 * ssc_buffer_print(map.hello); // "hello"
 * ssc_buffer_print(map.wrodl); // "world"
 */
#define SSCBufferStaticMap(...)                                                \
  struct {                                                                     \
    SSCBuffer __VA_ARGS__;                                                     \
  }

/**
 * A container for a bytes pointer with size.
 * @see `SSCBufferProperties(static_size)`
 */
typedef struct SSCBuffer SSCBuffer;

struct SSCBuffer {
  SSCBufferCoreProperties()
};

/**
 * Casts `value` to a `SSCBuffer`
 * @param value
 * @return `value` casted to `SSCBuffer`
 */
#define ssc_buffer(value) (*((SSCBuffer *) &((value))))

/**
 * Emits struct initialization for a static `SSCBuffer(size)` with
 * an optional `parent` and `offset` values.
 * @param self
 * @param parent Optional parent bytes pointer
 * @param offset Optional offset in parent bytes pointer
 * @return An initialized `SSCBuffer(size)` static buffer.
 */
#define ssc_buffer_static_init(self, ...)                                      \
  .bytes = { 0 }, .size = sizeof(self.bytes), ##__VA_ARGS__

/**
 * Converts `bytes` to an `SSCBuffer` with optional `size` and `parent`
 * properties.
 * @param bytes Bytes pointer
 * @param [parent = 0] Optional parent to bytes
 * @param [offset = 0] Optional byte offset in parent bytes
 * @return An `SSCBuffer` structure
 */
#define ssc_buffer_from(bytes, ...)                                            \
  ((SSCBuffer) { ssc_bytes(bytes), ##__VA_ARGS__ })

/**
 * Converts static `SSCBuffer(size)` to `SSCBuffer`.
 * @param value
 * @return An `SSCBuffer` structure
 */
#define ssc_buffer_from_static(value, ...)                                     \
  ((SSCBuffer) { value.bytes, sizeof(value.bytes), ##__VA_ARGS__ })

// clang-format on
/**
 * Converts `string` to an `SSCBuffer` with `size` computed dynamically.
 * @param string The string
 */
#define ssc_buffer_from_string(string)                                         \
  ssc_buffer_from(                                                             \
    ssc_bytes(ssc_string(string)), ssc_string_size(ssc_string(string))         \
  )

/**
 * Prints a buffer to stdout.
 * @param buffer
 */
#define ssc_buffer_print(buffer)                                               \
  {                                                                            \
    SSCBuffer self = (SSCBuffer) (buffer);                                     \
    ssc_string_fprintf(                                                        \
      ssc_stdout(), "%.*s\n", ssc_int(self.size), ssc_string(self.bytes)       \
    );                                                                         \
  }

/**
 * Writes zeros to `buffer` up to `size` bytes.
 * @param buffer
 * @param size
 */
#define ssc_buffer_zero(buffer, size) ssc_buffer_fill(&(buffer), 0, 0, size)

/**
 * @param buffer A pointer to a `SSCBuffer`
 * @param bytes A pointer to the `bytes` memory
 * @param size Size of memory in `bytes`
 */
#define ssc_buffer_set(buffer, _bytes, _size)                                  \
  ({                                                                           \
    SSCBuffer *_self = (buffer);                                               \
    _self->bytes = ssc_bytes(_bytes);                                          \
    _self->size = ssc_usize(_size);                                            \
    *(_self);                                                                  \
  })

/**
 * Set `input` buffer on `buffer` instance replaceing `bytes` and `size.
 * @param buffer
 * @param input
 */
#define ssc_buffer_set_buffer(self, buffer)                                    \
  ssc_buffer_set(self, buffer.bytes, buffer.size)

/**
 * Computes a new buffer with slice
 * @param buffer
 * @param start
 * @param end
 * @return A new `SSCBuffer` that points to memory in `buffer`
 */
SSC_EXPORT SSCBuffer
ssc_buffer_slice (const SSCBuffer buffer, SSCUSize start, SSCUSize end);

/**
 * Compares `left` and `right` buffers returning `-1`, `0`, or `1` if the left
 * buffer is less than the `right` buffer`, the buffers are the equal, or the
 * `left` buffer is greater than the `right` buffer.
 * @param left
 * @param right
 * @return `-1`, `0`, or `1` indicating the buffer difference or equality.
 */
SSC_EXPORT const SSCSize
ssc_buffer_compare (const SSCBuffer buffer, const SSCBuffer right);

/**
 * Compares `left` and `right` buffer equality
 * @param left
 * @param right
 * @return Returns `SSC_TRUE` if buffers are equal, otherwise `SSC_FALSE`
 */
SSC_EXPORT SSCBoolean
ssc_buffer_equals (const SSCBuffer left, const SSCBuffer right);

/**
 * Write `size` bytes at `offset` in `buffer`.
 * @param buffer
 * @param bytes
 * @param offset
 * @param size
 * @return Number of bytes written to `buffer`.
 */
SSC_EXPORT const SSCUSize
ssc_buffer_write (
  SSCBuffer *buffer,
  const SSCBytes bytes,
  const SSCUSize offset,
  const SSCUSize size
);

/**
 * Write nullterm `string` at `offset` in `buffer`.
 * @param buffer
 * @param string
 * @param offset
 * @return Number of bytes written to `buffer`.
 */
SSC_EXPORT const SSCUSize
ssc_buffer_write_string (
  SSCBuffer *buffer,
  const SSCString string,
  const SSCUSize offset
);

/**
 * Write `input_buffer` to `buffer` at `offset`.
 * @param buffer
 * @param input_buffer
 * @param offset
 * @return Number of bytes written to `buffer`.
 */
SSC_EXPORT const SSCUSize
ssc_buffer_write_buffer (
  SSCBuffer *buffer,
  const SSCBuffer input_buffer,
  const SSCUSize offset
);

/**
 * Fill `buffer` with `byte` starting at `offset` and stopping at `end`
 * @param byte
 * @param offset
 * @param end
 * @return The number of bytes written to `buffer`
 */
SSC_EXPORT const SSCSize
ssc_buffer_fill (
  SSCBuffer *buffer,
  const SSCByte byte,
  const SSCUSize offset,
  const SSCSize end
);

#endif
