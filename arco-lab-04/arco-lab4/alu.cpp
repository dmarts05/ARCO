#include "alu.h"
#include <bitset>
#include <iostream>
#include <limits>
#include <stdexcept>

ALU::ALU() {}

unsigned long ALU::onesComplement(unsigned long num) {
  std::bitset<24> onesComplementBinary(num);
  onesComplementBinary = ~onesComplementBinary;

  unsigned long onesComplement = onesComplementBinary.to_ulong();
  return onesComplement;
}

unsigned long ALU::twosComplement(unsigned long num) {
  std::bitset<24> twosComplementBinary(num);
  twosComplementBinary = (~twosComplementBinary).to_ulong() + 1;

  unsigned long twosComplement = twosComplementBinary.to_ulong();
  return twosComplement;
}

bool ALU::isDenormal(IEEEFloat num) {
  return (num.bitfield.expo == 0) && (num.bitfield.fractPart != 0);
}

IEEEFloat ALU::changeSign(IEEEFloat op) {
  IEEEFloat opChanged = op;
  opChanged.bitfield.sign = (op.bitfield.sign == 0) ? 1 : 0;
  return opChanged;
}

void ALU::makePositive(IEEEFloat &op) { op.bitfield.sign = 0; }

IEEEFloat ALU::add(IEEEFloat op1, IEEEFloat op2) {
  IEEEFloat result;

  // Handle infinity as first operand
  if (op1.number == std::numeric_limits<float>::infinity() ||
      op1.number == -std::numeric_limits<float>::infinity()) {

    result.number = op1.number;
    return result;
    // Handle infinity as second operand
  } else if (op2.number == std::numeric_limits<float>::infinity() ||
             op2.number == -std::numeric_limits<float>::infinity()) {
    result.number = op2.number;
  }
  // Handle 0 as result
  // Case 1: 0 as both operands (0 + 0)
  // Case 2: operands have different signs and their absolute values are equal
  // (e.g. 1 + (-1))
  else if ((op1.number == 0 && op2.number == 0) ||
           ((op1.bitfield.sign != op2.bitfield.sign) &&
            std::abs(op1.number) == std::abs(op2.number))) {
    result.number = 0;
    return result;
  }
  // Handle 0 as one of the operands
  else if (op1.number == 0) {
    result.number = op2.number;
    return result;
  } else if (op2.number == 0) {
    result.number = op1.number;
    return result;
  }

  // Step 1
  unsigned long p = 0;
  unsigned long g = 0;
  unsigned long r = 0;
  unsigned long st = 0;
  unsigned long n = 24;
  bool areOperandsSwapped = false;
  bool isPComplemented = false;
  unsigned long carry1 = 0;
  unsigned long carry2 = 0;

  // Step 2
  // Extract the exponents of the operands. Set them to 1 if they are denormal
  unsigned long expo1 = isDenormal(op1) ? 1 : op1.bitfield.expo;
  unsigned long expo2 = isDenormal(op2) ? 1 : op2.bitfield.expo;

  // If the exponent of the first operand is smaller than the exponent of the
  // second operand, then swap the operands
  if (expo1 < expo2) {
    std::swap(op1, op2);
    areOperandsSwapped = true;
  }

  long expoS = 0;

  // Extract the mantissas of the operands and add the implicit 1 or 0
  // (denormal)
  unsigned long mant1 = isDenormal(op1) ? op1.bitfield.fractPart | 0x000000
                                        : op1.bitfield.fractPart | 0x800000;
  unsigned long mant2 = isDenormal(op2) ? op2.bitfield.fractPart | 0x000000
                                        : op2.bitfield.fractPart | 0x800000;

  unsigned long mantS = 0;

  unsigned long sign1 = op1.bitfield.sign;
  unsigned long sign2 = op2.bitfield.sign;
  unsigned long signS = 0;

  // Step 3
  expoS = op1.bitfield.expo;
  // Calculate the difference between the exponents of the operands
  int d = op1.bitfield.expo - op2.bitfield.expo;

  // Step 4
  // If the signs of the operands are different, then set mant2 to its 2's
  // complement
  if (sign1 != sign2) {
    mant2 = twosComplement(mant2);
  }

  // Step 5
  p = mant2;

  // Step 6: Assign...
  // Extract the binary representation of p
  std::bitset<24> pBinary(p);

  // Iterate over the d-1 least significant bits of p
  for (int i = d - 1; i >= 0; i--) {
    unsigned long currentBit = pBinary[i];

    // If this is the first bit we've extracted, assign it to g
    // Otherwise, leave g unchanged
    g = (i == d - 1) ? currentBit : g;

    // If this is the second bit we've extracted, assign it to r
    // Otherwise, leave r unchanged
    r = (i == d - 2) ? currentBit : r;

    // OR the current bit with the st variable
    // This sets st to 1 if any of the d-1 least significant bits of p_bits are
    // 1, and leaves it unchanged otherwise
    st |= currentBit;
  }

  // Step 7
  // If the signs of the operands are different, then introduce d 1s on the left
  // of p
  if (sign1 != sign2) {
    p = onesComplement(p);
    p >>= d;
    p = onesComplement(p);
  }
  // Otherwise, introduce d 0s on the left of p
  else {
    p >>= d;
  }

  // Step 8
  p += mant1;
  carry1 = (p >> n) & 1;

  // Step 9
  pBinary = std::bitset<24>(p);

  if (sign1 != sign2 && pBinary[n - 1] == 1 && carry1 == 0) {
    p = twosComplement(p);
    isPComplemented = true;
  }

  // Step 10
  pBinary = std::bitset<24>(p);

  if (sign1 == sign2 && carry1 == 1) {
    st = g | r | st;
    r = pBinary[0];
    p >>= 1;
    expoS += 1;
  } else {
    // Calculate the number of k bits to shift p so it becomes a normalized
    // mantissa (24 bits and p[23] = 1)
    int k = 0;
    unsigned long pCopy = p;
    std::bitset<24> pCopyBinary(pCopy);
    while (pCopyBinary[n - 1] == 0) {
      pCopy <<= 1;
      k++;
      pCopyBinary = std::bitset<24>(pCopy);
    }

    if (k == 0) {
      st = r | st;
      r = g;
    } else if (k > 1) {
      r = 0;
      st = 0;
    }

    // Add guard bit k times to the right of p
    if (g == 0) {
      p <<= k;
    } else if (g == 1) {
      p = onesComplement(p);
      p <<= k;
      p = onesComplement(p);
    }

    // Update result exponent
    expoS -= k;
  }

  // Step 11
  pBinary = std::bitset<24>(p);

  if ((r == 1 && st == 1) || (r == 1 && st == 0 && pBinary[0] == 1)) {
    // Add 1 to p
    p++;

    // Calculate carry bit 2
    carry2 = (p >> n) & 1;

    if (carry2 == 1) {
      // Shift p to the right by 1 bit
      p >>= 1;
      // Set the most significant bit of p to carry bit 2
      pBinary = std::bitset<24>(p);
      pBinary[n - 1] = carry2;

      // Update p with the new value of pBinary
      p = pBinary.to_ulong();

      // Increment the exponent of the result
      expoS++;
    }
  }

  mantS = p;

  // Step 12
  if (!areOperandsSwapped && isPComplemented) {
    signS = sign2;
  } else {
    signS = sign1;
  }

  // Step 13
  result.bitfield.sign = signS;
  result.bitfield.expo = expoS;
  result.bitfield.fractPart = mantS;

  // Check for underflow and set the exponent to 1 if that's the case
  if (expoS <= 0) {
    result.bitfield.expo = 1;
  }

  return result;
}

