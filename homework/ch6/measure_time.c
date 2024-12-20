#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <fcntl.h>
#define ITER 1000000
#define SWITCH_NUM 10000

double measure_syscall() {
    struct timeval start, end;
    int fd = open("/dev/null", O_RDONLY);
    gettimeofday(&start, NULL);

    for (int i = 0; i < ITER; i++) {
        char buf;
        read(fd, &buf, 0);
    }

    gettimeofday(&end, NULL);
    close(fd);

    double total_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    return total_time / ITER;
}

double measure_context_switch() {
    struct timeval start, end;
    int pipe1[2], pipe2[2];
    cpu_set_t set;

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        perror("pipe creation failed");
        exit(1);
    }

    CPU_ZERO(&set);
    CPU_SET(0, &set);


    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork 실패");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // 자식 프로세스
        if (sched_setaffinity(0, sizeof(set), &set) < 0) {
            perror("sched_setaffinity 실패");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < SWITCH_NUM; i++) {
            char buf;
            read(pipe1[0], &buf, 1);
            write(pipe2[1], "from child", 1);
        }
        exit(0);
    } else {// 부모 프로젝스
        if (sched_setaffinity(0, sizeof(set), &set) < 0) {
            perror("sched_setaffinity 실패");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < SWITCH_NUM; i++) {
            write(pipe1[1], "from parent", 1);
            char buf;
            read(pipe2[0], &buf, 1);
        }

        wait(NULL);
    }
    gettimeofday(&end, NULL);

    double total_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    return total_time / (SWITCH_NUM * 2);

}

long get_diff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) * 1000000 + (end->tv_usec - start->tv_usec);
}

int main() {
    struct timeval start, end;
    const int iter = 1000000;
    long diff;
    long min_diff = 10000000;
    long total_diff = 0;

    printf("%d번 만큼 타이머 정밀도 측정 \n", iter);

    for (int i = 0; i < iter; i++) {
        gettimeofday(&start, NULL);
        gettimeofday(&end, NULL);

        diff = get_diff(&start, &end);
        if (diff < 0) {
            continue;
        }

        if (diff < min_diff && diff > 0) {
            min_diff = diff;
        }

        total_diff += diff;
    }
    printf("측정 반복 횟수: %d\n", ITER);
    printf("평균 시간 차이: %.2f 마이크로초\n", (double)total_diff / ITER);
    printf("최소 시간 차이: %ld 마이크로초\n", min_diff);
    printf("-------------------------------------\n");
    printf("read syscall 측정\n");
    double syscall_time = measure_syscall();
    printf("시스템 콜 평균 비용: %.3f 마이크로초\n", syscall_time);

    printf("-------------------------------------\n");
    printf("context switch 측정\n");
    double context_switch_cost = measure_context_switch();
    printf("컨텍스트 스위치 평균 비용: %.3f 마이크로초\n", context_switch_cost);

    return 0;
}

