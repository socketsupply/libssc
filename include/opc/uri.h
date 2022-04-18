#ifndef OPC_URI_H
#define OPC_URI_H

#include "platform.h"
#include "buffer.h"
#include "result.h"

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCResult
opc_uri_component_encode (OPCBuffer output, OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT unsigned long
opc_uri_component_encode_size (OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCResult
opc_uri_component_decode (OPCBuffer output, OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT unsigned long
opc_uri_component_decode_size (OPCBuffer input);
#endif