unsigned long ALU::multiplyWithoutSign(unsigned long mant1,
                                       unsigned long mant2) {
  // Initialize necessary variables
  unsigned long p = 0;
  unsigned long a = mant1;
  unsigned long c = 0;
  unsigned long n = 24;

  std::bitset<1> cBinary(c);
  std::bitset<24> pBinary(p);
  std::bitset<24> aBinary(a);
  std::bitset<49> cpaSet;

  // Iterate n times
  for (unsigned long i = 0; i < n; i++) {
    // If the least significant bit of a is 1, add mant2 to p and calculate
    // carry bit
    if (aBinary[0] == 1) {
      p += mant2;
      c = (p >> n) & 1;
    }
    // Otherwise, leave p and c unchanged
    else {
      p += 0;
    }

    // Update c an p values
    cBinary = std::bitset<1>(c);
    pBinary = std::bitset<24>(p);

    // Fill cpaSet with the values of c, p and a
    for (int j = 48; j >= 0; j--) {
      if (j == 48) {
        cpaSet[j] = cBinary[0];
      } else if (j >= 24 && j < 48) {
        cpaSet[j] = pBinary[j - 24];
      } else if (j < 24) {
        cpaSet[j] = aBinary[j];
      }
    }

    // Shift cpaSet to the right by 1 bit
    cpaSet >>= 1;

    // Update c, p and a values
    for (int j = 48; j >= 0; j--) {
      if (j == 48) {
        cBinary[0] = cpaSet[j];
      } else if (j >= 24 && j < 48) {
        pBinary[j - 24] = cpaSet[j];
      } else if (j < 24) {
        aBinary[j] = cpaSet[j];
      }
    }

    // Update c and p values (unsigned long)
    c = cBinary.to_ulong();
    p = pBinary.to_ulong();
  }

  // Fill product with the values of p and a
  std::bitset<48> product;

  for (int j = 47; j >= 0; j--) {
    if (j >= 24 && j < 48) {
      product[j] = pBinary[j - 24];
    } else if (j < 24) {
      product[j] = aBinary[j];
    }
  }

  // Return product (p, a)
  return product.to_ulong();
}

