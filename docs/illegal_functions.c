/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illegal_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:59:43 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/06 11:12:40 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_strarr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		fprintf(stderr, "%d = %s", i, str[i]);
		fprintf(stderr, "\n");
		i++;
	}
}
