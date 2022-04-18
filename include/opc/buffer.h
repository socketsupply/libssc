#ifndef OPC_BUFFER_H
#define OPC_BUFFER_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * @param string The string
 */
#define opc_buffer_from_string(string) ((OPCBuffer) { \
  (unsigned char *) string,                           \
  opc_string_size((unsigned char *) string)           \
})

/**
 * @TODO(jwerle)
 */
typedef struct OPCBuffer OPCBuffer;
struct OPCBuffer {
  unsigned char *buffer;
  unsigned long size;
};

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCBuffer
opc_buffer_slice (
  OPCBuffer *input,
  unsigned long start,
  unsigned long end
);

#endif
