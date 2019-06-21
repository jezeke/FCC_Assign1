#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ErrorFlag {NONE, WRONG_FLAG, BAD_KEY, WRONG_ARGS} ErrorFlag;

void encrypt(char* str, int a, int b);

void decrypt(char* str, int a, int b);

int gcd(int a, int b);

int gcdEx(int a, int b, int *x, int *y);

int valid(int a, int width); /*yes i know this belongs in a eligible.h but really eligible.c shouldn't be its own seperate file*/
