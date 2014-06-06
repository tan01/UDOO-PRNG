#include "key_gen.h"
#include "mod_exp.h"

#define PQBITS 32

int public_key(){
	return 65537;
}

int private_key(BIGNUM* n){
	BIGNUM* p = BN_new();
	BIGNUM* q = BN_new();

	generate_p_q(PQBITS, p, q);
	compute_key(p,q,n);

	BN_free(p);
	BN_free(q);

	return 1;
}

int rsa_encrypt(BIGNUM* M, BIGNUM* n, BIGNUM* C){
	BIGNUM * e = BN_new();
	unsigned long word = public_key();
	BN_set_word(e, word);

	mod_exp_binary(M, e, n, C);

	BN_free(e);

	return 0;
}

