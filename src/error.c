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

struct Error {
  const OPCResult code;
  const OPCString message;
};

// clang-format off
static struct Error errors[] = {
  { 0, "" },
  { OPC_ERROR, "An error occurred" },
  { OPC_NULL_POINTER, "NULL pointer reference" },
  { OPC_OUT_OF_MEMORY, "Ran out of memory" },
  { OPC_OUT_OF_BOUNDS, "Read out of bounds" },
  { OPC_INVALID_ARGUMENT, "Invalid argument" }
};

// clang-format on

// @TODO(jwerle): lock
static struct OPCError global_error = { 0 };

void
opc_error_init () {
  opc_error_reset();
}

const OPCString
opc_error_string (OPCResult error) {
  unsigned long count = sizeof(errors) / sizeof(struct Error);

  for (int i = 0; i < count; ++i) {
    if (errors[i].code == error) {
      return errors[i].message;
    }
  }

  return errors[0].message;
}

const OPCResult
opc_error_throw (
  const OPCResult code,
  const OPCString message,
  const OPCString location,
  const OPCUSize line,
  const OPCString function,
  ...
) {
  OPCBuffer buffer = opc_buffer_from(global_error.bytes);

  // header
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

  // clang-format off
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
    OPCUSize header_size = global_error.meta.header_size;
    global_error.message = opc_string(buffer.bytes + header_size);
    global_error.meta.message_size = opc_string_vnformat(
      global_error.message,
      OPC_ERROR_MAX_MESSAGE_BYTES,
      message,
      args
    );
  }

  // |location
  opc_string_nformat(
    global_error.location,
    OPC_ERROR_MAX_LOCATION_BYTES,
    "%s",
    location
  );

  // |function
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

const OPCResult
opc_error_catch (OPCError *error) {
  const OPCResult code = global_error.code;

  // catch can be called with `NULL` pointer
  if (error != 0) {
    OPCBuffer buffer = opc_buffer_from(error->bytes);
    opc_buffer_fill(&buffer, 0, 0, OPC_ERROR_MAX_BYTES);
    opc_buffer_write(&buffer, global_error.bytes, 0, OPC_ERROR_MAX_BYTES);

    error->line = global_error.line;
    error->code = global_error.code;
    error->string = opc_string(error->bytes);
    error->message = buffer.bytes + global_error.meta.header_size;
    error->location = buffer.bytes + OPC_ERROR_LOCATION_BYTES_OFFSET;
    error->function = buffer.bytes + OPC_ERROR_FUNCTION_BYTES_OFFSET;
  }

  opc_error_reset();
  return code;
}

void
opc_error_reset () {
  global_error.code = OPC_OK;
  global_error.line = 0;
  global_error.string = global_error.bytes;
  global_error.message = "";
  global_error.function = "unknown";
  global_error.location = "unknown";
  global_error.meta.header_size = 0;
  global_error.meta.message_size = 0;

  opc_buffer_fill(&opc_buffer_from(global_error.bytes), 0, 0, -1);
}

const OPCResult
opc_error_get_code () {
  return global_error.code;
}

const OPCString
opc_error_get_message () {
  return global_error.message;
}
