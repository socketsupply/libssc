#include <opc/opc.h>

unsigned long long
opc_math_uclamp (
  unsigned long long value,
  unsigned long long min,
  unsigned long long max
) {
  return opc_math_clamp_value(value, min, max);
}

/**
 * @TODO
 */
long long
opc_math_clamp (
  long long value,
  long long min,
  long long max) {
  return opc_math_clamp_value(value, min, max);
}
/**
 * Detects if an unsigned value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
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
/**
 * Detects if a signed value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
OPCBoolean
opc_math_in_range (int value, int lo, int hi) {
  return ((int) value >= (int) lo && (int) value <= (int) hi);
}
