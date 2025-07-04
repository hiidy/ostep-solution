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

void count_func(lock_t *lock, int *loop) {
  lock_acquire(lock);
  for (int i = 0; i < *loop; i++)
    number += 1;
  lock_release(lock);
  exit();
}

void malloc_func(int *size, int *loop) {
  int *arr;
  for (int i = 0; i < *loop; i++) {
    arr = malloc(*size * sizeof(int));
    arr[0] = 1; // 메모리 접근 테스트
    free(arr);
  }
  exit();
}

int main() {
  char *s = "I've tried not to remember no memories";
  int i = 69;

  printf(1, "Main thread pid: %d\n", getpid());
  printf(1, "Before thread_create()\n");

  thread_create((void (*)(void *, void *))thread_func, s, &i);
  printf(1, "Returned thread pid: %d\n", thread_join());
  printf(1, "best_num in main: %d\n", best_num);

  lock_t lock;
  lock_init(&lock);

  int loop1 = 100;
  int loop2 = 200;

  thread_create((void (*)(void *, void *))count_func, &lock, &loop1);
  thread_create((void (*)(void *, void *))count_func, &lock, &loop2);
  thread_join();
  thread_join();

  printf(1, "number: %d\n", number);

  int size = 2048;
  thread_create((void (*)(void *, void *))malloc_func, &size, &loop1);
  thread_create((void (*)(void *, void *))malloc_func, &size, &loop1);
  thread_join();
  thread_join();

  exit();
}
