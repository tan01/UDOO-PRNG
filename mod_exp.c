#include "mod_exp.h"

#include <openssl/bio.h>
#include <stdio.h>


void print_result(BIGNUM* result){
	BN_print_fp(stdout, result);
}
int mod_exp_binary(BIGNUM* M, BIGNUM* e, BIGNUM* n, BIGNUM* result){

	// k = size of exponent

	BN_CTX *bn_ctx;
	BIGNUM *a;

	
	bn_ctx = BN_CTX_new();
	a = BN_new();
	int k = BN_num_bits(e);
	//printf("k = %d\n",k);
	char *buf = malloc((BN_num_bytes(e)+1)*sizeof(char));
	buf[BN_num_bytes(e)]='\0';
	int len = BN_bn2bin(e,buf);
	//printf("len = %d\n",len);

	int start=0;
	int step_1=0;
	int i,j;	
	for(i=0;i<len;i++){

		for(j=7;j>=0;--j){
		
			if(start==0 && (buf[i]&(1<<j))==0)
				continue;
			start=1;			
	
			// step1
			//putchar( ( buf[i] &(1<<j))? '1':'0');
		
			if(step_1==0){
				
				step_1=1;

				if((buf[i]&(1<<j))){
					// C = M
					BN_copy(result, M);
				}
				else{
					// C = 1
					BN_one(result);
				}
	
				//printf("starting value: ",);

				continue;	
			}


			//step 2a
			//C=C*C
			BN_copy(a,result); //make copy of result ( C )
			BN_sqr(result,a,bn_ctx);
			//C=C mod n
			BN_copy(a,result);
			BN_mod(result,a,n,bn_ctx);	
			//step2b
			if ( (buf[i]&(1<<j))){
				//C=C*M
				BN_copy(a,result);
				BN_mul(result,a,M,bn_ctx);
				//C-C mod n
				BN_copy(a,result);
				BN_mod(result,a,n,bn_ctx);
			}
		}
	}	

		


	BN_CTX_free(bn_ctx);
	return 0;
}
