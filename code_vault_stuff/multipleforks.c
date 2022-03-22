#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*
	https://www.youtube.com/watch?v=94URLRsjqMQ&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=5&t=459s
	When you fork multiple times 
	If you put no conditions
	It will fork activ process
	Which means that the second time
	your actually forking
	The child will fork and the main will
	fork again to create 4 process after 
	2 forks which are all linked to the 
	first main look at multipleforks.png

	In our case we have id1 and id2
	How do we figure out which one is which

	(See multipleforks2.png)
	Main process : id1 = x; id2 = z
		Second Fork(z): id1=x; id2=0;
	First fork(x): id1=0; id2=y;
			Second fork(y): id1=0;id2=0;

	If id2 is 0 it means that the process is a child
	We can difference the two parent process by looking 
	at id1; if id1 is a 0 it means you are 
	not at the top parent 

*/

int main(int argc, char **argv)
{
	int id1 = fork();
	int id2 = fork();

	if(id1 == 0)
	{
		if(id2 == 0)
			printf("We are processs y\n");
		else
			printf("We are process x\n");
	}
	else
	{
		if(id2 == 0)
			printf("We are process z\n");
		else
			printf("we are the parent process\n");
	}
	/*wait returns -1 if there is no child process to wait for
	Otherwise it will return the process id of the 
	process you are waiting for 
	It is very usefull when you are working 
	with multiple child process*/
	while(wait(NULL) != -1 || errno != ECHILD)
	{
		printf("waited for a child to finish\n");
	}
	return (0);
}