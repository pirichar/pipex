/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:30 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/31 12:59:03 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
#include "../include/pipex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

char	*get_next_line(int fd);
char	*free_stuff(char *saved, char *new_line);
char	*ft_strchr(const char *s, int c);
char	*read_file(int fd, char *saved, char **new_line);

#endif
