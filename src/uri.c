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
static const OPCBuffer ENDING_OF_PROTOCOL_SLASHES = opc_buffer_from("://", 3);

static OPCResult
detect (OPCByte byte, OPCBoolean special) {
  // clang-format off
  // restricted  characters
  if (
    '-' == byte || '_' == byte || '.' == byte || '!' == byte ||
    '~' == byte || '*' == byte || '(' == byte || ')' == byte
  ) {
    // clang-format on
    return OPC_NOT_DETECTED;
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
      return OPC_NOT_DETECTED;
    }
  }

  return opc_utf8_detect(opc_buffer_from(opc_bytes(opc_pointer(byte)), 1));
}

static OPCSize
opc_uri_component_encode_ (
  OPCBuffer *output,
  const OPCBuffer input,
  OPCBoolean detect_special
) {
  OPCSize size = 0;

  if (output->bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Output bytes pointer cannot be NULL.");
  }

  if (input.bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Input bytes pointer cannot be NULL.");
  }

  for (int i = 0; i < input.size; ++i) {
    if (size >= output->size) {
      return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
    }

    const OPCByte byte = input.bytes[i];
    const long status = detect(byte, detect_special);

    if (status < OPC_OK) {
      return status;
    }

    if (status == OPC_NOT_DETECTED) {
      output->bytes[size++] = byte;
    } else {
      output->bytes[size++] = '%';

      if (size >= output->size) {
        return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[byte >> 4];

      if (size >= output->size) {
        return opc_throw(OPC_OUT_OF_MEMORY, "Output bytes out of memory.");
      }

      output->bytes[size++] = DEC2HEX[byte & 0x0f];
    }
  }

  return size;
}

OPCSize
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input) {
  return opc_uri_component_encode_(output, input, false);
}

static OPCSize
opc_uri_component_encode_size_ (
  const OPCBuffer input,
  OPCBoolean detect_special
) {
  OPCSize size = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  for (int i = 0; i < input.size && input.bytes[i] != 0; ++i) {
    OPCByte byte = input.bytes[i];
    const long status = detect(byte, detect_special);

    switch (status) {
      case OPC_NOT_DETECTED:
        size++;
        break;
      case OPC_DETECTED:
        size = size + 3; // %XX
        break;
      default:
        return status;
    }
  }

  return (long) size;
}

OPCSize
opc_uri_component_encode_size (const OPCBuffer input) {
  return opc_uri_component_encode_size_(input, false);
}

OPCSize
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input) {
  OPCSize size = 0;

  if (output->bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Output bytes cannot be NULL");
  }

  if (input.bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Input bytes cannot be NULL");
  }

  for (int i = 0; i < input.size; ++i) {
    if (input.bytes[i] == 0)
      break;

    if (size >= output->size) {
      return opc_throw(OPC_OUT_OF_MEMORY, "Output out of memory");
    }

    if (input.bytes[i] == '%') {
      OPCSize x = HEX2DEC[input.bytes[i + 1]];
      OPCSize y = HEX2DEC[input.bytes[i + 2]];

      i = i + 2;

      output->bytes[size++] = (x << 4) + y;
    } else {
      output->bytes[size++] = input.bytes[i];
    }
  }

  return size;
}

