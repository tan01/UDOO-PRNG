CC=gcc
CFLAGS=-Wall

LIBS=-lssl -lcrypto

SOURCE=key_gen.c
OBJ=key_gen.o mod_exp.o

all:
	$(CC) $(OBJ) primetest.c -o primetest $(LIBS) $(CFLAGS)

key_gen:
	$(CC) -c key_gen.c

mod_exp:
	$(CC) -c mod_exp.c
