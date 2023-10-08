#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#define MAX 20

int pid[MAX], arrivalT[MAX], burstT[MAX], waitingT[MAX], turnAroundT[MAX];

void nonPreemptive(int n)
{
	int runT[n];
	int i, complete = 0, time = 0, mini = INT_MAX, shortest;
	bool check = false;
	
	for(i = 0 ; i < n; i++)
		runT[i] = burstT[i];
	
	while(complete != n)
	{
		for(i = 0; i < n; i++)
		{
			if(arrivalT[i] <= time && runT[i] < mini && runT[i] > 0)
			{	
				mini = runT[i];
				shortest = i;
				check = true;
			}
		}
		
		if(!check)
		{
			time++;
			continue;
		}
		
		runT[shortest] -= burstT[shortest];
		mini = INT_MAX;
		
		time += burstT[shortest];
		
		if(runT[shortest] == 0)
		{
			complete++;
			check = false;
			
			waitingT[shortest] = time - burstT[shortest] - arrivalT[shortest];
			
			if(waitingT[shortest] < 0)
				waitingT[shortest] = 0;
		}	
	}
}

void preemptive(int n)
{
	int runT[n], temp, pos;
	int i, shortest, mini = INT_MAX, time = 0, complete = 0;
	bool check = false;
	
	for(i = 0; i < n; i++)
		runT[i] = burstT[i];
		
	while(complete != n)
	{
		for(i = 0; i < n; i++)
		{
			if(arrivalT[i] <= time && runT[i] < mini && runT[i] > 0)
			{	
				mini = runT[i];
				shortest = i;
				check = true;
			}
		}
		
		if(!check)
		{
			time++;
			continue;
		}
		
		runT[shortest]--;
		
		mini = runT[shortest];
		if(mini == 0)
			mini = INT_MAX;
			
		time++;
			
		if(runT[shortest] == 0)
		{
			complete++;
			check = false;
			
			waitingT[shortest] = time - burstT[shortest] - arrivalT[shortest];
			
			if(waitingT[shortest] < 0)
				waitingT[shortest] = 0;
		}
	}
}

void avgTime(int n)
{
	int i, j, total_wt = 0, total_tat = 0;
	float avg_wt = 0, avg_tat = 0;

	printf("\n\nProcessId\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\n\n");
	for(i = 0; i < n; i++)
	{
		total_wt += waitingT[i];
		turnAroundT[i] = burstT[i] + waitingT[i];
		total_tat += turnAroundT[i];
		
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arrivalT[i], burstT[i], waitingT[i], turnAroundT[i]);
	}
	
	avg_wt = (float) total_wt/n;
	avg_tat = (float) total_tat/n;
	
	printf("\nAverage Waiting Time is : %f\n\n", avg_wt);
	printf("\nAverage Turn Around Time is : %f\n\n", avg_tat);
}

int main()
{		
	int i, j, n, choice;
	
	printf("\nEnter no of processes : ");
	scanf("%d",&n);
	
	printf("\nEnter Arrival Time for Process : \n");
	
	//input arrival time
	for(i = 0; i < n; i++)
	{
		printf("P%d = ", i+1);
		scanf("%d", &arrivalT[i]);
		pid[i] = i+1;
	}
	
	printf("\nEnter Burst Time for Process : \n");
	
	//input burst time
	for(i = 0; i < n; i++)
	{
		printf("P%d = ", i+1);
		scanf("%d", &burstT[i]);
		
	}
	while(1)
	{
		printf("\n---------Menu---------\n");
		printf("\n1.Preemptive SJF\n");
		printf("2.Non-Preemptive SJF\n");
		printf("3.Exit\n");
		
		printf("\nChoose type of Process : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1: 
				preemptive(n);
				avgTime(n);
				break;
			case 2:
				nonPreemptive(n);
				avgTime(n);
				break;
			case 3:
				exit(0);
		}
	}
}



