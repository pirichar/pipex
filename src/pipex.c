/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:58:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/28 09:54:59 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**split_cmd(const char *path, const char *cmd)
{
	char	**rtn;
	char	*cmd_with_path;

	cmd_with_path = ft_strjoin(path, cmd);
	rtn = ft_split(cmd_with_path, ' ');
	free (cmd_with_path);
	return (rtn);
}

void	parse_and_exec_cmd(const char *cmd, char **env)
{
	int			i;
	t_exec_ptrs	p;

	p.path = path_to_strarr(env);
	p.cmd_with_slash = ft_strjoin("/", cmd);
	p.cmd_split = ft_split(cmd, ' ');
	i = 0;
	while (p.path[i])
	{
		if (search_argv1(p.path[i], p.cmd_split[0]) == true)
		{
			p.final_cmd = split_cmd(p.path[i], p.cmd_with_slash);
			execve(p.final_cmd[0], p.final_cmd, env);
			exit(1);
		}
		i++;
	}
	ft_put_str_error("PLR : Command not found\n");
	free (p.path);
	free (p.cmd_split);
	free (p.cmd_with_slash);
	exit(1);
}
/*
	Execute take as input the cmd, the fd it needs to read from
	An array of int for the pids, the fd it needs to write to
	and the variable of environement 

	pipes[0] is to read - Its the output 
	pipes[1] is to write - Its the input
	The execute function works this way :
	1-pipe only if we are not at the last operation
	2-Then it will fork the process
	3-In the child process it will dup2 the ouput of my pipe to stdin 
	it will then close the fd_in passed to the function
	4-Then if we are not at the last process and fd_out == 0
	It will dup2 the input of my pipe to the stdout
	and close the pipe[1]
	5-If we are at the last process it will dup2 into the outfile
	instead of the output of the pipe
	6-Finally i call parse_and_exec_cmd to exec the cmd
	7- In the main I close my fd_in , I close my pipe[1] 
	I write into the adress of the PID array my PID
	8- finally return the output of my pipe that is linked to my child
*/

int	execute(const char *cmd, int fd_in, int *p, int fd_out, char **env)
{
	int	pipes[2];
	int	pid;
	
	if (fd_out == 0)
		pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
		if (fd_out == 0) 
		{
			dup2(pipes[1], 1);
			close(pipes[1]);
		}
		else
		{
			dup2(fd_out, 1);
			close(fd_out);
		}
		parse_and_exec_cmd(cmd, env);
	}
	close(fd_in);
	close(pipes[1]);
	*p = pid;
	return (pipes[0]);
}

/* 
	Calling the exec goes through all the commands and run execute on that command
	It will give execute different parameters depending on 
	the command on are working with
	If it is the first command you will pas the infile to execute instead of fd
*/
int	calling_the_execs(int argc, char **argv, char **env, t_files f)
{	
	int	fd;
	int	j;

	fd = execute(argv[2], f.infile, &f.pids[0], 0, env);
	j = 3;
	while (j < argc - 2) 
	{
		fd = execute(argv[j], fd, &f.pids[j - 2], 0, env);
		j++;
	}
	f.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f.outfile == -1)
	{
		fprintf(stderr, "could not open output file\n");
		return (1);
	}
	//est-ce que je devrais quand meme faire fd = execute et fermer le fd ?!
	execute(argv[argc - 2], fd, &f.pids[argc - 2], f.outfile, env);
	return (0);
}

/*
*/
int main(int argc, char** argv, char **env) 
{
	int status;
	int i;
	t_files f;

	if (argc > 3)
	{
		i = 0;
		f.process_count = argc -3;
		f.pids = malloc(sizeof(int) * f.process_count);
		f.infile = open(argv[1], O_RDONLY);
		if (f.infile == -1)
		{
			ft_put_str_error("Could not open input file\n");
			free (f.pids);
			return (1);
		}
		if (calling_the_execs(argc, argv, env, f) == 1)
			return (1);
		while (i < f.process_count) 
		{
			waitpid(f.pids[i], &status, 0);
			i++;
		}
		close(f.infile);
		free(f.pids);
	}
}
