#include "types.h"
#include "user.h"

int best_num = 42;
int number = 0;

void thread_func(char *s, int *i) {
  printf(1, "First arg: %s, second arg: %d\n", s, *i);
  printf(1, "best_num in thread: %d\n", best_num);
  best_num = *i;
  printf(1, "thread pid: %d\n", getpid());
  exit();
}

void malloc_func(int *size, int *loop) {
  int *arr;
  for (int i = 0; i < *loop; i++) {
    arr = malloc(*size * sizeof(int));
    arr[0] = 1; // 메모리 접근 테스트
    free(arr);
  }
}

int main() {
  char *s = "I've tried not to remember no memories";
  int i = 69;

  printf(1, "Main thread pid: %d\n", getpid());
  printf(1, "Before thread_create()\n");

  thread_create((void (*)(void *, void *))thread_func, s, &i);
  printf(1, "Returned thread pid: %d\n", thread_join());
  printf(1, "best_num in main: %d\n", best_num);
  exit();
}
