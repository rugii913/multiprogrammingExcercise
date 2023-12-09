### pthread를 이용한 synchronization 예제

1. synchroEx1.c
- 각 스레드가 critical section을 한 번만 실행

2. synchroEx2.c
- 각 스레드가 critical section을 50,000번 실행

3. synchroEx3.c
- usleep()을 넣어보았는데, 문제 상황이 보이지 않게 됐다.
  - 이유를 생각해내기 어려움

4. synchroMutexEx1.c
- mutex 코드 참고 - https://dokhakdubini.tistory.com/466
- 시연 때 문제 됐던 코드
  - 그런데 출력해보면 문제 없는 것 같기도 함

5. synchroMutexEx2.c
- 조금 더 정확하게 보기 위해 출력 시도
  - mutex lock을 갖고 있는 동안 mutex lock를 갖고 있는지도 출력하게 하도록 함
- 여기부터 text 파일로도 출력해서 확인했음

6. synchroMutexEx3.c
- 입금 thread 3개, 출금 thread 3개로 늘림
- 프로그램이 계속 실행 중, 뭔가 잘못됐다.
  - 작성 중인 텍스트 파일 크기가 3GB

7. synchroMutexEx4.c
- 잔액 부족 경고는 한 번만 나오게 함
  - 여전히 프로그램 종료가 안 됨
  - 반복 횟수를 20회 정도로 줄여도 종료가 안 되는 경우가 발생함
- 텍스트 파일 출력이 아니라 터미널 출력으로 확인하니
  - 잔액 부족이 뜨면 그 이후로 프로그램이 중지됨
  - 로직 자체의 문제는 아닌 것으로 추측 중

8. synchroMutexEx5.c
- 로직의 문제가 아니라고 착각하고 있었는데 로직 자체의 문제가 맞았음
  - withdraw 함수에서 while 안 if 조건문에서 Java만 생각하고 strcmp의 반환 타입을 확인할 생각도 안 했다.
  - strcmp의 반환 타입은 int이다. - C에서는 int를 true, false를 나타내는 데에 많이 사용한다.
    - 같으면 1, 다르면 0 ==> 소유 thread가 다른 경우 unlock
- 그 밖에 굳이 함수도 다 다르게 사용하진 않도록 함수 숫자 줄임
- 종종 실행 중에 에러 발생하고 있음 - pthread error msg.jpg, pthread error searching.jpg 참고

9. synchroMutexEx6.c
- 혹시 문제가 되는 부분이 같은 함수를 쓰는 thread라면 mutex_owner도 같은 문자열이 되는 부분인가 ㅏㅎ여
  - 문자열로 구분하지 않고, pthread_self()로 반환되는 id로 구분하도록 함
  - 그럼에도 불구하고 여전히 Ex5와 동일한 에러 발생하고 있음

*bash 명령어
- gcc [c 파일 이름] -o [실행 파일] -lpthread: pthread 이용한 컴파일
- ./[실행 파일] > [생성할 파일 이름].txt: 화면에 출력하지 않고 파일에 출력 결과 저장
