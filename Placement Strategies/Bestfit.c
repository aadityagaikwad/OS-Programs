#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Block
{
    int size;
    int alloc;
};

void Bestfit(struct Block *memory,int nblocks,int prosize)
{
    int index = -1; //-1 indicates no suitable block has been found
    int minSize = INT_MAX;
    for(int i=0;i<nblocks;i++)
    {
        if(!memory[i].alloc && memory[i].size >= prosize)
        {
            if(memory[i].size < minSize)
            {
                minSize = memory[i].size;
                index = i;
            }
        }
    }

if(index!=-1)
{
    memory[index].alloc = 1;
    printf("\nProcess allocated to Block %d",index+1);
}
else
{
    printf("\nNo suitable block found for the process");
}
}
int main()
{
    int nblocks;
    printf("\nEnter number of blocks: ");
    scanf("%d",&nblocks);
    struct Block *memory = (struct Block*)malloc(nblocks * sizeof(struct Block));
    for(int i=0;i<nblocks;i++)
    {
        printf("\nEnter size of block: ");
        scanf("%d",&memory[i].size);
        memory[i].alloc = 0;
    }
    int npro;
    printf("\nEnter number of processes: ");
    scanf("%d",&npro);
   
    for(int j=0;j<npro;j++)
    {
        int prosize;
        printf("\nEnter size of process: ");
        scanf("%d",&prosize);
        Bestfit(memory,nblocks,prosize);
    }
    free(memory);
    return 0;
}