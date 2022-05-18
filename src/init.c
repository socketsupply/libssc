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

#include "internal.h"

// state
static OPCInitState state = OPC_INIT_NONE;

// program
static int argc = 0;
static const char **argv = 0;

// streams
static OPCHandle stdin_stream;
static OPCHandle stdout_stream;
static OPCHandle stderr_stream;

void
opc_init_library (
  OPCHandle init_stdin_stream,
  OPCHandle init_stdout_stream,
  OPCHandle init_stderr_stream,
  const int init_argc,
  const char **init_argv
) {
  if (state == OPC_INIT_NONE) {
    state = OPC_INIT_PENDING;
    argc = init_argc;
    argv = init_argv;
    stdin_stream = init_stdin_stream;
    stdout_stream = init_stdout_stream;
    stderr_stream = init_stderr_stream;
    opc_log_set_file_stream_pointer(init_stderr_stream);
    state = OPC_INIT_READY;
  }
}

OPCInitState
opc_init_state () {
  return state;
}

const int
opc_init_argc () {
  return argc;
}

const char **
opc_init_argv () {
  return argv;
}

const OPCHandle
opc_init_stdin () {
  return stdin_stream;
}

const OPCHandle
opc_init_stdout () {
  return stdout_stream;
}

const OPCHandle
opc_init_stderr () {
  return stderr_stream;
}
