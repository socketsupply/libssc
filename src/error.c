#include <opc/opc.h>

struct Error {
  OPCResult code;
  const char *message;
};

static struct Error errors[] = {
  { 0, "No error." },
  { OPC_ERROR, "An error occurred." },
  { OPC_NULL_POINTER, "NULL pointer reference." },
  { OPC_OUT_OF_MEMORY, "Ran out of memory." },
  { OPC_OUT_OF_BOUNDS, "Read out of bounds" }
};

const char *
opc_error_string (OPCResult error) {
  unsigned long count = sizeof(errors) / sizeof(struct Error);

  for (int i = 0; i < count; ++i) {
    if (errors[i].code == error) {
      return errors[i].message;
    }
  }

  return errors[0].message;
}
