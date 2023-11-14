Files Submitted:

List.h - header file for List.c

List.cpp - contains the List ADT

ListTest.cpp - contains tests for the List ADT
Usage: ./ListTest

Shuffle.cpp - contains the main function that uses the List ADT
Usage: ./Shuffle {amount of shuffles}

Makefile - contains the code to compile the above files
Usage:
make                makes Shuffle
make ListTest       makes ListTest
make clean          removes binary files
make check1         runs valgrind on ListTest
make check2         runs valgrind on Shuffle with CLA 35