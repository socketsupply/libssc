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

#include <ssc/ssc.h>

#include "internal.h"

// Define `SSC_MISSING_ERRNO=1` if `<errno.h>` or `strerror(3)` was not found in
// a user space configure or feature detection script
#ifndef SSC_MISSING_ERRNO
#define HAVE_ERRONO
#include <string.h>
#endif

struct Error {
  SSCSize code;
  SSCString message;
};

// clang-format off
static struct Error errors[1024] = {
  { 0, "" },
  { SSC_ERROR, "An error occurred" },
  { SSC_NULL_POINTER, "NULL pointer reference" },
  { SSC_OUT_OF_MEMORY, "Ran out of memory" },
  { SSC_OUT_OF_BOUNDS, "Read out of bounds" },
  { SSC_INVALID_ARGUMENT, "Invalid argument" },
  { SSC_BAD_STATE, "Bad state" },
  { SSC_MISSING_CONTEXT, "Missing context" },
  { SSC_MALFORMED_URI, "Malformed URI" },
  { 0, 0 },
};

// clang-format on

// @TODO(jwerle): lock
static struct SSCError global_error = { 0 };

void
ssc_error_init () {
  ssc_error_reset();
}

const SSCString
ssc_error_string (SSCSize error) {
  SSCUSize count = sizeof(errors) / sizeof(struct Error);

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
    SSCString message = strerror(ssc_int(ssc_math_abs(error)));
    if (message != 0) {
      return message;
    }
  }
#endif

  return errors[0].message;
}

const SSCSize
ssc_error_create (SSCSize code, const SSCString message) {
  SSCSize count = sizeof(errors) / sizeof(struct Error);
  SSCSize slot = -1;

  if (code >= 0) {
    return ssc_throw(SSC_INVALID_ARGUMENT, "Error code must be less than 0");
  }

  if (message == 0) {
    return ssc_throw(SSC_INVALID_ARGUMENT, "Message cannot be NULL");
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
    return ssc_throw(SSC_OUT_OF_BOUNDS, "Maximum errors created");
  }

  // assign code + message
  errors[slot].code = code;
  errors[slot].message = message;

  // set end marker slot
  errors[slot + 1].code = 0;
  errors[slot + 1].message = 0;

  return SSC_OK;
}

const SSCSize
ssc_error_throw (
  const SSCSize code,
  const SSCString message,
  const SSCString location,
  const SSCSize line,
  const SSCString function,
  ...
) {
  // clang-format off
  SSCBuffer buffer = ssc_buffer_from(
    global_error.bytes,
    sizeof(global_error.bytes)
  );

  // header
  // NOLINTNEXTLINE
  global_error.meta.header_size = ssc_string_nformat(
    ssc_string(buffer.bytes),
    SSC_ERROR_MAX_HEADER_BYTES,
    SSC_ERROR_HEADER_FORMAT,
    ssc_error_string(code),
    function,
    location,
    line
  );

  va_list args;
  va_start(args, function);

  global_error.code = code;
  global_error.line = line;
  global_error.location = ssc_string(
    buffer.bytes + SSC_ERROR_LOCATION_BYTES_OFFSET
  );

  global_error.function = ssc_string(
    buffer.bytes + SSC_ERROR_FUNCTION_BYTES_OFFSET
  );

  // +message
  if (message != 0 && ssc_string_size(message) > 0) {
    SSCSize header_size = global_error.meta.header_size;
    global_error.message = ssc_string(buffer.bytes + header_size);
    // NOLINTNEXTLINE
    global_error.meta.message_size = ssc_string_vnformat(
      global_error.message,
      SSC_ERROR_MAX_MESSAGE_BYTES,
      message,
      args
    );
  }

  // |location
  // NOLINTNEXTLINE
  ssc_string_nformat(
    global_error.location,
    SSC_ERROR_MAX_LOCATION_BYTES,
    "%s",
    location
  );

  // |function
  // NOLINTNEXTLINE
  ssc_string_nformat(
    global_error.function,
    SSC_ERROR_MAX_FUNCTION_BYTES,
    "%s",
    function
  );
  // clang-format on

  va_end(args);

  return code;
}

const SSCSize
ssc_error_catch (SSCError *error) {
  const SSCSize code = global_error.code;

  // catch can be called with `NULL` pointer
  if (error != 0) {
    SSCBuffer buffer = ssc_buffer_from(error->bytes, sizeof(error->bytes));
    ssc_buffer_fill(&buffer, 0, 0, SSC_ERROR_MAX_BYTES);
    ssc_buffer_write(&buffer, global_error.bytes, 0, SSC_ERROR_MAX_BYTES);

    error->line = global_error.line;
    error->code = global_error.code;
    error->string = ssc_string(error->bytes);
    error->message = ssc_string(buffer.bytes + global_error.meta.header_size);
    error->location =
      ssc_string(buffer.bytes + SSC_ERROR_LOCATION_BYTES_OFFSET);
    error->function =
      ssc_string(buffer.bytes + SSC_ERROR_FUNCTION_BYTES_OFFSET);
  }

  ssc_error_reset();
  return code;
}

void
ssc_error_reset () {
  global_error.code = SSC_OK;
  global_error.line = 0;
  global_error.string = ssc_string(global_error.bytes);
  global_error.message = "";
  global_error.function = "unknown";
  global_error.location = "unknown";
  global_error.meta.header_size = 0;
  global_error.meta.message_size = 0;

  ssc_buffer_fill(
    &ssc_buffer_from(global_error.bytes, sizeof(global_error.bytes)), 0, 0, -1
  );
}

const SSCSize
ssc_error_get_code () {
  return global_error.code;
}

const SSCString
ssc_error_get_message () {
  return global_error.message;
}

const SSCSize
ssc_error_get_code_at_slot (SSCUSize slot) {
  SSCUSize count = sizeof(errors) / sizeof(struct Error);
  return global_error.code;
}

const SSCString
ssc_error_get_message_at_slot (SSCUSize slot) {
  SSCUSize count = sizeof(errors) / sizeof(struct Error);
  return global_error.message;
}
