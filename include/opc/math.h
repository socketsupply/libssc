#ifndef OPC_MATH_H
#define OPC_MATH_H

/**
 * Computes a value between `min` and `max`.
 * @param value
 * @param min
 * @param max
 * @return A value between `min` and `max`
 */
#define opc_math_clamp(value, min, max) ({                   \
  min < max                                                  \
    ? ((value) < min ? min : (value) > max ? max : (value))  \
    : ((value) < max ? max : (value) > min ? min : (value)); \
})

/**
 * Detects if an unsigned value is between `lo` and `hi`.
 * @param value
 * @param lo
 * @param hi
 * @return true (1) if `value` is in between `lo` and `hi`.
 */
#define opc_math_in_urange(value, lo, hi) (    \
  (unsigned int) value >= (unsigned int) lo && \
  (unsigned int) value <= (unsigned int) hi    \
)

#endif
