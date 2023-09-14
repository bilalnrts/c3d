/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:50:13 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 19:50:28 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_init_player(t_map *map)
{
	t_player	*player;

	player = map->player;
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->move_no = 0;
	player->move_so = 0;
	player->move_we = 0;
	player->move_ea = 0;
	player->turn = 0;
	player->speed = 0.06;
}

void	ft_set_player_position(t_map *map, char c, int x, int y)
{
	map->player = malloc(sizeof(t_player));
	ft_init_player(map);
	if (map -> start_position != UNKNOWN)
	{
		printf("Error !\nThere must be only one player on the map !\n");
		ft_free_all(map);
		exit(1);
	}
	if (c == 'N')
		map -> start_position = WEST;
	else if (c == 'S')
		map -> start_position = EAST;
	else if (c == 'W')
		map -> start_position = NORTH;
	else if (c == 'E')
		map -> start_position = SOUTH;
	map->player->y = 1.0 * x + 0.5;
	map->player->x = 1.0 * y + 0.5;
}

void	ft_check_player(t_map *map)
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
				|| map -> map[i][j] == 'W' || map -> map[i][j] == 'E')
				ft_set_player_position(map, map -> map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (map -> start_position == UNKNOWN)
	{
		printf("Error !\nThere must be a player in the map !\n");
		ft_free_all(map);
		exit(1);
	}
}
