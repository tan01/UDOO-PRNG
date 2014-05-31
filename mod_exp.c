#include <openssl/bio.h>
#include <stdio.h>

#include "mod_exp.h"

void print_result(BIGNUM* result){
	BN_print_fp(stdout, result);
}
