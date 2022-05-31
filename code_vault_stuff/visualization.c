#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


/* 
	https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
	When you use fork; you copy all the data to the child process
	The child process will then gives its ID to the main ( 4300 in this case)
	The child process will take the ID 0
	So we refer to then main with 4300 which is the ID of tthe child process
	And we refer to the child as 0 
	All the memory is getting copied value by value
	Variable by variable from one process to an other
	when you do fork
	They are the same in both processes when you do fork
	They both have difference spaces in memory so when
	You modify one; you don't actually modify the other
	Both processes execute the same code 
	The difference will be in the ID of the processes
	You will play with that ID to inhibit some stuff from one or another

	*/

int main (int argc, char **argv)
{
	//main id = 4300
	//child process id = 0
	int id = fork();
	int n;
	int i;

	//if I am in the child process
	//my n = 1
	if (id == 0)
	{
		n = 1;
	}
	
	//If i am in the main process 
	//My n = 6
	else
	{
		n = 6;
	}
	//If I am not in the child process
	//I will call wait
	//Wait will wait untill A child process is finish
	//Then it will continue the process in which it has been called

	if (id != 0)
		wait(NULL);

	//Here I will go through this loop with my
	//Child process first since the main is waiting
	//For A child process to finish
	//I would then go trought it with the main
	//Once the child is done with the whole process
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}

	//If I am in the main I will print out the a new line
	//At the very end of all my processing
	if (id != 0)
		printf("\n");

	return (0);
}