/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:47:29 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/23 16:21:45 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "colors.h"

typedef struct s_files
{
	char file;
	char outfile;
}				t_files;

typedef struct s_ptrs
{
	char **path;
	char *cmd_with_slash;
	char **final_cmd;
	char **cmd_split;
}				t_ptrs;

bool	search_argv1(const char *p_arr, const char *argv1);
char 	**path_to_strarr(char **param);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	print_strarr(char **str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

