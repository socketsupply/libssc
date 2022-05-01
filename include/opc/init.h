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

#ifndef OPC_INIT_H
#define OPC_INIT_H

#include "platform.h"

/**
 * Enumerated init state values.
 */
typedef enum {
  OPC_INIT_ERROR = -1,
  OPC_INIT_NONE = 0,
  OPC_INIT_PENDING = 1,
  OPC_INIT_READY = 2,
  OPC_INIT_UNKNOWN = OPC_MAX_ENUM
} OPCInitState;

/**
 * Initializes the `libopc` library with command line arguments suitable for
 * custom configuration provided by the shell caller. The default `stdin`,
 * `stdout`, and `stderr` file stream pointers are used. Callers who want to use
 * custom file stream pointers should call `opc_init_library()` directly
 * instead.
 * @param argc The argument count as given to `main()`
 * @param argv The argument vector pointer as given to `main()`
 */
#define opc_init(argc, argv) opc_init_library(stdin, stdout, stderr, argc, argv)

/**
 * Initializes the `libopc` library with command line arguments suitable for
 * custom configuration provided by the shell caller.
 * @param stdin_stream The stdin stream pointer
 * @param stdout_stream The stdout stream pointer
 * @param stderr_stream The stdout stream pointer
 * @param argc The argument count as given to `main()`
 * @param argv The argument vector pointer as given to `main()`
 */
OPC_EXPORT void
opc_init_library (
  void *stdin_stream,
  void *stdout_stream,
  void *stderr_stream,
  const int argc,
  const char **argv
);

/**
 * Returns the current library initialization state.
 * @return The current initialization state
 */
OPC_EXPORT OPCInitState
opc_init_state ();

/**
 * Returns the initialized argument count given to `opc_init()`.
 * @return The argument count
 */
OPC_EXPORT const int
opc_init_argc ();

/**
 * Returns the initialized arguments vector pointer given to `opc_init()`.
 * @return A pointer to the argument vector
 */
OPC_EXPORT const char **
opc_init_argv ();

/**
 * @TODO
 */
OPC_EXPORT void *
opc_init_stdin ();

/**
 * @TODO
 */
OPC_EXPORT void *
opc_init_stdout ();

/**
 * @TODO
 */
OPC_EXPORT void *
opc_init_stderr ();

#endif
