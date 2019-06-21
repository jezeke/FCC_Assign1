#include "permute.h"
#include "sdes.h"

int main(int argc, char *argv[])
{
  uint8_t eightBit = 0x5F; //0b01011111
  uint8_t fourBit = 0x05; //0b0101
  long int tenBit = 0x02B2; //0b1010110010

  printf("P8 %u\n", permute8(tenBit)); //expected 0b11000101 aka 197
  printf("P10 %u\n", permute10(tenBit)); //expected 0b1100100110 aka 781
  printf("P4 %u\n", permute4(fourBit)); //expected 0b1100 aka 12
  printf("EP %u\n", permuteEP(fourBit)); //expected 0b10101010 aka 170
  printf("IPInv %u\n", permuteIPInverse(eightBit)); //expected 0b10011111 aka 159
  printf("IP %u\n", permuteIP(eightBit)); //expected 0b11001111 aka 207
  printf("SW %u\n", permuteSwitch(eightBit)); //expected 0b11110101 aka 245
  printf("SBOX0 %u\n", sbox1(fourBit)); //expected 1
  printf("SBOX1 %u\n", sbox2(fourBit)); //expected 1
}

/*int main(int argc, char *argv[])
{
  printf("P8 %u\n", permute8(0b1010110010)); //expected 0b11000101 got 0b11000101
  printf("P10 %u\n", permute10(0b1010110010)); //expected 0b1100100110 got 0b1100001101
  printf("P4 %u\n", permute4(0b1100)); //expected 0b1001 got 1001
  printf("EP %u\n", permuteEP(0b0010)); //expected 0b10000010 got 0b101000
  printf("IPInv %u\n", permuteIPInverse(0b11000001)); //expected 0b01000110 got 0b1000110
  printf("IP %u\n", permuteIP(0b01101101)); //expected 11100110 got 0b11100110
  printf("SW %u\n", permuteSwitch(0b01101101)); //expected 0b11010110 FINE
  printf("SBOX0 %u\n", sbox1(0b1011)); //expected 1 FINE
  printf("SBOX1 %u\n", sbox2(0b1111)); //expected 3 FINE
}*/
