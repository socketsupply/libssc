#ifndef OPC_ERROR_H
#define OPC_ERROR_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * @TODO(jwerle)
 */
OPC_EXPORT const OPCString
opc_error_string (OPCResult error);

#endif
