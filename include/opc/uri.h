#ifndef OPC_URI_H
#define OPC_URI_H

#include "buffer.h"
#include "platform.h"
#include "result.h"

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCResult
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT long
opc_uri_component_encode_size (const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCResult
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input);

/**
 * @TODO(jwerle)
 */
OPC_EXPORT long
opc_uri_component_decode_size (const OPCBuffer input);
#endif
