#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

/*
	https://www.youtube.com/watch?v=8Q9CPWuRC6o&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=10
	Here I try to :
	1- Create a random number in my main process
	2- Read it in the child;
	3- multiply it ay 4 and write it down in the pipe in the child
	4- Read the final answer in the main process

	When trying to use one pipe i had the problem that the main
	would write and read in the same execution and my
	child was stuck trying to read nothing

	It seems that the simple fix for that is using two pipes

*/

int main(int argc, char **argv)
{
	//p1[0] is to read
	//p1[1] is to wirte
	int p1[2]; 	//child to the parent
	int p2[2];	//parent to child
	int pid;

	if (pipe(p1) == -1)
		return (1);
	if (pipe(p2) == -1)
		return (1);
	pid = fork();
	// printf("PID IS %d\n", pid);
	if (pid == -1)
		return (2);

	if (pid == 0)
	{
		close(p1[0]);
		close(p2[1]);
		//child process
		int x;
		if (read(p2[0], &x, sizeof(x)) == -1)
			return (3);
		printf("Received %d\n", x);
		x *=4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return (4);
		printf("Wrote %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}

	else
	{
		close(p1[1]);
		close(p2[0]);
		//parent process
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return (5);
		// printf("Wrote %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1)
			return (6);
		printf("Result is %d\n", y);
		wait(NULL);
		close(p1[0]);
		close(p2[1]);
	}
	close(p1[0]);
	close(p1[1]);


	return (0);
}