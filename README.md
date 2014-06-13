UDOO-PRNG
=========

A couple of PRNG implementations to be tested on UDOO mini PC boards.

RUNNING SAMPLE PROGRAM
=====================
Compile with GNU Make utility.
Run random_number_test:
	USAGE:
	random_number_test <noargs>:
		defaults to seeding the RNG with 2 and producing a 262144 bit pseudo-random number.
	random_number_test <number of bits> <seed value>:
		seeds the RNGs with the seed value and produces the requested number of psuedo-random bits.

Random number test will run both PRNG bit generators and return the total running time and the time per bit.

Sample outputs are included, run on an UDOO board.
