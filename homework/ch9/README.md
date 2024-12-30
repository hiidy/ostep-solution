# Scheduling: Proportional Share


## Question

1. ```
   ./lottery.py -j 3 -s 0 -c
   ./lottery.py -j 3 -s 1 -c
   ./lottery.py -j 3 -s 1 -c
   ```
   
2. job1이 실행될 기회가 더 많다. 작업 0이 1이 종료 하기 전에 실행 될 확률은 1/101이다. 이런 불균형은 티켓이 적은 작업에 불리하다.
3. ```
   ./lottery.py -l 100:100,100:100 -s 0 -c
   U = 4/100 = 4%
   ./lottery.py -l 100:100,100:100 -s 1 -c
   U = 2/100 = 2%
   ./lottery.py -l 100:100,100:100 -s 2 -c
   U = 5/100 = 5%
   ./lottery.py -l 100:100,100:100 -s 3 -c
   U = 4/100 = 4%
   ```
   
4. 퀀텀의 크기가 커질수록 컨텍스트 스위칭이 줄어들고 따라서 각 작업이 더 오래 실행된다. -> 불공정성이 심해짐
5. x