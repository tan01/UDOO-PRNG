#include "key_gen.h"
#include "mod_exp.h"

// PUBKEY defines the public key exponent used in RSA.
#define PUBKEY 65537
// PQBITS defines the bit length of the two private key primes
#define PQBITS 32

/*
int public_key(){
	return 65537;
}
*/

/* 
 * private_key(BIGNUM* n: return value)
 * Generates two PQBITS-sized primes and computes their product
 * output:
 * 	BIGNUM* n
 * return value 1: if success
 */
int private_key(BIGNUM* n){
	BIGNUM* p = BN_new();
	BIGNUM* q = BN_new();

	generate_p_q(PQBITS, p, q);
	compute_key(p,q,n);

	BN_free(p);
	BN_free(q);

	return 1;
}

/*
 * rsa_encrypt(M, n, C)
 * encrypts the inputs M and n using the rsa encryption function and stores
 * the resulting value into C. M^e mod n.
 *
 * input:	BIGNUM* M
 * 		BIGNUM* n
 * output:	BIGNUM* C
 * return value: 1 if success
 *
 */
int rsa_encrypt(BIGNUM* M, BIGNUM* n, BIGNUM* C){
	BIGNUM * e = BN_new();
	unsigned long word = PUBKEY;
	BN_set_word(e, word);

	mod_exp_binary(M, e, n, C);

	BN_free(e);

	return 1;
}

