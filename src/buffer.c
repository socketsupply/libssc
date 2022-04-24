#include <opc/opc.h>

OPCBuffer
opc_buffer_slice (const OPCBuffer *self, OPCSize start, OPCSize end) {
  OPCSize size = opc_math_clamp(end - start, 0, self->size);
  OPCSize offset = opc_math_clamp(start, 0, self->size);
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

OPCSize
opc_buffer_write (
  OPCBuffer *self,
  const OPCBufferBytes bytes,
  const OPCSize offset,
  const OPCSize size
) {
  OPCSize written = 0;

  if (offset + size >= self->size) {
    return 0;
  }

  for (OPCSize i = offset; i < offset + size; ++i) {
    self->bytes[i] = bytes[i - offset];
    written = written + 1;
  }

  return written;
}

OPCSize
opc_buffer_write_string (
  OPCBuffer *self,
  const OPCString string,
  const OPCSize offset
) {
  OPCSize size = opc_string_size(string);
  return opc_buffer_write(self, opc_buffer_bytes(string), offset, size);
}
