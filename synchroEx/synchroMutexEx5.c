#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
// cf. mutex code ex - https://dokhakdubini.tistory.com/466

void* deposit1(void* arg);
void* withdraw1(void* arg);

int balance = 10;
int amount = 5;
int* amountPointer = &amount;
pthread_mutex_t mutex;
char mutex_owner[3];
const int repetition = 50;

int main() {
    printf("initial balance: %d\n", balance);

    pthread_t wife_thread1, husband_thread1;
    pthread_t wife_thread2, husband_thread2;
    pthread_t wife_thread3, husband_thread3;

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&wife_thread1, NULL, deposit1, (void *)amountPointer) != 0) return 1;
    if (pthread_create(&husband_thread1, NULL, withdraw1, (void *)amountPointer) != 0) return 2;
    if (pthread_create(&wife_thread2, NULL, deposit1, (void *)amountPointer) != 0) return 3;
    if (pthread_create(&husband_thread2, NULL, withdraw1, (void *)amountPointer) != 0) return 4;
    if (pthread_create(&wife_thread3, NULL, deposit1, (void *)amountPointer) != 0) return 5;
    if (pthread_create(&husband_thread3, NULL, withdraw1, (void *)amountPointer) != 0) return 6;

    if (pthread_join(husband_thread1, NULL) != 0) return 8;
    if (pthread_join(wife_thread1, NULL) != 0) return 7;
    if (pthread_join(husband_thread2, NULL) != 0) return 10;
    if (pthread_join(wife_thread2, NULL) != 0) return 9;
    if (pthread_join(wife_thread3, NULL) != 0) return 11;
    if (pthread_join(husband_thread3, NULL) != 0) return 12;

    pthread_mutex_destroy(&mutex);
    printf("final balance: %d\n", balance);

    return 0;
}

void* deposit1(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
        pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "d1");

        balance += amount;
        printf("balance: %d\tmutex_owner: %s\n", balance, mutex_owner);

        pthread_mutex_unlock(&mutex);
    }
}

void* withdraw1(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
    	pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "w1");
    
        if (balance <= 0) {
            printf("!!!!! 경고 !!!!! 잔액 부족 mutex_owner_thread_id: %lu\n", pthread_self());

            while (balance <= 0) {
                if (strcmp(mutex_owner, "w1") == 0) { // 이 부분이 문제였다. Java를 생각하고 strcmp의 반환 타입이 int인 걸 생각도 안 했다.
                    pthread_mutex_unlock(&mutex);
                    // usleep(100); // pthread_exit; // 어디가 문제인지 몰라서 시험삼아 넣어봤던 로직들
                }
                continue;
            }

            pthread_mutex_lock(&mutex); // 잔고가 0이 아닌 것을 확인 후 while을 탈출했으면, 다시 mutex lock를 획득해야함
            strcpy(mutex_owner, "w1");
        }
        
        balance -= amount;
        printf("balance: %d\tmutex_owner_thread_id: %lu\n", balance, pthread_self());
	    pthread_mutex_unlock(&mutex);
    }
}

// 현재 실행 중에 간혹 아래 에러 발생하고 있음 - pthread error msg.jpg, pthread error searching.jpg 참고
// synchroMutexEx5: pthread_mutex_lock.c:94: ___pthread_mutex_lock: Assertion `mutex->__data.__owner == 0' failed.
// [1]    7661 IOT instruction  ./synchroMutexEx5 > log/logSynchroMutexEx5.txt
