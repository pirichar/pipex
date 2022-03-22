#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
	https://www.youtube.com/watch?v=PZrQ4eGm-hM&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=4
	every single process get an ID
	include "sys/wait.h" and use getpid to get the pid
	the wait output the process ID you are waiting for 

	getpid will get the procecuss id for the current process that we are in
	It will retun an int and deosnt take any parameters 

	getppid will get the procecuss parent id

	When you use fork in a function
	you want to make sure that the main function wait for the 
	other function to finish before it finishes

	wait returns -1 if there is no child process to wait for
	Otherwise it will return the process id of the 
	process you are waiting for 
	It is very usefull when you are working 
	with multiple child process

	**You should call wait at the end of a program
		if you use fork**
*/

int main(int argc, char **argv)
{
	int id = fork();
	//here i can play on the fact that the child
	//id will always be 0 
	if (id == 0)
	{
		sleep(1);
	}
	if (id != 0)
	{
	printf("MAIN ID %d, Parent ID %d\n", 
		getpid(), getppid());
	}
	else
	{
		printf("CHILD ID %d, Parent ID %d\n", 
			getpid(), getppid());
	}
	
	/*
	Using int res = wait is the same
	as
	if (id != 0)
	{
		wait(NULL);
	}
	When you use it alone it implies you
	are the main process and not the child
	*/
	int res = wait(NULL);
	if (res == -1)
		printf("No children to wait\n");
	else
		printf("%d finished execution\n", res);
	return (0);
}