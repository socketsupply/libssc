#ifndef OPC_BUFFER_H
#define OPC_BUFFER_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * Converts `bytes` to an `OPCBuffer` with `.size` set to `0`.
 * @param bytes
 * @return An `OPCBuffer` structure
 */
#define opc_buffer(bytes) ((OPCBuffer) { (unsigned char *) (bytes), 0 })

/**
 * Converts `value` to a suitable `OPCBuffer` bytes
 * @param value Bytes pointer
 */
#define opc_buffer_bytes(value) (unsigned char *) (value)

/**
 * @TODO
 * @param
 */
#define opc_buffer_from(bytes) ((OPCBuffer) { \
  (unsigned char *) bytes,                    \
  sizeof(bytes)                               \
})

/**
 * @TODO
 * @param string The string
 */
#define opc_buffer_from_string(string) ((OPCBuffer) { \
  (unsigned char *) (string),                         \
  opc_string_size((char *) (string))                  \
})

/**
 * @TODO
 * @param bytes The bytes
 */
#define opc_buffer_from_bytes(bytes, size) ((OPCBuffer) { \
  (unsigned char *) (bytes),                              \
  (unsigned long) size                                    \
})

/**
 * @TODO
 * @param buffer
 */
#define opc_buffer_print(self) { \
  opc_string_printf("%.*s\n",    \
    (int) (self).size,           \
    opc_string((self).bytes)    \
  );                             \
}

/**
 * @TODO(jwerle)
 */
typedef struct OPCBuffer OPCBuffer;
struct OPCBuffer {
  unsigned char *bytes;
  unsigned long size;
};

/**
 * @TODO(jwerle)
 */
OPC_EXPORT OPCBuffer
opc_buffer_slice (
  const OPCBuffer *input,
  unsigned long start,
  unsigned long end
);

/**
 * @TODO
 * @param left
 * @param right
 */
OPC_EXPORT OPCResult
opc_buffer_compare (
  const OPCBuffer left,
  const OPCBuffer right
);

/**
 * @TODO
 */
OPC_EXPORT unsigned long
opc_buffer_write (
  OPCBuffer *left,
  const unsigned char *string,
  const unsigned long offset,
  const unsigned long size
);

/**
 * @TODO
 */
OPC_EXPORT unsigned long
opc_buffer_write_string (
  OPCBuffer *left,
  const unsigned char *string,
  const unsigned long offset
);

#endif
