#include <opc/opc.h>

OPCBuffer
opc_buffer_slice (
  OPCBuffer *input,
  unsigned long start,
  unsigned long end
) {
	unsigned long size = opc_math_clamp(end - start, 0, input->size);
	unsigned long offset = opc_math_clamp(start, 0, input->size);
	unsigned char *buffer = input->buffer + offset;

	return (OPCBuffer) { buffer, size };
}
