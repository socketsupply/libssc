/**
 * `libssc` - Socket SDK Client Library
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

#ifndef SSC_ERROR_H
#define SSC_ERROR_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * The format string used for formatting the error string.
 */
#ifndef SSC_ERROR_HEADER_FORMAT
#  define SSC_ERROR_HEADER_FORMAT "[Error: %s]: %s (%s:%llu): "
#endif

/**
 * Max size in bytes of the function string for an error.
 */
#define SSC_ERROR_MAX_FUNCTION_BYTES 1024

/**
 * Max size in header bytes for the error string header
 */
#define SSC_ERROR_MAX_HEADER_BYTES 1024

/**
 * Max size in bytes of the file locaton string for an error.
 */
#define SSC_ERROR_MAX_LOCATION_BYTES 1024

/**
 * Max size in bytes of the message string for an error.
 */
#define SSC_ERROR_MAX_MESSAGE_BYTES 1024

/**
 * Max size in extra bytes for custom error messages
 */
#define SSC_ERROR_MAX_STRING_BYTES                                             \
  SSC_ERROR_MAX_HEADER_BYTES + SSC_ERROR_MAX_MESSAGE_BYTES

/**
 * The byte offset where the function string is written to in the static error
 * bytes.
 */
#define SSC_ERROR_FUNCTION_BYTES_OFFSET                                        \
  SSC_ERROR_MAX_LOCATION_BYTES + SSC_ERROR_LOCATION_BYTES_OFFSET

/**
 * The byte offset where the location string is written to in the static error
 * bytes.
 */
#define SSC_ERROR_LOCATION_BYTES_OFFSET SSC_ERROR_MAX_STRING_BYTES

/**
 * Max total static bytes for an error suitable for the function string,
 * file location string, and a custom error message.
 */
// clang-format off
#define SSC_ERROR_MAX_BYTES                                                    \
  SSC_ERROR_MAX_FUNCTION_BYTES +                                               \
  SSC_ERROR_MAX_LOCATION_BYTES +                                               \
  SSC_ERROR_MAX_STRING_BYTES

// clang-format on
/**
 * @TODO
 */
#define SSCErrorProperties(static_size)                                        \
  /* <header+message|location|function> */                                     \
  SSCByte bytes[static_size];                                                  \
  SSCString string;                                                            \
  SSCString message;                                                           \
  SSCString location;                                                          \
  SSCString function;                                                          \
  SSCSize line;                                                                \
  SSCSize code;                                                                \
  struct {                                                                     \
    SSCSize message_size;                                                      \
    SSCSize header_size;                                                       \
  } meta;

/**
 * @TODO
 */
#define SSCError(static_size)                                                  \
  struct {                                                                     \
    SSCErrorProperties(static_size)                                            \
  }

/**
 * An error container with static bytes that contain a possible
 * custom error message thrown by an `ssc_*` function.
 */
typedef struct SSCError SSCError;

struct SSCError {
  SSCErrorProperties(SSC_ERROR_MAX_BYTES)
};

/**
 * Throws an error with `code` and `message` that can be caught with
 * `ssc_catch(err)
 * @param code An `SSCSize` error code. An error code defined in `<errno.h>`
 *             may be used to if the header is supported by the platform
 * @param message A custom error message
 * @param ... Variadic values to use in string formats in `message`
 * @example
 *   if (read_out_of_bounds) {
 *     return ssc_throw(SSC_OUT_OF_BOUNDS, "");
 *   }
 */
#define ssc_throw(code, message, ...)                                          \
  ssc_error_throw(                                                             \
    code,                                                                      \
    message,                                                                   \
    ssc_string(__FILE__),                                                      \
    ssc_usize(__LINE__),                                                       \
    ssc_string(__PRETTY_FUNCTION__),                                           \
    ##__VA_ARGS__                                                              \
  )

/**
 */
#define ssc_rethrow_error(error)                                               \
  ssc_error_throw(                                                             \
    error.code, error.message, error.location, error.line, error.function      \
  )

/**
 * Catches an error thrown by `ssc_throw(...)`
 * @param error The name of the error variable for the block scope
 * @example
 *   ssc_uri_component_encode(&output, input);
 *   ssc_catch(err) {
 *     opg_log_error(ssc_string(&err));
 *   }
 */
// @TODO(jwerle): use lock
#define ssc_catch(error)                                                       \
  for (SSCError error = { .code = SSC_UNKNOWN };                               \
       error.code == SSC_UNKNOWN && ssc_error_catch(&error) != SSC_OK;)
/**
 * Returns the built-in error string for the error result.
 * @param error An `SSCSize` error code.
 * @return Built-in error string.
 */
SSC_EXPORT const SSCString
ssc_error_string (const SSCSize error);

/**
 * Throws an error with `code` and `message` that can be caught with
 * `ssc_error_catch()`. Call site data must be given to this function.
 * The `ssc_throw()` function handles this.
 * @param code An `SSCSize` error code. An error code defined in `<errno.h>`
 *             may be used to if the header is supported by the platform
 * @param message A custom error message
 * @param location The file location of the error
 * @param line The file line number of the error
 * @param function The name of the function throwing the error
 * @param ... Variadic arguments used as additions to a possiblly formated
 *            `message` variable
 * @return The `code` value given to this function
 */
SSC_EXPORT const SSCSize
ssc_error_throw (
  const SSCSize code,
  const SSCString message,
  const SSCString location,
  const SSCSize line,
  const SSCString function,
  ...
);

/**
 * Catches a possibly thrown error and populates an `SSCError` pointer
 * with an error code, message, and call site data.
 * @param error A pointer to an `SSCError` structure
 * @return The caught error code
 */
SSC_EXPORT const SSCSize
ssc_error_catch (SSCError *error);

/**
 * Creates an error type with `code` and corresponding `message`.
 * @param code Custom error code
 * @param {
 */
const SSCSize
ssc_error_create (SSCSize code, const SSCString message);

/**
 * Resets the current global error state.
 */
SSC_EXPORT void
ssc_error_reset ();

/**
 * Returns the current global error code.
 */
SSC_EXPORT const SSCSize
ssc_error_get_code ();

/**
 * Returns the current global error message. An empty string is returned
 * if one is not set.
 */
SSC_EXPORT const SSCString
ssc_error_get_message ();

#endif
