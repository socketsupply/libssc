#include <opc/opc.h>

OPCBuffer
opc_buffer_slice (const OPCBuffer *self, OPCUSize start, OPCUSize end) {
  OPCUSize size = opc_math_clamp(end - start, 0, self->size);
  OPCUSize offset = opc_math_clamp(start, 0, self->size);
  OPCString bytes = self->bytes + offset;

  return (OPCBuffer) { bytes, size };
}

OPCResult
opc_buffer_compare (const OPCBuffer left, const OPCBuffer right) {
  return opc_string_compare_with_size(
    opc_string((left).bytes),
    (left).size,
    opc_string((right).bytes),
    (right).size
  );
}

OPCUSize
opc_buffer_write (
  OPCBuffer *self,
  const OPCBufferBytes bytes,
  const OPCUSize offset,
  const OPCUSize size
) {
  OPCUSize written = 0;

  if (offset + size >= self->size) {
    return 0;
  }

  for (OPCUSize i = offset; i < offset + size; ++i) {
    self->bytes[i] = bytes[i - offset];
    written = written + 1;
  }

  return written;
}

OPCUSize
opc_buffer_write_string (
  OPCBuffer *self,
  const OPCString string,
  const OPCUSize offset
) {
  OPCUSize size = opc_string_size(string);
  return opc_buffer_write(self, opc_buffer_bytes(string), offset, size);
}
