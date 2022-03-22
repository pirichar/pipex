#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include "colors.h"

/*
	https://www.youtube.com/watch?v=kCGaRdArSnA
	waitpid will wait for a specific child process to finish
*/
int main (int argc, char **argv)
{
	int pid1;
	int pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error creating process");
		return (1);
	}
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n",getpid());
		return (0);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error creating process");
		return (2);
	}
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution (%d)\n",getpid());
		return (0);
	}
	
	// int pid1_res = wait(NULL);
	// printf("Waited for %d\n", pid1_res);
	// int pid2_res = wait(NULL);
	// printf("Waited for %d\n", pid2_res);
	// WNOHANG means its not gonna wait for the process to finish
	// its gonna check if its finish and if it didnt
	// at the time of calling waitpid its gonna return straight ahead
	// and save the status of NULL 
	// we could use 0 to make it wait normally instead of WNOHANG
	int pid1_res = waitpid(pid1, NULL, WNOHANG);
	printf("Waited for %d\n", pid1_res);
	int pid2_res = waitpid(pid2, NULL, WNOHANG);
	printf("Waited for %d\n", pid2_res);
	return (0);
}