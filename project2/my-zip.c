/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 11.1.2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring the functions in this file
void compress(char *line);


void compress(char *file_name) {
    char line[4096];

    FILE *file = fopen(file_name, "r");
    if(file == NULL) {
        fprintf(stderr, "my-zip: cannot open file\n");
        exit(1);
    }
    while(fgets(line, 4096, file) != NULL) {
        int length = strlen(line);
        
        for(int i = 0; i < length; i++) {
            int counter = 1;
            while(line[i] == line[i + 1]) {
                counter++;
                i++;
            }
            fwrite(&counter, sizeof(int), 1, stdout);
            fwrite(&line[i], sizeof(char), 1, stdout);
        }

    }
    fclose(file);
}


int main(int argc, char **argv) {
    if(argc == 1) {
        fprintf(stderr, "my-zip: file1 [file2...]\n");
        exit(1);
    } else {
        for(int i = 1; i < argc; i++) {
            compress(argv[i]);
        }
    }

    return 0;
}