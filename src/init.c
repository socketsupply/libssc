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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#include <flag/flag.h>
#include <opc/opc.h>

static OPCInitState init_state = OPC_INIT_NONE;
static int init_argc = 0;
static const char **init_argv = 0;

OPCInitState
opc_init_state () {
  return init_state;
}

void
opc_init_library (
  void *stdin_stream,
  void *stdout_stream,
  void *stderr_stream,
  const int argc,
  const char **argv
) {
  if (init_state == OPC_INIT_NONE) {
    init_state = OPC_INIT_PENDING;
    init_argc = argc;
    init_argv = argv;
    opc_log_set_file_stream_pointer(stderr_stream);
    init_state = OPC_INIT_READY;
  }
}

const int
opc_init_argc () {
  return init_argc;
}

const char **
opc_init_argv () {
  return init_argv;
}
