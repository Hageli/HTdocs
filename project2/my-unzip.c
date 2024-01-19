/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 19.1.2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring the functions in this file
void decompress(char *file_name);

// This reads binary form integers and chars from file and decompresses them
void decompress(char *file_name) {
    int number;
    char letter;
    FILE *file = fopen(file_name, "r");
    // Exit if file open fails
    if(file == NULL) {
        fprintf(stderr, "my-unzip: cannot open file\n");
        exit(1);
    }
    // Loop thourgh the file
    while(!feof(file)) {
        // Reading next integer
        int temp = fread(&number, 4, 1, file);
        if(temp == 0) {
            break;
        }
        // Reading next char
        temp = fread(&letter, 1, 1, file);
        if(temp == 0) {
            break;
        }
        // Print in decompressed form
        for(int i = 0; i < number; i++) {
            printf("%c", letter);
        }
    }
    fclose(file);
}

int main(int argc, char **argv) {
    // If no input file is given
    if(argc == 1) {
        fprintf(stderr, "my-unzip: file1 [file2...]\n");
        exit(1);
    } else {
        for(int i = 1; i < argc; i++) {
            decompress(argv[i]);
        }
    }
    return 0;
}