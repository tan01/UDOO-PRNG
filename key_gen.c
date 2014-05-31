#include "key_gen.h"

/*
 *	compute_key(p,q,key)
 *	Generates an RSA/Rabin key from p and q. So multiplies them together.
 *	inputs:	BIGNUM* p
 *		BIGNUM* q
 *	outputs:	BIGNUM* key
 *
 *	return value:	0 if failure
 *			1 if success
 */
int compute_key(BIGNUM* p, BIGNUM* q, BIGNUM* key){
	BN_CTX* ctx = BN_CTX_new();
	if (BN_mul(key, p, q, ctx)){
		BN_CTX_free(ctx);
		return 1;
	} else {
		BN_CTX_free(ctx);
		return 0;
	}
}

/*
 * 	generate_p_q
 *	Generates two prime numbers of bit_length bit length, p and q
 *	inputs: 	int bit_length
 *	outputs:	BIGNUM* p
 * 			BIGNUM* q
 *
 *	return value:	0 if failure
 *			1 if success
 */
int generate_p_q(int bit_length, BIGNUM* p, BIGNUM* q){
	int res1 = BN_generate_prime_ex(p, bit_length, 0, NULL, NULL, NULL);
	int res2 = BN_generate_prime_ex(q, bit_length, 0, NULL, NULL, NULL);
	if ( res1 == 0 || res2 == 0 )
		return 0;
	else
		return 1;
}

/*	
 *	prime_totient(p,q,totient)
 *	Euler totient function of n, under the assumption
 *	that n = pq and p and q are prime
 *	inputs: BIGNUM* p
 *		BIGNUM* q
 *	output: BIGNUM* totient
 *
 *	return value: 	0 if failure
 *			1 if success
 */
int prime_totient(BIGNUM* p, BIGNUM* q, BIGNUM* totient){
	BIGNUM one;
	BN_init(&one);
	BN_one(&one);

	BIGNUM* temp_p = BN_dup(p);
	BIGNUM* temp_q = BN_dup(q);

	BN_sub_word(temp_p, 1);
	BN_sub_word(temp_q, 1);

	BN_CTX* ctx = BN_CTX_new();

	BN_mul(totient, temp_p, temp_q, ctx);

	BN_free(temp_p);
	BN_free(temp_q);
	BN_CTX_free(ctx);

	return 1;
}
