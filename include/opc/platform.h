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
#define opc_argc opc_init_argc

/**
 * @TODO
 */
#define opc_argv opc_init_argv

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

#endif
