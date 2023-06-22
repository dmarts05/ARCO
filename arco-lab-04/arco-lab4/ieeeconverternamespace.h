#ifndef IEEECONVERTERNAMESPACE_H
#define IEEECONVERTERNAMESPACE_H

#include "ieeefloat.h"
#include <string>

/**
 * @brief Namespace for IEEE 754 conversion functions.
 */
namespace IEEEConverter {
/**
 * @brief Convert a float number to its IEEE 754 representation.
 * @param value The float number to be converted.
 * @return The IEEE 754 representation of the input number as a
 * IEEEFloat struct.
 */
IEEEFloat floatToIEEE(float value);

/**
 * @brief Convert an IEEE 754 representation to a float number.
 * @param sign The sign bit of the IEEE 754 representation (0 for positive, 1
 * for negative).
 * @param expo The exponent bits of the IEEE 754 representation.
 * @param fractPart The fraction part of the IEEE 754 representation.
 * @return The float number represented by the given IEEE 754 representation.
 */
float IEEEToFloat(unsigned int sign, unsigned int expo, unsigned int fractPart);

/**
 * @brief Convert a hexadecimal string to its IEEE 754 representation.
 * @param hexString The hexadecimal string to be converted.
 * @return The IEEE 754 representation of the input hexadecimal value as a
 * IEEEFloat struct.
 */
IEEEFloat hexToIEEE(std::string hexString);

/**
 * @brief Convert an IEEE 754 representation to a hexadecimal string.
 * @param ieeeF The IEEE 754 representation to be converted.
 * @return A hexadecimal string that represents the input IEEE 754
 * representation.
 */
std::string IEEEToHex(IEEEFloat ieeeF);

/**
 * @brief Convert a binary string to its IEEE 754 representation.
 * @param binaryStr The binary string to be converted.
 * @return The IEEE 754 representation of the input binary string as a
 * IEEEFloat struct.
 */
IEEEFloat binaryToIEEE(std::string binaryStr);

/**
 * @brief Convert an IEEE 754 representation to its binary string.
 * @param ieeeF The IEEEFloat struct representing the IEEE 754 number.
 * @return The binary string representing the input IEEE 754 number.
 */
std::string IEEEToBinary(IEEEFloat ieeeF);
} // namespace IEEEConverter

#endif // IEEECONVERTERNAMESPACE_H
