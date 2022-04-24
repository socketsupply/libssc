#ifndef OPC_MATH_H
#define OPC_MATH_H

#include "platform.h"

/**
 * Computes a value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return A value between `min` and `max`
 */
// clang-format off
#define opc_math_clamp_value(value, min, max) ({                               \
  ((min) < (max))                                                              \
    ? (value) < (min)                                                          \
      ? (min)                                                                  \
      : (value) > (max)                                                        \
        ? (max)                                                                \
        : (value)                                                              \
    : (value) < (max)                                                          \
      ? (max)                                                                  \
      : (value) > (min)                                                        \
        ? (min)                                                                \
        : (value);                                                             \
})
// clang-format on

/**
 * Computes an unsigned value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return An unsigned value between `min` and `max`
 */
OPC_EXPORT unsigned long long
opc_math_uclamp (
  unsigned long long value,
  unsigned long long min,
  unsigned long long max
);

/**
 * Computes a signed value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return An signed value between `min` and `max`
 */
OPC_EXPORT long long
opc_math_clamp (long long value, long long min, long long max);

/**
 * Detects if an unsigned value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
OPC_EXPORT OPCBoolean
opc_math_in_urange (
  unsigned long long value,
  unsigned long long lo,
  unsigned long long hi
);

/**
 * Detects if a signed value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
OPC_EXPORT OPCBoolean
opc_math_in_range (int value, int lo, int hi);

#endif
