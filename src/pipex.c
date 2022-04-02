/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:58:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/02 13:27:16 by pirichar         ###   ########.fr       */
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

int	execute(const char *cmd, int fd_in, int *p, char **env)
{
	int	pipes[2];
	int	pid;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
		dup2(pipes[1], 1);
		close(pipes[1]);
		parse_and_exec_cmd(cmd, env);
	}
	close(fd_in);
	close(pipes[1]);
	*p = pid;
	return (pipes[0]);
}

void	execute_out(const char *cmd, int fds[2], int *p, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		parse_and_exec_cmd(cmd, env);
	}
	close(fds[0]);
	*p = pid;
}

/* 
	Calling the exec goes through all the commands and run execute on that command
	It will give execute different parameters depending on 
	the command on are working with
	If it is the first command you will pas the infile to execute instead of fd

	argc == 8
	argc - 2 == 6
	process count == 5
	pendant que J (3) est plus petit que 6
	PREMIER PROCESS pid[0]
	j = 2e process = 3 = pids[3 - 2 (1)]
	j = 3e process == 4 = pids[4 -2 (2)]
	j = 4e process == 5 = pids[5 -2 (3)]
	j = 5e process == 6 = I GET OUT OF THE LOOP
	LAST PROCESS = pids[process_count-1 (5) - 1 (4)]
*/

int	calling_the_execs_bonus(int argc, char **argv, char **env, t_files *f)
{	
	int	fd;

	fd = execute(argv[3], f->infile, &f->pids[0], env);
	f->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f->outfile == -1)
	{
		ft_put_str_error("could not open output file\n");
		return (1);
	}
	execute_out(argv[4], (int [2]){fd, f->outfile},
	&f->pids[f->process_count - 1], env);
	return (0);
}

int	calling_the_execs(int argc, char **argv, char **env, t_files *f)
{
	int	fd;
	int	j;

	if (f->here_doc == 0)
	{
		fd = execute(argv[2], f->infile, &f->pids[0], env);
		j = 3;
		while (j < argc - 2)
		{
			fd = execute(argv[j], fd, &f->pids[j - 2], env);
			j++;
		}
		f->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (f->outfile == -1)
		{
			ft_put_str_error("could not open output file\n");
			return (1);
		}
		execute_out(argv[argc - 2], (int [2]){fd, f->outfile},
			&f->pids[f->process_count - 1], env);
	}
	else
		calling_the_execs_bonus(argc, argv, env, f);
	return (0);
}