IEEEFloat ALU::multiply(IEEEFloat op1, IEEEFloat op2) {
  IEEEFloat result;

  // Check special cases (inf * 0, 0 * inf), if so return NaN as the result
  if (((op1.number == std::numeric_limits<float>::infinity() ||
        op1.number == -std::numeric_limits<float>::infinity()) &&
       op2.number == 0) ||
      ((op2.number == std::numeric_limits<float>::infinity() ||
        op2.number == -std::numeric_limits<float>::infinity()) &&
       op1.number == 0)) {
    result.number = std::numeric_limits<float>::quiet_NaN();
    return result;
  }
  // Check special cases (inf * inf, -inf * -inf, inf * -inf, -inf * inf)
  // inf * inf = inf
  else if (op1.number == std::numeric_limits<float>::infinity() &&
           op2.number == std::numeric_limits<float>::infinity()) {
    result.number = std::numeric_limits<float>::infinity();
    return result;
  }
  // -inf * -inf = inf
  else if (op1.number == -std::numeric_limits<float>::infinity() &&
           op2.number == -std::numeric_limits<float>::infinity()) {
    result.number = std::numeric_limits<float>::infinity();
    return result;
  }
  // inf * -inf = -inf
  else if (op1.number == std::numeric_limits<float>::infinity() &&
           op2.number == -std::numeric_limits<float>::infinity()) {
    result.number = -std::numeric_limits<float>::infinity();
    return result;
  }
  // -inf * inf = -inf
  else if (op1.number == -std::numeric_limits<float>::infinity() &&
           op2.number == std::numeric_limits<float>::infinity()) {
    result.number = -std::numeric_limits<float>::infinity();
    return result;
  }
  // Check special case 0 * 0, if so return zero as the result
  else if (op1.number == 0 || op2.number == 0) {
    result.number = 0;
    return result;
  }

  unsigned long n = 24;

  // Extract the mantissas of the operands and add the implicit 1 or 0
  // (denormal)
  unsigned long mant1 = isDenormal(op1) ? op1.bitfield.fractPart | 0x000000
                                        : op1.bitfield.fractPart | 0x800000;
  unsigned long mant2 = isDenormal(op2) ? op2.bitfield.fractPart | 0x000000
                                        : op2.bitfield.fractPart | 0x800000;

  // Step 1
  // Extract the signs of the operands and XOR them to get the sign of the
  // result
  unsigned long sign1 = op1.bitfield.sign;
  unsigned long sign2 = op2.bitfield.sign;
  unsigned long signP = sign1 ^ sign2;

  // Step 2
  // Calculate the exponent of the result by adding the exponents of the
  // operands and subtracting the bias
  long expoP = (op1.bitfield.expo + op2.bitfield.expo) - 127;

  // Step 3
  unsigned long p;
  // unsigned long a;

  // Calculate the product of the mantissas
  unsigned long product = multiplyWithoutSign(mant1, mant2);

  std::bitset<48> prodBinary(product);
  std::bitset<24> pBinary;
  std::bitset<24> aBinary;

  // Extract a and p from the product
  for (int j = 47; j >= 0; j--) {
    if (j >= 24 && j < 48) {
      pBinary[j - 24] = prodBinary[j];
    } else if (j < 24) {
      aBinary[j] = prodBinary[j];
    }
  }

  if (pBinary[n - 1] == 0) {
    // Shift p to the left by 1 if the most significant bit is 0
    prodBinary <<= 1;

    // Update p and a with the new values
    for (int j = 47; j >= 0; j--) {
      if (j >= 24 && j < 48) {
        pBinary[j - 24] = prodBinary[j];
      } else if (j < 24) {
        aBinary[j] = prodBinary[j];
      }
    }

    // Update p with its new binary value
    p = pBinary.to_ulong();
    // a = aBinary.to_ulong();
  } else {
    expoP++;
  }

  // Set rounding bit to aBinary most significant bit
  unsigned long r = aBinary[n - 1];

  // Initialize sticky bit to 0
  unsigned long st = 0;

  // Calculate sticky bit by ORing all the bits of aBinary
  for (unsigned long i = 0; i < n; i++) {
    st |= aBinary[i];
  }

  // Check if rounding is needed, if so increment p by 1
  if ((r == 1 && st == 1) || (r == 1 && st == 0 && pBinary[0] == 1)) {
    p++;
  }

  // Special cases from now on

  // Check if there's overflow, if so return infinity
  if (expoP >= 255) {
    result.number = std::numeric_limits<float>::infinity();
    return result;
  }
  // Check if there's underflow, if so return NaN
  else if (expoP <= 0) {
    // Calculate if bits need to be shifted to the right t times or return NaN
    // as the result
    unsigned long t = 0 - expoP;
    if (t >= n) {
      result.number = std::numeric_limits<float>::quiet_NaN();
      return result;
    } else {
      // Update product with new a and p values
      for (int j = 47; j >= 0; j--) {
        if (j >= 24 && j < 48) {
          prodBinary[j] = pBinary[j - 24];
        } else if (j < 24) {
          prodBinary[j] = aBinary[j];
        }
      }

      // Shift product to the right t times
      prodBinary >>= t;

      // Reset expoP to 0
      expoP = 0;

      // Update p and a with the new values
      for (int j = 47; j >= 0; j--) {
        if (j >= 24 && j < 48) {
          pBinary[j - 24] = prodBinary[j];
        } else if (j < 24) {
          aBinary[j] = prodBinary[j];
        }
      }
    }
  }

  // Check if one of the operands is denormal
  if (isDenormal(op1) || isDenormal(op2)) {
    if (expoP <= 0) {
      // Same procedure as with underflow
      unsigned long t = 0 - expoP;
      if (t >= n) {
        result.number = std::numeric_limits<float>::quiet_NaN();
        return result;
      } else {
        for (int j = 47; j >= 0; j--) {
          if (j >= 24 && j < 48) {
            prodBinary[j] = pBinary[j - 24];
          } else if (j < 24) {
            prodBinary[j] = aBinary[j];
          }
        }

        prodBinary >>= t;

        expoP = 0;

        for (int j = 47; j >= 0; j--) {
          if (j >= 24 && j < 48) {
            pBinary[j - 24] = prodBinary[j];
          } else if (j < 24) {
            aBinary[j] = prodBinary[j];
          }
        }
      }
    } else if (expoP > 0) {
      unsigned long t1 = expoP - 0;

      // Calculate the number of k bits to shift (p, a) so it becomes a
      // normalized mantissa
      int k = 0;
      unsigned long prodCopy = prodBinary.to_ulong();
      std::bitset<24> prodCopyBinary(prodCopy);
      while (prodCopyBinary[n - 1] == 0) {
        prodCopy <<= 1;
        k++;
        prodCopyBinary = std::bitset<24>(prodCopy);
      }

      unsigned long t2 = k;

      // Shift product to the left by t bits, where t is the minimum of t1 and
      // t2
      unsigned long t = std::min(t1, t2);
      prodBinary <<= t;
    } else if (expoP == 0) {
      // Denormalized result
      signP = 0;
      expoP = 0;
    }
  }

  // End special cases

  // Set result
  std::bitset<27> fractP;

  for (int j = 22; j >= 0; j--) {
    fractP[j] = pBinary[j];
  }

  result.bitfield.expo = expoP;
  result.bitfield.fractPart = fractP.to_ulong();
  result.bitfield.sign = signP;

  return result;
}

