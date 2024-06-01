#include<stdio.h>
#include<stdbool.h>
bool search(int key,int fr[],int fr_size)
{
    for(int i=0;i<fr_size;i++)
    {
        if(fr[i]==key)
        {
            return true;
        }
    }
    return false;
}
int predict(int pg[],int n,int fr[],int fr_size,int index)
{
    int res=-1,farthest=index;
    for(int i=0;i<fr_size;i++)
    {
        int j;
        for(int j=index;j<n;j++)
        {
            if(fr[i]==pg[j])
            {
                if(j>farthest)
                {
                    farthest=j;
                    res=i;
                }
                break;
            }
        }
        if(j==n)
        {return i;}
    }
    return (res==-1)?0:res;
}void printFrames(int fr[],int fr_size)
{
    for(int i=0;i<fr_size;i++)
    {
        if(fr[i]==-1)
        {
            printf("-");
        }
        else
        {
            printf("%d",fr[i]);
        }
    }
}
void OptimalPage(int pg[],int n,int fn)
{
    int fr[fn];
    for(int i=0;i<fn;i++)
    {
        fr[i]=-1;
    }
    int hit=0;
    char result;
    printf("\nPage\tFrame\tHit/Miss");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t",pg[i]);
        if(search(pg[i],fr,fn))
        {
            hit++;
            result='H';
        }
        else
        {
            if(fr[fn-1]==-1)
            {
                fr[fn-1]=pg[i];
                result='M';
            }
            else{
                int j = predict(pg,n,fr,fn,i+1);
                result='M';
                fr[j]=pg[i];
            }
        }
        printFrames(fr,fn);
        printf("\t\t%c\n",result);
    }
    printf("\nNumber of hits: ",hit);
    printf("\nNnumber of Misses: ",n-hit);
}
int main()
{
    printf("\nEnter number of pages: ");
    int n;
    scanf("%d",&n);

    int pg[n];
    printf("\nEnter the page references: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pg[i]);
    }

    int fn;
    printf("\nEnter the number of frames: ");
    scanf("%d",&fn);

    OptimalPage(pg,n,fn);

    return 0;
}