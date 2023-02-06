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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ~(~(x & ~y) & ~(~x & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    return !(~(x + 1) ^ x) & !!(~x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    // get long allOdd1 = 0xaaaa aaaa aaaa aaaa;

    // 00000000 00...00 00000000 10101010
    // 00000000 00...00 10101010 00000000;
    long last2Byte = 0xaa | (0xaa << 8);
    long allOdd = last2Byte | (last2Byte << 16);
    return !!!((x & allOdd) ^ allOdd);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // x - 39 <= 0;
    // ((x + (~(long)0x39)) >> 31) == -1
    //
    /* long res = ((x + (~(long)0x39)) >> 31) & (!(x + (~(long)0x2f)) >> 31); */
    return !!(((x + ~0x39) >> 31) & (!((x + ~0x2f) >> 31)));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // if x == 0:   bias == 1111...1111
    // if x != 0:   bias == 0000...0000
    int bias = (!x << 31) >> 31;
    return (y & ~bias) | (z & bias);;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

    return 1;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    // T(x): two's complement of x
    // if x != 0: x + T(x) < 1; (x + T(x)) >> 1 = 111...111
    //            111...111 + 1 = 0;
    // 
    // if x == 0: x + T(x) = 0; (x + T(x)) >> 1 = 0;
    //            0 + 1 = 1;
    return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /*
     * Thanks for Brian Magnuson, from https://stackoverflow.com/a/14676540/18553530
     *
     * We can think that all integers have one thing in common, some bits on the
     * left are all the same value (1 or 0), 
     * like(-2):    1111 1111 1111 1111 1111 1111 1111 1110
     *     (14):    0000 0000 0000 0000 0000 0000 0000 1110
     *
     * for(-2), We only need one number to hold the last binary digit: 0, The 
     * remaining digits are all 1.
     * 
     * for(14), we only need four number to hold the last four binary digit: 1110,
     * The remaining digits are all 0;
     *
     * But for uniform processing, we need to turn negative numbers into positive numbers.
     *
     * we assume that x is: 0001 1000 0111 1011 0101 1100 0001 0000
     */

    /* 
     * (x & ~sign) | (~x & sign): Negative numbers can be all inverted, 
     * while positive numbers remain unchanged.
     *
     * if x >= 0:  x >> 31 --> 000...000, sign = 000...000, x & ~sign = x, ~x & sign = 0;
     *
     * if x <  0:  x >> 31 --> 111...111, sign = 111...111, x & ~sign = 0, ~x & sign = ~x;
     */
    int sign = (x >> 31);
    x = (x & ~sign) | (~x & sign);


    /*
     * Notes: The numbers in parentheses are the numbers of x itself.
     * x:              (0001 1000 0111 1011  0101 1100 0001 0000)
     * x >> 16:         0000 0000 0000 0000 (0001 1000 0111 1011) 
     * 
     * We can find that if the result is greater than 0 after x >> 16, 
     * it means that x requires at least 16 bits to represent.
     *
     * But it is not enough to know that x requires at least 16 bits to represent, 
     * we need to know how many bits. So you can record 16 to prepare for how many 
     * bits are most needed later.
     * 
     * The value obtained by shifting x to the right by 16 bits will get 
     * 1 or 0 after two inversions, and after continuing to shift left by 4 bits, 
     * it will get 16 or 0, which is exactly the value we need.
     */
    int half = !!(x >> 16) << 4;
    int res = half;

    /*
     * It is now known that x requires at least 16 bits to represent, 
     * and it has been recorded with the variable res.
     *
     * Go ahead and consider how many bits are needed to represent the leftmost 16 bits of x.
     * x >> res(16):    0000 0000 0000 0000 (0001 1000  0111 1011)
     * x >> res >> 8:   0000 0000 0000 0000  0000 0000 (0001 1000) 
     *
     * The shifted result is still greater than 0, so x requires at least res + 8 = 24 bits to represent.
     */
    int quater = !!(x >> res >> 8) << 3;
    res += quater;

    /*
     * x >> res(24):    0000 0000 0000 0000 0000 0000 (0001 1000)
     * x >> res >> 4:   0000 0000 0000 0000 0000 0000  0000 (0001) 
     *
     * The shifted result is still greater than 0, so x requires at least res + 4 = 28 bits to represent.
     */
    int oneEight = !!(x >> res >> 4) << 2;
    res += oneEight;

    /* step(a):
     *
     * x >> res(28):    0000 0000 0000 0000 0000 0000  0000 (0001)
     * x >> res >> 2:   0000 0000 0000 0000 0000 0000  0000 00(00)
     *
     * The result of the shift is finally equal to 0, but we should not terminate the calculation,
     * because we stand in the perspective of God, we know that the result is 0 at this time,
     * but the computer does not know.
     *
     * We continue with the remaining 4 bits numbers.
     *
     * Please remember that at this time res = 28.
     */
    int oneSixteenth = !!(x >> res >> 2) << 1;
    res += oneSixteenth;

    /* step(b):
     *
     * x >> res(28):    0000 0000 0000 0000 0000 0000  0000 (0001)
     * x >> res >> 1:   0000 0000 0000 0000 0000 0000  0000 0(000)
     *
     * The result of the shift is still 0.
     *
     * This time res = 28;
     */
    int oneThirty_Two = !!(x >> res >> 1);
    res += oneThirty_Two;

    /* step(c):
     *
     * x >> res(28):    0000 0000 0000 0000 0000 0000  0000 (0001)  --> 1
     */
    res += x >> res;

    /*
     * At this time, the number of bits in res can represent all numbers of x except the sign,
     * so add 1 to res to represent x.
     */
    return res + 1;

    /* remind:
     *
     * Before (step a), we only have 4 bits left to judge.
     * After three steps of a, b, c, We can find out exactly how many 
     * bits are needed to represent those 4 bits.
     */
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
