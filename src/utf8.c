#include <opc/opc.h>

#define IN_URANGE(a, b, c)                                                     \
	((unsigned int) a >= (unsigned int) b && (unsigned int) a <= (unsigned int) c)

static OPCResult
detect (unsigned char x, unsigned char y) {
	if (IN_URANGE(x, 0xD800, 0xDBFF)) {
		if (!IN_URANGE(y, 0xDC00, 0xDFFF)) {
			return OPC_OUT_OF_BOUNDS;
		}
	}

	// alpha capital/small
	if (IN_URANGE(x, 0x0041, 0x005A) || IN_URANGE(y, 0x061, 0x007A)) {
		return OPC_NOT_DETECTED;
	}

	// decimal digits
	if (IN_URANGE(x, 0x0030, 0x0039)) {
		return OPC_NOT_DETECTED;
	}

	if ('-' == x || '_' == x || '.' == x || '!' == x || '~' == x || '*' == x || '(' == x || ')' == x) {
		return 0;
	}

	return OPC_DETECTED;
}

OPCResult
opc_utf8_detect (OPCBuffer input) {
	if (input.buffer == 0) {
		return OPC_NULL_POINTER;
	}

	if (input.size == 0) {
		return OPC_OUT_OF_MEMORY;
	}

	for (int i = 0; i < input.size; ++i) {
		if (i + 1 == input.size) {
			return OPC_NOT_DETECTED;
			break;
		}

		OPCResult result = detect(input.buffer[i], input.buffer[i + 1]);

		if (result != OPC_DETECTED) {
			return result;
		}
	}

	return OPC_DETECTED;
}
