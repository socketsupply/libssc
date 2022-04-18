#include <opc/opc.h>

unsigned long
opc_string_size (const unsigned char *string) {
  const unsigned char *pointer = string;

  while (string != 0 && *string) {
    ++string;
  }

  return string - pointer;
}
