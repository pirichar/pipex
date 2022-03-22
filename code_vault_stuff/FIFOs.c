#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "colors.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
	a fifo is a named pipe
	https://www.youtube.com/watch?v=2hba3etpoJg&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=8&t=7s
*/
int main(int argc, char **argv)
{
	//This was the old way of doing a pipe for now
	// int fd[2];
	// if (pipe(fd) == -1)
	// 	return (1);

	//creating a fifo
	//fist parameter is the name
	//Second parameter is the permission bits
	//0777 is read write for everyone
	//This will create a file and mkfifo return 
	//0 if everything fine or -1 if something bad happened
	if (mkfifo("myfifo1", 0777) == -1)
	{
		//Here I check with errno if the fifo
		//does not exist
		//If so I cant print the error
		//If not its just allready created
		if (errno != EEXIST)
		{
		printf("Could not create fifo file\n");
		return (1);
		}
	}


	return (0);
}