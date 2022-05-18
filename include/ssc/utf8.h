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

#ifndef SSC_UTF8_H
#define SSC_UTF8_H

#include "buffer.h"
#include "platform.h"
#include "result.h"

/**
 * Detects if `input` is UTF-8
 * @param input The input buffer to detect UTF-8
 * @return Returns an `SSC_RESULT` value:
 *   * `SSC_OUT_OF_MEMORY` - Input size was 0
 *   * `SSC_OUT_OF_BOUNDS` - Input contained characters out of bounds
 *   * `SSC_NULL_POINTER` - Input was null pointer
 *   * `SSC_NOT_DETECTED` - UTF-8 was not detected in input
 *   * `SSC_DETECTED`     - UTF-8 was detected in input
 */
SSC_EXPORT SSCResult
ssc_utf8_detect (const SSCBuffer input);

#endif
