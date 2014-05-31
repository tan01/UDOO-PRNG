#include "mod_exp.h"

int mod_exp_binary(BIGNUM* M, BIGNUM* e, BIGNUM* n, BIGNUM* result){

	// k = size of exponent

	BN_CTX *bn_ctx;
	BIGNUM *a;

	bn_ctx = BN_CTX_new();
	a = BN_new();

	// step1

	if( 1){
		// C = M
		BN_copy(result, M);
	}
	else{
		// C = 0
		BN_zero(M);
	}
	
	// step2
	
	for(int i=1;i<k;i++){

		BN_copy(a,result); //make copy of result ( C )

		//step 2a
		//C=C*C
		BN_sqr(result,a,bn_ctx);
		//C=C mod n
		BN_copy(a,result);
		BN_mod(result,a,n,bn_ctx);	
		//step2b
		if ( 1){
			//C=C*M
			BN_copy(a,result);
			BN_mul(result,a,M,bn_ctx);
			//C-C mod n
			BN_copy(a,result);
			BN_mod(result,a,n,bn_ctx);
		}

	}	

		


	BN_CTX_free(bn_ctx);
}
