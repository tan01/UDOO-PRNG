#include <openssl/bn.h>
#include <openssl/bio.h>
#include "rsa.h"
#include "rabin.h"

unsigned char* rsa_char_generator(BIGNUM* seed, unsigned long long bits);

unsigned char* rsa_bit_generator(BIGNUM* seed, unsigned long long bits);

unsigned char* rabin_char_generator(BIGNUM* seed, unsigned long long bits);

unsigned char* rabin_bit_generator(BIGNUM* seed, unsigned long long bits);
