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

#ifndef OPC_URI_H
#define OPC_URI_H

#include "buffer.h"
#include "platform.h"
#include "result.h"

#define OPC_FILE_URI_PREFIX "file://"
#define OPC_FILE_URI_PREFIX_SIZE sizeof(OPC_FILE_URI_PREFIX)

/**
 * Max URI in bytes including protocol prefix
 */
#define OPC_URI_MAX_BYTES 512 * 1024

/**
 * Emits static `OPCURI` properties of `static_size` bytes of memory.
 * @param static_size Number of bytes for static `OPCByte` array.
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
#define OPCURIProperties(static_size)                                          \
  OPCByte bytes[static_size];                                                  \
  OPCBuffer href;                                                              \
  OPCBuffer protocol;                                                          \
  OPCBuffer username;                                                          \
  OPCBuffer password;                                                          \
  OPCBuffer host;                                                              \
  OPCBuffer port;                                                              \
  OPCBuffer path;                                                              \
  OPCBuffer query;                                                             \
  OPCBuffer hash;

/**
 * @param static_size
 */
#define OPCURI(static_size)                                                    \
  struct {                                                                     \
    OPCURIProperties(static_size)                                              \
  }

/**
 * A simple container for a URI.
 */
typedef struct OPCURI OPCURI;
struct OPCURI {
  OPCURIProperties(OPC_URI_MAX_BYTES)
};

/**
 * Parses `input` buffer into `uri` pointer.
 * @param uri A pointer to a `OPCURI` struct
 * @param input An input buffer
 * @return `OPC_OK` upon success, otherwise an error
 */
OPC_EXPORT OPCResult
opc_uri_parse (OPCURI *uri, const OPCBuffer input);

/**
 * Prints `uri` to stdout`.
 * @param uri
 */
OPC_EXPORT void
opc_uri_print (const OPCURI uri);

/**
 * Encodes `input` as a URI component into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes URI component encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_component_encode_size (const OPCBuffer input);

/**
 * Decodes `input` URI component into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes URI component decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_component_decode_size (const OPCBuffer input);

/**
 * Encodes `input` as an URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_encode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes URI encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_encode_size (const OPCBuffer input);

/**
 * Decodes `input` URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_decode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes URI decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_decode_size (const OPCBuffer input);

/**
 * Encodes `input` as a file URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_file_encode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes file URI encode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the encode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_file_encode_size (const OPCBuffer input);

/**
 * Decodes `input` file URI into `output`
 * @param output Output buffer
 * @param input Input buffer
 * @return Bytes written to `output`
 */
OPC_EXPORT OPCSize
opc_uri_file_decode (OPCBuffer *output, const OPCBuffer input);

/**
 * Computes file URI decode output size for `input`
 * @param input Input buffer
 * @return Total bytes needed for the decode output of `input`
 */
OPC_EXPORT OPCSize
opc_uri_file_decode_size (const OPCBuffer input);

#endif
