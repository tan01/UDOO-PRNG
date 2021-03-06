#include "bitgenerator.h"

/*
 * set_bit( buf: buffer, pos: bit position, value: 1 or 0 )
 * sets bit of buf at position pos to value.
 */
void set_bit( char* buf, int pos, const unsigned char *value ){
	char bit_mask = 1 << pos;
	if ( *value == 0 ){
		bit_mask = ~bit_mask;
		*buf &= bit_mask;
	} else {
		*buf |= bit_mask;
	}
}

unsigned char* rsa_char_generator(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	private_key(n);

	int i = 0;
	for( i=0; i < (bits / 8); i++ ){
		//printf("Loop %d\n", i);
		rsa_encrypt(M, n, C);

		// debug
		//char* test = BN_bn2dec(C);
		//printf("%s\n", test);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		// grab least significant bits
		BN_bn2bin(C, binary_C);
		// put 8 bits into result_bits
		result_bits[i] = binary_C[bytes-1];

		//printf("binary_C[bytes-1]: %d\n", binary_C[bytes-1]);

		// freeing memory
		BN_copy(M, C);
		free(binary_C);
		//OPENSSL_free(test);
	}

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}

unsigned char* rsa_bit_generator(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	private_key(n);

	int i = 0;
	for( i=0; i < (bits >> 3); i++ ){
		//printf("Loop %d\n", i);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		int k;
		// little endian
		unsigned char temp_byte = 0;
		for( k=7; k>=0; k-- ){
			rsa_encrypt(M, n, C);

			// debug
			//char* test = BN_bn2dec(C);
			//printf("%s\n", test);
			//OPENSSL_free(test);

			BN_bn2bin(C, binary_C);
			// grab least significant bit
			unsigned char temp_bit = binary_C[bytes-1];
			temp_bit &= 1;
			//printf("temp_bit: %d\n", temp_bit);


			set_bit( &temp_byte, k, &temp_bit );
			//printf("temp_byte[%d]: %d\n", k, temp_byte);

			BN_copy(M, C);
		}

		// put 8 bits into result_bits
		result_bits[i] = temp_byte;

		//printf("result_bits[%d]: %d\n", i, temp_byte);

		// freeing memory
		free(binary_C);
	}

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}

unsigned char* rsa_bit_generator_timed(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	unsigned long long total_time = 0;

	private_key(n);

	
	struct timeval t0, t1;

	int i = 0;
	for( i=0; i < (bits >> 3); i++ ){


		gettimeofday(&t0,0);
	
		/*
		struct timespec tim,tim2;
		tim.tv_sec=0;
		tim.tv_nsec=1000000L;//sleep 
		//nanosleep(&tim,&tim2);	

		*/

		//printf("Loop %d\n", i);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		int k;
		// little endian
		unsigned char temp_byte = 0;
		for( k=7; k>=0; k-- ){
			rsa_encrypt(M, n, C);

			// debug
			char* test = BN_bn2dec(C);
			//printf("%s\n", test);
			OPENSSL_free(test);

			BN_bn2bin(C, binary_C);
			// grab least significant bit
			unsigned char temp_bit = binary_C[bytes-1];
			temp_bit &= 1;
			//printf("temp_bit: %d\n", temp_bit);


			set_bit( &temp_byte, k, &temp_bit );
			//printf("temp_byte[%d]: %d\n", k, temp_byte);

			BN_copy(M, C);
		}
			
		gettimeofday(&t1,0);
		unsigned long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
		//printf("TIME ELAPSED: %d \n",elapsed);
		total_time += elapsed;
		//printf("TOTAL TIME: %ld \n",total_time);
		// put 8 bits into result_bits
		result_bits[i] = temp_byte;

		//printf("result_bits[%d]: %d\n", i, temp_byte);

		// freeing memory
		free(binary_C);
	}

	double average_time = total_time / (double)bits;
	printf("Total time to compute %llu bits: %llu microseconds\n", bits, total_time);
	printf("AVERAGE time to compute 1 bit: %lf\n", average_time);

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}

