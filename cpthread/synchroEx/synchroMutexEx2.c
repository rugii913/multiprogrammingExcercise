#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// cf. mutex code ex - https://dokhakdubini.tistory.com/466

void* deposit(void* arg);
void* withdraw(void* arg);

int balance = 100;
int amount = 5;
int* amountPointer = &amount;
pthread_mutex_t mutex;
char mutex_owner;

int main() {
    printf("initial balance: %d\n", balance);

    pthread_t wife_thread, husband_thread;

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&wife_thread, NULL, deposit, (void *)amountPointer) != 0) return 1;
    if (pthread_create(&husband_thread, NULL, withdraw, (void *)amountPointer) != 0) return 2;

    if (pthread_join(wife_thread, NULL) != 0) return 3;
    if (pthread_join(husband_thread, NULL) != 0) return 4;

    pthread_mutex_destroy(&mutex);
    printf("final balance: %d\n", balance);

    return 0;
}

void* deposit(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < 500; i++) {
        pthread_mutex_lock(&mutex);
        mutex_owner = 'd';

        balance += amount;
        printf("balance: %d\tmutex_owner: %c\n", balance, mutex_owner);

        pthread_mutex_unlock(&mutex);
    }
}

void* withdraw(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < 500; i++) {
    	pthread_mutex_lock(&mutex);
        mutex_owner = 'w';
        /*
        // 지적된 부분
    	if (balance - amount < 0) {
    		printf("!!balance <= 0!!\n");
    		pthread_mutex_unlock(&mutex);
    		continue;
    	}
        */
        /*
        // 뭔가 그럴싸해보이도록 출력되게 만들었지만 unlock하는 부분에서 문제 발생함
        while (balance - amount < 0) {
            printf("!!!!! WARNING !!!!! balance <= 0\n");
            if (mutex_owner == 'w') {
                pthread_mutex_unlock(&mutex);
            }
    		continue;
        }
        */

        if (balance <= 0) {
            while (balance <= 0) {
                printf("!!!!! WARNING !!!!! out of balance\n");
                if (mutex_owner == 'w') {
                    pthread_mutex_unlock(&mutex);
                }
                continue;
            }

            pthread_mutex_lock(&mutex); // 잔고가 0이 아닌 것을 확인 후 while을 탈출했으면, 다시 mutext를 획득해야함
            mutex_owner = 'w';
        }
        
        balance -= amount;
        printf("balance: %d\tmutex_owner: %c\n", balance, mutex_owner);
	    pthread_mutex_unlock(&mutex);
    }
}
