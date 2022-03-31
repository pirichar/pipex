/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:47:29 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/31 08:45:19 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "colors.h"
#include <errno.h>

typedef struct s_files
{
	char	infile;
	char	outfile;
	int		*pids;
	int		process_count;
	int		status;
}				t_files;

typedef struct s_ptrs
{
	char	**path;
	char	*cmd_with_slash;
	char	**final_cmd;
	char	**cmd_split;
}				t_exec_ptrs;

bool	search_argv1(const char *p_arr, const char *argv1);
char	**path_to_strarr(char **param);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	print_strarr(char **str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_put_str_error(char *str);
int		calling_the_execs(int argc, char **argv, char **env, t_files *f);
void	execute_out(const char *cmd, int fds[2], int *p, char **env);
int		execute(const char *cmd, int fd_in, int *p, char **env);
void	parse_and_exec_cmd(const char *cmd, char **env);
char	**split_cmd(const char *path, const char *cmd);

#endif