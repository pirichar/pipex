#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

/*
	https://www.youtube.com/watch?v=5We_HtLlAbs&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=16
	unlike a pipe that could send an array 
	a signal is only a notification an integer 
	that tell the process what it should do 
*/

int main(int argc, char **argv)
{
	//to start up im gonna fork
	int pid;

	pid = fork();
	if (pid == -1)
		return (1);
	//child process
	if (pid == 0)
	{
		//here i just do an infinite loop
		//and print some text 20 times a second
		while(1)
		{
			printf("This is a sentence !\n");
			usleep(50000);
		}
	}
	//in the main process
	else
	{
		//kill will send a signal to the child
		//we will use the signal to terminate it
		//we give kill the pid and the signal we want to execute
		sleep(1);
		kill(pid,SIGKILL);
		wait(NULL);
	}
	return (0);
}