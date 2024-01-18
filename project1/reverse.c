/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 18.1.2024
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct for creating individual nodes
typedef struct node {
    char* data;
    struct node* next;
}Node;

Node* insertNode(Node* head, char* line);

Node *readUserInput(Node *head) {
    char *input = NULL;
    size_t length = 0;

    fprintf(stdout, "Add words, leave empty to stop:\n");
    while(getline(&input, &length, stdin) != -1) {
        if(strlen(input) == 1) {
            break;
        }
        head = insertNode(head, input);
    }
    free(input);
    return head;
}

Node *readData(Node *head, char *input_file) {
    char *line = NULL;
    size_t length = 0;
    FILE *file = fopen(input_file, "r");
    if(file == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", input_file);
        exit(1);
    }
    while(getline(&line, &length, file) != -1) {
        head = insertNode(head, line);
    }
    free(line);
    fclose(file);
    return head;
}

Node *insertNode(Node *head, char *line) {
    Node *new_node = malloc(sizeof(Node));

    if( new_node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    new_node->data = strdup(line);
    new_node->next = head;
    return new_node;
}

void reversePrint(Node *head) {
    while(head != NULL) {
        fprintf(stdout, "%s", head->data);
        head = head->next;
    }
}

void reverseWrite(Node *head, char *output_file) {
    FILE *file = fopen(output_file, "w");
    if(file == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", output_file);
        exit(1);
    }
    while(head != NULL) {
        fprintf(file, "%s", head->data);
        head = head->next;
    }
    fclose(file);
}

Node *freeNodes(Node *head) {
    Node *temp_node = head;
    while(temp_node != NULL) {
        head = temp_node->next;
        free(temp_node->data);
        free(temp_node);
        temp_node = head;
    }
    return head;
}

int main(int argc, char **argv) {
    Node *head = NULL;

    switch(argc) {
        case 1:
            head = readUserInput(head);
            reversePrint(head);
            break;
        case 2:
            head = readData(head, argv[1]);
            reversePrint(head);
            break;
        case 3:
            if(strcmp(argv[1], argv[2]) == 0) {
                fprintf(stderr, "Input and output file must differ\n");
                exit(1);
            }
            head = readData(head, argv[1]);
            reverseWrite(head, argv[2]);
            break;
        default:
            fprintf(stderr, "Usage: reverse <input> <utput>\n");
            exit(1);
    }
    head = freeNodes(head);
    return 0;
}