#include<stdio.h>
#include<stdlib.h>
struct Block
{
    int size;
    int alloc;
};

void WorstFit(struct Block * memory,int nblocks, int prosize)
{
    int index = -1;
    int max = 0;

    for(int i=0;i<nblocks;i++)
    {
        if(!memory[i].alloc && memory[i].size >= prosize)
        {
            if(memory[i].size>max)
            {
                max = memory[i].size;
                index = i;
            }
        }
    }
    if(index!=-1)
    {
        memory[index].alloc = 1;
        printf("\nProcess allocated to block %d",index +1);
    }
    else{
        printf("\nNo suitable block found");
    }
}


int main()
{
    int nblocks;
    printf("\nEnter number of blocks: ");
    scanf("%d",&nblocks);
    struct Block *memory = (struct Block *)malloc(nblocks * sizeof(struct Block));
    for(int i=0;i<nblocks;i++)
    {
        printf("\nEnter size of block: ");
        scanf("%d",&memory[i].size);
        memory[i].alloc = 0;
    }
    int npro;
    printf("\nEnter number of processes: ");
    scanf("%d",&npro);
    int prosize;
    for(int j=0;j<npro;j++)
    {
        printf("\nEnter size of process: ");
        scanf("%d",&prosize);
        WorstFit(memory,nblocks,prosize);
    }
    free(memory);
    return 0;
}
