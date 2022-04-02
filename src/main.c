/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:04:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/02 14:08:41 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_process(int argc, char **argv, t_files *f)
{
	if (f->here_doc == 0)
		f->process_count = (argc - 3);
	else
		f->process_count = (argc - 4);
	f->pids = malloc(sizeof(int) * f->process_count);
	if (f->here_doc == 0)
	{
		f->infile = open(argv[1], O_RDONLY);
		if (f->infile == -1)
		{
			ft_put_str_error("Could not open input file\n");
			free (f->pids);
			return (1);
		}
	}
	return (0);
}

void	wait_for_pids(t_files *f)
{
	int	i;

	i = 0;
	while (i < f->process_count)
	{
		waitpid(f->pids[i], &f->status, 0);
		i++;
	}
	close(f->infile);
	free(f->pids);
}

int	main(int argc, char **argv, char **env)
{
	t_files	f;

	if (argc > 3)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		{
			if (argc != 6)
			{
				ft_put_str_error("NOT ENOUGH ARGS FOR HEREDOC\n");
				return (1);
			}	
			if (run_here_doc(argv[2], &f) == 1)
			{
				ft_put_str_error("COULD NOT CREATE FILE FOR HEREDOC\n");
				return (2);
			}
		}
		else
			f.here_doc = 0;
		if (init_process(argc, argv, &f) == 1)
			return (3);
		if (calling_the_execs(argc, argv, env, &f) == 1)
			return (4);
		wait_for_pids(&f);
	}
	else
		ft_put_str_error("Pipex usage : ./pipex in_file cmd1...cmd2 out_file\n");
	return (0);
}
