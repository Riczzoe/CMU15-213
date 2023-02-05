/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  2. Function arguments and local variables (no global variables).
  3. Local variables of type int and long
  4. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  5. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  6. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

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

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
// 2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
    // Assuming the least significant bit is a,
    // x << 63         --> a0000...00000
    // (X << 63) >> 63 --> aaaa...aaaaaa
    return (x << 63) >> 63;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 63 (most significant)
 *   Examples: allOddBits(0xFFFFFFFDFFFFFFFDL) = 0L,
 *             allOddBits(0xAAAAAAAAAAAAAAAAL) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 2
 */
long allOddBits(long x) {
    // get long allOdd1 = 0xaaaa aaaa aaaa aaaa;

    // 00000000 00...00 00000000 10101010
    // 00000000 00...00 10101010 00000000;
    long last2Byte = 0xaa | (0xaa << 8);
    long last4Byte = last2Byte | (last2Byte << 16);
    long allOdd1 = last4Byte | (last4Byte << 32);
    return !!!((x & allOdd1) ^ allOdd1);
}
/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5L, 5L) = 0L, isNotEqual(4L, 5L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
long isNotEqual(long x, long y) {
    return !!(x ^ y);
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
    long bias = (x >> 63) & ~(~(long)0 << n);
    return (x + bias) >> n;
}
// 3
/*
 * remainderPower2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: remainderPower2(15L,2L) = 3, remainderPower2(-35L,3L) = -3L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
long remainderPower2(long x, long n) {
    // if n == 0; !n -> 1, !n << 63 == T(min), !n << 63 >> 63 == -1 (all 1)
    // if n != 0; !n -> 0, !n << 63 >> 63 = 0;
    // solve the n = 0 case
    x = x & (~(((long)!n << 63) >> 63));
    long sign = x >> 63 << n;
    long bias = ~(~(long)0 << n);
    long remainder = x & bias;

    // if remainder == 0; ignore sign
    return (remainder + sign) & (~(((long)!remainder << 63) >> 63));
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 63
 *   Examples:
 *      rotateLeft(0x8765432187654321L,4L) = 0x7654321876543218L
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
long rotateLeft(long x, long n) {
    long bias = ~(long)0 << n;
    long left = (x << n) & bias;
    long right = (x >> (65 + ~n)) & (~bias);
    return left | right;
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   between lowbit and highbit
 *   Examples: bitMask(5L,3L) = 0x38L
 *   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long bitMask(long highbit, long lowbit) {
    long zero = 0;
    long diff = highbit + ~(lowbit + ~0);
    long length = diff & (~(diff >> 63));
    return (~(~(long)zero << length << ((long)1 & (~(diff >> 63)))) << lowbit);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5L) = 0L, isPower2(8L) = 1L, isPower2(0) = 0L
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
long isPower2(long x) {
    // turn all negative numbers to 0
    long bias = ~x >> 63;
    x = x & bias;

    // if x is a power of 2 --> 000..0001000..0000 (only one 1)
    //                x - 1 --> 000..0000111..1111
    //
    // x * (x - 1) There will be two situations :
    //      1. x == 0:  (x & (x - 1)) --> 00000...000000
    //      2. x != 0 && x is power of 2: --> 000000...00000
    //
    return (!(x & (x + ~0))) & (!!x);
}
// 4
/*
 * allAsciiDigits - return 1 if each byte b in x satisfies
 *   0x30 <= b <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: allAsciiDigits(0x3031323536373839L) = 1L.
 *            allAsciiDigits(0x4031323536373839L) = 0L.
 *            allAsciiDigits(0x0031323536373839L) = 0L.
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 30
 *   Rating: 4
 */
long allAsciiDigits(long x) {
    // for 1 byte(b):
    // b - 39 <= 0;
    // ((x + (~(long)0x39)) >> 31) == -1
    //
    /* long res = ((x + (~(long)0x39)) >> 31) & (!(x + (~(long)0x2f)) >> 31); */
    /* printf("%lx: %lx\n", x, res); */
    return ((x + (~(long)0x39)) >> 31) & (!(x + (~(long)0x2f)) >> 31);
    /* return 0; */
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples:
 *    trueThreeFourths(11L) = 8
 *    trueThreeFourths(-9L) = -6
 *    trueThreeFourths(4611686018427387904L) = 3458764513820540928L (no
 * overflow) Legal ops: ! ~ & ^ | + << >> Max ops: 20 Rating: 4
 */
long trueThreeFourths(long x) {
    long bias = (x >> 63) & 0x3;

    long originRem = x & 0x3;
    long remMul3 = (originRem << 1) + originRem;
    long remFnal = (remMul3 + bias) >> 2;

    long div4 = x >> 2;
    long div4Mul3 = (div4 << 1) + div4;

    return div4Mul3 + remFnal;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5L) = 2, bitCount(7L) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
long bitCount(long x) {
    long x_0f_2 = ((long)0x0f << 8) | 0x0f;
    long x_0f_4 = (x_0f_2 << 16) | x_0f_2;
    long x_0f_8 = (x_0f_4 << 32) | x_0f_4;

    long x_33_8 = x_0f_8 ^ (x_0f_8 << 2);
    long x_55_8 = x_33_8 ^ (x_33_8 << 1);
    /* printf("x_55_8: %lx\nx_33_8: %lx\n", x_55_8, x_33_8); */

    // x & x_55_8:  all odd 1
    // (x >> 1) & x_55_8: all odd 1
    // think about the following number(32 bits):
    // x & x_55_8:
    // x:                   0110 1011 1001 0010 1010 0000 1111 1000
    // x_55_8:              0101 0101 0101 0101 0101 0101 0101 0101
    // x & x_55_8:          0100 0001 0001 0000 0000 0000 0101 0000
    //
    // (x >> 1) & x_55_8:
    // x >> 1:              0011 0101 1100 1001 0101 0000 0111 1100
    // x_55_8:              0101 0101 0101 0101 0101 0101 0101 0101
    // (x >> 1) & x_55_8:   0001 0101 0100 0001 0101 0000 0101 0100
    //
    // x & x_55_8:          0100 0001 0001 0000 0000 0000 0101 0000
    // (x >> 1) & x_55_8:   0001 0101 0100 0001 0101 0000 0101 0100
    // res =                0101 0110 0101 0001 0101 0000 1010 0100
    //
    // each 2 bits of res indicates how many 1s there are in the two bits:
    // take the last 16 bits of res and x:
    // x(last 16 bits):     10 | 10 | 00 | 00 | 11 | 11 | 10 |00
    // res(last 16 bits):   01 | 01 | 00 | 00 | 10 | 10 | 01 |00
    //                       1    1    0    0    2    1    1   0
    //
    long res = (x & x_55_8) + ((x >> 1) & x_55_8);
    // 14 ops

    // now, each 4 bits of res represent how many 1s in the 4 bits
    res = (res & x_33_8) + ((res >> 2) & x_33_8);

    // each 8 bits of res represent how many 1s in the 8 bits
    // Notes: no matter how much x is, the number of 1s in every 8 bytes
    //        must be less than or equal to 8, which can be represented by only
    //        4 bytes.
    //
    // therefore, the first four bits of every eight bits of res must be 0, so
    // no mask is needed. x(last 16 bits):             1010 0000 | 1111 1000 now
    // res(last 16 bits) is:    0000 0010 | 0000 0101
    //                                      2           5
    //
    res = (res & x_0f_8) + ((res >> 4) & x_0f_8);

    res = (res >> 8) + res;
    res = (res >> 16) + res;
    res = (res >> 32) + res;

    // the maximum number of 1s in a 64-bit number is 64,
    // only 7 bits are needed to represent it
    res = res & 0x7f;

    return res;
}
