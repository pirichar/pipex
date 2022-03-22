#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "colors.h"


/*
	Here I fork 2 times for a total of 3 process
	The first fork will have ID1 at 0
	The second fork will have ID2 at 0
	The first fork will gather the second third of the numbers and write it into the pipe
	The second fork will gather the last third then read the pipe add it to its sum and write that into the pipe
	The main process will gather the first 3 numbers read the pipe and add the total and print out the total sum
*/

int main(int argc, char **argv)
{
	int arr[] = {3,3,3, 4,4,4, 5,5,5};
	int start;
	int end;
	int first_third;
	int last_third;
	int last;
	int arr_size;
	int total_sum;
	int sum_from_child;
	int sum;
	//fd[1] == write end of pipe
	//fd[0] == read end of pipe
	int fd[2];
	int id1;
	int id2;

	arr_size = sizeof(arr) / sizeof(int);
	first_third = arr_size / 3;
	last_third = first_third * 2;

	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 != 0)
		id2 = fork();
	//if I am in the main
	if (id1 != 0 && id2 != 0)
	{
		while(wait(NULL) != -1 || errno != ECHILD)
		{
			;
		}
		printf(CYN"This is id1 in main = %d\n", id1);
		printf("This is id2 in main = %d\n"RESET, id2);
		start = 0;
		end = first_third;
	}
	//if I am in the first child
	else if (id1 == 0)
	{
		printf(YEL"This is id1 in first child = %d\n", id1);
		printf("This is id2 in first child = %d\n"RESET, id2);
		start = first_third;
		end = last_third;
	}
	//if my id1 is X (inherited after first fork) and my id2 is 0
	//Therefore I am in the second fork
	else if (id2 == 0)
	{
		printf(RED"This is id1 in second child = %d\n", id1);
		printf("This is id2 in second child = %d\n"RESET, id2);
		start = last_third;
		end = arr_size;
	}
	int i;

	i = start;
	sum = 0;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	//If I am in the first child
	//I write my sum into the pipe
	if (id1 == 0)
	{
		printf(YEL"This is sum of the first child %d\n"RESET, sum);
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (2);
		close(fd[1]);
	}
	else if (id2 == 0)
	{
		printf(RED"This is sum of the second child %d\n"RESET, sum);
		if (read(fd[0],&sum_from_child,sizeof(sum_from_child)) == -1)
			return (3);
		sum = sum_from_child + sum;
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (4);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		printf(CYN"This is sum of main %d\n"RESET, sum);
		if (read(fd[0],&sum_from_child,sizeof(sum_from_child)) == -1)
			return (4);
		sum = sum_from_child + sum;
		close(fd[0]);
		close(fd[1]);
		printf(GRN"THIS IS FINAL SUM = %d\n"RESET, sum);
	}	
}