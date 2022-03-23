/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:58:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/23 17:36:46 by pirichar         ###   ########.fr       */
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
		int i;
		t_ptrs p;

		p.path = path_to_strarr(env);
		p.cmd_with_slash = ft_strjoin("/", cmd);
		p.cmd_split = ft_split(cmd, ' ');
		i = 0;
		while(p.path[i])
		{
			if (search_argv1(p.path[i], p.cmd_split[0]) == true)
			{
				p.final_cmd = split_cmd(p.path[i], p.cmd_with_slash);
				// free (p.cmd_split);
				// free (p.path);
				// free (p.cmd_with_slash);
				//ici comment je fais pour free ma final_cmd ?!
				//Should i create them in main and pass them after ?
				execve(p.final_cmd[0], p.final_cmd, env);
				// free(p.final_cmd);
				exit(1);
			}
			i++;
		}
		fprintf(stderr, "PLR: command not found %s\n", cmd);
		// free(p.path);
		exit(1);
}


int execute(const char *cmd, int in, int *p, int out, char **env) 
{
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
		parse_and_exec_cmd(cmd, env);
	}
	close(in);
	close(pipes[1]);
	*p = pid;
	return (pipes[0]);
}

int	calling_the_execs(int argc, char **argv, char **env, t_files files, int *pids)
{	
	int fd;
	int j;

	fd = execute(argv[2], files.file, &pids[0], 0, env);
	//executing the middle commands
	j = 3;
	while (j < argc - 2) 
	{
		fd = execute(argv[j], fd, &pids[j - 2], 0, env);
		j++;
	}
	//opening the outfile
	files.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (files.outfile == -1)
	{
		fprintf(stderr, "could not open output file\n");
		return (1);
	}
	//executing the last command
	execute(argv[argc - 2], fd, &pids[argc - 2], files.outfile, env);
	return (0);
}

int main(int argc, char** argv, char **env) 
{
	int *pids;
	int status;
	int process_count;
	int i;
	t_files files;

	process_count = argc -3;
	pids = malloc(sizeof(int) * process_count);
	i = 0;
	files.file = open(argv[1], O_RDONLY);
	if (files.file == -1)
	{
		printf("could not open input file\n");
		return (1);
	}
	if (calling_the_execs(argc, argv, env, files, pids) == 1)
		return (1);
	while (i < process_count) 
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	close(files.file);
	free(pids);
}
