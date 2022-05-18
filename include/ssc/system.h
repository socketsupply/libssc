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

#ifndef SSC_SYSTEM_H
#define SSC_SYSTEM_H

#include "ipc.h"
#include "platform.h"
#include "result.h"
#include "window.h"

/**
 * Maximum windows managed by a system instance.
 */
#ifndef SSC_SYSTEM_MAX_WINDOWS
#define SSC_SYSTEM_MAX_WINDOWS 32
#endif

/**
 * A container for `SSCSystem` initialization configuration.
 */
typedef struct SSCSystemConfiguration SSCSystemConfiguration;
struct SSCSystemConfiguration {
  SSCUSize window_index_offset;
};

/**
 * A container for an initialized "system" container interface.
 */
typedef struct SSCSystem SSCSystem;
struct SSCSystem {
  SSCIPCContext ipc;
  SSCWindow windows[SSC_SYSTEM_MAX_WINDOWS];
  SSCSystemConfiguration configuration;
};

/**
 * @TODO
 * @return `SSCSystemConfiguration` with defaults
 */
#define ssc_system_default_configuration()                                     \
  ((SSCSystemConfiguration) { .window_index_offset = 0 })

/**
 * Initializes an `SSCSystem` instance.
 * @param system
 * @return `OCP_OK` upon success, otherwise an error.
 */
SSC_EXPORT SSCResult
ssc_system_init (SSCSystem *system, const SSCSystemConfiguration configuration);

/**
 * @TODO
 * @param system
 * @return `OCP_OK` upon success, otherwise an error.
 */
SSC_EXPORT SSCResult
ssc_system_send (SSCSystem *system, const SSCWindow window);

/**
 * @TODO
 * @param system
 * @return `OCP_OK` upon success, otherwise an error.
 */
SSC_EXPORT SSCResult
ssc_system_request (SSCSystem *system);

#endif
