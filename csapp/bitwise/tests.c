/* Testing Code */

#include <limits.h>
int test_bitNor(int x, int y)
{
  return ~(x|y);
}
int test_bitXor(int x, int y)
{
  return x^y;
}
int test_isNotEqual(int x, int y)
{
  return x != y;
}
int test_getByte(int x, int n)
{
  union {
    int word;
    unsigned char bytes[4];
  } u;
  int test = 1;
  int littleEndian = (int) *(char *) &test;
  u.word = x;
  return littleEndian ? (unsigned) u.bytes[n] : (unsigned) u.bytes[3-n];
}







int test_copyLSB(int x)
{
  return (x & 0x1) ? -1 : 0;
}
int test_logicalShift(int x, int n) {
  unsigned u = (unsigned) x;
  unsigned shifted = u >> n;
  return (int) shifted;
}



int test_bitCount(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result += (x >> i) & 0x1;
  return result;
}
int test_bang(int x)
{
  return !x;
}
int test_leastBitPos(int x) {
  int mask = 1;
  if (x == 0)
    return 0;
  while (!(mask & x)) {
    mask = mask << 1;
  }
  return mask;
}
int test_tmax(void) {
  return LONG_MAX;
}
int test_isNonNegative(int x) {
  return x >= 0;
}
int test_isGreater(int x, int y)
{
  return x > y;
}
int test_divpwr2(int x, int n)
{
    int p2n = 1<<n;
    return x/p2n;
}
int test_abs(int x) {
  return (x < 0) ? -x : x;
}
int test_addOK(int x, int y)
{
  int sum = x+y;
  return !(x < 0 && y < 0 && sum >= 0) && !(x > 0 && y > 0 && sum <= 0);
}
