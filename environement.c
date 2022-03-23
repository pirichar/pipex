/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:13:03 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/23 16:17:13 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

void	print_strarr(char **str)
{
	int i;
	i = 0;

	while (str[i])
	{
		fprintf(stderr, "%d = %s", i, str[i]);
		fprintf(stderr, "\n");
		i++;
	}
}

void	strarr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	strlen_path(char **env)
{
	int i;
	int rtn;

	i = 0;
	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			rtn = ft_strlen(env[i]);
			return (rtn);
		}
		i++;
	}
	return (1);
}

char **path_to_strarr(char **param)
{
	int i;
	int len;
	char *path;
	char *tmp;
	char **p_arr;

	len = strlen_path(param);
	path = malloc(sizeof(char) * len);
	i = 0;
	while(param[i])
	{
		if (ft_strncmp(param[i], "PATH=", 5) == 0)
		{
			ft_strlcpy(path, param[i], len);
			tmp = path;
			while(*path != '/')
				(*path)++;
			p_arr = ft_split(path + 5, ':');
		}
			i++;
	}
	free (tmp);
	return (p_arr);
}

bool	search_argv1(const char *p_arr, const char *argv1)
{
	char *line;
	char *with_slash;

	with_slash = ft_strjoin("/", argv1);
	line = ft_strjoin(p_arr, with_slash);
	if (access(line, X_OK) == 0)
	{
		free(line);
		free(with_slash);
		return (true);
	}
	free(line);
	free(with_slash);
	return (false);
}
