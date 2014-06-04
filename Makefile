CC=gcc
CFLAGS=-Wall

LIBS=-lssl -lcrypto

SOURCE=key_gen.c
OBJ=key_gen.o mod_exp.o rsa.o bitgenerator.o

all:
	make key_gen
	make mod_exp
	make rsa
	make bit
	$(CC) $(OBJ) primetest.c -o primetest $(LIBS) $(CFLAGS)

key_gen:
	$(CC) -c key_gen.c

mod_exp:
	$(CC) -c mod_exp.c

rsa:
	$(CC) -c rsa.c

rabin:
	$(CC) -c rabin.c

bit:
	$(CC) -c bitgenerator.c

clean:
	rm primetest
	rm *.o
