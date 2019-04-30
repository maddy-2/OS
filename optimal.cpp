//Page algorithm Optimal

#include <iostream>
#include <string.h>
using namespace std;
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
int search(string str,int m,int n,char a[])
{
	int k,j=0,flag=0,l=0;
	char r[n];
	for(int i=0;i<n;i++)
		r[i]='9';
	while(j<n)
	{
		for(k=m+1;(str[k]!='\0');k++)
		{
		
			if(str[k]==a[j])
			{
				r[j]=k;
				break;
			}
		}
		j++;	
	}
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
	int i,j=0,n,c=0;
	char a[10];
	
	
	cout<<"enter the reference string"<<endl;
	cin>>str;
	cout<<"enter the number of frames"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
		a[i]='9';
	

	for(i=0;str[i]!='\0';i++)
	{
		if(check(str[i],n,a)==1)
		{
			if(a[c%n]=='9')
			{
				a[c%n]=str[i];
				j++;
				c++;
				cout<<"page-"<<j<<endl;
				print(a,n);
				
			}
			else
			{
				int f=search(str,i,n,a);
				a[f]=str[i];
				j++;
				cout<<"page-"<<j<<endl;
				print(a,n);
			}
		}
	}
	cout<<"the page fault= "<<j<<endl;

}	
	
