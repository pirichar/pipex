#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char **argv, char **envp)
{
	int pid;
	char *vec[] = {"/sbin/ping", "-c", "3", "google.com", NULL};
	

	pid = fork();
	if (pid == -1)
		return (1);

	//Child process
	if(pid == 0) 
		execve("/sbin/ping", vec, envp);
	//parent process
	else
	{	
		wait(NULL);
		printf("SUCCES !!!!\n");
		printf("Some post processing goes here!\n");
	}
}