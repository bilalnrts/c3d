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
	free(map);
	system("leaks cub3d");
	return (0);
}
