#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>       //needed for wait;

#define TIME_WAIT 50
int main()
{
    /* We have algorithm to build tree by fork() function
                    pid0 = 0
              /             \        \
        pid1 = 0          pid4 = 0   pid7 = 0
        /     \             /           
    pid2 = 0  pid3 = 0  pid5 = 0
                          /
                      pid6 = 0
    */
	pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;
	pid1 = fork();
	if (pid1 == 0) {  // Process con cua A (Chinh la B)
		printf("Child with id: %d and its Parent id: %d \n", getpid(), getppid());
		pid2 = fork();
		if (pid2 == 0)  // Process con cua B (Chinh la E)
			printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
		else if (pid2 > 0) { 
			sleep(2 * TIME_WAIT);
			pid3 = fork();
			if (pid3 == 0)  // Process con cua B (Chinh la F)
				printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
			else if (pid3 > 0) 
				sleep(2 * TIME_WAIT);
		}
	}
	else if (pid1 > 0) {
		sleep(2 * TIME_WAIT);
		pid4 = fork();
		if (pid4 == 0) { // Process con cua A (Chinh la C)
			printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
			pid5 = fork();
			if (pid5 == 0) {// Process con cua C (Chinh la G)
				printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
				pid6 = fork();
				if (pid6 == 0) //Process con cua G (Chinh la I)
				    printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
				else if (pid6 > 0)
					sleep(2 * TIME_WAIT);
			}
			else if (pid5 > 0) 
				sleep(2 * TIME_WAIT);
			
		}
		else if (pid4 > 0) {
			sleep(TIME_WAIT);
			pid7 = fork();
			if (pid7 == 0) // Process con cua A (Chinh la D)
				printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
			else if (pid7 > 0) 
				sleep(TIME_WAIT);
		}
	}
	return 0;
}
