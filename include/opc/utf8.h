#ifndef OPC_UTF8_H
#define OPC_UTF8_H

#include "platform.h"
#include "buffer.h"
#include "result.h"

/**
 * Detects if `input` is UTF-8
 * @param input The input buffer to detect UTF-8
 * @return Returns an `OPC_RESULT` value:
 *   * `OPC_OUT_OF_MEMORY` - Input size was 0
 *   * `OPC_OUT_OF_BOUNDS` - Input contained characters out of bounds
 *   * `OPC_NULL_POINTER` - Input was null pointer
 *   * `OPC_NOT_DETECTED` - UTF-8 was not detected in input
 *   * `OPC_DETECTED`     - UTF-8 was detected in input
 */
OPC_EXPORT OPCResult
opc_utf8_detect (const OPCBuffer input);

#endif
