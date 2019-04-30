//SJF Non-Preemptive


#include <stdio.h>
#include <stdlib.h>

void ganttchart(int t[], int s[], int p)
{
	int i, j;
	for (i=0; i<=p; i++)
		for (j=0; j<=2*(t[i+1]-t[i]); j++)
			if (j==0)
				printf(" ");
			else
				printf("-");
	printf("\n");
	for (i=0; i<=p; i++)
		for (j=0; j<=2*(t[i+1]-t[i]); j++)
			if (j==0)
				printf("|");
			else if (j==(t[i+1]-t[i])&&i!=0)
			{
				printf("P%d", s[i-1]+1);
				j++;
			}
			else if (j==(t[i+1]-t[i])&&i==0)
			{
				printf("ID");
				j++;
			}
			else
				printf(" ");			
	printf("|\n");
	for (i=0; i<=p; i++)
		for (j=0; j<=2*(t[i+1]-t[i]); j++)
			if (j==0)
				printf(" ");
			else
				printf("-");
	printf("\n");
	
	for (i=0; i<=p; i++)
		for (j=0; j<=2*(t[i+1]-t[i]); j++)
			if (j==0)
			{
				printf("%d", t[i]);
			}
			else
				printf(" ");
	printf("%d\n", t[p+1]);
}

void drawtable (int a[], int t[], int c[], int tatime[], int wtime[], int p)
{
    int i, j;
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("|    Programs   | Arrival Time  |  Burst Time   |Completion Time|Turnaround Time| Waiting Time  |");
    printf("\n-------------------------------------------------------------------------------------------------\n");
    for (i=0; i<p; i++)
    {
        
        printf("|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", i+1, a[i], t[i], c[i], tatime[i], wtime[i]);

        
    }  
    printf("-------------------------------------------------------------------------------------------------\n");
} 

int main()
{
	int b[10], w[10], a[10], c[10], tatime[10], t[10], gantt[50], wtime[10], s[50];
	int i, j, k=0, min, count = 0, n, r=0;
	double wt = 0, tat = 0, ct, awt, atat;

	printf("\nNON-PREEMPTIVE SHORTEST JOB FIRST:");
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival timr and burst time:\n");
    for(i=0; i<n; i++)
    {
       
	scanf("%d %d",&a[i],&b[i]);
        t[i]=b[i];
        w[i]=b[i];
        
    }

   
	b[9]=9999;
	for(i=0; count!=n; i++)
	{
		min=9;
		for(j=0; j<n; j++)
		{
			if(a[j]<=i && b[j]<b[min] && b[j]>0)
				
			{
				if(b[j]==b[min])
				{
					if(a[j]<a[min])
						min=j;
				}
				else				
					min=j;
			}
		}
		
		if(min!=9)
        {
			s[k]=min;
			k++;
			gantt[k]=i;
			
			count++;
			ct=i+b[min];
			c[min]=ct;
			i=ct-1;
	
			wt+=ct-a[min]-t[min];
			tat+=ct-a[min];
			b[min]=0;
            
            
        }
        
	}
	for(i=0;i<n;i++)
	{
		tatime[i]=c[i]-a[i];
		wtime[i]=tatime[i]-t[i];
	}
	gantt[0]=0;
	gantt[j+1]=ct;
	
    drawtable(a, t, c, tatime, wtime, n);
	ganttchart(gantt, s, n);
    awt=wt/n; 
    atat=tat/n;
    printf("\nAverage Waiting Time: %lf", awt);
    printf("\nAverage Turnaround Time: %lf", atat);

    return 0;
}
