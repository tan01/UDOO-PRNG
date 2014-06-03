#include "rsa.h"
#include <stdio.h>

int main(){
	BIGNUM* p = BN_new();
	BIGNUM* q = BN_new();
	BIGNUM* M = BN_new();
	BIGNUM* e = BN_new();
	BIGNUM* f = BN_new();

	BN_zero(f);
	BN_zero(e);
	BN_zero(M);

	BN_set_word(M, 2);
	BN_set_word(e, 2);
	BN_set_word(f, 8);


	BIO *out = NULL;
	out = BIO_new(BIO_s_file());

	BIO_set_fp(out, stdout, BIO_NOCLOSE);

	generate_p_q(32,p,q);

	char* decimal_p = BN_bn2dec(p);
	char* decimal_q = BN_bn2dec(q);

	BN_print(out, p);

	printf("\n\n");

	//BN_print(out, q);
	//print_result(q);

	BIGNUM* key = BN_new();
	BIGNUM* totient = BN_new();
	
	compute_key(p,q,key);
	prime_totient(p,q,totient);

	char* decimal_k = BN_bn2dec(key);
	char* decimal_t = BN_bn2dec(totient);

	printf("Key: %s\n", decimal_k);
	printf("Totient of p:%s\n times totient of q:%s\n is %s\n", decimal_p, decimal_q, decimal_t);

	BIGNUM* res = BN_new();

	mod_exp_binary(M, e, f, res);

	char* decimal_res = BN_bn2dec(res);

	printf("exp_mod: %s\n", decimal_res);

	encrypt(M, key, res);
	decimal_res = BN_bn2dec(res);
	printf("rsa: %s\n", decimal_res);

	return 0;
}
