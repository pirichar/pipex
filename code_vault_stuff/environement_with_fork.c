#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./code_vault_stuff/colors.h"

/*
	To use this program just ./a.out + the name of the exec you are looking for
	example : ./a.out ping
*/

int	ft_w_counts(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			count ++;
		else if (s[i] != c && s[i - 1] == c)
			count ++;
		i++;
	}
	return (count);
}

char	*ft_fill_word(const char *s, int *pos, char c)
{
	char	*rtn;
	int		i;
	int		start;
	int		end;

	i = *pos;
	while (s[i] && s[i] == c)
		i++;
	start = i;
	while (s[i] && s[i + 1] != c)
		i++;
	end = i;
	*pos = i + 1;
	rtn = malloc(sizeof(char) * (end - start + 2));
	if (!rtn)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		rtn[i] = s[start];
		i++;
		start++;
	}	
	rtn[i] = '\0';
	return (rtn);
}

char	**ft_split(const char *s, char c)
{
	char	**rtn;
	int		w_count;
	int		pos;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	pos = 0;
	w_count = ft_w_counts(s, c);
	rtn = malloc(sizeof(char *) * (w_count + 1));
	if (!rtn)
		return (NULL);
	while (i < w_count)
	{
		rtn[i] = ft_fill_word(s, &pos, c);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (src[count])
	{
		count++;
	}
	if (size > 0)
	{
		while (src[i] && size != 0 && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

unsigned int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	print_strarr(char **str)
{
	int i;
	i = 0;

	while (str[i])
	{
		printf("%d = %s", i, str[i]);
		printf("\n");
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

char **env_to_strarr(char **param)
{
	int i;
	int len;
	char *path;
	char **p_arr;

	len = strlen_path(param);
	path = malloc(sizeof(char) * len);
	i = 0;
	while(param[i])
	{
		if (ft_strncmp(param[i], "PATH=", 5) == 0)
		{
			ft_strlcpy(path, param[i], len);
			p_arr = ft_split(path + 5, ':');
		}
			i++;
	}
	free (path);
	return (p_arr);
}

bool	search_argv1(char *p_arr, char *argv1)
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

int main(int argc, char **argv, char **env)
{
	char **p_arr;
	int i;
	int pid;

	if (argc > 1)
	{
		p_arr = env_to_strarr(env);
		print_strarr(p_arr);
		i = 0;
		while(p_arr[i])
		{
			if (search_argv1(p_arr[i], argv[1]) == true)
			{
				printf(GRN"\nWe found the command at i %d\n"RESET, i);
				strarr_free(p_arr);
				return (0);
			}
			i++;
		}
		printf(RED"We did not found the program your were looking for\n"RESET);
		strarr_free(p_arr);
		return (0);
	}
	else
		printf("Usage = ./a.out \"name of the program to search\"");
}