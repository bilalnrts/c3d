/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:48:40 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 18:49:14 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

int	ft_line_lenght(char *line)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			total += 4;
		else
		{
			if (line[i] != '\n')
				total++;
		}
		i++;
	}
	return (total);
}

char	*modificate_line(char *line)
{
	int		i;
	int		j;
	int		limit;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(ft_line_lenght(line) + 1);
	while (line[i])
	{
		if (line[i] == '\t')
		{
			limit = 4;
			while (limit)
			{
				new_line[j] = '2';
				limit--;
				j++;
			}
		}
		else if (line[i] == ' ')
		{
			new_line[j] = '2';
			j++;
		}
		else
		{
			if (line[i] != '\n')
			{
				new_line[j] = line[i];
				j++;
			}
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
