#ifndef IEEEFLOAT_H
#define IEEEFLOAT_H

/**
 * @union IEEEFloat
 * @brief Union representing a 32-bit IEEE 754 float.
 */
union IEEEFloat {
  struct {
    unsigned int fractPart : 23; ///< Mantissa of the IEEE 754 number.
    unsigned int expo : 8;       ///< Exponent part of the IEEE 754 number.
    unsigned int sign : 1; ///< Sign bit of the IEEE 754 number (0 for positive,
                           ///< 1 for negative).
  } bitfield;

  float number;         ///< Float represented by the IEEEFloat union.
  unsigned int numberx; ///< Raw binary representation of the Float.
};

#endif // IEEEFLOAT_H
