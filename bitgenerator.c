#include "bitgenerator.h"

// right now, I'm going to make some simplifying assumptions:
// bits is divisible by 8, or preferably a power of 2
unsigned char* rsa_bit_generator(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	private_key(n);

	int i = 0;
	for( i=0; i < (bits / 8); i++ ){
		printf("Loop %d\n", i);
		encrypt(M, n, C);

		// debug
		char* test = BN_bn2dec(C);
		printf("%s\n", test);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		printf("bytes: %d\n", bytes);

		// grab least significant bits
		BN_bn2bin(C, binary_C);
		// put 8 bits into result_bits
		result_bits[i] = binary_C[bytes-1];

		printf("binary_C[bytes-1]: %d\n", binary_C[bytes-1]);

		// freeing memory
		BN_copy(M, C);
		free(binary_C);
		OPENSSL_free(test);
	}

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}
