#include <stdio.h>
#include <unistd.h>
/* 

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