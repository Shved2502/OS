#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int count = 0;
int graph[][2] = {
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

void run(int top, int *visit) {
    visit[top] = 1;
    for (int i = 0; i < 9; ++i) {
        if ((graph[i][0] == top) && (visit[graph[i][1]] == 0)) {
            visit[graph[i][1]] = 1;
            pid_t pid = fork();
            if (pid > 0) {
                count++;
                printf("Parent process: pid %i, creating process pid %i, %i-%i \n", getpid(), pid, top, graph[i][1]);
                if (count == 7){
                   printf("Sum = %i", count);
                }
            } else {
                run(graph[i][1], visit);
            }
        }
    }
    int status;
    wait(&status);
}

int main() {
    printf("Main process: pid %i\n", getpid());
    int shared_mem_id;
    int *visit;
    if ((shared_mem_id = shmget(1, 6 * sizeof(int), IPC_CREAT | 0666)) < 0) {
        fprintf(stderr, "Error memory");
        return 1;
    }
    if ((visit = (int *) shmat(shared_mem_id, NULL, 0)) == (int *) -1) {
        fprintf(stderr, "Error memory");
        return 1;
    }
    memset(visit, 0, 8 * sizeof(int));
    run(0, visit);
    return 0;
}
