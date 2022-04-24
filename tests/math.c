#include "./test.h"

static const unsigned long long UMAX = -1;

test("math", 0) {
  assert(opc_math_clamp(1, 0, 2) == 1);
  assert(opc_math_clamp(-2, -3, 3) == -2);
  assert(opc_math_clamp(-128, -128, 128) == -128);
  assert(opc_math_uclamp(-2, -1, 2) == UMAX - 1);

  assert(opc_math_in_range(1, 0, 2));
  assert(opc_math_in_range(0, 0, 2));
  assert(opc_math_in_range(2, 0, 2));
  assert(!opc_math_in_range(-1, 0, 2));
  assert(!opc_math_in_range(3, 0, 2));
  assert(opc_math_in_urange(1, 0, 2));
  assert(opc_math_in_urange(0, 0, 2));
  assert(opc_math_in_urange(-1, 0, UMAX));
  assert(!opc_math_in_urange(-1, 0, UMAX - 2));
  assert(!opc_math_in_urange(-1, 0, 16));
}
