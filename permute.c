#include "permute.h"

//bit manipulations required for permutations generated using http://programming.sirrida.de/calcperm.php
//gen refers to actual shifting occuring - which is expected shift transposed around center and order reversed

uint16_t permute10(uint16_t input)
{ //[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] -> [2, 4, 1, 6, 3, 9, 0, 8, 7, 5]
  return ((input & 0x002) << 1) //gen 4 2 1 9 0 6 3 8 5 7
  | ((input & 0x080) << 2)  //0=9, 1=8, 2=7, 3=6, 4=5
  | ((input & 0x028) << 3)
  | ((input & 0x001) << 4)
  | ((input & 0x200) >> 6)
  | ((input & 0x010) >> 4)
  | ((input & 0x144) >> 1);
}

uint8_t permute8(uint16_t input)
{ //[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] -> [5, 2, 6, 3, 7, 4, 9, 8]
  return ((input & 0x005) << 1) //gen 1, 0, 5, 2, 6, 3, 7, 4
  | ((input & 0x008) << 2)
  | ((input & 0x010) << 3)
  | ((input & 0x020) >> 3)
  | ((input & 0x040) >> 2)
  | ((input & 0x082) >> 1);

}

uint8_t permute4(uint8_t input)
{ //[0, 1, 2, 3] -> [1, 3, 2, 0]
  return (input & 0x002) //gen 3 1 0 2
  | ((input & 0x004) << 1)
  | ((input & 0x001) << 2)
  | ((input & 0x008) >> 3);
}

uint8_t permuteIP(uint8_t input)
{ //[0, 1, 2, 3, 4, 5, 6, 7] -> [1, 5, 2, 0, 3, 7, 4, 6]
  return (input & 0x020) //gen 1 3 0 4 7 5 2 6
  | ((input & 0x040) << 1) //7=0, 6=1, 5=2, 4=3
  | ((input & 0x001) << 2)
  | ((input & 0x004) << 4)
  | ((input & 0x080) >> 3)
  | ((input & 0x008) >> 2)
  | ((input & 0x012) >> 1);
}

uint8_t permuteIPInverse(uint8_t input)
{ //[0, 1, 2, 3, 4, 5, 6, 7] -> [3, 0, 2, 4, 6, 1, 7, 5]
  return (input & 0x020) //gen 2 0 6 1 3 5 7 4
  | ((input & 0x009) << 1)
  | ((input & 0x002) << 2)
  | ((input & 0x010) << 3)
  | ((input & 0x040) >> 4)
  | ((input & 0x004) >> 2)
  | ((input & 0x080) >> 1);
}

uint8_t permuteEP(uint8_t input)
{ //[0, 1, 2, 3] -> [3, 0, 1, 2, 1, 2, 3, 0]
  return ((((input & 0x001) << 3) //gen 1 2 3 0 3 0 1 2
  | ((input & 0x00e) >> 1)) << 4)
  | ((input & 0x007) << 1)
  | ((input & 0x008) >> 3);
}

uint8_t permuteSwitch(uint8_t input)
{ //[0, 1, 2, 3, 4, 5, 6, 7] -> [4, 5, 6, 7, 0, 1, 2, 3]
  return ((input & 0x00f) << 4)
  | ((input & 0x0f0) >> 4);
}

uint8_t sbox1(uint8_t input)
{ //linearized, much faster than inner-outer comparison & table lookup
  int const sbox1[16] = {1, 3, 0, 2, 3, 1, 2, 0, 0, 3, 2, 1, 1, 3, 3, 2};

  return sbox1[input];
}

uint8_t sbox2(uint8_t input)
{
  int const sbox2[16] = {0, 2, 1, 0, 2, 1, 0, 3, 3, 2, 0, 1, 1, 0, 0, 3};

  return sbox2[input];
}
