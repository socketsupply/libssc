#ifndef OPC_LOG_H
#define OPC_LOG_H

#include "platform.h"
#include "string.h"

/**
 * Log line format used after formatted log level prefix for all
 * `opg_log_*` functions.
 */
#ifndef OPC_LOG_LINE_FORMAT
#define OPC_LOG_LINE_FORMAT "(%s) <%s:%llu>: "
#endif

/**
 * Enumerated log levels
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
 * Logs `[EMERG]: ...` with message to stderr.
 */
#define opc_log_emerg(...)                                                     \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_EMERGENCY,                                                   \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[ALERT]: ...` with message to stderr.
 */
#define opc_log_alert(...)                                                     \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_ALERT,                                                       \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[CRIT]: ...` with message to stderr.
 */
#define opc_log_crit(...)                                                      \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_CRITICAL,                                                    \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[ERR]: ...` with message to stderr.
 */
#define opc_log_error(...)                                                     \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_ERROR,                                                       \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[WARNING]: ...` with message to stderr.
 */
#define opc_log_warn(...)                                                      \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_WARNING,                                                     \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[NOTICE]: ...` with message to stderr.
 */
#define opc_log_notice(...)                                                    \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_NOTICE,                                                      \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[INFO]: ...` with message to stderr.
 */
#define opc_log_info(...)                                                      \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_INFO,                                                        \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[DEBUG]: ...` with message to stderr.
 */
#define opc_log_debug(...)                                                     \
  opc_log(                                                                     \
    OPC_LOG_LEVEL_DEBUG,                                                       \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Sets the current log level.
 * @param level One of `OPCLogLevel` values
 */
OPC_EXPORT void
opc_log_set_level (const OPCLogLevel level);

/**
 * Gets the current log level that is one of `OPCLogLevel`.
 * @return The current `OPCLogLevel` value.
 */
OPC_EXPORT const OPCLogLevel
opc_log_get_level ();

/**
 * Gets the current log level `OPCLogLevel` string value.
 * @return The current `OPCLogLevel` string value.
 */
OPC_EXPORT const OPCString
opc_log_get_level_string ();

/**
 * Gets the current log level name.
 * @return The current `OPCLogLevel` string name.
 */
OPC_EXPORT const OPCString
opc_log_get_level_name ();

/**
 * Sets the current stream pointer where logs are written to.
 * @param pointer An opaque file stream pointer (eg: `FILE *`)
 */
OPC_EXPORT void
opc_log_set_file_stream_pointer (void *pointer);

/**
 * Enables colors in log output.
 */
OPC_EXPORT void
opc_log_enable_colors ();

/**
 * Disables colors in log output.
 */
OPC_EXPORT void
opc_log_disable_colors ();

/**
 * Writes a log for a given `OPCLogLevel` with callsite information.
 * @notice This function is called by the
 *         `opc_log_{emerg,alert,crit,error,warn,notice,info,debug}()` family
 *         of function macros that include the callsite details so the caller
 *         does not need to provide them.
 * @param level The `OPCLogLevel` value for this log write
 * @param location The file location of the call site
 * @param line The file line number of the call site
 * @param function The function name of the call site
 * @param format Format string for formatted variadic values
 * @param ... Variadic values to be formatted in output
 */
OPC_EXPORT void
opc_log (
  const OPCLogLevel level,
  const OPCString location,
  const OPCUSize line,
  const OPCString function,
  const OPCString format,
  ...
);

#endif
