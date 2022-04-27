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
 * @TODO
 */
OPC_EXPORT void
opc_init (int argc, const char **argv);

/**
 * @TODO
 */
OPC_EXPORT OPCInitState
opc_init_state ();

/**
 * @TODO
 */
int
opc_init_argc ();

/**
 * @TODO
 */
const char **
opc_init_argv ();

#endif
