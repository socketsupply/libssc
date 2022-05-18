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

#ifndef SSC_INIT_H
#define SSC_INIT_H

#include "platform.h"

/**
 * Enumerated init state values.
 */
typedef enum {
  SSC_INIT_ERROR = -1,
  SSC_INIT_NONE = 0,
  SSC_INIT_PENDING = 1,
  SSC_INIT_READY = 2,
  SSC_INIT_UNKNOWN = SSC_MAX_ENUM
} SSCInitState;

/**
 * Initializes the `libssc` library with command line arguments suitable for
 * custom configuration provided by the shell caller. The default `stdin`,
 * `stdout`, and `stderr` file stream pointers are used. Callers who want to use
 * custom file stream pointers should call `ssc_init_library()` directly
 * instead.
 * @param argc The argument count as given to `main()`
 * @param argv The argument vector pointer as given to `main()`
 */
#define ssc_init(argc, argv) ssc_init_library(stdin, stdout, stderr, argc, argv)

/**
 * Initializes the `libssc` library with command line arguments suitable for
 * custom configuration provided by the shell caller.
 * @param stdin_stream The stdin stream pointer
 * @param stdout_stream The stdout stream pointer
 * @param stderr_stream The stdout stream pointer
 * @param argc The argument count as given to `main()`
 * @param argv The argument vector pointer as given to `main()`
 */
SSC_EXPORT void
ssc_init_library (
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
SSC_EXPORT SSCInitState
ssc_init_state ();

/**
 * Returns the initialized argument count given to `ssc_init()`.
 * @return The argument count
 */
SSC_EXPORT const int
ssc_init_argc ();

/**
 * Returns the initialized arguments vector pointer given to `ssc_init()`.
 * @return A pointer to the argument vector
 */
SSC_EXPORT const char **
ssc_init_argv ();

/**
 * Returns handle to stdin stream.
 * @return A `stdin` pointer
 */
SSC_EXPORT const SSCHandle
ssc_init_stdin ();

/**
 * Returns handle to stdout stream.
 * @return A `stdout` pointer
 */
SSC_EXPORT const SSCHandle
ssc_init_stdout ();

/**
 * Returns handle to stderr stream.
 * @return A `stderr` pointer
 */
SSC_EXPORT const SSCHandle
ssc_init_stderr ();

#endif
