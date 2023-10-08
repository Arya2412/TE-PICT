/*Code for Program to create processes using fork() and check orphan state in C Programming*/

# include <stdio.h>
int main()
{    
    int pid,p;
    pid=getpid();
    
    printf("Current Process ID is : %d\n\n",pid);

    printf("[ Forking for creating Child Process ... ] \n\n");    
    p=fork(); /* This will Create Child Process and
              Returns Child's PID */
    printf("\n\nFork Value : %d\n\n",p);
    if(p > 0)
    {
         printf("Now in Parent Process\nAfter Forking, Process Control is now with parent Process\n............Seleeping ...\n\n");
        
        sleep(1);
        /* Process Creation Failed ... */
        printf("Now in Parent Process wakes up, Process Control is now with parent Process ...\n\n");
        printf("Current Process ID is : %d\n\n",pid);
        printf("Parent Process is going for completing and exiting\n\n");
        exit(-1);
    }
    else 
    {
        	/* Child Process */
        	
		printf("Now in Child Process is Executing ...\n\n");
		printf("Current child Process ID is : %d\n\n",getpid());
		printf("Current child Parent Process ID is : %d\n\n",getppid());
	        printf("Now Child Process is going for Sleeping ...\n\n");
        	sleep(5);

        	/* 	           Orphan Child's Parent ID is 1                */

	        printf("\nNow Child Process wakes up ...\n\n");
	        printf("Current child Process ID is : %d\n\n",getpid());
		printf("Current child Parent Process ID is : %d\n\n",getppid());
	        printf("\n\nOrphan Child's Parent ID : %d\n\n",getppid());
		exit(0);
     }
	
    return 0;
}


