#include <iostream>
#include <fstream>
#include "BigInteger.h"  // Include your BigInteger implementation file

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    // Open input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file\n";
        return 1;
    }

    // Open output file
    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        inputFile.close();
        return 1;
    }

    // Read and parse line 1 of the input file as BigInteger A
    std::string line1A;
    std::getline(inputFile, line1A);
    BigInteger A(line1A);

    // Skip line 2
    std::string line2;
    std::getline(inputFile, line2);

    // Read and parse line 3 of the input file as BigInteger B
    std::string line3B;
    std::getline(inputFile, line3B);
    BigInteger B(line3B);

    // Perform arithmetic operations
    BigInteger sum = A + B;
    BigInteger diff = A - B;
    BigInteger zero = A - A;
    BigInteger expr1 = 3 * A - 2 * B;
    BigInteger prod = A * B;
    BigInteger squareA = A * A;
    BigInteger squareB = B * B;
    BigInteger expr2 = 9 * A * A * A * A + 16 * B * B * B * B * B;

    // Write results to the output file
    outputFile << A << '\n'
    	       << '\n'
               << B << '\n'
               << '\n'
               << sum << '\n'
               << '\n'
               << diff << '\n'
               << '\n'
               << zero << '\n'
               << '\n'
               << expr1 << '\n'
               << '\n'
               << prod << '\n'
               << '\n'
               << squareA << '\n'
               << '\n'
               << squareB << '\n'
               << '\n'
               << expr2 << '\n';

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
