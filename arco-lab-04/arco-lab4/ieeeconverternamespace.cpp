#include "ieeeconverternamespace.h"
#include <bitset>
#include <iomanip>

namespace IEEEConverter {
IEEEFloat floatToIEEE(float value) {
  // Create a IEEEFloat struct to store the IEEE 754 representation
  IEEEFloat ieeeF;

  // Assign the input float number to its respective variable in the struct
  ieeeF.number = value;

  return ieeeF;
}

float IEEEToFloat(unsigned int sign, unsigned int expo,
                  unsigned int fractPart) {
  // Create a IEEEFloat struct to store the IEEE 754 representation
  IEEEFloat ieeeF;

  // Assign the input sign, exponent, and fraction parts to the respective
  // member variables of the struct
  ieeeF.bitfield.sign = sign;
  ieeeF.bitfield.expo = expo;
  ieeeF.bitfield.fractPart = fractPart;

  return ieeeF.number;
}

IEEEFloat hexToIEEE(std::string hexString) {
  // Remove 0x prefix if present
  if (hexString.substr(0, 2) == "0x") {
    hexString = hexString.substr(2);
  }

  // Convert the hexadecimal string to an unsigned integer
  unsigned int value;
  std::stringstream ss;
  ss << std::hex << hexString;
  ss >> value;

  // Convert the unsigned integer to its IEEE 734 representation
  IEEEFloat ieeeF;
  ieeeF.bitfield.sign = (value >> 31) & 1;
  ieeeF.bitfield.expo = (value >> 23) & 0xFF;
  ieeeF.bitfield.fractPart = value & 0x7FFFFF;

  return ieeeF;
}

std::string IEEEToHex(IEEEFloat ieeeF) {
  // Convert the bitfields to an unsigned integer
  unsigned int value = *(reinterpret_cast<unsigned int *>(&ieeeF));

  // Convert the unsigned integer to hexadecimal string
  std::stringstream ss;
  ss << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(value) * 2)
     << value;
  return ss.str();
}

IEEEFloat binaryToIEEE(std::string binaryStr) {
  // Convert the binary string to an unsigned integer
  std::bitset<32> bits(binaryStr);
  unsigned int value = bits.to_ulong();

  // Convert the unsigned integer to its IEEE 754 representation
  IEEEFloat ieeeF;
  ieeeF.bitfield.sign = (value >> 31) & 1;
  ieeeF.bitfield.expo = (value >> 23) & 0xFF;
  ieeeF.bitfield.fractPart = value & 0x7FFFFF;

  return ieeeF;
}

std::string IEEEToBinary(IEEEFloat ieeeF) {
  // Extract the sign bit, exponent bits, and fraction bits from the IEEE 754
  // representation
  std::bitset<1> signBit(ieeeF.bitfield.sign);
  std::bitset<8> expoBits(ieeeF.bitfield.expo);
  std::bitset<23> fractBits(ieeeF.bitfield.fractPart);

  // Return binary string
  return signBit.to_string() + expoBits.to_string() + fractBits.to_string();
}
} // namespace IEEEConverter
