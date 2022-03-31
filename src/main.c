/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:04:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/31 08:56:51 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_process(int argc, char **argv, t_files *f)
{
	f->process_count = (argc - 3);
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

/*
	./pipex here_doc LIMITER cmd cmd1 file
	argc is 6
	number of command is 2
	here doc is at argv[1]
	limiter is at argv[2]
	first cmd is at argv[3]
	second cmd is at argv[4]
	the output file is at argv[5]
	
	1- while you dont find delemiter get every line of text in stdin and put it in a string
	2- Should I put it in a file or not ?
	3- Then I could write that string into a pipe and then fork for the first cmd
	4- the first cmd will dup the stdin to the output of the pipe ?
	5- The last cmd will take the output of the pipe of the first comand and output to the output file
	
	when I see here_doc
	I need to read the stdin untill i see the delemiter again
	This would then be passed to the first command as the input 
	For the output par its pretty much the same but I need to change the rights
*/
void	run_here_doc(void)
{	
	/* 
		Open a temp file 
		do an infinite while loop
		get the next line
		each time check if you have only the limiter
		when you have the limiter pass the tmp file as the infile
	*/
	// int file;

	// file = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC , 0777);

	ft_put_str_error("NOTHING TO DO YET CUZ PIER-LUC IS LAZY\n");
}

void	wait_for_pids(t_files *f)
{
	int i;

	i = 0;
	while (i < f->process_count)
	{
		waitpid(f->pids[i], &f->status, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_files	f;

	if (argc > 3)
	{
		if (ft_strncmp(argv[1], "here_doc",9) == 0)
		{
			run_here_doc();
			return (2);
		}
		else
			f.here_doc = 0;
		if (init_process(argc, argv, &f) == 1)
			return (1);
		if (calling_the_execs(argc, argv, env, &f) == 1)
			return (3);
		wait_for_pids(&f);
		close(f.infile);
		free(f.pids);
	}
	else
		ft_put_str_error("Pipex usage : ./pipex in_file cmd1...cmd2 out_file\n");
	return (0);
}


