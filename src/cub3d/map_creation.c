#include "../../inc/cub3.h"

char	*ft_get_texture(char *line) // There is no leak here
{
	int		i;
	char	**buffer;
	char	*texture;
	char	*new_line;

	i = 0;
	buffer = NULL;
	new_line = ft_strtrim(line, " \t");
	if (ft_strchr(new_line, ' '))
		buffer = ft_split(new_line, ' ');
	else if (ft_strchr(new_line, '\t'))
		buffer = ft_split(new_line, '\t');
	if (buffer && buffer[1])
	{
		texture = ft_strdup(buffer[1]);
		while (buffer[i])
		{
			free(buffer[i]);
			i++;
		}
		free(buffer);
		free(new_line);
		return (texture);
	}
	return (NULL);
}

int	ft_is_texture(char *t)
{
	char	*newT;
	int		returnVal;

	returnVal = 0;
	newT = ft_strtrim(t, " \t");
	if (!ft_strncmp(newT, "NO ", 3))
		returnVal = 1;
	else if (!ft_strncmp(newT, "SO ", 3))
		returnVal = 2;
	else if (!ft_strncmp(newT, "WE ", 3))
		returnVal = 3;
	else if (!ft_strncmp(newT, "EA ", 3))
		returnVal = 4;
	else if (!ft_strncmp(newT, "F ", 2))
		returnVal = 5;
	else if (!ft_strncmp(newT, "C ", 2))
		returnVal = 6;
	free(newT);
	return (returnVal);
}

void	ft_set_directions(t_map *map, int i, int checker)
{
	while (map -> buffer[i])
	{
		if (ft_is_texture(map -> buffer[i]) == 1 && ++checker)
			map -> no_texture = ft_get_texture(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 2 && ++checker)
			map -> so_texture = ft_get_texture(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 3 && ++checker)
			map -> we_texture = ft_get_texture(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 4 && ++checker)
			map -> ea_texture = ft_get_texture(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 5 && ++checker)
			map -> f_color_rgb = ft_get_texture(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 6 && ++checker)
			map -> c_color_rgb = ft_get_texture(map -> buffer[i]);
		i++;
	}
	if (checker != 6)
	{
		ft_printf("Error\nWrong number of directions or FC colors");
		ft_free_map_buffer(map);
		exit(1);
	}
	map -> map_height = i;
}

void	ft_get_map(t_map *map, int i)
{
	int		j;

	if (!map -> map_height - i)
	{
		printf("Error !\nThis is not playable map !");
		//FREE MAP -> BUFFER FUNCTION
		exit(1);
	}
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

char	*ft_seperate_line(char *line, char c)
{
	char	**spr;
	char	*new_line;
	int		i;

	spr = ft_split(line, c);
	new_line = ft_strdup(spr[0]);
	i = 0;
	while (spr[i])
	{
		free(spr[i]);
		i++;
	}
	free(spr);
	free(line);
	return (new_line);
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
			line = ft_seperate_line(line, ' ');
		else if (ft_strchr(line, '\t'))
			line = ft_seperate_line(line, '\t');
		if (line && (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
			checker++;
		else if (line && ft_strlen(line) > 1 && (ft_strncmp(line, "NO", 2) || ft_strncmp(line, "SO", 2) || ft_strncmp(line, "WE", 2) || ft_strncmp(line, "EA", 2) || ft_strncmp(line, "F", 1) || ft_strncmp(line, "C", 1)))
		{
			free(line);
			break ;
		}
		free(line);
		i++;
	}
	if (checker != 6)
	{
		ft_printf("Error\nThis map have invalid syntax");
		ft_free_map_buffer(map);
		exit(1);
	}
	while (map -> buffer[i] && ft_strlen(map -> buffer[i]) == 1 && map -> buffer[i][0] == '\n')
		i++;
	ft_get_map(map, i);
}

void	ft_create_map(t_map *map) // There is no leak here !
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
	{
		ft_printf("Error\nEmpty file");
		free(line);
		exit(1);
	}
	while (line)
	{
		ft_join_buffer(map, line);
		free(line);
		line = get_next_line(map->fd);
	} // close fd
	free(line);
	ft_set_directions(map, 0, 0);
	ft_find_start_map(map, 0, 0);
	ft_check_valid_map(map);
	ft_free_map_buffer(map);
}

void	ft_join_buffer(t_map *map, char *line) // There is no leak here !
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
	free(map->buffer);
	map->buffer = new_buffer;
}
