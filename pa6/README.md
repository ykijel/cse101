Files Submitted:
List.h - header file for List.c
List.cpp - contains the List ADT
ListTest.cpp - contains tests for the List ADT
Usage: ./ListTest
BigInteger.h - header file for BigInteger.c
BigInteger.cpp - contains the BigInteger ADT
BigIntegerTest.cpp - contains tests for the BigInteger ADT
Usage: ./BigIntegerTest
Arithmetic.cpp - contains the main function that uses the List ADT
Usage: ./Arithmetic {input.txt} {output.txt}
Makefile - contains the code to compile the above files
Usage:
make                     makes Arithmetic
make BigIntegerTest      makes BigIntegerTest
make ListTest            makes ListTest
make clean               removes all binaries
make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
make BigIntegerCheck     runs BigIntegerTest in valgrind
make ListCheck           runs ListTest in valgrind
