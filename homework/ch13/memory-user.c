#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("사용할 메모리의 MB수를 적어주세요\n");
        exit(EXIT_FAILURE);
    }

    long long input_bytes = atoll(argv[1]) * 1024 * 1024;

    char *array = malloc(input_bytes);

    printf("현재 pid: %d \n ", getpid());

    while (1) {
        for (long long i = 0; i < input_bytes; i++) {
            array[i] = 'x';
        }
    }
}