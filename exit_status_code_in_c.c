#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/*
	https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12
	https://man7.org/linux/man-pages/man2/wait.2.html
	IN THE CHILD PROCESS;
	IF WE WANT TO KNOW IF THE PROGRAM WAS FOUND
	WE CAN USE THE RETURN OF execve

	There are two types of errors 
	1 - command does not exist
	2 - Command is found and executed but it gives out an error
	The exec commands return an integer, 
	it will return -1 if a problem happened

	IN THE MAIN PROCESS
	If we want to know in the main if the child succeeded
	So we can or cannot say it succeded
	We can youse the wait function
	I use to use the wait function with a null
	In fact the parameter tells us some information
	about what happened with the child process
	It is an int pointer
	To test this use "google.CON" at the line 39 and see what happend

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
		//here we use the fact that execve
		//return -1 if it does not find the command
		//lets say i typed pingr instead of ping
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
		//So here instead of using wait(NULL)
		//We want to use wait(&wstatus)
		//after it finished the execution
		//we have to test if the program
		//actually terminated on its own
		//we have to use MACROS like WIFEXITED
		//For example when you kill a task
		//in the task manager 
		//it would not be considered normal
		//in linux we can send the sigkill signal
		//the wait status is linked to its child process
		//the process its actually waiting for !
		wait(&wstatus);
		//if WIFEXITED returns true the child return normally
		//then we know that the program exited normally
		//status code here is the return value inside the main
		//or the value it exited using the exit code
		//in linux an exite code that is not 0 signify an error
		//There are two tests with wstatus 
		//WIFEXITED test if the process eneded correctly 
		//
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