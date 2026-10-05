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

#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x&~y)&~(~x&y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x) {
  int sign = x>>31;
  int neg = ~x+1;
  return sign & neg;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int a = (x>>(src<<3))&0xFF;
  int b = x&(~(0xFF<<(dst<<3)));
  return (a<<(dst<<3))|b;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x>>n)&~(((1<<31)>>n)<<1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask;
  int a;
  int b;
  mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  a = (x & mask) << 4;
  b = ((x & ~mask) >> 4) & mask;
  return a | b;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int first_zero;
  int x2;
  int second_zero;
  first_zero = ~x & (x + 1);
  x2 = x | first_zero;
  second_zero = ~x2 & (x2 + 1);
  return second_zero;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int a = (x >> 28) & 0xF;
  int b = (x >> 24) & 0xF;
  int c = (x >> 20) & 0xF;
  int d = (x >> 16) & 0xF;
  int e = (x >> 12) & 0xF;
  int f = (x >> 8) & 0xF;
  int g = (x >> 4) & 0xF;
  int h = x & 0xF;
  int y = a ^ b ^ c ^ d ^ e ^ f ^ g ^ h;
  y = y ^ (y >> 2);
  y = y ^ (y >> 1);
  return !(y & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int a = (x >> n) & ~(((1 << 31) >> n) << 1);
  int b = x << ((~n + 1) & 31);
  return a|b;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int quo = (x>>n)&1;
  int bias = (1<<(n+~0))+~0;
  return ((quo + bias + x)>> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int half_x = x >> 1;
  int half_y = y >> 1;
  int half = half_x + half_y + (x & y & 1);
  int is_odd_sum = (x ^ y) & 1;
  int sx = x >> 31;
  int sy = y >> 31;
  int is_diff_sign = sx ^ sy;
  int x_minus_y = x + ~y + 1;
  int x_big_diff_sign = ~sx;
  int x_big_same_sign = ~(x_minus_y >> 31);
  int is_x_big = (is_diff_sign & x_big_diff_sign) | (~is_diff_sign & x_big_same_sign);
  return half + (is_odd_sum & is_x_big & 1);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int diff_a = (x^a)>>31;
  int sub_a = x+~a+1;
  int sign_x_a = (diff_a & (x>>31))|(~diff_a & (sub_a>>31));
  int diff_b = (x^b)>>31;
  int sub_b = x+~b+1;
  int sign_x_b = (diff_b & (x>>31))|(~diff_b & (sub_b>>31));
  int in_range = (sign_x_a ^ sign_x_b);
  int is_endpoint = !(x^a)|!(x^b);
  return (in_range&1)|is_endpoint;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */

int mul5Sat(int x) {
  int x4 = x << 2;
  int x5 = x4 + x;
  int ov_shift = (!!((x >> 29) ^ (x >> 31))) << 31 >> 31;
  int ov_add = (~(x4 ^ x) & (x4 ^ x5)) >> 31;
  int overflow = ov_shift | ov_add;
  int INT_MIN = 1 << 31;
  int INT_MAX = ~INT_MIN;
  int x_sign = x >> 31;
  int INT = (x_sign & INT_MIN) | (~x_sign & INT_MAX);
  return (overflow & INT) | (~overflow & x5);
}


// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  return 14;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf&0x80000000;
  unsigned exp = (uf>>23)&0xff;
  unsigned frac = uf&0x7fffff;

}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  return 16;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign;
  unsigned ux;
  unsigned frac;
  unsigned exp;
  unsigned mask;
  unsigned out;
  unsigned half;
  int e;
  if (x == 0) return 0;
  sign = x & 0x80000000;
  ux = x;               
  if (x < 0) ux = -ux;  
  e = 31;
  while (!(ux & (1u << e))) {
    e--;
  }
  exp = e + 127;
  if (e <= 23) {
    frac = (ux << (23 - e)) & 0x7fffff;
  } else {
    frac = (ux >> (e - 23)) & 0x7fffff;
    mask = (1 << (e - 23)) - 1;
    out = mask & ux;
    half = 1 << (e - 24);
    if (out > half) {
      frac++;
    } else if (out == half) {
      if (frac & 1) frac++;
    }
  }
  if (frac == (1 << 23)) {
    frac = 0;
    exp++;
  }
  return sign | (exp << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1;
  int mask2;
  int mask3;
  int mask4;
  int sum1;
  int sum2;
  int sum3;
  int sum4;
  mask1 = (0x11<<8)|0x11;
  mask1 = mask1|(mask1<<16);
  sum1 = (x&mask1)+((x>>1)&mask1)+((x>>2)&mask1)+((x>>3)&mask1);
  mask2 = (0x0f<<8)|0x0f;
  mask2 = (mask2<<16)|mask2;
  sum2 = (sum1&mask2)+((sum1>>4)&mask2);
  mask3 = 0xFF | (0xFF << 16);
  sum3 = (sum2 & mask3) + ((sum2 >> 8) & mask3);
  mask4 = 0xFF | (0xFF << 8);
  sum4 = (sum3 & mask4) + ((sum3 >> 16) & mask4);
  return sum4;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int re1;
  int re2;
  int re3;
  int re4;
  int re5;
  re1 = ((x>>1)&0x55555555)|((x&0x55555555)<<1);
  re2 = ((re1>>2)&0x33333333)|((re1&0x33333333)<<2);
  re3 = ((re2>>4)&0x0f0f0f0f)|((re2&0x0f0f0f0f)<<4);
  re4 = ((re3>>8)&0x00ff00ff)|((re3&0x00ff00ff)<<8);
  re5 = ((re4>>16)&0x0000ffff)|((re4&0x0000ffff)<<16);
  return re5;
}