unsigned char* rabin_char_generator(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	private_key(n);

	int i = 0;
	for( i=0; i < (bits / 8); i++ ){
		//printf("Loop %d\n", i);
		rabin_encrypt(M, n, C);

		// debug
		//char* test = BN_bn2dec(C);
		//printf("%s\n", test);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		// grab least significant bits
		BN_bn2bin(C, binary_C);
		// put 8 bits into result_bits
		result_bits[i] = binary_C[bytes-1];

		//printf("binary_C[bytes-1]: %d\n", binary_C[bytes-1]);

		// freeing memory
		BN_copy(M, C);
		free(binary_C);
		//OPENSSL_free(test);
	}

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}

unsigned char* rabin_bit_generator(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	private_key(n);

	int i = 0;
	for( i=0; i < (bits >> 3); i++ ){
		//printf("Loop %d\n", i);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		int k;
		// little endian
		unsigned char temp_byte = 0;
		for( k=7; k>=0; k-- ){
			rabin_encrypt(M, n, C);

			// debug
			//char* test = BN_bn2dec(C);
			//printf("%s\n", test);
			//OPENSSL_free(test);

			BN_bn2bin(C, binary_C);
			// grab least significant bit
			unsigned char temp_bit = binary_C[bytes-1];
			temp_bit &= 1;
			//printf("temp_bit: %d\n", temp_bit);


			set_bit( &temp_byte, k, &temp_bit );
			//printf("temp_byte[%d]: %d\n", k, temp_byte);

			BN_copy(M, C);
		}

		// put 8 bits into result_bits
		result_bits[i] = temp_byte;

		//printf("result_bits[%d]: %d\n", i, temp_byte);

		// freeing memory
		free(binary_C);
	}

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}

unsigned char* rabin_bit_generator_timed(BIGNUM* seed, unsigned long long bits){
	BIGNUM* n = BN_new();
	BIGNUM* C = BN_new();
	BIGNUM* M = BN_dup(seed);
	unsigned char* binary_C;
	unsigned char* result_bits = malloc(bits / 8 * sizeof(char));

	unsigned long long total_time = 0;

	private_key(n);

	struct timeval t0, t1;

	int i = 0;
	for( i=0; i < (bits >> 3); i++ ){
	
		gettimeofday(&t0, 0);	

		//printf("Loop %d\n", i);

		int bytes = BN_num_bytes(C);
		binary_C = malloc(bytes * sizeof(char));

		//printf("bytes: %d\n", bytes);

		int k;
		// little endian
		unsigned char temp_byte = 0;
		for( k=7; k>=0; k-- ){
			rabin_encrypt(M, n, C);

			// debug
			//char* test = BN_bn2dec(C);
			//printf("%s\n", test);
			//OPENSSL_free(test);

			BN_bn2bin(C, binary_C);
			// grab least significant bit
			unsigned char temp_bit = binary_C[bytes-1];
			temp_bit &= 1;
			//printf("temp_bit: %d\n", temp_bit);


			set_bit( &temp_byte, k, &temp_bit );
			//printf("temp_byte[%d]: %d\n", k, temp_byte);

			BN_copy(M, C);
		}

		gettimeofday(&t1,0);
		unsigned long elapsed = ((t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec) >> 3;
		total_time += elapsed;
		//printf("TIME ELAPSED: %d \n",elapsed);
		
		// put 8 bits into result_bits
		result_bits[i] = temp_byte;

		//printf("result_bits[%d]: %d\n", i, temp_byte);

		// freeing memory
		free(binary_C);
	}

	double average_time = total_time / (double)bits;
	printf("Total time to compute %llu bits: %llu microseconds\n", bits, total_time);
	printf("Average time to compute 1 bit: %lf\n", average_time);

	BN_free(n);
	BN_free(C);
	BN_free(M);

	return result_bits;
}
