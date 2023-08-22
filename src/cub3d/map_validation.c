#include "../../inc/cub3.h"

void	ft_is_there_enter_in_map(t_map *map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (map -> map[i])
	{
		if (map -> map[i][j] == '\n')
		{
			ft_printf("Error\nThere is an enter in the map");
			ft_free_map_buffer(map);
			exit(1); //leak maybe
		}
		i++;
	}
}

void	ft_check_valid_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_is_there_enter_in_map(map);
	while (map -> map[i])
	{
		j = 0;
		while (map -> map[i][j])
		{
			if (map -> map[i][j] == '0')
				ft_check_walls(map, i, j);
			j++;
		}
		i++;
	}
}

// 0'ları kontrol et 2 ya da 0 görmeden 1 görürsem problem yok.

void ft_check_walls(t_map *map, int i, int j)
{
	int checker;
	int	**directions;
	int	direction;

	if (i == 0 || i == map->map_height - 1 || j == 0 || j == ft_line_lenght(map->map[i]) - 1)
	{
		ft_printf("Error\nMap is not surrounded by walls");
		ft_free_map_buffer(map);
		exit(1);
	}
	directions = ft_give_directions(0, map); // memory leak !!!
	direction = 0;
	checker = 0;
	while (direction < 4)
	{
		int newI = i + directions[direction][0];
		int newJ = j + directions[direction][1];
		while (map -> map[newI][newJ])
		{
			if ((map -> map[newI][newJ] == '1' && ++checker) || (map -> map[newI][newJ] == '2'))
				break ;
			newI += directions[direction][0];
			newJ += directions[direction][1];
		}
		direction++;
	}
	i = 0;
	while (directions[i])
	{
		free(directions[i]);
		i++;
	}
	//free(directions);
	if (checker != 4)
	{
		ft_printf("Error\nMap is not surrounded by walls");
		ft_free_map_buffer(map);
		exit(1);
	}
}

int	**ft_give_directions(int i, t_map *map)
{
	int **directions;

	directions = (int **)malloc(4 * sizeof(int *));
	if (!directions)
	{
		printf("Memory Error!\n");
		ft_free_map_buffer(map);
		exit(1);
	}
	while (i < 4)
	{
		directions[i] = (int *)malloc(2 * sizeof(int));
		if (directions[i] == NULL)
		{
			printf("Memory Error!\n");
			ft_free_map_buffer(map);
			exit(1);
		}
		i++;
	}
	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	return directions;
}
