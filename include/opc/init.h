#ifndef OPC_INIT_H
#define OPC_INIT_H

#include "platform.h"

/**
 * Enumerated init state values.
 */
typedef enum {
  OPC_INIT_ERROR = -1,
  OPC_INIT_NONE = 0,
  OPC_INIT_PENDING = 1,
  OPC_INIT_READY = 2,
  OPC_INIT_UNKNOWN = OPC_MAX_ENUM
} OPCInitState;

/**
 * @TODO
 */
OPC_EXPORT void
opc_init ();

/**
 * @TODO
 */
OPC_EXPORT OPCInitState
opc_init_state ();

#endif
