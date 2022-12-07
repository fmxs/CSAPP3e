/*
 * CS:APP Data Lab
 *
 * <Jiayan Xu>
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
 *  1.使用dlc编译器检查您的解决方案是否符合编码规则。
 *  2.使用BDD检查器正式验证您的解决方案是否产生正确答案。
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  /*exploit ability of ~ to compute xor
   *使用~运算符将x按位取反，得到的结果和y按位相与，就得到了按位异或*/
  return (~x) & y;
}
/*
 * tmin - return minimum two's complement integer  返回最小的二进制补码
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  /*最小补码的位置在环的右下角靠左，右下角对应的二进制为100...00
  由于这里是32位，将1左移31位，也就是补31个0，这样得到了最小补码*/
  return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  /*最大补码的位置在环的右下角靠右，对应二进制为0111...11*/
  int max = 0x11111111 >> 1;
  /*将x与最大补码异或，如果得到结果为0，说明x是最大补码，函数返回1*/
  int flag = x ^ max;
  return !flag;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  /*先按位相与*/
  int temp = x & 0xAAAAAAAA;
  /*按位异或*/
  int result = temp ^ 0xAAAAAAAA;
  /*如果result为0，需要返回1；如果result不等于0，返回0*/
  return !result;
}
/*
 * negate - return -x  不用负号得到 -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  /*将x按位取反，然后+1，得到的结果就是环上x对应的相反数*/
  return ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  /*将x右移4位，得到x的高四位，再与3异或*/
  /*以上运算结果为0，说明符合要求，将flag置为true*/
  int flag_high = !((x >> 4) ^ 3);
  /*将x与0x01相与，得到x的低四位*/
  int low = x & 0x01;
  /*将x的低四位右移3位，再和0异或，如果得到结果为0，说明符合，flag_lowHigh置true*/
  int flag_lowHigh = !((low >> 3) ^ 0);
  /*将x的低四位右移1位，和4异或，如果得到结果为0，说明符合，flag_lowThree为true*/
  int flag_lowThree = !((low >> 1) ^ 4);
  return flag_high & ((flag_lowHigh) | (!flag_lowHigh & flag_lowThree));
}
/*
 * conditional - same as x ? y : z  写一个三目运算符，当x非0，返回y，否则返回z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  /*
   *if x!=0, mask=0x00000000, then y&~mask = y, z&mask = 0
   *if x==0, mask=0xffffffff, then y&~mask = 0; z&mask = z
   */
  int mask = ~!x + 1;
  return (y & ~mask) | (z & mask);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  /*x y同号，返回0，0表示同号；否则返回1，1表示异号*/
  int diffSign = (x >> 31) ^ (y >> 31);
  /*第一种情况，x负，且y正，那么返回1，1表示x<=y*/
  int xLessYSign = (x >> 31) & diffSign;
  /*第二种情况，xy同号，且y与x相反数的和无溢出，那么返回1, 1表示x<=y*/
  int overFlowSign = !diffSign & !((y + (~x + 1)) >> 31);
  return xLessYSign | overFlowSign;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
  /*取反+1，得到的结果和原始值按位或，接着取反，最后右移31位*/
  return (~((~x + 1) | x)) >> 31;
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
int howManyBits(int x)
{
  /*【负数转非负数】如果是负数，按位取反；非负数，就不变*/
  x = x ^ (x >> 31);
  /*求和*/
  int n = 0;
  /*x右移16位，用!!判断结果a是否为0，若a为1，1右移4位得到16，n+=16；若a为0，n+=0*/
  n = n + ((!!(x >> (n + 16))) << 4);
  /*x右移8位，同理，若结果不为0，则n+=8，若为0，n+=0*/
  n = n + ((!!(x >> (n + 8))) << 3);
  /*x右移4位，同理*/
  n = n + ((!!(x >> (n + 4))) << 2);
  /*x右移2位，同理*/
  n = n + ((!!(x >> (n + 2))) << 1);
  /*x右移1位，同理*/
  n = n + ((!!(x >> (n + 1))) << 0);
  /*符号位?*/
  n = n + (x >> n);
  /*为什么n+1?*/
  return n + 1;
}
// float
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
unsigned floatScale2(unsigned uf)
{
  unsigned f = uf;
  // 当exp = 111...1
  if ((f ^ 0x7F800000) == 0)
  {
    // 尾数不为0则尾数左移1位，尾数第1位为1则阶码加1，尾数为0则uf为0返回0
    f = ((f & 0x007FFFFF) << 1) | (f & 0x800000000);
  }
  // 当exp != 111...1，将uf乘2，也就是阶码+1
  else if ((f & 0x7F800000) != 0x7F800000)
  {
    f = f + 00800000;
  }
  return f;
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
int floatFloat2Int(unsigned uf)
{
  unsigned f = uf;
  // 特殊情况，阶码全1
  if (f ^ 0x7F800000 == 0)
  {
    return 0x80000000;
  }
  // 求指数exp
  int exp = ((f >> 23) & 0x000000FF) - 127;
  // 如果指数exp < 0，就是负指数，返回0
  if (exp < 0)
  {
    return 0;
  }
  // 保留frac中的前exp位，并将浮点数第23位置1，得到真值
  int restFrac = ((f & 0x007FFFFF) || 0x00800000) >> (23 - exp);
  // 将真值与符号位拼接，并返回
  int flag = 1;
  if (f >> 31 == 1)
  {
    flag = -1;
  }
  int result = restFrac * flag;
  return result;
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
unsigned floatPower2(int x)
{
  // 根据浮点数公式，2^x == (-1)^0 * 1.0 * 2^x，所以符号s = 0，阶码exp = 2^x，frac = 0
  int exp = x + 127;
  if (exp >= 255)
  {
    return (0xFF << 23); // 0xFF << 23 记作 +INF
  }
  if (x < 0)
  {
    return 0;
  }
  return exp << 23;
}
