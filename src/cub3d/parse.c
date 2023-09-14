/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:52:13 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 20:46:24 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_init_map(t_map *map, char *path)
{
	map->map = NULL;
	map->buffer = NULL;
	map->fd = open(path, O_RDONLY);
	map->map_width = 0;
	map->map_height = 0;
	map->buffer_height = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map -> start_position = UNKNOWN;
	ft_create_map(map);
}

void	ft_check_map_name(char *map_name)
{
	int	map_name_lenght;

	map_name_lenght = ft_strlen(map_name);
	if (ft_strncmp(map_name + map_name_lenght - 4, ".cub", 4))
	{
		printf("The map name is not valid !\nError !");
		exit(1);
	}
}

int	ft_render_next_frame(t_map *map)
{
	ft_move(map);
	ft_raycast(map);
	mlx_put_image_to_window(map->mlx, map->img.window, map->img.image, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	ft_check_map_name(av[1]);
	map = malloc(sizeof(t_map));
	ft_init_map(map, av[1]);
	ft_mlx_init(map);
	mlx_hook(map->img.window, 2, 0, ft_press_key, map);
	mlx_hook(map->img.window, 3, 0, ft_release_key, map);
	mlx_hook(map->img.window, 17, 1L << 2, ft_close, map);
	mlx_loop_hook(map->mlx, &ft_render_next_frame, map);
	mlx_loop(map->mlx);
	ft_free_all(map);
	free(map);
	mlx_destroy_window(map->mlx, map->img.window);
	mlx_destroy_image(map->mlx, map->img.image);
	return (0);
}
