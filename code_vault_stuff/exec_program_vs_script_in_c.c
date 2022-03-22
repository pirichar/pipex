#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/*
	https://www.youtube.com/watch?v=HAN_kCJyrOc&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=15
	Exec does not execute bash commands; it execute and executable 
	You can't pass anything like a pipe (|) or something like that to exec
*/

int main(int argc, char **argv, char **envp)
{
	int pid;
	int err;
	int wstatus;
	int status_code;
	char *vec[] = {"/sbin/ping", "-c", "3", "google.com", NULL};
	

	pid = fork();
	if (pid == -1)
		return (1);

	//Child process
	if(pid == 0) 
	{
		
		err = execve("/sbin/ping", vec, envp);
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (2);
		}
	}
	//parent process
	else
	{	

		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			//if status code is 0 we know that we have executed our program
			if (status_code == 0)
						printf("SUCCES !!!!\n");
			else
				printf("Failure with status code %d\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}