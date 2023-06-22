#ifndef ALU_H
#define ALU_H

#include "commonenums.h"
#include "ieeefloat.h"

/**
 * @class ALU
 * @brief ALU class for performing IEEE 754 float arithmetic operations.
 */
class ALU {
private:
  /**
   * @brief Perform one's complement on a 24-bit unsigned longeger.
   * @param num The number to perform one's complement on.
   * @return The result of the one's complement operation.
   */
  unsigned long onesComplement(unsigned long num);

  /**
   * @brief Perform two's complement on a 24-bit unsigned longeger.
   * @param num The number to perform two's complement on.
   * @return The result of the two's complement operation.
   */
  unsigned long twosComplement(unsigned long num);

  /**
   * @brief Check if an IEEE 754 float is denormal.
   * @param num The IEEE 754 float to check.
   * @return True if the float is denormal, false otherwise.
   */
  bool isDenormal(IEEEFloat num);

  /**
   * @brief Changes the sign of a number
   * @param op
   * @return
   */
  IEEEFloat changeSign(IEEEFloat op);

  /**
   * @brief Makes a number positive
   * @param op
   */
  void makePositive(IEEEFloat &op);

  /**
   * @brief Perform addition of two IEEE 754 floats.
   * @param op1 The first operand.
   * @param op2 The second operand.
   * @return The result of the addition as an IEEEFloat.
   */
  IEEEFloat add(IEEEFloat op1, IEEEFloat op2);

  /**
   * @brief Perform multiplication of two IEEE 754 floats.
   * @param op1 The first operand.
   * @param op2 The second operand.
   * @return The result of the multiplication as an IEEEFloat.
   */
  IEEEFloat multiply(IEEEFloat op1, IEEEFloat op2);

  /**
   * @brief Perform multiplication of two unsigned longegers without
   * considering the sign.
   * @param mant1 The first operand.
   * @param mant2 The second operand.
   * @return The result of the multiplication as an unsigned longeger.
   */
  unsigned long multiplyWithoutSign(unsigned long mant1, unsigned long mant2);

  /**
   * @brief Aproximating table for inverse of a real number (for division)
   * @param op
   * @return
   */
  IEEEFloat inverseTable(IEEEFloat op);

  /**
   * @brief Perform division of two IEEE 754 floats.
   * @param op1 The first operand.
   * @param op2 The second operand.
   * @return The result of the division as an IEEEFloat.
   */
  IEEEFloat divide(IEEEFloat a, IEEEFloat b);

public:
  /**
   * @brief Constructor for the ALU class.
   */
  ALU();

  /**
   * @brief Perform an arithmetic operation on two IEEE 754 floats.
   * @param op1 The first operand.
   * @param op2 The second operand.
   * @param op The arithmetic operation to be performed (addition,
   * multiplication or division).
   * @return The result of the arithmetic operation as an IEEEFloat.
   */
  IEEEFloat operate(IEEEFloat op1, IEEEFloat op2, Operation op);
};

#endif // ALU_H
