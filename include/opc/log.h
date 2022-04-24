#ifndef OPC_LOG_H
#define OPC_LOG_H

#include "platform.h"
#include "string.h"

/**
 * @TODO
 */
typedef enum {
  OPC_LOG_LEVEL_NONE = -1,
  OPC_LOG_LEVEL_EMERGENCY = 0,
  OPC_LOG_LEVEL_ALERT = 1,
  OPC_LOG_LEVEL_CRITICAL = 2,
  OPC_LOG_LEVEL_ERROR = 3,
  OPC_LOG_LEVEL_WARNING = 4,
  OPC_LOG_LEVEL_NOTICE = 5,
  OPC_LOG_LEVEL_INFO = 6,
  OPC_LOG_LEVEL_DEBUG = 7
} OPCLogLevel;

/**
 * @TODO
 */
#define opc_log_emerg(...)                                                     \
  opc_log(OPC_LOG_LEVEL_EMERGENCY, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_alert(...)                                                     \
  opc_log(OPC_LOG_LEVEL_ALERT, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_crit(...)                                                     \
  opc_log(OPC_LOG_LEVEL_CRITICAL, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_error(...)                                                     \
  opc_log(OPC_LOG_LEVEL_ERROR, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_warn(...)                                                     \
  opc_log(OPC_LOG_LEVEL_WARNING, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_notice(...)                                                     \
  opc_log(OPC_LOG_LEVEL_NOTICE, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_info(...)                                                     \
  opc_log(OPC_LOG_LEVEL_INFO, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
#define opc_log_debug(...)                                                     \
  opc_log(OPC_LOG_LEVEL_DEBUG, __FILE__, __VA_ARGS__)

/**
 * @TODO
 */
OPC_EXPORT void
opc_log_set_level (const OPCLogLevel level);

/**
 * @TODO
 */
OPC_EXPORT OPCLogLevel
opc_log_get_level ();

/**
 * @TODO
 */
OPC_EXPORT OPCString
opc_log_get_level_string ();

/**
 * @TODO
 */
OPC_EXPORT OPCString
opc_log_get_level_name ();

/**
 * @TODO
 */
OPC_EXPORT void
opc_log_set_file_stream_pointer (void *pointer);

/**
 * @TODO
 */
OPC_EXPORT void
opc_log_enable_colors ();

/**
 * @TODO
 */
OPC_EXPORT void
opc_log_disable_colors ();

/**
 * @TODO
 */
OPC_EXPORT void
opc_log (
  const OPCLogLevel level,
  const OPCString location,
  const OPCString format,
  ...
);

#endif
