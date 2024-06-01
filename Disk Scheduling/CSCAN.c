#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare(const void*a, const void*b)
{
    return (*(int*)a-*(int*)b);
}
int cscan(int *requests,int n,int init,char *direction,int track_size)
{
    int totalst = 0;
    int current = init;
    int *left = NULL;
    int *right = NULL;
    int flag1=0,flag2=0;

    left = (int*)malloc(n*sizeof(int));
    if(left==NULL)
    {
        printf("\nMemory not allocated!!");
        return -1;
    }
    right = (int *)malloc(n*sizeof(int));
    if(right==NULL)
    {
        printf("\nMemory not allocated!!");
        free(left);
        return -1;
    }
    left[0]=0;
    right[0]=track_size-1;

    int left_count=1,right_count=1;
    for(int i=0;i<n;i++)
    {
        if(requests[i]<init)
        {
            left[left_count++]=requests[i];
        }
        else
        {
            right[right_count++]=requests[i];
        }
        qsort(left,left_count,sizeof(int),compare);
        qsort(right,right_count,sizeof(int),compare);

        int run = 2;
        while(n--)
        {
            if(strcmp(direction,"right")==0)
            {
                for(int i=0;i<right_count;i++)
                {
                    int distance = abs(right[i]-current);
                    totalst += distance;
                    current = right[i];
                }
                strcpy(direction,"left");
                flag1=1;
                current = 0;
            }
            else if(strcmp(direction,"left")==0)
            {
                for(int i=0;i<left_count;i++)
                {
                    int distance = abs(left[i]-current);
                    totalst += distance;
                    current = left[i];
                }
                strcpy(direction,"right");
                current = track_size-1;
                flag2=1;
            }
        }
        if(flag1==1 && flag2==1)
        {
            totalst += track_size-1;
        }
        free(left);
        free(right);

        return totalst;
    }
}
int main()
{
    int n;
    printf("Enter the number of track requests you want: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the track requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    int init;
    printf("Enter the Initial Position of the head: ");
    scanf("%d", &init);

    char direction[10];
    printf("Enter the direction (left/right): ");
    scanf("%s", direction);

    int track_size;
    printf("Enter the maximum number of tracks: ");
    scanf("%d", &track_size);

    int seekTime = cscan(requests, n, init, direction, track_size);

    printf("The total seek time is: %d\n", seekTime);

    free(requests);

    return 0;
}