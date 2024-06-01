#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid;
    int burst;
    int arrival;
};

void findWaiting(struct process proc[], int n, int wt[]) {
    int rem[n];
    for (int i = 0; i < n; i++)
        rem[i] = proc[i].burst;
    
    int complete = 0, t = 0, min = INT_MAX;
    int shortest = 0, finish;
    int check = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrival <= t) && (rem[j] < min) && rem[j] > 0) {
                min = rem[j];
                shortest = j;
                check = 1;
            }
        }
        
        if (check == 0) {
            t++;
            continue;
        }

        rem[shortest]--;
        min = rem[shortest];
        if (min == 0)
            min = INT_MAX;

        if (rem[shortest] == 0) {
            complete++;
            check = 0;
            finish = t + 1;
            wt[shortest] = finish - proc[shortest].arrival - proc[shortest].burst;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findTAT(struct process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burst + wt[i];
    }
}

void findAvg(struct process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaiting(proc, n, wt);
    findTAT(proc, n, wt, tat);

    printf(" P\t\tBT\t\tWT\t\tTAT\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst, wt[i], tat[i]);
    }

    printf("\nAverage waiting time: %f", (float)total_wt / (float)n);
    printf("\nAverage Turnaround time: %f", (float)total_tat / (float)n);
}

int main() {
    struct process proc[] = {{1, 6, 2}, {2, 2, 5}, {3, 8, 1}, {4, 3, 0}, {5, 4, 4}};
    int n = sizeof(proc) / sizeof(proc[0]);

    findAvg(proc, n);
    return 0;
}
