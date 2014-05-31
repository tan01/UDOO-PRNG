#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/bn.h>

int main()
{


	BIGNUM *a;
	a = BN_new();

	BN_set_word(a,278);
	char *buf = malloc((BN_num_bytes(a)+1)*sizeof(char)); 
	buf[BN_num_bytes(a)]='\0';
	int len = BN_bn2bin(a,buf);

	printf("output is : %s\n",buf);
	int start=0;

	int i,j;
	for(j=0;j<len;j++){

		
		for(i=7;i>=0;--i){
			if(start==0 && (buf[j]&(1<<i))==0)
				continue;
			start=1;
			putchar( (buf[j] &(1<<i))? '1':'0');
		}

	}
	
	printf("number of bits is: %d",BN_num_bits(a));

}
