#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define ERROR "An error has occurred\n"
#define INTERACTIVE_MODE 1
#define BATCH_MODE 2
#define BUFF_SIZE 256

FILE *fp = NULL;
char *line = NULL;


void clear() {
    free(line);
    fclose(fp);
}

void print_error() {
    write(STDERR_FILENO, ERROR, strlen(ERROR));
}

int searchPath(char path[], char *arg, char *paths[]) {
    int i = 0;
    while (paths[i] != NULL) {
        snprintf(path, BUFF_SIZE, "%s/%s", paths[i], arg);
        if (access(path, X_OK) == 0)
            return 0;
        i++;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    char *paths[BUFF_SIZE] = {"/bin", NULL};
    int mode = 0;
    fp = stdin;
    if (argc == 1) {
        mode = INTERACTIVE_MODE;
    } else {
        mode = BATCH_MODE;
        fp = fopen(argv[1], "r");
    }
    char *args[64];
    char *tmp;
    char *token;
    size_t len = 0;

    while (1) {
        if (mode == INTERACTIVE_MODE) {
            printf("wish> ");
        }

        ssize_t read = getline(&line, &len, fp);
        if (read == -1) {
            if (mode == BATCH_MODE) {
                clear();
                exit(EXIT_SUCCESS);
            }
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        tmp = line;
        int arg_count = 0;
        while ((token = strsep(&tmp, " \t")) != NULL) {
            if (*token != '\0') {
                args[arg_count] = strdup(token);
                arg_count++;
            }
        }

        args[arg_count] = NULL;
        if (arg_count == 0)
            continue;
        if (strcmp(args[0], "exit") == 0) {
            if (arg_count > 1) {
                print_error();
            } else {
                clear();
                exit(EXIT_SUCCESS);
            }
        } else if (strcmp(args[0], "cd") == 0) {
            if (arg_count != 2) {
                print_error();
            } else if (chdir(args[1]) != 0) {
                print_error();
            }
        } else {
            char path[BUFF_SIZE];
            if (searchPath(path, args[0], paths) == 0) {
                pid_t pid = fork();
                if (pid == -1) {
                    print_error();
                } else if (pid == 0) {
                    if (execv(path, args) == -1) {
                        print_error();
                        exit(EXIT_FAILURE);
                    }
                } else if (pid > 0) {
                    int status;
                    waitpid(pid, &status, 0);
                }
            } else {
                print_error();

            }
        }
        for (int i = 0; i < arg_count; i++) {
            free(args[i]);
        }
    }

}

//
// Created by hiidy on 12/13/24.
//
