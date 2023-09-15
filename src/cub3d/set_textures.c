/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:39:54 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/15 17:33:41 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_free_all_msg(map, "Error !\nThere is no seperetor\
			in the F & C & Textures !\n");
	free(new_line);
	return (seperetor);
}

int	ft_is_texture(char *t)
{
	char	*new_t;
	int		return_val;

	return_val = 0;
	new_t = ft_strtrim(t, " \t");
	if (!ft_strncmp(new_t, "NO ", 3) || !ft_strncmp(new_t, "NO	", 3))
		return_val = 1;
	else if (!ft_strncmp(new_t, "SO ", 3) || !ft_strncmp(new_t, "SO	", 3))
		return_val = 2;
	else if (!ft_strncmp(new_t, "WE ", 3) || !ft_strncmp(new_t, "WE	", 3))
		return_val = 3;
	else if (!ft_strncmp(new_t, "EA ", 3) || !ft_strncmp(new_t, "EA	", 3))
		return_val = 4;
	else if (!ft_strncmp(new_t, "F ", 2) || !ft_strncmp(new_t, "F	", 2))
		return_val = 5;
	else if (!ft_strncmp(new_t, "C ", 2) || !ft_strncmp(new_t, "C	", 2))
		return_val = 6;
	free(new_t);
	return (return_val);
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
	buffer = ft_texture_split(new_line, ft_find_seperator(new_line, map));
	free(new_line);
	if (buffer && buffer[1])
	{
		new_line = ft_strtrim(buffer[1], " \t");
		texture = ft_strdup(new_line);
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

int	ft_check_texture_is_full(t_map *map)
{
	if (map->c_color_rgb != -1 && map->f_color_rgb != -1 && map->no_texture
		&& map->so_texture && map->we_texture && map->ea_texture)
		return (1);
	return (0);
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
			ft_get_color(map -> buffer[i], map, -1);
		else if (ft_is_texture(map -> buffer[i]) == 6 && ++checker)
			ft_get_color(map -> buffer[i], map, -1);
		i++;
	}
	if (!ft_check_texture_is_full(map) || checker != 6)
	{
		ft_printf("Error\nWrong number of directions or F&C colors");
		ft_free_buffer(map);
		ft_free_textures(map);
		exit(1);
	}
	map -> buffer_height = i;
}
