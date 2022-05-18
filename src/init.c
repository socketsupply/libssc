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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#include <flag/flag.h>
#include <ssc/ssc.h>

#include "internal.h"

// state
static SSCInitState state = SSC_INIT_NONE;

// program
static int argc = 0;
static const char **argv = 0;

// streams
static SSCHandle stdin_stream;
static SSCHandle stdout_stream;
static SSCHandle stderr_stream;

void
ssc_init_library (
  SSCHandle init_stdin_stream,
  SSCHandle init_stdout_stream,
  SSCHandle init_stderr_stream,
  const int init_argc,
  const char **init_argv
) {
  if (state == SSC_INIT_NONE) {
    state = SSC_INIT_PENDING;
    argc = init_argc;
    argv = init_argv;
    stdin_stream = init_stdin_stream;
    stdout_stream = init_stdout_stream;
    stderr_stream = init_stderr_stream;
    ssc_log_set_file_stream_pointer(init_stderr_stream);
    state = SSC_INIT_READY;
  }
}

SSCInitState
ssc_init_state () {
  return state;
}

const int
ssc_init_argc () {
  return argc;
}

const char **
ssc_init_argv () {
  return argv;
}

const SSCHandle
ssc_init_stdin () {
  return stdin_stream;
}

const SSCHandle
ssc_init_stdout () {
  return stdout_stream;
}

const SSCHandle
ssc_init_stderr () {
  return stderr_stream;
}
