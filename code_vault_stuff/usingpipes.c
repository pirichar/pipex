#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*
	https://www.youtube.com/watch?v=Mqb2dVRe0uo&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=6
	In this program we use pipe
	Pipe act as a communication channel between 2 things
	Pipe works with 2 fd 0 to read and 1 to write
	It will return -1 if any error
	
	So basically I fork
	Then I ask my child process to get a number
	Then I write into my pipe in this child process
	I then retrieve the info in the read portion
	of the pipe with my main process

*/

int main(int argc, char **argv)
{
	int	fd[2];
	//fd[0] - read
	//fd[1] - write
	if (pipe(fd) == -1)
	{
		printf("An error occured with opening the pipe\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("An error occured with fork\n");
		return (4);
	}
	//if i am the child 
	//I want to ask the user for an input and writ it in the 
	//write part of the pipe
	if (id == 0)
	{
		//its standard procedure to close
		//one of the end of the pipe
		//when using the pipe
		//here i don't read i write
		close(fd[0]);
		int x;
		printf("Input a number : ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1 )
		{
			printf("An error occured with writing to the pipe\n");
			return (2);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1 )
		{
			printf("An error occured with reading from the pipe\n");
			return (3);
		}
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	
}