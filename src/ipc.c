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
#include <stdarg.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <stdio.h>
#include <unistd.h>
#endif

#include "internal.h"

SSCResult
ssc_ipc_context_init (SSCIPCContext *ctx) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

#ifdef _WIN32
  _getcwd((char *) ctx->cwd, IPC_MAX_CWD_PATH_BYTES);
#else
  getcwd((char *) ctx->cwd, IPC_MAX_CWD_PATH_BYTES);
#endif

  ctx->seq = 0;
  ctx->io.stdin = ssc_init_stdin();
  ctx->io.stdout = ssc_init_stdout();
  ctx->io.stderr = ssc_init_stderr();

  return SSC_OK;
}

SSCResult
ssc_ipc_write (SSCIPCContext *ctx, const SSCBuffer buffer) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  return ssc_ipc_write_string(
    ctx, "%*.s\n", buffer.size, ssc_string(buffer.bytes)
  );
}

SSCResult
ssc_ipc_vwrite_string (
  SSCIPCContext *ctx,
  const SSCString string,
  va_list args
) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  if (string == 0) {
    return ssc_throw(SSC_NULL_POINTER, "String cannot be NULL");
  }

  // NOLINTNEXTLINE
  SSC_VFPRINTF(ctx->io.stdout, string, args);
  return SSC_OK;
}

SSCResult
ssc_ipc_write_string (SSCIPCContext *ctx, const SSCString string, ...) {
  va_list args;

  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  va_start(args, string);
  ssc_ipc_vwrite_string(ctx, string, args);
  va_end(args);

  return SSC_OK;
}

SSCResult
ssc_ipc_flush (SSCIPCContext *ctx) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  return ssc_ipc_write_string(ctx, "\n");
}

SSCResult
ssc_ipc_send (SSCIPCContext *ctx, const SSCIPCSendOptions options) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  if (options.event == 0) {
    return ssc_throw(SSC_INVALID_ARGUMENT, "Missing options.event");
  }

  if (options.value.size > 0 && options.value.bytes != 0) {
    return ssc_ipc_write_string(
      ctx,
      "ipc://send?window=%llu&event=%s&value=%*.s\n",
      options.window,
      options.event,
      options.value.size,
      ssc_string(options.value.bytes)
    );
  }

  return ssc_ipc_write_string(
    ctx,
    "ipc://send?window=%llu&event=%s&value=\"\"\n",
    options.window,
    options.event
  );
}

SSCResult
ssc_ipc_request (SSCIPCContext *ctx, const SSCIPCRequestOptions options) {
  if (ctx == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Context pointer cannot be NULL");
  }

  SSCBuffer buffer = ssc_buffer_from(ctx->memory, IPC_MAX_MEMORY_BYTES);
  SSCUSize seq = ctx->seq++;

  ssc_ipc_write_string(
    ctx,
    "ipc://%.*s?seq=%llu&value=\"\"&window=%llu",
    options.command.size,
    options.command.bytes,
    seq,
    options.window
  );

  for (int i = 0; i < options.data.length; i += 2) {
    SSCBuffer *key = options.data.tuples[i];
    SSCBuffer *value = options.data.tuples[i + 1];

    if (key != 0 && value != 0) {
      if (key->size > 0 && value->size > 0) {
        SSCSize key_size = ssc_uri_component_encode(&buffer, *key);
        ssc_ipc_write_string(ctx, "&%.*s=", key_size, buffer.bytes);

        SSCSize value_size = ssc_uri_component_encode(&buffer, *value);
        ssc_ipc_write_string(ctx, "%.*s", value_size, buffer.bytes);
      }
    }
  }

  ssc_ipc_flush(ctx);
  return SSC_OK;
}
