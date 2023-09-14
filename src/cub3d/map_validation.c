/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:04:39 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 20:28:33 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ft_free_all(map);
			exit(1);
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
	ft_is_map_letters(map);
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
	ft_check_player(map);
}

int	ft_check_around(t_map *map, int **directions, int i, int j)
{
	int	new_i;
	int	new_j;
	int	count;
	int	direction;

	count = 0;
	direction = 0;
	while (direction < 4)
	{
		new_i = i + directions[direction][0];
		new_j = j + directions[direction][1];
		while (map -> map[new_i][new_j])
		{
			if ((map -> map[new_i][new_j] == '1' && ++count)
				|| (map -> map[new_i][new_j] == '2'))
				break ;
			new_i += directions[direction][0];
			new_j += directions[direction][1];
		}
		direction++;
	}
	return (count);
}

void	ft_check_walls(t_map *map, int i, int j)
{
	int	checker;
	int	**directions;

	if (i == 0 || i == map->map_height - 1 || j == 0
		|| j == ft_line_lenght(map->map[i]) - 1)
		ft_free_all_msg(map, "Error\nMap is not surrounded by walls");
	directions = ft_give_directions(0, map);
	checker = ft_check_around(map, directions, i, j);
	i = 0;
	while (i < 4)
	{
		free(directions[i]);
		i++;
	}
	free(directions);
	if (checker != 4)
		ft_free_all_msg(map, "Error\nMap is not surrounded by walls");
}

int	**ft_give_directions(int i, t_map *map)
{
	int	**directions;

	directions = (int **)malloc(4 * sizeof(int *));
	if (!directions)
		ft_free_all_msg(map, "Memory Error!\n");
	while (i < 4)
	{
		directions[i] = (int *)malloc(2 * sizeof(int));
		if (directions[i] == NULL)
			ft_free_all_msg(map, "Memory Error!\n");
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
	return (directions);
}
