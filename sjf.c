//SJF Preemptive


#include <stdio.h>
#include <stdlib.h>

void ganttchart (int s[], int n)
{
	int i, j;
	printf("\n");
	for(i=0; i<n; i++)
		printf("---");
	printf("\n");
	
	for(i=0; i<n; i++)
	{
		if(s[i]==10)
			printf("|ID");
		if(s[i]!=s[i-1] && s[i]!=10)
			printf("|P%d", s[i]);
		if(s[i]==s[i-1])
			printf("|P%d", s[i]);
		if(i==n-1)
			printf("|");
	}
	printf("\n");

	for(i=0; i<n; i++)
		printf("---");
	printf("\n");
	
	for(i=0;i<n;i++)
	{
		if(s[i]==10 || (s[i]!=s[i-1] && s[i]!=10))
			printf("%d  ", i);
		if(s[i]==s[i-1])
			printf("   ");
		if(i==n-1)
			printf("%d", n);	
		
	}		
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
	int b[10], w[10], a[10], c[10], t[10], s[50], g[50], tatime[10], wtime[10];
	int i, j, min, count = 0, n;
	double wt = 0, tat = 0, ct, awt, atat;

	printf("\nPREEMPTIVE SHORTEST JOB FIRST:");
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time:\n");
    for(i=0; i<n; i++)
    {
      
	scanf("%d %d",&a[i],&b[i]);        
	t[i]=b[i];
    }

	b[9]=9999;

    for(i=0; count!=n; i++)
	{
		min=9;
		for(j=0; j<n; j++)
		{
			if(a[j]<=i && b[j]<=b[min] && b[j]>0)
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
		s[i]=min+1;
		g[i]=i;
		b[min]--;
		if(b[min]==0 && min!=9)
        {
			count++;
			ct=i+1;
			c[min]=ct;
			wt+=ct-a[min]-t[min];
			tat+=ct-a[min];
        }
	}
    ganttchart(s, i);
	for(i=0; i<n; i++)
	{
		tatime[i]=c[i]-a[i];
		wtime[i]=tatime[i]-t[i];
	}
	drawtable(a, t, c, tatime, wtime, n);
	
    awt=wt/n; 
    atat=tat/n;
    printf("\n\nAverage Waiting Time: %lf", awt);
    printf("\nAverage Turnaround Time: %lf", atat);
    
    return 0;
}
