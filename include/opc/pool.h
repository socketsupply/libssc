#ifndef OPC_POOL_H
#define OPC_POOL_H

#include "platform.h"
#include "result.h"

typedef struct OPCPool OPCPool;
struct OPCPool {
  void *internal;
};

/**
 * @TODO
 */
OPC_EXPORT OPCResult
opc_pool_init (void (*alloc)(unsigned long long), void (free)(void *));
#endif
