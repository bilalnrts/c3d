#include "../../inc/cub3.h"

char	ft_find_seperator(char *str, t_map *map)
{
	char	*new_line;
	char	seperetor;

	seperetor = 0;
	new_line = ft_strtrim(str, " \t\n");
	if (ft_strchr(new_line, ' '))
		seperetor = ' ';
	else if (ft_strchr(new_line, '\t'))
		seperetor = '\t';
	else
		ft_free_all_msg(map, "Error !\nThere is no seperetor in the F & C & Textures !\n");
	free(new_line);
	return (seperetor);
}

int	ft_is_texture(char *t)
{
	char	*newT;
	int		returnVal;

	returnVal = 0;
	newT = ft_strtrim(t, " \t");
	if (!ft_strncmp(newT, "NO ", 3)) // if \t ???
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

char	*ft_get_texture(char *line, t_map *map)
{
	int		i;
	char	**buffer;
	char	*texture;
	char	*new_line;

	i = 0;
	buffer = NULL;
	new_line = ft_strtrim(line, " \t\n");
	buffer = ft_split(new_line, ft_find_seperator(new_line, map));
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

void	ft_set_directions(t_map *map, int i, int checker)
{
	while (map -> buffer[i])
	{
		if (ft_is_texture(map -> buffer[i]) == 1 && ++checker)
			map -> no_texture = ft_get_texture(map -> buffer[i], map);
		else if (ft_is_texture(map -> buffer[i]) == 2 && ++checker)
			map -> so_texture = ft_get_texture(map -> buffer[i], map);
		else if (ft_is_texture(map -> buffer[i]) == 3 && ++checker)
			map -> we_texture = ft_get_texture(map -> buffer[i], map);
		else if (ft_is_texture(map -> buffer[i]) == 4 && ++checker)
			map -> ea_texture = ft_get_texture(map -> buffer[i], map);
		else if (ft_is_texture(map -> buffer[i]) == 5 && ++checker)
			ft_get_color(map -> buffer[i], map);	//map -> f_color_rgb = ft_get_texture(map -> buffer[i]); ft_get_color(map -> buffer[i]);
		else if (ft_is_texture(map -> buffer[i]) == 6 && ++checker)
			ft_get_color(map -> buffer[i], map);	//map -> c_color_rgb = ft_get_texture(map -> buffer[i]);
		i++;
	}
	if (checker != 6)
	{
		ft_printf("Error\nWrong number of directions or FC colors");
		ft_free_all(map);
		exit(1);
	}
	map -> buffer_height = i;
}
