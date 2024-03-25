#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define ITERATIONS 1000000


int main() {

    // measure system call
    FILE *file;
    struct timeval start, end;
    double elapsed;

    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("no file");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&start, NULL);
    for (int i = 0; i < ITERATIONS; i++) {
        while (fgetc(file) != EOF) {

        }
        fseek(file, 0, SEEK_SET);
    }
    gettimeofday(&end, NULL);

    elapsed = (end.tv_sec - start.tv_sec) * 100000 + (end.tv_usec - start.tv_usec);
    printf("fopen system call time: %.2f", elapsed / ITERATIONS);
    fclose(file);

    // measure context switch

    pid_t pid;
    int pipe_fd[2];
    

    // create pipe
    if (pipe(pipe_fd) == -1) {
        perror("failed to create pipe");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&start, NULL);

    // parent process

    if ((pid == fork()) > 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            write(pipe_fd[1], "a", 1);
            read(pipe_fd[0], NULL, 1);
        }
        wait(NULL);
    } else if (pid == 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            read(pipe_fd[0], NULL, 1);
            write(pipe_fd[1], "a", 1);
        }
        exit(EXIT_SUCCESS);
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&end, NULL);

    elapsed = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

    printf("elapsed time: %.2f ms\n", elapsed);

    return 0;
    
}