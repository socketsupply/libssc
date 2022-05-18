/**
 * `libssc` - Socket SDK Client Library
 *
 * This file is part of libssc.
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

#ifndef SSC_LOG_H
#define SSC_LOG_H

#include "platform.h"
#include "string.h"

/**
 * Log line format used after formatted log level prefix for all
 * `opg_log_*` functions.
 */
#ifndef SSC_LOG_LINE_FORMAT
#define SSC_LOG_LINE_FORMAT "<%s:%llu> %s: "
#endif

/**
 * Enumerated log levels
 */
typedef enum {
  SSC_LOG_LEVEL_NONE = -1,
  SSC_LOG_LEVEL_EMERGENCY = 0,
  SSC_LOG_LEVEL_ALERT = 1,
  SSC_LOG_LEVEL_CRITICAL = 2,
  SSC_LOG_LEVEL_ERROR = 3,
  SSC_LOG_LEVEL_WARNING = 4,
  SSC_LOG_LEVEL_NOTICE = 5,
  SSC_LOG_LEVEL_INFO = 6,
  SSC_LOG_LEVEL_DEBUG = 7
} SSCLogLevel;

/**
 * Logs `[EMERG]: ...` with message to stderr.
 */
#define ssc_log_emerg(...)                                                     \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_EMERGENCY,                                                   \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[ALERT]: ...` with message to stderr.
 */
#define ssc_log_alert(...)                                                     \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_ALERT,                                                       \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[CRIT]: ...` with message to stderr.
 */
#define ssc_log_crit(...)                                                      \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_CRITICAL,                                                    \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[ERR]: ...` with message to stderr.
 */
#define ssc_log_error(...)                                                     \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_ERROR,                                                       \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[WARNING]: ...` with message to stderr.
 */
#define ssc_log_warn(...)                                                      \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_WARNING,                                                     \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[NOTICE]: ...` with message to stderr.
 */
#define ssc_log_notice(...)                                                    \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_NOTICE,                                                      \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[INFO]: ...` with message to stderr.
 */
#define ssc_log_info(...)                                                      \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_INFO,                                                        \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[DEBUG]: ...` with message to stderr.
 */
#define ssc_log_debug(...)                                                     \
  ssc_log(                                                                     \
    SSC_LOG_LEVEL_DEBUG,                                                       \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    __VA_ARGS__                                                                \
  )

/**
 * Logs `[EMERG]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_emergb(buffer)                                                 \
  ssc_log_emerg("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[ALERT]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_alertb(buffer)                                                 \
  ssc_log_alert("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[CRIT]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_critb(buffer)                                                 \
  ssc_log_crit("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[ERROR]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_errorb(buffer)                                                 \
  ssc_log_error("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[WARN]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_warnb(buffer)                                                 \
  ssc_log_warn("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[NOTICE]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_noticeb(buffer)                                                 \
  ssc_log_notice("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[INFO]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_infob(buffer)                                                 \
  ssc_log_info("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Logs `[DEBUG]: ...` with buffer to stderr.
 * @param buffer
 */
#define ssc_log_debugb(buffer)                                                 \
  ssc_log_debug("%.*s", ssc_int(buffer.size), ssc_string(buffer.bytes))

/**
 * Sets the current log level.
 * @param level One of `SSCLogLevel` values
 */
SSC_EXPORT void
ssc_log_set_level (const SSCLogLevel level);

/**
 * Gets the current log level that is one of `SSCLogLevel`.
 * @return The current `SSCLogLevel` value.
 */
SSC_EXPORT const SSCLogLevel
ssc_log_get_level ();

/**
 * Gets the current log level `SSCLogLevel` string value.
 * @return The current `SSCLogLevel` string value.
 */
SSC_EXPORT const SSCString
ssc_log_get_level_string ();

/**
 * Gets the current log level name.
 * @return The current `SSCLogLevel` string name.
 */
SSC_EXPORT const SSCString
ssc_log_get_level_name ();

/**
 * Sets the current stream pointer where logs are written to.
 * @param pointer An opaque file stream pointer (eg: `FILE *`)
 */
SSC_EXPORT void
ssc_log_set_file_stream_pointer (void *pointer);

/**
 * Enables colors in log output.
 */
SSC_EXPORT void
ssc_log_enable_colors ();

/**
 * Disables colors in log output.
 */
SSC_EXPORT void
ssc_log_disable_colors ();

/**
 * Writes a log for a given `SSCLogLevel` with callsite information.
 * @notice This function is called by the
 *         `ssc_log_{emerg,alert,crit,error,warn,notice,info,debug}()` family
 *         of function macros that include the callsite details so the caller
 *         does not need to provide them.
 * @param level The `SSCLogLevel` value for this log write
 * @param location The file location of the call site
 * @param line The file line number of the call site
 * @param function The function name of the call site
 * @param format Format string for formatted variadic values
 * @param ... Variadic values to be formatted in output
 */
SSC_EXPORT void
ssc_log (
  const SSCLogLevel level,
  const SSCString location,
  const SSCUSize line,
  const SSCString function,
  const SSCString format,
  ...
);

#endif
