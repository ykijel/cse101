#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h" // Include your Matrix ADT header

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    // Open the input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Cannot open input file %s\n", inputFileName);
        exit(1);
    }

    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fprintf(stderr, "Error: Cannot open output file %s\n", outputFileName);
        fclose(inputFile);
        exit(1);
    }

    int n, a, b;

    // Read the input file
    if (fscanf(inputFile, "%d %d %d", &n, &a, &b) != 3) {
        fprintf(stderr, "Error: Invalid input format.\n");
        fclose(inputFile);
        fclose(outputFile);
        exit(1);
    }

    // Create and initialize matrices A and B
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    
    for (int i = 0; i < a; i++) {
    int row, col;
    double val;
    if (fscanf(inputFile, "%d %d %lf", &row, &col, &val) != 3) {
        fprintf(stderr, "Error: Invalid input format for matrix A.\n");
        fclose(inputFile);
        fclose(outputFile);
        exit(1);
    }
    changeEntry(A, row, col, val);
}

// Skip the blank line
fgetc(inputFile); // Reads and discards the newline character

// Read and populate matrix B
for (int i = 0; i < b; i++) {
    int row, col;
    double val;
    if (fscanf(inputFile, "%d %d %lf", &row, &col, &val) != 3) {
        fprintf(stderr, "Error: Invalid input format for matrix B.\n");
        fclose(inputFile);
        fclose(outputFile);
        exit(1);
    }
    changeEntry(B, row, col, val);
}

    // Calculate and print the specified matrices
    fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outputFile, A);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outputFile, B);
    fprintf(outputFile, "\n");
    
    Matrix scaledA = scalarMult(1.5, A);
    fprintf(outputFile, "(1.5)*A =\n");
    printMatrix(outputFile, scaledA);
    fprintf(outputFile, "\n");

    Matrix sumAB = sum(A, B);
    fprintf(outputFile, "A+B =\n");
    printMatrix(outputFile, sumAB);
    fprintf(outputFile, "\n");

    Matrix sumAA = sum(A, A);
    fprintf(outputFile, "A+A =\n");
    printMatrix(outputFile, sumAA);
    fprintf(outputFile, "\n");

    Matrix diffBA = diff(B, A);
    fprintf(outputFile, "B-A =\n");
    printMatrix(outputFile, diffBA);
    fprintf(outputFile, "\n");

    Matrix diffAA = diff(A, A);
    fprintf(outputFile, "A-A =\n");
    printMatrix(outputFile, diffAA);
    fprintf(outputFile, "\n");

    Matrix transposeA = transpose(A);
    fprintf(outputFile, "Transpose(A) =\n");
    printMatrix(outputFile, transposeA);
    fprintf(outputFile, "\n");

    Matrix productAB = product(A, B);
    fprintf(outputFile, "A*B =\n");
    printMatrix(outputFile, productAB);
    fprintf(outputFile, "\n");

    Matrix productBB = product(B, B);
    fprintf(outputFile, "B*B =\n");
    printMatrix(outputFile, productBB);

    // Clean up and close files
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scaledA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transposeA);
    freeMatrix(&productAB);
    freeMatrix(&productBB);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
