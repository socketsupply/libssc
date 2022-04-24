#include <opc/opc.h>

unsigned long long
opc_math_uclamp (
  unsigned long long value,
  unsigned long long min,
  unsigned long long max
) {
  return opc_math_clamp_value(value, min, max);
}

long long
opc_math_clamp (long long value, long long min, long long max) {
  return opc_math_clamp_value(value, min, max);
}

OPCBoolean
opc_math_in_urange (
  unsigned long long value,
  unsigned long long lo,
  unsigned long long hi
) {
  return (
    (unsigned long long) value >= (unsigned long long) lo
    && (unsigned long long) value <= (unsigned long long) hi
  );
}

OPCBoolean
opc_math_in_range (int value, int lo, int hi) {
  return ((int) value >= (int) lo && (int) value <= (int) hi);
}
