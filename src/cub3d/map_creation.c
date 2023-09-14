/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:25:38 by binurtas          #+#    #+#             */
/*   Updated: 2023/09/14 20:58:52 by binurtas         ###   ########.fr       */
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
	ft_get_map(map, i);
}

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
