# Interlude: Memory API


Question
1. null.c라는 간단한 프로그램을 작성하라. 이 프로그램은 정수를 가리키는 포인터를 만들고 NULL로 초기화하고 그것을 역참조하려고 한다. null이라는 실행 파일이 생성되도록 컴파일하라. 프로그램을 실행시키면 어떤 일이 발생하는가?
  `segmentation fault가 발생한다.`


2. 다음에 이 프로그램을 심볼 정보가 포함되도록 컴파일하라(-g 플래그 사용). 실행 파일에 더 많은 정보를 추가하여 디버거가 변수 이름 등의 유용한 정보를 접근할 수 있게 한다. 디버거에서 프로그램을 실행하라(gdb null). gdb가 실행되면, run 명령어를 입력하라.gdb는 무엇을 보여주는가?
    
    ```
    Program received signal SIGSEGV, Segmentation fault.
    0x00005555555551b6 in main (argc=1, argv=0x7fffffffe438) at null.c:8
    8	    printf("%d\n", *x);
    ```

3. 마지막으로, 이 프로그램에 valgrind 도구를 사용하라. 우리는 valgrind의 일부 인 memcheck 도구를 사용하여 어떤 일이 일어나는지 분석할 것이다. 다음과 같은 명령어를 실행시켜라 : valgrind - -leak-check=yes null. 이를 실행하면 어떻게 되는가? 출력을 해석할 수 있는가?  

    ```
    프로그램이 유효하지 않은 주소인 0x0에 접근하려고 함. (Invalid read of size 4) 두 번째 오류는 segmentation fault가 발생했다고 free가 제대로 되지 않았다고 한다. 
    ```

4. malloc()을 사용하여 메모리를 할당하지만 종료 전에 해제하는 것을 잊어버리는 간단한 프로그램을 작성하라. 이 프로그램을 실행시키면 무슨 일이 일어나는가? 이 프로그램의 문제를 gdb를 사용하여 발견할 수 있는가? valgrind는 어떤가(다시 - -leak-check=yes 플래그를 주고 실행)?

    ```
    프로그램은 문제 없이 실행된다. valgrind로 메모리 누수를 알 수 있다. gdb는 문제가 없다고 나옴.

5. 크기가 100인 data라는 이름의 정수 배열을 만드는 프로그램을 작성하라. 그런 후 data[100]을 0으로 클리어 하라. 이 프로그램을 실행하면 어떤 일이 벌어지는가? valgrind를 사용하여 프로그램을 실행하면 어떤 일이 일어나는가? 프로그램은 정확한가?
   
   ```
   아무런 일도 일어나지 않는다.
   ==2247== Invalid write of size 4
   ==2247==    at 0x1091B4: main (array_100.c:7)
   ==2247==  Address 0x4a8e1d0 is 0 bytes after a block of size 400 alloc'd
   ==2247==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   valgrind로 잘못된 메모리에 접근했다고 알 수 있다. -> 0~99까지만 접근 가능한데 100번째에 접근했기에 memory corruption이 발생.
   ```

6. 정수 배열을 할당하고(위와 동일), 다시 해제하고, 배열의 원소 하나의 값을 출력하려 고 시도하는 프로그램을 작성하라. 프로그램이 실행되는가? Valgrind를 사용하여 실행하면 어떤 일이 발생하는가?
   
   ```
   ==2247== Invalid read of size 4
   ==2247==    at 0x1091C4: main (array_100.c:8)==2247==  Address 0x4a8e1d0 is 0 bytes after a block of size 400 alloc'd
   ==2247==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==2247==    by 0x1091A5: main (array_100.c:5)
   잘못 할당한 메모리의 값을 읽기 때문에 Invalid read of size 4가 발생한다.
   ```

