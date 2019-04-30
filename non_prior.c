//Priority Non-Preemptive

#include <stdio.h>
#include <stdlib.h>

void ganttchart(int s[], int n, int l)
{
	int i, j;
	for(i=0; i<=n; i++)
		printf("---");
	printf("\n");
	for(i=0; i<n; i++)
	{
		if(s[i]!=0)
		{
			if(s[i]==10)
				printf("|ID");
			if(s[i]!=s[i-1] && s[i]!=10)
				printf("|P%d", s[i]);
			if(s[i]==s[i-1])
				printf("   ");
		}
		else
			printf("   ");
		if(i==n-1)
			printf("|");
	}
	printf("\n");
	for(i=0; i<=n; i++)
		printf("---");
	printf("\n");
	for(i=0;i<n;i++)
	{
		if(s[i]==10 || (s[i]>0 && s[i]<=l))
			printf("%d  ", i);
		if(s[i]==0)
			printf("   ");
		if(i==n-1)
			printf("%d", n);
	}	
}

void drawtable (int a[], int b[], int pr[], int c[], int tt[], int w[], int p)
{
    int i, j;
    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("|    Programs   | Arrival Time  |  Burst Time   |   Priority    |Completion Time|Turnaround Time| Waiting Time  |");
    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    for (i=1; i<=p; i++)
    {
        printf("|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", i, a[i-1], b[i-1], pr[i-1], c[i-1], tt[i-1], w[i-1]);
       
    }  
    printf("-----------------------------------------------------------------------------------------------------------------\n");
} 

int main()
{
	int b[10], w[10], a[10], c[10], t[10], p[10], wtime[10], tatime[10], s[50]={0};
	int i, largest, count = 0, time, n;
	double wt = 0, tat = 0, ct, awt, atat;

    printf("\nNON-PREEMPTIVE PRIORITY SCHEDULING:");
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival , burst and priority:\n");
    for(i = 0; i < n; i++)
    {
      
	scanf("%d %d %d",&a[i],&b[i],&p[i]);
        t[i]=b[i];
		w[i]=b[i];
    }

	p[9]=0;

	for(time=0; count!=n; time++)
	{
		largest=9;
		for(i=0; i<n; i++)
		{
			if (a[i]<=time && p[i]>p[largest] && b[i]>0)
			{
				if(p[i]==p[largest])
				{
					if(a[i]<a[largest])
						largest=i;
				}
				else
					largest=i;
			}
		}
		
		if (largest!=9)
        {
            count++;
            ct=time+b[largest];
		    c[largest]=ct;
			s[time]=largest+1;
		    time=ct-1;
		  
            wt+=ct-a[largest]-t[largest];
            tat+=ct-a[largest];
		    b[largest]=0;
        }
	}
	for (i=0; i<n; i++)
	{
		tatime[i]=c[i]-a[i];
		wtime[i]=tatime[i]-t[i];
	}

    drawtable(a, t, p, c, tatime, wtime, n);
    ganttchart(s, time, n);

	awt=wt/n; 
    atat=tat/n;
    printf("\n\nAverage Waiting Time: %lf", awt);
    printf("\nAverage Turnaround Time: %lf", atat);
    
    return 0;
}
