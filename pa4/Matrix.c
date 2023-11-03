#include <stdio.h>
#include <stdlib.h>
#include "List.h" //You might need List ADT implementation

// Define the Entry struct
typedef struct EntryObj {
    int column;
    double value;
} Entry;

// Define the MatrixObj struct
typedef struct MatrixObj {
    int size;     // Size of the square matrix
    int nnz;      // Number of non-zero entries
    List* rows;   // Array of Lists (each list represents a row of the matrix)
} MatrixObj;

// Define the Matrix type as a pointer to MatrixObj
typedef struct MatrixObj* Matrix;

Entry* newEntry(int column, double value) {
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    if (entry == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(1);
    }
    entry->column = column;
    entry->value = value;
    return entry;
}

void freeEntry(Entry* entry)
{
    free(entry);
    entry = NULL;
}

// Create a newMatrix of size n
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;
    M->rows = malloc((n + 1) * sizeof(List));

    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }

    return M;
}

// Free the Matrix and its associated memory
void freeMatrix(Matrix* pM) {
    if(pM && *pM)
    {
        for(int i = 1; i <= (*pM)->size; i++)
        {
            moveFront((*pM)->rows[i]);
            while(index((*pM)->rows[i]) >= 0)
            {
                Entry* E = (Entry*)get((*pM)->rows[i]);
                freeEntry(E);
                moveNext((*pM)->rows[i]);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}

// Access functions
int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    return M->nnz;
}

int equals(Matrix A, Matrix B) {
    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;
    }

    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        moveFront(rowA);
        moveFront(rowB);
        if(length(rowA) != length(rowB))
        {
            return 0;
        }

        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* entryB = (Entry*)get(rowB);

            if (entryA->column != entryB->column || entryA->value != entryB->value) {
                return 0;
            }

            moveNext(rowA);
            moveNext(rowB);
        }

    }

    return 1;
}

void makeZero(Matrix M) {
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->rows[i]);
        while(index((M)->rows[i]) >= 0)
            {
                Entry* E = (Entry*)get((M)->rows[i]);
                freeEntry(E);
                moveNext((M)->rows[i]);
            }
        clear(M->rows[i]);

    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        fprintf(stderr, "Error: Invalid matrix indices.\n");
        exit(1);
    }

    List row = M->rows[i];

    if (x == 0.0) {
        // If x is 0, remove the entry at column j if it exists
        moveFront(row);
        while (index(row) >= 0) {
            Entry* entry = (Entry*)get(row);
            if (entry->column == j) {
                delete (row);
                M->nnz--;
                return;
            } else if (entry->column < j) {
                moveNext(row);
            } else {
                return; // No need to insert if x is 0
            }
        }
    } else {
        // If x is not 0, update or insert the entry at column j
        moveFront(row);
        while (index(row) >= 0) {
            Entry* entry = (Entry*)get(row);
            if (entry->column == j) {
                entry->value = x;
                return;
            } else if (entry->column < j) {
                moveNext(row);
            } else {
                break;
            }
        }

        // Insert the new entry at the correct position
        Entry* newEntry = malloc(sizeof(Entry));
        newEntry->column = j;
        newEntry->value = x;
        if (index(row) == -1) {
            append(row, newEntry);
        } else {
            insertBefore(row, newEntry);
        }
        M->nnz++;
    }
}

Matrix copy(Matrix A) {
    Matrix B = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);

        while (index(rowA) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* e = newEntry(entryA->column, entryA->value);
            append(rowB, e);
            moveNext(rowA);
        }
    }

    B->nnz = A->nnz;

    return B;
}

