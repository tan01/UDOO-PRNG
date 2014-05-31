#include <openssl/bn.h>

// return value is ev:
// 	0: failure
// 	1: success
int mod_exp_binary(BIGNUM* M, BIGNUM* e, BIGNUM* n, BIGNUM* result);
