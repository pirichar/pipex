#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
	https://www.youtube.com/watch?v=OVFEWSP7n8c
	Exec family function are standard in linux
	https://linux.die.net/man/3/execl
*/

int main(int argc, char **argv, char **envp)
{
	// ***With EXECL***
	//L stand for list of arguments
	// execl("/sbin/ping", "/sbin/ping" ,"google.com", NULL);
	
	//with EXECLP
	//Here you don't even have to specify the path
	//you just use the command
	// execlp("ping","ping", "google.com", NULL);
	
	// ***with EXECV***
	// V Stand for Vector
	// u need to put everything into a vector
	// char *vec[100];
	
	// vec[0] = "/sbin/ping";
	// vec[1] = "google.com";
	// vec[2] = NULL;
	// execv("/sbin/ping",vec);

	// ***with EXECP***
	// V Stand for Vector
	// P stand for file instead of path
	//u need to put everything into a vector
	// char *vec[100];
	
	// vec[0] = "ping";
	// vec[1] = "google.com";
	// vec[2] = NULL;
	// execvp("ping",vec);

	// ***with EXECVE***
	// V Stand for Vector
	// u need to put everything into a vector
	// E stend for ENVIRONMENT
	char *vec[100];
	char *env[] = {"TEST=environment variable", NULL};
	
	vec[0] = "/sbin/ping";
	vec[1] = "google.com";
	vec[2] = NULL;
	execve("/sbin/ping",vec, env);

	//we can use errno to know why a program is not working
	//in this case here if i use lets say /sbin/ping2 instead of ping
	//as my path I would have the errno of 2
	// 2 which is ENOENT No such file or directory.
	int err = errno;

	printf("This is errno = %d\n", err);
	printf("Ping finished executing\n");
	return (0);
}
