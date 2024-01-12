/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 12.1.2024
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structs for creating individual nodes and the linked list
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    int size;
    Node* head;
} LinkedList;

// This prints LinkedList in reverse to console
void printNodes(Node* head) {

    // Return here if the LinkedList is empty
    if(head == NULL) {
        return;
    }
    Node *current = head;
    while(current != NULL) {
        fprintf(stdout, "%s", current->data);
        current = current->next;
    }
}

// This writes LinkedList to output file
void writeNodes(Node *head, char *outputFile) {
    FILE *writefile = fopen(outputFile, "w");
    if(writefile == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", outputFile);
        exit(1);
    }

    // Return here if the LinkedList is empty
    if(head == NULL) {
        fclose(writefile);
        return;
    }
    Node *current = head;
    while(current != NULL) {
        fprintf(writefile, "%s", current->data);
        current = current->next;
    }
    fclose(writefile);
}

// Used to create an empty LinkedList
LinkedList* createLinkedList() {
    LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));

    // Exit in case malloc fails
    if(newLinkedList == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    return newLinkedList;
}

// This adds a node to LinkedList  
void addNode(LinkedList* linked_list, char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    // Exit in case malloc fails
    if(newNode == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = linked_list->head;
    linked_list->head = newNode;
    linked_list->size++;
}


// this frees the memory allocated to our LinkedList nodes
void freeLinkedList(LinkedList* linked_list) {
    
    // List is empty, nothing to free
    if(linked_list->size == 0) {
        return;
    }
    Node* current = linked_list->head;
    while(current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(linked_list);
}


int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t length = 0;
    size_t content;
    LinkedList* nodeList = createLinkedList();

    // Case where too many args are used
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);

    // Case where stdin is read instead of file
    } else if (argc == 1) {
        fprintf(stdout, "Add words, leave empty to stop:\n");
        while((content = getline(&line, &length, stdin)) != -1) {
            if(strlen(line) == 1) {
                break;
            }
            addNode(nodeList, line);
        }
        printNodes(nodeList->head);
        exit(0);

    // Case where we only have an input file
    } else if (argc == 2) {

        FILE *readfile = fopen(argv[1], "r");
        if(readfile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        while((content = getline(&line, &length, readfile)) != -1) {
            addNode(nodeList, line);
        }
        printNodes(nodeList->head);

        freeLinkedList(nodeList);
        fclose(readfile);
        exit(0);

    // Case where input and output files are the same
    } else if(strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr,"input and output file must differ\n");
        exit(1); 
    
    // Case where we have both input and output files that are different
    } else {
        FILE *readfile = fopen(argv[1], "r");
        if(readfile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        while((content = getline(&line, &length, readfile)) != -1) {
            addNode(nodeList, line);
        }
        writeNodes(nodeList->head, argv[2]);
        freeLinkedList(nodeList);
        fclose(readfile);
        exit(0);
    }
}