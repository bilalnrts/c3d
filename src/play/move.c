/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:58:02 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 17:58:02 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_move_east_west(t_map *map, int dir)
{
	if (map->map[(int)(map->player->y)][(int)(map->player->x
			- dir * map->player->dir_y * map->player->speed)] < '1')
		map->player->x -= dir * map->player->dir_y * map->player->speed;
	if (map->map[(int)(map->player->y + dir * map->player->dir_x
			* map->player->speed)][(int)(map->player->x)] < '1')
		map->player->y += dir * map->player->dir_x * map->player->speed;
}

void	ft_move_north_south(t_map *map, int dir)
{
	if (map->map[(int)(map->player->y)][(int)(map->player->x
			+ dir * map->player->dir_x * map->player->speed)] < '1')
		map->player->x += dir * map->player->dir_x * map->player->speed;
	if (map->map[(int)(map->player->y + dir * map->player->dir_y
			* map->player->speed)][(int)(map->player->x)] < '1')
		map->player->y += dir * map->player->dir_y * map->player->speed;
}

void	ft_turn(t_map *map, int dir)
{
	double	old_dir_x;
	double	old_plane_x;

	map->player->speed /= 2;
	old_dir_x = map->player->dir_x;
	old_plane_x = map->player->plane_x;
	map->player->dir_x = map->player->dir_x * cos(dir * map->player->speed)
		- map->player->dir_y * sin(dir * map->player->speed);
	map->player->dir_y = old_dir_x * sin(dir * map->player->speed)
		+ map->player->dir_y * cos(dir * map->player->speed);
	map->player->plane_x = map->player->plane_x * cos(dir * map->player->speed)
		- map->player->plane_y * sin(dir * map->player->speed);
	map->player->plane_y = old_plane_x * sin(dir * map->player->speed)
		+ map->player->plane_y * cos(dir * map->player->speed);
	map->player->speed *= 2;
}

void	ft_move(t_map *map)
{
	if (map->player->move_ea == 1)
		ft_move_east_west(map, 1);
	else if (map->player->move_we == 1)
		ft_move_east_west(map, -1);
	if (map->player->move_no == 1)
		ft_move_north_south(map, 1);
	else if (map->player->move_so == 1)
		ft_move_north_south(map, -1);
	if (map->player->turn == LEFT)
		ft_turn(map, LEFT);
	else if (map->player->turn == RIGHT)
		ft_turn(map, RIGHT);
}
