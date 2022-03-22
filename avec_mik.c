#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
	example of a command : ./a.out file1 cat wc file2   
	fun one to do is to compare :
		./a.out file1 ls cat file2
		<file1 ls | cat >file2
	HEY don't forget that you write in 1 and read in 0 
	like this  ---->  1<====THIS IS A PIPE====>0 ---->
*/

/*
	The execute function takes as command:
	1- the function you want to exec
	2- The in fd which is used to dup2 to the input to the stdin
	3- The third is a pointer to a process array with all of the PIDS ? WHY 5 ????
	4- The third is the out, its not the best way to do because we only use it for the last one
		but it was easier this way then managing all the PID in another way
		we use it at the end to dup2 the stdout into the outputfile
	5- The function return the fd of the output of the pipe pipe[0] which is use again as the 
		second parameter
*/
int execute(const char* cmd, int in, int* p, int out) {
	int pipes[2] = {};

	if (out == 0)
		pipe(pipes);
	int pid = fork();
	if (pid == 0) 
	{
		dup2(in, 0);
		close(in);
		if (out == 0) 
		{
			dup2(pipes[1], 1);
			close(pipes[1]);
		}
		else
		{
			dup2(out, 1);
			close(out);
		}
		// ici au lieu d'exec je devrais  utiliser la fonction que j'ai créer
		// pour valider si la fonction existe et est valable
		// si il n'existe pas j'envoi un message d'erreur
		// après je l'exec avec le path que j'ai trouvé
		// ne pas prendre pour acquis que si je le trouve exve va réeussir d'ou le but d'utilsier
		// exit -1 a la fin
		execlp(cmd, cmd, NULL);
		exit(1);
	}
	// ici je ferme l'entrée du pipe et je retourne la sortie du pipe
	// qui va servir pour ma prochaine fonction
	close(in);
	close(pipes[1]);
	*p = pid;
	return (pipes[0]);
}

int main(int argc, char** argv) 
{
	//malloc argc * sizeof(int) idéalement
	int pids[1024];
	int file;
	int fd;
	int outfile;
	int status;

	//------FROM HERE ITS ALL IN MY CHLD PROCESS I DO NOTHING OTHERWISE-----//
	
	// 						FOR THE FIRST EXEC 
	// we firstly open the first fd and put it into file
	// we then pass file to execute, with the command in the argv[2]
	// execute receives as well all the pids
	file = open(argv[1], O_RDONLY); //protect your open you dumb fuck
		if (file == -1)
		{
			printf("could not open input file\n");
						return (1);
		}
	fd = execute(argv[2], file, &pids[0], 0);
	//						FOR EVERY EXEC IN THE MIDDLE
	//I start from 3 since my argv[0] is program , argv[1] is the file
	//and argv[2] is my first program I hard coded before
	//I will loop t'il i'm dne with all my arguments but the last (argc - 1)
	for (int i = 3; i < argc - 2; ++i) 
	{
		fd = execute(argv[i], fd, &pids[i - 2], 0);
	}
	//						FOR THE LAST EXEC
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	execute(argv[argc - 2], fd, &pids[argc - 2], outfile);

	//------FROM HERE WE ARE IN THE MAIN PROCESS-----//
	//Here I mostly just wait t'ill all of my PID ARE DONE
	for (int i = 0; i < 4; ++i) 
	{
		waitpid(pids[i], &status, 0);
	}
	close(file);
	close(outfile);
	printf("Done with the operation\n");
}
