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
#include <stdarg.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <stdio.h>
#include <unistd.h>
#endif

#include "types.h"

OPCResult
opc_ipc_context_init (OPCIPCContext *ctx) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

#ifdef _WIN32
  _getcwd((char *) ctx->cwd, IPC_MAX_CWD_PATH_BYTES);
#else
  getcwd((char *) ctx->cwd, IPC_MAX_CWD_PATH_BYTES);
#endif

  ctx->seq = 0;
  ctx->io.stdin = opc_init_stdin();
  ctx->io.stdout = opc_init_stdout();
  ctx->io.stderr = opc_init_stderr();

  return OPC_OK;
}

OPCResult
opc_ipc_write (OPCIPCContext *ctx, const OPCBuffer buffer) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  return opc_ipc_write_string(
    ctx, "%*.s\n", buffer.size, opc_string(buffer.bytes)
  );
}

OPCResult
opc_ipc_vwrite_string (
  OPCIPCContext *ctx,
  const OPCString string,
  va_list args
) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  if (string == 0) {
    return opc_throw(OPC_NULL_POINTER, "String cannot be NULL");
  }

  // NOLINTNEXTLINE
  OPC_VFPRINTF(ctx->io.stdout, string, args);
  return OPC_OK;
}

OPCResult
opc_ipc_write_string (OPCIPCContext *ctx, const OPCString string, ...) {
  va_list args;

  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  va_start(args, string);
  opc_ipc_vwrite_string(ctx, string, args);
  va_end(args);

  return OPC_OK;
}

OPCResult
opc_ipc_flush (OPCIPCContext *ctx) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  return opc_ipc_write_string(ctx, "\n");
}

OPCResult
opc_ipc_send (OPCIPCContext *ctx, const OPCIPCSendOptions options) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  if (options.event == 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Missing options.event");
  }

  if (options.value.size > 0 && options.value.bytes != 0) {
    return opc_ipc_write_string(
      ctx,
      "ipc://send?window=%llu&event=%s&value=%*.s\n",
      options.window,
      options.event,
      options.value.size,
      opc_string(options.value.bytes)
    );
  }

  return opc_ipc_write_string(
    ctx,
    "ipc://send?window=%llu&event=%s&value=\"\"\n",
    options.window,
    options.event
  );
}

OPCResult
opc_ipc_request (OPCIPCContext *ctx, const OPCIPCRequestOptions options) {
  if (ctx == 0) {
    return opc_throw(OPC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  OPCBuffer buffer = opc_buffer_from(ctx->memory, IPC_MAX_MEMORY_BYTES);
  OPCUSize seq = ctx->seq++;

  opc_ipc_write_string(
    ctx,
    "ipc://%.*s?seq=%llu&value=\"\"&window=%llu",
    options.command.size,
    options.command.bytes,
    seq,
    options.window
  );

  for (int i = 0; i < options.data.length; i += 2) {
    OPCBuffer *key = options.data.tuples[i];
    OPCBuffer *value = options.data.tuples[i + 1];

    if (key != 0 && value != 0) {
      if (key->size > 0 && value->size > 0) {
        OPCSize key_size = opc_uri_component_encode(&buffer, *key);
        opc_ipc_write_string(ctx, "&%.*s=", key_size, buffer.bytes);

        OPCSize value_size = opc_uri_component_encode(&buffer, *value);
        opc_ipc_write_string(ctx, "%.*s", value_size, buffer.bytes);
      }
    }
  }

  opc_ipc_flush(ctx);
  return OPC_OK;
}
