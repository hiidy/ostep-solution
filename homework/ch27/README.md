# Interlude: Thread API

## Questions

1. 경합이 생기는 데이터의 주소와 사이즈를 알려준다.

2. 공유변수 balacne를 갱신하는 코드 2개 중 하나를 제거하면 에러가 발생하지 않는다. 락을 하나만 추가하면 에러가 발생하고 2개 모두 추가하면 에러가 발생하지 않는다.

3. lock 획득 순서가 꼬여서 deadlock이 발생한다.

4. m1, m2에 대한 lock순서를 올바르게 하라고 알려줌.

5. global lock을 선언해서 데드락 상황을 피하고 있지만 helgrind가 잡아내지 못하고 같은 오류를 보여준다.

6. 자식 스레드가 완료되기 전까지 부모 스레드에 busy-waiting 발생

7. done 공유 변수에 동기화 없이 접근한다는 에러를 보여줌

8. 정확성, 성능 둘 다 좋아졌다. busy-waiting 하는 대신 conditon variable 사용해서 cpu 낭비를 막았다.(sleep 상태 유지) 그리고 lock으로 done 공유 변수와 관련된 동기화 문제 해결

9. 에러를 보여주지 않는다.