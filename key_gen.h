#include <openssl/bn.h>
#include <openssl/bio.h>

int compute_key(BIGNUM* p, BIGNUM* q, BIGNUM* key);

int generate_p_q(int bit_length, BIGNUM* p, BIGNUM* q);

int prime_totient(BIGNUM* p, BIGNUM* q, BIGNUM* totient);
