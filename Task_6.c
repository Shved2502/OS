#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define gen_time 1000
#define sum_time 2000
#define prin_time 3000

// Ðàçìåðíîñòü ìàòðèö
#define N 3

int **A, **B, **C;

/* Çàïîëíèì ìàòðèöû A è B ñëó÷àéíûìè ÷èñëàìè.
srand(time(NULL)) – èíèöèàëèçàöèÿ ãåíåðàòîðà ñëó÷àéíûõ òåêóùèì âðåìåíåì
êîìïüþòåðà.
rand() % 10 – áåð¸ì îñòàòîê îò äåëåíèÿ íà 10, ñëåäîâàòåëüíî ýëåìåíòû ìàòðèöû
áóäóò çàïîëíÿòüñÿ ÷èñëàìè îò 0 äî 9.
*/
int flag;

void *generator() {
  while (1) {
    if (flag != gen_time) {
      sleep(1);
      continue;
    }
    srand(time(NULL));
    int i, j;
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++) {
        A[i][j] = rand() % 10;
        B[i][j] = rand() % 10;
      }
    flag = 2000;
  }
}

// Âûïîëíÿåì ñëîæåíèå ìàòðèö

void *summator() {
  while (1) {
    if (flag != sum_time) {
      sleep(1);
      continue;
    }
    int i, j;
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++) {
        C[i][j] = A[i][j] + B[i][j];
      }
    flag = 3000;
  }
}

// Âûâîäèì ìàòðèöû íà ýêðàí

void *printer() {
  while (1) {
    if (flag != prin_time) {
      sleep(1);
      continue;
    }
    int i, j;
    printf("matrix A\n");
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
        printf("%d ", A[i][j]);
      printf("\n");
    }
    printf("\nmatrix B\n");
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
        printf("%d ", B[i][j]);
      printf("\n");
    }
    printf("\nresult\n");
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
        printf("%3d ", C[i][j]);
      printf("\n");
    }
    printf("\n");
    sleep(4);
    flag = 1000;
  }
}

int main() {

  A = (int **)malloc(N * sizeof(int *));
  B = (int **)malloc(N * sizeof(int *));
  C = (int **)malloc(N * sizeof(int *));
  int i;
  for (i = 0; i < N; i++) {
    A[i] = (int *)malloc(N * sizeof(int));
    B[i] = (int *)malloc(N * sizeof(int));
    C[i] = (int *)malloc(N * sizeof(int));
  }

  flag = 1000;
  pthread_t gen, sum, print;
  pthread_create(&gen, NULL, generator, NULL);
  pthread_create(&sum, NULL, summator, NULL);
  pthread_create(&print, NULL, printer, NULL);

  // áîëüøå ãëàâíîìó ïîòîêó äåëàòü íå÷åãî
  while (1) {
  }
  /*
    for (i = 0; i < N; i++) {
      free(A[i]);
      free(B[i]);
      free(C[i]);
    }
    free(A);
    free(B);
    free(C);
  */
  return 0;
}
