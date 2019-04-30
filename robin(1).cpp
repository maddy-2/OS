//Round Robin

#include<iostream>
using namespace std;

void gantt(int rq[],int rqt[],int l)
{
    int i,j;
    if(rqt[0]>0)
    {
        cout<<"---";
    }
   for(i=0;i<3*rqt[l];i++)
   {
     cout<<"-";
   }
   cout<<"\n";
   if(rqt[0]>0)
    {
        cout<<"NO ";
    }
   for(i=0;i<l;i++)
   {
    cout<<"|P"<<rq[i]+1;
    for(j=0;j<3*(rqt[i+1]-rqt[i])-3;j++)
    {
       cout<<" ";
    }
   }
   cout<<"|";
   cout<<"\n";
    if(rqt[0]>0)
    {
        cout<<"---";
    }

    for(i=0;i<rqt[l];i++)
   {
     cout<<"---";
   }
   cout<<"\n";
    if(rqt[0]>0)
    {
        cout<<"0  ";
    }
    for(i=0;i<l;i++)
   {
       cout<<rqt[i];
     if(rqt[i]>=10)
     {
       for(j=0;j<3*(rqt[i+1]-rqt[i])-2;j++)
    {
       cout<<" ";
    }
     }
     else
     {
         for(j=0;j<3*(rqt[i+1]-rqt[i])-1;j++)
    {
       cout<<" ";
    }
     }
   }
   cout<<rqt[l];
}

int main()
{
int n;
cout<<"Enter no. of Process you want to enter : ";
cin>>n;
int a[n],b[n],b1[n],c[n],tat[n],w[n],rq[50],f=0,l=0,i,tq,t1=0,t2=0,j,nq[n],m,p,rqt[50];
cout<<"Enter time Quantum(TimePeriod) : ";
cin>>tq;
cout<<"Enter arrival time and burst time for processors:\n";
for(i=0;i<n;i++)
{
cin>>a[i];
cin>>b[i];
b1[i]=b[i];
}

int id=0;
for(i=0;i<n;i++)
{

      if(a[i]<a[id])
       {
        id=i;
        }
       else if(a[i]==a[id])
       {
        if(b[i]<b[id])
         {
        id=i;
          }
      }
}
rq[0]=id;
f=0;l=1;
if(t1!=a[id])
  t1=a[id];
  t2=t1;
rqt[0]=t1;
while(f!=l)
{
    m=0;
  if(b1[rq[f]]>tq)
    {
     t2=t1;
      t1=t1+tq;
      rqt[f+1]=t1;
     b1[rq[f]]=b1[rq[f]]-tq;
     m=1;
     }
  else
     {
      t2=t1;
	t1=t1+b1[rq[f]];
	     rqt[f+1]=t1;
        b1[rq[f]]=0;
       c[rq[f]]=t1;
     }

 int k=0;
for(i=0;i<n;i++)
 {
   if(a[i]>t2 && a[i]<=t1)
      {
        nq[k]=i;
         k++;
      }
}

for(i=0;i<k;i++)
 {
   for(j=0;j<k;j++)
    {
     if(a[nq[i]]<a[nq[j]])
      {
            p=nq[i];
            nq[i]=nq[j];
               nq[j]=p;
      }
     else if(a[nq[i]]==a[nq[j]])
     {
      if(b[nq[i]]<b[nq[j]])
      {
        int p=nq[i];
            nq[i]=nq[j];
               nq[j]=p;
      }
     }
    }
}


     for(i=0;i<k;i++)
        {
          rq[l]=nq[i];
            l++;
        }


      if(m==1)
        {
         rq[l]=rq[f];
            l++;
         }
       f++;

}
float awt=0,atat=0;
  cout<<"\n Process"<<"  "<<"Arival  "<<"Burst     "<<"Complition    "<<"Turn Around     "<<"Waiting";
  cout<<"\n        "<<"  "<<"Time    "<<"Time      "<<"Time          "<<"Time            "<<"Time";

 for(i=0;i<n;i++)
 {
     tat[i]=c[i]-a[i];
     w[i]=tat[i]-b[i];
     awt+=w[i];
     atat+=tat[i];
   cout<<"\n P"<<i+1<<"          "<<a[i]<<"        "<<b[i]<<"       \t "<<c[i]<<"      \t"<<tat[i]<<" \t    "<<w[i];
 }
 cout<<"\n\n Avg TAT="<<atat/n;
 cout<<"\n Avg WT="<<awt/n;
 cout<<"\n";

   gantt(rq,rqt,l);

}
