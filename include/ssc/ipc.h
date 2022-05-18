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

#ifndef SSC_IPC_H
#define SSC_IPC_H

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
 */
#define SSC_IPC_URI_PREFIX "ipc://"

/**
 * Options for a low-level `send` IPC RPC command.
 */
typedef struct SSCIPCSendOptions SSCIPCSendOptions;

struct SSCIPCSendOptions {
  const SSCUSize window;
  const SSCString event;
  const SSCBuffer value;
};

/**
 * Key-value pair of request data to be encoded before sending as an IPC RPC
 * request.
 */
typedef struct SSCIPCRequestData SSCIPCRequestData;

struct SSCIPCRequestData {
  SSCBuffer **tuples;
  SSCUSize length;
};

/**
 * Options for a low-level IPC RPC request.
 */
typedef struct SSCIPCRequestOptions SSCIPCRequestOptions;

struct SSCIPCRequestOptions {
  const SSCUSize window;
  const SSCBuffer command;
  const SSCIPCRequestData data;
};

/**
 * IPC RPC context that tracks state required for request-response
 * resolution.
 */
typedef struct SSCIPCContext SSCIPCContext;

struct SSCIPCContext {
  SSCUSize seq;
  SSCByte cwd[IPC_MAX_CWD_PATH_BYTES];
  SSCByte memory[IPC_MAX_MEMORY_BYTES];

  struct {
    SSCHandle stdin;
    SSCHandle stdout;
    SSCHandle stderr;
  } io;
};

/**
 * Initializes an `SSCIPCContext` context.
 * @param context IPC context to write to
 * @param context
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_context_init (SSCIPCContext *context);

/**
 * Write a `string` formatted with vector `args` to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param args `va_list` vector of values for `string` format
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_vwrite_string (
  SSCIPCContext *context,
  const SSCString string,
  va_list args
);

/**
 * Write a `string` formatted with variadic arguments to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param ... Variadic arguments for `string` format
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_write_string (SSCIPCContext *context, const SSCString string, ...);

/**
 * Write a `buffer` to the IPC context.
 * @param context IPC context to write to
 * @param string Format string
 * @param ... Variadic arguments for `string` format
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_write (SSCIPCContext *context, const SSCBuffer buffer);

/**
 * Flush the IPC context.
 * @param context IPC context to write to
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_flush (SSCIPCContext *context);

/**
 * Send an event to the IPC context.
 * @param context IPC context to write to
 * @param options IPC send options (window, event, value)
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_send (SSCIPCContext *context, const SSCIPCSendOptions options);

/**
 * Send a request to the IPC context.
 * @param context IPC context to write to
 * @param options IPC request options (window, command, ...data)
 * @return `SSC_OK` upon success, otherwise an error code
 */
SSC_EXPORT SSCResult
ssc_ipc_request (SSCIPCContext *context, const SSCIPCRequestOptions options);

#endif
