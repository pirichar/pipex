/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:04:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/28 18:29:49 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_process(int argc, char **argv, t_files *f)
{
	f->process_count = (argc - 3);
	f->pids = malloc(sizeof(int) * f->process_count);
	f->infile = open(argv[1], O_RDONLY);
	if (f->infile == -1)
	{
		ft_put_str_error("Could not open input file\n");
		free (f->pids);
		return (1);
	}
	return (0);
}
/*
	when I see here_doc
	I need to read the stdin untill i see the delemiter again
	This would then be passed to the first command as the input 
	For the output par its pretty much the same but I need to change the rights
*/
void	run_here_doc(void)
{
	//dans l'exemple il utilisent << et >>
	// >> va append le fichier au lieu de simplement overwrite
	// il faudra donc que le outfile soit ouvert différament
	// il creer toujours le file sil nexiste pas mais nappend pas

	ft_put_str_error("NOTHING TO DO YET CUZ PIER-LUC IS LAZY\n");
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_files	f;

	if (argc > 3)
	{
		if (ft_strncmp(argv[1], "here_doc",9) == 0)
		{
			run_here_doc();
			return (2);
		}
		if (init_process(argc, argv, &f) == 1)
			return (1);
		if (calling_the_execs(argc, argv, env, &f) == 1)
			return (3);
		i = 0;
		while (i < f.process_count)
		{
			waitpid(f.pids[i], &f.status, 0);
			i++;
		}
		close(f.infile);
		free(f.pids);
	}
	else
		ft_put_str_error("Pipex usage : ./pipex in_file cmd1...cmd2 out_file\n");
	return (0);
}
