#ifndef OPC_BUFFER_H
#define OPC_BUFFER_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * @TODO
 */
typedef unsigned char *OPCBufferBytes;

/**
 * @TODO(jwerle)
 */
typedef struct OPCBuffer OPCBuffer;

struct OPCBuffer {
  OPCBufferBytes bytes;
  OPCUSize size;
};

/**
 * Converts `bytes` to an `OPCBuffer` with `.size` set to `0`.
 * @param bytes
 * @return An `OPCBuffer` structure
 */
#define opc_buffer(bytes) ((OPCBuffer) { (OPCBufferBytes) (bytes), 0 })

/**
 * Converts `value` to a suitable `OPCBuffer` bytes
 * @param value Bytes pointer
 */
#define opc_buffer_bytes(value) (OPCBufferBytes)(value)

/**
 * @TODO
 * @param
 */
#define opc_buffer_from(bytes)                                                 \
  ((OPCBuffer) { (OPCBufferBytes) bytes, sizeof(bytes) })

/**
 * @TODO
 * @param string The string
 */
#define opc_buffer_from_string(string)                                         \
  ((OPCBuffer) { (OPCBufferBytes) (string),                                    \
                 opc_string_size((char *) (string)) })

/**
 * @TODO
 * @param bytes The bytes
 */
#define opc_buffer_from_bytes(bytes, size)                                     \
  ((OPCBuffer) { (OPCBufferBytes) (bytes), (OPCUSize) size })

/**
 * @TODO
 * @param buffer
 */
#define opc_buffer_print(self)                                                 \
  opc_string_printf("%.*s\n", (int) (self).size, opc_string((self).bytes))

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCBuffer
opc_buffer_slice (const OPCBuffer *input, OPCUSize start, OPCUSize end);

/**
 * @TODO
 * @param left
 * @param right
 */
OPC_EXPORT OPCResult
opc_buffer_compare (const OPCBuffer left, const OPCBuffer right);

/**
 * @TODO
 */
OPC_EXPORT OPCUSize
opc_buffer_write (
  OPCBuffer *left,
  const OPCBufferBytes string,
  const OPCUSize offset,
  const OPCUSize size
);

/**
 * @TODO
 */
OPC_EXPORT OPCUSize
opc_buffer_write_string (
  OPCBuffer *left,
  const OPCString string,
  const OPCUSize offset
);

#endif
