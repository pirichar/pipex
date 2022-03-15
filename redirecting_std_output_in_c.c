#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
	https://www.youtube.com/watch?v=5fnVr-zH-SE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=14	https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12
	int this I add an int file which I send open to
	in order to redirect the output of a process

	SO YOU DONT WANT TO USE THIS BUT IT EXISTS EH !
	You can use dup(file) to duplicate the fd
	It will return another file descriptor
	which will point to the same thing as the first one
	you could use on or another for read or write 

	OR

	You can use dup2(file, 1)
	This function takes 2 parametes
	The first is fd we actually want to clone
	The second one is the value we one the new FD to have
	so if we use dup2(file, 1) instead of creating a new value
	its gonna take a look at fd1 and close this stream (stdout)
	then its gonna open it again to our ping result
	This way we finally duplicate the new created FD into the stdout
*/

int main(int argc, char **argv, char **envp)
{
	int pid;
	int err;
	int wstatus;
	int status_code;
	int file;
	int file2;
	char *vec[] = {"/bin/ping", "-c", "3", "google.com", NULL};
	

	pid = fork();
	if (pid == -1)
		return (1);

	//Child process
	if(pid == 0) 
	{
		//here I use open to give the fd of the file to the in
		// Doing so I create a new FD which I will use later on
		file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (2);
		//here I use dup2 to duplicate the newly created FD (lets say 3)
		//into the stdout this way when you use write or printf or anything
		//that would use the stdout it will go to the file instead
		//this work because before even the first line of main
		//stdout is set to 1 in linux (stdin = 0 and error are 2)
		//Finally we could change the one for STDOUT_FILENO which
		//is a constant in linux and will give 1 as well
		printf("The fd to ping_result.txt : %d\n", file);
		file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n", file2);
		close(file);
		//here we use the fact that execve
		//return -1 if it does not find the command
		//lets say i typed pingr instead of ping
		err = execve("/bin/ping", vec, envp);
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (2);
		}
	}
	//parent process
	else
	{	
		//So here instead of using wait(NULL)
		//We want to use wait(&wstatus)
		//after it finished the execution
		//we have to test if the program
		//actually terminated on its own
		//we have to use MACROS like WIFEXITED
		//For example when you kill a task
		//in the task manager 
		//it would not be considered normal
		//in linux we can send the sigkill signal
		//the wait status is linked to its child process
		//the process its actually waiting for !
		wait(&wstatus);
		//if WIFEXITED returns true the child return normally
		//then we know that the program exited normally
		//status code here is the return value inside the main
		//or the value it exited using the exit code
		//in linux an exite code that is not 0 signify an error
		//There are two tests with wstatus 
		//WIFEXITED test if the process eneded correctly 
		//
		if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			//if status code is 0 we know that we have executed our program
			if (status_code == 0)
						printf("SUCCES !!!!\n");
			else
				printf("Failure with status code %d\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}