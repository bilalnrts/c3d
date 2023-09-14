#include "../../inc/cub3.h"

void	ft_is_map_letters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map -> map && map -> map[i])
	{
		j = 0;
		while (map -> map[i][j])
		{
			if (map -> map[i][j] == 'N'
				|| map -> map[i][j] == 'S'
				|| map -> map[i][j] == 'W'
				|| map -> map[i][j] == 'E'
				|| map -> map[i][j] == '0'
				|| map -> map[i][j] == '1'
				|| map -> map[i][j] == '2'
				|| map -> map[i][j] == '\n')
				j++;
			else
			{
				printf("Error !\nThere is an unrecognizable letter on the map !\n");
				ft_free_all(map);
				exit(1);
			}
		}
		i++;
	}
}
