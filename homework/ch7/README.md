# Scheudling: Introduction

## Homework (Simulation)
process-run.py 프로그램을 실행하면서 다음 질문에 답하기

Question
1. 길이가 200인 세 개의 작업을 SJF와 FIFO 스케줄링 방식으로 실행할 경우 응답 시간과 반환 시간을 계산하시오.
  
  ```
  ./scheduler.py -l 200,200,200 -p SJF  -c 
  Response Time: 0, 200, 400
  Turnaround Time: 200, 400, 600

  ./scheduler.py -l 200,200,200 -p FIFO  -c
  Response Time: 0, 200, 400
  Turnaround Time: 200, 400, 600
  ```

2. 같은 조건이지만 작업의 길이가 각각 100, 200 및 300일 경우에 대해 계산하시오.

  ```
  ./scheduler.py -l 100,200,300 -p SJF  -c 
  Response Time: 0, 100, 300
  Turnaround Time: 100, 300, 600
  
  ./scheduler.py -l 100,200,300 -p FIFO  -c
  Response Time: 0, 100, 300
  Turnaround Time: 100, 300, 600
  ```

3. 2번과 같은 조건으로 타임 슬라이스가 1인 RR 스케줄러에 대해서도 계산하시오.

  ```
  ./sceduler.py -l 100,200,300 -p RR -c
  Response Time: 0, 1, 2
  Turnaround Time: 298, 499, 600
  ```

4. SJF와 FIFO가 같은 반환 시간을 보이는 워크로드의 유형은 무엇인가?
  SJF는 짧은 순서대로 처리하기 때문에 작업의 길이가 오름차순으로 정렬되어 있으면 같은 반환 시간을 보인다.

5. SJF가 RR과 같은 응답 시간을 보이기 위한 워크로드와 타임 퀀텀의 길이는 무엇인가?
  워크로드의 작업 시간과 타임 퀀텀의 길이가 모두 같아야 한다.

6. 작업의 길이가 증가하면 SJF의 응답 시간은 어떻게 되는가? 변화의 추이를 보이기 위해서 시뮬레이터를 사용할 수 있는가?
  작업의 길이가 증가할수록 응답 시간이 증가한다.

7. 타임 퀀텀의 길이가 증가하면 RR의 응답 시간은 어떻게 되는가? N개의 작업이 주어졌을 때, 최악의 응답 시간을 계산하는 식을 만들 수 있는가?
  -TODO
