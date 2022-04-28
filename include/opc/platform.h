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

#ifndef OPC_PLATFORM_H
#define OPC_PLATFORM_H

/**
 * @TODO
 */
#if defined(_WIN32)
#  define OPC_EXPORT __declspec(dllimport)
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR) >= 303
#  define OPC_EXPORT __attribute__((visibility("default")))
#  define OPC_INLINE inline
#else
#  define OPC_EXPORT
#  define OPC_INLINE
#endif

/**
 * @TODO
 */
#ifndef _WIN32
#  define _POSIX_C_SOURCE 1
#endif

/**
 * @TODO
 */
#ifndef OPC_ALIGNMENT
#  define OPC_ALIGNMENT sizeof(unsigned long) // platform word
#endif

/**
 * @TODO
 */
#ifndef OPC_MAX_ENUM
#  define OPC_MAX_ENUM 0x7FFFFFFF
#endif

/**
 * @TODO
 */
#ifndef OPC_PRINTF
#  include <stdio.h>
#  define OPC_PRINTF printf
#endif

/**
 * @TODO
 */
#ifndef OPC_FPRINTF
#  include <stdio.h>
#  define OPC_FPRINTF fprintf
#endif

/**
 * @TODO
 */
#ifndef OPC_SPRINTF
#  include <stdio.h>
#  define OPC_SPRINTF sprintf
#endif

/**
 * @TODO
 */
#ifndef OPC_SNPRINTF
#  include <stdio.h>
#  define OPC_SNPRINTF snprintf
#endif

/**
 * @TODO
 */
#ifndef OPC_VFPRINTF
#  include <stdarg.h>
#  define OPC_VFPRINTF vfprintf
#endif

/**
 * @TODO
 */
#ifndef OPC_VSPRINTF
#  include <stdarg.h>
#  define OPC_VSPRINTF vsprintf
#endif

/**
 * @TODO
 */
#ifndef OPC_VSNPRINTF
#  include <stdarg.h>
#  define OPC_VSNPRINTF vsnprintf
#endif

/**
 * @TODO
 */
#define opc_bytes(value) (OPCBytes) (value)

/**
 * @TODO
 */
#define opc_size(value) (OPCSize) (value)

/**
 * @TODO
 */
#define opc_usize(value) (OPCUSize) (value)

/**
 * @TODO
 */
#define opc_bool(value) ((value) ? OPC_TRUE : OPC_FALSE)

/**
 * @TODO
 */
#define opc_main()                                                             \
  int start();                                                                 \
  int main(int argc, const char **argv) {                                      \
    opc_init(argc, argv);                                                      \
    return start();                                                            \
  }                                                                            \
  int start()

/**
 * @TODO
 */
typedef unsigned long long OPCUSize;
typedef unsigned char *OPCBytes;
typedef unsigned char OPCByte;
typedef long long OPCSize;

/**
 * @TODO
 */
typedef enum {
  OPC_FALSE = 0,
  OPC_TRUE = 1
} OPCBoolean;

/**
 * @TODO
 */
typedef enum {
  OPC_OFF = 0,
  OPC_ON = 1
} OPCBit;

#endif
