#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


/* 
	https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
	I want to print numbers from 1 to 10 
	I want the five first to be printed by the child
	and the 5 last by the main

	To garantee that the child process will go first
	we can use wait
	Wait says stop the execution untill the child process is done
	Wait for a child process to print its numbers
	then print your numbers
	https://man7.org/linux/man-pages/man2/wait.2.html
*/

int main (int argc, char **argv)
{
	int id = fork();
	int n;

	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	if (id !=0)
		wait(NULL);
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return (0);
}