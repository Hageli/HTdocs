/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 12.1.2024
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct for creating individual nodes
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node *readData(char *input_file, Node *head) {
    
}

Node *insertNode(Node *head, char *line) {

}

void reversePrint(Node *head) {

}

void reverseWrite(Node *head, char *output_file) {

}

int main(int argc) {
    Node *head = NULL;

    switch(argc) {
        case 1:

        case 2:

        case 3:

        default:
            fprintf(stderr, "Usage: reverse <input> <utput>\n");
            exit(1);
    }
}