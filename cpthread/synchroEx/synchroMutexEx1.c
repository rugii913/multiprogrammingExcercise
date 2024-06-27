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

    for (int i = 0; i < 5000; i++) {
	pthread_mutex_lock(&mutex);
        balance += amount;
        printf("balance: %d\n", balance);
	pthread_mutex_unlock(&mutex);
    }
}

void* withdraw(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    for (int i = 0; i < 5000; i++) {
	pthread_mutex_lock(&mutex);
        balance -= amount;
        printf("balance: %d\n", balance);
	pthread_mutex_unlock(&mutex);
    }
}
