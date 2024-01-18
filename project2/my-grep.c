/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 18.1.2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring the functions in this file
void readInput(char *needle);
void readFile(char *needle, FILE *file);

// Reads the user input if no input file is given
void readInput(char *needle) {
    size_t length = 0;
    char *line = NULL;
    // Reading one line at a time, using strstr to check if string exists in line
    while(getline(&line, &length, stdin) != -1) {
        // Break if line is left empty
        if(strlen(line) == 1) {
            break;
        // Print if line contains the string
        } else if(strstr(line, needle) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
}

// Reads file content and finds matching lines
void readFile(char *needle, FILE *file) {
    size_t length = 0;
    char *line = NULL;
    // Reading one line at a time, using strstr to check if string exists in line
    while(getline(&line, &length, file) != -1) {
        // Print if line contains the string
        if(strstr(line, needle) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
} 

int main(int argc, char **argv) {
    // No search string or file
    if(argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file...]\n");
        exit(1);
    // Only search string given but no input file
    } else if (argc == 2) {
        readInput(argv[1]);
    } else {
        // Search string and input file given
        for(int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if(file == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            }
            readFile(argv[1], file);
            fclose(file);
        }
    }
    return 0;
}