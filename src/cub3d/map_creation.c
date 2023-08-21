#include "../../inc/cub3.h"

char	*ft_get_texture(char *line)
{
	int		i;
	char	**buffer;
	char	*texture;

	i = 0;
	buffer = NULL;
	line = ft_strtrim(line, " \t");
	if (ft_strchr(line, ' '))
		buffer = ft_split(line, ' '); //leak maybe
	else if (ft_strchr(line, '\t'))
		buffer = ft_split(line, '\t'); //leak maybe
	if (buffer && buffer[1])
	{
		texture = ft_strdup(buffer[1]);
		while (buffer[i])
		{
			free(buffer[i]);
			i++;
		}
		free(buffer);
		return (texture);
	}
	return (NULL);
}
void	ft_set_directions(t_map *map, int i, int checker)
{
	while (map -> buffer[i])
	{
		if (!ft_strncmp(map -> buffer[i], "SO ", 3) && ++checker)
			map -> so_texture = ft_get_texture(map -> buffer[i]);
		else if (ft_strncmp(map -> buffer[i], "NO ", 3) == 0 && ++checker)
			map -> no_texture = ft_get_texture(map -> buffer[i]);
		else if (!ft_strncmp(map -> buffer[i], "WE ", 3) && ++checker)
			map -> we_texture = ft_get_texture(map -> buffer[i]);
		else if (!ft_strncmp(map -> buffer[i], "EA ", 3) && ++checker)
			map -> ea_texture = ft_get_texture(map -> buffer[i]);
		else if (!ft_strncmp(map -> buffer[i], "F ", 2) && ++checker)
			map -> f_color_rgb = ft_get_texture(map -> buffer[i]);
		else if (!ft_strncmp(map -> buffer[i], "C ", 2) && ++checker)
			map -> c_color_rgb = ft_get_texture(map -> buffer[i]);
		i++;
	}
	if (checker != 6)
	{
		ft_printf("Error\nWrong number of directions or FC colors");
		exit(1); //leak maybe
	}
	map -> map_height = i;
}

void	ft_get_map(t_map *map, int i)
{
	int		j;
	map -> map = malloc(sizeof(char *) * (map -> map_height - i + 1));
	j = 0;
	while (map -> buffer[i])
	{
		map -> map[j] = modificate_line(map -> buffer[i]);
		i++;
		j++;
	}
	map -> map[j] = NULL;	//map artık hazır
}

void	ft_find_start_map(t_map *map, int i, int checker)
{
	char	*line;

	while (map -> buffer[i])
	{
		if (checker == 6)
			break ;
		line = ft_strtrim(map -> buffer[i], " \t");
		if (ft_strchr(line, ' '))
			line = ft_split(line, ' ')[0]; //leak maybe
		else if (ft_strchr(line, '\t'))
			line = ft_split(line, '\t')[0]; //leak maybe
		if (line && (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
			checker++;
		free(line);
		i++;
	}
	while (map -> buffer[i] && ft_strlen(map -> buffer[i]) == 1 && map -> buffer[i][0] == '\n')
		i++;
	// checker'ın 6 olması lazım daha sonra kontrol et
	// C ya da F map dosyasının en altındaysa checker yine 6 olacak !!
	ft_get_map(map, i);
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
	} // close fd
	ft_set_directions(map, 0, 0);
	ft_find_start_map(map, 0, 0);
	ft_check_valid_map(map);
	printf("This is a valid map\n");
	printf("NO: %s", map -> no_texture);
	printf("SO: %s", map -> so_texture);
	printf("WE: %s", map -> we_texture);
	printf("EA: %s", map -> ea_texture);
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
