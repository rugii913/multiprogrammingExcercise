#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
// cf. mutex code ex - https://dokhakdubini.tistory.com/466

void* deposit1(void* arg);
void* withdraw1(void* arg);
void* deposit2(void* arg);
void* withdraw2(void* arg);
void* deposit3(void* arg);
void* withdraw3(void* arg);

int balance = 10;
int amount = 5;
int* amountPointer = &amount;
pthread_mutex_t mutex;
char mutex_owner[3];
int repetition = 5;

int main() {
    printf("initial balance: %d\n", balance);

    pthread_t wife_thread1, husband_thread1;
    pthread_t wife_thread2, husband_thread2;
    pthread_t wife_thread3, husband_thread3;

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&wife_thread1, NULL, deposit1, (void *)amountPointer) != 0) return 1;
    if (pthread_create(&husband_thread1, NULL, withdraw1, (void *)amountPointer) != 0) return 2;
    if (pthread_create(&wife_thread2, NULL, deposit2, (void *)amountPointer) != 0) return 3;
    if (pthread_create(&husband_thread2, NULL, withdraw2, (void *)amountPointer) != 0) return 4;
    if (pthread_create(&wife_thread3, NULL, deposit3, (void *)amountPointer) != 0) return 5;
    if (pthread_create(&husband_thread3, NULL, withdraw3, (void *)amountPointer) != 0) return 6;

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

void* deposit2(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
        pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "d2");

        balance += amount;
        printf("balance: %d\tmutex_owner: %s\n", balance, mutex_owner);

        pthread_mutex_unlock(&mutex);
    }
}

void* deposit3(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
        pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "d3");

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
            printf("!!!!! 경고 !!!!! 잔액 부족\n");

            while (balance <= 0) {
                if (strcmp(mutex_owner, "w1")) {
                    pthread_mutex_unlock(&mutex);
                }
                continue;
            }

            pthread_mutex_lock(&mutex); // 잔고가 0이 아닌 것을 확인 후 while을 탈출했으면, 다시 mutex lock를 획득해야함
            strcpy(mutex_owner, "w1");
        }
        
        balance -= amount;
        printf("balance: %d\tmutex_owner: %s\n", balance, mutex_owner);
	    pthread_mutex_unlock(&mutex);
    }
}

void* withdraw2(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
    	pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "w2");

        if (balance <= 0) {
            printf("!!!!! 경고 !!!!! 잔액 부족\n");

            while (balance <= 0) {
                if (strcmp(mutex_owner, "w2")) {
                    pthread_mutex_unlock(&mutex);
                }
                continue;
            }

            pthread_mutex_lock(&mutex); // 잔고가 0이 아닌 것을 확인 후 while을 탈출했으면, 다시 mutex lock를 획득해야함
            strcpy(mutex_owner, "w2");
        }
        
        balance -= amount;
        printf("balance: %d\tmutex_owner: %s\n", balance, mutex_owner);
	    pthread_mutex_unlock(&mutex);
    }
}

void* withdraw3(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < repetition; i++) {
    	pthread_mutex_lock(&mutex);
        strcpy(mutex_owner, "w3");

        if (balance <= 0) {
            printf("!!!!! 경고 !!!!! 잔액 부족\n");

            while (balance <= 0) {
                if (strcmp(mutex_owner, "w3")) {
                    pthread_mutex_unlock(&mutex);
                }
                continue;
            }

            pthread_mutex_lock(&mutex); // 잔고가 0이 아닌 것을 확인 후 while을 탈출했으면, 다시 mutex lock를 획득해야함
            strcpy(mutex_owner, "w3");
        }
        
        balance -= amount;
        printf("balance: %d\tmutex_owner: %s\n", balance, mutex_owner);
	    pthread_mutex_unlock(&mutex);
    }
}
