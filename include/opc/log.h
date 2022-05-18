/**
 * `libopc` - Operator Framework Client Library
 *
 * This file is part of libopc.
 *
 * MIT License
 *
 * Copyright (c) 2022 Socket Supply Co.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2022 Socket Supply Co. <socketsupply.co>
 */

#ifndef OPC_LOG_H
#define OPC_LOG_H

#include "platform.h"
#include "string.h"

/**
 * Log line format used after formatted log level prefix for all
 * `opg_log_*` functions.
 */
#ifndef OPC_LOG_LINE_FORMAT
#define OPC_LOG_LINE_FORMAT "<%s:%llu> %s: "
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
 * Logs `[EMERG]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_emergb(buffer)                                                 \
  opc_log_emerg("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[ALERT]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_alertb(buffer)                                                 \
  opc_log_alert("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[CRIT]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_critb(buffer)                                                 \
  opc_log_crit("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[ERROR]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_errorb(buffer)                                                 \
  opc_log_error("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[WARN]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_warnb(buffer)                                                 \
  opc_log_warn("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[NOTICE]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_noticeb(buffer)                                                 \
  opc_log_notice("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[INFO]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_infob(buffer)                                                 \
  opc_log_info("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

/**
 * Logs `[DEBUG]: ...` with buffer to stderr.
 * @param buffer
 */
#define opc_log_debugb(buffer)                                                 \
  opc_log_debug("%.*s", opc_int(buffer.size), opc_string(buffer.bytes))

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
