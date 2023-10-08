#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#define MAX 20

void quick_sort(int a[MAX],int ,int);
int partition(int a[MAX],int ,int);

void merge_sort(int a[MAX],int ,int);
void merge(int a[MAX],int ,int ,int);

int main()
{
pid_t pid;
int i,arr[MAX],arrq[MAX],num,numq;

printf("\nENTER THE NUMBER OF ELEMENTS FOR QUICK SORT : \n");
scanf("%d",&numq);
printf("\nENTER THE ELEMENTS : ");
for(i=0;i<numq;i++)
scanf("%d",&arrq[i]);


pid=fork();
if(pid==0)
{
  printf("\n-------------------------I am in child...%d\n",getpid());
  printf("\n-------------------------My parent's Id is..--1---.%d\n",getppid());
  printf("\n-------------------------Child Sleeping---executing Parent Process\n");
  sleep(5);
  printf("\n-------------------------Child wakes up\n");
  printf("\n-------------------------I am in child...%d\n",getpid());
  printf("\n-------------------------My parent's Id is..--2---.%d\n",getppid());
  quick_sort(arrq,0,numq-1);
  printf("\n-------------------------AFTER PERFORMING THE QUICK SORT : \n");
  for(int i=0;i<numq;i++)
      printf("%d\t",arrq[i]);
printf("\n");
printf("\n-------------------------I (CHILD) COMPLETED MY EXECUTION and exiting.\n");
//system("ps -elf | grep a.out");
}
else
{
sleep(1);
printf("\n I am in Parent..---A---.%d\n",getpid());
merge_sort(arrq,0,numq-1);
printf("\nAFTER PERFORMING THE MERGE SORT : \n");
for(int i=0;i<numq;i++)
  printf("%d\t",arrq[i]);
printf("\n");
//system("ps -elf | grep a.out");
printf("\n-------------------------Parent Exectuing Wait Call for child to complete it process\n");
wait();
printf("\nAfter Wait Call.....CHILD COMPLETED ITS EXECUTION , NOW I (PARENT) AM FREE TO EXIT.\n");
exit(0);
}
return(0);
}

void quick_sort(int a[MAX],int l,int u)
{
 int j;
 if(l<u)
 {
    j=partition(a,l,u);
    quick_sort(a,l,j-1);
    quick_sort(a,j+1,u);
    
 }
}
int partition(int a[MAX],int l,int u)
{
int v,i,j,temp;
v=a[l];
i=l;
j=u+1;
do
{
     do
     i++;
     while(a[i]<v && i<=u);

      do
      j--;
     while(v<a[j]);

     if(i<j)
     {
       temp=a[i];
       a[i]=a[j];
       a[j]=temp;
      }
}while(i<j);

a[l]=a[j];
a[j]=v;
return(j);
}

void merge_sort(int a[MAX],int l,int u)
{
 int mid;
 if(l<u)
 {
    mid=(l+u)/2;
    merge_sort(a,l,mid);
    merge_sort(a,mid+1,u);
    merge(a,l,mid,u);
 }
}

void merge(int a[MAX],int l,int mid,int u)
{  
int c[MAX];
int i,j,k;
i=l;
j=mid+1;
k=0;
while(i<=mid && j<=u)
{ 
  if(a[i]>a[j])
    {
       c[k]=a[i];
       k++;i++;
    }
   else
    {
       c[k]=a[j];
       k++;j++;
    }
 
}
while(i<=mid)
{
  c[k]=a[i];
  k++;i++;
}
while(j<=u)
{
  c[k]=a[j];
  k++;j++;
}
for(i=l,j=0;i<=u;i++,j++)
a[i]=c[j];
}