OPCSize
opc_uri_component_decode_size (const OPCBuffer input) {
  OPCSize size = 0;
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

OPCResult
opc_uri_parse (OPCURI *self, const OPCBuffer input) {
  // parser static memory
  OPCByte memory[OPC_URI_MAX_BYTES] = { 0 };

  if (self == 0) {
    return opc_throw(OPC_NULL_POINTER, "OPCURI pointer cannot be NULL");
  }

  if (input.bytes == 0) {
    return opc_throw(OPC_NULL_POINTER, "Input bytes cannot be NULL");
  }

  if (input.size == 0) {
    return opc_throw(OPC_INVALID_ARGUMENT, "Input size cannot be 0");
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

  OPCUSize tmp_offset = 0;
  OPCUSize offset = 0;
  OPCInt state = NONE;

  // clang-format off
  OPCBufferStaticMap(tmp, output) buffers = {
    .output = opc_buffer_from(self->bytes, OPC_URI_MAX_BYTES),
    .tmp = opc_buffer_from(memory, sizeof(memory))
  };

  // reset URI buffers
  // clang-format on
  opc_buffer_set(&self->href, opc_bytes(""), 0);
  opc_buffer_set(&self->protocol, opc_bytes(""), 0);
  opc_buffer_set(&self->username, opc_bytes(""), 0);
  opc_buffer_set(&self->password, opc_bytes(""), 0);
  opc_buffer_set(&self->host, opc_bytes(""), 0);
  opc_buffer_set(&self->port, opc_bytes(""), 0);
  opc_buffer_set(&self->path, opc_bytes(""), 0);
  opc_buffer_set(&self->query, opc_bytes(""), 0);
  opc_buffer_set(&self->hash, opc_bytes(""), 0);

  // both `protocol` and `href` point to the beginning of `bytes`, which
  // is a static value and the first member of `OPCURI` so
  // `opc_string_print("%s", opc_string(opc_pointer(uri)));`
  self->protocol.bytes = self->bytes;
  self->href.bytes = self->bytes;

  state = PROTOCOL;

  for (int i = 0; i < input.size; ++i) {
    OPCByte byte = input.bytes[i];
    OPCUSize written = 0;

    if (offset >= buffers.output.size) {
      return opc_throw(OPC_OUT_OF_MEMORY, "Out of memory");
    }

    // protocol://username:password@host:port
    if (state < PATH) {
      written = opc_buffer_write(&buffers.output, opc_bytes(&byte), offset, 1);

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
          OPCBuffer slice = opc_buffer_slice(input, i + 1, i + 3);
          written = opc_buffer_write_buffer(&buffers.output, slice, offset);

          if (written < 0) {
            break;
          }

          offset += written;
          state = USERNAME;
          opc_buffer_set(&self->username, buffers.output.bytes + offset, 0);
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
          opc_buffer_set_buffer(&self->host, self->username);
          self->host.size = self->username.size;
          self->host.bytes = self->username.bytes;
          self->username.size = 0;
          self->username.bytes = opc_bytes("");
        } else if (state == HOST) {
        } else {
          return opc_throw(OPC_MALFORMED_URI, "Invalid state in URI parser");
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

  opc_catch(err) {
    return opc_rethrow_error(err);
  }

  self->href.size = offset - 1;

  opc_log_alertb(self->href);

  return OPC_OK;
}

static void
uri_format (OPCString string, const OPCString format, const OPCURI self) {
  // NOLINTNEXTLINE
  opc_string_nformat(
    opc_string(string),
    OPC_URI_MAX_BYTES,
    "%.*s%.*s%.*s%.*s%.*s",
    opc_int(self.protocol.size),
    opc_string(self.protocol.bytes),
    opc_int(self.host.size),
    opc_string(self.host.bytes),
    opc_int(self.path.size),
    opc_string(self.path.bytes),
    opc_int(self.query.size),
    opc_string(self.query.bytes),
    opc_int(self.hash.size),
    opc_string(self.hash.bytes)
  );
}

static void
uri_fprintf (OPCHandle stream, const OPCString format, const OPCURI self) {
  OPCChar string[OPC_URI_MAX_BYTES] = { 0 };
  uri_format(string, format, self);
  opc_string_fprintf(stream, "%s\n", string);
}

void
opc_uri_print (const OPCURI self) {
  uri_fprintf(opc_stdout(), "%s\n", self);
}

OPCSize
opc_uri_encode (OPCBuffer *output, const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_encode_size (const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_decode (OPCBuffer *output, const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_decode_size (const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_file_encode (OPCBuffer *output, const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_file_encode_size (const OPCBuffer input) {
  return OPC_FILE_URI_PREFIX_SIZE + opc_uri_component_encode_size(input);
}

OPCSize
opc_uri_file_decode (OPCBuffer *output, const OPCBuffer input) {
  return 0;
}

OPCSize
opc_uri_file_decode_size (const OPCBuffer input) {
  return 0;
}