Matrix transpose(Matrix A) {
    Matrix T = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);

        while (index(row) >= 0) {
            Entry* entry = (Entry*)get(row);
            int j = entry->column;
            double x = entry->value;

            changeEntry(T, j, i, x);
            moveNext(row);
        }
    }

    return T;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix B = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        moveFront(rowA);

        while (index(rowA) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            int j = entryA->column;
            double valA = entryA->value;
            changeEntry(B, i, j, x * valA);
            moveNext(rowA);
        }
    }

    return B;
}

Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices have different sizes.\n");
        exit(1);
    }

    // Check if A and B are equal
    if (equals(A, B)) {
        // Create and return a zero matrix of the same size as A
        
        return scalarMult(2, A);
    }

    Matrix D = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        List rowD = D->rows[i]; // Create a new list for rowD
        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* entryB = (Entry*)get(rowB);

            if (entryA->column == entryB->column) {
                double diffValue = entryA->value + entryB->value;
                if (diffValue != 0.0) {
                    Entry* e = newEntry(entryA->column, diffValue);
                    append(rowD, e);
                }
                moveNext(rowA);
                moveNext(rowB);
            } else if (entryA->column < entryB->column) {
                Entry* e = newEntry(entryA->column, entryA->value);
                append(rowD, e);
                moveNext(rowA);
            } else {
                Entry* e = newEntry(entryB->column, -entryB->value);
                append(rowD, e);
                moveNext(rowB);
            }
        }

        while (index(rowA) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* e = newEntry(entryA->column, entryA->value);
            append(rowD, e);
            moveNext(rowA);
        }

        while (index(rowB) >= 0) {
            Entry* entryB = (Entry*)get(rowB);
            Entry* e = newEntry(entryB->column, -entryB->value);
            append(rowD, e);
            moveNext(rowB);
        }

        //D->rows[i] = rowD;
        D->nnz += length(rowD);
    }

    return D;
}

Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices have different sizes.\n");
        exit(1);
    }

    // Check if A and B are equal
    if (equals(A, B)) {
        // Create and return a zero matrix of the same size as A
        Matrix D = newMatrix(size(A));
        return D;
    }

    Matrix D = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        List rowD = D->rows[i]; // Create a new list for rowD
        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* entryB = (Entry*)get(rowB);

            if (entryA->column == entryB->column) {
                double diffValue = entryA->value - entryB->value;
                if (diffValue != 0.0) {
                    Entry* e = newEntry(entryA->column, diffValue);
                    append(rowD, e);
                }
                moveNext(rowA);
                moveNext(rowB);
            } else if (entryA->column < entryB->column) {
                Entry* e = newEntry(entryA->column, entryA->value);
                append(rowD, e);
                moveNext(rowA);
            } else {
                Entry* e = newEntry(entryB->column, -entryB->value);
                append(rowD, e);
                moveNext(rowB);
            }
        }

        while (index(rowA) >= 0) {
            Entry* entryA = (Entry*)get(rowA);
            Entry* e = newEntry(entryA->column, entryA->value);
            append(rowD, e);
            moveNext(rowA);
        }

        while (index(rowB) >= 0) {
            Entry* entryB = (Entry*)get(rowB);
            Entry* e = newEntry(entryB->column, -entryB->value);
            append(rowD, e);
            moveNext(rowB);
        }

        //D->rows[i] = rowD;
        D->nnz += length(rowD);
    }

    return D;
}

double vectorDot(List P, List Q) {
    double dotProduct = 0.0;
    
    moveFront(P);
    moveFront(Q);

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry* entryP = (Entry*)get(P);
        Entry* entryQ = (Entry*)get(Q);

        if (entryP->column == entryQ->column) {
            dotProduct += entryP->value * entryQ->value;
            moveNext(P);
            moveNext(Q);
        } else if (entryP->column < entryQ->column) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }

    return dotProduct;
}

int nonZeroExists(List row) {
    // Iterate through the list and check if any non-zero entry exists
    for (moveFront(row); index(row) >= 0; moveNext(row)) {
        Entry *entry = (Entry *)get(row);
        if (entry->value != 0.0) {
            return 1; // Non-zero entry found
        }
    }
    return 0; // No non-zero entry found
}

Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices have different sizes.\n");
        exit(1);
    }

    Matrix C = newMatrix(size(A));
    Matrix B_transpose = transpose(B);

    for (int i = 1; i <= size(A); i++) {
        // Check if the current row in A has non-zero entries
        int hasNonZero = nonZeroExists(A->rows[i]);
        if (hasNonZero) {
            for (int j = 1; j <= size(B_transpose); j++) {
                double dotProduct = vectorDot(A->rows[i], B_transpose->rows[j]);
                if (dotProduct != 0.0) {
                    changeEntry(C, i, j, dotProduct);
                }
            }
        }
    }

    freeMatrix(&B_transpose);

    return C;
}


void printMatrix(FILE* out, Matrix M) {
    if (M == NULL || out == NULL) {
        fprintf(stderr, "Error: NULL Matrix or output file.\n");
        return;
    }

    for (int i = 1; i <= size(M); i++) {
        List row = M->rows[i];
        if (length(row) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(row);

            while (index(row) >= 0) {
                Entry* entry = (Entry*)get(row);
                fprintf(out, "(%d, %0.1f)", entry->column, entry->value);

                if (index(row) < length(row) - 1) {
                    fprintf(out, " ");
                }

                moveNext(row);
            }

            fprintf(out, "\n");
        }
    }
}

