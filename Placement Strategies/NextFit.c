#include<stdio.h>
#include<stdlib.h>
struct Block
{
    int size;
    int alloc;
};

void NextFit(struct Block *memory, int nblocks, int prosize,int *lastAllocated)
{
    int startIndex = *lastAllocated;
    
    do
    {
        if(!memory[startIndex].alloc && memory[startIndex].size >= prosize)
        {
            memory[startIndex].alloc = 1;
            printf("\nProcess allocated to block %d", startIndex+1);
            *lastAllocated = (startIndex + 1)%nblocks;
            return;
        }
        startIndex = (startIndex+1)%nblocks;
    } while(startIndex!= *lastAllocated);
    {
        printf("\nNo suitable block found.");
    }
    
}
int main()
{
    int nblocks;
    printf("\nEnter number of blocks: ");
    scanf("%d",&nblocks);
    struct Block *memory = (struct Block*)malloc(nblocks  * sizeof(struct Block));
    for(int i=0;i<nblocks;i++)
    {
        printf("\nEnter size of block: ");
        scanf("%d",&memory[i].size);
        memory[i].alloc = 0;
    }
    int npro;
    int lastAllocated = 0;
    printf("\nEnter number of processes: ");
    scanf("%d",&npro);
    for(int j=0;j<npro;j++)
    {
        int prosize;
        printf("\nEnter size of Process: ");
        scanf("%d",&prosize);
        NextFit(memory,nblocks,prosize,&lastAllocated);
    }
    free(memory);
    return 0;

}