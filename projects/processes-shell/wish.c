#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#define ERROR "An error has occurred\n"
#define INTERACTIVE_MODE 1
#define BATCH_MODE 2
#define BUFF_SIZE 256
#define MAX_ARGS 64
#define MAX_PATHS 256

FILE *fp = NULL;
char *line = NULL;

typedef struct {
    char **args;
    int arg_count;
    char *output_file;
} Command;

typedef struct {
    char **paths;
    int path_count;
} PathList;

int execute_command(Command *cmd, PathList *pl);
int handle_builtin_command(Command *cmd, PathList *pl);
int execute_external_command(Command *cmd, PathList *pl);
void free_command(Command *cmd);
PathList *create_paths();

void clear() {
    free(line);
    fclose(fp);
}

void print_error() {
    write(STDERR_FILENO, ERROR, strlen(ERROR));
}

int search_path(char *result, Command *command, PathList *pl) {
    for (int i = 0; i < pl->path_count; i++) {
        if (!pl->paths[i])
            continue;

        snprintf(result, BUFF_SIZE, "%s/%s", pl->paths[i], command->args[0]);

        if (access(result, X_OK) == 0) {
            return 0;
        }
    }
    return -1;
}

Command *parse_command(char *line) {
    Command *cmd = malloc(sizeof(Command));
    cmd->args = malloc(sizeof(char *) * MAX_ARGS);
    cmd->arg_count = 0;

    char *tmp = line;

    // redirection 개수 확인
    int redirect_cnt = 0;
    while (*tmp != '\0') {
        if (*tmp == '<') {
            redirect_cnt++;
        }
        tmp++;
    }

    if (redirect_cnt > 1) {
        print_error();
        free_command(cmd);
        exit(EXIT_FAILURE);
    }

    char *command_part = strsep(&line, ">");
    char *redirect_part = line;

    char *token;
    tmp = command_part;

    while ((token = strsep(&tmp, " \t")) != NULL) {
        if (*token != '\0') {
            cmd->args[cmd->arg_count] = strdup(token);
            cmd->arg_count++;
        }
    }

    if (redirect_part != NULL) {
        if (*redirect_part == '\0' || *command_part == '\0') {
            print_error();
            return NULL;
        }
        tmp = redirect_part;
        while ((token = strsep(&tmp, " \t")) != NULL) {
            if (*token != '\0') {
                if (cmd->output_file != NULL) {
                    print_error();
                    free_command(cmd);
                    return NULL;
                }
                cmd->output_file = strdup(token);
            }
        }
    }

    cmd->args[cmd->arg_count] = NULL;
    return cmd;
}

int execute_command(Command *cmd, PathList *pl) {
    if (cmd->arg_count == 0) {
        return 0;
    }

    if (handle_builtin_command(cmd, pl)) {
        return 0;
    }

    return execute_external_command(cmd, pl);
}

int handle_builtin_command(Command *cmd, PathList *pl) {
    char *command = cmd->args[0];
    if (strcmp(command, "exit") == 0) {
        if (cmd->arg_count > 1) {
            print_error();
            return 1;
        }
        clear();
        exit(EXIT_SUCCESS);
    }

    if (strcmp(command, "cd") == 0) {
        if (cmd->arg_count != 2) {
            print_error();
            return 1;
        }
        if (chdir(cmd->args[1]) != 0) {
            print_error();
            return 1;
        }
        return 1;
    }

    if (strcmp(command, "path") == 0) {
        for (int i = 0; i < pl->path_count; i++) {
            free(pl->paths[i]);
        }

        pl->path_count = 0;
        for (int i = 1; i < cmd->arg_count; i++) {
            pl->paths[pl->path_count++] = strdup(cmd->args[i]);
        }
        return 1;
    }

    return 0;
}

int execute_external_command(Command *cmd, PathList *pl) {
    char path[BUFF_SIZE];

    if (search_path(path, cmd, pl) == 0) {
        pid_t pid = fork();

        if (pid == -1) {
            print_error();
            return -1;
        }

        if (pid == 0) {  // 자식 프로세스
            if (cmd->output_file != NULL) {
                int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    print_error();
                    exit(EXIT_FAILURE);
                }

                // 표준 출력을 파일로 리다이렉션
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    print_error();
                    close(fd);
                    exit(EXIT_FAILURE);
                }
                close(fd);  // 복제 후 원본 fd는 닫기
            }

            if (execv(path, cmd->args) == -1) {
                print_error();
                exit(EXIT_FAILURE);
            }
        }

        if (pid > 0) {  // 부모 프로세스
            int status;
            waitpid(pid, &status, 0);
            return status;
        }
    }

    print_error();
    return -1;
}

PathList *create_paths() {
    PathList *pl = malloc(sizeof(PathList));
    pl->paths = malloc(sizeof(char *) * MAX_PATHS);
    pl->paths[0] = strdup("/bin");
    pl->path_count = 1;
    return pl;
}

void free_command(Command *cmd) {
    if (cmd == NULL)
        return;

    for (int i = 0; i < cmd->arg_count; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    free(cmd);
}



int main(int argc, char *argv[]) {
    PathList *pl = create_paths();
    int mode = 0;
    fp = stdin;
    if (argc == 1) {
        mode = INTERACTIVE_MODE;
    } else {
        mode = BATCH_MODE;
        if (argc > 2 || (fp = fopen(argv[1], "r")) == NULL) {
            print_error();
            exit(EXIT_FAILURE);
        }
    }

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


        Command *cmd = parse_command(line);
        if (cmd != NULL) {
            execute_command(cmd, pl);
            free_command(cmd);
        }


    }
}

//
// Created by hiidy on 12/13/24.
//
