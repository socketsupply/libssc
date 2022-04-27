#include <opc/opc.h>

struct Result {
  const OPCResult code;
  const OPCString string;
};

// clang-format off
static struct Result results[] = {
  { OPC_OUT_OF_BOUNDS, "OPC_OUT_OF_BOUNDS" },
  { OPC_OUT_OF_MEMORY, "OPC_OUT_OF_MEMORY" },
  { OPC_NULL_POINTER, "OPC_NULL_POINTER" },
  { OPC_ERROR, "OPC_ERROR" },
  { OPC_OK, "OPC_OK" },
  { OPC_DETECTED, "OPC_DETECTED" },
  { OPC_NOT_DETECTED, "OPC_NOT_DETECTED" },
  { OPC_UNKNOWN, "OPC_UNKNOWN" }
};

// clang-format on

const OPCString
opc_result_string (const OPCResult result) {
  unsigned long count = sizeof(results) / sizeof(struct Result);

  for (int i = 0; i < count; ++i) {
    if (results[i].code == result) {
      return results[i].string;
    }
  }

  return results[count - 1].string;
}