IEEEFloat ALU::inverseTable(IEEEFloat op) {
  IEEEFloat ret;
  if (op.number < 1.25) {
    ret.number = 1.00;
  } else {
    ret.number = 0.80;
  }
  return ret;
}

IEEEFloat ALU::divide(IEEEFloat a, IEEEFloat b) {

  // Check division by 0 -> returns NaN
  if (b.number == 0) {
    IEEEFloat result;
    result.number = std::numeric_limits<float>::quiet_NaN();
    return result;
  }

  // Handle both operands as infinite
  if ((a.number == std::numeric_limits<float>::infinity() ||
       a.number == -std::numeric_limits<float>::infinity()) &&
      (b.number == std::numeric_limits<float>::infinity() ||
       b.number == -std::numeric_limits<float>::infinity())) {

    IEEEFloat result;
    if ((a.number > 0 && b.number > 0) || (a.number < 0 && b.number < 0))
      result.number = std::numeric_limits<float>::infinity();
    else
      result.number = -std::numeric_limits<float>::infinity();
    return result;
  }

  // Step 1: Escalate...
  IEEEFloat aEsc = a;
  makePositive(aEsc);
  aEsc.bitfield.expo = 127;

  IEEEFloat bEsc = b;
  makePositive(bEsc);
  bEsc.bitfield.expo = 127;

  // Step 2: Get 1/b...
  IEEEFloat bInv = inverseTable(bEsc);

  // Step 3: Asign Xo, Yo...
  IEEEFloat X = multiply(aEsc, bInv);
  IEEEFloat Y = multiply(bEsc, bInv);

  // Step 4: Iterate...
  IEEEFloat two;
  two.number = 2.00;
  IEEEFloat oldX, dif;

  do {
    IEEEFloat r = add(two, changeSign(Y));
    Y = multiply(Y, r);
    oldX = X;
    X = multiply(X, r);

    dif = add(X, changeSign(oldX));
    dif.bitfield.sign = 0;

  } while (dif.number >= 0.0001);

  // Step 5: Get sign...
  unsigned int divSign = a.bitfield.sign ^ b.bitfield.sign;

  // Step 6: Get exponent...
  unsigned int divExp = a.bitfield.expo - b.bitfield.expo + X.bitfield.expo;

  // Check for infinite result
  if (divExp >= 255) {
    IEEEFloat ret;
    ret.number = (divSign == 0) ? std::numeric_limits<float>::infinity()
                                : -std::numeric_limits<float>::infinity();
    return ret;
  }

  // Step 7: Final result...
  IEEEFloat result;
  result.bitfield.sign = divSign;
  result.bitfield.expo = divExp;
  result.bitfield.fractPart = X.bitfield.fractPart;

  return result;
}

IEEEFloat ALU::operate(IEEEFloat op1, IEEEFloat op2, Operation op) {
  switch (op) {
  case Operation::ADDITION:
    return add(op1, op2);
  case Operation::MULTIPLICATION:
    return multiply(op1, op2);
  case Operation::DIVISION:
    return divide(op1, op2);
  default:
    throw std::runtime_error("Invalid operation.");
  }
}
