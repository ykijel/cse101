#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {

    int token_count, line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char **test;
    char tokenBuffer[MAX_LEN];
    char *token;
    int newlines = 0;
    List myList = newList();

    // check command line for the correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Determine the number of lines in the file first
    line_count = 0;
    while (fgets(line, MAX_LEN, in) != NULL) {
        line_count++;
    }

    // Allocate memory for the array of strings
    test = (char **)malloc(line_count * sizeof(char *));
    if (test == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Close and reopen the input file to reset the file pointer
    fclose(in);
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    // Read each line of input file, then count and print tokens
    line_count = 0;
    while (fgets(line, MAX_LEN, in) != NULL) {
        // Allocate memory for the current line in the test array
        test[line_count] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        if (test[line_count] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        if(strlen(line) != 1)
        {
        	strcpy(test[line_count], line);
        }
        else
        {
        	newlines++;
        }
        

        // get tokens in this line
        token_count = 0;
        tokenBuffer[0] = '\0';

        // get first token
        token = strtok(line, " \n");

        while (token != NULL) { // we have a token
            // update token buffer
            strcat(tokenBuffer, "   ");
            strcat(tokenBuffer, token);
            strcat(tokenBuffer, "\n");
            token_count++;

            // get next token
            token = strtok(NULL, " \n");
        }
        // print tokens in this line

        // Add all strings to the char array
        if (length(myList) == 0) {
            prepend(myList, line_count);
        } else {
            moveFront(myList);
            int inserted = 0;

            while (index(myList) >= 0) {
            	
                if (strcmp(line, test[get(myList)]) < 0) {
                    insertBefore(myList, line_count);
                    inserted = 1;
                    break;
                }
                moveNext(myList);
            }

            // If the line was not inserted, insert it at the end
            if (!inserted) {
                append(myList, line_count);
            }
        }

        // Increment line_count
        line_count++;
    }
    moveFront(myList);
    for(int i = 0; i < length(myList); i++)
    {
    	fprintf(out, "%s", test[get(myList)]);
    	moveNext(myList);	

    }
    if(newlines > 0)
    {
    	for(int i = 0; i < newlines; i++)
    	{
    		fprintf(out, "\n");
    	}
    }

    // Free the dynamically allocated memory for test
    for (int i = 0; i < line_count; i++) {
        free(test[i]);
    }
    free(test);
    freeList(&myList);

    // close files
    fclose(in);
    fclose(out);

    return (0);
}