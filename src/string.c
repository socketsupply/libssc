#include <opc/opc.h>

OPCUSize
opc_string_size (const OPCString string) {
  const OPCString pointer = string;
  OPCString ref = string;

  while (ref != 0 && *ref) {
    ++ref;
  }

  return ref - pointer;
}

int
opc_string_compare (const OPCString left, const OPCString right) {
  if (left == 0 && right == 0) {
    return 0;
  }

  if (left == 0 && right != 0) {
    return -1;
  }

  if (left != 0 && right == 0) {
    return 1;
  }

  for (int i = 0; left[i] != 0 || right[i] != 0; ++i) {
    if (left[i] < right[i]) {
      return -1;
    }

    if (left[i] > right[i]) {
      return 1;
    }
  }

  return 0;
}

int
opc_string_compare_with_size (
  const OPCString left,
  const OPCUSize left_size,
  const OPCString right,
  const OPCUSize right_size
) {
  if (left == 0 && right == 0) {
    return 0;
  }

  if (left == 0 && right != 0) {
    return -1;
  }

  if (left != 0 && right == 0) {
    return 1;
  }

  for (int i = 0; i < left_size && i < right_size; ++i) {
    if (left[i] < right[i]) {
      return -1;
    }

    if (left[i] > right[i]) {
      return 1;
    }
  }

  return 0;
}

const OPCString
opc_string_slice (const OPCString self, const OPCUSize offset) {
  if (self == 0) {
    return 0;
  }

  return self + offset;
}

OPCBoolean
opc_string_equals (const OPCString left, const OPCString right) {
  return opc_string_compare(left, right) == 0 ? OPC_TRUE : OPC_FALSE;
}
