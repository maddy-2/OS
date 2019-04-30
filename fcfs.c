#include<stdio.h>
 
int main()
{
    int n,bt[5],wt[5],avwt=0,i,j;
    printf("Enter total number of processes(max 5):");
    scanf("%d",&n);
 
    printf("\nEnter Process Burst Time\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
 
    wt[0]=0;    
 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("\nProcess\t\tBurst Time\tWaiting Time");
 
   
    for(i=0;i<n;i++)
    {
       
        avwt+=wt[i];
        printf("\nP[%d]\t\t%d\t\t%d",i+1,bt[i],wt[i]);
    }
 	
    avwt/=i;
    printf("\n\nAverage Waiting Time:%d",avwt);
   
 
    return 0;
}
