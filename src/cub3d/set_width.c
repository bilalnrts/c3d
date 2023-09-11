#include "../../inc/cub3.h"

void	ft_find_max_width(t_map *map)
{
	int	max_index;
	int	max_width;
	int	current_width;
	int	i;

	i = 0;
	max_index = 0;
	max_width = 0;
	while (map -> map[i])
	{
		current_width = ft_strlen(map -> map[i]);
		if (current_width > max_width)
		{
			max_width = current_width;
			max_index = i;
		}
		i++;
	}
	map -> max_index = max_index;
	map -> max_width = max_width;
}

void	ft_fill(t_map *map, int i, int len)
{
	int		fill_len;
	char	*new_line;
	int		j;

	fill_len = map -> max_width - len;
	new_line = malloc(map -> max_width);
	j = 0;
	while (map -> map[i][j])
	{
		new_line[j] = map -> map[i][j];
		j++;
	}
	while (fill_len)
	{
		new_line[j] = '2';
		j++;
		fill_len--;
	}
	new_line[j] = '\0';
	free(map -> map[i]);
	map -> map[i] = new_line;
}

void	ft_set_width(t_map *map)
{
	int	i;
	int	current_line;

	ft_find_max_width(map);
	i = 0;
	while (map -> map[i])
	{
		current_line = ft_strlen(map -> map[i]);
		if (current_line < map -> max_width)
			ft_fill(map, i, current_line);
		i++;
	}
}
