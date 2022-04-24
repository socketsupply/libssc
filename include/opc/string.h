#ifndef OPC_STRING_H
#define OPC_STRING_H

#include "platform.h"
#include "result.h"

/**
 * @TODO
 */
typedef char * OPCString;

/**
 * @TODO
 */
#define opc_string(value) (OPCString) (value)

/**
 * @TODO
 */
#define opc_string_fprintf(stream, value, ...)                                 \
  OPC_FPRINTF(stream, opc_string(value), __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_printf(value, ...) OPC_PRINTF(opc_string(value), __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_print(value) opc_string_printf("%s\n", opc_string(value))

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
OPC_EXPORT OPCSize
opc_string_size (const OPCString string);

/**
 * Compares `left` and `right` string
 * @param left
 * @param right
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare (const OPCString left, const OPCString right);

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
  const OPCString left,
  OPCSize left_size,
  const OPCString right,
  OPCSize right_size
);

/**
 * @TODO
 */
OPC_EXPORT const OPCString
opc_string_slice (const OPCString self, OPCSize offset);

#endif
