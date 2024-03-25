#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#define ITERATIONS 10000

int main() {
    int pipe_fd[2];
    pid_t pid;
    struct timeval start, end;
    double elapsed_time;

    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // 시작 시간 기록
    gettimeofday(&start, NULL);

    // 부모 프로세스
    if ((pid = fork()) > 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            // 파이프를 통해 데이터 쓰기
            write(pipe_fd[1], "a", 1);
            // 파이프로부터 데이터 읽기
            read(pipe_fd[0], NULL, 1);
        }
        // 부모 프로세스가 자식 프로세스의 종료를 기다림
        wait(NULL);
    }
    // 자식 프로세스
    else if (pid == 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            // 파이프로부터 데이터 읽기
            read(pipe_fd[0], NULL, 1);
            // 파이프를 통해 데이터 쓰기
            write(pipe_fd[1], "a", 1);
        }
        exit(EXIT_SUCCESS);
    }
    else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // 종료 시간 기록
    gettimeofday(&end, NULL);

    // 소요된 시간 계산
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0; // 초를 밀리초로 변환
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0; // 마이크로초를 밀리초로 변환

    printf("Elapsed time: %.2f milliseconds\n", elapsed_time);

    return 0;
}
