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

// clang-format off
static const char DEC2HEX[16 + 1] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'A', 'B',
  'C', 'D', 'E', 'F',
  '0'
};

static const char HEX2DEC[256] = {
  /*       0   1   2   3   4   5   6   7   8   9   A   B   C   D    E  F */
  /* 0 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 1 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 2 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 3 */  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
  /* 4 */ -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 5 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 6 */ -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 7 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 8 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* 9 */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* A */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* B */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* C */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* D */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* E */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  /* F */ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

// clang-format on
//
static const SSCBuffer ENDING_OF_PROTOCOL_SLASHES = ssc_buffer_from("://", 3);

static SSCResult
detect (SSCByte byte, SSCBoolean special) {
  // clang-format off
  // restricted  characters
  if (
    '-' == byte || '_' == byte || '.' == byte || '!' == byte ||
    '~' == byte || '*' == byte || '(' == byte || ')' == byte
  ) {
    // clang-format on
    return SSC_NOT_DETECTED;
  }

  if (special) {
    // clang-format off
    // special characters
    if (
      '#' == byte || '$' == byte || '&' == byte || '+' == byte ||
      ',' == byte || '/' == byte || ':' == byte | ';' == byte ||
      '=' == byte || '?' == byte || '@' == byte
    ) {
      // clang-format on
      return SSC_NOT_DETECTED;
    }
  }

  return ssc_utf8_detect(ssc_buffer_from(ssc_bytes(ssc_pointer(byte)), 1));
}

static SSCSize
ssc_uri_component_encode_ (
  SSCBuffer *output,
  const SSCBuffer input,
  SSCBoolean detect_special
) {
  SSCSize size = 0;

  if (output->bytes == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Output bytes pointer cannot be NULL.");
  }

  if (input.bytes == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Input bytes pointer cannot be NULL.");
  }

  for (int i = 0; i < input.size; ++i) {
    if (size >= output->size) {
      return ssc_throw(SSC_OUT_OF_MEMORY, "Output bytes out of memory.");
    }

    const SSCByte byte = input.bytes[i];
    const long status = detect(byte, detect_special);

    if (status < SSC_OK) {
      return status;
    }

    if (status == SSC_NOT_DETECTED) {
      output->bytes[size++] = byte;
    } else {
      output->bytes[size++] = '%';

      if (size >= output->size) {
        return ssc_throw(SSC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[byte >> 4];

      if (size >= output->size) {
        return ssc_throw(SSC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[byte & 0x0f];
    }
  }

  return size;
}

SSCSize
ssc_uri_component_encode (SSCBuffer *output, const SSCBuffer input) {
  return ssc_uri_component_encode_(output, input, false);
}

static SSCSize
ssc_uri_component_encode_size_ (
  const SSCBuffer input,
  SSCBoolean detect_special
) {
  SSCSize size = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  for (int i = 0; i < input.size && input.bytes[i] != 0; ++i) {
    SSCByte byte = input.bytes[i];
    const long status = detect(byte, detect_special);

    switch (status) {
      case SSC_NOT_DETECTED:
        size++;
        break;
      case SSC_DETECTED:
        size = size + 3; // %XX
        break;
      default:
        return status;
    }
  }

  return (long) size;
}

SSCSize
ssc_uri_component_encode_size (const SSCBuffer input) {
  return ssc_uri_component_encode_size_(input, false);
}

SSCSize
ssc_uri_component_decode (SSCBuffer *output, const SSCBuffer input) {
  SSCSize size = 0;

  if (output->bytes == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Output bytes cannot be NULL");
  }

  if (input.bytes == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Input bytes cannot be NULL");
  }

  for (int i = 0; i < input.size; ++i) {
    if (input.bytes[i] == 0)
      break;

    if (size >= output->size) {
      return ssc_throw(SSC_OUT_OF_MEMORY, "Output out of memory");
    }

    if (input.bytes[i] == '%') {
      SSCSize x = HEX2DEC[input.bytes[i + 1]];
      SSCSize y = HEX2DEC[input.bytes[i + 2]];

      i = i + 2;

      output->bytes[size++] = (x << 4) + y;
    } else {
      output->bytes[size++] = input.bytes[i];
    }
  }

  return size;
}

SSCSize
ssc_uri_component_decode_size (const SSCBuffer input) {
  SSCSize size = 0;
  int i = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  while (i < input.size && input.bytes[i] != 0) {
    if (input.bytes[i] == '%') {
      i = i + 3;
    } else {
      i = i + 1;
    }

    if (input.bytes[i] == 0) {
      break;
    }

    size = size + 1;
  }

  return size;
}

SSCResult
ssc_uri_parse (SSCURI *self, const SSCBuffer input) {
  // parser static memory
  SSCByte memory[SSC_URI_MAX_BYTES] = { 0 };

  if (self == 0) {
    return ssc_throw(SSC_NULL_POINTER, "SSCURI pointer cannot be NULL");
  }

  if (input.bytes == 0) {
    return ssc_throw(SSC_NULL_POINTER, "Input bytes cannot be NULL");
  }

  if (input.size == 0) {
    return ssc_throw(SSC_INVALID_ARGUMENT, "Input size cannot be 0");
  }

  // parser state
  enum {
    NONE = 0,
    PROTOCOL,
    USERNAME,
    PASSWORD,
    HOST,
    PORT,
    PATH,
    QUERY,
    HASH
  };

  SSCUSize tmp_offset = 0;
  SSCUSize offset = 0;
  SSCInt state = NONE;

  // clang-format off
  SSCBufferStaticMap(tmp, output) buffers = {
    .output = ssc_buffer_from(self->bytes, SSC_URI_MAX_BYTES),
    .tmp = ssc_buffer_from(memory, sizeof(memory))
  };

  // reset URI buffers
  // clang-format on
  ssc_buffer_set(&self->href, ssc_bytes(""), 0);
  ssc_buffer_set(&self->protocol, ssc_bytes(""), 0);
  ssc_buffer_set(&self->username, ssc_bytes(""), 0);
  ssc_buffer_set(&self->password, ssc_bytes(""), 0);
  ssc_buffer_set(&self->host, ssc_bytes(""), 0);
  ssc_buffer_set(&self->port, ssc_bytes(""), 0);
  ssc_buffer_set(&self->path, ssc_bytes(""), 0);
  ssc_buffer_set(&self->query, ssc_bytes(""), 0);
  ssc_buffer_set(&self->hash, ssc_bytes(""), 0);

  // both `protocol` and `href` point to the beginning of `bytes`, which
  // is a static value and the first member of `SSCURI` so
  // `ssc_string_print("%s", ssc_string(ssc_pointer(uri)));`
  self->protocol.bytes = self->bytes;
  self->href.bytes = self->bytes;

  state = PROTOCOL;

  for (int i = 0; i < input.size; ++i) {
    SSCByte byte = input.bytes[i];
    SSCUSize written = 0;

    if (offset >= buffers.output.size) {
      return ssc_throw(SSC_OUT_OF_MEMORY, "Out of memory");
    }

    // protocol://username:password@host:port
    if (state < PATH) {
      written = ssc_buffer_write(&buffers.output, ssc_bytes(&byte), offset, 1);

      if (written < 0) {
        break;
      }

      offset += written;

      if (state == PROTOCOL) {
        self->protocol.size += written;
      }

      if (state == USERNAME) {
        self->username.size += written;
      }

      if (state == PASSWORD) {
        self->password.size += written;
      }

      if (state == HOST) {
        self->host.size += written;
      }

      if (state == PORT) {
        self->port.size += written;
      }

      if (byte == ':') {
        if (state == PROTOCOL) {
          SSCBuffer slice = ssc_buffer_slice(input, i + 1, i + 3);
          written = ssc_buffer_write_buffer(&buffers.output, slice, offset);

          if (written < 0) {
            break;
          }

          offset += written;
          state = USERNAME;
          ssc_buffer_set(&self->username, buffers.output.bytes + offset, 0);
        }

        if (state == HOST) {
          state = PORT;
        }
      }

      if (byte == '@') {
        state = HOST;
      }

      if (byte == '/') {
        if (state == USERNAME) {
          ssc_buffer_set_buffer(&self->host, self->username);
          self->host.size = self->username.size;
          self->host.bytes = self->username.bytes;
          self->username.size = 0;
          self->username.bytes = ssc_bytes("");
        } else if (state == HOST) {
        } else {
          return ssc_throw(SSC_MALFORMED_URI, "Invalid state in URI parser");
        }

        state = PATH;
      }

      // `?` could come after `port` or `host` implying `path` omission
      if (byte == '?') {
        if (state < QUERY) {
          state = QUERY;
        }
      }

      // `#` could come after `port` or `host` implying `path` omission
      if (byte == '#') {
        if (state < HASH) {
          state = HASH;
        }
      }
    } else { // /?query#fragment
      if (byte == '#') {
        if (state < HASH) {
          state = HASH;
        }
      }
    }
  }

  ssc_catch(err) {
    return ssc_rethrow_error(err);
  }

  self->href.size = offset - 1;

  ssc_log_alertb(self->href);

  return SSC_OK;
}

static void
uri_format (SSCString string, const SSCString format, const SSCURI self) {
  // NOLINTNEXTLINE
  ssc_string_nformat(
    ssc_string(string),
    SSC_URI_MAX_BYTES,
    "%.*s%.*s%.*s%.*s%.*s",
    ssc_int(self.protocol.size),
    ssc_string(self.protocol.bytes),
    ssc_int(self.host.size),
    ssc_string(self.host.bytes),
    ssc_int(self.path.size),
    ssc_string(self.path.bytes),
    ssc_int(self.query.size),
    ssc_string(self.query.bytes),
    ssc_int(self.hash.size),
    ssc_string(self.hash.bytes)
  );
}

static void
uri_fprintf (SSCHandle stream, const SSCString format, const SSCURI self) {
  SSCChar string[SSC_URI_MAX_BYTES] = { 0 };
  uri_format(string, format, self);
  ssc_string_fprintf(stream, "%s\n", string);
}

void
ssc_uri_print (const SSCURI self) {
  uri_fprintf(ssc_stdout(), "%s\n", self);
}

SSCSize
ssc_uri_encode (SSCBuffer *output, const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_encode_size (const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_decode (SSCBuffer *output, const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_decode_size (const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_file_encode (SSCBuffer *output, const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_file_encode_size (const SSCBuffer input) {
  return SSC_FILE_URI_PREFIX_SIZE + ssc_uri_component_encode_size(input);
}

SSCSize
ssc_uri_file_decode (SSCBuffer *output, const SSCBuffer input) {
  return 0;
}

SSCSize
ssc_uri_file_decode_size (const SSCBuffer input) {
  return 0;
}
