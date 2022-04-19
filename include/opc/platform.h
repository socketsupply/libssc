#ifndef OPC_PLATFORM_H
#define OPC_PLATFORM_H

#if defined(_WIN32)
#  define OPC_EXPORT __declspec(dllimport)
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR) >= 303
#  define OPC_EXPORT __attribute__((visibility("default")))
#  define OPC_INLINE inline
#else
#  define OPC_EXPORT
#  define OPC_INLINE
#endif

#ifndef OPC_ALIGNMENT
#  define OPC_ALIGNMENT sizeof(unsigned long) // platform word
#endif

#ifndef OPC_MAX_ENUM
#  define OPC_MAX_ENUM 0x7FFFFFFF
#endif

#ifndef OPC_PRINTF
#include <stdio.h>
#define OPC_PRINTF printf
#endif

#ifndef OPC_FPRINTF
#include <stdio.h>
#define OPC_FPRINTF fprintf
#endif

#endif
