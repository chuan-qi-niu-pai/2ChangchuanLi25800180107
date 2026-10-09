/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
int signMask(void) {
    return 1 << 31;
}

// P2
int bitXor(int x, int y) {
    int nx = ~x;
    int ny = ~y;
    return ~(nx & ny) & ~(x & y);
}

// P3
int negativePart(int x) {
    int mask = x >> 31;
    return mask & (~x + 1);
}

// P4
int copyByteWithin(int x, int src, int dst) {
    int sShift = src << 3;
    int dShift = dst << 3;
    int byte = (x >> sShift) & 0xFF;
    int mask = 0xFF << dShift;
    return (x & ~mask) | (byte << dShift);
}

// P5
int logicalShift(int x, int n) {
    int amt = 31 + ~n + 1;           // 31 - n
    int mask = ~((~0 << amt) << 1);
    return (x >> n) & mask;
}

// P6
int swapNibblePairs(int x) {
    int m = 0x0F;
    m = m | (m << 8);
    m = m | (m << 16);
    int lo = x & m;
    int hi = x & (m << 4);
    return (lo << 4) | ((hi >> 4) & m);
}

// P7
int secondLowestZeroBit(int x) {
    int first = ~x & (x + 1);
    int x2 = x | first;
    return ~x2 & (x2 + 1);
}

// P8
int oddParity(int x) {
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return (x & 1) ^ 1;
}

// P9
int rotateRightBits(int x, int n) {
    int t = 32 + ~n + 1;            // 32 - n
    int lowMask = (1 << t) + ~0;
    return ((x >> n) & lowMask) | (x << t);
}

// P10
int roundEvenPow2(int x, int n) {
    int m = 1 << n;
    int half = m >> 1;
    int q = x >> n;
    int r = x & (m + ~0);
    int diff = r + ~half + 1;       // r - half
    int sign = diff >> 31;          // 0 if diff>=0, -1 if diff<0
    int eq = !diff;
    int greater = (sign + 1) + ~eq + 1;  // 1 if diff>0
    int qOdd = q & 1;
    int up = greater | (eq & qOdd);
    return (q + up) << n;
}

// P11
int midpointTowardFirst(int x, int y) {
    int base = (x & y) + ((x ^ y) >> 1);
    int tie = (x ^ y) & 1;
    int diff = x + ~y + 1;
    int signsDiff = (x ^ y) >> 31;
    int addSign = (signsDiff & (x >> 31)) | ((~signsDiff) & (diff >> 31));
    int xGTy = addSign + 1;
    return base + (tie & xGTy);
}

// P12
int isBetweenEitherOrder(int x, int a, int b) {
    int da = a + ~b + 1;
    int sd = (a ^ b) >> 31;
    int aGEb = (sd & ~(a >> 31)) | (~sd & ~(da >> 31));
    int n = ~aGEb;
    int ab = a ^ b;
    int lo = b ^ (ab & n);
    int hi = a ^ (ab & n);
    int sd1 = (x ^ lo) >> 31;
    int geLo = ~((sd1 & (x >> 31)) | (~sd1 & ((x + ~lo + 1) >> 31))) & 1;
    int sd2 = (hi ^ x) >> 31;
    int hiGEx = ~((sd2 & (hi >> 31)) | (~sd2 & ((hi + ~x + 1) >> 31))) & 1;
    return geLo & hiGEx;
}






// P13
int mul5Sat(int x) {
    int fourX = x << 2;
    int five = fourX + x;
    int sign = x >> 31;

    int overflow4 = (x >> 29) ^ sign;
    int overflowAdd = ((fourX ^ five) & (x ^ five)) >> 31;
    int overflow = !!(overflow4 | overflowAdd);

    int max = ~(1 << 31);
    int min = 1 << 31;
    int saturated = (sign & min) | (~sign & max);

    int mask = (~overflow) + 1;

    return (mask & saturated) | (~mask & five);
}












// P14
int classifyAdd3(int x, int y, int z) {
    int s = x + y;
    int r = s + z;
    int ov1neg = ((x & y & ~s)) >> 31;
    int ov1pos = ((~x & ~y & s)) >> 31;
    int ov2neg = ((s & z & ~r)) >> 31;
    int ov2pos = ((~s & ~z & r)) >> 31;
    int posOvf = (ov1pos & ~ov2neg) | (~ov1neg & ov2pos);
    int negOvf = (ov1neg & ~ov2pos) | (~ov1pos & ov2neg);
    return (posOvf & 1) | (negOvf + ~0 + 1);
}

