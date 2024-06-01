#include <stdio.h>

struct process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void round_robin(struct process proc[], int n, int time_slice) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    int queue[100], front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].remaining_time = proc[i].burst_time;
        queue[rear++] = i;
    }

    while (completed < n) {
        int i = queue[front++];
        if (proc[i].remaining_time > 0) {
            if (proc[i].remaining_time <= time_slice) {
                current_time += proc[i].remaining_time;
                proc[i].remaining_time = 0;
                proc[i].turnaround_time = current_time - proc[i].arrival_time;
                proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                total_waiting_time += proc[i].waiting_time;
                total_turnaround_time += proc[i].turnaround_time;
                completed++;
            } else {
                current_time += time_slice;
                proc[i].remaining_time -= time_slice;
                queue[rear++] = i;
            }
        }
    }

    printf("Process ID\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", proc[i].id, proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, time_slice = 4;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process proc[n];

    printf("Enter Arrival time and Burst time of the processes:\n");
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    round_robin(proc, n, time_slice);

    return 0;
}
