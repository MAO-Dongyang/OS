#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_t tid[2];
volatile unsigned int gCount = 5;

void *FirstThreadFunction(void *pArguments) {
  int i;
  for (i = 0; i < 100000000; i++) {
    pthread_mutex_lock(&mutex);
    gCount++;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *SecondThreadFunction(void *pArguments) {
  int i;
  for (i = 0; i < 100000000; i++) {
    pthread_mutex_lock(&mutex);
    gCount--;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&(tid[0]), NULL, FirstThreadFunction, NULL);
  pthread_create(&(tid[1]), NULL, SecondThreadFunction, NULL);
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&mutex);
  printf("gCount = %d\n", gCount);
  return 0;
}
