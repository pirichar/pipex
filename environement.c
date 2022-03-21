#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

int ft_strlen(const char *str)
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

char **env_to_strarr(char **param)
{
	int i;
	char *path;
	char *tmp;
	char **p_arr;

	//here I should probably look for the strlen of the path and malloc that instead
	path = malloc(sizeof(char) * 1000);
	i = 0;
	while(param[i])
	{
		if (ft_strncmp(param[i], "PATH=", 5) == 0)
		{
			ft_strlcpy(path, param[i],1000);
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

int main(int argc, char **argv, char **env)
{
	char **p_arr;
	char *vec[100];

	vec[0] = "/sbin/ping";
	vec[1] = "google.com";
	vec[2] = "-c";
	vec[3] = "3";
 	vec[4] = NULL;

	p_arr = env_to_strarr(env);
	print_strarr(p_arr);
	// printf("==================================================================================\n");
	// print_strarr(env);
	// printf("==================================================================================\n");
	
	int i = 0;
	//do i use strjoin to join the name of my command to my 
	while(p_arr[i])
	{
		char *line = ft_strjoin(p_arr[i], "/ping");
		// printf("This is line %s for the turn %d\n", line , i);
		 if (access(line, X_OK) == 0)
				 printf("We found the command at the string i %d\n", i);
		free(line);
		i++;
	}
	// execve("/sbin/ping",vec, p_arr);
	strarr_free(p_arr);
	return (0);
}