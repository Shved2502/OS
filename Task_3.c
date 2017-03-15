#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int graph[][2] = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 3},
    {1, 2},
    {2, 4},
    {3, 2},
    {4, 5},
    {4, 6},
    {5, 7},
    {5, 8},
    {6, 9},
    {7, 8},
    {8, 9}
};

void run(int top, int *visit) {
    visit[top] = 1;
    for (int i = 0; i < 14; ++i) {
        if ((graph[i][0] == top) && (visit[graph[i][1]] == 0)) {
            visit[graph[i][1]] = 1;
            pid_t pid = fork();
            if (pid > 0) {
                printf("Parent process: pid %i, creating process pid %i, %i-%i \n", getpid(), pid, top, graph[i][1]);
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
        fprintf(stderr, "Error while allocating shared memory.");
        return 1;
    }
    if ((visited = (int *) shmat(shared_mem_id, NULL, 0)) == (int *) -1) {
        fprintf(stderr, "Error while attaching shared memory.");
        return 1;
    }
    memset(visit, 0, 10 * sizeof(int));
    run(0, visit);
    return 0;
}
