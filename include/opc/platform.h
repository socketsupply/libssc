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

#include <stdio.h>
#include <stdarg.h>

/**
 * Define `OPC_EXPORT` and `OPC_INLINE` macros
 */
#if defined(_WIN32)
#  define OPC_EXPORT __declspec(dllimport)
#  define OPC_INLINE
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR) >= 303
#  define OPC_EXPORT __attribute__((visibility("default")))
#  define OPC_INLINE inline
#else
#  define OPC_EXPORT
#  define OPC_INLINE
#endif

/**
 * Define source types
 */
#ifndef _WIN32
#  ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 1
#  endif
#  ifndef _DARWIN_C_SOURCE
#    define _DARWIN_C_SOURCE
#  endif
#endif

/**
 * Computed alignment size, a platform "word".
 */
#ifndef OPC_ALIGNMENT
#  define OPC_ALIGNMENT sizeof(unsigned long) // platform word
#endif

/**
 * Define max enum value size.
 */
#ifndef OPC_MAX_ENUM
#  define OPC_MAX_ENUM 0x7FFFFFFF
#endif

/**
 * Define `OPC_EXIT` if compiler has not.
 */
#ifndef OPC_EXIT
#  include <stdlib.h>
#  define OPC_EXIT exit
#endif

/**
 * Define `OPC_PRINTF` if compiler has not.
 */
#ifndef OPC_PRINTF
#  define OPC_PRINTF printf
#endif

/**
 * Define `OPC_FPRINTF` if compiler has not.
 */
#ifndef OPC_FPRINTF
#  define OPC_FPRINTF fprintf
#endif

/**
 * Define `OPC_SPRINTF` if compiler has not.
 */
#ifndef OPC_SPRINTF
#  define OPC_SPRINTF sprintf
#endif

/**
 * Define `OPC_SNPRINTF` if compiler has not.
 */
#ifndef OPC_SNPRINTF
#  define OPC_SNPRINTF snprintf
#endif

/**
 * Define `OPC_VPRINTF` if compiler has not.
 */
#ifndef OPC_VPRINTF
#  define OPC_VPRINTF vprintf
#endif

/**
 * Define `OPC_VFPRINTF` if compiler has not.
 */
#ifndef OPC_VFPRINTF
#  define OPC_VFPRINTF vfprintf
#endif

/**
 * Define `OPC_VSPRINTF` if compiler has not.
 */
#ifndef OPC_VSPRINTF
#  define OPC_VSPRINTF vsprintf
#endif

/**
 * Define `OPC_VSNPRINTF` if compiler has not.
 */
#ifndef OPC_VSNPRINTF
#  define OPC_VSNPRINTF vsnprintf
#endif

/**
 * Cast to library bytes.
 */
#define opc_bytes(value) (OPCBytes) (value)

/**
 * Cast to library byte.
 */
#define opc_byte(value) (OPCByte) (value)

/**
 * Cast to library string.
 */
#define opc_string(value) (OPCString) (value)

/**
 * Cast to library char/
 */
#define opc_char(value) (OPCChar) (value)

/**
 * Cast to static library char array.
 */
#define opc_chars(...) ((OPCChar []) { __VA_ARGS__ })

/**
 * Cast to library signed size value.
 */
#define opc_size(value) (OPCSize) (value)

/**
 * Cast to library unsigned size value.
 */
#define opc_usize(value) (OPCUSize) (value)

/**
 * Cast to library unsigned int value.
 */
#define opc_uint(value) (OPCUInt) (value)

/**
 * Cast to library int value.
 */
#define opc_int(value) (OPCInt) (value)

/**
 * Cast to library boolean.
 */
#define opc_bool(value) ((value) ? OPC_TRUE : OPC_FALSE)

/**
 * Cast to library pointer.
 */
#define opc_pointer(value) ((unsigned long int *) &(value))

/**
 * Cast to library handle (void *).
 */
#define opc_handle(value) (OPCHandle) (value)

/**
 * Helper macro for a libary main function which calls `opc_init()`.
 */
#define opc_main()                                                             \
  int start();                                                                 \
  int main(int argc, const char **argv) {                                      \
    opc_init(argc, argv);                                                      \
    return start();                                                            \
  }                                                                            \
  int start()

/**
 * Library platform types.
 */

typedef unsigned long long OPCUSize;
typedef long long OPCSize;
typedef unsigned char *OPCBytes;
typedef unsigned char OPCByte;
typedef unsigned int OPCUInt;
typedef int OPCInt;
typedef double OPCDouble;
typedef float OPCFloat;
typedef char OPCChar;
typedef char *OPCString;
typedef void *OPCHandle;

/**
 * Libary booleans.
 */
typedef enum {
  OPC_FALSE = 0,
  OPC_TRUE = 1
} OPCBoolean;

/**
 * Libary bits.
 */
typedef enum {
  OPC_OFF = 0,
  OPC_ON = 1
} OPCBit;

#endif
