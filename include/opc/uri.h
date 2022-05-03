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

#ifndef OPC_URI_H
#define OPC_URI_H

#include "buffer.h"
#include "platform.h"
#include "result.h"

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCSize
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCSize
opc_uri_component_encode_size (const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCSize
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCSize
opc_uri_component_decode_size (const OPCBuffer input);
#endif
