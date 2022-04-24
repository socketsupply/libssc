#include <opc/opc.h>

// clang-format off
static const char DEC2HEX[16 + 1] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F',
	'0'
};

static const char HEX2DEC[256] = {
  /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
  /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

  /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

  /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

  /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
  /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

// clang-format on

OPCResult
opc_uri_component_encode (OPCBuffer *output, const OPCBuffer input) {
  unsigned long size = 0;

  if (output->bytes == 0 || input.bytes == 0) {
    return OPC_NULL_POINTER;
  }

  for (int i = 0; i < input.size; ++i) {
    if (size >= output->size) {
      return OPC_OUT_OF_MEMORY;
    }

    const long status = opc_utf8_detect(opc_buffer_slice(&input, i, i + 1));

    if (status < OPC_OK) {
      return status;
    }

    if (status == OPC_NOT_DETECTED) {
      output->bytes[size++] = input.bytes[i];
    } else {
      output->bytes[size++] = '%';

      if (size >= output->size) {
        return OPC_OUT_OF_MEMORY;
      }

      output->bytes[size++] = DEC2HEX[input.bytes[i] >> 4];

      if (size >= output->size) {
        return OPC_OUT_OF_MEMORY;
      }

      output->bytes[size++] = DEC2HEX[input.bytes[i] & 0x0f];
    }
  }

  output->size = size;

  return OPC_OK;
}

long
opc_uri_component_encode_size (const OPCBuffer input) {
  unsigned long size = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  for (int i = 0; i < input.size; ++i) {
    long status = opc_utf8_detect(opc_buffer_slice(&input, i, i + 1));

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

OPCResult
opc_uri_component_decode (OPCBuffer *output, const OPCBuffer input) {
  unsigned long size = 0;

  if (output->bytes == 0 || input.bytes == 0) {
    return OPC_NULL_POINTER;
  }

  for (int i = 0; i < input.size; ++i) {
    if (input.bytes[i] == 0)
      break;

    if (size >= output->size) {
      return OPC_OUT_OF_MEMORY;
    }

    if (input.bytes[i] == '%') {
      unsigned long x = HEX2DEC[input.bytes[i + 1]];
      unsigned long y = HEX2DEC[input.bytes[i + 2]];

      i = i + 2;

      output->bytes[size++] = (x << 4) + y;
    } else {
      output->bytes[size++] = input.bytes[i];
    }
  }

  output->size = size;

  return OPC_OK;
}

long
opc_uri_component_decode_size (const OPCBuffer input) {
  unsigned long size = 0;
  unsigned long length = input.size;
  int i = 0;

  if (input.bytes == 0 || input.size == 0) {
    return 0;
  }

  while (length-- && i < input.size) {
    if (input.bytes[i] == '%') {
      i = i + 3;
    } else {
      i = i + 1;
    }

    size = size + 1;
  }

  return size;
}
