#include "sdes.h"

int main(int argc, char *argv[])
{ //all errors are handled at the bottom
  ErrorFlag error = NONE;
  FILE *input = NULL;
  FILE *output = NULL;

  if(argc == 5) //no args are optional
  { //args: 1=-e or -d, 2=input filename, 3=output filename 5=key string
    input = fopen(argv[2], "r");
    if(input != NULL)
    {
      output = fopen(argv[3], "w");
      if(output != NULL)
      {
        if(!strcmp(argv[1], "-d"))
        {
          decrypt(input, output, argv[4]);
        }
        else
        {
          if(!strcmp(argv[1], "-e"))
          {
            encrypt(input, output, argv[4]);
          }
          else
          {
            error = WRONG_FLAG;
          }
        }
      }
      else
      {
        error = BAD_OUTPUT;
      }
    }
    else
    {
      error = BAD_INPUT;
    }
  }
  else
  {
    error = WRONG_ARGS;
  }

  switch(error)
  {
    case NONE:
      fclose(input);
      fclose(output);
      break;
    case WRONG_FLAG: fprintf(stderr, "Second argument not recognized. Expecting -e or -d.\n");
      fclose(input);
      fclose(output);
      break;
    case BAD_INPUT: perror("Unable to load input file:");
      break;
    case BAD_OUTPUT: perror("Unable to open output file:");
      fclose(input);
      break;
    case WRONG_ARGS: fprintf(stderr, "Invalid arguments.\nExpecting form: sdes -e|-d \"/path/to the/input\" \"/path/to the/output\" \"key\"\n");
      break;
  }
}

uint8_t leftShiftWrap(uint8_t bits, uint8_t byte)
{ //circular leftshifts 5bits left n bits
  int i;

  for(i = 0; i < bits; i++)
  { // [0, 1, 2, 3, 4] -> [1, 2, 3, 4, 0] this is required for wrapping
    byte = ((byte & 0x00f) << 1)
  | ((byte & 0x010) >> 4); //i tried to figure a less weird way of doing this but gave up
  }

  return byte;
}

uint16_t keyChop(char *keyInput)
{ //turns string of chars into a ten-bit binary key
  uint16_t key = 0;
  int i = 0;

  while(i < (int)ceil(10.0/(double)sizeof(char)*8) && keyInput[i] != '\0')
  {
    key = key | ((uint16_t)keyInput[i] << (i*sizeof(char))*8);
    i++;
  }

  return key & 0x3FF; //chop to ten bits. 0x3ff == 0b1111111111 (ten bits)
}

void generateKeys(uint8_t *k1, uint8_t *k2, char *keyInput)
{
  uint16_t key;
  uint8_t left5, right5;

  key = keyChop(keyInput);

  key = permute10(key);

  printf("10bit key: %u\n", key);

  left5 = key & 0x1F; //just get rightmost five bits. 0x1F == 0b0000011111
  right5 = key & 0x3E0 >> 5; //get leftmost and shift to back least sig bit. 0x3E0 == 0b1111100000

  left5 = leftShiftWrap(1, left5);
  right5 = leftShiftWrap(1, right5);

  *k1 = permute8(right5 | (left5 << 5));

  left5 = leftShiftWrap(2, left5);
  right5 = leftShiftWrap(2, right5);

  *k2 = permute8(right5 | (left5 << 5));

  printf("k1 = %u, k2 = %u.\n", *k1, *k2);
}

uint8_t f(uint8_t val, uint8_t key)
{
  uint8_t temp = permuteEP(val) ^ key; //this value is stored so it isn't calculated twice
  return permute4(sbox2(temp & 0x0F) |  (sbox1((temp & 0xF0) >> 4) << 2)); //xor with k1, split into 2x4bytes, left-half to s0 and right half to s1. recombined and then passed through p4.
}

uint8_t fk(uint8_t input, uint8_t key)
{
  uint8_t left = (input & 0xF0) >> 4;
  uint8_t right = input & 0x0F;

  return right | ((left ^ f(right, key)) << 4);
}

void encrypt(FILE *input, FILE *output, char *key)
{
  uint8_t k1, k2;

  generateKeys(&k1, &k2, key);

  crypt(k1, k2, input, output);
}

void decrypt(FILE *input, FILE *output, char *key)
{ //only difference to encrypt func is subkey order
  uint8_t k1, k2;

  generateKeys(&k1, &k2, key);

  crypt(k2, k1, input, output); //key order swapped when decrypting
}

void crypt(uint8_t k1, uint8_t k2, FILE *input, FILE *output)
{ //as encryption is just decryption with the key order swapped, the two can be combined
  char next;

  while(fread(&next, 1, 1, input) != 0) //performance bottleneck
  {
    fprintf(output, "%c", permuteIPInverse(fk(permuteSwitch(fk(permuteIP((uint8_t)next), k1)), k2)));
  }
}
