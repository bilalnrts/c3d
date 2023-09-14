/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:15:26 by binurtas          #+#    #+#             */
/*   Updated: 2023/09/14 21:03:38 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_is_map_letters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map -> map && map -> map[i])
	{
		j = 0;
		while (map -> map[i][j])
		{
			if (map -> map[i][j] == 'N' || map -> map[i][j] == 'S'
				|| map -> map[i][j] == 'W' || map -> map[i][j] == 'E'
				|| map -> map[i][j] == '0' || map -> map[i][j] == '1'
				|| map -> map[i][j] == '2' || map -> map[i][j] == '\n')
				j++;
			else
			{
				printf("Error !\nThere is an unrecognizable \
					letter on the map !\n");
				ft_free_all(map);
				exit(1);
			}
		}
		i++;
	}
}

int	ft_start_map_checker(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	ft_start_map_helper(char *buffer, int *checker, int i)
{
	char	*line;

	line = ft_strtrim(buffer, " \t");
	if (ft_strchr(line, ' '))
		line = ft_seperate_line(line, ' ');
	else if (ft_strchr(line, '\t'))
		line = ft_seperate_line(line, '\t');
	if (line && ft_start_map_checker(line))
		*checker += 1;
	else if (line && ft_strlen(buffer) > 1 && !ft_start_map_checker(line))
	{
		free(line);
		return (-1);
	}
	free(line);
	i++;
	return (i);
}
