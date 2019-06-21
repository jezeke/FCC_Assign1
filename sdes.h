#include <stdio.h>
#include <math.h>
#include <string.h>
#include "permute.h"

typedef enum ErrorFlag {NONE, WRONG_FLAG, BAD_OUTPUT, BAD_INPUT, WRONG_ARGS} ErrorFlag;

uint8_t leftShiftWrap(uint8_t bits, uint8_t byte);

void generateKeys(uint8_t *k1, uint8_t *k2, char *keyInput);

uint8_t f(uint8_t val, uint8_t key);

uint8_t fk(uint8_t input, uint8_t key);

void encrypt(FILE *input, FILE *output, char *key);

void decrypt(FILE *input, FILE *output, char *key);

void crypt(uint8_t k1, uint8_t k2, FILE *input, FILE *output);

uint16_t keyChop(char *keyInput);
