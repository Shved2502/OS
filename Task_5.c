#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock;

const int n = 9;
const int graph[][2] = {
        {0, 1},
        {0, 2},
        {0, 3},
        {1, 4},
        {1, 5},
        {2, 6},
        {3, 7},
        {5, 6},
        {4, 7},
};

int *visit;
int *pass;
int count = 0;

void *run(void *arg) {
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
    int top = *((int *) arg);
    int i;
    for (i = 0; i < n; ++i) {
        if (graph[i][0] == top) {
            int c = graph[i][1];
            pthread_mutex_lock(&mutex);
            if (pass[i]) {
                pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
            }
            if (visit[c]) {
                printf("Thread %ld: %i-%i, top %i\n", pthread_self(), top, c, c);
                pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
            }
            visit[c] = 1;
            pass[i] = 1;
            pthread_mutex_unlock(&mutex);
            printf("Thread %ld: %i-%i\n", pthread_self(), top, c);
            pthread_t thr;
            pthread_create(&thr, NULL, run, &c);
            pthread_join(thr, NULL);
//            printf("Currient sum = %i\n", count);
        }
    }
    pthread_exit(NULL);
}

int main(){
  visit = (int *) malloc(n * sizeof(int));
  pass = (int *) malloc(n * sizeof(int));
  memset(visit, 0, n * sizeof(int));
  int v0 = 0;
  pthread_t init;
  pthread_create(&init, NULL, run, &v0);
  pthread_join(init, NULL);
  printf("Sum = %i\n", count);
  return 0;
}
