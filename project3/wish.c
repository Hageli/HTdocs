/*
TEKIJÄ: MIRO HAGELBERG
OPISKELIJANUMERO: 0604373
VIIMEKSI MUOKATTU: 19.1.2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Declaring functions used in this file
int execute(char *path, char **command);
char **parseCommand(char* line);
int commandSize(char **commands);
void exec_cd(char *command, int temp);

// This executes non-built in functions
int execute(char *path, char **command) {
    // Creating the path 
    char *PATH = malloc(256);
    strcpy(PATH, path);
    strcat(PATH, command[0]);
    // Creating the subprocess
    int subp = fork();
    // If fork fails
    if(subp < 0) {
        fprintf(stderr, "Fork failed\n");
    // Trying to execute command if path is accessible
    } else if(subp == 0) {
        if(access(PATH, X_OK) == 0) {
            execv(PATH, command);
        // Returning 0 if unable to
        } else {
            free(PATH);
            return 0;
        }
    } else {
        wait(NULL);
    }
    free(PATH);
    return 1;
}

// This gets us the command tokens
char **parseCommand(char* line) {
    int i = 0;
    char* token = NULL;
    char* delim = " ";
    char** command = malloc(100 *sizeof(char*));
    while ((token = strtok_r(line, delim, &line)) != NULL) {
        command[i] = strdup(token);
        i++;
    }
    command[i + 1] = NULL;
    return command;
}

// This is used to get the amount of command args
int commandSize(char **commands) {
    int command_size = 0;
    while(commands[command_size] != NULL) {
        command_size++;
    }
    return command_size;
}

// This executes built-in cd
void exec_cd(char *command, int temp) {
    if(temp == 2) {
        if(chdir(command) != 0) {
            fprintf(stderr, "Chdir failed\n");
        }
    } else {
        fprintf(stderr, "No destination folder\n");
    }
}


int main(int argc, char** argv) {
    char *line = NULL;
    size_t length = 0;
    char *path[100] = {"/bin/"};
    char **commands;
    int temp = 0;
    int status = 0;
    int path_status = 0;
    // Interactive mode
    if(argc == 1) {
        printf("wish> ");
        while(getline(&line, &length, stdin) != -1) {
            if(strlen(line) > 1) {
                line[strlen(line) - 1] = '\0';
                commands = parseCommand(line);
                temp = commandSize(commands);
                // built-in exit
                if(strcmp(commands[0], "exit") == 0) {
                    if(temp > 1) {
                        fprintf(stderr, "Exit does not accept arguments\n");
                    } else {
                        free(line);
                        free(commands);
                        exit(0);
                    }
                // Built-in cd
                } else if(strcmp(commands[0], "cd") == 0) {
                    exec_cd(commands[1], temp);
                // Built-in path
                } else if(strcmp(commands[0], "path") == 0) {
                    // if path is empty, change status
                    if(temp == 1) {
                        path_status = 1;
                    } else {
                        // Setting new paths
                        for(int i = 0; i < temp - 1; i++) {
                            path[i] = commands[i + 1];
                        }
                        path[temp] = NULL;
                    }
                } else {
                    // if path is empty, do nothing
                    if(path_status == 0) {
                        int counter = 0;
                        while(path[counter] != NULL) {
                            status = execute(path[counter], commands);
                            // break if execute is successful
                            if(status == 1) {
                                break;
                            }
                            counter++;
                        }
                    }
                }
            }
            printf("wish> ");
        }
    // Batch mode
    } else if (argc == 2) {
        for(int j = 1; j < argc; j++) {
            // Exit if file open fails
            FILE *file = fopen(argv[j], "r");
            if(file == NULL) {
                fprintf(stderr, "wish: cannot open file\n");
                exit(1);
            }
            while(getline(&line, &length, file) != -1) {
                if(strlen(line) > 1) {
                line[strlen(line) - 1] = '\0';
                commands = parseCommand(line);
                temp = commandSize(commands);
                // built-in exit
                if(strcmp(commands[0], "exit") == 0) {
                    if(temp > 1) {
                        fprintf(stderr, "Exit does not accept arguments\n");
                    } else {
                        free(line);
                        free(commands);
                        exit(0);
                    }
                // Built-in cd
                } else if(strcmp(commands[0], "cd") == 0) {
                    exec_cd(commands[1], temp);
                // Built-in path
                } else if(strcmp(commands[0], "path") == 0) {
                    // if path is empty, change status
                    if(temp == 1) {
                        path_status = 1;
                    } else {
                        // Setting new paths
                        for(int i = 0; i < temp - 1; i++) {
                            path[i] = commands[i + 1];
                        }
                        path[temp] = NULL;
                    }
                } else {
                    // if path is empty, do nothing
                    if(path_status == 0) {
                        int counter = 0;
                        while(path[counter] != NULL) {
                            status = execute(path[counter], commands);
                            // break if execute is successful
                            if(status == 1) {
                                break;
                            }
                            counter++;
                        }
                    }
                }
            }
            }
            fclose(file);
        }
    // Too many arguments
    } else {
        exit(1);
    }

}