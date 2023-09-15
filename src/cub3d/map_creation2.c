/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:25:38 by binurtas          #+#    #+#             */
/*   Updated: 2023/09/15 18:59:18 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_create_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
	{
		ft_printf("Error\nEmpty file");
		free(line);
		exit(1);
	}
	while (line)
	{
		ft_join_buffer(map, line);
		free(line);
		line = get_next_line(map->fd);
	}
	free(line);
	ft_set_directions(map, 0, 0);
	ft_find_start_map(map, 0, 0);
	ft_check_valid_map(map);
	ft_set_width(map);
}

void	ft_join_buffer(t_map *map, char *line)
{
	int		i;
	char	**new_buffer;

	i = 0;
	if (!map->buffer)
	{
		map->buffer = malloc(sizeof(char *) * 2);
		map->buffer[0] = ft_strdup(line);
		map->buffer[1] = NULL;
		return ;
	}
	while (map->buffer[i])
		i++;
	new_buffer = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (map->buffer[i])
	{
		new_buffer[i] = ft_strdup(map->buffer[i]);
		free(map->buffer[i]);
		i++;
	}
	new_buffer[i] = ft_strdup(line);
	new_buffer[i + 1] = NULL;
	free(map->buffer);
	map->buffer = new_buffer;
}
