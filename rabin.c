#include "key_gen.h"
#include "mod_exp.h"

#define PQBITS 32

int public_key(){
	return 3;
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

int encrypt(BIGNUM* M, BIGNUM* n, BIGNUM* C){
	BIGNUM * two = BN_new();
	//unsigned long word = public_key();
	BN_set_word(e, 2);

	mod_exp_binary(M, two, n, C);

	BN_free(two);

	return 0;
}
