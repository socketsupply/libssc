#ifndef OPC_MATH_H
#define OPC_MATH_H

/**
 * @TODO(jwerle)
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

#endif
