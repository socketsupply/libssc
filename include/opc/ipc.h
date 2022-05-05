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

#ifndef OPC_IPC_H
#define OPC_IPC_H

#include "buffer.h"
#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * Maximum memory in bytes for an IPC context.
 */
#define IPC_MAX_MEMORY_BYTES 524288 // 512 * 1024

/**
 * Maximum bytes for a path used in an IPC context.
 */
#define IPC_MAX_CWD_PATH_BYTES 1024

/**
 * Options for a low-level `send` IPC RPC command.
 */
typedef struct OPCIPCSendOptions OPCIPCSendOptions;

struct OPCIPCSendOptions {
  const OPCUSize window;
  const OPCString event;
  const OPCBuffer value;
};

/**
 * Key-value pair of request data to be encoded before sending as an IPC RPC
 * request.
 */
typedef struct OPCIPCRequestData OPCIPCRequestData;

struct OPCIPCRequestData {
  OPCBuffer **tuples;
  OPCUSize length;
};

/**
 * Options for a low-level IPC RPC request.
 */
typedef struct OPCIPCRequestOptions OPCIPCRequestOptions;

struct OPCIPCRequestOptions {
  const OPCUSize window;
  const OPCBuffer command;
  const OPCIPCRequestData data;
};

/**
 * IPC RPC context that tracks state required for request-response
 * resolution.
 */
typedef struct OPCIPCContext OPCIPCContext;

struct OPCIPCContext {
  OPCUSize seq;
  OPCByte cwd[IPC_MAX_CWD_PATH_BYTES];
  OPCByte memory[IPC_MAX_MEMORY_BYTES];

  struct {
    OPCHandle stdin;
    OPCHandle stdout;
    OPCHandle stderr;
  } io;
};

/**
 * Initializes an `OPCIPCContext` context.
 * @param context IPC context to write to
 * @param context
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_context_init (OPCIPCContext *context);

/**
 * Write a `string` formatted with vector `args` to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param args `va_list` vector of values for `string` format
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_vwrite_string (
  OPCIPCContext *context,
  const OPCString string,
  va_list args
);

/**
 * Write a `string` formatted with variadic arguments to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param ... Variadic arguments for `string` format
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_write_string (OPCIPCContext *context, const OPCString string, ...);

/**
 * Write a `buffer` to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param ... Variadic arguments for `string` format
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_write (OPCIPCContext *context, const OPCBuffer buffer);

/**
 * Flush the IPC context.
 * @param context IPC context to write to
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_flush (OPCIPCContext *context);

/**
 * Send an event to the IPC context.
 * @param context IPC context to write to
 * @param options IPC send options (window, event, value)
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_send (OPCIPCContext *context, const OPCIPCSendOptions options);

/**
 * Send a request to the IPC context.
 * @param context IPC context to write to
 * @param options IPC request options (window, command, ...data)
 * @return `OPC_OK` upon success, otherwise an error code
 */
OPC_EXPORT OPCResult
opc_ipc_request (OPCIPCContext *context, const OPCIPCRequestOptions options);

#endif
