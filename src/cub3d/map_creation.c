/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:25:38 by binurtas          #+#    #+#             */
/*   Updated: 2023/09/15 19:09:12 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_get_map(t_map *map, int i)
{
	int		j;

	if (map -> buffer_height - i == 0)
	{
		printf("Error !\nThis is not playable map !");
		ft_free_buffer(map);
		exit(1);
	}
	map -> map_height = map -> buffer_height - i;
	map -> map = malloc(sizeof(char *) * (map -> map_height + 1));
	j = 0;
	while (map -> buffer[i])
	{
		map -> map[j] = modificate_line(map -> buffer[i], -1, 0);
		i++;
		j++;
	}
	map -> map[j] = NULL;
}

char	*ft_seperate_line(char *line, char c)
{
	char	**spr;
	char	*new_line;
	int		i;

	spr = ft_split(line, c);
	new_line = ft_strdup(spr[0]);
	i = 0;
	while (spr[i])
	{
		free(spr[i]);
		i++;
	}
	free(spr);
	free(line);
	return (new_line);
}

void	ft_check_other_letter(t_map *map, int i)
{
	int	j;

	while (map->buffer[i])
	{
		j = -1;
		while (map->buffer[i][++j])
			if (!(map->buffer[i][j] == '\n' || map->buffer[i][j] == ' '
			|| map->buffer[i][j] == '\t' || map->buffer[i][j] == '0'
			|| map->buffer[i][j] == '1' || map->buffer[i][j] == 'N'
			|| map->buffer[i][j] == 'S' || map->buffer[i][j] == 'W'
			|| map->buffer[i][j] == 'E'))
				ft_free_all_msg(map, "Error\nThis map have invalid characters");
		i++;
	}
}

void	ft_find_start_map(t_map *map, int i, int checker)
{
	while (map -> buffer[i] && checker < 6)
	{
		i = ft_start_map_helper(map -> buffer[i], &checker, i);
		if (i == -1)
			break ;
	}
	if (checker != 6)
		ft_free_all_msg(map, "Error\nThis map have invalid syntax");
	while (map -> buffer[i] && ft_strlen(map -> buffer[i]) == 1
		&& map -> buffer[i][0] == '\n')
		i++;
	ft_check_other_letter(map, i);
	ft_get_map(map, i);
}
