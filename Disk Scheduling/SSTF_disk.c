#include<stdio.h>
#include<stdlib.h>

int findClosest(int *requests, int n, int current)
{
    int min = 999;
    int closest = -1;

    for(int i =0;i<n;i++)
    {
        int seek_dist = abs(requests[i] - current);
        if(seek_dist<min)
        {
            min = seek_dist;
            closest = requests[i];
        }
    }
    return closest;
}
int sstf(int *requests, int n, int init)
{
    int totalst = 0;
    int current = init;
    while(n>0)
    {
        int closest = findClosest(requests,n,current);
        int seek_dist = abs(closest - current);
        totalst +=seek_dist;
        current = closest;

        for(int i=0;i<n;i++)
        {
            if(requests[i]==closest)
            {
                for(int j=i;j<n-1;j++)
                {
                    requests[j] = requests[j+1];
                }
                n--;
                break;
            }
        }
    }
    return totalst;
}

int main()
{
    int n;
    printf("\nEnter the number of requests: ");
    scanf("%d",&n);

    int *requests = (int *)malloc(n * sizeof(int));
    if(requests == NULL)
    {
        printf("\nMemory allocation failed!");
        return 1;
    }
    printf("\nEnter the requests: ");
    for(int i =0;i<n;i++)
    {
        scanf("%d",&requests[i]);
    }
    int initial_pos;
    printf("\nEnter the initial position: ");
    scanf("%d",&initial_pos);

    int seekTime = sstf(requests,n,initial_pos);
    printf("\nThe total seek time using SSTF is: %d",seekTime);

    free(requests);

    return 0;
}
