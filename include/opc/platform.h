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
typedef unsigned long long OPCSize;

/**
 * @TODO
 */
typedef enum {
  OPC_FALSE = 0,
  OPC_TRUE = 1
} OPCBoolean;

#endif
