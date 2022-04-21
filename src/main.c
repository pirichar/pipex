/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:04:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/21 10:38:44 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
	Takes as input argument count, argument vector and a pointer to the struct f
	it will init the process count;  malloc the array for the process 
	Finally it will take care of opening the infile passed in argv1
*/
static void	init_process(int argc, char **argv, t_files *f)
{
	f->process_count = (argc - 4);
	f->pids = malloc(sizeof(int) * f->process_count);
	f->infile = open(argv[1], O_RDONLY);
	if (f->infile == -1)
	{
		ft_put_str_error("Could not open input file\n");
	}
}

/*
	Simple function that wait for all the pids to be done in the main
*/
static void	wait_for_pids(t_files *f)
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

/*
	My main function will :
	Init the structure needed for the processing
	Call the execs and return and error if it cant open the output file
	Wait for the pids 
	If you don't pass the proper amount of args it wont work
*/
int	main(int argc, char **argv, char **env)
{
	t_files	f;

	if (argc == 5)
	{
		init_process(argc, argv, &f);
		if (calling_the_execs(argc, argv, env, &f) == 1)
			return (3);
		wait_for_pids(&f);
	}
	else
		ft_put_str_error("Pipex usage : ./pipex in_file cmd1...cmd2 out_file\n");
	return (0);
}
