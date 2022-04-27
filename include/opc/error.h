#ifndef OPC_ERROR_H
#define OPC_ERROR_H

#include "platform.h"
#include "result.h"
#include "string.h"

/**
 * The format string used for formatting the error string.
 */
#ifndef OPC_ERROR_HEADER_FORMAT
#  define OPC_ERROR_HEADER_FORMAT "[Error: %s]: %s (%s:%llu): "
#endif

/**
 * Max size in bytes of the function string for an error.
 */
#define OPC_ERROR_MAX_FUNCTION_BYTES 1024

/**
 * Max size in header bytes for the error string header
 */
#define OPC_ERROR_MAX_HEADER_BYTES 1024

/**
 * Max size in bytes of the file locaton string for an error.
 */
#define OPC_ERROR_MAX_LOCATION_BYTES 1024

/**
 * Max size in bytes of the message string for an error.
 */
#define OPC_ERROR_MAX_MESSAGE_BYTES 1024

/**
 * Max size in extra bytes for custom error messages
 */
#define OPC_ERROR_MAX_STRING_BYTES                                             \
  OPC_ERROR_MAX_HEADER_BYTES + OPC_ERROR_MAX_MESSAGE_BYTES

/**
 * The byte offset where the function string is written to in the static error
 * bytes.
 */
#define OPC_ERROR_FUNCTION_BYTES_OFFSET                                        \
  OPC_ERROR_MAX_LOCATION_BYTES + OPC_ERROR_LOCATION_BYTES_OFFSET

/**
 * The byte offset where the location string is written to in the static error
 * bytes.
 */
#define OPC_ERROR_LOCATION_BYTES_OFFSET OPC_ERROR_MAX_STRING_BYTES

/**
 * Max total static bytes for an error suitable for the function string,
 * file location string, and a custom error message.
 */
// clang-format off
#define OPC_ERROR_MAX_BYTES                                                    \
  OPC_ERROR_MAX_FUNCTION_BYTES +                                               \
  OPC_ERROR_MAX_LOCATION_BYTES +                                               \
  OPC_ERROR_MAX_STRING_BYTES

// clang-format on
/**
 * An error container with static bytes that contain a possible
 * custom error message thrown by an `opc_*` function.
 */
typedef struct OPCError OPCError;

struct OPCError {
  OPCString string;
  OPCString message;
  OPCString location;
  OPCString function;
  OPCUSize line;
  OPCResult code;
  struct {
    OPCUSize message_size;
    OPCUSize header_size;
  } meta;
  // <header+message|location|function>
  OPCByte bytes[OPC_ERROR_MAX_BYTES];
};

/**
 * Throws an error with `code` and `message` that can be caught with
 * `opc_catch(err)
 */
#define opc_throw(code, message, ...)                                          \
  opc_error_throw(                                                             \
    code,                                                                      \
    message,                                                                   \
    opc_string(__FILE__),                                                      \
    opc_usize(__LINE__),                                                       \
    opc_string(__PRETTY_FUNCTION__),                                           \
    ##__VA_ARGS__                                                              \
  )

/**
 * Catches an error thrown by `opc_throw(...)`
 * @param error The name of the error variable for the block scope
 * @example
 *   opc_uri_component_encode(&output, input);
 *   opc_catch(err) {
 *     opg_log_error(opc_string(&err));
 *   }
 */
// @TODO(jwerle): use lock
#define opc_catch(error)                                                       \
  for (OPCError error = { .code = -1 };                                        \
       error.code == -1 && opc_error_catch(&error) != OPC_OK;)

/**
 * Returns the built-in error string for the error result.
 * @param error An `OPCResult` error code.
 * @return Built-in error string.
 */
OPC_EXPORT const OPCString
opc_error_string (const OPCResult error);

/**
 * Throws an error with `code` and `message` that can be caught with
 * `opc_error_catch()`. Call site data must be given to this function.
 * The `opc_throw()` function handles this.
 * @param code An `OPCResult` error code
 * @param message A custom error message
 * @param location The file location of the error
 * @param line The file line number of the error
 * @param function The name of the function throwing the error
 * @param ... Variadic arguments used as additions to a possiblly formated
 *            `message` variable
 * @return The `code` value given to this function
 */
OPC_EXPORT const OPCResult
opc_error_throw (
  const OPCResult code,
  const OPCString message,
  const OPCString location,
  const OPCUSize line,
  const OPCString function,
  ...
);

/**
 * Catches a possibly thrown error and populates an `OPCError` pointer
 * with an error code, message, and call site data.
 * @param error A pointer to an `OPCError` structure
 * @return The caught error code
 */
OPC_EXPORT const OPCResult
opc_error_catch (OPCError *error);

/**
 * Resets the current global error state.
 */
OPC_EXPORT void
opc_error_reset ();

/**
 * Returns the current global error code.
 */
OPC_EXPORT const OPCResult
opc_error_get_code ();

/**
 * Returns the current global error message. An empty string is returned
 * if one is not set.
 */
OPC_EXPORT const OPCString
opc_error_get_message ();

#endif
