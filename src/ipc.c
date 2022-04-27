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

void
ipc_flush () {
  OPC_FPRINTF(stdout, "\n");
}

OPCResult
opc_ipc_vwrite (const OPCString string, va_list args) {
  if (string != 0) {
    OPC_VFPRINTF(stdout, string, args);
  }
}

OPCResult
opc_ipc_write (const OPCString string, ...) {
  va_list args;

  va_start(args, string);
  opc_ipc_vwrite(string, args);
  va_end(args);

  return OPC_OK;
}

OPCResult
opc_ipc_flush (const OPCString string, ...) {
  va_list args;

  va_start(args, string);
  opc_ipc_vwrite(string, args);
  ipc_flush();
  va_end(args);

  return OPC_OK;
}

OPCResult
opc_ipc_send (const OPCIPCSendOptions options) {
  if (options.event == 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Missing options.event");
  }

  if (options.value.size > 0 && options.value.bytes != 0) {
    return opc_ipc_write(
      "ipc://send?window=%llu&event=%s&value=%*.s\n",
      options.window,
      options.event,
      options.value.size,
      opc_string(options.value.bytes)
    );
  }

  return opc_ipc_write(
    "ipc://send?window=%llu&event=%s\n",
    options.window,
    options.event
  );
}

OPCResult
opc_ipc_request (const OPCIPCRequestOptions options) {
  return OPC_OK;
}
