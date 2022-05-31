#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*
	https://www.youtube.com/watch?v=6u_iPGVkfZ4&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=7
*/

int main(int argc, char **argv)
{
	int arr[] = {1, 2, 3, 4 ,1 ,2, 7};
	int arrSize = sizeof(arr) / sizeof(int);
	int start;
	int end;
	//fd[1] == write end of pipe
	//fd[0] == read end of pipe
	int	fd[2];
	if (pipe(fd) == -1)
		return (1);

	int id = fork();
	if (id == -1)
		return (2);

	//if I am in the child process
	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}

	int sum = 0;
	int i;
	i = start;
	while(i < end)
	{
		sum+= arr[i];
		i++;
	}
	printf("Calculated partial sum : %d\n", sum);

	//if I am in the child process
	//I will write the sum into the write
	//part of the pipe at the size of sum
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (3);
		close(fd[1]);
	}
	//In the main process
	//First of all you have to wait for
	//your child to finish
	//Then you read into the pipe what
	//you wrote down in the child
	//You then place it in an int
	//and add it into the sum 
	//we always protect read and write so 
	//we know what happends when using alot of processes
	
	else
	{
		int sumFromChild;
		close(fd[1]);
		if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
			return (4);
		close(fd[0]);

		int totalSum = sum + sumFromChild;
		printf("Total sum is %d\n", totalSum);
		wait(NULL);
	}
}