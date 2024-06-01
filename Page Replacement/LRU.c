#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>


void cacheHeader()
{
    printf("Cache\t Hit/Miss\n");
}
void displayCache(int s[], int n,int page, bool isHit,bool displayHeader)
{
    if(displayHeader)
    {
        cacheHeader();
    }
    for(int i=0;i<n;i++)
    {
        printf("%d\t",s[i]);
        if(s[i]==page && isHit)
        {
            printf("Hit");
        }
        else
        {
            printf("Miss");
        }
        printf("\n");
    }
    printf("\n");
}
int pageFaults(int pages[], int n, int capacity)
{
    int s[capacity];
    int indexes[1000]={0};
    int page_faults = 0;
    bool displayHeader = true;
    for(int i =0;i<n;i++)
    {
        printf("Page %d - \n",pages[i]);
        bool isHit = false;
        for(int j =0;j<capacity;j++)
        {
            if(s[j]==pages[i])
            {
                isHit = true;
                break;
            }
        }
        if(!isHit)
        {
            if(page_faults == capacity)
            {
                int lru = INT_MAX,val;
                for(int j=0;j<capacity;j++)
                {
                    if(indexes[s[j]]<lru)
                    {
                        lru = indexes[s[j]];
                        val = s[j];
                    }
                }
                for(int j =0;j<capacity;j++)
                {
                    if(s[j]==val)
                    {
                        s[j]=pages[i];
                        break;
                    }
                }

            }
            else
            {
                s[page_faults] = pages[i];
            }
            page_faults++;
        }
        displayCache(s,capacity,pages[i],isHit,displayHeader);
        displayHeader = false;
        indexes[pages[i]] = 1;
    }
    return page_faults;
}
int main ()
{
    int n;
    printf("\nEnter number of pages: ");
    scanf("%d",&n);

    int pages[n];

    printf("\nEnter different page numbers: ");
    for(int i = 0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    int capacity;
    printf("\nEnter capcity of the cache: ");
    scanf("%d",&capacity);
    printf("\nPage Faults: %d",pageFaults(pages, n, capacity));

    return 0;
}