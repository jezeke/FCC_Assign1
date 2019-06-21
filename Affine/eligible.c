#include "affine.h"

int valid(int a, int width)
{ /*only valid if a and width of character set are coprimes*/
  return (gcd(a, width) == 1) ? 1: 0;
}
