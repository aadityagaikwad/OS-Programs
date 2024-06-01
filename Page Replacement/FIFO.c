#include<stdio.h>
#include<stdbool.h>
struct PageTable
{
    int frame;
    bool valid;
};

bool isPresent(struct PageTable PT[],int page, int n)
{
    if(PT[page].valid==true)
    {
        return true;
    }
    return false;
}
void updatePageTable(struct PageTable PT[],int page, int fr_no,int status)
{
    PT[page].frame = fr_no;
    PT[page].valid = status;
}
void PrintContents(int frame[],int nframes)
{
    for(int i=0;i<nframes;i++)
        printf("%d\t",frame[i]);
    printf("\tH\n");
}
void PrintContentsHit(int frame[],int nframes)
{
    for(int i=0;i<nframes;i++)
        printf("%d\t",frame[i]);
    printf("\tH\n");
}

int main()
{
    int n,nframes,page_fault=0,page_hit=0,current=0;
    bool flag = false;

    printf("\nEnter number of pages: ");
    scanf("%d",&n);
    int reference[n];
    printf("\nEnter the different page numbers: ");
    for(int j=0;j<n;j++)
    {
        scanf("%d",&reference[j]);
    }
    printf("\nEnter the number of frames: ");
    scanf("%d",&nframes);

    int frame[nframes];
    for(int i=0;i<nframes;i++)
    {
        frame[i]=-1;
    }
    struct PageTable PT[50];
    for(int i=0;i<50;i++)
    {
        PT[i].valid=false;
    }
    printf("\nThe Contents inside the Frame array:\n\n");
    for(int i=0;i<nframes;i++)
    {
        printf("F%d\t",i);
    }
    printf("Hit or Miss\n\n");
    for(int i=0;i<n;i++)
    {
        if(!(isPresent(PT,reference[i],n)))
        {
            page_fault++;
            if(flag==false && current<nframes)
            {
                frame[current] = reference[i];
                PrintContents(frame,nframes);
                updatePageTable(PT,reference[i],current,true);
                current += 1;
                if(current == nframes)
                {
                    current=0;
                    flag = true;
                }
            }
            else
            {
                updatePageTable(PT,frame[current],-1,false);
                frame[current] = reference[i];
                PrintContents(frame,nframes);
                updatePageTable(PT,reference[i],current,true);
                current=(current + 1)%nframes;
            }
        }
        else
        {
            PrintContentsHit(frame,nframes);
            page_hit++;
        }
    }
    printf("\nTotal Page faults: %d",page_fault);
    printf("\nTotal PAge Hits: %d",page_hit);
    printf("\nPage Fault Ratio: %f",(float)page_fault/n);
    printf("\nPage Hit Ratio: %f",(float)page_hit/n);

    return 0;
}