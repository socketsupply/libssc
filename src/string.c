#include <opc/opc.h>

unsigned long
opc_string_size (const char *string) {
  const char *pointer = string;

  while (string != 0 && *string) {
    ++string;
  }

  return string - pointer;
}

int
opc_string_compare (
  const char *left,
  const char *right
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
  const char *left,
  unsigned long left_size,
  const char *right,
  unsigned long right_size
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

  for (
    int i = 0;
    (left[i] != 0 || right[i] != 0) && i < left_size && i < right_size;
    ++i
  ) {
    if (left[i] < right[i]) {
      return -1;
    }

    if (left[i] > right[i]) {
      return 1;
    }
  }

  return 0;
}
