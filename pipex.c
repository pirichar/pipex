/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:58:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/23 15:55:39 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

//COMMENT JE FREE MES TRUCS SI JE LES EXECS ?!
char **split_cmd(const char *path, const char *cmd)
{
	char **rtn;
	char *cmd_with_path;

	cmd_with_path = ft_strjoin(path, cmd);
	rtn = ft_split(cmd_with_path, ' ');
	free (cmd_with_path);
	return (rtn);
}

void	parse_and_exec_cmd(const char *cmd, char **env)
{
		char **path;
		char *with_slash;
		char **final_cmd;
		char **cmd_split;
		int i;

		path = path_to_strarr(env);
		with_slash = ft_strjoin("/", cmd);
		cmd_split = ft_split(cmd, ' ');
		i = 0;
		while(path[i])
		{
			if (search_argv1(path[i], cmd_split[0]) == true)
			{
				free(cmd_split);
				final_cmd = split_cmd(path[i], with_slash);
				free (path);
				free (with_slash);
				execve(final_cmd[0], final_cmd, env);
				free(final_cmd);
				exit(1);
			}
			i++;
		}
		fprintf(stderr, "PLR: command not found %s\n", cmd);
		free(path);
		exit(1);
}


int execute(const char *cmd, int in, int *p, int out, char **env) 
{
	int pipes[2] = {};
	// printf("THIS IS CMD IN EXECUTE = %s\n", cmd);
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
		parse_and_exec_cmd(cmd, env);
	}
	close(in);
	close(pipes[1]);
	*p = pid;
	return (pipes[0]);
}

int	clean_the_main(int argc, char **argv, char **env, char file, int *pids)
{	
	int fd;
	int j;
	int outfile;

	fd = execute(argv[2], file, &pids[0], 0, env);
	//executing the middle commands
	j = 3;
	while (j < argc - 2) 
	{
		fd = execute(argv[j], fd, &pids[j - 2], 0, env);
		j++;
	}
	//opening the outfile
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile == -1)
	{
		printf("could not open output file\n");
		return (1);
	}
	//executing the last command
	execute(argv[argc - 2], fd, &pids[argc - 2], outfile, env);
	return (0);
}

int main(int argc, char** argv, char **env) 
{
	int *pids;
	int file;
	// int fd;
	// int outfile;
	int status;
	int process_count;
	int i;
	// int j;

	process_count = argc -3;
	pids = malloc(sizeof(int) * process_count);
	i = 0;
	//Opening the in_file which is the argv1
	file = open(argv[1], O_RDONLY);
	if (file == -1)
	{
		printf("could not open input file\n");
		return (1);
	}
	// // -----------I SHOULD SEPERATE ALL THIS PART-----------//
	// //executing the first command 
	// fd = execute(argv[2], file, &pids[0], 0, env);
	// //executing the middle commands
	// j = 3;
	// while (j < argc - 2) 
	// {
	// 	fd = execute(argv[j], fd, &pids[j - 2], 0, env);
	// 	j++;
	// }
	// //opening the outfile
	// outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	// if (outfile == -1)
	// {
	// 	printf("could not open output file\n");
	// 	return (1);
	// }
	// //executing the last command
	// execute(argv[argc - 2], fd, &pids[argc - 2], outfile, env);
	// // -----------I SHOULD SEPERATE ALL THIS PART UNTILL HERE-----------//
	if (clean_the_main(argc, argv, env, file, pids) == 1)
		return (1);
	while (i < process_count) 
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	close(file);
	// close(outfile);
	free(pids);
}
