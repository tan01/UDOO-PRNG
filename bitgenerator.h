#include <openssl/bn.h>
#include <openssl/bio.h>
#include "rsa.h"

unsigned char* rsa_bit_generator(BIGNUM* seed, unsigned long long bits);
