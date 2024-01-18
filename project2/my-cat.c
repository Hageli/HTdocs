/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 18.1.2024
*/

#include <stdio.h>
#include <stdlib.h>

// Declaring the functions in this file
void readContent(char *input_file);

void readContent(char *input_file) {
    FILE *file = fopen(input_file, "r");
    char buffer[255];
    int length = 255;
    // Exit if file open fails
    if(file == NULL) {
        fprintf(stderr, "my-cat: cannot open file\n");
        exit(1);
    }
    // Reading the lines in file
    while(fgets(buffer, length, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

int main(int argc, char **argv) {
    // case where no input file is given
    if(argc == 1) {
        exit(0);
    } else {
        // Read through the given files one at a time
        for(int i = 1; i < argc; i++) {
            readContent(argv[i]);
        }
    }
    return 0;
}
