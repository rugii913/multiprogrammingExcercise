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

*bash 명령어
- gcc [c 파일 이름] -o [실행 파일] -lpthread: pthread 이용한 컴파일
- ./[실행 파일] > [생성할 파일 이름].txt: 화면에 출력하지 않고 파일에 출력 결과 저장
