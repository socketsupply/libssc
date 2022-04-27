#ifndef OPC_STRING_H
#define OPC_STRING_H

#include "platform.h"

/**
 * @TODO
 */
typedef char *OPCString;

/**
 * @TODO
 */
#define opc_string(value) (OPCString)(value)

/**
 * @TODO
 */
#define opc_string_from_buffer(buffer) (OPCString)((buffer).bytes)

/**
 * @TODO
 */
#define opc_string_fprintf(stream, value, ...)                                 \
  OPC_FPRINTF(stream, opc_string(value), ##__VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_sprintf(string, format, ...)                                \
  OPC_SPRINTF(string, opc_string(format), ##__VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_snprintf(string, size, format, ...)                         \
  OPC_SNPRINTF(string, size, opc_string(format), ##__VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_vsprintf(string, ...) OPC_VSPRINTF(string, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_vsnprintf(string, ...) OPC_VSNPRINTF(string, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_printf(value, ...)                                          \
  OPC_PRINTF(opc_string(value), ##__VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_print(value) opc_string_printf("%s\n", opc_string(value))

/**
 * @TODO
 */
#define opc_string_format(string, ...) opc_string_sprintf(string, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_vformat(string, ...) opc_string_vsprintf(string, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_nformat(string, size, ...)                                  \
  opc_string_snprintf(string, size, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_string_vnformat(string, ...)                                       \
  opc_string_vsnprintf(string, __VA_ARGS__)

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
OPC_EXPORT OPCUSize
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
 * Compares `left` and `right` string equality
 * @param left
 * @param right
 * @return Returns `OPC_TRUE` if strings are equal, otherwise `OPC_FALSE`
 */
OPC_EXPORT OPCBoolean
opc_string_equals (const OPCString left, const OPCString right);

/**
 * Compares `left` string of `left_size` length and `right` string of
 * `right_size` length.
 * @param left
 * @param left_size
 * @param right
 * @param right_size
 * @return Returns 0 if strings are equal, otherwise the difference between them
 */
OPC_EXPORT int
opc_string_compare_with_size (
  const OPCString left,
  const OPCUSize left_size,
  const OPCString right,
  const OPCUSize right_size
);

/**
 * @TODO
 */
OPC_EXPORT const OPCString
opc_string_slice (const OPCString self, const OPCUSize offset);

#endif
