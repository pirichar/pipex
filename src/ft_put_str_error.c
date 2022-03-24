/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:07:53 by pirichar          #+#    #+#             */
/*   Updated: 2022/03/24 13:58:35 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_err_putchar(char c)
{
	write (2, &c, 1);
}

void	ft_put_str_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_err_putchar(str[i]);
		i++;
	}
}
