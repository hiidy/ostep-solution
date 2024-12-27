# Concurrency and Threads

## Question

1. `./x86.py -p loop.s -t 1 -i 100 -R dx -c`를 실행하면 어떤 결과가 나오는지?
   - dx가 -1로 감소하고 이를 계속 반복하는 코드이다.
   - 초기값이 0이기 때문에 -1이 되고 halt 되므로 한 번만 반복된다.
  
2. `./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx`를 실행하면 어떤 결과가 나오는지?
   - dx에는 3이 저장된다.
   - 이 코드에서는 race가 발생하지 않는다. 왜냐하면 각자의 dx에 3이 저장되고 이후에는 dx가 -1로 감소하고 halt되기 때문이다.

3. `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -c`를 실행하면 어떤 결과가 나오는지?
   - 인터럽트가 무작위로 발생해서 스레드 실행의 순서 차이나 진행 속도가 차이가 발생한다.
   - 그러나 독립적으로 자신의 dx를 변화시키고 있기 때문에 race가 발생하지 않고 프로그램 결과에도 영향을 미치지 않는다.

4. `./x86.py -p looping-race-nolock.s -t 1 -M 2000 -c` 실행 결과는?
    - 2000번지에 값이 1이 증가하고 끝이다.

5. `python ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 -c` 의 실행 결과와 3번씩 반복되는 이유는?
    - loop를 담당하는 bx에 3이 저장되어 있기 때문에 loop를 끝날 때까지 각 스레드가 3번씩 반복된다.
    - 따라서 value의 최종 값은 6이 된다.

6. `python ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1 -c` race condition이 발생했는지?
   - seed에 따라서 race condition이 발생할 수도 있고 발생하지 않을 수도 있다.
   - 발생하게 된다면 thread0이 계산을 마치기 전에 thread 1이 계산이 끝났고 thread0은 그전에 불러온 레지스터의 값으로 계산을 하기 떄문이다.
   - 따라서 인터럽트의 타이밍이 중요하고 메모리 연산 전후에 발생하면 문제가 생기지 않는다.
   - 메모리 읽기 쓰기 사이에 인터럽트가 발생하면 문제가 발생함
  
7. `python ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 3` interrupt 주기가 몇 일 때 올바른 결과가 나오는가?
   - interrupt 주기가 3일 때 올바른 결과가 나온다.
   - 왜냐하면 2000번지에 옮겨야지 결과가 올바르게 나오기 때문이다.

8. 7에서 bx=100일 때  interval이 어떻게 되어야지 올바른 값이 나오는가?
   - interval이 3의 배수일 때

9. thread0은 2000번지를 1로 만들고 thread1은 2000번이 1이 될때까지 무한 루프
10. thread0은 계속 루프에 빠진다.