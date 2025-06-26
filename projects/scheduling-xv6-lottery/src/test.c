#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

#define LOOP 50

int main() {
  int pid1 = fork();
  if (pid1 == 0) {
    settickets(30);
    while (1) ; // 계속 CPU 사용
  }

  int pid2 = fork();
  if (pid2 == 0) {
    settickets(20);
    while (1) ;
  }

  int pid3 = fork();
  if (pid3 == 0) {
    settickets(10);
    while (1) ;
  }

  // parent: tick log 수집
  struct pstat st;
  for (int i = 0; i < LOOP; i++) {
    sleep(10); // 10 ticks 정도 기다림

    getpinfo(&st);
    for (int j = 0; j < NPROC; j++) {
      if (st.inuse[j]) {
        printf(1, "%d %d %d\n", st.pid[j], st.tickets[j], st.ticks[j]);
      }
    }
    printf(1, "---\n"); // 한 사이클 끝
  }

  kill(pid1);
  kill(pid2);
  kill(pid3);

  while(wait() != -1);
  exit();
}
