#ifndef OPC_CALLSITE_H
#define OPC_CALLSITE_H

#include "platform.h"
#include "pp.h"

/**
 * Prints call site information to stdout.
 */
#define opc_print_callsite(format, ...)                                        \
  opc_printf(OPC_PP_CALLSITE_VARGS_WITH_FORMAT(format), ##__VA_ARGS__)

/**
 * Computes static callsite string.
 */
#define opc_callsite_file_location() OPC_PP_CALLSITE_FILE_LOCATION_STRING()

/**
 * Computes calsite function name string.
 */
#define opc_callsite_function_name() OPC_PP_CALLSITE_FUNCTION_NAME()

#endif
