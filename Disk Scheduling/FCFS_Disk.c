#include<stdio.h>
#include<stdlib.h>

int fcfs(int *requests,int n,int init_pos)
{
    int total_st = 0;
    int current = init_pos;
    for(int i = 0;i<n;i++)
    {
        int seek_dist = abs(requests[i] - current);
        total_st += seek_dist;
        current = requests[i];
    }
    return total_st;
}
int main ()
{
    int num_requests;
    printf("\nEnter number of requests in the request queue: ");
    scanf("%d",&num_requests);

    int * reqQueue = (int *)malloc(num_requests* sizeof(int));
        if(reqQueue == NULL)
        {
            printf("\nMemory allocation failed!");
            return 1;
        }
        printf("\nEnter the requests: ");
        for(int i =0;i<num_requests;i++)
        {
            scanf("%d",&reqQueue[i]);
        }
        int initial;
        printf("\nEnter initial Position: ");
        scanf("%d",&initial);

        int seektime = fcfs(reqQueue,num_requests,initial);

        printf("\nTotal seek time using FCFS aaproach: %d",seektime);

        free(reqQueue);
        return 0;  
}