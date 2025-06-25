#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"  // NPROC 정의되어 있음

struct pstat {
  int inuse[NPROC];   // 프로세스 테이블의 이 슬롯이 사용 중인지 여부
  int tickets[NPROC]; // 각 프로세스의 티켓 수
  int pid[NPROC];     // PID
  int ticks[NPROC];   // 누적 틱 수
};

#endif // _PSTAT_H_
