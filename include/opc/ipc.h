#ifndef OPC_IPC_H
#define OPC_IPC_H

#include "buffer.h"
#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * @TODO
 */
typedef struct OPCIPCSendOptions OPCIPCSendOptions;
struct OPCIPCSendOptions {
  const OPCUSize window;
  const OPCString event;
  const OPCBuffer value;
};

/**
 * @TODO
 */
typedef struct OPCIPCRequestData OPCIPCRequestData;
struct OPCIPCRequestData {
  const OPCString key;
  const OPCBuffer value;
};

/**
 * @TODO
 */
typedef struct OPCIPCRequestOptions OPCIPCRequestOptions;
struct OPCIPCRequestOptions {
  const OPCUSize window;
  const OPCBuffer value;
  const OPCIPCRequestData **data;
  const OPCUSize data_count;
};

/**
 * @TODO
 */
OPC_EXPORT OPCResult
opc_ipc_write (const OPCString string, ...);

/**
 * @TODO
 */
OPC_EXPORT OPCResult
opc_ipc_flush (const OPCString string, ...);

/**
 * @TODO
 */
OPC_EXPORT OPCResult
opc_ipc_send (const OPCIPCSendOptions options);

/**
 * @TODO
 */
OPC_EXPORT OPCResult
opc_ipc_request (const OPCIPCRequestOptions options);

#endif
