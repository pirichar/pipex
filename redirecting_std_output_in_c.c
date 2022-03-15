#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
	https://www.youtube.com/watch?v=5fnVr-zH-SE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=14	https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12
	int this I add an int file which I send open to
*/

int main(int argc, char **argv, char **envp)
{
	int pid;
	int err;
	int wstatus;
	int status_code;
	int file;
	char *vec[] = {"/sbin/ping", "-c", "3", "google.com", NULL};
	

	pid = fork();
	if (pid == -1)
		return (1);

	//Child process
	if(pid == 0) 
	{
		//here I use open to give the fd of the file to the in
		file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (2);

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