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

#ifndef SSC_URI_H
#define SSC_URI_H

#include "buffer.h"
#include "platform.h"
#include "result.h"

#define SSC_FILE_URI_PREFIX "file://"
#define SSC_FILE_URI_PREFIX_SIZE sizeof(SSC_FILE_URI_PREFIX)

/**
 * Max URI in bytes including protocol prefix
 */
#define SSC_URI_MAX_BYTES 512 * 1024

/**
 * Emits static `SSCURI` properties of `static_size` bytes of memory.
 * @param static_size Number of bytes for static `SSCByte` array.
 * @prop bytes
 * @prop href
 * @prop protocol
 * @prop username
 * @prop password
 * @prop host
 * @prop port
 * @prop path
 * @prop query
 * @prop hash
 */
#define SSCURIProperties(static_size)                                          \
  SSCByte bytes[static_size];                                                  \
  SSCBuffer href;                                                              \
  SSCBuffer protocol;                                                          \
  SSCBuffer username;                                                          \
  SSCBuffer password;                                                          \
  SSCBuffer host;                                                              \
  SSCBuffer port;                                                              \
  SSCBuffer path;                                                              \
  SSCBuffer query;                                                             \
  SSCBuffer hash;

/**
 * @param static_size
 */
#define SSCURI(static_size)                                                    \
  struct {                                                                     \
    SSCURIProperties(static_size)                                              \
  }

/**
 * A simple container for a URI.
 */
typedef struct SSCURI SSCURI;
struct SSCURI {
  SSCURIProperties(SSC_URI_MAX_BYTES)
};

/**
 * Parses `input` buffer into `uri` pointer.
 * @param uri A pointer to a `SSCURI` struct
 * @param input An input buffer
 * @return `SSC_OK` upon success, otherwise an error
 */
SSC_EXPORT SSCResult
ssc_uri_parse (SSCURI *uri, const SSCBuffer input);

/**
 * Prints `uri` to stdout`.
 * @param uri
 */
SSC_EXPORT void
ssc_uri_print (const SSCURI uri);

/**
 * Encodes `input` as a URI component into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_component_encode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes URI component encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_component_encode_size (const SSCBuffer input);

/**
 * Decodes `input` URI component into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_component_decode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes URI component decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_component_decode_size (const SSCBuffer input);

/**
 * Encodes `input` as an URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_encode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes URI encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_encode_size (const SSCBuffer input);

/**
 * Decodes `input` URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_decode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes URI decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_decode_size (const SSCBuffer input);

/**
 * Encodes `input` as a file URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_file_encode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes file URI encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_file_encode_size (const SSCBuffer input);

/**
 * Decodes `input` file URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
SSC_EXPORT SSCSize
ssc_uri_file_decode (SSCBuffer *output, const SSCBuffer input);

/**
 * Computes file URI decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
SSC_EXPORT SSCSize
ssc_uri_file_decode_size (const SSCBuffer input);

#endif
