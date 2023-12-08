#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* deposit(void* arg);
void* withdraw(void* arg);

int balance = 100;
int amount = 5;
int* amountPointer = &amount;

int main() {
    printf("initial balance: %d\n", balance);

    pthread_t wife_thread, husband_thread;
    pthread_create(&wife_thread, NULL, deposit, (void *)amountPointer);
    pthread_create(&husband_thread, NULL, withdraw, (void *)amountPointer);

    pthread_join(wife_thread, NULL);
    pthread_join(husband_thread, NULL);

    printf("final balance: %d\n", balance);

    return 0;
}

// deposit(), withdraw() 각 한 번씩만 실행
void* deposit(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    balance += amount;
}

void* withdraw(void* arg) {
    int* amountPointer = (int*) arg;
    int amount = *amountPointer;

    balance -= amount;
}

