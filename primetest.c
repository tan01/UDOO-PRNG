#include "key_gen.h"
#include "mod_exp.h"
#include <stdio.h>

int main(){
	BIGNUM* p = BN_new();
	BIGNUM* q = BN_new();

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
	printf("Totient of p:%s\n times totient of q:%s\n is\n%s", decimal_p, decimal_q, decimal_t);

	return 0;
}
