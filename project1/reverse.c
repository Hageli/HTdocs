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

// Declaring the functions in this file
Node *readUserInput(Node *head);
Node *readData(Node *head, char *input_file);
Node *insertNode(Node* head, char* line);
void reversePrint(Node *head);
void reverseWrite(Node *head, char *output_file);
Node *freeNodes(Node *head);

// This reads user input if no args are given
Node *readUserInput(Node *head) {
    char *input = NULL;
    size_t length = 0;

    // Asking the user for input and reading the input here
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

// This reads content from file and calls insertNode() to add nodes to the linked list
Node *readData(Node *head, char *input_file) {
    char *line = NULL;
    size_t length = 0;
    FILE *file = fopen(input_file, "r");

    // Exit if file open fails
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

// This creates a new node and adds it to linked list
Node *insertNode(Node *head, char *line) {
    Node *new_node = malloc(sizeof(Node));

    // Exit if malloc fails
    if( new_node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Inserting values to the new node
    new_node->data = strdup(line);
    new_node->next = head;
    return new_node;
}

// This prints out linked list in reverse
void reversePrint(Node *head) {
    while(head != NULL) {
        fprintf(stdout, "%s", head->data);
        head = head->next;
    }
}

// This writes linked list content to file in reverse order
void reverseWrite(Node *head, char *output_file) {
    FILE *file = fopen(output_file, "w");

    // Exit if file open fails
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

// This frees the memory allocated to the nodes
Node *freeNodes(Node *head) {
    Node *temp_node = head;

    // Freeing the nodes one at a time
    while(temp_node != NULL) {
        head = temp_node->next;
        free(temp_node);
        temp_node = head;
    }
    return head;
}

int main(int argc, char **argv) {
    Node *head = NULL;

    switch(argc) {
        // Case where no input or output files are given
        case 1:
            head = readUserInput(head);
            reversePrint(head);
            break;
        // Case where only the input file is given
        case 2:
            head = readData(head, argv[1]);
            reversePrint(head);
            break;
        // Case where both required files are given
        case 3:
            // Exit if input and output files are the same
            if(strcmp(argv[1], argv[2]) == 0) {
                fprintf(stderr, "Input and output file must differ\n");
                exit(1);
            }
            head = readData(head, argv[1]);
            reverseWrite(head, argv[2]);
            break;
        // Default case, user has given too many args
        default:
            fprintf(stderr, "Usage: reverse <input> <utput>\n");
            exit(1);
    }
    head = freeNodes(head);
    return 0;
}