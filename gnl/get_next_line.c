/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:27 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/25 12:57:25 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *saved, char **new_line)
{
	char			*buff;
	ssize_t			ret;

	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE)
	{
		buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[ret] = '\0';
		saved = ft_strjoin_free(saved, buff);
		free (buff);
		*new_line = ft_strchr(saved, '\n');
		if (*new_line)
			break ;
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	static char		*saved[1024];
	char			*rtn;
	char			*new_line;

	saved[fd] = read_file(fd, saved[fd], &new_line);
	if (saved[fd] == NULL)
		return (NULL);
	if (new_line)
	{
		rtn = ft_substr(saved[fd], 0, (new_line - saved[fd] + 1));
		saved[fd] = free_stuff(saved[fd], new_line);
	}
	else
	{
		rtn = saved[fd];
		saved[fd] = NULL;
		if (!*rtn)
		{
			free(rtn);
			rtn = NULL;
		}
	}
	return (rtn);
}

/*
	Free_stuff va prendre le saved et prendre ce qu'il reste après le new_line
	Je pars de new_line qui pointe au new line
	C'est mon premier paramètre
	Le 2e est 1 car je veux partir après le new line
	Finalemnent je coupe la phrase pour la longueur de mon new line
	
*/

char	*free_stuff(char *saved, char *new_line)
{
	char	*tmp;

	tmp = ft_substr(new_line, 1, ft_strlen(new_line));
	if (!*tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	free(saved);
	saved = tmp;
	return (saved);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = c;
	while (*s != c2 && *s)
		s++;
	if (*s == c2)
		return ((char *)s);
	return (0);
}
