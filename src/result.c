#include <opc/opc.h>

struct Result {
	OPCResult code;
	const char *string;
};

static struct Result results[] = {
	{ OPC_OUT_OF_BOUNDS, "OUT_OF_BOUNDS" },
	{ OPC_OUT_OF_MEMORY, "OUF_OF_MEMORY" },
	{ OPC_NULL_POINTER, "NULL_POINTER" },
	{ OPC_ERROR, "OPC_ERROR" },
	{ OPC_OK, "OPC_OK" },
	{ OPC_DETECTED, "OPC_DETECTED" },
	{ OPC_NOT_DETECTED, "OPC_NOT_DETECTED" },
	{ OPC_UNKNOWN, "OPC_UNKNOWN" }
};

const char *
opc_result_string (OPCResult result) {
	unsigned long count = sizeof(results) / sizeof(struct Result);

	for (int i = 0; i < count; ++i) {
		if (results[i].code == result) {
			return results[i].string;
		}
	}

	return results[count - 2].string;
}
