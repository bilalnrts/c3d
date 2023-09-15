/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:52:13 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/15 18:05:51 by aderviso         ###   ########.fr       */
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
	map->f_color_rgb = -1;
	map->c_color_rgb = -1;
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

char	*ft_check_map_name_helper(char *str)
{
	char	*map_name;
	char	**buffer;
	int		i;

	buffer = NULL;
	i = 0;
	if (ft_strchr(str, '/'))
	{
		buffer = ft_split(str, '/');
		while (buffer[i])
			i++;
		map_name = ft_strdup(buffer[i - 1]);
	}
	else
		map_name = ft_strdup(str);
	if (buffer != NULL)
	{
		while (--i >= 0)
			free(buffer[i]);
		free(buffer);
	}
	return (map_name);
}

void	ft_check_map_name(char *str)
{
	char	*map_name;
	int		map_name_lenght;

	map_name = ft_check_map_name_helper(str);
	map_name_lenght = ft_strlen(map_name);
	if (ft_strncmp(map_name + map_name_lenght - 4, ".cub", 4)
		|| map_name_lenght < 5)
	{
		free(map_name);
		printf("Error !\nThe map name is not valid !\n");
		exit(1);
	}
	free(map_name);
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
