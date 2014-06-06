#include "key_gen.h"
#include "mod_exp.h"

#define PQBITS 32

int rabin_public_key(){
	return 3;
}

int rabin_private_key(BIGNUM* n){
	BIGNUM* p = BN_new();
	BIGNUM* q = BN_new();

	generate_p_q(PQBITS, p, q);
	compute_key(p,q,n);

	BN_free(p);
	BN_free(q);

	return 1;
}

/*
 * rabin_encrypt(M, n, C)
 * encrypts the inputs M and n using the rabin encryption function and stores
 * the resulting value into C. M^2 mod n.
 *
 * input:	BIGNUM* M
 * 		BIGNUM* n
 * output:	BIGNUM* C
 * return value: 0 if success
 *
 */

int rabin_encrypt(BIGNUM* M, BIGNUM* n, BIGNUM* C){
	BIGNUM * two = BN_new();
	//unsigned long word = public_key();
	BN_set_word(two, 2);

	mod_exp_binary(M, two, n, C);

	BN_free(two);

	return 0;
}