// P15
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xFFu;
    unsigned frac = uf & 0x7FFFFFu;
    if (exp == 0xFFu) return uf;
    if (exp == 0u && frac == 0u) return uf;
    unsigned m; int e;
    if (exp == 0u) {
        m = frac; e = -126;
        while ((m & 0x800000u) == 0) { m <<= 1; e--; }
    } else {
        m = frac; e = exp - 127;
    }
    unsigned mant = (1u << 23) | m;
    unsigned prod = mant + mant + mant;
    e -= 1;
    unsigned roundBits = 0;
    while (prod >= (1u << 24)) { roundBits = (roundBits << 1) | (prod & 1u); prod >>= 1; e++; }
    unsigned frac2 = prod & 0x7FFFFFu;
    unsigned lsb = frac2 & 1u;
    unsigned guard = roundBits & 1u;
    unsigned sticky = roundBits >> 1;
    if (guard && (lsb || sticky)) frac2++;
    if (frac2 >= (1u << 23)) { frac2 = 0; e++; }
    e += 127;
    if (e <= 0) {
        if (e < -23) return sign;
        int shift = 1 - e;
        unsigned dm = prod >> shift;
        unsigned lost = prod & ((1u << shift) - 1);
        unsigned half = 1u << (shift - 1);
        if ((lost > half) || (lost == half && (dm & 1u))) dm++;
        if (dm >= (1u << 23)) return sign | (1u << 23) | (dm & 0x7FFFFFu);
        return sign | dm;
    }
    if (e >= 0xFF) return sign | (0xFFu << 23);
    return sign | (e << 23) | frac2;
}

// P16
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xFFu;
    unsigned frac = uf & 0x7FFFFFu;
    if (exp == 0xFFu) return uf;
    if (exp == 0u) return sign;
    int e = (int)exp - 127;
    if (e < 0) {
        if (e == -1 && frac > 0u) return sign | (127u << 23);
        return sign;
    }
    if (e >= 23) return uf;
    int shift = 23 - e;
    unsigned mask = (1u << shift) - 1;
    unsigned half = 1u << (shift - 1);
    unsigned rest = frac & mask;
    unsigned newFrac = frac & ~mask;
    unsigned lsb = (e == 0) ? 1u : ((frac >> (23 - e)) & 1u);
    if ((rest > half) || (rest == half && lsb)) {
        newFrac += (1u << shift);
    }
    if (newFrac >= (1u << 23)) { newFrac = 0; exp++; }
    return sign | (exp << 23) | newFrac;
}

// P17
unsigned float_i2f(int x) {
    if (x == 0) return 0u;
    if (x == 0x80000000) return 0xCF000000u;
    unsigned sign = x & 0x80000000u;
    unsigned v;
    if (x < 0) v = -x; else v = x;
    int e = 0;
    while ((v & 0x80000000u) == 0) { v <<= 1; e--; }
    e += 31;
    unsigned frac = (v >> 8) & 0x7FFFFFu;
    unsigned rest = v & 0xFFu;
    if ((rest > 0x80u) || (rest == 0x80u && (frac & 1u))) {
        frac++;
        if (frac >= 0x800000u) { frac = 0; e++; }
    }
    return sign | ((e + 127) << 23) | frac;
}

// P18
int bitCount(int x) {
    int m1 = 0x55;
    int m2 = 0x33;
    int m3 = 0x0F;
    m1 = m1 | (m1 << 8);
    m1 = m1 | (m1 << 16);      /* 0x55555555 */
    m2 = m2 | (m2 << 8);
    m2 = m2 | (m2 << 16);      /* 0x33333333 */
    m3 = m3 | (m3 << 8);
    m3 = m3 | (m3 << 16);      /* 0x0F0F0F0F */
    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m3) + ((x >> 4) & m3);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F;
}

// P19
int bitReverse(int x) {
    int m1 = 0x55 | (0x55 << 8); m1 = m1 | (m1 << 16);
    int m2 = 0x33 | (0x33 << 8); m2 = m2 | (m2 << 16);
    int m4 = 0x0F | (0x0F << 8); m4 = m4 | (m4 << 16);
    int m8 = 0xFF | (0xFF << 16);
    int m8b = m8 << 8;
    int m16 = 0xFF | (0xFF << 8);
    int m16b = m16 << 16;
    x = ((x >> 1) & m1) | ((x & m1) << 1);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    x = ((x >> 8) & m8) | ((x << 8) & m8b);
    x = ((x >> 16) & m16) | ((x << 16) & m16b);
    return x;
}


