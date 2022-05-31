#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

/*
	https://www.youtube.com/watch?v=3MZjaZxZYrE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=17
*/

int main(int argc, char **argv)
{
	int	pid;
	int	t;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		while(1)
		{
			printf("Some output\n");
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		do 
		{
			printf("Time in seconds for execution : ");
			scanf("%d", &t);
			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGSTOP);
			}
		}
		while (t > 0);

		//to be sure that we terminate the process
		kill(pid, SIGKILL);
		wait(NULL);
	}

	return (0);
}