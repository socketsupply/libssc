#ifndef OPC_STRING_H
#define OPC_STRING_H

#include "platform.h"
#include "result.h"

/**
 * @TODO
 */
#define opc_string(value) (char *) (value)

/**
 * @TODO
 */
#define opc_string_printf(value, ...) \
  OPC_PRINTF(opc_string(value), __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_print(value) opc_string_printf("%s\n", opc_string(value))

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
OPC_EXPORT unsigned long
opc_string_size (const char *string);

/**
 * Compares `left` and `right` string
 * @param left
 * @param right
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare (const char *left, const char *right);

/**
 * Compares `left` string of `left_size` length and `right` string of `right_size` length.
 * @param left
 * @param left_size
 * @param right
 * @param right_size
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare_with_size (
  const char *left,
  unsigned long left_size,
  const char *right,
  unsigned long right_size
);

#endif
