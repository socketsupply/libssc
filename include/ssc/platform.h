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

#ifndef SSC_PLATFORM_H
#define SSC_PLATFORM_H

#include <stdio.h>
#include <stdarg.h>

/**
 * Define `SSC_EXPORT` and `SSC_INLINE` macros
 */
#if defined(_WIN32)
#  define SSC_EXPORT __declspec(dllimport)
#  define SSC_INLINE
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR) >= 303
#  define SSC_EXPORT __attribute__((visibility("default")))
#  define SSC_INLINE inline
#else
#  define SSC_EXPORT
#  define SSC_INLINE
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
#ifndef SSC_ALIGNMENT
#  define SSC_ALIGNMENT sizeof(unsigned long) // platform word
#endif

/**
 * Define max enum value size.
 */
#ifndef SSC_MAX_ENUM
#  define SSC_MAX_ENUM 0x7FFFFFFF
#endif

/**
 * Define `SSC_EXIT` if compiler has not.
 */
#ifndef SSC_EXIT
#  include <stdlib.h>
#  define SSC_EXIT exit
#endif

/**
 * Define `SSC_PRINTF` if compiler has not.
 */
#ifndef SSC_PRINTF
#  define SSC_PRINTF printf
#endif

/**
 * Define `SSC_FPRINTF` if compiler has not.
 */
#ifndef SSC_FPRINTF
#  define SSC_FPRINTF fprintf
#endif

/**
 * Define `SSC_SPRINTF` if compiler has not.
 */
#ifndef SSC_SPRINTF
#  define SSC_SPRINTF sprintf
#endif

/**
 * Define `SSC_SNPRINTF` if compiler has not.
 */
#ifndef SSC_SNPRINTF
#  define SSC_SNPRINTF snprintf
#endif

/**
 * Define `SSC_VPRINTF` if compiler has not.
 */
#ifndef SSC_VPRINTF
#  define SSC_VPRINTF vprintf
#endif

/**
 * Define `SSC_VFPRINTF` if compiler has not.
 */
#ifndef SSC_VFPRINTF
#  define SSC_VFPRINTF vfprintf
#endif

/**
 * Define `SSC_VSPRINTF` if compiler has not.
 */
#ifndef SSC_VSPRINTF
#  define SSC_VSPRINTF vsprintf
#endif

/**
 * Define `SSC_VSNPRINTF` if compiler has not.
 */
#ifndef SSC_VSNPRINTF
#  define SSC_VSNPRINTF vsnprintf
#endif

/**
 * Cast to library bytes.
 */
#define ssc_bytes(value) (SSCBytes) (value)

/**
 * Cast to library byte.
 */
#define ssc_byte(value) (SSCByte) (value)

/**
 * Cast to library string.
 */
#define ssc_string(value) (SSCString) (value)

/**
 * Cast to library char/
 */
#define ssc_char(value) (SSCChar) (value)

/**
 * Cast to static library char array.
 */
#define ssc_chars(...) ((SSCChar []) { __VA_ARGS__ })

/**
 * Cast to library signed size value.
 */
#define ssc_size(value) (SSCSize) (value)

/**
 * Cast to library unsigned size value.
 */
#define ssc_usize(value) (SSCUSize) (value)

/**
 * Cast to library unsigned int value.
 */
#define ssc_uint(value) (SSCUInt) (value)

/**
 * Cast to library int value.
 */
#define ssc_int(value) (SSCInt) (value)

/**
 * Cast to library boolean.
 */
#define ssc_bool(value) ((value) ? SSC_TRUE : SSC_FALSE)

/**
 * Cast to library pointer.
 */
#define ssc_pointer(value) ((SSCByte *) &(value))

/**
 * Cast to library pointer at `offset`.
 */
#define ssc_pointer_at(value, offset) ((SSCByte *) &(value)) + offset

/**
 * Cast to library handle (void *).
 */
#define ssc_handle(value) (SSCHandle) (value)

/**
 * `offsetof` library function.
 */
#define ssc_offsetof(type, property) ((SSCSize) & (((type *) 0)->property))

/**
 * Write `byte to `pointer`.
 */
#define ssc_byte_write(pointer, byte) *(SSCUSize *) ((pointer)) = (byte)

/**
 * Write `byte` to `pointer` at `offset`.
 */
#define ssc_byte_write_at(pointer, byte, offset)                               \
  ssc_byte_write(((pointer) + (offset)), byte)

/**
 * Helper macro for a libary main function which calls `ssc_init()`.
 */
#define ssc_main()                                                             \
  int start();                                                                 \
  int main(int argc, const char **argv) {                                      \
    ssc_init(argc, argv);                                                      \
    return start();                                                            \
  }                                                                            \
  int start()

/**
 * Library platform types.
 */

typedef unsigned long long SSCUSize;
typedef long long SSCSize;
typedef unsigned char *SSCBytes;
typedef unsigned char SSCByte;
typedef unsigned int SSCUInt;
typedef int SSCInt;
typedef double SSCDouble;
typedef float SSCFloat;
typedef unsigned char SSCUChar;
typedef char SSCChar;
typedef char *SSCString;
typedef void *SSCHandle;

/**
 * Libary booleans.
 */
typedef enum {
  SSC_FALSE = 0,
  SSC_TRUE = 1
} SSCBoolean;

/**
 * Libary bits.
 */
typedef enum {
  SSC_OFF = 0,
  SSC_ON = 1
} SSCBit;

#endif
