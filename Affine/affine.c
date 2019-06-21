#include "affine.h"

int main(int argc, char* argv[])
{
  ErrorFlag error = NONE;
  int a, b;

  if(argc == 5)
  {
    a = atoi(argv[3]); /*get key from args*/
    b = atoi(argv[4]);

    if(valid(a, 26)) /*26 is number of characters in latin alphabet*/
    {
      if(!strcmp(argv[2], "-d"))
      {
        decrypt(argv[1], a, b);
      }
      else
      {
        if(!strcmp(argv[2], "-e"))
        {
          encrypt(argv[1], a, b);
        }
        else
        {
          error = WRONG_FLAG;
        }
      }
    }
    else
    {
      error = BAD_KEY;
    }
  }
  else
  {
    error = WRONG_ARGS;
  }

  switch(error)
  {
    case NONE: printf("%s\n", argv[1]);
      break;
    case WRONG_FLAG: fprintf(stderr, "Second argument not recognized. Expecting -e or -d.\n");
      break;
    case BAD_KEY: fprintf(stderr, "Invalid key values. First key must be integer coprime with 26 and greater than zero. Second key must be integer greater than zero.\n");
      break;
    case WRONG_ARGS: fprintf(stderr, "Invalid arguments.\nExpecting form: affine \"message\" -e|-d <key1> <key2>\nWhere key1 is an integer greater than zero and coprime with 26, and key2 is an integer greater than zero.\n");
      break;
  }
}

void encrypt(char* str, int a, int b)
{
  int i = 0;

  while(str[i] != '\0')
  {
    if(str[i] >= 'a' && str[i] <= 'z')
    { //basic affine function but subtracting and adding 'a' before and after
      str[i] = ((((str[i] - 'a') * a) + b) % 26) + 'a';
    }
    else
    {
      if(str[i] >= 'A' && str[i] <= 'Z')
      {
        str[i] = ((((str[i] - 'A') * a) + b) % 26) + 'A';
      }

    }
    /*if not lower or upper case latin alphabet, do nothing*/
    i++;
  }
}

void decrypt(char* str, int a, int b)
{
  int i = 0;
  int inverse, x, y;

  gcdEx(26, a, &x, &y); /*calculate inverse of a for decryption*/
  inverse = (y > 0) ? y: 26 + y; /*fix if negative*/

  while(str[i] != '\0')
  {
    if(str[i] >= 'a' && str[i] <= 'z')
    {
      str[i] = ((str[i] - 'a' - b) * inverse) % 26;

      if(str[i] < 0)
      {
        str[i] += 26;
      }

      str[i] += 'a';
    }
    else
    {
      if(str[i] >= 'A' && str[i] <= 'Z')
      {
        str[i] = (((str[i] - 'A' - b) * inverse) % 26);

        if(str[i] < 0)
        {
          str[i] += 26;
        }

        str[i] += 'A';
      }
    }
    /*if not lower or upper case latin alphabet, do nothing*/
    i++;
  }
}

int gcd(int a, int b)
{ /*recursive function to calculate greatest common denominator of a and b*/
  return (a != 0) ? gcd(b%a, a): b;
}

int gcdEx(int a, int b, int *x, int *y)
{ /*extended euclidean implementation*/
  int val1, val2, ret;

  if(a == 0)
  {
    *x = 0;
    *y = 1;
    ret = b;
  }
  else
  {
    ret = gcdEx((b % a), a, &val1, &val2);
    *x = val2 - (b / a) * val1;
    *y = val1;
  }

  return ret;
}
