#include "types.h"
#include "user.h"

int thread_create(void (*start_routine)(void *, void *), void *arg1, void *arg2) {

    void *stack;
    stack = malloc(4096);

    int pid = clone(start_routine, arg1, arg2, stack);

    if (pid < 0) {
        return -1;
    }

    return pid;
}