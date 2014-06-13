/*
 *	random_number_test.c
 *	Generates a pseudo-random number off a hardcoded seed
 *	and prints out performance metrics for
 *	rabin and rsa bit generators.
 *
 *	A decimal representation of the pseudo-random number
 *	is printed to stdout.
 *
 *	USAGE:
 *	random_number_test <noargs>:
 *		defaults to seeding the RNG with 2 and producing a 262144 bit pseudo-random number.
 *	random_number_test <number of bits> <seed value>:
 *		seeds the RNGs with the seed value and produces the requested number of psuedo-random bits.
 */

#include "rsa.h"
#include "rabin.h"
#include "bitgenerator.h"
#include <stdio.h>

int main(int argc, char** argv){

	// default values if bits and seed value are not supplied
	unsigned long bit_length = 262144;
	unsigned seed = 2;

	if( argc > 1 ){
		bit_length = strtol(argv[1], NULL, 10);
	}
	if ( argc > 2 ){
		seed = strtol(argv[2], NULL, 10);
	}

	BIGNUM* M = BN_new();
	BN_set_word(M, seed);

	// Rabin bit generator
	printf("*** Rabin Bit Generator ***\nSeed: %u\nBits: %lu\n", seed, bit_length);
	unsigned char* result = rabin_bit_generator_timed(M, bit_length);

	BIGNUM* bignumrep = BN_new();

	BN_bin2bn(result, (bit_length + 7) / 8, bignumrep);

	char* decimal_res = BN_bn2dec(bignumrep);
	printf("random number: %s\n", decimal_res);
	printf("number of bytes: %d\n", BN_num_bytes(bignumrep));

	OPENSSL_free(decimal_res);
	OPENSSL_free(result);
	
	// RSA bit generator
	printf("*** RSA Bit Generator ***\nSeed: %u\nBits: %lu\n", seed, bit_length);
	unsigned char* rsa_result = rsa_bit_generator_timed(M, bit_length);
	BN_bin2bn(result, (bit_length + 7) / 8, bignumrep);
	decimal_res = BN_bn2dec(bignumrep);

	printf("random number: %s\n", decimal_res);
	printf("number of bytes: %d\n", BN_num_bytes(bignumrep));

	OPENSSL_free(decimal_res);
	OPENSSL_free(rsa_result);

	BN_free(bignumrep);
	BN_free(M);

	return 0;
}
