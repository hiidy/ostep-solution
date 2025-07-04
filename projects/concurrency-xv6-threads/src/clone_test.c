#include "types.h"
#include "user.h"
#include "thread.h"

int best_num = 42;
int number = 0;

void thread_func(char *s, int *i) {
    printf(1, "First arg: %s, second arg: %d\n", s, *i);
    printf(1, "best_num in thread: %d\n", best_num);
    best_num = *i;
    printf(1, "thread pid: %d\n", getpid());
    exit();
}

int main() {
    char *s = "I've tried not to remember no memories";
    int i = 69;
    printf(1, "Main thread pid: %d\n", getpid());
    printf(1, "Before thread_create()\n");

    int tid = thread_create((void (*)(void *, void *))thread_func, s, &i);
    if (tid < 0) {
        printf(1, "thread_create failed\n");
    }

    sleep(100);  // 충분히 기다려줌
    printf(1, "best_num in main: %d\n", best_num);
    exit();
}
