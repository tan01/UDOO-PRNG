#include <openssl/bn.h>
#include <openssl/bio.h>
#include <timer.h>
#include "rsa.h"
#include "rabin.h"


unsigned char* rsa_bit_generator(BIGNUM* seed, unsigned long long bits);
