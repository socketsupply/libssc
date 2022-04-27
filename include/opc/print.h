#ifndef OPC_PRINT_H
#define OPC_PRINT_H

#include "platform.h"
#include "string.h"

/**
 * Simply print something.
 * @param value The value to be printed
 */
#define opc_print(value) opc_string_print(value)

/**
 * Simply print a formatted string
 * @param format The string format
 * @param ... Values to be formated
 */
#define opc_printf(format, ...) opc_string_printf(format, ##__VA_ARGS__)

#endif
