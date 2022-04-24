#ifndef OPC_RESULT_H
#define OPC_RESULT_H

#include "platform.h"

/**
 * Enumerated result types for various `libopc` function
 * return values.
 */
typedef enum {
  OPC_OUT_OF_BOUNDS = -4,
  OPC_OUT_OF_MEMORY = -3,
  OPC_NULL_POINTER = -2,
  OPC_ERROR = -1,

  OPC_OK = 0,
  OPC_DETECTED = 10,
  OPC_NOT_DETECTED = 11,
  OPC_UNKNOWN = OPC_MAX_ENUM
} OPCResult;

/**
 * @TODO(jwerle)
 */
OPC_EXPORT const char * // OPCString
opc_result_string (const OPCResult result);

#endif
