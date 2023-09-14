#include "../../inc/cub3.h"

void	ft_set_colors(t_map *map, char **buffer, char **colors)
{
	if (buffer[0][0] == 'F')
		map->f_color_rgb = ft_atoi(colors[0]) << 16 | ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]);
	else if(buffer[0][0] == 'C')
		map->c_color_rgb = ft_atoi(colors[0]) << 16 | ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]);
}

void	ft_is_rgb(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			ft_free_all_msg(map, "Error !\nColors must be numbers !\n");
	}
}

void	ft_get_color(char *line, t_map *map)
{
	char	**buffer;
	char	**colors;
	char	*newline;
	int		i;

	i = -1;
	newline = ft_strtrim(line, " \n\t");
	buffer = ft_split(newline, ft_find_seperator(newline, map));
	if (buffer && buffer[1])
	{
		colors = ft_split(buffer[1], ',');
		while (colors[++i])
			ft_is_rgb(colors[i], map);
		if (i != 3)
			ft_free_all_msg(map, "Error !\nColors must be rgb formatting !\n");
		ft_set_colors(map, buffer, colors);
		i = -1;
		while (colors[++i]) // --i
			free(colors[i]);
		free(colors);
	}
	i = -1;
	while (buffer[++i])
		free(buffer[i]);
	free(buffer);
	free(newline);
}
