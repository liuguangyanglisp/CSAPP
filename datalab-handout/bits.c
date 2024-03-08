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
  /*when x != y, bit is 1. Not sure what 0 represents now, maybe =, maybe !=.*/
  int xAndNotY = x & ~y; 
  int yAndNotX = y & ~x;

  /*0 represents x != y, 1 represents x = y. Combine to make sure every bit's meaning is clear. */
  int flipAndCombine = ~xAndNotY & ~yAndNotX;

  return ~flipAndCombine; /*use not to flip bit, bit is 0 when x = y, bit is 1 when x != y. */
  
  /*I spend at least 5 hours in this problem, because i misunderstanding Xor has to return 1 or 0. */
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
  /*if x is Tmax 0111..., then x + 1 is Tmin 1000...*/
  int Tmin = x + 1;
  /*use !Tmin to avoid situation x = 1111..., x + 1 = 0*/
  int Tmin_add0 = Tmin + !Tmin;
  /*Tmax ^ Tmin must return 111...*/
  int all1 = x^Tmin_add0;
  return !(~all1);
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
  /*and left half and right half of origin bits until 2 orginal bits remain. if any orgin odd bit is 0, the 1th bit is 0.
  right shift the 1th bit to 0, op& with 1, and return value. */
  int and_16bits = (x>>16) & x;
  int and_8bits = (and_16bits>>8) & and_16bits;
  int and_4bits = (and_8bits>>4) & and_8bits;
  int and_2bits = (and_4bits>>2) & and_4bits;
  int and_oddbit_wiht_1 = (and_2bits >> 1) & 1;/*if value is 1, it means all odd bits is 1.*/
  return and_oddbit_wiht_1;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*if x is Tmin, negate x = ~ x, x + ~x = 0, x + ~x + 1 = 1.
  else: negate x = ~x + 1, x + ~x + 1 = 0. */
  /*int z = x + ~x + 1;
  return ~x + !z*/
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
  int Tmin = 1<<31;
  int xsub30 = (x+(~0x30+1))&Tmin;
  int xsub39 = !((x+(~0x39+1+~1+1))&Tmin);
  int xbigthan0 = x&Tmin;
  int or = xsub30 | xsub39 | xbigthan0;
  return !or;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*if x is false, return z, else return y.*/
  int isfalse = !x; 
  int all_1or0 = (isfalse<<31)>>31;/*if x is false, return all 1. else all 0.*/
  int returnValue = (all_1or0 | y) & (~all_1or0 | z);
  return returnValue;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int ysubx = y + (~x + 1);
  int sub_morethan0 = !(ysubx & (1<<31));
  return sub_morethan0;
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
  int and_16bits = (x>>16) | x;
  int and_8bits = (and_16bits>>8) | and_16bits;
  int and_4bits = (and_8bits>>4) | and_8bits;
  int and_2bits = (and_4bits>>2) | and_4bits;
  int and_1bits = (and_2bits>>1) | and_2bits;
  int lastbitValue = and_1bits & 1;
  return (~lastbitValue) + 2;
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
  int sign = x>>31;
  x = (x&(~sign)) | ((~x)&sign);
  
  int s30 = !(x>>30);
  int s29 = !(x>>29);
  int s28 = !(x>>28);
  int s27 = !(x>>27);
  int s26 = !(x>>26);
  int s25 = !(x>>25);
  int s24 = !(x>>24);
  int s23 = !(x>>23);
  int s22 = !(x>>22);
  int s21 = !(x>>21);
  int s20 = !(x>>20);
  int s19 = !(x>>19);
  int s18 = !(x>>18);
  int s17 = !(x>>17);
  int s16 = !(x>>16);
  int s15 = !(x>>15);
  int s14 = !(x>>14);
  int s13 = !(x>>13);
  int s12 = !(x>>12);
  int s11 = !(x>>11);
  int s10 = !(x>>10);
  int s9 = !(x>>9);
  int s8 = !(x>>8);
  int s7 = !(x>>7);
  int s6 = !(x>>6);
  int s5 = !(x>>5);
  int s4 = !(x>>4);
  int s3 = !(x>>3);
  int s2 = !(x>>2);
  int s1 = !(x>>1);
  int num = s1+s2+s3+s4+s5+s6+s7+s8+s9+s10+s11+s12+s13+s14+s15+s16+s17+s18+s19+s20+s21+s22+s23+s24+s25+s26+s27+s28+s29+s30;
  int subnum = 32+(~num)+ !(!x);
  return subnum;
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
  /*if uf = 0, return uf. */
  if (!uf || !(uf+uf))
  {
    return uf;
  }

  unsigned sign = uf&(1<<31);
  unsigned ex = (uf>>23)&0xff;
  unsigned exAreOne = !(ex+ (~255 + 1));
  unsigned frarHelp = (~(0x1ff<<23));/*9zeros, 23ones*/
  unsigned frac = frarHelp&uf;
  unsigned newEx = ((ex+1)&0xff)<<23;
  unsigned newFrac = frac;
  unsigned newf = sign + newEx +newFrac;

  /*1. normal, ex!=0 !=255*/

  if (ex && !exAreOne)
  {
  return newf;
  }

  /*2. denormal, ex = 0. */
  /*if ex not 0. */
  newFrac = frac<<1;
    /*if frac overflow, ex + 1. if not, still ex.*/
  if (!(newFrac>>23))
  {
    newEx = ex;
  }
  newFrac = frarHelp&newFrac;
  newf = sign + newEx +newFrac;


  /*3. if arg is nan or infinity, return arg.*/
  if (exAreOne)
  {
    return uf;
  }

  return newf;
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
  unsigned sign = uf&(1<<31);
  unsigned e = (uf>>23)&0xff;/*8 exp bits*/
  unsigned exAreOne = !(e+ (~255 + 1));
  unsigned fracHelp = (~(0x1ff<<23));/*9zeros, 23ones*/
  unsigned frac = fracHelp&uf;
  int bias = 127;
  int E = e+(~bias+1);
  unsigned twoPowerE = 1;

   /*if e = 0, E<0, |float|<1, int = 0. */
  if (!e || E>>31)
  {
    return 0;
  }

  /*if out of range, return 0x80000000u*/

  int EbigThan30 = !((E+(~31+1))>>31);

  if (exAreOne  || EbigThan30)
  {
    return 0x80000000u;
  }

  /*normal float values, e!=0 !=255, 0<=E<=30. */
 while (E)
    {
      twoPowerE = twoPowerE<<1;/*evaluate 2^E. */
      E = E-1;
    }
    
    /*returnValue = (-1)^sing + (1+frac)*2^E. */
    int returnValue = twoPowerE; 

    int i = 23;
    while (frac)
    {
      int fracBit = frac&1;
      int fracBitValue = twoPowerE>>i; /*if fracbit*2^E <1, round to zero. */
      if (fracBit || fracBitValue)
      {
        returnValue = returnValue + fracBitValue;
      }
      frac = frac>>1;
      i = i-1;
    }
    if(sign) {
      returnValue = ~returnValue + 1;/*if arg f is negative, return negate returnValue. */
    }
  return returnValue;
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
  unsigned e = (x+127)&0xff;
  unsigned newe =e<<23;
  unsigned returnValue = 0|newe;
  int xBigThan127 = !((x+(~128+1))>>31);
  int xlessThanN126 = (x+126)>>31;
  if (xBigThan127)
  {
    return 0x7f800000;/*positive infinity. */
  }
  
  if (xlessThanN126)
  {
    return 0;
  }

  return returnValue;
}
