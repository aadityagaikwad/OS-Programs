#include <stdio.h>
#include <stdlib.h>

int findMinAT(int *arrive, int *executed, int npro) {
    int min = 999, idx = -1;
    for (int i = 0; i < npro; i++) {
        if (!executed[i] && arrive[i] < min) {
            min = arrive[i];
            idx = i;
        }
    }
    return idx;
}

void fcfs(int *process, int *arrive, int *burst, int npro) {
    int *completion = (int *)malloc(npro * sizeof(int));
    int *turnAround = (int *)malloc(npro * sizeof(int));
    int *waiting = (int *)malloc(npro * sizeof(int));
    int *executed = (int *)calloc(npro, sizeof(int));
    int currTime = 0;

    for (int i = 0; i < npro; i++) {
        int min = findMinAT(arrive, executed, npro);
        int factor = 0;
        if (arrive[min] > currTime) {
            factor = arrive[min] - currTime;
        }
        completion[min] = burst[min] + currTime + factor;
        currTime = completion[min];
        executed[min] = 1;
    }

    for (int i = 0; i < npro; i++) {
        turnAround[i] = completion[i] - arrive[i];
        waiting[i] = turnAround[i] - burst[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < npro; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrive[i], burst[i], completion[i], turnAround[i], waiting[i]);
    }

    int totalTAT = 0, totalWT = 0;
    for (int i = 0; i < npro; i++) {
        totalTAT += turnAround[i];
        totalWT += waiting[i];
    }
    float avgTAT = (float)totalTAT / npro;
    float avgWT = (float)totalWT / npro;

    printf("\nAverage Turnaround Time: %.2f", avgTAT);
    printf("\nAverage Waiting Time: %.2f", avgWT);

    free(completion);
    free(turnAround);
    free(waiting);
    free(executed);
}

int main() {
    int n = 4;
    int pro[] = {1, 2, 3, 4};
    int at[] = {0, 1, 4, 5};
    int bt[] = {2, 2, 3, 4};
    fcfs(pro, at, bt, n);
    return 0;
}
