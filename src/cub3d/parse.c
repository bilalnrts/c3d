#include "../../inc/cub3.h"

void	ft_init_map(t_map *map, char *path)
{
	map->map = NULL;
	map->buffer = NULL;
	map->fd = open(path, O_RDONLY); //check if file exists
	map->map_width = 0;
	map->map_height = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->f_color_rgb = NULL;
	map->c_color_rgb = NULL;
	ft_create_map(map);
}

int main(int ac, char **av) {
	t_map	*map;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	map = malloc(sizeof(t_map));
	ft_init_map(map, av[1]);

	return (0);
}
