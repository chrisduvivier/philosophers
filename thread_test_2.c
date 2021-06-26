#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define BIG 10000000UL
__uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *count_to_big(void *arg) {
    (void) arg;
    for (__uint32_t i=0; i < BIG; i++)
    {
        pthread_mutex_lock(&lock);          //thread will wait here until it can get the lock  
        counter++;
        pthread_mutex_unlock(&lock);        // unlock
    }
    return (NULL);
}

int main()
{
    pthread_t new_thread;

    pthread_create(&new_thread, NULL, count_to_big, NULL);
    count_to_big(NULL);
    pthread_join(new_thread, NULL);     //make it wait for the end of thread before exit main.
    printf("Done. Counter = %d\n", counter);
    return (0);
}
