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

#include <opc/opc.h>
#include "types.h"

// Define `OPC_MISSING_ERRNO=1` if `<errno.h>` or `strerror(3)` was not found in
// a user space configure or feature detection script
#ifndef OPC_MISSING_ERRNO
#define HAVE_ERRONO
#include <string.h>
#endif

struct Error {
  OPCSize code;
  OPCString message;
};

// clang-format off
static struct Error errors[1024] = {
  { 0, "" },
  { OPC_ERROR, "An error occurred" },
  { OPC_NULL_POINTER, "NULL pointer reference" },
  { OPC_OUT_OF_MEMORY, "Ran out of memory" },
  { OPC_OUT_OF_BOUNDS, "Read out of bounds" },
  { OPC_INVALID_ARGUMENT, "Invalid argument" },
  { OPC_BAD_STATE, "Bad state" },
  { OPC_MISSING_CONTEXT, "Missing context" },
  { 0, 0 },
};

// clang-format on

// @TODO(jwerle): lock
static struct OPCError global_error = { 0 };

void
opc_error_init () {
  opc_error_reset();
}

const OPCString
opc_error_string (OPCSize error) {
  OPCUSize count = sizeof(errors) / sizeof(struct Error);

  if (error < 0) {
    for (int i = 0; i < count; ++i) {
      if (errors[i].code == 0 && errors[i].message == 0) {
        break;
      }

      if (errors[i].code == error) {
        return errors[i].message;
      }
    }
  }

#ifdef HAVE_ERRONO
  if (error > 0) {
    OPCString message = strerror(opc_int(opc_math_abs(error)));
    if (message != 0) {
      return message;
    }
  }
#endif

  return errors[0].message;
}

const OPCSize
opc_error_create (OPCSize code, const OPCString message) {
  OPCSize count = sizeof(errors) / sizeof(struct Error);
  OPCSize slot = -1;

  if (code >= 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Error code must be less than 0");
  }

  if (message == 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Message cannot be NULL");
  }

  for (int i = 0; i < count - 1; ++i) {
    if (errors[i].code == code) {
      slot = i;
      break;
    }

    if (errors[i].code == 0 && errors[i].message == 0) {
      slot = i;
      break;
    }
  }

  if (slot == -1 || slot >= count) {
    return opc_throw(OPC_OUT_OF_BOUNDS, "Maximum errors created");
  }

  // assign code + message
  errors[slot].code = code;
  errors[slot].message = message;

  // set end marker slot
  errors[slot + 1].code = 0;
  errors[slot + 1].message = 0;

  return OPC_OK;
}

const OPCSize
opc_error_throw (
  const OPCSize code,
  const OPCString message,
  const OPCString location,
  const OPCSize line,
  const OPCString function,
  ...
) {
  // clang-format off
  OPCBuffer buffer = opc_buffer_from(
    global_error.bytes,
    sizeof(global_error.bytes)
  );

  // header
  // NOLINTNEXTLINE
  global_error.meta.header_size = opc_string_nformat(
    opc_string(buffer.bytes),
    OPC_ERROR_MAX_HEADER_BYTES,
    OPC_ERROR_HEADER_FORMAT,
    opc_error_string(code),
    function,
    location,
    line
  );

  va_list args;
  va_start(args, function);

  global_error.code = code;
  global_error.line = line;
  global_error.location = opc_string(
    buffer.bytes + OPC_ERROR_LOCATION_BYTES_OFFSET
  );

  global_error.function = opc_string(
    buffer.bytes + OPC_ERROR_FUNCTION_BYTES_OFFSET
  );

  // +message
  if (message != 0 && opc_string_size(message) > 0) {
    OPCSize header_size = global_error.meta.header_size;
    global_error.message = opc_string(buffer.bytes + header_size);
    // NOLINTNEXTLINE
    global_error.meta.message_size = opc_string_vnformat(
      global_error.message,
      OPC_ERROR_MAX_MESSAGE_BYTES,
      message,
      args
    );
  }

  // |location
  // NOLINTNEXTLINE
  opc_string_nformat(
    global_error.location,
    OPC_ERROR_MAX_LOCATION_BYTES,
    "%s",
    location
  );

  // |function
  // NOLINTNEXTLINE
  opc_string_nformat(
    global_error.function,
    OPC_ERROR_MAX_FUNCTION_BYTES,
    "%s",
    function
  );
  // clang-format on

  va_end(args);

  return code;
}

const OPCSize
opc_error_catch (OPCError *error) {
  const OPCSize code = global_error.code;

  // catch can be called with `NULL` pointer
  if (error != 0) {
    OPCBuffer buffer = opc_buffer_from(error->bytes, sizeof(error->bytes));
    opc_buffer_fill(&buffer, 0, 0, OPC_ERROR_MAX_BYTES);
    opc_buffer_write(&buffer, global_error.bytes, 0, OPC_ERROR_MAX_BYTES);

    error->line = global_error.line;
    error->code = global_error.code;
    error->string = opc_string(error->bytes);
    error->message = opc_string(buffer.bytes + global_error.meta.header_size);
    error->location =
      opc_string(buffer.bytes + OPC_ERROR_LOCATION_BYTES_OFFSET);
    error->function =
      opc_string(buffer.bytes + OPC_ERROR_FUNCTION_BYTES_OFFSET);
  }

  opc_error_reset();
  return code;
}

void
opc_error_reset () {
  global_error.code = OPC_OK;
  global_error.line = 0;
  global_error.string = opc_string(global_error.bytes);
  global_error.message = "";
  global_error.function = "unknown";
  global_error.location = "unknown";
  global_error.meta.header_size = 0;
  global_error.meta.message_size = 0;

  opc_buffer_fill(&opc_buffer_from(global_error.bytes), 0, 0, -1);
}

const OPCSize
opc_error_get_code () {
  return global_error.code;
}

const OPCString
opc_error_get_message () {
  return global_error.message;
}

const OPCSize
opc_error_get_code_at_slot (OPCUSize slot) {
  OPCUSize count = sizeof(errors) / sizeof(struct Error);
  return global_error.code;
}

const OPCString
opc_error_get_message_at_slot (OPCUSize slot) {
  OPCUSize count = sizeof(errors) / sizeof(struct Error);
  return global_error.message;
}
