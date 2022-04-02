/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:02:12 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/02 14:11:09 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
	./pipex here_doc LIMITER cmd cmd1 file
	argc is 6
	number of command is 2
	./pipex is argv[0]
	here doc is at argv[1]
	limiter is at argv[2]
	first cmd is at argv[3]
	second cmd is at argv[4]
	the output file is at argv[5]
	
	1- while you dont find delemiter get every line 
	of text in stdin and put it in a string
	2- Should I put it in a file or not ?
	3- Then I could write that string into a pipe
	 and then fork for the first cmd
	4- the first cmd will dup the stdin to the output of the pipe ?
	5- The last cmd will take the output of the pipe
	 of the first comand and output to the output file
	
	when I see here_doc
	I need to read the stdin untill i see the delemiter again
	This would then be passed to the first command as the input 
	For the output par its pretty much the same but I need to change the rights
*/
int	run_here_doc(char *limiter, t_files *f)
{	
	int		file;
	char	*buf;

	file = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file == -1)
		return (1);
	while (1)
	{
		write(1, "heredoc>", 9);
		buf = get_next_line(0);
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		write(file, buf, ft_strlen(buf));
		free (buf);
	}
	free (buf);
	close(file);
	f->infile = open("here_doc", O_RDONLY);
	if (f->infile == -1)
	{
		ft_put_str_error("Could not open input file\n");
		free (f->pids);
	}
	f->here_doc = 1;
	return (0);
}
	//I COULD HANDLE ALL THE CASES WITH MULTIPLE CMD JUST BY 
	//AADDING J = 4 and looping while j < argc - something
	// I should also change the last execute for argv[count -1]

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
