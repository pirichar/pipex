#include <stdio.h>
#include <unistd.h>
/* 
	https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=1
	When you fork, you are gonna create a child process
	this process will run in parallel
	everything after the fork is command be executed twice
	fork will return an integer
	The child process will always be identified as 0
	Every process has a process ID
*/

int main ()
{

	int id = fork();
	if (id != 0)
		fork();

	printf("Hello world\n");
	// int id = fork();
	// if (id == 0)
	// {
	// 	printf("hello from child process \n");
	// }
	// else
	// {
	// 	printf("Hello from the main process\n");
	// }
	return (0);
}