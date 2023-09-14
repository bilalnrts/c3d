/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:18:58 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 18:18:58 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_init_raycast(t_map *map, int x)
{
	map->player->camera_x = 2 * x / (double)WIDTH - 1;
	map->player->ray_dir_x = map->player->dir_x
		+ map->player->plane_x * map->player->camera_x;
	map->player->ray_dir_y = map->player->dir_y
		+ map->player->plane_y * map->player->camera_x;
	map->player->map_x = (int)map->player->x;
	map->player->map_y = (int)map->player->y;
	if (map->player->ray_dir_x == 0)
		map->delta_dist_x = 1e30;
	else
		map->delta_dist_x = fabs(1 / map->player->ray_dir_x);
	if (map->player->ray_dir_y == 0)
		map->delta_dist_y = 1e30;
	else
		map->delta_dist_y = fabs(1 / map->player->ray_dir_y);
	map->hit = 0;
}

void	ft_calculate_step(t_map *map)
{
	if (map->player->ray_dir_x < 0)
	{
		map->step_x = -1;
		map->side_dist_x = (map->player->x - map->player->map_x)
			* map->delta_dist_x;
	}
	else
	{
		map->step_x = 1;
		map->side_dist_x = (map->player->map_x + 1.0 - map->player->x)
			* map->delta_dist_x;
	}
	if (map->player->ray_dir_y < 0)
	{
		map->step_y = -1;
		map->side_dist_y = (map->player->y - map->player->map_y)
			* map->delta_dist_y;
	}
	else
	{
		map->step_y = 1;
		map->side_dist_y = (map->player->map_y + 1.0 - map->player->y)
			* map->delta_dist_y;
	}
}

void	ft_calculate_side_dist(t_map *map)
{
	while (map->hit == 0)
	{
		if (map->side_dist_x < map->side_dist_y)
		{
			map->side_dist_x += map->delta_dist_x;
			map->player->map_x += map->step_x;
			map->side = 0;
		}
		else
		{
			map->side_dist_y += map->delta_dist_y;
			map->player->map_y += map->step_y;
			map->side = 1;
		}
		if (map->map[map->player->map_y][map->player->map_x] > '0')
			map->hit = 1;
	}
	if (map->side == 0)
		map->perp_wall_dist = (map->side_dist_x - map->delta_dist_x);
	else
		map->perp_wall_dist = (map->side_dist_y - map->delta_dist_y);
	map->line_height = (int)(HEIGHT / map->perp_wall_dist);
}

void	ft_raycast(t_map *map)
{
	int	x;

	x = -1;
	mlx_clear_window(map->mlx, map->img.window);
	while (++x < WIDTH)
	{
		ft_init_raycast(map, x);
		ft_calculate_step(map);
		ft_calculate_side_dist(map);
		ft_calculate_draw_start_end(map);
		ft_draw_texture(map, x);
	}
}
