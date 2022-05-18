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

static SSCByte memory[4096] = { 0 };

int
main (int argc, const char **argv) {
  SSCIPCContext ctx = { 0 };
  SSCBuffer file = ssc_buffer_from(memory, 1024);
  SSCBuffer *title[] = { &ssc_buffer_from_string("value"),
                         &ssc_buffer_from_string("Hello World from libssc") };

  SSCBuffer *navigate[] = { &ssc_buffer_from_string("value"), &file };

  ssc_init(argc, argv);
  ssc_ipc_context_init(&ctx);

  file.size = // NOLINTNEXTLINE
    ssc_string_format(ssc_string(file.bytes), "file://%s/index.html", ctx.cwd);

  for (int i = 0; i < argc; i++) {
    ssc_log_debug("%s", argv[i]);
  }

  ssc_ipc_request(
    &ctx,
    (SSCIPCRequestOptions) {
      .window = 0,
      .data = { title, 2 },
      .command = ssc_buffer_from_string("title"),
    }
  );

  ssc_ipc_request(
    &ctx,
    (SSCIPCRequestOptions) {
      .window = 0,
      .command = ssc_buffer_from_string("show"),
    }
  );

  ssc_ipc_request(
    &ctx,
    (SSCIPCRequestOptions) {
      .window = 0,
      .data = { navigate, 2 },
      .command = ssc_buffer_from_string("navigate"),
    }
  );

  return 0;
}
