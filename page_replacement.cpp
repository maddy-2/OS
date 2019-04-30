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
		cout<<"|"<<a[m]<<"|"<<endl;
		//cout<<"---"<<endl;
	}
}

int main()
{
	int i,j=0,n,c=0;
	char a[10]={0};
	string str;
	cout<<"enter the reference string"<<endl;
	cin>>str;
	cout<<"enter the number of frames"<<endl;
	cin>>n;
	
	for(i=0;str[i]!='\0';i++)
	{
		if(check(str[i],n,a)==1)
		{
			if(a[c%n]=='0')
			{
				a[c%n]=str[i];
				j++;
				c++;
				cout<<"page-"<<j<<endl;
				print(a,n);
				
			}
			else if(a[c%n]!=str[i])
			{
				a[c%n]=str[i];
				j++;
				c++;
				cout<<"page-"<<j<<endl;
				print(a,n);
				
			}
		}
	}
	cout<<"the page fault= "<<j<<endl;

			
}	
