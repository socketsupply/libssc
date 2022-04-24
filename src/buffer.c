#include <opc/opc.h>

OPCBuffer
opc_buffer_slice (
  const OPCBuffer *self,
  unsigned long start,
  unsigned long end
) {
  unsigned long size = opc_math_clamp(end - start, 0, self->size);
  unsigned long offset = opc_math_clamp(start, 0, self->size);
  unsigned char *bytes = self->bytes + offset;

  return (OPCBuffer) { bytes, size };
}

OPCResult
opc_buffer_compare (const OPCBuffer left, const OPCBuffer right) {
  return opc_string_compare_with_size(
    opc_string((left).bytes), (left).size, opc_string((right).bytes),
    (right).size
  );
}

unsigned long
opc_buffer_write (
  OPCBuffer *self,
  const unsigned char *string,
  const unsigned long offset,
  const unsigned long size
) {
  unsigned long written = 0;

  if (offset + size >= self->size) {
    return 0;
  }

  for (int i = offset; i < offset + size; ++i) {
    self->bytes[i] = string[i - offset];
    written = written + 1;
  }

  return written;
}

unsigned long
opc_buffer_write_string (
  OPCBuffer *self,
  const unsigned char *string,
  const unsigned long offset
) {
  unsigned long size = opc_string_size(string);
  return opc_buffer_write(self, string, offset, size);
}
