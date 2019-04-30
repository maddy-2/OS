//Page algorithm LRU


#include <iostream>
using namespace std;
#include <string.h>
int check(char c,int n,char a[])
{
	for(int k=0;k<n;k++)
	{
		if(c==a[k])
			return 0;
	}
	return 1;
}
void print(char a[],int n)
{
	for(int m=0;m<n;m++)
	{
		
		cout<<"---"<<endl;
		if(a[m]!='9')
			cout<<"|"<<a[m]<<"|"<<endl;
		else
			cout<<"|"<<" "<<"|"<<endl;
		
		//cout<<"---"<<endl;
		
		
	}
}
int search(int n,int r[])
{
	int k,l=0,j;
	for(k=0;k<n;k++)
	{
		if(l<r[k])
		{
			l=r[k];
			j=k;
		}
	}
	return j;
}
			
		

int main()
{
	string str;
	int i,j=0,n,c=0,r[10],m;
	char a[10];
	
	
	cout<<"enter the reference string"<<endl;
	cin>>str;
	cout<<"enter the number of frames"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
	{
		a[i]='9';
		r[i]=0;
	}
	

	for(i=0;str[i]!='\0';i++)
	{
		if(check(str[i],n,a)==1)
		{
			if(a[c%n]=='9')
			{
				a[c%n]=str[i];
				r[c%n]++;
				j++;
				c++;
				cout<<"page-"<<j<<endl;
				print(a,n);
				
			}
			else
			{
				int f=search(n,r);
				a[f]=str[i];
				for(m=0;m<n;m++)
				{
					if(m!=f)
						r[m]++;
					else
					{
						r[m]=0;
					}
				}
				j++;
				cout<<"page-"<<j<<endl;
				print(a,n);
			}
		}
		else
		{
			for(m=0;m<n;m++)
			{
				if(str[i]!=a[m])
					r[m]++;
				else
					r[m]=0;
					
			}
		}
	}
	cout<<"the page fault= "<<j<<endl;

}	

