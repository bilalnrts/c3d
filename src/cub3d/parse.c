#include "../../inc/cub3.h"

void	ft_init_map(t_map *map, char *path)
{
	map->map = NULL;
	map->buffer = NULL;
	map->fd = open(path, O_RDONLY); //check if file exists
	map->map_width = 0;
	map->map_height = 0;
	map->buffer_height = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map -> start_position = UNKNOWN;
	ft_create_map(map);
}

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

int ft_render_next_frame(t_map *map)
{
	ft_move(map);
	ft_raycast(map);
	mlx_put_image_to_window(map->mlx, map->img.window, map->img.image, 0, 0);
	return (0);
}

int main(int ac, char **av) {
	t_map	*map;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	ft_check_map_name(av[1]);
	map = malloc(sizeof(t_map));
	ft_init_map(map, av[1]);
    map->map_width = 33;
    map->map_height = 14;
	ft_mlx_init(map);
	mlx_hook(map->img.window, 2, 0, ft_press_key, map);
	mlx_hook(map->img.window, 3, 0, ft_release_key, map);
	mlx_hook(map->img.window, 17, 1L << 2, ft_close, map);
	mlx_loop_hook(map->mlx, &ft_render_next_frame, map);
	// free(map);
	mlx_loop(map->mlx);
	mlx_destroy_window(map->mlx, map->img.window);
	mlx_destroy_image(map->mlx, map->img.image);
	return (0);
}
