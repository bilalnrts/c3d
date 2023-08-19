#include "../../inc/cub3.h"

void	ft_set_directions(t_map *map, int i, int checker)
{
	while (map -> buffer[i])
	{
		if (!ft_strncmp(map -> buffer[i], "SO ", 3) && ++checker)
			map -> so_texture = ft_strdup(map -> buffer[i] + 3);
		else if (ft_strncmp(map -> buffer[i], "NO ", 3) == 0 && ++checker) // LAN NİYE GİRMİYOR BU KOŞULA
			map -> no_texture = ft_strdup(map -> buffer[i] + 3);
		else if (!ft_strncmp(map -> buffer[i], "WE ", 3) && ++checker)
			map -> we_texture = ft_strdup(map -> buffer[i] + 3);
		else if (!ft_strncmp(map -> buffer[i], "EA ", 3) && ++checker)
			map -> ea_texture = ft_strdup(map -> buffer[i] + 3);
		else if (!ft_strncmp(map -> buffer[i], "F ", 2) && ++checker)
			map -> f_color_rgb = ft_strdup(map -> buffer[i] + 2);
		else if (!ft_strncmp(map -> buffer[i], "C ", 2) && ++checker)
			map -> c_color_rgb = ft_strdup(map -> buffer[i] + 2);
		i++;
	}
	if (checker != 6)
	{
		ft_printf("Error\nWrong number of directions or FC colors");
		exit(1); //leak maybe
	}
	map -> map_height = i;
}

void	ft_create_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
	{
		ft_printf("Error\nEmpty file");
		exit(1); //leak maybe
	}
	while (line)
	{
		ft_join_buffer(map, line);
		free(line); //maybe error !! check here later !!
		line = get_next_line(map->fd);
	}
	ft_set_directions(map, 0, 0);
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
	free(map->buffer); //leak maybe
	map->buffer = new_buffer;
}
