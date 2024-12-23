# Address Translation

## Question

1. virtual address가 bound를 넘어가면 SEGMENTATION VIOLATION가 발생한다.

2. 930을 bound로 설정해야 한다. 시드를 0으로 설정했을 때 최대 VA가 929기 때문이다.

3. 16 * 1024 - 100 = 16284(bytes)가 최대 base다. 

4. base 레지스터의 최대값이 증가한다. 그리고 더 많은 가상 주소 범위를 다루게 된다. 

5. todo