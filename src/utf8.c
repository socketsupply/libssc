#include <opc/opc.h>

static const char UTF8_SAFE_CHARS[256] = {
  /*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
  /* 0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 1 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 2 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 3 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  /* 4 */ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  /* 5 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  /* 6 */ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  /* 7 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  /* 8 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* 9 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* A */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* B */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* C */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* D */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* E */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  /* F */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static OPCResult
detect (unsigned char x) {
  // alpha capital/small
  if (opc_math_in_urange(x, 'a', 'z') || opc_math_in_urange(x, 'A', 'Z')) {
    return OPC_NOT_DETECTED;
  }

  // decimal digits
  if (opc_math_in_urange(x, 0x0030, 0x0039)) {
    return OPC_NOT_DETECTED;
  }

  // special characters
  if (
		'-' == x || '_' == x || '.' == x || '!' == x ||
		'~' == x || '*' == x || '(' == x || ')' == x
	) {
    return OPC_NOT_DETECTED;
  }

  if (UTF8_SAFE_CHARS[x]) {
    return OPC_NOT_DETECTED;
  }

  return OPC_DETECTED;
}

OPCResult
opc_utf8_detect (const OPCBuffer input) {
  if (input.bytes == 0) {
    return OPC_NULL_POINTER;
  }

  if (input.size == 0) {
    return OPC_OUT_OF_MEMORY;
  }

  for (int i = 0; i < input.size; ++i) {
    OPCResult result = detect(input.bytes[i]);

    if (result != OPC_NOT_DETECTED) {
      return result;
    }
  }

  return OPC_NOT_DETECTED;
}
