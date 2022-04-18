#ifndef OPC_STRING_H
#define OPC_STRING_H

#include "platform.h"

/**
 * Computes string size.
 * @param string The string size to compute
 * @return Number of bytes in string
 */
OPC_EXPORT unsigned long
opc_string_size (const unsigned char *string);

#endif
