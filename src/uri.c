#include <opc/opc.h>

OPCResult
opc_uri_component_encode (OPCBuffer output, OPCBuffer input) {
	return OPC_OK;
}

unsigned long
opc_uri_component_encode_size (OPCBuffer input) {
	unsigned long size = 0;

	if (input.buffer == 0 || input.size == 0) {
		return 0;
	}

	for (int i = 0; i < input.size; ++i) {
		switch (opc_utf8_detect(opc_buffer_slice(&input, i, i + 1))) {
			default: break;
		}
	}

	return size;
}

OPCResult
opc_uri_component_decode (OPCBuffer output, OPCBuffer input) {
	return OPC_OK;
}

unsigned long
opc_uri_component_decode_size (OPCBuffer input) {
	unsigned long size = 0;

	if (input.buffer == 0 || input.size == 0) {
		return 0;
	}

	return size;
}
